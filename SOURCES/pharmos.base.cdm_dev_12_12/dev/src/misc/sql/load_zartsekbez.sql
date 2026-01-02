unload to 'D:\temp\rs\zartsekbez_20111221.txt'
select * from zartsekbez


select * from TH
delete from TH


create temp table TH (pzn integer, sekbez char(30), bem char (240));

load from 'D:\temp\rs\SecondaryArtName.csv' delimiter ';'
insert into TH;

create unique index i_TH on TH (pzn)

select pzn, count(pzn) from TH group by 1 order by 2 desc


select * from zartsekbez where artikel_nr in (select pzn from TH)
select * from TH where pzn not in (select artikel_nr from zartikel)

select z.artikel_nr, z.artikel_mc, b.artikel_mc from zartsekbez b, zartikel z where z.artikel_nr = b.artikel_nr and b.artikel_mc != z.artikel_mc

delete from zartsekbez where artikel_nr in (select pzn from TH);

insert into zartsekbez (artikel_mc, artikel_nr, artikel_name, bemerkungen, pharmos_sekbez)
select substr(replace(sekbez, ' ', ''), 0, 12), pzn, sekbez, bem, '1' from TH

insert into zapflege (artikel_nr, datum)
select pzn, '20111221' from TH where pzn not in (
select artikel_nr from zapflege where datum = 20111221)



