create temp table raab_discgrp (
rgr integer,
name char(30),
type smallint,
pzn integer
);

drop table raab_discgrp
delete from raab_discgrp

create unique index i_raab_discgrp  on raab_discgrp (rgr, pzn);

load from 'h:\Pharmos-Länder\Serbien\Schnittstellen\091026\cdiscgrp_rs.txt'
delimiter ';'
insert into raab_discgrp 

select count(*) from raab_discgrp
select * from raab_discgrp  order by rgr
delete from raab_discgrp 
select * from cpharmgrp
delete from cpharmgrp

select distinct rgr, name, type, pzn from raab_discgrp into temp raab_discgrp2
create unique index i_raab_discgrp2  on raab_discgrp2 (rgr, pzn);
select count(*) from raab_discgrp2

select pzn from raab_discgrp where pzn not in (select artikel_nr from zartikel) order by pzn

delete from cdiscgrp

insert into cdiscgrp (discountgrpno, description, discountgrptype)
select distinct rgr, name, type from raab_discgrp

delete from cdiscgrpmem

insert into cdiscgrpmem (discountgrpno, articleno)
select rgr, pzn from raab_discgrp

select * from cdiscgrp;
select * from cdiscgrpmem;

