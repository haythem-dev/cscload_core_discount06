#=============================================================
#   recursive makefile
#   18.02.2014
#   v 1.0.0
#=============================================================

#-------------------------------------------------------------
# subprojects
#-------------------------------------------------------------

SUBPROJECTS = \
	cxxtools \
	pxdb \
	pxverbund \
	libcsc \
	thrift \
	aaorderclose \
	aapserv \
	clearreservation \
	kscserver \
	csc_host_interface \
	csc_deli \
	ibtorderimport

#-------------------------------------------------------------
# TOOLS
#-------------------------------------------------------------

# path
#TOOL_PATH     = $(DEVLIB_PATH)/marathon/make

#-------------------------------------------------------------
# build recurse macro
#-------------------------------------------------------------

BUILD_RECUR = @+ \
	set -e; \
	for prj in $(SUBPROJECTS); do \
		echo "Entering $$prj"; \
		cd "$$prj";           \
		$(MAKE) $@;           \
		echo "Leaving $$prj"; \
		cd ..;                \
	done

#-------------------------------------------------------------
# build targets
#-------------------------------------------------------------

dbg:
	$(BUILD_RECUR)

all:
	$(BUILD_RECUR)

rel:
	$(BUILD_RECUR)

#-------------------------------------------------------------
# clean generated files
#-------------------------------------------------------------

clean:
	$(BUILD_RECUR)

cleanall:
	$(BUILD_RECUR)

cleandbg:
	$(BUILD_RECUR)

cleanrel:
	$(BUILD_RECUR)

#-------------------------------------------------------------
# doc target
#-------------------------------------------------------------
doc: 
	cd ../doc && doc.sh && cd ../src

#-------------------------------------------------------------
# install target
#-------------------------------------------------------------
install: 
	installhome.sh

#-------------------------------------------------------------
# test target
#-------------------------------------------------------------
test:
	cd sandboxpxverbund && make && run.sh $(DBSERVER)

#-------------------------------------------------------------
# usage
#-------------------------------------------------------------
help:
	@echo ""
	@echo "usage:"
	@echo "  make           : build default configuration"
	@echo "  make all       : build all configurations"
	@echo "  make dbg       : build debug configuration"
	@echo "  make rel       : build release configuration"
	@echo ""
	@echo "  make clean     : delete default configuration"
	@echo "  make cleanall  : delete all configurations"
	@echo "  make cleandbg  : delete debug configuration"
	@echo "  make cleanrel  : delete release configuration"
	@echo ""
	@echo "  make help      : makefile usage"
	@echo ""

.PHONY: doc
