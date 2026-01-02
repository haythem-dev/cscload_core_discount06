#include "cmnut.h"
#include "configfilereaderfixture.h"
#include <util/configfilereader.h>
#include <sstream>

namespace libcscUnitTest
{
using namespace libutil::unittest;

SUITE(TestConfigFileReader)
{
//									methodName_condition_expectation
FIXTURE_TEST_START(ConfigFileReaderFixture, readIni)
{
	libcsc::util::ConfigFileReader reader("cscservice.ini", libcsc::util::ConfigFileReader::CONFIG_FORMAT_INI);
	CHECK_EQUAL(true, reader.read());

	CHECK_EQUAL("$INI_PATH/message.txt",	reader.getString("Generic.MessageFile"));
#ifdef WIN32
	CHECK_EQUAL("C:\\marathon/message.txt",	reader.getEnvString("Generic.MessageFile"));
#else
	CHECK_EQUAL("/software/wss/de/ksc/server/ini/message.txt",	reader.getEnvString("Generic.MessageFile"));
#endif
	CHECK_EQUAL("ode21@zdev21_shm",			reader.getString("Session.DataSource"));
	CHECK_EQUAL("ZZZZ",						reader.getString("Session.DeviceName"));
	CHECK_EQUAL("ZZZZ",						reader.get<std::string>("Session.DeviceName")); // same as getString
	CHECK_EQUAL(int(2),						reader.getInt("Session.DeviceType"));
	CHECK_EQUAL(int(2),						reader.get<int>("Session.DeviceType"));				// same as getInt
	CHECK_EQUAL(unsigned long(2UL),			reader.get<unsigned long>("Session.DeviceType"));	// get as unsigned long
	CHECK_EQUAL(signed long(2L),			reader.get<signed long>("Session.DeviceType"));		// get as signed long
	CHECK_EQUAL(unsigned short(2U),			reader.get<unsigned short>("Session.DeviceType"));	// get as unsigned short
	CHECK_EQUAL(signed short(2),			reader.get<signed short>("Session.DeviceType"));	// get as signed short
	CHECK_EQUAL(std::string("2"),			reader.get<std::string>("Session.DeviceType"));		// get as string
	CHECK_EQUAL("DE",						reader.getString("Session.Country"));
	CHECK_EQUAL("",							reader.getString("Session.Computer"));	// empty value
	CHECK_EQUAL("",							reader.getString("Session.XYZ"));		// non-existent key
	CHECK_EQUAL("",							reader.getString("XYZ.Country"));		// non-existent section
	CHECK_EQUAL(56001,						reader.getInt("Thrift.Port"));
	CHECK_EQUAL(-1,							reader.getInt("Thrift.ForkLimit"));
	CHECK_EQUAL("",							reader.getString("Thrift.Encoding"));
}
FIXTURE_TEST_END

FIXTURE_TEST_START(ConfigFileReaderFixture, readXml)
{
	libcsc::util::ConfigFileReader reader("csc_corpha.xml", libcsc::util::ConfigFileReader::CONFIG_FORMAT_XML);
	CHECK_EQUAL(true, reader.read());

	CHECK_EQUAL(3000, reader.getInt("KSCRefreshSettings.Country.Settings.General.<xmlattr>.PollInterval"));
}
FIXTURE_TEST_END

} // end TESTSUITE
} // end namespace libutilUnitTest

