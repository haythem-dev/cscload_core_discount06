create temp table raab_manufacturer (
hersteller_nr integer,
name char(30),
landeskuerzel char(3),
plz char(7),
ort char(30),
strasse char(30),
telefon_nr char(15),
producercode char(5)
);

create unique index i_raab_manufacturer on raab_manufacturer (hersteller_nr);

load from 'D:\temp\rs\manufacturer_rs.txt'
delimiter '#'
insert into raab_manufacturer

select * from raab_manufacturer order by hersteller_nr
delete from raab_manufacturer
select first 10 * from herstel
select producercode, count(*) as anz from raab_manufacturer group by producercode order by anz desc

update raab_manufacturer set landeskuerzel = " " where landeskuerzel IS NULL;
update raab_manufacturer set plz = " " where plz IS NULL;
update raab_manufacturer set ort = " " where ort IS NULL;
update raab_manufacturer set strasse = " " where strasse IS NULL;
update raab_manufacturer set telefon_nr = " " where telefon_nr IS NULL;

update herstel set 
sortiername = (select sortiername from raab_manufacturer where raab_manufacturer.hersteller_nr = herstel.hersteller_nr),
name = (select name from raab_manufacturer where raab_manufacturer.hersteller_nr = herstel.hersteller_nr),
landeskuerzel = (select landeskuerzel from raab_manufacturer where raab_manufacturer.hersteller_nr = herstel.hersteller_nr),
plz = (select plz from raab_manufacturer where raab_manufacturer.hersteller_nr = herstel.hersteller_nr),
ort = (select ort from raab_manufacturer where raab_manufacturer.hersteller_nr = herstel.hersteller_nr),
strasse = (select strasse from raab_manufacturer where raab_manufacturer.hersteller_nr = herstel.hersteller_nr),
telefon_nr = (select telefon_nr from raab_manufacturer where raab_manufacturer.hersteller_nr = herstel.hersteller_nr),
hersteller_code = (select producercode from raab_manufacturer where raab_manufacturer.hersteller_nr = herstel.hersteller_nr)
where hersteller_nr in (select hersteller_nr from raab_manufacturer)

insert into herstel (hersteller_nr, sortiername, name, landeskuerzel, plz, ort, strasse, telefon_nr, hersteller_code) 
select hersteller_nr, name, name, landeskuerzel, plz, ort, strasse, telefon_nr, producercode from raab_manufacturer
where hersteller_nr not in (select hersteller_nr from herstel)

delete from herstel where hersteller_nr not in (select r.hersteller_nr from raab_manufacturer r)

-- Test, ob Herstellernummern im Artikelstamm plausibel sind
select hersteller_nr from zartikel where hersteller_nr > 0 and hersteller_nr not in (select hersteller_nr from herstel)

-- nummerek
select max(hersteller_nr) from herstel

update nummerek set nr = (select max(hersteller_nr) + 1 from herstel) where nr_art = 'NEWHNR'

select * from nummerek

