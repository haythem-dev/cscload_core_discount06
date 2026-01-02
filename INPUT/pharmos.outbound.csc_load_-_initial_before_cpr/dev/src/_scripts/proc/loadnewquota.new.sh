#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            j.skuratovski
 #Creation-Date:     04.07.2024
 #Creation-Time:     10:12
 #Creator:           generate_proc_file - Version: 02.01.00.00
 #Creation-Type:     BATCH_PROCEDURE
 #Purpose:           Starts, stops and status the binary loadnewquota for presentation only.
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
. $(dirname $0)/../vars/loadnewquota.new.vars

 #--------------------------------------------------------------------#
 # LIBRARY / BINARY VARIABLES
 #--------------------------------------------------------------------#
 readonly BINARY=loadnewquota.bin
 process="${BIN_PATH}/${BINARY}"

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 start="";
 stop="";
 status="";
 send="";
 send_val="";
 inputfile="";
 updateonly="";
 typeset -i rc=0;

 #--- E-Mails addresses for receivers ---#
 arr_email_receivers[0]=w.feki@externals.phoenixgroup.eu;
 arr_email_receivers[1]=t.arnold@externals.phoenixgroup.eu;
 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";
 readonly SEND_OPTION="-send";
 readonly INPUTFILE_OPTION="-inputfile";
 readonly UPDATEONLY_OPTION="-updateonly";

 readonly QUOTA_FULL_DATA_PATH=${DATA_PATH}/quota
 readonly QUOTA_DELTA_DATA_PATH=${DATA_PATH}/quota/delta
 
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
	 printf "%-30s%-90s\n" "\$DB_OPTION:" ">$DB_OPTION<"
	 printf "%-30s%-90s\n" "\$INPUTFILE_OPTION:" ">$INPUTFILE_OPTION<"
	 printf "%-30s%-90s\n" "\$UPDATEONLY_OPTION:" ">$UPDATEONLY_OPTION<"

 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
 	 printf "%-30s%-90s\n" "\$send:" ">$send<"
 	 printf "%-30s%-90s\n" "\$send_val:" ">$send_val<"
	 printf "%-30s%-90s\n" "\$db:" ">$db<"
	 printf "%-30s%-90s\n" "\$inputfile:" ">$inputfile<"
	 printf "%-30s%-90s\n" "\$updateonly:" ">$updateonly<"
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

 		 if [[ "$1" == "$INPUTFILE_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 inputfile=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$UPDATEONLY_OPTION" ]]; then
 			 shift;
   			 updateonly="-nodelete";
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
 	 if [[ "${inputfile}" == "" ]] || (( 1 != `check_string_parameter "${INPUTFILE_OPTION}" "${inputfile}"` )); then
 		 printStartStop "${STARTMSG}"
 		 rc=13;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${inputfile}: >${inputfile}<!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
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
 ###############################################################################################
 # GENERATED FUNCTIONS - END
 ###############################################################################################

 ###############################################################################################
 # INDIVIDUAL FUNCTIONS - BEGIN
 ###############################################################################################
  
 #===========================================================#
 # function sending EMails
 #===========================================================#
 function send_emails
 {
 	local _FUNCNAME="send_emails";
	
	local _msg="$1";
	local _type="$2";
	local _file="$3";
	local _filename_attachment="$4";
	local _subject="$(hostname): ${PROC_PATH}/${PROCNAME} with ${_type}."

	for address in ${arr_email_receivers[*]}
	do
		if [[ "" != "${_file}" &&  "" != "${_filename_attachment}" ]]; then
			unix2dos "${_file}" "${_file}"; 1>&2 2>/dev/null;
			(echo "${_msg}"; uuencode ${_file} ${_filename_attachment}) | mailx -s "${_subject}" ${address};
		else
			echo "${_msg}" | mailx -s "${_subject}" ${address};
		fi
	done
 }
 #======================================================#
 # function process_loadnewquota
 #======================================================#
 function process_loadnewquota
 {
	local _FUNCNAME="process_loadnewquota";
	typeset -i _rc=0;
	process_inputfile="";
	process_type="";
	# get the filename without path
	filename=$(basename -- "${inputfile}")
	if [[ "" == "${updateonly}" ]]; then
		process_inputfile=${QUOTA_FULL_DATA_PATH}/${filename}
		process_type="full";
	else
		process_inputfile=${QUOTA_DELTA_DATA_PATH}/${filename}
		process_type="delta";
	fi

 	#-----------------------------------------------------------------------------------
 	echo "--> STEP 1: Copy file from transfer to DATA_PATH for ${process_type} quota " | tee -a ${LOG_RESOURCE}
 	#-----------------------------------------------------------------------------------
	echo "Copy from ${inputfile} ---> ${process_inputfile}" | tee -a ${LOG_RESOURCE}
	cp -rf "${inputfile}" "${process_inputfile}"

 	#-----------------------------------------------------------------------------------
 	echo "--> STEP 2: Convert DOS LF's to UNIX " | tee -a ${LOG_RESOURCE}
 	#-----------------------------------------------------------------------------------
	# convert dos LF to Unix LF's
	dos2unix ${process_inputfile} ${process_inputfile} | tee -a ${LOG_RESOURCE}

	#-----------------------------------------------------------------------------------
	echo "--> STEP 3: Verify if file <${filename}> after checks is not empty." | tee -a ${LOG_RESOURCE}
	#-----------------------------------------------------------------------------------
	if [ ! -s $process_inputfile ] ; then 
		errmsg="ERROR: No or empty ${process_type} file <${process_inputfile}>!\nThe Quota loader got an empty or not existing ${process_type} file.\nImport aborted.";
		echo "\t${errmsg}" | tee -a ${LOG_RESOURCE}
		send_emails "${errmsg}" "Error";
		_rc=3;
	else
		echo "\tOK: load file <${process_inputfile}> contains `wc -l <${process_inputfile}` lines." | tee -a ${LOG_RESOURCE}

		#-----------------------------------------------------------------------------------
		echo "--> STEP 4: Start loadnewquota.bin with <${filename}> in ${process_type} mode." | tee -a ${LOG_RESOURCE}
		#-----------------------------------------------------------------------------------
		# start processing
		#./loadnewquota -inputcsv $csvfile -db $database -nodelete
		echo "Process: $process -inputcsv ${process_inputfile} ${ADDITIONAL_PARA} ${updateonly}" | tee -a ${LOG_RESOURCE}
		${process} -inputcsv ${process_inputfile} ${ADDITIONAL_PARA} ${updateonly}
		_rc=${?};

		if [ $_rc -eq 5 ]; then
	        	errmsg="\tERROR: CSV ${process_type} file containg invalid data <${process_inputfile}>!";
	        	echo "${errmsg}" | tee -a ${LOG_RESOURCE}
			send_emails "${errmsg}" "Error";
		fi
	fi

	return ${_rc};
 }
 ###############################################################################################
 # INDIVIDUAL FUNCTIONS - END
 ###############################################################################################

 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/loadnewquota.new.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";
 check_existence_of_binary ${process};
 print_msg "$STARTMSG" "$*"
 
 #======================================================#
 # CALLS METHOD START-PROCESS
 #======================================================#
 if [[ "$start" == "YES" ]]; then
	process_loadnewquota
	rc=${?};
 	print_msg "${STOPMSG}" "$*" "<$rc>"
 fi
 #======================================================#
 # CALLS METHOD STOP-PROCESS
 #======================================================#
 if [[ "$stop" == "YES" ]]; then
 	 msg="NOT IMPLEMENTED!";
 	 rc=$?;
 	 echo "$msg" | tee -a ${LOG_RESOURCE}
 fi
 #======================================================#
 # CALLS METHOD STATUS-PROCESS
 #======================================================#
 if [[ "$status" == "YES" ]]; then
 	 msg="NOT IMPLEMENTED!";
 	 rc=$?;
 	 echo "$msg" | tee -a ${LOG_RESOURCE}
 fi
 #======================================================#
 # CALLS METHOD SEND-PROCESS
 #======================================================#
 if [[ "$send" == "YES" ]]; then
 	 msg="NOT IMPLEMENTED!";
 	 rc=$?;
 	 echo "$msg" | tee -a ${LOG_RESOURCE}
 fi
 exit ${rc};
