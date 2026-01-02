#ifndef GUARD_LIBCSC_NULL_RESULT_PROCESSOR_H
#define GUARD_LIBCSC_NULL_RESULT_PROCESSOR_H

#include "iresultprocessor.h"
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class NullResultProcessor : public IResultProcessor
{
public:
	NullResultProcessor();
	virtual ~NullResultProcessor();

	virtual void process( 
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter, 
		const DiscountCalculatorResult & calcResult 
			);
	void print() const;
	void reset();
};

typedef boost::shared_ptr<libcsc::discount::NullResultProcessor> NullResultProcessorPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_NULL_RESULT_PROCESSOR_H
