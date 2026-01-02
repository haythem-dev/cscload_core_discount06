#include "cmnut.h"
#include "common/discountcalculatorresultfixture.h"

namespace libcscUnitTest
{
using namespace libutil::unittest;
using namespace libcsc::discount;

SUITE( TestDiscountCalculatorResult )
{
//													  methodName_condition_expectation
FIXTURE_TEST_START( DiscountCalculatorResultFixture, DiscountCalculatorResult_stdCtor_isUnset )
{
	DiscountCalculatorResult dcr;
	CHECK( dcr.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, getDiscountResult_emptyCollection_isUnset )
{
	const DiscountResult & dr = m_DiscountCalculatorResult.getDiscountResult( 1 );
	CHECK( dr.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, getDiscountResult_validEntry_isValid )
{
	DiscountResult dr1;
	dr1.discountPercent = basar::Decimal( 11.11 );
	dr1.discountPercentOrigin = CT_RETAIL_TYPE;
	dr1.discountValue = basar::Decimal( 12.12 );
	dr1.discountValueOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE;
	dr1.discountedArticlePrice = basar::Decimal( 13.13 );
	dr1.discountedArticlePriceOrigin = CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE;
	m_DiscountCalculatorResult.results[ 1 ] = dr1;

	const DiscountResult & dr2 = m_DiscountCalculatorResult.getDiscountResult( 1 );
	CHECK_EQUAL( basar::Decimal( 11.11 ), dr2.discountPercent );
	CHECK_EQUAL( CT_RETAIL_TYPE, dr2.discountPercentOrigin );
	CHECK_EQUAL( basar::Decimal( 12.12 ), dr2.discountValue );
	CHECK_EQUAL( CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE, dr2.discountValueOrigin );
	CHECK_EQUAL( basar::Decimal( 13.13 ), dr2.discountedArticlePrice );
	CHECK_EQUAL( CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE, dr2.discountedArticlePriceOrigin );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, addRebateInKind_emptyCollection_isValid )
{
	RebateInKindValue rikv1( CT_RETAIL_TYPE, 4711, 1, basar::Decimal( 23.45 ), true );
	m_DiscountCalculatorResult.addRebateInKind( rikv1 );

	RebateInKindValueCollection::const_iterator iter = m_DiscountCalculatorResult.rebateInKindArticles.begin();
	CHECK_EQUAL( false, iter == m_DiscountCalculatorResult.rebateInKindArticles.end() );

	const RebateInKindValue & rikv2( *iter );
	CHECK_EQUAL( CT_RETAIL_TYPE, rikv2.origin );
	CHECK_EQUAL( 4711, rikv2.articleNo );
	CHECK_EQUAL( 1, rikv2.quantity );
	CHECK_EQUAL( basar::Decimal( 23.45 ), rikv2.articlePrice );
	CHECK_EQUAL( true, rikv2.isManufacturerRebate );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, addRebateInKind_validEntrySameArticle_isAccumulated )
{
	RebateInKindValue rikv1( CT_RETAIL_TYPE, 4711, 1, basar::Decimal( 23.45 ), true );
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( rikv1 );

	RebateInKindValue rikv2( CT_RETAIL_TYPE, 4711, 1, basar::Decimal( 23.45 ), true );
	m_DiscountCalculatorResult.addRebateInKind( rikv2 );

	RebateInKindValueCollection::const_iterator iter = m_DiscountCalculatorResult.rebateInKindArticles.begin();
	CHECK_EQUAL( false, iter == m_DiscountCalculatorResult.rebateInKindArticles.end() );

	const RebateInKindValue & rikv3( *iter );
	CHECK_EQUAL( CT_RETAIL_TYPE, rikv3.origin );
	CHECK_EQUAL( 4711, rikv3.articleNo );
	CHECK_EQUAL( 2, rikv3.quantity );
	CHECK_EQUAL( basar::Decimal( 23.45 ), rikv3.articlePrice );
	CHECK_EQUAL( true, rikv3.isManufacturerRebate );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, addRebateInKind_validEntryDifferentArticle_isAdditionalEntry )
{
	RebateInKindValue rikv1( CT_RETAIL_TYPE, 4711, 1, basar::Decimal( 23.45 ), true );
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( rikv1 );

	RebateInKindValue rikv2( CT_RETAIL_TYPE, 4712, 1, basar::Decimal( 34.56 ), false );
	m_DiscountCalculatorResult.addRebateInKind( rikv2 );

	RebateInKindValueCollection::const_iterator iter = m_DiscountCalculatorResult.rebateInKindArticles.begin();
	CHECK_EQUAL( false, iter == m_DiscountCalculatorResult.rebateInKindArticles.end() );

	const RebateInKindValue & rikv3( *iter );
	CHECK_EQUAL( CT_RETAIL_TYPE, rikv3.origin );
	CHECK_EQUAL( 4711, rikv3.articleNo );
	CHECK_EQUAL( 1, rikv3.quantity );
	CHECK_EQUAL( basar::Decimal( 23.45 ), rikv3.articlePrice );
	CHECK_EQUAL( true, rikv3.isManufacturerRebate );

	++iter;
	CHECK_EQUAL( false, iter == m_DiscountCalculatorResult.rebateInKindArticles.end() );

	const RebateInKindValue & rikv4( *iter );
	CHECK_EQUAL( CT_RETAIL_TYPE, rikv4.origin );
	CHECK_EQUAL( 4712, rikv4.articleNo );
	CHECK_EQUAL( 1, rikv4.quantity );
	CHECK_EQUAL( basar::Decimal( 34.56 ), rikv4.articlePrice );
	CHECK_EQUAL( false, rikv4.isManufacturerRebate );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, operatorEqual_unsetUnset_equal )
{
	DiscountCalculatorResult dcr1;
	DiscountCalculatorResult dcr2;
	CHECK_EQUAL( true, dcr1.operator==( dcr2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, operatorEqual_equalValues_equal )
{
	DiscountCalculatorResult dcr1;
	dcr1.baseValue = getDiscountResultBaseValue();
	dcr1.results[ 1 ] = getDiscountResult();
	dcr1.rebateInKindArticles.push_back( getRebateInKindValue() );

	DiscountCalculatorResult dcr2;
	dcr2.baseValue = getDiscountResultBaseValue();
	dcr2.results[ 1 ] = getDiscountResult();
	dcr2.rebateInKindArticles.push_back( getRebateInKindValue() );
	
	CHECK_EQUAL( true, dcr1.operator==( dcr2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, operatorEqual_differentValues_notEqual )
{
	DiscountResultBaseValue drbv1;
	drbv1.articleNo = 4711;
	drbv1.quantity = 29;
	drbv1.baseArticlePrice = basar::Decimal( 56.43 );

	DiscountResultBaseValue drbv2;
	drbv2.articleNo = 4712;
	drbv2.quantity = 13;
	drbv2.baseArticlePrice = basar::Decimal( 34.56 );

	DiscountResult dr1;
	dr1.discountPercent = basar::Decimal( 11.11 );
	dr1.discountPercentOrigin = CT_RETAIL_TYPE;
	dr1.discountValue = basar::Decimal( 12.12 );
	dr1.discountValueOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE;
	dr1.discountedArticlePrice = basar::Decimal( 13.13 );
	dr1.discountedArticlePriceOrigin = CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE;

	DiscountResult dr2;
	dr2.discountPercent = basar::Decimal( 21.21 );
	dr2.discountPercentOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE;
	dr2.discountValue = basar::Decimal( 22.22 );
	dr2.discountValueOrigin = CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE;
	dr2.discountedArticlePrice = basar::Decimal( 23.23 );
	dr2.discountedArticlePriceOrigin = CT_RETAIL_TYPE;

	RebateInKindValue rikv1( CT_RETAIL_TYPE, 4711, 1, basar::Decimal( 23.45 ), true );
	RebateInKindValue rikv2( CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE, 4713, 2, basar::Decimal( 2.35 ), false );

	DiscountCalculatorResult dcr1;
	dcr1.baseValue = drbv1;
	dcr1.results[ 1 ] = dr1;
	dcr1.rebateInKindArticles.push_back( rikv1 );

	DiscountCalculatorResult dcr2;
	dcr2.baseValue = drbv2;
	dcr2.results[ 1 ] = dr2;
	dcr2.rebateInKindArticles.push_back( rikv2 );
	
	CHECK_EQUAL( false, dcr1.operator==( dcr2 ) );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, toStream_values_stringValues )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );
	std::stringstream ss;
	m_DiscountCalculatorResult.toStream( ss );
	const char * expected = "DiscountCalculatorResult:\n"
		"baseValue=<DiscountResultBaseValue: articleNo=<4711 (DIRTY)>, quantity=<29 (DIRTY)>, baseArticlePrice=<56.43 (DIRTY)>>\n"
		"results=\n"
		"1: DiscountResult: source=<DiscountSource: number=<0 (DIRTY)>, type=<DST_POSITION>, pharmacyGroup=< (DIRTY)>>, discountPercent=<11.109999999999999 (DIRTY)>, discountPercentOrigin=<CT_RETAIL_TYPE>, discountValue=<12.119999999999999 (DIRTY)>, discountValueOrigin=<CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE>, discountedArticlePrice=<13.130000000000001 (DIRTY)>, discountedArticlePriceOrigin=<CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE>\n"
		"rebate in kind=\n"
		"RebateInKindValue: source=<DiscountSource: number=<0 (DIRTY)>, type=<DST_POSITION>, pharmacyGroup=< (DIRTY)>>, origin=<CT_RETAIL_TYPE>, quantity=<1 (DIRTY)>, articleNo=<4711 (DIRTY)>, articlePrice=<23.449999999999999 (DIRTY)>\n";

	CHECK_EQUAL( expected, ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, toStream_unset_stringUnset )
{
	std::stringstream ss;
	m_DiscountCalculatorResult.toStream( ss );
	const char * expected = "DiscountCalculatorResult:\n"
		"baseValue=<UNSET>\n"
		"results=\n"
		"<UNSET>\n"
		"rebate in kind=\n"
		"<UNSET>\n";

	CHECK_EQUAL( expected, ss.str().c_str() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsUnset_baseValueUnset_true )
{
	m_DiscountCalculatorResult.baseValue = getUnsetDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsUnset_discountResultsUnset_true )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getUnsetDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsUnset_rebateInKindArticlesUnset_true )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getUnsetRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsUnset_allSet_false )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.containsUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsClean_baseValueClean_true )
{
	m_DiscountCalculatorResult.baseValue = getCleanDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsClean_discountResultsClean_true )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getCleanDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsClean_rebateInKindArticlesClean_true )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getCleanRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsClean_allUnset_false )
{
	m_DiscountCalculatorResult.baseValue = getUnsetDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getUnsetDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getUnsetRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.containsClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsDirty_baseValueDirty_true )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getCleanDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getCleanRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsDirty_discountResultsDirty_true )
{
	m_DiscountCalculatorResult.baseValue = getCleanDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getCleanRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsDirty_rebateInKindArticlesDirty_true )
{
	m_DiscountCalculatorResult.baseValue = getCleanDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getCleanDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.containsDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, containsDirty_allClean_false )
{
	m_DiscountCalculatorResult.baseValue = getCleanDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getCleanDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getCleanRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.containsDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isUnset_baseValueNotUnset_false )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getUnsetDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getUnsetRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isUnset_discountResultsNotUnset_false )
{
	m_DiscountCalculatorResult.baseValue = getUnsetDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getUnsetRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isUnset_rebateInKindArticlesNotUnset_false )
{
	m_DiscountCalculatorResult.baseValue = getUnsetDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getUnsetDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isUnset_allUnset_true )
{
	m_DiscountCalculatorResult.baseValue = getUnsetDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getUnsetDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getUnsetRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.isUnset() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isClean_baseValueNotClean_false )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getCleanDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getCleanRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isClean_discountResultsNotClean_false )
{
	m_DiscountCalculatorResult.baseValue = getCleanDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getCleanRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isClean_rebateInKindArticlesNotClean_false )
{
	m_DiscountCalculatorResult.baseValue = getCleanDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getCleanDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isClean_allClean_true )
{
	m_DiscountCalculatorResult.baseValue = getCleanDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getCleanDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getCleanRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.isClean() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isDirty_baseValueNotDirty_false )
{
	m_DiscountCalculatorResult.baseValue = getCleanDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isDirty_discountResultsNotDirty_false )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getCleanDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isDirty_rebateInKindArticlesNotDirty_false )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getCleanRebateInKindValue() );

	CHECK_EQUAL( false, m_DiscountCalculatorResult.isDirty() );
}
FIXTURE_TEST_END

FIXTURE_TEST_START( DiscountCalculatorResultFixture, isDirty_allDirty_true )
{
	m_DiscountCalculatorResult.baseValue = getDiscountResultBaseValue();
	m_DiscountCalculatorResult.results[ 1 ] = getDiscountResult();
	m_DiscountCalculatorResult.rebateInKindArticles.push_back( getRebateInKindValue() );

	CHECK_EQUAL( true, m_DiscountCalculatorResult.isDirty() );
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libcscUnitTest

