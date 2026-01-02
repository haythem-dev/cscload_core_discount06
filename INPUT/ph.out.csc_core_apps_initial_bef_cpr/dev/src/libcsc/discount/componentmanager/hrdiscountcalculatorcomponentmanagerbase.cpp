#include "hrdiscountcalculatorcomponentmanagerbase.h"

#include <discount/calculator/commands/bestof4customercombinedcalculatorcommand.h>
#include <discount/calculator/commands/firstwinscalculatorcommand.h>
#include <discount/calculator/commands/sumcalculatorcommand.h>

#include <discount/calculator/commands/idiscountcalculatorcommand.h>

#include <discount/calculator/commands/fixedpricecalculatorcommand.h>
#include <discount/calculator/commands/retailcalculatorcommand.h>
#include <discount/calculator/commands/wholesaleallcustomerarticlecalculatorcommand.h>
#include <discount/calculator/commands/wholesaleallcustomerarticlegroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesaleallcustomermanufacturercalculatorcommand.h>
#include <discount/calculator/commands/wholesaleallcustomermanufacturergroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesalecustomerarticlecalculatorcommand.h>
#include <discount/calculator/commands/wholesalecustomerarticlegroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesalecustomergrouparticlecalculatorcommand.h>
#include <discount/calculator/commands/wholesalecustomergrouparticlegroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesalecustomergroupmanufacturercalculatorcommand.h>
#include <discount/calculator/commands/wholesalecustomergroupmanufacturergroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesalecustomermanufacturercalculatorcommand.h>
#include <discount/calculator/commands/wholesalecustomermanufacturergroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustryallcustomerarticlecalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustryallcustomerarticlegroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustryallcustomermanufacturercalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustryallcustomermanufacturergroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustrycustomerarticlecalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustrycustomerarticlegroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustrycustomergrouparticlecalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustrycustomergrouparticlegroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustrycustomergroupmanufacturercalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustrycustomergroupmanufacturergroupcalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustrycustomermanufacturercalculatorcommand.h>
#include <discount/calculator/commands/wholesaleindustrycustomermanufacturergroupcalculatorcommand.h>


