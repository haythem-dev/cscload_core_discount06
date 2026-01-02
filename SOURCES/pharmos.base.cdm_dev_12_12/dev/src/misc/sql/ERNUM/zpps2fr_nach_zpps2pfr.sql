unload to 'C:\temp\fr\ean.txt'
select * from ean;

unload to 'C:\temp\fr\codes.txt'
select * from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1);

create temp table th (pzn integer, ean char(20), pfl char(2));
load from  'C:\temp\fr\ean.txt'
insert into th
create unique index i_th on th (pzn)


delete from th where pzn not in (select artikel_nr from zartikel)
delete from th where pzn in (select artikel_nr from ean)
delete from th where ean in (select ean_nr from ean)


select * from th
select * from ean


insert into ean 
select * from zpznpflege

insert into zpznpflege
select pzn, cast(to_char(current, '%Y%m%d') as integer), '09'
from th where pzn not in (select artikel_nr from zpznpflege where dezap_sa = '09' and datum = cast(to_char(current, '%Y%m%d') as integer))

------------------
drop table th

create temp table th (pzn integer, type smallint, code char(25), serial smallint, pref smallint, dat integer);
load from  'C:\temp\fr\codes.txt'
insert into th
create unique index i_th on th (pzn, type)


delete from th where pzn not in (select artikel_nr from zartikel)
delete from th where pzn in (select articleno from carticlecodes where code_type = type)

delete from th where pref = 1


insert into carticlecodes (articleno, code_type, article_code, serial_number, preferred_flag, date_changed)
select pzn ,type ,code ,serial ,pref ,'20130121' from th

insert into zpznpflege
select pzn, cast(to_char(current, '%Y%m%d') as integer), '34'
from th where pzn not in (select artikel_nr from zpznpflege where dezap_sa = '34' and datum = cast(to_char(current, '%Y%m%d') as integer))