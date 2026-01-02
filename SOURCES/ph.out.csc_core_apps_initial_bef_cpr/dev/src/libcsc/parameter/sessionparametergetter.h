#ifndef GUARD_LIBCSC_SESSION_PARAMETER_GETTER_H
#define GUARD_LIBCSC_SESSION_PARAMETER_GETTER_H

#include <parameter/isessionparametergetter.h>

class pxSession;

namespace libcsc
{
namespace parameter
{
class SessionParameterGetter : public ISessionParameterGetter
{
public:
	SessionParameterGetter( pxSession * session );
	virtual ~SessionParameterGetter();

	virtual bool isCountryHR() const;
	virtual bool isCountryDE() const;
	virtual basar::Decimal getTaxSpannenFestBetrag() const;

private:
	pxSession *		m_Session;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_SESSION_PARAMETER_GETTER_H
