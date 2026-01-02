


create temp table TH (grp integer);
create unique index i_TH on TH (grp);

load from 'D:\temp\rs\cdiscgrps.csv'
insert into TH

unload to 'D:\temp\rs\discgrpmem.txt' delimiter ';'
select discountgrpno, articleno from cdiscgrpmem where discountgrpno in (select grp from TH) order by 1, 2