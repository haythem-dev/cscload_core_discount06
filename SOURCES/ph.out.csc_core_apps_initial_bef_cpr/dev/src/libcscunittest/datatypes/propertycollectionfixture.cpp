#include "cmnut.h"
#include "propertycollectionfixture.h"

namespace libcscUnitTest
{
namespace SuiteTestPropertyCollection
{
PropertyCollectionFixture::PropertyCollectionFixture()
{
	m_Collection.add( m_Decimal );
	m_Collection.add( m_Int32 );
	m_Collection.add( m_VarString );
	m_Collection.add( m_DateTime );
}

PropertyCollectionFixture::~PropertyCollectionFixture()
{
}

} // end namespace SuiteTestPropertyCollection
} // end namespace libcscUnitTest

