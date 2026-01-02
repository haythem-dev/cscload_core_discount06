create temp table TH (pzn integer, ean char(30));
create unique index i_TH on TH(pzn);
create unique index i_TH2 on TH(ean);

load from 'D:\temp\HR\product_ean.csv' delimiter ';'
insert into TH

select * from TH order by pzn;

select ean, count(ean) from TH group by 1 order by 2 desc
delete from TH where ean in ('3850343046442', '3850343045513', '3850343065542')
select *  from ean where ean_nr in (select ean from TH)
select *  from ean where artikel_nr in (select pzn from TH)


delete from TH where ean in (select ean_nr from ean)


insert into ean (artikel_nr, ean_nr)
select pzn, ean from TH;

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select pzn, '20111121', '09' from TH where pzn not in (select artikel_nr from zpznpflege where dezap_sa = '09' and datum = 20111121)


select * from zpznpflege