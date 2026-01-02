DELETE FROM ich21@zdev21_tcp:cdiscount WHERE articleno BETWEEN 30000 AND 30015;

INSERT INTO ich21@zdev21_tcp:cdiscount(articleno,datefrom,dateto,baseqty,discountqty,discountgrpno,discountvaluepct,discountqtypct,surchargepct,fixedprice,pharmacygroupid,customerno,discountspec) 
SELECT * 
FROM TABLE(LIST{
  ROW(30000, 20220810, 20301231,  5, 1, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30000, 20220810, 20301231, 10, 3, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30000, 20220810, 20301231, 15, 6, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30000, 20220810, 20301231, 20,10, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30001, 20220810, 20301231,  5, 1, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30001, 20220810, 20301231,  5, 0, 0, 1.20::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '100'::char(3), 0, 0),
  ROW(30002, 20220810, 20301231,  5, 1, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30002, 20220810, 20301231,  5, 0, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '100'::char(3), 0, 0),
  ROW(30003, 20220810, 20301231,  1, 0, 0, 1.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30003, 20220810, 20301231,  5, 0, 0, 3.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30003, 20220810, 20301231, 10, 0, 0, 8.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30003, 20220810, 20301231, 20, 0, 0,12.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30004, 20220810, 20301231,  1, 0, 0, 1.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30004, 20220810, 20301231,  5, 0, 0, 3.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '000'::char(3), 0, 0),
  ROW(30004, 20220810, 20301231, 10, 0, 0, 8.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30004, 20220810, 20301231, 20, 0, 0,12.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '000'::char(3), 0, 0),
  ROW(30005, 20220810, 20301231,  1, 0, 0, 1.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '510'::char(3), 0, 0),
  ROW(30005, 20220810, 20301231,  5, 0, 0, 3.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '510'::char(3), 0, 0),
  ROW(30005, 20220810, 20301231, 10, 0, 0, 8.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '510'::char(3), 0, 0),
  ROW(30005, 20220810, 20301231, 20, 0, 0,12.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '510'::char(3), 0, 0),
  ROW(30006, 20220810, 20301231,  1, 0, 0, 1.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '000'::char(3), 3148080, 0),
  ROW(30006, 20220810, 20301231,  5, 0, 0, 3.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '000'::char(3), 3148080, 0),
  ROW(30006, 20220810, 20301231, 10, 0, 0, 8.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '000'::char(3), 3148080, 0),
  ROW(30006, 20220810, 20301231, 20, 0, 0,12.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '000'::char(3), 3148080, 0),
  ROW(30007, 20220810, 20301231,  1, 0, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.55::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 1),
  ROW(30007, 20220810, 20301231,  5, 0, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.45::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 1),
  ROW(30007, 20220810, 20301231, 10, 0, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.35::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 1),
  ROW(30007, 20220810, 20301231, 20, 0, 0, 0.00::decimal(4,2), 0.00::decimal(4,2), 0.25::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 1),
  ROW(30009, 20220810, 20301231,  1, 0, 0, 1.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30009, 20220810, 20301231,  5, 0, 0, 3.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30009, 20220810, 20301231, 10, 0, 0, 8.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0),
  ROW(30009, 20220810, 20301231, 20, 0, 0,12.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), 0.00::decimal(4,2), '010'::char(3), 0, 0)
}) T(articleno,datefrom,dateto,baseqty,discountqty,discountgrpno,discountvaluepct,discountqtypct,surchargepct,fixedprice,pharmacygroupid,customerno,discountspec);

