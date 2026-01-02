#! /usr/bin/sh
# set -x

typeset -i BRANCHNO=$1

FROM_SERVER="zdev21"	# "ode22"
TO_SERVER="zdev21"		# "ode21"
KDDISPO_SERVER="zdev21"	# "ide21"
UADM_SERVER="zdev21"	# "ode21"

FROM_DB_INST="ode22"
TO_DB_INST="ode21"
KDDISPO_DB_INST="ide21"
UADM_DB_INST="zpcua1"

FROM_DBSERVER="${FROM_SERVER}_tcp"
FROM_DBSERVER_SHM="${FROM_SERVER}_shm"
TO_DBSERVER="${TO_SERVER}_tcp"
TO_DBSERVER_SHM="${TO_SERVER}_shm"


FROMDB="${FROM_DB_INST}@${FROM_DBSERVER}"
FROMDB_SHM="${FROM_DB_INST}@${FROM_DBSERVER_SHM}"
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

# Verhindern Erfassung neuer Aufträge in Alt-System für [FILIALEN]
doSQL "
update ${TODB}:werte   set zahl=0 where vertriebszentrumnr=${BRANCHNO} and bezeichner='AA_NEW_ORD';
update ${FROMDB}:werte set zahl=1 where vertriebszentrumnr=${BRANCHNO} and bezeichner='AA_NEW_ORD';
"

#--rechner
doSQL "
update ${FROMDB}:rechner set rechner_name='${FROM_SERVER}', datenbank_name='${FROMDB_SHM}' where filialnr=${BRANCHNO};
update ${TODB}:rechner   set rechner_name='${FROM_SERVER}', datenbank_name='${FROMDB}' where filialnr=${BRANCHNO};
"

# kundendispo
doSQL "
update ${KDDISPO_DB}:parameterkd set auspraeg='${FROMDB}'        where filialnr=${BRANCHNO} and programmname='KD2CLIENT' and zweck='STRINGS'      and parametername='LOGINTABLE';
update ${KDDISPO_DB}:parameterkd set auspraeg='${FROM_SERVER}'   where filialnr=${BRANCHNO} and programmname='KD2ROPOS'  and zweck='FILIALKONFIG' and parametername='AESERVER';
update ${KDDISPO_DB}:parameterkd set auspraeg='${FROM_DB_INST}'  where filialnr=${BRANCHNO} and programmname='KD2ROPOS'  and zweck='FILIALKONFIG' and parametername='DBAE';
update ${KDDISPO_DB}:parameterkd set auspraeg='${FROM_DBSERVER}' where filialnr=${BRANCHNO} and programmname='KD2ROPOS'  and zweck='FILIALKONFIG' and parametername='DBSERVER';
"

# UADM
# CSC (48) - csc_batches/abbauw
# IBTSPLITTING (91)
# IRM (43)
# NARCOTICS (28)
# ORDER_ENTRY (80) - ibtorderimport
doSQL "
update ${UADM_DB}:pplogpara set paravalue='DE2'                  where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'CSC')          and para1='${BRANCHNO}' and parabez='GROUP';

update ${UADM_DB}:pplogpara set paravalue='${FROM_DB_INST}'      where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'IBTSPLITTING') and para1='${BRANCHNO}' and parabez='DB';
update ${UADM_DB}:pplogpara set paravalue='${FROM_DBSERVER}'     where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'IBTSPLITTING') and para1='${BRANCHNO}' and parabez='DBSRV';

update ${UADM_DB}:pplogpara set paravalue='${FROM_SERVER}'       where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'IRM')          and para1='${BRANCHNO}' and parabez='CSC_SRVNAME';

update ${UADM_DB}:pplogpara set paravalue='${FROM_DB_INST}'      where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'NARCOTICS')    and para1='${BRANCHNO}' and parabez='DB';
update ${UADM_DB}:pplogpara set paravalue='${FROM_DBSERVER}'     where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'NARCOTICS')    and para1='${BRANCHNO}' and parabez='HOST';

update ${UADM_DB}:pplogpara set paravalue='${FROM_DB_INST}'      where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'ORDER_ENTRY')  and para1='${BRANCHNO}' and parabez='DB';
update ${UADM_DB}:pplogpara set paravalue='${FROM_DBSERVER_SHM}' where applicationid=(select applicationid from ${UADM_DB}:ppapplication where name = 'ORDER_ENTRY')  and para1='${BRANCHNO}' and parabez='DBSRV';
"
