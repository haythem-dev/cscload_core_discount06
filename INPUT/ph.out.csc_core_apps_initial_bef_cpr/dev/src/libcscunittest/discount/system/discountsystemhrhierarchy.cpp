#include "cmnut.h"
#include "common/discountsystemfixture.h"
#include <discount/componentmanager/hrorderdiscountcalculatorcomponentmanager.h>
#include <discount/componentmanager/hrpositiondiscountcalculatorcomponentmanager.h>
#include <discount/logger/hierarchylogger/shellhierarchylogger.h>
#include <discount/calculator/commands/idiscountcalculatorcommand.h>

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace discountSystemTest;

// This is for documentation purposes only: 
// Output of hierarchy in a human readable form.

SUITE( TestDiscountSystemHRHierarchy )
{
//	  methodName_condition_expectation
TEST( SystemHR_positionDiscount_hierarchy )
{
	using namespace libcsc::discount;
	ShellHierarchyLoggerPtr logger( new ShellHierarchyLogger() );
	HRPositionDiscountCalculatorComponentManager cm;
	cm.inject( logger );

	IDiscountCalculatorCommandPtr calc = cm.getDiscountCalculator();
	calc->logHierarchy();

	std::cout << std::endl << "Position discount calculator hierarchy:" << std::endl << std::endl;
	logger->toStream( std::cout );

	// nothing to test here
	CHECK( true );
}

TEST( SystemHR_orderDiscount_hierarchy )
{
	using namespace libcsc::discount;
	ShellHierarchyLoggerPtr logger( new ShellHierarchyLogger() );
	HROrderDiscountCalculatorComponentManager cm;
	cm.inject( logger );

	IDiscountCalculatorCommandPtr calc = cm.getDiscountCalculator();
	calc->logHierarchy();

	std::cout << std::endl << "Order discount calculator hierarchy:" << std::endl << std::endl;
	logger->toStream( std::cout );

	// nothing to test here
	CHECK( true );
}

} // end TESTSUITE
} // end namespace libcscUnitTest

