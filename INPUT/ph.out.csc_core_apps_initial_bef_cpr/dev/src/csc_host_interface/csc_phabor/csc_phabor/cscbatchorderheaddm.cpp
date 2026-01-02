//-------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      main interface for domain module of ifxorderitems (table pharmosbatchorderpos)
 *  \author     Julian Machata
 *  \date       17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cscbatchorderheaddm.h"
#include "property_definitions.h"
#include "pharmosbatchorderheadacc_definitions.h"
#include "cscbatchorderdm_definitions.h"
#include "ipxvbsession.h"
#include "ipxvbordertransmitptr.h"
#include "ipxvbordertransmit.h"
#include "pxvbordertransmit.h"
#include "icscorderobjectgetter.h"
#include "icsc_logger.h"
#include "orderprocessingexception.h"
#include "pxcstbas.hpp"
#include "pxcustinf.hpp"
#include "pxcstot.hpp"
#include "pxbranch.hpp"

namespace domMod
{
namespace batchOrder
{
namespace processing
{
//-------------------------------------------------------------------------------------------------------------------//
CSCBatchOrderHeadDM::CSCBatchOrderHeadDM(libcsc_utils::ICSC_LoggerPtr csc_logger) :
    m_CSC_Logger(csc_logger)
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, CSCBatchOrderHeadDM );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
CSCBatchOrderHeadDM::~CSCBatchOrderHeadDM()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, ~CSCBatchOrderHeadDM );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::doInit( const InitParamsDMPtr initParamsDM )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, doInit );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_InitParamsDMPtr = initParamsDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::doShutdown()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, doShutdown );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );
}

//--------------------------------------------------------------------------------------------------//
// GETTER
//--------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderHeadDM::getOrderText()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getOrderText );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderHead.getString( properties::pharmosbatchorderhead::INFOTEXT );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderHeadDM::getMainWareHouseFlag()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getMainWareHouseFlag );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderHead.getString( properties::pharmosbatchorderhead::PARENTCOMPANYFLAG );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderHeadDM::getEdiDeliveryNoteFlag()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getEdiDeliveryNoteFlag );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderHead.getString( properties::pharmosbatchorderhead::EDIDELIVERYNOTEFLAG );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::DateTime CSCBatchOrderHeadDM::getCurrentDateTime()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, doShutdown );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return basar::DateTime();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderHeadDM::getCustomerNo()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getCustomerNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderHead.getInt32( properties::pharmosbatchorderhead::CUSTOMERNO );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int16 CSCBatchOrderHeadDM::getBranchNo()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getBranchNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return  m_YitOrderHead.getInt16( properties::pharmosbatchorderhead::BRANCHNO );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderHeadDM::getSapDeliveryNote()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getSapDeliveryNote );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    if ( getBranchNo() == domMod::batchOrder::processing::cscBatchOrderDM::BRANCH_FOR_SAP_DELNO )
    {
        return m_YitOrderHead.getString( properties::pharmosbatchorderhead::SAPDELIVERYNOTE );
    }

    return "";
}

//-------------------------------------------------------------------------------------------------------------------//
OriginTypeEnum CSCBatchOrderHeadDM::getOriginTypeID()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getOriginTypeID );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    OriginTypeEnum  ret = cORTYPE_UNKNOWN;

    ret = pxOrderCloseParam::ConvertBatchSchreiben( m_YitOrderHead.getString( properties::pharmosbatchorderhead::ORIGINTYPE ).c_str() );

    return ret;
}

//-------------------------------------------------------------------------------------------------------------------//
pxCustBase* CSCBatchOrderHeadDM::getPxCustomer()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getPxCustomer );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxCustomer();
}

//-------------------------------------------------------------------------------------------------------------------//
pxCustOrderInfo* CSCBatchOrderHeadDM::getPxCustomerInfo()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getPxCustomerInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxCustomerInfo();
}

//-------------------------------------------------------------------------------------------------------------------//
pxParameter* CSCBatchOrderHeadDM::getPxOrderParameter()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getPxOrderParameter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxOrderParameter();
}

