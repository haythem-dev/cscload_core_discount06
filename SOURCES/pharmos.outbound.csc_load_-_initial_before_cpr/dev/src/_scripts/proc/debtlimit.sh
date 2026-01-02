#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            j.machat                                                                                  
 #Creation-Date:     21.05.2012                                                                                
 #Creation-Time:     16:58                                                                                     
 #Creator:           procgen.sh - Version: 01.00.01.00                                                         
 #Creation-Type:     BATCH_PROCEDURE                                                                           
 #Purpose:           Starts, stops and status the exemplar binary debtlimit for presentation only.             
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
 . $(dirname $0)/../vars/debtlimit.vars

 #--------------------------------------------------------------------#
 # LIBRARY / BINARY VARIABLES
 #--------------------------------------------------------------------#
 readonly BINARY=debtlimit.bin
 process="${BIN_PATH}/${BINARY}"

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 typeset -i noreset_flag=0;       	#incremental update, does not set to zero if no updates found
 typeset -i nosap_flag=0;         	#does not load or reset sum_creditside and sum_debitside
 typeset -i noturnover_flag=0;    	#does not load or reset monturnover, dayturnover, returns
 typeset -i nodebitside_flag=0;   	#does not load or reset debitside from sap
 typeset -i nocreditside_flag=0;  	#does not load or reset creditside from sap
 typeset -i nocreditlimit_flag=0; 	#does not load or reset credit limit (crema)
 typeset -i nomonturnover_flag=0; 	#does not load or reset monturnover from db
 typeset -i nodayturnover_flag=0; 	#does not reset dayturnover
 typeset -i noreturns_flag=0;     	#does not load or reset returns
 typeset -i resethalfmonth_flag=0;	#does indicate that halfmonth payments are loaded and necessary steps are to do
 typeset -i crema_flag=0;	  	#does indicate that the crema sqls are to be done
 typeset -i fak_tunrover=1;	  	#does indicate that the invoicing data is used for turnover
 typeset -i fak_file_set=0;
 typeset -i fak_file_allowed=0;
 									
 #--- end declaration procedure variables ---#
 start="";
 stop="";
 status="";
 typeset -i rc=0;

 typeset -i errno=0;
 errmsg="no error(s)";
 INFORMIXDIR=${INFORMIXDIR};
 
  # INDIVIDUAL RETURN VALUES
 typeset -ir RET_CODE_SAP_FILE_NOT_EXISTING=13;
 typeset -ir RET_CODE_SAP_FILE_NO_READ_RIGHTS=14;
 typeset -ir RET_CODE_UNLOAD_TURNOVER=15;
 typeset -ir RET_CODE_TURNOVER_FILE_NOT_EXISTING=16;
 typeset -ir RET_CODE_TURNOVER_SQL_FORMAT_FAILED=17;
 typeset -ir RET_CODE_TURNOVER_FORMAT_FILE_NOT_EXISTING=18;
 typeset -ir RET_CODE_SAP_BALANCE_FORMAT_FILE_NOT_EXISTING=19;
 typeset -ir RET_CODE_SAP_LIMIT_FORMAT_FILE_NOT_EXISTING=20;
 typeset -ir RET_CODE_SAP_SQL_FORMAT_FAILED=21;
 typeset -ir RET_CODE_BACKUP_PATH_ODD=22;
 typeset -ir RET_CODE_FAK_FILE_NOT_EXISTING=23;
 
 #FULL PATH VARIABLES TO A FILE
 readonly PATH_SAP_BALANCE_EXPORT="${DIR_SAP_EXPORT}/${FILE_SAP_BALANCE}";					
 readonly PATH_SAP_BALANCE_EXPORT_FORMAT="${DIR_WORK}/${FILE_SAP_BALANCE_FORMAT}";
 readonly PATH_SAP_LIMIT_EXPORT="${DIR_SAP_EXPORT}/${FILE_SAP_LIMIT}"; #"${DIR_SAP_EXPORT}/${FILE_SAP_LIMIT}";					
 readonly PATH_SAP_LIMIT_EXPORT_FORMAT="${DIR_WORK}/${FILE_SAP_LIMIT_FORMAT}";
 readonly PATH_SAP_EXPORT_SQL="${DIR_WORK}/${FILE_SAP_SQL}";			
 readonly PATH_TURNOVER="${DIR_WORK}/${FILE_TURNOVER}";
 readonly PATH_TURNOVER_FORMAT="${DIR_WORK}/${FILE_TURNOVER_FORMAT}";
 readonly PATH_TURNOVER_SQL="${DIR_WORK}/${FILE_TURNOVER_SQL}";	
 readonly PATH_TURNOVER_FAK_EXPORT="${DIR_SAP_EXPORT}/${FILE_TURNOVER_FAK}";
 readonly PATH_TURNOVER_FAK_SQL="${DIR_WORK}/${FILE_TURNOVER_FAK_SQL}";
 readonly PATH_CREMA_SQL="${DIR_WORK}/${FILE_CREMA_SQL}";
 readonly PATH_FILE_EXPORT_SAP_TURNOVER="${DIR_DATA}/${FILE_EXPORT_SAP_TURNOVER}"; 
 
 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";
 readonly NORESET_OPTION="-noreset";
 readonly NOSAP_OPTION="-nosap";
 readonly NOTURNOVER_OPTION="-noturnover";
 readonly NODEBITSIDE_OPTION="-nodebitside";   
 readonly NOCREDITSIDE_OPTION="-nocreditside";  
 readonly NOCREDITLIMIT_OPTION="-nocreditlimit";  
 
 readonly NOMONTURNOVER_OPTION="-nomonturnover"; 
 readonly NODAYTURNOVER_OPTION="-nodayturnover"; 
 readonly NORETURNS_OPTION="-noreturns";     
 readonly RESETHALFMONTH_OPTION="-resethalfmonth";     
 readonly CREMA_OPTION="-crema";    
 readonly FAK_TURNOVER_OPTION="-fak";
 readonly FAK_FILE_SET_OPTION="-fakfile"
  
 typeset -ir ERROR=1;
 typeset -ir OK=0;
 typeset -ir HINT=2;
 typeset -ir TRUE=1;
 typeset -ir FALSE=0;

 #SQLs
  typeset -r sql_update_debtlimit_mturnover="update debtlimit d set sum_monturnover = (select NVL((sum(c.amount)),0) \
												from cstinvoicedata c inner join kunde k on c.customerno = k.kundennr and c.branchno = k.filialnr \
												where k.partnernr = d.partnerno and c.doctype = 1 and c.invoiced = 0);"
 if (( ${UPDATE_SUM_WE} == "1" )); then	 
	typeset -r sql_update_debtlimit_cturnover="update debtlimit d set sum_returns = (select times(NVL(sum(c.amount),0),-1) \
												from cstinvoicedata c inner join kunde k on c.customerno = k.kundennr and c.branchno = k.filialnr \
												where k.partnernr = d.partnerno and c.doctype = 2 and c.invoiced = 0 and c.textkey = 20); \
												update debtlimit d set sum_goodsreceipt = (select times(NVL(sum(c.amount),0),-1) \
												from cstinvoicedata c inner join kunde k on c.customerno = k.kundennr and c.branchno = k.filialnr \
												where k.partnernr = d.partnerno and c.doctype = 2 and c.invoiced = 0 and c.textkey = 21);"
 else											
	typeset -r sql_update_debtlimit_cturnover="update debtlimit d set sum_returns = (select times(NVL(sum(c.amount),0),-1) \
												from cstinvoicedata c inner join kunde k on c.customerno = k.kundennr and c.branchno = k.filialnr \
												where k.partnernr = d.partnerno and c.doctype = 2 and c.invoiced = 0 and c.textkey = 20);"
 fi

 typeset -r sql_create_sap_turnover="select c.customerno as customerno, c.branchno as branchno, NVL((sum(c.amount)),0) as turnover from cstinvoicedata c \
									inner join kunde k  on c.customerno = k.kundennr and c.branchno = k.filialnr \
									where (c.doctype = 1 and c.invoiced = 0) or (c.doctype = 2 and c.textkey = 20 and c.invoiced = 0) \
									or (c.doctype = 2 and c.textkey = 21 and c.invoiced = 0) \
									group by c.customerno, c.branchno \
									order by c.customerno, c.branchno \
									into temp t_export_sap_turnover; \
									unload to ${PATH_FILE_EXPORT_SAP_TURNOVER} delimiter ';' select branchno, customerno, turnover from t_export_sap_turnover;";
									
