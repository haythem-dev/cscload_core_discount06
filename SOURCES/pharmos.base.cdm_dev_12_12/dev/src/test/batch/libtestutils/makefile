################################################
#                                              #
#   libivc makefile (Solaris)                  #
#	Dirk Kapusta                               #
#	01.07.2008                                 #
#                                              #
################################################

# ----------------------------------------------
# include makefile containing vars
# ----------------------------------------------
include ../makevars.inc

# ----------------------------------------------
# global defines
# ----------------------------------------------
TARGET_NAME					= libtestutils.a

# ----------------------------------------------
# flags for target
# ----------------------------------------------
FLAGS_RELEASE_PROJECT    	=
FLAGS_DEBUG_PROJECT    		=
FLAGS_GCC_PROJECT    		=

# ----------------------------------------------
# includes for target
# ----------------------------------------------
INCS_PROJECT				= -I$(INCS_UNITTEST)
INCS                  		= -I. -I$(INCS_BASAR) -I$(INCS_QT) -I$(INCS_QTCORE) -I$(INCS_BOOST) -I$(INCS_LOG4CPLUS) $(INCS_PROJECT)

# ----------------------------------------------
# libs for target
# ----------------------------------------------
LIBS_DIR_PROJECT			= 
LIBS_DIR	              	= -L$(LIBS_DIR_BASAR) -L$(LIBS_DIR_TCACCESS) $(LIBS_DIR_PROJECT)


LIBS_PROJECT				= -xar
LIBS               			= $(LIBS_BASAR) $(LIBS_TCACCESS) $(LIBS_BOOST) $(LIBS_LOG4CPLUS) $(LIBS_SYSTEM) $(LIBS_PROJECT)

# ----------------------------------------------
# paths for target
# ----------------------------------------------
OUTDIR             			= -o ./$@

# ----------------------------------------------
# object files 
# ----------------------------------------------
PROJ_SRC_LIB 				= 

# ----------------------------------------------
# include list of cpp files
# ----------------------------------------------
# $(FILES_INC) contains PROJ_SRC_CPP
include $(FILES_INC)

PROJ_OBJS    				= $(PROJ_SRC_CPP:%.cpp=$(RELSUBDIR)/%.o)
PROJ_LIBS    				= $(PROJ_SRC_LIB)

# ----------------------------------------------
# include common makefile
# ----------------------------------------------
include ../makefile.inc

# all dms unter unix (printerdm is not part of this library)
SRC_DIRS = . \
           utils \

PROJ_RELSUBDIRS += $(SRC_DIRS:%=$(RELSUBDIR)/%)

# ----------------------------------------------
# include dependencies 
# ---------------------------------------------- 
include $(DEPS_INC)
