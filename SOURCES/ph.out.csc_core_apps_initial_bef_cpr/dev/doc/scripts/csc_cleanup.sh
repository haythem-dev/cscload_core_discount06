#!/usr/bin/ksh

COUNTRY=$1;

if [ "at" == "${COUNTRY}" ]; then
    for BRANCH in 61 62 63 64
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;

if [ "ch" == "${COUNTRY}" ]; then
    for BRANCH in 12 13
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;

if [ "de" == "${COUNTRY}" ]; then
    for BRANCH in 05 06 08 09 21 31 33 40 44 46 51 52 54 56 57 58 59 70 78 81 82
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;

if [ "fr" == "${COUNTRY}" ]; then
    for BRANCH in 17 18 30 32 34 36 37 38 39 41 42 45 47 50 53 55 60 66 68 75 76 80 86 87
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;

if [ "hr" == "${COUNTRY}" ]; then
    for BRANCH in 71 72 73 74 77
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;

if [ "rs" == "${COUNTRY}" ]; then
    for BRANCH in 03 84 85
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;

if [ "pat" == "${COUNTRY}" ]; then
    for BRANCH in 83
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;

if [ "pch" == "${COUNTRY}" ]; then
    for BRANCH in 16
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;

if [ "pfr" == "${COUNTRY}" ]; then
    for BRANCH in 43 48
    do
        /software/wss/${COUNTRY}/ksc/load/proc/tpldauftr.sh -start -fil ${BRANCH}        
    done
fi;


