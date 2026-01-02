#!/usr/bin/sh
 set -x
###############################################################################################
# installs csc_load to $WSS
###############################################################################################

COUNTRIES="at bg ch de de4 fr pfr hr rs"	# pat pch pfr: not all applications...

###############################################################################################
# install kscserver
###############################################################################################

function install_proc_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/load

	echo "###################################################################"
	echo "# installing proc to $GLOBAL_KSC_DIR"
	echo "###################################################################"
	echo

	# proc directory
	cp -f _scripts/proc/*.sh $GLOBAL_KSC_DIR/proc
	cp -f _scripts/proc/*.option $GLOBAL_KSC_DIR/proc
}

function install_all_proc
{
	for country in $COUNTRIES; do
		install_proc_country $country
	done
}

###############################################################################################
# install cscservice
###############################################################################################

function install_bin_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/load

	echo "###################################################################"
	echo "# installing bin to $GLOBAL_KSC_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f _scripts/bin/*.bin $GLOBAL_KSC_DIR/bin

	BINARIES="
	delkdkritik
	deloldsubsequent
	
	loadartcom
	loadarticlecodes
	loadarticlecodesean
	loadarticlecodeseanzdp
	loadarticleinfo
	loadarticlelppr
	loadchainlimit
	loadcharge
	loadconditions
	loadcstcalcavp
	loadcstdiscacc
	loadcstpharmgrp
	loadcstshort
	loadcustgroups
	loaddealvol
	loaddebtlimit
	loaddkkaa
	loaddkopo
	loaddktmd
	loaddrivers
	loadean
	loadgeneralcalcavp
	loadibtbrancharticleconfig
	loadlppr
	loadmanufacturergroup
	loadnewquota
	loadordercriteria
	loadpayterm
	loadpharmgrp
	loadpricehistory
	loadpromoquota
	loadpromotion
	loadpromotionscale
	loadpseudotours
	loadquotabyfile
	loadrange
	loadreimport
	loadroutecheck
	loadroutes
	loadrouting
	loadroutingms
	loadsalesman
	loadservices
	loadshortlist
	loadtempquota
	loadworkingdayscalendar

	resetquota
	setarticlecategory

	tpldanrufplan
	tpldartindex
	tpldarttext
	tpldauftr
	tplddkkui
	tpldean
	tpldhercode
	tpldhipath2
	tpldlokalart
	tpldreimp
	tpldtour
	tpldvseauftrag
	tpldzentknd
	tpldzentral
	"

	for binary in $BINARIES; do
		cp -f $binary/build/debug/$binary.bin $GLOBAL_KSC_DIR/bin/release
	done
}

function install_all_bin
{
	for country in $COUNTRIES; do
		install_bin_country $country
	done
}

###############################################################################################
# install to $HOME/wss
###############################################################################################


if [[ $# == 1 ]]; then
	COUNTRY=$1
	install_proc_country $COUNTRY
	install_bin_country $COUNTRY

else
	echo "missing country!!!"
	#install_all_kscserver
	#install_all_aapserv
	#install_all_aaorderclose
	#install_all_clearreservation
	#install_all_ibtorderimport
	#install_all_vborderimport
	#install_all_vborderimport2
	#install_all_csc_corpha
	#install_all_csc_phatra
	#install_all_csc_phabor
	#install_all_csc_deli
	#install_all_umk
	#install_all_hmk
	#install_all_bytecumk
	#install_all_lockman
fi
