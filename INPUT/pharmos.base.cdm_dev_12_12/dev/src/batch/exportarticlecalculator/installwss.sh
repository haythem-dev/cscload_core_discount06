#!/usr/bin/sh
# set -x
###############################################################################################
# installs application to $WSS
###############################################################################################

# targets
TARGET_EXPORTARTICLECALC=exportarticlecalculator

# subtargets
PROJECT_EXPORTARTICLECALC=./exportarticlecalculator

function install_exportarticlecalc_country
{
	COUNTRY=$1
	GLOBAL_EXPORTARTICLECALC_DIR=$HOME/wss/$COUNTRY/cdm

	echo "###################################################################"
	echo "# installing $TARGET_EXPORTARTICLECALC to $GLOBAL_EXPORTARTICLECALC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_EXPORTARTICLECALC/build/release/exportarticlecalculator.bin $GLOBAL_EXPORTARTICLECALC_DIR/bin/exportarticlecalculator.bin

	# proc directory
	cp -f $PROJECT_EXPORTARTICLECALC/unix/exportarticlecalculator.sh $GLOBAL_EXPORTARTICLECALC_DIR/proc/exportarticlecalculator.sh
	cp -f $PROJECT_EXPORTARTICLECALC/unix/exportarticlecalculator.option $GLOBAL_EXPORTARTICLECALC_DIR/proc/exportarticlecalculator.option
	
	# ini directory
	cp -f $PROJECT_EXPORTARTICLECALC/exportarticlecalculator.cfg $GLOBAL_EXPORTARTICLECALC_DIR/ini/exportarticlecalculator.cfg
}

###############################################################################################
# install to $WSS
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1	
	install_exportarticlecalc_country $COUNTRY
else
	echo "missing country!!!"
fi
