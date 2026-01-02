//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "customerturnoverexportdm.h"

#include "domainmodule/turnover/icustomerturnovercollectionloader.h"
#include "domainmodule/sap/isapcollectionwriter.h"

#include "domainmodule/libcsc_deli_properties_definitions.h"
#include "loggerpool/libcsc_deli_loggerpool.h"

#include <libutil/domainmodule.h>
#include <libutil/version.h>
#include <libutil/exception.h>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace turnover
{
    const libutil::misc::ClassInfo& CustomerTurnoverExportDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "CustomerTurnoverExportDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    CustomerTurnoverExportDM::CustomerTurnoverExportDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( CustomerTurnoverExportDM, CustomerTurnoverExportDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    CustomerTurnoverExportDM::~CustomerTurnoverExportDM()
    {
        METHODNAME_DEF( CustomerTurnoverExportDM, ~CustomerTurnoverExportDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void CustomerTurnoverExportDM::injectCustomerTurnoverCollection( ICustomerTurnoverCollectionLoaderPtr customerTurnoverCollectionLoader )
    {
        m_CustomerTurnoverCollectionLoader = customerTurnoverCollectionLoader;
    }

    ICustomerTurnoverCollectionLoaderPtr CustomerTurnoverExportDM::getCustomerTurnoverCollectionLoader()
    {
        CHECK_INSTANCE_EXCEPTION( m_CustomerTurnoverCollectionLoader.get() );
        return m_CustomerTurnoverCollectionLoader;
    }

    void CustomerTurnoverExportDM::injectSAPCustomerTurnoverCollection( sap::ISAPCollectionWriterPtr sapCustomerTurnoverCollection )
    {
        m_SAPCustomerTurnoverCollection = sapCustomerTurnoverCollection;
    }

    sap::ISAPCollectionWriterPtr CustomerTurnoverExportDM::getSAPCustomerTurnoverCollection()
    {
         CHECK_INSTANCE_EXCEPTION( m_SAPCustomerTurnoverCollection.get() );
         return m_SAPCustomerTurnoverCollection;
    }

    const log4cplus::Logger& CustomerTurnoverExportDM::getLogger() const
    {
        return m_Logger;
    }

    void CustomerTurnoverExportDM::loadCustomerTurnoverCollection()
    {
        METHODNAME_DEF( CustomerTurnoverExportDM, loadCustomerTurnoverCollection )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getCustomerTurnoverCollectionLoader()->load(); // lt. Klaus Hinz ist die Sortierung der KSC2SAP- Datei nicht relevant !!!
    }

    void CustomerTurnoverExportDM::exportToSAP()
    {
        METHODNAME_DEF( CustomerTurnoverExportDM, exportToSAP )
        BLOG_TRACE_METHOD( getLogger(), fun );

        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = getCustomerTurnoverCollectionLoader()->get().begin(); ! yit.isEnd(); ++yit )
        {
            getSAPCustomerTurnoverCollection()->insert( yit );
        }

        getSAPCustomerTurnoverCollection()->writeCollection();
    }

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli
