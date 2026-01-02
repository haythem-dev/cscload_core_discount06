create temp table TH (pzn integer, code char(20), type smallint);

load from 'c:\temp\fr\Codes.csv' delimiter ';'
insert into TH

--> 1 Code zeigt auf mehrere PZN´s
select code, count(code) from th group by code HAVING     (COUNT(code) > 1 AND count(distinct pzn) > 1) 
-- delete from th where code in ('3700366000047', '3288131500010', '4015400534600')

 --> PZN´s nicht bekannt
select * from carticlecodes, th where article_code = pzn and code_type in (8,9,10,11,12) and articleno != article_code
update th set pzn = (select articleno from carticlecodes where cast(article_code as integer) = th.pzn and code_type = 11 and articleno != article_code) where pzn not in (select artikel_nr from zartikel)
select * from th where pzn not in (select artikel_nr from zartikel)
-- delete from th where pzn not in (select artikel_nr from zartikel)

 --> Sätze bereits vorhanden
select * from th, carticlecodes where code = article_code 
and pzn = articleno 
and type = code_type
-- delete from th where code in (select article_code from carticlecodes where code_type = th.type)

--> Code-Type != GTIN und mehr als 1 Code
select pzn, count(pzn) from th where type != 8 group by 1 order by 2 desc
select * from th, carticlecodes where pzn = articleno and type = code_type and type != 8
-- delete from th where pzn in (select articleno from carticlecodes where th.type = code_type) and type != 8

--> eine andere GTIN für diesen Artikel existiert bereits = serial_number beachten
select * from th, carticlecodes where pzn = articleno and type = code_type  and serial_number != 1 and type = 8

create temp table TH2 (pzn integer, code char(20), type smallint, serialno integer);
create unique index i_th2 on th2 (pzn, type, serialno);
insert into th2 select pzn, code, type, '1' from th where type != 8; --> ACL´s serialno 1
insert into th2 select pzn, code, type, '1' from th where pzn not in (select articleno from carticlecodes where code_type = type) and type = 8 and pzn not in (select pzn from th where type = 8 group by 1 HAVING  COUNT(pzn) > 1 ); --> bisher noch keine GTIN im System + nur 1 GTIN in csv = serialno 1
insert into th2 select pzn, code, type, '2' from th where pzn in (select articleno from carticlecodes where code_type = type group by 1 having max(serial_number) = 1) and type = 8 and pzn in (select pzn from th where type = 8 group by 1 HAVING  COUNT(pzn) = 1 ) and pzn not in (select pzn from th2 where type = 8); --> bislang nur 1 GTIN + 1 GTIN in csv = serialno 2
insert into th2 select pzn, code, type, '3' from th where pzn in (select articleno from carticlecodes where code_type = type group by 1 having max(serial_number) = 2) and type = 8 and pzn in (select pzn from th where type = 8 group by 1 HAVING  COUNT(pzn) = 1 ) and pzn not in (select pzn from th2 where type = 8);
insert into th2 select pzn, code, type, max(serial_number) + 1 from th a, carticlecodes where pzn = articleno and code_type = type and type = 8 and pzn in (select pzn from th where type = 8 group by 1 HAVING  COUNT(pzn) = 2 )  and code = (select max(code) from th where a.pzn = pzn and a.type = type) group by 1, 2, 3;
insert into th2 select pzn, code, type, max(serial_number) + 2 from th a, carticlecodes where pzn = articleno and code_type = type and type = 8 and pzn in (select pzn from th where type = 8 group by 1 HAVING  COUNT(pzn) = 2 )  and code = (select min(code) from th where a.pzn = pzn and a.type = type) group by 1, 2, 3;
insert into th2 select pzn, code, type, max(serial_number) + 1 from th a, carticlecodes where pzn = articleno and code_type = type and type = 8 and pzn in (select pzn from th where type = 8 group by 1 HAVING  COUNT(pzn) = 3 )  and code = (select max(code) from th where a.pzn = pzn and a.type = type) group by 1, 2, 3;
insert into th2 select pzn, code, type, max(serial_number) + 2 from th a, carticlecodes where pzn = articleno and code_type = type and type = 8 and pzn in (select pzn from th where type = 8 group by 1 HAVING  COUNT(pzn) = 3 )  and code = (select min(code) from th where a.pzn = pzn and a.type = type) group by 1, 2, 3;
insert into th2 select pzn, code, type, max(serial_number) + 3 from th a, carticlecodes where pzn = articleno and code_type = type and type = 8 and pzn in (select pzn from th where type = 8 group by 1 HAVING  COUNT(pzn) = 3 )  and code not in (select code from th2 where a.pzn = pzn and a.type = type) group by 1, 2, 3;

--> serialno > 1
select pzn, count(pzn) from th where pzn not in (select pzn from th2) and  type = 8 group by 1 

select * from th2 where serialno > 5

select count(*) from th;
select count(*) from th2;

insert into carticlecodes (articleno, code_type, article_code, serial_number, preferred_flag, date_changed)
select pzn, type, code, serialno, '0', cast(to_char(current, '%Y%m%d') as integer)
from th2

insert into zpznpflege
select distinct pzn, cast(to_char(current, '%Y%m%d') as integer), '34'
from th2 where pzn not in (select artikel_nr from zpznpflege where dezap_sa = '34' and datum = cast(to_char(current, '%Y%m%d') as integer))

