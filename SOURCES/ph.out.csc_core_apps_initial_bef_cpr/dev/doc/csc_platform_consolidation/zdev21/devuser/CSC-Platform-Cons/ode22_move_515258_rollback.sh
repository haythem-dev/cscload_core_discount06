#! /usr/bin/ksh
exit;

echo '==========================================================='
echo 'Script started                                             '
echo '==========================================================='

echo ' --> prepare aaorderclose ini files '
mv /software/wss/de4/ksc/batch/ini/old/aaordclose51.ini /software/wss/de4/ksc/batch/ini/aaordclose51.ini
mv /software/wss/de4/ksc/batch/ini/old/aaordclose52.ini /software/wss/de4/ksc/batch/ini/aaordclose52.ini
mv /software/wss/de4/ksc/batch/ini/old/aaordclose58.ini /software/wss/de4/ksc/batch/ini/aaordclose58.ini

echo ' --> prepare csc_corpha config file '
cp /software/wss/de4/ksc/batch/ini/old/csc_corpha.xml /software/wss/de4/ksc/batch/ini/csc_corpha.xml
cp /software/wss/de4/ksc/batch/ini/old/csc_phabor.xml /software/wss/de4/ksc/batch/ini/csc_phabor.xml
cp /software/wss/de4/ksc/batch/ini/old/csc_phadex.xml /software/wss/de4/ksc/batch/ini/csc_phadex.xml
cp /software/wss/de4/ksc/batch/ini/old/csc_phatra.xml /software/wss/de4/ksc/batch/ini/csc_phatra.xml

echo ' --> prepare tpldhipath2 vars file '
cp /software/wss/de4/ksc/load/vars/old/tpldhipath2.vars /software/wss/de4/ksc/load/vars/tpldhipath2.vars

echo ' --> move SWStocklevel'
/software/home/devuser/CSC-Platform-Cons/ode22_move_swstocklevel_rollback.sh 51
/software/home/devuser/CSC-Platform-Cons/ode22_move_swstocklevel_rollback.sh 52
/software/home/devuser/CSC-Platform-Cons/ode22_move_swstocklevel_rollback.sh 58

echo '==========================================================='
echo 'Script finished                                            '
echo '==========================================================='
