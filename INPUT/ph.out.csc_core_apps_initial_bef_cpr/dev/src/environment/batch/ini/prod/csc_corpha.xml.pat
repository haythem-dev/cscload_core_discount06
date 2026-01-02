<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings xsi:noNamespaceSchemaLocation="KSCRefreshSettings.xsd" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
	<Country Country="AT">
		<Settings>
			<General PollInterval="3000" LogLevel="Errors" Test="false"/>			
			<SMTP Port="25" Host="10.100.121.30" SendMailFrom="csc_corpha@phoenixgroup.eu">
				<Information eMail="kscrefreshtest@phoenixgroup.eu"/>
				<Warnings eMail="kscrefreshtest@phoenixgroup.eu"/>
				<Errors eMail="kscrefreshtest@phoenixgroup.eu"/>
			</SMTP>
			<TCAccess IPAddress="129.210.15.61" TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="CORPHA" Password="" />			
			<pxVerbund DeviceType="7" DeviceName="CORPHA" Computer="" LogMode="1" DataSource="oat21pre@oat21_shm" MessageFile="/software/wss/pat/ksc/batch/ini/message.txt" />
			<Informix IfxServiceName="53004" IfxHost="oat21_tcp" IfxDataBase="oat21pre" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" />									
		</Settings>
		<Branches>				
			<Branch BranchNo="83">
				<Settings>
					<TCAccess Port="3183"/>
				</Settings>
			</Branch>
		</Branches>		
	</Country>
</KSCRefreshSettings>
