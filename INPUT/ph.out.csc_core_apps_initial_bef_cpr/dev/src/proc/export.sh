#! /usr/bin/ksh

#set -x

CWD=`pwd`
EXPORT_DIR=${CWD}/../../export/csc_core_applications
BINSOURCE="debug"

function copynewversion
{
    local readonly _SOURCE=${1};
    local readonly _TARGET=${2};
    echo "   copying ${_SOURCE} to ${_TARGET}";
    rm -rf ${_TARGET};
    cp -f ${_SOURCE} ${_TARGET};
    chmod 777 ${_TARGET};
    touch ${_TARGET};
}


rm -rf ${EXPORT_DIR}
mkdir -p ${EXPORT_DIR}


function copy_binaries
{
    BATCH_PROC_DIR=${EXPORT_DIR}/batch/proc
    BATCH_BIN_DIR=${EXPORT_DIR}/batch/bin/release
    SERVER_BIN_DIR=${EXPORT_DIR}/server/bin/release
    mkdir -p ${BATCH_BIN_DIR}
    mkdir -p ${SERVER_BIN_DIR}
    echo "Copy binaries... "

    copynewversion "${CWD}/aaorderclose/build/${BINSOURCE}/aaorderclose.R.bin"              "${BATCH_BIN_DIR}/aaorderclose.R.bin";
    copynewversion "${CWD}/clearreservation/build/${BINSOURCE}/clearreservation.bin"        "${BATCH_BIN_DIR}/clearreservation.bin";

    copynewversion "${CWD}/csc_host_interface/csc_corpha/build/${BINSOURCE}/csc_corpha.bin" "${BATCH_BIN_DIR}/csc_corpha.bin";
    copynewversion "${CWD}/csc_host_interface/csc_phabor/build/${BINSOURCE}/csc_phabor.bin" "${BATCH_BIN_DIR}/csc_phabor.bin";
    copynewversion "${CWD}/csc_host_interface/csc_phatra/build/${BINSOURCE}/csc_phatra.bin" "${BATCH_BIN_DIR}/csc_phatra.bin";
    copynewversion "${CWD}/csc_host_interface/csc_phadex/build/${BINSOURCE}/csc_phadex.bin" "${BATCH_BIN_DIR}/csc_phadex.bin";

    copynewversion "${CWD}/ibtorderimport/build/${BINSOURCE}/ibtorderimport.bin"            "${BATCH_BIN_DIR}/ibtorderimport.bin";

    copynewversion "${CWD}/csc_deli/csc_deli/build/${BINSOURCE}/csc_deli.bin"               "${BATCH_BIN_DIR}/csc_deli.bin";

    copynewversion "${CWD}/kscserver/build/${BINSOURCE}/kscserver.bin"                      "${SERVER_BIN_DIR}/kscserver.bin";
    copynewversion "${CWD}/aapserv/build/${BINSOURCE}/zaapunix.bin"                         "${SERVER_BIN_DIR}/zaapunix.bin";
    copynewversion "${CWD}/thrift/build/${BINSOURCE}/cscservice.bin"                        "${SERVER_BIN_DIR}/cscservice.bin";
}


