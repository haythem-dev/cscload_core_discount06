#include "customerhandler.h"

#include <logger/loggerpool.h>
#include <libbasarcmnutil_decimal.h>
#include <libbasarcmnutil_date.h>

#include "cscservicehelper.h"
#include <customer/componentmanager/customercomponentmanagerptr.h>
#include <customer/componentmanager/customercomponentmanager.h>
#include <customer/icustomerrepository.h>
#include <customer/icustomerptr.h>
#include <customer/icustomer.h>
#include <customer/customercondition/customerconditioncollectionptr.h>
#include <customer/customercondition/icustomerconditionptr.h>

#include <customer/tenderinfo/itenderinfo.h>
#include <customer/customercondition/icustomercondition.h>
#include <customer/articleinfo/articleinfo.h>
#include <customer/orderinfo/iorderinfo.h>
#include <customer/orderstatus/orderstatus.h>
#include <customer/pricesanddiscounts/pricesanddiscounts.h>
#include <customer/payments/payments.h>
#include <customer/paymentconditions/paymentconditions.h>
#include <customer/turnover/turnover.h>
#include <customer/changedquantities/changedquantities.h>
#include <customer/discountaccount/discountaccount.h>
#include <customer/promotions/promotions.h>
#include <customer/routes/routes.h>
#include <customer/tours/tours.h>
#include <customer/tours/weektours/weektours.h>

#include <types/messagecodeenum.inc>
#include <messagecodeenum_types.h>

#include <pxxmit.hpp>
#include "pxdelpos.hpp"
#include "pxartmas.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxsess.hpp"
#include "pxartprc.hpp"
#include "pxarticlecodes.hpp"

#include <discount/discountcollectionfinder/idiscountcollectionfinderptr.h>
#include <discount/discountcollectionfinder/idiscountcollectionfinder.h>
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>

namespace csc {
namespace service {

CustomerHandler::CustomerHandler()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CustomerHandler::CustomerHandler()");
}

CustomerHandler::~CustomerHandler()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CustomerHandler::~CustomerHandler()");
}

void CustomerHandler::processCustomerDetails(
    ::csc::customer::CustomerDetailsResponse& _return,
    const ::csc::customer::CustomerDetailsRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CustomerHandler::processCustomerDetails()");

    findCustomerDetails(
        _return,
        request.BranchNo,
        request.CustomerNo,
        request.__isset.GetTenderInformation && true == request.GetTenderInformation,
        request.__isset.GetCreditLimitInformation && true == request.GetCreditLimitInformation,
        request.__isset.GetLogisticSurcharge && true == request.GetLogisticSurcharge
    );
}

void CustomerHandler::findCustomerDetails(
    ::csc::customer::CustomerDetailsResponse& _return,
    const basar::Int16 branchNo, const basar::Int32 customerNo,
    bool withTender, bool withCreditLimit, bool withLogisticSurcharge)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CustomerHandler::findCustomerDetails()");

    libcsc::customer::ICustomerRepositoryPtr repo;
    libcsc::customer::CustomerCollectionPtr coll;

    repo = getSession()->getCustomerComponentManager()->getCustomerRepository();
    coll = repo->findCustomer(
        branchNo,
        customerNo,
        withTender,
        withCreditLimit,
        withLogisticSurcharge
    );

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
    _return.__set_Customers(csc::customer::CustomerDetailsList());

    libcsc::customer::CustomerCollection::const_iterator it = coll->begin();
    while (it != coll->end())
    {
        libcsc::customer::ICustomerPtr customer = (*it);
        csc::customer::CustomerDetails details;
        details.__set_BranchNo(customer->getBranchNo());
        details.__set_CustomerNo(customer->getCustomerNo());
        details.__set_PharmacyName(customer->getPharmacyName());
        // salutation
        details.__set_OwnerName(customer->getPharmacyOwner());
        details.__set_CustomerAddress(csc::base::Address());
        details.CustomerAddress.__set_City(customer->getCity());
        details.CustomerAddress.__set_PostalCode(customer->getPostalCode());
        details.CustomerAddress.__set_Street(customer->getStreet());

        if (!customer->getMailAddress().empty() &&
            // Efficient way to check if std::string has only spaces:
            // https://stackoverflow.com/questions/6444842/efficient-way-to-check-if-stdstring-has-only-spaces/36535031
            customer->getMailAddress().find_first_not_of(' ') != std::string::npos
            )
        {
            details.__set_MailAddress(customer->getMailAddress());
        }

        if (!customer->getFaxNo().empty() &&
            customer->getFaxNo().find_first_not_of(' ') != std::string::npos
            )
        {
            details.__set_FaxNo(customer->getFaxNo());
        }

        details.__set_Language(Helper::getLanguageEnumByString(customer->getLanguage()));
        details.__set_SalutationId(customer->getSalutationId());

        //TODO: following properties are still missing:
        // -->  customerDetails.__set_Salutation("");               // not available! currently no concept to get the correct salutation by ANREDEKZ, Customer Language and Customer Group => TODO
        // -->  customerDetails.__set_SalutationExtension("");      // not available! currently no concept to get the correct salutation by ANREDEKZ, Customer Language and Customer Group => TODO
        /*
        DEUTSCHLAND
        Anrede                              Kundengruppe 01 & 11
        0                   "FIRMA"
        1                   "HERR"          " APOTHEKER"
        2                   "FRL."          " APOTHEKERIN"
        3                   "FRAU"          " APOTHEKERIN"
        4                   "FIRMA"


        SCHWEIZ
        Anrede              DEFAULT         Kundensprache F
        0                   ""
        1                   "HERR"          "MONSIEUR"
        2                   "HERR/FRAU"     ""
        3                   "FRAU"          "MADAME"
        4                   "FIRMA"


        ÖSTERREICH
        Anrede
        2                   "FILIALAPOTHEKE"
        3                   "PARFUEMERIE"
        4                   "REFORMHAUS"
        5                   "APOTHEKE"
        6                   "STADTAPOTHEKE"
        7                   "ANSTALTSAPOTHEKE"
        8                   "DROGERIE"
        9                   "FIRMA"
        */



        details.__set_CustomerGroup(customer->getCustomerGroup());
        details.__set_ChainCustomerNo(customer->getCustomerNoChain());
        // phone no
        details.__set_IsActive(customer->isActive());
        details.__set_XmlInfoLevel(static_cast<csc::types::XMLInfoLevelEnum::type>(customer->getXMLInfoLevel()));
        if (withTender)
        {
            details.__set_HasTender(customer->hasTender());
        }
        if (withCreditLimit)
        {
            details.__set_CreditLimit(csc::customer::CreditLimitInformation());
            details.CreditLimit.__set_PartnerNo(customer->getPartnerNo());
            details.CreditLimit.__set_Limit(customer->getLimit().toFloat64());
            details.CreditLimit.__set_SumDebitSide(customer->getSumDebitSide().toFloat64());
            details.CreditLimit.__set_SumCreditSide(customer->getSumCreditSide().toFloat64());
            details.CreditLimit.__set_SumMonthTurnover(customer->getSumMonthTurnover().toFloat64());
            details.CreditLimit.__set_SumDayTurnover(customer->getSumDayTurnover().toFloat64());
            details.CreditLimit.__set_SumReturns(customer->getSumReturns().toFloat64());
            details.CreditLimit.__set_SumGoodsReceipt(customer->getSumGoodsReceipt().toFloat64());
        }

        if (withLogisticSurcharge)
        {
            details.__set_LogisticSurchargePct(customer->getLogisticSurchargePct().toFloat64());
            details.__set_LogisticSurchargeMinValue(customer->getLogisticSurchargeMinValue().toFloat64());
        }
        _return.Customers.push_back(details);
        ++it;
    }
}

