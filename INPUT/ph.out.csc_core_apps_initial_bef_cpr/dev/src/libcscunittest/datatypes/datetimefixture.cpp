#include "cmnut.h"
#include "datetimefixture.h"
#include <libbasarcmnutil_locale.h>

namespace libcscUnitTest
{
namespace SuiteTestDateTime
{
DateTimeFixture::DateTimeFixture()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

DateTimeFixture::~DateTimeFixture()
{
}

} // end namespace SuiteTestDateTime
} // end namespace libcscUnitTest

