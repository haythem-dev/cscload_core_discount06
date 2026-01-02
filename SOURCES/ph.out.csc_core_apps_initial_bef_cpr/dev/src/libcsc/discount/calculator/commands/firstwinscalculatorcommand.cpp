#include "discount/calculator/commands/firstwinscalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "exceptions/emptycompositeexception.h"
#include "discountcalculatorcommandbaseptr.h"

namespace libcsc
{
namespace discount
{
FirstWinsCalculatorCommand::FirstWinsCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType,
	const bool delegateResultProcessing
		)
: DiscountCalculatorCompositeCommandBase( parentCalcType, calcType, delegateResultProcessing )
{
}

FirstWinsCalculatorCommand::~FirstWinsCalculatorCommand()
{
}

const DiscountCalculatorResult & FirstWinsCalculatorCommand::doCalculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "FirstWinsCalculatorCommand::doCalculate()" );

	m_Winner = libcsc::discount::IDiscountCalculatorCommandPtr();

	DiscountCalculatorResult result;
	CalculatorCollection::const_iterator iter = getCalculatorCollection().begin();
	for( ; iter != getCalculatorCollection().end(); ++iter )
	{
		IDiscountCalculatorCommandPtr cmd = ( *iter );
		result = cmd->calculate();
		if( result.containsDirty() )
		{
			m_Winner = cmd;
			break;
		}
	}

	setResult( result );
	logCalculation( result );
	return getResult();
}

void FirstWinsCalculatorCommand::delegateResultProcessing() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "FirstWinsCalculatorCommand::delegateResultProcessing()" );

	if( NULL == m_Winner.get() )
	{
		return;
	}
	m_Winner->processResult();
}

void FirstWinsCalculatorCommand::delegateResultProcessing( const DiscountCalculatorResult & result ) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "FirstWinsCalculatorCommand::delegateResultProcessing(const DiscountCalculatorResult &)" );

	if( NULL == m_Winner.get() )
	{
		return;
	}

	DiscountCalculatorCommandBasePtr cmd = boost::dynamic_pointer_cast<DiscountCalculatorCommandBase>( m_Winner );
	cmd->processResult( result );
}

} // end namespace discount
} // end namespace libcsc
