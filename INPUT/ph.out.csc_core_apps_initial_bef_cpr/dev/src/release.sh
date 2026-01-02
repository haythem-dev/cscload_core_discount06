#! /usr/bin/ksh

set -e

function copynewversion
{
	local readonly _SOURCE=${1};
	local readonly _TARGET=${2};
	echo "   copying ${_SOURCE} to ${_TARGET}";
	rm -f ${_TARGET};
	cp ${_SOURCE} ${_TARGET};
	chmod 777 ${_TARGET};	
	touch ${_TARGET};
}

function copynewversiondos2unix
{
	local readonly _SOURCE=${1};
	local readonly _TARGET=${2};	
	copynewversion ${_SOURCE} ${_TARGET};
	dos2unix ${_TARGET} ${_TARGET};
}

function check_create_dir 
{
	DIRECTORY=$1

	if [[ ! -d $DIRECTORY ]]; then
		mkdir -p $DIRECTORY;
	fi
}

CWD=$(dirname $0);
BINSOURCE=$1;

VERSION=`grep CSC_CORE_APPLICATIONS_VERSION pxverbund/include/pxverbund_version.h | cut -f 3 -d ' ' | cut -b2-10`
BIN_TARGET="${WSS}/release/ksc/$VERSION/bin";
SCRIPT_TARGET="${WSS}/release/ksc/$VERSION/proc";
INI_TARGET="${WSS}/release/ksc/$VERSION/ini";

echo "BIN_TARGET=$BIN_TARGET"
echo "SCRIPT_TARGET=$SCRIPT_TARGET"
echo "INI_TARGET=$INI_TARGET"

check_create_dir $BIN_TARGET
check_create_dir $SCRIPT_TARGET
check_create_dir $INI_TARGET

if [ "${BINSOURCE}" != "release" ]; then BINSOURCE="debug"; fi;
echo "SOURCE: */build/${BINSOURCE} BIN-TARGET: ${BIN_TARGET}!";

###############################################################################################################################
# copy files to BIN_TARGET
###############################################################################################################################
copynewversion "${CWD}/aaorderclose/build/${BINSOURCE}/aaorderclose.R.bin" 				"${BIN_TARGET}/aaorderclose.R.bin";
copynewversion "${CWD}/aapserv/build/${BINSOURCE}/zaapunix.bin" 						"${BIN_TARGET}/zaapunix.bin";
copynewversion "${CWD}/clearreservation/build/${BINSOURCE}/clearreservation.bin" 		"${BIN_TARGET}/clearreservation.bin";
copynewversion "${CWD}/csc_deli/csc_deli/build/${BINSOURCE}/csc_deli.bin" 				"${BIN_TARGET}/csc_deli.bin";
copynewversion "${CWD}/csc_host_interface/csc_corpha/build/${BINSOURCE}/csc_corpha.bin" "${BIN_TARGET}/csc_corpha.bin";
copynewversion "${CWD}/csc_host_interface/csc_phabor/build/${BINSOURCE}/csc_phabor.bin" "${BIN_TARGET}/csc_phabor.bin";
copynewversion "${CWD}/csc_host_interface/csc_phatra/build/${BINSOURCE}/csc_phatra.bin" "${BIN_TARGET}/csc_phatra.bin";
copynewversion "${CWD}/ibtorderimport/build/${BINSOURCE}/ibtorderimport.bin" 			"${BIN_TARGET}/ibtorderimport.bin";
copynewversion "${CWD}/kscserver/build/${BINSOURCE}/kscserver.bin" 						"${BIN_TARGET}/kscserver.bin";
copynewversion "${CWD}/kscserver/build/${BINSOURCE}/kscserver.bin" 						"${BIN_TARGET}/kscserverLN.bin";
copynewversion "${CWD}/kscserver/build/${BINSOURCE}/kscserver.bin" 						"${BIN_TARGET}/kscserverLS.bin";
copynewversion "${CWD}/kscserver/build/${BINSOURCE}/kscserver.bin" 						"${BIN_TARGET}/kscserverXmlNord.bin";
copynewversion "${CWD}/kscserver/build/${BINSOURCE}/kscserver.bin" 						"${BIN_TARGET}/kscserverXmlSued.bin";
copynewversion "${CWD}/thrift/build/${BINSOURCE}/cscservice.bin" 						"${BIN_TARGET}/cscservice.bin";
copynewversion "${CWD}/thrift/build/${BINSOURCE}/cscservice.bin" 						"${BIN_TARGET}/cscserviceLN.bin";
copynewversion "${CWD}/thrift/build/${BINSOURCE}/cscservice.bin" 						"${BIN_TARGET}/cscserviceLS.bin";
copynewversion "${CWD}/vborderimport2/build/${BINSOURCE}/vborderimport2.bin" 			"${BIN_TARGET}/vborderimport2.bin";

