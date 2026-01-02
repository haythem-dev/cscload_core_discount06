create temp table raab_article (
--artikel_aktiv char(1),
--key_alt_1 integer,
--key_alt_2 integer,
artikel_nr integer,
artikel_name char(30),
einheit char(9),
darreichform char(3),
herstelller_nr integer,
ve1 integer,
chargenartikel char(1),
positivliste char(1),
warnung_vor_verfall integer,
mwst char(1),
zollnummer char(10),
ean char(13),
laenge integer,
breite integer,
hoehe integer,
gewicht integer,
gep decimal(15,8),
aep decimal(9,2),
artikel_typ smallint,
zertifikat smallint,
btm char(1),
rezeptpfl char(1),
apothekenpfl char(1),
kuehlartikel char(1)
);

create unique index i_raab_article on raab_article (artikel_nr);
--create unique index i_raab_article on raab_article (artikel_nr, barcode_typ);

drop table raab_article
delete from raab_article

load from 'D:\temp\rs\article_rs.txt'
delimiter ';'
insert into raab_article

select * from raab_article
select artikel_nr, mwst from raab_article
select count(*) from raab_article where zertifikat = 1 and chargenartikel != 1
select count(*) from raab_article where chargenartikel = 1
delete from zartikel
select * from zartikel where btm = '1'
select first 10 * from zartserbia
select first 10 * from zartikel

-- zartikel
update raab_article set einheit = " " where einheit is NULL;
update raab_article set darreichform = " " where darreichform is NULL

update zartikel set 
artikel_mc = (select substr(artikel_name, 1, 12) from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
artikel_name = (select artikel_name from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
einheit = (select einheit from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
darreichform = (select darreichform from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
hersteller_nr = (select herstelller_nr from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
chargenartikel = (select chargenartikel from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
verfall = (select chargenartikel from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
warntagevorverf = (select warnung_vor_verfall from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
laenge = (select laenge from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
hoehe = (select hoehe from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
breite = (select breite from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
gewicht = (select gewicht from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
btm = (select btm from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
rezeptpfl = (select rezeptpfl from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
apothekenpfl = (select apothekenpfl from raab_article where raab_article.artikel_nr = zartikel.artikel_nr),
kuehlartikel = (select kuehlartikel from raab_article where raab_article.artikel_nr = zartikel.artikel_nr)
where artikel_nr in (select artikel_nr from raab_article)

insert into zartikel (artikel_nr, artikel_mc, artikel_name, einheit, darreichform, hersteller_nr, chargenartikel, verfall, warntagevorverf, laenge, breite, hoehe, gewicht, btm, rezeptpfl, apothekenpfl, kuehlartikel, bestandsbuchung) 
select artikel_nr, substr(artikel_name, 1, 12), artikel_name, einheit, darreichform, herstelller_nr, chargenartikel, chargenartikel, warnung_vor_verfall, laenge, breite, hoehe, gewicht, btm, rezeptpfl, apothekenpfl, kuehlartikel, '1' from raab_article where artikel_nr not in (select artikel_nr from zartikel)

-- Korrektur Hersteller
select * from zartikel where hersteller_nr = 0
update zartikel set hersteller_nr = 829 where hersteller_nr = 0

-- delete from zartikel where artikel_nr not in (select r.artikel_nr from raab_article r)
update zartikel set artikel_geloescht = '1' where artikel_nr not in (select r.artikel_nr from raab_article r)

-- zapflege
insert into zapflege
select artikel_nr, cast(to_char(current, '%Y%m%d') as integer) from zartikel where
artikel_nr not in (select artikel_nr from zapflege where datum = cast(to_char(current, '%Y%m%d') as integer))

-- zartserbia
update raab_article set zollnummer = " " where zollnummer is NULL

update zartserbia set 
articletype = (select artikel_typ from raab_article where raab_article.artikel_nr = zartserbia.articleno),
customsno = (select zollnummer from raab_article where raab_article.artikel_nr = zartserbia.articleno),
refundtype = (select positivliste from raab_article where raab_article.artikel_nr = zartserbia.articleno),
certificateflag = (select zertifikat from raab_article where raab_article.artikel_nr = zartserbia.articleno),
pack_size = (select ve1 from raab_article where raab_article.artikel_nr = zartserbia.articleno)
where articleno in (select artikel_nr from raab_article)

insert into zartserbia (articleno, articletype, customsno, refundtype, certificateflag)
select artikel_nr, artikel_typ, zollnummer, positivliste, zertifikat from raab_article where artikel_nr not in (select articleno from zartserbia)

-- delete from zartserbia where articleno not in (select r.artikel_nr from raab_article r)

-- ean
select ean, count(*) as anz from raab_article group by ean order by anz desc

delete from ean

insert into ean (artikel_nr, ean_nr) 
select min(artikel_nr), ean from raab_article where ean is not null group by ean 
--select artikel_nr, ean from raab_article where ean is not null

-- zartpreis
-- delete from zartpreis where datumgueltigab = 20090921

insert into zartpreis (artikel_nr, datumgueltigab, grosso, aep, ke_mwst)
select artikel_nr, cast(to_char(current, '%Y%m%d') as integer), round(gep, 2), aep, (CASE mwst WHEN '1' THEN '0' ELSE '1' END) from raab_article

select * from zartpreis where datumgueltigab = 20091008 and grosso > aep

-- nummerek
select max(artikel_nr) from zartikel
update nummerek set nr = 141976 where nr_art = 'NEWPZN'

/* ab hier vorerst nicht nötig */
update raab_article set x04 = " " where x04 IS NULL

delete from zartwg

insert into zartwg (artikel_nr, art, warengruppe) 
select artikel_nr, "B", x04 from raab_article where x04 != " "

insert into zartwg (artikel_nr, art, warengruppe) 
select artikel_nr, "4", x11 from raab_article where x11 != " "

insert into zartwg (artikel_nr, art, warengruppe) 
select artikel_nr, "2", x12 from raab_article where x12 != " "
