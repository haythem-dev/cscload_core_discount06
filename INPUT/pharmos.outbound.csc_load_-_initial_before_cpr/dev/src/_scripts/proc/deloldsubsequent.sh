#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            devuser                                                                                   
 #Creation-Date:     09.08.2021                                                                                
 #Creation-Time:     13:18                                                                                     
 #Creator:           generate_proc_file - Version: 02.01.00.00                                                 
 #Creation-Type:     ONLINE_SERVER_PROCEDURE                                                                   
 #Purpose:           Starts, stops and status the exemplar binary deloldsubsequent for presentation only.      
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
 . $(dirname $0)/../vars/ksc_load_global.vars

 #--------------------------------------------------------------------#
 # LIBRARY / BINARY VARIABLES
 #--------------------------------------------------------------------#
 readonly BINARY=deloldsubsequent.bin
 process="${BIN_PATH}/${BINARY}"

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 branchno="";
 excludeOrderTypes="";
 includeOrderTypes="";
 typeset -i del=0;
 #--- end declaration procedure variables ---#
 start="";
 stop="";
 status="";
 send="";
 send_val="";
 typeset -i rc=0;

 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";
 readonly SEND_OPTION="-send";
 readonly BRANCHNO_OPTION="-branchno";
 readonly EXCLUDE_OPTION="-excludeOrderTypes";
 readonly INCLUDE_OPTION="-includeOrderTypes";
 readonly DEL_OPTION="-del";

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
 	 printf "%-30s%-90s\n" "\$SEND_OPTION:" ">$SEND_OPTION<"
	 printf "%-30s%-90s\n" "\$BRANCHNO_OPTION:" ">$BRANCHNO_OPTION<"
	 printf "%-30s%-90s\n" "\$EXCLUDE_OPTION:" ">$EXCLUDE_OPTION<"
	 printf "%-30s%-90s\n" "\$INCLUDE_OPTION:" ">$INCLUDE_OPTION<"
	 printf "%-30s%-90s\n" "\$DEL_OPTION:" ">$DEL_OPTION<"

 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
 	 printf "%-30s%-90s\n" "\$send:" ">$send<"
 	 printf "%-30s%-90s\n" "\$send_val:" ">$send_val<"
	 printf "%-30s%-90s\n" "\$branchno:" ">$branchno<"
	 printf "%-30s%-90s\n" "\$excludeOrderTypes:" ">$excludeOrderTypes<"
	 printf "%-30s%-90s\n" "\$includeOrderTypes:" ">$includeOrderTypes<"
	 printf "%-30s%-90s\n" "\$del:" ">$del<"
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
 		 if [[ "$1" == "$START_OPTION" ]]; then start="YES"; shift; continue; fi
 		 if [[ "$1" == "$STOP_OPTION" ]]; then stop="YES"; shift; continue; fi
 		 if [[ "$1" == "$STATUS_OPTION" ]]; then status="YES"; shift; continue; fi

 		 if [[ "$1" == "$SEND_OPTION" ]]; then 
 			 send="YES"; 
 			 shift; 
 			 if (( $# > 0 )); then 
 				 send_val=$1; 
 				 shift; 
 				 continue; 
 			 else 
 				 break; 
 			 fi 
 		 fi

 		 #read in parameters
 		 if [[ "$1" == "$BRANCHNO_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 branchno=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi
 		 
 		 if [[ "$1" == "$EXCLUDE_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 excludeOrderTypes=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

		 if [[ "$1" == "$INCLUDE_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 includeOrderTypes=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$DEL_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 del=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

		break;
 	 done

 	 #--------------------------#
 	 # evaluation of options
 	 #--------------------------#
 	 if [ ! "${start}${stop}${status}${send}" ] ; then 
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
 		 if [[ "${send}" == "YES" ]] ; then
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

 	 if [[ "${send}" == "YES" ]]; then 
 		 if [[ "${send_val}" == "" ]] || (( 1 != `check_send_parameter "${send_val}"` )); then 
 			 printStartStop "${STARTMSG}" 
 			 rc=12; 
 			 echo "${PROCNAME}: Send value missed or invalid value \${send_val}: >${send_val}<!" | tee -a ${LOG_RESOURCE} 
 			 echo ${USAGE} | tee -a ${LOG_RESOURCE} 
 			 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>" 
 			 exit ${rc}; 
 		 fi 
 	 fi

	 #--------------------------#
 	 # evaluation of parameters
 	 #--------------------------#
 	 if [[ "${branchno}" != "" ]]; then
 		 if [[ "${branchno}" == "" ]] || (( 1 != `check_string_parameter "${BRANCHNO_OPTION}" "${branchno}"` )) || [[ "${branchno}" == "0" ]]; then
 			 printStartStop "${STARTMSG}"
 			 rc=12;
 			 echo "${PROCNAME}: Parameter value missed or invalid value \${branchno}: >${branchno}<!" | tee -a ${LOG_RESOURCE}
 			 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 			 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 			 exit ${rc};
 		 fi
 	 fi
 	 
 	 if [[ "${excludeOrderTypes}" != "" ]]; then
 		 if [[ "${excludeOrderTypes}" == "" ]] || (( 1 != `check_string_parameter "${BRANCHNO_OPTION}" "${excludeOrderTypes}"` )) || [[ "${excludeOrderTypes}" == "0" ]]; then
 			 printStartStop "${STARTMSG}"
 			 rc=12;
 			 echo "${PROCNAME}: Parameter value missed or invalid value \${excludeOrderTypes}: >${excludeOrderTypes}<!" | tee -a ${LOG_RESOURCE}
 			 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 			 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 			 exit ${rc};
 		 fi
 	 fi

	 if [[ "${includeOrderTypes}" != "" ]]; then
 		 if [[ "${includeOrderTypes}" == "" ]] || (( 1 != `check_string_parameter "${BRANCHNO_OPTION}" "${includeOrderTypes}"` )) || [[ "${includeOrderTypes}" == "0" ]]; then
 			 printStartStop "${STARTMSG}"
 			 rc=12;
 			 echo "${PROCNAME}: Parameter value missed or invalid value \${includeOrderTypes}: >${includeOrderTypes}<!" | tee -a ${LOG_RESOURCE}
 			 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 			 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 			 exit ${rc};
 		 fi
 	 fi

 	 if (( ${del} > 0 )); then
 		 if [[ "${del}" == "" ]] || (( 1 != `check_numeric_parameter "${DEL_OPTION}" "${del}"` )) || [[ "${del}" == "0" ]]; then
 			 printStartStop "${STARTMSG}"
 			 rc=12;
 			 echo "${PROCNAME}: Parameter value missed or invalid value \${del}: >${del}<!" | tee -a ${LOG_RESOURCE}
 			 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 			 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 			 exit ${rc};
 		 fi
 	 fi

 }
 #======================================================#
 # checks send parameter (signal) value
 #======================================================#
 function check_send_parameter
 {
 	 typeset -r FUNCNAME=check_send_parameter;
 	 typeset -i _rc=0;
 	 typeset -r _SIGNAL=${1};
 	 is_signal_valid "${_SIGNAL}" >/dev/null;
 	 _rc=${?};
 	 echo ${_rc};
 	 return ${_rc};
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

 	 if [[ "${_OPTION}" == "${DEL_OPTION}" ]]; then
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

 	 if [[ "${_OPTION}" == "${BRANCHNO_OPTION}" ]]; then
 		 # do the possibly necessary checks with parameter ${_ARG}
 		 # e.g. database server validity: [a-z]*([a-z]|[1-9])@+([a-z]|[1-9]|[_])_@(shm|tcp)
 		 _rc=1;
 	 fi
 	 
 	 if [[ "${_OPTION}" == "${EXCLUDE_OPTION}" ]]; then
 		 # do the possibly necessary checks with parameter ${_ARG}
 		 # e.g. database server validity: [a-z]*([a-z]|[1-9])@+([a-z]|[1-9]|[_])_@(shm|tcp)
 		 _rc=1;
 	 fi
	
	 if [[ "${_OPTION}" == "${INCLUDE_OPTION}" ]]; then
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
 	 if [[ "$branchno" != "" ]]; then
 		 _parameters="${_parameters} $BRANCHNO_OPTION ";
 		 _parameters="${_parameters} $branchno ";
 	 fi
 	 
 	 if [[ "$excludeOrderTypes" != "" ]]; then
 		 _parameters="${_parameters} $EXCLUDE_OPTION ";
 		 _parameters="${_parameters} $excludeOrderTypes ";
 	 fi

	 if [[ "$includeOrderTypes" != "" ]]; then
 		 _parameters="${_parameters} $INCLUDE_OPTION ";
 		 _parameters="${_parameters} $includeOrderTypes ";
 	 fi

 	 if (( $del > 0 )); then
 		 _parameters="${_parameters} $DEL_OPTION ";
 		 _parameters="${_parameters} $del ";
 	 fi

 	 if (( ${#_parameters} > 0 )); then
 		 _parameters="${_parameters%?}"
 		 _parameters="${_parameters#?}"
 	 fi

 	 if (( ${#ADDITIONAL_PARA} > 0 )); then
 		 if (( ${#_parameters} > 0 )); then
 			 _parameters="${_parameters} ${ADDITIONAL_PARA}";
 		 else
 			 _parameters="${ADDITIONAL_PARA}";
 		 fi
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
 . $(dirname $0)/deloldsubsequent.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";

 # After calling function 'eval_parameters', the additional vars file could be read in,
 # because there parameter are build on the base of passed parameter read in 'eval_parameters'.
 . $(dirname $0)/../vars/deloldsubsequent.vars;

 check_existence_of_binary ${process};
 assembling_process;
 print_msg "$STARTMSG" "$*"
 
 #======================================================#
 # CALLS METHOD START-PROCESS
 #======================================================#
 if [[ "$start" == "YES" ]]; then
 	 msg=`start_process "${process}" `
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
 #======================================================#
 # CALLS METHOD SEND-PROCESS
 #======================================================#
 if [[ "$send" == "YES" ]]; then
 	 msg=`send_process "${process}" "${send_val}"`
 	 rc=$?;
 	 echo "$msg" | tee -a ${LOG_RESOURCE}
 fi


 print_msg "$STOPMSG" "$*" "<$rc>"


 exit ${rc};
