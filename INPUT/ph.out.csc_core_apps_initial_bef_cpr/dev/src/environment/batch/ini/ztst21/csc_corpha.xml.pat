<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings xsi:noNamespaceSchemaLocation="../../KSCRefreshSettings.xsd" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
	<Country Country="AT">
		<Settings>
			<General PollInterval="5000" LogLevel="Warnings" Test="false" MaxSelectOrders="40" BulkInsert="true"/>
			<SMTP Port="25" Host="10.156.80.21" SendMailFrom="kscrefreshtest@phoenixgroup.eu">
				<Information eMail=""/>
				<Warnings eMail=""/>
				<Errors eMail="kscrefreshtest@phoenixgroup.eu;"/>
			</SMTP>
			<TCAccess IPAddress="10.242.5.212" TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="CORPHA" Password=""/>
			<pxVerbund DeviceType="7" DeviceName="CORPHA" Computer="" LogMode="1" DataSource="oat21pre@ztst21_shm" MessageFile="/software/wss/pat/ksc/batch/ini/message.txt"/>
			<Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="ztst21_tcp" IfxDataBase="oat21pre"/>
		</Settings>
		<Branches>
			<Branch BranchNo="83">
				<Settings>
					<TCAccess IPAddress="10.242.5.212" Port="3283"/>
					<pxVerbund LogFile="/software/wss/pat/ksc/batch/log/83_csc_corpha.log" SystemLogFile="/software/wss/pat/ksc/batch/log/83_csc_corpha_wss.log"/>
				</Settings>
			</Branch>
		</Branches>
	</Country>
</KSCRefreshSettings>
