#================================================================================
#   common libs and headers
#================================================================================
$(info Including main makevars.inc)

#--------------------------------------------------------------------------------
#   base directories
#--------------------------------------------------------------------------------

### base directories
MARATHON_DIR          = $(DEVLIB_PATH)/marathon
BASE_DIR              := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
EXT_DIR               = $(BASE_DIR)../ext

### informix base directory
INFORMIX_DIR          = $(INFORMIXDIR)

#--------------------------------------------------------------------------------
#   library versions
#--------------------------------------------------------------------------------
TCACCESS_VERSION      = 8.0.11.4

#--------------------------------------------------------------------------------
#   library directories
#--------------------------------------------------------------------------------
CXXTOOLS_DIR          = $(BASE_DIR)cxxtools
PXDB_DIR              = $(BASE_DIR)pxdb
PXVERBUND_DIR         = $(BASE_DIR)pxverbund
LIBCSC_DIR            = $(BASE_DIR)libcsc
LIBBATCH_DIR          = $(BASE_DIR)csc_host_interface/libbatch
LIBCSC_UTILS_DIR      = $(BASE_DIR)csc_host_interface/libcsc_utils
LIBCSC_DELI_DIR       = $(BASE_DIR)csc_deli/libcsc_deli/


SSUK_DIR              = $(EXT_DIR)/ssuk
BASAR_DIR             = $(SSUK_DIR)/basar
BOOST_DIR             = $(SSUK_DIR)
LOG4CPLUS_DIR         = $(SSUK_DIR)/log4cplus
QT_DIR                = $(SSUK_DIR)/qt

LIBUTIL_DIR           = $(EXT_DIR)/libutil
HDATUM_DIR            = $(EXT_DIR)/hdatum
LIBLOCKMANAGER_DIR    = $(EXT_DIR)/liblockmanager
PPUNIXC_DIR           = $(EXT_DIR)/pplib
TCACCESS_DIR          = $(MARATHON_DIR)/lib/tcaccess/$(TCACCESS_VERSION)
THRIFT_DIR            = $(EXT_DIR)/thrift_vs2010
UNITTESTPP_DIR        = $(EXT_DIR)/unittestpp

#--------------------------------------------------------------------------------
#   include directories
#--------------------------------------------------------------------------------
BASAR_INC             = -I$(BASAR_DIR)/include
BOOST_INC             = -I$(BOOST_DIR)
CXXTOOLS_INC          = -I$(CXXTOOLS_DIR)/include
HDATUM_INC            = -I$(HDATUM_DIR)/include
INFORMIX_INC          = -I$(INFORMIX_DIR)/incl/esql
LIBBATCH_INC          = -I$(LIBBATCH_DIR)
LIBCSC_INC            = -I$(LIBCSC_DIR)
LIBCSC_UTILS_INC      = -I$(LIBCSC_UTILS_DIR)
LIBCSC_DELI_INC       = -I$(LIBCSC_DELI_DIR)
LIBLOCKMANAGER_INC    = -I$(LIBLOCKMANAGER_DIR)/include -I$(LIBLOCKMANAGER_DIR)/include/liblockmanager
LIBTPLD_INC           = -I$(LIBTPLD_DIR)/include
LOG4CPLUS_INC         = -I$(LOG4CPLUS_DIR)/include
PPUNIXC_INC           = -I$(PPUNIXC_DIR)/include
PXDB_INC              = -I$(PXDB_DIR)/include
PXVERBUND_INC         = -I$(PXVERBUND_DIR) -I$(PXVERBUND_DIR)/include
QT_INC                = -I$(QT_DIR)/include
QT_CORE_INC           = -I$(QT_DIR)/include/QtCore
QT_XML_INC            = -I$(QT_DIR)/include/QtXml
TCACCESS_INC          = -I$(TCACCESS_DIR)/include
LIBUTIL_INC           = -I$(LIBUTIL_DIR)/include
THRIFT_INC            = -I$(THRIFT_DIR)/include
UNITTESTPP_INC        = -I$(UNITTESTPP_DIR)/include

#--------------------------------------------------------------------------------
#   static libraries
#--------------------------------------------------------------------------------
### others mostly local libraries
LIBBATCH              = $(LIBBATCH_DIR)/build/$(CONFVER)/libbatch.a
LIBCSC                = $(LIBCSC_DIR)/build/$(CONFVER)/libcsc.a
LIBCSC_UTILS          = $(LIBCSC_UTILS_DIR)/build/$(CONFVER)/libcsc_utils.a
LIBCSC_DELI           = $(LIBCSC_DELI_DIR)/build/$(CONFVER)/libcsc_deli.a

