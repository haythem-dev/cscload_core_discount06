#!/usr/bin/ksh

BRANCHNO=$1;

. $(dirname $0)/getBranchDirectory.sh;
KSCPATH="";
getBranchDirectory ${BRANCHNO};

echo "BranchNo       : ${BRANCHNO}";
echo "Directory      : ${KSCPATH}";

PROC_DIR=$( echo "${KSCPATH}server/proc/");
echo "proc-Directory : ${PROC_DIR}";
${PROC_DIR}/kscserver.sh -stop;
${PROC_DIR}/zaapunix.sh -stop;
${PROC_DIR}/zaasunix.sh -stop;

PROC_DIR=$( echo "${KSCPATH}lockman/proc/");
echo "proc-Directory : ${PROC_DIR}";
${PROC_DIR}/lockman.sh -stop;
${PROC_DIR}/lockman.sh -start;

PROC_DIR=$( echo "${KSCPATH}server/proc/");
echo "proc-Directory : ${PROC_DIR}";
${PROC_DIR}/kscserver.sh -start;
${PROC_DIR}/zaapunix.sh -start;
${PROC_DIR}/zaasunix.sh -start;

PROC_DIR=$( echo "${KSCPATH}load/proc/");
echo "proc-Directory : ${PROC_DIR}";

${PROC_DIR}/loaddkkaa.sh -start -branchno ${BRANCHNO};
${PROC_DIR}/tplddkkui.sh -start -lf ${BRANCHNO};
${PROC_DIR}/tpldzentknd.sh -start -lf ${BRANCHNO};
${PROC_DIR}/tpldtour.sh -start -lf ${BRANCHNO};
${PROC_DIR}/loadroutes.sh -start -vz ${BRANCHNO};
${PROC_DIR}/loadcstpharmgrp.sh -start -vz ${BRANCHNO};
${PROC_DIR}/tpldlokalart.sh -start -vz ${BRANCHNO};

PROC_DIR=$( echo "${KSCPATH}batch/proc/");
echo "proc-Directory : ${PROC_DIR}";
${PROC_DIR}/stop_kscrefresh.sh ${BRANCHNO};
${PROC_DIR}/start_kscrefresh.sh ${BRANCHNO};

exit;
