#include "cmnut.h"
#include "resultprocessorfixture.h"
#include <libbasarcmnutil_locale.h>
//#include <discount/basevalues/discountbasevalue/discountbasevaluecollection.h>
//#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
//#include <fstream>
//#include <exceptions/invalidparameterexception.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountResultProcessor
{
//using namespace libcsc::discount;

ResultProcessorFixture::ResultProcessorFixture()
//: m_DiscountBaseValueCollection( new libcsc::discount::DiscountBaseValueCollection() ),
//  m_NullLogger( new libcsc::discount::NullDiscountLogger() )
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

ResultProcessorFixture::~ResultProcessorFixture()
{
}

//void ResultProcessorFixture::addDiscountBaseValue( const libcsc::discount::DiscountBaseValuePtr baseValue )
//{
//	m_DiscountBaseValueCollection->add( baseValue );
//}


} // end namespace SuiteTestDiscountResultProcessor
} // end namespace libcscUnitTest

