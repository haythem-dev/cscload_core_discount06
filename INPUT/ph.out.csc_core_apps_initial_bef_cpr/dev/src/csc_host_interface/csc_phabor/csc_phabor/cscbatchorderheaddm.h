//-------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      main interface for domain module of ifxorderitems (table pharmosbatchorderpos)
 *  \author     Julian Machata
 *  \date       17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERHEADDM_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERHEADDM_H

#include "pvhx04_includes.h"
#include "dmbase.h"
#include "icsc_loggerptr.h"
#include "searchdmbase.h"
#include "initparamsdmptr.h"
#include "ipxvbsessionptr.h"
#include "ipxvbordertransmitptr.h"
#include "icscorderobjectgetterptr.h"

//-------------------------------------------------------------------------------------------------//
// namespace
//-------------------------------------------------------------------------------------------------//

namespace domMod
{
namespace batchOrder
{
namespace processing
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
    class CSCBatchOrderHeadDM : public domMod::DMBase< InitParamsDMPtr, CSCBatchOrderHeadDM >
    {
        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
        public:
            static const char* getClassName() { return "CSCBatchOrderHeadDM"; }

        public:
            CSCBatchOrderHeadDM(libcsc_utils::ICSC_LoggerPtr csc_logger);
            virtual ~CSCBatchOrderHeadDM();

            void process( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxOrderHead );

            void injectICSCOrderObjectGetter( domMod::batchOrder::util::ICSCOrderObjectGetterPtr cscOrderObjectGetter );

        protected:

            virtual void                                                doInit( const InitParamsDMPtr );
            virtual void                                                doShutdown();

        private:
            /////////////////////////////////////////////////////////////////////////
            // private member methods
            /////////////////////////////////////////////////////////////////////////
            CSCBatchOrderHeadDM(const CSCBatchOrderHeadDM& r);
            CSCBatchOrderHeadDM& operator=(const CSCBatchOrderHeadDM& r);

            pxCustBase*         getPxCustomer();
            pxCustOrderInfo*    getPxCustomerInfo();
            pxParameter*        getPxOrderParameter();
            pxOrder*            getPxOrder();
            void                setPxCustomer( pxCustBase* customer );
            void                setPxCustomerInfo( pxCustOrderInfo* customerInfo );
            void                setPxOrderParameter( pxParameter* parameter );
            void                setPxOrder( pxOrder* order );

            pxVerbund::IPXVBOrderTransmitPtr    getPxOrderTransmit();
            pxVerbund::IPXVBSessionPtr          getPxVbSession();

            basar::Int32        getCustomerNo();
            basar::Int16        getBranchNo();
            basar::VarString    getSapDeliveryNote();
            OriginTypeEnum      getOriginTypeID();
            basar::VarString    getOrderText();
            basar::VarString    getMainWareHouseFlag();
            basar::VarString    getEdiDeliveryNoteFlag();
            basar::DateTime     getCurrentDateTime();

            bool                hasToCreateNewOrder();
            bool                hasCustomerRoutes();
            bool                isTransferOrder();
            bool                isOrderValid();
            bool                isIbtOrder();
            bool                isPickingError();

            void                setSessionBranchNo();
            void                setSessionCustomerNo();
            void                setRoutes();
            void                setOrderType();
            void                setOrderText();
            void                setOriginType();
            void                setSapDeliveryNote();
            void                setValueDate();
            void                setDeliveryDate();
            void                setFreeText();
            void                setCurrentHead( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxOrderHead );
            void                setCscOrderno( basar::Int32 cscorderno );

            void                handleNewOrder();
            void                handleTransferOrder();
            void                handlePickingError();
            void                handleIbtOrder();
            void                createOrder();
            void                trim( basar::VarString& str, const basar::Int32 length, const char filler );
            void                activateOrder(  const basar::VarString& orderType,
                                                const basar::VarString& orderNumber,
                                                basar::Int32 pickingType,
                                                basar::Int32 bookingType,
                                                OriginTypeEnum originTypeID );

            void                saveOrderParameter();
            void                saveOrderInfo();
            bool greater( basar::DateTime a, basar::DateTime b );

            /////////////////////////////////////////////////////////////////////////
            // private member variables
            /////////////////////////////////////////////////////////////////////////
            InitParamsDMPtr                                             m_InitParamsDMPtr;
            libcsc_utils::ICSC_LoggerPtr                                m_CSC_Logger;
            domMod::batchOrder::util::ICSCOrderObjectGetterPtr          m_CscOrderObjectGetter;

            basar::db::aspect::AccessorPropertyTable_YIterator          m_YitOrderHead;

            bool                                                        m_CustomerOk;
    };

} // namespace processing
} // namespace batchOrder
} // namespace domMod

#endif
