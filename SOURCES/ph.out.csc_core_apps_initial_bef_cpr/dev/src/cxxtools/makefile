#================================================================================
#   cxxtools makefile
#   03.04.2012
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = cxxtools.a

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------
BASEDIR        = ..
VARS_FILE      = $(BASEDIR)/makevars.inc
include $(VARS_FILE)

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------

# sources (seperated with blank if more than one directory)
DIR_SRCS       = libsrc

# headers (seperated with blank if more than one directory)
DIR_INCS       = include

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------

LIBS_STATIC    =

LIBS_SHARED    =

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -Werror

# additional linker options like -lpthread
ADD_LINK_OPTS  =

#--------------------------------------------------------------------------------
# defines
#--------------------------------------------------------------------------------

COMMON_DEFINES =

C_DEFINES      =
ESQL_DEFINES   = -DESQL_C
CPP_DEFINES    =

#--------------------------------------------------------------------------------
# headers
#--------------------------------------------------------------------------------

# include paths
INCS           = -Iinclude

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

