#!/usr/bin/sh
set -x
###############################################################################################
# installs csc core applications to $HOME/wss/zqas21
###############################################################################################

CWD=`pwd`
EXPORT_DIR=${CWD}/../../export/zqas21

# targets
TARGET_KSCSERVER=kscserver
TARGET_CSCSERVICE=cscservice
TARGET_AAPSERV=aapserv
TARGET_AAORDERCLOSE=aaorderclose
TARGET_IBTORDERIMPORT=ibtorderimport
TARGET_CLEARRESERVATION=clearreservation
TARGET_CSC_CORPHA=csc_corpha
TARGET_CSC_DELI=csc_deli
TARGET_CSC_PHABOR=csc_phabor
TARGET_CSC_PHADEX=csc_phadex
TARGET_CSC_PHATRA=csc_phatra

# subtargets
PROJECT_KSCSERVER=./kscserver
PROJECT_CSCSERVICE=./thrift
PROJECT_AAPSERV=./aapserv
PROJECT_AAORDERCLOSE=./aaorderclose
PROJECT_IBTORDERIMPORT=./ibtorderimport
PROJECT_CLEARRESERVATION=./clearreservation
PROJECT_CSC_DELI=./csc_deli
PROJECT_CSC_CORPHA=./csc_host_interface/csc_corpha
PROJECT_CSC_PHABOR=./csc_host_interface/csc_phabor
PROJECT_CSC_PHADEX=./csc_host_interface/csc_phadex
PROJECT_CSC_PHATRA=./csc_host_interface/csc_phatra
PROJECT_KSCREFRESH_SCRIPTS=./csc_host_interface/kscrefresh_scripts

COUNTRIES="de at pat bg ch pch fr pfr hr"	 

###############################################################################################
#
###############################################################################################

function check_create_dir 
{
	DIRECTORY=$1

	if [[ ! -d $DIRECTORY ]]; then
		mkdir -p $DIRECTORY;
	fi
}

###############################################################################################
#
###############################################################################################

function create_dirs_country
{
	COUNTRY=$1
	KSC_BATCH_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch
	KSC_SERVER_DIR=$EXPORT_DIR/$COUNTRY/ksc/server
	SUBDIRS="bin ini proc vars"

	for dir in $SUBDIRS; do
		check_create_dir $KSC_BATCH_DIR/$dir
		check_create_dir $KSC_SERVER_DIR/$dir
	done
}

###############################################################################################
#
###############################################################################################

function create_all_dirs
{
	for country in $COUNTRIES; do
		create_dirs_country $country
	done
}

###############################################################################################
# install kscserver
###############################################################################################

function install_global_scripts
{
	COUNTRY=$1
	SRC_DIR=./environment/server
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/server

	echo "# installing global SCRIPTS to $COUNTRY"	

	# server vars
	cp -f $SRC_DIR/vars/zqas21/ksc_server_global.vars.$COUNTRY $TARGET_DIR/vars/ksc_server_global.vars

	# server ini
	cp -f ./pxverbund/files/message.txt $TARGET_DIR/ini/message.txt

	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch

	# batch vars
	cp -f $SRC_DIR/vars/zqas21/ksc_batch_global.vars.$COUNTRY $TARGET_DIR/vars/ksc_batch_global.vars

	# batch ini
	cp -f ./pxverbund/files/message.txt $TARGET_DIR/ini/message.txt

	cp -f $SRC_DIR/bin/zqas21/basar.config.xml $TARGET_DIR/bin/basar.config.xml
}

function install_all_global_scripts
{
	echo "###################################################################"
	echo "# installing global scripts..."
	echo "###################################################################"	

	for country in $COUNTRIES; do
		install_global_scripts $country
	done
}

###############################################################################################
# install kscserver
###############################################################################################

function scripts_kscserver_country
{
	COUNTRY=$1
	SRC_DIR=./environment/server
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/server
	
	echo "# installing kscserver SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/kscserver.sh                    $TARGET_DIR/proc/kscserver.sh
	cp -f $SRC_DIR/proc/kscserver.option                $TARGET_DIR/proc/kscserver.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/kscserver.ini.$COUNTRY    $TARGET_DIR/ini/kscserver.ini
	cp -f $SRC_DIR/ini/zqas21/kscserver.cfg             $TARGET_DIR/ini/kscserver.cfg
	if [[ $COUNTRY == "bg" ]]; then
		cp -f $SRC_DIR/ini/zqas21/tcaconfig*            $TARGET_DIR/ini
	fi

	# vars directory
	cp -f $SRC_DIR/vars/zqas21/kscserver.vars.$COUNTRY  $TARGET_DIR/vars/kscserver.vars
}

function install_all_kscserver
{
	for country in $COUNTRIES; do
		scripts_kscserver_country $country
	done
}

###############################################################################################
# install aapserv
###############################################################################################

