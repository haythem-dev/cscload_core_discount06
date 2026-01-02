//-----------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      declaration of database login class
 *  \author     Bischof Bjoern
 *  \date       15.06.2015
 *  \version    00.00.00.01 first version
 */ 
//-----------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------//
// include section
//-----------------------------------------------------------------------------------------------//
#include "dbparameter.h"

#include <libutil/util.h>
#include <libutil/log4cplus.h>
#include <libutil/dbconnection.h>
#include "loggerpool/csc_phadex_loggerpool.h"

//-----------------------------------------------------------------------------------------------//
// class definition section
//-----------------------------------------------------------------------------------------------//
namespace csc_phadex
{
	namespace infrastructure
	{
		namespace parameter
		{
			DBParameter::DBParameter()
			: m_Logger( LoggerPool::getLoggerCsc_phadex() )
			{
				METHODNAME_DEF( DBParameter, UserAdminParameterGetter )
				BLOG_TRACE_METHOD( m_Logger, fun );
			}

			DBParameter::~DBParameter()
			{
				METHODNAME_DEF( DBParameter, ~UserAdminParameterGetter )
				BLOG_TRACE_METHOD( m_Logger, fun );
			}

            void DBParameter::injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr parameterGateway )
            {
                METHODNAME_DEF( DBParameter, injectParameterGateway )
				BLOG_TRACE_METHOD( m_Logger, fun );

                m_ParameterGateway = parameterGateway;
            }

			bool DBParameter::getParameterValue( const basar::I18nString& parameterName, basar::I18nString& value ) const
			{
				METHODNAME_DEF( DBParameter, getParameterValue )
				BLOG_TRACE_METHOD( m_Logger, fun );

                return m_ParameterGateway->getParameterValue( getParameterName(parameterName), value );
			}
            
            basar::I18nString DBParameter::getParameterName( const basar::I18nString& parameterName ) const
            {
                METHODNAME_DEF( DBParameter, getParameterValue )
				BLOG_TRACE_METHOD( m_Logger, fun );

                basar::I18nString parameterNameMapped("");

                if( libutil::infrastructure::db::dbConnection::DBSRV_PARAMETERNAME == parameterName )
                {
                    //  here is the place to assign the parameter name (e.g. in the user admin) the specific application is searching for.
                    //  This class does make sense only if the individual parameter name diverges from the deafult parameter name 'DBSRV_PARAMETERNAME'.
                    parameterNameMapped = basar::I18nString(libutil::infrastructure::db::dbConnection::DBSRV_PARAMETERNAME) + "_X";
                }

                if( libutil::infrastructure::db::dbConnection::DB_PARAMETERNAME == parameterName )
                {
                    //  here is the place to assign the parameter name (e.g. in the user admin) the specific application is searching for.
                    //  This class does make sense only if the individual parameter name diverges from the deafult parameter name 'DBSRV_PARAMETERNAME'.
                    parameterNameMapped = basar::I18nString( libutil::infrastructure::db::dbConnection::DB_PARAMETERNAME) + "_X";
                }

                return parameterNameMapped;
            }

			bool DBParameter::getParameterValue( const basar::I18nString& parameter1, const basar::I18nString& parameterName, basar::I18nString& value ) const
			{
				METHODNAME_DEF( DBParameter, getParameterValue )
				BLOG_TRACE_METHOD( m_Logger, fun );

                return m_ParameterGateway->getParameterValue( parameter1, getParameterName(parameterName), value );
			}

			bool DBParameter::getParameterValue( const basar::Int16 parameter1, const basar::I18nString& parameterName, basar::I18nString& value ) const
			{
				METHODNAME_DEF( DBParameter, getParameterValue )
				BLOG_TRACE_METHOD( m_Logger, fun );

                return m_ParameterGateway->getParameterValue( parameter1, getParameterName(parameterName), value );
			}

			bool DBParameter::getParameterValue( const basar::I18nString& parameter1,    const basar::I18nString& parameter2, 
												 const basar::I18nString& parameterName, basar::I18nString& value ) const
			{
				METHODNAME_DEF( DBParameter, getParameterValue )
				BLOG_TRACE_METHOD( m_Logger, fun );
                
                return m_ParameterGateway->getParameterValue( parameter1, parameter2, getParameterName(parameterName), value );
			}

		} // end namespace parameter
	} // end namespace infrastructure
} // end namespace csc_phadex
