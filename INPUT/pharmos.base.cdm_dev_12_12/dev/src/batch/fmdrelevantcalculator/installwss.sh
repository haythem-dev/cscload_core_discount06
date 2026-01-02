#!/usr/bin/sh
# set -x
###############################################################################################
# installs application to $WSS
###############################################################################################

# targets
TARGET_FMDRELEVANTCALC=fmdrelevantcalculator

# subtargets
PROJECT_FMDRELEVANTCALC=./fmdrelevantcalculator

function install_fmdrelevantcalc_country
{
	COUNTRY=$1
	GLOBAL_FMDRELEVANTCALC_DIR=$HOME/wss/$COUNTRY/cdm

	echo "###################################################################"
	echo "# installing $TARGET_FMDRELEVANTCALC to $GLOBAL_FMDRELEVANTCALC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_FMDRELEVANTCALC/build/release/fmdrelevantcalculator.bin $GLOBAL_FMDRELEVANTCALC_DIR/bin/fmdrelevantcalculator.bin

	# proc directory
	cp -f $PROJECT_FMDRELEVANTCALC/unix/fmdrelevantcalculator.sh $GLOBAL_FMDRELEVANTCALC_DIR/proc/fmdrelevantcalculator.sh
	cp -f $PROJECT_FMDRELEVANTCALC/unix/fmdrelevantcalculator.option $GLOBAL_FMDRELEVANTCALC_DIR/proc/fmdrelevantcalculator.option
	
	# ini directory
	cp -f $PROJECT_FMDRELEVANTCALC/fmdrelevantcalculator.cfg $GLOBAL_FMDRELEVANTCALC_DIR/ini/fmdrelevantcalculator.cfg
}

###############################################################################################
# install to $WSS
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1	
	install_fmdrelevantcalc_country $COUNTRY
else
	echo "missing country!!!"
fi
