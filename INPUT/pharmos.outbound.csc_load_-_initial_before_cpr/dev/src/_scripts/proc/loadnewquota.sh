# qual
 . /software/etc/profile_prz

set -u

dbaccess ofr21 -<<% 
create temp table t_quota ( cip char(25), val char(1), quot integer, vz smallint, cust integer, from integer, to integer);
load from $1 delimiter ';' insert into t_quota;

begin work;
delete from articlequota where branchno = (select distinct vz from t_quota);
commit work;

begin work;
insert into articlequota (branchno, customerno, articleno, quota, validity, datefrom, dateto, dateupdate) \
select tq.vz, tq.cust, ac.articleno, tq.quot, tq.val,  tq.from , tq.to, cast(to_char(current, '%Y%m%d') as integer) \
from t_quota tq \
inner join articlecodes ac on tq.cip = ac.article_code;
commit work;
%
