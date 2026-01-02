#================================================================================
#   common libs and headers
#================================================================================

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------+
VAR_FILE       = ../../makevars.inc
include $(VAR_FILE)

#--------------------------------------------------------------------------------
#   base directories
#--------------------------------------------------------------------------------

### marathon base directory
MARATHON_DIR          = $(DEVLIB_PATH)/marathon

### informix base directory
INFORMIX_DIR          = $(INFORMIXDIR)

#--------------------------------------------------------------------------------
#   library directories
#--------------------------------------------------------------------------------
QT_DIR                = $(EXT_DIR)/qt5
LOG4CPLUS_DIR         = $(EXT_DIR)/log4cplus
LIBUTIL_DIR           = $(EXT_DIR)/libutil

#--------------------------------------------------------------------------------
#   include directories
#--------------------------------------------------------------------------------
BASAR_INC             = -I$(INCS_BASAR)
BOOST_INC             = -I$(INCS_BOOST)
LIBUTIL_INC           = -I$(LIBUTIL_DIR)/include
LOG4CPLUS_INC         = -I$(LOG4CPLUS_DIR)/include
QT_INC                = -I$(QT_DIR)/include

#--------------------------------------------------------------------------------
#   static libraries
#--------------------------------------------------------------------------------
### global libraries
LIBUTIL_LIB           = $(LIBUTIL_DIR)/lib/$(CONFVER)/libutil.a

#--------------------------------------------------------------------------------
#   shared libraries
#--------------------------------------------------------------------------------
### directories for library paths

BASAR_LIB_DIR         = $(SSUK_HOME)/sharedlib/$(CONFVER)
LOG4CPLUS_LIB_DIR     = $(LOG4CPLUS_DIR)/lib/$(CONFVER)
BOOST_LIB_DIR         = $(BOOST_DIR)/lib/$(CONFVER)
QT_LIB_DIR            = $(QT_DIR)/lib

INFORMIX_LIB_DIR      = $(INFORMIX_DIR)/lib

### shared libs
BASAR_SHARED_LIBS     = -L$(BASAR_LIB_DIR) -lbasardebug -lbasarcmnutil \
                        -lbasarproperty  -lbasardbsql -lbasardbaspect \
                        -lbasarlogin -lbasarappl
												
BASAR_LIBS_SQL_CMNUTIL	= -L$(BASAR_LIB_DIR) $(LOG4CPLUS_SHARED_LIBS) $(BOOST_FS_SHARED_LIBS) \
                        -lbasarcmnutil -lbasardbsql -lpthread -pthread

LOG4CPLUS_SHARED_LIBS = -L$(LOG4CPLUS_LIB_DIR) -llog4cplus

BOOST_SYSTEM_SHARED_LIBS = -L$(BOOST_LIB_DIR) -lboost_system -lboost_filesystem -lboost_date_time
BOOST_REGEX_SHARED_LIBS= -L$(BOOST_LIB_DIR) -lboost_regex
BOOST_PO_SHARED_LIBS  = -L$(BOOST_LIB_DIR) -lboost_program_options
BOOST_FS_SHARED_LIBS  = -L$(BOOST_LIB_DIR) -lboost_system -lboost_filesystem -lboost_date_time

QT_CORE_SHARED_LIBS   = -L$(QT_LIB_DIR) -lQt5Core
QT_XML_SHARED_LIBS    = -L$(QT_LIB_DIR) -lQt5Xml

BASAR_PROJECT_LIBS    = $(LOG4CPLUS_SHARED_LIBS) $(BOOST_FS_SHARED_LIBS) \
                        $(BASAR_SHARED_LIBS) -lpthread -pthread

INFORMIX_SHARED_LIBS  = -L$(INFORMIX_LIB_DIR) \
                        -lifsql -lifasf -lifgen -lifos -lifgls -lifglx

SOCKET_SHARED_LIBS    = -lnsl
# remove next line when completely transitioned to AIX because this is Solaris specific
# on most unix based systems socket support is directly included in libc
SOCKET_SHARED_LIBS:sh = echo -lsocket -lnsl

VOODOO_SHARED_LIBS    = -L$(VOODOO_LIB_DIR) -lscsvoodoo

# modeline - do not remove
# vim: ff=unix ts=4 sw=4 noexpandtab syntax=make
