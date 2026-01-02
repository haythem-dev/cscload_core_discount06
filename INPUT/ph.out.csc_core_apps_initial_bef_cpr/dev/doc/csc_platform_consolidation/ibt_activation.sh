#! /usr/bin/sh
# set -x

FROM_SERVER="zdev21"	# "ode22"
TO_SERVER="zdev21"		# "ode21"

FROM_DB_INST="ode22"
TO_DB_INST="ode21"

FROM_DBSERVER="${FROM_SERVER}_tcp"
TO_DBSERVER="${TO_SERVER}_tcp"

FROMDB="${FROM_DB_INST}@${FROM_DBSERVER}"
TODB="${TO_DB_INST}@${TO_DBSERVER}"

typeset -i BRANCHNO=$1

#---------------------------------------------------------------------------------------------
#
#---------------------------------------------------------------------------------------------
function doSQL
{
	SQL="$1";

	echo "${SQL}" 2>&1;
	echo "${SQL}" | dbaccess ${FROMDB} 2>&1;
}

#---------------------------------------------------------------------------------------------
# main script starts here
#---------------------------------------------------------------------------------------------

doSQL "
update ${FROMDB}:ibtbranches set active_flag=1 where (branchno=${BRANCHNO} or ibtbranchno=${BRANCHNO}) and active_flag=99;
update ${TODB}:ibtbranches set active_flag=1 where (branchno=${BRANCHNO} or ibtbranchno=${BRANCHNO}) and active_flag=99;
"
