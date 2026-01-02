//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       18.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERITEM_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERITEM_H

#include <icsc_loggerptr.h>
#include <list>

#include "pvhx04_includes.h"
#include "ipxvborderentryparamcheckerptr.h"
#include "ipxvbsessionptr.h"
#include "pxorderptr.h"
//#include "pxdeliveryposptr.h"
//#include "pxdeliveryposlistptr.h"
#include "pxitemdiscountlistptr.h"
#include "pxorderposcalcmodeptr.h"
#include <discount/orderpositiondiscount/orderpositiondiscountcollectionptr.h>

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{

class PXVBOrderItem
{
private:
    PXVBOrderItem( const PXVBOrderItem& );
    PXVBOrderItem& operator= ( const PXVBOrderItem& );

public:
    PXVBOrderItem( ::pxOrder*, ::pxOrderItem* item );
    ~PXVBOrderItem();

    void                                        injectPXVBOrderEntryParamChecker( pxVerbund::IPXVBOrderEntryParamCheckerPtr );
    void                                        injectPXVBSession( pxVerbund::IPXVBSessionPtr );
    void                                        injectLogger( libcsc_utils::ICSC_LoggerPtr );

    void                                        init();
    void                                        shutdown();

    bool                                        hasToBeTransferred();
    bool                                        checkDispo();
    bool                                        isMSV3Item();

    ::pxOrder*                                  getOrder();
    ::pxOrderItem*                              getOrderItem();
    //::pxDeliveryPosPtr                          getDeliveryInformation();
    ::pxItemDiscountListPtr                     getDiscountList();
    ::pxOrderPosCalcModePtr                     getOrderPosCalcMode();
    libcsc::discount::OrderPositionDiscountListPtr getNewDiscountList(); // TODO HR-08 -> get new discount list into member

private:
    //void                                        initDeliveryInformation();
    void                                        initCountrySpecific();
    void                                        initBulgarianSpecific();
    //void                                        initSerbianSpecific();

private:
    pxVerbund::IPXVBSessionPtr                    m_PXVBSession;
    pxVerbund::IPXVBOrderEntryParamCheckerPtr   m_PXVBOrderEntryParamChecker;

    ::pxOrder*                                  m_pxOrder;
    ::pxOrderItem*                              m_pxOrderItem;

    //::pxDeliveryPosListPtr                      m_pxDeliveryPosList;
    //::pxDeliveryPosPtr                          m_pxDeliveryPos;
    ::pxItemDiscountListPtr                     m_pxItemDiscountList;
    ::pxOrderPosCalcModePtr                     m_pxOrderPosCalcMode;

    libcsc_utils::ICSC_LoggerPtr                m_Logger;
};

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERITEM_H
