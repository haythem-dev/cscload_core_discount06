create temp table raab_pharmgrp (
egr char(3),
name char(30)
);

drop table raab_pharmgrp
delete from raab_pharmgrp

create unique index i_raab_pharmgrp  on raab_pharmgrp (egr);

load from 'h:\Pharmos-Länder\Serbien\Schnittstellen\091026\cpharmgrp_rs.txt'
delimiter ';'
insert into raab_pharmgrp 

select * from raab_pharmgrp  order by egr
delete from raab_pharmgrp 
select * from cpharmgrp

delete from cpharmgrp

insert into cpharmgrp (pharmacygroupid, group_name)
select egr, name from raab_pharmgrp 

select * from cpharmgrp

