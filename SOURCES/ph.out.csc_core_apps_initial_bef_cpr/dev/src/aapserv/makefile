#================================================================================
#   aapserv makefile
#   04.04.2012
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = zaapunix.bin

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
                 $(HDATUM_LIB) $(LIBCSC)

LIBS_SHARED    = $(BASAR_LIBS_SQL_CMNUTIL) $(BOOST_REGEX_SHARED_LIBS) $(INFORMIX_SHARED_LIBS)
                 

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options
ADD_COMP_OPTS  = -DIFX_DISABLE_LOC_T -mminimal-toc

# additional linker options
ADD_LINK_OPTS  = 

#--------------------------------------------------------------------------------
# defines
#--------------------------------------------------------------------------------

COMMON_DEFINES =

C_DEFINES      =
ESQL_DEFINES   = -DESQL_C -DZENTRAL
CPP_DEFINES    = -D__CPLUS__ -D__ONLY_DISTRIBUTE__

#--------------------------------------------------------------------------------
# header
#--------------------------------------------------------------------------------

# include paths
INCS           = -I. $(INFORMIX_INC) $(PPUNIXC_INC) $(HDATUM_INC) \
                 $(PXVERBUND_INC) $(CXXTOOLS_INC) $(LIBLOCKMANAGER_INC) \
                 $(PXDB_INC) $(LIBCSC_INC) $(BOOST_INC) $(BASAR_INC) $(LOG4CPLUS_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

