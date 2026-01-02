#! /usr/bin/ksh
 . /software/etc/profile_prz #This line has to be removed and the next one has to be activated if adopted to production environment 
# . /software/zpps2/etc/profile_prz #Replace the angle bracket by the host name migrated to 
 

 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author: devuser 
 #Creation-Date:	15.07.2008
 #Creation-Time:	10:50
 #Purpose:			starts, stops and status the exemplar binary provide_dezap for presentation only
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
 . $(dirname $0)/../vars/cdm_pw_global.vars

 #--------------------------------------------------------------------#
 # INDIVIDUAL VARIABLES
 #--------------------------------------------------------------------#
 #--- begin declaration procedure variables ---#
 branchno=0;
 from="";
 to="";
 #--- end declaration procedure variables ---#
 start="";
 stop="";
 status="";
 fromfile="";
 todir="";
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
 readonly BRANCHNO_OPTION="-branchno";
 readonly FROM_OPTION="-from";
 readonly TO_OPTION="-to";

 ###############################################################################################
 # F U N C T I O N S
 ###############################################################################################
 #====================================#
 # PRINT START-/ STOP-MELDUNG
 #====================================#
 function printStartStop
 {
 	 if [[ "$2" == "" ]]; then set /software/wss/de/cdm 15.07.08 10:50:43; fi
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
	 echo "\$BRANCHNO_OPTION:			>$BRANCHNO_OPTION<"
	 echo "\$FROM_OPTION:			>$FROM_OPTION<"
	 echo "\$TO_OPTION:			>$TO_OPTION<"

 	 echo "\$para:							>$para<"
 	 echo "\$process:						>$process<"
 	 echo "\$start:							>$start<"
 	 echo "\$stop:							>$stop<"
 	 echo "\$status:						>$status<"
	 echo "\$branchno:			>$branchno<"
	 echo "\$from:			>$from<"
	 echo "\$to:			>$to<"
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
 
 		 #read in parameters
 		 if [[ "$1" == "$BRANCHNO_OPTION" ]]; then
 			 shift
 			 if (( $# > 0 )) ; then
 				 branchno=$1;
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$FROM_OPTION" ]]; then
 			 shift
 			 if (( $# > 0 )) ; then
 				 from=$1;
                                 fromfile=$(basename $from);
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

 		 if [[ "$1" == "$TO_OPTION" ]]; then
 			 shift
 			 if (( $# > 0 )) ; then
 				 to=$1;
 				 todir=$(dirname $to);
 				 shift;
 				 continue;
 			 else 
 				 break;
 			 fi
 		 fi

		break;
 	 done

 	 # evaluation of options
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

	 # evaluation of parameters
 	 if [[ "$branchno" == "" ]] || (( 1 != `check_numeric_parameter "$branchno"` )) || [[ "$branchno" == "0" ]]; then
 		 printStartStop "$STARTMSG"
 		 rc=12;
 		 echo "$PROCNAME: Parameter value missed or invalid value \$branchno: >$branchno<!" | tee -a $LOG_RESOURCE
 		 echo ${USAGE} | tee -a $LOG_RESOURCE
 		 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 

 	 if [[ "$from" == "" ]] || (( 1 != `check_string_parameter "$from"` )); then
 		 printStartStop "$STARTMSG"
 		 rc=12;
 		 echo "$PROCNAME: Parameter value missed or invalid value \$from: >$from<!" | tee -a $LOG_RESOURCE
 		 echo ${USAGE} | tee -a $LOG_RESOURCE
 		 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
 		 exit ${rc};
 	 fi
 

 	 if [[ "$to" == "" ]] || (( 1 != `check_string_parameter "$to"` )); then
 		 printStartStop "$STARTMSG"
 		 rc=12;
 		 echo "$PROCNAME: Parameter value missed or invalid value \$to: >$to<!" | tee -a $LOG_RESOURCE
 		 echo ${USAGE} | tee -a $LOG_RESOURCE
 		 printStartStop "$STOPMSG" "with Exit-Code: <${rc}>"
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
	 local readonly _PARA="$BRANCHNO_OPTION $branchno $FROM_OPTION $from $TO_OPTION $to";
	 process="$process ${_PARA}";
 }
 
 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/provide_dezap.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";
 #check_existence_of_binary;
 assembling_process;
 print_msg "$STARTMSG" "$*"
 
 #======================================================#
 # CALLS METHOD START-PROCESS
 #======================================================#
 if [[ "$start" == "YES" ]]; then
 	 #msg=`start_process "${process}" `
         DATUM=$(date '+%Y%m%d')
 	 msg=$(set -x
               cp -p ${from} ${todir}
               rc=$?
               if [[ $rc -ne 0 ]]
               then
                  echo "Kopieren von ${from} -> ${to} mit RC $rc abgebrochen"
                  exit $rc
               fi
               OHNEDAT=${fromfile%*.*}
               cd $todir
               rc=$?
               if [[ ( $rc -ne 0 ) || ( ! -d ${todir} ) ]]
               then
                  echo "Verzweigen auf Verzeichnis $todir mit RC $rc abgebrochen"
                  exit $rc
               fi
               if [[ ! -f $fromfile ]]
               then
                  echo "Datei $fromfile nicht vorhanden, bitte ueberpruefen"
                  exit 97
               fi
               #CONVDATAPATH=/transfer/tools
               #export CONVDATAPATH
               /transfer/tools/convdata2 /transfer/schema/DEZAP.ini ${todir}/$fromfile ${todir}/${fromfile}.out
               rc=$?
               if [[ $rc -ne 0 ]]
               then
                  echo "convdata2 von $fromfile fehlgeschlagen (RC $rc)"
                  exit $rc
               fi
               mv ${fromfile}.out $to
               rc=$?
               if [[ $rc -ne 0 ]]
               then
                  echo "Probleme $rc beim Erstellen von ${to}, bitte pruefen"
                  exit $rc
               fi
               cat $to | wc -l | read ANZ
               echo "---------------------------------------"
               echo "$ANZ Saetze in dezap von Fil. ${branchno}"
               echo "---------------------------------------"

               # Dateien ins Archiv abstellen
               mv $fromfile ${fromfile}.${DATUM}
               compress -f ${fromfile}.${DATUM}
               chmod 777 ${fromfile}.${DATUM}*
               mkdir archive/$OHNEDAT 2> /dev/null
               mv ${fromfile}.${DATUM}.Z archive/$OHNEDAT
               #mv ${from} ${from}.${DATUM}
               rm ${from}
               find archive -name '${fromfile}*' -mtime +180 -exec rm {} \;
               find $HOME/${fromfile}* -name '*' -mtime +5 -exec rm {} \;
               exit 0)
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
