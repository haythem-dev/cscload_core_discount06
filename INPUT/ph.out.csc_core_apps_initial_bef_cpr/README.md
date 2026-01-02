# csc_core_applications

## Useful links

### CSC

#### ERWIN 
erwin files can be found in the "Database models" channel of Outbound Logistics:
[Outbound Logistics - Database models](https://phoenixonline.sharepoint.com/:f:/r/sites/CS-CIT-ORG-CITOutboundLogistics/Shared%20Documents/Database%20models?csf=1&web=1&e=bsdDUa)


#### COIN
- [COIN CSC page](https://coin-collaboration.phoenix.loc/communities/Outbound/CSC/SitePages/Homepage.aspx)
- [CSC / AE Customer documentation in COIN](https://coin-portal.phoenix.loc/groupIT/Outbound_documents/Forms/AllItems.aspx#InplviewHash9b4634f3-ca5c-42b2-9362-31211d065a8e=FilterField1%3DCategory-FilterValue1%3DAE%2520%252F%2520KSC)
- [CSCWiki Sharepoint](https://coin-collaboration.phoenix.loc/communities/Outbound/CSC/CSCWiki/Home.aspx)

#### PROD
- [Changelog for Customers](http://denu1vc0029.phoenix.loc/Outbound/csc_core_applications/customer/)
- [Changelog for Developers](http://denu1vc0029.phoenix.loc/Outbound/csc_core_applications/changelog/)
- [Live Version Overview](https://myphoenixapp1.phoenix.loc/CSC/csc_core_applications_version_overview/prod/index.php)
- [Version History](http://denu1vc0029.phoenix.loc/VersionTracking/indexCscCoreApplications.html)
- [LPAR2RRD AIX Performance](http://10.159.8.32/lpar2rrd/?menu=ef87988&tab=0)
- [B2B Monitoring](http://groupapps.phoenix.loc/B2Bmonitoring/)

#### TEST
- [Live Version Overview TEST](https://myphoenixapp1.phoenix.loc/CSC/csc_core_applications_version_overview/dev/index.php/)
- [PortScan KSCServer/Zaapunix Test](https://myphoenixapp1.phoenix.loc/CSC/ksc_portscan/dev/)


### CICS / tcACCESS

- [Test-CICS Overview](https://myphoenixapp1.phoenix.loc/CSC/test_cics_overview/)
- [TcAccess- Ports prüfen ...](https://myphoenixapp1.phoenix.loc/CSC/tcaccess_portscan/)


### MSV3

#### PROD
- [DATEG Anforderungsformular für MSV3-Spezifikation](http://www.dateg-mbh.de/anforderungsformular.aspx)
- [MSV3 LogClient PROD](https://groupapps.phoenix.loc/MSV3-DE-Logclient/Default/Home)
- [User Account Check PROD](https://myphoenixapp1.phoenix.loc/csc/usercheck/)

#### TEST
- [MSV3 LogClient TEST](https://groupapps.phoenix.loc/MSV3-DE-Test-Logclient/Default/Home)
- [User Account Check TEST](https://myphoenixapp1.phoenix.loc/csc/userchecktest/)


### SalesWeb

#### PROD
- [User Account Check](https://myphoenixapp1.phoenix.loc/csc/usercheck/)
- [SWIMP LogClient Austria](https://groupapps.phoenix.loc/SWIMP-AT-Logclient/Default/Home)
- [SWIMP LogClient Switzerland](https://groupapps.phoenix.loc/SWIMP-CH-Logclient/Default/Home)
- [SWIMP LogClient Bulgaria](https://groupapps.phoenix.loc/SWIMP-BG-Logclient/Default/Home)
- [SWIMP LogClient Croatia](https://groupapps.phoenix.loc/SWIMP-HR-Logclient/Default/Home)
- [SWIMP LogClient France](https://groupapps.phoenix.loc/SWIMP-FR-Logclient/Default/Home)
- [SWIMP LogClient Serbia](https://groupapps.phoenix.loc/SWIMP-RS-Logclient/Default/Home)
- [ShipmentTracking Logclient](https://groupapps.phoenix.loc/TnT-DE-Logclient/Default/DeSt)

#### TEST
- [User Account Check](https://myphoenixapp1.phoenix.loc/csc/userchecktest/)
- [SWIMP LogClient](https://groupapps.phoenix.loc/SWIMP-ALL-Test-Logclient/Default/Home)



## KSC Ports
zaapunix ports = ksc.ini ports

### KSC Ports - Produktion

Land | Host  | cscservice | zaapunix   | kscserver 
---- | ----- | ---------- | ---------- | --------- 
AT   | oat21 | 56111      | 56113 	   | 56630     
PAT  | oat21 | 56191      | 56193 	   | 56655     
BG   | obg21 | 56161      | 56163 	   | 56640     
CH   | och21 | 56101      | 56103      | 56615     
PCH  | och21 | 56141      | 56143 	   | 56620     
DE   | ode21 | 56001      | 56003 	   | 56600     
FR   | ofr21 | 56121      | 56123 	   | 56605     
PFR  | ofr21 | 56131      | 56133 	   | 56610     
HR   | ohr21 | 56201      | 56203 	   | 56625     
RS   | ors21 | 56171      | 56173 	   | 56645     

### KSC Ports - Produktion - Bestandsanfragen DE

Land |Loadbalancer           | Host   | cscservice | name
---- |---------------------  | ------ |----------- | -------
DE   | ode-pa.phoenix.loc    | ode23  | 56670      | cscservice70.bin
DE   |                       | ode24  | 56671      | cscservice71.bin
DE   |                       | ode25  | 56672      | cscservice72.bin
DE   |                       | ode26  | 56673      | cscservice73.bin
DE   |                       | ode27  | 56674      | cscservice74.bin
DE   |                       | ode28  | 56675      | cscservice75.bin
DE   |                       | ode29  | 56676      | cscservice76.bin
DE   |                       |        | 56677      | cscservice77.bin
FR   | ofr-pa.phoenix.loc    | ofr23  | 5XXX0      | cscservice70.bin
FR   |                       |        | 5XXX1      | cscservice71.bin
FR   |                       |        | 5XXX2      | cscservice72.bin
FR   |                       |        | 5XXX3      | cscservice73.bin
FR   |                       |        | 5XXX4      | cscservice74.bin
FR   |                       |        | 5XXX5      | cscservice75.bin
FR   |                       |        | 5XXX6      | cscservice76.bin
FR   |                       |        | 5XXX7      | cscservice77.bin
PFR  | ofrpre-pa.phoenix.loc | ofr23  | 5XXX0      | cscservice70.bin
PFR  |                       |        | 5XXX1      | cscservice71.bin
PFR  |                       |        | 5XXX2      | cscservice72.bin
PFR  |                       |        | 5XXX3      | cscservice73.bin
PFR  |                       |        | 5XXX4      | cscservice74.bin
PFR  |                       |        | 5XXX5      | cscservice75.bin
PFR  |                       |        | 5XXX6      | cscservice76.bin
PFR  |                       |        | 5XXX7      | cscservice77.bin

Land	| cscservice | cscservice Binary Name 
------- | ---------- | ---------------------------
DE   	| 56001      | cscserviceLN.bin

### KSC Ports - Test

Land    | kscserver | cscservice | zaapunix 
------- | --------- | ---------- | ----------
AT      | 56630     | 56111      | 56113 
PAT     | 56655     | 56191      | 56193 
BG      | 56640     | 56161      | 56163 
CH      | 56615     | 56101      | 56103 
PCH     | 56620     | 56141      | 56143 
DE      | 56600     | 56001      | 56003 
FR      | 56605     | 56121      | 56123 
PFR     | 56610     | 56131      | 56133 
HR      | 56625     | 56201      | 56203 
RS      | 56645     | 56171      | 56173 


### KSC Ports - Test - Developer

Developer           | cscservice | kscserver | zaapunix
------------------- | ---------- | --------- | ---------
Heinlein, Steffen   | 56075      | 56076     | 56077
Muenschke, Bjoern   | 56051      | 56052     | 56053
Gugonatu, Dorin     | 56054      | 56055     | 56056
Kolli, Sanjeev      | 56063      | 56064     | 56065
Kondratyev, Dmitry  | 56066      | 56067     | 56068
Degloorwar, Sachin  | 56069      | 56070     | 56071
Gettam, Varun       | 56072      | 56073     | 56074
Zdjelar, David      | 56078      | 56079     | 56080
Singh, Kirtan       | 56081      | 56082     | 56083
Naumann, Frank      | 56084      | 56085     | 56086
CHI Dev             | 56087      | 56088     | 56089
CHI Dev 2           | 56060      | 56061     | 56062
CSCTest             | 56090      | 56091     | 56092
Barth, Sebastian    | 56093      | 56094     | 56095
Schuh, Alexander    | 56096      | 56097     | 56098
Erkens, Ruediger    | 56057      | 56058     | 56059

## Rollout Process ( February 2025 )

### Build artifacts

1. Merge feature branch into develop
2. The comments to the version history ( pxverbund_version.h ) should be written in the following format:

```
\version XX.XX.XX.XX
\date XXXX-XX-XX
\internal
- ...
- ...
\endinternal
\customer
\de
- ...
- ...
\en
- ...
- ...
\endcustomer
```

Don't touch version number ( also in ivy.xml ): It should remain XX.XX.XX.XX. The correct version number will be set later automatically in both files via script.

3. Log in to zdev21 and increase version on develop, e.g.:

`git bumpversion build`

Alternatively, specify another type of version increment:

`major | minor | patch | build`

As a result, a new commit to develop will be pushed with a message "Incremented version number due to new outstanding release!"

4. Open Azure DevOps, create a pull request and merge develop into master.

5. If the merge operation is successful, the pipeline `pharmos.outbound.csc_core_applications.auto_tag_on_master` will be triggered immediately. It will create a new annotated tag for master ( for example, rel0281_20250113_11.03.21.11 ). The pipelines
- `pharmos.outbound.csc_core_applications.Manual.AIX`
- `pharmos.outbound.csc_core_applications.Manual.Win32`
- `pharmos.outbound.csc_core_applications.Manual.Win64`

will start building the tag automatically.

6. Open Azure DevOps, create a pull request and merge the created tag into sikom-new.

7. If the merge operation is successful, the pipeline `pharmos.outbound.csc_core_applications.auto_tag_on_sikom-new` will be triggered immediately. It will create a new annotated tag for sikom-new ( for example, UCC-UnifySikom-11_03_21_11-RC11 ) which will be automatically built by
- `pharmos.outbound.csc_core_applications.Manual.Win32.sikom-new`

### Deploy artifacts

8. Open Azure DevOps, go to Release-Pipelines and start `pharmos.outbound.csc_core_applications`. The build artifacts ( produced in the fifth step ) will be uploaded to Nexus and zdev21 ( /software/wss/release/csc_core_applications/ ).

9. To upload AE binaries and translation files to the Citrix network share ( \\DENU00MS5011.phoenix.loc\Citrix_W2K22_Delivery$\Phoenix ) use release pipelines
- `pharmos.outbound.csc_core_applications.master`
- `pharmos.outbound.csc_core_applications.sikom-new`

This step requires caution ! Before execution, the PowerShell script must be checked and, if necessary, adapted: The countries and environments to which the rollout is required must be specified !

The master-version of AE is currently being used only in France ! All remaining Pharmos-countries are using sikom-new !
