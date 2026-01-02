#include "cmnut.h"
#include "discountresultfixture.h"
#include <libbasarcmnutil_locale.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
DiscountResultFixture::DiscountResultFixture()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

DiscountResultFixture::~DiscountResultFixture()
{
}

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

