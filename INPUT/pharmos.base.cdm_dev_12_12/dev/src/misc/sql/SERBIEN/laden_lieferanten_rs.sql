create temp table raab_supplier (
lant_nr integer,
name char(30),
plz_strasse char(7),
ort char(30),
strasse char(30),
telefon char(15),
landeskuerzel char(3),
sap_lantnr char(5)
);

create unique index i_raab_supplier on raab_supplier (lant_nr);

load from 'h:\Pharmos-Länder\Serbien\Schnittstellen\091014_1\supplier_rs.txt'
delimiter ';'
insert into raab_supplier

drop table raab_supplier
select * from raab_supplier order by lant_nr
delete from raab_supplier
select * from liefer order by lant_nr
select * from bliefer order by besla_nr
select lant_nr, sap_lantnr, sap_lantneu from liefer
delete from liefer where lant_nr = 1
select lant_nr, landeskuerzel from liefer
select * from zliefsapr3

update raab_supplier set plz_strasse = " " where plz_strasse IS NULL;
update raab_supplier set ort = " " where ort IS NULL;
update raab_supplier set strasse = " " where strasse IS NULL;
update raab_supplier set telefon = " " where telefon IS NULL;
update raab_supplier set landeskuerzel = " " where landeskuerzel IS NULL;

-- liefer
update liefer set 
lant_name = (select name from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr),
lant_mc = (select name from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr),
plz_strasse = (select plz_strasse from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr),
ort = (select ort from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr),
strasse = (select strasse from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr),
telefon = (select telefon from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr),
landeskuerzel = (select landeskuerzel from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr),
sap_lantnr = (select sap_lantnr from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr),
sap_lantneu = (select "381"||sap_lantnr from raab_supplier where raab_supplier.lant_nr = liefer.lant_nr)
where lant_nr in (select lant_nr from raab_supplier)

insert into liefer (lant_nr, lant_name, lant_mc, plz_strasse, ort, strasse, telefon, landeskuerzel, sap_lantnr, sap_lantneu, arzneimittelbezug) 
select lant_nr, name, name, plz_strasse, ort, strasse, telefon, landeskuerzel, sap_lantnr, "381"||sap_lantnr, 'K' from raab_supplier
where lant_nr not in (select lant_nr from liefer)

delete from liefer where lant_nr not in (select r.lant_nr from raab_supplier r)

-- zliefsapr3
delete from zliefsapr3

insert into zliefsapr3 (lant_nr, delcredere_art, datumgueltigab, delcredere_nr) 
select lant_nr, 1, 20010101, "381"||sap_lantnr from raab_supplier
where lant_nr not in (select lant_nr from zliefsapr3)

-- bliefer
update bliefer set 
lant_nr = (select lant_nr from raab_supplier where raab_supplier.lant_nr = bliefer.besla_nr),
besla_name = (select name from raab_supplier where raab_supplier.lant_nr = bliefer.besla_nr),
besla_mc = (select name from raab_supplier where raab_supplier.lant_nr = bliefer.besla_nr),
plz_strasse = (select plz_strasse from raab_supplier where raab_supplier.lant_nr = bliefer.besla_nr),
ort = (select ort from raab_supplier where raab_supplier.lant_nr = bliefer.besla_nr),
strasse = (select strasse from raab_supplier where raab_supplier.lant_nr = bliefer.besla_nr),
telefon = (select telefon from raab_supplier where raab_supplier.lant_nr = bliefer.besla_nr),
landeskuerzel = (select landeskuerzel from raab_supplier where raab_supplier.lant_nr = bliefer.besla_nr)
where besla_nr in (select lant_nr from raab_supplier)

insert into bliefer (besla_nr, lant_nr, besla_name, besla_mc, plz_strasse, ort, strasse, telefon, landeskuerzel) 
select lant_nr, lant_nr, name, name, plz_strasse, ort, strasse, telefon, landeskuerzel from raab_supplier
where lant_nr not in (select besla_nr from bliefer)

delete from bliefer where besla_nr not in (select r.lant_nr from raab_supplier r)

-- nummerek
select max(lant_nr) from liefer

update nummerek set nr = (select max(lant_nr) + 1 from liefer) where nr_art = 'NEWLNR';
update nummerek set nr = (select max(lant_nr) + 1 from liefer) where nr_art = 'NEWBNR'

select * from nummerek


