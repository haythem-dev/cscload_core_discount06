#================================================================================
#   ibtorderimport makefile (AIX) 
#   13.06.2012
#   v 1.0.0
#================================================================================


#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = ibtorderimport.bin

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
                 domainmodule \
				 ibtorderimport \
				 infrastructure \
                 infrastructure/mail \
                 infrastructure/cmdline \
				 infrastructure/accessor \
				 infrastructure/setup \
                 usecase \
                 loggerpool

# headers (seperated with blank if more than one directory)
DIR_INCS       = $(DIR_SRCS)
                 

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------
LIBS_STATIC    = $(LIBUTIL_LIB) $(PXVERBUND_LIB) $(PXDB_LIB) \
				 $(CXXTOOLS_LIB) $(LIBLOCKMANAGER) $(LIBCSC_UTILS) $(LIBBATCH) $(LIBCSC)

LIBS_SHARED    = $(LOG4CPLUS_SHARED_LIBS) $(BOOST_SYSTEM_SHARED_LIBS) $(BOOST_FS_SHARED_LIBS) \
                 $(BOOST_REGEX_SHARED_LIBS) $(BASAR_SHARED_LIBS) \
                 $(QT_CORE_SHARED_LIBS) $(TCACCESS_SHARED_LIBS) $(INFORMIX_SHARED_LIBS)

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
       $(LIBBATCH_INC) \
       $(LIBCSC_UTILS_INC) \
	   $(LIBLOCKMANAGER_INC) \
       $(CXXTOOLS_INC) \
       $(PXVERBUND_INC) \
       $(PXDB_INC) \
	   $(LIBUTIL_INC) \
       $(BASAR_INC) \
       $(BOOST_INC) \
       $(LOG4CPLUS_INC) \
       $(QT_INC) \
	   $(LIBCSC_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(DEVLIB_PATH)/marathon/make/makefile.inc
include $(BUILD_RULES_FILE)
