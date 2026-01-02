#! /usr/bin/ksh
exit;

echo '==========================================================='
echo 'Script started                                             '
echo '==========================================================='

echo ' --> prepare aaorderclose ini files '
mv /software/wss/de/ksc/batch/ini/release/aaordclose05.ini /software/wss/de/ksc/batch/ini/aaordclose05.ini
mv /software/wss/de/ksc/batch/ini/release/aaordclose56.ini /software/wss/de/ksc/batch/ini/aaordclose56.ini

echo ' --> prepare csc_corpha config file '
cp /software/wss/de/ksc/batch/ini/csc_corpha.xml /software/wss/de/ksc/batch/ini/old/csc_corpha.xml
cp /software/wss/de/ksc/batch/ini/release/csc_corpha.xml.0556 /software/wss/de/ksc/batch/ini/csc_corpha.xml

echo ' --> prepare csc_phabor config file '
cp /software/wss/de/ksc/batch/ini/csc_phabor.xml /software/wss/de/ksc/batch/ini/old/csc_phabor.xml
cp /software/wss/de/ksc/batch/ini/release/csc_phabor.xml.0556 /software/wss/de/ksc/batch/ini/csc_phabor.xml

echo ' --> prepare csc_phadex config file '
cp /software/wss/de/ksc/batch/ini/csc_phadex.xml /software/wss/de/ksc/batch/ini/old/csc_phadex.xml
cp /software/wss/de/ksc/batch/ini/release/csc_phadex.xml.0556 /software/wss/de/ksc/batch/ini/csc_phadex.xml

echo ' --> prepare csc_phatra config file '
cp /software/wss/de/ksc/batch/ini/csc_phatra.xml /software/wss/de/ksc/batch/ini/old/csc_phatra.xml
cp /software/wss/de/ksc/batch/ini/release/csc_phatra.xml.0556 /software/wss/de/ksc/batch/ini/csc_phatra.xml

echo ' --> prepare global function to get the ksc db '
cp /software/wss/procfunc/get_ksc_db /software/wss/procfunc/old/get_ksc_db
cp /software/home/devuser/CSC-Platform-Cons/files/get_ksc_db.0556 /software/wss/procfunc/get_ksc_db

echo ' --> prepare global function to get the ksc informix server '
cp /software/wss/procfunc/get_ksc_infxsrv /software/wss/procfunc/old/get_ksc_infxsrv
cp /software/home/devuser/CSC-Platform-Cons/files/get_ksc_infxsrv.0556 /software/wss/procfunc/get_ksc_infxsrv

echo ' --> prepare bi unload unload_akdauftrag.bin'
cp /software/wss/de/bi/bin/unload_akdauftrag.bin /software/wss/de/bi/bin/old/unload_akdauftrag.bin
cp /software/wss/de/bi/bin/release/unload_akdauftrag.bin.0556 /software/wss/de/bi/bin/unload_akdauftrag.bin

echo ' --> prepare bi unload unload_base_database.bin'
cp /software/wss/de/bi/bin/unload_base_database.bin /software/wss/de/bi/bin/old/unload_base_database.bin
cp /software/wss/de/bi/bin/release/unload_base_database.bin.0556 /software/wss/de/bi/bin/unload_base_database.bin

echo ' --> prepare tpldhipath2 vars file '
cp /software/wss/de/ksc/load/vars/tpldhipath2.vars /software/wss/de/ksc/load/vars/old/tpldhipath2.vars
cp /software/wss/de/ksc/load/vars/release/tpldhipath2.vars.0556 /software/wss/de/ksc/load/vars/tpldhipath2.vars

echo '==========================================================='
echo 'Script finished                                            '
echo '==========================================================='
