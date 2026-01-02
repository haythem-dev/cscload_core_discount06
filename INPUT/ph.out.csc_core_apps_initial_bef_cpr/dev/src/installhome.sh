#!/usr/bin/sh
# set -x
###############################################################################################
# installs csc core applications to $HOME/wss
###############################################################################################

# targets
TARGET_KSCSERVER=kscserver
TARGET_CSCSERVICE=cscservice
TARGET_AAPSERV=aapserv
TARGET_AAORDERCLOSE=aaorderclose
TARGET_IBTORDERIMPORT=ibtorderimport
TARGET_VBORDERIMPORT2=vborderimport2
TARGET_CLEARRESERVATION=clearreservation
TARGET_CSC_CORPHA=csc_corpha
TARGET_CSC_DELI=csc_deli
TARGET_CSC_PHABOR=csc_phabor
TARGET_CSC_PHADEX=csc_phadex
TARGET_CSC_PHATRA=csc_phatra

# subtargets
PROJECT_KSCSERVER=./kscserver
PROJECT_CSCSERVICE=./thrift
PROJECT_AAPSERV=./aapserv
PROJECT_AAORDERCLOSE=./aaorderclose
PROJECT_IBTORDERIMPORT=./ibtorderimport
PROJECT_VBORDERIMPORT2=./vborderimport2
PROJECT_CLEARRESERVATION=./clearreservation
PROJECT_CSC_DELI=./csc_deli
PROJECT_CSC_CORPHA=./csc_host_interface/csc_corpha
PROJECT_CSC_PHABOR=./csc_host_interface/csc_phabor
PROJECT_CSC_PHADEX=./csc_host_interface/csc_phadex
PROJECT_CSC_PHATRA=./csc_host_interface/csc_phatra
PROJECT_KSCREFRESH_SCRIPTS=./csc_host_interface/kscrefresh_scripts

COUNTRIES="de"	 
LINK_COUNTRIES="at pat bg ch pch fr pfr hr"	# pat pch pfr: not all applications...

###############################################################################################
#
###############################################################################################

function check_create_dir 
{
	DIRECTORY=$1

	if [[ ! -d $DIRECTORY ]]; then
		mkdir -p $DIRECTORY;
	fi
}

###############################################################################################
#
###############################################################################################

function create_dirs_country
{
	COUNTRY=$1
	KSC_BATCH_DIR=$HOME/wss/$COUNTRY/ksc/batch
	KSC_SERVER_DIR=$HOME/wss/$COUNTRY/ksc/server
	SUBDIRS="bin data ini log proc vars"

	for dir in $SUBDIRS; do
		check_create_dir $KSC_BATCH_DIR/$dir
		check_create_dir $KSC_SERVER_DIR/$dir
	done
}

###############################################################################################
#
###############################################################################################

function create_all_dirs
{
	for country in $COUNTRIES; do
		create_dirs_country $country
	done
	for country in $LINK_COUNTRIES; do
		create_dirs_country $country
	done
}

###############################################################################################
# install kscserver
###############################################################################################

typeset -s _userport
#											kscserver				zaasunix				zaapunix
#									Servicename 	Port	Servicename 	Port	Servicename 	Port
#
#Petra Kessling		p.kessli		ksc01_server	56061	aa01_server2	56060	aa01_server3	56062
#Sanjeev Kolli		s.kolli     	ksc02_server	56064	aa02_server2	56063	aa02_server3	56065
#Dmitry Kondratyev	d.kondratyev	ksc03_server	56067	aa03_server2	56066	aa03_server3	56068
#Sachin Degloorwar 	s.degloorwar   	ksc04_server	56070	aa04_server2	56069	aa04_server3	56071
#Varun Gettam		v.gettam		ksc05_server	56073	aa05_server2	56072	aa05_server3	56074
#Steffen Heinlein	s.heinle		ksc06_server	56076	aa06_server2	56075	aa06_server3	56077
#David Zdjelar		d.zdjelar		ksc07_server	56079	aa07_server2	56078	aa07_server3	56080
#Kirtan Singh		k.singh			ksc08_server	56082	aa08_server2	56081	aa08_server3	56083
#Frank Naumann		f.nauman		ksc09_server	56085	aa09_server2	56084	aa09_server3	56086
#Bjoern Bischof		b.bischof		ksc10_server	56088	aa10_server2	56087	aa10_server3	56089
#csctest			csctest			ksc11_server	56091	aa11_server2	56090	aa11_server3	56092
#Sebastian Barth	s.barth			ksc12_server	56094	aa12_server2	56093	aa12_server3	56095
# aa14_server2            56051/tcp       # zaapunix Sagner
# ksc14_server            56052/tcp       # zaasunix Sagner
# aa14_server3            56053/tcp       # zaapunix Sagner
# aa15_server2            56054/tcp       # zaapunix Gugonatu
# ksc15_server            56055/tcp       # zaasunix Gugonatu
# aa15_server3            56056/tcp       # zaapunix Gugonatu
# aa16_server2            56057/tcp       # zaapunix Richter
# ksc16_server            56058/tcp       # zaasunix Richter
# aa16_server3            56059/tcp       # zaapunix Richter
# aa13_server2            56096/tcp       # zaapunix Schuh
# ksc13_server            56097/tcp       # zaasunix Schuh
# aa13_server3            56098/tcp       # zaapunix Schuh
# aa17_server2            56057/tcp       # zaapunix d.florichescu
# ksc17_server            56058/tcp       # zaasunix d.florichescu
# aa17_server3            56059/tcp       # zaapunix d.florichescu


