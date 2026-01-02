#ifndef GUARD_LIBCSC_HR_POSITION_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_HR_POSITION_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_H

#include <discount/componentmanager/hrdiscountcalculatorcomponentmanagerbase.h>

namespace libcsc
{
namespace discount
{
class HRPositionDiscountCalculatorComponentManager : public HRDiscountCalculatorComponentManagerBase
{
public:
	HRPositionDiscountCalculatorComponentManager();
	virtual ~HRPositionDiscountCalculatorComponentManager();

	virtual IDiscountCalculatorCommandPtr getDiscountCalculator();

private:
	HRPositionDiscountCalculatorComponentManager( const HRPositionDiscountCalculatorComponentManager & );
	HRPositionDiscountCalculatorComponentManager & operator=( const HRPositionDiscountCalculatorComponentManager & );

	// composite calculators
	IDiscountCalculatorCommandPtr createSumAll( const DiscountCalculatorTypeEnum parentCalcType ) const;
	//IDiscountCalculatorCommandPtr createFixedPriceBeatsAll( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createSumRetailWholesaleWholesaleIndustry( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createFirstWinsWholesale( const DiscountCalculatorTypeEnum parentCalcType ) const;
	IDiscountCalculatorCommandPtr createFirstWinsWholesaleIndustry( const DiscountCalculatorTypeEnum parentCalcType ) const;
};

} // end namespace discount
} // end namespace libcsc

#endif //end GUARD_LIBCSC_HR_POSITION_DISCOUNT_CALCULATOR_COMPONENT_MANAGER_H
