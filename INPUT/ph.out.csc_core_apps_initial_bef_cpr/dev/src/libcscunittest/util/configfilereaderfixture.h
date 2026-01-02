#ifndef GUARD_LIBCSC_UNITTEST_CONFIGFILEREADER_FIXTURE_H
#define GUARD_LIBCSC_UNITTEST_CONFIGFILEREADER_FIXTURE_H

#include <unittest/testfixturebase.h>

namespace libcscUnitTest
{
namespace SuiteTestConfigFileReader
{
class ConfigFileReaderFixture : public libutil::unittest::TestFixtureBase
{
public:
	ConfigFileReaderFixture();
	virtual	~ConfigFileReaderFixture();

protected:

private:
	ConfigFileReaderFixture(const ConfigFileReaderFixture&);
	ConfigFileReaderFixture operator=(const ConfigFileReaderFixture&);
};

} // end namespace SuiteTestConfigFileReader
} // end namespace libcscUnitTest

#endif	// GUARD_LIBCSC_UNITTEST_CONFIGFILEREADER_FIXTURE_H
