#!/usr/bin/ksh

BRANCHNO=$1;

. $(dirname $0)/getBranchDirectory.sh;
KSCPATH="";
getBranchDirectory ${BRANCHNO};

PROC_DIR=$( echo "${KSCPATH}load/proc/");

echo "BranchNo       : ${BRANCHNO}";
echo "Directory      : ${KSCPATH}";
echo "proc-Directory : ${PROC_DIR}";

${PROC_DIR}/loaddkkaa.sh -start -branchno ${BRANCHNO};
${PROC_DIR}/tplddkkui.sh -start -lf ${BRANCHNO};
${PROC_DIR}/tpldzentknd.sh -start -lf ${BRANCHNO};
${PROC_DIR}/tpldtour.sh -start -lf ${BRANCHNO};
${PROC_DIR}/loadroutes.sh -start -vz ${BRANCHNO};
${PROC_DIR}/loadcstpharmgrp.sh -start -vz ${BRANCHNO};
${PROC_DIR}/tpldlokalart.sh -start -vz ${BRANCHNO};

exit;
