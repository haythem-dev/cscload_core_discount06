#! /usr/bin/ksh

#--------------------------------------------------------------------#
# PARAMETERS
#--------------------------------------------------------------------#

readonly TST_OPTION="-tst";
readonly ACC_OPTION="-acc";
readonly PRD_OPTION="-prd";

readonly WEB_COMP_OPTION="-companies";
readonly WEB_MEDP_OPTION="-personals";
readonly WEB_NORQ_OPTION="-no";

file_env="";
sel_env="";
mail_to="";
key_call="";
web_call="";
file_call="";
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
	if [[ "$1" == "$TST_OPTION" ]]; then 
		sel_env="Test Environment"; file_env="tst";
		mail_to="t.arnold@externals.phoenixgroup.eu, o.wasmuth@externals.phoenixgroup.eu, b.muenschke@externals.phoenixgroup.eu";
		#mail_to="t.arnold@externals.phoenixgroup.eu";
		shift;
		continue;
	fi
	if [[ "$1" == "$ACC_OPTION" ]]; then
		sel_env="Acceptance Environment"; file_env="acc";
		mail_to="t.arnold@externals.phoenixgroup.eu, o.wasmuth@externals.phoenixgroup.eu, b.muenschke@externals.phoenixgroup.eu";
		#mail_to="t.arnold@externals.phoenixgroup.eu";
		shift;
		continue;
	fi
	if [[ "$1" == "$PRD_OPTION" ]]; then
		sel_env="Prod Environment"; file_env="prd";
		mail_to="t.arnold@externals.phoenixgroup.eu, o.wasmuth@externals.phoenixgroup.eu, k.tischhoefer@phoenixgroup.eu, vid@avosano.ch, ladina.walicki@avosano.ch, quality@avosano.ch, lorenza.grossi@avosano.ch, frank.lison@avosano.ch";
		#mail_to="t.arnold@externals.phoenixgroup.eu, o.wasmuth@externals.phoenixgroup.eu, k.tischhoefer@phoenixgroup.eu, albina.rossier@amedis.ch, vid@amedis.ch, antje.zoschke@amedis.ch, ladina.walicki@amedis.ch, quality@amedis.ch, lorenza.grossi@amedis.ch";
		#mail_to="t.arnold@externals.phoenixgroup.eu";
		shift;
		continue;
	fi
	if [[ "$1" == "$KEY_OPTION" ]]; then key_call="YES"; sel_call="Key-Manager"; file_call="no"; shift; continue; fi
	if [[ "$1" == "$WEB_COMP_OPTION" ]]; then web_call="YES"; sel_call="Companies Webservice"; file_call="companies"; shift; continue; fi
        if [[ "$1" == "$WEB_MEDP_OPTION" ]]; then web_call="YES"; sel_call="Medical Persons Webservice"; file_call="medicalpersons"; shift; continue; fi
        if [[ "$1" == "$WEB_NORQ_OPTION" ]]; then web_call="NO"; sel_call="No Webservice"; file_call="no"; shift; continue; fi
	break;
done

#--------------------------#
# EVALUATION OF OPTIONS
#--------------------------#
if [ ! "${sel_env}${sel_call}" ] ; then 
	rc=10;
	echo "importmedreg_mail_err: No options set in command line!" | tee -a ${LOG_RESOURCE}
	exit ${rc};
fi

#--------------------------#
# scan for data files to be attached in mail
#--------------------------#

DIR=$(dirname $0)/../data/medreg
ARCHDIR=./archive
DATAFILE=medreg_${file_call}_export_${file_env}.csv

cd $DIR
rc=$?
if [[ rc -ne 0 ]]
then
   echo "Error ${rc}. Problems accessing directory '${DIR}'. Please check!"
   exit $rc
fi

ANZ=$( ls $DATAFILE | wc -l )

if [[ $ANZ -gt 0 ]]
then
    export TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
    export MAILTO=$mail_to
    export SUBJECT="MedReg $sel_call download file ($sel_env)"
    export ATTACH=$DATAFILE
    (
    echo "From: medregdata@phoenixgroup.eu"
    echo "To: $MAILTO"
    echo "Subject: $SUBJECT"
    echo "MIME-Version: 1.0"
    echo "Content-Type: multipart/mixed; boundary=\"q1w2e3r4t5\""
    echo 
    echo "--q1w2e3r4t5"
    echo "Content-Type: text/html"
    echo "Content-Disposition: inline\n"
    echo "Die MedReg-Listendatei: ${DATAFILE} wurde erfolgreich vom ${sel_call} heruntergeladen.<br>"
    echo "Die Datei befindet sich im Anhang dieser Mail.<br>"
    echo "Eine Kopie wurde im Archiv als ${DATAFILE}_${TIMESTAMP} abgelegt.<br>"
    echo "<hr><br>"
    echo "The MedReg data file: ${DATAFILE} has been downloaded successfully from ${sel_call}.<br>"
    echo "The file can be found attached to this mail.<br>"
    echo "A copy of the file was created in the archive as ${DATAFILE}_${TIMESTAMP}.<br>\n"
    echo "--q1w2e3r4t5"
    echo "Content-Type: text/csv;"
    echo "Content-Disposition: attachment; filename=\"$ATTACH\";"
    echo
    cat "$ATTACH"
    echo "--q1w2e3r4t5--"
    ) | /usr/sbin/sendmail -vvvv $MAILTO
    echo "file $DATAFILE was mailed successfully."

    mv "$DATAFILE" "${ARCHDIR}/${DATAFILE}_${TIMESTAMP}"
    rc=$?
    if [[ $rc -ne 0 ]]; then
      echo "error moving ${DIR}/$DATAFILE to ${ARCHDIR}/${DATAFILE}_${TIMESTAMP}. Please check!"
    else
	    echo "file $DATAFILE was archived to ${DATAFILE}_${TIMESTAMP} successfully."
    fi
else
  echo "no files found!"
fi
exit $rc
