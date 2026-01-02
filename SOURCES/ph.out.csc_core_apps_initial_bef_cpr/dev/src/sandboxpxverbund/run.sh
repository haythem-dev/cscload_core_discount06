#! /usr/bin/ksh

# -------------------------------------------------------------------------
. /software/etc/profile_prz
# -------------------------------------------------------------------------

export MARATHON_LOG_CONFIGDIR=$(dirname $0)
export MARATHON_LOG_LOGSDIR=$(dirname $0)/build/debug

#LIBRARY PATH
readonly LIBRARY_PATH=${LIB_PATH}/marathon/ssuk-01.12.01.01/sharedlib/debug:${LIB_PATH}/tcaccess/8.0.11.4/sharedlib/release
export LD_LIBRARY_PATH=${LIBRARY_PATH}:${LD_LIBRARY_PATH}

$(dirname $0)/build/debug/sandboxpxverbund.bin $*
