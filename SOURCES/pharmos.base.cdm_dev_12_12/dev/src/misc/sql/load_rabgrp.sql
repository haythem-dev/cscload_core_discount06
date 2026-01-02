create temp table TH (pzn integer, grp char(5));
create unique index i_TH on TH (pzn);

load from 'D:\temp\rs\rabgrp.csv' delimiter ';'
insert into TH

delete from TH

select distinct pzn, grp from TH

create temp table TH_2 (pzn integer, grp char(5));
create unique index i_TH on TH_2 (pzn);


insert into TH_2
select distinct pzn, grp from TH


select * from TH where grp not in (select rabattgruppe from zrabgrp);
select * from TH where pzn not in (select artikel_nr from zartikel);

select * from zrabgrp order by rabattgruppe

select * from zartwg where art = '9';
select * from TH order by pzn

select * from zartwg where art = '9' and artikel_nr in (select pzn from TH)



insert into zartwg (artikel_nr, art, warengruppe)
select pzn, '9', grp from TH


insert into zapflege
select pzn, '20120330' from TH where pzn not in (select artikel_nr from zapflege where datum = 20120330)



-------------------------------------------------
load from 'D:\temp\cdiscgrpmem_rs.txt'
insert into cdiscgrpmem


create temp table TH (pzn integer, grp_old char(5), grp_new char(5));
create unique index i_TH on TH (pzn);

load from 'D:\temp\rs\cdiscgrpmem.csv' delimiter ';'
insert into TH

select * from TH order by grp_old


select * from TH where pzn not in (select articleno from cdiscgrpmem)
select * from TH where pzn not in (select articleno from cdiscgrpmem where discountgrpno = grp_old)

delete from cdiscgrpmem where articleno in (select pzn from TH where grp_old = discountgrpno)
delete from cdiscgrpmem where articleno in (select pzn from TH where grp_new = discountgrpno)

insert into cdiscgrpmem (articleno, discountgrpno) 
select pzn, grp_new from TH

--update cdiscgrpmem set discountgrpno = (select grp_new from TH where pzn = articleno) where articleno in (select pzn from TH) and discountgrpno = (select grp_old from TH where pzn = articleno)

select * from zgrppflege where dezap_sa = '31'


select distinct "0"||to_char(grp_old) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '31' as z from TH where 0||to_char(grp_old) not in (select key_gruppe from zgrppflege where dezap_sa = '31' and datum = cast(to_char(current, '%Y%m%d') as integer))  
into temp th1

select * from th1

insert into zgrppflege
select * from th1 where x not in (select key_gruppe from zgrppflege where dezap_sa = '31' and datum = cast(to_char(current, '%Y%m%d') as integer))



select distinct "0"||to_char(grp_new) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '31' as z from TH where 0||to_char(grp_new) not in (select key_gruppe from zgrppflege where dezap_sa = '31' and datum = cast(to_char(current, '%Y%m%d') as integer))  
into temp th2

select * from th2

insert into zgrppflege
select * from th2 where x not in (select key_gruppe from zgrppflege where dezap_sa = '31' and datum = cast(to_char(current, '%Y%m%d') as integer))
