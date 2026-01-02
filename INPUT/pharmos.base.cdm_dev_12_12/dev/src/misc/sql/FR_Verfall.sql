//------------- Warengruppen ------------------------//
create temp table TH_FR (wgr char(5) );
load from "D:/temp/fr_wgrs.txt" insert into TH_FR;

//------------- Artikel, die auf Verfall = '1' gesetzt werden ------------------------//
create temp table TH_set_verf_1 ( artnr integer );

insert into TH_set_verf_1 
select artikel_nr from zartikel where 
(kuehlartikel != '0' or tierarznei = '1' or artikel_nr in (select artikel_nr from zartwg where art = '2' and warengruppe in (select wgr from TH_FR)))
and verfall != '1'

unload to 'D:/temp/zdp_fr_pzns_verf_1.txt'
select * from TH_set_verf_1 order by artnr
--> 40.000 Artikel

update zartikel set verfall = '1' where artikel_nr in ( select artnr from TH_set_verf_1)

insert into zapflege (artikel_nr, datum) 
select artnr, 20081016 from TH_set_verf_1
where artnr not in (select artikel_nr from zapflege where datum = 20081016)

select co

//------------- Artikel, die auf Verfall = '0' gesetzt werden ------------------------//
create temp table TH_set_verf_0 ( artnr integer );

insert into TH_set_verf_0 
select artikel_nr from zartikel where 
(kuehlartikel = '0' and tierarznei != '1' and artikel_nr not in (select artikel_nr from zartwg where art = '2' and warengruppe in (select wgr from TH_FR)))
and verfall != '0'

unload to 'D:/temp/zdp_fr_pzns_verf_0.txt'
select * from TH_set_verf_0 order by artnr
--> 11.000 Artikel

update zartikel set verfall = '0' where artikel_nr in ( select artnr from TH_set_verf_0)

insert into zapflege (artikel_nr, datum) 
select artnr, 20081016 from TH_set_verf_0
where artnr not in (select artikel_nr from zapflege where datum = 20081016)

select count(*) from zapflege where datum = 20081016


select count(*) from zartikel where verfall = '0';
select distinct kuehlartikel from zartikel;
select distinct tierarznei from zartikel;
select distinct verfall from zartikel;


// bisher 83000 Artikel mit verfall = '0', 21000 mit verfall = '1'
// --> 62000 zu 42000