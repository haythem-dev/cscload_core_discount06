--> LÖSCHEN FALSCHEINGABEN:
select * from cdiscount where pharmacygroupid in ('511') and datefrom =  20120601 order by articleno

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select distinct articleno, cast(to_char(current, '%Y%m%d') as integer) , '28' from cdiscount where pharmacygroupid in ('511') and datefrom =  20120601 and articleno > 0 and articleno not in (select artikel_nr from zpznpflege where datum = cast(to_char(current, '%Y%m%d') as integer)  and  dezap_sa = '28')

select "0000"||to_char(discountgrpno) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno < 10 and discountgrpno > 0 and 0000||to_char(discountgrpno) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('511') and datefrom =  20120601
union
select "000"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 10 and discountgrpno < 100 and 000||to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('511') and datefrom =  20120601
union
select "00"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 100 and discountgrpno < 1000 and 00||to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('511') and datefrom =  20120601
union
select "0"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 1000 and discountgrpno < 10000 and 0||to_char(discountgrpno) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))  and pharmacygroupid in ('511') and datefrom =  20120601
union
select to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 10000 and to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('511') and datefrom =  20120601
into temp th1

select * from th1

insert into zgrppflege
select * from th1 where x not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))


select "0000"||to_char(manufacturerno) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno < 10 and manufacturerno > 0 and 0000||to_char(manufacturerno) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and  pharmacygroupid in ('511') and datefrom =  20120601 
union
select "000"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 10 and manufacturerno < 100 and 000||to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and  pharmacygroupid in ('511') and datefrom =  20120601
union
select "00"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 100 and manufacturerno < 1000 and 00||to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and  pharmacygroupid in ('511') and datefrom =  20120601
union
select "0"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 1000 and manufacturerno < 10000 and 0||to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and  pharmacygroupid in ('511') and datefrom =  20120601
union
select to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 10000 and to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and  pharmacygroupid in ('511') and datefrom =  20120601
into temp th2

select * from th2

insert into zgrppflege
select * from th2 where x not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))

delete from cdiscount where pharmacygroupid in ('511') and datefrom =  20120601

--------------------------------------------------------------------------------------------------------------------------------------------



select * from cdiscount where pharmacygroupid in ('510') and dateto  > 20120611 order by articleno


select * from zgrppflege where key_gruppe = '00629'


create temp table raab3 (
pzn integer,
--grp integer,
man integer,
basis integer,
datvon integer,
datbis integer,
target smallint,
pct decimal(5,2)
);


create unique index i_raab3 on raab3 (
pzn,
--grp,
man, 
basis, 
datvon, datbis, target);


load from 'D:\temp\rs\NEW_DISCOUNTS_009.txt'
delimiter '|'
insert into raab3;

delete from raab3

select * from raab3 order by 
pzn
grp
man

select * from cdiscount where pharmacygroupid = '035' 
--and articleno in (select pzn from raab3) and articleno > 0
-- and manufacturerno in (select man from raab3) 
-- and discountgrpno in (select grp from raab3) 
and dateto > 20120330 order by articleno



---------------------------------------------------------------------------------------------------------------------

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select distinct articleno, cast(to_char(current, '%Y%m%d') as integer) , '28' from cdiscount where pharmacygroupid in ('510') and dateto  > 20120611 and articleno > 0 and articleno not in (select artikel_nr from zpznpflege where datum = cast(to_char(current, '%Y%m%d') as integer)  and  dezap_sa = '28')


select "0000"||to_char(discountgrpno) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno < 10 and discountgrpno > 0 and 0000||to_char(discountgrpno) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
union
select "000"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 10 and discountgrpno < 100 and 000||to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
union
select "00"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 100 and discountgrpno < 1000 and 00||to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
union
select "0"||to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 1000 and discountgrpno < 10000 and 0||to_char(discountgrpno) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))  and pharmacygroupid in ('510') and dateto  > 20120611
union
select to_char(discountgrpno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from cdiscount where discountgrpno >= 10000 and to_char(discountgrpno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
into temp th1

select * from th1

insert into zgrppflege
select * from th1 where x not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))