case $LOGNAME in
	p.kessli)		_userport="01"; _cscserviceport="56060";;
	s.kolli)		_userport="02"; _cscserviceport="56063";;
	d.kondratyev)	_userport="03"; _cscserviceport="56066";;
	s.degloorwar)	_userport="04"; _cscserviceport="56069";;
	v.gettam)		_userport="05"; _cscserviceport="56072";;
	s.heinle)		_userport="06"; _cscserviceport="56075";;
	d.zdjelar)		_userport="07"; _cscserviceport="56078";;
	k.singh)		_userport="08"; _cscserviceport="56081";;
	f.nauman)		_userport="09"; _cscserviceport="56084";;
	b.bischof)		_userport="10"; _cscserviceport="56087";;
	csctest)		_userport="11"; _cscserviceport="56090";;
	s.barth)		_userport="12"; _cscserviceport="56093";;
	a.schuh)		_userport="13"; _cscserviceport="56096";;
    m.sagner)       _userport="14"; _cscserviceport="56051";;
    d.gugonatu)     _userport="15"; _cscserviceport="56054";;
    d.florichescu)  _userport="16"; _cscserviceport="56057";;
esac

function install_global_scripts
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/server

	echo "# installing global SCRIPTS to $COUNTRY"	

	# server vars
	cp -f ./environment/server/vars/zdev21/ksc_server_global.vars.$COUNTRY $HOME_KSC_DIR/vars/ksc_server_global.vars
	sed "s#PATH=\$WSS\/$COUNTRY\/ksc#PATH=$HOME\/wss\/$COUNTRY\/ksc#g" $HOME_KSC_DIR/vars/ksc_server_global.vars > $HOME_KSC_DIR/vars/ksc_server_global.vars.neu
	mv $HOME_KSC_DIR/vars/ksc_server_global.vars.neu $HOME_KSC_DIR/vars/ksc_server_global.vars

	# server ini
	cp -f ./pxverbund/files/message.txt $HOME_KSC_DIR/ini/message.txt

	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	# batch vars
	cp -f ./environment/batch/vars/zdev21/ksc_batch_global.vars.$COUNTRY $HOME_KSC_DIR/vars/ksc_batch_global.vars
	sed "s#PATH=\$WSS\/$COUNTRY\/ksc#PATH=$HOME\/wss\/$COUNTRY\/ksc#g" $HOME_KSC_DIR/vars/ksc_batch_global.vars > $HOME_KSC_DIR/vars/ksc_batch_global.vars.neu
	mv $HOME_KSC_DIR/vars/ksc_batch_global.vars.neu $HOME_KSC_DIR/vars/ksc_batch_global.vars

	# batch ini
	cp -f ./pxverbund/files/message.txt $HOME_KSC_DIR/ini/message.txt
}

function install_all_global_scripts
{
	echo "###################################################################"
	echo "# installing global scripts..."
	echo "###################################################################"	

	for country in $COUNTRIES; do
		install_global_scripts $country
	done
	for country in $LINK_COUNTRIES; do
		install_global_scripts $country
	done
}

###############################################################################################
# install kscserver
###############################################################################################

