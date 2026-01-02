create temp table TH (pzn integer, dfo char(5))

create unique index i_TH on TH (pzn);


load from 'D:\temp\hr\dfo.csv' delimiter ';'
insert into TH


select distinct pzn, dfo from TH group by 1 order by 2, 1

drop table TH

create temp table TH2 (pzn integer, dfo char(3));
create unique index i_TH2 on TH2 (pzn);

insert into TH2
select distinct pzn, dfo from TH


2221
2184

select distinct darreichform from zartikel where artikel_nr in (select pzn from TH2)

update zartikel set darreichform = (select dfo from TH2 where zartikel.artikel_nr = pzn) where artikel_nr in (select pzn from TH2)

insert into zapflege (datum, artikel_nr)
select '20101020', pzn from TH2

select * from zapflege where datum = 20101020

select distinct dfo from TH
select * from zdarreichform

I
III
IIA
IIB