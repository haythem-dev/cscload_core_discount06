#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            Machata, Julian                                                                                   
 #Creation-Date:     24.11.2011                                                                                
 #Creation-Time:     14:27                                                                                     
 #Creator:           procgen.sh - Version: 01.00.01.00                                                         
 #Creation-Type:     BATCH_PROCEDURE                                                                           
 #Purpose:           Starts, stops and status the exemplar binary loadpseudotours for presentation only.     
 # 					 Loading pseudo tours for all customers and each day of given branch.
 #					 Attention: All tours with the pseudo-tour-id will be deleted! The id can 
 #								be found in the pseudotours.vars file and changed if necessary.
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
 # READ IN SPECIFIC VARIABLES
 #--------------------------------------------------------------------#
 . $(dirname $0)/../vars/loadpseudotours.vars

 #--------------------------------------------------------------------#
 # LIBRARY / BINARY VARIABLES
 #--------------------------------------------------------------------# 
 readonly BINARY=loadpseudotours.bin
 process="${BIN_PATH}/${BINARY}"

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 typeset -i branchno=0;
 #--- end declaration procedure variables ---#
 start="";
 stop="";
 status="";
 typeset -i rc=0;

 typeset -i errno=0;
 errmsg="";
 INFORMIXDIR=${INFORMIXDIR};
 
 # LOGFILES
 typeset -r SQL_RESULT_FILE="${LOG_PATH}/${PROCNAME}.${$}.res"
 typeset -r SQL_ERROR_FILE="${LOG_PATH}/${PROCNAME}.${$}.err"

 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";
 readonly BRANCHNO_OPTION="-branchno";
 readonly DB_OPTION="-db";
 readonly DBSRV_OPTION="-dbsrv";

 typeset -ir ERROR=1;
 typeset -ir OK=0;
 typeset -ir HINT=2;
 typeset -ir TRUE=1;
 typeset -ir FALSE=0;
 
 

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
	 
 	 if [[ "${branchno}" == "" ]] || (( 1 != `check_numeric_parameter "${BRANCHNO_OPTION}" "${branchno}"` )) || [[ "${branchno}" == "0" ]]; then
 		 printStartStop "${STARTMSG}"
 		 rc=12;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${branchno}: >${branchno}<!" | tee -a ${LOG_RESOURCE}
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

 	 #INFORMIXDIR=${INFORMIXDIR%/*};
 	 #export INFORMIXDIR;
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
 	 typeset -ir _rc=/software/wss/hl/ksc/load;
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
		 rm ${SQL_RESULT_FILE}
		 rm ${SQL_ERROR_FILE}
 	 else
 		 errno=${ERROR};
 		 errmsg="${_FUNCNAME}: Error executing SQL-Statement (see ${SQL_ERROR_FILE})";
 		 #errmsg=${errmsg}"with error text <`cat ${SQL_ERROR_FILE}`>.";
		 echo "${_sql}" >> ${SQL_ERROR_FILE}
 	 fi
	 
 	 return ${errno};
 }
 #======================================================#
 # function load_table_tour
 #======================================================#
 function load_table_tour
 {
	 local _FUNCNAME="load_table_tour";
	 
	 typeset -r _FULL_DB=$1
	 typeset -r _BRANCHNO=$2
	 typeset -r _FULL_TABLENAME_TOUR="${_FULL_DB}:tour";
	 typeset -i _rc=${OK}
	 
	 typeset -r _STMT_DELETE_PSEUDO_TOURS="DELETE FROM ${_FULL_TABLENAME_TOUR} WHERE tourid = ${PSEUDO_TOUR_ID} AND filialnr = ${_BRANCHNO};";
	 typeset -r _STMT_INSERT_PSEUDO_TOURS="INSERT INTO ${_FULL_TABLENAME_TOUR} 
										   (datumkommi, tourid, zeitkoende, 
										   datumversand, zeitversand, bahnhofversand, 
										   tourstat, fahrtzeit, bezeichnung, bemerkungen, tourinaktiv, filialnr) 
										   values 
										   (${PSEUDO_TOUR_DATE_PICKING}, ${PSEUDO_TOUR_ID}, ${PSEUDO_TOUR_TIME_PICKING_END}, 
										   ${PSEUDO_TOUR_DATE_SHIPPING}, ${PSEUDO_TOUR_TIME_SHIPPING_END}, ${PSEUDO_TOUR_SHIPPING_STATION},
										   ${PSEUDO_TOUR_STAT}, ${PSEUDO_TOUR_DRIVING_TIME}, '${PSEUDO_TOUR_NAME}', '${PSEUDO_TOUR_NOTE}',
										   ${PSEUDO_TOUR_INACTIVE}, ${_BRANCHNO});";
	 
	 reset_error_indicators;		
	
	 do_sql "begin work; ${_STMT_DELETE_PSEUDO_TOURS} commit work;" "${_FULL_DB}"
	 _rc=${?};
	 if (( ${ERROR} == ${_rc} )); then
 		 return ${_rc};
 	 fi	 
	
	 do_sql "begin work; ${_STMT_INSERT_PSEUDO_TOURS} commit work;" "${_FULL_DB}"
	 _rc=${?};	 
	 if (( ${ERROR} == ${_rc} )); then
 		 return ${_rc};
 	 fi
	 
	 echo "\t\t -> OK!";

 	 return ${_rc};
 }
 #======================================================#
 # function load_table_tourplantagwoche
 #======================================================#
 function load_table_tourplantagwoche
 {
 	 local _FUNCNAME="load_table_tourplantagwoche";
	 
	 typeset -r _FULL_DB=$1;
	 typeset -r _BRANCHNO=$2;
	 typeset -r _FULL_TABLENAME_TOURPLANTAGWOCHE="${_FULL_DB}:tourplantagwoche";
	 typeset -i _rc=${OK};
	 typeset -i _counter=0; 								
	 set -A  _WEEKDAYS "SO" "MO" "DI" "MI" "DO" "FR" "SA"; # number 0 is for sunday, 6 for saturday
	 
	 for weekday in ${_WEEKDAYS[@]}
	 do
		 echo "\t\t ...loading tour for weekday '${weekday}'";
		 reset_error_indicators;	
	  
		 _STMT_DELETE_PSEUDO_ENTRY="DELETE FROM ${_FULL_TABLENAME_TOURPLANTAGWOCHE} 
												WHERE tourid = ${PSEUDO_TOUR_ID} AND vertriebszentrumnr = ${_BRANCHNO}
												AND tagestyp = '${weekday}' AND weekday = ${_counter};";
		 _STMT_INSERT_PSEUDO_ENTRY="INSERT INTO ${_FULL_TABLENAME_TOURPLANTAGWOCHE} 
											   (vertriebszentrumnr, kundennr, tourid, tagestyp, weekday) 
											   select ${_BRANCHNO}, kd.idfnr, ${PSEUDO_TOUR_ID}, '${weekday}', ${_counter} 
											   from kunde kd where filialnr = ${_BRANCHNO};";
		 _counter=$_counter+1;

		 do_sql "begin work; ${_STMT_DELETE_PSEUDO_ENTRY} commit work;" "${_FULL_DB}"
		 _rc=${?};	 
		 if (( ${ERROR} == ${_rc} )); then
			 return ${_rc};
		 fi
		 
		 do_sql "begin work; ${_STMT_INSERT_PSEUDO_ENTRY} commit work;" "${_FULL_DB}"
		 _rc=${?};	 
		 if (( ${ERROR} == ${_rc} )); then
			 return ${_rc};
		 fi
	 
	 done 	
	 
	 echo "\t\t -> OK!";

 	 return ${_rc};
 }
 #======================================================#
 # function load_table_tourplantag
 #======================================================#
 function load_table_tourplantag
 {
 	 local _FUNCNAME="load_table_tourplantag";
	 
	 typeset -r _FULL_DB=$1;
	 typeset -r _BRANCHNO=$2;
	 typeset -r _FULL_TABLENAME_TOURPLANTAG="${_FULL_DB}:tourplantag";
	 typeset -i _rc=${OK};
	 
	 reset_error_indicators;
		 	
	 _STMT_DELETE_PSEUDO_ENTRY="DELETE FROM ${_FULL_TABLENAME_TOURPLANTAG} 
											WHERE tourid = ${PSEUDO_TOUR_ID} AND vertriebszentrumnr = ${_BRANCHNO};";
	 _STMT_INSERT_PSEUDO_ENTRY="INSERT INTO ${_FULL_TABLENAME_TOURPLANTAG} 
										   (vertriebszentrumnr, kundennr, idfnr, datumkommi, tourid, 
										   tourinaktiv, kzautozuord) 
										   select ${_BRANCHNO}, kd.idfnr, kd.idfnr, ${PSEUDO_TOUR_DATE_PICKING}, ${PSEUDO_TOUR_ID}, 
										   ${PSEUDO_TOUR_INACTIVE}, ${PSEUDO_TOUR_CUSTOMER_AUTO_ASSIGNEMENT} 
										   from kunde kd where filialnr = ${_BRANCHNO};";

	 do_sql "begin work; ${_STMT_DELETE_PSEUDO_ENTRY} commit work;" "${_FULL_DB}"
	 _rc=${?};	 
	 if (( ${ERROR} == ${_rc} )); then
		 return ${_rc};
	 fi
	 
	 do_sql "begin work; ${_STMT_INSERT_PSEUDO_ENTRY} commit work;" "${_FULL_DB}"
	 _rc=${?};	 
	 if (( ${ERROR} == ${_rc} )); then
		 return ${_rc};
	 fi
	 
	 echo "\t\t -> OK!";

 	 return ${_rc};
 }
 #======================================================#
 # function process_loadpseudotours
 #======================================================#
 function process_loadpseudotours
 {
 	 local _FUNCNAME="process_loadpseudotours";
	 
	 typeset -r _FULL_DB="${1}@${2}";
	 typeset -r _BRANCHNO=$3;
	 typeset -r _FULL_TABLENAME_TOUR="${_FULL_DB}:tour";
	 typeset -r _FULL_TABLENAME_TOURPLANTAGWOCHE="${_FULL_DB}:tourplantagwoche";
	 typeset -r _FULL_TABLENAME_TOURPLANTAG="${_FULL_DB}:tourplantag";
 
	 reset_error_indicators;
	 
	 echo "\n";
		 
	 #-------------------------------------#
	 # loading table tour
	 #-------------------------------------#
	 echo "\t 1. loading table ${_FULL_TABLENAME_TOUR}";	 
	 load_table_tour "${_FULL_DB}" ${_BRANCHNO}
	 _rc=${?};
	 if (( ${ERROR} == ${_rc} )); then
		 return ${_rc};
	 fi
	 
	 #-------------------------------------#
	 # loading table tourplantagwoche
	 #-------------------------------------#	 
	 echo "\t 2. loading table ${_FULL_TABLENAME_TOURPLANTAGWOCHE}";	 
	 load_table_tourplantagwoche "${_FULL_DB}" ${_BRANCHNO}
	 _rc=${?};
	 if (( ${ERROR} == ${_rc} )); then
		 return ${_rc};
	 fi
	 
	 #-------------------------------------#
	 # loading table tourplantag
	 #-------------------------------------#	 
	 echo "\t 3. loading table ${_FULL_TABLENAME_TOURPLANTAG}";	 
	 load_table_tourplantag "${_FULL_DB}" ${_BRANCHNO}
	 _rc=${?};
	 if (( ${ERROR} == ${_rc} )); then
		 return ${_rc};
	 fi
	 
	 echo "\n";
	 
 	 return ${OK};
 }
 ###############################################################################################
 # INDIVIDUAL FUNCTIONS - END
 ###############################################################################################

 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/loadpseudotours.option
 
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
 	 echo " ${cnt_step}. Step: BEGIN loading pseudo tours." | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 process_loadpseudotours "${db}" "${dbsrv}" "${branchno}"
 	 rc=${?};
 	 if (( ${ERROR} == ${rc} )); then
 		 exit ${rc};
 	 fi
 	 echo "Return code: `transform_rc ${rc}`: ${errmsg}" | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 echo " ${cnt_step}. Step: loading pseudo tours. (Return-Code:<${rc}>)." | tee -a ${LOG_RESOURCE}
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
