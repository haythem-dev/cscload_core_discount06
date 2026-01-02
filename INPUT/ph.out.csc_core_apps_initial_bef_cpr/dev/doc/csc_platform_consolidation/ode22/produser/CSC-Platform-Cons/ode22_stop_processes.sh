#! /usr/bin/ksh

BRANCHNO=$1
if [ "$BRANCHNO" = "" ]
then
	echo "Es muss eine Filialnummer als Script-Parameter angegeben werden!"
	exit 99;
fi

echo '==========================================================='
echo 'Script started'
echo '==========================================================='

/software/wss/de/ksc/batch/proc/aaordclose.sh -stop -v $BRANCHNO
/software/wss/de/ksc/batch/proc/ibtorderimport.sh -stop -branchno $BRANCHNO -username ibtrelcalc.batch -password H9yItDrj
/software/wss/de/ksc/batch/proc/clearreservation.sh -stop -vz $BRANCHNO
/software/wss/de/ksc/batch/proc/csc_corpha.sh -stop -branchno $BRANCHNO -configfile /software/wss/de/ksc/batch/ini/csc_corpha.xml -orderfilter even
/software/wss/de/ksc/batch/proc/csc_corpha.sh -stop -branchno $BRANCHNO -configfile /software/wss/de/ksc/batch/ini/csc_corpha.xml -orderfilter odd
/software/wss/de/ksc/batch/proc/csc_phabor.sh -stop -branchno $BRANCHNO -configfile /software/wss/de/ksc/batch/ini/csc_phabor.xml -transfer -process
/software/wss/de/ksc/batch/proc/csc_phadex.sh -stop -branchno $BRANCHNO -configfile /software/wss/de/ksc/batch/ini/csc_phadex.xml -country de
/software/wss/de/ksc/batch/proc/csc_phatra.sh -stop -branchno $BRANCHNO -configfile /software/wss/de/ksc/batch/ini/csc_phatra.xml

echo '==========================================================='
echo 'Script finished'
echo '==========================================================='