function scripts_kscserver_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/server
	
	echo "# installing kscserver SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f ./environment/server/proc/kscserver.sh $HOME_KSC_DIR/proc/kscserver.sh
	cp -f ./environment/server/proc/kscserver.option $HOME_KSC_DIR/proc/kscserver.option

	# ini directory
	cp -f ./environment/server/ini/zdev21/kscserver.ini.$COUNTRY $HOME_KSC_DIR/ini/kscserver.ini
	cp -f ./environment/server/ini/zdev21/kscserver.cfg $HOME_KSC_DIR/ini/kscserver.cfg
	if [[ $COUNTRY == "bg" ]]; then
		cp -f ./environment/server/ini/zdev21/tcaconfig* $HOME_KSC_DIR/ini
	fi

	# vars directory
	cp -f ./environment/server/vars/zdev21/kscserver.vars.$COUNTRY $HOME_KSC_DIR/vars/kscserver.vars
	sed "s/export PORTNR=\".*\"/export PORTNR=\"ksc${_userport}_server\"/g" $HOME_KSC_DIR/vars/kscserver.vars > $HOME_KSC_DIR/vars/kscserver.vars.neu
	mv $HOME_KSC_DIR/vars/kscserver.vars.neu $HOME_KSC_DIR/vars/kscserver.vars
}

function link_kscserver_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing kscserver LINK to $COUNTRY_ORIG for $COUNTRY"	
	
	rm $HOME/wss/$COUNTRY/ksc/server/bin/kscserver.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/server/bin/kscserver.bin $HOME/wss/$COUNTRY/ksc/server/bin/kscserver.bin
}

function install_kscserver_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/server	

	echo "###################################################################"
	echo "# installing BINARY $TARGET_KSCSERVER to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_KSCSERVER/build/debug/kscserver.bin $HOME_KSC_DIR/bin/kscserver.bin
}

function install_all_kscserver
{
	for country in $COUNTRIES; do
		install_kscserver_country $country
		scripts_kscserver_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_kscserver_country "de" $country
		scripts_kscserver_country $country
	done
}

###############################################################################################
# install aapserv
###############################################################################################

function scripts_aapserv_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/server
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/server	
	
	echo "# installing aapserv SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f ./environment/server/proc/zaapunix.sh $HOME_KSC_DIR/proc/zaapunix.sh
	cp -f ./environment/server/proc/zaapunix.option $HOME_KSC_DIR/proc/zaapunix.option

	# ini directory
	cp -f ./environment/server/ini/zdev21/aasunix.ini.$COUNTRY $HOME_KSC_DIR/ini/aasunix.ini
	cp -f ./environment/server/ini/zdev21/zaapunix.cfg $HOME_KSC_DIR/ini/zaapunix.cfg

	# vars directory
	cp -f ./environment/server/vars/zdev21/zaapunix.vars.$COUNTRY $HOME_KSC_DIR/vars/zaapunix.vars
	sed "s/export PORTNR=\".*\"/export PORTNR=\"aa${_userport}_server3\"/g" $HOME_KSC_DIR/vars/zaapunix.vars > $HOME_KSC_DIR/vars/zaapunix.vars.neu
	mv $HOME_KSC_DIR/vars/zaapunix.vars.neu $HOME_KSC_DIR/vars/zaapunix.vars
}

function link_aapserv_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing aapserv LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/server/bin/zaapunix.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/server/bin/zaapunix.bin $HOME/wss/$COUNTRY/ksc/server/bin/zaapunix.bin
}

function install_aapserv_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/server

	echo "###################################################################"
	echo "# installing BINARY $TARGET_AAPSERV to $HOME_KSC_DIR..."
	echo "###################################################################"	

	cp -f $PROJECT_AAPSERV/build/debug/zaapunix.bin $HOME_KSC_DIR/bin/zaapunix.bin
}

function install_all_aapserv
{
	for country in $COUNTRIES; do
		install_aapserv_country $country
		scripts_aapserv_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_aapserv_country "de" $country
		scripts_aapserv_country $country
	done
}

###############################################################################################
# install cscservice
###############################################################################################

