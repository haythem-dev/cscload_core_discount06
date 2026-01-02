#================================================================================
#   loadcstpharmgrp makefile (Solaris)
#   05.04.2012
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = loadcstpharmgrp.bin

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------

VARS_FILE      = ../makevars.inc
include $(VARS_FILE)

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

LIBS_STATIC    = $(ESQL_CHECKAPI_LIB) $(PPUNIXC_LIB) $(LIBVERSION)

LIBS_SHARED    = $(INFORMIX_SHARED_LIBS)  -lm -liconv

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -library=stlport4 (xcode=pic32 supersedes KPIC)
ADD_COMP_OPTS  = -DIFX_DISABLE_LOC_T

# additional linker options like -library=stlport4 or -z lazyload
ADD_LINK_OPTS  =

#--------------------------------------------------------------------------------
# defines
#--------------------------------------------------------------------------------

COMMON_DEFINES =

C_DEFINES      =
ESQL_DEFINES   = -DESQL_C -DZENTRAL
CPP_DEFINES    =

#--------------------------------------------------------------------------------
# header
#--------------------------------------------------------------------------------

# include paths
INCS           = $(PPUNIXC_INC) -I../common

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

