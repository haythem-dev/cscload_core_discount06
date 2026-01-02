select * from zpznpflege where dezap_sa = '28' and datum = 20090212 and artikel_nr not in (select articleno from cdiscount where datefrom = 20090213)

delete from cdiscount where datefrom =  20090213 and articleno in (3593549, 3593532)
select * from cdiscount where datefrom =  20090213 and articleno in (3593549, 3593532)

create temp table th_pzn_rab (artno integer )

load from 'D:\prj\zdp\000_5_10_xxx_2030.csv'
insert into th_pzn_rab

insert into cdiscount (articleno, pharmacygroupid, baseqty, datefrom, dateto, discountvaluepct, refundpct,
pharmgrpexcluded, internaldiscount, monthlydiscount, pharmgrpexcl_2, pharmgrpexcl_3, no_multiple_qty) 
select artno, '000', 25, 20090213, 20301231, 25, 100,
'000', '0', '0', '000', '000', '0' from th_pzn_rab

insert into zpznpflege (artikel_nr, datum, dezap_sa)
select artno, 20090212, '28' from th_pzn_rab where artno not in (select artikel_nr from zpznpflege where dezap_sa = '28' and datum = 20090212)

drop table th_pzn_rab



select * from cdiscount where articleno = 3669152

select count(*) from cdiscount where refundpct != 100

update cdiscount set dateto = 20090212
--select * from cdiscount 
where articleno in (select artno from th_pzn_rab) and dateto = 20301231 and pharmacygroupid = '000'