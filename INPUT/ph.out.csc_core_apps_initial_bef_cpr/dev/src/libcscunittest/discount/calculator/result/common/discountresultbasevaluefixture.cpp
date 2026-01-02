#include "cmnut.h"
#include "discountresultbasevaluefixture.h"
#include <libbasarcmnutil_locale.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
DiscountResultBaseValueFixture::DiscountResultBaseValueFixture()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

DiscountResultBaseValueFixture::~DiscountResultBaseValueFixture()
{
}

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

