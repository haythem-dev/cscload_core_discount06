#! /usr/bin/sh
# set -x
BRANCHNO=$1
LOGFILE="masterscript_${BRANCHNO}.log"


echo "$(date -u +"%T") datamigration_branch" >> ${LOGFILE} 2>&1;
datamigration_branch.sh ${BRANCHNO} >> ${LOGFILE} 2>&1;

echo "$(date -u +"%T") pep (abba)" >> ${LOGFILE} 2>&1;
/software/wss/de/narcotics/proc/narcpep.sh -start -branchno ${BRANCHNO} -mode abba -fromdb ode22@zdev21_tcp -todb ode21@zdev21_tcp -inbounddb ide21@zdev21_tcp >> ${LOGFILE} 2>&1;

echo "$(date -u +"%T") pep (narc)" >> ${LOGFILE} 2>&1;
/software/wss/de/narcotics/proc/narcpep.sh -start -branchno ${BRANCHNO} -mode narc -fromdb ode22@zdev21_tcp -todb ode21@zdev21_tcp -inbounddb ide21@zdev21_tcp >> ${LOGFILE} 2>&1;
