#! /usr/bin/ksh

echo '==========================================================='
echo '== ! ! ! ! ! ! ! !   A T T E N T I O N   ! ! ! ! ! ! ! ! =='
echo '==-------------------------------------------------------=='
echo '== Deactivated to ensure the script cannot run by fault! =='
echo '==-------------------------------------------------------=='
echo '== <<<<<   Remove  EXIT  to run the script  ! ! !  >>>>> =='
echo '==========================================================='

exit;

echo '==========================================================='
echo 'Script started                                             '
echo '==========================================================='

echo ' --> prepare aaorderclose ini files '
mv /software/wss/de/ksc/batch/ini/old/aaordclose51.ini /software/wss/de/ksc/batch/ini/aaordclose51.ini
mv /software/wss/de/ksc/batch/ini/old/aaordclose52.ini /software/wss/de/ksc/batch/ini/aaordclose52.ini
mv /software/wss/de/ksc/batch/ini/old/aaordclose58.ini /software/wss/de/ksc/batch/ini/aaordclose58.ini

echo ' --> prepare csc_corpha config file '
cp /software/wss/de/ksc/batch/ini/old/csc_corpha.xml /software/wss/de/ksc/batch/ini/csc_corpha.xml

echo ' --> prepare csc_phabor config file '
cp /software/wss/de/ksc/batch/ini/old/csc_phabor.xml /software/wss/de/ksc/batch/ini/csc_phabor.xml

echo ' --> prepare csc_phadex config file '
cp /software/wss/de/ksc/batch/ini/old/csc_phadex.xml /software/wss/de/ksc/batch/ini/csc_phadex.xml

echo ' --> prepare csc_phatra config file '
cp /software/wss/de/ksc/batch/ini/old/csc_phatra.xml /software/wss/de/ksc/batch/ini/csc_phatra.xml

echo ' --> prepare global function to get the ksc db '
cp /software/wss/procfunc/old/get_ksc_db /software/wss/procfunc/get_ksc_db

echo ' --> prepare global function to get the ksc informix server '
cp /software/wss/procfunc/old/get_ksc_infxsrv /software/wss/procfunc/get_ksc_infxsrv

echo ' --> prepare bi unload unload_akdauftrag.bin'
cp /software/wss/de/bi/bin/old/unload_akdauftrag.bin /software/wss/de/bi/bin/unload_akdauftrag.bin

echo ' --> prepare bi unload unload_base_database.sh'
cp /software/wss/de/bi/bin/old/unload_base_database.sh /software/wss/de/bi/bin/unload_base_database.sh

echo ' --> prepare tpldhipath2 vars file '
cp /software/wss/de/ksc/load/vars/old/tpldhipath2.vars /software/wss/de/ksc/load/vars/tpldhipath2.vars

echo ' --> move SWStocklevel'
/software/home/produser/CSC-Platform-Cons/ode22_move_swstocklevel_rollback.sh 51
/software/home/produser/CSC-Platform-Cons/ode22_move_swstocklevel_rollback.sh 52
/software/home/produser/CSC-Platform-Cons/ode22_move_swstocklevel_rollback.sh 58

echo ' --> prepare biactive depent '
cp /software/wss/de/biactive/depent/bin/old/load_tourdepart.bin /software/wss/de/biactive/depent/bin/load_tourdepart.bin
cp /software/wss/de/biactive/depent/bin/old/unload_tourdep.bin /software/wss/de/biactive/depent/bin/unload_tourdep.bin

echo '==========================================================='
echo 'Script finished                                            '
echo '==========================================================='
