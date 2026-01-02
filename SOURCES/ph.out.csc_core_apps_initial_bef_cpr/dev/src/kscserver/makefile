#================================================================================
#   kscserver makefile
#   05.04.2012
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = kscserver.bin

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
DIR_SRCS       = .

# headers (seperated with blank if more than one directory)
DIR_INCS       = .

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------

LIBS_STATIC    = $(PXVERBUND_LIB) $(PXDB_LIB) \
                 $(CXXTOOLS_LIB) $(LIBLOCKMANAGER) $(PPUNIXC_LIB) \
                 $(LIBCSC)

LIBS_SHARED    = $(BASAR_LIBS_SQL_CMNUTIL) $(BOOST_REGEX_SHARED_LIBS) $(INFORMIX_SHARED_LIBS)

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
ESQL_DEFINES   = -DESQL_C -DZENTRAL -std=c99
CPP_DEFINES    =

#--------------------------------------------------------------------------------
# header
#--------------------------------------------------------------------------------

# include paths
INCS   = $(CXXTOOLS_INC) \
         $(PPUNIXC_INC) \
         $(PXDB_INC) \
         $(PXVERBUND_INC) \
         $(LIBCSC_INC) \
         $(BOOST_INC) \
         $(BASAR_INC) \
         $(LOG4CPLUS_INC) \
         $(LIBLOCKMANAGER_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

