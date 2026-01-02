#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            s.heinle                                                                                  
 #Creation-Date:     16.07.2012                                                                                
 #Creation-Time:     08:44                                                                                     
 #Creator:           procgen.sh - Version: 01.00.01.00                                                         
 #Creation-Type:     ONLINE_SERVER_PROCEDURE                                                                   
 #Purpose:           Starts, stops and status the exemplar binary csc_phatra for presentation only.            
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
# set -x #zeigt jede Zeile vor ihrer Ausfuehrung jedoch nach ihren Ersetzungen an (xtrace);
 
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
 
 #BINARY NAMES
 readonly BINARY=csc_phatra.bin
 process="${BIN_PATH}/${BINARY}"

 readonly SCRIPT_CALL="$(cd $(dirname $0);echo $PWD)/$(basename $0) $@"
 
 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 typeset -i branchno=-1;
 typeset configfile="";
 typeset -i binextension=0;
 typeset -i nomail=0;
 typeset -i testing=0;
 typeset -i extlog=0;
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
 readonly NOMAIL_OPTION="-nomail";
 readonly TESTING_OPTION="-testing";
 readonly EXTENDED_LOGGING_OPTION="-extlog";
 readonly BINEXTENSION_OPTION="-binextension";

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

 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
	 printf "%-30s%-90s\n" "\$branchno:" ">$branchno<"
 	 echo "--------------------------"
 	 echo "EXIT $FUNCNAME"
 	 echo "--------------------------"
 }
 #=============================================#
 # ACTIVATION OF THE TEST BINARY IF IT EXISTS 
 #=============================================#
 function activate_test_binary
 {
 	 local _TEST_BINARY=${BIN_PATH}/${BINARY}.${branchno};
 	 if [[ -f ${_TEST_BINARY} ]]; then
 		 # The name of the process will be renamed if the test binary exists.
 		 # So the current name of the process is transparent for the method 'check_existence_of_binary'.
 		 process=${_TEST_BINARY};

 		 # Reassignment of the library variable 'LD_LIBRARY_PATH'
 		 if [[ "${TEST_LIBRARY_PATH}" != "" ]]; then
 			 export LD_LIBRARY_PATH=${TEST_LIBRARY_PATH}:${OLD_LD_LIBRARY_PATH};
 		 fi
 	 fi
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
 		 if [[ "$1" == "$BINEXTENSION_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 binextension=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi
		 if [[ "$1" == "$NOMAIL_OPTION" ]]; then
				 shift;
				 nomail=1;
				 continue;
 		 fi
 		 if [[ "$1" == "$TESTING_OPTION" ]]; then
				shift;
 				 testing=1;
 				 continue;
 		 fi		 
  		 if [[ "$1" == "$EXTENDED_LOGGING_OPTION" ]]; then
				shift;
 				 extlog=1;
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
 	 if [[ "${branchno}" == "" ]] || (( 1 != `check_numeric_parameter "${BRANCHNO_OPTION}" "${branchno}"` )) || [[ "${branchno}" == "-1" ]]; then
 		 printStartStop "${STARTMSG}"
 		 rc=12;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${branchno}: >${branchno}<!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 
 	if [[ "${configfile}" == "" ]] || [[ ! -f "${configfile}" ]]; then
 	     printStartStop "${STARTMSG}"
 	    rc=12;
 	    echo "${PROCNAME}: Parameter value missed or file not found \${configfile}: >${configfile}<!" | tee -a ${LOG_RESOURCE}
 	    echo ${USAGE} | tee -a ${LOG_RESOURCE}
 	    printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 	    exit ${rc};
	fi
 
 	 if (( ${binextension} > 0 )); then
 		 if [[ "${binextension}" == "" ]] || (( 1 != `check_numeric_parameter "${BINEXTENSION_OPTION}" "${binextension}"` )) || [[ "${binextension}" == "0" ]]; then
 			 printStartStop "${STARTMSG}"
 			 rc=12;
 			 echo "${PROCNAME}: Parameter value missed or invalid value \${binextension}: >${binextension}<!" | tee -a ${LOG_RESOURCE}
 			 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 			 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
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

 	 local readonly _OPTION=${1};
 	 local readonly _ARG=${2};

 	 is_numeric "${_ARG}" "-NO_VERBOSE" # do the checks considered to be necessary
 	 if (( $? == 0 )); then return ${_rc}; fi
 	 _rc=1;

 	 if [[ "${_OPTION}" == "${BRANCHNO_OPTION}" ]]; then
 		 # do the possibly necessary checks with parameter ${_ARG}
 		 _rc=1;
 	 fi

 	 if [[ "${_OPTION}" == "${BINEXTENSION_OPTION}" ]]; then
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

 	 echo ${_rc}
 	 return ${_rc}
 }
 #======================================================#
 # set parameters with new values of the command line --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED ([optional] parameters) <-- 
 #======================================================#
 function assembling_process
 {
	 local _parameters="";
	 
	 
	 _parameters="$BRANCHNO_OPTION $branchno"
	 
	 _parameters="${_parameters} $CONFIGFILE_OPTION $configfile"
	 
	 
	 if (( $nomail == 1 )); then
		_parameters="${_parameters} $NOMAIL_OPTION"
	 fi
	 if (( $testing == 1 )); then
		_parameters="${_parameters} $TESTING_OPTION"
	 fi	 
	 if (( $extlog == 1 )); then
		_parameters="${_parameters} $EXTENDED_LOGGING_OPTION"
	 fi	 
	 
# 	 if (( ${#_parameters} > 0 )); then
# 		 _parameters="${_parameters%?}"
# 		 _parameters="${_parameters#?}"
# 	 fi

 #	 if (( ${#_parameters} > 0 )); then
 		 
 #	 else
 #		 _parameters="$BRANCHNO_OPTION $branchno";
 	 

	#	if (( ${#ADDITIONAL_PARA} > 0 )); then
	#		if (( ${#_parameters} > 0 )); then
	#			_parameters="${_parameters} ${ADDITIONAL_PARA}";
	#		else
	#			_parameters="${ADDITIONAL_PARA}";
	#		fi
	#	fi

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
 . $(dirname $0)/csc_phatra.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";

 # After calling function 'eval_parameters', the additional vars file could be read in,
 # because there parameter are build on the base of passed parameter read in 'eval_parameters'.
# . $(dirname $0)/../vars/csc_phatra.vars;

 activate_test_binary;
 check_existence_of_binary ${process};
 assembling_process;

 export CSC_BRANCHNO=${branchno};
 export CSC_LOGDATE=`date +"%Y%m%d"`
  
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
