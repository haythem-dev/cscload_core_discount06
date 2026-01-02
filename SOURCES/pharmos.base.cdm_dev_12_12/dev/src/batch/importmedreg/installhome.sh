#!/usr/bin/sh
# set -x
###############################################################################################
# installs application to $WSS
###############################################################################################

# targets
TARGET_IMPORTMEDREG=importmedreg

# subtargets
PROJECT_IMPORTMEDREG=./


function install_importmedreg_ch
{
	GLOBAL_IMPORTMEDREG_DIR=$HOME/wss/ch/cdm/ws
	ARCHIVE_DIR=$HOME/wss/ch/cdm/ws/data/medreg/archive
	BIN_DIR=$HOME/wss/ch/cdm/ws/bin
	PROC_DIR=$HOME/wss/ch/cdm/ws/proc
	INI_DIR=$HOME/wss/ch/cdm/ws/ini
	LOG_DIR=$HOME/wss/ch/cdm/ws/log
	VARS_DIR=$HOME/wss/ch/cdm/ws/vars

	mkdir -p ${GLOBAL_IMPORTMEDREG_DIR} ${BIN_DIR} ${PROC_DIR} ${INI_DIR} ${VARS_DIR} ${ARCHIVE_DIR} ${LOG_DIR} 2> /dev/null

	echo "###################################################################"
	echo "# installing $TARGET_IMPORTMEDREG to $GLOBAL_IMPORTMEDREG_DIR..."
	echo "###################################################################"
	echo

	# bin directory
	cp -f $PROJECT_IMPORTMEDREG/build/release/importmedreg.bin $GLOBAL_IMPORTMEDREG_DIR/bin/importmedreg.bin

	# proc directory
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_web.sh $GLOBAL_IMPORTMEDREG_DIR/proc/importmedreg_web.sh
        cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_mail_tst.sh $GLOBAL_IMPORTMEDREG_DIR/proc/importmedreg_mail_tst.sh
        cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_mail_acc.sh $GLOBAL_IMPORTMEDREG_DIR/proc/importmedreg_mail_acc.sh
        cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_mail_prd.sh $GLOBAL_IMPORTMEDREG_DIR/proc/importmedreg_mail_prd.sh
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_key.sh $GLOBAL_IMPORTMEDREG_DIR/proc/importmedreg_key.sh
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg.option $GLOBAL_IMPORTMEDREG_DIR/proc/importmedreg.option


	# vars directory
	cp -f $PROJECT_IMPORTMEDREG/unix/cdm_ws_global.vars $GLOBAL_IMPORTMEDREG_DIR/vars/cdm_ws_global.vars
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_web_tst.vars $GLOBAL_IMPORTMEDREG_DIR/vars/importmedreg_web_tst.vars
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_web_acc.vars $GLOBAL_IMPORTMEDREG_DIR/vars/importmedreg_web_acc.vars
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_web_prd.vars $GLOBAL_IMPORTMEDREG_DIR/vars/importmedreg_web_prd.vars
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_key_tst.vars $GLOBAL_IMPORTMEDREG_DIR/vars/importmedreg_key_tst.vars
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_key_acc.vars $GLOBAL_IMPORTMEDREG_DIR/vars/importmedreg_key_acc.vars
	cp -f $PROJECT_IMPORTMEDREG/unix/importmedreg_key_prd.vars $GLOBAL_IMPORTMEDREG_DIR/vars/importmedreg_key_prd.vars
	
	# ini directory
	cp -f $PROJECT_IMPORTMEDREG/ini/importmedreg_log.cfg $GLOBAL_IMPORTMEDREG_DIR/ini/importmedreg_log.cfg
	cp -f $PROJECT_IMPORTMEDREG/ini/importmedreg_properties_tst.cfg $GLOBAL_IMPORTMEDREG_DIR/ini/importmedreg_properties_tst.cfg
	cp -f $PROJECT_IMPORTMEDREG/ini/importmedreg_properties_acc.cfg $GLOBAL_IMPORTMEDREG_DIR/ini/importmedreg_properties_acc.cfg
	cp -f $PROJECT_IMPORTMEDREG/ini/importmedreg_properties_prd.cfg $GLOBAL_IMPORTMEDREG_DIR/ini/importmedreg_properties_prd.cfg
	cp -f $PROJECT_IMPORTMEDREG/ini/importmedreg_token_tst.csv $GLOBAL_IMPORTMEDREG_DIR/ini/importmedreg_token_tst.csv
	cp -f $PROJECT_IMPORTMEDREG/ini/importmedreg_token_acc.csv $GLOBAL_IMPORTMEDREG_DIR/ini/importmedreg_token_acc.csv
	cp -f $PROJECT_IMPORTMEDREG/ini/importmedreg_token_prd.csv $GLOBAL_IMPORTMEDREG_DIR/ini/importmedreg_token_prd.csv
}

###############################################################################################
# install to $WSS
###############################################################################################

install_importmedreg_ch