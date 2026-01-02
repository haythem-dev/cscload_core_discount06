select BLIESORT.BESLA_NR,BESLA_MC,ORT,ABTEILUNG,
ARTIKEL_NR_BLIEFER 
from BLIESORT,outer BLIEFER,outer ARTNRBL 
where 
BLIESORT.ARTIKEL_NR= 582203
and BLIEFER.BESLA_NR=BLIESORT.BESLA_NR
and ARTNRBL.BESLA_NR=BLIESORT.BESLA_NR
and ARTNRBL.ARTIKEL_NR=BLIESORT.ARTIKEL_NR

select * from bliesort where besla_nr = 17 and artikel_nr = 582203


create temp table TH (pzn integer);
create unique index i_TH on TH (pzn)

load from 'D:\temp\CH\bliesort_lösch_17.csv'
insert into TH

select * from bliesort where besla_nr = 17 and artikel_nr in (select pzn from TH)


select * from carticlecodes