dbaccess  ode21@zdev21_shm << EOF
select "file to process :", '$1' FROM sysmaster:sysdual;

SELECT first 1 * FROM articlequota INTO TEMP tmp1;
delete tmp1;

load from '$1' delimiter ";" insert into tmp1(BRANCHNO,CUSTOMERNO,ARTICLENO,QUOTA,VALIDITY,DATEFROM,DATETO);
-- select * from tmp1;

MERGE INTO articlequota as AQ USING tmp1 as T
on AQ.customerno=T.customerno and AQ.ARTICLENO=T.ARTICLENO
        WHEN NOT MATCHED THEN
                 INSERT
        (BRANCHNO,CUSTOMERNO,ARTICLENO,QUOTA,DATEUPDATE, DATEFROM,DATETO)
        values (T.BRANCHNO,T.CUSTOMERNO,T.ARTICLENO,T.QUOTA,to_number(to_char(TODAY, '%Y%m%d')), T.DATEFROM,T.DATETO)
        WHEN MATCHED THEN UPDATE
       SET
                AQ.QUOTA=T.QUOTA,
                AQ.DATEUPDATE=to_number(to_char(TODAY, '%Y%m%d')),
                AQ.DATEFROM=T.DATEFROM,
                AQ.DATETO=T.DATETO

EOF
