//----------------------------------------------------------------------------//
/*! \file
 *  \brief  PXVBComponentManager
 *  \author Steffen Heinlein
 *  \date   09.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBCOMPONENTMANAGER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PXVERBUND_PXVBCOMPONENTMANAGER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "ipxvbservicelocator.h"
#include "ipxvbsessionptr.h"
#include "ipxvbordertransmitptr.h"
#include "ipxvbinitializationptr.h"
#include "ipxvborderentryparamcheckerptr.h"
#include "pxorderentryparamptr.h"
#include "pxordertransmitptr.h"
#include <iapplconfigurationptr.h>
#include <icsc_loggerptr.h>

#include "pvhx04_includes.h"


//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace batchOrder
{
namespace pxVerbund
{

class PXVBComponentManager : public IPXVBServiceLocator
{
    public:
        PXVBComponentManager( libcsc_utils::IApplConfigurationPtr, libcsc_utils::ICSC_LoggerPtr );
        ~PXVBComponentManager();

        virtual IPXVBSessionPtr                     getPXVBSession();
        virtual IPXVBInitializationPtr              getPXVBInitialization();
        virtual IPXVBOrderEntryParamCheckerPtr      getPXVBOrderEntryParamChecker();
        virtual IPXVBOrderTransmitPtr               getPXVBOrderTransmit();

        void    injectCscDbConnection(libcsc::persistence::ConnectionPtr);

    private:
        ///////////////////////////////////////////////////////////////////////////////////
        // member methods
        ///////////////////////////////////////////////////////////////////////////////////
        PXVBComponentManager( const PXVBComponentManager& );
        PXVBComponentManager& operator= ( const PXVBComponentManager& );

        pxOrderTransmitPtr                          getPXOrderTransmit();
        pxOrderEntryParamPtr                        getPXOrderEntryParam();

        libcsc::persistence::ConnectionPtr          getCscDbConnection() const;

        ///////////////////////////////////////////////////////////////////////////////////
        // member variables
        ///////////////////////////////////////////////////////////////////////////////////
        libcsc::persistence::ConnectionPtr          m_CscDbConnection;

        // real pxverbund
        ::pxOrderTransmitPtr                        m_pxOrderTransmit;
        ::pxOrderEntryParamPtr                      m_pxOrderEntryParam;

        // pxverbund wrappers (csc_phatra specific)
        IPXVBSessionPtr                             m_PXVBSession;
        IPXVBInitializationPtr                      m_PXVBInitialization;
        IPXVBOrderEntryParamCheckerPtr              m_PXVBOrderEntryParamChecker;
        IPXVBOrderTransmitPtr                       m_PXVBOrderTransmit;

        // configuration & logger
        libcsc_utils::IApplConfigurationPtr         m_IApplConfiguration;
        libcsc_utils::ICSC_LoggerPtr                m_CSC_Logger;
};

} // end namespace pxVerbund
} // end namespace batchOrder
} // end namespace domMod

#endif
