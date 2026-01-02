//-------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      main interface for domain module of ifxorderheads (table pharmosbatchorderheads)
 *  \author     Julian Machata
 *  \date       17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERPOSDM_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERPOSDM_H

#include "dmbase.h"
#include "icsc_loggerptr.h"
#include "searchdmbase.h"
#include "initparamsdmptr.h"
#include "pvhx04_includes.h"
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
    class CSCBatchOrderPosDM : public domMod::DMBase< InitParamsDMPtr, CSCBatchOrderPosDM >
    {
        //--------------------------------------------------------------------------------------------------//
        // static declaration section
        //--------------------------------------------------------------------------------------------------//
        public:
            static const char* getClassName() { return "CSCBatchOrderPosDM"; }

        public:
            CSCBatchOrderPosDM( libcsc_utils::ICSC_LoggerPtr csc_logger);
            virtual ~CSCBatchOrderPosDM();

            void process( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxOrderPos );


            void injectICSCOrderObjectGetter( domMod::batchOrder::util::ICSCOrderObjectGetterPtr cscOrderObjectGetter );

        protected:
            virtual void                                                doInit( const InitParamsDMPtr );
            virtual void                                                doShutdown();

        private:
            enum RecordType{ RECORDTYPE_POSITION = 2, RECORDTYPE_ORDERHEADTEXT = 3, RECORDTYPE_ORDERHEADTYPE4 = 4 };

            /////////////////////////////////////////////////////////////////////////
            // private member methods
            /////////////////////////////////////////////////////////////////////////
            CSCBatchOrderPosDM(const CSCBatchOrderPosDM& r);
            CSCBatchOrderPosDM& operator=(const CSCBatchOrderPosDM& r);

            void processPosition();
            void processOrderHeadText();
            void processOrderHeadType4();

            pxCustBase*         getPxCustomer();
            pxCustOrderInfo*    getPxCustomerInfo();
            pxParameter*        getPxOrderParameter();
            pxOrder*            getPxOrder();
            void                setPxCustomer( pxCustBase* customer );
            void                setPxCustomerInfo( pxCustOrderInfo* customerInfo );
            void                setPxOrderParameter( pxParameter* parameter );
            void                setPxOrder( pxOrder* order );
            void                createArticleAccRestDelivery( pxArtBase* art );

            void                setBatchOrderInfo();
            void                setArticleCodeValues();
            void                setItemText(bool checkQty = false);
            void                setQuantities();
            void                setItemPrices();
            void                setItemDiscount();
            void                addOrderItem();
            void                updateArticleData();
            //void                createDeliveryPos();
            void                createDeliveryPosByCustomer();
            void                checkArticle();

            basar::VarString    getArticleCode();
            basar::Int16        getArticleType();
            basar::Int32        getArticleNo();
            basar::Int32        getQuantity();
            basar::Int32        getQuantityInKind();
            basar::Int32        getBatchOrderNo();
            basar::Int32        getBatchOrderPosNo();
            basar::Int32        getCustomerNo();
            basar::Int16        getOriginalBranchno();
            basar::VarString    get1stIBTPartner();
            basar::VarString    get2ndIBTPartner();
            basar::Int32        getCustomerOrderNo();
            basar::Int32        getCustomerPosNo();
            basar::VarString    getItemText();
            basar::VarString    getSalesIncreaseFlag();

            basar::Decimal      getPharmacyPurchasePrice();
            basar::Decimal      getDiscountPercentage();
            basar::Decimal      getInvoicePrice();
            basar::Decimal      getLineValue();
            basar::Decimal      getPieceDiscountValue();
            basar::Int16        getPriceZero();


            pxVerbund::IPXVBOrderTransmitPtr    getPxOrderTransmit();
            pxVerbund::IPXVBSessionPtr          getPxVbSession();

            void                activateOrder(  const basar::VarString orderType,
                                                const basar::VarString orderNumber,
                                                basar::Int32 pickingType,
                                                basar::Int32 bookingType,
                                                OriginTypeEnum originTypeID );

            bool                isBatchOrder();
            bool                isParameterSet();
            bool                isOrderSet();
            bool                isItemSet();
            bool                hasQuantity();
            bool                hasToSetComment();
            bool                isRestDelivery();
            bool                isQuantityOk();
            //bool                isOriginForSubsequentDelivery();
            bool                isIBTOrder();
            bool                hasToConstructDeliveryPos();

            void                setCurrentPos( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxOrderPos );

            /////////////////////////////////////////////////////////////////////////
            // private member variables
            /////////////////////////////////////////////////////////////////////////
            InitParamsDMPtr                                             m_InitParamsDMPtr;
            libcsc_utils::ICSC_LoggerPtr                                m_CSC_Logger;

            domMod::batchOrder::util::ICSCOrderObjectGetterPtr          m_CscOrderObjectGetter;

            basar::db::aspect::AccessorPropertyTable_YIterator          m_YitOrderPos;

            pxCustOrderInfo*                                            m_pxCustomerInfo;
            pxOrderItem*                                                m_pxOrderItem;
            pxOrder*                                                    m_pxOrder;

            bool                                                        m_ArticleNotOnStore;
    };

} // namespace processing
} // namespace batchOrder
} // namespace domMod

#endif
