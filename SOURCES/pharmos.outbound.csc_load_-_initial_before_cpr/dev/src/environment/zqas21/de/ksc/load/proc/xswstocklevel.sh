#! /usr/bin/ksh
 
 ###############################################################################################
 # HEADER-DATA 
 ###############################################################################################
 #Author:            devuser                                                                                   
 #Creation-Date:     03.04.2009                                                                                
 #Creation-Time:     07:01                                                                                     
 #Purpose:           Starts, stops and status the exemplar binary swstocklevel for presentation only.          
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
 readonly BINARY=swstocklevel.bin
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

 	 printf "%-30s%-90s\n" "\$process:" ">$process<"
 	 printf "%-30s%-90s\n" "\$start:" ">$start<"
 	 printf "%-30s%-90s\n" "\$stop:" ">$stop<"
 	 printf "%-30s%-90s\n" "\$status:" ">$status<"
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

 	 # DO SOME checks here - e.g. database server validity: [a-z]*([a-z]|[1-9])@+([a-z]|[1-9]|[_])_@(shm|tcp)

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
 	 if (( ${#_parameters} > 0 )); then
 		 _parameters="${_parameters%?}"
 		 _parameters="${_parameters#?}"
 	 fi

 	 if (( ${#_parameters} > 0 )); then
 		 process="$process ${_parameters}"
 	 fi

 }
 
 ###############################################################################################
 # H E L P & V E R S I O N 
 ###############################################################################################
 . $(dirname $0)/swstocklevel.option
 
 ###############################################################################################
 # S H E L L - L O G I C 
 ###############################################################################################
 check_parameters "$@";
 eval_parameters "$@";
 #check_existence_of_binary ${process};
 assembling_process;
 print_msg "$STARTMSG" "$*"
 
 #======================================================#
 # CALLS METHOD START-PROCESS
 #======================================================#
 if [[ "$start" == "YES" ]]; then

	# set informix dir
        HOSTNAME=$(hostname)

        # walk through all request files
		for i in `ls ${DATA_PATH}/input/xstocklevel-*-*.info`; do

		echo "----- process request file ${i} -----" >> ${LOG_RESOURCE}

                # determine branch number and customer number
			BRANCHNO=`echo $i | cut -d- -f2`
			CUSTOMER=`echo $i | cut -d- -f3 | sed 's/.info//g'`
			echo Filiale: ${BRANCHNO} Kunde: ${CUSTOMER} >> ${LOG_RESOURCE}

		# determine file with articles			
			FILESIZE=`ls -l ${i} | nawk '{ print $5 }'`
			ARTICLEFILE=${DATA_PATH}/input/stocklevel-${BRANCHNO}.allpzn
                	if (( ${FILESIZE} > 0 )); then
				ARTICLEFILE=${i}
                	fi
			echo Artikeldatei: ${ARTICLEFILE} >> ${LOG_RESOURCE}

		# determine ksc database
			DB=`get_ksc_db ${BRANCHNO}`; rc=$?
			if (( 0 != ${rc} )); then
				echo KSC Datenbank: ${DB}
				print_msg "$STOPMSG" "$*" "<$rc>"
				continue
			fi
			echo KSC Datenbank: ${DB} >> ${LOG_RESOURCE}

                # delete sql workfile  
    			SQLFILE=${DATA_PATH}/input/swstocklevel.sql
			rm ${SQLFILE} 2>/dev/null

		# determine interbranchtransfer branches for customer
			set -A arrIBTBranches
			if [[ -f ${DATA_PATH}/input/swstocklevel_ibt.sql ]]; then
				rm ${DATA_PATH}/input/swstocklevel_ibt.sql 
			fi				
			
			echo "UNLOAD TO '${DATA_PATH}/input/swstocklevel_ibt.info' delimiter ';' " >> ${DATA_PATH}/input/swstocklevel_ibt.sql
			echo "SELECT DISTINCT verbundfilialnr FROM alternativfiliale WHERE filialnr=${BRANCHNO};" >> ${DATA_PATH}/input/swstocklevel_ibt.sql
			dbaccess ${DB} ${DATA_PATH}/input/swstocklevel_ibt.sql 1>>${LOG_RESOURCE} 2>>${LOG_RESOURCE_ERROR}
			sed 's/;/ /g' ${DATA_PATH}/input/swstocklevel_ibt.info >> ${DATA_PATH}/input/swstocklevel_ibt.info.tmp
			
			while read IBT 
			do
				ISVALID=`is_branchno_valid ${IBT}`; 
				rc=$?
                if [[ "TRUE" == ${ISVALID} ]]; then
					arrIBTBranches[${#arrIBTBranches[*]}+1]=${IBT}
				fi
			done < ${DATA_PATH}/input/swstocklevel_ibt.info.tmp
			
			rm ${DATA_PATH}/input/swstocklevel_ibt.sql 2>/dev/null
			rm ${DATA_PATH}/input/swstocklevel_ibt.info 2>/dev/null
			rm ${DATA_PATH}/input/swstocklevel_ibt.info.tmp 2>/dev/null
			
			echo "Determined the following interbranchtransfer branches for this customer:" >> ${LOG_RESOURCE}
			for IBTBranch in ${arrIBTBranches[*]}; do
				echo " ${IBTBranch}" >> ${LOG_RESOURCE}
			done

		# build up sql query
			echo "SET ISOLATION DIRTY READ; CREATE TEMP TABLE tarticle (artikel_nr int not null); " >> ${SQLFILE}
			echo "LOAD FROM '${ARTICLEFILE}' INSERT INTO tarticle; " >> ${SQLFILE}
			echo >> ${SQLFILE}

			echo "SELECT a.artikel_nr, bestand, verbundartikel FROM vartikellokal a, tarticle WHERE" >> ${SQLFILE}
			echo " a.artikel_nr = tarticle.artikel_nr AND filialnr = ${BRANCHNO} INTO TEMP t${BRANCHNO} WITH NO LOG;" >> ${SQLFILE}
			echo >> ${SQLFILE}

			for IBTBranch in ${arrIBTBranches[*]}; do
				echo "SELECT a.artikel_nr, bestand, verbundartikel FROM vartikellokal a, tarticle WHERE" >> ${SQLFILE}
				echo " a.artikel_nr = tarticle.artikel_nr AND filialnr = ${IBTBranch} INTO TEMP t${IBTBranch} WITH NO LOG;" >> ${SQLFILE}
                                echo "UPDATE t${IBTBranch} SET bestand=0 WHERE verbundartikel=0;" >> ${SQLFILE}
				echo >> ${SQLFILE}
			done

			echo "SELECT * FROM t${BRANCHNO} INTO TEMP tvz${BRANCHNO}quotedstock WITH NO LOG;" >> ${SQLFILE}
			echo "SELECT articleno, quota-kumqty AS quota FROM varticlequota, tarticle WHERE " >> ${SQLFILE}
			echo " customerno=${CUSTOMER} AND branchno=${BRANCHNO} AND articleno=artikel_nr " >> ${SQLFILE}
  			echo " INTO TEMP tquota WITH NO LOG;" >> ${SQLFILE}
			echo "UPDATE tvz${BRANCHNO}quotedstock SET bestand=(SELECT quota FROM tquota WHERE " >> ${SQLFILE}
			echo " tvz${BRANCHNO}quotedstock.artikel_nr = tquota.articleno) WHERE " >> ${SQLFILE}
			echo " artikel_nr IN (SELECT articleno FROM tquota) AND bestand > " >> ${SQLFILE}
			echo " (SELECT quota FROM tquota WHERE tvz${BRANCHNO}quotedstock.artikel_nr = tquota.articleno); " >> ${SQLFILE}
			echo "DROP TABLE tquota;" >> ${SQLFILE}
			echo >> ${SQLFILE}

			for IBTBranch in ${arrIBTBranches[*]}; do
				echo "SELECT * FROM t${IBTBranch} INTO TEMP tvz${IBTBranch}quotedstock WITH NO LOG;" >> ${SQLFILE}
				echo "SELECT articleno, quota-kumqty AS quota FROM varticlequota, tarticle WHERE " >> ${SQLFILE}
				echo " customerno=${CUSTOMER} AND branchno=${IBTBranch} AND articleno=artikel_nr " >> ${SQLFILE}
  				echo " INTO TEMP tquota WITH NO LOG;" >> ${SQLFILE}
				echo "UPDATE tvz${IBTBranch}quotedstock SET bestand=(SELECT quota FROM tquota WHERE " >> ${SQLFILE}
				echo " tvz${IBTBranch}quotedstock.artikel_nr = tquota.articleno) WHERE " >> ${SQLFILE}
				echo " artikel_nr IN (SELECT articleno FROM tquota) AND bestand > " >> ${SQLFILE}
				echo " (SELECT quota FROM tquota WHERE tvz${IBTBranch}quotedstock.artikel_nr = tquota.articleno); " >> ${SQLFILE}
				echo "DROP TABLE tquota;" >> ${SQLFILE}
				echo >> ${SQLFILE}
			done			

			echo "CREATE TEMP TABLE tstocklevel(article char(20), flagibt char(20) default '0' not null, " >> ${SQLFILE}
			echo " stockleveldc char(20) default '0' not null " >> ${SQLFILE}
			for IBTBranch in ${arrIBTBranches[*]}; do
 				echo ", stocklevelibt${IBTBranch} char(20) default '0' not null " >> ${SQLFILE}
			done
			echo " );" >> ${SQLFILE}
			echo >> ${SQLFILE}

			echo "INSERT INTO tstocklevel VALUES ('Article', 'IBT', '${BRANCHNO}'" >> ${SQLFILE}
			for IBTBranch in ${arrIBTBranches[*]}; do
		            echo ", '${IBTBranch}'" >> ${SQLFILE}
			done
			echo " );" >> ${SQLFILE}

			echo "INSERT INTO tstocklevel SELECT " >> ${SQLFILE}
			echo "tvz${BRANCHNO}quotedstock.artikel_nr AS article, " >> ${SQLFILE}
			echo "NVL(tvz${BRANCHNO}quotedstock.verbundartikel, '0') AS flagibt, " >> ${SQLFILE} 
			echo "NVL(tvz${BRANCHNO}quotedstock.bestand, '0') AS stockleveldc " >> ${SQLFILE}
			for IBTBranch in ${arrIBTBranches[*]}; do
				echo ", NVL(tvz${IBTBranch}quotedstock.bestand, '0') AS stocklevelibt${IBTBranch}" >> ${SQLFILE}
			done
			echo "FROM tvz${BRANCHNO}quotedstock " >> ${SQLFILE}
			for IBTBranch in ${arrIBTBranches[*]}; do
				echo ", OUTER tvz${IBTBranch}quotedstock " >> ${SQLFILE}
			done
			echo "WHERE 1=1 " >> ${SQLFILE}
			for IBTBranch in ${arrIBTBranches[*]}; do
				echo "AND tvz${BRANCHNO}quotedstock.artikel_nr = tvz${IBTBranch}quotedstock.artikel_nr " >> ${SQLFILE}
			done
			echo "; " >> ${SQLFILE}
			echo >> ${SQLFILE}
			
			echo "SELECT pharmacygroupid FROM customerpharmacygr" >> ${SQLFILE}
			echo "WHERE branchno=${BRANCHNO} AND customerno=${CUSTOMER} " >> ${SQLFILE}
			echo " AND pharmacygroupid IN (SELECT pharmacygroupid FROM articlereservation WHERE branchno=${BRANCHNO})" >> ${SQLFILE}
			echo "INTO TEMP t${BRANCHNO}phgrid WITH NO LOG; " >> ${SQLFILE}
			
			echo "UPDATE tstocklevel SET stockleveldc = cast( stockleveldc + " >> ${SQLFILE}
			echo "( " >> ${SQLFILE}                      
			echo "  SELECT SUM(reservedqty) FROM articlereservation WHERE branchno = ${BRANCHNO} " >> ${SQLFILE}						
			echo "  AND articleno = tstocklevel.article AND pharmacygroupid IN " >> ${SQLFILE}
			echo "    ( SELECT pharmacygroupid FROM t${BRANCHNO}phgrid " >> ${SQLFILE}
			echo "    ) " >> ${SQLFILE}						
			echo ") as int ) " >> ${SQLFILE}
			echo "WHERE article NOT LIKE 'Article%' AND " >> ${SQLFILE}
			echo "cast( article as int ) IN " >> ${SQLFILE}
			echo "( " >> ${SQLFILE}
			echo "  SELECT articleno FROM articlereservation WHERE branchno = ${BRANCHNO} " >> ${SQLFILE}
			echo "  AND pharmacygroupid IN " >> ${SQLFILE}
			echo "    ( SELECT pharmacygroupid FROM t${BRANCHNO}phgrid " >> ${SQLFILE}
			echo "    ) " >> ${SQLFILE}						
			echo "); " >> ${SQLFILE}

			
			echo "UPDATE tstocklevel SET article=(SELECT NVL(article_code, tstocklevel.article) FROM articlecodes " >> ${SQLFILE}
			echo "WHERE CAST(tstocklevel.article AS int)= articlecodes.articleno AND code_type=16) WHERE article NOT LIKE 'Article%'; " >> ${SQLFILE}
			echo "UPDATE tstocklevel SET flagibt='1' WHERE flagibt NOT IN('0', '1') and article != 'Article';" >> ${SQLFILE}
			echo "UPDATE tstocklevel SET stockleveldc = '99' WHERE stockleveldc > 99; " >> ${SQLFILE}
			for IBTBranch in ${arrIBTBranches[*]}; do
				echo "UPDATE tstocklevel SET stocklevelibt${IBTBranch} = '99' WHERE " >> ${SQLFILE}
				echo "stocklevelibt${IBTBranch} > 99; " >> ${SQLFILE}
            done
			echo >> ${SQLFILE}

			#hierr echo "UNLOAD TO '${DATA_PATH}/output/bestand-${BRANCHNO}-${CUSTOMER}.info' " >> ${SQLFILE} 
			echo "UNLOAD TO '${DATA_PATH}/output/bestand-${BRANCHNO}-${CUSTOMER}.info' " >> ${SQLFILE} 
			echo "SELECT article, flagibt, stockleveldc " >> ${SQLFILE}
			for IBTBranch in ${arrIBTBranches[*]}; do
				echo ", stocklevelibt${IBTBranch} " >> ${SQLFILE}
			done
			echo "FROM tstocklevel ; " >> ${SQLFILE}
			echo >> ${SQLFILE}

			echo "DROP TABLE tarticle;" >> ${SQLFILE}
			echo "DROP TABLE tstocklevel;" >> ${SQLFILE}
			echo "DROP TABLE tvz${BRANCHNO}quotedstock;" >> ${SQLFILE}
			echo "DROP TABLE t${BRANCHNO};" >> ${SQLFILE}			
			echo "DROP TABLE t${BRANCHNO}phgrid;" >> ${SQLFILE}
			
			for IBTBranch in ${arrIBTBranches[*]}; do
				echo "DROP TABLE tvz${IBTBranch}quotedstock;" >> ${SQLFILE}
				echo "DROP TABLE t${IBTBranch};" >> ${SQLFILE}
			done

		# execute SQL query
			echo "executing query for customer ${CUSTOMER} of branch ${BRANCHNO}"
			echo "executing query for customer ${CUSTOMER} of branch ${BRANCHNO}" >> ${LOG_RESOURCE}
			#hierr rm ${DATA_PATH}/output/bestand-${BRANCHNO}-${CUSTOMER}.info 2>/dev/null
			rm ${DATA_PATH}/output/bestand-${BRANCHNO}-${CUSTOMER}.info 2>/dev/null
			dbaccess ${DB} ${SQLFILE} 1>>${LOG_RESOURCE} 2>>${LOG_RESOURCE_ERROR}

		# delete sql workfile
	        rm ${SQLFILE} 2>/dev/null

			echo "finished query for customer ${CUSTOMER} of branch ${BRANCHNO}"
			echo "finished query for customer ${CUSTOMER} of branch ${BRANCHNO}" >> ${LOG_RESOURCE}

	done

 	rc=$?;
 	echo "$msg" | tee -a $LOG_RESOURCE
 fi
 
 print_msg "$STOPMSG" "$*" "<$rc>"
 
 exit $rc;
