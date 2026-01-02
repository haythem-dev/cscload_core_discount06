#ifndef GUARD_LIBCSC_UNITTEST_COMMON_RESULT_PROCESSOR_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_COMMON_RESULT_PROCESSOR_FIXTURE_H

#include <unittest/testfixturebase.h>
//#include <discount/basevalues/discountbasevalue/discountbasevaluecollectionptr.h>
//#include <discount/logger/discountlogger/nulldiscountlogger.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountResultProcessor
{
class ResultProcessorFixture : public libutil::unittest::TestFixtureBase
{
public:
	ResultProcessorFixture();
	virtual	~ResultProcessorFixture();

protected:
	//void addDiscountBaseValue( const libcsc::discount::DiscountBaseValuePtr baseValue );
	//void addDiscountBaseValue( const basar::VarString & text );
	//void addDiscountBaseValues( const std::vector<basar::VarString> & lines );
	//void readDiscountBaseValuesFromFile( const basar::VarString & filename );

	//libcsc::discount::DiscountBaseValueCollectionPtr	m_DiscountBaseValueCollection;
	//libcsc::discount::NullDiscountLoggerPtr				m_NullLogger;

private:
	ResultProcessorFixture( const ResultProcessorFixture & );
	ResultProcessorFixture operator=( const ResultProcessorFixture & );	
};

} // end namespace SuiteTestDiscountResultProcessor
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_COMMON_RESULT_PROCESSOR_FIXTURE_H
