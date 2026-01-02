#================================================================================
#   importmedreg makefile (AIX) 
#   24.06.2022
#   v 1.0.0
#================================================================================


#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = importmedreg.bin

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------+

VARS_FILE      = makevars.inc

include $(VARS_FILE)

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------

# sources (separated with blank if more than one directory)
DIR_SRCS       = . \

# headers (separated with blank if more than one directory)
DIR_INCS       = $(DIR_SRCS)
                 

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------
LIBS_STATIC    = 

LIBS_SHARED    = $(LOG4CPLUS_SHARED_LIBS) \
                 $(QT_CORE_SHARED_LIBS) -lssl

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   = -L$(EXT_DIR)/openssl/lib

ENABLE_BIG_TOC = 0

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -std=gnu++0x
# additional linker options like -lpthread
ADD_LINK_OPTS   = -Wl,-brtl,-bexpfull,-bbigtoc

#--------------------------------------------------------------------------------
# defines
#--------------------------------------------------------------------------------

COMMON_DEFINES =

C_DEFINES      =
ESQL_DEFINES   =
CPP_DEFINES    =

#--------------------------------------------------------------------------------
# header
#--------------------------------------------------------------------------------
# include paths
INCS = -I. \
       $(LOG4CPLUS_INC) \
       $(QT_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(DEVLIB_PATH)/marathon/make/makefile.inc
include $(BUILD_RULES_FILE)
