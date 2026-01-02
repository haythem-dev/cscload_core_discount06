#! /usr/bin/sh
# set -x
BRANCHNO=$1
LOGFILE="loadarticles_${BRANCHNO}.log"


echo "$(date -u +"%T") tpldlokalart" >> ${LOGFILE} 2>&1;
cp -f /transfer/ksc/data/deakz.${BRANCHNO}.Z /software/wss/de/ksc/load/data/deakz.${BRANCHNO}.Z >> ${LOGFILE} 2>&1;
rm -f /software/wss/de/ksc/load/data/deakz.${BRANCHNO} >> ${LOGFILE} 2>&1;
uncompress /software/wss/de/ksc/load/data/deakz.${BRANCHNO}.Z >> ${LOGFILE} 2>&1;
/software/wss/de/ksc/load/proc/tpldlokalart.sh -start -vz ${BRANCHNO} -bu -h24 >> ${LOGFILE} 2>&1;
