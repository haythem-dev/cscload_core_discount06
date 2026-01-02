#! /usr/bin/ksh 

 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author: 			S. Heinlein
 #Creation-Date:	15.03.2016
 #Creation-Time:	08:00
 #Purpose:			starts, stops and status the exemplar binary unload_orderivcvoucherno
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
  . $(dirname $0)/../vars/unload_orderivcvoucherno.vars;
 
 #--------------------------------------------------------------------#
 # LIBRARY VARIABLES
 #--------------------------------------------------------------------#
 readonly OLD_LD_LIBRARY_PATH=$LD_LIBRARY_PATH;
 
 #LIBRARY PATH 
 readonly LIBRARY_PATH=${LIB_PATH}//sharedlib/release
 export LD_LIBRARY_PATH=${LIBRARY_PATH}:$LD_LIBRARY_PATH
 readonly BINARY=unload_orderivcvoucherno.bin 
  process="${BIN_PATH}/${BINARY}"
 

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 start="";
 stop="";
 status="";
 process_count=0; # for checking the number of process starts
 typeset -i rc=0;
 
 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";

 ###############################################################################################
 # F U N C T I O N S
 ###############################################################################################
 #====================================#
 # PRINT START-/ STOP-MELDUNG
 #====================================#
 function printStartStop
 {
 	 echo "=====================================================================================" | tee -a $LOG_RESOURCE
 	 echo "SH: $1 `pwd`/${0}! $2" | tee -a $LOG_RESOURCE
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
 		 local readonly MSG="$1 with return code <${3}>."
 		 logging "${MSG}"; 
 		 printStartStop "$1" "$2"
 	 fi
 }
 #====================================#
 # PRINT LOCAL VARIABLES 
 #====================================#
 function print_local_var
 {
 	 local FUNCNAME="print_local_var";
 	 echo "--------------------------"
 	 echo "ENTER $FUNCNAME"
 	 echo "--------------------------"
 	 echo "\$MARATHON_SSUK_VERSION:			>$MARATHON_SSUK_VERSION<"
 	 echo "\$MARATHON_SSUK_LIBRARY_PATH:	>$MARATHON_SSUK_LIBRARY_PATH<"
 	 echo "\$LD_LIBRARY_PATH:				>$LD_LIBRARY_PATH<"
 	 echo "\$BINARY:						>$BINARY<"
 	 echo "\$STARTMSG:						>$STARTMSG<"
 	 echo "\$STOPMSG:						>$STOPMSG<"
 	 echo "\$START_OPTION:					>$START_OPTION<"
 	 echo "\$STOP_OPTION:					>$STOP_OPTION<"
 	 echo "\$STATUS_OPTION:					>$STATUS_OPTION<"

 	 echo "\$para:							>$para<"
 	 echo "\$process:						>$process<"
 	 echo "\$start:							>$start<"
 	 echo "\$stop:							>$stop<"
 	 echo "\$status:						>$status<"
 	 echo "--------------------------"
 	 echo "EXIT $FUNCNAME"
 	 echo "--------------------------"
 }
 #=============================================#
 # CHECKING IF BINARY is EXISTING 
 #=============================================#
 function check_existence_of_binary
 {	 
 	 if [[ ! -f ${BIN_PATH}/${BINARY} ]]; then
 		 printStartStop "$STARTMSG"
 		 echo "Error: Binary \"${BIN_PATH}/${BINARY}\" does not exist!"
 		 printStartStop "$STOPMSG"
 		 exit 8;
 	 fi
}
 #=============================================#
 # CHECKING IF PARAMETERS ARE BASICALLY SET 
 #=============================================#
 function check_parameters
 {
 	 if (( $# == 0 )); then
 		 printStartStop "$STARTMSG"
 		 echo "Error: No Parameters passed!"
 		 echo ${USAGE};
 		 printStartStop "$STOPMSG"
 		 exit 9;
 	 fi
 }
 #=============================================#
 # READ IN PARAMETERS DISREGARDING THE ORDER 
 #=============================================#
 function eval_parameters
 {
 	 while (( $# > 0 )) 
 	 do
 		 #read in option
 		 if [[ "$1" == "$START_OPTION" ]] ; then start="YES"; shift; continue; fi
 		 if [[ "$1" == "$STOP_OPTION" ]] ; then stop="YES"; shift; continue; fi
 		 if [[ "$1" == "$STATUS_OPTION" ]] ; then status="YES"; shift; continue; fi 
 		 #read in parameters
		break;
 	 done

 	 # evaluation of options
 	 if [ ! "$start$stop$status" ] ; then 
 		 printStartStop "$STARTMSG"
 		 echo "$PROCNAME: No options set in command line!" 
 		 echo ${USAGE};
 		 printStartStop "$STOPMSG"
 		 exit 10;
 	 else 
 		 typeset -i options_counter=0;
 		 if [[ "$start" == "YES" ]] ; then
 			 options_counter=options_counter+1
 		 fi
 		 if [[ "$stop" == "YES" ]] ; then
 			 options_counter=options_counter+1
 		 fi
 		 if [[ "$status" == "YES" ]] ; then
 			 options_counter=options_counter+1
 		 fi
 	 fi
 	 if (( $options_counter > 1 )) ; then
 		 printStartStop "$STARTMSG"
 		 echo "$PROCNAME: More than one Option is set in command Line!" 
 		 echo ${USAGE};
 		 printStartStop "$STOPMSG"
 		 exit 11;
 	 fi

	 # evaluation of parameters 	 
 }
 #======================================================#
 # checks numeric parameter 
 #======================================================#
 function check_numeric_parameter
 {
 	 local readonly FUNCNAME=check_numeric_parameter;
 	 local _rc=0;

 	 is_numeric "$1" "-NO_VERBOSE" # do the checks considered to be necessary
 	 if (( $? == 1 )); then
 		 _rc=1
 	 fi
 	 echo ${_rc}
 	 return ${_rc}
 }
 #======================================================#
 # checks string parameter 
 #======================================================#
 function check_string_parameter
 {
 	 local readonly FUNCNAME=check_string_parameter;
 	 local _rc=0;

 	 # do some checks here - e.g. database server validity: [a-z]*([a-z]|[1-9])@+([a-z]|[1-9]|[_])_@(shm|tcp)

 	 _rc=1
 	 echo ${_rc}
 	 return ${_rc}
 }
 #======================================================#
 # set parameters with new values of the command line --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED ([optional] parameters) <-- 
 #======================================================#
 function assembling_process
 {
	 local readonly _PARA="";
	 process="$process ${_PARA}";
 }
 
 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/unload_orderivcvoucherno.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";
 check_existence_of_binary;
 assembling_process;
 print_msg "$STARTMSG" "$*"
 
 #======================================================#
 # CALLS METHOD START-PROCESS
 #======================================================#
 if [[ "$start" == "YES" ]]; then
 	 msg=`start_process "${process}" `
 	 rc=$?;
 	 echo "$msg" | tee -a $LOG_RESOURCE
 fi
 #======================================================#
 # CALLS METHOD STOP-PROCESS
 #======================================================#
 if [[ "$stop" == "YES" ]]; then
 	 msg=`stop_process "${process}"`
 	 rc=$?;
 	 echo "$msg" | tee -a $LOG_RESOURCE 

 fi
 #======================================================#
 # CALLS METHOD STATUS-PROCESS
 #======================================================#
 if [[ "$status" == "YES" ]]; then
 	 msg=`status_process "${process}"`
 	 rc=$?;
 	 echo "$msg" | tee -a $LOG_RESOURCE

 fi
 
 print_msg "$STOPMSG" "$*" "$rc"
 
 exit $rc;
