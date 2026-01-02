#!/usr/bin/sh
# set -x
###############################################################################################
# installs application to $WSS
###############################################################################################

# targets
TARGET_IBTRELCALC=ibtrelevantcalculator

# subtargets
PROJECT_IBTRELCALC=./ibtrelevantcalculator

function install_ibtrelcalc_country
{
	COUNTRY=$1
	GLOBAL_IBTRELCALC_DIR=$HOME/wss/$COUNTRY/cdm

	echo "###################################################################"
	echo "# installing $TARGET_IBTRELCALC to $GLOBAL_IBTRELCALC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_IBTRELCALC/build/release/ibtrelevantcalculator.bin $GLOBAL_IBTRELCALC_DIR/bin/ibtrelevantcalculator.bin

	# proc directory
	cp -f $PROJECT_IBTRELCALC/unix/ibtrelevantcalculator.sh $GLOBAL_IBTRELCALC_DIR/proc/ibtrelevantcalculator.sh
	cp -f $PROJECT_IBTRELCALC/unix/ibtrelevantcalculator.option $GLOBAL_IBTRELCALC_DIR/proc/ibtrelevantcalculator.option
	
	# ini directory
	cp -f $PROJECT_IBTRELCALC/ibtrelevantcalculator.cfg $GLOBAL_IBTRELCALC_DIR/ini/ibtrelevantcalculator.cfg
}

###############################################################################################
# install to $WSS
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1	
	install_ibtrelcalc_country $COUNTRY
else
	echo "missing country!!!"
fi
