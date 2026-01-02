//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Heinlein Steffen
 *  \date       08.10.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERCOLLECTIONDM_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERCOLLECTIONDM_H

#include <icsc_loggerptr.h>
#include <iapplconfigurationptr.h>

#include "pvhx04_includes.h"
#include "ipxvbordercollection.h"
#include "ipxvbservicelocatorptr.h"
#include "pxvbordercollectiondm_definitions.h"

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{

class PXVBOrderCollectionDM : public domMod::corpha::pxVerbund::IPXVBOrderCollection
{
public:
    PXVBOrderCollectionDM( libcsc_utils::ICSC_LoggerPtr, domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr, libcsc_utils::IApplConfigurationPtr );
    ~PXVBOrderCollectionDM();

private:
    PXVBOrderCollectionDM( const PXVBOrderCollectionDM& );
    PXVBOrderCollectionDM& operator= ( const PXVBOrderCollectionDM& );

public:
    void                findOrders2BeTransferred( OrderSelectionMode );
    PXVBOrderDMPtr      getFirst();
    PXVBOrderDMPtr      getNext();
    bool                isEnd();

private:
    void                deleteOrderList();
    ::pxOrderListIter   getOrderListIterator();
    PXVBOrderDMPtr      createPXVBOrderDM( pxOrder* );

private:
    libcsc_utils::ICSC_LoggerPtr                        m_Logger;
    domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr   m_PXVBServiceLocator;
    libcsc_utils::IApplConfigurationPtr                 m_ApplConfiguration;

    ::pxOrderList*                                      m_pxOrderList;
    ::pxOrderListIter                                   m_pxOrderListIter;
};

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERCOLLECTIONDM_H
