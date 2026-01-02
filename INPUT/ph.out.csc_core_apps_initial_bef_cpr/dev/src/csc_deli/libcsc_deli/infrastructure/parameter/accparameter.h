#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_ACCPARAMETER_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_ACCPARAMETER_H

#include "iaccparameter.h"

#include <libbasar_definitions.h>
#include <libutil/parameter.h>

namespace log4cplus 
{
    class Logger;
}

namespace libcsc_deli
{
namespace infrastructure
{
namespace parameter
{
	class ACCParameter : public IACCParameter
	{
	public:
        ACCParameter();
        ~ACCParameter();

        void injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr );
        void setAreaId( basar::Int16 );

        // from IACCParameter interface
        basar::I18nString        getParameterValue ( const basar::I18nString& parameterName ) const;
        ParameterValueCollection getParameterValues( const basar::I18nString& parameterName ) const;

	private:
		ACCParameter( const ACCParameter& );
		ACCParameter& operator = ( const ACCParameter& );

        libutil::infrastructure::parameter::IParameterGatewayPtr    getParameterGateway() const;
        const basar::VarString&                                     getAreaId() const;

    private:
	    const log4cplus::Logger&                                    m_Logger;
        libutil::infrastructure::parameter::IParameterGatewayPtr    m_ParameterGateway;
        basar::VarString                                            m_AreaId;
	};

} // end namespace parameter
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_ACCPARAMETER_H
