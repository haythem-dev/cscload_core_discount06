#!/usr/bin/sh
# set -x
###############################################################################################
# installs csc core applications to $HOME/wss/ztst21
###############################################################################################

CWD=`pwd`

# subtargets
PROJECT_KSCSERVER=$CWD/kscserver
PROJECT_CSCSERVICE=$CWD/thrift
PROJECT_AAPSERV=$CWD/aapserv

PROJECT_AAORDERCLOSE=$CWD/aaorderclose
PROJECT_IBTORDERIMPORT=$CWD/ibtorderimport
PROJECT_CLEARRESERVATION=$CWD/clearreservation
PROJECT_CSC_DELI=$CWD/csc_deli
PROJECT_CSC_CORPHA=$CWD/csc_host_interface/csc_corpha
PROJECT_CSC_PHABOR=$CWD/csc_host_interface/csc_phabor
PROJECT_CSC_PHADEX=$CWD/csc_host_interface/csc_phadex
PROJECT_CSC_PHATRA=$CWD/csc_host_interface/csc_phatra

COUNTRIES="at bg ch de fr hr pat pch pfr"	 

###############################################################################################

function install_bin_country
{
	COUNTRY=$1
	HOST='ztst21'
	USER='produser'
	PASSWD='d5XatpAN1Tm7'

	ftp -n -i <<END_SCRIPT
open $HOST
user $USER $PASSWD 
cd /software/wss/$COUNTRY/ksc/server/bin/release

lcd $PROJECT_KSCSERVER/build/debug
put kscserver.bin

lcd $PROJECT_AAPSERV/build/debug
put zaapunix.bin

lcd $PROJECT_CSCSERVICE/build/debug
put cscservice.bin

cd /software/wss/$COUNTRY/ksc/batch/bin/release

lcd $PROJECT_CSC_CORPHA/build/debug
put csc_corpha.bin

lcd $PROJECT_CSC_PHATRA/build/debug
put csc_phatra.bin

lcd $PROJECT_CSC_PHADEX/build/debug
put csc_phadex.bin

lcd $PROJECT_CSC_PHABOR/build/debug
put csc_phabor.bin

lcd $PROJECT_AAORDERCLOSE/build/debug
put aaorderclose.R.bin

lcd $PROJECT_CSC_DELI/csc_deli/build/debug
put csc_deli.bin

lcd $PROJECT_IBTORDERIMPORT/build/debug
put ibtorderimport.bin

lcd $PROJECT_CLEARRESERVATION/build/debug
put clearreservation.bin

disconnect
quit
END_SCRIPT
}


if [[ $# == 1 ]]; then
	install_bin_country $1
else
	for country in $COUNTRIES; do
		install_bin_country $country
	done
fi

