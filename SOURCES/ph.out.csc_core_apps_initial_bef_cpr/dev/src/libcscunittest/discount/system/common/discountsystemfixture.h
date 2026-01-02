#ifndef GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_SYSTEM_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_SYSTEM_FIXTURE_H

#include <unittest/testfixturebase.h>
//#include <discount/basevalues/discountbasevalue/discountbasevaluecollectionptr.h>
//#include <discount/logger/discountlogger/nulldiscountlogger.h>
//#include "discountbasevaluemapperstub.h"
#include <persistence/connection.h>
#include <discount/basevalues/discountbasevalue/discountbasevaluerepository.h>

namespace libcscUnitTest
{
namespace discountSystemTest
{
class DiscountSystemFixture : public libutil::unittest::TestFixtureBase
{
public:
	DiscountSystemFixture();
	virtual	~DiscountSystemFixture();

protected:
	void init();
	void getDiscountBaseValues();
	void createCalculatorHierarchy();	// TODO: parameters???
	void calculate();
	void logResults();
	void checkResults();


	libcsc::persistence::Connection						m_Connection;
	libcsc::discount::DiscountBaseValueRepository		m_Repository;
	libcsc::discount::DiscountBaseValueCollectionPtr	m_DiscountBaseValueCollection;
	//libcsc::discount::NullDiscountLoggerPtr				m_NullLogger;

private:
	DiscountSystemFixture( const DiscountSystemFixture & );
	DiscountSystemFixture operator=( const DiscountSystemFixture & );	
};

} // end namespace discountSystemTest
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_COMMON_DISCOUNT_SYSTEM_FIXTURE_H
