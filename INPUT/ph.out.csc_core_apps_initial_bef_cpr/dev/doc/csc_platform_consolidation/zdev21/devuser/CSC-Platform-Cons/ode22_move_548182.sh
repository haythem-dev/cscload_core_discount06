#! /usr/bin/ksh
exit;

echo '==========================================================='
echo 'Script started                                             '
echo '==========================================================='

echo ' --> prepare aaorderclose ini files '
mv /software/wss/de4/ksc/batch/ini/aaordclose54.ini /software/wss/de4/ksc/batch/ini/old/aaordclose54.ini
mv /software/wss/de4/ksc/batch/ini/aaordclose81.ini /software/wss/de4/ksc/batch/ini/old/aaordclose81.ini
mv /software/wss/de4/ksc/batch/ini/aaordclose82.ini /software/wss/de4/ksc/batch/ini/old/aaordclose82.ini

echo ' --> prepare csc_corpha config file '
cp /software/wss/de4/ksc/batch/ini/csc_corpha.xml /software/wss/de4/ksc/batch/ini/old/csc_corpha.xml
cp /software/wss/de4/ksc/batch/ini/release/csc_corpha.xml.548182 /software/wss/de4/ksc/batch/ini/csc_corpha.xml

echo ' --> prepare csc_phabor config file '
cp /software/wss/de4/ksc/batch/ini/csc_phabor.xml /software/wss/de4/ksc/batch/ini/old/csc_phabor.xml
cp /software/wss/de4/ksc/batch/ini/release/csc_phabor.xml.548182 /software/wss/de4/ksc/batch/ini/csc_phabor.xml

echo ' --> prepare csc_phadex config file '
cp /software/wss/de4/ksc/batch/ini/csc_phadex.xml /software/wss/de4/ksc/batch/ini/old/csc_phadex.xml
cp /software/wss/de4/ksc/batch/ini/release/csc_phadex.xml.548182 /software/wss/de4/ksc/batch/ini/csc_phadex.xml

echo ' --> prepare csc_phatra config file '
cp /software/wss/de4/ksc/batch/ini/csc_phatra.xml /software/wss/de4/ksc/batch/ini/old/csc_phatra.xml
cp /software/wss/de4/ksc/batch/ini/release/csc_phatra.xml.548182 /software/wss/de4/ksc/batch/ini/csc_phatra.xml

echo ' --> prepare tpldhipath2 vars file '
cp /software/wss/de4/ksc/load/vars/tpldhipath2.vars /software/wss/de4/ksc/load/vars/old/tpldhipath2.vars
cp /software/wss/de4/ksc/load/vars/release/tpldhipath2.vars.548182 /software/wss/de4/ksc/load/vars/tpldhipath2.vars

echo ' --> move SWStocklevel'
/software/home/devuser/CSC-Platform-Cons/ode22_move_swstocklevel.sh 54
/software/home/devuser/CSC-Platform-Cons/ode22_move_swstocklevel.sh 81
/software/home/devuser/CSC-Platform-Cons/ode22_move_swstocklevel.sh 82

echo '==========================================================='
echo 'Script finished                                            '
echo '==========================================================='

