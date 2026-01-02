#ifndef GUARD_LIBCSC_I_SESSION_PARAMETER_GETTER_H
#define GUARD_LIBCSC_I_SESSION_PARAMETER_GETTER_H

#include <libbasarcmnutil_decimal.h>

namespace libcsc
{
namespace parameter
{
class ISessionParameterGetter
{
public:
	virtual ~ISessionParameterGetter() {}

	virtual bool isCountryHR() const = 0;
	virtual bool isCountryDE() const = 0;
	virtual basar::Decimal getTaxSpannenFestBetrag() const = 0;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_SESSION_PARAMETER_GETTER_H
