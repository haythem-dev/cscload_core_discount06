#!/usr/bin/sh

#============================================================================================================================================================#
# Input Paratmeters : 
# Parameter 1:           not being used #ode21@zdev21_tcp 
# Parameter 2:           not being used #merge.sql 
#============================================================================================================================================================#

#============================================================================================================================================================#
#   commands:
#   dirname:        command removes the trailing / from the NAME and prints the remaining portion
#                   If the NAME does not contain / component then it prints '.' (means current directory)
#   which :         is used to find the location of a program
#                   e.g. which firefox
#                   The output will be something like :/usr/bin/firefox
#   CLIENT_LOCALE : The client locale specifies the language, territory, and code set that the client application uses to perform read and write (I/O)
#   DB_LOCALE:      The database locale, which is set to the DB_LOCALE environment variable, specifies the language, territory, and code set 
#                   that the database server needs to correctly interpret locale-sensitive data types (NCHAR and NVARCHAR) a particular database.
#   local:          Simply declares a variable to have scope only In the currently-defined fnction
#   dbaccess:       command to start DB-Access
#                   Use the dbaccess command to start DB-Access. Include options to specify the database, command files, or to go to a specific menu screen
#   basename:       strips directory and suffix from filenames. E.G. basename test/sample.txt output will be sample.txt
#   eval:           It will take an argument and construct a command of it, which will be executed by the shell
#                   E.G foo=10 x=foo y='$'$x echo $y same with eval  eval y='$'$x echo $y outpur is 10
#=============================================================================================================================================================#

#==========================================================#
# GLOBAL VARIABLES
#==========================================================#
. $(dirname $0)/../vars/ksc_load_global.vars
. $(dirname $0)/../vars/filldeliveryadvicedata.vars

#==========================================================# 
# General settings
#==========================================================# 
today="$(date '+%Y-%m-%d')"
logfile=$LOG_PATH/$(basename $0).$today.log
dbtool=dbaccess

version=1.0.0.0

#dbserver=ode21@zdev21_tcp
#sqfile=merge.sql
#DB=$1
#SQLFILE=$2

#==========================================================#
# log to logfile 
#==========================================================#
function f_log
# output message to log file
{
    
	printf "%s %s\n"         \
        "$(eval $timestamp)" \
        "$1"                 \
        >> $logfile
}

#============================================================#
# log to stdout and logfile 
#============================================================#
function f_out
# output message to console
{
    printf "%s %s\n"         \
        "$(eval $timestamp)" \
        "$1" 
    f_log "$1"
}
#====================================#
# CHECK SQL FILE : merge.sql 
#====================================#
function f_check_file
{
    echo "Check for the sql file $sqfile in the current folder"
    FILE=$sqfile
    if [ -f "$FILE" ];
    then
         echo "File $FILE exist."
         retval=0
    else
         echo "File $FILE does not exist"
         retval=1
    fi
	return "$retval"
}

#====================================#
# PRINT LOCAL VARIABLES 
#====================================#
function print_local_var
{
 	 
local FUNCNAME="print_local_var";
 	 
echo "--------------------------"
echo "ENTER $FUNCNAME"
echo "--------------------------"
#echo "\$MARATHON_SSUK_VERSION:		>$MARATHON_SSUK_VERSION<"
#echo "\$MARATHON_SSUK_LIBRARY_PATH:	>$MARATHON_SSUK_LIBRARY_PATH<"
echo "\$LD_LIBRARY_PATH:			>$LD_LIBRARY_PATH<"
#echo "\$BINARY:						>$BINARY<"
#echo "\$STARTMSG:					>$STARTMSG<"
#echo "\$STOPMSG:					>$STOPMSG<"
#echo "\$START_OPTION:				>$START_OPTION<"
#echo "\$STOP_OPTION:				>$STOP_OPTION<"
#echo "\$STATUS_OPTION:				>$STATUS_OPTION<"
#echo "\$VZ_OPTION:					>$VZ_OPTION<"
#echo "\$LD_OPTION:					>$LD_OPTION<"
#echo "\$WD_OPTION:					>$WD_OPTION<"
#echo "\$para:						>$para<"
#echo "\$process:					>$process<"
#echo "\$start:						>$start<"
#echo "\$stop:						>$stop<"
#echo "\$status:						>$status<"
#echo "\$vz:			>$vz<"
#echo "\$ld:			>$ld<"
#echo "\$wd:			>$wd<"
echo "\$LOG_PATH:	>$LOG_PATH<"
echo "\$sqfile: >$sqfile<"
echo "\$dbserver: >$dbserver<"
echo "--------------------------"
echo "EXIT $FUNCNAME"
echo "--------------------------"

}

#====================================#
# Database Environment
#====================================#
function f_db_environ
{
    # extract base directory from dbaccess path
    export INFORMIXDIR=$(dirname $(dirname $(which $dbtool)))
    f_log "--- f_db_environ ------------
    INFORMIXDIR  : $INFORMIXDIR
    CLIENT_LOCALE: $CLIENT_LOCALE
    DB_LOCALE    : $DB_LOCALE
    DBMONEY      : $DBMONEY
    DBDATE       : $DBDATE
    GL_DATE      : $GL_DATE"
}

#================================================#
# dbsql- For executing sql query written in this script  
#================================================#
function f_dbsqlquery
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
	$dbtool -a $outboundDb 1>>$logfile 2>&1 <<SQLBLOCK
	$stmts
	
SQLBLOCK
}

#================================================================#
# dbsync : For executing a external.sql file containg all Querys
#===============================================================#
function f_dbsqlfile 
{
    f_log "--- f_dbsqlfile -------------------"
    echo $dbserver
    #$dbtool -e -a 	$DB "${SQLFILE}" 
    $dbtool -a $dbserver "$sqfile" 
}

#====================================#
# error handling 
#====================================#
function f_error
# $1 : error's line number
{
    status=$?

    f_out "ERROR in line $1: command exited with status $status"
    f_log "*** stop *****************************************"

    exit $status
}

#====================================#
# cleanup 
#====================================#
function f_tidy
# $1: tidy 0|1
{
    f_log "---  f_tidy --------------------------------------"

    if [ "$1" = "1" ]
    then
        f_dbsqlquery "$sql_cucosprep_trunc"
    else
        f_log "tidy not forced"
    fi
}

#==============================================
# MAIN
#==============================================
trap 'f_error $LINENO' ERR
f_log "*** START ****************************************
version: $version
script : $0
options: $*"

f_out "start processing"

f_check_file
retval=$?
if [ "$retval" == 0 ]
then
    print_local_var
    f_out "prepare DB env"
    f_db_environ 
    f_out "Execute SQL File"
    f_dbsqlfile
else
    echo "File merge.sql not found"
fi
f_out "*****STOP*********************"
exit $rc
