#! /usr/bin/ksh

. $(dirname $0)/../vars/ksc_batch_global.vars
readonly OLD_LD_LIBRARY_PATH=${LD_LIBRARY_PATH};
 
export CSC_PHABOR_BRANCHNO='gdb';
export CSC_PHABOR_FILTER='gdb';
export CSC_PHABOR_DATE='gdb';

readonly LIBRARY_PATH=${LIB_PATH}/marathon/ssuk-01.10.01.00/sharedlib/debug:${LIB_PATH}/tcaccess/current/sharedlib/release:${LIB_PATH}/icu/50.1.2_1/lib
export LD_LIBRARY_PATH=${LIBRARY_PATH}:${LD_LIBRARY_PATH}
readonly BINARY=csc_phabor.bin
process="${BIN_PATH}/${BINARY}"

echo $CLIENT_LOCALE
gdb ${process}
