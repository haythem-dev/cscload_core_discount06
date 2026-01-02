#!/usr/bin/ksh

BRANCHNO=$1;

. $(dirname $0)/getBranchDirectory.sh;
KSCPATH="";
getBranchDirectory ${BRANCHNO};

PROC_DIR=$( echo "${KSCPATH}batch/proc/");

echo "BranchNo       : ${BRANCHNO}";
echo "Directory      : ${KSCPATH}";
echo "proc-Directory : ${PROC_DIR}";

${PROC_DIR}/status_kscrefresh.sh ${BRANCHNO};

exit;
