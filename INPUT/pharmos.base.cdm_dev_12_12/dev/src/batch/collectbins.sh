#!/usr/bin/sh
 set -x
###############################################################################################
# collect cdm binaries to $HOME/wss/cdm/bin
###############################################################################################

# targets
TARGETS="zpiartik zpignart zpagpgnart zpadglf srvzdpdruck zpadgreimp zpautidm zpcalcprice zpcalcrg zpcronpf zpdailyclosing zpdatacarelf zpdcartik zpdcgnart zpdefpa zpdrupro zpifalf zpifestb zpiherst zpimswgr zpisichg zpisiclf zplfzart zpliartik zplieums zplignart zplilf zpmasaen zpprotok zppwartik zpumldir zputil importarticlegenerator importpricelist importmedreg zpexpensv"

# directory
CDM_BATCH_DIR=$HOME/wss/cdm/bin

###############################################################################################
# check_create_dir 
###############################################################################################

function check_create_dir 
{
	DIRECTORY=$1

	if [[ ! -d $DIRECTORY ]]; then
		mkdir -p $DIRECTORY;
	fi
}

###############################################################################################
# install_cdm_bin target 
###############################################################################################

function install_cdm_bin 
{
	TARGET=$1

	# bin directory
	cp -f ./$TARGET/build/release/$TARGET $CDM_BATCH_DIR
}

###############################################################################################
# install install_all_cdm_bins
###############################################################################################

function install_all_cdm_bins
{
	CDM_BATCH_DIR=$HOME/wss/cdm/bin

	echo "###################################################################"
	echo "# installing $TARGETS to $CDM_BATCH_DIR..."
	echo "###################################################################"
	echo

	for target in $TARGETS; do
		install_cdm_bin $target
	done
}

###############################################################################################
# install to $HOME/cdm/bin
###############################################################################################

check_create_dir $CDM_BATCH_DIR
check_create_dir $CDM_BATCH_DIR/../ini
check_create_dir $CDM_BATCH_DIR/../proc
install_all_cdm_bins
cd ./zpldcust 
make copy
cd ../ibtrelevantcalculator
installwss.sh .
cd ../exportarticlecalculator
installwss.sh .
cd ../mainwarehousearticlesrelevantcalculator
installwss.sh .
cd ../fmdrelevantcalculator
installwss.sh .
