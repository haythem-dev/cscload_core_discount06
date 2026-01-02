//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/accessor.h>
#include <libutil/util.h>

#include "infrastructure/accessor/customer/customeracc.h"
#include "infrastructure/accessor/customer/customeracc_definitions.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"

#include <libbasardbaspect.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace customer
{
    //---------------------------------------------------------------------------------------------//
    // accessor definition
    //---------------------------------------------------------------------------------------------//
        BEGIN_ACCESSOR_DEFINITION( lit::CUSTOMER_ACC )
            BEGIN_PROPERTY_DESCRIPTION_LIST
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NAME  )
                PROPERTY_DESCRIPTION_LIST_ADD( properties::PARTNER_NO    )

            ACCESS_METHOD( lit::SELECT_CUSTOMER_BY_PARTNERNO )
                SQL_BUILDER_CREATE   ( SelectCustomerByPartnerNo )
                SQL_BUILDER_PUSH_BACK( SelectCustomerByPartnerNo )

        END_ACCESSOR_DEFINITION

        //////////////////////////////////////////////////////////////////////////////////////////
        // BUILDER_DEFINITION( SelectCustomerByPartnerNo )
        //////////////////////////////////////////////////////////////////////////////////////////
        BUILDER_DEFINITION( SelectCustomerByPartnerNo )

        bool SelectCustomerByPartnerNo::isExecutable() const
        {
            METHODNAME_DEF( SelectCustomerByPartnerNo, isExecutable );
            static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
            BLOG_TRACE_METHOD( logger, fun );

            const bool executable = arePropertiesSet( properties::PARTNER_NO.toPropertyString() );
            
            CHECK_EXECUTABILITY( getPropertyList(), logger, fun );
            return executable;
        }

        void SelectCustomerByPartnerNo::buildSQLString()
        {
            static const basar::VarString constSQL(
            "SELECT FIRST 1 '1', trim(k.nameapo) || '=' || k.ort AS "         + properties::PARTNER_NAME.getName() +
                ", s.skdkundeaegesperrt, k.partnernr AS "                     + properties::PARTNER_NO.getName()   +
                " FROM kunde k, kundeschalter s "
                " WHERE k.mastercstno = k.idfnr "
                " AND k.partnernr = "                                         + properties::PARTNER_NO.toSQLReplacementString() +
				" and k.idfnr = s.idfnr and k.filialnr = s.vertriebszentrumnr and s.skdkundeaegesperrt = '0' "
			" UNION "
			"SELECT '2', trim(k.nameapo) || '=' || k.ort AS "                 + properties::PARTNER_NAME.getName() +
                ", s.skdkundeaegesperrt, k.partnernr AS "                     + properties::PARTNER_NO.getName()   +
                " FROM kunde k, kundeschalter s "
				" WHERE k.partnernr = "                                       + properties::PARTNER_NO.toSQLReplacementString() +
				" and k.idfnr = s.idfnr and k.filialnr = s.vertriebszentrumnr "
				" ORDER BY 1, 3 "
            );

            resolve( constSQL );
            BLOG_TRACE_SQLSTRING( libcsc_deli::LoggerPool::getLoggerAccessors() );
        }

} // end namespace customer
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
