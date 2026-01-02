#================================================================================
#   tpldhipath2 makefile (Solaris)
#   24.07.2013   
#   v 1.0.0
#================================================================================


#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET = tpldhipath2.bin

#--------------------------------------------------------------------------------
# defines
#--------------------------------------------------------------------------------
COMMON_DEFINES = -DVERBOSE=1
CPP_DEFINES = 
ESQL_DEFINES = -DESQL_C -DEBUGOFF=1


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

LIBS_STATIC = $(ESQL_CHECKAPI_LIB) $(LIBVERSION)

LIBS_SHARED = -L$(INFORMIX_ESQL_LIB_DIR) -L$(INFORMIX_LIB_DIR) $(INFORMIX_SHARED_LIBS) 

LIBS           = 


# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -library=stlport4 (xcode=pic32 supersedes KPIC)
ADD_COMP_OPTS  = -DIFX_DISABLE_LOC_T

# additional linker options like -library=stlport4 or -z lazyload
ADD_LINK_OPTS = -Wl,-bquiet 


#--------------------------------------------------------------------------------
# header
#--------------------------------------------------------------------------------

# include paths
INCS           = -I../common

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)