###############################################################################################################################
# copy files to SCRIPTS_TARGET
###############################################################################################################################
copynewversion "${CWD}/aaorderclose/proc/aaordclose.sh"                          		"${SCRIPT_TARGET}/aaordclose.sh";
copynewversion "${CWD}/aapserv/proc/zaapunix.sh"                                 		"${SCRIPT_TARGET}/zaapunix.sh";
copynewversion "${CWD}/clearreservation/proc/clearreservation.sh"                		"${SCRIPT_TARGET}/clearreservation.sh";
copynewversion "${CWD}/csc_deli/proc/csc_deli.sh"                    			 		"${SCRIPT_TARGET}/csc_deli.sh";
copynewversion "${CWD}/csc_host_interface/kscrefresh_scripts/proc/csc_corpha.sh" 		"${SCRIPT_TARGET}/csc_corpha.sh";
copynewversion "${CWD}/csc_host_interface/kscrefresh_scripts/proc/csc_phatra.sh" 		"${SCRIPT_TARGET}/csc_phatra.sh";
copynewversion "${CWD}/csc_host_interface/kscrefresh_scripts/proc/csc_phabor.sh" 		"${SCRIPT_TARGET}/csc_phabor.sh";
copynewversion "${CWD}/ibtorderimport/unix/ibtorderimport.sh"                    		"${SCRIPT_TARGET}/ibtorderimport.sh";
copynewversion "${CWD}/kscserver/proc/kscserver.sh"                              		"${SCRIPT_TARGET}/kscserver.sh";
copynewversion "${CWD}/kscserver/proc/kscserverLN.sh"                            		"${SCRIPT_TARGET}/kscserverLN.sh";
copynewversion "${CWD}/kscserver/proc/kscserverLS.sh"                            		"${SCRIPT_TARGET}/kscserverLS.sh";
copynewversion "${CWD}/kscserver/proc/kscserverXmlNord.sh"                       		"${SCRIPT_TARGET}/kscserverXmlNord.sh";
copynewversion "${CWD}/kscserver/proc/kscserverXmlSued.sh"                       		"${SCRIPT_TARGET}/kscserverXmlSued.sh";
copynewversion "${CWD}/thrift/proc/cscservice.sh"                                		"${SCRIPT_TARGET}/cscservice.sh";
copynewversion "${CWD}/thrift/proc/cscserviceLN.sh"                              		"${SCRIPT_TARGET}/cscserviceLN.sh";
copynewversion "${CWD}/thrift/proc/cscserviceLS.sh"                              		"${SCRIPT_TARGET}/cscserviceLS.sh";
copynewversion "${CWD}/vborderimport2/proc/vbordimport2.sh"                      		"${SCRIPT_TARGET}/vbordimport2.sh";

###############################################################################################################################
# copy files to INI_TARGET
###############################################################################################################################
copynewversiondos2unix "${CWD}/pxverbund/files/message.txt"                              "${INI_TARGET}/message.txt";

exit;
