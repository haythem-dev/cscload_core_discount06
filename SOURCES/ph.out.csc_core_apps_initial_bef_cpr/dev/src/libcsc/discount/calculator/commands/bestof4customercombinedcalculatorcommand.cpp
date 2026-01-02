#include "discount/calculator/commands/bestof4customercombinedcalculatorcommand.h"
#include "discount/basevalues/discountbasevalue/idiscountbasevaluegetter.h"
#include "discount/basevalues/discountbasevalue/discountbasevalue.h"
#include "exceptions/emptycompositeexception.h"
#include "discountcalculatorcommandbaseptr.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/orderitembasevaluecollection.h"

namespace libcsc
{
namespace discount
{
BestOf4CustomerCombinedCalculatorCommand::BestOf4CustomerCombinedCalculatorCommand(
    const DiscountCalculatorTypeEnum parentCalcType,
    const DiscountCalculatorTypeEnum calcType,
    const bool delegateResultProcessing
        )
: DiscountCalculatorCompositeCommandBase( parentCalcType, calcType, delegateResultProcessing )
{
}

BestOf4CustomerCombinedCalculatorCommand::~BestOf4CustomerCombinedCalculatorCommand()
{
}

const DiscountCalculatorResult & BestOf4CustomerCombinedCalculatorCommand::doCalculate() const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::doCalculate" );

    m_Winners.clear();
    m_RebateInKindWinner.command = IDiscountCalculatorCommandPtr();
    m_RebateInKindWinner.result = DiscountCalculatorResult();

    CalculatorCollection::const_iterator iter = getCalculatorCollection().begin();
    for( ; iter != getCalculatorCollection().end(); ++iter )
    {
        IDiscountCalculatorCommandPtr cmd = ( *iter );
        const DiscountCalculatorResult & tempResult = cmd->calculate();
        compareFixedPriceResults( cmd, tempResult );
        compareValueResults( cmd, tempResult );
        comparePercentResults( cmd, tempResult );
        compareRebateInKindResults( cmd, tempResult );
    }

    DiscountCalculatorResult result;
    combineResults( result );
    setResult( result );
    logCalculation( result );
    return getResult();
}

void BestOf4CustomerCombinedCalculatorCommand::compareFixedPriceResults(
    IDiscountCalculatorCommandPtr cmd,
    const DiscountCalculatorResult & rhs
        ) const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::compareFixedPriceResults()" );

    if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << std::endl << "rhs: " << rhs;
        LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    DiscountResultCollection::const_iterator iter = rhs.results.begin();
    for( ; iter != rhs.results.end(); ++iter )
    {
        const basar::Int32 positionNo( iter->first );
        const DiscountResult & discountResult( iter->second );

        WinnerStruct & winner = getWinner( positionNo, DT_FIXED_PRICE );
        DiscountResult & winnerDiscountResult( winner.result.getDiscountResult( positionNo ) );
        if( 0 > compareResults( getFixedPriceDiscountValue( winnerDiscountResult, winner.result.baseValue ), getFixedPriceDiscountValue( discountResult, rhs.baseValue ) ) )
        {
            copyBaseValues( winner.result.baseValue, rhs.baseValue );
            copyFixedPriceValues( winnerDiscountResult, discountResult );
            winner.command = cmd;
        }
    }
}

void BestOf4CustomerCombinedCalculatorCommand::compareValueResults(
    IDiscountCalculatorCommandPtr cmd,
    const DiscountCalculatorResult & rhs
        ) const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::compareValueResults()" );

    if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << std::endl << "rhs: " << rhs;
        LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    DiscountResultCollection::const_iterator iter = rhs.results.begin();
    for( ; iter != rhs.results.end(); ++iter )
    {
        const basar::Int32 positionNo( iter->first );
        const DiscountResult & discountResult( iter->second );

        WinnerStruct & winner = getWinner( positionNo, DT_VALUE );
        DiscountResult & winnerDiscountResult( winner.result.getDiscountResult( positionNo ) );
        if( 0 > compareResults( getValueDiscountValue( winnerDiscountResult, winner.result.baseValue ), getValueDiscountValue( discountResult, rhs.baseValue ) ) )
        {
            copyBaseValues( winner.result.baseValue, rhs.baseValue );
            copyValueDiscountValues( winnerDiscountResult, discountResult );
            winner.command = cmd;
        }
    }
}

