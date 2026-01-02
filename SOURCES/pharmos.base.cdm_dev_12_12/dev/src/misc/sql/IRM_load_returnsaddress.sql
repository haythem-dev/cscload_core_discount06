create temp table th (SUPPLIERNO integer,
NAME char(30),
NAME2 char(30),
MATCHCODE char(20),
LOCATION char(30),
ZIPCODE char(10),
STREET char(50),
PHONE char(30),
FAX char(30),
COUNTRY char(3),
OUR_CUSTOMERNO char(20),
PHARMOS_SUPPLIERNO integer,
CONTACT_PERSON char(30),
LINK_TO_CONTRACT char(255),
GENERALCONDITION char(255));


delete from th;

load from 'C:\temp\fr\ReturnAdressUploading-170224.csv' delimiter ';'
insert into th;

create unique index i_th on th (supplierno);


select * from th where supplierno not in (select lant_nr from liefer)

unload to 'C:\temp\fr\returnsaddress_20170227.txt'
select * from returnsaddress 

delete from returnsaddress

insert into returnsaddress
select 
SUPPLIERNO * 10, 
SUPPLIERNO, 
NAME ,
nvl(NAME2, ''),
nvl(OUR_CUSTOMERNO, ''),
nvl(MATCHCODE,''),
nvl(STREET,''),
nvl(ZIPCODE, ''),
nvl(LOCATION,''),
nvl(PHONE,''),
nvl(FAX, ''),
nvl(PHARMOS_SUPPLIERNO, 0),
nvl(CONTACT_PERSON, ''),
nvl(LINK_TO_CONTRACT, ''),
'0',
'batch',
current,
current,
nvl(COUNTRY,''),
nvl(GENERALCONDITION, '')
from th



delete from irmreturnsrule 

unload to 'C:\temp\fr\irmreturnsrulecategory.txt'
select * from irmreturnsrulecategory;

load from 'C:\temp\fr\irmreturnsrulecategory.txt'
insert into irmreturnsrulecategory;

insert into irmreturnsrule (branchno, returnsrulecategoryid, returnsaddressno, rule, percentpayment, changeuser, creationdatetime, monthsbefore, monthsafter)
select '0', returnsrulecategoryid, returnsaddressno, 'TBD', defaultpercentpayment, 'batch', current, '0', '0' from returnsaddress, irmreturnsrulecategory;

