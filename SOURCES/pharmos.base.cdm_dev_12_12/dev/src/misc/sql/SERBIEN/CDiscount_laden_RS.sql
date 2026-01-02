select * from cdiscount where pharmacygroupid = '513' and dateto > 20111030 and (articleno = 0 and manufacturerno = 0)

select * from cdiscount where pharmacygroupid = '513' and dateto > 20111030 and (articleno != 0 or manufacturerno != 0)

select * from cdiscount where pharmacygroupid = '513' and dateto > 20111030 and articleno != 0;
select * from cdiscount where pharmacygroupid = '513' and dateto > 20111030 and manufacturerno != 0;


unload to 'D:\temp\rs\cdiscount_513.txt'
select * from cdiscount where pharmacygroupid = '525' and dateto > 20111122


update cdiscount set dateto = 20111031 where pharmacygroupid = '513' and dateto > 20111030

-----------------------------------------------------
insert into zpznpflege
select distinct articleno, cast(to_char(current, '%Y%m%d') as integer), '28' from cdiscount
where articleno not in 
(select artikel_nr from zpznpflege where datum = cast(to_char(current, '%Y%m%d') as integer) and dezap_sa = '28')
and pharmacygroupid = '513' and dateto > 20111030 and articleno != 0;

-----------------------------------------------------

select "0000"||to_char(artcategoryno) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2C' as z from cdiscount where artcategoryno < 10 and 0000||to_char(artcategoryno) not in (select key_gruppe from zgrppflege where dezap_sa = '2C' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and artcategoryno > 0 and dateto > 20111030
union
select "000"||to_char(artcategoryno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2C' as z from cdiscount where artcategoryno >= 10 and artcategoryno < 100 and 000||to_char(artcategoryno) not in (select key_gruppe from zgrppflege where dezap_sa = '2C' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and artcategoryno > 0 and dateto > 20111030
union
select "00"||to_char(artcategoryno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2C' as z from cdiscount where artcategoryno >= 100 and artcategoryno < 1000 and 00||to_char(artcategoryno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2C' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and artcategoryno > 0 and dateto > 20111030
union
select "0"||to_char(artcategoryno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2C' as z from cdiscount where artcategoryno >= 1000 and artcategoryno < 10000 and 0||to_char(artcategoryno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2C' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513'  and artcategoryno > 0 and dateto > 20111030
union
select to_char(artcategoryno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2C' as z from cdiscount where artcategoryno >= 10000 and to_char(artcategoryno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2C' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and artcategoryno > 0 and dateto > 20111030
into temp TH1

insert into zgrppflege (key_gruppe, datum, dezap_sa ) 
select * from TH1

-----------------------------------------------------

select "0000"||to_char(discountgrpno) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno < 10 and 0000||to_char(discountgrpno) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and discountgrpno > 0 and dateto > 20111030
union
select "000"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 10 and discountgrpno < 100 and 000||to_char(discountgrpno) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and discountgrpno > 0 and dateto > 20111030
union
select "00"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 100 and discountgrpno < 1000 and 00||to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and discountgrpno > 0 and dateto > 20111030
union
select "0"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 1000 and discountgrpno < 10000 and 0||to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513'  and discountgrpno > 0 and dateto > 20111030
union
select to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 10000 and to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and discountgrpno > 0 and dateto > 20111030
into temp TH2

insert into zgrppflege (key_gruppe, datum, dezap_sa ) 
select * from TH2

-----------------------------------------------------

select "0000"||to_char(manufacturerno) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno < 10 and 0000||to_char(manufacturerno) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and manufacturerno > 0 and dateto > 20111030
union
select "000"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 10 and manufacturerno < 100 and 000||to_char(manufacturerno) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and manufacturerno > 0 and dateto > 20111030
union
select "00"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 100 and manufacturerno < 1000 and 00||to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and manufacturerno > 0 and dateto > 20111030
union
select "0"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 1000 and manufacturerno < 10000 and 0||to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513'  and manufacturerno > 0 and dateto > 20111030
union
select to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 10000 and to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid = '513' and manufacturerno > 0 and dateto > 20111030
into temp TH3

insert into zgrppflege (key_gruppe, datum, dezap_sa ) 
select * from TH3

-----------------------------------------------------

select * from zgrppflege where datum = 20111028;
select * from zpznpflege where datum = 20111028




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
create temp table raab3 (
pzn integer,
basis integer,
datvon integer,
datbis integer,
target smallint,
pct decimal(5,2)
);

create unique index i_raab3 on raab3 (pzn, 
basis, 
datvon, datbis, target);

delete from raab3
drop table raab3

load from 'D:\temp\rs\AU_SABAC_NEW_Discounts_18.11.11.txt'
delimiter '|'
insert into raab3;

select * from raab3 order by pzn

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select distinct pzn, '20111121', '28' from raab3 where pzn not in (select artikel_nr from zpznpflege where datum = 20111121 and  dezap_sa = '28')

insert into cdiscount (pharmacygroupid, baseqty, datefrom, dateto, paymenttargetno, discountvaluepct, articleno, 
fixedprice, 
pharmgrpexcluded, internaldiscount, monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty, addondiscountok, paymenttermtype, turnovercalcimpact, addondiscount )
select '525', 
basis, 
datvon, datbis, target, pct, pzn, 0, 
'000', '0', '0', '000', '000', '0', '0' , '0' , '0' , '0'  from raab3 



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
create temp table raab4 (
man integer,
basis integer,
datvon integer,
datbis integer,
target smallint,
pct decimal(5,2)
);

create unique index i_raab4 on raab4 (man, 
basis, 
datvon, datbis, target);

delete from raab4
drop table raab4

load from 'D:\temp\rs\513_supplier_level.txt'
delimiter '|'
insert into raab4;

select * from raab4 order by man


insert into cdiscount (pharmacygroupid, baseqty, datefrom, dateto, paymenttargetno, discountvaluepct, manufacturerno, 
fixedprice, 
pharmgrpexcluded, internaldiscount, monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty, addondiscountok, paymenttermtype, turnovercalcimpact, addondiscount )
select '513', 
basis, 
datvon, datbis, target, pct, man, 0, 
'000', '0', '0', '000', '000', '0', '0' , '0' , '0' , '0'  from raab4



select "0000"||to_char(man) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab4 where man < 10 and 0000||to_char(man) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "000"||to_char(man) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab4 where man >= 10 and man < 100 and 000||to_char(man ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "00"||to_char(man) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab4 where man >= 100 and man < 1000 and 00||to_char(man ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "0"||to_char(man) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab4 where man >= 1000 and man < 10000 and 0||to_char(man ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select to_char(man) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab4 where man >= 10000 and to_char(man ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
into temp TH4


select * from TH4

insert into zgrppflege (key_gruppe, datum, dezap_sa) 
select * from TH4 where x not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))