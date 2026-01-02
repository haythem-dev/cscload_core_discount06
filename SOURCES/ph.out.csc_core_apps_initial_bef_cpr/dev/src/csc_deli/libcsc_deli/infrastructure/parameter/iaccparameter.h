#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_IACCPARAMETER_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_IACCPARAMETER_H

#include <libbasar_definitions.h>
#include <vector>

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
	class IACCParameter
	{
	public:
        virtual ~IACCParameter() {}
        typedef std::vector< basar::I18nString > ParameterValueCollection;

		virtual basar::I18nString        getParameterValue ( const basar::I18nString& parameterName ) const = 0;
        virtual ParameterValueCollection getParameterValues( const basar::I18nString& parameterName ) const = 0;
	};

} // end namespace parameter
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_PARAMETER_IACCPARAMETER_H
