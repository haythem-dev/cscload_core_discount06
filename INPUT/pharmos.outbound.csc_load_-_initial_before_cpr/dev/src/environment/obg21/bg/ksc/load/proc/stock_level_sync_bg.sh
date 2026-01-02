#!/usr/bin/ksh

###################################### Author #######################################
#
# André Egerer
# 25.06.2012
#
##########################################################################################

###################################### Description #######################################
#
# This script loads the stock level from purchase into ksc for all bulgarian branches
# where KSC ist not active at the moment
#
##########################################################################################

############################## Parameter and Return codes ################################
#
# Parameter:
# $1: KSC database
# $3: Purchase database
# $5: Branch number
# example for call of this script: cucosbulgaria._sh -kscdb zpos6bg -pdb zpps2bg@db2_zpps2_tcp -branchno 24
#
# Return codes:
# 0: ok
# 1: wrong usage
# 2: branch not allowed
#
# 2012-10-01: Processing deactivated for branch 22
#
####################################### Version ##########################################
#
##########################################################################################
VERSION=1.0.0.2

################################ Adaptations #####################################
export INFORMIXDIR=$(dirname $INFORMIXDIR) #cuts the last sub directory

################################# general settings ###################################
TODAY=`date +%Y-%m-%d`
LOG_PATH=$(dirname $0)/../log
ERROR=0
KSC_TABLE=artikellokal
PPS_TABLE=artikelf

################################# check parameter ###################################
### -version (Version):
if [[ $1 = "-version" ]];then
        echo ${0} version ${VERSION}
        exit 0
fi

if [[ ! $1 = "-kscdb" ]];then
        ERROR=1
fi
KSC_DB=$2

if [[ ! $3 = "-ppsdb" ]];then
	ERROR=1
fi
PPS_DB=$4

if [[ ! $5 = "-branchno" ]];then
	ERROR=1
fi
BRANCHNO=$6

if [[ ! $BRANCHNO = "26" ]] && [[ ! $BRANCHNO = "28" ]] && [[ $ERROR = "0" ]];then
	ERROR=2
fi

if [[ $BRANCHNO = "22" ]];then
	ERROR=22
fi

if [[ $BRANCHNO = "24" ]];then
	ERROR=22
fi

case $ERROR in
	1)
		echo "usage: $(basename $0) -kscdb KSCDB -ppsdb PURCHASEDB -branchno BRANCHNO"
        	exit 1
	;;
	
	2)
		echo "Only allowed for branch 26, 28"
		exit 2
	;;
	22)
		echo "Branch 22/24 is no longer without PHARMOS :-)"
		exit 0
	
esac;

################################# general settings ###################################
FILELOG=${LOG_PATH}/$(basename $0).${BRANCHNO}.${TODAY}.log

CHECK_FILE=${LOG_PATH}/$(basename $0).'*'.${TODAY}.log

TEMPTABLE1=temp_cucos1;
echo "$(basename $0) $VERSION" >>$FILELOG
echo "$0 $*" >>$FILELOG


################################ f_db_dest_env ################################
function f_db_dest_env {
  country=$1

  if [[ "bg" = "${country}" ]] ; then
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


################################# f_prepararing ###################################
function f_prepararing {
  echo "`date +'[%H:%M:%S]'` *** f_prepararing" >>${FILELOG}
  f_db_dest_env bg

} # f_prepararing 

################################# f_lock_cucosbulgaria_for_salesweb ###################################
function f_stock_sync {
  echo "`date +'[%H:%M:%S]'` *** enter f_stock_sync" >>${FILELOG}

  # get stock from purchase into ksc!
  sql_statement_stock_sync="UPDATE $KSC_TABLE SET $KSC_TABLE.bestand = (SELECT NVL(pps.bestand, 0) FROM $PPS_DB:$PPS_TABLE pps WHERE $KSC_TABLE.filialnr = pps.filialnr and $KSC_TABLE.artikel_nr = pps.artikel_nr) WHERE filialnr = $BRANCHNO and artikel_nr in (SELECT artikel_nr FROM $PPS_DB:$PPS_TABLE WHERE filialnr = $BRANCHNO);"
  
  echo "$sql_statement_stock_sync" >>${FILELOG}

dbaccess ${KSC_DB} >>${FILELOG} 2>&1 <<%
$sql_statement_stock_sync
%
 echo "`date +'[%H:%M:%S]'` *** leave f_stock_sync" >>${FILELOG}
} # f_stock_sync


  f_prepararing

  # Aufruf nur fuer eine Branch:
  echo "`date +'[%H:%M:%S]'` start processing branchno ${BRANCHNO}" 2>&1 \
         | tee -a ${FILELOG}
  
  f_stock_sync

  echo "`date +'[%H:%M:%S]'` finished processing branchno ${BRANCHNO}" 2>&1 \
         | tee -a ${FILELOG}


  exit 0

