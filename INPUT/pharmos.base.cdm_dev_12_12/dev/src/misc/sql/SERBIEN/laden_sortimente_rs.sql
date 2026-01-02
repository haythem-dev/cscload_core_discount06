create temp table raab_article_supplier1 (
artikel_nr integer,
besla_nr integer
);

create unique index i_raab_article_supplier1  on raab_article_supplier1 (artikel_nr, besla_nr);

load from 'h:\Pharmos-Länder\Serbien\Schnittstellen\091014_2\article_supplier_rs.txt'
delimiter ';'
insert into raab_article_supplier1 


delete from bliesort 

insert into bliesort  (artikel_nr, besla_nr) 
select artikel_nr, besla_nr from raab_article_supplier1

select * from bliesort

select * from bliesort where artikel_nr not in (select artikel_nr from zartikel)
select * from bliesort where besla_nr not in (select besla_nr from bliefer)



