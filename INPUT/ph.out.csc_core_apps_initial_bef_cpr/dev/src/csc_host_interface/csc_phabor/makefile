#================================================================================
#   csc_phabor makefile
#   13.07.2012
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = csc_phabor.bin

#--------------------------------------------------------------------------------
# include common library versions and library depends
#--------------------------------------------------------------------------------
BASEDIR        = ../..
VARS_FILE      = $(BASEDIR)/makevars.inc
include $(VARS_FILE)

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------

# sources (seperated with blank if more than one directory)
DIR_SRCS       = csc_phabor

# headers (seperated with blank if more than one directory)
DIR_INCS       = csc_phabor

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------
LIBS_STATIC    = $(PXVERBUND_LIB) $(PXDB_LIB) $(CXXTOOLS_LIB) \
				 $(LIBCSC_UTILS) $(LIBBATCH) $(LIBCSC) $(LIBLOCKMANAGER)

LIBS_SHARED    = $(LOG4CPLUS_SHARED_LIBS) $(BOOST_FS_SHARED_LIBS) \
                 $(BOOST_REGEX_SHARED_LIBS) $(BASAR_SHARED_LIBS) \
                 $(TCACCESS_SHARED_LIBS) $(INFORMIX_SHARED_LIBS) \
                 $(QT_CORE_SHARED_LIBS) $(UUID_LIBS)

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -Wno-long-long -Werror -mminimal-toc

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
INCS = $(LIBCSC_UTILS_INC) \
       $(LIBBATCH_INC) \
       $(LIBLOCKMANAGER_INC) \
       $(CXXTOOLS_INC) \
       $(PXVERBUND_INC) \
       $(PXDB_INC) \
       $(BASAR_INC) $(BOOST_INC) $(LOG4CPLUS_INC) \
       $(QT_INC) $(LIBCSC_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

