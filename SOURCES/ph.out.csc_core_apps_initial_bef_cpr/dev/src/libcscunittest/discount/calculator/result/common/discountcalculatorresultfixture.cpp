#include "cmnut.h"
#include "discountcalculatorresultfixture.h"
#include <libbasarcmnutil_locale.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorResult
{
using namespace libcsc::discount;

DiscountCalculatorResultFixture::DiscountCalculatorResultFixture()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

DiscountCalculatorResultFixture::~DiscountCalculatorResultFixture()
{
}

const DiscountResultBaseValue DiscountCalculatorResultFixture::getDiscountResultBaseValue() const
{
	DiscountResultBaseValue drbv;
	drbv.articleNo = 4711;
	drbv.quantity = 29;
	drbv.baseArticlePrice = basar::Decimal( 56.43 );
	return drbv;
}

const DiscountResult DiscountCalculatorResultFixture::getDiscountResult() const
{
	DiscountResult dr;
	dr.discountPercent = basar::Decimal( 11.11 );
	dr.discountPercentOrigin = CT_RETAIL_TYPE;
	dr.discountValue = basar::Decimal( 12.12 );
	dr.discountValueOrigin = CT_WH_CUSTOMER_GROUP_ARTICLE_TYPE;
	dr.discountedArticlePrice = basar::Decimal( 13.13 );
	dr.discountedArticlePriceOrigin = CT_WH_ALL_CUSTOMER_ARTICLE_GROUP_TYPE;
	return dr;
}

const RebateInKindValue DiscountCalculatorResultFixture::getRebateInKindValue() const
{
	return RebateInKindValue( CT_RETAIL_TYPE, 4711, 1, basar::Decimal( 23.45 ), true );
}

const libcsc::discount::DiscountResultBaseValue DiscountCalculatorResultFixture::getCleanDiscountResultBaseValue() const
{
	DiscountResultBaseValue drbv( getDiscountResultBaseValue() );
	drbv.articleNo.setClean();
	drbv.quantity.setClean();
	drbv.baseArticlePrice.setClean();
	return drbv;
}

const libcsc::discount::DiscountResult DiscountCalculatorResultFixture::getCleanDiscountResult() const
{
	DiscountResult dr( getDiscountResult() );
	dr.discountPercent.setClean();
	dr.discountValue.setClean();
	dr.discountedArticlePrice.setClean();
	return dr;
}

const libcsc::discount::RebateInKindValue DiscountCalculatorResultFixture::getCleanRebateInKindValue() const
{
	RebateInKindValue rikv( getRebateInKindValue() );
	rikv.articleNo.setClean();
	rikv.quantity.setClean();
	rikv.articlePrice.setClean();

	rikv.source.number.setClean();
	rikv.source.type.setClean();
	rikv.source.pharmacyGroup.setClean();
	return rikv;
}

const libcsc::discount::DiscountResultBaseValue DiscountCalculatorResultFixture::getUnsetDiscountResultBaseValue() const
{
	DiscountResultBaseValue drbv;
	drbv.articleNo.setUnset();
	drbv.quantity.setUnset();
	drbv.baseArticlePrice.setUnset();
	return drbv;
}

const libcsc::discount::DiscountResult DiscountCalculatorResultFixture::getUnsetDiscountResult() const
{
	DiscountResult dr;
	dr.discountPercent.setUnset();
	dr.discountValue.setUnset();
	dr.discountedArticlePrice.setUnset();
	return dr;
}

const libcsc::discount::RebateInKindValue DiscountCalculatorResultFixture::getUnsetRebateInKindValue() const
{
	RebateInKindValue rikv;
	rikv.articleNo.setUnset();
	rikv.quantity.setUnset();
	rikv.articlePrice.setUnset();

	rikv.source.number.setUnset();
	rikv.source.type.setUnset();
	rikv.source.pharmacyGroup.setUnset();
	return rikv;
}

} // end namespace SuiteTestDiscountCalculatorResult
} // end namespace libcscUnitTest