//-------------------------------------------------------------------------------------------------------------------//
pxOrder* CSCBatchOrderHeadDM::getPxOrder()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getPxOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxOrder();
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setPxCustomer( pxCustBase* customer )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setPxCustomer );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter->setPxCustomer(customer);
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setPxCustomerInfo( pxCustOrderInfo* customerInfo )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setPxCustomerInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter->setPxCustomerInfo(customerInfo);
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setPxOrderParameter( pxParameter* parameter )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setPxOrderParameter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter->setPxOrderParameter(parameter);
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setPxOrder( pxOrder* order )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setPxOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter->setPxOrder(order);
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setCscOrderno( basar::Int32 cscorderno)
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setCscOrderno );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_YitOrderHead.setInt32( properties::pharmosbatchorderhead::CSCORDERNO, cscorderno );
}


pxVerbund::IPXVBOrderTransmitPtr CSCBatchOrderHeadDM::getPxOrderTransmit()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getPxOrderTransmit );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxOrderTransmit();
}

//-------------------------------------------------------------------------------------------------------------------//
pxVerbund::IPXVBSessionPtr CSCBatchOrderHeadDM::getPxVbSession()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, getPxVbSession );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxVbSession();
}

//--------------------------------------------------------------------------------------------------//
// SETTER
//--------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setOrderText()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setOrderText );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    // Write order type into table kdauftragbem

    basar::VarString orderText = "";
    basar::VarString mainWareHouseFlag = "";

    switch (getOriginTypeID())
    {
    case cORTYPE_CLEARING:
    {
        orderText = getOrderText();
        mainWareHouseFlag = getMainWareHouseFlag();

        if (cscBatchOrderDM::ORDER_FLAG_PICKING_ERROR == mainWareHouseFlag)
        {
            getPxOrder()->SetCommiError();
        }
        break;
    }
    case cORTYPE_INSTALLER:
    {
        orderText = cscBatchOrderDM::ORDER_TEXT_SET_UP;
        orderText.append(cscBatchOrderDM::ORDER_TEXT_DEFAULT);
        break;
    }
    case cORTYPE_STOCK:
    {
        orderText = cscBatchOrderDM::ORDER_TEXT_WAREHOSUE;
        orderText.append(cscBatchOrderDM::ORDER_TEXT_DEFAULT);
        break;
    }
    case cORTYPE_STOCK_DISTRIBUTION:
    {
        orderText = cscBatchOrderDM::ORDER_TEXT_WAREHOUSE_DISTRIBUTION;
        orderText.append(cscBatchOrderDM::ORDER_TEXT_DEFAULT);
        break;
    }
    case cORTYPE_INDUSTRIAL_RETURN:
    {
        orderText = cscBatchOrderDM::ORDER_TEXT_INDUSTRY_RETURN;
        orderText.append(cscBatchOrderDM::ORDER_TEXT_DEFAULT);
        break;
    }
    case cORTYPE_PARENT_COMPANY:
    {
        orderText = getOrderText();
        mainWareHouseFlag = getMainWareHouseFlag();
        if (cscBatchOrderDM::ORDER_FLAG_MAIN_WAREHOUSE == mainWareHouseFlag)
        {
            getPxOrder()->SetParentCompany();
        }
        break;
    }
    default:
    {
        orderText.clear();
        break;
    }
    }

    if (!m_CustomerOk)
    {

        basar::VarString strCustomerNo = "";
        strCustomerNo.itos( getCustomerNo() );

        if ( orderText.empty() )
        {
            orderText = cscBatchOrderDM::ORDER_TEXT_WRONG_CUSTOMER + strCustomerNo;
        }
        else
        {
            orderText = cscBatchOrderDM::ORDER_TEXT_WRONG_CUSTOMER + strCustomerNo + " " + orderText;
        }

        getPxOrderTransmit()->get()->SetWrongIDFNr(strCustomerNo.c_str());
    }

    if (!orderText.empty())
    {
        getPxOrder()->Bemerkungen(orderText.c_str());
    }
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setRoutes()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setRoutes );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    if ( !hasCustomerRoutes() )
    {
        activateOrder ( m_YitOrderHead.getString( properties::pharmosbatchorderhead::ORDERTYPE ),
                        "0",
                        m_YitOrderHead.getString( properties::pharmosbatchorderhead::PICKINGTYPE ).stoi(),
                        m_YitOrderHead.getString( properties::pharmosbatchorderhead::BOOKINGTYPE ).stoi(),
                        getOriginTypeID()
            );
    }
    else
    {
        // new order with customer
        createOrder();
    }
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setSessionBranchNo()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setSessionBranchNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    pxBranch customerBranch( getPxVbSession()->get(), getBranchNo() );

    if (customerBranch.IsGoodState())
    {
        *(getPxVbSession()->get()->Branch()) = customerBranch;
    }
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setSessionCustomerNo()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setSessionCustomerNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    pxCustBase* customer = getPxOrderTransmit()->get()->CustomerId(getCustomerNo());
    if ( NULL == customer )
    {
        customer = getPxOrderTransmit()->get()->CustomerId(getPxOrderTransmit()->get()->Branch()->BGANr()); // todo really???

        if (customer == NULL)
        {
            getPxOrderTransmit()->get()->CancelTransmission();
            basar::VarString msg = "customer could not be found, order canceled!";
            throw csc_phabor::exception::OrderProcessingException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
        }
        else
        {
            m_CustomerOk = false;
        }
    }

    setPxCustomer(customer);
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setOrderType()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setOrderType );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    nString orderhead = m_YitOrderHead.getString( properties::pharmosbatchorderhead::ORDERTYPE ).c_str();

    getPxOrder()->OrderType( orderhead, m_YitOrderHead.getString( properties::pharmosbatchorderhead::PICKINGTYPE )[0],
                        m_YitOrderHead.getString( properties::pharmosbatchorderhead::BOOKINGTYPE )[0]);
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setOriginType()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setOriginType );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    getPxOrder()->BatchSchreiben(getOriginTypeID());
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setSapDeliveryNote()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setSapDeliveryNote );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    basar::VarString sapDeliveryNote = getSapDeliveryNote();

    if ( "" == sapDeliveryNote )
    {
       return;
    }

    trim( sapDeliveryNote, 9, '0' );

    getPxOrder()->SetReferenceNr( &sapDeliveryNote[0] );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setValueDate()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setValueDate );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    basar::Date  basarValueDate = m_YitOrderHead.getDate(properties::pharmosbatchorderhead::VALUEDATE);
    basar::Int16 valueMonthsAuto = getPxOrder()->OrderType().ValMonthsAuto();

    if (basarValueDate.isValid())
    {
        nDate nValueDate(basarValueDate.getDate());
        getPxOrder()->SetDatumValutaBatch(nValueDate);

        if (valueMonthsAuto > 0)
        {
            nValueDate.AddMonth(valueMonthsAuto);
        }
        getPxOrder()->ValDate(nValueDate);
    }
    else
    {
        if (valueMonthsAuto > 0)
        {
            getPxOrder()->ValDateMonAuto(valueMonthsAuto);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setFreeText()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setFreeText );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    OriginTypeEnum originTypeID = getOriginTypeID();

    if ( originTypeID != cORTYPE_PARENT_COMPANY &&
         originTypeID != cORTYPE_CLEARING )
    {

        basar::VarString freeText = getOrderText();
        basar::VarString tempText = freeText;

        tempText.trim ( basar::cmnutil::BString::ALL );

        if ( !tempText.empty() )
        {
            getPxOrderTransmit()->get()->FreeTextDoc(nString(freeText.c_str()));
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setDeliveryDate()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setDeliveryDat );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    // delivery date is in format yymmdd, to get YYYYmmdd you have to add VSE_CENTURY_DEF
    // if there is no delivery date, it is a kind of filler from vse which is defined as VSE_RUBBISH

    basar::Date     deliveryDate = m_YitOrderHead.getDate( properties::pharmosbatchorderhead::DELIVERYDATE );
    basar::DateTime deliveryDateTime ( deliveryDate.getYear(), deliveryDate.getMonth(), deliveryDate.getDay() );
    basar::DateTime now = getCurrentDateTime();

    if ( !deliveryDate.isValid() )  // dont check deliveryDateTime cause somehow its always invalid
    {
        return;
    }

    if ( greater( now, deliveryDateTime ) )
    {
        return;
    }

    getPxOrder()->SetDatumAuslieferung(deliveryDateTime.getDate());
    getPxOrder()->SetVerzoegerAusgeliefert();
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::injectICSCOrderObjectGetter( domMod::batchOrder::util::ICSCOrderObjectGetterPtr cscOrderObjectGetter )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, injectICSCOrderObjectGetter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter = cscOrderObjectGetter;
}

//--------------------------------------------------------------------------------------------------//
// SAVER
//--------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::saveOrderParameter()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, saveParameter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    // set new entry in parameter table
    pxParameter* parameter;

    parameter = new pxParameter( getPxVbSession()->get(),
                                 getBranchNo() ,
                                 cscBatchOrderDM::PARAMETER_APPLICATION.c_str(),
                                 cscBatchOrderDM::PARAMETER_REASON.c_str(),
                                 cscBatchOrderDM::PARAMETER_NAME.c_str()
                               );

    if ( parameter->Get(cDBGET_READONLY))
    {
        delete parameter;
        parameter = 0;
    }

    setPxOrderParameter(parameter);
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::saveOrderInfo()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, saveOrderInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    //basar::Int32 batchNo = m_YitOrderHead.getInt32( properties::pharmosbatchorderhead::TRANSFERORDERNO  );
    basar::Int32 batchNo = m_YitOrderHead.getInt32( properties::pharmosbatchorderhead::BATCHORDERNO  );
    basar::VarString ediDeliveryNoteFlag = getEdiDeliveryNoteFlag();

    if (batchNo <= 0 )
    {
        return;
    }

    pxCustOrderInfo* customerInfo = new pxCustOrderInfo((getPxVbSession()->get()));
    customerInfo->CheckMembers();
    customerInfo->SetOrderNr(getPxOrder()->KdAuftragNr());
    if (ediDeliveryNoteFlag.empty())
    {
        customerInfo->SetEdiLieferSchein(' ');
    }
    else
    {
        customerInfo->SetEdiLieferSchein(ediDeliveryNoteFlag[0]);
    }

    customerInfo->SetBatchOrderNr(batchNo);
    customerInfo->Put();
    setPxCustomerInfo( customerInfo );
}

