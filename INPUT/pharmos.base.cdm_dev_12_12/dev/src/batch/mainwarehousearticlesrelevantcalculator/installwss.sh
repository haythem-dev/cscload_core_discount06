#!/usr/bin/sh
# set -x
###############################################################################################
# installs application to $WSS
###############################################################################################

# targets
TARGET=mainwarehousearticlesrelevantcalculator

# subtargets
PROJECT=./mainwarehousearticlesrelevantcalculator

function install_country
{
	COUNTRY=$1
	GLOBAL_DIR=$HOME/wss/$COUNTRY/cdm

	echo "###################################################################"
	echo "# installing $TARGET to $GLOBAL_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f build/release/$TARGET.bin $GLOBAL_DIR/bin/$TARGET.bin

	# proc directory
	cp -f $PROJECT/unix/$TARGET.sh $GLOBAL_DIR/proc/$TARGET.sh
	cp -f $PROJECT/unix/$TARGET.option $GLOBAL_DIR/proc/$TARGET.option
	
	# ini directory
	cp -f $PROJECT/$TARGET.cfg $GLOBAL_DIR/ini/$TARGET.cfg
}

###############################################################################################
# install to $WSS
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1	
	install_country $COUNTRY
else
	echo "missing country!!!"
fi
