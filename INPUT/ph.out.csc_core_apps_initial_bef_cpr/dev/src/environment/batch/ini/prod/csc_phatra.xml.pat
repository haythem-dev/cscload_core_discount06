<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings xsi:noNamespaceSchemaLocation="KSCRefreshSettings.xsd" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
	<Country Country="AT">
		<Settings>
			<General PollInterval="5" LogLevel="Warnings" Test="false" />			
			<SMTP Port="25" Host="10.100.121.30" SendMailFrom="csc_phatra@phoenixgroup.eu">
				<Information eMail="" />
				<Warnings eMail="kscrefresh@phoenixgroup.eu" />
				<Errors eMail="int.dl-FU2ServiceDeskInfos@phoenixgroup.eu; kscrefresh@phoenixgroup.eu; a.egerer@phoenixgroup.eu;" />
			</SMTP>
			<TCAccess IPAddress="129.210.15.61" TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="PHATRA" Password="" />			
			<pxVerbund DeviceType="7" DeviceName="PHATRA" Computer="" LogMode="1" DataSource="oat21pre@oat21_shm" MessageFile="/software/wss/pat/ksc/batch/ini/message.txt" />
			<Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="oat21_tcp" IfxDataBase="oat21pre" />	
		</Settings>
		<Branches>			
			<Branch BranchNo="83">
				<Settings>
					<TCAccess Port="3183" />
				</Settings>
			</Branch>
		</Branches>		
	</Country>
</KSCRefreshSettings>
