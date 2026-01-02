#include "cmnut.h"
#include "rebateinkindvaluefixture.h"
#include <libbasarcmnutil_locale.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
RebateInKindValueFixture::RebateInKindValueFixture()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

RebateInKindValueFixture::~RebateInKindValueFixture()
{
}

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

