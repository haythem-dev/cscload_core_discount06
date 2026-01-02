insert into cdiscount (articleno, pharmacygroupid, baseqty, datefrom,
dateto, discountvaluepct, discountqty, pharmgrpexcluded, refundpct, internaldiscount, 
monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty)
select zartwg.artikel_nr, '099', '1', '20090202', '20201231', '15', '0', '000', '0', '0', 
'0', '000', '000', '0' from zartikel, zartwg where zartwg.art = '4' and zartwg.warengruppe = '01MAV' and zartwg.artikel_nr = zartikel.artikel_nr and zartikel.datum_av = 0

create temp table raab2 (
pzn integer,
egr char(3), 
menge1 integer, 
rabatt1 decimal (5,2), 
menge2 integer, 
rabatt2 decimal (5,2), 
datumvon char(10),
datumbis char(10)
);

create unique index i_raab2 on raab2 (pzn, egr);

delete from raab2
drop table raab2

load from 'D:\fuer_unix\rabatte_ch_280509.txt'
delimiter ';'
insert into raab2;

update raab2 set datumvon = '05.05.2009' where datumvon = '01.05.2009'
select * from raab2 order by pzn;
select pzn, cast(substr(datumvon,7,4)||substr(datumvon,4,2)||substr(datumvon,1,2) as integer) from raab2 order by pzn;

insert into cdiscount (articleno, pharmacygroupid, baseqty, datefrom,
dateto, discountvaluepct, discountqty, pharmgrpexcluded, refundpct, internaldiscount, 
monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty)
select pzn, egr, menge1, cast(substr(datumvon,7,4)||substr(datumvon,4,2)||substr(datumvon,1,2) as integer), cast(substr(datumbis,7,4)||substr(datumbis,4,2)||substr(datumbis,1,2) as integer), rabatt1, '0', '000', '0', '0', 
'0', '000', '000', '0' from raab2 

insert into cdiscount (articleno, pharmacygroupid, baseqty, datefrom,
dateto, discountvaluepct, discountqty, pharmgrpexcluded, refundpct, internaldiscount, 
monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty)
select pzn, egr, menge2, cast(substr(datumvon,7,4)||substr(datumvon,4,2)||substr(datumvon,1,2) as integer), cast(substr(datumbis,7,4)||substr(datumbis,4,2)||substr(datumbis,1,2) as integer), rabatt2, '0', '000', '0', '0', 
'0', '000', '000', '0' from raab2 where menge2 is not null

insert into cdiscount (articleno, pharmacygroupid, baseqty, datefrom,
dateto, discountvaluepct, discountqty, pharmgrpexcluded, refundpct, internaldiscount, 
monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty)
select pzn, egr, menge3, cast(substr(datumvon,7,4)||substr(datumvon,4,2)||substr(datumvon,1,2) as integer), cast(substr(datumbis,7,4)||substr(datumbis,4,2)||substr(datumbis,1,2) as integer), rabatt3, '0', '000', '0', '0', 
'0', '000', '000', '0' from raab2 where menge3 is not null

insert into cdiscount (articleno, pharmacygroupid, baseqty, datefrom,
dateto, discountvaluepct, discountqty, pharmgrpexcluded, refundpct, internaldiscount, 
monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty)
select pzn, egr, menge4, 20090401, 20301231, rabatt4, '0', '000', '0', '0', 
'0', '000', '000', '0' from raab2 where menge4 is not null and datumbis = '31.12.1930'

insert into zpznpflege
select distinct zartwg.artikel_nr, cast(to_char(current, '%Y%m%d') as integer), '28' from zartikel, zartwg where zartwg.art = '4' and zartwg.warengruppe = '01MAV' and zartwg.artikel_nr = zartikel.artikel_nr and zartikel.datum_av = 0 
and zartwg.artikel_nr not in (select artikel_nr from zpznpflege where datum = cast(to_char(current, '%Y%m%d') as integer) and dezap_sa = '28')

insert into zpznpflege
select distinct pzn, cast(to_char(current, '%Y%m%d') as integer), '28' from raab2 
where pzn not in 
(select artikel_nr from zpznpflege where datum = cast(to_char(current, '%Y%m%d') as integer) and dezap_sa = '28')

select distinct pharmacygroupid from cdiscount order by pharmacygroupid
select * from cdiscount where pharmacygroupid = '4' order by articleno
update cdiscount set pharmacygroupid = '004' where pharmacygroupid = '4'

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
create temp table raab3 (
pzn integer,
--man integer,
basis integer,
datvon integer,
datbis integer,
--fix   decimal(9,2),
target smallint,
pct decimal(5,2)
);

