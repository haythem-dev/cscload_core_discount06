#ifndef GUARD_LIBCSC_COMPOSITE_RESULT_PROCESSOR_H
#define GUARD_LIBCSC_COMPOSITE_RESULT_PROCESSOR_H

#include <discount/resultprocessor/repositoryresultprocessorbase.h>
#include <discount/resultprocessor/iresultprocessorptr.h>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace libcsc
{
namespace discount
{
class CompositeResultProcessor : public RepositoryResultProcessorBase
{
public:
	CompositeResultProcessor();
	virtual ~CompositeResultProcessor();

	void add( IResultProcessorPtr processor );

	virtual void process( 
		const DiscountCalculatorTypeEnum calcType, 
		const IOrderBaseValueGetterPtr baseValueGetter, 
		const DiscountCalculatorResult & calcResult 
			);

private:
	typedef std::vector<libcsc::discount::IResultProcessorPtr> ResultProcessorCollection;

	ResultProcessorCollection	m_ResultProcessors;
};

typedef boost::shared_ptr<libcsc::discount::CompositeResultProcessor> CompositeResultProcessorPtr;

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_COMPOSITE_RESULT_PROCESSOR_H
