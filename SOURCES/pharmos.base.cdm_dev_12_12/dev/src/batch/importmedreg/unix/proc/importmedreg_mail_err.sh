#! /usr/bin/ksh

#--------------------------------------------------------------------#
# READ IN GLOBAL VARIABLES
#--------------------------------------------------------------------#
. $(dirname $0)/../vars/cdm_ws_global.vars

#--------------------------------------------------------------------#
# PARAMETERS
#--------------------------------------------------------------------#
readonly TST_OPTION="-tst";
readonly ACC_OPTION="-acc";
readonly PRD_OPTION="-prd";
readonly KEY_OPTION="-key";
readonly WEB_COMP_OPTION="-companies";
readonly WEB_MEDP_OPTION="-personals";
readonly WEB_NORQ_OPTION="-no";

tst_env="";
acc_env="";
prd_env="";
sel_env="";
key_call="";
web_call="";
sel_call="";
typeset -i rc=0;

#--------------------------------------------------------------------#
# CHECK GIVEN PARAMETERS
#--------------------------------------------------------------------#
if (( $# == 0 )); then
	rc=9;
	echo "importmedreg_mail_err: Error: No Parameters passed!" | tee -a ${LOG_RESOURCE}
	exit ${rc};
fi

while (( $# > 0 )) 
do
	if [[ "$1" == "$TST_OPTION" ]]; then tst_env="YES"; sel_env="Test Environment"; shift; continue; fi
	if [[ "$1" == "$ACC_OPTION" ]]; then acc_env="YES"; sel_env="Acceptance Environment"; shift; continue; fi
	if [[ "$1" == "$PRD_OPTION" ]]; then prd_env="YES"; sel_env="Prod Environment"; shift; continue; fi
	if [[ "$1" == "$KEY_OPTION" ]]; then key_call="YES"; sel_call="Key-Manager"; shift; continue; fi
	if [[ "$1" == "$WEB_COMP_OPTION" ]]; then web_call="YES"; sel_call="Companies Webservice"; shift; continue; fi
        if [[ "$1" == "$WEB_MEDP_OPTION" ]]; then web_call="YES"; sel_call="Medical Personals Webservice"; shift; continue; fi
        if [[ "$1" == "$WEB_NORQ_OPTION" ]]; then web_call="NO"; sel_call="No Webservice"; shift; continue; fi
	break;
done

#--------------------------#
# EVALUATION OF OPTIONS
#--------------------------#
if [ ! "${selenv}${sel_call}" ] ; then 
	rc=10;
	echo "importmedreg_mail_err: No options set in command line!" | tee -a ${LOG_RESOURCE}
	exit ${rc};
fi

export TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
export MAILTO="t.arnold@externals.phoenixgroup.eu, o.wasmuth@externals.phoenixgroup.eu, k.tischhoefer@phoenixgroup.eu"
#export MAILTO="t.arnold@externals.phoenixgroup.eu"
export SUBJECT="MedReg Error (${sel_call} ${sel_env})"
(
	echo "From: medregdata@phoenixgroup.eu"
	echo "To: $MAILTO"
	echo "Subject: $SUBJECT"
	echo "MIME-Version: 1.0"
	echo 'Content-Type: multipart/mixed; boundary="-q1w2e3r4t5"'
	echo
	echo '---q1w2e3r4t5'
	echo "Content-Type: text/html"
	echo "Content-Disposition: inline\n"
	echo "Dear Support-Team,<br><br>"
	echo "The MedReg <b>${sel_call}</b> interface has reported an error in <b>${sel_env}</b>.<br>"
	echo "The logfles can be found in <b>${HOSTNAME}:${LOG_PATH}</b>.<br><br>\n"
	echo "Best Regards<br>\nImportMedReg Interface Bot<br>\n"
	echo '---q1w2e3r4t5--'
) | /usr/sbin/sendmail -vvvv $MAILTO

exit $rc
