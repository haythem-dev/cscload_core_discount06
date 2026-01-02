<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings xsi:noNamespaceSchemaLocation="KSCRefreshSettings.xsd" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    <Country Country="RS">
        <Settings>
            <General PollInterval="5000" LogLevel="Warnings" Test="false" />			
            <SMTP Port="25" Host="10.156.80.21" SendMailFrom="kscrefreshtest@phoenixgroup.eu">
                <Information eMail="kscrefreshtest@phoenixgroup.eu" />
                <Warnings eMail="kscrefreshtest@phoenixgroup.eu" />
                <Errors eMail="kscrefreshtest@phoenixgroup.eu" />
            </SMTP>
            <TCAccess TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="PHADEX" Password="" />
            <pxVerbund DeviceType="7" DeviceName="PHADEX" Computer="" LogMode="1" DataSource="ors21@zqas21_shm" MessageFile="/software/wss/rs/ksc/batch/ini/message.txt" />
            <Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="zqas21_tcp" IfxDataBase="ors21" />	
        </Settings>
        <Branches>			
            <Branch BranchNo="3">
                <Settings>
                    <TCAccess IPAddress="10.242.5.215" Port="3303"/>
                    <pxVerbund/>
                </Settings>
            </Branch>
            <Branch BranchNo="84">
                <Settings>
                    <TCAccess IPAddress="10.242.5.215" Port="3384"/>
                    <pxVerbund/>
                </Settings>
            </Branch>
            <Branch BranchNo="85">
                <Settings>
                    <TCAccess IPAddress="10.242.5.215" Port="3385"/>
                    <pxVerbund/>
                </Settings>
            </Branch>
        </Branches>		
    </Country>
</KSCRefreshSettings>
