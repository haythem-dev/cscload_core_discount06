#!/usr/bin/sh
 set -x
###############################################################################################
# installs csc core applications to $HOME/wss
###############################################################################################

# targets
TARGET_CSCSERVICE=cscservice

# subtargets
PROJECT_CSCSERVICE=./thrift


COUNTRIES="at bg ch de fr pfr hr"	# pat pch pfr: not all applications...


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
# install to $HOME/wss
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1	
	install_cscservice_country $COUNTRY

else
	echo "missing country!!!"
	#install_all_cscservice
fi
