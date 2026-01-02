select * from zartfrance where articleno = 4264931;
select * from clpprcode where code_lppr in ('2118823', '2105938', '201D012', '01103140');


update zartfrance set code_lppr = '', reimbursement_val = 10.55 where articleno = 4264931;
update clpprcode set reimbursement_val =0, lppr_desc = 'first lppr test descriptions' where code_lppr in ('2118823', '2105938', '201D012',  '01103140', '01103618');

insert into clpprreimb values ('2118823', 20160101, 10);
insert into clpprreimb values ('2118823', 20160901, 9.25);
insert into clpprreimb values ('2118823', 20180101, 8);
insert into clpprreimb values ('2105938', 20160101, 15.71);
insert into clpprreimb values ('201D012', 20180101, 22.40);
insert into clpprreimb values ('01103140', 20160901, 2.96);
insert into clpprreimb values ('01103618', 20160901, 1.30);

insert into clppr2article values ('2118823', 4264931, 20160701, 1);
insert into clppr2article values ('2105938', 4264931, 20161201, 1);
insert into clppr2article values ('201D012', 4264931, 20160701, 1);
insert into clppr2article values ('01103140', 4264931, 20160701, 0);
insert into clppr2article values ('01103618', 4264931, 20160901, 1);

select * from clpprreimb where code_lppr in ('2118823', '2105938', '201D012',  '01103140', '01103618');
select * from clpprcode where code_lppr in ('2118823', '2105938', '201D012', '01103140', '01103618');
select * from zartfrance where articleno = 4264931;
select * from clppr2article where articleno = 4264931;


----- BEFÜLLEN DER NEUEN TABELLEN MIT DEN ALTEN WERTEN

delete from clppr2article;

insert into clppr2article (code_lppr, articleno, datefrom, reimbcalcflag)
select code_lppr, articleno, cast(to_char(current, '%Y%m%d') as integer), '1'
from zartfrance where code_lppr != '' and reimbursement_type = 2;


delete from clpprreimb;

insert into clpprreimb (code_lppr, datefrom, reimbursement_val)
select code_lppr,  cast(to_char(current, '%Y%m%d') as integer), reimbursement_val
from clpprcode;



--- SÄUBERN DER ALTEN TABELLEN, wenn Pflege + KSC + unload komplett umgestellt !!!

update zartfrance set  code_lppr = '' where  reimbursement_type = 2;
update clpprcode  set reimbursement_val = 0;