#include "discount/logger/hierarchylogger/nullhierarchylogger.h"

namespace libcsc
{
namespace discount
{
NullHierarchyLogger::NullHierarchyLogger()
{
}

NullHierarchyLogger::~NullHierarchyLogger()
{
}

void NullHierarchyLogger::log(
	const DiscountCalculatorTypeEnum, 
	const DiscountCalculatorTypeEnum, 
	const DiscountCalculatorResult & 
		)
{
}

} // end namespace discount
} // end namespace libcsc
