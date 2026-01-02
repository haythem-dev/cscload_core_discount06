#================================================================================
#   csc_phadex makefile
#   29.11.2016
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = csc_phadex.bin

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
DIR_SRCS       = componentmanager\
                 csc_phadex\
                 domainmodule\
                 domainmodule/cicstransaction\
                 domainmodule/narcotics\
                 domainmodule/taskcontrol\
                 domainmodule/phadextransaction\
                 domainmodule/phadextransaction/transactionrecord\
                 domainmodule/phadextransaction/transactionrecord/narcprintupdate\
                 domainmodule/phadextransaction/transactionrecord/tenderinvoicecancellation\
                 domainmodule/phadextransaction/transactionrecord/deliverynotecompleted\
                 domainmodule/phadextransaction/transactionrecord/deliverynotecancellation\
                 domainmodule/phadextransaction/transactionrecord/blockedarticlerecord\
                 domainmodule/phadextransaction/transactionrecord/documentprintinfo\
                 domainmodule/phadextransaction/transactionrecord/sapreferencenorecord\
                 infrastructure/accessor\
                 infrastructure/cmdline\
                 infrastructure/config\
                 infrastructure/login\
                 infrastructure/parameter\
                 infrastructure/setup\
                 usecase/*\
                 usecase/processuc/transactionrecordmapper\
                 loggerpool\

# headers (seperated with blank if more than one directory)
DIR_INCS       = . $(DIR_SRCS)

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------
LIBS_STATIC    = $(PXVERBUND_LIB) $(PXDB_LIB) $(CXXTOOLS_LIB) \
                 $(LIBLOCKMANAGER) $(LIBUTIL_LIB) \
                 $(LIBCSC_UTILS) $(LIBCSC) $(LIBBATCH) 

LIBS_SHARED    = $(LOG4CPLUS_SHARED_LIBS) $(BOOST_FS_SHARED_LIBS) \
                 $(BOOST_REGEX_SHARED_LIBS) $(BASAR_SHARED_LIBS) \
                 $(TCACCESS_SHARED_LIBS) $(INFORMIX_SHARED_LIBS) \
                 $(QT_CORE_SHARED_LIBS) $(UUID_LIBS)

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -Werror -Wno-long-long -mminimal-toc

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
INCS = -I. $(LIBLOCKMANAGER_INC) \
           $(LIBCSC_INC) \
           $(CXXTOOLS_INC) \
           $(PXVERBUND_INC) \
           $(LIBUTIL_INC) \
           $(LIBCSC_UTILS_INC) \
           $(BASAR_INC) \
           $(BOOST_INC) \
           $(LOG4CPLUS_INC) \
           $(QT_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