function scripts_cscservice_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/server
	
	echo "# installing cscservice SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f ./environment/server/proc/cscservice.sh $HOME_KSC_DIR/proc/cscservice.sh
	cp -f ./environment/server/proc/cscservice.option $HOME_KSC_DIR/proc/cscservice.option

	# ini directory
	cp -f ./environment/server/ini/zdev21/cscservice.ini.$COUNTRY $HOME_KSC_DIR/ini/cscservice.ini
	sed "s/Port.*=.*/Port               = ${_cscserviceport}/g" $HOME_KSC_DIR/ini/cscservice.ini > $HOME_KSC_DIR/ini/cscservice.ini.neu
	mv $HOME_KSC_DIR/ini/cscservice.ini.neu $HOME_KSC_DIR/ini/cscservice.ini

	cp -f ./environment/server/ini/zdev21/cscservice.cfg $HOME_KSC_DIR/ini/cscservice.cfg

	# vars directory
	cp -f ./environment/server/vars/zdev21/cscservice.vars.$COUNTRY $HOME_KSC_DIR/vars/cscservice.vars
	sed "s/export PORTNR=.*/export PORTNR=${_cscserviceport} /g" $HOME_KSC_DIR/vars/cscservice.vars > $HOME_KSC_DIR/vars/cscservice.vars.neu
	mv $HOME_KSC_DIR/vars/cscservice.vars.neu $HOME_KSC_DIR/vars/cscservice.vars	
}

function link_cscservice_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing cscservice LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/server/bin/cscservice.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/server/bin/cscservice.bin $HOME/wss/$COUNTRY/ksc/server/bin/cscservice.bin	
}

function install_cscservice_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/server

	echo "###################################################################"
	echo "# installing BINARY $TARGET_CSCSERVICE to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_CSCSERVICE/build/debug/cscservice.bin $HOME_KSC_DIR/bin/cscservice.bin
}

function install_all_cscservice
{
	for country in $COUNTRIES; do
		install_cscservice_country $country
		scripts_cscservice_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_cscservice_country "de" $country
		scripts_cscservice_country $country
	done
}


###############################################################################################
# install csc_corpha
###############################################################################################

function scripts_csc_corpha_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch
	SCRIPT_DIR=./csc_host_interface/kscrefresh_scripts
	
	echo "# installing csc_corpha SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f ./environment/batch/proc/csc_corpha.sh $HOME_KSC_DIR/proc/csc_corpha.sh
	cp -f ./environment/batch/proc/csc_corpha.option $HOME_KSC_DIR/proc/csc_corpha.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/csc_corpha.cfg $HOME_KSC_DIR/ini/csc_corpha.cfg
	cp -f $SCRIPT_DIR/ini/zdev21/$COUNTRY/csc_corpha.xml $HOME_KSC_DIR/ini/csc_corpha.xml
	sed "s#/software/wss/#$HOME/wss/#g" $HOME_KSC_DIR/ini/csc_corpha.xml > $HOME_KSC_DIR/ini/csc_corpha.xml.neu && mv $HOME_KSC_DIR/ini/csc_corpha.xml.neu $HOME_KSC_DIR/ini/csc_corpha.xml
	
	# vars directory
	cp -f ./environment/batch/vars/zdev21/csc_corpha.vars $HOME_KSC_DIR/vars/csc_corpha.vars
}

function link_csc_corpha_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing csc_corpha LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/csc_corpha.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/csc_corpha.bin $HOME/wss/$COUNTRY/ksc/batch/bin/csc_corpha.bin
}

function install_csc_corpha_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing BINARY $TARGET_CSC_CORPHA to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_CSC_CORPHA/build/debug/csc_corpha.bin $HOME_KSC_DIR/bin/csc_corpha.bin
}

function install_all_csc_corpha
{
	for country in $COUNTRIES; do
		install_csc_corpha_country $country
		scripts_csc_corpha_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_csc_corpha_country "de" $country
		scripts_csc_corpha_country $country
	done
}

###############################################################################################
# install csc_phatra
###############################################################################################

