#include "cmnut.h"
#include "commoncalculatorcommandfixture.h"
#include <libbasarcmnutil_locale.h>
#include <discount/basevalues/discountbasevalue/discountbasevaluecollection.h>
#include <discount/basevalues/discountbasevalue/discountbasevalue.h>
#include <fstream>
#include <exceptions/invalidparameterexception.h>

namespace libcscUnitTest
{
namespace SuiteTestDiscountCalculatorCommands
{
using namespace libcsc::discount;

CommonCalculatorCommandFixture::CommonCalculatorCommandFixture()
: m_DiscountBaseValueCollection( new libcsc::discount::DiscountBaseValueCollection() ),
  m_NullLogger( new libcsc::discount::NullDiscountLogger() )
{
	basar::cmnutil::Locale::setLocale( basar::cmnutil::Locale::C );
}

CommonCalculatorCommandFixture::~CommonCalculatorCommandFixture()
{
}

void CommonCalculatorCommandFixture::addDiscountBaseValue( const libcsc::discount::DiscountBaseValuePtr baseValue )
{
	m_DiscountBaseValueCollection->add( baseValue );
}

void CommonCalculatorCommandFixture::addDiscountBaseValue( const basar::VarString & text )
{
	DiscountBaseValuePtr baseValue( new DiscountBaseValue() );
	DiscountBaseValueMapperStub mapper( baseValue );
	mapper.setValuesFromText( text );
	mapper.map();
	addDiscountBaseValue( baseValue );
}

void CommonCalculatorCommandFixture::addDiscountBaseValues( const std::vector<basar::VarString> & lines )
{
	std::vector<basar::VarString>::const_iterator iter = lines.begin();
	for( ; iter != lines.end(); ++iter );
	{
		addDiscountBaseValue( *iter );
	}
}

void CommonCalculatorCommandFixture::readDiscountBaseValuesFromFile( const basar::VarString & filename )
{
	std::string line;
	std::ifstream file( filename );
	if( file.is_open() )
	{
		while( getline( file, line ) )
		{
			addDiscountBaseValue( line.c_str() );
		}
		file.close();
	}
	else 
	{
		std::stringstream ss;
		ss << "Could not open file, filename=<" << filename.c_str() << ">";
		throw libcsc::exceptions::InvalidParameterException( basar::ExceptInfo( "CommonCalculatorCommandFixture::readDiscountBaseValuesFromFile()", ss.str().c_str(), __FILE__, __LINE__ ) );
	}
}

} // end namespace SuiteTestDiscountCalculatorCommands
} // end namespace libcscUnitTest

