select * from zartfrance


create temp table th (code char(20), rembtype char(1), rembpct integer, base decimal (7,2), rembval decimal (7,2));


--load from 'C:\temp\fr\ChargementCREATIONTTFR2016.csv' delimiter ';'
load from 'C:\temp\fr\ChargementMODIFICATIONTFR2016.csv' delimiter ';'
insert into th

unload to 'C:\temp\fr\tfr_refund_codes_doubled.txt'
select code, count(*) from th group by 1 order by 2 desc

delete from th
create unique index i_th on th (code);

select * from th where rembtype != 1;
select * from th where rembpct  < 0 or rembpct > 5;
select * from th where code not in (select article_code from carticlecodes where code_type in (select code_type from ccodetypes where artnr_substitute = 1))


select articleno, rembtype, rembpct, base, rembval from carticlecodes, th where code_type in (select code_type from ccodetypes where artnr_substitute = 1) and article_code = code
into temp th2;
create unique index i_th2 on th2 (articleno);

select * from th2 where articleno not in (select articleno from zartfrance);
select * from th2 where articleno not in (select articleno from cartrefundfrance)

update zartfrance set 
REIMBURSEMENT_TYPE = 1, 
REIMBURSEMENT_PERC = (select rembpct from th2 where articleno = zartfrance.articleno)  , 
REIMBURSEMENT_VAL = (select rembval from th2 where articleno = zartfrance.articleno), 
TFR_BASE_PRICE = (select base from th2 where articleno = zartfrance.articleno), 
CODE_LPPR = '' 
where articleno in (select articleno from th2)


insert into cartrefundfrance (ARTICLENO, DATEFROM, REIMBURSEMENT_PERC, REIMBURSEMENT_VAL, REIMBURSEMENT_TYPE,  CODE_LPPR, TFR_BASE_PRICE)
select articleno, '20160221', rembpct , rembval, '1', '', base from th2


insert into zapflege (artikel_nr, datum)
select articleno, '20160113' from th2 where articleno not in (select artikel_nr from zapflege where datum = 20160113)


select * from cartrefundfrance where articleno in (select articleno from th2)
unload to 'C:\temp\zartfrance_20160113.txt'
select * from zartfrance where articleno in (select articleno from th2)



