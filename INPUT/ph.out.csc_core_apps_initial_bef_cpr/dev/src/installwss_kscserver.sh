#!/usr/bin/sh
 set -x
###############################################################################################
# installs csc core applications to $HOME/wss
###############################################################################################

# targets
TARGET_KSCSERVER=kscserver

# subtargets
PROJECT_KSCSERVER=./kscserver


COUNTRIES="at bg ch de fr pfr hr"	# pat pch pfr: not all applications...


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
# install to $HOME/wss
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1	
	install_kscserver_country $COUNTRY

else
	echo "missing country!!!"
	#install_all_kscserver
fi
