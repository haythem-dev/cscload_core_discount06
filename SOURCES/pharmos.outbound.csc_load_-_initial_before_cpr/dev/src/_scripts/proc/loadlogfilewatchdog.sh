#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            devuser                                                                                   
 #Creation-Date:     23.01.2025                                                                                
 #Creation-Time:     06:45                                                                                     
 #Creator:           generate_proc_file - Version: 02.01.00.00                                                 
 #Creation-Type:     ONLINE_SERVER_PROCEDURE                                                                   
 #Purpose:           Starts, stops and status the exemplar binary LogfileWatchdog for presentation only.        
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

 . $(dirname $0)/../vars/monitoring_global.vars

 #--------------------------------------------------------------------#
 # LIBRARY / BINARY VARIABLES
 #--------------------------------------------------------------------#
 readonly BINARY=logfilewatchdog.bin
 process="${BIN_PATH}/${BINARY}"
 readonly SCRIPT_CALL="$(cd $(dirname $0);echo $PWD)/$(basename $0) $@"
 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 start="";
 stop="";
 status="";
 inifile="";
 inifile_val="";
 runtime="";
 runtime_val="";
 sleep="";
 sleep_val="";
 typeset -i rc=0;

 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";
 readonly INIFILE_OPTION="-inifile";
 readonly RUNTIME_OPTION="-runtime";
 readonly SLEEP_OPTION="-sleep";

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
 	 printf "%-30s%-90s\n" "\$INIFILE_OPTION:" ">$INIFILE_OPTION<"
 	 printf "%-30s%-90s\n" "\$RUNTIME_OPTION:" ">$RUNTIME_OPTION<"
 	 printf "%-30s%-90s\n" "\$SLEEP_OPTION:" ">$SLEEP_OPTION<"

 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
 	 printf "%-30s%-90s\n" "\$inifile:" ">$inifile<"
 	 printf "%-30s%-90s\n" "\$inifile_val:" ">$inifile_val<"
 	 printf "%-30s%-90s\n" "\$runtime:" ">$runtime<"
 	 printf "%-30s%-90s\n" "\$runtime_val:" ">$runtime_val<"
 	 printf "%-30s%-90s\n" "\$sleep:" ">$sleep<"
 	 printf "%-30s%-90s\n" "\$sleep_val:" ">$sleep_val<"

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

 		 if [[ "$1" == "$INIFILE_OPTION" ]]; then 
 			 inifile="YES"; 
 			 shift; 
 			 if (( $# > 0 )); then 
 				 inifile_val=$1; 
 				 shift; 
 				 continue; 
 			 else 
 				 break; 
 			 fi 
 		 fi

 		 if [[ "$1" == "$RUNTIME_OPTION" ]]; then 
 			 runtime="YES"; 
 			 shift; 
 			 if (( $# > 0 )); then 
 				 runtime_val=$1; 
 				 shift; 
 				 continue; 
 			 else 
 				 break; 
 			 fi 
 		 fi

 		 if [[ "$1" == "$SLEEP_OPTION" ]]; then 
 			 sleep="YES"; 
 			 shift; 
 			 if (( $# > 0 )); then 
 				 sleep_val=$1; 
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
 	 if [ ! "${start}${stop}${status}${inifile}${runtim}${sleep}" ] ; then 
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
 		 if [[ "${inifle}" == "YES" ]] ; then
 			 options_counter=${options_counter}+1
 		 fi
 		 if [[ "${runtime}" == "YES" ]] ; then
 			 options_counter=${options_counter}+1
 		 fi
 		 if [[ "${sleep}" == "YES" ]] ; then
 			 options_counter=${options_counter}+1
 		 fi
 	 fi
 	 if (( ${options_counter} > 3 )) ; then
 		 printStartStop "${STARTMSG}"
 		 rc=11;
 		 echo "${PROCNAME}: More than three Options are set in command Line!" | tee -a ${LOG_RESOURCE}
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

 	 echo ${_rc}
 	 return ${_rc}
 }
 #======================================================#
 # set parameters with new values of the command line --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED ([optional] parameters) <-- 
 #======================================================#
 function assembling_process
 {
	 local _parameters="";
 	 if (( ${#_parameters} > 0 )); then
 		 _parameters="${_parameters%?}"
 		 _parameters="${_parameters#?}"
 	 fi

	 if [[ "${inifile}" == "YES" ]] ; then
		 _parameters="${_parameters} -i ${INI_PATH}/${inifile_val}";
	 fi

	 if [[ "${runtime}" == "YES" ]] ; then
		 _parameters="${_parameters} -r ${runtime_val}";
	 fi

	 if [[ "${sleep}" == "YES" ]] ; then
		 _parameters="${_parameters} -s ${sleep_val}";
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
 . $(dirname $0)/loadlogfilewatchdog.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";

 # After calling function 'eval_parameters', the additional vars file could be read in,
 # because there parameter are build on the base of passed parameter read in 'eval_parameters'.
 . $(dirname $0)/../vars/loadlogfilewatchdog.vars;

 check_existence_of_binary ${process};
 assembling_process;
 print_msg "$STARTMSG" "$*"
 
 #======================================================#
 # CALLS METHOD START-PROCESS
 #======================================================#
 if [[ "$start" == "YES" ]]; then
	 eval "nohup $process &>/dev/null &"
 	 rc=$?;
	 sleep 1
	 result=`eval ps -ef|grep "$inifile_val"|grep -v inifile|grep -v grep| awk '{print $2}'`
	 if [ "$result" == "" ]; then
 	 	echo Process not started.| tee -a ${LOG_RESOURCE}
	 else
 	 	echo Process with PID="$result" started.| tee -a ${LOG_RESOURCE}
 	 fi
 fi
 #======================================================#
 # CALLS METHOD STOP-PROCESS
 #======================================================#
 if [[ "$stop" == "YES" ]]; then
	 result=`eval ps -ef|grep "$inifile_val"|grep -v inifile|grep -v grep| awk '{print $2}'`
	 if [ "$result" == "" ]; then
 	 	echo No running process with this parameter to stop.| tee -a ${LOG_RESOURCE}
	 else
	 	eval "kill -9 $result"
 	 	rc=$?
 	 	echo Process PID="$result" stopped.| tee -a ${LOG_RESOURCE}
 	 fi
 fi
 #======================================================#
 # CALLS METHOD STATUS-PROCESS
 #======================================================#
 if [[ "$status" == "YES" ]]; then
	 result=`eval ps -ef|grep "$inifile_val"|grep -v inifile|grep -v grep| awk '{print $2}'`
	 rc=$?
	 if [ "$result" == "" ]; then
 	 	echo No running process with this parameter.| tee -a ${LOG_RESOURCE}
	 else
 	 	echo Process PID="$result" is running.| tee -a ${LOG_RESOURCE}
 	 fi
 fi

 print_msg "$STOPMSG" "$*" "<$rc>"


 exit ${rc};
