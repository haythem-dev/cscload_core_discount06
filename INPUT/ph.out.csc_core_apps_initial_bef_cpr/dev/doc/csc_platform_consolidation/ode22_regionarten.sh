#! /usr/bin/sh
# set -x
SERVER="zdev21"		# "ode22"
DB_INST="ode22"
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
DELETE FROM ${DB}:regionarten WHERE regionnr!=${BRANCHNO} AND regionteilnr=${BRANCHNO};
"
