unload to 'D:\temp\at\aktionen_zu_beenden.txt'
select * from cdiscount 
where datefrom <= 20120630 and dateto > 20120630
and pharmacygroupid in ( '000', '017' )  
--and customerno in ( 4096110 )  
and articleno in 
(select artikel_nr from zartikel where hersteller_nr in  ( 1383,1112,1497  ))
--and datefrom = 20110801
--and customerno <= 0


update cdiscount set dateto = 20120630 
where datefrom <= 20120630 and dateto > 20120630
and pharmacygroupid in  ( '000', '017' )  
--and customerno in ( 4096110 )  
and articleno in 
(select artikel_nr from zartikel where hersteller_nr in  ( 1383,1112,1497 ))
--and datefrom = 20110801
--and customerno <= 0


insert into zpznpflege 
select distinct articleno,  '20120612', '28' from cdiscount 
where dateto = 20120630
and pharmacygroupid in ( '000', '017' ) 
--and customerno in ( 4096110 )  
and articleno in 
(select artikel_nr from zartikel where hersteller_nr in  (1383,1112,1497  ))
--and customerno <= 0
and articleno not in (
select artikel_nr from zpznpflege where dezap_sa = '28' and datum = 20120612 )


select * from ccustomermaindata order by customerno



//////////////////////////////////////////////////////////

insert into zpznpflege 
select distinct articleno,  '20110209', '28' from cdiscount 
where datefrom < 20110209 and dateto > 20110209 and articleno in (2448874,2448880,2448897,2448905,2471749,2471838,3761656,3761679,3762348,3761685,3761716,3762354,2473754,2473783) 
and articleno not in (
select artikel_nr from zpznpflege where dezap_sa = '28' and datum = 20110209 )

select distinct articleno from cdiscount where datefrom < 20110209 and dateto > 20110209 and articleno in (2448874,2448880,2448897,2448905,2471749,2471838,3761656,3761679,3762348,3761685,3761716,3762354,2473754,2473783) 
select * from cdiscount where datefrom < 20110209 and dateto > 20110209 and articleno in (2448874,2448880,2448897,2448905,2471749,2471838,3761656,3761679,3762348,3761685,3761716,3762354,2473754,2473783) 

update cdiscount set dateto = 20110209 
where datefrom < 20110209 and dateto > 20110209 and articleno in (2448874,2448880,2448897,2448905,2471749,2471838,3761656,3761679,3762348,3761685,3761716,3762354,2473754,2473783) 


//////// CH //////////////////////////////////////////////////

create temp table TH (pzn integer, idf integer);
create unique index i_TH on TH (pzn);

drop table TH

load from 'D:\temp\CH\Pfizer_RP_löschen_Overdrive.csv' delimiter ';'
insert into TH

select * from cdiscount where dateto > 20110531 and customerno in (select idf from TH where cdiscount.articleno = pzn)

update cdiscount set dateto = 20110531 
where dateto > 20110531 and customerno in (select idf from TH where cdiscount.articleno = pzn)

insert into zpznpflege 
select distinct articleno,  '20110525', '28' from cdiscount 
where dateto > 20110531 and customerno in (select idf from TH where cdiscount.articleno = pzn)
and articleno not in (
select artikel_nr from zpznpflege where dezap_sa = '28' and datum = 20110525)




//////// FR //////////////////////////////////////////////////
unload to 'D:\temp\frankreich\aktionen_zu_beenden_20120224.txt'
select * from cdiscount where dateto >= 20120223 and pharmacygroupid in ('810', '812', '814', '815');

unload to 'D:\temp\frankreich\aktionen_zu_beenden_20120229.txt'
select * from cdiscount where dateto >= 20120229 and pharmacygroupid in ('932', '931', '920');

insert into zpznpflege 
select distinct articleno,  '20120224', '28' from cdiscount 
where dateto >= 20120223 and pharmacygroupid in ('810', '812', '814', '815')
and articleno not in (
select artikel_nr from zpznpflege where dezap_sa = '28' and datum = 20120224 )

update cdiscount set dateto = 20120224
where dateto >= 20120223 and pharmacygroupid in ('810', '812', '814', '815');

insert into zpznpflege 
select distinct articleno,  '20120229', '28' from cdiscount 
where dateto >= 20120229 and pharmacygroupid in ('932', '931', '920')
and articleno not in (
select artikel_nr from zpznpflege where dezap_sa = '28' and datum = 20120229 )


update cdiscount set dateto = 20120229
where dateto >= 20120229 and pharmacygroupid in ('932', '931', '920');