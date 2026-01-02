#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_CUSTOMERTURNOVEREXPORTDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_CUSTOMERTURNOVEREXPORTDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icustomerturnoverexporter.h"

#include "domainmodule/turnover/icustomerturnovercollectionloaderptr.h"
#include "domainmodule/sap/isapcollectionwriterptr.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace turnover
{
    class CustomerTurnoverExportDM : public ICustomerTurnoverExporter
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        CustomerTurnoverExportDM();
        ~CustomerTurnoverExportDM();

        void injectCustomerTurnoverCollection( ICustomerTurnoverCollectionLoaderPtr );
        void injectSAPCustomerTurnoverCollection( sap::ISAPCollectionWriterPtr );

        // from ICustomerTurnverExporter interface
        void                                                        loadCustomerTurnoverCollection();
        void                                                        exportToSAP();

    private:
        // forbidden
        CustomerTurnoverExportDM( const CustomerTurnoverExportDM& );
        CustomerTurnoverExportDM& operator = ( const CustomerTurnoverExportDM& );
        
        ICustomerTurnoverCollectionLoaderPtr                        getCustomerTurnoverCollectionLoader();
        sap::ISAPCollectionWriterPtr                                getSAPCustomerTurnoverCollection();
                    
        const log4cplus::Logger&                                    getLogger() const;

    private:
        const log4cplus::Logger&                                    m_Logger;

        ICustomerTurnoverCollectionLoaderPtr                        m_CustomerTurnoverCollectionLoader;
        sap::ISAPCollectionWriterPtr                                m_SAPCustomerTurnoverCollection;
    };

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_CUSTOMERTURNOVEREXPORTDM_H
