#!/usr/bin/ksh

BRANCHNO=$1;
FWD=$(dirname $0);
cd ${FWD};

# get paths to ini and procedure directory
PROC_DIR=$(pwd)
INI_DIR=$(echo ${PROC_DIR}|sed -e "s/\/proc/\/ini/g")

# get country from path
COUNTRY="";
COUNTRY=$(echo ${PROC_DIR}|sed -e "s/\/software\/wss\///g")
COUNTRY=$(echo ${COUNTRY}|sed -e "s/\/ksc\/batch\/proc//g")

# get database name by country
DBASENAME="";
if [ "${COUNTRY}" == "at" ]; then 
	DBASENAME="oat21" 
	fi;
if [ "${COUNTRY}" == "bg" ]; then 
	DBASENAME="obg21" 
	fi;
if [ "${COUNTRY}" == "ch" ]; then 
	DBASENAME="och21" 
	fi;
if [ "${COUNTRY}" == "de" ]; then 
	DBASENAME="ode21"
	fi;
if [ "${COUNTRY}" == "de4" ]; then 
	DBASENAME="ode22" 
	fi;
if [ "${COUNTRY}" == "fr" ]; then 
	DBASENAME="ofr21" 
	fi;
if [ "${COUNTRY}" == "hr" ]; then 
	DBASENAME="ohr21" 
	fi;
if [ "${COUNTRY}" == "rs" ]; then 
	DBASENAME="ors21" 
	fi;
if [ "${COUNTRY}" == "pat" ]; then 
	DBASENAME="oat21pre"
	fi;
if [ "${COUNTRY}" == "pch" ]; then 
	DBASENAME="och21pre"
	fi;
if [ "${COUNTRY}" == "pfr" ]; then 
	DBASENAME="ofr21pre"
	fi;

echo "Procedure Directory: ${PROC_DIR}";
echo "Ini Directory      : ${INI_DIR}";
echo "Country            : ${COUNTRY}";
echo "BranchNo           : ${BRANCHNO}";
echo "Database Name      : ${DBASENAME}";

# stop processes that may not run during prune
${PROC_DIR}/stop_kscrefresh.sh ${BRANCHNO}

# prune data
${PROC_DIR}/csc_prune.sh -start -branchno ${BRANCHNO} -dbname ${DBASENAME}

# start processes
${PROC_DIR}/csc_corpha.sh -start -branchno ${BRANCHNO} -configfile ${INI_DIR}/csc_corpha.xml -orderfilter even
${PROC_DIR}/csc_corpha.sh -start -branchno ${BRANCHNO} -configfile ${INI_DIR}/csc_corpha.xml -orderfilter odd
${PROC_DIR}/csc_phabor.sh -start -branchno ${BRANCHNO} -configfile ${INI_DIR}/csc_phabor.xml -transfer -process
${PROC_DIR}/csc_phatra.sh -start -branchno ${BRANCHNO} -configfile ${INI_DIR}/csc_phatra.xml 
${PROC_DIR}/aaordclose.sh -start -v ${BRANCHNO}
${PROC_DIR}/vbordimport.sh -start -v ${BRANCHNO}

echo "finished.";