function scripts_csc_phatra_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch
	SCRIPT_DIR=./csc_host_interface/kscrefresh_scripts
	
	echo "# installing csc_phatra SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SCRIPT_DIR/proc/csc_phatra.sh $HOME_KSC_DIR/proc/csc_phatra.sh
	cp -f $SCRIPT_DIR/proc/csc_phatra.option $HOME_KSC_DIR/proc/csc_phatra.option

	# ini directory
	cp -f $SCRIPT_DIR/ini/csc_phatra.cfg $HOME_KSC_DIR/ini/csc_phatra.cfg
	cp -f $SCRIPT_DIR/ini/zdev21/$COUNTRY/csc_phatra.xml $HOME_KSC_DIR/ini/csc_phatra.xml
	sed "s#/software/wss/#$HOME/wss/#g" $HOME_KSC_DIR/ini/csc_phatra.xml > $HOME_KSC_DIR/ini/csc_phatra.xml.neu && mv $HOME_KSC_DIR/ini/csc_phatra.xml.neu $HOME_KSC_DIR/ini/csc_phatra.xml
	
	# vars directory
	cp -f $SCRIPT_DIR/vars/csc_phatra.vars $HOME_KSC_DIR/vars/csc_phatra.vars
}

function link_csc_phatra_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing csc_phatra LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/csc_phatra.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/csc_phatra.bin $HOME/wss/$COUNTRY/ksc/batch/bin/csc_phatra.bin
}

function install_csc_phatra_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing BINARY $TARGET_CSC_PHATRA to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_CSC_PHATRA/build/debug/csc_phatra.bin $HOME_KSC_DIR/bin/csc_phatra.bin
}

function install_all_csc_phatra
{
	for country in $COUNTRIES; do
		install_csc_phatra_country $country
		scripts_csc_phatra_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_csc_phatra_country "de" $country
		scripts_csc_phatra_country $country
	done
}

###############################################################################################
# install csc_phadex
###############################################################################################

function scripts_csc_phadex_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch
	SCRIPT_DIR=./csc_host_interface/kscrefresh_scripts
	
	echo "# installing csc_phadex SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SCRIPT_DIR/proc/csc_phadex.sh $HOME_KSC_DIR/proc/csc_phadex.sh
	cp -f $SCRIPT_DIR/proc/csc_phadex.option $HOME_KSC_DIR/proc/csc_phadex.option

	# ini directory
	cp -f $SCRIPT_DIR/ini/csc_phadex.cfg $HOME_KSC_DIR/ini/csc_phadex.cfg
	cp -f $SCRIPT_DIR/ini/zdev21/$COUNTRY/csc_phadex.xml $HOME_KSC_DIR/ini/csc_phadex.xml
	sed "s#/software/wss/#$HOME/wss/#g" $HOME_KSC_DIR/ini/csc_phadex.xml > $HOME_KSC_DIR/ini/csc_phadex.xml.neu && mv $HOME_KSC_DIR/ini/csc_phadex.xml.neu $HOME_KSC_DIR/ini/csc_phadex.xml
	
	# vars directory
	cp -f $SCRIPT_DIR/vars/csc_phadex.vars $HOME_KSC_DIR/vars/csc_phadex.vars
}

function link_csc_phadex_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing csc_phadex LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/csc_phadex.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/csc_phadex.bin $HOME/wss/$COUNTRY/ksc/batch/bin/csc_phadex.bin
}

function install_csc_phadex_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing BINARY $TARGET_CSC_PHADEX to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_CSC_PHADEX/build/debug/csc_phadex.bin $HOME_KSC_DIR/bin/csc_phadex.bin
}

function install_all_csc_phadex
{
	for country in $COUNTRIES; do
		install_csc_phadex_country $country
		scripts_csc_phadex_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_csc_phadex_country "de" $country
		scripts_csc_phadex_country $country
	done
}

###############################################################################################
# install csc_phabor
###############################################################################################

function scripts_csc_phabor_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch
	SCRIPT_DIR=./csc_host_interface/kscrefresh_scripts
	
	echo "# installing csc_phabor SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $SCRIPT_DIR/proc/csc_phabor.sh $HOME_KSC_DIR/proc/csc_phabor.sh
	cp -f $SCRIPT_DIR/proc/csc_phabor.option $HOME_KSC_DIR/proc/csc_phabor.option

	# ini directory
	cp -f $SCRIPT_DIR/ini/csc_phabor.cfg $HOME_KSC_DIR/ini/csc_phabor.cfg
	cp -f $SCRIPT_DIR/ini/zdev21/$COUNTRY/csc_phabor.xml $HOME_KSC_DIR/ini/csc_phabor.xml
	sed "s#/software/wss/#$HOME/wss/#g" $HOME_KSC_DIR/ini/csc_phabor.xml > $HOME_KSC_DIR/ini/csc_phabor.xml.neu && mv $HOME_KSC_DIR/ini/csc_phabor.xml.neu $HOME_KSC_DIR/ini/csc_phabor.xml
	
	# vars directory
	cp -f $SCRIPT_DIR/vars/csc_phabor.vars $HOME_KSC_DIR/vars/csc_phabor.vars
}

