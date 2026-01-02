#!/bin/ksh
set -x
# start script to aid in starting mainwarehousearticlesrelevantcalculator
# example: start.sh -country DE

MARATHON_DIR=/software/ae/marathon
MARATHON_LOG_CONFIGDIR=mainwarehousearticlesrelevantcalculator export MARATHON_LOG_CONFIGDIR
MARATHON_LOG_LOGSDIR=log export MARATHON_LOG_LOGSDIR

readonly LIBRARY_PATH=${LIB_PATH}/marathon/ssuk-01.12.01.01/sharedlib/debug:${LIB_PATH}/tcaccess/current/sharedlib/release
export LD_LIBRARY_PATH=${LIBRARY_PATH}:${LD_LIBRARY_PATH}

export MWHARTICLES_RELCALC_BRANCHNO=5
gdb --args build/debug/mainwarehousearticlesrelevantcalculator.bin $@
