select * from catccode;
select * from cephmracode;
select * from clpprcode

create temp table th (pzn integer, eph char (20), atc char (20), lppr char(20), maxpr decimal (10,2), orig integer);
create unique index i_th on th (pzn);

drop table th

load from 'C:\temp\fr\changes_masterdata2.csv' delimiter ';'
insert into th


select * from th order by pzn


select * from th where pzn not in (select artikel_nr from zartikel)
--> 2658 PZN´s nicht in zartikel !? / 0
delete from th where pzn not in (select artikel_nr from zartikel)

----------------------
unload to 'C:\temp\fr\eph.txt' delimiter ';'
select pzn, eph from th where eph not in (select code_ephmra from cephmracode)
--> 126 / 105
update th set eph = '' where eph != '' and  eph not in (select code_ephmra from cephmracode)
update th set eph = '' where eph is null

delete from carticlecodes where code_type = 14 and articleno in (select pzn from th where eph != '')
insert into carticlecodes (articleno, code_type, article_code, serial_number, preferred_flag, date_changed) select pzn, '14', eph, '0', '0', '20121128' from th where eph != ''
--> 9886

select * from th where eph = ''

----------------------

unload to 'C:\temp\fr\atc.txt' delimiter ';'
select pzn, atc from th where atc not in (select code_atc from catccode)
--> 561 / 432
update th set atc = '' where atc != '' and  atc not in (select code_atc from catccode)
update th set atc = '' where atc is null

delete from carticlecodes where code_type = 2 and articleno in (select pzn from th where atc != '')
insert into carticlecodes (articleno, code_type, article_code, serial_number, preferred_flag, date_changed) select pzn, '2', atc, '0', '0', '20121128' from th where atc != ''
--> 9557

select * from catccode

----------------------
unload to 'C:\temp\fr\orig.txt' delimiter ';'
select pzn, orig from th where orig not in (select artikel_nr from zartikel)
--> 85 / 7
update th set orig = 0 where orig != 0 and orig not in (select artikel_nr from zartikel)
update th set orig = 0 where orig is null

update zartikel set artikel_nr_orig = (select orig from th where orig != 0 and pzn = zartikel.artikel_nr) where artikel_nr in (select pzn from th where orig != 0)
--> 387

----------------------
unload to 'C:\temp\fr\lppr.txt' delimiter ';'
select pzn, lppr  from th where lppr not in (select code_lppr  from clpprcode)
--> OK !!! / 17

update th set lppr = '' where lppr != '' and  lppr not in (select code_lppr  from clpprcode)
update th set lppr = '' where lppr is null

select * from zartfrance where articleno in (select pzn from th where lppr != '')
--> haben bereits alle reimbursement_type = 2 = OK

update zartfrance set code_lppr = (select lppr from th where lppr != '' and pzn = zartfrance.articleno) where articleno in (select pzn from th where lppr != '')
--> 2389

----------------------

select * from th where maxpr > 0

select * from zartpreis as a where artikel_nr in
(select pzn from th as b where maxpr > 0) and
datumgueltigab = (select max(datumgueltigab) from zartpreis as c
where a.artikel_nr = c.artikel_nr) 
into temp r1

select * from r1

update r1 set maxavp = (select maxpr from th where pzn = r1.artikel_nr), datumgueltigab = 20121129

unload to 'C:\temp\fr\maxavp.txt' delimiter ';'
select artikel_nr, maxavp from r1 where maxavp < avp
--> 1 / 1
delete from r1 where maxavp < avp

insert into zartpreis
select * from r1
--> 1155

----------------------

insert into zapflege (datum, artikel_nr)
select '20121128', pzn from th
where pzn not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer))


