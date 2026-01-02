#include "cmnut.h"
#include "configfilereaderfixture.h"
#include <fstream>

namespace libcscUnitTest
{
namespace SuiteTestConfigFileReader
{
ConfigFileReaderFixture::ConfigFileReaderFixture()
{
	std::ofstream of;
	of.open("cscservice.ini");
	of <<
		"#########################################"						<< std::endl <<
		"# cscservice initialization parameters"						<< std::endl <<
		"#########################################"						<< std::endl <<
		""																<< std::endl <<
		"[Generic]"														<< std::endl <<
		"MessageFile        = $INI_PATH/message.txt"					<< std::endl <<
		""																<< std::endl <<
		"[Session]"														<< std::endl <<
		"Computer           = "											<< std::endl <<
		"DataSource         = ode21@zdev21_shm"							<< std::endl <<
		"DeviceName         = ZZZZ"										<< std::endl <<
		"DeviceType         = 2"										<< std::endl <<
		"Country            = DE"										<< std::endl <<
		""																<< std::endl <<
		"[Thrift]"														<< std::endl <<
		"#56001 ( cscservice DE Nord )"									<< std::endl <<
		"#56101 ( cscservice CH )"										<< std::endl <<
		"#56111 ( cscservice AT )"										<< std::endl <<
		"#56121 ( cscservice FR )"										<< std::endl <<
		"#56131 ( cscservice PFR )"										<< std::endl <<
		"#56141 ( cscservice PCH )"										<< std::endl <<
		"#56161 ( cscservice BG )"										<< std::endl <<
		"#56171 ( cscservice RS )"										<< std::endl <<
		"#56181 ( cscservice DE Süd )"									<< std::endl <<
		"#56191 ( cscservice PAT )"										<< std::endl <<
		"#56201 ( cscservice HR )"										<< std::endl <<
		"Port               = 56001"									<< std::endl <<
		"ForkLimit          = -1"										<< std::endl <<
		"Encoding           = "											<< std::endl;
	of.close();

#ifdef WIN32
	_putenv("INI_PATH=C:\\marathon");
#else
	putenv("INI_PATH=/software/wss/de/ksc/server/ini");
#endif

	of.open("csc_corpha.xml");
	of <<
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl <<
		"<KSCRefreshSettings xsi:noNamespaceSchemaLocation=\"../../KSCRefreshSettings.xsd\" xmlns:xsi=\"http:/www.w3.org/2001/XMLSchema-instance\">" << std::endl <<
		"	<Country Country=\"DE\">" << std::endl <<
		"		<Settings>" << std::endl <<
		"			<General PollInterval=\"3000\" LogLevel=\"Errors\" Test=\"false\" MaxSelectOrders=\"40\" BulkInsert=\"true\"/>" << std::endl <<
		"			<SMTP Port=\"25\" Host=\"10.100.121.30\" SendMailFrom=\"csc_corpha@phoenixgroup.eu\">" << std::endl <<
		"				<Information eMail=\"\"/>" << std::endl <<
		"				<Warnings eMail=\"\"/>" << std::endl <<
		"				<Errors eMail=\"kscrefreshtest@phoenixgroup.eu\"/>" << std::endl <<
		"			</SMTP>" << std::endl <<
		"			<TCAccess TCATransaction=\"TCAS\" TCAHost=\"PhoenixGeneric_west\" ConnectionRetries=\"10\" ConnectionWaitBeforeRetry=\"10000\" Username=\"CORPHA\" Password=\"\"/>" << std::endl <<
		"			<pxVerbund DeviceType=\"7\" DeviceName=\"CORPHA\" Computer=\"\" LogMode=\"1\" DataSource=\"ode21@zdev21_shm\" MessageFile=\"/software/wss/de/ksc/batch/ini/message.txt\"/>" << std::endl <<
		"			<Informix ConnectionRetries=\"10\" ConnectionWaitBeforeRetry=\"10000\" IfxServiceName=\"53004\" IfxHost=\"zdev21_tcp\" IfxDataBase=\"ode21\"/>" << std::endl <<
		"		</Settings>" << std::endl <<
		"		<Branches>" << std::endl <<
		"			<Branch BranchNo=\"09\">" << std::endl <<
		"				<Settings>" << std::endl <<
		"					<TCAccess IPAddress=\"10.242.5.210\" Port=\"3101\"/>" << std::endl <<
		"					<pxVerbund LogFile=\"/software/wss/de/ksc/batch/log/09_csc_corpha.log\" SystemLogFile=\"/software/wss/de/ksc/batch/log/09_csc_corpha_wws.log\"/>" << std::endl <<
		"				</Settings>" << std::endl <<
		"			</Branch>" << std::endl <<
		"			<Branch BranchNo=\"59\">" << std::endl <<
		"				<Settings>" << std::endl <<
		"					<TCAccess IPAddress=\"10.242.5.210\" Port=\"3105\"/>" << std::endl <<
		"					<pxVerbund LogFile=\"/software/wss/de/ksc/batch/log/59_csc_corpha.log\" SystemLogFile=\"/software/wss/de/ksc/batch/log/59_csc_corpha_wws.log\"/>" << std::endl <<
		"				</Settings>" << std::endl <<
		"			</Branch>" << std::endl <<
		"			<Branch BranchNo=\"40\">" << std::endl <<
		"				<Settings>" << std::endl <<
		"					<TCAccess IPAddress=\"10.242.5.210\" Port=\"3106\"/>" << std::endl <<
		"					<pxVerbund LogFile=\"/software/wss/de/ksc/batch/log/40_csc_corpha.log\" SystemLogFile=\"/software/wss/de/ksc/batch/log/40_csc_corpha_wws.log\"/>" << std::endl <<
		"				</Settings>" << std::endl <<
		"			</Branch>" << std::endl <<
		"		</Branches>" << std::endl <<
		"	</Country>" << std::endl <<
		"</KSCRefreshSettings>" << std::endl;
	of.close();

}

ConfigFileReaderFixture::~ConfigFileReaderFixture()
{
	remove("cscservice.ini");
}

} // end namespace SuiteTestConfigFileReader
} // end namespace libcscUnitTest

