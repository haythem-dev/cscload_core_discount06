SET ISOLATION DIRTY READ;

UPDATE ode21@zdev21_shm:rechner SET datenbank_name='ode21@zdev21_shm' 			WHERE datenbank_name='ode21@ode21_shm';
UPDATE ode21@zdev21_shm:rechner SET datenbank_name='ode22@zdev21_tcp' 			WHERE datenbank_name='ode22@ode22_tcp';
UPDATE ode21@zdev21_shm:rechner SET warehouse_datenbankname='wde21@zdev21_tcp' 	WHERE warehouse_datenbankname='wde21@wde21_tcp';
UPDATE ode21@zdev21_shm:rechner SET inbound_datenbankname='ide21@zdev21_tcp' 	WHERE inbound_datenbankname='ide21@ide21_tcp';
SELECT * FROM ode21@zdev21_shm:rechner ORDER BY filialnr;

UPDATE ode22@zdev21_shm:rechner SET datenbank_name='ode21@zdev21_tcp'          WHERE datenbank_name='ode21@ode21_tcp';
UPDATE ode22@zdev21_shm:rechner SET datenbank_name='ode22@zdev21_shm'          WHERE datenbank_name='ode22@ode22_shm';
UPDATE ode22@zdev21_shm:rechner SET warehouse_datenbankname='wde21@zdev21_tcp' WHERE warehouse_datenbankname='wde21@wde21_tcp';
UPDATE ode22@zdev21_shm:rechner SET inbound_datenbankname='ide21@zdev21_tcp'   WHERE inbound_datenbankname='ide21@ide21_tcp';
SELECT * FROM ode22@zdev21_tcp:rechner ORDER BY filialnr;

UPDATE ode21@zdev21_shm:filiale SET name = 'ZDEV21.NORD ' || SUBSTR(standort_lang, 0, LENGTH(standort_lang)) WHERE name NOT LIKE 'ZDEV21.NORD%';
SELECT * FROM ode21@zdev21_shm:filiale;

UPDATE ode22@zdev21_shm:filiale SET name = 'ZDEV21.SUED ' || SUBSTR(standort_lang, 0, LENGTH(standort_lang)) WHERE name NOT LIKE 'ZDEV21.SUED%';
SELECT * FROM ode22@zdev21_shm:filiale;

UPDATE ode21@zdev21_shm:smtpusergroups SET url = REPLACE(url, 'https://crema.', 'https://crematest.') WHERE url LIKE 'https://crema.%';
UPDATE ode22@zdev21_shm:smtpusergroups SET url = REPLACE(url, 'https://crema.', 'https://crematest.') WHERE url LIKE 'https://crema.%';

DELETE FROM ode21@zdev21_shm:smtpsendtoemailaddresses;
INSERT INTO ode21@zdev21_shm:smtpsendtoemailaddresses (senttoaddress, smtpemailtypeid) SELECT 'kscrefreshtest@phoenixgroup.eu', id FROM ode21@zdev21_shm:smtpemailtype;

DELETE FROM ode22@zdev21_shm:smtpsendtoemailaddresses;
INSERT INTO ode22@zdev21_shm:smtpsendtoemailaddresses (senttoaddress, smtpemailtypeid) SELECT 'kscrefreshtest@phoenixgroup.eu', id FROM ode22@zdev21_shm:smtpemailtype;

SELECT 'ode21', * FROM ode21@zdev21_shm:smtpsendtoemailaddresses UNION SELECT 'ode22', * FROM ode21@zdev21_shm:smtpsendtoemailaddresses;


update ode21@zdev21_tcp:parameter set parametername='zdev21', auspraegung='/software/wss/de/ksc/server/data/' where filialnr=0 and programmname='KSC' and zweck='CSVIMPORTSERVER';
	
update ode22@zdev21_tcp:parameter set parametername='zdev21', auspraegung='/software/wss/de4/ksc/server/data/' 	where filialnr=0 and programmname='KSC' and zweck='CSVIMPORTSERVER';


select * from filiale;