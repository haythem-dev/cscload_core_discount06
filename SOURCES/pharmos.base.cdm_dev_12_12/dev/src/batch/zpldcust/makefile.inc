################################################
#                                              #
#   common makefile                            #
#	Dirk Kapusta                               #
#	10.03.2006                                 #
#                                              #
################################################

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------+
BASEDIR        = ../..
VARS_FILE      = $(BASEDIR)/makevars.inc
include $(VARS_FILE)

#--------------------------------------------------------------------------------+
FLAGS_COMMON			= -DUSE_BASAR -ansi -Wall -Wextra -maix64 -pthread -c
FLAGS_RELEASE_COMMON    = -DNDEBUG -O2 $(FLAGS_COMMON)
FLAGS_DEBUG_COMMON   	= -g $(FLAGS_COMMON)
LINK_FLAGS				= -Wl,-brtl,-bexpfull,-bbigtoc -maix64 -lpthread -pthread
ADD_CPP_FLAGS			=
CPP						= g++
STRIP					= strip -X64

# ----------------------------------------------
# libs for target
# ----------------------------------------------
LIBS_DIR_TCACCESS	= $(TCACCESS_HOME)/lib
LIBS_DIR_BASAR		= $(SSUK_HOME)/sharedlib/$(DBGDIR)

LIBS_TCACCESS		= -lComHd -lChTN3270 -lChTcpIp -lSpecMap -lBml -lbmlApi -lBmlCh -lBmlUtils
LIBS_BASAR			= -lbasarcmnutil -lbasarproperty -lbasardbsql -lbasardbaspect -lbasarlogin -lbasarappl
LIBS_LOG4CPLUS		= -llog4cplus -lboost_system -lboost_filesystem

# ----------------------------------------------
# misc
# ----------------------------------------------
TEMP_FILES          	= SunWS_cache ir.out

# ----------------------------------------------
# flags
# ----------------------------------------------
FLAGS_GCC_COMMON    	= -g -Wall -pedantic -Wno-long-long -Wextra -maix64 -fPIC
FLAGS_DEBUG     		= $(FLAGS_DEBUG_COMMON) $(FLAGS_DEBUG_PROJECT)
FLAGS_RELEASE     		= $(FLAGS_RELEASE_COMMON) $(FLAGS_RELEASE_PROJECT)
CPPFLAGS     			= $(ADD_CPP_FLAGS) $(INCS) $(FLAGS_DEBUG)
GCC_CPPFLAGS   			= $(INCS) $(FLAGS_GCC_COMMON)

RELDIR_VALUE 			= release
DBGDIR_VALUE 			= debug
GCCDBGDIR_VALUE			= gccdbg
DBGDIR       			= $(DBGDIR_VALUE)

RELSUBDIR_RELVALUE    = release
RELSUBDIR_DBGVALUE    = debug
RELSUBDIR_GCCVALUE    = gccdbg
RELSUBDIR             = $(RELSUBDIR_DBGVALUE)

LFLAGS       		  = $(LINK_FLAGS) -o $(RELSUBDIR)/$(TARGET_NAME) $(LIBS_DIR)
GCC_LFLAGS			  = $(LINK_FLAGS) -o $(RELSUBDIR_GCCVALUE)/$(TARGET_NAME) $(LIBS_DIR)

CMD_PATH           = LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(LIBS_DIR_BASAR):$(WSS)/lib/tcaccess/$(TCACCESS_VERSION)/sharedlib/release; \
                     export LD_LIBRARY_PATH

# ----------------------------------------------
#   tools
# ----------------------------------------------
# CC        : Forte C++ compiler/linker
# strip     : strip symbol table, debugging and line number information from an object file
# nawk		: new awk

GCC   = g++
LINK  = $(CPP)
AWK   = nawk
MKDIR = mkdir -p

