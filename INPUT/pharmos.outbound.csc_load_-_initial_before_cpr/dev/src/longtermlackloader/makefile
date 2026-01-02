#================================================================================
#   longtermlackloader makefile (AIX) 
#   13.06.2012
#   v 1.0.0
#================================================================================


#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = longtermlackloader.bin

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------+
BASEDIR        = ..
VARS_FILE      = $(BASEDIR)/makevars.inc
include $(VARS_FILE)

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------

# sources (seperated with blank if more than one directory)
DIR_SRCS       = . \
                 componentmanager \
                 infrastructure \
                 infrastructure/accessor \
                 infrastructure/accessor/longtermlackpgk \
                 infrastructure/cmdline \
                 infrastructure/loggerpool \
                 infrastructure/login \
                 infrastructure/parameter \
                 infrastructure/setup \
                 longtermlackloader \
                 longtermlackloaderversion \
                 usecase

# headers (seperated with blank if more than one directory)
DIR_INCS       = $(DIR_SRCS)
                 

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------
LIBS_STATIC    = $(LIBUTIL_LIB) $(LIBVERSION)

LIBS_SHARED    = $(LOG4CPLUS_SHARED_LIBS) \
                 $(BOOST_SYSTEM_SHARED_LIBS) \
                 $(BASAR_SHARED_LIBS) \
                 $(QT_CORE_SHARED_LIBS) \
                 $(INFORMIX_SHARED_LIBS)

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

ENABLE_BIG_TOC = 0

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -Werror -Wno-long-long -mminimal-toc
# additional linker options like -lpthread
ADD_LINK_OPTS   =

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
INCS = -I. \
        -I infrastructure \
        -I usecase \
        -I../common \
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
