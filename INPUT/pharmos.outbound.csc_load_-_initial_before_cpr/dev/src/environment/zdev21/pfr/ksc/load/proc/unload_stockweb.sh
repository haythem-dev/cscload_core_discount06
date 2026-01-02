#!/usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            j.li                                                                                      
 #Creation-Date:     15.01.2013                                                                                
 #Creation-Time:     18:05                                                                                     
 #Creator:           procgen.sh - Version: 01.00.01.00                                                         
 #Creation-Type:     BATCH_PROCEDURE                                                                           
 #Purpose:           Starts, stops and status the exemplar binary unload_stockweb for presentation only.       
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
 ################################ constants #####################################
 VERSION=1.0.4.0
 
 ###############################################################################################
 # NEW VERSIONS
 # VERSION=1.0.0.0
 # Name of the exported file -> stockweb.csv
 # exported filename, e.g.: stockweb.4348.20130116.103000.csv
 # VERSION=1.0.1.0
 # Name of the exported file -> stockweb.csv
 # Old file stockweb.csv with time stamp will be saved in achiv-folder
 # VERSION=1.0.2.0
 # -db zpos2pfr
 # zpps2pfr will be derivated from -db
 # left outer join carticlecodes
 # left outer join ean
 # VERSION=1.0.3.0
 # temptable for external table ean on db2_zpps2_tcp
 # artikelzentral.businesstypeno in where-clause
 # VERSION=1.0.4.0
 # Handling of reserved articles is now correct
 ###############################################################################################
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
 #readonly BINARY=unload_stockweb.bin
 #process="${BIN_PATH}/${BINARY}"
 
 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 db="";
 #generated
 #typeset -i branchlist=0;
 #manual
 typeset -i length_arr_branchlist=0;
 set -A arr_branchlist;
 set -A arr_code_types;
 #--- end declaration procedure variables ---#
 start="";
 stop="";
 status="";
 typeset -i rc=0;

 typeset -i errno=0;
 errmsg="";
 INFORMIXDIR=${INFORMIXDIR};
 
 typeset -r PREFIX_ARCHIVE="archive";
 
 typeset -r PREFIX_FILENAME="stockweb";
 typeset -r SUFFIX_FILENAME="csv";
 typeset -r NOW_DATE=`date +%Y%m%d`;
 typeset -r NOW_TIME_SECOND=`date +%H%M%S`;
 # typeset -r NOW_TIME=`echo $NOW_TIME_SECOND | cut -c1-4`;
 typeset -r TIMESTAMP_FILENAME="${NOW_DATE}.""${NOW_TIME_SECOND}";
 # typeset -r FILE="${PREFIX_FILENAME}.""${TIMESTAMP_FILENAME}"".${SUFFIX_FILENAME}";
 typeset -r FILE_NAME="${PREFIX_FILENAME}.""${SUFFIX_FILENAME}";
 typeset -r FILE="${DATA_PATH}/${PREFIX_FILENAME}.""${SUFFIX_FILENAME}";
 
 #--------------------------------------------------------------------#
 # L I T E R A L S --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED <--
 #--------------------------------------------------------------------#
 readonly STARTMSG="START";
 readonly STOPMSG="STOP";
 readonly START_OPTION="-start";
 readonly STOP_OPTION="-stop";
 readonly STATUS_OPTION="-status";
 readonly DB_OPTION="-db";
 readonly BRANCHLIST_OPTION="-branchlist";

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
 	 printf "%-30s%-90s\n" "\$STARTMSG:k>$STARTMSG<"
 	 printf "%-30s%-90s\n" "\$STOPMSG:" ">$STOPMSG<"
 	 printf "%-30s%-90s\n" "\$START_OPTION:" ">$START_OPTION<"
 	 printf "%-30s%-90s\n" "\$STOP_OPTION:" ">$STOP_OPTION<"
 	 printf "%-30s%-90s\n" "\$STATUS_OPTION:" ">$STATUS_OPTION<"
	 printf "%-30s%-90s\n" "\$DB_OPTION:" ">$DB_OPTION<"
	 printf "%-30s%-90s\n" "\$BRANCHLIST_OPTION:" ">$BRANCHLIST_OPTION<"

 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
	 printf "%-30s%-90s\n" "\$db:" ">$db<"
	 #generated
	 #printf "%-30s%-90s\n" "\$branchlist:" ">$branchlist<"
	 #manual
	 typeset -i _index=0
	 while (( ${_index} < ${length_arr_branchlist} ))
	 do
		 printf "%-30s%-90s\n" "\$branch in the branchlist:" ">${arr_branchlist[_index]}<";
		 _index=${_index}+1;
	 done
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

 		 if [[ "$1" == "$BRANCHLIST_OPTION" ]]; then
 			 shift;
			 #manual
			 typeset -i _index=0;
			 while(( $# > 0 ))
			 do
				 arr_branchlist[_index]=$1;
				 _index=${_index}+1;
				 shift;
			 done
			 #generated
			 # if (( $# > 0 )) ; then
 				 # branchlist=$1;
 				 # shift;
 				 # continue;
 			 # else 
 				 # break;
 			 # fi
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
 

 	 #generated
	 # if [[ "${branchlist}" == "" ]] || (( 1 != `check_numeric_parameter "${BRANCHLIST_OPTION}" "${branchlist}"` )) || [[ "${branchlist}" == "0" ]]; then
 		 # printStartStop "${STARTMSG}"
 		 # rc=12;
 		 # echo "${PROCNAME}: Parameter value missed or invalid value \${branchlist}: >${branchlist}<!" | tee -a ${LOG_RESOURCE}
 		 # echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 # printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 # exit ${rc};
 	 # fi
	 #manual
	 length_arr_branchlist=${#arr_branchlist[*]};
	 if [[ "${length_arr_branchlist}" == "0" ]]; then
 		 printStartStop "${STARTMSG}"
 		 rc=12;
 		 echo "${PROCNAME}: Parameter value missed or invalid value \${branchlist}!" | tee -a ${LOG_RESOURCE}
 		 echo ${USAGE} | tee -a ${LOG_RESOURCE}
 		 printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
	 _index=0;
	 while (( ${_index} < ${length_arr_branchlist} ))
	 do
		 if [[ "${arr_branchlist[_index]}" == "" ]] || (( 1 != `check_numeric_parameter "${BRANCHLIST_OPTION}" "${arr_branchlist[_index]}"` )) || [[ "${arr_branchlist[_index]}" == "0" ]]; then
			printStartStop "${STARTMSG}"
			rc=12;
			echo "${PROCNAME}: Parameter value missed or invalid value \${branchlist}: >${arr_branchlist[_index]}<!" | tee -a ${LOG_RESOURCE}
			echo ${USAGE} | tee -a ${LOG_RESOURCE}
			printStartStop "${STOPMSG}" "with Exit-Code: <${rc}>"
			exit ${rc};
		 fi
		 _index=${_index}+1;
	 done
	 
 

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

 	 if [[ "${_OPTION}" == "${BRANCHLIST_OPTION}" ]]; then
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
 	 typeset -ir _rc=/software/home/j.li/unload_stockweb/fr/ksc/load;
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
 	 local _result_file=${PROCNAME}.${$}.res
 	 local _error_file=${PROCNAME}.${$}.err
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
 	 else
 		 errno=${ERROR};
 		 errmsg="${_FUNCNAME}: Error executing following SQL-String: <${_sql}>";
 		 errmsg=${errmsg}"with error text <`cat ${_error_file}`>.";
 	 fi

 	 rm ${_result_file}
 	 rm ${_error_file}

 	 return ;
 }
 #======================================================#
 # function process_unload_stockweb
 #======================================================#
 function process_unload_stockweb
 {
 	 local _FUNCNAME="process_unload_stockweb";
	 # typeset -r _tbl="${1}";
 	 typeset -r _db=${1};
 	 typeset -i _rc=${FALSE};

 	 reset_error_indicators;

 	 #-------------------------------------#
 	 # SQL-String
 	 #-------------------------------------#
	 #manual
	 typeset -i _index=0;
	 typeset _joincondition_filialnr="( 1!=1";
	 typeset _joincondition_branchno="( 1!=1";
	 typeset -r _conditionsegm_filialnr=" OR al.filialnr=";
	 typeset -r _conditionsegm_branchno=" OR cc.branchno=";
	 typeset _identifier_file="";
	 # typeset -A arr_code_types;
	 while (( ${_index} < ${length_arr_branchlist} ))
	 do
		 _joincondition_filialnr="${_joincondition_filialnr}""${_conditionsegm_filialnr}""${arr_branchlist[_index]}";
		 _joincondition_branchno="${_joincondition_branchno}""${_conditionsegm_branchno}""${arr_branchlist[_index]}";
		 _identifier_file="${_identifier_file}""${arr_branchlist[_index]}";
		 _index=${_index}+1;
	 done
	 _joincondition_filialnr="${_joincondition_filialnr}"" )";
	 _joincondition_branchno="${_joincondition_branchno}"" )";
	 ####################################################
	 # 1. step: DB Environment configuration
	 ####################################################
	 f_db_dest_env ${_db};
	 
	 # FILE="${DATA_PATH}/${PREFIX_FILENAME}.""${_identifier_file}"".${TIMESTAMP_FILENAME}"".${SUFFIX_FILENAME}";
 	 ####################################################
	 # 2. step: sql assembling
	 ####################################################
	 local _sql="set isolation to dirty read; 
				select artikel_nr, ean_nr from ${DB_PURCHASE_PREWHOLE}:ean into temp temptable;
				unload to '${FILE}' delimiter ';'
				SELECT 
					LPAD(cast(NVL(ac.article_code, ea.ean_nr) as int8), 25, ' '), 
					LPAD(az.artikel_nr, 11, ' '), 
					RPAD(az.artikel_name, 30, ' '), 
					LPAD(al.bestand, 11, ' '), 
					RPAD(al.codeblocage, 1, ' '), 
					RPAD(az.warengruppeeigen, 5, ' '), 
					LPAD(tr.salestaxrate, 7, ' '), 
					LPAD(ap.preisekapo, 11, ' '), 
					RPAD(cc.seracode, 20, ' ')
				FROM 
					artikelzentral az
				JOIN 
					artikellokal al ON al.artikel_nr=az.artikel_nr AND ${_joincondition_filialnr}
				LEFT OUTER JOIN 
					articlecodes ac ON ac.articleno=az.artikel_nr AND ac.code_type IN (8, 9) AND ac.preferred_flag=1
				LEFT OUTER JOIN
					temptable ea ON ea.artikel_nr=az.artikel_nr
				JOIN 
					artikelpreis ap ON ap.artikel_nr=az.artikel_nr
				JOIN 
					taxrates tr ON tr.taxlevel=az.taxlevel
				LEFT OUTER JOIN 
					countrycodes cc ON cc.infocode=al.codeblocage AND ${_joincondition_branchno} 
				WHERE
					az.businesstypeno in (2,3,4);
				drop table temptable; ";
	 echo "SQL-STATEMENT:	${_sql}" >> ${LOG_RESOURCE_IN_DETAIL};
 	 # _sql=""; # example of formatting sql string: `printf "SELECT count(*) FROM %s:%s;" "${_db}" "${_tbl}"`;
 	 ####################################################
	 # 3. step: Run
	 ####################################################
	 do_sql "${_sql}" "${_db}";
 	 _rc=0;
 	 return ;
 }
 ###############################################################################################
 # INDIVIDUAL FUNCTIONS - END
 ###############################################################################################
 #======================================================#
 # function config_environment
 #======================================================#
 function config_environment
 {
 	local _FUNCNAME="config_environment";
 	export LOG_RESOURCE_IN_DETAIL=${LOG_PATH}/$(basename $0).${NOW_DATE}.log;
	if [[ ! -f "${LOG_RESOURCE}" ]]; then
 		touch ${LOG_RESOURCE};
 	fi
 	if [[ ! -f "${LOG_RESOURCE_IN_DETAIL}" ]]; then
 		touch ${LOG_RESOURCE_IN_DETAIL};
 	fi
	echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" >> ${LOG_RESOURCE_IN_DETAIL};
 	echo "Time: ${NOW_TIME_SECOND}" >> ${LOG_RESOURCE_IN_DETAIL};
	echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" >> ${LOG_RESOURCE_IN_DETAIL};
 } # config_environment
 #======================================================#
 # function archive_env_op
 #======================================================#
 function archive_env_op
 {
 	local _FUNCNAME="archive_env_op";
 	export ARCHIVE_PATH=${DATA_PATH}/"${PREFIX_ARCHIVE}_""${PREFIX_FILENAME}";
	# export ARCHIVE_FILE=${ARCHIVE_PATH}/${PREFIX_ARCHIVE};
	# export ARCHIVE_FILE_WITH_TIMESTAMP=${ARCHIVE_PATH}/"${PREFIX_ARCHIVE}_"$(basename $0);
	if [[ ! -d "${ARCHIVE_PATH}" ]]; then
 		mkdir ${ARCHIVE_PATH};
 	fi
 	if [[ -f "${FILE}" ]]; then
 		cp ${FILE} ${ARCHIVE_PATH};
		mv ${ARCHIVE_PATH}/${FILE_NAME} "${ARCHIVE_PATH}/${PREFIX_FILENAME}.""${TIMESTAMP_FILENAME}"".${SUFFIX_FILENAME}";
		rm ${FILE};
 	fi
	echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" >> ${LOG_RESOURCE_IN_DETAIL};
 	echo "The old file will be achived in :" >> ${LOG_RESOURCE_IN_DETAIL};
	echo "${ARCHIVE_PATH}/${PREFIX_FILENAME}.""${TIMESTAMP_FILENAME}"".${SUFFIX_FILENAME}" >> ${LOG_RESOURCE_IN_DETAIL};
	echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" >> ${LOG_RESOURCE_IN_DETAIL};
 } # archive_env_op
#======================================================#
# function f_db_dest_env
#======================================================#
function f_db_dest_env 
{
	local local _FUNCNAME="f_db_dest_env";
	export DB_PURCHASE_PREWHOLE="ifr21pre@zdev21_tcp";
	#  configuration of bulgarian local
	echo "" >>${LOG_RESOURCE_IN_DETAIL}
	echo "***  ${_FUNCNAME} (DB=$_db)" >>${LOG_RESOURCE_IN_DETAIL}
	echo "" >>${LOG_RESOURCE_IN_DETAIL}
	
} # f_db_dest_env
#======================================================#
# function send_errormessage
#======================================================#
function send_errormessage
{
	local _FUNCNAME="send_errormessage";
	
	set -A email_addresses; 
	 email_addresses[0]="a.egerer@phoenixgroup.eu"; 
	# email_addresses[1]="s.heinlein@phoenixgroup.eu";
	# email_addresses[2]="r.imschweiler@phoenixgroup.eu";
	# email_addresses[3]="y.bouma@phoenixgroup.eu";
	# email_addresses[4]="zbw@phoenixgroup.eu";
	# email_addresses[5]="cct@phoenixgroup.eu";
	# email_addresses[6]="AVOperations@phoenixgroup.eu";
	
	typeset -i idx=0
	typeset -ri cnt_addresses=${#email_addresses[*]}
	while(( idx < cnt_addresses ))
	do
		cat ${LOG_RESOURCE_IN_DETAIL} | mailx -s "Error: unload_stockweb @ `hostname`" "${email_addresses[idx]}"
		idx=idx+1
	done
}
 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/unload_stockweb.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";
 print_msg "$STARTMSG" "$*"
 # self-defined DATA_PATH which does not exist in bi_global.vars
 # export readonly DATA_PATH=./../data
 config_environment;
 echo "$0 $*" >>${LOG_RESOURCE_IN_DETAIL}
 echo "$(basename $0) Version: $VERSION" >>${LOG_RESOURCE_IN_DETAIL}
 archive_env_op;
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
 	 #set_informixdir;
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
 	 #generated
	 # process_unload_stockweb #parameters
 	 #manual
	 process_unload_stockweb ${db}
	 rc=${?};
 	 if (( ${ERROR} == ${rc} )); then
 		 send_errormessage;
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