# ----------------------------------------------
#   default goal
# ----------------------------------------------
$(RELSUBDIR)/$(TARGET_NAME): $(PROJ_OBJS) $(PROJ_LIBS)
	@echo "  linkinglinking $(RELSUBDIR)/$(TARGET_NAME) ...";
	$(LINK) $(LFLAGS) $(PROJ_OBJS) $(PROJ_LIBS) $(LIBS);
	@echo "";
	ls -l $(RELSUBDIR)/$(TARGET_NAME);
	@echo "";
	@if [ "$(DBGDIR)" = "$(RELDIR_VALUE)" -a ["zpldcust" = "$(TARGET_NAME)"] ]; \
	then $(STRIP) $(RELSUBDIR)/$(TARGET_NAME); \
	    echo "$(STRIP) $(RELSUBDIR)/$(TARGET_NAME)"; \
	    ls -l $(RELSUBDIR)/$(TARGET_NAME); \
	    echo ""; \
	fi;     
	@echo "";

	
# ----------------------------------------------
#   C++ sources
# ----------------------------------------------
%.o : $(RELSUBDIR)/%.o

$(RELSUBDIR)/%.o : %.cpp
	@echo "  compiling $< ...";
	$(MKDIR) $(RELSUBDIR);
	$(CPP) $(CPPFLAGS) -o ./$@ -c $<;
	@echo "";

# ----------------------------------------------
#   build debug version
# ----------------------------------------------
debug dbg: FORCE
	@$(MAKE) $(RELSUBDIR_DBGVALUE)/$(TARGET_NAME);

	
# ----------------------------------------------
#   build release version
# ----------------------------------------------
release rel: FORCE
	@$(MAKE) FLAGS_DEBUG='$(FLAGS_RELEASE_COMMON) $(FLAGS_RELEASE_PROJECT)' DBGDIR='$(RELDIR_VALUE)' RELSUBDIR='$(RELSUBDIR_RELVALUE)' $(RELSUBDIR_RELVALUE)/$(TARGET_NAME);


# ----------------------------------------------
#   build gcc version
# ----------------------------------------------
gccdbg: FORCE
	@$(MAKE) LINK='$(GCC)' CPP='$(GCC)' LFLAGS='$(GCC_LFLAGS)' \
	         CPPFLAGS='$(GCC_CPPFLAGS)' \
	         FLAGS_DEBUG='$(FLAGS_GCC_COMMON) $(FLAGS_GCC_PROJECT)' \
	         DBGDIR='$(GCCDBGDIR_VALUE)' RELSUBDIR='$(RELSUBDIR_GCCVALUE)' \
	         $(RELSUBDIR_GCCVALUE)/$(TARGET_NAME);
#-------------------------------------------------------------
#   build all
#-------------------------------------------------------------
all: release debug gccdbg
	
	
#-------------------------------------------------------------
#   start process
#-------------------------------------------------------------
start: FORCE
	echo "  start $(RELSUBDIR)/$(TARGET_NAME) ($(DBGDIR)) ...";
	touch $(RELSUBDIR)/login4test.cfg;
	$(CMD_PATH); $(RELSUBDIR)/$(TARGET_NAME);
	
#-------------------------------------------------------------
#   start debug process
#-------------------------------------------------------------
stdbg start_dbg dbg_start: FORCE
	@$(MAKE) start DBGDIR='$(DBGDIR_VALUE)'  RELSUBDIR='$(RELSUBDIR_DBGVALUE)'

#-------------------------------------------------------------
#   start release process
#-------------------------------------------------------------
strel start_rel rel_start: FORCE
	@$(MAKE) start DBGDIR='$(RELDIR_VALUE)'  RELSUBDIR='$(RELSUBDIR_RELVALUE)'
	
# ----------------------------------------------
# create file dependencies for target
# ----------------------------------------------
dodeps: FORCE
	@pwd;
	@echo "  creating dependency files";
	@rm -f $(DEPSNF_INC);
	@rm -f $(DEPS_INC);
	@touch $(DEPS_INC);
	ls *.cpp | nawk '{ system( "gcc $(INCS) -MM -MG " $$0 " 2> $(DEPSNF_INC)" ) }' | nawk '{ print $$0; }' >> $(DEPS_INC)
	@ls -l $(DEPS_INC) $(DEPSNF_INC)
	
	
