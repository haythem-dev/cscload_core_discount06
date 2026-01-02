#=============================================================
#   makefile
#=============================================================

#-------------------------------------------------------------
# build artifact 
#-------------------------------------------------------------

TARGET = zpautidm

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------+
BASEDIR        = ..
VARS_FILE      = $(BASEDIR)/makevars.inc
include $(VARS_FILE)

#-------------------------------------------------------------
# header
#-------------------------------------------------------------

# include paths
INCS         = -I. \
                           -I$(SERVCLNT_DIR)/include \
                           -I$(SERVCLNT_DIR)/include/libscsvoodoo \
                           -I$(EKLIBS_DIR)/lib \
                           -I$(EKLIBS_DIR)/include \
                           -I$(EKLIBS_DIR)/include/eklibs \
                           -I$(EKLIBS_DIR)/include/eklibs/wdbups \
                           -I$(HDATUM_DIR)/include \
                           -I$(HDATUM_DIR)/include/hdatum \
                           -I$(HDATUM_DIR)/lib \
                           -I$(VOODOO_HEADER_DIR)/include \
                           -I$(VOODOO_HEADER_DIR)/include/voodoo_table_header

#-------------------------------------------------------------
# libraries 
#-------------------------------------------------------------

LIBS_DIRS          = \
                     -L$(LIBS_INFX_ESQL_DIR) \
                     -L$(LIBS_INFX_DIR) \
					 -L$(LIBS_SERVCLNT_DIR)

LIBS_INFX_ESQL = -lifgen -lifos -lifsql -lifgls $(LIBS_INFX_ESQL_DIR)/checkapi.o
LIBS_INFX      = -lifasf

LIBS_SHARED    = $(LIBS_INFX_ESQL) $(LIBS_INFX) $(LIBS_SYSTEM)

LIBS_STATIC    = $(LIBS_EKLIBS_DIR)/wdbups.a \
                 $(LIBS_HDATUM_DIR)/hdatum.a \
                 $(LIBS_EKLIBS_DIR)/sqltabs.a \
                 $(LIBS_EKLIBS_DIR)/ifalibs.a \
                 $(LIBS_EKLIBS_DIR)/hconfkts.a \
                 $(LIBS_SERVCLNT_DIR)/libscsvoodoo.a \
                 $(LIBS_SERVCLNT_DIR)/libscczlib.a \
                 $(LIBS_SERVCLNT_DIR)/libsccstring.a \
                 $(LIBS_SERVCLNT_DIR)/libsccutilclass.a \
                 $(LIBS_SERVCLNT_DIR)/libsccdate.a

#-------------------------------------------------------------
# build options
#-------------------------------------------------------------

ADD_COMP_OPTS  = \
                 -w \
                 -D_SC_VOODOO_LOCAL_  # Project specific flag

#-------------------------------------------------------------
# Sources
#-------------------------------------------------------------

DIR_SRCS = src

#-------------------------------------------------------------
# Headers
#-------------------------------------------------------------

DIR_INCS = src

#-------------------------------------------------------------
# Library Directories
#-------------------------------------------------------------

ADD_LIB_DIRS = $(LIBS_DIRS)

#-------------------------------------------------------------
# Import all common rules
#-------------------------------------------------------------

include $(INCLUDE_FILE)

