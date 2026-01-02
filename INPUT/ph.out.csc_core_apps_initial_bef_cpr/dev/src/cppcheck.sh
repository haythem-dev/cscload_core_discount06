#!/usr/bin/sh

### base directories
MARATHON_DIR=$DEVLIB_PATH/marathon
BASE_DIR=.
EXT_DIR=$BASE_DIR/../ext

### informix base directory
INFORMIX_DIR=$INFORMIXDIR

#--------------------------------------------------------------------------------
#   library versions
#--------------------------------------------------------------------------------
TCACCESS_VERSION=8.0.11.4

#--------------------------------------------------------------------------------
#   library directories
#--------------------------------------------------------------------------------
CXXTOOLS_DIR=$BASE_DIR/cxxtools
PXDB_DIR=$BASE_DIR/pxdb
PXVERBUND_DIR=$BASE_DIR/pxverbund
LIBCSC_DIR=$BASE_DIR/libcsc
#LIBBATCH_DIR          = $BASE_DIR/csc_host_interface/libbatch
#LIBCSC_UTILS_DIR      = $BASE_DIR/csc_host_interface/libcsc_utils
#LIBCSC_DELI_DIR       = $BASE_DIR/csc_deli/libcsc_deli/


SSUK_DIR=$EXT_DIR/ssuk
BASAR_DIR=$SSUK_DIR/basar
BOOST_DIR=$SSUK_DIR
LOG4CPLUS_DIR=$SSUK_DIR/log4cplus
QT_DIR=$SSUK_DIR/qt

#LIBUTIL_DIR           = $EXT_DIR/libutil
#HDATUM_DIR            = $EXT_DIR/hdatum
LIBLOCKMANAGER_DIR=$EXT_DIR/liblockmanager
#PPUNIXC_DIR           = $EXT_DIR/pplib
TCACCESS_DIR=$MARATHON_DIR/lib/tcaccess/$TCACCESS_VERSION
THRIFT_DIR=$EXT_DIR/thrift_vs2010

#--------------------------------------------------------------------------------
#   include directories
#--------------------------------------------------------------------------------
BASAR_INC=-I$BASAR_DIR/include
BOOST_INC=-I$BOOST_DIR
CXXTOOLS_INC=-I$CXXTOOLS_DIR/include
#HDATUM_INC            = -I$(HDATUM_DIR)/include
INFORMIX_INC=-I$INFORMIX_DIR/incl/esql
#LIBBATCH_INC          = -I$(LIBBATCH_DIR)
LIBCSC_INC=-I$LIBCSC_DIR
#LIBCSC_UTILS_INC      = -I$(LIBCSC_UTILS_DIR)
#LIBCSC_DELI_INC       = -I$(LIBCSC_DELI_DIR)
LIBLOCKMANAGER_INC="-I${LIBLOCKMANAGER_DIR}/include -I${LIBLOCKMANAGER_DIR}/include/liblockmanager"
LOG4CPLUS_INC=-I$LOG4CPLUS_DIR/include
#PPUNIXC_INC           = -I$(PPUNIXC_DIR)/include
PXDB_INC=-I$PXDB_DIR/include
PXVERBUND_INC="-I$PXVERBUND_DIR/include -I$PXVERBUND_DIR/tcawrap"
#QT_INC                = -I$QT_DIR/include
#QT_CORE_INC           = -I$QT_DIR/include/QtCore
#QT_XML_INC            = -I$QT_DIR/include/QtXml
TCACCESS_INC=-I$TCACCESS_DIR/include
LIBUTIL_INC=-I$LIBUTIL_DIR/include
THRIFT_INC=-I$THRIFT_DIR/include

#style,performance,portability,information,unusedFunction,missingInclude
#	--check-config \

cppcheck \
	--enable=warning,style,performance,portability,information,missingInclude \
	--quiet \
	--platform=unix64 \
	--template='{file}:{line}:{severity},{id}: {message}' \
	-Dunix \
	--suppress=missingIncludeSystem \
	--suppress=preprocessorErrorDirective \
	--suppress=cstyleCast \
	--suppress=*:../ext/ssuk/boost/* \
	--suppress=*:thrift/build/* \
	--suppress=*:thrift/gen-cpp/* \
	--error-exitcode=1 \
	-j 40 \
	$CXXTOOLS_INC \
	$PXDB_INC \
	$PXVERBUND_INC \
	$LIBCSC_INC \
	$LIBLOCKMANAGER_INC \
	$BASAR_INC \
	$LOG4CPLUS_INC \
	$BOOST_INC \
	$INFORMIX_INC \
	$TCACCESS_INC \
	cxxtools \
	pxverbund \
	aaorderclose \
	clearreservation \
	csc_host_interface/libbatch \
	csc_host_interface/libcsc_utils \
	thrift 2>&1

#	pxdb \
#	libcsc

echo retval $?




#	pxdb \
#	libumk \
#	thrift \
#	aaorderclose \
#	aapserv \
#	clearreservation \
#	kscserver \
#	vborderimport2 \
#	csc_host_interface \
#	csc_deli \
#	umk \
#	ibtorderimport

