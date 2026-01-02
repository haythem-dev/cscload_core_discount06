set isolation dirty read;

-- create new sequence example
create sequence cscorderno start 1 increment 1 maxvalue 999999 cycle;
revoke all on cscorderno from public;
/* DEV */
grant select on cscorderno to public;
grant alter, select on cscorderno to devuser;

-- check existing sequence
select t.tabname, c.colname, s.* 
from syscolumns c
join systables t on t.tabid=c.tabid
join syssequences s on s.tabid=t.tabid
where t.tabname='cscorderno';

-- get next value (increment)
select cscorderno.nextval from systables where tabid = 1;

-- get current value (no increment)
select cscorderno.currval from systables where tabid = 1;





