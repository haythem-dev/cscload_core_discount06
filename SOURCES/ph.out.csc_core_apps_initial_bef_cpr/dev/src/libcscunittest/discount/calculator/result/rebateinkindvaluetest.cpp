#include "cmnut.h"
#include "common/rebateinkindvaluefixture.h"

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace libcsc::discount;

SUITE( TestDiscountCalculatorResult )
{
//												methodName_condition_expectation
FIXTURE_TEST_START( RebateInKindValueFixture, RebateInKindValue_stdCtor_values )
{
	RebateInKindValue rikv;
	CHECK_EQUAL( CT_UNSET, rikv.origin );
	CHECK_EQUAL( 0, rikv.articleNo );
	CHECK_EQUAL( 0, rikv.quantity );
	CHECK_EQUAL( basar::Decimal( 0 ), rikv.articlePrice );
	CHECK_EQUAL( false, rikv.isManufacturerRebate );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, RebateInKindValue_valuesCtor_values )
{
	RebateInKindValue  rikv( CT_RETAIL_TYPE, 4711, 100000, basar::Decimal( 29.95 ), true );
	CHECK_EQUAL( CT_RETAIL_TYPE, rikv.origin );
	CHECK_EQUAL( 4711, rikv.articleNo );
	CHECK_EQUAL( 100000, rikv.quantity );
	CHECK_EQUAL( basar::Decimal( 29.95 ), rikv.articlePrice );
	CHECK_EQUAL( true, rikv.isManufacturerRebate );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, RebateInKindValue_copyCtor_values )
{
	RebateInKindValue rikv( m_RebateInKindValue );
	CHECK_EQUAL( CT_UNSET, rikv.origin );
	CHECK_EQUAL( 0, rikv.articleNo );
	CHECK_EQUAL( 0, rikv.quantity );
	CHECK_EQUAL( basar::Decimal( 0 ), rikv.articlePrice );
	CHECK_EQUAL( false, rikv.isManufacturerRebate );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, constOperatorRebateInKindValue_values_keepsValues )
{
	m_RebateInKindValue.origin = CT_RETAIL_TYPE;
	m_RebateInKindValue.articleNo = 4711;
	m_RebateInKindValue.quantity = 100000;
	m_RebateInKindValue.articlePrice = basar::Decimal( 29.95 );
	m_RebateInKindValue.isManufacturerRebate = true;
	RebateInKindValue rikv;
	rikv.operator=( m_RebateInKindValue );

	CHECK_EQUAL( CT_RETAIL_TYPE, rikv.origin );
	CHECK_EQUAL( 4711, rikv.articleNo );
	CHECK_EQUAL( 100000, rikv.quantity );
	CHECK_EQUAL( basar::Decimal( 29.95 ), rikv.articlePrice );
	CHECK_EQUAL( true, rikv.isManufacturerRebate );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, operatorEqual_valuesEqual_equal )
{
	RebateInKindValue rikv1;
	RebateInKindValue rikv2;
	CHECK_EQUAL( true, rikv1.operator==( rikv2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, operatorEqual_valuesNotEqual_notEqual )
{
	RebateInKindValue rikv1;
	RebateInKindValue rikv2;
	rikv1.quantity = 10;
	rikv2.articleNo = 4711;
	CHECK_EQUAL( false, rikv1.operator==( rikv2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, operatorLess_valuesEqual_notLess )
{
	RebateInKindValue rikv1;
	RebateInKindValue rikv2;
	CHECK_EQUAL( false, rikv1.operator<( rikv2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, operatorLess_lhsLessThanRhs_less )
{
	RebateInKindValue rikv1;
	RebateInKindValue rikv2;
	rikv2.articleNo = 4711;
	rikv2.quantity = 1;
	rikv2.articlePrice = basar::Decimal( 29.95 );
	CHECK_EQUAL( true, rikv1.operator<( rikv2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, operatorLess_rhsLessThanLhs_notLess )
{
	RebateInKindValue rikv1;
	RebateInKindValue rikv2;
	rikv1.articleNo = 4711;
	rikv1.quantity = 1;
	rikv1.articlePrice = basar::Decimal( 29.95 );
	CHECK_EQUAL( false, rikv1.operator<( rikv2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, toStream_values_stringValues )
{
	m_RebateInKindValue.origin = CT_RETAIL_TYPE;
	m_RebateInKindValue.articleNo = 4711;
	m_RebateInKindValue.quantity = 100000;
	m_RebateInKindValue.articlePrice = basar::Decimal( 29.95 );
	m_RebateInKindValue.isManufacturerRebate = true;
	std::stringstream ss;
	m_RebateInKindValue.toStream( ss );
	CHECK_EQUAL( "RebateInKindValue: source=<DiscountSource: number=<0 (DIRTY)>, type=<DST_POSITION>, pharmacyGroup=< (DIRTY)>>, origin=<CT_RETAIL_TYPE>, quantity=<100000 (DIRTY)>, articleNo=<4711 (DIRTY)>, articlePrice=<29.949999999999999 (DIRTY)>", ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( RebateInKindValueFixture, toStream_unset_stringUnset )
{
	m_RebateInKindValue.articleNo.setUnset();
	m_RebateInKindValue.quantity.setUnset();
	m_RebateInKindValue.articlePrice.setUnset();
	std::stringstream ss;
	m_RebateInKindValue.toStream( ss );
	CHECK_EQUAL( "RebateInKindValue: source=<DiscountSource: number=<0 (DIRTY)>, type=<DST_POSITION>, pharmacyGroup=< (DIRTY)>>, origin=<CT_UNSET>, quantity=<UNSET>, articleNo=<UNSET>, articlePrice=<UNSET>", ss.str().c_str() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