function scripts_aapserv_country
{
	COUNTRY=$1
	SRC_DIR=./environment/server
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/server
	
	echo "# installing aapserv SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/zaapunix.sh                    $TARGET_DIR/proc/zaapunix.sh
	cp -f $SRC_DIR/proc/zaapunix.option                $TARGET_DIR/proc/zaapunix.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/aasunix.ini.$COUNTRY     $TARGET_DIR/ini/aasunix.ini
	cp -f $SRC_DIR/ini/zqas21/zaapunix.cfg             $TARGET_DIR/ini/zaapunix.cfg

	# vars directory
	cp -f $SRC_DIR/vars/zqas21/zaapunix.vars.$COUNTRY  $TARGET_DIR/vars/zaapunix.vars
}

function install_all_aapserv
{
	for country in $COUNTRIES; do
		scripts_aapserv_country $country
	done
}

###############################################################################################
# install cscservice
###############################################################################################

function scripts_cscservice_country
{
	COUNTRY=$1
	SRC_DIR=./environment/server
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/server
	
	echo "# installing cscservice SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/cscservice.sh                    $TARGET_DIR/proc/cscservice.sh
	cp -f $SRC_DIR/proc/cscservice.option                $TARGET_DIR/proc/cscservice.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/cscservice.ini.$COUNTRY    $TARGET_DIR/ini/cscservice.ini
	cp -f $SRC_DIR/ini/zqas21/cscservice.cfg             $TARGET_DIR/ini/cscservice.cfg

	# vars directory
	cp -f $SRC_DIR/vars/zqas21/cscservice.vars.$COUNTRY  $TARGET_DIR/vars/cscservice.vars
}

function install_all_cscservice
{
	for country in $COUNTRIES; do
		scripts_cscservice_country $country
	done
}


###############################################################################################
# install csc_corpha
###############################################################################################

function scripts_csc_corpha_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch
	
	echo "# installing csc_corpha SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/csc_corpha.sh                  $TARGET_DIR/proc/csc_corpha.sh
	cp -f $SRC_DIR/proc/csc_corpha.option              $TARGET_DIR/proc/csc_corpha.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/csc_corpha.cfg           $TARGET_DIR/ini/csc_corpha.cfg
	cp -f $SRC_DIR/ini/zqas21/csc_corpha.xml.$COUNTRY  $TARGET_DIR/ini/csc_corpha.xml
	
	# vars directory
	cp -f $SRC_DIR/vars/zqas21/csc_corpha.vars         $TARGET_DIR/vars/csc_corpha.vars
}

function install_all_csc_corpha
{
	for country in $COUNTRIES; do
		scripts_csc_corpha_country $country
	done
}

###############################################################################################
# install csc_phatra
###############################################################################################

function scripts_csc_phatra_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch
	
	echo "# installing csc_phatra SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/csc_phatra.sh                  $TARGET_DIR/proc/csc_phatra.sh
	cp -f $SRC_DIR/proc/csc_phatra.option              $TARGET_DIR/proc/csc_phatra.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/csc_phatra.cfg           $TARGET_DIR/ini/csc_phatra.cfg
	cp -f $SRC_DIR/ini/zqas21/csc_phatra.xml.$COUNTRY  $TARGET_DIR/ini/csc_phatra.xml
	
	# vars directory
	cp -f $SRC_DIR/vars/zqas21/csc_phatra.vars         $TARGET_DIR/vars/csc_phatra.vars
}

function install_all_csc_phatra
{
	for country in $COUNTRIES; do
		scripts_csc_phatra_country $country
	done
}

###############################################################################################
# install csc_phadex
###############################################################################################

function scripts_csc_phadex_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch
	
	echo "# installing csc_phadex SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/csc_phadex.sh                  $TARGET_DIR/proc/csc_phadex.sh
	cp -f $SRC_DIR/proc/csc_phadex.option              $TARGET_DIR/proc/csc_phadex.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/csc_phadex.cfg           $TARGET_DIR/ini/csc_phadex.cfg
	cp -f $SRC_DIR/ini/zqas21/csc_phadex.xml.$COUNTRY  $TARGET_DIR/ini/csc_phadex.xml
	
	# vars directory
	cp -f $SRC_DIR/vars/zqas21/csc_phadex.vars         $TARGET_DIR/vars/csc_phadex.vars
}

function install_all_csc_phadex
{
	for country in $COUNTRIES; do
		scripts_csc_phadex_country $country
	done
}

###############################################################################################
# install csc_phabor
###############################################################################################

function scripts_csc_phabor_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch
	
	echo "# installing csc_phabor SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/csc_phabor.sh                  $TARGET_DIR/proc/csc_phabor.sh
	cp -f $SRC_DIR/proc/csc_phabor.option              $TARGET_DIR/proc/csc_phabor.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/csc_phabor.cfg           $TARGET_DIR/ini/csc_phabor.cfg
	cp -f $SRC_DIR/ini/zqas21/csc_phabor.xml.$COUNTRY  $TARGET_DIR/ini/csc_phabor.xml
	
	# vars directory
	cp -f $SRC_DIR/vars/zqas21/csc_phabor.vars         $TARGET_DIR/vars/csc_phabor.vars
}

