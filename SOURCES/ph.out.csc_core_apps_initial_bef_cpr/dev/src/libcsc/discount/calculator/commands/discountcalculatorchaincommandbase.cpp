#include "discount/calculator/commands/discountcalculatorchaincommandbase.h"	
#include "exceptions/emptycompositeexception.h"
#include <sstream>

namespace libcsc
{
namespace discount
{
DiscountCalculatorChainCommandBase::DiscountCalculatorChainCommandBase( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType,
	const bool delegateResultProcessing
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType ),
  m_DelegateResultProcessing( delegateResultProcessing )
{
}

DiscountCalculatorChainCommandBase::~DiscountCalculatorChainCommandBase()
{
}

void DiscountCalculatorChainCommandBase::injectPreviousCalculator( DiscountCalculatorCommandBasePtr calculator )
{
	m_PreviousCalculator = calculator;
}

const DiscountCalculatorCommandBasePtr DiscountCalculatorChainCommandBase::getPreviousCalculator() const
{
	if( NULL == m_PreviousCalculator.get() )
	{
		std::stringstream ss;
		ss << "Calculator type " << getType() << ": Previous calculator is NULL!";
		throw exceptions::EmptyCompositeException( basar::ExceptInfo( "DiscountCalculatorChainCommandBase::calculatePreviousResult()", ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	return m_PreviousCalculator;
}

const DiscountCalculatorResult & DiscountCalculatorChainCommandBase::calculatePreviousResult() const
{
	return getPreviousCalculator()->calculate();
}

void DiscountCalculatorChainCommandBase::processResult() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorChainCommandBase::processResult()" );

	if( m_DelegateResultProcessing )
	{
		getPreviousCalculator()->processResult();
	}

	DiscountCalculatorCommandBase::processResult();
}

void DiscountCalculatorChainCommandBase::processResult( const DiscountCalculatorResult & result ) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorChainCommandBase::processResult(const DiscountCalculatorResult &)" );

	if( m_DelegateResultProcessing )
	{
		getPreviousCalculator()->processResult( result );
	}

	DiscountCalculatorCommandBase::processResult( result );
}

void DiscountCalculatorChainCommandBase::logHierarchy() const
{
	DiscountCalculatorCommandBase::logHierarchy();
	getPreviousCalculator()->logHierarchy();
}

} // end namespace discount
} // end namespace libcsc