###############################################################################################################################
# copy files to SCRIPTS_TARGET
###############################################################################################################################
function copy_scripts
{
    BATCH_PROC_DIR=${EXPORT_DIR}/batch/proc
    SERVER_PROC_DIR=${EXPORT_DIR}/server/proc
    mkdir -p ${BATCH_PROC_DIR}
    mkdir -p ${SERVER_PROC_DIR}
    echo "Copy scripts... "

    copynewversion "${CWD}/environment/batch/proc/aaordclose.sh"                            "${BATCH_PROC_DIR}/aaordclose.sh";
    copynewversion "${CWD}/environment/batch/proc/aaordclose.option"                        "${BATCH_PROC_DIR}/aaordclose.option";
    copynewversion "${CWD}/environment/batch/proc/clearreservation.sh"                      "${BATCH_PROC_DIR}/clearreservation.sh";
    copynewversion "${CWD}/environment/batch/proc/clearreservation.option"                  "${BATCH_PROC_DIR}/clearreservation.option";
    copynewversion "${CWD}/environment/batch/proc/csc_deli.sh"                              "${BATCH_PROC_DIR}/csc_deli.sh";
    copynewversion "${CWD}/environment/batch/proc/csc_deli.option"                          "${BATCH_PROC_DIR}/csc_deli.option";
    copynewversion "${CWD}/environment/batch/proc/csc_corpha.sh"                            "${BATCH_PROC_DIR}/csc_corpha.sh";
    copynewversion "${CWD}/environment/batch/proc/csc_corpha.option"                        "${BATCH_PROC_DIR}/csc_corpha.option";
    copynewversion "${CWD}/environment/batch/proc/csc_phatra.sh"                            "${BATCH_PROC_DIR}/csc_phatra.sh";
    copynewversion "${CWD}/environment/batch/proc/csc_phatra.option"                        "${BATCH_PROC_DIR}/csc_phatra.option";
    copynewversion "${CWD}/environment/batch/proc/csc_phabor.sh"                            "${BATCH_PROC_DIR}/csc_phabor.sh";
    copynewversion "${CWD}/environment/batch/proc/csc_phabor.option"                        "${BATCH_PROC_DIR}/csc_phabor.option";
    copynewversion "${CWD}/environment/batch/proc/csc_phadex.sh"                            "${BATCH_PROC_DIR}/csc_phadex.sh";
    copynewversion "${CWD}/environment/batch/proc/csc_phadex.option"                        "${BATCH_PROC_DIR}/csc_phadex.option";
    copynewversion "${CWD}/environment/batch/proc/csc_prune.pl"                             "${BATCH_PROC_DIR}/csc_prune.pl";
    copynewversion "${CWD}/environment/batch/proc/ibtorderimport.sh"                        "${BATCH_PROC_DIR}/ibtorderimport.sh";
    copynewversion "${CWD}/environment/batch/proc/ibtorderimport.option"                    "${BATCH_PROC_DIR}/ibtorderimport.option";
    copynewversion "${CWD}/environment/batch/proc/vbordimport2.sh"                          "${BATCH_PROC_DIR}/vbordimport2.sh";
    copynewversion "${CWD}/environment/batch/proc/vbordimport2.option"                      "${BATCH_PROC_DIR}/vbordimport2.option";

    copynewversion "${CWD}/environment/server/proc/kscserver.sh"                            "${SERVER_PROC_DIR}/kscserver.sh";
    copynewversion "${CWD}/environment/server/proc/kscserver.option"                        "${SERVER_PROC_DIR}/kscserver.option";
    copynewversion "${CWD}/environment/server/proc/kscserverLN.sh"                          "${SERVER_PROC_DIR}/kscserverLN.sh";
    copynewversion "${CWD}/environment/server/proc/kscserverLN.option"                      "${SERVER_PROC_DIR}/kscserverLN.option";
    copynewversion "${CWD}/environment/server/proc/kscserverXmlNord.sh"                     "${SERVER_PROC_DIR}/kscserverXmlNord.sh";
    copynewversion "${CWD}/environment/server/proc/kscserverXmlNord.option"                 "${SERVER_PROC_DIR}/kscserverXmlNord.option";
    copynewversion "${CWD}/environment/server/proc/cscservice.sh"                           "${SERVER_PROC_DIR}/cscservice.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice.option"                       "${SERVER_PROC_DIR}/cscservice.option";
    copynewversion "${CWD}/environment/server/proc/cscserviceLN.sh"                         "${SERVER_PROC_DIR}/cscserviceLN.sh";
    copynewversion "${CWD}/environment/server/proc/cscserviceLN.option"                     "${SERVER_PROC_DIR}/cscserviceLN.option";
    copynewversion "${CWD}/environment/server/proc/zaapunix.sh"                             "${SERVER_PROC_DIR}/zaapunix.sh";
    copynewversion "${CWD}/environment/server/proc/zaapunix.option"                         "${SERVER_PROC_DIR}/zaapunix.option";
    copynewversion "${CWD}/environment/server/proc/cscservice70.sh"                         "${SERVER_PROC_DIR}/cscservice70.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice70.option"                     "${SERVER_PROC_DIR}/cscservice70.option";
    copynewversion "${CWD}/environment/server/proc/cscservice71.sh"                         "${SERVER_PROC_DIR}/cscservice71.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice71.option"                     "${SERVER_PROC_DIR}/cscservice71.option";
    copynewversion "${CWD}/environment/server/proc/cscservice72.sh"                         "${SERVER_PROC_DIR}/cscservice72.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice72.option"                     "${SERVER_PROC_DIR}/cscservice72.option";
    copynewversion "${CWD}/environment/server/proc/cscservice73.sh"                         "${SERVER_PROC_DIR}/cscservice73.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice73.option"                     "${SERVER_PROC_DIR}/cscservice73.option";
    copynewversion "${CWD}/environment/server/proc/cscservice74.sh"                         "${SERVER_PROC_DIR}/cscservice74.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice74.option"                     "${SERVER_PROC_DIR}/cscservice74.option";
    copynewversion "${CWD}/environment/server/proc/cscservice75.sh"                         "${SERVER_PROC_DIR}/cscservice75.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice75.option"                     "${SERVER_PROC_DIR}/cscservice75.option";
    copynewversion "${CWD}/environment/server/proc/cscservice76.sh"                         "${SERVER_PROC_DIR}/cscservice76.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice76.option"                     "${SERVER_PROC_DIR}/cscservice76.option";
    copynewversion "${CWD}/environment/server/proc/cscservice77.sh"                         "${SERVER_PROC_DIR}/cscservice77.sh";
    copynewversion "${CWD}/environment/server/proc/cscservice77.option"                     "${SERVER_PROC_DIR}/cscservice77.option";
}

