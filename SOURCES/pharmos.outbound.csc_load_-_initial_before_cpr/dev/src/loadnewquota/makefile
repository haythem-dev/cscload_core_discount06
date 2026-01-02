#================================================================================
#   loadnewquota makefile
#================================================================================

#--------------------------------------------------------------------------------
# build artifact
#--------------------------------------------------------------------------------

TARGET         = loadnewquota.bin

#--------------------------------------------------------------------------------
# include common library versions and library depends
#--------------------------------------------------------------------------------

VARS_FILE      = ../makevars.inc
include $(VARS_FILE)

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------

# sources (separated with blank if more than one directory)
DIR_SRCS       = .

# headers (separated with blank if more than one directory)
DIR_INCS       = .

#--------------------------------------------------------------------------------
# libraries
#--------------------------------------------------------------------------------

LIBS_STATIC    = $(ESQL_CHECKAPI_LIB) $(PPUNIXC_LIB) $(LIBVERSION)

LIBS_SHARED    = $(INFORMIX_SHARED_LIBS) -liconv

# additional library dirs to add with -L like -L$(LIB_DIR)
ADD_LIB_DIRS   =

# additional compiler options like -pthread
ADD_COMP_OPTS  = -DIFX_DISABLE_LOC_T -std=c++0x

# additional linker options like -lpthread
ADD_LINK_OPTS  =

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
INCS           = $(LIBTPLD_INC) $(PPUNIXC_INC) $(BOOST_INC) -I../common 

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

dbg: | showsrc
	@echo "Build $(CONFIG) ..."
	make build_dbg

rel: | showsrc
	@$(eval CONFIG=release)
	@echo "Build for $(CONFIG) ..."
	make build_rel

build_dbg:
	mkdir -p build/obj/$(CONFIG) build/$(CONFIG)
	cp ./loadnewquota.cxx build/obj/loadnewquota.ec
	esql -g -c -cc -x c++ -I../../ext/libtpld/include  -I../../ext/libtpld/include/libtpld  -I../../ext/pplib/include -I../common -D ESQL_C \
                                   -std=c++0x -pedantic-errors -Wall -Wextra -Wno-unused-variable -Wno-missing-field-initializers \
                                   -Wno-unused-but-set-variable -Wno-sign-compare -Wno-long-long -Wno-format -Wno-comment \
                                   -O2 -s -DNDEBUG \
                                   -D strtk_no_tr1_or_boost -O2 -s -DNDEBUG build/obj/loadnewquota.ec -o build/obj/$(CONFIG)/loadnewquota.o
	$(CXX) -maix64 -g -o build/$(CONFIG)/loadnewquota.bin \
		build/obj/$(CONFIG)/loadnewquota.o -lstdc++ -lm $(INFORMIX_SHARED_LIBS)

build_rel:
	mkdir -p build/obj/release build/release
	cp ./loadnewquota.cxx build/obj/loadnewquota.ec
	esql -c -cc -x c++ -I../../ext/libtpld/include  -I../../ext/libtpld/include/libtpld  -I../../ext/pplib/include -I../common -D ESQL_C \
                                   -std=c++0x -pedantic-errors -Wall -Wextra -Wno-unused-variable -Wno-missing-field-initializers \
                                   -Wno-unused-but-set-variable -Wno-sign-compare -Wno-long-long -Wno-format -Wno-comment \
                                   -O2 -s -DNDEBUG \
                                   -D strtk_no_tr1_or_boost -O2 -s -DNDEBUG build/obj/loadnewquota.ec -o build/obj/release/loadnewquota.o
	$(CXX) -maix64 -o build/release/loadnewquota.bin \
		build/obj/release/loadnewquota.o -lstdc++ -lm $(INFORMIX_SHARED_LIBS)

