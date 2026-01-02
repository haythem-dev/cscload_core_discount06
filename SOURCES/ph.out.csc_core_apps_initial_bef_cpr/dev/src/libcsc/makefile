#================================================================================
#   libcsc makefile
#   10.09.2014
#   v 1.0.0
#================================================================================

#--------------------------------------------------------------------------------
# build artifact 
#--------------------------------------------------------------------------------

TARGET         = libcsc.a

#--------------------------------------------------------------------------------
# include common library versions and library depends 
#--------------------------------------------------------------------------------
BASEDIR        = ..
VARS_FILE      = $(BASEDIR)/makevars.inc
include $(VARS_FILE)

DEPLOYMENT_DIR = $(MARATHON_DIR)/orderentry/libcsc

#---------------------------------------------------------------------------------
# source directories
#---------------------------------------------------------------------------------

# sources (seperated with blank if more than one directory)
DIR_SRCS       = \
	blockedarticles \
	blockedarticles/componentmanager \
	callback/componentmanager \
	callback/domainmodule \
	callback/exceptions \
	callback/repository \
	callback/usecase \
	crema \
	crema/repository \
	crema/componentmanager \
	crema/guidata \
	crema/maildata \
	crema/reason \
	crema/orderdata \
	crema/usersuggestion \
	crema/cremaorder \
	crema/creditlimitdata \
	customer \
	customer/componentmanager \
	customer/customercondition \
	customer/tenderinfo \
	customer/articleinfo \
	customer/orderinfo \
	customer/orderstatus \
	customer/turnover \
	customer/changedquantities \
	customer/discountaccount \
	customer/promotions \
	customer/routes \
	customer/pricesanddiscounts \
	customer/payments \
	customer/paymentconditions \
    customer/tours \
	customer/tours/weektours \
	datatypes \
	discount/basevalues/discountbasevalue \
	discount/basevalues/orderbasevalue \
	discount/calculator \
	discount/calculator/commands \
	discount/componentmanager \
	discount/discountcollectionfinder \
	discount/logger/discountlogger \
	discount/logger/hierarchylogger \
	discount/orderpositiondiscount \
	discount/orderpositiondiscountprocessed \
	discount/resultprocessor \
	discount/tender \
	discount/tender/repository \
	discount/tender/sqlmapper \
	discount/usecase \
	document/componentmanager \
	document/deliveryadvice \
	document/deliveryadvice/deliveryadviceline \
	document/deliveryadvice/deliveryadvicelineibtlink \
	document/documentarchiveinfo \
	document/documentprintinfo \
	document/narcoticarchive \
	document/taxrates \
	tender \
	tender/componentmanager \
	tender/repository \
	tender/sqlmapper \
	exceptions \
	ibt/articlequotachecker \
	ibt/bookingcompletedchecker \
	ibt/componentmanager \
	ibt/environmentchecker \
	ibt/exceptions \
	ibt/ibtbranch \
	ibt/ibtrequest \
	ibt/ibtrequest/discount \
	ibt/ibtrequest/remark \
	ibt/ibtresponse \
	ibt/transportexclusionchecker \
	ibt/usecase \
	ibt/bulkrangeselector \
	logger \
	msv3/componentmanager \
	msv3/transmissionresponse \
	msv3/orderresponse \
	msv3/customerdata \
	msv3/documentarchiveinfo \
	parameter \
	parameter/componentmanager \
	parameter/csvorderimport \
	persistence \
	procurementpermission/componentmanager \
	procurementpermission/repository \
	util \
	base/usecase \
	returns/componentmanager \
	returns/returnannouncement \
	returns/returnannouncement/returnannouncementhead \
	returns/returnannouncement/returnannouncementpos \
	returns/returnperiod \
	returns/returnrulebook \
	returns/returnpositioncheckuc \
	subseqdelivery/componentmanager \
	subseqdelivery/workupcompletedchecker \
	stockbooking/componentmanager \
	stockbooking/bulkrangeselector \
	stockbooking/longtermlack \
	stockbooking/reservation \
	stockbooking/reservationconfig \
	cscorder \
	cscorder/componentmanager \
	cscorder/exceptions \
	cscorder/repository \
	cscorder/csccallplan \
	cscorder/cscorderflags \
	cscorder/usecase \
    cscorder/cscorderibtpickingdata \
    cscorderpos \
    cscorderpos/componentmanager \
    cscorderpos/cscorderpossplittinfo \
	cscordertype \
	cscordertype/componentmanager \
	cscordertype/cscordertypebatchconfig \
	cscordertype/ordertypeflagtype \
	cscordertype/repository \
	cscordertype/sqlmapper \
	workingdayscalendar \
	workingdayscalendar/componentmanager \
	shipmenttracking \
	shipmenttracking/componentmanager \
	shipmenttracking/configuration \
	shipmenttracking/packageinformation \
	shipmenttracking/tourinformation \
	
# headers (seperated with blank if more than one directory)
DIR_INCS       = . $(DIR_SRCS)

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
INCS           = -I. $(BASAR_INC) $(BOOST_INC) $(LOG4CPLUS_INC) \
                 $(PXDB_INC) $(PXVERBUND_INC) $(CXXTOOLS_INC) $(LIBLOCKMANAGER_INC)

#--------------------------------------------------------------------------------
# build rules includes
#--------------------------------------------------------------------------------

BUILD_RULES_FILE = $(MARATHON_DIR)/make/makefile.inc
include $(BUILD_RULES_FILE)

