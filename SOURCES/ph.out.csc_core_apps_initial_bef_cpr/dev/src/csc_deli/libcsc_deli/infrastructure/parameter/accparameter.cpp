#include "accparameter.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include <misc/metaclassmacro_definitions.h>
#include <libbasarcmnutil_logging.h>

#include <libbasarcmnutil_i18nstring.h>
#include <misc/instancechecker_macro_definition.h>

#include <libbasarcmnutil_exceptions.h>
#include <libbasarlogin_exceptions.h> 

namespace libcsc_deli
{
namespace infrastructure
{
namespace parameter
{
    ACCParameter::ACCParameter()
        : m_Logger( LoggerPool::getLoggerCsc_deli() ), m_AreaId( -1 )
    {
        METHODNAME_DEF( ACCParameter, ACCParameter )
		BLOG_TRACE_METHOD( m_Logger, fun );
    }

    ACCParameter::~ACCParameter()
    {
        METHODNAME_DEF( ACCParameter, ~ACCParameter )
		BLOG_TRACE_METHOD( m_Logger, fun );
    }

    void ACCParameter::injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr paramGateway )
    {
        m_ParameterGateway = paramGateway;
    }

    libutil::infrastructure::parameter::IParameterGatewayPtr ACCParameter::getParameterGateway() const
    {
        CHECK_INSTANCE_EXCEPTION( m_ParameterGateway.get() );
        return m_ParameterGateway;
    }

    void ACCParameter::setAreaId( basar::Int16 areaId )
    {
        std::ostringstream oss;
        oss << areaId;
        m_AreaId = oss.str();
    }

    const basar::VarString& ACCParameter::getAreaId() const
    {
        METHODNAME_DEF( ACCParameter, getAreaId );

        if( m_AreaId.empty() )
        {
            basar::VarString msg = "AreaID is unset!";
            throw basar::login::InvalidAreaException( basar::cmnutil::ExceptionInfoStruct( fun, msg, __FILE__, __LINE__ ) );
        }

        return m_AreaId;
    }

    basar::I18nString ACCParameter::getParameterValue( const basar::I18nString& parameterName ) const
    {
        METHODNAME_DEF( ACCParameter, getParameterValue )
		BLOG_TRACE_METHOD( m_Logger, fun );

        basar::I18nString value;

        // first look for area specific parameter
        if( ! getParameterGateway()->getParameterValue( getAreaId(), parameterName, value ) )
        {
            // no area specific parameter found - look for general one
            if( ! getParameterGateway()->getParameterValue( parameterName, value ) )
            {
                std::ostringstream oss;
		        oss << "There is no general and no branch-global parameter '" << parameterName << "' in user administration.";
                throw basar::login::NoTextFoundException( basar::cmnutil::ExceptionInfoStruct( fun, oss.str().c_str(), __FILE__, __LINE__ ) );
            }
        }
    
        return value;
    }

    ACCParameter::ParameterValueCollection ACCParameter::getParameterValues( const basar::I18nString& parameterName ) const
    {
        METHODNAME_DEF( ACCParameter, getParameterValues )
		BLOG_TRACE_METHOD( m_Logger, fun );

        ParameterValueCollection values;

        // first get list of branches to get values for from userAdm
        // _BRANCHES is appended to the passed parameter to get the list of branches
        basar::I18nString value;
        if( getParameterGateway()->getParameterValue( getAreaId(), parameterName + "_BRANCHES", value ) )
        {
            // use each branch as additional argument to search in userAdm
            basar::cmnutil::CollBString branchColl = value.tokenizeAndTrim( ",", basar::I18nString::ALL, true, true );
            for( basar::cmnutil::CollBString::const_iterator it = branchColl.begin(); it != branchColl.end(); ++it )
            {
                if( getParameterGateway()->getParameterValue( getAreaId(), *it, parameterName, value ) )
                {
                    values.push_back( value );
                }
                else
                {
                    std::ostringstream oss;
		            oss << "There is no parameter " << "'" << parameterName << "' for branch '" << *it << "' in user administration.";
                    throw basar::login::NoTextFoundException( basar::cmnutil::ExceptionInfoStruct( fun, oss.str().c_str(), __FILE__, __LINE__ ) );
                }
            }
        }
        else
        {
            std::ostringstream oss;
		    oss << "There is no branch-global parameter '" << parameterName + "_BRANCHES" << "' for AreaID '" << m_AreaId 
                << "' in user administration which is needed to get all suitable branches when calling getParameterValues().";
            throw basar::login::NoTextFoundException( basar::cmnutil::ExceptionInfoStruct( fun, oss.str().c_str(), __FILE__, __LINE__ ) );
        }

        return values;
    }

} // end namespace parameter
} // end namespace infrastructure
} // end namespace libcsc_deli
