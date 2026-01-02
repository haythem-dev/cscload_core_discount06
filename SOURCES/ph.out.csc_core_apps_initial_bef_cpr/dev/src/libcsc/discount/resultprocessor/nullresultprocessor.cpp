#include <discount/resultprocessor/nullresultprocessor.h>

namespace libcsc
{
namespace discount
{
NullResultProcessor::NullResultProcessor()
{
}

NullResultProcessor::~NullResultProcessor()
{
}

void NullResultProcessor::process(
	const DiscountCalculatorTypeEnum, 
	const IOrderBaseValueGetterPtr, 
	const DiscountCalculatorResult &
		)
{
}

void NullResultProcessor::print() const
{
}

void NullResultProcessor::reset()
{
}

} // end namespace discount
} // end namespace libcsc
