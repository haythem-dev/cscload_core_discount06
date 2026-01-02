#!/usr/bin/ksh

BRANCHNO=$1;
FWD=$(dirname $0);
cd ${FWD};

PROC_DIR=$(pwd)

${PROC_DIR}/stop_kscrefresh.sh ${BRANCHNO}
${PROC_DIR}/start_kscrefresh.sh ${BRANCHNO}


echo "finished.";