###############################################################################################################################
# copy files to INI_TARGET
###############################################################################################################################
function copy_inis
{
    BATCH_INI_DIR=${EXPORT_DIR}/batch/ini
    SERVER_INI_DIR=${EXPORT_DIR}/server/ini
    mkdir -p ${BATCH_INI_DIR}
    mkdir -p ${SERVER_INI_DIR}
    echo "Copy inis... "

    copynewversion "${CWD}/pxverbund/files/message.txt"                                     "${BATCH_INI_DIR}/message.txt";
    copynewversion "${CWD}/environment/batch/ini/prod/aaorderclose.R.cfg"                   "${BATCH_INI_DIR}/aaorderclose.R.cfg";
    copynewversion "${CWD}/environment/batch/ini/prod/clearreservation.cfg"                 "${BATCH_INI_DIR}/clearreservation.cfg";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_deli.cfg"                         "${BATCH_INI_DIR}/csc_deli.cfg";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.cfg"                       "${BATCH_INI_DIR}/csc_corpha.cfg";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.at"                    "${BATCH_INI_DIR}/csc_corpha.xml.at";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.bg"                    "${BATCH_INI_DIR}/csc_corpha.xml.bg";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.ch"                    "${BATCH_INI_DIR}/csc_corpha.xml.ch";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.de"                    "${BATCH_INI_DIR}/csc_corpha.xml.de";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.fr"                    "${BATCH_INI_DIR}/csc_corpha.xml.fr";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.hr"                    "${BATCH_INI_DIR}/csc_corpha.xml.hr";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.pat"                   "${BATCH_INI_DIR}/csc_corpha.xml.pat";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.pch"                   "${BATCH_INI_DIR}/csc_corpha.xml.pch";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.pfr"                   "${BATCH_INI_DIR}/csc_corpha.xml.pfr";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_corpha.xml.rs"                    "${BATCH_INI_DIR}/csc_corpha.xml.rs";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_phatra.cfg"                       "${BATCH_INI_DIR}/csc_phatra.cfg";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_phatra.xml.at"                    "${BATCH_INI_DIR}/csc_phatra.xml.at";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_phatra.xml.ch"                    "${BATCH_INI_DIR}/csc_phatra.xml.ch";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_phabor.cfg"                       "${BATCH_INI_DIR}/csc_phabor.cfg";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_phabor.xml.at"                    "${BATCH_INI_DIR}/csc_phabor.xml.at";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_phadex.cfg"                       "${BATCH_INI_DIR}/csc_phadex.cfg";
    copynewversion "${CWD}/environment/batch/ini/prod/csc_phadex.xml.at"                    "${BATCH_INI_DIR}/csc_phadex.xml.at";
    copynewversion "${CWD}/environment/batch/ini/prod/ibtorderimport.cfg"                   "${BATCH_INI_DIR}/ibtorderimport.cfg";
    copynewversion "${CWD}/environment/batch/ini/prod/vborderimport2.cfg"                   "${BATCH_INI_DIR}/vborderimport2.cfg";

    copynewversion "${CWD}/pxverbund/files/message.txt"                                     "${SERVER_INI_DIR}/message.txt";
    copynewversion "${CWD}/environment/server/ini/prod/kscserver.cfg"                       "${SERVER_INI_DIR}/kscserver.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/kscserver.cfg"                       "${SERVER_INI_DIR}/kscserverLN.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/kscserver.cfg"                       "${SERVER_INI_DIR}/kscserverXmlNord.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscserviceLN.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice70.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice71.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice72.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice73.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice74.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice75.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice76.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.cfg"                      "${SERVER_INI_DIR}/cscservice77.cfg";
    copynewversion "${CWD}/environment/server/ini/prod/zaapunix.cfg"                        "${SERVER_INI_DIR}/zaapunix.cfg";

    copynewversion "${CWD}/environment/server/ini/prod/kscserver.ini.LN"                    "${SERVER_INI_DIR}/kscserver.ini.LN";
    copynewversion "${CWD}/environment/server/ini/prod/kscserver.ini.XmlNord"               "${SERVER_INI_DIR}/kscserver.ini.XmlNord";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.at"                   "${SERVER_INI_DIR}/cscservice.ini.at";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.bg"                   "${SERVER_INI_DIR}/cscservice.ini.bg";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.ch"                   "${SERVER_INI_DIR}/cscservice.ini.ch";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.de"                   "${SERVER_INI_DIR}/cscservice.ini.de";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.fr"                   "${SERVER_INI_DIR}/cscservice.ini.fr";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.hr"                   "${SERVER_INI_DIR}/cscservice.ini.hr";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.pat"                  "${SERVER_INI_DIR}/cscservice.ini.pat";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.pch"                  "${SERVER_INI_DIR}/cscservice.ini.pch";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.pfr"                  "${SERVER_INI_DIR}/cscservice.ini.pfr";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.rs"                   "${SERVER_INI_DIR}/cscservice.ini.rs";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.LN"                   "${SERVER_INI_DIR}/cscservice.ini.LN";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.70"                   "${SERVER_INI_DIR}/cscservice.ini.70";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.71"                   "${SERVER_INI_DIR}/cscservice.ini.71";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.72"                   "${SERVER_INI_DIR}/cscservice.ini.72";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.73"                   "${SERVER_INI_DIR}/cscservice.ini.73";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.74"                   "${SERVER_INI_DIR}/cscservice.ini.74";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.75"                   "${SERVER_INI_DIR}/cscservice.ini.75";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.76"                   "${SERVER_INI_DIR}/cscservice.ini.76";
    copynewversion "${CWD}/environment/server/ini/prod/cscservice.ini.77"                   "${SERVER_INI_DIR}/cscservice.ini.77";
}

