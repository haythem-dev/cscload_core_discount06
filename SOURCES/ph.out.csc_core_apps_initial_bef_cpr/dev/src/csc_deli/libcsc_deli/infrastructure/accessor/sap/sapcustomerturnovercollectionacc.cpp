#include "infrastructure/accessor/sap/sapcustomerturnovercollectionacc.h"
#include "infrastructure/accessor/sap/sapcustomerturnovercollectionacc_definitions.h"

#include "infrastructure/csvfile/csvfile.h"
#include "infrastructure/parameter/iaccparameter.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"

#include <boost/filesystem.hpp>

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace sap
{
    SAPCustomerTurnoverCollectionACC::SAPCustomerTurnoverCollectionACC()
        : AccessorBase( lit::SAP_CUSTOMER_TURNOVER_COLLECTION_ACC ), m_Logger( LoggerPool::getLoggerAccessors() )
    {
    }

    SAPCustomerTurnoverCollectionACC::~SAPCustomerTurnoverCollectionACC()
    {
    }

    void SAPCustomerTurnoverCollectionACC::registerAccessorMethods( AccMethodCaller& accMethodCaller )
    {
        accMethodCaller.registerAccessMethod( lit::WRITE_SAP_CUSTOMER_TURNOVER_COLLECTION, 
                                              &SAPCustomerTurnoverCollectionACC::writeCustomerTurnoverCollection, this );
    }

    void SAPCustomerTurnoverCollectionACC::setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef pdl ) const
    {
        pdl.push_back( properties::BRANCH_NO    );
        pdl.push_back( properties::CUSTOMER_NO  );
        pdl.push_back( properties::SUM_TURNOVER );
    }

    void SAPCustomerTurnoverCollectionACC::injectACCParameter( parameter::IACCParameterPtr accParam )
    {
        m_AccParameter = accParam;
    }

    parameter::IACCParameterPtr SAPCustomerTurnoverCollectionACC::getAccParameter() const
    {
        CHECK_INSTANCE_EXCEPTION( m_AccParameter.get() );
        return m_AccParameter;
    }

    const log4cplus::Logger& SAPCustomerTurnoverCollectionACC::getLogger() const
    {
        return m_Logger;
    }

    const basar::db::aspect::ExecuteResultInfo SAPCustomerTurnoverCollectionACC::writeCustomerTurnoverCollection( basar::db::aspect::AccessorPropertyTable_YIterator,
                                                                                                            bool /*flagExcept*/ )
    {
        METHODNAME_DEF( SAPCustomerTurnoverCollectionACC, writeCustomerTurnoverCollection );
        BLOG_TRACE_METHOD( getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo resInfo;

        infrastructure::csv::CSVFile turnoverExport( getAccParameter()->getParameterValue( lit::CUSTOMER_TURNOVER_FILE ).c_str(), ';', true );
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = getPropertyTable().begin(); ! yit.isEnd(); ++yit, ++resInfo.m_affectedRows )
        {
            infrastructure::csv::CSVRow row( turnoverExport.separator() );
            row.insert( yit.getInt16( properties::BRANCH_NO )                       );
            row.insert( yit.getInt32( properties::CUSTOMER_NO )                     );
            row.insert( yit.getDecimal( properties::SUM_TURNOVER ).toNonLocString() );

            turnoverExport.append( row );
        }

        return resInfo;
    }

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
