#=============================================================
#   recursive makefile
#   18.02.2014
#   v 1.0.0
#=============================================================

#-------------------------------------------------------------
# subprojects
#-------------------------------------------------------------

SUBPROJECTS = common \
              delkdkritik \
              delartikelkonto \
              deloldsubsequent \
			  delvaccinsubsequent \
              loadartcom \
              loadarticlecodes \
              loadarticlecodesean \
              loadarticlecodeseanzdp \
              loadarticlelppr \
              loadarticleinfo \
              loadbrancharticleconfig \
              loadchainlimit \
              loadcharge \
              loadconditions \
			  loadcscbeskopfandposi \
              loadcstcalcavp \
              loadcstdiscacc \
              loadcstpharmgrp \
              loadcscarticleprognosis \
			  loadcscbrancharticle \
			  loadpubranchsupplier \
              loadcstshort \
              loadcustgroups \
              loaddealvol \
              loaddebtlimit \
              loaddkkaa \
              loaddkopo \
              loaddktmd \
              loaddrivers \
              loadean \
              loadflyersubsequent \
              loadgeneralcalcavp \
              loadlppr \
			  loadmanufacturer \
			  loadsupplier \
              loadmanufacturergroup \
              loadnewquota \
              loadordercriteria \
              loadpayterm \
              loadpharmgrp \
              loadpharmgrpvse \
              loadpricehistory \
              loadpricelist \
              loadpromoquota \
              loadpromotion \
              loadpromotionscale \
              loadrange \
              loadreimport \
              loadroutecheck \
              loadroutes \
              loadrouting \
              loadroutingms \
		      loadsalesman \
              loadservices \
              loadshortlist \
              loadtempquota \
			  loadpusupplier \
			  loadcscpubatchorderpos \
              loadworkingdayscalendar \
              longtermlackloader \
              resetquota \
              setarticlecategory \
              tpldanrufplan \
              tpldartindex \
              tpldarttext \
              tpldauftr \
              tplddkkui \
              tpldean \
              tpldhercode \
              tpldhipath2 \
              tpldlokalart \
              tpldreimp \
              tpldtour \
              tpldvseauftrag \
              tpldzentknd \
              tpldzentral \

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
# tag target
#-------------------------------------------------------------

checktag:
	$(BUILD_RECUR)
	$(BUILD_STATUS) -f build.xml

pretag: doc

tag: checktag
	@$(CREATETAG) -i patch -u .

#-------------------------------------------------------------
# doc target
#-------------------------------------------------------------
doc:
	cd doc && doc.sh && cd ..

#-------------------------------------------------------------
# install target
#-------------------------------------------------------------
install:
	installhome.sh

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
