#!/usr/bin/ksh

COUNTRY=$1;

if [ "devuser" != "${USER}" ]; then
    echo "ERROR: script has to be started with devuser!";
    exit -1;
fi;

function StartBranchProcesses
{
    local readonly _COUNTRY=${1};
    local readonly _BRANCH=${2};
    /software/wss/${_COUNTRY}/ksc/batch/proc/aaordclose.sh -start -v ${_BRANCH}        
    /software/wss/${_COUNTRY}/ksc/batch/proc/clearreservation.sh -start -vz ${_BRANCH}
    /software/wss/${_COUNTRY}/ksc/batch/proc/ibtorderimport.sh -start -branchno ${_BRANCH} -username ibtrelcalc.batch -password H9yItDrj              
}

function StopBranchProcesses
{
    local readonly _COUNTRY=${1};
    local readonly _BRANCH=${2};
    /software/wss/${_COUNTRY}/ksc/batch/proc/aaordclose.sh -stop -v ${_BRANCH}        
    /software/wss/${_COUNTRY}/ksc/batch/proc/clearreservation.sh -stop -vz ${_BRANCH}
    /software/wss/${_COUNTRY}/ksc/batch/proc/ibtorderimport.sh -stop -branchno ${_BRANCH} -username ibtrelcalc.batch -password H9yItDrj        
    /software/wss/${_COUNTRY}/ksc/batch/proc/csc_corpha.sh -stop -branchno ${_BRANCH} -configfile /software/wss/${_COUNTRY}/ksc/batch/ini/csc_corpha.xml -orderfilter even
    /software/wss/${_COUNTRY}/ksc/batch/proc/csc_corpha.sh -stop -branchno ${_BRANCH} -configfile /software/wss/${_COUNTRY}/ksc/batch/ini/csc_corpha.xml -orderfilter odd
    /software/wss/${_COUNTRY}/ksc/batch/proc/csc_phabor.sh -stop -branchno ${_BRANCH} -configfile /software/wss/${_COUNTRY}/ksc/batch/ini/csc_phabor.xml -transfer -process
    /software/wss/${_COUNTRY}/ksc/batch/proc/csc_phadex.sh -stop -country ${_COUNTRY} -branchno ${_BRANCH} -configFile /software/wss/${_COUNTRY}/ksc/batch/ini/csc_phadex.xml
    /software/wss/${_COUNTRY}/ksc/batch/proc/csc_phatra.sh -stop -branchno ${_BRANCH} -configfile /software/wss/${_COUNTRY}/ksc/batch/ini/csc_phatra.xml    
}

function RestartCountryProcesses
{
    local readonly _COUNTRY=${1};    
    /software/wss/${_COUNTRY}/ksc/server/proc/kscserver.sh -stop
    /software/wss/${_COUNTRY}/ksc/server/proc/cscservice.sh -stop
    #/software/wss/${_COUNTRY}/ksc/server/proc/zaapunix.sh -stop        
    /software/wss/${_COUNTRY}/ksc/server/proc/kscserver.sh -start
    /software/wss/${_COUNTRY}/ksc/server/proc/cscservice.sh -start    
    #/software/wss/${_COUNTRY}/ksc/server/proc/zaapunix.sh -start               
}

if [ "at" == "${COUNTRY}" ]; then
    for BRANCH in 61 62 63 64 
    do 
        StopBranchProcesses ${COUNTRY} ${BRANCH};            
    done
    for BRANCH in 61 62 63 64
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};        
    done        
    RestartCountryProcesses ${COUNTRY};
fi;

if [ "bg" == "${COUNTRY}" ]; then
    for BRANCH in 22 23 25 26 28
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 22 23 25 26 28
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY}; 
fi;

if [ "ch" == "${COUNTRY}" ]; then
    for BRANCH in 12 13
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 12 13
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY};
fi;

if [ "de" == "${COUNTRY}" ]; then
    for BRANCH in 05 06 08 09 21 31 33 40 44 46 51 52 54 56 57 58 59 70 78 81 82
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 05 06 08 09 21 31 33 40 44 46 51 52 54 56 57 58 59 70 78 81 82
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY};      
fi;

if [ "fr" == "${COUNTRY}" ]; then
    for BRANCH in 17 18 30 32 34 36 37 38 39 41 42 45 47 50 53 55 60 66 68 75 76 80 86 87
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 17 18 30 32 34 36 37 38 39 41 42 45 47 50 53 55 60 66 68 75 76 80 86 87
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY};  
fi;

if [ "hr" == "${COUNTRY}" ]; then
    for BRANCH in 71 72 73 74 77
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 71 72 73 74 77
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY};       
fi;

if [ "rs" == "${COUNTRY}" ]; then
    for BRANCH in 03 84 85
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 03 84 85
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY};  
fi;

if [ "pat" == "${COUNTRY}" ]; then
    for BRANCH in 83
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 83
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY}; 
fi;

if [ "pch" == "${COUNTRY}" ]; then
    for BRANCH in 16
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 16
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY}; 
fi;

if [ "pfr" == "${COUNTRY}" ]; then
    for BRANCH in 43 48
    do
        StopBranchProcesses ${COUNTRY} ${BRANCH};        
    done
    for BRANCH in 43 48
    do
        StartBranchProcesses ${COUNTRY} ${BRANCH};
    done        
    RestartCountryProcesses ${COUNTRY}; 
fi;

exit 0;
