<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings>
    <Country Country="CH">
        <Settings>
            <General PollInterval="3000" LogLevel="Errors" Test="false" BulkInsert="true" MaxSelect="40"/>
            <SMTP Port="25" Host="10.156.80.21" SendMailFrom="kscrefreshtest@phoenixgroup.eu">
                <Information eMail="kscrefreshtest@phoenixgroup.eu"/>
                <Warnings eMail="kscrefreshtest@phoenixgroup.eu"/>
                <Errors eMail="kscrefreshtest@phoenixgroup.eu"/>
            </SMTP>
            <TCAccess TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="PHADEX" Password="" />
            <pxVerbund DeviceType="7" DeviceName="PHADEX" Computer="" LogMode="1" DataSource="och21@zqas21_tcp" MessageFile="/software/wss/ch/ksc/batch/ini/message.txt" />
            <Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="zqas21_tcp" IfxDataBase="och21" />
        </Settings>
        <Branches>
            <Branch BranchNo="12">
                <Settings>
                    <TCAccess IPAddress="10.242.5.216" Port="3312" />
                </Settings>
            </Branch>		
            <Branch BranchNo="13">
                <Settings>
                    <TCAccess IPAddress="10.242.5.216" Port="3313" />
                </Settings>
            </Branch>					
        </Branches>
    </Country>
</KSCRefreshSettings>
