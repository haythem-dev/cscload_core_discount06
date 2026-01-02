unload to 'D:\temp\zartikel_sortiment_3_4.txt'
select artikel_nr, sortiment_3, sortiment_4 from zartikel where sortiment_4 = '1' or sortiment_3 = '1' order by 1

drop table TH


create temp table TH (pzn integer, flag smallint);
create unique index i_TH on TH (pzn);

load from 'D:\temp\s4_1.csv' delimiter ';'
insert into TH;

insert into zapflege (artikel_nr, datum)
select artikel_nr, '20110607' from zartikel where sortiment_4 = '1'
and artikel_nr not in (select artikel_nr from zapflege where datum = 20110607)

update zartikel set sortiment_4 = '0' where sortiment_4 = '1'

update zartikel set sortiment_4 = 
'1'
--(select flag from TH where pzn = zartikel.artikel_nr)
where artikel_nr in (select pzn from TH);

insert into zapflege (artikel_nr, datum)
select pzn, '20110607' from TH where pzn not in (select artikel_nr from zapflege where datum = 20110607)