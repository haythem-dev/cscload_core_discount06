select * from umkverwaltung order by umknr
select * from modemanrufplan order by filialnr


DELETE FROM modemanrufplan 
WHERE filialnr IN (5,21,44,51,52,54,56,57,58,81,82);

INSERT INTO modemanrufplan (filialnr,geraeteid,sequenznr,geraeteart,geraetnst,geraeteverw1,terminalstatus,modemtyp,startzeit,endezeit
,vertriebszentrumnr,kundennr,urrufzeit,datum,auftragstatus,kdauftragnr1,poolnr,umknr,tourid,tm_date,tm_time
,loginid,changeid,aktiv,umknst) 
SELECT filialnr,geraeteid,sequenznr,geraeteart,geraetnst,geraeteverw1,terminalstatus,modemtyp,startzeit,endezeit
,vertriebszentrumnr,kundennr,urrufzeit,datum,auftragstatus,kdauftragnr1,poolnr,umknr,tourid,tm_date,tm_time
,loginid,changeid,aktiv,umknst
FROM ode22@ode22_tcp:modemanrufplan 
WHERE filialnr IN (5,21,44,51,52,54,56,57,58,81,82);

DELETE FROM umkverwaltung 
WHERE filialnr IN (5,21,44,51,52,54,56,57,58,81,82); 

INSERT INTO umkverwaltung (filialnr,umknr,rechnername,portnr,tm_date,tm_time,loginid,changeid) 
SELECT filialnr,umknr,'ode21',portnr,tm_date,tm_time,loginid,changeid FROM ode22@ode22_tcp:umkverwaltung 
WHERE filialnr IN (5,21,44,51,52,54,56,57,58,81,82); 

 