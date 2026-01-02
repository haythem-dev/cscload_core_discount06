##############################################################
#                                                            #
#    makefile for all cdm binaries on unix               #
#                                                            #
##############################################################

debug dbg release rel gccdbg gccrel all clean clean_rel clean_dbg clean_gcc rel_clean dbg_clean gcc_clean dodeps copy: FORCE
	cd ./zpldcust ; $(MAKE) $@;
	
help: FORCE
	@echo "  make              : update (compile and link) (debug)";
	@echo "  make all          : update (compile and link) $(TARGET_NAME) (all versions)";
	@echo "  make release      : create release version   ";
	@echo "  make debug        : create debug version  ";
	@echo "  make gccdbg       : create gcc debug version  ";
	@echo "  make clean        : delete all versions (*.o and temporary files)";
	@echo "  make clean_rel    : delete release version ";
	@echo "  make clean_dbg    : delete debug version ";
	@echo "  make clean_gcc    : delete gcc version  ";
	@echo "  make copy         : publish release binary";
	@echo "  make dodeps       : scan all cpp-Files to find out all dependencies:\n" \
              "                  	all resolved dependencies are piped in the file 'deps'(dependencies),\n" \
              "                  	the unresolved ones in 'depsnf' (dependencies not found).";
	@echo "";
	
FORCE:
