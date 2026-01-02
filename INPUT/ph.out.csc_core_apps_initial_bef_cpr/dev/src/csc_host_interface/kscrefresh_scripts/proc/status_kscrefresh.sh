#!/usr/bin/ksh

BRANCHNO=$1;
FWD=$(dirname $0);
cd ${FWD};

PROC_DIR=$(pwd)
INI_DIR=$(echo ${PROC_DIR}|sed -e "s/\/proc/\/ini/g")

${PROC_DIR}/csc_corpha.sh -status -branchno ${BRANCHNO} -configfile ${INI_DIR}/csc_corpha.xml -orderfilter even
${PROC_DIR}/csc_corpha.sh -status -branchno ${BRANCHNO} -configfile ${INI_DIR}/csc_corpha.xml -orderfilter odd
${PROC_DIR}/csc_phabor.sh -status -branchno ${BRANCHNO} -configfile ${INI_DIR}/csc_phabor.xml -transfer -process
${PROC_DIR}/csc_phatra.sh -status -branchno ${BRANCHNO} -configfile ${INI_DIR}/csc_phatra.xml 