select "0000"||to_char(manufacturerno) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno < 10 and manufacturerno > 0 and 0000||to_char(manufacturerno) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
union
select "000"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 10 and manufacturerno < 100 and 000||to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
union
select "00"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 100 and manufacturerno < 1000 and 00||to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
union
select "0"||to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 1000 and manufacturerno < 10000 and 0||to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
union
select to_char(manufacturerno) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from cdiscount where manufacturerno >= 10000 and to_char(manufacturerno ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer)) and pharmacygroupid in ('510') and dateto  > 20120611
into temp th2

select * from th2

insert into zgrppflege
select * from th2 where x not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))

////////////////
check, dass dadurch alle rabatte beendet werden !!!
////////////////
update cdiscount set dateto = 20120611 where pharmacygroupid in ('510') and dateto  > 20120611
--update cdiscount set dateto = 20120331 where pharmacygroupid = '515' and manufacturerno in (select man from raab3)  and dateto > 20120331  
--update cdiscount set dateto = 20120331 where pharmacygroupid = '515' and discountgrpno in (select grp from raab3)  and dateto > 20120331  

---------------------------------------------------------------------------------------------------------------------


insert into cdiscount (pharmacygroupid, baseqty, datefrom, dateto, paymenttargetno, discountvaluepct, 
articleno, 
manufacturerno,
--discountgrpno,
fixedprice, 
pharmgrpexcluded, internaldiscount, monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty, addondiscountok, paymenttermtype, turnovercalcimpact, addondiscount )
select '009', 
basis, 
datvon, datbis, target, pct, 
pzn,
man,
--grp,
0,
'000', '0', '0', '000', '000', '0', '0' , '0' , '0' , '0'  from raab3 

---------------------------------------------------------------------------------------------------------------------

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select distinct pzn, cast(to_char(current, '%Y%m%d') as integer), '28' from raab3 where pzn not in (select artikel_nr from zpznpflege where datum = cast(to_char(current, '%Y%m%d') as integer) and  dezap_sa = '28') and pzn > 0


---------------------------------------------------------------------------------------------------------------------

select "0000"||to_char(grp) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from raab3 where grp < 10 and grp > 0 and 0000||to_char(grp) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "000"||to_char(grp) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from raab3 where grp >= 10 and grp < 100 and 000||to_char(grp ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "00"||to_char(grp) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from raab3 where grp >= 100 and grp < 1000 and 00||to_char(grp ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "0"||to_char(grp) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from raab3 where grp >= 1000 and grp < 10000 and 0||to_char(grp ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select to_char(grp) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2A' as z from raab3 where grp >= 10000 and to_char(grp ) not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))
into temp raab2


select * from raab2

insert into zgrppflege
select * from raab2 where x not in (select key_gruppe from zgrppflege where dezap_sa = '2A' and datum = cast(to_char(current, '%Y%m%d') as integer))



---------------------------------------------------------------------------------------------------------------------

select "0000"||to_char(man) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab3 where man < 10 and man > 0 and 0000||to_char(man) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "000"||to_char(man) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab3 where man >= 10 and man < 100 and 000||to_char(man ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "00"||to_char(man) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab3 where man >= 100 and man < 1000 and 00||to_char(man ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select "0"||to_char(man) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab3 where man >= 1000 and man < 10000 and 0||to_char(man ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
union
select to_char(man) as x, cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab3 where man >= 10000 and to_char(man ) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
into temp raab1


select * from raab1

insert into zgrppflege
select * from raab1 where x not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))

---------------------------------------------------------------------------------------------------------------------

unload to 'C:\temp\rs\rabatte_zu_beenden.txt'
select * from cdiscount 
where datefrom <= 20121102 and dateto > 20121102
and discountgrpno >= 2000 and discountgrpno <= 2113
and pharmacygroupid = '501' 

update cdiscount set dateto = 20121103 
where datefrom <= 20121102 and dateto > 20121102
and discountgrpno >= 2000 and discountgrpno <= 2113
and pharmacygroupid = '501' 

insert into zgrppflege 
--values ('05034', cast(to_char(current, '%Y%m%d') as integer), '2A');
select distinct  '0' || discountgrpno, cast(to_char(current, '%Y%m%d') as integer), '2A' from cdiscount 
where datefrom <= 20121102 and dateto > 20121102
and discountgrpno >= 2000 and discountgrpno <= 2113
and pharmacygroupid = '501' 