###############################################################################################################################
# copy files to VARS_TARGET
###############################################################################################################################
function copy_vars
{
    BATCH_VARS_DIR=${EXPORT_DIR}/batch/vars
    SERVER_VARS_DIR=${EXPORT_DIR}/server/vars
    mkdir -p ${BATCH_VARS_DIR}
    mkdir -p ${SERVER_VARS_DIR}
    echo "Copy vars... "

    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.at"                    "${BATCH_VARS_DIR}/ksc_batch_global.vars.at";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.bg"                    "${BATCH_VARS_DIR}/ksc_batch_global.vars.bg";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.ch"                    "${BATCH_VARS_DIR}/ksc_batch_global.vars.ch";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.de"                    "${BATCH_VARS_DIR}/ksc_batch_global.vars.de";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.fr"                    "${BATCH_VARS_DIR}/ksc_batch_global.vars.fr";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.hr"                    "${BATCH_VARS_DIR}/ksc_batch_global.vars.hr";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.pat"                   "${BATCH_VARS_DIR}/ksc_batch_global.vars.pat";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.pch"                   "${BATCH_VARS_DIR}/ksc_batch_global.vars.pch";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.pfr"                   "${BATCH_VARS_DIR}/ksc_batch_global.vars.pfr";
    copynewversion "${CWD}/environment/batch/vars/prod/ksc_batch_global.vars.rs"                    "${BATCH_VARS_DIR}/ksc_batch_global.vars.rs";
    copynewversion "${CWD}/environment/batch/vars/prod/csc_corpha.vars"                             "${BATCH_VARS_DIR}/csc_corpha.vars";
    copynewversion "${CWD}/environment/batch/vars/prod/csc_phatra.vars"                             "${BATCH_VARS_DIR}/csc_phatra.vars";
    copynewversion "${CWD}/environment/batch/vars/prod/csc_phabor.vars"                             "${BATCH_VARS_DIR}/csc_phabor.vars";
    copynewversion "${CWD}/environment/batch/vars/prod/csc_phadex.vars"                             "${BATCH_VARS_DIR}/csc_phadex.vars";

    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.at"                  "${SERVER_VARS_DIR}/ksc_server_global.vars.at";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.bg"                  "${SERVER_VARS_DIR}/ksc_server_global.vars.bg";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.ch"                  "${SERVER_VARS_DIR}/ksc_server_global.vars.ch";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.de"                  "${SERVER_VARS_DIR}/ksc_server_global.vars.de";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.fr"                  "${SERVER_VARS_DIR}/ksc_server_global.vars.fr";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.hr"                  "${SERVER_VARS_DIR}/ksc_server_global.vars.hr";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.pat"                 "${SERVER_VARS_DIR}/ksc_server_global.vars.pat";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.pch"                 "${SERVER_VARS_DIR}/ksc_server_global.vars.pch";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.pfr"                 "${SERVER_VARS_DIR}/ksc_server_global.vars.pfr";
    copynewversion "${CWD}/environment/server/vars/prod/ksc_server_global.vars.rs"                  "${SERVER_VARS_DIR}/ksc_server_global.vars.rs";

    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.at"                         "${SERVER_VARS_DIR}/cscservice.vars.at";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.bg"                         "${SERVER_VARS_DIR}/cscservice.vars.bg";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.ch"                         "${SERVER_VARS_DIR}/cscservice.vars.ch";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.de"                         "${SERVER_VARS_DIR}/cscservice.vars.de";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.fr"                         "${SERVER_VARS_DIR}/cscservice.vars.fr";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.hr"                         "${SERVER_VARS_DIR}/cscservice.vars.hr";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.pat"                        "${SERVER_VARS_DIR}/cscservice.vars.pat";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.pch"                        "${SERVER_VARS_DIR}/cscservice.vars.pch";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.pfr"                        "${SERVER_VARS_DIR}/cscservice.vars.pfr";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice.vars.rs"                         "${SERVER_VARS_DIR}/cscservice.vars.rs";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice70.vars"                          "${SERVER_VARS_DIR}/cscservice70.vars";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice71.vars"                          "${SERVER_VARS_DIR}/cscservice71.vars";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice72.vars"                          "${SERVER_VARS_DIR}/cscservice72.vars";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice73.vars"                          "${SERVER_VARS_DIR}/cscservice73.vars";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice74.vars"                          "${SERVER_VARS_DIR}/cscservice74.vars";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice75.vars"                          "${SERVER_VARS_DIR}/cscservice75.vars";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice76.vars"                          "${SERVER_VARS_DIR}/cscservice76.vars";
    copynewversion "${CWD}/environment/server/vars/prod/cscservice77.vars"                          "${SERVER_VARS_DIR}/cscservice77.vars";
    copynewversion "${CWD}/environment/server/vars/prod/cscserviceLN.vars"                          "${SERVER_VARS_DIR}/cscserviceLN.vars";
}