### global libraries
CXXTOOLS_LIB          = $(CXXTOOLS_DIR)/build/$(CONFVER)/cxxtools.a
HDATUM_LIB            = $(HDATUM_DIR)/lib/$(CONFVER)/hdatum.a
LIBCALLPLAN           = $(LIBCALLPLAN_DIR)/lib/$(CONFVER)/libcallplan.a
LIBLOCKMANAGER        = $(LIBLOCKMANAGER_DIR)/lib/$(CONFVER)/liblockmanager.a
LIBTPLD               = $(LIBTPLD_DIR)/lib/$(CONFVER)/libtpld.a
PPUNIXC_LIB           = $(PPUNIXC_DIR)/lib/$(CONFVER)/ppunixc.a -liconv
PXDB_LIB              = $(PXDB_DIR)/build/$(CONFVER)/libpxdb.a
PXVERBUND_LIB         = $(PXVERBUND_DIR)/build/$(CONFVER)/libpxverbund.a
LIBUTIL_LIB           = $(LIBUTIL_DIR)/lib/$(CONFVER)/libutil.a
UNITTESTPP_LIB        = $(UNITTESTPP_DIR)/lib/$(CONFVER)/libUnitTest++.a

### ESQL libraries
ESQL_CHECKAPI_LIB     = $(INFORMIX_ESQL_LIB_DIR)/checkapi.o

#--------------------------------------------------------------------------------
#   shared libraries
#--------------------------------------------------------------------------------
### directories for library paths

BASAR_LIB_DIR         = $(SSUK_DIR)/sharedlib/$(CONFVER)
TCACCESS_LIB_DIR      = $(TCACCESS_DIR)/lib
LOG4CPLUS_LIB_DIR     = $(SSUK_DIR)/sharedlib/$(CONFVER)
BOOST_LIB_DIR         = $(SSUK_DIR)/sharedlib/$(CONFVER)
QT_LIB_DIR            = $(SSUK_DIR)/sharedlib/$(CONFVER)

INFORMIX_LIB_DIR      = $(INFORMIX_DIR)/lib
INFORMIX_ESQL_LIB_DIR = $(INFORMIX_LIB_DIR)/esql

VOODOO_LIB_DIR        = $(VOODOO_DIR)/lib/$(CONFVER)
THRIFT_LIB_DIR        = $(THRIFT_DIR)/lib

### shared libs
BASAR_SHARED_LIBS     = -L$(BASAR_LIB_DIR) -lbasardebug -lbasarcmnutil \
                        -lbasarproperty  -lbasardbsql -lbasardbaspect \
                        -lbasarlogin -lbasarappl

BASAR_LIBS_SQL_CMNUTIL	= -L$(BASAR_LIB_DIR) $(LOG4CPLUS_SHARED_LIBS) $(BOOST_FS_SHARED_LIBS) \
                        -lbasarcmnutil -lbasardbsql -lpthread -pthread $(TCACCESS_SHARED_LIBS)

LOG4CPLUS_SHARED_LIBS = -L$(LOG4CPLUS_LIB_DIR) -llog4cplus

BOOST_LOC_SHARED_LIBS = -L$(BOOST_LIB_DIR) -lboost_locale
BOOST_REGEX_SHARED_LIBS= -L$(BOOST_LIB_DIR) -lboost_regex
BOOST_PO_SHARED_LIBS  = -L$(BOOST_LIB_DIR) -lboost_program_options
BOOST_FS_SHARED_LIBS  = -L$(BOOST_LIB_DIR) -lboost_system -lboost_filesystem

QT_CORE_SHARED_LIBS   = -L$(QT_LIB_DIR) -lQt5Core
QT_XML_SHARED_LIBS    = -L$(QT_LIB_DIR) -lQt5Xml

TCACCESS_SHARED_LIBS  = -L$(TCACCESS_LIB_DIR) \
                        -lComHd -lChTN3270 -lChTcpIp -lSpecMap \
                        -lBml -lbmlApi -lBmlCh -lBmlUtils

BASAR_PROJECT_LIBS    = $(LOG4CPLUS_SHARED_LIBS) $(BOOST_FS_SHARED_LIBS) \
                        $(BASAR_SHARED_LIBS) -lpthread -pthread \
                        $(TCACCESS_SHARED_LIBS)

INFORMIX_SHARED_LIBS  = -L$(INFORMIX_LIB_DIR) -L$(INFORMIX_ESQL_LIB_DIR) \
                        -lifsql -lifasf -lifgen -lifos -lifgls -lifglx

SOCKET_SHARED_LIBS    = -lnsl

VOODOO_SHARED_LIBS    = -L$(VOODOO_LIB_DIR) -lscsvoodoo

THRIFT_SHARED_LIBS    = -L$(THRIFT_LIB_DIR) -lthrift

#--------------------------------------------------------------------------------
#   tool variables
#--------------------------------------------------------------------------------

THRIFT                = $(THRIFT_DIR)/bin/thrift


# modeline - do not remove
# vim: ff=unix ts=4 sw=4 noexpandtab syntax=make
