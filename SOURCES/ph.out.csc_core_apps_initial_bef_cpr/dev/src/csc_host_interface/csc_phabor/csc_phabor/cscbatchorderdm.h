//-------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      domain module for handling batchorders on ifx side
 *  \author     Julian Machata
 *  \date       17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERDM_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERDM_H

#include "dmbase.h"
#include "icsc_loggerptr.h"
#include "cscbatchorderheaddmptr.h"
#include "cscbatchorderposdmptr.h"
#include "batchorderptr.h"
#include "ipxvbsessionptr.h"
#include "pxordertransmitptr.h"
#include "ipxvbordertransmitptr.h"
#include "icscorderobjectgetter.h"
#include "ibatchorderstatusupdaterptr.h"

class pxCustOrderInfo;

//-------------------------------------------------------------------------------------------------//
// using declarations section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
            class AccessorPropertyTableRef;
            class ConnectionRef;
        }
    }
}


namespace domMod
{
namespace batchOrder
{
namespace processing
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
    class CSCBatchOrderDM : public domMod::batchOrder::util::ICSCOrderObjectGetter
    {
        public:
            CSCBatchOrderDM( libcsc_utils::ICSC_LoggerPtr csc_logger );

            virtual ~CSCBatchOrderDM();

            void injectBatchOrderStatusUpdater  ( domMod::batchOrder::util::IBatchOrderStatusUpdaterPtr statusUpdater );
            void injectCSCBatchOrderHeadDM      ( CSCBatchOrderHeadDMPtr cscOrderHeadDM );
            void injectCSCBatchOrderPosDM       ( CSCBatchOrderPosDMPtr cscOrderPosDM );
            void injectPXVBSession              ( pxVerbund::IPXVBSessionPtr sess );
            void injectPXVBOrderTransmit        ( pxVerbund::IPXVBOrderTransmitPtr xmit );

            bool isProcessable( ::domMod::batchOrder::core::BatchOrderPtr ifxOrder );
            void saveBatchOrder( ::domMod::batchOrder::core::BatchOrderPtr ifxOrder );

        private:

            virtual pxCustBase*         getPxCustomer();
            virtual pxCustOrderInfo*    getPxCustomerInfo();
            virtual pxParameter*        getPxOrderParameter();
            virtual pxOrder*            getPxOrder();

            virtual void setPxCustomer( pxCustBase* customer );
            virtual void setPxCustomerInfo( pxCustOrderInfo* customerInfo );
            virtual void setPxOrderParameter( pxParameter* parameter );
            virtual void setPxOrder( pxOrder* order );

            virtual pxVerbund::IPXVBOrderTransmitPtr    getPxOrderTransmit();
            virtual pxVerbund::IPXVBSessionPtr          getPxVbSession();

            void SetArticleCodeValues();

            /////////////////////////////////////////////////////////////////////////
            // private member methods
            /////////////////////////////////////////////////////////////////////////
            CSCBatchOrderDM(const CSCBatchOrderDM& r);
            CSCBatchOrderDM& operator=(const CSCBatchOrderDM& r);

            void            prepareOrderHeadDM();

            void            processOrderHead( basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead );
            void            processOrderPositions( basar::db::aspect::AccessorPropertyTableRef orderPositionPropTab );

            void            logProcessingOrderHead( basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead );
            void            logProcessingOrderPos( basar::db::aspect::AccessorPropertyTable_YIterator yitOrderPos );

            void            openOrder(basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead);
            void            closeOrder(basar::db::aspect::AccessorPropertyTable_YIterator yitOrderHead);

            /////////////////////////////////////////////////////////////////////////
            // private member variables
            /////////////////////////////////////////////////////////////////////////
            libcsc_utils::ICSC_LoggerPtr                                m_CSC_Logger;

            CSCBatchOrderHeadDMPtr                                      m_CscBatchOrderHeadDM;
            CSCBatchOrderPosDMPtr                                       m_CscBatchOrderPosDM;

            pxCustBase*                                                 m_pxCustomer;
            pxCustOrderInfo*                                            m_pxCustomerInfo;
            pxParameter*                                                m_pxOrderParameter;
            pxOrderItem*                                                m_pxOrderItem;
            pxOrder*                                                    m_pxOrder;

            pxVerbund::IPXVBOrderTransmitPtr                            m_PxOrderTransmit;
            pxVerbund::IPXVBSessionPtr                                  m_PxVbSession;
            domMod::batchOrder::util::IBatchOrderStatusUpdaterPtr        m_StatusUpdater;
    };

} // namespace processing
} // namespace batchOrder
} // namespace domMod

#endif
