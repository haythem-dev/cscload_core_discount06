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

//#include <libutil/parameter.h>

//#include <libbasar_definitions.h>
//#include <libbasarcmnutil.h>
//#include <libbasarlogin_manager.h>

//-----------------------------------------------------------------------------------------------//
// class definition section
//-----------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace parameter
        {
            DBParameter::DBParameter()
            : m_Logger( libutil::LoggerPool::getLoggerLibUtilUserAdmin() )
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
                    //parameterNameMapped = basar::I18nString(libutil::infrastructure::db::dbConnection::DBSRV_PARAMETERNAME) + "_X";
                    parameterNameMapped = basar::I18nString(libutil::infrastructure::db::dbConnection::DBSRV_PARAMETERNAME);
                }

                if( libutil::infrastructure::db::dbConnection::DB_PARAMETERNAME == parameterName )
                {
                    //parameterNameMapped = basar::I18nString( libutil::infrastructure::db::dbConnection::DB_PARAMETERNAME) + "_X";
                    parameterNameMapped = basar::I18nString( libutil::infrastructure::db::dbConnection::DB_PARAMETERNAME);
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
} // end namespace longtermlackloader
