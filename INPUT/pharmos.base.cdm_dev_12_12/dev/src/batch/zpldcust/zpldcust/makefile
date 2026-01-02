################################################
#                                              #
#   libgi makefile                             #
#   Frank Naumann                              #
#   28.01.2008                                 #
#                                              #
################################################

# ----------------------------------------------
# global defines
# ----------------------------------------------
TARGET_NAME			= zpldcust
FILES_INC			= files.inc
DEPS_INC			= deps.inc
DEPSNF_INC			= depsnf
MAKEFILE_COMMON			= ../makefile.inc
BASAR_CONFIG_XML		= ./basar.config.xml

# ----------------------------------------------
# flags for target
# ----------------------------------------------
FLAGS_RELEASE_PROJECT	=
FLAGS_DEBUG_PROJECT		=
FLAGS_GCC_PROJECT		=

# ----------------------------------------------
# includes for target
# ----------------------------------------------
INCS				= -I. -I$(INCS_BASAR) -I$(INCS_BOOST) -I$(INCS_LOG4CPLUS)

# ----------------------------------------------
# libs for target
# ----------------------------------------------
LIBS_DIR			= -L$(LIBS_DIR_BASAR) -L$(LIBS_DIR_TCACCESS)
LIBS				= $(LIBS_LOG4CPLUS) $(LIBS_BASAR) $(LIBS_TCACCESS)

# ----------------------------------------------
# object files 
# ----------------------------------------------
PROJ_SRC_LIB			=

# ----------------------------------------------
# include list of cpp files
# ----------------------------------------------
PROJ_SRC_CPP = \
main.cpp \
loggerpool.cpp \
cicscustomerdm.cpp \
connection.cpp \
customeracc.cpp \
customerdm.cpp \
dkkulacc.cpp \
generalbranchparameterdm.cpp \
loadcustomerappl.cpp \
loadcustomeruc.cpp \
publicholidayacc.cpp

# ----------------------------------------------

PROJ_OBJS			= $(PROJ_SRC_CPP:%.cpp=$(RELSUBDIR)/%.o)
PROJ_LIBS			= $(PROJ_SRC_LIB)

# ----------------------------------------------
# include common makefile
# ----------------------------------------------
include $(MAKEFILE_COMMON)

copy_debug: FORCE
	make RELDIR_VALUE=debug copy
copy: FORCE
	cp -f $(RELDIR_VALUE)/$(TARGET_NAME) $(BASAR_CONFIG_XML) $(HOME)/wss/cdm/bin;
	@ls -la $(HOME)/wss/cdm/bin
	cp -f zpldcust.cfg $(HOME)/wss/cdm/ini;
	@ls -la $(HOME)/wss/cdm/ini
	cp -f zpldcust.sh zpldcust.option $(HOME)/wss/cdm/proc;
	@ls -la $(HOME)/wss/cdm/proc


# ----------------------------------------------
# include dependencies 
# ---------------------------------------------- 
include $(DEPS_INC)