long CustomerHandler::convertToInternalArticleNo( const std::string& articleCode ) const
{
    pxArticleCodes articleCodes( getSession()->Session(), articleCode.c_str() );
    if( 0 == articleCodes.Get() )
    {
        return articleCodes.ArticleNo();
    }
    
    return 0;
}

void CustomerHandler::findCustomerArticlePrices(::csc::customer::CustomerArticlePricesResponse& _return, const ::csc::customer::CustomerArticlePricesRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CustomerHandler::findCustomerArticlePrices()");

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 1. Pre-Checks
    ////////////////////////////////////////////////////////////////////////////////////////////////
    if (false == (request.__isset.BranchNo && request.__isset.CustomerNo && request.__isset.CollectionArticleCode))
    {
        csc::base::ReturnStruct returnStruct;
        returnStruct.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
        returnStruct.__set_ErrorMessage("Branch Number, Customer Number or List of Article Numbers is not set.");
        _return.__set_RetValue(returnStruct);
        return;
    }

    if (true == request.CollectionArticleCode.empty())
    {
        csc::base::ReturnStruct returnStruct;
        returnStruct.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
        returnStruct.__set_ErrorMessage("List of Article Numbers are empty.");
        _return.__set_RetValue(returnStruct);
        return;
    }

    pxSession* session = getSession()->Session();
    pxCustBase customer( session, request.BranchNo, request.CustomerNo );
    if( false == customer.IsGoodState() ) 
    {
        _return.__set_RetValue( Helper::getReturnStructFromError(customer) );
        return; 
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 2. Procwessing Article Codes of the Request
    ////////////////////////////////////////////////////////////////////////////////////////////////
    pxOrder order( session, &customer, pxOrder::INFO_ORDER_TYPE_DEFAULT ); // pxOrder(...) [ctor] -> OpenInfo[internal Call] -> OpenInfoCommon [internal Call] ==> implicit default order of type NO00 <==
    const int qty = 1000; // Quantity 1000 is coded here hard because this number of items quantity should never be exceeded by the combination price/qty scale.
    libcsc::discount::IDiscountCollectionFinderPtr discountCollectionFinder( session->getDiscountCollectionFinder() );
    
    _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
    _return.__set_CollectionCustomerArticlePrices( csc::customer:: CustomerArticlePricesCollection() );
    
    csc::customer::ArticleCodeCollection::const_iterator iterArticleCode = request.CollectionArticleCode.begin();
    for (; iterArticleCode != request.CollectionArticleCode.end(); ++iterArticleCode)
    {
        const int articleNo = convertToInternalArticleNo(*iterArticleCode);
        if (0 == articleNo)
        {
            csc::base::ReturnStruct returnStruct;
            returnStruct.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
            returnStruct.__set_ErrorMessage("Conversion from Articel Code to Article Number failed!.");

            csc::customer::CustomerArticlePrices customerArticlePrices;
            customerArticlePrices.__set_RetValue(returnStruct);
            customerArticlePrices.__set_ArticleCode(*iterArticleCode);
            _return.CollectionCustomerArticlePrices.push_back(customerArticlePrices);

            continue;
        }

        // Getting discounts and Pharmacy Purchase Price (AEP)
        double pharmacyPurchasePrice = 0.0; // Pharmacy Purchase Price is get with the help of the discount finders. The find function has been newly extended for this.
        discountCollectionFinder->clear();
        const libcsc::discount::DiscountBaseValueList& discountColl = discountCollectionFinder->find(&order, articleNo, qty, &pharmacyPurchasePrice);

        if (true == discountColl.empty())
        {
            csc::customer::CustomerArticlePrices customerArticlePrices;
            customerArticlePrices.__set_RetValue(Helper::getReturnStructFromError(nError()));
            customerArticlePrices.__set_ArticleCode(*iterArticleCode);

            _return.CollectionCustomerArticlePrices.push_back(customerArticlePrices);
            continue;
        }


        csc::customer::CustomerArticlePrices customerArticlePrices;
        customerArticlePrices.__set_RetValue(Helper::getReturnStructFromError(nError()));
        customerArticlePrices.__set_ArticleCode(*iterArticleCode);
        customerArticlePrices.__set_PharmacyPurchasePrice(pharmacyPurchasePrice); // The AEP can only be set when at least one discount record has been found b/c AEP is searched in that context.

        customerArticlePrices.__set_CollectionPriceList( csc::customer::PriceListCollection() );

        // Processing: Found at least one discounts dataset
        libcsc::discount::DiscountBaseValueList::const_iterator Iter4PriceList = discountColl.begin();
        while (Iter4PriceList != discountColl.end())
        {
            csc::customer::PriceList priceList;
            priceList.__set_PricingListNo((*Iter4PriceList)->getPharmacyGrpId().c_str());
            priceList.__set_CollectionPricingTier(csc::customer::PricingTierCollection()); // creation of internal collection

            libcsc::discount::DiscountBaseValueList::const_iterator Iter4PricingTiers = Iter4PriceList;
            while (Iter4PricingTiers != discountColl.end())
            {
                if ((*Iter4PriceList)->getPharmacyGrpId() != (*Iter4PricingTiers)->getPharmacyGrpId())
                {
                    break;
                }

                csc::customer::PricingTier pricingTier;
                pricingTier.__set_ArticleQty((*Iter4PricingTiers)->getBaseQty());
                pricingTier.__set_ArticlePrice((*Iter4PricingTiers)->getFixedPrice().toFloat64());

                priceList.CollectionPricingTier.push_back(pricingTier);

                ++Iter4PricingTiers;
            }
            Iter4PriceList = Iter4PricingTiers;
            customerArticlePrices.CollectionPriceList.push_back(priceList);
        }
         
        _return.CollectionCustomerArticlePrices.push_back( customerArticlePrices );
    }
}

void CustomerHandler::adjustSubsequentDeliveries(::csc::customer::SubsequentDeliveryAdjustmentResponse& _return, const csc::customer::SubsequentDeliveryAdjustmentRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CustomerHandler::adjustSubsequentDeliveries()");

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 1. Global Checks
    ////////////////////////////////////////////////////////////////////////////////////////////////
    if (false == (request.__isset.BranchNo && request.__isset.CustomerNo))
    {
        csc::base::ReturnStruct returnStruct;

        returnStruct.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
        returnStruct.__set_ErrorMessage("Branch Number or Customer Number not set." );
        _return.__set_RetValue(returnStruct);

        return;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 2. Processng / updating
    ////////////////////////////////////////////////////////////////////////////////////////////////
    _return.__set_BranchNo  ( request.BranchNo   );
    _return.__set_CustomerNo( request.CustomerNo );
    _return.__set_SubsequentDeliveryAcknowledgements( csc::customer::SubsequentDeliveryAcknowledgementList() );
    
    ::csc::customer::SubsequentDeliveryAdjustmentList::const_iterator it = request.SubsequentDeliveries.begin();

    for (; it != request.SubsequentDeliveries.end(); ++it)
    {
        csc::customer::SubsequentDeliveryAcknowledgement subsequentDeliveryAcknowledgement;

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // 2.1 Item Checks
        ////////////////////////////////////////////////////////////////////////////////////////////////
        if( false == isSubsequentDeliveryKeySet(it->Key) )
        {
            // error / warning setting 
            csc::base::ReturnStruct returnStruct;
            returnStruct.__set_ErrorCode( csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION );
            returnStruct.__set_ErrorMessage( "Key Attributes for SubsequentDeliveryAdjustment Request are not set." );
            subsequentDeliveryAcknowledgement.__set_RetValue( returnStruct );
            
            _return.SubsequentDeliveryAcknowledgements.push_back( subsequentDeliveryAcknowledgement );
            continue;
        }

        subsequentDeliveryAcknowledgement.__set_Key(it->Key);

        if( 0 > it->Qty )
        {
            csc::base::ReturnStruct returnStruct;
            returnStruct.__set_ErrorCode( csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION );
            returnStruct.__set_ErrorMessage( "Qty requested less than 0." );
            subsequentDeliveryAcknowledgement.__set_RetValue( returnStruct );

            _return.SubsequentDeliveryAcknowledgements.push_back(subsequentDeliveryAcknowledgement);
            continue;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // 2.2 Subsequent Delivery Item DB Selection (important for previous values)
        ////////////////////////////////////////////////////////////////////////////////////////////////
        getSession()->nDBBeginTransaction();
        ::pxVerbund::subsequentDelivery::pxDeliveryPos subsequentDeliveryPosition(  getSession()->Session(), it->Key.CustomerOrderNo, it->Key.PositionNo, nDate(it->Key.Date), 
                                                                                    static_cast<pxVerbund::subsequentDelivery::pxDelPosTyp>(it->Key.PositionType), 
                                                                                    static_cast<DBAccessMode>(cDBGET_FORUPDATE) );
        if( !subsequentDeliveryPosition.IsGoodState() )
        {
            subsequentDeliveryAcknowledgement.__set_RetValue(Helper::getReturnStructFromError(subsequentDeliveryPosition.Error()) );
            _return.SubsequentDeliveryAcknowledgements.push_back( subsequentDeliveryAcknowledgement );

            getSession()->nDBRollBack();
            continue;
        }

        if( false == (request.BranchNo == subsequentDeliveryPosition.VertriebszentrumNr() && request.CustomerNo == subsequentDeliveryPosition.KundenNr()) )
        {
            csc::base::ReturnStruct returnStruct;
            returnStruct.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
            returnStruct.__set_ErrorMessage("Requested Branch Number and/or Customer Number does not correspond with the Key Values of the Subsequent Delivery.");
            
            subsequentDeliveryAcknowledgement.__set_RetValue( returnStruct );
            _return.SubsequentDeliveryAcknowledgements.push_back(subsequentDeliveryAcknowledgement);

            getSession()->nDBRollBack();
            continue;
        }

        subsequentDeliveryAcknowledgement.__set_PreviousQty(subsequentDeliveryPosition.Menge());
        subsequentDeliveryAcknowledgement.__set_ArticleNo(subsequentDeliveryPosition.ArtikelNr());
        subsequentDeliveryAcknowledgement.__set_ArticleCode(static_cast<char*>(subsequentDeliveryPosition.ArticleCode()));

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 2.3 Check: Existing qty of current Subsequent Delivery item (db) must not be exceeded by the requested qty.
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if( it->Qty > subsequentDeliveryPosition.Menge() )
        {
            csc::base::ReturnStruct returnStruct;
            returnStruct.__set_ErrorCode( csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION );
            returnStruct.__set_ErrorMessage( "Qty of the Request is greater than the Qty of the existing Subsequent Delivery." );
            subsequentDeliveryAcknowledgement.__set_RetValue( returnStruct );

            _return.SubsequentDeliveryAcknowledgements.push_back(subsequentDeliveryAcknowledgement);
            
            getSession()->nDBRollBack();
            continue;
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 2.4 DB Update of the current Subsequent Delivery item with new requested qty.
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        subsequentDeliveryPosition.SetMenge( it->Qty );
        if (0 != subsequentDeliveryPosition.Put())
        {
            subsequentDeliveryAcknowledgement.__set_RetValue(Helper::getReturnStructFromError(subsequentDeliveryPosition.Error()) );
            _return.SubsequentDeliveryAcknowledgements.push_back(subsequentDeliveryAcknowledgement);
            
            getSession()->nDBRollBack();
            continue;
        }
        getSession()->nDBCommit();

        subsequentDeliveryAcknowledgement.__set_AdjustedQty(subsequentDeliveryPosition.Menge());
        subsequentDeliveryAcknowledgement.__set_RetValue( Helper::getReturnStructFromError(nError()) );
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 2.6 Pushing of the current SubsequentDeliveryAcknowledgement to the list of response structure
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        _return.SubsequentDeliveryAcknowledgements.push_back( subsequentDeliveryAcknowledgement );
    }

    _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
}

bool CustomerHandler::isSubsequentDeliveryKeySet( const csc::customer::SubsequentDeliveryKey& subsequentDeliveryKey ) const
{
    bool subsequentDeliveryKeySet = subsequentDeliveryKey.__isset.CustomerOrderNo;
    subsequentDeliveryKeySet &= subsequentDeliveryKey.__isset.PositionNo;
    subsequentDeliveryKeySet &= subsequentDeliveryKey.__isset.Date;
    subsequentDeliveryKeySet &= subsequentDeliveryKey.__isset.PositionType;

    return subsequentDeliveryKeySet;
}

void CustomerHandler::findSubsequentDeliveryArticleQtyAggregation(::csc::customer::SubsequentDeliveryArticleQtyAggregationResponse& _return, const ::csc::customer::SubsequentDeliveryRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CustomerHandler::findSubsequentDeliveriesAggregation()");

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 1. Checks
    ////////////////////////////////////////////////////////////////////////////////////////////////
    if( false == (request.__isset.BranchNo && request.__isset.ArticleNo) )
    {
        csc::base::ReturnStruct returnStruct;
        returnStruct.__set_ErrorCode( csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION );
        returnStruct.__set_ErrorMessage( "Branch Number or Article Number not set." );
        _return.__set_RetValue( returnStruct );
        return;
    }

    csc::base::ReturnStruct branchCheckResult = Helper::checkBranch( getSession(), request.BranchNo );
    if( branchCheckResult.ErrorCode != csc::types::MessageCodeEnum::CMSG_OK )
    {
        _return.__set_RetValue( branchCheckResult );
        return;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 2. Selection
    ////////////////////////////////////////////////////////////////////////////////////////////////
    csc::customer::SubsequentDeliveryArticleQtyAggregation subsequentDeliveryArticleQtyAggregation;
    subsequentDeliveryArticleQtyAggregation.__set_FrequencyOfArticle( 0 );
    subsequentDeliveryArticleQtyAggregation.__set_AccumulationOfQty( 0 );
        
    _return.__set_subsequent_DeliveryArticleQtyAggregation( subsequentDeliveryArticleQtyAggregation );
    
    boost::scoped_ptr< ::pxVerbund::subsequentDelivery::pxDeliveryPosList > coll( new ::pxVerbund::subsequentDelivery::pxDeliveryPosList(getSession()->Session()) );
        
    coll->SelectByArticle( request.BranchNo, request.ArticleNo, ::pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM );
    populateSubDelCollection( coll, _return.subsequent_DeliveryArticleQtyAggregation );

    coll->Clear();

    coll->SelectByArticle(request.BranchNo, request.ArticleNo, ::pxVerbund::subsequentDelivery::pxDPT_RESERVE_ITEM);
    populateSubDelCollection(coll, _return.subsequent_DeliveryArticleQtyAggregation);

    _return.__set_RetValue( Helper::getReturnStructFromError(*getSession()) );
 }

void CustomerHandler::populateSubDelCollection( SubsequentDeliveryScopedPtr& coll,
                                                csc::customer::SubsequentDeliveryArticleQtyAggregation& subsequent_DeliveryArticleQtyAggregation )
{
    pxVerbund::subsequentDelivery::pxDeliveryPosListIter iter(*coll);
    pxVerbund::subsequentDelivery::pxDeliveryPos* deliveryPos;

    while ((deliveryPos = (pxVerbund::subsequentDelivery::pxDeliveryPos*) ++iter) != NULL)
    {
        if (deliveryPos->Menge() > 0)
        {
            subsequent_DeliveryArticleQtyAggregation.FrequencyOfArticle++;
            subsequent_DeliveryArticleQtyAggregation.AccumulationOfQty += deliveryPos->Menge();
        }
    }
}

void CustomerHandler::findSubsequentDeliveries(::csc::customer::SubsequentDeliveryResponse& _return, const csc::customer::SubsequentDeliveryRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CustomerHandler::findSubsequentDeliveries()");

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 1. Checks
    ////////////////////////////////////////////////////////////////////////////////////////////////
    if( false == (request.__isset.BranchNo && request.__isset.CustomerNo) ) 
    {
        csc::base::ReturnStruct returnStruct;
        returnStruct.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
        returnStruct.__set_ErrorMessage( "Branch Number or Customer Number not set." );
        _return.__set_RetValue( returnStruct );
        return;
    }
    
    csc::base::ReturnStruct branchCheckResult = Helper::checkBranch(getSession(), request.BranchNo);
    if (branchCheckResult.ErrorCode != csc::types::MessageCodeEnum::CMSG_OK )
    {
        _return.__set_RetValue(branchCheckResult);
        return;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // 2. Selection
    ////////////////////////////////////////////////////////////////////////////////////////////////
    _return.__set_Subsequent_DeliveryList( csc::customer::SubsequentDeliveryList() );
    
    boost::scoped_ptr< ::pxVerbund::subsequentDelivery::pxDeliveryPosList > coll(new ::pxVerbund::subsequentDelivery::pxDeliveryPosList( getSession()->Session()));
    coll->SelectCustomersRestDeliveryAndReserveItems( request.CustomerNo, request.BranchNo );
    if (!coll->Entries())
    {
        return;
    }
    
    pxVerbund::subsequentDelivery::pxDeliveryPosListIter iter( *coll );
    pxVerbund::subsequentDelivery::pxDeliveryPos* deliveryPos;
    
    while( (deliveryPos = (pxVerbund::subsequentDelivery::pxDeliveryPos*) ++iter) != NULL)
    {
        csc::customer::SubsequentDelivery subsequentDelivery;

        // articlecode
        subsequentDelivery.__set_ArticleNo  ( deliveryPos->ArtikelNr()                       );
        subsequentDelivery.__set_ArticleCode( static_cast<char*>(deliveryPos->ArticleCode()) );
        subsequentDelivery.__set_CSCOrderNo ( deliveryPos->KdAuftragNr()                     );
        subsequentDelivery.__set_CustomerNo ( deliveryPos->KundenNr()                        );
        subsequentDelivery.__set_Date       ( deliveryPos->Datum().GetYYYYMMDD()             );
        subsequentDelivery.__set_PosNo      ( deliveryPos->PosNr()                           );
        subsequentDelivery.__set_PosType    ( deliveryPos->DeliveryPosTyp()                  );
        subsequentDelivery.__set_Qty        ( deliveryPos->Menge()                           );
        
        pxArtMaster article( getSession()->Session(), deliveryPos->ArtikelNr() );
        if( 0 == article.Get() )
        {
            subsequentDelivery.__set_ArticleName( std::string(article.Bezeichnung()) );
            subsequentDelivery.__set_ArticleUnit(std::string(article.Einheit()) );
        }
                
        _return.Subsequent_DeliveryList.push_back(subsequentDelivery); 
    }

    _return.__set_RetValue( Helper::getReturnStructFromError(*getSession()) );
}

void CustomerHandler::processCustomerConditionsSerbia(
    csc::customer::CustomerConditionsResponse& _return,
    const csc::customer::CustomerConditionsRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo;
    libcsc::customer::CustomerConditionCollectionPtr coll;

    repo = getSession()->getCustomerComponentManager()->getCustomerRepository();
    coll = repo->findCustomerConditions(request.BranchNo, request.FromCustomerNo,
        request.FromArticleNo, request.MaxPriceElements, request.CustomerNoFilter);

    _return.__set_CustomerConditions(csc::customer::CustomerConditionList());

    csc::customer::CustomerCondition* cc = NULL;
    basar::Int32 recordCount = 0;
    basar::Int32 currentCustomerNo = 0;
    libcsc::customer::CustomerConditionCollection::const_iterator it = coll->begin();
    while (it != coll->end())
    {
        ++recordCount;
        if (recordCount > request.MaxPriceElements)
        {
            _return.__set_NextCustomerNo((*it)->getCustomerNo());
            _return.__set_NextArticleNo((*it)->getArticleNo());
            break;
        }
        if (currentCustomerNo != (*it)->getCustomerNo())
        {
            _return.CustomerConditions.push_back(csc::customer::CustomerCondition());
            cc = &_return.CustomerConditions.back();
            cc->__set_CustomerNo((*it)->getCustomerNo());
            cc->__set_ArticleConditions(csc::customer::ArticleConditionList());
            currentCustomerNo = (*it)->getCustomerNo();
        }

        csc::customer::ArticleCondition ac;
        ac.__set_ArticleNo((*it)->getArticleNo());
        ac.__set_BaseQuantity((*it)->getBaseQuantity());
        ac.__set_BasePrice((*it)->getPharmacyPurchasePrice().toFloat64());
        ac.__set_DiscountPercent((*it)->getDiscountPercentage().toFloat64());
        ac.__set_DiscountPrice((*it)->getDiscountPrice().toFloat64());
        ac.__set_PaymentTargets(csc::customer::PaymentTargetList());
        if ((*it)->getPTPaymentDays1() > 0)
        {
            csc::customer::PaymentTarget pt;
            pt.__set_TargetDays((*it)->getPTPaymentDays1());
            pt.__set_DiscountPercent((*it)->getPTDiscountPercentage1().toFloat64());
            pt.__set_DiscountPrice((*it)->getPTDiscountPrice1().toFloat64());
            ac.PaymentTargets.push_back(pt);
        }

        if ((*it)->getPTPaymentDays2() > 0)
        {
            csc::customer::PaymentTarget pt;
            pt.__set_TargetDays((*it)->getPTPaymentDays2());
            pt.__set_DiscountPercent((*it)->getPTDiscountPercentage2().toFloat64());
            pt.__set_DiscountPrice((*it)->getPTDiscountPrice2().toFloat64());
            ac.PaymentTargets.push_back(pt);
        }

        if ((*it)->getPTPaymentDays3() > 0)
        {
            csc::customer::PaymentTarget pt;
            pt.__set_TargetDays((*it)->getPTPaymentDays3());
            pt.__set_DiscountPercent((*it)->getPTDiscountPercentage3().toFloat64());
            pt.__set_DiscountPrice((*it)->getPTDiscountPrice3().toFloat64());
            ac.PaymentTargets.push_back(pt);
        }

        if ((*it)->getPTPaymentDays4() > 0)
        {
            csc::customer::PaymentTarget pt;
            pt.__set_TargetDays((*it)->getPTPaymentDays4());
            pt.__set_DiscountPercent((*it)->getPTDiscountPercentage4().toFloat64());
            pt.__set_DiscountPrice((*it)->getPTDiscountPrice4().toFloat64());
            ac.PaymentTargets.push_back(pt);
        }

        if ((*it)->getPTPaymentDays5() > 0)
        {
            csc::customer::PaymentTarget pt;
            pt.__set_TargetDays((*it)->getPTPaymentDays5());
            pt.__set_DiscountPercent((*it)->getPTDiscountPercentage5().toFloat64());
            pt.__set_DiscountPrice((*it)->getPTDiscountPrice5().toFloat64());
            ac.PaymentTargets.push_back(pt);
        }

        if ((*it)->getPTPaymentDays6() > 0)
        {
            csc::customer::PaymentTarget pt;
            pt.__set_TargetDays((*it)->getPTPaymentDays6());
            pt.__set_DiscountPercent((*it)->getPTDiscountPercentage6().toFloat64());
            pt.__set_DiscountPrice((*it)->getPTDiscountPrice6().toFloat64());
            ac.PaymentTargets.push_back(pt);
        }

        if (cc != NULL)
        {
            cc->ArticleConditions.push_back(ac);
        }
        ++it;
    }

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}


void CustomerHandler::processTenderInfoSerbia(
    csc::customer::TenderInfoResponse& _return,
    const csc::customer::TenderInfoRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo;
    libcsc::customer::TenderInfoCollectionPtr coll;

    repo = getSession()->getCustomerComponentManager()->getCustomerRepository();
    coll = repo->findTenderInfo(request.BranchNo, request.CustomerNo, request.ContractNo, request.ArticleNo);
    _return.__set_Tenders(csc::customer::TenderList());
    csc::customer::Tender* tender = NULL;
    libcsc::customer::TenderInfoCollection::const_iterator it = coll->begin();
    while (it != coll->end())
    {
        if (tender == NULL || tender->TenderNo != (*it)->getTenderNo())
        {
            _return.Tenders.push_back(csc::customer::Tender());
            tender = &_return.Tenders.back();
            tender->__set_CustomerNo((*it)->getCustomerNo());
            tender->__set_TenderNo((*it)->getTenderNo());
            tender->__set_ContractNo((*it)->getContractNo());
            tender->__set_ValidFrom(Helper::getCscDateFromBasarDate((*it)->getValidFromDate()));
            tender->__set_ValidTo(Helper::getCscDateFromBasarDate((*it)->getValidToDate()));
            tender->__set_ChainNo((*it)->getChainNo());
            tender->__set_TenderItems(csc::customer::TenderItemList());
        }
        csc::customer::TenderItem ti;
        ti.__set_ArticleNo((*it)->getArticleNo());
        ti.__set_TenderQty((*it)->getTenderQuantity());
        ti.__set_DeliveredQty((*it)->getDeliveredTenderQuantity());
        ti.__set_ReturnedQty((*it)->getReturnedTenderQuantity());
        ti.__set_FreeTenderQty(ti.TenderQty - ti.DeliveredQty + ti.ReturnedQty);
        tender->TenderItems.push_back(ti);
        ++it;
    }

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}


void CustomerHandler::processArticleInfoSerbia(
    csc::customer::ArticleInfoResponse& _return,
    const ::csc::customer::ArticleInfoRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo;
    libcsc::customer::ArticleInfoCollectionPtr coll;

    repo = getSession()->getCustomerComponentManager()->getCustomerRepository();
    coll = repo->findArticleInfo(request.BranchNo, request.ArticleNo);
    _return.__set_Articles(csc::customer::ArticleInfoList());
    libcsc::customer::ArticleInfoCollection::const_iterator it = coll->begin();
    while (it != coll->end())
    {
        csc::customer::ArticleInfo info;
        info.__set_BranchNo((*it)->getBranchNo());
        info.__set_ArticleNo((*it)->getArticleNo());
        info.__set_EAN((*it)->getEAN());
        info.__set_Name((*it)->getName());
        info.__set_AlternateName((*it)->getAlternateName());
        info.__set_ManufacturerName((*it)->getManufacturerName());
        info.__set_BasePrice((*it)->getBasePrice().toFloat64());
        info.__set_VatPercentage((*it)->getVatPercentage().toFloat64());
        info.__set_PositiveList((*it)->getPositiveList());
        info.__set_ActiveFlag((*it)->getActiveFlag());
        info.__set_BlockedFlag((*it)->getBlockedFlag());
        info.__set_CreationDate(Helper::getCscDateFromBasarDate((*it)->getCreationDate()));
        info.__set_ColdChainFlag((*it)->getColdChainFlag());
        info.__set_NarcoticFlag((*it)->getNarcoticFlag());
        _return.Articles.push_back(info);
        ++it;
    }

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}


void CustomerHandler::processOrderInfoSerbia(
    csc::customer::OrderInfoResponse& _return,
    const ::csc::customer::OrderInfoRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo;
    libcsc::customer::OrderInfoCollectionPtr coll;

    repo = getSession()->getCustomerComponentManager()->getCustomerRepository();
    coll = repo->findOrderInfo(request.BranchNo, Helper::getBasarDateFromCscDate(request.OrderDate), request.CustomerNo, request.ArticleNo);
    _return.__set_Orders(csc::customer::OrderInfoList());
    csc::customer::OrderInfo* order = NULL;
    libcsc::customer::OrderInfoCollection::const_iterator it = coll->begin();
    while (it != coll->end())
    {
        if (order == NULL || order->OrderNo != (*it)->getOrderNo())
        {
            _return.Orders.push_back(csc::customer::OrderInfo());
            order = &_return.Orders.back();
            order->__set_BranchNo((*it)->getBranchNo());
            order->__set_CustomerNo((*it)->getCustomerNo());
            order->__set_OrderDate(Helper::getCscDateFromBasarDate((*it)->getOrderDate()));
            order->__set_OrderNo((*it)->getOrderNo());
            order->__set_OrderType((*it)->getOrderType());
            order->__set_OrderLines(csc::customer::OrderLineInfoList());
        }
        csc::customer::OrderLineInfo line;
        line.__set_ArticleNo((*it)->getArticleNo());
        line.__set_QuantityOrdered((*it)->getQuantityOrdered());
        line.__set_QuantityConfirmed((*it)->getQuantityConfirmed());
        line.__set_ReferenceNo((*it)->getReferenceNo());
        order->OrderLines.push_back(line);
        ++it;
    }
    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}

void CustomerHandler::processChangeCreditLimit(
    ::csc::customer::ChangeCreditLimitResponse& _return,
    const ::csc::customer::ChangeCreditLimitRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo;
    libcsc::customer::CustomerCollectionPtr coll;

    repo = getSession()->getCustomerComponentManager()->getCustomerRepository();
    coll = repo->findCustomer(request.BranchNo, request.CustomerNo, false, true, false);

    libcsc::customer::CustomerCollection::const_iterator it = coll->begin();
    if (it != coll->end())
    {
        libcsc::customer::ICustomerPtr customer = (*it);
        _return.__set_BranchNo(customer->getBranchNo());
        _return.__set_CustomerNo(customer->getCustomerNo());
        _return.__set_OldLimit(customer->getLimit().toFloat64());
        _return.__set_CreditLimit(csc::customer::CreditLimitInformation());
        _return.CreditLimit.__set_PartnerNo(customer->getPartnerNo());
        _return.CreditLimit.__set_Limit(customer->getLimit().toFloat64());
        _return.CreditLimit.__set_SumDebitSide(customer->getSumDebitSide().toFloat64());
        _return.CreditLimit.__set_SumCreditSide(customer->getSumCreditSide().toFloat64());
        _return.CreditLimit.__set_SumMonthTurnover(customer->getSumMonthTurnover().toFloat64());
        _return.CreditLimit.__set_SumDayTurnover(customer->getSumDayTurnover().toFloat64());
        _return.CreditLimit.__set_SumReturns(customer->getSumReturns().toFloat64());
        _return.CreditLimit.__set_SumGoodsReceipt(customer->getSumGoodsReceipt().toFloat64());

        repo->changeCreditLimit(customer->getPartnerNo(), basar::Decimal(request.NewLimit));

        _return.CreditLimit.__set_Limit(request.NewLimit);
    }
    else
    {
        getSession()->ExternalError(getSession()->CMsgStream(), CMSG_CST_NOTFOUND, request.CustomerNo);
    }
    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}

void CustomerHandler::processOrderStatusBulgaria(
    csc::customer::OrderStatusResponse& _return,
    const ::csc::customer::OrderStatusRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::OrderStatusPtr result = repo->findOrderStatus(
        request.BranchNo, request.CustomerNo, request.OrderNo, Helper::getBasarDateFromCscDate(request.OrderDate));

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Inprocess(result->getInprocess());
    _return.__set_Onhold(result->getOnhold());
    _return.__set_Ordercreated(result->getOrdercreated());
    _return.__set_Readyforinvoicing(result->getReadyforinvoicing());
    _return.__set_Invoicecreated(result->getInvoicecreated());
    _return.__set_Ordercanceled(result->getOrdercanceled());
    _return.__set_Onhold2(result->getOnhold2());
    _return.__set_DriverId(result->getDriverId());
    _return.__set_InvoiceNo(result->getInvoiceNo());
    _return.__set_PharmosOrderNo(result->getPharmosOrderNo());
}

void CustomerHandler::processPricesAndDiscountsBulgaria(
    csc::customer::PricesAndDiscountsResponse& _return,
    const ::csc::customer::PricesAndDiscountsRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::PricesAndDiscountsCollectionPtr result;

    try
    {
        result = repo->findPricesAndDiscounts(request.BranchNo, request.CustomerNo);
    }
    catch (nError const& err)
    {
        _return.__set_RetValue(Helper::getReturnStructFromError(err));
        return;
    }

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_PricesAndDiscounts_List(csc::customer::PricesAndDiscountsList());
    libcsc::customer::PricesAndDiscountsCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::customer::PricesAndDiscounts pricesAndDiscounts;
        pricesAndDiscounts.__set_ArticleNo((*it)->getArticleNo());
        pricesAndDiscounts.__set_SellingMode((*it)->getSellingMode());
        pricesAndDiscounts.__set_DiscountPercentage((*it)->getDiscountPercentage().toFloat64());
        pricesAndDiscounts.__set_GrossProfitPercentage((*it)->getGrossProfitPercentage().toFloat64());
        pricesAndDiscounts.__set_SalesPrice((*it)->getSalesPrice().toFloat64());
        pricesAndDiscounts.__set_PharmacySellPrice((*it)->getPharmacySellPrice().toFloat64());
        pricesAndDiscounts.__set_NZOKCode((*it)->getNZOKCode());
        _return.PricesAndDiscounts_List.push_back(pricesAndDiscounts);
        ++it;
    }
}

void CustomerHandler::processPaymentsBulgaria(
    csc::customer::PaymentsResponse& _return,
    const ::csc::customer::PaymentsRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::PaymentsCollectionPtr result = repo->findPayments(
        request.BranchNo, request.CustomerNo, Helper::getBasarDateFromCscDate(request.DateFrom), Helper::getBasarDateFromCscDate(request.DateTo),
        static_cast<PaymentsFilterEnum>(request.Filter));

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Payments_List(csc::customer::PaymentsList());
    libcsc::customer::PaymentsCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::customer::Payments payment;
        payment.__set_InvoiceNo((*it)->getInvoiceNo());
        payment.__set_InvoiceDate((*it)->getInvoiceDate());
        payment.__set_DocType((*it)->getDocType());
        payment.__set_KindOfInvoice((*it)->getKindOfInvoice());
        payment.__set_KindOfOrder((*it)->getKindOfOrder());
        payment.__set_DueDays((*it)->getDueDays());
        payment.__set_DueDate((*it)->getDueDate());
        payment.__set_InvoiceValue((*it)->getInvoiceValue().toFloat64());
        payment.__set_PaidValue((*it)->getPaidValue().toFloat64());
        payment.__set_PaymentSpec((*it)->getPaymentSpec());
        _return.Payments_List.push_back(payment);
        ++it;
    }
}

void CustomerHandler::processPaymentConditionsBulgaria(
    csc::customer::PaymentConditionsResponse& _return,
    const ::csc::customer::PaymentConditionsRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::PaymentConditionsPtr result = repo->findPaymentConditions(
        request.BranchNo, request.CustomerNo);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_NZOKDiscountMethod(result->getNZOKDiscountMethod());
    _return.__set_DiscountMethod(result->getDiscountMethod());
    _return.__set_NZOKDaysOfPayment(result->getNZOKDaysOfPayment());
    _return.__set_DaysOfPayment(result->getDaysOfPayment());
}

void CustomerHandler::processTurnoverBulgaria(
    csc::customer::TurnoverResponse& _return,
    const ::csc::customer::TurnoverRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::TurnoverPtr result = repo->findTurnover(
        request.BranchNo, request.CustomerNo, Helper::getBasarDateFromCscDate(request.DateFrom), Helper::getBasarDateFromCscDate(request.DateTo));

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Total(result->getTotal().toFloat64());
    _return.__set_XmlValue(result->getXmlValue().toFloat64());
    _return.__set_Value(result->getValue().toFloat64());
}

void CustomerHandler::processChangedQuantitiesBulgaria(
    csc::customer::ChangedQuantitiesResponse& _return,
    const ::csc::customer::ChangedQuantitiesRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::ChangedQuantitiesCollectionPtr result = repo->findChangedQuantities(
        request.BranchNo, request.CustomerNo, request.OrderNo, Helper::getBasarDateFromCscDate(request.DateFrom), Helper::getBasarDateFromCscDate(request.DateTo));

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_ChangedQuantities_List(csc::customer::ChangedQuantitiesList());
    libcsc::customer::ChangedQuantitiesCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::customer::ChangedQuantities changedQuantities;
        changedQuantities.__set_BranchNo((*it)->getBranchNo());
        changedQuantities.__set_CustomerNo((*it)->getCustomerNo());
        changedQuantities.__set_OrderDate((*it)->getOrderDate());
        changedQuantities.__set_OrderNo((*it)->getOrderNo());
        changedQuantities.__set_InvoiceNo((*it)->getInvoiceNo());
        changedQuantities.__set_ArticleNo((*it)->getArticleNo());
        changedQuantities.__set_ArticleName((*it)->getArticleName());
        changedQuantities.__set_QuantityOriginal((*it)->getQuantityOriginal());
        changedQuantities.__set_QuantityNew((*it)->getQuantityNew());
        changedQuantities.__set_QuantityOrdered((*it)->getQuantityOrdered());
        _return.ChangedQuantities_List.push_back(changedQuantities);
        ++it;
    }
}

void CustomerHandler::processDiscountAccountBulgaria(
    csc::customer::DiscountAccountResponse& _return,
    const ::csc::customer::DiscountAccountRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::DiscountAccountPtr result = repo->findDiscountAccount(
        request.BranchNo, request.CustomerNo, Helper::getBasarDateFromCscDate(request.DateFrom), Helper::getBasarDateFromCscDate(request.DateTo), request.AccNatRebateGroup);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Value(result->getValue().toFloat64());
}

void CustomerHandler::processPromotionsBulgaria(
    csc::customer::PromotionsResponse& _return,
    const ::csc::customer::PromotionsRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::PromotionsCollectionPtr result = repo->findPromotions(
        request.BranchNo, request.CustomerNo);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Promotions_List(csc::customer::PromotionsList());
    libcsc::customer::PromotionsCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::customer::Promotions promotions;
        promotions.__set_MaxQuantity1((*it)->getMaxQuantity1());
        promotions.__set_MaxQuantity((*it)->getMaxQuantity());
        promotions.__set_SoldQuantity((*it)->getSoldQuantity());
        promotions.__set_MinQuantity((*it)->getMinQuantity());
        promotions.__set_DateFrom((*it)->getDateFrom());
        promotions.__set_DateTo((*it)->getDateTo());
        promotions.__set_ArticleNo((*it)->getArticleNo());
        promotions.__set_BaseQuantity((*it)->getBaseQuantity());
        promotions.__set_BaseValue((*it)->getBaseValue().toFloat64());
        promotions.__set_DiscountValuePercentage((*it)->getDiscountValuePercentage().toFloat64());
        promotions.__set_DiscountQuantity((*it)->getDiscountQuantity());
        promotions.__set_DiscountArticle((*it)->getDiscountArticle());
        promotions.__set_DiscountSpecification((*it)->getDiscountSpecification());
        promotions.__set_NotViaSalesWeb((*it)->getNotViaSalesWeb());
        promotions.__set_PromotionNo((*it)->getPromotionNo());
        promotions.__set_Name((*it)->getName());
        _return.Promotions_List.push_back(promotions);
        ++it;
    }
}

void CustomerHandler::processRoutesBulgaria(
    csc::customer::RoutesResponse& _return,
    const ::csc::customer::RoutesRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::RoutesCollectionPtr result = repo->findRoutes(
        request.BranchNo, request.CustomerNo, request.Weekday);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Routes_List(csc::customer::RoutesList());
    libcsc::customer::RoutesCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::customer::Routes routes;
        routes.__set_Weekday((*it)->getWeekday());
        routes.__set_TourId((*it)->getTourId());
        routes.__set_Duration((*it)->getDuration());
        _return.Routes_List.push_back(routes);
        ++it;
    }
}

void CustomerHandler::processGetTourIDs(
    csc::customer::CustomerTourIDsResponse& _return,
    const ::csc::customer::CustomerTourIDsRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    std::vector<std::string> result = repo->findTours(
        request.BranchNo, request.TourDate);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
    _return.__set_BranchNo(request.BranchNo);
    _return.__set_TourDate(request.TourDate);
    _return.__set_TourIDs(result);    
}

void CustomerHandler::processGetCustomerIDFsByTourId(
    csc::customer::CustomerIDFsByTourIdResponse& _return,
    const ::csc::customer::CustomerIDFsByTourIdRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::ToursCollectionPtr result = repo->findCustomerToursInfo(
        request.BranchNo, request.TourDate, request.TourIDs);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
    _return.__set_BranchNo(request.BranchNo);
    _return.__set_TourDate(request.TourDate);

    if (result == NULL)
    {
        return;
    }

    _return.__set_CustomerTourInfos(csc::customer::CustomerTourInfoList());
    libcsc::customer::ToursCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::customer::CustomerTourInfo tourInfo;

        tourInfo.__set_Tourid((*it)->getTourId());
        tourInfo.__set_Idfnr((*it)->getIdfnr());
        tourInfo.__set_DatumVersand((*it)->getDatumVersand());
        tourInfo.__set_ZeitVersand((*it)->getZeitVersand());
        tourInfo.__set_FahrtZeit((*it)->getFahrtZeit());
        tourInfo.__set_Delivered((*it)->getDelivered());

        _return.CustomerTourInfos.push_back(tourInfo);
        ++it;
    }

}