create unique index i_raab3 on raab3 (
pzn,
--man, 
basis, 
datvon, datbis, target);

delete from raab3
drop table raab3

load from 'D:\temp\rs\AUKG_515_man.txt'
--load from 'D:\temp\rs\AUBG_OTC_NEW.txt'
delimiter '|'
insert into raab3;

select * from raab3 order by man pzn

select * from cdiscount where pharmacygroupid = '515' and articleno in (select pzn from raab3) 
--select * from cdiscount where pharmacygroupid = '515' and manufacturerno in (select man from raab3) 
and dateto >= 20120312 order by articleno

update cdiscount set dateto = 20120311 where pharmacygroupid = '515' and articleno in (select pzn from raab3)  and dateto >= 20120312 
--update cdiscount set dateto = 20120311 where pharmacygroupid = '515' and manufacturerno in (select man from raab3)  and dateto >= 20120312 

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select distinct pzn, '20120312', '28' from raab3 where pzn not in (select artikel_nr from zpznpflege where datum = 20120312 and  dezap_sa = '28')

--select artikel_nr from zpznpflege where dezap_sa = '28' and datum = 20120309 into temp raab2
--update zpznpflege set datum = 20120309 where dezap_sa = '28' and datum = 20120312 and artikel_nr not in (select artikel_nr from raab2)

insert into cdiscount (pharmacygroupid, baseqty, datefrom, dateto, paymenttargetno, discountvaluepct, 
articleno, 
--manufacturerno,
fixedprice, 
pharmgrpexcluded, internaldiscount, monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty, addondiscountok, paymenttermtype, turnovercalcimpact, addondiscount )
select '515', 
basis, 
--'1', 
datvon, datbis, target, pct, 
pzn,
--man,
-- fix, 
0,
'000', '0', '0', '000', '000', '0', '0' , '0' , '0' , '0'  from raab3 
--where man not in (select manufacturerno from cdiscount where datefrom = 20101014)

--> zapflege !?
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

-- insert into cdiscount (articleno, pharmacygroupid, baseqty, datefrom,
-- dateto, discountspec, discountvaluepct, discountqty, surchargepct, pharmgrpexcluded, refundpct, internaldiscount, 
-- monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty)
-- select pzn, egr, menge1, 20090401, 20301231, '1', '0', '0', '0', '000', '6', '0', 
-- '0', '000', '000', '0' from raab3 

unload to 'D:\temp\rs\discount_rs_20101014.txt'
select * from cdiscount where datefrom = 20101014


select * from zgrppflege where dezap_sa = '2B' datum = 20101014


update cdiscount set addondiscountok = 0, paymenttermtype = 0, turnovercalcimpact = 0, addondiscount = 0 where datefrom = 20101014 and addondiscountok != 0

select * from cdiscount where datefrom = 20101014 and addondiscountok != 0
addondiscountok, paymenttermtype, turnovercalcimpact, addondiscount


create temp table TH (dat integer, sa char(2), key char(5)

insert into zgrppflege (datum, dezap_sa, key_gruppe) 

select "0000"||to_char(man) as x , cast(to_char(current, '%Y%m%d') as integer) as y, '2B' as z from raab3 where man < 10 and 0000||to_char(man) not in (select key_gruppe from zgrppflege where dezap_sa = '2B' and datum = cast(to_char(current, '%Y%m%d') as integer))
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
create temp table raab3 (
pzn integer,
datvon integer,
datbis integer,
fix   decimal(9,2)
);

create unique index i_raab3 on raab3 (pzn, datvon, datbis);

delete from raab3
drop table raab3

load from 'D:\temp\rs\AUBG_NEW_PRICES_20_06_11.txt'
delimiter '|'
insert into raab3;

select * from raab3 order by pzn

unload to 'D:\temp\RS\cdiscount_20110619.txt'
select * from cdiscount where pharmacygroupid = '501' and articleno in (select pzn from raab3) 
and dateto >= 20110620 
into temp TH

select * from TH

update TH set fixedprice = (select fix from raab3 where pzn = TH.articleno), datefrom = 20110620

update cdiscount set dateto = 20110619 where pharmacygroupid = '501' and articleno in (select pzn from raab3)  and dateto >= 20110620 

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select distinct pzn, '20110619', '28' from raab3 where pzn not in (select artikel_nr from zpznpflege where datum = 20110619 and  dezap_sa = '28')

insert into cdiscount 
select * from TH


select * from cdiscount where dateto = 20110619;
select * from cdiscount where datefrom = 20110620;
