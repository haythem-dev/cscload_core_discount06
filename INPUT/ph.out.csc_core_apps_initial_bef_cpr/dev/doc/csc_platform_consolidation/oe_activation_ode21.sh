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
update ${DB}:werte set zahl=1 where vertriebszentrumnr=${BRANCHNO} and bezeichner='AA_NEW_ORD';
"
