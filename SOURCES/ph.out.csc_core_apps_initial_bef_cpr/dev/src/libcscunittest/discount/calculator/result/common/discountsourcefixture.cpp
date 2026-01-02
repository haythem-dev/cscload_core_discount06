#include "cmnut.h"
#include "discountsourcefixture.h"
#include <libbasarcmnutil_locale.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
DiscountSourceFixture::DiscountSourceFixture()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

DiscountSourceFixture::~DiscountSourceFixture()
{
}

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

