select artikel_nr_herst, hersteller_nr from zartikel where artikel_nr = 31213
select * from artnrbl where artikel_nr = 4134795
select count(*) from artnrbl

unload to 'C:\temp\at\artnrbl_sicher_20160817.txt'
select * from artnrbl

---------------------------------------------------------------------------------------------------------------
// bestehende Einträge korrigieren

select a.artikel_nr, a.besla_nr, z.hersteller_nr, a.artikel_nr_bliefer, z.artikel_nr_herst 
from artnrbl a, zartikel z 
where a.artikel_nr = z.artikel_nr and a.besla_nr = z.hersteller_nr and z.artikel_nr_herst != a.artikel_nr_bliefer 
--and z.awl1 = 0

--union

--select a.artikel_nr, a.besla_nr, z.awl1, a.artikel_nr_bliefer, z.artikel_nr_herst 
--from artnrbl a, zartikel z 
--where a.artikel_nr = z.artikel_nr and a.besla_nr = z.awl1 and z.artikel_nr_herst != a.artikel_nr_bliefer 
--and z.awl1 > 0

order by 1



update artnrbl 
set artikel_nr_bliefer = nvl((select artikel_nr_herst from zartikel where artnrbl.artikel_nr = artikel_nr and artnrbl.besla_nr = hersteller_nr and artikel_nr_herst != artnrbl.artikel_nr_bliefer
-- and awl1 = 0
), artikel_nr_bliefer) 

update artnrbl 
set artikel_nr_bliefer = nvl((select artikel_nr_herst from zartikel where artnrbl.artikel_nr = artikel_nr and artnrbl.besla_nr = awl1 and artikel_nr_herst != artnrbl.artikel_nr_bliefer and awl1 > 0), artikel_nr_bliefer) 


---------------------------------------------------------------------------------------------------------------
// fehlende Einträge einfügen

select 
--count(*)
artikel_nr, hersteller_nr, artikel_nr_herst 
from zartikel where artikel_nr_herst != '' 
--and hersteller_nr > 0 and awl1 = 0 
and hersteller_nr in (select besla_nr from bliefer) 
and artikel_nr not in (select artikel_nr from artnrbl where besla_nr = zartikel.hersteller_nr)

select 
--count(*)
artikel_nr, awl1, artikel_nr_herst 
from zartikel where artikel_nr_herst != '' and awl1 > 0 and awl1 in (select besla_nr from bliefer) and artikel_nr not in (select artikel_nr from artnrbl where besla_nr = zartikel.awl1)

create temp table TH (pzn integer, hnr integer, artnr char(30));
create unique index i_TH on TH (pzn, hnr)

insert into TH
select artikel_nr, hersteller_nr, artikel_nr_herst 
from zartikel where artikel_nr_herst != '' 
--and hersteller_nr > 0 and awl1 = 0 
and hersteller_nr in (select besla_nr from bliefer) and artikel_nr not in (select artikel_nr from artnrbl where besla_nr = zartikel.hersteller_nr)

insert into TH
select artikel_nr, awl1, artikel_nr_herst 
from zartikel where artikel_nr_herst != '' and awl1 > 0 and awl1 in (select besla_nr from bliefer) and artikel_nr not in (select artikel_nr from artnrbl where besla_nr = zartikel.awl1)

insert into artnrbl (artikel_nr, besla_nr, artikel_nr_bliefer)
select pzn, hnr, artnr from TH

---------------------------------------------------------------------------------------------------------------



select * from artnrbl where artikel_nr_bliefer = '384862'  besla_nr = 408 artikel_nr = 4784814


select distinct hersteller_nr from zartikel where hersteller_nr > 0 and hersteller_nr not in (select besla_nr from bliefer)


------------------------------
-- AT 
create temp table TH (pzn integer, artnr char(30), hnr integer );
create unique index i_TH on TH (pzn, hnr)

drop table th


load from 'C:\temp\at\artnrbl_1057.csv' delimiter ';'
insert into TH

select * from TH

unload to 'C:\temp\at\artnrbl_1057.txt'
select * from artnrbl where artikel_nr in (select pzn from TH where artnrbl.besla_nr = hnr)

delete from artnrbl where artikel_nr in (select pzn from TH where artnrbl.besla_nr = hnr)


insert into artnrbl (artikel_nr, besla_nr, artikel_nr_bliefer)
select pzn, hnr, artnr from TH

