create temp table th (pzn integer, code char(25));
create unique index i_TH on th (pzn);

load from 'C:\temp\lohmann-intrastat.csv' delimiter ';'
insert into th

select * from th where pzn not in (select artikel_nr from zartikel);
select * from carticlecodes where article_code in (select cast (pzn as char(8)) from th where pzn not in (select artikel_nr from zartikel))

delete from carticlecodes where code_type = 6 and articleno in (select pzn from th)
delete from th where pzn is null

insert into carticlecodes (articleno, code_type, article_code, date_changed)
select pzn, '6', code, '20141126' from th 

insert into zapflege 
select pzn, '20141126' from th where pzn not in
(select artikel_nr from zapflege where datum = 20141126)