function link_csc_phabor_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing csc_phabor LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/csc_phabor.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/csc_phabor.bin $HOME/wss/$COUNTRY/ksc/batch/bin/csc_phabor.bin
}

function install_csc_phabor_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing BINARY $TARGET_CSC_PHABOR to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_CSC_PHABOR/build/debug/csc_phabor.bin $HOME_KSC_DIR/bin/csc_phabor.bin
}

function install_all_csc_phabor
{
	for country in $COUNTRIES; do
		install_csc_phabor_country $country
		scripts_csc_phabor_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_csc_phabor_country "de" $country
		scripts_csc_phabor_country $country
	done
}

###############################################################################################
# install aaorderclose
###############################################################################################

function scripts_aaorderclose_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "# installing aaorderclose SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f ./environment/batch/proc/aaordclose.sh $HOME_KSC_DIR/proc/aaordclose.sh
	cp -f ./environment/batch/proc/aaordclose.option $HOME_KSC_DIR/proc/aaordclose.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/aaorderclose.R.cfg $HOME_KSC_DIR/ini/aaorderclose.R.cfg
	cp -f ./environment/batch/ini/zdev21/aaordclose.ini.$COUNTRY $HOME_KSC_DIR/ini/aaordclose.ini
}

function link_aaorderclose_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing aaorderclose LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/aaorderclose.R.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/aaorderclose.R.bin $HOME/wss/$COUNTRY/ksc/batch/bin/aaorderclose.R.bin
}

function install_aaorderclose_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing BINARY $TARGET_AAORDERCLOSE to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_AAORDERCLOSE/build/debug/aaorderclose.R.bin $HOME_KSC_DIR/bin/aaorderclose.R.bin
}

function install_all_aaorderclose
{
	for country in $COUNTRIES; do
		install_aaorderclose_country $country
		scripts_aaorderclose_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_aaorderclose_country "de" $country
		scripts_aaorderclose_country $country
	done
}

###############################################################################################
# install csc_deli
###############################################################################################

function scripts_csc_deli_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "# installing csc_deli SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $PROJECT_CSC_DELI/proc/csc_deli.sh $HOME_KSC_DIR/proc/csc_deli.sh
	cp -f $PROJECT_CSC_DELI/proc/csc_deli.option $HOME_KSC_DIR/proc/csc_deli.option

	# ini directory
	cp -f $PROJECT_CSC_DELI/ini/csc_deli.cfg $HOME_KSC_DIR/ini/csc_deli.cfg
}

function link_csc_deli_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing csc_deli LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/csc_deli.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/csc_deli.bin $HOME/wss/$COUNTRY/ksc/batch/bin/csc_deli.bin
}

function install_csc_deli_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing BINARY $TARGET_CSC_DELI to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_CSC_DELI/csc_deli/build/debug/csc_deli.bin $HOME_KSC_DIR/bin/csc_deli.bin
}

function install_all_csc_deli
{
	for country in $COUNTRIES; do
		install_csc_deli_country $country
		scripts_csc_deli_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_csc_deli_country "de" $country
		scripts_csc_deli_country $country
	done
}

###############################################################################################
# install ibtorderimport
###############################################################################################

function scripts_ibtorderimport_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "# installing ibtorderimport SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f ./environment/batch/proc/ibtorderimport.sh $HOME_KSC_DIR/proc/ibtorderimport.sh
	cp -f ./environment/batch/proc/ibtorderimport.option $HOME_KSC_DIR/proc/ibtorderimport.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/ibtorderimport.cfg $HOME_KSC_DIR/ini/ibtorderimport.cfg
}

function link_ibtorderimport_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing ibtorderimport LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/ibtorderimport.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/ibtorderimport.bin $HOME/wss/$COUNTRY/ksc/batch/bin/ibtorderimport.bin
}

function install_ibtorderimport_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing BINARY $TARGET_IBTORDERIMPORT to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_IBTORDERIMPORT/build/debug/ibtorderimport.bin $HOME_KSC_DIR/bin/ibtorderimport.bin
}

