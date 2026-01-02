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
export TIMESTAMP=$(date '+%Y%m%d_%H%M%S')
export MAILTO="t.arnold@externals.phoenixgroup.eu, f.feki@externals.phoenixgroup.eu"
export SUBJECT="importocp error"
(
	echo "To: $MAILTO"
	echo "Subject: $SUBJECT"
	echo "MIME-Version: 1.0"
	echo 'Content-Type: multipart/mixed; boundary="-q1w2e3r4t5"'
	echo
	echo '---q1w2e3r4t5'
	echo "Content-Type: text/html"
	echo "Content-Disposition: inline\n"
	echo "Dear Support-Team,<br><br>"
	echo "The Import OCP interface has reported an error.<br>"
	echo "The logfles can be found in <b>${HOSTNAME}:${LOG_PATH}</b>.<br><br>\n"
	echo '---q1w2e3r4t5--'
) | /usr/sbin/sendmail $MAILTO

exit $rc
