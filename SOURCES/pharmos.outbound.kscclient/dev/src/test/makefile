#================================================================================
#   kscserver makefile
#   05.04.2012
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = kscclienttest.bin

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


LIBS_STATIC    = ../build/$(CONFVER)/kscclient.a $(PPUNIXC_LIB)

LIBS_SHARED    = 

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   = 

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -Werror -mminimal-toc

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
# header
#--------------------------------------------------------------------------------

# include paths
INCS   = -I.. $(PPUNIXC_INC)


#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

