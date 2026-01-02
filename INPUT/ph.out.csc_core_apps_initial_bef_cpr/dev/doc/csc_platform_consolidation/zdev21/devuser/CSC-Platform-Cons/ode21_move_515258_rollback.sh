#! /usr/bin/ksh
exit;

echo '==========================================================='
echo 'Script started                                             '
echo '==========================================================='

echo ' --> prepare aaorderclose ini files '
mv /software/wss/de/ksc/batch/ini/aaordclose51.ini /software/wss/de/ksc/batch/ini/release/aaordclose51.ini
mv /software/wss/de/ksc/batch/ini/aaordclose52.ini /software/wss/de/ksc/batch/ini/release/aaordclose52.ini
mv /software/wss/de/ksc/batch/ini/aaordclose58.ini /software/wss/de/ksc/batch/ini/release/aaordclose58.ini

echo ' --> prepare corpha, phabor, phadex, phatra config files '
cp /software/wss/de/ksc/batch/ini/old/csc_corpha.xml /software/wss/de/ksc/batch/ini/csc_corpha.xml
cp /software/wss/de/ksc/batch/ini/old/csc_phabor.xml /software/wss/de/ksc/batch/ini/csc_phabor.xml
cp /software/wss/de/ksc/batch/ini/old/csc_phadex.xml /software/wss/de/ksc/batch/ini/csc_phadex.xml
cp /software/wss/de/ksc/batch/ini/old/csc_phatra.xml /software/wss/de/ksc/batch/ini/csc_phatra.xml

echo ' --> prepare global function to get the ksc db and informix server '
cp /software/wss/procfunc/old/get_ksc_db /software/wss/procfunc/get_ksc_db
cp /software/wss/procfunc/old/get_ksc_infxsrv /software/wss/procfunc/get_ksc_infxsrv

echo ' --> prepare bi unload unload_akdauftrag.bin and unload_base_database.bin'
cp /software/wss/de/bi/bin/old/unload_akdauftrag.bin /software/wss/de/bi/bin/unload_akdauftrag.bin
cp /software/wss/de/bi/bin/old/unload_base_database.bin /software/wss/de/bi/bin/unload_base_database.bin

echo ' --> prepare tpldhipath2 vars file '
cp /software/wss/de/ksc/load/vars/old/tpldhipath2.vars /software/wss/de/ksc/load/vars/tpldhipath2.vars

echo '==========================================================='
echo 'Script finished                                            '
echo '==========================================================='
