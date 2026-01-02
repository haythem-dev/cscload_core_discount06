create temp table TH (pzn integer, grp_old integer, grp_new integer)

load from 'D:\temp\rs\Discount_group_change.csv' delimiter ';'
insert into TH

select * from TH
delete from TH

create unique index i_TH on TH (pzn)

select pzn, grp_old, grp_new, count(pzn) from TH group by 1, 2, 3 order by 4 desc 


select * from TH where grp_old not in (
select discountgrpno from cdiscgrp )


select * from cdiscgrpmem where articleno in (select pzn from TH where cdiscgrpmem.discountgrpno = grp_old )

unload to 'D:\temp\rs\cdiscgrpmem_28022011.txt'
select * from cdiscgrpmem 



update cdiscgrpmem set discountgrpno = nvl((select grp_new from TH where cdiscgrpmem.discountgrpno = grp_old and cdiscgrpmem.articleno = pzn) , discountgrpno)

insert into zgrppflege (dezap_sa, datum, key_gruppe)
select distinct '31', '20110228', grp_new from TH
where grp_new not in (select key_gruppe from zgrppflege where dezap_sa = '31' and datum = 20110228)