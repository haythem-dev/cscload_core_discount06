#============================================================================================#
# READ IN GLOBAL VARIABLES
#============================================================================================#

. /software/etc/profile_prz

#============================================================================================#
# MODUL GLOBAL VARIABLES --> ATTENTION: INDIVIDUAL MODIFICATION REQUIRED (new variables) <--
#============================================================================================#
export readonly LOCKMAN=$WSS/pat/ksc/lockman/commonmem
export readonly BIN_PATH=$WSS/pat/ksc/server/bin
export readonly LOG_PATH=$WSS/pat/ksc/server/log
export readonly INI_PATH=$WSS/pat/ksc/server/ini
export readonly PROC_PATH=$WSS/pat/ksc/server/proc
export readonly DATA_PATH=$WSS/pat/ksc/server/data
export readonly MODULE_PATH=$WSS/pat/ksc/server
export readonly PROCNAME=$(basename $0);
export readonly LOG_FILE=${PROCNAME}.log
export readonly LOG_RESOURCE=${LOG_PATH}/${LOG_FILE}
export readonly LOG_RESOURCE_ERROR=${LOG_RESOURCE}
export MARATHON_LOG_CONFIGDIR=$INI_PATH   # export important for framework log4cplusplus
export MARATHON_LOG_LOGSDIR=$LOG_PATH 	# export important for framework log4cplusplus
RT_CICS=$WSS/lib/tcaccess/current/sharedlib/release
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$RT_CICS
export LD_LIBRARY_PATH
## xz:wird erst auskommentiert
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LIB_PATH}/stlport/4.5.3/sharedlib/release
export LD_LIBRARY_PATH
#============================================================================================#
# GLOBAL VARIABLES EXTENSION
#============================================================================================#
export readonly PATH=${BIN_PATH}:${PATH}
export PLCONFIG=ksc_server_pat
#TRACE_PRINT=1

#============================================================================================#
# FUNCTION print_modul_global_var
#============================================================================================#
function print_modul_global_var
{
	local readonly FUNCNAME="print_global_var";
	echo "--------------------------"
	echo "ENTER $FUNCNAME"
	echo "--------------------------"

	echo "\$BIN_PATH:                >$BIN_PATH<"
	echo "\$LOG_PATH:                >$LOG_PATH<"
	echo "\$INI_PATH:                >$INI_PATH<"
	echo "\$PROC_PATH:               >$PROC_PATH<"
	echo "\$MODULE_PATH:             >$MODULE_PATH<"
	echo "\$PROCNAME:                >$PROCNAME<"
	echo "\$LOG_FILE:                >$LOG_FILE<"
	echo "\$LOG_RESOURCE:            >$LOG_RESOURCE<"
	echo "\$LOG_RESOURCE_ERROR:      >$LOG_RESOURCE_ERROR<"
	echo "\$TRACE_PRINT:             >$TRACE_PRINT<"
	echo "\$MARATHON_LOG_CONFIGDIR:  >$MARATHON_LOG_CONFIGDIR<"
	echo "\$MARATHON_LOG_LOGSDIR:    >$MARATHON_LOG_LOGSDIR<"

	echo "--------------------------"
	echo "EXIT $FUNCNAME"
	echo "--------------------------"

}
