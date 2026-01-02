//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       18.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERDM_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERDM_H

#include <icsc_loggerptr.h>
#include <list>

#include "pvhx04_includes.h"

#include "ipxvbdbconnectionptr.h"
#include "ipxvbsessionptr.h"
#include "ipxvborderentryparamcheckerptr.h"
#include "pxnarccollectlistptr.h"
#include "pxorderptr.h"

#include "pxvborderheaderptr.h"
#include "pxvborderitemptr.h"

#include "recordtypecollectionptr.h"
#include "recordtypebaseptr.h"
#include "recordtypeorderresponse_definitions.h"

#include "packagelabelcollection.h"

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{
    class PXVBOrderDM
    {
        public:
            PXVBOrderDM( ::pxOrder* );
            ~PXVBOrderDM();

        private:
            PXVBOrderDM( const PXVBOrderDM& );
            PXVBOrderDM& operator= ( const PXVBOrderDM& );

        public:
            void                                        init();
            void                                        shutdown();
            void                                        injectPXVBDBConnection( pxVerbund::IPXVBDBConnectionPtr );
            void                                        injectPXVBSession( pxVerbund::IPXVBSessionPtr );
            void                                        injectPXVBOrderEntryParamChecker( pxVerbund::IPXVBOrderEntryParamCheckerPtr );
            void                                        injectLogger( libcsc_utils::ICSC_LoggerPtr );
            bool                                        hasToBeTransferred();
            bool                                        hasOrderTypeWithPackageLabels();
            bool                                        isMSV3Order();
            bool                                        isSwimpATOrder();
            void                                        setEventOrderTransferStarted();
            void                                        finishTransfer( domMod::corpha::recordtypes::RecordTypeCollectionPtr );
            void                                        finishWithoutTransfer();
            basar::Long64                               getTime();

            pxVerbund::PXVBOrderHeaderPtr               getOrderHeader();
            ::pxOrderItemListIter                       getOrderItemIterator();
            pxVerbund::PXVBOrderItemPtr                 createOrderItem( ::pxOrderItem* );
            PackageLabelCollection                      m_PackageLabelCollection;

        private:
            void                                        setTime();
            void                                        checkArticleCode( ::pxOrderItem* );
            void                                        completeNarcoticsTransfer( pxOrder&, basar::Long64 );
            void                                        updateNarcoticsTransfer( ::pxOrderItem& );

            recordtypes::RecordType                     processResponseRecord( pxOrder&, const recordtypes::RecordTypeBasePtr, const basar::Long64 );
            void                                        processResponseRecordA1( pxOrder&, const domMod::corpha::recordtypes::OrderResponseValues& );
            void                                        processResponseRecordP1( pxOrder&, const domMod::corpha::recordtypes::OrderResponseValues& );
            void                                        processResponseRecordS1( pxOrder&, const domMod::corpha::recordtypes::OrderResponseValues& );
            basar::VarString                            getLogDetails( pxOrder& );
            basar::VarString                            getLogDetails();

            bool                                        hasOrderLabel();

        private:
            pxVerbund::IPXVBDBConnectionPtr             m_PXVBDBConnection;
            pxVerbund::IPXVBSessionPtr                  m_PXVBSession;
            pxVerbund::IPXVBOrderEntryParamCheckerPtr   m_PXVBOrderEntryParamChecker;

            pxVerbund::PXVBOrderHeaderPtr               m_PXVBOrderHeader;

            basar::Long64                               m_Time;

            libcsc_utils::ICSC_LoggerPtr                m_Logger;

            ::pxOrderItemList*                          m_pxOrderItemList;
    };

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERDM_H
