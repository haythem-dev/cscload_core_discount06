#include "cmnut.h"
#include "datefixture.h"
#include <libbasarcmnutil_locale.h>

namespace libcscUnitTest
{
namespace SuiteTestDate
{
DateFixture::DateFixture()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

DateFixture::~DateFixture()
{
}

} // end namespace SuiteTestDate
} // end namespace libcscUnitTest

