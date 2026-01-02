#! /usr/bin/sh
# set -x

BRANCHNO=$1

FROM_SERVER="zdev21"	# "ode21"
TO_SERVER="zdev21"		# "ode22"

FROM_DB_INST="ode21"
TO_DB_INST="ode22"

FROM_DBSERVER="${FROM_SERVER}_tcp"
TO_DBSERVER="${TO_SERVER}_tcp"


FROMDB="${FROM_DB_INST}@${FROM_DBSERVER}"
TODB="${TO_DB_INST}@${TO_DBSERVER}"

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

# 
doSQL "
delete from ${TODB}:artikellokal                                                where filialnr=${BRANCHNO};
select count(*) from ${FROMDB}:artikellokal                                     where filialnr=${BRANCHNO};
insert into ${TODB}:artikellokal     select * from ${FROMDB}:artikellokal       where filialnr=${BRANCHNO};
select count(*) from ${TODB}:artikellokal                                       where filialnr=${BRANCHNO};
"

doSQL "
delete from ${TODB}:articlereservation                                                      where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:articlereservation                                           where branchno=${BRANCHNO};
insert into ${TODB}:articlereservation     select * from ${FROMDB}:articlereservation       where branchno=${BRANCHNO};
select count(*) from ${TODB}:articlereservation                                             where branchno=${BRANCHNO};
"

doSQL "
delete from ${TODB}:cststockreserved                                              where branchno=${BRANCHNO};
select count(*) from ${FROMDB}:cststockreserved                                   where branchno=${BRANCHNO} and reservtype=7;
insert into ${TODB}:cststockreserved   select * from ${FROMDB}:cststockreserved   where branchno=${BRANCHNO} and reservtype=7;
select count(*) from ${TODB}:cststockreserved                                     where branchno=${BRANCHNO} and reservtype=7;
"