###############################################################################################################################
# create csc_core_applications artifact
###############################################################################################################################
copy_binaries
copy_scripts
copy_inis
copy_vars

TARBALL=csc_core_applications.tar.gz

echo "--- tar ${EXPORT_DIR}/${TARBALL} ..."
cd ${EXPORT_DIR}
TARDIRS=`ls -d */`
gtar -czf ./${TARBALL} ${TARDIRS}
rm -rf ${TARDIRS}
echo "--- tarball contains:"
gtar -tzf ./${TARBALL} ${TARDIRS}
cd ${CWD}


###############################################################################################################################
# create csc_service_idl artifact
###############################################################################################################################

mkdir -p ${EXPORT_DIR}/idl
cp -f thrift/idl/*.thrift ${EXPORT_DIR}/idl

mkdir -p ${EXPORT_DIR}/idl/types
cp -f pxverbund/include/types/*.inc ${EXPORT_DIR}/idl/types

cd ${EXPORT_DIR}
zip  ./csc_service_idl.zip ./idl/* ./idl/types/*
rm -rf ./idl
cd ${CWD}

###############################################################################################################################
# create csc_legacy_idl artifact
###############################################################################################################################

mkdir -p ${EXPORT_DIR}/idl/kscserver

cp -f kscserver/articleinfostruct.h         ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/articleinquiry.h            ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/articleinquirybulk.h        ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/callbackdivisioninquiry.h   ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/callbackinquiry.h           ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/callbackreasoninquiry.h     ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/kscsrv.h                    ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/kscsrvdata.h                ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/kscsrvfkt.h                 ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/newcallback.h               ${EXPORT_DIR}/idl/kscserver
cp -f kscserver/newcallbackcritpos.h        ${EXPORT_DIR}/idl/kscserver

cd ${EXPORT_DIR}
zip  ./csc_legacy_idl.zip ./idl/kscserver/*
rm -rf ./idl
cd ${CWD}

cp -f ivy.xml       ${EXPORT_DIR}
cp -f build.xml     ${EXPORT_DIR}
cp -f proc/deploy_zdev.ps1  ${EXPORT_DIR}