//--------------------------------------------------------------------------------------------------//
// CHECKER
//--------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderHeadDM::isTransferOrder()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, isTransferOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    OriginTypeEnum originTypeID = getOriginTypeID();

    if ( originTypeID == cORTYPE_TRANSFER ||
         originTypeID == cORTYPE_BATCH_TRANSFER )
    {

        return true;
    }
    return false;
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderHeadDM::hasToCreateNewOrder()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, hasToCreateNewOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    OriginTypeEnum originTypeID = getOriginTypeID();

    return (originTypeID != cORTYPE_AUXILIARY &&
            originTypeID != cORTYPE_KOMMI_ERROR);
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderHeadDM::hasCustomerRoutes()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, hasCustomerRoutes );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return !getPxOrderTransmit()->get()->Customer()->IsNoRoutesToday(); // negate result because: true == no routes, false == routes
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderHeadDM::isPickingError()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, isPickingError );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return ( cORTYPE_KOMMI_ERROR == getPxOrder()->BatchSchreiben() );
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderHeadDM::isOrderValid()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, isOrderValid );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return ( getPxCustomer() != 0 );
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderHeadDM::isIbtOrder()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, isIbtOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return ( 0 == getPxOrder()->BatchSchreiben() );
}

//--------------------------------------------------------------------------------------------------//
// HELPER
//--------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::activateOrder( const basar::VarString& orderType,
                                         const basar::VarString& orderNumber,
                                         basar::Int32 pickingType,
                                         basar::Int32 bookingType,
                                         OriginTypeEnum originTypeID )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, activateOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    basar::VarString strPickingType = "";
    basar::VarString strBookingType = "";

    strPickingType.itos(pickingType);
    strBookingType.itos(bookingType);

    pxOrder* order = getPxOrder();
    order = getPxOrderTransmit()->get()->OrderType( orderType.c_str(),
                                                    orderNumber.c_str(),
                                                    strPickingType[0],
                                                    strBookingType[0],
                                                    originTypeID );

    setPxOrder( order );
    setCscOrderno( (int) order->KdAuftragNr() );

    if ( 0 == order )
    {
        basar::VarString msg = "DB error when activatng order while processing head!";
        throw csc_phabor::exception::OrderProcessingException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
    }
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::createOrder()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, createOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    pxOrder* order = getPxOrder();

    order = getPxOrderTransmit()->get()->OrderList()->NewOrder(*(getPxOrderTransmit()->get()->Customer()));
    setPxOrder( order );

    if ( 0 == order )
    {
        basar::VarString msg = "DB error when creating order!";
        throw csc_phabor::exception::OrderProcessingException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
    }
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::trim( basar::VarString& str, const basar::Int32 length, const char filler )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, trim );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    nString conv (str.c_str());
    conv.Trim( length, nString::cLEADING, filler );

    str = basar::VarString( conv() );
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderHeadDM::greater( basar::DateTime a, basar::DateTime b )
{
    bool ret = false;

    if ( a.getYear() > b.getYear() )
    {
        return true;
    }
    else if (a.getYear() < b.getYear())
    {
        return false;
    }

    if ( a.getMonth() > b.getMonth() )
    {
        return true;
    }
    else if (a.getMonth() < b.getMonth())
    {
        return false;
    }

    if ( a.getDay() > b.getDay() )
    {
        return true;
    }
    else if (a.getDay() < b.getDay())
    {
        return false;
    }

    if ( a.getHour() > b.getHour() )
    {
        return true;
    }
    else if (a.getHour() < b.getHour())
    {
        return false;
    }

    if ( a.getMinute() > b.getMinute() )
    {
        return true;
    }
    else if (a.getMinute() < b.getMinute())
    {
        return false;
    }

    if ( a.getSec() > b.getSec() )
    {
        return true;
    }
    else if (a.getSec() < b.getSec())
    {
        return false;
    }

    if ( a.getMSec() > b.getMSec() )
    {
        return true;
    }
    else if (a.getMSec() < b.getMSec())
    {
        return false;
    }

    return ret;
}