void BestOf4CustomerCombinedCalculatorCommand::comparePercentResults(
    IDiscountCalculatorCommandPtr cmd,
    const DiscountCalculatorResult & rhs
        ) const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::comparePercentResults()" );

    if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << std::endl << "rhs: " << rhs;
        LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    DiscountResultCollection::const_iterator iter = rhs.results.begin();
    for( ; iter != rhs.results.end(); ++iter )
    {
        const basar::Int32 positionNo( iter->first );
        const DiscountResult & discountResult( iter->second );

        WinnerStruct & winner = getWinner( positionNo, DT_PERCENT );
        DiscountResult & winnerDiscountResult( winner.result.getDiscountResult( positionNo ) );
        if( 0 > compareResults( getPercentDiscountValue( winnerDiscountResult, winner.result.baseValue ), getPercentDiscountValue( discountResult, rhs.baseValue ) ) )
        {
            copyBaseValues( winner.result.baseValue, rhs.baseValue );
            copyPercentValues( winnerDiscountResult, discountResult );
            winner.command = cmd;
        }
    }
}

void BestOf4CustomerCombinedCalculatorCommand::compareRebateInKindResults(
    IDiscountCalculatorCommandPtr cmd,
    const DiscountCalculatorResult & rhs
        ) const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::compareRebateInKindResults()" );

    if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << std::endl << "rhs: " << rhs;
        LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    basar::Int32 res = compareResults( getRebateInKindDiscountValue( m_RebateInKindWinner.result ), getRebateInKindDiscountValue( rhs ) );
    if( 0 > res )
    {
        copyBaseValues( m_RebateInKindWinner.result.baseValue, rhs.baseValue );
        copyRebateInKindValues( m_RebateInKindWinner.result, rhs );
        m_RebateInKindWinner.command = cmd;
    }
    else if( 0 == res )
    {
        // value of goods is equal, count the number of articles: The more rubber ducks, the better it is ;)
        if( 0 > compareRebateInKindQuantity( m_RebateInKindWinner.result, rhs ) )
        {
            copyBaseValues( m_RebateInKindWinner.result.baseValue, rhs.baseValue );
            copyRebateInKindValues( m_RebateInKindWinner.result, rhs );
            m_RebateInKindWinner.command = cmd;
        }
    }
}

basar::Int32 BestOf4CustomerCombinedCalculatorCommand::compareResults(
    const basar::Decimal & lhs,
    const basar::Decimal & rhs
        ) const
{
    if( lhs < rhs )
    {
        return -1;
    }
    else if( lhs > rhs )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

basar::Int32 BestOf4CustomerCombinedCalculatorCommand::compareRebateInKindQuantity(
    const DiscountCalculatorResult & lhs,
    const DiscountCalculatorResult & rhs
        ) const
{
    basar::Int32 lhsCount = 0;
    basar::Int32 rhsCount = 0;

    RebateInKindValueCollection::const_iterator iter = lhs.rebateInKindArticles.begin();
    for( ; iter != lhs.rebateInKindArticles.end(); ++iter )
    {
        const RebateInKindValue & rebate( *iter );
        lhsCount += rebate.quantity;
    }

    iter = rhs.rebateInKindArticles.begin();
    for( ; iter != rhs.rebateInKindArticles.end(); ++iter )
    {
        const RebateInKindValue & rebate( *iter );
        rhsCount += rebate.quantity;
    }

    if( lhsCount < rhsCount )
    {
        return -1;
    }
    else if( lhsCount > rhsCount )
    {
        return 1;
    }

    return 0;
}

const basar::Decimal BestOf4CustomerCombinedCalculatorCommand::getFixedPriceDiscountValue(
    const DiscountResult & result,
    const DiscountResultBaseValue & baseValue
        ) const
{
    basar::Decimal value( 0 );

    if( result.discountedArticlePrice.isDirty() )
    {
        value += ( basar::Decimal( baseValue.baseArticlePrice ) - basar::Decimal( result.discountedArticlePrice ) ) * baseValue.quantity;
    }

    return value;
}

const basar::Decimal BestOf4CustomerCombinedCalculatorCommand::getValueDiscountValue(
    const DiscountResult & result,
    const DiscountResultBaseValue & baseValue
        ) const
{
    basar::Decimal value( 0 );

    if( result.discountValue.isDirty() )
    {
        basar::Int32 quantity = 0;
        if( baseValue.quantity.isDirty() )
        {
            quantity = baseValue.quantity;
        }
        else
        {
            quantity = getOrderBaseValueGetter()->getOrderItemBaseValueCollection()->getArticleQuantity();
        }

        value = basar::Decimal( result.discountValue ) * quantity;
    }

    return value;
}

const basar::Decimal BestOf4CustomerCombinedCalculatorCommand::getPercentDiscountValue(
    const DiscountResult & result,
    const DiscountResultBaseValue & baseValue
        ) const
{
    basar::Decimal value( 0 );

    if( result.discountPercent.isDirty() )
    {
        if( baseValue.isDirty() )
        {
            // single article
            value = basar::Decimal( result.discountPercent ) * basar::Decimal( baseValue.baseArticlePrice ) / basar::Decimal( 100 ) * baseValue.quantity;
        }
        else
        {
            // range
            value = basar::Decimal( result.discountPercent ) * basar::Decimal( getOrderBaseValueGetter()->getOrderItemBaseValueCollection()->getArticleValue() ) / basar::Decimal( 100 );
        }
    }

    return value;
}

const basar::Decimal BestOf4CustomerCombinedCalculatorCommand::getRebateInKindDiscountValue(
    const DiscountCalculatorResult & result
        ) const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::getRebateInKindDiscountValue()" );

    if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << "result: " << result;
        LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    basar::Decimal value( 0 );

    RebateInKindValueCollection::const_iterator iter = result.rebateInKindArticles.begin();
    for( ; iter != result.rebateInKindArticles.end(); ++iter )
    {
        const RebateInKindValue & rebate( *iter );
        value += basar::Decimal( rebate.articlePrice ) * rebate.quantity;
    }

    if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << "value: " << value;
        LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    return value;
}

