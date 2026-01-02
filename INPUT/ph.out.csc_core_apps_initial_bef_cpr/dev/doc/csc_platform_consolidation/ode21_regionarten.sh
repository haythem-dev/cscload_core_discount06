#! /usr/bin/sh
# set -x
SERVER="zdev21"		# "ode21"
DB_INST="ode21"
DBSERVER="${SERVER}_tcp"
DB="${DB_INST}@${DBSERVER}"

typeset -i BRANCHNO=$1

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
function doSQL
{
	SQL="$1";

	echo "${SQL}" 2>&1;
	echo "${SQL}" | dbaccess ${DB} 2>&1;
}

#---------------------------------------------------------------------------------------------
# main script starts here
#---------------------------------------------------------------------------------------------

doSQL "
DELETE FROM ${DB}:regionarten WHERE regionnr=${BRANCHNO} AND regionteilnr!=${BRANCHNO};
INSERT INTO ${DB}:regionarten (regionentyp, regionnr, regionteilnr, tm_date) 
	SELECT 1, ${BRANCHNO}, r.filialnr, cast(to_char(current,'%Y%m%d') as integer) from ${DB}:rechner r 
	WHERE datenbank_name like 'ode21%' and r.filialnr not in (${BRANCHNO},21,27,0);
DELETE FROM ${DB}:regionarten WHERE regionnr!=${BRANCHNO} AND regionteilnr=${BRANCHNO};
INSERT INTO ${DB}:regionarten (regionentyp, regionnr, regionteilnr, tm_date)
	SELECT 1, r.filialnr, ${BRANCHNO}, cast(to_char(current,'%Y%m%d') as integer) from ${DB}:rechner r 
	WHERE datenbank_name like 'ode21%' and r.filialnr not in (${BRANCHNO},21,27,0);
"
