<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings xsi:noNamespaceSchemaLocation="../../KSCRefreshSettings.xsd" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
	<Country Country="RS">
		<Settings>
			<General PollInterval="3000" LogLevel="Errors" Test="false" MaxSelectOrders="40" BulkInsert="true"/>
			<SMTP Port="25" Host="10.156.80.21" SendMailFrom="kscrefreshtest@phoenixgroup.eu">
				<Information eMail=""/>
				<Warnings eMail=""/>
				<Errors eMail="kscrefreshtest@phoenixgroup.eu"/>
			</SMTP>
			<TCAccess TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="CORPHA" Password=""/>
			<pxVerbund DeviceType="7" DeviceName="CORPHA" Computer="" LogMode="1" DataSource="ors21@ztst21_shm" MessageFile="/software/wss/rs/ksc/batch/ini/message.txt"/>
			<Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="ztst21_tcp" IfxDataBase="ors21"/>
		</Settings>
		<Branches>
			<Branch BranchNo="03">
				<Settings>
					<TCAccess IPAddress="10.242.5.211" Port="3203"/>
					<pxVerbund LogFile="/software/wss/rs/ksc/batch/log/03_csc_corpha.log" SystemLogFile="/software/wss/rs/ksc/batch/log/03_csc_corpha_wss.log"/>
				</Settings>
			</Branch>
			<Branch BranchNo="84">
				<Settings>
					<TCAccess IPAddress="10.242.5.211" Port="3284"/>
					<pxVerbund LogFile="/software/wss/rs/ksc/batch/log/84_csc_corpha.log" SystemLogFile="/software/wss/rs/ksc/batch/log/84_csc_corpha_wss.log"/>
				</Settings>
			</Branch>
			<Branch BranchNo="85">
				<Settings>
					<TCAccess IPAddress="10.242.5.211" Port="3285"/>
					<pxVerbund LogFile="/software/wss/rs/ksc/batch/log/85_csc_corpha.log" SystemLogFile="/software/wss/rs/ksc/batch/log/85_csc_corpha_wss.log"/>
				</Settings>
			</Branch>
		</Branches>
	</Country>
</KSCRefreshSettings>
