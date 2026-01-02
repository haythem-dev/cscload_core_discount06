select * from carticlecodes where code_type in (8,9,10,11)

load from 'D:\temp\codetypes.txt'
insert into ccodetypes


delete from carticlecodes where code_type = 11;

update carticlecodes set preferred_flag = 1 where code_type in (11) and articleno = 3030303

insert into carticlecodes
select artikel_nr, '11', artikel_nr, '1', '1', cast(to_char(current, '%Y%m%d') as integer)
from zartikel

select * from carticlecodes where articleno in (
select artikel_nr from zartikel where artikel_nr not in (select articleno from carticlecodes where code_type = 11))

select * from zartikel where artikel_nr not in (select articleno from carticlecodes where code_type = 11)


insert into zpznpflege
select artikel_nr, cast(to_char(current, '%Y%m%d') as integer), '34'
from zartikel where artikel_nr not in (select articleno from carticlecodes where code_type = 11)
--from zartikel where datum_anlage = 20110512
and artikel_nr not in (select artikel_nr from zpznpflege where dezap_sa = '34' and datum = cast(to_char(current, '%Y%m%d') as integer))
--and artikel_geloescht != '1'


insert into carticlecodes
select artikel_nr, '11', artikel_nr, '1', '1', cast(to_char(current, '%Y%m%d') as integer)
from zartikel where artikel_nr not in (select articleno from carticlecodes where code_type = 11)
--and artikel_geloescht != '1'

select * from zartikel where datum_anlage = 20110512




select * from carticlecodes where articleno = 3030303 and code_type = 8


select * from zpznpflege where dezap_sa = '34' and datum > 20101201


insert into zpznpflege
select artikel_nr, cast(to_char(current, '%Y%m%d') as integer), '34'
from zartikel where datum_einfuehrung = 20101203
and artikel_nr not in (select artikel_nr from zpznpflege where dezap_sa = '34' and datum = cast(to_char(current, '%Y%m%d') as integer))


////////////////////////////////
CHECKS
////////////////////////////////
--> nur max 1 preferred code pro PZN
select count(articleno), articleno from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) and preferred_flag = 1
group by 2 order by 1 desc

--> preferred code für Nicht-PZN-Ersatz nicht erlaubt!
select * from carticlecodes where preferred_flag = 1 and code_type not in (select code_type from ccodetypes where artnr_substitute = 1) 
-- update carticlecodes set preferred_flag = 0 where preferred_flag = 1 and code_type not in (select code_type from ccodetypes where artnr_substitute = 1) 

--> zu 1 Code mehrere PZNs
select article_code, count(article_code) from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) 
group by article_code
HAVING     (COUNT(article_code) > 1 AND count(distinct articleno) > 1) 

select * from carticlecodes where article_code = '3401525875352'

-->  PZN ohne preferred code
select articleno from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) and articleno not in (
select articleno from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) and preferred_flag = 1)
--and code_type = 11 into temp th
--select * from th
-- create unique index i_th on th (articleno)
--update carticlecodes set preferred_flag = 1 where articleno in (select articleno from th) and code_type = 11

--> PZN ohne 1:1 Code
select artikel_nr from zartikel where artikel_nr not in (select articleno from carticlecodes where code_type = 11)

--> serial_number = 1
select * from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) and serial_number != 1
--delete from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) and serial_number != 1

select * from ccodetypes
delete from carticlecodes where article_code in ('9000000000000')
select * from zartikel where artikel_nr = 257437
update carticlecodes set preferred_flag = 1 where articleno = 1304311

delete from carticlecodes where articleno not in (select artikel_nr from zartikel)


update carticlecodes set preferred_flag = 0 where articleno in (257437) and code_type != '11'


select * from zifaoart where a00pzn = 257437




//////////////////////////////////////////
// AT --> ß
//////////////////////////////////////////

create temp table TH (pzn integer, code char(20));
create unique index i_th on TH (pzn)

delete from TH

load from 'D:\temp\at\tmp\rolfraab.txt' delimiter ';'
insert into TH


select * from carticlecodes where code_type = 12

insert into carticlecodes (articleno, code_type, article_code, serial_number, preferred_flag, date_changed)
select pzn, '12', code, '1', '0', '20110127' from TH

//////////////////////////////////////////
// FR
//////////////////////////////////////////
create temp table TH (pzn integer, code char(20), typename char(10), type smallint);
create unique index i_th on TH (pzn);

load from 'c:\temp\fr\Code13_CodesArticles.csv' delimiter ';'
insert into TH

select code, count(code) from th group by code HAVING     (COUNT(code) > 1 AND count(distinct pzn) > 1) 

delete from carticlecodes where articleno in (select pzn from th where type = carticlecodes.code_type)

delete from carticlecodes where date_changed = cast(to_char(current, '%Y%m%d') as integer)

insert into carticlecodes (articleno, code_type, article_code, serial_number, preferred_flag, date_changed)
select pzn, type, code, '1', '0', cast(to_char(current, '%Y%m%d') as integer)
from th

insert into zpznpflege
select pzn, cast(to_char(current, '%Y%m%d') as integer), '34'
from th where pzn not in (select artikel_nr from zpznpflege where dezap_sa = '34' and datum = cast(to_char(current, '%Y%m%d') as integer))

select * from ccodetypes



create temp table TH (pzn integer, code char(20));
create unique index i_th on TH (pzn);

load from 'c:\temp\fr\EAN13_a_changer.csv' delimiter ';'
insert into TH

unload to 'C:\temp\fr\ean_20130603.txt'
select * from ean

select * from ean where artikel_nr = 4780868;
select * from th where pzn = 4780868;

select *  from ean where ean_nr in (select code from TH where pzn = ean.artikel_nr)
select *  from ean where artikel_nr in (select pzn from TH where code != ean.ean_nr)

delete from ean where artikel_nr in (select pzn from TH where code != ean.ean_nr)
delete from TH where pzn in (select artikel_nr from ean)

select * from ean where artikel_nr in (select pzn from TH)
select * from TH where code in (select ean_nr from ean)

delete  from TH where code in (select ean_nr from ean)

insert into ean (artikel_nr, ean_nr)
select pzn, code from TH;

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select pzn, cast(to_char(current, '%Y%m%d') as integer), '09' from TH where pzn not in (select artikel_nr from zpznpflege where dezap_sa = '09' and datum = cast(to_char(current, '%Y%m%d') as integer))

