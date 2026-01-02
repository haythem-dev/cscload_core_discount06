#include "cmnut.h"
#include "decimalfixture.h"
#include <libbasarcmnutil_locale.h>

namespace libcscUnitTest
{
namespace SuiteTestDecimal
{
DecimalFixture::DecimalFixture()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

DecimalFixture::~DecimalFixture()
{
}

} // end namespace SuiteTestDecimal
} // end namespace libcscUnitTest

