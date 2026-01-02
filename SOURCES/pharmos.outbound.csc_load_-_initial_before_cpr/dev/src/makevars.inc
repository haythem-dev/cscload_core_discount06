#================================================================================
#   common libs and headers
#================================================================================

#--------------------------------------------------------------------------------
#   base directories
#--------------------------------------------------------------------------------

### marathon base directory
MARATHON_DIR          = $(DEVLIB_PATH)/marathon

### informix base directory
INFORMIX_DIR          = $(INFORMIXDIR)

BASE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

EXT_DIR := $(abspath $(BASE_DIR)../ext)

#--------------------------------------------------------------------------------
#   library directories
#--------------------------------------------------------------------------------
SSUK_DIR              = $(EXT_DIR)/ssuk
BASAR_DIR             = $(SSUK_DIR)/basar

BOOST_DIR             = $(EXT_DIR)/boost
LOG4CPLUS_DIR         = $(EXT_DIR)/log4cplus
QT_DIR                = $(EXT_DIR)/qt5
LIBUTIL_DIR           = $(EXT_DIR)/libutil
HDATUM_DIR            = $(EXT_DIR)/hdatum
LIBCALLPLAN_DIR       = $(EXT_DIR)/libcallplan
LIBTPLD_DIR           = $(EXT_DIR)/libtpld
PPUNIXC_DIR           = $(EXT_DIR)/pplib

#--------------------------------------------------------------------------------
#   include directories
#--------------------------------------------------------------------------------
BASAR_INC             = -I$(BASAR_DIR)/include
BOOST_INC             = -I$(BOOST_DIR)/include
LOG4CPLUS_INC         = -I$(LOG4CPLUS_DIR)/include
QT_INC                = -I$(QT_DIR)/include
QT_CORE_INC           = -I$(QT_DIR)/include/QtCore
LIBUTIL_INC           = -I$(LIBUTIL_DIR)/include

HDATUM_INC            = -I$(HDATUM_DIR)/include
LIBCALLPLAN_INC       = -I$(LIBCALLPLAN_DIR)/include
LIBTPLD_INC           = -I$(LIBTPLD_DIR)/include
PPUNIXC_INC           = -I$(PPUNIXC_DIR)/include

#--------------------------------------------------------------------------------
#   static libraries
#--------------------------------------------------------------------------------
LIBUTIL_LIB           = $(LIBUTIL_DIR)/lib/$(CONFVER)/libutil.a
HDATUM_LIB            = $(HDATUM_DIR)/lib/$(CONFVER)/hdatum.a
LIBCALLPLAN           = $(LIBCALLPLAN_DIR)/lib/$(CONFVER)/libcallplan.a
LIBTPLD               = $(LIBTPLD_DIR)/lib/$(CONFVER)/libtpld.a
PPUNIXC_LIB           = $(PPUNIXC_DIR)/lib/$(CONFVER)/ppunixc.a
LIBVERSION            = ../common/build/$(CONFVER)/libversion.a
ESQL_CHECKAPI_LIB     = $(INFORMIX_ESQL_LIB_DIR)/checkapi.o


#--------------------------------------------------------------------------------
#   shared libraries
#--------------------------------------------------------------------------------
### directories for library paths

BASAR_LIB_DIR         = $(SSUK_DIR)/sharedlib/$(CONFVER)
QT_LIB_DIR            = $(QT_DIR)/lib
LOG4CPLUS_LIB_DIR     = $(LOG4CPLUS_DIR)/lib/$(CONFVER)
BOOST_LIB_DIR         = $(BOOST_DIR)/lib

INFORMIX_LIB_DIR      = $(INFORMIX_DIR)/lib
INFORMIX_ESQL_LIB_DIR = $(INFORMIX_LIB_DIR)/esql

### shared libs
INFORMIX_SHARED_LIBS  = -L$(INFORMIX_LIB_DIR) -L$(INFORMIX_ESQL_LIB_DIR) \
                        -lifsql -lifasf -lifgen -lifos -lifgls -lifglx

### shared libs
BASAR_SHARED_LIBS     = -L$(BASAR_LIB_DIR) -lbasardebug -lbasarcmnutil \
                        -lbasarproperty  -lbasardbsql -lbasardbaspect \
                        -lbasarlogin -lbasarappl

QT_CORE_SHARED_LIBS   = -L$(QT_LIB_DIR) -lQt5Core

LOG4CPLUS_SHARED_LIBS = -L$(LOG4CPLUS_LIB_DIR) -llog4cplus

BOOST_SYSTEM_SHARED_LIBS  = -L$(BOOST_LIB_DIR) -lboost_system

# modeline - do not remove
# vim: ff=unix ts=4 sw=4 noexpandtab syntax=make
