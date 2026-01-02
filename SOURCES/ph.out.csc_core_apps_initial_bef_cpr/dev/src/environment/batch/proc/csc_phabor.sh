#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            devuser                                                                                   
 #Creation-Date:     17.06.2013                                                                                
 #Creation-Time:     13:35                                                                                     
 #Creator:           procgen.sh - Version: 01.00.01.00                                                         
 #Creation-Type:     ONLINE_SERVER_PROCEDURE                                                                   
 #Purpose:           Starts, stops and status the exemplar binary csc_phabor for presentation only.            
 ###############################################################################################

 ###############################################################################################
 # set options
 ###############################################################################################
 #set -a #automatischer Export aller neu angelegten oder veraenderten Variablen (export all);
 #set -e #beendet die Shell, wenn ein Befehl nicht 0 zurueckgibt (exit on error);
 #set -h #sucht und merkt sich die Lage von Kommandos innerhalb von Funktionen (hash function commands)
 #set -n #lese und teste auf syntaktische Korrektheit; fuehre nicht aus (no execution);
 #set -u #gebe eine Fehlermeldung aus bei der Verwendung von undefinierten Variablen, anstatt eine leere Zeichenkette einzusetzen (unset);
 #set -v #zeigt jede Zeile vor ihrer Ausfuehrung unveraendert an (verbose);
 #set -x #zeigt jede Zeile vor ihrer Ausfuehrung jedoch nach ihren Ersetzungen an (xtrace);
 
 ###############################################################################################
 # VARIABLES
 ###############################################################################################
 #--------------------------------------------------------------------#
 # READ IN GLOBAL VARIABLES
 #--------------------------------------------------------------------#
 . $(dirname $0)/../vars/ksc_batch_global.vars

 #--------------------------------------------------------------------#
 # LIBRARY / BINARY VARIABLES
 #--------------------------------------------------------------------#
 readonly OLD_LD_LIBRARY_PATH=${LD_LIBRARY_PATH};
 
 #LIBRARY PATH 
 readonly LIBRARY_PATH=${LIB_PATH}/marathon/ssuk-01.12.01.01/sharedlib/debug:${LIB_PATH}/tcaccess/8.0.11.4/sharedlib/release
 export LD_LIBRARY_PATH=${LIBRARY_PATH}:${LD_LIBRARY_PATH}
 readonly BINARY=csc_phabor.bin
 process="${BIN_PATH}/${BINARY}"

 readonly SCRIPT_CALL="$(cd $(dirname $0);echo $PWD)/$(basename $0) $@"

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 typeset -i branchno=0;
 configfile="";
 typeset -i transfer_flag=0;
 typeset -i process_flag=0;
 typeset -i test_flag=0;
 typeset -i nomail_flag=0;
 #--- end declaration procedure variables ---#
 start="";
 stop="";
 status="";
 export CSC_BRANCHNO=0;
 export CSC_LOGDATE=`date +"%Y%m%d"`;
 typeset -i rc=0;

 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";
 readonly BRANCHNO_OPTION="-branchno";
 readonly CONFIGFILE_OPTION="-configfile";
 readonly TRANSFER_OPTION="-transfer";
 readonly PROCESS_OPTION="-process";
 readonly TEST_OPTION="-test";
 readonly NOMAIL_OPTION="-nomail";

 ###############################################################################################
 # GENERATED FUNCTIONS - BEGIN
 ###############################################################################################
 #====================================#
 # PRINT START-/ STOP-MELDUNG
 #====================================#
 function printStartStop
 {
 	 if [[ "$2" == "" ]]; then set $1 `date +"%d.%m.%y-%H:%M:%S"`; fi
 	 echo "=====================================================================================" | tee -a $LOG_RESOURCE
 	 echo "SH: $1 `pwd`/${PROCNAME} $2" | tee -a $LOG_RESOURCE
 	 echo "=====================================================================================" | tee -a $LOG_RESOURCE
 }
 #====================================#
 # LOG START-/ STOP-MELDUNG
 #====================================#
 function logging
 {
 	 local _branchno=0;
 	 if [[ "${branchno}" != "" ]]; then
 		 _branchno=${branchno};
 	 fi
 	 echo `log "O" "$_branchno" "================================================" "${LOG_RESOURCE}"`
 	 echo `log "O" "$_branchno" "$1" "${LOG_RESOURCE}"`
 	 echo `log "O" "$_branchno" "================================================" "${LOG_RESOURCE}"`
 }
 #======================================================#
 # logging start - printing on console
 #======================================================#
 function print_msg
 {
 	 if [[ "$1" == "$STARTMSG" ]]; then 
 		 printStartStop "$1" "$2" 
 		 logging "$1"; 
 	 else 
 		 local readonly MSG="$1 with Return-Code: <${3}>."
 		 logging "${MSG}";
 		 printStartStop "$1" "$2"
 	 fi
 }
 #====================================#
 # PRINT LOCAL VARIABLES --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED (new variables) <-- 
 #====================================#
 function print_local_var
 {
 	 local FUNCNAME="print_local_var";
 	 echo "--------------------------"
 	 echo "ENTER $FUNCNAME"
 	 echo "--------------------------"
 	 printf "%-30s%-90s\n" "\$MARATHON_SSUK_VERSION:" ">$MARATHON_SSUK_VERSION<"
 	 printf "%-30s%-90s\n" "\$MARATHON_SSUK_LIBRARY_PATH:" ">$MARATHON_SSUK_LIBRARY_PATH<"
 	 printf "%-30s%-90s\n" "\$LD_LIBRARY_PATH:" ">$LD_LIBRARY_PATH<"
 	 printf "%-30s%-90s\n" "\$BINARY:" ">$BINARY<"
 	 printf "%-30s%-90s\n" "\$STARTMSG:" ">$STARTMSG<"
 	 printf "%-30s%-90s\n" "\$STOPMSG:" ">$STOPMSG<"
 	 printf "%-30s%-90s\n" "\$START_OPTION:" ">$START_OPTION<"
 	 printf "%-30s%-90s\n" "\$STOP_OPTION:" ">$STOP_OPTION<"
 	 printf "%-30s%-90s\n" "\$STATUS_OPTION:" ">$STATUS_OPTION<"
	 printf "%-30s%-90s\n" "\$BRANCHNO_OPTION:" ">$BRANCHNO_OPTION<"
	 printf "%-30s%-90s\n" "\$CONFIGFILE_OPTION:" ">$CONFIGFILE_OPTION<"
	 printf "%-30s%-90s\n" "\$TRANSFER_OPTION:" ">$TRANSFER_OPTION<"
	 printf "%-30s%-90s\n" "\$PROCESS_OPTION:" ">$PROCESS_OPTION<"
	 printf "%-30s%-90s\n" "\$TEST_OPTION:" ">$TEST_OPTION<"
	 printf "%-30s%-90s\n" "\$NOMAIL_OPTION:" ">$NOMAIL_OPTION<"

 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
	 printf "%-30s%-90s\n" "\$branchno:" ">$branchno<"
	 printf "%-30s%-90s\n" "\$configfile:" ">$configfile<"
	 printf "%-30s%-90s\n" "\$transfer:" ">$transfer<"
	 printf "%-30s%-90s\n" "\$process:" ">$process<"
	 printf "%-30s%-90s\n" "\$test:" ">$test<"
	 printf "%-30s%-90s\n" "\$nomail:" ">$nomail<"
 	 echo "--------------------------"
 	 echo "EXIT $FUNCNAME"
 	 echo "--------------------------"
 }
 #=============================================#
 # CHECKING IF BINARY is EXISTING 
 #=============================================#
 function check_existence_of_binary
 {
 	 local _PROCESS_2_CHECK=${1};
 	 if [[ ! -f ${_PROCESS_2_CHECK} ]]; then
 		 printStartStop "$STARTMSG"
 		 rc=8;
 		 echo "Error: Binary \"${_PROCESS_2_CHECK}\" does not exist!" | tee -a $LOG_RESOURCE
 		 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 }
 #=============================================#
 # CHECKING IF PARAMETERS ARE BASICALLY SET 
 #=============================================#
 function check_parameters
 {
 	 if (( $# == 0 )); then
 		 printStartStop "$STARTMSG"
 		 rc=9;
 		 echo "Error: No Parameters passed!" | tee -a $LOG_RESOURCE
 		 echo ${USAGE} | tee -a $LOG_RESOURCE
 		 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 }
 #=============================================#
 # READ IN PARAMETERS DISREGARDING THE ORDER --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <-- 
 #=============================================#
 function eval_parameters
 {
 	 #-------------------------------#
 	 # read in options / parameters
 	 #-------------------------------#
 	 while (( $# > 0 )) 
 	 do
 		 #read in options
 		 if [[ "$1" == "$START_OPTION" ]] ; then start="YES"; shift; continue; fi
 		 if [[ "$1" == "$STOP_OPTION" ]] ; then stop="YES"; shift; continue; fi
 		 if [[ "$1" == "$STATUS_OPTION" ]] ; then status="YES"; shift; continue; fi

 		 #read in parameters
 		 if [[ "$1" == "$BRANCHNO_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 branchno=$1;
				 export CSC_BRANCHNO=$branchno;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$CONFIGFILE_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 configfile=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$TRANSFER_OPTION" ]]; then
 			 shift;
			 transfer_flag=1;
			 continue;
 		 fi

 		 if [[ "$1" == "$PROCESS_OPTION" ]]; then
 			 shift;
			 process_flag=1;
			 continue;
 		 fi

 		 if [[ "$1" == "$TEST_OPTION" ]]; then
 			 shift;
			 test_flag=1;
			 continue;
 		 fi

 		 if [[ "$1" == "$NOMAIL_OPTION" ]]; then
 			 shift;
			 nomail_flag=1;
			 continue;
 		 fi

		break;
 	 done

 	 #--------------------------#
 	 # evaluation of options
 	 #--------------------------#
 	 if [ ! "${start}${stop}${status}" ] ; then 
 		 printStartStop "${STARTMSG}"
 		 rc=10;
 		 echo "${PROCNAME}: No options set in command line!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 else 
 		 typeset -i options_counter=0;
 		 if [[ "${start}" == "YES" ]] ; then
 			 options_counter=${options_counter}+1
 		 fi
 		 if [[ "${stop}" == "YES" ]] ; then
 			 options_counter=${options_counter}+1
 		 fi
 		 if [[ "${status}" == "YES" ]] ; then
 			 options_counter=${options_counter}+1
 		 fi
 	 fi
 	 if (( ${options_counter} > 1 )) ; then
 		 printStartStop "${STARTMSG}"
 		 rc=11;
 		 echo "${PROCNAME}: More than one Option is set in command Line!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi

	 #--------------------------#
 	 # evaluation of parameters
 	 #--------------------------#
 	 if [[ "${branchno}" == "" ]] || (( 1 != `check_numeric_parameter "${BRANCHNO_OPTION}" "${branchno}"` )) || [[ "${branchno}" == "0" ]]; then
 		 printStartStop "${STARTMSG}"
 		 rc=12;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${branchno}: >${branchno}<!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 

 	 if [[ "${configfile}" == "" ]] || (( 1 != `check_string_parameter "${CONFIGFILE_OPTION}" "${configfile}"` )); then
 		 printStartStop "${STARTMSG}"
 		 rc=12;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${configfile}: >${configfile}<!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 

 }
 #======================================================#
 # checks numeric parameter --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED (separate validity) <-- 
 #======================================================#
 function check_numeric_parameter
 {
 	 local readonly FUNCNAME=check_numeric_parameter;
 	 local _rc=0;

 	 local readonly _OPTION=${1};
 	 local readonly _ARG=${2};

 	 is_numeric "${_ARG}" "-NO_VERBOSE" # do the checks considered to be necessary
 	 if (( $? == 0 )); then return ${_rc}; fi
 	 _rc=1;

 	 if [[ "${_OPTION}" == "${BRANCHNO_OPTION}" ]]; then
 		 # do the possibly necessary checks with parameter ${_ARG}
 		 _rc=1;
 	 fi

 	 echo ${_rc}
 	 return ${_rc}
 }
 #======================================================#
 # checks string parameter --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED (separate validity) <-- 
 #======================================================#
 function check_string_parameter
 {
 	 local readonly FUNCNAME=check_string_parameter;
 	 local _rc=0;

 	 local readonly _OPTION=${1};
 	 local readonly _ARG=${2};

 	 _rc=1;

 	 if [[ "${_OPTION}" == "${CONFIGFILE_OPTION}" ]]; then
 		 # do the possibly necessary checks with parameter ${_ARG}
 		 # e.g. database server validity: [a-z]*([a-z]|[1-9])@+([a-z]|[1-9]|[_])_@(shm|tcp)
 		 _rc=1;
 	 fi

 	 echo ${_rc}
 	 return ${_rc}
 }
 #======================================================#
 # set parameters with new values of the command line --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED ([optional] parameters) <-- 
 #======================================================#
 function assembling_process
 {
	 local _parameters="";
 	 if (( ${transfer_flag} == 1 )); then
 		 _parameters="${_parameters} $TRANSFER_OPTION";
 	 fi

 	 if (( ${process_flag} == 1 )); then
 		 _parameters="${_parameters} $PROCESS_OPTION";
 	 fi

 	 if (( ${test_flag} == 1 )); then
 		 _parameters="${_parameters} $TEST_OPTION";
 	 fi

 	 if (( ${nomail_flag} == 1 )); then
 		 _parameters="${_parameters} $NOMAIL_OPTION";
 	 fi

 	 if (( ${#_parameters} > 0 )); then
 		 #_parameters="${_parameters%?}"
 		 _parameters="${_parameters#?}"
 	 fi

 	 if (( ${#_parameters} > 0 )); then
 		 _parameters="${_parameters} $BRANCHNO_OPTION $branchno $CONFIGFILE_OPTION $configfile"
 	 else
 		 _parameters="$BRANCHNO_OPTION $branchno $CONFIGFILE_OPTION $configfile";
 	 fi

 	 if (( ${#_parameters} > 0 )); then
 		 process="$process ${_parameters}"
 	 fi

 }
 ###############################################################################################
 # GENERATED FUNCTIONS - END
 ###############################################################################################

 ###############################################################################################
 # INDIVIDUAL FUNCTIONS - BEGIN
 ###############################################################################################
 ###############################################################################################
 # INDIVIDUAL FUNCTIONS - END
 ###############################################################################################

 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/csc_phabor.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";
 check_existence_of_binary ${process};
 assembling_process;
 print_msg "$STARTMSG" "$*"
 
 #======================================================#
 # CALLS METHOD START-PROCESS
 #======================================================#
 if [[ "$start" == "YES" ]]; then
 	 msg=`start_process "${process}" "-NOHUP" "-BG"`
	 rc=$?;
 	 echo "$msg" | tee -a ${LOG_RESOURCE}
 fi
 #======================================================#
 # CALLS METHOD STOP-PROCESS
 #======================================================#
 if [[ "$stop" == "YES" ]]; then
 	 msg=`stop_process "${process}"`
 	 rc=$?;
 	 echo "$msg" | tee -a ${LOG_RESOURCE}
 fi
 #======================================================#
 # CALLS METHOD STATUS-PROCESS
 #======================================================#
 if [[ "$status" == "YES" ]]; then
 	 msg=`status_process "${process}"`
 	 rc=$?;
 	 echo "$msg" | tee -a ${LOG_RESOURCE}
 fi


 print_msg "$STOPMSG" "$*" "<$rc>"


 exit ${rc};
