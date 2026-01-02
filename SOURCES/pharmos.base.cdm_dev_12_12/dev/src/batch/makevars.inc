#================================================================================
#   common libs and headers
#================================================================================
$(info Including main makevars.inc)


#-------------------------------------------------------------
# externals 
#-------------------------------------------------------------

COMMON_RULES_DIR   = $(DEVLIB_PATH)/marathon/make
INCLUDE_FILE       = $(COMMON_RULES_DIR)/makefile.inc
#VOODOO_HEADER_DIR  = ../../ext/voodoo_table_header

BASE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

EXT_DIR            = $(BASE_DIR)../../ext

##############################################
####### AIX ##################################
##############################################
TCACCESS_VERSION   = 8.0.11.4
LIBS_SYSTEM        = -lz
##############################################

VOODOO_HEADER_DIR  = $(EXT_DIR)/voodoo_table_header

EKLIBS_DIR         = $(EXT_DIR)/eklibs
LIBS_EKLIBS_DIR    = $(EKLIBS_DIR)/lib/$(CONFIG)

HDATUM_DIR         = $(EXT_DIR)/hdatum
LIBS_HDATUM_DIR    = $(HDATUM_DIR)/lib/$(CONFIG)

SERVCLNT_DIR       = $(EXT_DIR)/servclnt
LIBS_SERVCLNT_DIR  = $(SERVCLNT_DIR)/lib/$(CONFIG)

LIBS_INFX_ESQL_DIR = $(INFORMIXDIR)/lib/esql
LIBS_INFX_DIR      = $(INFORMIXDIR)/lib

SSUK_HOME			= $(EXT_DIR)/ssuk
TCACCESS_HOME		= $(DEVLIB_PATH)/marathon/lib/tcaccess/$(TCACCESS_VERSION)

BOOST_DIR			= $(EXT_DIR)/boost
INCS_BOOST			= $(BOOST_DIR)/include
INCS_BASAR			= $(SSUK_HOME)/basar/include
INCS_LOG4CPLUS		= $(EXT_DIR)/log4cplus/include

# modeline - do not remove
# vim: ff=unix ts=4 sw=4 noexpandtab syntax=make