void CustomerHandler::processGetCustomerToursForWeek(
    csc::customer::CustomerToursForWeekResponse& _return,
    const csc::customer::CustomerToursForWeekRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    libcsc::customer::WeekToursCollectionPtr result = repo->findCustomerToursForWeek(request.BranchNo, request.CustomerNo);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
    _return.__set_BranchNo(request.BranchNo);
    _return.__set_CustomerNo(request.CustomerNo);
    if (result == NULL)
    {
        return;
    }

    _return.__set_WeekTourInfos(csc::customer::WeekTourInfoList());
    libcsc::customer::WeekToursCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::customer::WeekTourInfo weekTourInfo;

        weekTourInfo.__set_Tourid((*it)->getTourId());
        weekTourInfo.__set_FahrtZeit((*it)->getFahrtZeit());
        weekTourInfo.__set_Weekday((*it)->getWeekday());
        weekTourInfo.__set_OrderType((*it)->getOrderType());
        weekTourInfo.__set_IsIbtTour((*it)->isIbtTour());
        weekTourInfo.__set_IsBtmTour((*it)->isBtmTour());
        weekTourInfo.__set_IsKKTour((*it)->isKKTour());
        weekTourInfo.__set_IsK08Tour((*it)->isK08Tour());
        weekTourInfo.__set_IsK20Tour((*it)->isK20Tour());
        weekTourInfo.__set_IsReturnsTour((*it)->isReturnsTour());
        weekTourInfo.__set_OrderPeriodFromTime((*it)->getOrderPeriodFromTime());
        weekTourInfo.__set_OrderPeriodToTime((*it)->getOrderPeriodToTime());
        weekTourInfo.__set_OrderPeriodMainTime((*it)->getOrderPeriodMainTime());

        _return.WeekTourInfos.push_back(weekTourInfo);
        ++it;
    }

}

} // namespace service
} // namespace csc
