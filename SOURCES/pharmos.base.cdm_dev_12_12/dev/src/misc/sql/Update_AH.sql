create temp table TH (pzn integer, rrdat integer);
create unique index i_TH on TH (pzn);


load from 'D:\temp\ch\Artikel_Swissmedic.csv' delimiter ';'
insert into TH

delete from Th where pzn not in (select artikel_nr from zartikel)

select distinct pzn from TH group by 1 order by 2, 1

drop table TH

select artikel_nr, datum_rr from zartikel where artikel_nr in (select pzn from TH) order by 2

update zartikel set datum_rr = (select rrdat from TH where TH.pzn = zartikel.artikel_nr) where artikel_nr in (select pzn from TH) and artikel_nr = 127829

insert into zapflege (datum, artikel_nr)
select '20110126', pzn from TH

select * from zapflege where datum = 20110126



unload to 'D:\temp\ch\kuko_ah.txt'
select * from cdiscount where dateto > 20110622 and articleno in (select artikel_nr from zartikel where datum_ah > 0 ) order by 1

insert into zpznpflege 
select distinct articleno,  '20110622', '28' from cdiscount 
where dateto > 20110622 and articleno in (select artikel_nr from zartikel where datum_ah > 0 ) 
and articleno not in (
select artikel_nr from zpznpflege where dezap_sa = '28' and datum = 20110622 )

update cdiscount set dateto = 20110630 
where dateto > 20110622 and articleno in (select artikel_nr from zartikel where datum_ah > 0 ) 
