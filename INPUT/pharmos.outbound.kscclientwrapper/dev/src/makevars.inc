#================================================================================
#   common libs and headers
#================================================================================

#--------------------------------------------------------------------------------
#   base directories
#--------------------------------------------------------------------------------

### marathon base directory
MARATHON_DIR          = $(DEVLIB_PATH)/marathon

BASE_DIR             := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
EXT_DIR              := $(abspath $(BASE_DIR)../ext)

### informix base directory
INFORMIX_DIR          = $(INFORMIXDIR)

#--------------------------------------------------------------------------------
#   library directories
#--------------------------------------------------------------------------------
SSUK_DIR              = $(EXT_DIR)/ssuk

BASAR_DIR             = $(SSUK_DIR)/basar
BOOST_DIR             = $(SSUK_DIR)
KSCCLIENT_DIR         = $(EXT_DIR)/kscclient
LOG4CPLUS_DIR         = $(SSUK_DIR)/log4cplus
PPUNIXC_DIR           = $(EXT_DIR)/pplib

#--------------------------------------------------------------------------------
#   include directories
#--------------------------------------------------------------------------------
BASAR_INC             = -I$(BASAR_DIR)/include
BOOST_INC             = -I$(BOOST_DIR)
KSCCLIENT_INC         = -I$(KSCCLIENT_DIR)/include
LOG4CPLUS_INC         = -I$(LOG4CPLUS_DIR)/include
PPUNIXC_INC           = -I$(PPUNIXC_DIR)/include

#--------------------------------------------------------------------------------
#   static libraries
#--------------------------------------------------------------------------------

### global libraries
KSCCLIENT_LIB         = $(KSCCLIENT_DIR)/lib/$(CONFVER)/kscclient.a
PPUNIXC_LIB           = $(PPUNIXC_DIR)/lib/$(CONFVER)/ppunixc.a

### ESQL libraries
ESQL_CHECKAPI_LIB     = $(INFORMIX_ESQL_LIB_DIR)/checkapi.o

#--------------------------------------------------------------------------------
#   shared libraries
#--------------------------------------------------------------------------------
### directories for library paths

BASAR_LIB_DIR         = $(SSUK_DIR)/sharedlib/$(CONFVER)
TCACCESS_LIB_DIR      = $(TCACCESS_DIR)/lib/
LOG4CPLUS_LIB_DIR     = $(SSUK_DIR)/sharedlib/$(CONFVER)
BOOST_LIB_DIR         = $(SSUK_DIR)/sharedlib/$(CONFVER)
QT_LIB_DIR            = $(SSUK_DIR)/sharedlib/$(CONFVER)

INFORMIX_LIB_DIR      = $(INFORMIX_DIR)/lib
INFORMIX_ESQL_LIB_DIR = $(INFORMIX_LIB_DIR)/esql

### shared libs
BASAR_SHARED_LIBS     = -L$(BASAR_LIB_DIR) -lbasarcmnutil \
                        -lbasardbsql -lbasardebug

LOG4CPLUS_SHARED_LIBS = -L$(LOG4CPLUS_LIB_DIR) -llog4cplus

BOOST_REGEX_SHARED_LIBS= -L$(BOOST_LIB_DIR) -lboost_regex
BOOST_PO_SHARED_LIBS  = -L$(BOOST_LIB_DIR) -lboost_program_options
BOOST_FS_SHARED_LIBS  = -L$(BOOST_LIB_DIR) -lboost_system -lboost_filesystem

QT_CORE_SHARED_LIBS   = -L$(QT_LIB_DIR) -lQtCore
QT_XML_SHARED_LIBS    = -L$(QT_LIB_DIR) -lQtXml

TCACCESS_SHARED_LIBS  = -L$(TCACCESS_LIB_DIR) \
                        -lComHd -lChTN3270 -lChTcpIp -lBmlCh -lBmlCh -lSpecMap \
                        -lBml -lbmlApi -lBmlUtils

BASAR_PROJECT_LIBS    = $(LOG4CPLUS_SHARED_LIBS) $(BOOST_FS_SHARED_LIBS) \
                        $(BASAR_SHARED_LIBS) -lpthread -pthread \
                        $(TCACCESS_SHARED_LIBS)

INFORMIX_SHARED_LIBS  = -L$(INFORMIX_LIB_DIR) -L$(INFORMIX_ESQL_LIB_DIR) \
                        -lifsql -lifasf -lifgen -lifos -lifgls -lifglx

SOCKET_SHARED_LIBS    = -lnsl
# remove next line when completely transitioned to AIX because this is Solaris specific
# on most unix based systems socket support is directly included in libc
SOCKET_SHARED_LIBS:sh = echo -lsocket -lnsl

VOODOO_SHARED_LIBS    = -L$(VOODOO_LIB_DIR) -lscsvoodoo

# modeline - do not remove
# vim: ff=unix ts=4 sw=4 noexpandtab syntax=make
