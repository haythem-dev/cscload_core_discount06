<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings>
	<Country Country="CH">
		<Settings>
			<General PollInterval="3000" LogLevel="Errors" Test="false" BulkInsert="true" MaxSelect="40"/>
			<SMTP Port="25" Host="10.100.121.30" SendMailFrom="zbw@phoenixgroup.eu">
				<Information eMail="kscrefresh@phoenixgroup.eu"/>
				<Warnings eMail="kscrefresh@phoenixgroup.eu; a.egerer@phoenixgroup.eu"/>
				<Errors eMail="int.dl-FU2ServiceDeskInfos@phoenixgroup.eu; kscrefresh@phoenixgroup.eu; a.egerer@phoenixgroup.eu"/>
			</SMTP>
			<TCAccess TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="PHADEX" Password="" />
			<pxVerbund DeviceType="7" DeviceName="PHADEX" Computer="" LogMode="1" DataSource="och21@och21_shm" MessageFile="/software/wss/ch/ksc/batch/ini/message.txt" />
			<Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="och21_tcp" IfxDataBase="och21" />
		</Settings>
		<Branches>
			<Branch BranchNo="12">
				<Settings>
					<TCAccess IPAddress="129.210.15.12" Port="3112" />
				</Settings>
			</Branch>		
			<Branch BranchNo="13">
				<Settings>
					<TCAccess IPAddress="129.210.15.12" Port="3113" />
				</Settings>
			</Branch>					
		</Branches>
	</Country>
</KSCRefreshSettings>
