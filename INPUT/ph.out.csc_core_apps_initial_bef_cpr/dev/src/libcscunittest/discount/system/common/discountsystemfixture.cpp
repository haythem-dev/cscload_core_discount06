#include "cmnut.h"
#include "discountsystemfixture.h"
#include <libbasarcmnutil_locale.h>
//#include <discount/basevalues/discountbasevalue/discountbasevaluecollection.h>
//#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
#include <persistence/accessor.h>
#include <persistence/iaccessorptr.h>
#include <discount/basevalues/orderbasevalue/iorderbasevaluegetterptr.h>
#include <discount/common/orderbasevaluestub.h>

namespace libcscUnitTest
{
namespace discountSystemTest
{
DiscountSystemFixture::DiscountSystemFixture()
//: m_DiscountBaseValueCollection( new libcsc::discount::DiscountBaseValueCollection() ),
//  m_NullLogger( new libcsc::discount::NullDiscountLogger() )
{
	
	


	//DiscountBaseValuePtr baseValue( new DiscountBaseValue() );


	/* TODO
	- calc hierarchie aufbauen
	- test: ergebnisse mit werten aus der db vergleichen, zwischendurch andere IDFs selektieren
	*/
}

DiscountSystemFixture::~DiscountSystemFixture()
{
	// remove accessor from repository in order zu reset statement member variable before closing connection
	m_Repository.injectSingleSelectAccessor( libcsc::persistence::IAccessorPtr() );
	m_Repository.injectMultiSelectAccessor( libcsc::persistence::IAccessorPtr() );

	//m_Connection.close();
}

void DiscountSystemFixture::init()
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
	//m_Connection.open( "zdev21_tcp", "ofr21" );
}

void DiscountSystemFixture::getDiscountBaseValues()
{
	using namespace libcsc::persistence;
	m_Repository.injectSingleSelectAccessor( IAccessorPtr( new Accessor( m_Connection.getDbSqlConnection() ) ) );
	m_Repository.injectMultiSelectAccessor( IAccessorPtr( new Accessor( m_Connection.getDbSqlConnection() ) ) );

	//using namespace libcsc::discount;
	//IOrderBaseValueGetterPtr orderBaseValue( new libcscUnitTest::discount::OrderBaseValueStub( 41, 475909, 0, "NO", 0, 4262429, 10, basar::Decimal( 0 ), basar::Decimal( 0 ), "4262429" ) );

	m_DiscountBaseValueCollection = m_Repository.get();
}

void DiscountSystemFixture::createCalculatorHierarchy()
{
	// TODO
}

void DiscountSystemFixture::calculate()
{
	// TODO
}

void DiscountSystemFixture::logResults()
{
	// TODO
}

void DiscountSystemFixture::checkResults()
{
	// TODO
	CHECK_EQUAL( "TODO: to be implemented", "not implemented yet" );
}


} // end namespace discountSystemTest
} // end namespace libcscUnitTest

