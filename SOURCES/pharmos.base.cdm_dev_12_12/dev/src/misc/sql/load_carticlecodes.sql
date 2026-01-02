select * from carticlecodes where code_type in (8,9,10,11)

load from 'D:\temp\codetypes.txt'
insert into ccodetypes


delete from carticlecodes where code_type = 11;

update carticlecodes set preferred_flag = 0 where code_type in (8,9,10) and preferred_flag = 1;

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




--delete from carticlecodes where articleno = 16099 and code_type = 11


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

--> zu 1 Code mehrere PZNs
select article_code, count(article_code) from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) 
--and code_type not in (11, 16)
group by article_code
HAVING     (COUNT(article_code) > 1) 

-->  PZN ohne preferred code
select articleno from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) and articleno not in (
select articleno from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1) and preferred_flag = 1)

--> PZN ohne 1:1 Code
select artikel_nr from zartikel where artikel_nr not in (select articleno from carticlecodes where code_type = 11)



select * from carticlecodes where articleno = 256797
update carticlecodes set preferred_flag = 1 where articleno = 1304311

delete from carticlecodes where articleno not in (select artikel_nr from zartikel)


update carticlecodes set preferred_flag = 0 where articleno in (2280937, 2585016, 2591347) and code_type != '11'




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