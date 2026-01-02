<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings xsi:noNamespaceSchemaLocation="KSCRefreshSettings.xsd" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
	<Country Country="RS">
		<Settings>
			<General PollInterval="3000" LogLevel="Errors" Test="false"/>
			<SMTP Port="25" Host="10.100.121.30" SendMailFrom="zbw@phoenixgroup.eu">
				<Information eMail="kscrefresh@phoenixgroup.eu"/>
				<Warnings eMail="kscrefresh@phoenixgroup.eu; a.egerer@phoenixgroup.eu"/>
				<Errors eMail="int.dl-FU2ServiceDeskInfos@phoenixgroup.eu; kscrefresh@phoenixgroup.eu; a.egerer@phoenixgroup.eu"/>
			</SMTP>
			<TCAccess TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="CORPHA" Password=""/>
			<pxVerbund DeviceType="7" DeviceName="CORPHA" Computer="" LogMode="1" DataSource="ors21@ors21_shm" MessageFile="/software/wss/rs/ksc/batch/ini/message.txt"/>
			<Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="ors21_tcp" IfxDataBase="ors21"/>
		</Settings>
		<Branches>
			<Branch BranchNo="84">
				<Settings>
					<TCAccess IPAddress="129.210.15.84" Port="3184"/>
				</Settings>
			</Branch>
			<Branch BranchNo="85">
				<Settings>
					<TCAccess IPAddress="129.210.15.84" Port="3185"/>
				</Settings>
			</Branch>
			<Branch BranchNo="03">
				<Settings>
					<TCAccess IPAddress="129.210.15.84" Port="3103"/>
				</Settings>
			</Branch>
		</Branches>
	</Country>
</KSCRefreshSettings>
