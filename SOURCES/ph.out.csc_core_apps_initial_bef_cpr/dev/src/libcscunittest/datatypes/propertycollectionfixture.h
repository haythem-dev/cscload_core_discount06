#ifndef GUARD_LIBCSC_UNITTEST_PROPERTY_COLLECTION_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_PROPERTY_COLLECTION_FIXTURE_H

#include <unittest/testfixturebase.h>
#include <datatypes/propertycollection.h>
#include <datatypes/decimal.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <datatypes/datetime.h>

namespace libcscUnitTest
{
namespace SuiteTestPropertyCollection
{
class PropertyCollectionFixture : public libutil::unittest::TestFixtureBase
{
public:
	PropertyCollectionFixture();
	virtual	~PropertyCollectionFixture();

protected:
	libcsc::Decimal				m_Decimal;
	libcsc::Int32				m_Int32;
	libcsc::VarString			m_VarString;
	libcsc::DateTime			m_DateTime;
	libcsc::PropertyCollection	m_Collection;

private:
	PropertyCollectionFixture( const PropertyCollectionFixture & );
	PropertyCollectionFixture operator=( const PropertyCollectionFixture & );
};

} // end namespace SuiteTestPropertyCollection
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_PROPERTY_COLLECTION_FIXTURE_H
