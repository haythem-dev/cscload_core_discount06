#!/usr/bin/sh
 set -x
###############################################################################################
# installs csc core applications to $HOME/wss
###############################################################################################

# targets
TARGET_KSCSERVER=kscserver
TARGET_AAPSERV=aapserv
TARGET_AAORDERCLOSE=aaorderclose
TARGET_VBORDERIMPORT2=vborderimport2
TARGET_CLEARRESERVATION=clearreservation
TARGET_CSC_DELI=csc_deli
TARGET_CSC_CORPHA=csc_corpha
TARGET_CSC_PHABOR=csc_phabor
TARGET_CSC_PHATRA=csc_phatra
TARGET_IBTORDERIMPORT=ibtorderimport
TARGET_CSCSERVICE=cscservice

# subtargets
PROJECT_KSCSERVER=./kscserver
PROJECT_AAPSERV=./aapserv
PROJECT_AAORDERCLOSE=./aaorderclose
PROJECT_VBORDERIMPORT2=./vborderimport2
PROJECT_CLEARRESERVATION=./clearreservation
PROJECT_CSC_CORPHA=./csc_host_interface/csc_corpha
PROJECT_CSC_PHABOR=./csc_host_interface/csc_phabor
PROJECT_CSC_PHATRA=./csc_host_interface/csc_phatra
PROJECT_CSC_PHADEX=./csc_host_interface/csc_phadex
PROJECT_KSCREFRESH_SCRIPTS=./csc_host_interface/kscrefresh_scripts
PROJECT_IBTORDERIMPORT=./ibtorderimport
PROJECT_CSC_DELI=./csc_deli
PROJECT_CSCSERVICE=./thrift


COUNTRIES="at bg ch de fr pfr hr"	# pat pch pfr: not all applications...

function install_global_scripts
{
	COUNTRY=$1
	CONFIG_DIR=./pxverbund/files
	HOME_KSC_DIR=$WSS/$COUNTRY/ksc/server

	echo "# installing message.txt to $COUNTRY"	

	# server ini
	cp -f $CONFIG_DIR/message.txt $HOME_KSC_DIR/ini/message.txt

	HOME_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	# batch ini
	cp -f $CONFIG_DIR/message.txt $HOME_KSC_DIR/ini/message.txt
}


###############################################################################################
# install kscserver
###############################################################################################

function install_kscserver_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/server

	echo "###################################################################"
	echo "# installing $TARGET_KSCSERVER to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_KSCSERVER/build/debug/kscserver.bin $GLOBAL_KSC_DIR/bin/release/kscserver.bin

	# proc directory
	cp -f ./environment/server/proc/kscserver.sh $GLOBAL_KSC_DIR/proc/kscserver.sh
	cp -f ./environment/server/proc/kscserver.option $GLOBAL_KSC_DIR/proc/kscserver.option

	# ini directory
	cp -f ./environment/server/ini/zdev21/kscserver.cfg $GLOBAL_KSC_DIR/ini/kscserver.cfg
}

function install_all_kscserver
{
	for country in $COUNTRIES; do
		install_kscserver_country $country
	done
}

###############################################################################################
# install cscservice
###############################################################################################

function install_cscservice_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/server

	echo "###################################################################"
	echo "# installing $TARGET_CSCSERVICE to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_CSCSERVICE/build/debug/cscservice.bin $GLOBAL_KSC_DIR/bin/release/cscservice.bin

	# proc directory
	cp -f ./environment/server/proc/cscservice.sh $GLOBAL_KSC_DIR/proc/cscservice.sh
	cp -f ./environment/server/proc/cscservice.option $GLOBAL_KSC_DIR/proc/cscservice.option

	# ini directory
	cp -f ./environment/server/ini/zdev21/cscservice.cfg $GLOBAL_KSC_DIR/ini/cscservice.cfg

	# vars directory
	cp -f ./environment/server/vars/zdev21/cscservice.vars.$COUNTRY $GLOBAL_KSC_DIR/vars/cscservice.vars
}

function install_all_cscservice
{
	for country in $COUNTRIES; do
		install_cscservice_country $country
	done
}

###############################################################################################
# install aapserv
###############################################################################################

