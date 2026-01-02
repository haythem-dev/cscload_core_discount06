//-------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      domain module for handling batchorders on ifx side
 *  \author     Julian Machata
 *  \date       17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "cscbatchorderdm.h"
#include "cscbatchorderdm_definitions.h"
#include "cscbatchorderdmptr.h"
#include "cscbatchorderheaddm.h"
#include "cscbatchorderposdm.h"
#include "ipxvbordertransmit.h"
#include "batchorder.h"
#include "property_definitions.h"
#include "orderprocessingexception.h"
#include "ibatchorderstatusupdater.h"
#include "pxcustinf.hpp"

namespace domMod
{
namespace batchOrder
{
namespace processing
{
//-------------------------------------------------------------------------------------------------------------------//
CSCBatchOrderDM::CSCBatchOrderDM( libcsc_utils::ICSC_LoggerPtr csc_logger )
:   m_CSC_Logger( csc_logger ),
    m_pxCustomer(0),
    m_pxCustomerInfo(0),
    m_pxOrderParameter(0),
    m_pxOrderItem(0),
    m_pxOrder(0)
{
    METHODNAME_DEF( CSCBatchOrderDM, CSCBatchOrderDM );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
CSCBatchOrderDM::~CSCBatchOrderDM()
{
    METHODNAME_DEF( CSCBatchOrderDM, ~CSCBatchOrderDM );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::injectBatchOrderStatusUpdater( domMod::batchOrder::util::IBatchOrderStatusUpdaterPtr statusUpdater )
{
    METHODNAME_DEF( CSCBatchOrderDM, injectBatchOrderStatusUpdater );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    m_StatusUpdater = statusUpdater;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::injectCSCBatchOrderHeadDM ( CSCBatchOrderHeadDMPtr cscOrderHeadDM )
{
    METHODNAME_DEF( CSCBatchOrderDM, injectCSCBatchOrderHeadDM );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    m_CscBatchOrderHeadDM = cscOrderHeadDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::injectCSCBatchOrderPosDM ( CSCBatchOrderPosDMPtr cscOrderPosDM )
{
    METHODNAME_DEF( CSCBatchOrderDM, injectCSCBatchOrderPosDM );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    m_CscBatchOrderPosDM = cscOrderPosDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::processOrderHead( basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead )
{
    METHODNAME_DEF( CSCBatchOrderDM, processOrderHead );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    logProcessingOrderHead( yitOrderHead );

    try
    {

        m_CscBatchOrderHeadDM->process( yitOrderHead );

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

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::closeOrder(basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead)
{
    METHODNAME_DEF( CSCBatchOrderDM, closeOrder );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    if ( m_PxOrderTransmit.get() != 0 && m_PxOrderTransmit->get()->Order() != 0 )
    {
        // No more data
        // End it
        if ( m_PxOrderTransmit->get()->Order()->FilialNr() == domMod::batchOrder::processing::cscBatchOrderDM::BRANCH_FOR_SAP_DELNO )
        {
            m_PxOrderTransmit->get()->CheckDoubleOrder();
        }

         m_PxOrderTransmit->get()->End(); // thats the trick

        if ( m_pxOrderParameter)
        {
            delete m_pxOrderParameter;
            m_pxOrderParameter = 0;
        }
        if ( m_pxCustomerInfo )
        {
            delete m_pxCustomerInfo;
            m_pxCustomerInfo = 0;
        }
        if ( m_pxOrder )
        {
            m_pxOrder = 0;
        }
        if ( m_pxCustomer )
        {
            m_pxCustomer = 0;
        }
    }
    m_StatusUpdater->setBatchOrderClosed( yitOrderHead );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::logProcessingOrderHead( basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead )
{
    METHODNAME_DEF( CSCBatchOrderDM, logProcessingOrderHead );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    basar::VarString vseoffset = "";
    vseoffset.itos( yitOrderHead.getInt32( properties::pharmosbatchorderhead::VSEOFFSET ) );

    basar::VarString batchorderno = "";
    batchorderno.itos( yitOrderHead.getInt32( properties::pharmosbatchorderhead::BATCHORDERNO ) );

    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "processing order: <" + batchorderno + "> vseoffset: <" + vseoffset + ">");
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::logProcessingOrderPos( basar::db::aspect::AccessorPropertyTable_YIterator yitOrderPos )
{
    METHODNAME_DEF( CSCBatchOrderDM, logProcessingOrderPos );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    basar::VarString vseoffset = "";
    vseoffset.itos( yitOrderPos.getInt32( properties::pharmosbatchorderpos::VSEOFFSET ) );

    basar::VarString articleno = "";
    articleno.itos( yitOrderPos.getInt32( properties::pharmosbatchorderpos::ARTICLENO ) );

    basar::VarString batchorderposno = "";
    batchorderposno.itos( yitOrderPos.getInt32( properties::pharmosbatchorderpos::BATCHORDERPOSNO ) );

    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "processing article: <" + articleno + "> vseoffset: <" + vseoffset + "> posno: <" + batchorderposno + ">" );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::processOrderPositions( basar::db::aspect::AccessorPropertyTableRef orderPositionPropTab )
{
    METHODNAME_DEF( CSCBatchOrderDM, processOrderHead );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    basar::db::aspect::AccessorPropertyTable_YIterator yitOrderPos = orderPositionPropTab.begin();

    for ( ; !yitOrderPos.isEnd(); ++yitOrderPos )
    {
        logProcessingOrderPos( yitOrderPos );

        m_StatusUpdater->setBatchOrderPosInProcess( yitOrderPos );
        m_CscBatchOrderPosDM->process( yitOrderPos );
        m_StatusUpdater->setBatchOrderPosClosed( yitOrderPos );
    }
}


//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::openOrder(basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead)
{
    METHODNAME_DEF( CSCBatchOrderDM, openOrder );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    m_StatusUpdater->setBatchOrderInProcess( yitOrderHead );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::injectPXVBOrderTransmit( pxVerbund::IPXVBOrderTransmitPtr  xmit )
{
    METHODNAME_DEF( CSCBatchOrderDM, injectPXVBDBConnection );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_PxOrderTransmit = xmit;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::injectPXVBSession( pxVerbund::IPXVBSessionPtr sess )
{
    METHODNAME_DEF( CSCBatchOrderDM, injectPXVBSession );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_PxVbSession = sess;
}


//-------------------------------------------------------------------------------------------------------------------//
pxCustBase* CSCBatchOrderDM::getPxCustomer()
{
    METHODNAME_DEF( CSCBatchOrderDM, getPxCustomer );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_pxCustomer;
}

//-------------------------------------------------------------------------------------------------------------------//
pxCustOrderInfo* CSCBatchOrderDM::getPxCustomerInfo()
{
    METHODNAME_DEF( CSCBatchOrderDM, getPxCustomerInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_pxCustomerInfo;
}


//-------------------------------------------------------------------------------------------------------------------//
pxParameter* CSCBatchOrderDM::getPxOrderParameter()
{
    METHODNAME_DEF( CSCBatchOrderDM, getPxOrderParameter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_pxOrderParameter;
}


//-------------------------------------------------------------------------------------------------------------------//
pxOrder* CSCBatchOrderDM::getPxOrder()
{
    METHODNAME_DEF( CSCBatchOrderDM, getPxOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_pxOrder;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::setPxCustomer( pxCustBase* customer )
{
    METHODNAME_DEF( CSCBatchOrderDM, setPxCustomer );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_pxCustomer = customer;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::setPxCustomerInfo( pxCustOrderInfo* customerInfo )
{
    METHODNAME_DEF( CSCBatchOrderDM, setPxCustomerInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_pxCustomerInfo = customerInfo;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::setPxOrderParameter( pxParameter* parameter )
{
    METHODNAME_DEF( CSCBatchOrderDM, setPxOrderParameter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_pxOrderParameter = parameter;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::setPxOrder( pxOrder* order )
{
    METHODNAME_DEF( CSCBatchOrderDM, setPxOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_pxOrder = order;
}

//-------------------------------------------------------------------------------------------------------------------//
pxVerbund::IPXVBOrderTransmitPtr CSCBatchOrderDM::getPxOrderTransmit()
{
    METHODNAME_DEF( CSCBatchOrderDM, injectPXVBSession );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_PxOrderTransmit;
}

//-------------------------------------------------------------------------------------------------------------------//
pxVerbund::IPXVBSessionPtr CSCBatchOrderDM::getPxVbSession()
{
    METHODNAME_DEF( CSCBatchOrderDM, getPxVbSession );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_PxVbSession;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderDM::saveBatchOrder( domMod::batchOrder::core::BatchOrderPtr ifxOrder )
{
    METHODNAME_DEF( CSCBatchOrderDM, saveBatchOrder );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    try
    {

        openOrder(ifxOrder->getOrderHead());
        processOrderHead        ( ifxOrder->getOrderHead()      );
        processOrderPositions   ( ifxOrder->getOrderPositions() );
        closeOrder(ifxOrder->getOrderHead());

    }
    catch ( csc_phabor::exception::OrderProcessingException& ex )
    {
        throw ex;
    }
    catch ( ... )
    {
        basar::VarString msg = "unknown error when processing order!";
        throw csc_phabor::exception::OrderProcessingException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
    }
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderDM::isProcessable(domMod::batchOrder::core::BatchOrderPtr ifxOrder)
{
    basar::Int32 posCountHead = ifxOrder->getOrderHead().getInt32(properties::pharmosbatchorderhead::POSITIONCOUNT);
    basar::Int32 posCountPos = 0;
    basar::db::aspect::AccessorPropertyTable_YIterator yitPos;

    yitPos = ifxOrder->getOrderPositions().begin();
    while (!yitPos.isEnd())
    {
        posCountPos++;
        yitPos++;
    }

    std::stringstream s;
    s << "comparePositions: head: " << posCountHead << ", pos: " << posCountPos;
    BLOG_DEBUG(m_CSC_Logger->getLogger(), s.str());

    return (posCountHead == posCountPos);
}


} // namespace processing
} // namespace batchOrder
} // namespace domMod