namespace libcsc
{
namespace discount
{
HRDiscountCalculatorComponentManagerBase::HRDiscountCalculatorComponentManagerBase()
{
}

HRDiscountCalculatorComponentManagerBase::~HRDiscountCalculatorComponentManagerBase()
{
}

void HRDiscountCalculatorComponentManagerBase::inject( IDiscountBaseValueGetterPtr baseValueGetter )
{
	m_DiscountBaseValueGetter = baseValueGetter;
}

void HRDiscountCalculatorComponentManagerBase::inject( IOrderBaseValueGetterPtr baseValueGetter )
{
	m_OrderBaseValueGetter = baseValueGetter;
}

void HRDiscountCalculatorComponentManagerBase::inject( IDiscountLoggerPtr logger )
{
	m_DiscountLogger = logger;
}

void HRDiscountCalculatorComponentManagerBase::inject( IResultProcessorPtr logger )
{
	m_ResultLogger = logger;
}

void HRDiscountCalculatorComponentManagerBase::inject( IHierarchyLoggerPtr logger )
{
	m_HierarchyLogger = logger;
}

// conditional calculators
DiscountCalculatorCompositeCommandBasePtr HRDiscountCalculatorComponentManagerBase::createBestOf4CustomerCombined(
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType,
	const bool delegateResultLogging
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( new BestOf4CustomerCombinedCalculatorCommand( parentCalcType, calcType, delegateResultLogging ) );
	injectComponents( calc );
	return calc;
}

DiscountCalculatorCompositeCommandBasePtr HRDiscountCalculatorComponentManagerBase::createFirstWins(
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType,
	const bool delegateResultLogging
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( new FirstWinsCalculatorCommand( parentCalcType, calcType, delegateResultLogging ) );
	injectComponents( calc );
	return calc;
}

DiscountCalculatorCompositeCommandBasePtr HRDiscountCalculatorComponentManagerBase::createSum(
	const DiscountCalculatorTypeEnum parentCalcType,
	const DiscountCalculatorTypeEnum calcType,
	const bool delegateResultLogging
		) const
{
	DiscountCalculatorCompositeCommandBasePtr calc( new SumCalculatorCommand( parentCalcType, calcType, delegateResultLogging ) );
	injectComponents( calc );
	return calc;
}

// specific calculators
IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createFixedPrice(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new FixedPriceCalculatorCommand( parentCalcType, CT_FIXED_PRICE_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createRetail(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new RetailCalculatorCommand( parentCalcType, CT_RETAIL_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleCustomerArticle(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleCustomerArticleCalculatorCommand( parentCalcType, CT_WH_CUSTOMER_ARTICLE_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleCustomerArticleGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleCustomerArticleGroupCalculatorCommand( parentCalcType, CT_WH_CUSTOMER_ARTICLE_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleCustomerManufacturer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleCustomerManufacturerCalculatorCommand( parentCalcType, CT_WH_CUSTOMER_MANUFACTURER_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleCustomerManufacturerGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleCustomerManufacturerGroupCalculatorCommand( parentCalcType, CT_WH_CUSTOMER_MANUFACTURER_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleCustomerGroupArticle(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleCustomerGroupArticleCalculatorCommand( parentCalcType, CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleCustomerGroupArticleGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleCustomerGroupArticleGroupCalculatorCommand( parentCalcType, CT_WH_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleCustomerGroupManufacturer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleCustomerGroupManufacturerCalculatorCommand( parentCalcType, CT_WH_CUSTOMER_GROUP_MANUFACTURER_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleCustomerGroupManufacturerGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleCustomerGroupManufacturerGroupCalculatorCommand( parentCalcType, CT_WH_CUSTOMER_GROUP_MANUFACTURER_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleAllCustomerArticle(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleAllCustomerArticleCalculatorCommand( parentCalcType, CT_WH_ALL_CUSTOMER_ARTICLE_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleAllCustomerArticleGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleAllCustomerArticleGroupCalculatorCommand( parentCalcType, CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleAllCustomerManufacturer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleAllCustomerManufacturerCalculatorCommand( parentCalcType, CT_WH_ALL_CUSTOMER_MANUFACTURER_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleAllCustomerManufacturerGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleAllCustomerManufacturerGroupCalculatorCommand( parentCalcType, CT_WH_ALL_CUSTOMER_MANUFACTURER_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryCustomerArticle(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryCustomerArticleCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_CUSTOMER_ARTICLE_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryCustomerArticleGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryCustomerArticleGroupCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_CUSTOMER_ARTICLE_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryCustomerManufacturer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryCustomerManufacturerCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_CUSTOMER_MANUFACTURER_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryCustomerManufacturerGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryCustomerManufacturerGroupCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_CUSTOMER_MANUFACTURER_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryCustomerGroupArticle(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryCustomerGroupArticleCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_CUSTOMER_GROUP_ARTICLE_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryCustomerGroupArticleGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryCustomerGroupArticleGroupCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_CUSTOMER_GROUP_ARTICLE_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryCustomerGroupManufacturer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryCustomerGroupManufacturerCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_CUSTOMER_GROUP_MANUFACTURER_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryCustomerGroupManufacturerGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryCustomerGroupManufacturerGroupCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_CUSTOMER_GROUP_MANUFACTURER_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryAllCustomerArticle(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryAllCustomerArticleCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_ALL_CUSTOMER_ARTICLE_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryAllCustomerArticleGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryAllCustomerArticleGroupCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_ALL_CUSTOMER_ARTICLE_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryAllCustomerManufacturer(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryAllCustomerManufacturerCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_TYPE ) );
	injectComponents( calc );
	return calc;
}

IDiscountCalculatorCommandPtr HRDiscountCalculatorComponentManagerBase::createWholesaleIndustryAllCustomerManufacturerGroup(
	const DiscountCalculatorTypeEnum parentCalcType
		) const
{
	DiscountCalculatorCommandBasePtr calc( new WholesaleIndustryAllCustomerManufacturerGroupCalculatorCommand( parentCalcType, CT_WH_INDUSTRY_ALL_CUSTOMER_MANUFACTURER_GROUP_TYPE ) );
	injectComponents( calc );
	return calc;
}

void HRDiscountCalculatorComponentManagerBase::injectComponents( DiscountCalculatorCommandBasePtr calc ) const
{
	calc->inject( m_DiscountBaseValueGetter );
	calc->inject( m_OrderBaseValueGetter );
	calc->inject( m_DiscountLogger );
	calc->inject( m_ResultLogger );
	calc->inject( m_HierarchyLogger );
}

 }// end namespace discount
} // end namespace libcsc
