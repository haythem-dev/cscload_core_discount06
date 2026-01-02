#!/usr/bin/ksh

###############################################################################
#
# Versionshistorie:
# 1.0.0.1:
# first release
# 2012.10.10: 
################################ settings #####################################
. $(dirname $0)/../vars/ksc_load_global.vars
LOGFILE=$LOG_PATH/$(basename $0).`date +'%Y%m%d_%H%M%S`.log
VERSION=1.0.0.0
echo "$(basename $0) Version: $VERSION"  >>$LOGFILE

################################ f_db_dest_env ################################
function f_db_dest_env {
  if [[ "bg" = "${COUNTRY}" || "BG" = "${COUNTRY}" ]] ; then
    export CLIENT_LOCALE=bg_bg.8859-5
    export DB_LOCALE=bg_bg.8859-5
    export DBMONEY=.
    export DBDATE="MDY4/"
    export GL_DATE=%m/%d/%iY
  else
    unset CLIENT_LOCALE
    unset DB_LOCALE
    export DBMONEY=,
    unset DBDATE
    unset GL_DATE
  fi
} # f_db_dest_env

#################################### main ########################################
#
##################################################################################

################################ help ################################
  if [[ "-h" == "$1" || "?" == "$1" || "" == $1 ]]; then
    echo
    echo $(basename $0) -database DB -country CC -branch BRANCHNO -datum ARCHIVEDATE 
    echo
    echo "DATABASE:"
    echo "zpos3"
    echo
    echo "BRANCHNO:"
    echo "30 | 32 | ..."
    echo
    echo "ARCHIVEDATE:"
    echo "im Format YYYYMMDD, z.B. 20100831"
    echo
    echo "Bsp: $(basename $0) -database zpos2fr -country fr -branch 23 -datum 20010831"
    echo
    exit 1
  fi



################################ check parameters ################################
  if (( $# < 8 || $# > 8 )); then
    echo "ERROR! Please type in:" >>$LOGFILE
    echo "$(basename $0) -h" >>$LOGFILE
    exit 1
  fi

################################ copy parameters ################################
  DB=$2
  COUNTRY=$4
  BRANCHNO=$6
  ARCHIVEDATE=$8
################################ adaptations #####################################

################################ settings #####################################
  FILENAME_DATE=`date +"%Y%m%d"`
  FILENAME_TIME=`date +"%H%M"`

  FILENAME_RESULT="${DATA_PATH}/DWHOPFK."${BRANCHNO}"."${FILENAME_DATE}"."${FILENAME_TIME}
  FILENAME="${DATA_PATH}/DWHOPFK.${BRANCHNO}"

  rm $FILENAME 2>/dev/null
  TEMPFILE="${FILENAME}.tmp"
  rm $TEMPFILE 2>/dev/null
  mkdir -p ${DATA_PATH}
  touch ${FILENAME}

  f_db_dest_env
  sql_statement1="set isolation to dirty read;"
  
  sql_statement2="unload to '${TEMPFILE}' delimiter ';'
	select 'F', a.datum, a.filialnr, a.kdauftragnr, b.posnr, b.subgeraettyp 
	from informix.akdauftrag a INNER JOIN  informix.akdauftragpos b
	on a.kdauftragnr = b.kdauftragnr and a.datum = b.datum
	where a.datum >= $ARCHIVEDATE and a.filialnr = $BRANCHNO;"

  sql_statement=${sql_statement1}${sql_statement2}
  echo "sql_statement=$sql_statement" >>$LOGFILE

dbaccess ${DB} -<<%
$sql_statement
%

  res=$?
  if [[ $res -ne 0 ]];then
    echo "Unload aus der Tabellen akdauftragpos und akdauftrag fuer VZ $VZ nicht erfolgreich"
    exit 99
  fi

  awk -F';' '{printf("%-3s;%011d;%06d;%011d;%011d;%06d;\r\n",$1,$2,$3,$4,$5,$6)}' $TEMPFILE> $FILENAME

  res=$?
  if [[ $res -ne 0 ]];then
    echo "Formatierung der entladenen Daten aus unload_akdauftragpos_subgeraet fuer VZ $VZ nicht erfolgreich"
    exit 99
  fi

  cp $FILENAME $FILENAME_RESULT
  compress -f $FILENAME_RESULT*

  rm $TEMPFILE 2>/dev/null

  exit 0

