#include "inquiryhandler.h"
#include "cscservicehelper.h"
#include "csctypes_types.h"
#include "cscinquiry_types.h"

#include <sstream>
#include <vector>

#include <pxxmit.hpp>
#include <pxbranch.hpp>
#include <pxcstbas.hpp>
#include <pxcustomerflags.hpp>
#include <pxorder.hpp>
#include <pxitem.hpp>
#include <pxartbas.hpp>
#include <pxarticlecodes.hpp>
#include <pxarticleinfo.hpp>
#include <pxarticletext.hpp>
#include <pxcountrycodes.hpp>
#include <pxsuppldeliveryinfo.hpp>
#include <customer/componentmanager/customercomponentmanagerptr.h>
#include <customer/componentmanager/customercomponentmanager.h>
#include <customer/customerrepositoryptr.h>
#include <customer/customerrepository.h>
#include <customer/articleinfo/articleinfoptr.h>
#include <customer/articleinfo/articleinfo.h>
#include <customer/articleinfo/articleorderinfoptr.h>
#include <customer/articleinfo/articleorderinfo.h>

namespace csc {
namespace service {

InquiryHandler::InquiryHandler()
{
}

InquiryHandler::~InquiryHandler()
{
}

void InquiryHandler::processArticleInquiryOpen(
    inquiry::ArticleInquiryResponse& response,
    const inquiry::ArticleInquiryRequest& request)
{
    pxCustBase* customer;

    csc::base::ReturnStruct branchCheckResult = Helper::checkBranch(getSession(), request.BranchNo);
    if (branchCheckResult.ErrorCode != nError().ErrorNumber())
    {
        response.__set_RetValue(branchCheckResult);
        return;
    }

    basar::Int16 AlterVZ = 0;
    AlterVZ = getSession()->CustomerRouting(request.CustomerNo);
    if (AlterVZ > 0)
    {
        customer = getSession()->CustomerId(request.CustomerNo, AlterVZ);
    }
    else
    {
        customer = getSession()->CustomerId(request.CustomerNo);
    }
    if (customer == NULL)
    {
        response.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        return;
    }
    if (getSession()->NewOrderInfo() == NULL)
    {
        response.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        return;
    }
    if (false == getSession()->Order()->IsGoodState())
    {
        response.__set_RetValue(Helper::getReturnStructFromError(*getSession()->Order()));
        return;
    }
    response.__set_BranchNo     (getSession()->Order()->FilialNr());
    response.__set_CustomerNo   (getSession()->Order()->IDFNr());
    response.__set_PharmacyName (getSession()->Order()->Customer()->NameApo()());
    response.__set_XmlInfoLevel (static_cast < csc::types::XMLInfoLevelEnum::type > (getSession()->Order()->Customer()->XMLInfoLevel() - '0')); // TODO
    response.__set_RetValue(Helper::getReturnStructFromError(*getSession()->Order()));
}



void InquiryHandler::processArticleInquiryPosition(
        inquiry::ArticleInquiryPositionResponse& response,
        const inquiry::ArticleInquiryPositionRequest request)
{
    basar::Int32 articleNo = 0;
    pxArticleCodes ArtCode(getSession().get(), request.ArticleCode.c_str());
    if (ArtCode.Get())
    {
    }
    else
    {
        articleNo = ArtCode.ArticleNo();
    }

    if (request.__isset.InternalPosReference)
    {
        response.__set_InternalPosReference(request.InternalPosReference);
    }

    pxOrderItem* orderitem = getSession()->ItemQuery(articleNo, request.QuantityOrdered);
    if (orderitem == NULL)
    {
        response.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        return;
    }

    setArticleDelivered(orderitem, request.ArticleCode, response);

    // prices
    Helper::getPriceInformation(response, orderitem);

    // quantities
    response.__set_QuantityOrdered(request.QuantityOrdered);
    response.__set_QuantityReserved(orderitem->MengeReserviert());
    if (getSession()->Order()->Customer()->IsNoInfoLevel() || getSession()->Order()->Customer()->IsInfoLevelLow() || 0 == request.QuantityOrdered)
    {
        if (orderitem->MengeGeliefert() > 0)
            response.__set_Available(true);
        else
            response.__set_Available(false);
    }
    else
    {
        response.__set_QuantityLack                 (request.QuantityOrdered -
                                                    orderitem->MengeGeliefert() -
                                                    orderitem->MengeMoeglich() -
                                                    orderitem->MengeNachgeliefert() -
                                                    orderitem->MengeDisponiert());
        if (response.QuantityLack < 0)
            response.__set_QuantityLack(0);
        response.__set_QuantityInterBranch          (orderitem->TotalIBTQuantity());
        response.__set_QuantityInterBranchPossible  (orderitem->MengeMoeglich());
        response.__set_QuantityRestDelivery         (orderitem->MengeNachgeliefert());
        if (response.QuantityRestDelivery == 0)
        {
            if (orderitem->IsRestDeliveryPossible())
            {
                response.__set_QuantityRestDelivery(response.QuantityLack);
                response.__set_QuantityLack(0);
            }
        }
        response.__set_QuantityDelivered            (orderitem->MengeGeliefert());
        response.__set_QuantityDispo                (orderitem->MengeDisponiert());
        response.__set_QuantityNatra                (orderitem->MengeNatra());
        response.__set_BranchNoIbt                  (getSession()->Order()->AuxFil());
    }

    if (getSession()->isSwitzerland())
    {
        if (getSession()->Order()->Customer()->Flags().ExpiryInfo() == '1' || getSession()->Order()->Customer()->Flags().ExpiryInfo() == '3')
        {
            response.__set_ExpiryDate(orderitem->ArticleExpireDate());
        }
    }
    else
    {
        response.__set_ExpiryDate(orderitem->ArticleExpireDate());
    }

    // codes
    if (getSession()->isFrance() || getSession()->isFrancePrewhole())
    {
        pxCountryCodes* CC = getSession()->CountryCodesInfo(getSession()->Order()->FilialNr(), response.CodeBlocage.c_str());
        if (CC != NULL)
        {
            response.__set_SeraCode(CC->SeraCode()());
            response.__set_XmlCode(CC->XMLCode()());
            response.__set_XmlText(CC->XMLText()());
            delete CC;
        }
    }
    else if (getSession()->Country() == "AU" || getSession()->isGermany())
    {
        basar::VarString xmlcode;
        xmlcode.format("%ld", response.RetValue.ErrorCode/100);
        response.__set_XmlCode(xmlcode);
        if (response.RetValue.ErrorCode != 0)
        {
            pxCountryCodes* CC = getSession()->CountryCodesInfo(getSession()->Order()->FilialNr(), xmlcode.c_str(), (short)pxCountryCodes::CCT_XMLCODE);
            if(CC != NULL)
            {
                response.__set_SeraCode(CC->SeraCode()());
                response.__set_XmlText(CC->XMLText()());
                response.__set_LackReasonCountryCode(CC->InfoCode()());
                delete CC;
            }
        }
    }

    // Ausweichartikel gebucht
    if (orderitem->IsQStateAlternate() || orderitem->IsReimportArtikel() || (orderitem->SubstProposalArticleNo() > 0L))
    {
        csc::order::ArticleInformation articleOrdered;
        articleOrdered.__set_ArticleCode(request.ArticleCode);
        articleOrdered.__set_ArticleNo(articleNo);
        articleOrdered.__set_Ean(getSession()->ConvertPzn2Ean(articleNo, 13)());
        pxArticleInfo* ArtInfo = orderitem->ArticleInfoRequest(articleNo, orderitem->MengeBestaetigt());
        if (ArtInfo != NULL)
        {
            basar::VarString tmp;

            tmp = ArtInfo->ArtBase()->Bezeichnung()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrdered.__set_ArticleName(tmp);

            tmp = ArtInfo->ArtBase()->ArtikelLangname()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrdered.__set_ArticleLongName(tmp);

            tmp = ArtInfo->ArtBase()->Einheit()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrdered.__set_ArticleUnit(tmp);

            tmp = ArtInfo->ArtBase()->Darreichform()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrdered.__set_ArticleHandout(tmp);

            articleOrdered.__set_PricePharmacyPurchase(ArtInfo->PreisEKApo());
            articleOrdered.__set_PriceCustomerPurchase(ArtInfo->PreisEKApo());
            articleOrdered.__set_PricePharmacySell(ArtInfo->PreisVKApo());
        }
        response.__set_ArticleOrdered(articleOrdered);
    }

    if (getSession()->isAustria())
    {
        pxSupplDeliveryInfo deliveryInfo(getSession().get(), orderitem->ArtikelNr());
        deliveryInfo.Get();
        if (deliveryInfo.IsGoodState())
        {
            response.__set_PredictedAvailabilityDate(deliveryInfo.PredictedAvailDate().getDate());
        }
        response.__set_LackReasonList(orderitem->GetLackReasonList().c_str());
    }

    order::TourInformation tourInfo = Helper::getPositionDeliveryInformation(orderitem, true);
    response.__set_TourInfo(tourInfo);

    if (orderitem->SubstProposalArticleNo() > 0L)
    {
        std::stringstream s;
        s << CMSG_ART_REIMPORT_PROPOSAL;
        response.__set_LackReasonList(s.str());
    }

    char TEXT[100];
    memset(TEXT, 0, sizeof(TEXT));
    int errCode = orderitem->GetError(TEXT);
    if (errCode > 100000)
    {
        errCode /= 100;
    }

    csc::base::ReturnStruct retValue;
    retValue.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(errCode));
    retValue.__set_ErrorMessage(TEXT);
    response.__set_RetValue(retValue);
}

void InquiryHandler::processArticleInquiryClose(
    inquiry::ArticleInquiryResponse& response,
    const inquiry::ArticleInquiryRequest& /*request*/)
{
    order::TourInformation tourInfo = Helper::getOrderDeliveryInformation(getSession()->Order());
    response.__set_TourInfo(tourInfo);
    getSession()->Reset();
    response.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}

std::vector<basar::Int32> InquiryHandler::findArticleNosByPeriodHR(const inquiry::ArticleInquiryHRRequest& request)
{
    libcsc::customer::ICustomerRepositoryPtr repo = getSession()->getCustomerComponentManager()->getCustomerRepository();

    return repo->findArticleNosByPeriod(request.ArticleInquiryReq.BranchNo,
        request.PositionsPerPage, request.BeginningArticleNo, Helper::getBasarDateFromCscDate(request.Period.DateFrom),
        Helper::getBasarDateFromCscDate(request.Period.DateTo), static_cast<ArticleInquiryPeriodDateTypeEnum>(request.Period.DateType));
}

void InquiryHandler::setArticleDelivered(pxOrderItem* orderitem, std::string requestedArticleCode, inquiry::ArticleInquiryPositionResponse& response)
{
    order::ArticleInformation articleDelivered;
    basar::VarString tmp;

    if (orderitem->SubstProposalArticleNo() > 0L)
    {
        // Parallel import - Substitution
        boost::shared_ptr<pxArticleCodes> pArtCode = boost::shared_ptr<pxArticleCodes>(orderitem->GetArticleCode(orderitem->SubstProposalArticleNo()));
        tmp = pArtCode->ArticleCode()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        articleDelivered.__set_ArticleCode(tmp);
        articleDelivered.__set_ArticleNo(orderitem->SubstProposalArticleNo());
    }
    else
    {
        articleDelivered.__set_ArticleNo(orderitem->ArtikelNr());
        articleDelivered.__set_ArticleCode(requestedArticleCode);

        tmp = orderitem->ArticleCode()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        if (false == tmp.empty())
        {
            articleDelivered.__set_ArticleCode(tmp);
        }

        articleDelivered.__set_Ean(getSession()->ConvertPzn2Ean(orderitem->ArtikelNr(), 13)());    // TODO verify!!!

        if (orderitem->ArtBase() != NULL && orderitem->ArtBase()->IsGoodState())
        {
            short TextKey = orderitem->ArtBase()->TextKey();
            if (TextKey > 0)
            {
                pxArticleText ptext(getSession().get(), TextKey);
                if (!ptext.Get(cDBGET_READONLY))
                {
                    articleDelivered.__set_ArticleText(ptext.Text()());
                }
            }

            tmp = orderitem->ArtBase()->Bezeichnung()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleDelivered.__set_ArticleName(tmp);

            tmp = orderitem->ArtBase()->ArtikelLangname()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleDelivered.__set_ArticleLongName(tmp);

            tmp = orderitem->ArtBase()->Einheit()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleDelivered.__set_ArticleUnit(tmp);

            tmp = orderitem->ArtBase()->Darreichform()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleDelivered.__set_ArticleHandout(tmp);

            std::stringstream cb;
            cb << orderitem->ArtBase()->CodeBlocage();
            response.__set_CodeBlocage(cb.str());
        }
        else
        {
            response.__set_CodeBlocage("2");
        }
        articleDelivered.__set_ManufacturerNo(orderitem->ArtBase()->HerstellerNr());
        articleDelivered.__set_CreationDate(Helper::getCscDateFromNDate(orderitem->ArtBase()->DatumAnlage()));
        articleDelivered.__set_ChangeDate(Helper::getCscDateFromNDate(orderitem->ArtBase()->Datum_Aender()));
        articleDelivered.__set_ATCCode(orderitem->ArtBase()->ATC_Code()());

        if (getSession()->isCroatia() || getSession()->isSerbia() || getSession()->isGermany())
        {
            libcsc::customer::ArticleInfoCollectionPtr artList = getSession()->getCustomerComponentManager()->getCustomerRepository()->findArticleInfo(
                orderitem->ArtBase()->FilialNr(), orderitem->ArtBase()->ArtikelNr());
            if (artList->size() > 0)
            {
                if (getSession()->isCroatia() || getSession()->isSerbia())
                {
                    articleDelivered.__set_ManufacturerName(artList->at(0)->getManufacturerName());
                    if (getSession()->isCroatia())
                    {
                        articleDelivered.__set_ArticleInfoText(artList->at(0)->getArtInfoText());
                    }
                }
                else if (getSession()->isGermany())
                {
                    response.__set_PredictedAvailabilityDate(artList->at(0)->getAvailableFrom().getDate());
                    articleDelivered.__set_IsQuotaPPE(artList->at(0)->getQuotaPPE());

                    libcsc::customer::ArticleOrderInfoPtr artOrderInfo = getSession()->getCustomerComponentManager()->getCustomerRepository()
                        ->findArticleOrderInfo(orderitem->ArtBase()->FilialNr(), orderitem->ArtBase()->ArtikelNr());
                    if (artOrderInfo != NULL)
                    {
                        response.__set_ArticleOrderDate(artOrderInfo->getArticleOrderDate());
                        if (artOrderInfo->getIsArticleOrderEffective())
                        {
                            response.__set_ArticleGoodsReceiptTargetDate(artOrderInfo->getArticleGoodsReceiptTargetDate());
                        }
                    }
                }
            }
        }
    }

    response.__set_ArticleDelivered(articleDelivered);
}

} // namespace service
} // namespace csc
