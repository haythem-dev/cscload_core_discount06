//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       18.09.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERHEADER_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERHEADER_H

#include <icsc_loggerptr.h>
#include <list>

#include "pvhx04_includes.h"

#include "ipxvbsessionptr.h"
#include "ipxvbdbconnectionptr.h"

#include "pxorderptr.h"
#include "pxtextdocptr.h"
#include "pxcustorderinfoptr.h"
#include "pxorderprolinkptr.h"
#include "pxorderdiscaccptr.h"
#include "pxordercalcmodeptr.h"

//#include "pxnewdiscountlistptr.h" // TODO HR-08 -> include for sharedptr

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{

class PXVBOrderHeader
{
private:
    PXVBOrderHeader( const PXVBOrderHeader& );
    PXVBOrderHeader& operator= ( const PXVBOrderHeader& );

public:
    PXVBOrderHeader( ::pxOrder* );
    ~PXVBOrderHeader();

    void                                        injectPXVBSession( pxVerbund::IPXVBSessionPtr );
    void                                        injectPXVBDBConnection( pxVerbund::IPXVBDBConnectionPtr );
    void                                        injectLogger( libcsc_utils::ICSC_LoggerPtr );

    void                                        init();
    void                                        shutdown();

    bool                                        isOrderTypeValid();
    bool                                        isCalcExpressCharge();
    basar::Int16                                getNumberOfDiscountRecords();

    ::pxOrder*                                  getOrder();
    ::pxTextDoc*                                getHeadText();
    ::pxTextDoc*                                getFooterText();
    ::pxCustOrderInfoPtr                        getOrderInfo();
    ::pxOrderDiscAccPtr                         getOrderDiscountAccount();
    ::pxOrderCalcModePtr                        getOrderCalcMode();
    ::pxOrderProLinkPtr                         getOrderProLink();

    //::pxNewDiscountListIter                   getNewDiscountListIter(); // TODO HR-08 -> get iterator for new discount list


private:
    void                                        determineOrderType();
    void                                        setPrewholesaleBatchOrderNo();
    void                                        initCountrySpecific();
    void                                        initBulgarianSpecific();
    void                                        initSerbianSpecific();
    void                                        initFranceSpecific();
    libcsc::discount::OrderPositionDiscountListPtr getNewDiscountList(); // TODO HR-08 -> get new discount list into member

private:
    bool                                        m_OrderTypeValid;


    pxVerbund::IPXVBSessionPtr                  m_PXVBSession;
    pxVerbund::IPXVBDBConnectionPtr             m_PXVBDBConnection;

    libcsc_utils::ICSC_LoggerPtr                m_Logger;

    ::pxOrder*                                  m_pxOrder;
    ::pxCustOrderInfoPtr                        m_pxCustOrderInfo;
    ::pxOrderProLinkPtr                         m_pxOrderProLink;
    ::pxOrderDiscAccPtr                         m_pxOrderDiscAcc;
    ::pxOrderCalcModePtr                        m_pxOrderCalcMode;
    //::pxNewDiscountListPtr                    m_pxNewDiscountList; // TODO HR-08 -> SharePtr for the new discount list object
};

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERHEADER_H
