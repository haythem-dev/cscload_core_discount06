#ifndef GUARD_LIBCSC_UNITTEST_COMMON_CALCULATOR_COMMAND_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_COMMON_CALCULATOR_COMMAND_FIXTURE_H

#include <unittest/testfixturebase.h>
#include <discount/basevalues/discountbasevalue/discountbasevaluecollectionptr.h>
#include <discount/logger/discountlogger/nulldiscountlogger.h>
#include "discountbasevaluemapperstub.h"

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
class CommonCalculatorCommandFixture : public libutil::unittest::TestFixtureBase
{
public:
	CommonCalculatorCommandFixture();
	virtual	~CommonCalculatorCommandFixture();

protected:
	void addDiscountBaseValue( const libcsc::discount::DiscountBaseValuePtr baseValue );
	void addDiscountBaseValue( const basar::VarString & text );
	void addDiscountBaseValues( const std::vector<basar::VarString> & lines );
	void readDiscountBaseValuesFromFile( const basar::VarString & filename );

	libcsc::discount::DiscountBaseValueCollectionPtr	m_DiscountBaseValueCollection;
	libcsc::discount::NullDiscountLoggerPtr				m_NullLogger;

private:
	CommonCalculatorCommandFixture( const CommonCalculatorCommandFixture & );
	CommonCalculatorCommandFixture operator=( const CommonCalculatorCommandFixture & );	
};

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_COMMON_CALCULATOR_COMMAND_FIXTURE_H
