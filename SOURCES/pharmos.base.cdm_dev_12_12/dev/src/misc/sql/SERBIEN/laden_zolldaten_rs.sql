create temp table raab_customs (
zollnummer char(10),
gebuehr decimal(5,2),
text char(254)
);

drop table raab_customs
delete from raab_customs

create unique index i_raab_customs  on raab_customs (zollnummer);

load from 'h:\Pharmos-Länder\Serbien\Schnittstellen\091008\customs_rs.txt'
delimiter '#'
insert into raab_customs 

select * from raab_customs  order by zollnummer
delete from raab_customs 

delete from ccustomsregulation

insert into ccustomsregulation (customsno, customs_pct, description) 
select zollnummer, gebuehr, text from raab_customs 

select * from ccustomsregulation 

-- Test, ob Zollnummern im Artikelstamm plausibel sind
select customsno from zartserbia where customsno != " " and customsno not in (select customsno from ccustomsregulation)
