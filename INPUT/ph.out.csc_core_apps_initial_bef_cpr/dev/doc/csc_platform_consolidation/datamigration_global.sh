#! /usr/bin/sh
# set -x
FROMDB="ode22@zdev21_tcp"
TODB="ode21@zdev21_tcp"

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
function doSQL
{
	SQL="$1";

	echo $(date -u +"%T") "${SQL}" 2>&1;
	echo "${SQL}" | dbaccess ${FROMDB} 2>&1;
}

#---------------------------------------------------------------------------------------------
# main script starts here
#---------------------------------------------------------------------------------------------
# Achtung: Tabelle mailgroup nur einmalig übernehmen!
doSQL "
select count(*) from ${FROMDB}:mailgroup;
insert into ${TODB}:mailgroup          select * from ${FROMDB}:mailgroup;
"

doSQL "
update ${FROMDB}:kdkritik      set kritiknr = kritiknr - 3000000;
update ${FROMDB}:kdkritikpos   set kritiknr = kritiknr - 3000000;
update ${FROMDB}:callbackitems set kritiknr = kritiknr - 3000000, callbackno = callbackno - 3000000;
"

#-- Crema Mail
#-- einmalig vor dem ersten Umzug der Daten von ode22 auf ode21
#--> Serial smtpemailtype um 100 erhöhen (incl. Referenzierungen in Sub-Tabellen), damit anschließend die Werte von ode22 unverändert übernommen werden können!
doSQL "
insert into ${TODB}:smtpemailtype select id + 100, emailtype + 100, smtpusergroupid from ${TODB}:smtpemailtype;
delete from ${TODB}:smtpemailtype where id < 100;
update ${TODB}:smtpemailtype set emailtype = emailtype - 100 where id > 100;
--update ${TODB}:smtpemailtype set id = id + 100;
update ${TODB}:smtpgvlmail set smtpemailtypeid = smtpemailtypeid + 100;
update ${TODB}:smtpsendtoemailaddresses set smtpemailtypeid = smtpemailtypeid + 100;
"

#--> Serials erhöhen, damit anschließend die Werte von ode22 unverändert übernommen werden können!
doSQL "
insert into ${TODB}:smtpgvlmail select id + 100, smtpemailtypeid, sendgvlmail + 100 from ${TODB}:smtpgvlmail;
delete from ${TODB}:smtpgvlmail where id < 100;
update ${TODB}:smtpgvlmail set sendgvlmail = sendgvlmail - 100 where id > 100;
--update ${TODB}:smtpgvlmail set id = id + 100;
insert into ${TODB}:smtpsendtoemailaddresses select id + 1000, senttoaddress, smtpemailtypeid + 1000 from ${TODB}:smtpsendtoemailaddresses;
delete from ${TODB}:smtpsendtoemailaddresses where id < 1000;
update ${TODB}:smtpsendtoemailaddresses set smtpemailtypeid = smtpemailtypeid - 1000 where id > 1000;
--update ${TODB}:smtpsendtoemailaddresses set id = id + 1000;
"

