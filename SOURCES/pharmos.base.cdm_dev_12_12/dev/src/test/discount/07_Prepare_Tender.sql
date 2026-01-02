DELETE FROM och21@zdev21_tcp:tenderhead WHERE tenderno IN(45257,45258);

INSERT INTO och21@zdev21_tcp:tenderhead(tenderno,tendertype,contractno,branchno,customerno,accbranchno,acccustomerno,datefrom,dateto,exceedancepct,tenderstate,changedate,nameofuser,pharmacychainno,partnerno,deletedflag,purchaseorderproposalflag,customergroupid,pharmacygroupid)
SELECT *
FROM TABLE(LIST{
  ROW(45257,1,'OW Tender Test'::char(48),12,3148080,12,3148080,20220101,20301231,0.00,0,20220914,'o.wasmut',0,0,0,0,'00','010'),
  ROW(45258,1,       'TEST OW'::char(48),12,3148080,12,3148080,20220810,20301231,0.00,1,20221021,'o.wasmut',0,0,0,0,'00','010')
}) T(tenderno,tendertype,contractno,branchno,customerno,accbranchno,acccustomerno,datefrom,dateto,exceedancepct,tenderstate,changedate,nameofuser,pharmacychainno,partnerno,deletedflag,purchaseorderproposalflag,customergroupid,pharmacygroupid);

DELETE FROM och21@zdev21_tcp:tenderpos WHERE tenderno IN(45257,45258);

INSERT INTO och21@zdev21_tcp:tenderpos(tenderno,articleno,articlecode,contractqty,contractprice,remaininglife,adddiscountpct,aep,tenderstate,changedate,nameofuser,pricediff,ownquotaqty,ownquotaflag,recallflag,creationdate)
SELECT *
FROM TABLE(LIST{
  ROW(45257,1324880,'1324880'::char(25),50,0.00,0,19.00,0.00,8,20220914,'o.wasmut',0.00,0,0,1,20220914),
  ROW(45257,30000,    '30000'::char(25),50,0.00,0,19.00,0.00,8,20220914,'o.wasmut',0.00,0,0,1,20220914),
  ROW(45258,30009,    '30009'::char(25),50,0.00,0,19.00,0.00,1,20221021,'o.wasmut',0.00,0,0,1,20221021)
}) T(tenderno,articleno,articlecode,contractqty,contractprice,remaininglife,adddiscountpct,aep,tenderstate,changedate,nameofuser,pricediff,ownquotaqty,ownquotaflag,recallflag,creationdate);

-- To activate OMG set both tenderstate == 1