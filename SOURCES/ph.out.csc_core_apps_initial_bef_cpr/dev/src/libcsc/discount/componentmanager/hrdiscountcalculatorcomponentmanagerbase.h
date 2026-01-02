#ifndef GUARD_LIBCSC_HR_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_BASE_H
#define GUARD_LIBCSC_HR_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_BASE_H

#include <discount/logger/discountlogger/idiscountloggerptr.h>
#include <discount/resultprocessor/iresultprocessorptr.h>
#include <discount/logger/hierarchylogger/ihierarchyloggerptr.h>
#include <discount/basevalues/discountbasevalue/idiscountbasevaluegetterptr.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>
#include <discount/calculator/discountcalculatortypeenum.h>
#include <discount/calculator/commands/idiscountcalculatorcommandptr.h>
#include <discount/calculator/commands/discountcalculatorcommandbaseptr.h>
#include <discount/calculator/commands/discountcalculatorcompositecommandbaseptr.h>

namespace libcsc
{
namespace discount
{
class HRDiscountCalculatorComponentManagerBase
{
public:
	HRDiscountCalculatorComponentManagerBase();
	virtual ~HRDiscountCalculatorComponentManagerBase();

	void inject( IDiscountBaseValueGetterPtr baseValueGetter );
	void inject( IOrderBaseValueGetterPtr baseValueGetter );
	void inject( IDiscountLoggerPtr logger );
	void inject( IResultProcessorPtr logger );
	void inject( IHierarchyLoggerPtr logger );

	virtual IDiscountCalculatorCommandPtr getDiscountCalculator() = 0;

protected:
	// conditional calculators
	DiscountCalculatorCompositeCommandBasePtr createBestOf4CustomerCombined(
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType,
		const bool delegateResultLogging
			) const;
	DiscountCalculatorCompositeCommandBasePtr createFirstWins(
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType,
		const bool delegateResultLogging
			) const;
	DiscountCalculatorCompositeCommandBasePtr createSum(
		const DiscountCalculatorTypeEnum parentCalcType,
		const DiscountCalculatorTypeEnum calcType,
		const bool delegateResultLogging
			) const;

	// specific calculators
	IDiscountCalculatorCommandPtr createFixedPrice( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createRetail( const DiscountCalculatorTypeEnum parentCalcType ) const;

	IDiscountCalculatorCommandPtr createWholesaleCustomerArticle( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleCustomerArticleGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleCustomerManufacturer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleCustomerManufacturerGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;

	IDiscountCalculatorCommandPtr createWholesaleCustomerGroupArticle( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleCustomerGroupArticleGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleCustomerGroupManufacturer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleCustomerGroupManufacturerGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;

	IDiscountCalculatorCommandPtr createWholesaleAllCustomerArticle( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleAllCustomerArticleGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleAllCustomerManufacturer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleAllCustomerManufacturerGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;

	IDiscountCalculatorCommandPtr createWholesaleIndustryCustomerArticle( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryCustomerArticleGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryCustomerManufacturer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryCustomerManufacturerGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;

	IDiscountCalculatorCommandPtr createWholesaleIndustryCustomerGroupArticle( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryCustomerGroupArticleGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryCustomerGroupManufacturer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryCustomerGroupManufacturerGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;

	IDiscountCalculatorCommandPtr createWholesaleIndustryAllCustomerArticle( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryAllCustomerArticleGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryAllCustomerManufacturer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createWholesaleIndustryAllCustomerManufacturerGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;

private:
	HRDiscountCalculatorComponentManagerBase( const HRDiscountCalculatorComponentManagerBase & );
	HRDiscountCalculatorComponentManagerBase & operator=( const HRDiscountCalculatorComponentManagerBase & );

	void injectComponents( DiscountCalculatorCommandBasePtr calc ) const;

	IDiscountBaseValueGetterPtr		m_DiscountBaseValueGetter;
	IOrderBaseValueGetterPtr		m_OrderBaseValueGetter;
	IDiscountLoggerPtr				m_DiscountLogger;
	IResultProcessorPtr				m_ResultLogger;
	IHierarchyLoggerPtr				m_HierarchyLogger;
};

} // end namespace discount
} // end namespace libcsc

#endif //end GUARD_LIBCSC_HR_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_BASE_H
