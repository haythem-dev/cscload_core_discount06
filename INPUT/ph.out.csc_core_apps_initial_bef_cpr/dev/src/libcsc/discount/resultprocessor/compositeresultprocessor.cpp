#include "compositeresultprocessor.h"

namespace libcsc
{
namespace discount
{
CompositeResultProcessor::CompositeResultProcessor()
{
}

CompositeResultProcessor::~CompositeResultProcessor()
{
}

void CompositeResultProcessor::add( IResultProcessorPtr processor )
{
	m_ResultProcessors.push_back( processor );
}

void CompositeResultProcessor::process( 
	const DiscountCalculatorTypeEnum calcType, 
	const IOrderBaseValueGetterPtr baseValueGetter, 
	const DiscountCalculatorResult & calcResult 
		)
{
	ResultProcessorCollection::iterator iter = m_ResultProcessors.begin();
	for( ; iter != m_ResultProcessors.end(); ++iter )
	{
		( *iter )->process( calcType, baseValueGetter, calcResult );
	}
}

} // end namespace discount
} // end namespace libcsc