INSERT INTO ich21@zdev21_tcp:cdiscount(articleno,baseqty,discountgrpno,datefrom,dateto,discountvaluepct,discountqtypct,surchargepct,refundpct,discountcalcfrom,discountapplyto,maxqty,pharmacygroupid) 
SELECT * 
FROM TABLE(LIST{
  ROW(30008,1,0,20220801,20301231,2.15,1.15,5.15,100,0,1,999,'010'),
  ROW(30008,2,0,20220801,20301231,2.25,1.25,5.25,100,0,1,999,'010'),
  ROW(30008,3,0,20220801,20301231,2.35,1.35,5.35,100,0,1,999,'010'),
  ROW(30008,1,0,20230101,20231231,2.16,1.16,5.16,100,0,1,999,'010'),
  ROW(30008,2,0,20230101,20231231,2.26,1.26,5.26,100,0,1,999,'010'),
  ROW(30008,3,0,20230101,20231231,2.36,1.36,5.36,100,0,1,999,'010'),
  ROW(30010,1,0,20220801,20301231,2.18,1.18,5.18, 90,1,0,999,'090'),
  ROW(30010,2,0,20220801,20301231,2.28,1.28,5.28, 90,1,0,999,'090'),
  ROW(30010,3,0,20220801,20301231,2.38,1.38,5.38, 90,1,0,999,'090'),
  ROW(30011,1,0,20220801,20301231,2.28,2.18,4.28, 90,1,0,999,'001'),
  ROW(30011,2,0,20220801,20301231,2.38,2.28,4.38, 90,1,0,999,'001'),
  ROW(30011,3,0,20220801,20301231,2.48,2.38,4.48, 90,1,0,999,'001'),
  ROW(30012,1,0,20220801,20301231,2.17,1.18,5.19, 95,1,0,999,'810'),
  ROW(30012,2,0,20220801,20301231,2.27,1.28,5.29, 95,1,0,999,'810'),
  ROW(30012,3,0,20220801,20301231,2.37,1.38,5.39, 95,1,0,999,'810'),
  ROW(30015,1,0,20220801,20301231,3.15,2.15,6.15,100,0,1,999,'140'),
  ROW(30015,2,0,20220801,20301231,3.25,2.25,6.25,100,0,1,999,'140'),
  ROW(30015,3,0,20220801,20301231,3.35,2.35,6.35,100,0,1,999,'140'),
  ROW(30015,1,0,20230101,20231231,3.16,2.16,6.16,100,0,1,999,'140'),
  ROW(30015,2,0,20230101,20231231,3.26,2.26,6.26,100,0,1,999,'140'),
  ROW(30015,3,0,20230101,20231231,3.36,2.36,6.36,100,0,1,999,'140')
}) T(articleno,baseqty,discountgrpno,datefrom,dateto,discountvaluepct,discountqtypct,surchargepct,refundpct,discountcalcfrom,discountapplyto,maxqy,pharmacygroupid);

INSERT INTO ich21@zdev21_tcp:cdiscount(articleno,baseqty,datefrom,dateto,discountvaluepct,discountqtypct,surchargepct,refundpct,discountcalcfrom,discountapplyto,maxqty,pharmacygroupid) 
SELECT * 
FROM TABLE(LIST{
  ROW(30013,1,20220801,20301231,2.16,1.16,5.16,100,0,1,999,'890'),
  ROW(30013,2,20220801,20301231,2.26,1.26,5.26,100,0,1,999,'890'),
  ROW(30013,3,20220801,20301231,2.36,1.36,5.36,100,0,1,999,'890'),
  ROW(30013,1,20230101,20231231,2.17,1.17,5.17,100,0,1,999,'890'),
  ROW(30013,2,20230101,20231231,2.27,1.27,5.27,100,0,1,999,'890'),
  ROW(30013,3,20230101,20231231,2.37,1.37,5.37,100,0,1,999,'090'),
  ROW(30014,1,20220801,20301231,2.18,1.18,5.18,100,1,0,999,'090'),
  ROW(30014,2,20220801,20301231,2.28,1.28,5.28,100,1,0,999,'090'),
  ROW(30014,3,20220801,20301231,2.38,1.38,5.38,100,1,0,999,'090'),
  ROW(30015,1,20220801,20301231,2.17,1.18,5.19,100,1,0,999,'810'),
  ROW(30015,2,20220801,20301231,2.27,1.28,5.29,100,1,0,999,'810'),
  ROW(30015,3,20220801,20301231,2.37,1.38,5.39,100,1,0,999,'810')
}) T(articleno,baseqty,datefrom,dateto,discountvaluepct,discountqtypct,surchargepct,refundpct,discountcalcfrom,discountapplyto,maxqy,pharmacygroupid);