//--------------------------------------------------------------------------------------------------//
// CORE
//--------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::handleTransferOrder()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, saveOrderInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    setValueDate();
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::handleNewOrder()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, createNewOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    setRoutes();

    if ( !isOrderValid() )
    {
        return ; // exception!!
    }

    setOrderType();
    setOriginType();
    setSapDeliveryNote();

    saveOrderInfo();

    if ( isTransferOrder() )
    {
        handleTransferOrder();
    }

    setDeliveryDate();
    setOrderText();
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::handleIbtOrder()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, handleIbtOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    getPxOrder()->BatchSchreiben(getOriginTypeID());
    getPxOrder()->Bemerkungen(cscBatchOrderDM::ORDER_TEXT_IBT);
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::handlePickingError()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, handlePickingError );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    getPxOrder()->Bemerkungen(cscBatchOrderDM::ORDER_TEXT_PICKING_ERROR);
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::setCurrentHead( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxOrderHead )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setCurrentHead );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_YitOrderHead = yitIfxOrderHead;
    m_CustomerOk = true;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderHeadDM::process( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxOrderHead )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, process );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    try
    {

        setCurrentHead( yitIfxOrderHead );
        std::stringstream ss;
        yitIfxOrderHead.toStream(ss);

        setSessionBranchNo();
        setSessionCustomerNo();
        saveOrderParameter();

        if ( !isOrderValid() )
        {
            return;
        }

        if ( hasToCreateNewOrder() )
        {
            handleNewOrder();
        }

        activateOrder(  m_YitOrderHead.getString( properties::pharmosbatchorderhead::ORDERTYPE ),
                        cscBatchOrderDM::DEFAULT_ORDERNO,
                        m_YitOrderHead.getString( properties::pharmosbatchorderhead::PICKINGTYPE ).stoi(),
                        m_YitOrderHead.getString( properties::pharmosbatchorderhead::BOOKINGTYPE ).stoi(),
                        getOriginTypeID()
                    );

        if ( !isOrderValid() )
        {
            //strcpy(retvalue_, bDBERROR);
            return ;
        }

        if ( isIbtOrder() )
        {
            handleIbtOrder();
        }
        else
        {

            if ( isPickingError() )
            {
                handlePickingError();
            }

            setFreeText();
        }

    }
    catch ( csc_phabor::exception::OrderProcessingException& ex )
    {
        throw ex;
    }
    catch ( ... )
    {
        basar::VarString msg = "unknown error when processing orderhead!";
        throw csc_phabor::exception::OrderProcessingException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
    }
}

} // namespace processing
} // namespace batchOrder
} // namespace domMod