function install_all_csc_phabor
{
	for country in $COUNTRIES; do
		scripts_csc_phabor_country $country
	done
}

###############################################################################################
# install csc_prune
###############################################################################################

function scripts_csc_prune_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch
	
	echo "# installing csc_prune SCRIPTS to $COUNTRY"
	
	# proc directory
	cp -f $SRC_DIR/proc/csc_prune.sh                   $TARGET_DIR/proc/csc_prune.sh
	cp -f $SRC_DIR/proc/csc_prune.option               $TARGET_DIR/proc/csc_prune.option
	cp -f $SRC_DIR/proc/csc_prune.pl                   $TARGET_DIR/proc/csc_prune.pl
}

function install_all_csc_prune
{
	for country in $COUNTRIES; do
		scripts_csc_prune_country $country
	done
}

###############################################################################################
# install aaorderclose
###############################################################################################

function scripts_aaorderclose_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch

	echo "# installing aaorderclose SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/aaordclose.sh                 $TARGET_DIR/proc/aaordclose.sh
	cp -f $SRC_DIR/proc/aaordclose.option             $TARGET_DIR/proc/aaordclose.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/aaorderclose.R.cfg      $TARGET_DIR/ini/aaorderclose.R.cfg
	cp -f $SRC_DIR/ini/zqas21/aaordclose.ini.$COUNTRY $TARGET_DIR/ini/aaordclose.ini
}

function install_all_aaorderclose
{
	for country in $COUNTRIES; do
		scripts_aaorderclose_country $country
	done
}

###############################################################################################
# install csc_deli
###############################################################################################

function scripts_csc_deli_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch

	echo "# installing csc_deli SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/csc_deli.sh         $TARGET_DIR/proc/csc_deli.sh
	cp -f $SRC_DIR/proc/csc_deli.option     $TARGET_DIR/proc/csc_deli.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/csc_deli.cfg  $TARGET_DIR/ini/csc_deli.cfg
}

function install_all_csc_deli
{
	for country in $COUNTRIES; do
		scripts_csc_deli_country $country
	done
}

###############################################################################################
# install ibtorderimport
###############################################################################################

function scripts_ibtorderimport_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch

	echo "# installing ibtorderimport SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/ibtorderimport.sh         $TARGET_DIR/proc/ibtorderimport.sh
	cp -f $SRC_DIR/proc/ibtorderimport.option     $TARGET_DIR/proc/ibtorderimport.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/ibtorderimport.cfg  $TARGET_DIR/ini/ibtorderimport.cfg
}

function install_all_ibtorderimport
{
	for country in $COUNTRIES; do
		scripts_ibtorderimport_country $country
	done
}

###############################################################################################
# install clearreservation
###############################################################################################

function scripts_clearreservation_country
{
	COUNTRY=$1
	SRC_DIR=./environment/batch
	TARGET_DIR=$EXPORT_DIR/$COUNTRY/ksc/batch

	echo "# installing clearreservation SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SRC_DIR/proc/clearreservation.sh                  $TARGET_DIR/proc/clearreservation.sh
	cp -f $SRC_DIR/proc/clearreservation.option              $TARGET_DIR/proc/clearreservation.option

	# ini directory
	cp -f $SRC_DIR/ini/zqas21/clearreservation.ini.$COUNTRY  $TARGET_DIR/ini/clearreservation.ini
	cp -f $SRC_DIR/ini/zqas21/clearreservation.cfg           $TARGET_DIR/ini/clearreservation.cfg
}

function install_all_clearreservation
{
	for country in $COUNTRIES; do
		scripts_clearreservation_country $country
	done
}

###############################################################################################
# install to $HOME/wss/zqas21
###############################################################################################

if [[ $# == 1 ]]; then
	echo "hi" $1
else
	create_all_dirs
	install_all_global_scripts
	install_all_cscservice
	install_all_kscserver
	install_all_aapserv
	install_all_aaorderclose
	install_all_ibtorderimport		
	install_all_clearreservation
#	install_all_csc_deli
	install_all_csc_corpha
	install_all_csc_phatra
	install_all_csc_phadex
	install_all_csc_phabor
	install_all_csc_prune
fi

TARBALL=csc_core_applications_zqas.tar.gz

echo "--- tar ${EXPORT_DIR}/${TARBALL} ..."
cd ${EXPORT_DIR}
TARDIRS=`ls -d */`
gtar -zcvpf ./${TARBALL} ${TARDIRS}
rm -rf ${TARDIRS}
echo "--- tarball contains:"
gtar -ztvpf ./${TARBALL} ${TARDIRS}

HOST='zqas21'
USER='produser'
PASSWD='d5XatpAN1Tm7'

ftp -n -i <<END_SCRIPT
open $HOST
user $USER $PASSWD 
cd /software/wss
put ${TARBALL}
disconnect
quit
END_SCRIPT

cd ${CWD}

