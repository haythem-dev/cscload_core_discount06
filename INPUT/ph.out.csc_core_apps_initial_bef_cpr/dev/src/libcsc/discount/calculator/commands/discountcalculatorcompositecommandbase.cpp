#include "discount/calculator/commands/discountcalculatorcompositecommandbase.h"	
#include "exceptions/emptycompositeexception.h"
#include <sstream>

namespace libcsc
{
namespace discount
{
DiscountCalculatorCompositeCommandBase::DiscountCalculatorCompositeCommandBase( 
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType,
	const bool delegateResultProcessing
		)
: DiscountCalculatorCommandBase( parentCalcType, calcType ),
  m_DelegateResultProcessing( delegateResultProcessing )
{
}

DiscountCalculatorCompositeCommandBase::~DiscountCalculatorCompositeCommandBase()
{
}

void DiscountCalculatorCompositeCommandBase::add( IDiscountCalculatorCommandPtr calculator )
{
	m_CalculatorCollection.push_back( calculator );
}

const DiscountCalculatorResult & DiscountCalculatorCompositeCommandBase::calculate() const
{
	if( getCalculatorCollection().empty() )
	{
		std::stringstream ss;
		ss << "Calculator type " << getType() << ": Calculator collection is empty!";
		throw exceptions::EmptyCompositeException( basar::ExceptInfo( "BestOf4CustomerCalculatorCommand::calculate()", ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	return doCalculate();
}

const CalculatorCollection & DiscountCalculatorCompositeCommandBase::getCalculatorCollection() const
{
	return m_CalculatorCollection;
}

void DiscountCalculatorCompositeCommandBase::processResult() const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCompositeCommandBase::processResult()" );

	if( m_DelegateResultProcessing )
	{
		delegateResultProcessing();
		return;
	}

	DiscountCalculatorCommandBase::processResult();
}

void DiscountCalculatorCompositeCommandBase::processResult( const DiscountCalculatorResult & result ) const
{
	CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCalculatorCompositeCommandBase::processResult(const DiscountCalculatorResult &)" );

	if( m_DelegateResultProcessing )
	{
		delegateResultProcessing( result );
		return;
	}

	DiscountCalculatorCommandBase::processResult( result );
}

void DiscountCalculatorCompositeCommandBase::logHierarchy() const
{
	DiscountCalculatorCommandBase::logHierarchy();
	CalculatorCollection::const_iterator iter = m_CalculatorCollection.begin();
	for( ; iter != m_CalculatorCollection.end(); ++iter )
	{
		IDiscountCalculatorCommandPtr cmd = ( *iter );
		cmd->logHierarchy();
	}
}

void DiscountCalculatorCompositeCommandBase::copyFixedPriceValues( 
	DiscountResult & destination, 
	const DiscountResult & source 
		) const
{
	destination.source = source.source;
	if( source.discountedArticlePrice.isDirty() )
	{
		destination.discountedArticlePrice = source.discountedArticlePrice;
		destination.discountedArticlePriceOrigin = source.discountedArticlePriceOrigin;
	}
}

void DiscountCalculatorCompositeCommandBase::copyValueDiscountValues( 
	DiscountResult & destination, 
	const DiscountResult & source 
		) const
{
	destination.source = source.source;
	if( source.discountValue.isDirty() )
	{
		destination.discountValue = source.discountValue;
		destination.discountValueOrigin = source.discountValueOrigin;
	}
}

void DiscountCalculatorCompositeCommandBase::copyPercentValues( 
	DiscountResult & destination, 
	const DiscountResult & source 
		) const
{
	destination.source = source.source;
	if( source.discountPercent.isDirty() )
	{
		destination.discountPercent = source.discountPercent;
		destination.discountPercentOrigin = source.discountPercentOrigin;
	}
}

void DiscountCalculatorCompositeCommandBase::copyRebateInKindValues( 
	DiscountCalculatorResult & destination, 
	const DiscountCalculatorResult & source 
		) const
{
	destination.rebateInKindArticles = source.rebateInKindArticles;
}

void DiscountCalculatorCompositeCommandBase::combineRebateInKindValues( 
	DiscountCalculatorResult & destination, 
	const DiscountCalculatorResult & source 
		) const
{
	RebateInKindValueCollection::const_iterator iter = source.rebateInKindArticles.begin();
	for( ; iter != source.rebateInKindArticles.end(); ++iter )
	{
		const RebateInKindValue & rebate( *iter );
		destination.addRebateInKind( rebate );
	}
}

} // end namespace discount
} // end namespace libcsc
