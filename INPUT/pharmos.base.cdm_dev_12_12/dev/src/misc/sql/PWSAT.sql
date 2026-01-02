select * from zartikel where artikel_geloescht != '1'


unload to 'D:\temp\pwsat_langname.txt'
select artikel_nr, artikel_name from zartikel where artikel_geloescht != '1'


create temp table TH (pzn integer, name char(100));
create unique index i_TH on TH (pzn)


load from  'D:\temp\pwsat_langname.txt'
insert into TH


delete from TH where pzn not in (select artikel_nr from zartikel)

unload to 'D:\temp\pwsat\diff_langname.txt'
select pzn, name, artikel_name from TH, zartikel where pzn = artikel_nr and name != artikel_name


update zartikel set preis0artikel = '1'  where artikel_geloescht != '1'

insert into zapflege
select artikel_nr, cast(to_char(current, '%Y%m%d') as integer) from zartikel
where artikel_geloescht != '1'
and artikel_nr not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer))

insert into zpznpflege
select artikel_nr, cast(to_char(current, '%Y%m%d') as integer), '33' from zartikel
where artikel_geloescht != '1'
and artikel_nr not in (select artikel_nr from zpznpflege where dezap_sa = '33' and datum = cast(to_char(current, '%Y%m%d') as integer))


create temp table TH (pzn integer, wg char(5));
create unique index i_TH on TH (pzn);

load from  'D:\temp\pwsat\ARTWGR_83.csv' delimiter ';'
insert into TH


select * from TH where pzn not in (select artikel_nr from zartikel)


delete from zartwg where art = '2' and artikel_nr in (select pzn from TH)

insert into zartwg (artikel_nr, art, warengruppe)
select pzn, '2', wg from TH;

insert into zapflege
select distinct pzn, cast(to_char(current, '%Y%m%d') as integer) from TH
where pzn in (select artikel_nr from zartikel)
and pzn not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer))



select distinct wg from TH where wg not in (select wgr_gruppe from zdkwgr)


select * from zdkwgr

select * from herstel where hersteller_nr = 11729


select * from zartikel where artikel_geloescht != '1' and artikel_langname like '%µ%'


update zartikel set artikel_name = upper(artikel_name) where artikel_geloescht != '1'  and artikel_nr > 9000000

update zartikel set artikel_langname = replace(artikel_langname, 'µ', 'mc') where artikel_geloescht != '1' and artikel_langname like '%µ%' and artikel_nr = 3517301

update zartikel set artikel_langname = 'Formoterol rtp 12 mcg Hkps z.Tr.inh.60 AEM' where artikel_nr = 9006381


select * from zartikel where artikel_geloescht != '1' and artikel_nr = 3517519

unload to 'D:\temp\pwsat\liste_artikel.txt'
select a.artikel_nr, artikel_name, artikel_langname, artikel_nr_herst, awl1, hersteller_nr, warengruppe from zartikel a, zartwg w where a.artikel_nr = w.artikel_nr and w.art = '2' and  artikel_geloescht != '1'
order by 1
