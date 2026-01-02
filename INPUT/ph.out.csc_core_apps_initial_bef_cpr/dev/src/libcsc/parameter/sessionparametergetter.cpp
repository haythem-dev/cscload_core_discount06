#include "sessionparametergetter.h"

#ifdef WIN32
	#pragma warning (push)
	#pragma warning(disable: 4244 4430 4806 4996)
#endif

#ifdef __GNUC__
	//#pragma GCC diagnostic push
	//#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <pxsess.hpp>
#include <pxparameter.hpp>

#ifdef __GNUC__
	//#pragma GCC diagnostic pop
#endif

#ifdef WIN32
	#pragma warning (pop)
#endif

namespace libcsc
{
namespace parameter
{
SessionParameterGetter::SessionParameterGetter( pxSession * session )
: m_Session( session )
{
}

SessionParameterGetter::~SessionParameterGetter()
{
}

bool SessionParameterGetter::isCountryHR() const
{
	return m_Session->isCroatia();
}

bool SessionParameterGetter::isCountryDE() const
{
	return m_Session->isGermany();
}

basar::Decimal SessionParameterGetter::getTaxSpannenFestBetrag() const
{
	static bool isInitialized = false;
	static basar::Decimal s_TaxSpannenFestBetrag = basar::Decimal(0.7);

	if (false == isInitialized)
	{
		pxParameter parameter(m_Session, 0, cPAR_GROUP_ORDERENTRY, cPAR_PURPOSE_TAXSPANNE, cPAR_PARAM_FIXZUSCHLAG);
		if (parameter.Get() == 0)
		{
			s_TaxSpannenFestBetrag = basar::Decimal(parameter.Wert() / 100.0);
		}
		isInitialized = true;
	}
	return s_TaxSpannenFestBetrag;
}

} // end namespace parameter
} // end namespace libcsc