function install_all_ibtorderimport
{
	for country in $COUNTRIES; do
		install_ibtorderimport_country $country
		scripts_ibtorderimport_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_ibtorderimport_country "de" $country
		scripts_ibtorderimport_country $country
	done
}

###############################################################################################
# install vborderimport2
###############################################################################################

function scripts_vborderimport2_country
{
	COUNTRY=$1
	GLOBAL_KSC_DIR=$WSS/$COUNTRY/ksc/batch
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch
	
	echo "# installing vborderimport2 SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f $PROJECT_VBORDERIMPORT2/proc/vbordimport2.sh $HOME_KSC_DIR/proc/vbordimport2.sh
	cp -f $PROJECT_VBORDERIMPORT2/proc/vbordimport2.option $HOME_KSC_DIR/proc/vbordimport2.option

	# ini directory
	cp -f $GLOBAL_KSC_DIR/ini/vbordimport??.ini $HOME_KSC_DIR/ini
	cp -f $PROJECT_VBORDERIMPORT2/ini/vborderimport2.cfg $HOME_KSC_DIR/ini/vborderimport2.cfg
}

function link_vborderimport2_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing vborderimport2 LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/vborderimport2.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/vborderimport2.bin $HOME/wss/$COUNTRY/ksc/batch/bin/vborderimport2.bin
}

function install_vborderimport2_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing BINARY $TARGET_VBORDERIMPORT2 to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_VBORDERIMPORT2/build/debug/vborderimport2.bin $HOME_KSC_DIR/bin/vborderimport2.bin
}

function install_all_vborderimport2
{
	install_vborderimport2_country "fr"
	link_vborderimport2_country "fr" "pfr"
	scripts_vborderimport2_country "fr"
	scripts_vborderimport2_country "pfr"
}

###############################################################################################
# install clearreservation
###############################################################################################

function scripts_clearreservation_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "# installing clearreservation SCRIPTS to $COUNTRY"	
	
	# proc directory
	cp -f ./environment/batch/proc/clearreservation.sh $HOME_KSC_DIR/proc/clearreservation.sh
	cp -f ./environment/batch/proc/clearreservation.option $HOME_KSC_DIR/proc/clearreservation.option

	# ini directory
	cp -f ./environment/batch/ini/zdev21/clearreservation.ini.$COUNTRY $HOME_KSC_DIR/ini/clearreservation.ini
	cp -f ./environment/batch/ini/zdev21/clearreservation.cfg $HOME_KSC_DIR/ini/clearreservation.cfg
}

function link_clearreservation_country
{
	COUNTRY_ORIG=$1
	COUNTRY=$2
	
	echo "# installing clearreservation LINK to $COUNTRY_ORIG for $COUNTRY"
	
	rm $HOME/wss/$COUNTRY/ksc/batch/bin/clearreservation.bin
	ln -s $HOME/wss/$COUNTRY_ORIG/ksc/batch/bin/clearreservation.bin $HOME/wss/$COUNTRY/ksc/batch/bin/clearreservation.bin
}

function install_clearreservation_country
{
	COUNTRY=$1
	HOME_KSC_DIR=$HOME/wss/$COUNTRY/ksc/batch

	echo "###################################################################"
	echo "# installing $TARGET_CLEARRESERVATION to $HOME_KSC_DIR..."
	echo "###################################################################"	

	# bin directory
	cp -f $PROJECT_CLEARRESERVATION/build/debug/clearreservation.bin $HOME_KSC_DIR/bin/clearreservation.bin
}

function install_all_clearreservation
{
	for country in $COUNTRIES; do
		install_clearreservation_country $country
		scripts_clearreservation_country $country
	done
	for country in $LINK_COUNTRIES; do
		link_clearreservation_country "de" $country
		scripts_clearreservation_country $country
	done
}

###############################################################################################
# install to $HOME/wss
###############################################################################################

if [[ $# == 1 ]]; then
	echo "hi" $1
else
	create_all_dirs
	install_all_global_scripts
	install_all_cscservice
	install_all_kscserver
	install_all_aapserv
	install_all_aaorderclose
	install_all_ibtorderimport	
#	install_all_vborderimport2	
	install_all_clearreservation
#	install_all_csc_deli
	install_all_csc_corpha
#	install_all_csc_phatra
#	install_all_csc_phadex
#	install_all_csc_phabor
fi