typeset -r sql_update_sum_dayturnover="update debtlimit d set sum_dayturnover = (select NVL(sum(wertlieferung),0) from kdauftrag where kundennr in \
									(select kundennr from kunde k where d.partnerno = k.partnernr));";

 
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
	 printf "%-30s%-90s\n" "\$NORESET_OPTION:" ">$NORESET_OPTION<"
	 printf "%-30s%-90s\n" "\$NOSAP_OPTION:" ">$NOSAP_OPTION<"
	 printf "%-30s%-90s\n" "\$NOTURNOVER_OPTION:" ">$NOTURNOVER_OPTION<"
	 printf "%-30s%-90s\n" "\$NODEBITSIDE_OPTION:" ">$NODEBITSIDE_OPTION<"
	 printf "%-30s%-90s\n" "\$NOCREDITSIDE_OPTION:" ">$NOCREDITSIDE_OPTION<"
	 printf "%-30s%-90s\n" "\$NOCREDITLIMIT_OPTION:" ">$NOCREDITLIMIT_OPTION<"
	 printf "%-30s%-90s\n" "\$NOMONTURNOVER_OPTION:" ">$NOMONTURNOVER_OPTION<"
	 printf "%-30s%-90s\n" "\$NODAYTURNOVER_OPTION:" ">$NODAYTURNOVER_OPTION<"
	 printf "%-30s%-90s\n" "\$NORETURNS_OPTION:" ">$NORETURNS_OPTION<"
	 printf "%-30s%-90s\n" "\$RESETHALFMONTH_OPTION:" ">$RESETHALFMONTH_OPTION<"
	 printf "%-30s%-90s\n" "\$CREMA_OPTION:" ">$CREMA_OPTION<"
	 printf "%-30s%-90s\n" "\$FAK_TURNOVER_OPTION:" ">$FAK_TURNOVER_OPTION<"
	 
 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
	 printf "%-30s%-90s\n" "\$noreset:" ">$noreset<"
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
	print_debug "eval_parameters";
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
 		 if [[ "$1" == "$NORESET_OPTION" ]]; then
 			 shift;
			 noreset_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$NOSAP_OPTION" ]]; then
 			 shift;
			 nosap_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$NOTURNOVER_OPTION" ]]; then
 			 shift;
			 noturnover_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$NODEBITSIDE_OPTION" ]]; then
 			 shift;
			 nodebitside_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$NOCREDITSIDE_OPTION" ]]; then
 			 shift;
			 nocreditside_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$NOCREDITSIDE_OPTION" ]]; then
 			 shift;
			 nocreditlimit_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$NOMONTURNOVER_OPTION" ]]; then
 			 shift;
			 nomonturnover_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$NODAYTURNOVER_OPTION" ]]; then
 			 shift;
			 nodayturnover_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$NORETURNS_OPTION" ]]; then
 			 shift;
			 noreturns_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$RESETHALFMONTH_OPTION" ]]; then
 			 shift;
			 resethalfmonth_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$CREMA_OPTION" ]]; then
 			 shift;
			 crema_flag=1;
			 continue;
 		 fi
		 
		 #read in parameters
 		 if [[ "$1" == "$FAK_TURNOVER_OPTION" ]]; then
			 shift;
			 fak_tunrover=1;
			 continue;
 		 fi

		 if [[ "$1" == "$FAK_FILE_SET_OPTION" ]]; then
			 shift;
			 echo ${ARRAY_TURNOVER_FAK[@]} | grep $1 >/dev/null;
			 if [[ "$?" == "0" ]]; then
				fak_file_allowed=1;
			 else
				fak_file_allowed=0;
			 fi
			 unset ARRAY_TURNOVER_FAK;
			 set -A ARRAY_TURNOVER_FAK $1;
			 print_debug "ARRAY_TURNOVER_FAK: ${ARRAY_TURNOVER_FAK[@]}";
			 fak_file_set=1;
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
 # backup given file
 #===========================================================#
 function backup_file
 {
	 local _FUNCNAME="backup_file";
	 local _FILENAME="${1}";
	 local _TODAY=`date +%Y-%m-%d`;
	 
	 reset_error_indicators;

	 #-------------------------------------#
 	 # check if file is existing
 	 #-------------------------------------#
	 check_is_file_existing "${_FILENAME}";
	 rc=${?};
	 
 	 if (( ${TRUE} == ${rc} )); then
		 if (( ${TRUE} == ${CTRL_BACKUP} )); then
			 cp "${_FILENAME}" "${DIR_BACKUP}/${_TODAY}.${$}.${_FILENAME##*/}.bu"
		 fi
 	 fi
}
 #======================================================#
 # prints output
 #======================================================#
 function print_debug
 {
	 local _FUNCNAME="print_debug";
	 local _msg="${1}"
	 
	 if (( CTRL_PRINT_DEBUG_OUTPUT==TRUE )); then
		echo "${_msg}" | tee -a ${LOG_RESOURCE}
	 fi
 }
 #===========================================================#
 # Sets the directory of informix automatically
 #===========================================================#
 function set_informixdir
 {
 	 local _FUNCNAME="set_informixdir";

 	 reset_error_indicators;

 	 #INFORMIXDIR=${INFORMIXDIR%/*}; #unix foundation!
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
 		 ${ERROR}) _result="ERROR";;
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
 	 typeset -ir _rc=/software/home/j.machat/ch/ksc/batch;
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
 	 local _result_file="${DIR_BACKUP}/${PROCNAME}.${$}.res"
 	 local _error_file="${DIR_BACKUP}/${PROCNAME}.${$}.err"
 	 typeset -i _rc=${ERROR};
 	 reset_error_indicators;

 	 echo "${_sql}" | dbaccess ${_db} 1>${_result_file} 2>${_error_file};
 	 _rc=${?};

 	 if (( ${OK} == ${_rc} )); then
 		 set -A arr_result `cat ${_result_file}`;
 		 if (( 0 == ${#arr_result[*]} )); then
 			 _rc=${OK};
 		 else
 			 _rc=${arr_result[1]};
 		 fi
		 rm ${_result_file};
		 rm ${_error_file};
 	 else
 		 errno=${ERROR};
 		 errmsg="${_FUNCNAME}: Error executing following SQL-String: <${_sql}>";
 		 errmsg=${errmsg}"with error text <`cat ${_error_file}`>.";
 	 fi

 	 return ;
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
	 local _result_file="${DIR_BACKUP}/${PROCNAME}.${$}.res"
 	 local _error_file="${DIR_BACKUP}/${PROCNAME}.${$}.err"
	 
 	 reset_error_indicators;
	 
	 dbaccess "${_FULL_DB}" "${_SQL_STATEMENT_FILE}" 1>${_result_file} 2>${_error_file};
 	 _rc=${?};	 
	 
	 if (( ${OK} == ${_rc} )); then
 		 set -A arr_result `cat ${_result_file}`;
 		 if (( 0 == ${#arr_result[*]} )); then
 			 _rc=${OK};
 		 else
 			 _rc=${arr_result[1]};
 		 fi
		 rm ${_result_file};
		 rm ${_error_file};
 	 else
 		 errno=${ERROR};
 		 errmsg="${_FUNCNAME}: Error when executing <${_SQL_STATEMENT_FILE}>, see error file!";
		 return ${ERROR};
 	 fi

 	 return ${OK};
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
 # checks if backup dir exists and create if necessary
 #===========================================================#
 function create_backup_dir
 {
 	 local _FUNCNAME="create_backup_dir";
	  
	 
	 local _dirname=${1};
	 
	 reset_error_indicators
	 
 	 if [[ ! -d "${_dirname}" ]]; then	
	 
		 reset_error_indicators;
		 mkdir ${_dirname};
		 rc=${?};
		 if (( ${FALSE} == ${rc} )); then
			return ${FALSE}; 
		 fi
	 fi
	 
	 return ${TRUE};
 }
 #===========================================================#
 # evaluating input parameters such as file and directory
 #===========================================================#
 function evaluate_input
 {
 	 local _FUNCNAME="evaluate_input";
	  
	 
	 reset_error_indicators;
	 
	 print_debug "\n>Started evaluating input parameters";
	 
	 if (( ${FALSE} == ${nosap_flag} )); then
	 
		 #-------------------------------------#
		 # check if sap file is existing
		 #-------------------------------------#
		 check_is_file_existing "${PATH_SAP_BALANCE_EXPORT}";
		 rc1=${?};
		 check_is_file_existing "${PATH_SAP_LIMIT_EXPORT}";
		 rc2=${?};
		 
		 if (( ${FALSE} == ${rc1} || ${FALSE} == ${rc2} )); then
			 errno=${RET_CODE_SAP_FILE_NOT_EXISTING};
			 if (( ${FALSE} == ${CTRL_CONTINUE_ON_ERROR} )); then
				 return ${ERROR};
			 else
				if (( ${FALSE} == ${rc1} )); then
					print_debug "...error <${errno}>, SAP-Balance file not existing"
					nodebitside_flag=${TRUE};
					nocreditside_flag=${TRUE};
					print_debug "...continue anyway without loading SAP-Balance! ([${NOCREDITSIDE_OPTION}] and [${NODEBITSIDE_OPTION}])"
				fi
				if (( ${FALSE} == ${rc2} )); then
					print_debug "...error <${errno}>, SAP-Limit file not existing"
					nocreditlimit_flag=${TRUE};
					print_debug "...continue anyway without loading SAP-Limits!"
				fi
			 fi
		 fi
		
		echo ${ARRAY_TURNOVER_FAK[@]}
		for i in ${ARRAY_TURNOVER_FAK[@]}
		do
			_PATH_TURNOVER_FAK_EXPORT="${DIR_SAP_EXPORT}/${i}"
			
			if (( $fak_file_set == 1 && $fak_file_allowed == 0 )); then
						print_debug "Exiting... Given file ${_PATH_TURNOVER_FAK_EXPORT} not allowed!!!"
						exit ${RETURN_ON_FAK_ERROR};	
			fi
			
			check_is_file_existing "${_PATH_TURNOVER_FAK_EXPORT}";
			rc=${?};
			if (( ${FALSE} == ${rc} )); then
					errno=${RET_CODE_FAK_FILE_NOT_EXISTING};
					print_debug "...error <${errno}>, file ${_PATH_TURNOVER_FAK_EXPORT} not existing"					
					nomonturnover_flag=${TRUE};
					noturnover_flag=${TRUE};
					print_debug "...continue without turnover!"
			fi
		done;
	 
		 #-------------------------------------#
		 # check if sap file is readable (only if it was existing)
		 #-------------------------------------#
		 if (( ${TRUE} == ${rc1} && ${TRUE} == ${rc2} )); then
			 check_is_file_readable "${PATH_SAP_BALANCE_EXPORT}";
			 rc1=${?};
			 check_is_file_readable "${PATH_SAP_LIMIT_EXPORT}";
			 rc2=${?};
			 
			 if (( ${FALSE} == ${rc1} || ${FALSE} == ${rc2} )); then
				 errno=${RET_CODE_SAP_FILE_NO_READ_RIGHTS};
				 if (( ${FALSE} == ${CTRL_CONTINUE_ON_ERROR} )); then
					 return ${ERROR};
				 else
					if (( ${FALSE} == ${rc1} )); then
						print_debug "...error <${errno}>, No read rights for SAP-Balance file!"
						nodebitside_flag=${TRUE};
						nocreditside_flag=${TRUE};
						print_debug "...continue anyway without loading SAP-Balance! ([${NOCREDITSIDE_OPTION}] and [${NODEBITSIDE_OPTION}])"
					fi
					if (( ${FALSE} == ${rc2} )); then
						print_debug "...error <${errno}>, No read rights for SAP-Limit file!"
						nocreditlimit_flag=${TRUE};
						print_debug "...continue anyway without loading SAP-Limits!"
					fi
				 fi
			 fi
		 fi
		 
		 # ask again because could have changed since we may continue after error
		 if (( ${FALSE} == ${nosap_flag} )); then
			print_debug "...SAP input files are OK";
		 fi
		 
	 fi	
	 
	 #-------------------------------------#
 	 # create backup dir if necessary
 	 #-------------------------------------#
	 if (( ${TRUE} == ${CTRL_BACKUP} )); then
		 create_backup_dir "${DIR_BACKUP}";
		 rc=${?};
	 
		 if (( ${FALSE} == ${rc} )); then
			 print_debug "...backup directory does not exist and cannot be created, continue anyway!";	  
		 else 
			 print_debug "...backup directory is OK";
		 fi
	 fi	
		
 	 return ${OK};
 }
 #===========================================================#
 # printing debug information
 #===========================================================#
 function print_info
 {
 	 local _FUNCNAME="print_info";
	  
	 
	 reset_error_indicators;
	 
	 print_debug "\n>Values for loading";
	 print_debug "...SAP balance file:\t<${PATH_SAP_BALANCE_EXPORT}>";
	 print_debug "...SAP limit file:\t<${PATH_SAP_LIMIT_EXPORT}>";
	 
	for i in ${ARRAY_TURNOVER_FAK[@]}
	do
		_PATH_TURNOVER_FAK_EXPORT="${DIR_SAP_EXPORT}/${i}"
		print_debug "...FAK turnover file:\t<${_PATH_TURNOVER_FAK_EXPORT}>";
	done;

	 print_debug "...turnover DB:\t\t<${DB_TURNOVER}>";
	 print_debug "...debtlimit DB:\t<${DB_DEBTLIMIT}>";
	 if (( ${TRUE} == ${noreset_flag} )); then		 
		 print_debug "...reset:\t\t<NO>";
	 else
		 print_debug "...reset:\t\t<YES>";
 	 fi
	 if (( ${TRUE} == ${nosap_flag} )); then		 
		 print_debug "...load SAP:\t\t<NO>";
	 else
		 print_debug "...load SAP:\t\t<YES>";
 	 fi
	 if (( ${TRUE} == ${noturnover_flag} )); then		 
		 print_debug "...load turnover:\t<NO>";
	 else
		 print_debug "...load turnover:\t<YES>";
 	 fi
	 if (( ${TRUE} == ${nodebitside_flag} )); then		 
		 print_debug "...load debitside:\t<NO>";
	 else
		 print_debug "...load debitside:\t<YES>";
 	 fi
	 if (( ${TRUE} == ${nocreditside_flag} )); then		 
		 print_debug "...load creditside:\t<NO>";
	 else
		 print_debug "...load creditside:\t<YES>";
 	 fi
	 if (( ${TRUE} == ${nocreditlimit_flag} )); then		 
		 print_debug "...load creditlimit:\t<NO>";
	 else
		 print_debug "...load creditlimit:\t<YES>";
 	 fi
	 if (( ${TRUE} == ${nomonturnover_flag} )); then		 
		 print_debug "...load monturnover:\t<NO>";
	 else
		 print_debug "...load monturnover:\t<YES>";
 	 fi
	 if (( ${TRUE} == ${nodayturnover_flag} )); then		 
		 print_debug "...reset dayturnover:\t<NO>";
	 else
		 print_debug "...reset dayturnover:\t<YES>";
 	 fi
	 if (( ${TRUE} == ${noreturns_flag} )); then		 
		 print_debug "...load returns:\t<NO>";
	 else
		 print_debug "...load returns:\t<YES>";
 	 fi
	 if (( ${TRUE} == ${resethalfmonth_flag} )); then		 
		 print_debug "...reset halfmonth:\t<YES>";
	 else
		 print_debug "...reset halfmonth:\t<NO>";
 	 fi
	 if (( ${TRUE} == ${crema_flag} )); then		 
		 print_debug "...perform crema sqls:\t<YES>";
	 else
		 print_debug "...perform crema sqls:\t<NO>";
 	 fi
	 if (( ${TRUE} == ${fak_tunrover} )); then		 
		 print_debug "...perform invoicing turnover sqls:\t<YES>";
	 else
		 print_debug "...perform invoicing turnover sqls:\t<NO>";
 	 fi
	 if (( ${TRUE} == ${CTRL_CONTINUE_ON_ERROR} )); then		 
		 print_debug "...continue on error:\t<YES>";
	 else
		 print_debug "...continue on error:\t<NO>";
 	 fi
	 if (( ${TRUE} == ${CTRL_BACKUP} )); then		 
		 print_debug "...backup:\t\t<YES>";
		 print_debug "...backup dir:\t\t<${DIR_BACKUP}>";
	 else
		 print_debug "...backup:\t\t<NO>";
 	 fi
 	 return ${OK};
 }
 #===========================================================#
 # unload turnover + returns from database 
 #===========================================================#
 function unload_turnover
 {
	 local _FUNCNAME="unload_turnover";
	  
	 
	 local _SQL_UNLOAD="";
	 
	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # get current date
 	 #-------------------------------------#
	 YEAR=20`date '+%y'`;
	 MONTH=`date '+%m'`;
	 TODAY=`date +%Y-%m-%d`;
	 
	 #-------------------------------------#
 	 # unload database
 	 #-------------------------------------#
	 _SQL_UNLOAD="UNLOAD TO '${PATH_TURNOVER}' \
				  SELECT k.partnernr, sum(m.ums_aep_kl) ums, sum(m.wertgutschrift) gut \
				  FROM kundemonums m, kunde k \
				  WHERE m.kundennr IN (SELECT kundennr FROM kunde WHERE partnernr > 0) \
				  AND m.vertriebszentrumnr IN (SELECT vertriebszentrumnr FROM kunde WHERE partnernr > 0) \
				  AND m.jahr = ${YEAR} \
				  AND m.monat = ${MONTH} \
				  AND m.kundennr = k.kundennr \
				  AND m.vertriebszentrumnr = k.vertriebszentrumnr AND k.partnernr > 0 \
				  GROUP BY k.partnernr;";
	 
	 do_sql "${_SQL_UNLOAD}" "${DB_TURNOVER}"
	 
	 rc=${?};
	 
	 if (( ${ERROR} == ${rc} )); then
	 
  		 errno=${RET_CODE_UNLOAD_TURNOVER};
 		 errmsg="${_FUNCNAME}: Error when trying to unload turnover from DB!";
		 
		 return ${ERROR};
 	 fi
	 
	 return ${OK};
 }
 #===========================================================#
 # creating sql file and execute to update turnover data in debtlimit
 #===========================================================#
 function update_turnover
 {
	 local _FUNCNAME="update_turnover"; 	 
	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # check if formatted turnover file is existing
 	 #-------------------------------------#
	 check_is_file_existing "${PATH_TURNOVER_FORMAT}";
	 rc=${?};
	 
 	 if (( ${FALSE} == ${rc} )); then
		 
  		 errno=${RET_CODE_TURNOVER_FORMAT_FILE_NOT_EXISTING};
 		 errmsg="${_FUNCNAME}: Formatted turnover file does not exist!";
		 
		 return ${ERROR};
	 fi	 
	 
	 #-------------------------------------#
 	 # creating sql file for mass update
 	 #-------------------------------------#
	 cat /dev/null > ${PATH_TURNOVER_SQL}; 
	 
	 if (( ${TRUE} == ${noreset_flag} )); then
		print_debug "...skipping reset of turnover because [${NORESET_OPTION}] was set";
	 else
		 if (( ${FALSE} == ${nomonturnover_flag} )); then
			echo "update debtlimit set sum_monturnover = 0;\n" >> ${PATH_TURNOVER_SQL};
		 fi
		 if (( ${FALSE} == ${nodayturnover_flag} )); then
			echo "update debtlimit set sum_dayturnover = 0;\n" >> ${PATH_TURNOVER_SQL};
		 fi
		 if (( ${FALSE} == ${noreturns_flag} )); then
			echo "update debtlimit set sum_returns = 0;\n" >> ${PATH_TURNOVER_SQL};
		 fi
	 fi
	
	if (( ${TRUE} == ${fak_tunrover} )); then
			load_cstinvoicedata;
			rc=${?};
	else
		awk -F\| ' 
		{
			PARTNR = $1; UMS = $2; GUT = $3;
			if ( "'"${FALSE}"'" == "'"${nomonturnover_flag}"'" )
				printf("update debtlimit set sum_monturnover = "UMS" where partnerno ="PARTNR" ;\n");
			if ( "'"${FALSE}"'" == "'"${noreturns_flag}"'" )
				printf("update debtlimit set sum_returns = "GUT" where partnerno ="PARTNR" ;\n");
		}' "${PATH_TURNOVER_FORMAT}" >> "${PATH_TURNOVER_SQL}"
		
	 rc=${?};
	fi 
	 if [[ ${rc} -ne 0 ]];	then
  		 errno=${RET_CODE_TURNOVER_SQL_FORMAT_FAILED};
 		 errmsg="${_FUNCNAME}: Formatting of turnover sql file failed!";
		 
		 return ${ERROR};
	 fi
	 
	 if (( ${TRUE} == ${noreset_flag} )); then
		print_debug "...skipping reset of halfmonthturnover because [${NORESET_OPTION}] was set";
	 else
		 if (( ${TRUE} == ${resethalfmonth_flag} )); then
			echo "update debtlimit set sum_monturnover = 0 where partnerno in ( \
			      select partnernr from kunde left join kundekondi on kunde.idfnr = kundekondi.idfnr and kunde.filialnr = kundekondi.vertriebszentrumnr  where partnernr > 0 and paymentinterval = 'H' \
				  );\n" >> ${PATH_TURNOVER_SQL};
		 fi
	 fi
	 
	 #-------------------------------------#
 	 # execute and backup sql file
 	 #-------------------------------------#
	 do_sql_file "${DB_DEBTLIMIT}" "${PATH_TURNOVER_SQL}"
	 rc=${?};
	 if (( ${ERROR} == ${rc} )); then	
 		 return ${ERROR}; 
	 fi
	 backup_file "${PATH_TURNOVER}";
	 backup_file "${PATH_TURNOVER_FORMAT}";
	 backup_file "${PATH_TURNOVER_SQL}";
 	 
	 return ${OK};
}
 #===========================================================#
 # format unloaded turnover file
 #===========================================================#
 function format_turnover
 {
	 local _FUNCNAME="format_turnover";
	  
	 
	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # check if turnover file is existing
 	 #-------------------------------------#
	 check_is_file_existing "${PATH_TURNOVER}";
	 rc=${?};
	 
 	 if (( ${FALSE} == ${rc} )); then
		 
  		 errno=${RET_CODE_TURNOVER_FILE_NOT_EXISTING};
 		 errmsg="${_FUNCNAME}: Turnover file from unload does not exist!";
		 
		 return ${ERROR};
 	 fi
	 
	 #-------------------------------------#
 	 # format comma to dot
 	 #-------------------------------------#
	 cat "${PATH_TURNOVER}" | sed 's/,/./g' > "${PATH_TURNOVER_FORMAT}"

	 return ${OK};
 }
 #===========================================================#
 # getting turnover + returns from database and format it
 #===========================================================#
 function load_turnover
 {
	 local _FUNCNAME="load_turnover";
	  
	 
	 reset_error_indicators;
	 
	 print_debug "\n>Loading turnover to DB";
	 
	 #-------------------------------------#
 	 # unload database
 	 #-------------------------------------#
	 touch "${PATH_TURNOVER_FORMAT}"
	 touch "${PATH_TURNOVER}"
	 
	 if (( ${FALSE} == ${fak_tunrover} )); then
		unload_turnover;
		rc=${?};
	 fi	 
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 print_debug "...unload OK";
	 
	 #-------------------------------------#
 	 # format unloaded data
 	 #-------------------------------------#
	 if (( ${ERROR} == ${rc} )); then
		format_turnover;
		rc=${?};
	 fi
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 print_debug "...format unloaded file OK";
	 
	 #-------------------------------------#
 	 # creating sql file and execute
 	 #-------------------------------------#
	 update_turnover;
	 
	 rc=${?};
	 
 	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 print_debug "...loading turnover OK";
	 
	 return ${OK};
 }
 #===========================================================#
 # formatting exported sap limit file
 #===========================================================#
 function format_sap_limit_file
 {
	 local _FUNCNAME="format_sap_limit_file";
	  
	 
	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # format comma to dot
 	 #-------------------------------------#
	 cat "${PATH_SAP_LIMIT_EXPORT}" | sed 's/,/./g' > "${PATH_SAP_LIMIT_EXPORT_FORMAT}"
	 
	 return ${OK};
 }
 #===========================================================#
 # formatting exported sap balance file
 #===========================================================#
 function format_sap_balance_file
 {
	 local _FUNCNAME="format_sap_balance_file";
	  
	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # format comma to dot
 	 #-------------------------------------#
	 #cat "${PATH_SAP_BALANCE_EXPORT}" | sed 's/,/./g' > "${PATH_SAP_BALANCE_EXPORT_FORMAT}" # does not work for miraculous reasons
	 tr ',' '.' < "${PATH_SAP_BALANCE_EXPORT}" > "${PATH_SAP_BALANCE_EXPORT_FORMAT}";
	 
	 return ${OK};
 }
 #===========================================================#
 # creating temporary and load files data to db
 #===========================================================#
 function load_file_into_temp_table
 {
	 local _FUNCNAME="create_temp_load_table";
	  
	 reset_error_indicators;
	 
	 typeset -r _sql_create_temp_statement="create temp table ${DB_DEBTLIMIT}:debtlimit_load ( partnerno int default 0 not null, limit decimal default 0.0 not null );";
	 
	 
	 echo ${_sql_create_temp_statement} >> ${PATH_SAP_EXPORT_SQL};
	 
	 awk -F\| '{
	     PARTNER = substr($1, 1, 9);
	     BUK = substr($1, 10, 4);
	     DK = substr($1, 14, 1);
	     WERT = substr($1, 23, 16);

	     if (BUK == "'"${FILE_SAP_SFX}"'"){
			 if (DK == "L"){
				if ( "'"${FALSE}"'" == "'"${nocreditlimit_flag}"'" ){			
					printf("insert into debtlimit_load (partnerno,limit) VALUES ("PARTNER","WERT");\n")
					printf("select first 1 nameapo, partnernr from kunde where partnernr = "PARTNER" and mastercstno = idfnr into temp t_kunde;\n")
					printf("update debtlimit set partnername = NVL((select nameapo from t_kunde where partnernr = "PARTNER"), \"\") where partnerno = "PARTNER" and partnername = \"\";\n")
					printf("drop table t_kunde;\n")
					printf("update debtlimit set sum_dayturnover = (select NVL(sum(wertlieferung),0) from kdauftrag where kundennr in (select kundennr from kunde where partnernr ="PARTNER	")) where partnerno="PARTNER";\n")
				}
			}
	     }
	}' ${PATH_SAP_LIMIT_EXPORT_FORMAT} >> ${PATH_SAP_EXPORT_SQL}

	rc=${?};
	
	return ${rc};
 }
 
 #===========================================================#
 # create load_cstinvoicedata
 #===========================================================#
 function load_cstinvoicedata
 {
	 local _FUNCNAME="load_cstinvoicedata";
	 
	 reset_error_indicators;
	 local _PATH_TURNOVER_FAK_EXPORT="";#${PATH_TURNOVER_FAK_EXPORT};
	 
	typeset -r _sql_create_t_cstinvoicedata="CREATE TEMP TABLE t_cstinvoicedata \
											( \
											   branchno smallint DEFAULT 0 NOT NULL, \
											   customerno integer DEFAULT 0 NOT NULL, \
											   doctype smallint DEFAULT 0 NOT NULL, \
											   docno varchar(10) NOT NULL, \
											   date integer DEFAULT 0 NOT NULL, \
											   amount decimal(11,0) DEFAULT 0.0000000000 NOT NULL, \
											   textkey varchar(2) NOT NULL \
											) \
											; \
											CREATE INDEX i_t_cstinvoicedata_2 ON t_cstinvoicedata \
											( \
											  branchno, \
											  customerno \
											) \
											;"
											
	typeset -r _sql_merge_cstinvoicedata="MERGE INTO cstinvoicedata d \
									  USING t_cstinvoicedata t \
									  ON d.branchno=t.branchno \
									  AND d.customerno=t.customerno \
									  AND d.doctype=t.doctype \
									  AND d.docno=t.docno \
									  AND d.date=t.date \
									  WHEN MATCHED THEN \
									  UPDATE SET d.amount = t.amount/100 \
									  WHEN NOT MATCHED THEN \
									  INSERT (d.branchno, d.customerno, d.doctype, d.docno, d.date, d.amount, d.textkey, d.invoiced) \
									  VALUES (t.branchno, t.customerno, t.doctype, t.docno, t.date, t.amount/100, t.textkey, 0);" 
	 
	echo ${_sql_create_t_cstinvoicedata}>>${PATH_TURNOVER_SQL}
 
	for i in ${ARRAY_TURNOVER_FAK[@]}
	do
	
		_PATH_TURNOVER_FAK_EXPORT="${DIR_SAP_EXPORT}/${i}"
		print_debug "....processing file ${_PATH_TURNOVER_FAK_EXPORT}";

		
		awk -F";"\| '{
			FS = ";"
			
			BRANCH = $1;
			CSTNO = $2;
			DOCTYPE = $3;
			DOCNO = $4;
			DDATE = $5;
			VAL = $6;
			TKEY = $7;
			
			printf("insert into t_cstinvoicedata values ("BRANCH", "CSTNO", "DOCTYPE", "DOCNO", "DDATE", "VAL", "TKEY" );\n")
			
		}'  ${_PATH_TURNOVER_FAK_EXPORT} >> ${PATH_TURNOVER_SQL}
		backup_file ${_PATH_TURNOVER_FAK_EXPORT};
	done
	 
	echo ${_sql_merge_cstinvoicedata}>>${PATH_TURNOVER_SQL}
	echo ${sql_update_debtlimit_mturnover}>>${PATH_TURNOVER_SQL}
	echo ${sql_update_debtlimit_cturnover}>>${PATH_TURNOVER_SQL}
	 
	 rc=${?};
	 
	 if (( ${ERROR} == ${rc} )); then
	 
  		 errno=${RET_CODE_UNLOAD_TURNOVER};
 		 errmsg="${_FUNCNAME}: Error when trying to create t_cstinvoicedata!";
		 
		 return ${ERROR};
 	 fi
	 
	 return ${OK};
 }
 
  
 #===========================================================#
 # merging temporary load table into the real debtlimit table
 #===========================================================#
 function merge_temp_load_into_debtlimit
 {
	 local _FUNCNAME="create_temp_load_table";
	 
	 reset_error_indicators;
	 
	 typeset -r _sql_merge_debtlimit="MERGE INTO debtlimit d \
									  USING debtlimit_load t \
									  ON d.partnerno=t.partnerno \
									  WHEN MATCHED THEN \
									  UPDATE SET d.limit = t.limit \
									  WHEN NOT MATCHED THEN \
									  INSERT (d.partnerno, d.limit) VALUES (t.partnerno, t.limit); ";
	 
	 echo ${_sql_merge_debtlimit} >> ${PATH_SAP_EXPORT_SQL};
 }
 #===========================================================#
 # creating sql file and execute to update sap limits data in debtlimit table
 #===========================================================#
 function update_sap_limit
 {
	 local _FUNCNAME="update_sap_limit";
	 
	 reset_error_indicators;	 
	 
	 #-------------------------------------#
 	 # check if formatted sap file is existing
 	 #-------------------------------------#
	 check_is_file_existing "${PATH_SAP_LIMIT_EXPORT_FORMAT}";
	 rc=${?};
	 
 	 if (( ${FALSE} == ${rc} )); then

  		 errno=${RET_CODE_SAP_LIMIT_FORMAT_FILE_NOT_EXISTING};
 		 errmsg="${_FUNCNAME}: Formatted SAP limit file does not exist!";
		 
		 return ${ERROR};
 	 fi
	 
	 #-------------------------------------#
 	 # loading files data into temp db table
 	 #-------------------------------------#
	 load_file_into_temp_table;
	 rc=${?};
	 
	 if [[ ${rc} -ne 0 ]];	then
  		 errno=${RET_CODE_SAP_SQL_FORMAT_FAILED};
 		 errmsg="${_FUNCNAME}: Loading file into temp table failed (formatting error)!";
		 
		 return ${ERROR};
 	 fi	 
	
	 #-------------------------------------#
	 # remove debtlimit entries if partnerno not in file
	 #-------------------------------------#
	 if (( ${TRUE} == ${noreset_flag} )); then
		print_debug "...Skipping reset of sap-limits because [${NORESET_OPTION}] was set";
	 else
		 if (( ${FALSE} == ${nocreditlimit_flag} )); then
			echo "delete from debtlimit where partnerno not in (select partnerno from debtlimit_load);" >> ${PATH_SAP_EXPORT_SQL};
		 fi
	 fi
	 
	 #-------------------------------------#
	 # merge temp table into original debtlimit
	 #-------------------------------------#
	 merge_temp_load_into_debtlimit;
	 
	 return ${OK};
 }
 
 
 #===========================================================#
 # creating sql file and execute to update sap balance data in debtlimit
 #===========================================================#
 function update_invoice_data
 {
	 local _FUNCNAME="update_invoice_data";
	  
	 
	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # check if formatted sap file is existing
 	 #-------------------------------------#
	 check_is_file_existing "${PATH_SAP_BALANCE_EXPORT_FORMAT}";
	 rc=${?};
	 
 	 if (( ${FALSE} == ${rc} )); then

  		 errno=${RET_CODE_SAP_BALANCE_FORMAT_FILE_NOT_EXISTING};
 		 errmsg="${_FUNCNAME}: Formatted SAP balance file does not exist!";
		 
		 return ${ERROR};
 	 fi
	 
	 if (( ${TRUE} == ${noreset_flag} )); then
		print_debug "...skipping reset of sap-balance because [${NORESET_OPTION}] was set";
	 else
		 if (( ${FALSE} == ${nodebitside_flag} )); then
			echo "update debtlimit set sum_debitside = 0;" >> ${PATH_FAK_EXPORT_SQL};
		 fi
		 if (( ${FALSE} == ${nocreditside_flag} )); then
			echo "update debtlimit set sum_creditside = 0;" >> ${PATH_FAK_EXPORT_SQL};
		 fi
		 
		 echo ${sql_update_sum_dayturnover} >> ${PATH_FAK_EXPORT_SQL};
	 fi
		 
	 awk -F\| '{
	 
		BEGIN {FS = ","}
		{print $1,$3}
	     BRANCH = substr($1, 1, 4);
		 CSTNO = substr($1, 5, 10);
		 DOCTYPE = substr($1, 15, 2);
		 DOCNO = substr($1, 17, 7);
		 DDATE = substr($1, 24, 5);
	     VAL = substr($1, 29, 17);
		 PDATE = substr($1, 46, 8);
		 DDATE = substr($1, 54, 8);
		 
		#if (DDATE == "00000000")
		#{
		#	DDATE = PDATE;
		#}
		
		if (BUK == "'"${FILE_SAP_SFX}"'"){
			if ( "'"${FALSE}"'" == "'"${nodebitside_flag}"'" ){
				printf("update debtlimit set sum_debitside = (sum_debitside + ("VAL")) where partnerno = "PARTNER";\n")
				printf("update cstinvoicedata set invoiced = 1 where customerno = "CST" and date <= "DDATE";\n")
			}
		}
	     if (BUK == "'"${FILE_SAP_SFX}"'"){
			 if (DK == "K"){
				if ( "'"${FALSE}"'" == "'"${nocreditside_flag}"'" ){
					printf("update debtlimit set sum_creditside = (sum_creditside  + ("WERT")) where partnerno = "PARTNER";\n")
					}
			}
			 if (DK == "D"){
				if ( "'"${FALSE}"'" == "'"${nodebitside_flag}"'" ){
					printf("update debtlimit set sum_debitside = (sum_debitside + ("WERT")) where partnerno = "PARTNER";\n")
				}
			}
	     }
	}' ${PATH_FAK_EXPORT_FORMAT} >> ${PATH_FAK_EXPORT_SQL}
	 
	 rc=${?};
	 
	#-------------------------------------#
 	# execute and backup sql file
 	#-------------------------------------#
	 if [[ ${rc} -ne 0 ]];	then
  		 errno=${RET_CODE_SAP_SQL_FORMAT_FAILED};
 		 errmsg="${_FUNCNAME}: Formatting of SAP balance sql file failed!";
		 
		 return ${ERROR};
 	 fi	 
	 return ${OK};
 }
 
 
 #===========================================================#
 # creating sql file and execute to update sap balance data in debtlimit
 #===========================================================#
 function update_sap_balance
 {
	 local _FUNCNAME="update_sap_balance";
	 local _BLANK_PARTNER="         ";
	 
	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # check if formatted sap file is existing
 	 #-------------------------------------#
	 check_is_file_existing "${PATH_SAP_BALANCE_EXPORT_FORMAT}";
	 rc=${?};
	 
 	 if (( ${FALSE} == ${rc} )); then

  		 errno=${RET_CODE_SAP_BALANCE_FORMAT_FILE_NOT_EXISTING};
 		 errmsg="${_FUNCNAME}: Formatted SAP balance file does not exist!";
		 
		 return ${ERROR};
 	 fi
	 
	 if (( ${TRUE} == ${noreset_flag} )); then
		print_debug "...skipping reset of sap-balance because [${NORESET_OPTION}] was set";
	 else
		 if (( ${FALSE} == ${nodebitside_flag} )); then
			echo "update debtlimit set sum_debitside = 0;" >> ${PATH_SAP_EXPORT_SQL};
		 fi
		 if (( ${FALSE} == ${nocreditside_flag} )); then
			echo "update debtlimit set sum_creditside = 0;" >> ${PATH_SAP_EXPORT_SQL};
		 fi
	 fi
		 
	 awk -F\| '{
	     BUK = substr($1, 1, 4);
		 DEBNR = substr($1, 5, 10);
		 BRANCH = substr($1, 15, 2);
		 CST = substr($1, 17, 7);
		 PARTNER = substr($1, 24, 9);
	     VAL = substr($1, 33, 17);
		 PDATE = substr($1, 50, 8);
		 DDATE = substr($1, 58, 8);
		 
		#if (DDATE == "00000000")
		#{
		#	DDATE = PDATE;
		#}
		
		if (BUK == "'"${FILE_SAP_SFX}"'"){
			if ( "'"${FALSE}"'" == "'"${nodebitside_flag}"'" ){
				if ( PARTNER == "'"${_BLANK_PARTNER}"'" ){
				}
				else{
					printf("update debtlimit set sum_debitside = (sum_debitside + ("VAL")) where partnerno = "PARTNER";\n")
				}
				printf("update cstinvoicedata set invoiced = 1 where customerno = "CST" and date <= "DDATE";\n")
			}
		}
	     if (BUK == "'"${FILE_SAP_SFX}"'"){
			 if (DK == "K"){
				if ( "'"${FALSE}"'" == "'"${nocreditside_flag}"'" ){
					printf("update debtlimit set sum_creditside = (sum_creditside  + ("WERT")) where partnerno = "PARTNER";\n")
					}
			}
			 if (DK == "D"){
				if ( "'"${FALSE}"'" == "'"${nodebitside_flag}"'" ){
					printf("update debtlimit set sum_debitside = (sum_debitside + ("WERT")) where partnerno = "PARTNER";\n")
				}
			}
	     }
	}' ${PATH_SAP_BALANCE_EXPORT_FORMAT} >> ${PATH_SAP_EXPORT_SQL}
												
	echo ${sql_update_debtlimit_mturnover}>>${PATH_SAP_EXPORT_SQL}
	echo ${sql_update_debtlimit_cturnover}>>${PATH_SAP_EXPORT_SQL}

	 
	 
	 rc=${?};
	 
	#-------------------------------------#
 	# execute and backup sql file
 	#-------------------------------------#
	 if [[ ${rc} -ne 0 ]];	then
  		 errno=${RET_CODE_SAP_SQL_FORMAT_FAILED};
 		 errmsg="${_FUNCNAME}: Formatting of SAP balance sql file failed!";
		 
		 return ${ERROR};
 	 fi	 
	 return ${OK};
 }
 #===========================================================#
 # getting credit limti from sap file and load to database
 #===========================================================#
 function load_sap_limit
 {
	 local _FUNCNAME="load_sap_limit";
	 
	 reset_error_indicators;
	 
	 if (( ${TRUE} == ${nocreditlimit_flag} )); then		 
		 print_debug "...skipping load of SAP limits because [${NOCREDITLIMIT_OPTION}] was set";
		 return ${OK};
 	 fi
 
	 print_debug "...format SAP limits";
  
	 #-------------------------------------#
 	 # format sap file
 	 #-------------------------------------#
	 format_sap_limit_file;
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 print_debug "...format SAP limit file OK";
	 
	 #-------------------------------------#
 	 # creating sql file and execute
 	 #-------------------------------------#
	 update_sap_limit;
	 
	 rc=${?};
	 
 	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 return ${OK};
 }
 #===========================================================#
 # getting sum_debit,sum_creditside from sap file and load to database
 #===========================================================#
 function load_sap_balance
 {
	 local _FUNCNAME="load_sap_balance";
	 
	 reset_error_indicators;
	 
	 if (( ${TRUE} == ${nodebitside_flag} && ${TRUE} == ${nocreditside_flag} )); then		 
		 print_debug "...skipping load of SAP balance because [${NOCREDITSIDE_OPTION}] and [${NODEBITSIDE_OPTION}] was set";
		 return ${OK};
 	 fi
 
	 print_debug "...format SAP balance";
  
	 #-------------------------------------#
 	 # format sap file
 	 #-------------------------------------#
	 format_sap_balance_file;
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 print_debug "...format SAP balance file OK";
	 
	 #-------------------------------------#
 	 # creating sql file and execute
 	 #-------------------------------------#
	 update_sap_balance;
	 
	 rc=${?};
	 
 	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 return ${OK};
 }
 #===========================================================#
 # getting sum_debit,sum_creditside,limit from sap files and load to database
 #===========================================================#
 function load_sap_files
 {
	 local _FUNCNAME="load_sap_files";
	 
	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # creating sql file for mass update
 	 #-------------------------------------#
	 cat /dev/null > ${PATH_SAP_EXPORT_SQL}; 
 
	 print_debug "\n>Loading SAP files to DB";
	 
	 #-------------------------------------#
 	 # load limits
 	 #-------------------------------------#
	 load_sap_limit
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
  
	 #-------------------------------------#
 	 # load balances
 	 #-------------------------------------#
	 load_sap_balance
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 #-------------------------------------#
 	 # execute sql file
 	 #-------------------------------------#
	
	 do_sql_file "${DB_DEBTLIMIT}" "${PATH_SAP_EXPORT_SQL}"
	 rc=${?};
	 if (( ${ERROR} == ${rc} )); then	
		 return ${ERROR};
	 fi
	
	 #-------------------------------------#
 	 # backing up
 	 #-------------------------------------#
	 backup_file "${PATH_SAP_BALANCE_EXPORT}";
	 backup_file "${PATH_SAP_BALANCE_EXPORT_FORMAT}";
	 backup_file "${PATH_SAP_LIMIT_EXPORT}";
	 backup_file "${PATH_SAP_LIMIT_EXPORT_FORMAT}";
	 backup_file "${PATH_SAP_EXPORT_SQL}";
	
	 print_debug "...loading SAP files OK";
	 
	 return ${OK};
 }
 #===========================================================#
 # checking if value has fallen below warning level,         #
 # then removing warning mail send entries,                  #
 # so that warning mails will be send again                  #
 #===========================================================#
 function perform_crema_check_and_deletion
 {
	 local _FUNCNAME="perform_crema_sqls";
	 
	 reset_error_indicators;
	 
	 if (( ${FALSE} == ${crema_flag} )); then
		print_debug "...skipping crema warningmail check and deletion because [${CREMA_OPTION}] was set";
	 else
		 #-------------------------------------#
		 # creating sql file for deletion      #
		 #-------------------------------------#
		 rm -f ${PATH_CREMA_SQL}
		 
		 _CREMA_SQL_="delete from debtmailsend where id in ( \
						SELECT dms.id \
						FROM debtmailsend dms \
						JOIN crematype ct ON dms.crematypeid = ct.id AND ct.type = 0 \
						JOIN debtlevelformail dlfm ON ct.typeid = dlfm.id \
						JOIN (SELECT ka.kdauftragnr, ka.idfnr FROM kdauftrag ka JOIN debtmailsend dms ON ka.kdauftragnr = dms.kdauftragnr  \
								UNION  \
							SELECT ka.kdauftragnr, ka.idfnr FROM akdauftrag ka JOIN debtmailsend dms ON ka.kdauftragnr = dms.kdauftragnr) ka ON dms.kdauftragnr = ka.kdauftragnr \
						JOIN kunde k ON ka.idfnr = k.idfnr \
						JOIN debtlimit dl ON k.partnernr = dl.partnerno \
						WHERE dlfm.leveltype = 1 AND (dl.sum_debitside + dl.sum_creditside + dl.sum_monturnover + dl.sum_dayturnover - dl.sum_returns - dl.sum_goodsreceipt) < (dl.limit / 100*dlfm.dlpercentage));\n"

		echo $_CREMA_SQL_ >> ${PATH_CREMA_SQL};
		
		
		_CREMA_SQL_="delete from debtmailsend where id in ( \
						SELECT dms.id \
						FROM debtmailsend dms \
						JOIN crematype ct ON dms.crematypeid = ct.id AND ct.type = 1 \
						JOIN amountformail afm ON ct.typeid = afm.id  \
						JOIN (SELECT ka.kdauftragnr, ka.idfnr FROM kdauftrag ka JOIN debtmailsend dms ON ka.kdauftragnr = dms.kdauftragnr  \
								UNION  \
							SELECT ka.kdauftragnr, ka.idfnr FROM akdauftrag ka JOIN debtmailsend dms ON ka.kdauftragnr = dms.kdauftragnr) ka ON dms.kdauftragnr = ka.kdauftragnr \
						JOIN kunde k ON ka.idfnr = k.idfnr \
						JOIN debtlimit dl ON k.partnernr = dl.partnerno \
						WHERE (dl.sum_debitside + dl.sum_creditside + dl.sum_monturnover + dl.sum_dayturnover - dl.sum_returns - dl.sum_goodsreceipt) < afm.thresholdamount);\n"

		echo $_CREMA_SQL_ >> ${PATH_CREMA_SQL};
		
		 #-------------------------------------#
		 # execute and backup sql file         #
		 #-------------------------------------#
		 do_sql_file "${DB_DEBTLIMIT}" "${PATH_CREMA_SQL}"
		 rc=${?};
		 if (( ${ERROR} == ${rc} )); then	
			 return ${ERROR}; 
		 fi
		 backup_file "${PATH_CREMA_SQL}";
 	 fi
	 return ${OK};
 }
 
 function create_sap_turnover
 {
	local _FUNCNAME="create_sap_turnover";
	reset_error_indicators;
	
	print_debug "Creating SAP turnover file...";
	
	do_sql "${sql_create_sap_turnover}" "${DB_DEBTLIMIT}";
	 rc=${?};
	 if (( ${ERROR} == ${rc} )); then	
		 return ${ERROR}; 
	 fi
	 backup_file "${PATH_FILE_EXPORT_SAP_TURNOVER}";
	 
	 print_debug "Creating SAP turnover file... done!";
	 
	 return ${OK};
 }
 
 
 #===========================================================#
 # cleaning content of temp files
 #===========================================================#
 function clean_temp_files
 {
	 local _FUNCNAME="clean_temp_files";
	 
	 reset_error_indicators;
	   
	 cat /dev/null > ${PATH_SAP_BALANCE_EXPORT_FORMAT}; 
	 cat /dev/null > ${PATH_SAP_EXPORT_SQL}; 
	 cat /dev/null > ${PATH_TURNOVER}; 
	 cat /dev/null > ${PATH_TURNOVER_FORMAT}; 
	 cat /dev/null > ${PATH_TURNOVER_SQL};
	 cat /dev/null > ${FILE_TURNOVER_FAK_SQL};
 }
 #===========================================================#
 # deleting old log files and temp files
 #===========================================================#
 function clean_up
 {
	 local _FUNCNAME="clean_up";
	 
	 reset_error_indicators;
 
	 print_debug "\n>Cleaning up";
  
	 #-------------------------------------#
 	 # cleaning content of temp files
 	 #-------------------------------------#
	 clean_temp_files;
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 print_debug "...cleaning temp files OK";
	 
	 return ${OK};
 }
 #======================================================#
 # function process_debtlimit
 #======================================================#
 function process_debtlimit
 {
 	 local _FUNCNAME="process_debtlimit";

 	 reset_error_indicators;
	 
	 #-------------------------------------#
 	 # Info
 	 #-------------------------------------#
	 print_info;
	 
	 #-------------------------------------#
 	 # Checking input parameters
 	 #-------------------------------------#	 
	 evaluate_input;
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi
	 
	 #-------------------------------------#
 	 # Get and load current turnover to database
 	 #-------------------------------------#
	 if (( ${FALSE} == ${noturnover_flag} )); then
		 load_turnover;
		 rc=${?};
		
		#if (( ${TRUE} == ${fak_tunrover} )); then
		#	load_cstinvoicedata;
		#	rc=${?};
		#fi
		
		 if (( ${ERROR} == ${rc} )); then		 
			 if (( ${FALSE} == ${CTRL_CONTINUE_ON_ERROR} )); then
				return ${ERROR};
			 else
				print_debug "...error <${errno}>, ${errmsg}"
				print_debug "...continue anyway!"
			 fi
		 fi
	 fi
	 
	 #-------------------------------------#
 	 # Get and load sap balance from file to database
 	 #-------------------------------------#
	 if (( ${FALSE} == ${nosap_flag} )); then
		 load_sap_files; # limit and balances
		 rc=${?};
		
		 if (( ${ERROR} == ${rc} )); then		 
			 if (( ${FALSE} == ${CTRL_CONTINUE_ON_ERROR} )); then
				return ${ERROR};
			 else
				print_debug "...error <${errno}>, ${errmsg}"
				print_debug "...continue anyway!"
			 fi
		 fi
	 fi
	 
	 #-------------------------------------#
 	 # remove crema warning mails, so that #
	 # they can be send again if the value #
	 # is below 80 percent.                #
 	 #-------------------------------------#
	 if (( ${TRUE} == ${crema_flag} )); then
		 perform_crema_check_and_deletion;
		 rc=${?};
		
		 if (( ${ERROR} == ${rc} )); then		 
			 if (( ${FALSE} == ${CTRL_CONTINUE_ON_ERROR} )); then
				return ${ERROR};
			 else
				print_debug "...error <${errno}>, ${errmsg}"
				print_debug "...continue anyway!"
			 fi
		 fi
	 fi
	 
	 if (( ${TRUE} == ${CREATE_FILE_EXPORT_SAP_TURNMOVER} )); then
		create_sap_turnover;
		rc=${?};
		
		 if (( ${ERROR} == ${rc} )); then		 
			 if (( ${FALSE} == ${CTRL_CONTINUE_ON_ERROR} )); then
				return ${ERROR};
			 else
				print_debug "...error <${errno}>, ${errmsg}"
				print_debug "...continue anyway!"
			 fi
		 fi
	 fi
	 
	 
	 #-------------------------------------#
 	 # delete old logs and temporary files
 	 #-------------------------------------#
	 clean_up;
	 rc=${?};
	
	 if (( ${ERROR} == ${rc} )); then		 
		 return ${ERROR};
 	 fi

 	 return ${OK};
 }
 ###############################################################################################
 # INDIVIDUAL FUNCTIONS - END
 ###############################################################################################

 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/debtlimit.option
 
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

 	 current_table="debtlimit";
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 echo " ${cnt_step}. Step: BEGIN processing table \"${current_table}\"." | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 process_debtlimit #parameter
 	 rc=${?};
 	 echo "\n>Return `transform_rc ${rc}`\n...${errmsg}\n" | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
 	 echo " ${cnt_step}. Step: END processing table \"${current_table}\" (Return-Code:<${rc}>)." | tee -a ${LOG_RESOURCE}
 	 echo "#-----------------------------------------------------------------#" | tee -a ${LOG_RESOURCE}
	 
	 if (( ${ERROR} == ${rc} )); then
		 if [[ ${errno} -ne ${OK} ]];	then
			rc=${errno} #concrete error number if available
		 fi
 		 exit ${rc};
 	 fi

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
