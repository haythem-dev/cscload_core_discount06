#! /usr/bin/sh
# set -x

BRANCHNO=$1

FROM_SERVER="zdev21"	# "ode22"
TO_SERVER="zdev21"		# "ode21"
KDDISPO_SERVER="zdev21"	# "ide21"
UADM_SERVER="zdev21"	# "ode21"

FROM_DB_INST="ode22"
TO_DB_INST="ode21"
KDDISPO_DB_INST="ide21"
UADM_DB_INST="zpcua1"

FROM_DBSERVER="${FROM_SERVER}_tcp"
TO_DBSERVER="${TO_SERVER}_tcp"
TO_DBSERVER_SHM="${TO_SERVER}_shm"


FROMDB="${FROM_DB_INST}@${FROM_DBSERVER}"
TODB="${TO_DB_INST}@${TO_DBSERVER}"
TODB_SHM="${TO_DB_INST}@${TO_DBSERVER_SHM}"
KDDISPO_DB="${KDDISPO_DB_INST}@${KDDISPO_SERVER}_tcp"
UADM_DB="${UADM_DB_INST}@${UADM_SERVER}_tcp"

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

doSQL "
delete from ${TODB}:anrufparameter where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:articlequota where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:articlereservation where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:auftragartkomb where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:backrouting where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:buchungsart where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:branchinfo where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:callbackattach where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:callbackdivision where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:callbackitems where kritiknr in (select kritiknr from ${TODB}:kdkritik where filialnr=${BRANCHNO});
"

doSQL "
delete from ${TODB}:callbackofftime where callbackpartno in (select callbackpartno from ${TODB}:callbackpartner where vertriebszentrumnr=${BRANCHNO});
"

doSQL "
delete from ${TODB}:callbackpartner where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:callbackreasons where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:collordergrp where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:collordergrpmem where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:cremawebusersuggestion where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:cscini where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:cstseporderartgrp where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:cststockreserved where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:customernomapping where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:customerphoneno where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:delayeddeliverycst where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:deliverynoteheader where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:deliverynotefooter where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:deliverynotepos where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:distressrouting where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:feiertag where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:filiale where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:ibtbranches where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kdauftragart where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kdauftragendezeit where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kdkritik where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kdkritikpos where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kommiarten where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kundemasterplan where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kundenotdienstplan where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:kundeurlaub where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:ladeanrufplan where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:mailusers where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:nachlieferpos where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:orderperiodtime where order_period_id in (select id from ${TODB}:orderperiod where branchno=${BRANCHNO});
delete from ${TODB}:orderperiod where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:paraauftragbearb where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:parameter where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:passwd where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:pseudolagerorte where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:regionarten where regionnr=${BRANCHNO} and regionteilnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:salesman where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:shipauxno where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:seporderartgrp where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:sondertouren where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:stockentry where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:werte where vertriebszentrumnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:zeitarten where vertriebszentrumnr=${BRANCHNO};
"

#-- narcotics
doSQL "
delete from ${TODB}:narcopenorders where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:narcnumber where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:narctransactionoriginal where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:narcprotocol where catalogid in (select catalogid from ${TODB}:narctransactioncatalog where branchno = ${BRANCHNO});
"

doSQL "
delete from ${TODB}:narctransactioncatalog where branchno = ${BRANCHNO};
"

#--> Serial (id) ist wg debtmailsend schon DB-übergreifend eindeutig!
doSQL "
delete from ${TODB}:smtpusergroups  where branchno=${BRANCHNO};
"

#--> Serial (id) auf ode21 wurde vorab um 100 erhöht, so dass die Übernahme von ode22 mit ID´s < 100 kein Problem mehr ist!
doSQL "
delete from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO});
"

#--> Serial (id) auf ode21 wurde vorab um 100 erhöht, so dass die Übernahme von ode22 mit ID´s < 100 kein Problem mehr ist!
doSQL "
delete from ${TODB}:smtpgvlmail where smtpemailtypeid in (select id from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO}));
"

#--> Serial (id) auf ode21 wurde vorab um 1000 erhöht, so dass die Übernahme von ode22 mit ID´s < 1000 kein Problem mehr ist!
doSQL "
delete from ${TODB}:smtpsendtoemailaddresses where smtpemailtypeid in (select id from ${TODB}:smtpemailtype where smtpusergroupid in (select id from ${TODB}:smtpusergroups where branchno=${BRANCHNO}));
"

# ABBA
doSQL "
delete from ${TODB}:orderhead where branchno=${BRANCHNO};
delete from ${TODB}:orderpos where branchno=${BRANCHNO};
delete from ${TODB}:orderproposal where branchno=${BRANCHNO};
"
