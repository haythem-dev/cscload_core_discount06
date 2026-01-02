#================================================================================
#   mainwarehousearticlesrelevantcalculator makefile (AIX) 
#   06.07.2016
#   v 1.0.0
#================================================================================


#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = mainwarehousearticlesrelevantcalculator.bin

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------+

VARS_FILE      = makevars.inc

include $(VARS_FILE)

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------

# sources (seperated with blank if more than one directory)
DIR_SRCS       = mainwarehousearticlesrelevantcalculator \
                 mainwarehousearticlesrelevantcalculator/mainwarehousearticlesrelevantcalculatorinfo \
                 mainwarehousearticlesrelevantcalculator/componentmanager \
                 mainwarehousearticlesrelevantcalculator/domainmodule/* \
                 mainwarehousearticlesrelevantcalculator/mainwarehousearticlesrelevantcalculator \
                 mainwarehousearticlesrelevantcalculator/infrastructure/* \
                 mainwarehousearticlesrelevantcalculator/infrastructure/accessor/* \
                 mainwarehousearticlesrelevantcalculator/usecase \
                 mainwarehousearticlesrelevantcalculator/loggerpool \
                 mainwarehousearticlesrelevantcalculator/exceptions

# headers (seperated with blank if more than one directory)
DIR_INCS       = $(DIR_SRCS)
                 

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------
LIBS_STATIC    = $(LIBUTIL_LIB)

LIBS_SHARED    = $(LOG4CPLUS_SHARED_LIBS) $(BOOST_SYSTEM_SHARED_LIBS) $(BASAR_SHARED_LIBS) \
                 $(QT_CORE_SHARED_LIBS) -liconv

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -std=gnu++0x -Wno-long-long
# additional linker options like -lpthread
ADD_LINK_OPTS   =

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
INCS = -Imainwarehousearticlesrelevantcalculator \
       $(LIBUTIL_INC) \
       $(BASAR_INC) \
       $(BOOST_INC) \
       $(LOG4CPLUS_INC) \
       $(QT_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(DEVLIB_PATH)/marathon/make/makefile.inc
include $(BUILD_RULES_FILE)
