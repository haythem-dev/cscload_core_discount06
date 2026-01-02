<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings xsi:noNamespaceSchemaLocation="../../KSCRefreshSettings.xsd" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
	<Country Country="CH">
		<Settings>
			<General PollInterval="3000" LogLevel="Errors" Test="false" MaxSelectOrders="40" BulkInsert="true"/>
			<SMTP Port="25" Host="10.156.80.21" SendMailFrom="kscrefreshtest@phoenixgroup.eu">
				<Information eMail=""/>
				<Warnings eMail=""/>
				<Errors eMail="kscrefreshtest@phoenixgroup.eu"/>
			</SMTP>
			<TCAccess TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="CORPHA" Password=""/>
			<pxVerbund DeviceType="7" DeviceName="CORPHA" Computer="" LogMode="1" DataSource="och21@zqas21_shm" MessageFile="/software/wss/ch/ksc/batch/ini/message.txt"/>
			<Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="zqas21_tcp" IfxDataBase="och21"/>
		</Settings>
		<Branches>
			<Branch BranchNo="12">
				<Settings>
					<TCAccess IPAddress="10.242.5.216" Port="3312"/>
					<pxVerbund LogFile="/software/wss/ch/ksc/batch/log/12_csc_corpha.log" SystemLogFile="/software/wss/ch/ksc/batch/log/12_csc_corpha_wws.log"/>
				</Settings>
			</Branch>
			<Branch BranchNo="13">
				<Settings>
					<TCAccess IPAddress="10.242.5.216" Port="3313"/>
					<pxVerbund LogFile="/software/wss/ch/ksc/batch/log/13_csc_corpha.log" SystemLogFile="/software/wss/ch/ksc/batch/log/13_csc_corpha_wws.log"/>
				</Settings>
			</Branch>
		</Branches>
	</Country>
</KSCRefreshSettings>
