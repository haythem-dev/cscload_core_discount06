create temp table raab_discount (
pzn integer,
rgr integer, 
hnr integer,
cat integer,
zahlungsziel smallint,
basismenge integer,
datvon integer,
datbis integer,
rabatt decimal (5,2),
natra integer,
egr char(3)
);

delete from raab_discount
drop table raab_discount

load from 'H:\Pharmos-länder\serbien\schnittstellen\091026\cdiscount_rs.txt'
delimiter ';'
insert into raab_discount;

select * from raab_discount order by pzn, rgr;
select * from cdiscount

delete from cdiscount

insert into cdiscount (articleno, discountgrpno, manufacturerno, artcategoryno, pharmacygroupid, baseqty, datefrom,
dateto, paymenttargetno, discountvaluepct, discountqty)
select pzn, rgr, hnr, cat, egr, basismenge, datvon, datbis, zahlungsziel, rabatt, natra from raab_discount 

-- Test, ob Rabattgruppen in den Rabatten plausibel sind
select discountgrpno from cdiscount where discountgrpno != " " and discountgrpno not in (select discountgrpno from cdiscgrp)

-- Test, ob Einkaufsgruppen in den Rabatten plausibel sind
select pharmacygroupid from cdiscount where pharmacygroupid != " " and pharmacygroupid not in (select pharmacygroupid from cpharmgrp)