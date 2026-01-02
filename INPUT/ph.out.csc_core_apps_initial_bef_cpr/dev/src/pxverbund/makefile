#================================================================================
#   pxverbund makefile
#   10.04.2012
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = libpxverbund.a

# assures script call (Solaris/GNU make)
GITVERSIONINFO:sh = gitversioninfo.sh
GITVERSIONINFO    = $(shell gitversioninfo.sh >/dev/null 2>&1)

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------
BASEDIR        = ..
VARS_FILE      = $(GITVERSIONINFO)$(BASEDIR)/makevars.inc
include $(VARS_FILE)

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------

# sources (seperated with blank if more than one directory)
DIR_SRCS       = . libsrc tcawrap

# headers (seperated with blank if more than one directory)
DIR_INCS       = . include tcawrap

#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------

LIBS_STATIC    =

LIBS_SHARED    =

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -Werror -mminimal-toc

# additional linker options like -lptread
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
INCS   = -Iinclude -Itcawrap \
		 $(LIBLOCKMANAGER_INC) \
		 $(CXXTOOLS_INC) \
		 $(PXDB_INC) \
		 $(LIBCSC_INC) \
		 $(BASAR_INC) \
		 $(LOG4CPLUS_INC) \
		 $(BOOST_INC) \
		 $(INFORMIX_INC) \
		 $(TCACCESS_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

