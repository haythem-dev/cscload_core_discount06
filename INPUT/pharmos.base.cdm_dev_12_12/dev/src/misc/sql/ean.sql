create temp table th(pzn integer, ean char(15)); 
create unique index i_th on th (pzn); 

load from 'D:\temp\at\ean.csv' delimiter ';' 
insert into th 

//-- bestehende Einträge für PZN´s ändern
select * from ean where artikel_nr in (select pzn from th) and ean_nr != (select ean from th where pzn = ean.artikel_nr) 
update ean set ean_nr = (select ean from th where pzn = ean.artikel_nr) where artikel_nr in (select pzn from th) 

//-- bestehende EAN´s für andere PZN´s löschen
select * from ean where ean_nr in (select ean from th) and artikel_nr != (select pzn from th where ean = ean.ean_nr) 

insert into zpznpflege (artikel_nr, datum, dezap_sa) 
select artikel_nr, '20120828', '09'  from ean where ean_nr in (select ean from th) and artikel_nr != (select pzn from th where ean = ean.ean_nr) 

delete from ean where ean_nr in (select ean from th) and artikel_nr != (select pzn from th where ean = ean.ean_nr) 


//-- neue EAN´s laden
insert into ean (artikel_nr, ean_nr) 
select pzn, ean from th where pzn not in (select artikel_nr from ean) 


insert into zpznpflege (artikel_nr, datum, dezap_sa) 
select pzn, '20120828', '09' from th