function install_aapserv_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/server

	echo "###################################################################"
	echo "# installing $TARGET_AAPSERV to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_AAPSERV/build/debug/zaapunix.bin $GLOBAL_KSC_DIR/bin/release/zaapunix.bin

	# proc directory
	cp -f ./environment/server/proc/zaapunix.sh $GLOBAL_KSC_DIR/proc/zaapunix.sh
	cp -f ./environment/server/proc/zaapunix.option $GLOBAL_KSC_DIR/proc/zaapunix.option

	# ini directory
	cp -f ./environment/server/ini/zdev21/zaapunix.cfg $GLOBAL_KSC_DIR/ini/zaapunix.cfg
}

function install_all_aapserv
{
	for country in $COUNTRIES; do
		install_aapserv_country $country
	done
}

###############################################################################################
# install csc_corpha
###############################################################################################

function install_csc_corpha_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_CSC_CORPHA to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_CSC_CORPHA/build/debug/csc_corpha.bin $GLOBAL_KSC_DIR/bin/release/csc_corpha.bin

	# proc directory
	cp -f ./environment/batch/proc/csc_corpha.sh $GLOBAL_KSC_DIR/proc/csc_corpha.sh
	cp -f ./environment/batch/proc/csc_corpha.option $GLOBAL_KSC_DIR/proc/csc_corpha.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/csc_corpha.cfg $GLOBAL_KSC_DIR/ini/csc_corpha.cfg
}

function install_all_csc_corpha
{
	for country in $COUNTRIES; do
		install_csc_corpha_country $country
	done
}

###############################################################################################
# install csc_phatra
###############################################################################################

function install_csc_phatra_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_CSC_PHATRA to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_CSC_PHATRA/build/debug/csc_phatra.bin $GLOBAL_KSC_DIR/bin/release/csc_phatra.bin

	# proc directory
	cp -f ./environment/batch/proc/csc_phatra.sh $GLOBAL_KSC_DIR/proc/csc_phatra.sh
	cp -f ./environment/batch/proc/csc_phatra.option $GLOBAL_KSC_DIR/proc/csc_phatra.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/csc_phatra.cfg $GLOBAL_KSC_DIR/ini/csc_phatra.cfg
}

function install_all_csc_phatra
{
	for country in $COUNTRIES; do
		install_csc_phatra_country $country
	done
}

###############################################################################################
# install csc_phabor
###############################################################################################

function install_csc_phabor_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_CSC_PHABOR to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_CSC_PHABOR/build/debug/csc_phabor.bin $GLOBAL_KSC_DIR/bin/release/csc_phabor.bin

	# proc directory
	cp -f ./environment/batch/proc/csc_phabor.sh $GLOBAL_KSC_DIR/proc/csc_phabor.sh
	cp -f ./environment/batch/proc/csc_phabor.option $GLOBAL_KSC_DIR/proc/csc_phabor.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/csc_phabor.cfg $GLOBAL_KSC_DIR/ini/csc_phabor.cfg
}

function install_all_csc_phabor
{
	for country in $COUNTRIES; do
		install_csc_phabor_country $country
	done
}

###############################################################################################
# install csc_phadex
###############################################################################################

function install_csc_phadex_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_CSC_PHADEX to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_CSC_PHADEX/build/debug/csc_phadex.bin $GLOBAL_KSC_DIR/bin/release/csc_phadex.bin

	# proc directory
	cp -f ./environment/batch/proc/csc_phadex.sh $GLOBAL_KSC_DIR/proc/csc_phadex.sh
	cp -f ./environment/batch/proc/csc_phadex.option $GLOBAL_KSC_DIR/proc/csc_phadex.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/csc_phadex.cfg $GLOBAL_KSC_DIR/ini/csc_phadex.cfg
}

function install_all_csc_phadex
{
	for country in $COUNTRIES; do
		install_csc_phadex_country $country
	done
}

###############################################################################################
# install aaorderclose
###############################################################################################

function install_aaorderclose_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_AAORDERCLOSE to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_AAORDERCLOSE/build/debug/aaorderclose.R.bin $GLOBAL_KSC_DIR/bin/release/aaorderclose.R.bin

	# proc directory
	cp -f ./environment/batch/proc/aaordclose.sh $GLOBAL_KSC_DIR/proc/aaordclose.sh
	cp -f ./environment/batch/proc/aaordclose.option $GLOBAL_KSC_DIR/proc/aaordclose.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/aaorderclose.R.cfg $GLOBAL_KSC_DIR/ini/aaorderclose.R.cfg
}

function install_all_aaorderclose
{
	for country in $COUNTRIES; do
		install_aaorderclose_country $country
	done
}

###############################################################################################
# install ibtorderimport
###############################################################################################

