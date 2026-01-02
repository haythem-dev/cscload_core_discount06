<?xml version="1.0" encoding="UTF-8"?>
<KSCRefreshSettings xsi:noNamespaceSchemaLocation="../../KSCRefreshSettings.xsd" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
    <Country Country="AT">
        <Settings>
            <General PollInterval="3000" LogLevel="Warnings" Test="false"/>
            <SMTP Port="25" Host="10.156.80.21" SendMailFrom="csc_phatra@phoenixgroup.eu">
                <Information eMail=""/>
                <Warnings eMail=""/>
                <Errors eMail="kscrefreshtest@phoenixgroup.eu;"/>
            </SMTP>
            <TCAccess IPAddress="10.242.5.212" TCATransaction="TCAS" TCAHost="PhoenixGeneric_west" ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" Username="CORPHA" Password=""/>
            <pxVerbund DeviceType="7" DeviceName="PHATRA" Computer="" LogMode="1" DataSource="oat21pre@zqas21_shm" MessageFile="/software/wss/pat/ksc/batch/ini/message.txt"/>
            <Informix ConnectionRetries="10" ConnectionWaitBeforeRetry="10000" IfxServiceName="53004" IfxHost="zqas21_tcp" IfxDataBase="oat21pre"/>
        </Settings>
        <Branches>
            <Branch BranchNo="83">
                <Settings>
                    <TCAccess IPAddress="10.242.5.216" Port="3383"/>
                    <pxVerbund LogFile="/software/wss/pat/ksc/batch/log/cics02_csc_phatra.log" SystemLogFile="/software/wss/pat/ksc/batch/log/cics02_csc_phatra_wws.log"/>
                </Settings>
            </Branch>
        </Branches>
    </Country>
</KSCRefreshSettings>