#-------------------------------------------------------------
#   remove temporary files
#-------------------------------------------------------------
.clean: FORCE
	@if rm -r $(RELSUBDIR) 2>/dev/null; \
	then echo "  directory $(RELSUBDIR) removed"; \
	else echo "  directory $(RELSUBDIR) already removed"; \
	fi;
	@rm -r $(TEMP_FILES) 2>/dev/null || true; \
	echo "  temporary files $(TEMP_FILES) for $(RELSUBDIR)/$(TARGET_NAME) removed";
	@if rm $(PROJ_OBJS) $(RELSUBDIR)/$(TARGET_NAME) 2>/dev/null; \
	then echo " additional object and binary files for $(RELSUBDIR)/$(TARGET_NAME) removed"; \
	fi;
	
#-------------------------------------------------------------
#   remove temporary files
#-------------------------------------------------------------
clean_rel rel_clean: FORCE
	@$(MAKE) .clean  RELSUBDIR='$(RELSUBDIR_RELVALUE)'

clean_dbg dbg_clean: FORCE
	@$(MAKE) .clean  RELSUBDIR='$(RELSUBDIR_DBGVALUE)'

clean_gcc gcc_clean: FORCE
	@$(MAKE) .clean  RELSUBDIR='$(RELSUBDIR_GCCVALUE)' TEMP_FILES=''
	
clean: clean_rel clean_dbg clean_gcc

# ----------------------------------------------
# copy release binary to public directory
# ----------------------------------------------
#copy: FORCE
#	@if [ "zpldcust" = "$(TARGET_NAME)" ]; \
#		then cp $(RELDIR_VALUE)/$(TARGET_NAME) $(WSS)/de/cdm/bin; \
#		echo "cp $(RELDIR_VALUE)/$(TARGET_NAME) $(WSS)/de/cdm/bin"; \
#		cp $(RELDIR_VALUE)/../*.cfg $(WSS)/de/cdm/ini; \
#		echo "cp $(RELDIR_VALUE)/../*.cfg $(WSS)/de/cdm/ini"; \
#	fi;     
	
# ----------------------------------------------
#   Usage
# ----------------------------------------------
help: FORCE
	@echo "  make           : update (compile and link) $(TARGET_NAME) (debug)";
	@echo "  make all       : update (compile and link) $(TARGET_NAME) (all versions)";
	@echo "  make release   : create release version";
	@echo "  make debug     : create debug version";
	@echo "  make gcc       : create gcc-compiled version (useful for pedantic syntax checking)";
	@echo "  make stdbg     : start debug       ($(RELSUBDIR_DBGVALUE)/$(TARGET_NAME))";
	@echo "  make strel     : start release     ($(RELSUBDIR_RELVALUE)/$(TARGET_NAME))";
	@echo "  make clean     : delete $(TARGET_NAME), *.o and temporary files";
	@echo "  make clean_rel : delete release version ";
	@echo "  make clean_dbg : delete debug version ";
	@echo "  make clean_gcc : delete gcc version  ";
	@echo "  make copy      : publish release binary";
	@echo "  make dodeps    : scan all cpp-Files to find out all dependencies:\n" \
          "                  all resolved dependencies are piped in the file 'deps'(dependencies),\n" \
          "                  the unresolved ones in 'depsnf' (dependencies not found).";
	@echo "";

	
# ----------------------------------------------
#   Dummy
# ----------------------------------------------
FORCE:


# ----------------------------------------------
#   Undefined
# ----------------------------------------------
.c:

# ----------------------------------------------
#   File Suffixes
# ----------------------------------------------
.SUFFIXES:
.SUFFIXES: .o .cpp

