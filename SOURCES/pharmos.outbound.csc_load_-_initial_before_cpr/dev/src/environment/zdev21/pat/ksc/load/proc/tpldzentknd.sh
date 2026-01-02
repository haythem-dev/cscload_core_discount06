#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author: devuser 
 #Creation-Date:	13.10.2008
 #Creation-Time:	10:25
 #Purpose:			starts, stops and status the exemplar binary tpldzentknd for presentation only
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
 readonly BINARY=tpldzentknd.bin
 process="${BIN_PATH}/${BINARY}"
 

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 lf=0;
 ld=0;
 allvz_flag=0;
 #--- end declaration procedure variables ---#
 start="";
 stop="";
 status="";
 backup="${BACKUPFLAG}";
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
 readonly BACKUP_OPTION="-backup";
 readonly LF_OPTION="-lf";
 readonly LD_OPTION="-ld";
 readonly ALLVZ_OPTION="-allvz";

 ###############################################################################################
 # F U N C T I O N S
 ###############################################################################################
 #====================================#
 # PRINT START-/ STOP-MELDUNG
 #====================================#
 function printStartStop
 {
 	 if [[ "$2" == "" ]]; then set $1 "13.10.08 10:25:06"; fi
 	 echo "=====================================================================================" | tee -a $LOG_RESOURCE
 	 echo "SH: $1 `pwd`/${0} $2" | tee -a $LOG_RESOURCE
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
 	 echo "\$MARATHON_SSUK_VERSION:			>$MARATHON_SSUK_VERSION<"
 	 echo "\$MARATHON_SSUK_LIBRARY_PATH:	>$MARATHON_SSUK_LIBRARY_PATH<"
 	 echo "\$LD_LIBRARY_PATH:				>$LD_LIBRARY_PATH<"
 	 echo "\$BINARY:						>$BINARY<"
 	 echo "\$STARTMSG:						>$STARTMSG<"
 	 echo "\$STOPMSG:						>$STOPMSG<"
 	 echo "\$START_OPTION:			>$START_OPTION<"
 	 echo "\$STOP_OPTION:			>$STOP_OPTION<"
 	 echo "\$STATUS_OPTION:			>$STATUS_OPTION<"
	 echo "\$BACKUP_OPTION:			>$BACKUP_OPTION<"
	 echo "\$LF_OPTION:			>$LF_OPTION<"
	 echo "\$LD_OPTION:			>$LD_OPTION<"
	 echo "\$ALLVZ_OPTION:			>$ALLVZ_OPTION<"

 	 echo "\$para:							>$para<"
 	 echo "\$process:						>$process<"
 	 echo "\$start:							>$start<"
 	 echo "\$stop:							>$stop<"
 	 echo "\$status:						>$status<"
	 echo "\$backup:						>$backup<"
	 echo "\$lf:			>$lf<"
	 echo "\$ld:			>$ld<"
	 echo "\$allvz:			>$allvz<"
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
 		 rc=8;
 		 echo "Error: Binary \"${BIN_PATH}/${BINARY}\" does not exist!" | tee -a $LOG_RESOURCE
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
 	 while (( $# > 0 )) 
 	 do
 		 #read in option
 		 if [[ "$1" == "$START_OPTION" ]] ; then start="YES"; shift; continue; fi
 		 if [[ "$1" == "$STOP_OPTION" ]] ; then stop="YES"; shift; continue; fi
 		 if [[ "$1" == "$STATUS_OPTION" ]] ; then status="YES"; shift; continue; fi
		 if [[ "$1" == "$BACKUP_OPTION" ]] ; then backup="e"; shift; continue; fi

 		 #read in parameters
 		 if [[ "$1" == "$LF_OPTION" ]]; then
 			 shift
 			 if (( $# > 0 )) ; then
 				 lf=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$LD_OPTION" ]]; then
 			 shift
 			 if (( $# > 0 )) ; then
 				 ld=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$ALLVZ_OPTION" ]]; then
 			 shift
			 allvz_flag=1;
 			 continue;
 		 fi

		break;
 	 done

 	 #--------------------------#
 	 # evaluation of options
 	 #--------------------------#
 	 if [ ! "$start$stop$status" ] ; then 
 		 printStartStop "$STARTMSG"
 		 rc=10;
 		 echo "$PROCNAME: No options set in command line!" | tee -a $LOG_RESOURCE
 		 echo ${USAGE} | tee -a $LOG_RESOURCE
 		 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 else 
 		 typeset -i options_counter=0;
 		 if [[ "$start" == "YES" ]] ; then
 			 options_counter=$options_counter+1
 		 fi
 		 if [[ "$stop" == "YES" ]] ; then
 			 options_counter=$options_counter+1
 		 fi
 		 if [[ "$status" == "YES" ]] ; then
 			 options_counter=$options_counter+1
 		 fi
 	 fi
 	 if (( $options_counter > 1 )) ; then
 		 printStartStop "$STARTMSG"
 		 rc=11;
 		 echo "$PROCNAME: More than one Option is set in command Line!" | tee -a $LOG_RESOURCE
 		 echo ${USAGE} | tee -a $LOG_RESOURCE
 		 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi

	 #--------------------------#
 	 # evaluation of parameters
 	 #--------------------------#
 	 if [[ "$lf" == "" ]] || (( 1 != `check_numeric_parameter "$lf"` )) || [[ "$lf" == "0" ]]; then
 		 printStartStop "$STARTMSG"
 		 rc=12;
 		 echo "$PROCNAME: Parameter value missed or invalid value \$lf: >$lf<!" | tee -a $LOG_RESOURCE
 		 echo ${USAGE} | tee -a $LOG_RESOURCE
 		 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 

 	 if (( ${ld} > 0 )); then
 		 if [[ "$ld" == "" ]] || (( 1 != `check_numeric_parameter "$ld"` )) || [[ "$ld" == "0" ]]; then
 			 printStartStop "$STARTMSG"
 			 rc=12;
 			 echo "$PROCNAME: Parameter value missed or invalid value \$ld: >$ld<!" | tee -a $LOG_RESOURCE
 			 echo ${USAGE} | tee -a $LOG_RESOURCE
 			 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
 			 exit ${rc};
 		 fi
 	 fi

 }
 #======================================================#
 # checks numeric parameter --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED (separate validity) <-- 
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
 # checks string parameter --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED (separate validity) <-- 
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
	 local _parameters="";
 	 if (( $ld > 0 )); then
 		 _parameters="${_parameters} $LD_OPTION ";
 		 _parameters="${_parameters} $ld ";
 	 fi

 	 if (( ${allvz_flag} == 1 )); then
 		 _parameters="${_parameters} $ALLVZ_OPTION ";
 	 fi

 	 if (( ${#_parameters} > 0 )); then
 		 _parameters="${_parameters%?}"
 		 _parameters="${_parameters#?}"
 	 fi

 	 if (( ${#_parameters} > 0 )); then
 		 _parameters="${_parameters} $LF_OPTION $lf"
 	 else
 		 _parameters="$LF_OPTION $lf";
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
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/tpldzentknd.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";

 # After calling function 'eval_parameters', the additional vars file could be read in,
 # because there parameter are build on the base of passed parameter read in 'eval_parameters'.
 . $(dirname $0)/../vars/tpldzentknd.vars;

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
 
 print_msg "$STOPMSG" "$*" "<$rc>"
 
 exit $rc;
