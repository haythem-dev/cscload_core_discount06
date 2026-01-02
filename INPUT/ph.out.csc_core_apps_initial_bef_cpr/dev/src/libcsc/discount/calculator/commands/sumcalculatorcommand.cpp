#include "discount/calculator/commands/sumcalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "exceptions/emptycompositeexception.h"
#include "exceptions/invaliddataexception.h"
#include <sstream>
#include "discountcalculatorcommandbaseptr.h"

namespace libcsc
{
namespace discount
{
SumCalculatorCommand::SumCalculatorCommand( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType,
	const bool delegateResultProcessing
		)
: DiscountCalculatorCompositeCommandBase( parentCalcType, calcType, delegateResultProcessing )
{
}

SumCalculatorCommand::~SumCalculatorCommand()
{
}

const DiscountCalculatorResult & SumCalculatorCommand::doCalculate() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "SumCalculatorCommand::doCalculate" );

	CalculatorCollection::const_iterator iter = getCalculatorCollection().begin();
	IDiscountCalculatorCommandPtr cmd( *iter );
	DiscountCalculatorResult result = cmd->calculate();
	for( ++iter; iter != getCalculatorCollection().end(); ++iter )
	{
		cmd = ( *iter );
		DiscountCalculatorResult tempResult = cmd->calculate();
		addResult( result, tempResult );
	}

	if( result.containsDirty() )
	{
		setResult( result );
	}
	logCalculation( result );
	return getResult();
}

void SumCalculatorCommand::delegateResultProcessing() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "SumCalculatorCommand::delegateResultProcessing()" );

	CalculatorCollection::const_iterator iter = getCalculatorCollection().begin();
	for( ; iter != getCalculatorCollection().end(); ++iter )
	{
		IDiscountCalculatorCommandPtr cmd = ( *iter );
		cmd->processResult();
	}
}

void SumCalculatorCommand::delegateResultProcessing( const DiscountCalculatorResult & result ) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "SumCalculatorCommand::delegateResultProcessing(const DiscountCalculatorResult &)" );

	CalculatorCollection::const_iterator iter = getCalculatorCollection().begin();
	for( ; iter != getCalculatorCollection().end(); ++iter )
	{
		DiscountCalculatorCommandBasePtr cmd = boost::dynamic_pointer_cast<DiscountCalculatorCommandBase>( *iter );
		cmd->processResult( result );
	}
}

void SumCalculatorCommand::addResult( 
	DiscountCalculatorResult & result, 
	const DiscountCalculatorResult & rhs
		) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "SumCalculatorCommand::addResult()" );

	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << std::endl << "result: " << result << std::endl << "rhs: " << rhs;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	if( rhs.isUnset() )
	{
		return;
	}

	if( result.baseValue.isUnset() )
	{
		copyBaseValues( result.baseValue, rhs.baseValue );
	}

	DiscountResultCollection::const_iterator iterSrc = rhs.results.begin();
	for( ; iterSrc != rhs.results.end(); ++iterSrc )
	{
		const DiscountResult & discountResultSrc( iterSrc->second );
		DiscountResult & discountResultDest( result.getDiscountResult( iterSrc->first ) );

		if( discountResultSrc.discountedArticlePrice.isDirty() )
		{
			if( discountResultDest.discountedArticlePrice.isDirty() )
			{
				std::stringstream ss;
				ss << "Calculator type " << getType() << ": Can't summarize fixed prices!";
				throw exceptions::InvalidDataException( basar::ExceptInfo( "SumCalculatorCommand::addResult()", ss.str().c_str(), __FILE__, __LINE__ ) );
			}

			discountResultDest.discountedArticlePrice = discountResultSrc.discountedArticlePrice;
			discountResultDest.discountedArticlePriceOrigin = discountResultSrc.discountedArticlePriceOrigin;
		}

		if( discountResultSrc.discountValue.isDirty() )
		{
			if( discountResultDest.discountValue.isDirty() )
			{
				discountResultDest.discountValue = basar::Decimal( discountResultDest.discountValue ) + basar::Decimal( discountResultSrc.discountValue );
			}
			else
			{
				discountResultDest.discountValue = discountResultSrc.discountValue;
				discountResultDest.discountValueOrigin = discountResultSrc.discountValueOrigin;
			}
		}

		if( discountResultSrc.discountPercent.isDirty() )
		{
			if( discountResultDest.discountPercent.isDirty() )
			{
				discountResultDest.discountPercent = basar::Decimal( discountResultDest.discountPercent ) + basar::Decimal( discountResultSrc.discountPercent );
			}
			else
			{
				discountResultDest.discountPercent = discountResultSrc.discountPercent;
				discountResultDest.discountPercentOrigin = discountResultSrc.discountPercentOrigin;
			}
		}
	}

	RebateInKindValueCollection::const_iterator iter = rhs.rebateInKindArticles.begin();
	for( ; iter != rhs.rebateInKindArticles.end(); ++iter )
	{
		result.addRebateInKind( *iter );
	}
}

} // end namespace discount
} // end namespace libcsc
