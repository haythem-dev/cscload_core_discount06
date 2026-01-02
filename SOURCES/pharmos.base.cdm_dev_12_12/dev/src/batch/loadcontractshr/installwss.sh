#!/usr/bin/sh
# set -x
###############################################################################################
# installs application to $WSS
###############################################################################################

# targets
TARGET_LOADCONTRACTSHRCALC=loadcontractshr

# subtargets
PROJECT_LOADCONTRACTSHRCALC=./loadcontractshr

function install_loadcontractshrcalc_country
{
	COUNTRY=$1
	GLOBAL_LOADCONTRACTSHRCALC_DIR=$HOME/wss/$COUNTRY/cdm

	echo "###################################################################"
	echo "# installing $TARGET_LOADCONTRACTSHRCALC to $GLOBAL_LOADCONTRACTSHRCALC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_LOADCONTRACTSHRCALC/build/release/loadcontractshr.bin $GLOBAL_LOADCONTRACTSHRCALC_DIR/bin/loadcontractshr.bin

	# proc directory
	cp -f $PROJECT_LOADCONTRACTSHRCALC/unix/loadcontractshr.sh $GLOBAL_LOADCONTRACTSHRCALC_DIR/proc/loadcontractshr.sh
	cp -f $PROJECT_LOADCONTRACTSHRCALC/unix/loadcontractshr.option $GLOBAL_LOADCONTRACTSHRCALC_DIR/proc/loadcontractshr.option
	
	# ini directory
	cp -f $PROJECT_LOADCONTRACTSHRCALC/loadcontractshr.cfg $GLOBAL_LOADCONTRACTSHRCALC_DIR/ini/loadcontractshr.cfg
}

###############################################################################################
# install to $WSS
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1	
	install_LoadContractsHrcalc_country $COUNTRY
else
	echo "missing country!!!"
fi
