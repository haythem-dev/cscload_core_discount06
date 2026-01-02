#ifndef GUARD_LIBCSC_REPOSITORY_RESULT_PROCESSOR_BASE_H
#define GUARD_LIBCSC_REPOSITORY_RESULT_PROCESSOR_BASE_H

#include "iresultprocessor.h"
#include <discount/orderpositiondiscount/orderpositiondiscountmodeenum.h>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class RepositoryResultProcessorBase : public IResultProcessor
{
public:
	RepositoryResultProcessorBase();
	virtual ~RepositoryResultProcessorBase();

	virtual void process( 
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter, 
		const DiscountCalculatorResult & calcResult 
			) = 0;

protected:
	OrderPositionDiscountModeEnum getDiscountMode( 
		const DiscountCalculatorTypeEnum type, 
		const bool isRebateInKind 
			) const;
	bool isPositionDiscountCalculatorType(
		const DiscountCalculatorTypeEnum calcType 
			) const;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_REPOSITORY_RESULT_PROCESSOR_BASE_H
