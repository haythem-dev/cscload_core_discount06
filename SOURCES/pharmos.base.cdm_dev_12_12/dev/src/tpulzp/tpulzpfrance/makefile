#=============================================================
#   makefile
#=============================================================
#-------------------------------------------------------------
# build artifact 
#-------------------------------------------------------------

TARGET = tpulzpfrance

#-------------------------------------------------------------
# common libs and headers
#-------------------------------------------------------------
# marathon base directory
MARATHON_DIR          = $(DEVLIB_PATH)/marathon

# informix base directory
INFORMIX_DIR          = $(INFORMIXDIR)

#--------------------------------------------------------------------------------
# library versions
#--------------------------------------------------------------------------------
VERSIONFILE = 

#--------------------------------------------------------------------------------
# library directories
#--------------------------------------------------------------------------------
LIBTPLD_DIR           = ../../../ext/libtpld

#--------------------------------------------------------------------------------
# include directories
#--------------------------------------------------------------------------------
LIBTPLD_INC           = -I$(LIBTPLD_DIR)/include
VOODOO_HEADER_DIR     = ../../../ext/voodoo_table_header

#--------------------------------------------------------------------------------
# static libraries
#--------------------------------------------------------------------------------
# ESQL libraries
ESQL_CHECKAPI_LIB     = $(INFORMIX_ESQL_LIB_DIR)/checkapi.o

# others
LIBTPLD               = $(LIBTPLD_DIR)/lib/$(CONFVER)/libtpld.a

#--------------------------------------------------------------------------------
# shared libraries
#--------------------------------------------------------------------------------
# directories for library paths
INFORMIX_LIB_DIR      = $(INFORMIX_DIR)/lib
INFORMIX_ESQL_LIB_DIR = $(INFORMIX_LIB_DIR)/esql

# shared libs
INFORMIX_SHARED_LIBS  = -L$(INFORMIX_LIB_DIR) -L$(INFORMIX_ESQL_LIB_DIR) \
                        -lifsql -lifasf -lifgen -lifos -lifgls -lifglx

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------
DEPLOYMENT_DIR = $(DIR_OUT)
VARS_FILE =  

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------
# sources (seperated with blank if more than one directory)
DIR_SRCS       = .

# headers (seperated with blank if more than one directory)
DIR_INCS       = .

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------
LIBS_STATIC    = $(ESQL_CHECKAPI_LIB) $(LIBTPLD)
LIBS_SHARED    = $(INFORMIX_SHARED_LIBS) -lm

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -pthread
ADD_COMP_OPTS  = -DIFX_DISABLE_LOC_T

# additional linker options like -lpthread
ADD_LINK_OPTS  =

#--------------------------------------------------------------------------------
# defines
#--------------------------------------------------------------------------------
COMMON_DEFINES = 
C_DEFINES      =
ESQL_DEFINES   =
CPP_DEFINES    =

#--------------------------------------------------------------------------------
# headers
#--------------------------------------------------------------------------------
# include paths
INCS           = -I. $(LIBTPLD_INC) -I$(VOODOO_HEADER_DIR)/include

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------
BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)
