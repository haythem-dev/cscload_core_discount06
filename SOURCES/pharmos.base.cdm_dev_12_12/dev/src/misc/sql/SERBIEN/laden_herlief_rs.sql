create temp table raab_manufacturer_supplier1 (
hersteller_nr integer,
lant_nr integer
);

create unique index i_raab_manufacturer_supplier1  on raab_manufacturer_supplier1 (hersteller_nr, lant_nr);

load from 'h:\Pharmos-Länder\Serbien\Schnittstellen\091014_2\manufacturer_supplier_rs.txt'
delimiter ';'
insert into raab_manufacturer_supplier1 

delete from herlief

insert into herlief  (hersteller_nr, lant_nr) 
select hersteller_nr, lant_nr from raab_manufacturer_supplier1

select * from herlief

select * from herlief where hersteller_nr not in (select hersteller_nr from herstel)
select * from herlief where lant_nr not in (select lant_nr from liefer)



