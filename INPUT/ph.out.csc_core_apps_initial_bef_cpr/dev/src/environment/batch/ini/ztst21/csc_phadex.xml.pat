<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings>
	<Country Country="AT">
		<Settings>
			<General PollInterval="3000" LogLevel="Errors" Test="false" BulkInsert="true" MaxSelect="40"/>
			<SMTP Port="25" Host="10.156.80.21" SendMailFrom="kscrefreshtest@phoenixgroup.eu">
				<Information eMail="kscrefreshtest@phoenixgroup.eu"/>
				<Warnings eMail="kscrefreshtest@phoenixgroup.eu"/>
				<Errors eMail="kscrefreshtest@phoenixgroup.eu"/>
			</SMTP>
			<TCAccess TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="PHADEX" Password=""/>
			<pxVerbund DeviceType="7" DeviceName="PHADEX" Computer="" LogMode="1" DataSource="oat21pre@ztst21_shm" MessageFile="/software/wss/pat/ksc/batch/ini/message.txt"/>
			<Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="ztst21_tcp" IfxDataBase="oat21pre"/>
		</Settings>
		<Branches>
			<Branch BranchNo="83">
				<Settings>
					<TCAccess IPAddress="10.242.5.212" Port="3283"/>
					<pxVerbund LogFile="/software/wss/pat/ksc/batch/log/83_csc_phadex.log" SystemLogFile="/software/wss/pat/ksc/batch/log/83_csc_phadex_wss.log"/>
				</Settings>
			</Branch>
		</Branches>
	</Country>
</KSCRefreshSettings>
