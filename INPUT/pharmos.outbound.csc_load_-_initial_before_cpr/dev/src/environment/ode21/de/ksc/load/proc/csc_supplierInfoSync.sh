#!/usr/bin/sh

 . $(dirname $0)/../vars/ksc_load_global.vars
###################################### Description #############################
#
#	Sync table deliveryreadyness between INBOUND/OUTBOUND-DB
#
################################################################################

### parameter and return code ##################################################

# parameter:
#   #1: Outbound database
#   #2: Inbound database, fully-qualified

### version ####################################################################

version=1.0.0.0

### check positional parameters ################################################

usage="usage: $(basename $0) \
-outboundDb <DB> \
-inboundDb <DB@SRV>"

if [ $1 = "-version" ]
then
    echo ${0} version $version
    exit 0
fi

if [ ! "$1" = "-outboundDb" ]
then
    echo $usage
    exit 1
fi
outboundDb=$2

if [ ! "$3" = "-inboundDb" ]
then
    echo $usage
    exit 1
fi
inboundDb=$4

tidy=0;
outboundTbl="SupplDeliveryInfo"
inboundTbl="deliveryreadiness"
inboundTmpTbl="t_"$inboundTbl

### general settings ###########################################################

timestamp="date +'[%Y-%m-%d %H:%M:%S]'"
sqltimestamp="!printf \"%s\" \"\$($timestamp)\""

today="$(date '+%Y-%m-%d')"
logfile=$LOG_PATH/$(basename $0).$today.log

dbtool=dbaccess

# needed for DB connection: locale
country=at

# module for table parameter
program=csc_supplierInfoSync
avail=available

### general statements #########################################################


### log to logfile #############################################################
function f_log
# $1: log message
{
    printf "%s %s\n"         \
        "$(eval $timestamp)" \
        "$1"                 \
        >> $logfile
}

### log to stdout and logfile ##################################################
function f_out
# $1: output message
{
    printf "%s %s\n"         \
        "$(eval $timestamp)" \
        "$1" 

    f_log "$1"
}

### dbaccess ####################################################################
function f_dbsql
# $* : SQL statements
{
    stmts="\
    SET LOCK MODE TO WAIT 30;"

    # implicitly $*
    for sqlarg
    do
        stmts="$(printf "%s\n%s\n%s" \
                   "$stmts"          \
                   "$sqltimestamp"   \
                   "$sqlarg")"
    done

    # -e : echo SQL statament
    # -a : stop session directly after first statement error
    $dbtool -e -a $outboundDb 1>>$logfile 2>&1 <<SQLBLOCK
$stmts
SQLBLOCK
}

### database environment ########################################################
function f_db_environ 
{
    country=$1

    if [ "bg" = "${country}" ]
    then
        export CLIENT_LOCALE=bg_bg.8859-5
        export DB_LOCALE=bg_bg.8859-5
        export DBMONEY=.
        export DBDATE="MDY4/"
        export GL_DATE=%m/%d/%iY
    else
        unset  CLIENT_LOCALE
        unset  DB_LOCALE
        export DBMONEY=,
        export DBDATE="MDY4/"
        unset  GL_DATE
    fi

    # extract base directory from dbaccess path
    export INFORMIXDIR=$(dirname $(dirname $(which $dbtool)))

    f_log "--- f_db_environ ---------------------------------
    INFORMIXDIR  : $INFORMIXDIR
    CLIENT_LOCALE: $CLIENT_LOCALE
    DB_LOCALE    : $DB_LOCALE
    DBMONEY      : $DBMONEY
    DBDATE       : $DBDATE
    GL_DATE      : $GL_DATE"
}

### prepare tables ##############################################################
function f_preparing 
{
    f_log "--- f_preparing ----------------------------------"
}

### sync tables  ####################################
function f_sync_data 
{
    f_log "--- f_sync_data -------------------"
    
    sql_delete_not_exixsting="\
    delete from $outboundTbl o where o.id not in (select id from $inboundDb:$inboundTbl);"

#   Sync all, because of inbound...
    sql_select_into_i_tmp="\
    SELECT i.id, i.articleno, i.comments, CAST (NVL(i.lastchange, '1901-01-01 00:00:00') AS DATETIME YEAR TO SECOND) lastchange, 
    CASE WHEN DATE(NVL(i.againdeliverablefrom, DATE('12/31/2099'))) > DATE('12/31/2099') THEN DATE('12/31/2099') ELSE DATE(NVL(i.againdeliverablefrom, DATE('12/31/2099'))) END againdeliverablefrom, 
    CASE WHEN DATE(NVL(i.redeliverablefrom, DATE('12/31/2099'))) > DATE('12/31/2099') THEN DATE('12/31/2099') ELSE DATE(NVL(i.redeliverablefrom, DATE('12/31/2099'))) END redeliverablefrom  
    FROM $inboundDb:$inboundTbl i INTO TEMP $inboundTmpTbl;"


    sql_update_insert_existing="\
    MERGE INTO $outboundTbl o
    USING $inboundTmpTbl i
	ON i.id = o.id
    WHEN MATCHED THEN UPDATE 
	SET o.availabilityInfo = i.comments, o.sdichangedate = i.lastchange, o.predictedavaildate = i.againdeliverablefrom, o.availabledate = i.redeliverablefrom
    WHEN NOT MATCHED THEN
	INSERT (o.id, o.articleno, o.availabilityInfo, o.sdichangedate, o.predictedavaildate, o.availabledate) 
	VALUES (i.id, i.articleno, i.comments, NVL(i.lastchange, '1901-01-01 00:00:00' ), NVL(i.againdeliverablefrom, '12/31/2099'), NVL(i.redeliverablefrom, '12/31/2099'));"

    f_dbsql "$sql_delete_not_exixsting"\
	    "$sql_select_into_i_tmp"\
	    "$sql_update_insert_existing"
}


### cleanup ####################################################################
function f_tidy
# $1: tidy 0|1
{
    f_log "---  f_tidy --------------------------------------"

    if [ "$1" = "1" ]
    then
        f_dbsql "$sql_cucosprep_trunc"
    else
        f_log "tidy not forced"
    fi
}

### error handling #############################################################
function f_error
# $1 : error's line number
{
    status=$?

    f_out "ERROR in line $1: command exited with status $status"
    f_log "*** stop *****************************************"

    exit $status
}

### main #######################################################################

# check for script/function command exit with non-zero status
# call error handler
trap 'f_error $LINENO' ERR

f_log "*** start ****************************************
    version: $program  $version
    script : $0
    options: $*"
f_out "start processing"

f_db_environ $country
f_preparing

# cucos preparation table
f_sync_data

f_tidy $tidy

f_log "--------------------------------------------------"
f_out "finished processing"
f_log "*** stop *****************************************"