void BestOf4CustomerCombinedCalculatorCommand::combineResults(
    DiscountCalculatorResult & result
        ) const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::combineResults()" );

    WinnerCollection::iterator iterWinner = m_Winners.begin();
    for( ; iterWinner != m_Winners.end(); ++iterWinner )
    {
        const basar::Int32 positionNo( iterWinner->first );
        TypeCollection & typeCollection( iterWinner->second );
        TypeCollection::iterator iterType = typeCollection.begin();
        for( ; iterType != typeCollection.end(); ++iterType )
        {
            const DiscountType type( iterType->first );
            WinnerStruct & winner( iterType->second );
            DiscountCalculatorResult & winnerResult = winner.result;

            if( result.baseValue.isUnset() )
            {
                copyBaseValues( result.baseValue, winnerResult.baseValue );
            }

            DiscountResult & positionDiscountResult = result.getDiscountResult( positionNo );
            const DiscountResult & winnerPositionDiscountResult = winnerResult.getDiscountResult( positionNo );
            switch( type )
            {
                case DT_FIXED_PRICE:    copyFixedPriceValues( positionDiscountResult, winnerPositionDiscountResult ); break;
                case DT_VALUE:          copyValueDiscountValues( positionDiscountResult, winnerPositionDiscountResult ); break;
                case DT_PERCENT:        copyPercentValues( positionDiscountResult, winnerPositionDiscountResult ); break;
                default: break;
            }
        }
    }

    combineRebateInKindValues( result, m_RebateInKindWinner.result );
}


void BestOf4CustomerCombinedCalculatorCommand::delegateResultProcessing() const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::delegateResultProcessing()" );

    CalculatorCollection::const_iterator iter = getCalculatorCollection().begin();
    for( ; iter != getCalculatorCollection().end(); ++iter )
    {
        DiscountCalculatorCommandBasePtr cmd = boost::dynamic_pointer_cast<DiscountCalculatorCommandBase>( *iter );
        cmd->processResult( getResult() );
    }
}

void BestOf4CustomerCombinedCalculatorCommand::delegateResultProcessing( const DiscountCalculatorResult & result ) const
{
    CALC_BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "BestOf4CustomerCombinedCalculatorCommand::delegateResultProcessing(const DiscountCalculatorResult &)" );

    CalculatorCollection::const_iterator iter = getCalculatorCollection().begin();
    for( ; iter != getCalculatorCollection().end(); ++iter )
    {
        DiscountCalculatorCommandBasePtr cmd = boost::dynamic_pointer_cast<DiscountCalculatorCommandBase>( *iter );
        cmd->processResult( result );
    }
}

BestOf4CustomerCombinedCalculatorCommand::WinnerStruct & BestOf4CustomerCombinedCalculatorCommand::getWinner(
    const basar::Int32 positionNo,
    const DiscountType type
        ) const
{
    WinnerCollection::iterator iterWinner = m_Winners.find( positionNo );
    if( iterWinner == m_Winners.end() )
    {
        m_Winners[ positionNo ] = TypeCollection();
        iterWinner = m_Winners.find( positionNo );
    }
    TypeCollection & typeCollection( iterWinner->second );

    TypeCollection::iterator iterType = typeCollection.find( type );
    if( iterType == typeCollection.end() )
    {
        typeCollection[ type ] = WinnerStruct();
        iterType = typeCollection.find( type );
    }

    WinnerStruct & winner( iterType->second );
    return winner;
}

} // end namespace discount
} // end namespace libcsc
