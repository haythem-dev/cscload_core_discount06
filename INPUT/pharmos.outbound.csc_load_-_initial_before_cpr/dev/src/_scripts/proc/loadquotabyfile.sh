#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            Julian Machata                                                                                   
 #Creation-Date:     24.04.2012                                                                                
 #Creation-Time:     10:55                                                                                     
 #Creator:           procgen.sh - Version: 01.00.01.00                                                         
 #Creation-Type:     BATCH_PROCEDURE                                                                           
 #Purpose:           Starts, stops and status the exemplar binary loadquotabyfile for presentation only.       
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
 . $(dirname $0)/../vars/loadquotabyfile.vars

 #--------------------------------------------------------------------#
 # LIBRARY / BINARY VARIABLES
 #--------------------------------------------------------------------#
 readonly BINARY=loadquotabyfile.bin
 process="${BIN_PATH}/${BINARY}"

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 db="";
 dbsrv="";
 filename="";
 typeset -i clearbeforeload_flag=0;	  #if truncate table before loading file
 #--- end declaration procedure variables ---#
 start="";
 stop="";
 status="";
 typeset -i rc=0;

 typeset -i errno=0;
 errmsg="";
 INFORMIXDIR=${INFORMIXDIR};

 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";
 readonly DB_OPTION="-db";
 readonly DBSRV_OPTION="-dbsrv";
 readonly FILENAME_OPTION="-filename";
 readonly CLEARBEFORELOAD_OPTION="-clearbeforeload";

 typeset -ir ERROR=1;
 typeset -ir OK=0;
 typeset -ir HINT=2;
 typeset -ir TRUE=1;
 typeset -ir FALSE=0;
 
 typeset -ir PRINT_DEBUG_OUTPUT=TRUE;
 
 typeset -ir RET_CODE_INPUT_FILE_NOT_EXISTING=13;
 typeset -ir RET_CODE_INPUT_FILE_NO_READ_RIGHTS=14;
 typeset -ir RET_CODE_INPUT_FILE_IS_EMPTY=15;
 typeset -ir RET_CODE_INPUT_FILE_SPLIT_ERROR=16;
 
  # FOLDER 
 typeset -r SQL_LOG_FOLDER="${LOG_PATH}"
 
 # FILES
 typeset -r SQL_STATEMENT_FILE="${SQL_LOG_FOLDER}/${PROCNAME}.sql"
 typeset -r SQL_RESULT_FILE="${SQL_LOG_FOLDER}/${PROCNAME}.res"
 typeset -r SQL_ERROR_FILE="${SQL_LOG_FOLDER}/${PROCNAME}.err"

 #--------------------------------------------------------------------#
 # S I G N A L - Installation
 #--------------------------------------------------------------------#
 trap "func_exit" 0


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
 	 printf "%-30s%-90s\n" "\$MARATHON_SSUK_VERSION:" ">$MARATHON_SSUK_VERSION<"
 	 printf "%-30s%-90s\n" "\$MARATHON_SSUK_LIBRARY_PATH:" ">$MARATHON_SSUK_LIBRARY_PATH<"
 	 printf "%-30s%-90s\n" "\$LD_LIBRARY_PATH:" ">$LD_LIBRARY_PATH<"
 	 printf "%-30s%-90s\n" "\$BINARY:" ">$BINARY<"
 	 printf "%-30s%-90s\n" "\$STARTMSG:" ">$STARTMSG<"
 	 printf "%-30s%-90s\n" "\$STOPMSG:" ">$STOPMSG<"
 	 printf "%-30s%-90s\n" "\$START_OPTION:" ">$START_OPTION<"
 	 printf "%-30s%-90s\n" "\$STOP_OPTION:" ">$STOP_OPTION<"
 	 printf "%-30s%-90s\n" "\$STATUS_OPTION:" ">$STATUS_OPTION<"
	 printf "%-30s%-90s\n" "\$DB_OPTION:" ">$DB_OPTION<"
	 printf "%-30s%-90s\n" "\$DBSRV_OPTION:" ">$DBSRV_OPTION<"
	 printf "%-30s%-90s\n" "\$FILENAME_OPTION:" ">$FILENAME_OPTION<"
	 printf "%-30s%-90s\n" "\$CLEARBEFORELOAD_OPTION:" ">$CLEARBEFORELOAD_OPTION<"

 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
	 printf "%-30s%-90s\n" "\$db:" ">$db<"
	 printf "%-30s%-90s\n" "\$dbsrv:" ">$dbsrv<"
	 printf "%-30s%-90s\n" "\$filename:" ">$filename<"
 	 echo "--------------------------"
 	 echo "EXIT $FUNCNAME"
 	 echo "--------------------------"
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
 		 if [[ "$1" == "$DB_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 db=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$DBSRV_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 dbsrv=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$FILENAME_OPTION" ]]; then
 			 shift;
 			 if (( $# > 0 )) ; then
 				 filename=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$CLEARBEFORELOAD_OPTION" ]]; then
 			 shift;
			 clearbeforeload_flag=1;
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
 	 if [[ "${db}" == "" ]] || (( 1 != `check_string_parameter "${DB_OPTION}" "${db}"` )); then
 		 printStartStop "${STARTMSG}"
 		 rc=12;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${db}: >${db}<!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 

 	 if [[ "${dbsrv}" == "" ]] || (( 1 != `check_string_parameter "${DBSRV_OPTION}" "${dbsrv}"` )); then
 		 printStartStop "${STARTMSG}"
 		 rc=12;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${dbsrv}: >${dbsrv}<!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 

 	 if [[ "${filename}" == "" ]] || (( 1 != `check_string_parameter "${FILENAME_OPTION}" "${filename}"` )); then
 		 printStartStop "${STARTMSG}"
 		 rc=12;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${filename}: >${filename}<!" | tee -a ${LOG_RESOURCE}
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

 	 if [[ "${_OPTION}" == "${DB_OPTION}" ]]; then
 		 # do the possibly necessary checks with parameter ${_ARG}
 		 # e.g. database server validity: [a-z]*([a-z]|[1-9])@+([a-z]|[1-9]|[_])_@(shm|tcp)
 		 _rc=1;
 	 fi

 	 if [[ "${_OPTION}" == "${DBSRV_OPTION}" ]]; then
 		 # do the possibly necessary checks with parameter ${_ARG}
 		 # e.g. database server validity: [a-z]*([a-z]|[1-9])@+([a-z]|[1-9]|[_])_@(shm|tcp)
 		 _rc=1;
 	 fi

 	 if [[ "${_OPTION}" == "${FILENAME_OPTION}" ]]; then
 		 # do the possibly necessary checks with parameter ${_ARG}
 		 # e.g. database server validity: [a-z]*([a-z]|[1-9])@+([a-z]|[1-9]|[_])_@(shm|tcp)
 		 _rc=1;
 	 fi

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
 # Sets the directory of informix automatically
 #===========================================================#
 function set_informixdir
 {
 	 local _FUNCNAME="set_informixdir";

 	 reset_error_indicators;

 	 INFORMIXDIR=${INFORMIXDIR%/*};
 	 export INFORMIXDIR;
 	 if [[ "" == ${INFORMIXDIR} ]]; then
 		 errno=ERROR;
 		 errmsg="ERROR - ${_FUNCNAME}: Environment variable 'INFORMIXDIR' is empty. No modification could be made.";
 	 else
 		 errno=${OK};
 		 errmsg="";
 	 fi

 	 return ${errno};
 }
 #===========================================================#
 # function reset_error_indicators
 #===========================================================#
 function reset_error_indicators
 {
 	 local _FUNCNAME="reset_error_indicators";

 	 errno=${OK};
 	 errmsg="";
 }
 #===========================================================#
 # function automatically executed by exiting the procedure
 #===========================================================#
 function func_exit
 {
 	 local _FUNCNAME="func_exit";
 	 if (( ${ERROR} == ${errno} )); then
 		 echo ${errmsg} | tee -a ${LOG_RESOURCE};
 	 fi
 	 print_msg "${STOPMSG}" "$*" "<$rc>"
 }
 #====================================================================================#
 # function function transforming the integer return code '0', '1' and '2'
 # to the strings 'OK', 'ERROR' and 'HINT'
 #====================================================================================#
 function transform_rc
 {
 	 local _FUNCNAME="transform_rc";
 	 typeset -ir _rc=${1};
 	 local _result="";
 	 case ${_rc} in
 		 ${OK}) _result="OK";;
 		 ${ERROR}) _result="ERRRO";;
 		 ${HINT}) _result="HINT";;
 		 *) _result="No transformation possible - no valid value passed (<_rc>)!";;
 	 esac
 	 echo ${_result};
 }
 #====================================================================================#
 # function transforming the bool value '0' and '1' to the strings 'FALSE' and 'TRUE'
 #====================================================================================#
 function transform_bool
 {
 	 local _FUNCNAME="transform_bool";
 	 typeset -ir _rc=/software/wss/rs/ksc/load;
 	 local _result="";
 	 case ${_rc} in
 		 ${TRUE}) _result="TRUE";;
 		 ${FALSE}) _result="FALSE";;
 		 *) _result="No bool transformation possible - no valid value passed (<_rc>)!";;
 	 esac
 	 echo ${_result};
 }
 #======================================================#
 # executes sql statement
 #======================================================#
 #======================================================#
 # executes sql statement
 #======================================================#
  function do_sql
 {
 
	 local _FUNCNAME=do_sql;
 	 local _sql=${1};
 	 local _db=${2};
 	 typeset -i _rc=${ERROR};
 	 reset_error_indicators;
	 
 	 echo "${_sql}" | dbaccess ${_db} 1>${SQL_RESULT_FILE} 2>${SQL_ERROR_FILE};
 	 _rc=${?};

 	 if (( ${OK} == ${_rc} )); then
 		 set -A arr_result `cat ${SQL_RESULT_FILE}`;
 		 if (( 0 == ${#arr_result[*]} )); then
 			 _rc=${OK};
 		 else
 			 _rc=${arr_result[1]};
 		 fi
 	 else
 		 errno=${ERROR};
 		 errmsg="${_FUNCNAME}: Error executing SQL-Statement (see ${SQL_ERROR_FILE})";
 		 #errmsg=${errmsg}"with error text <`cat ${SQL_ERROR_FILE}`>.";
		 echo "${_sql}" >> ${SQL_ERROR_FILE}
 	 fi
	 
 	 return ${errno};
 }
 #======================================================#
 # prints output
 #======================================================#
 function print_debug
 {
	 local _FUNCNAME="print_debug";
	 local _msg="${1}"
	 
	 if (( PRINT_DEBUG_OUTPUT==TRUE )); then
		echo "${_msg}"
	 fi
 }
#===========================================================#
 # checks if passed file is readable
 #===========================================================#
 function check_is_file_readable
 {
 	 local _FUNCNAME="check_is_file_readable";
	 local _filename=${1};
	 
	 reset_error_indicators
	 
 	 if [[ ! -r "${_filename}" ]]; then		
		return ${FALSE};
	 fi

 	 return ${TRUE};
 }
 #===========================================================#
 # checks if passed file is existing
 #===========================================================#
 function check_is_file_existing
 {
 	 local _FUNCNAME="check_is_file_existing";
	 local _filename=${1};
	 
	 reset_error_indicators

 	 if [[ ! -f "${_filename}" ]]; then		
		return ${FALSE};
	 else
		return ${TRUE};
	 fi
 }
 #===========================================================#
 # checks if passed file is empty
 #===========================================================#
 function check_is_file_empty
 {
 	 local _FUNCNAME="check_is_file_empty";
	 local _filename=${1};
	 
	 reset_error_indicators
	 
	 typeset -ir _INPUTFILE_SIZE=`ls -l "${_filename}" | awk '{print $5}'` 
	 
	 if (( ${_INPUTFILE_SIZE} == 0 )); then
		return ${TRUE};
	 fi 

 	 return ${FALSE};
 }
 #===========================================================#
 # evaluating input file for further usage
 #===========================================================#
 function evaluate_input_file
 {
 	 local _FUNCNAME="evaluate_input_file";
	 typeset -r _INPUTFILENAME="${1}"
	 
	 reset_error_indicators;
	 
	 print_debug "\n>Started evaluating input file";

	 #-------------------------------------#
 	 # check if file is existing
 	 #-------------------------------------#
	 check_is_file_existing "${_INPUTFILENAME}";
	 rc=${?};

 	 if (( ${FALSE} == ${rc} )); then
		 
  		 errno=${RET_CODE_INPUT_FILE_NOT_EXISTING};
 		 errmsg="${_FUNCNAME}: Passed input file <${_INPUTFILENAME}> does not exist!";
		 
		 return ${ERROR};
 	 fi

	 #-------------------------------------#
 	 # check if is readable
 	 #-------------------------------------#
	 check_is_file_readable "${_INPUTFILENAME}";
	 rc=${?};
	 
 	 if (( ${FALSE} == ${rc} )); then
	 
  		 errno=${RET_CODE_INPUT_FILE_NO_READ_RIGHTS};
 		 errmsg="${_FUNCNAME}: No read rights for passed input file <${_INPUTFILENAME}>!";
		 
		 return ${ERROR};
 	 fi

	 #-------------------------------------#
 	 # check if file is empty
 	 #-------------------------------------#
	 check_is_file_empty "${_INPUTFILENAME}";
	 rc=${?};
	 
	 if (( ${TRUE} == ${rc} )); then
	
		 errno=${RET_CODE_INPUT_FILE_IS_EMPTY};
 		 errmsg="${_FUNCNAME}: Passed input file <${_INPUTFILENAME}> is empty!";
		 
		 return ${ERROR};
	 fi

	 print_debug "...input file is OK!";

 	 return ${OK};
 }
 
 #===========================================================#
 # checks if split dir exists and create if necessary
 #===========================================================#
 function create_split_dir
 {
 	 local _FUNCNAME="create_split_dir";
	 local _dirname=${1};
	 
	 reset_error_indicators
	 
 	 if [[ ! -d "${_dirname}" ]]; then	
	 
		 reset_error_indicators;
		 mkdir ${_dirname};
		 rc=${?};
		 if (( ${FALSE} == ${rc} )); then
			return ${ERROR}; 
		 fi
	 fi

	 return ${OK};
 }
 
 #===========================================================#
 # evaluating input file for further usage
 #===========================================================#
 function split_input_file
 {
	 local _FUNCNAME="split_input_file";
	 typeset -r _INPUTFILENAME="${1}"
	 
	 reset_error_indicators;
	 
	 print_debug "\n>Creating split directory";
	 
	 #-------------------------------------#
 	 # Creating directory for split files
 	 #-------------------------------------#	 
	 create_split_dir "${OUTPUTFILE_PATH}"
	 rc=${?};
	 	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi	 
	 
	 print_debug "...directory created!";
	 
	 reset_error_indicators;
	 
	 print_debug "\n>Splitting input file";
	 
	 #-------------------------------------#
 	 # check if is readable
 	 #-------------------------------------#
	 split -l ${JUNK_SIZE} "${_INPUTFILENAME}" "${OUTPUTFILE_PATH}/${OUTPUTFILENAME_SUFFIX}";
	 rc=${?};
	 
 	 if (( ${ERROR} == ${rc} )); then
	 
  		 errno=${RET_CODE_INPUT_FILE_SPLIT_ERROR};
 		 errmsg="${_FUNCNAME}: Was not able to split input file <${_INPUTFILENAME}>!";
		 
		 return ${ERROR};
 	 fi 
	 
	 print_debug "...file splitted!";
 }
 #===========================================================#
 # Writing passed statement to collective .sql-file (pass with ';' at the end of statement)
 #===========================================================#
 function write_to_sql_file
 {
	 local _FUNCNAME="write_to_sql_file";
	 local _sql=$1;
	 local _append=$2;
	 
	 reset_error_indicators;
	 
	 if (( ${_append} == ${TRUE} )); then 
		echo "${_sql} \n" >> "${OUTPUTFILE_SQL_PATH}";
	 else
		echo "${_sql} \n" > "${OUTPUTFILE_SQL_PATH}";
     fi	 
 }
 #======================================================#
 # executes sql statement from file
 #======================================================#
 function do_sql_file
 {
 	 local _FUNCNAME="do_sql_file";
	 
	 typeset -r _FULL_DB="${1}"
	 typeset -r _SQL_STATEMENT_FILE="${2}";
 	 typeset -i _rc=${ERROR};
	 
 	 reset_error_indicators;
	 
	 dbaccess ${_FULL_DB} ${_SQL_STATEMENT_FILE} 1>${SQL_RESULT_FILE} 2>${SQL_ERROR_FILE};
 	 _rc=${?};	 

 	 return ${_rc};
 }
 #===========================================================#
 # loading split filse
 #===========================================================#
 function load_split_files
 {
	 local _FUNCNAME="load_split_files";
	 typeset -r _full_tablename="${1}"
	 typeset -r _full_temp_tablename="${2}"
	 typeset -r _insert_columns="${3}"
	 typeset -r _full_db="${4}"
	 typeset -r _filecount=`ls -l "${OUTPUTFILE_PATH}" | egrep -c '^-'`;
	 local      _i=1;	 
	 
	 reset_error_indicators;
											 
	 for file in ${OUTPUTFILE_PATH}/*
	 do
		 echo "...loading file ${_i} of ${_filecount} from ${file}";
		 _i=$((_i+1));
		 
		 load_split_file "${file}" "${_full_temp_tablename}" "${_full_tablename}" "${_insert_columns}" "${_full_db}";
		 rc=${?};
		 
		 if (( ${ERROR} == ${rc} )); then
			print_debug "...loading error!\n"	 
			return ${ERROR};
		 fi	 
	 done
}

#===========================================================#
# loading given split file
#===========================================================#
function load_split_file
{
	 local _FUNCNAME="load_split_file";
	 typeset -r _split_filename="${1}"
	 typeset -r _full_temp_tablename="${2}"
	 typeset -r _full_tablename="${3}"
	 typeset -r _insert_columns="${4}"
	 typeset -r _full_db="${5}"
	 
	
	 typeset -r _sql_create_temp_statement="create temp table ${_full_temp_tablename} ( branchno smallint default 0 not null, customerno int default 0 not null, articleno int default 0 not null, \n \
											 quota int default 0 not null, \n \
											 validity char default '' not null, \n \
											 datefrom int default 0 not null, \n \
											 dateto int default 0 not null );";
	 
	 typeset -r _sql_load_statement="load from '${_split_filename}' delimiter '${FILE_FIELD_DELIMITER}' insert into ${_full_temp_tablename} ;"; 
	 
	 typeset -r _sql_copy_statement="insert into ${_full_tablename} (${INSERT_COLUMNS})  \
										 select t1.* from ${_full_temp_tablename} t1 left join (  \
												select *  \
												from  \
												${_full_temp_tablename} t left join ${_full_tablename} q on  \
												t.branchno = q.branchno and  \
												t.customerno = q.customerno and  \
												t.articleno = q.articleno  \
												where  \
												not q.branchno is null and  \
												not q.customerno is null and  \
												not q.articleno is null  \
												) as t2  \
										 on  \
										 t1.branchno = t2.branchno and  \
										 t1.customerno = t2.customerno and  \
										 t1.articleno = t2.articleno  \
										 where  \
										 t2.branchno is null and  \
										 t2.customerno is null and  \
										 t2.articleno is null; ";
	 
	 typeset -r _sql_delete_temp_statement="delete from ${_full_temp_tablename};";
	 
	 reset_error_indicators;
	 
	 write_to_sql_file "${_sql_create_temp_statement}" ${FALSE};
	 write_to_sql_file "${_sql_load_statement}" ${TRUE};
	 write_to_sql_file "${_sql_copy_statement}" ${TRUE};
	 write_to_sql_file "${_sql_delete_temp_statement}" ${TRUE}; #not necessary because table will be dropped when session ends
	 
	 #-------------------------------------#
 	 # load split file
 	 #-------------------------------------#	
	 do_sql_file "${_full_db}" "${OUTPUTFILE_SQL_PATH}";
	 rc=${?};
	 
	 if (( ${ERROR} == ${rc} )); then 
		return ${ERROR};
     fi	 
}

#======================================================#
# function process_loadquotabyfile
#======================================================#
function truncate_articlequota
{
	 local _FUNCNAME="truncate_articlequota";
	 typeset -r _full_tablename="${1}"
	 typeset -r _full_db="${2}"
	 
	 if (( ${FALSE} == ${clearbeforeload_flag} )); then
		print_debug "...skipping truncate because -clearbeforeload option was not set!"
		return ${OK};
     fi	 
	 
	 typeset -r _sql_truncate_statement="truncate ${_full_tablename};"; 
	 
	 write_to_sql_file "${_sql_truncate_statement}" ${FALSE};
	 
	 #-------------------------------------#
 	 # load split file
 	 #-------------------------------------#	
	 do_sql_file "${_full_db}" "${OUTPUTFILE_SQL_PATH}";
	 rc=${?};
	 
	 if (( ${ERROR} == ${rc} )); then 
		return ${ERROR};
     fi	 
	 
	 print_debug "...successfully truncated table!"
}

 #======================================================#
 # function process_loadquotabyfile
 #======================================================#
 function process_loadquotabyfile
 {
 	 local _FUNCNAME="process_loadquotabyfile";
 	 typeset -r _db="${1}";
 	 typeset -r _dbsrv="${2}";
	 typeset -r _filepath="${INPUTFILE_PATH}";
	 typeset -r _filename="${3}";
	 typeset -r _insert_columns="${4}";
	 typeset -r _delimiter="${5}";
	 	 
	 # put all values together
	 typeset -r _full_db="${db}@${dbsrv}"
	 typeset -r _full_temp_tablename="${_full_db}:loadquotabyfile_stage_table";
	 typeset -r _full_tablename="${_full_db}:articlequota";
	 typeset -r _full_filename="${_filepath}/${_filename}";
	 
	 print_debug "DATABASE: \t ${_full_db}";
	 print_debug "TABLE: \t\t ${_full_tablename}";
	 print_debug "TEMP TABLE: \t ${_full_temp_tablename}";
	 print_debug "FILE: \t\t ${_full_filename}";
	 print_debug "OUTPUT: \t ${OUTPUTFILE_PATH}/${OUTPUTFILENAME_SUFFIX}XX";
	 #print_debug "STATEMENT: \t ${_sql_load_statement}";
	 
 	 typeset -i _rc=${FALSE};

 	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # Checking input file
 	 #-------------------------------------#	 
	 evaluate_input_file "${_full_filename}";
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi	 
	 
	 #-------------------------------------#
 	 # Splitting/Junking Input
 	 #-------------------------------------#	 
	 split_input_file "${_full_filename}";
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi	 
	 
	 #-------------------------------------#
 	 # Truncate articlequota
 	 #-------------------------------------#	 
	 print_debug "\n>Truncating articlequota table";
	 
	 truncate_articlequota "${_full_tablename}" "${_full_db}";
	 rc=${?};
	 
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi	 
	 
	 #-------------------------------------#
 	 # Loading data
 	 #-------------------------------------#	 
	 print_debug "\n>Started loading data";
	 
	 load_split_files "${_full_tablename}" "${_full_temp_tablename}" "${_insert_columns}" "${_full_db}";
	 
	 #do_sql "${_sql_load_statement}" "${_full_db}" ;
	 #rc=${?};
	 
	 #if (( ${ERROR} == ${rc} )); then
	 #	 print_debug "...loading error!\n"	 
	 #	 return ${ERROR};
 	 # fi	 
	 print_debug "...loading ok!\n"
	 
 	 return ;
 }
 ###############################################################################################
 # INDIVIDUAL FUNCTIONS - END
 ###############################################################################################

 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/loadquotabyfile.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";
 print_msg "$STARTMSG" "$*"
 
 #======================================================#
 # CALLS METHOD START-PROCESS
 #======================================================#
 if [[ "$start" == "YES" ]]; then

 	 typeset -i cnt_step=1;

 	 #---------------------------------------------------------------------------------------------#
 	 msg="${PROCNAME}: Setting the informixdir.";
 	 #---------------------------------------------------------------------------------------------#
 	 echo "" | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 echo " ${cnt_step}. Step: BEGIN Setting the INFORMIX specific directory." | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 set_informixdir;
 	 rc=${?};
 	 if (( ${ERROR} == ${rc} )); then
 		 exit ${rc};
 	 fi
 	 echo "Return code: "`transform_rc ${rc}` | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 echo " ${cnt_step}. Step: END Setting the INFORMIX specific directory." | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}

 	 cnt_step=cnt_step+1;
 	 echo "" | tee -a ${LOG_RESOURCE}

 	 current_table="tablename";
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 echo " ${cnt_step}. Step: BEGIN processing table \"${current_table}\"." | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 process_loadquotabyfile "${db}" "${dbsrv}" "${filename}" "${INSERT_COLUMNS}" "${FILE_FIELD_DELIMITER}" #"${DATA_PATH}" "${filename}" "${INSERT_COLUMNS}" "${FILE_FIELD_DELIMITER}"
 	 rc=${?};
 	 if (( ${ERROR} == ${rc} )); then
 		 exit ${rc};
 	 fi
 	 echo "Return code: `transform_rc ${rc}`: ${errmsg}" | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 echo " ${cnt_step}. Step: END processing table \"${current_table}\" (Return-Code:<${rc}>)." | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}

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


 exit ${rc};
