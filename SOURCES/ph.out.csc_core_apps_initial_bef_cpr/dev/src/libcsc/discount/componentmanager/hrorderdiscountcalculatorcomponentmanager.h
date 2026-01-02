#ifndef GUARD_LIBCSC_HR_ORDER_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_HR_ORDER_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_H

#include <discount/componentmanager/hrdiscountcalculatorcomponentmanagerbase.h>

namespace libcsc
{
namespace discount
{
class HROrderDiscountCalculatorComponentManager : public HRDiscountCalculatorComponentManagerBase
{
public:
	HROrderDiscountCalculatorComponentManager();
	virtual ~HROrderDiscountCalculatorComponentManager();

	virtual IDiscountCalculatorCommandPtr getDiscountCalculator();

private:
	HROrderDiscountCalculatorComponentManager( const HROrderDiscountCalculatorComponentManager & );
	HROrderDiscountCalculatorComponentManager & operator=( const HROrderDiscountCalculatorComponentManager & );

	// composite calculators
	IDiscountCalculatorCommandPtr createSumAll( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createSumRetailWholesaleWholesaleIndustry( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createFirstWinsWholesale( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createFirstWinsWholesaleIndustry( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createBestOfWholesaleCustomer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createBestOfWholesaleCustomerGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createBestOfWholesaleAllCustomer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createBestOfWholesaleIndustryCustomer( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createBestOfWholesaleIndustryCustomerGroup( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createBestOfWholesaleIndustryAllCustomer( const DiscountCalculatorTypeEnum parentCalcType ) const;
};

} // end namespace discount
} // end namespace libcsc

#endif //end GUARD_LIBCSC_HR_ORDER_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_H
