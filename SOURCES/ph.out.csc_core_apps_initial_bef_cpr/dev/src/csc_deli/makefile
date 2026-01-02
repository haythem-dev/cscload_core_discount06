#=============================================================
#   recursive makefile
#   04.07.2013
#   v 1.0.0
#=============================================================

#-------------------------------------------------------------
# subprojects
#-------------------------------------------------------------

SUBPROJECTS = libcsc_deli csc_deli

#-------------------------------------------------------------
# TOOLS
#-------------------------------------------------------------

# path
TOOL_PATH     = $(DEVLIB_PATH)/marathon/make

BUILD_STATUS  = $(TOOL_PATH)/build-status
CREATETAG     = $(TOOL_PATH)/createtag

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

dev:
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

cleandev:
	$(BUILD_RECUR)

#-------------------------------------------------------------
# tag target
#-------------------------------------------------------------

checktag:
	$(BUILD_RECUR)

tag: checktag
	$(BUILD_STATUS) -f $(BUILD_XML)
	@$(CREATETAG) -i minor -u .

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

