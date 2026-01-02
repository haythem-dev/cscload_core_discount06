#! /usr/bin/ksh

#--------------------------------------------------------------------#
# READ IN GLOBAL VARIABLES
#--------------------------------------------------------------------#
. $(dirname $0)/../vars/cdm_ws_global.vars

#--------------------------------------------------------------------#
# PARAMETERS
#--------------------------------------------------------------------#
typeset -i rc=0;

#--------------------------------------------------------------------#
# CHECK GIVEN PARAMETERS
#--------------------------------------------------------------------#

DIR=$(dirname $0)/../log
PREFIX="importocp-status-"
SUFFIX=".csv"
cd $DIR
rc=$?
if [[ rc -ne 0 ]]
then
   echo "Error ${rc}. Problems accessing directory '${DIR}'. Please check!"
   exit $rc
fi

for DATAFILE in $( ls -rtl importocp-status-*.csv | awk '{print $9}' )
do
	export TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
	export FILESTAMP=${DATAFILE#"$PREFIX"}
	export FILESTAMP=${FILESTAMP%"$SUFFIX"}
	export MAILFROM="PHARMOS OCP Import"
	export MAILTO="t.arnold@externals.phoenixgroup.eu, f.feki@externals.phoenixgroup.eu, Alain.THOLLON@phoenixpharma.fr"
	#export MAILTO="t.arnold@externals.phoenixgroup.eu"
	export SUBJECT="importocp Error (file timestamp ${FILESTAMP})"
	export ATTACH=$DATAFILE
	(
		echo "To: $MAILTO"
		echo "Subject: $SUBJECT"
		echo "MIME-Version: 1.0"
		echo 'Content-Type: multipart/mixed; boundary="-q1w2e3r4t5"'
		echo
		echo '---q1w2e3r4t5'
		echo "Content-Type: text/html"
		echo "Content-Disposition: inline\n"
		echo "Dear colleagues,<br><br>"
		echo "The Import OCP interface has reported an error about the import of OCP file with timestamp ${FILESTAMP}.<br>"
		echo "You can find in the attachment the details of the specific OCP articles and its error</b>.<br><br>\n"
		echo "For missing articlecode mappings please use the ZDP Articlecode view to create the corresponding mapping between OCP and PHX articleno and re-import the file via ZDP OCP Staging view of this timestamp.<br><br>\n"
		echo "Best regards<br>\n"
		echo "PHARMOS OCP Import<br>\n"
		echo '---q1w2e3r4t5'
		echo "Content-Type: text/csv;"
		echo "Content-Disposition: attachment; filename=\"$ATTACH\";"
		echo
		cat "$ATTACH"
		echo '---q1w2e3r4t5--'
	) | /usr/sbin/sendmail $MAILTO -f $MAILFROM
	echo "file '$DATAFILE' was mailed successfully."

	if [[ $rc == 0 ]]; then
		mv "${DIR}/${DATAFILE}" "${DIR}/${DATAFILE}.log"
	fi
done;
if [[ $rc != 0 ]]; then
	echo "no file '$DATAFILE' with missing articlecodes found, no mail send out"
	rc=0
fi

exit $rc
