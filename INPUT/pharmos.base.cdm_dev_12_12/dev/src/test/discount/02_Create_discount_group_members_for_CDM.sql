DELETE FROM ich21@zdev21_tcp:cdiscgrp WHERE discountgrpno BETWEEN 30 AND 33;

INSERT INTO ich21@zdev21_tcp:cdiscgrp(discountgrpno,description,discountgrptype,customerno) 
SELECT *
FROM TABLE(LIST{
  ROW(30,'NTTDATA DISCOUNT GROUP ALPHA'::char(254),0,0),
  ROW(31,'NTTDATA DISCOUNT GROUP BETA' ::char(254),0,0),
  ROW(32,'NTTDATA DISCOUNT GROUP GAMMA'::char(254),0,0),
  ROW(33,'NTTDATA DISCOUNT GROUP DELTA'::char(254),0,0)
}) T(discountgrpno,description,discountgrptype,customerno);

DELETE FROM ich21@zdev21_tcp:cdiscgrpmem WHERE discountgrpno BETWEEN 30 AND 33;

INSERT INTO ich21@zdev21_tcp:cdiscgrpmem(discountgrpno,articleno,discountcondition,manufacturerno) 
SELECT *
FROM TABLE(LIST{
  ROW(30,30010,0,0),
  ROW(31,30011,0,0),
  ROW(31,30012,0,0),
  ROW(31,30015,0,0),
  ROW(32,30012,0,0),
  ROW(32,30014,0,0),
  ROW(33,30013,0,0),
  ROW(33,30015,0,0)  
}) T(discountgrpno,articleno,discountcondition,manufacturerno);
