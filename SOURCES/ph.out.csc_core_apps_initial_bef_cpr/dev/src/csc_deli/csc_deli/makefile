#================================================================================
#   csc_deli makefile
#   07.09.2015
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = csc_deli.bin

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
DIR_SRCS       = csc_deli csc_deliinfo componentmanager infrastructure/* \
                 usecase

# headers (seperated with blank if more than one directory)
DIR_INCS       = csc_deli csc_deliinfo componentmanager infrastructure/* \
                 usecase

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------

LIBS_STATIC    = $(LIBUTIL_LIB) $(PXVERBUND_LIB) $(PXDB_LIB) \
                 $(CXXTOOLS_LIB) $(LIBLOCKMANAGER) $(LIBCSC) $(LIBCSC_DELI)

LIBS_SHARED    = $(QT_CORE_SHARED_LIBS) $(BASAR_PROJECT_LIBS) $(INFORMIX_SHARED_LIBS) $(BOOST_REGEX_SHARED_LIBS)

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -Werror -Wno-long-long 

# additional linker options like -lpthread
ADD_LINK_OPTS  = 

ENABLE_LAZYLOADING=1
ENABLE_BIG_TOC = 1

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
INCS           = -I. $(BASAR_INC) $(BOOST_INC) $(LIBUTIL_INC) $(LOG4CPLUS_INC) \
                 $(QT_INC) $(PXVERBUND_INC) $(LIBCSC_INC) \
                 $(LIBCSC_DELI_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)
