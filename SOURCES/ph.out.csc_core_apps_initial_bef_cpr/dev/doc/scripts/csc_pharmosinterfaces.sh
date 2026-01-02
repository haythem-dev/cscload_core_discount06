#!/usr/bin/ksh

COUNTRY=$1;
BRANCH=$2;

/software/wss/${COUNTRY}/ksc/batch/proc/csc_corpha.sh -stop -branchno ${BRANCH} -configfile /software/wss/${COUNTRY}/ksc/batch/ini/csc_corpha.xml -orderfilter even
/software/wss/${COUNTRY}/ksc/batch/proc/csc_corpha.sh -stop -branchno ${BRANCH} -configfile /software/wss/${COUNTRY}/ksc/batch/ini/csc_corpha.xml -orderfilter odd
/software/wss/${COUNTRY}/ksc/batch/proc/csc_phabor.sh -stop -branchno ${BRANCH} -configfile /software/wss/${COUNTRY}/ksc/batch/ini/csc_phabor.xml -transfer -process
/software/wss/${COUNTRY}/ksc/batch/proc/csc_phadex.sh -stop -country ${COUNTRY} -branchno ${BRANCH} -configFile /software/wss/${COUNTRY}/ksc/batch/ini/csc_phadex.xml
/software/wss/${COUNTRY}/ksc/batch/proc/csc_phatra.sh -stop -branchno ${BRANCH} -configfile /software/wss/${COUNTRY}/ksc/batch/ini/csc_phatra.xml

/software/wss/${COUNTRY}/ksc/batch/proc/csc_corpha.sh -start -branchno ${BRANCH} -configfile /software/wss/${COUNTRY}/ksc/batch/ini/csc_corpha.xml -orderfilter even
/software/wss/${COUNTRY}/ksc/batch/proc/csc_corpha.sh -start -branchno ${BRANCH} -configfile /software/wss/${COUNTRY}/ksc/batch/ini/csc_corpha.xml -orderfilter odd
/software/wss/${COUNTRY}/ksc/batch/proc/csc_phabor.sh -start -branchno ${BRANCH} -configfile /software/wss/${COUNTRY}/ksc/batch/ini/csc_phabor.xml -transfer -process
/software/wss/${COUNTRY}/ksc/batch/proc/csc_phadex.sh -start -country ${COUNTRY} -branchno ${BRANCH} -configFile /software/wss/${COUNTRY}/ksc/batch/ini/csc_phadex.xml
/software/wss/${COUNTRY}/ksc/batch/proc/csc_phatra.sh -start -branchno ${BRANCH} -configfile /software/wss/${COUNTRY}/ksc/batch/ini/csc_phatra.xml    
