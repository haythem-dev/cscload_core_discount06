#================================================================================
#   cscserver makefile
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = cscservice.bin

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
DIR_SRCS      = .

# headers (seperated with blank if more than one directory)
DIR_INCS      = .

ADD_SOURCES   = $(patsubst idl/%.thrift,$(DIR_GEN_SRC)/%_constants.cpp,$(wildcard idl/*.thrift)) \
                $(patsubst idl/%.thrift,$(DIR_GEN_SRC)/%_types.cpp,$(wildcard idl/*.thrift)) \
                $(patsubst ../pxverbund/include/types/%.inc,$(DIR_GEN_SRC)/%_constants.cpp,$(wildcard ../pxverbund/include/types/*.inc)) \
                $(patsubst ../pxverbund/include/types/%.inc,$(DIR_GEN_SRC)/%_types.cpp,$(wildcard ../pxverbund/include/types/*.inc)) \
                $(DIR_GEN_SRC)/CscServiceBase.cpp \
                $(DIR_GEN_SRC)/CscServiceBatch.cpp \
                $(DIR_GEN_SRC)/CscServiceOnline.cpp
#                $(patsubst idl/types/%.inc,$(DIR_GEN_SRC)/%_constants.cpp,$(wildcard idl/types/*.inc)) \
#                $(patsubst idl/types/%.inc,$(DIR_GEN_SRC)/%_types.cpp,$(wildcard idl/types/*.inc)) \

ADD_HEADERS   = $(patsubst idl/%.thrift,$(DIR_GEN_SRC)/%_constants.h,$(wildcard idl/*.thrift)) \
                $(patsubst idl/%.thrift,$(DIR_GEN_SRC)/%_types.h,$(wildcard idl/*.thrift)) \
                $(patsubst ../pxverbund/include/types/%.inc,$(DIR_GEN_SRC)/%_constants.h,$(wildcard ../pxverbund/include/types/*.inc)) \
                $(patsubst ../pxverbund/include/types/%.inc,$(DIR_GEN_SRC)/%_types.h,$(wildcard ../pxverbund/include/types/*.inc)) \
                $(DIR_GEN_SRC)/CscServiceBase.h \
                $(DIR_GEN_SRC)/CscServiceBatch.h \
                $(DIR_GEN_SRC)/CscServiceOnline.h
#                $(patsubst idl/types/%.inc,$(DIR_GEN_SRC)/%_constants.h,$(wildcard idl/types/*.inc)) \
#                $(patsubst idl/types/%.inc,$(DIR_GEN_SRC)/%_types.h,$(wildcard idl/types/*.inc)) \


#--------------------------------------------------------------------------------
# libraries 
#--------------------------------------------------------------------------------

LIBS_STATIC    = $(PXVERBUND_LIB) $(PXDB_LIB) \
                 $(CXXTOOLS_LIB) $(LIBLOCKMANAGER) $(LIBCSC)

LIBS_SHARED    = $(BASAR_LIBS_SQL_CMNUTIL) $(BOOST_REGEX_SHARED_LIBS) $(INFORMIX_SHARED_LIBS) \
                 $(THRIFT_SHARED_LIBS) $(BOOST_LOC_SHARED_LIBS)

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   = 

# additional compiler options like -pthread
ADD_COMP_OPTS  = -pedantic -Werror -Wno-long-long  -Wno-variadic-macros -mminimal-toc

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
INCS           = $(CXXTOOLS_INC) \
		 $(PXDB_INC) \
		 $(PXVERBUND_INC) \
		 $(LIBCSC_INC) \
		 $(BOOST_INC) \
		 $(BASAR_INC) \
		 $(LOG4CPLUS_INC) \
		 $(THRIFT_INC) \
		 $(LIBLOCKMANAGER_INC) \
		 -I$(DIR_GEN_SRC) -I.


#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE =  $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

#--------------------------------------------------------------------------------
# custom build rules because of thrift
#--------------------------------------------------------------------------------

$(DIR_GEN_SRC)/%_constants.cpp $(DIR_GEN_SRC)/%_constants.h \
$(DIR_GEN_SRC)/%_types.cpp $(DIR_GEN_SRC)/%_types.h \
$(DIR_GEN_SRC)/%.cpp $(DIR_GEN_SRC)/%.h: idl/%.thrift
	@$(MKDIR) $(DIR_GEN_SRC)
	$(THRIFT) -r -strict --gen cpp --out $(DIR_GEN_SRC) -I ../pxverbund/include $<


$(DIR_GEN_SRC)/%_constants.cpp $(DIR_GEN_SRC)/%_constants.h \
$(DIR_GEN_SRC)/%_types.cpp $(DIR_GEN_SRC)/%_types.h \
$(DIR_GEN_SRC)/%.cpp $(DIR_GEN_SRC)/%.h: ../pxverbund/include/types/%.inc
	@$(MKDIR) $(DIR_GEN_SRC)
	$(THRIFT) -r -strict --gen cpp --out $(DIR_GEN_SRC) -I ../pxverbund/include $<


$(DIR_GEN_SRC)/CscServiceBase.cpp  $(DIR_GEN_SRC)/CscServiceBase.h \
$(DIR_GEN_SRC)/CscServiceBatch.cpp  $(DIR_GEN_SRC)/CscServiceBatch.h \
$(DIR_GEN_SRC)/CscServiceOnline.cpp  $(DIR_GEN_SRC)/CscServiceOnline.h \
$(DIR_GEN_SRC)/cscservice_types.cpp $(DIR_GEN_SRC)/cscservice_types.h \
$(DIR_GEN_SRC)/cscservice_constants.cpp $(DIR_GEN_SRC)/cscservice_constants.h: idl/cscservice.thrift