function install_ibtorderimport_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_IBTORDERIMPORT to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_IBTORDERIMPORT/build/debug/ibtorderimport.bin $GLOBAL_KSC_DIR/bin/release/ibtorderimport.bin

	# proc directory
	cp -f ./environment/batch/proc/ibtorderimport.sh $GLOBAL_KSC_DIR/proc/ibtorderimport.sh
	cp -f ./environment/batch/proc/ibtorderimport.option $GLOBAL_KSC_DIR/proc/ibtorderimport.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/ibtorderimport.cfg $GLOBAL_KSC_DIR/ini/ibtorderimport.cfg
}

function install_all_ibtorderimport
{
	IBTORDERIMPORT_COUNTRIES="at bg ch de de4 fr pfr hr"
	for country in $IBTORDERIMPORT_COUNTRIES; do
		install_ibtorderimport_country $country
	done
}

###############################################################################################
# install cac_deli
###############################################################################################

function install_csc_deli_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_CSC_DELI to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_CSC_DELI/csc_deli/build/debug/csc_deli.bin $GLOBAL_KSC_DIR/bin/release/csc_deli.bin

	# proc directory
	cp -f ./environment/batch/proc/csc_deli.sh $GLOBAL_KSC_DIR/proc/csc_deli.sh
	cp -f ./environment/batch/proc/csc_deli.option $GLOBAL_KSC_DIR/proc/csc_deli.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/csc_deli.cfg $GLOBAL_KSC_DIR/ini/csc_deli.cfg
}

function install_all_csc_deli
{
	CSC_DELI_COUNTRIES="at bg ch de fr hr"
	for country in $CSC_DELI_COUNTRIES; do
		install_cac_deli_country $country
	done
}

###############################################################################################
# install vborderimport2
###############################################################################################

function install_vborderimport2_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_VBORDERIMPORT2 to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_VBORDERIMPORT2/build/debug/vborderimport2.bin $GLOBAL_KSC_DIR/bin/release/vborderimport2.bin

	# proc directory
	cp -f ./environment/batch/proc/vbordimport2.sh $GLOBAL_KSC_DIR/proc/vbordimport2.sh
	cp -f ./environment/batch/proc/vbordimport2.option $GLOBAL_KSC_DIR/proc/vbordimport2.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/vborderimport2.cfg $GLOBAL_KSC_DIR/ini/vborderimport2.cfg
}

function install_all_vborderimport2
{
	VBORDERIMPORT2_COUNTRIES="fr pfr"
	for country in $VBORDERIMPORT2_COUNTRIES; do
		install_vborderimport2_country $country
	done
}

###############################################################################################
# install clearreservation
###############################################################################################

function install_clearreservation_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_CLEARRESERVATION to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_CLEARRESERVATION/build/debug/clearreservation.bin $GLOBAL_KSC_DIR/bin/release/clearreservation.bin

	# proc directory
	cp -f ./environment/batch/proc/clearreservation.sh $GLOBAL_KSC_DIR/proc/clearreservation.sh
	cp -f ./environment/batch/proc/clearreservation.option $GLOBAL_KSC_DIR/proc/clearreservation.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/clearreservation.cfg $GLOBAL_KSC_DIR/ini/clearreservation.cfg
	cp -f ./environment/batch/ini/zdev21/clearreservation.ini.$COUNTRY $GLOBAL_KSC_DIR/ini/clearreservation.ini
}

function install_all_clearreservation
{
	for country in $COUNTRIES; do
		install_clearreservation_country $country
	done
}


###############################################################################################
# install to $HOME/wss
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1	
	install_global_scripts $COUNTRY
	install_kscserver_country $COUNTRY
	install_cscservice_country $COUNTRY
	install_aapserv_country $COUNTRY
	install_aaorderclose_country $COUNTRY
	install_clearreservation_country $COUNTRY
	install_ibtorderimport_country $COUNTRY	
	install_vborderimport2_country $COUNTRY
	install_csc_corpha_country $COUNTRY
	install_csc_phatra_country $COUNTRY
	install_csc_phabor_country $COUNTRY
	install_csc_phadex_country $COUNTRY
	install_csc_deli_country $COUNTRY

else
	echo "missing country!!!"
	#install_all_kscserver
	#install_all_aapserv
	#install_all_aaorderclose
	#install_all_clearreservation
	#install_all_ibtorderimport	
	#install_all_vborderimport2
	#install_all_csc_corpha
	#install_all_csc_phatra
	#install_all_csc_phabor
	#install_all_csc_deli
fi
