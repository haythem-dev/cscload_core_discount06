#ifndef GUARD_AAPSERV_CSC_ORDER_IMPORT_H
#define GUARD_AAPSERV_CSC_ORDER_IMPORT_H

#include <iostream>
#include <fstream>
#include <string>
#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_definitions.h>
#include <parameter/csvorderimport/icscorderimportcsvformatsptr.h>
#include <parameter/csvorderimport/icscorderimportfieldsptr.h>

enum OrdImpMessagesEnum
{
	CMSG_ORDIMPORT_PROCESSING = 1000,                     // "Processing  "
	CMSG_ORDIMPORT_EMPTY_LINE = 1001,                     // "empty line!"
	CMSG_ORDIMPORT_INVALID_FORMAT = 1002,                 // "Invalid Format: "
	CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD = 1003,        // "Missing mandatory fields"
	CMSG_ORDIMPORT_UNKNOWN_SERVICE_TYPE = 1004,           // "Service type '%s' do not exist"
	CMSG_ORDIMPORT_MISSING_ARTCODE_OR_ARTDESC = 1005,     // "At least one of articlecode or articledescription should be filled"
	CMSG_ORDIMPORT_ARTCODE_NOTFOUND = 1006,               // "ArticleCode %s not found"
	CMSG_ORDIMPORT_ORD_OPEN_FAILED = 1007,                // "Order could not be opened!"
	CMSG_ORDIMPORT_ORD_OPENED = 1008,                     // "Order %ld opened for branch %d, CustomerNo %d"
	CMSG_ORDIMPORT_ORD_TYPE_COMM_LABEL = 1009,            // "OrderType %s, commission %c, Booking type %c, Tour %s, Label %s"
	CMSG_ORDIMPORT_ORD_TYPE_COMM = 1010,                  // "OrderType %s, commission %c, Booking type %c, Tour %s"
	CMSG_ORDIMPORT_DATE_VALUE = 1011,                     // " Date value %ld.%ld.%ld"
	CMSG_ORDIMPORT_DATE_EXTRAD = 1012,                    // " Date delivery %ld.%ld.%ld"
	CMSG_ORDIMPORT_EMPTY_ORD_CANCELED = 1013,             // "Order cancelled because there are no valid items\n"
	CMSG_ORDIMPORT_ORD_CANCELED_VALID_INVALID = 1014,     // "Order cancelled with %d positions and %d invalid positions\n"
	CMSG_ORDIMPORT_ORD_CANCELED_VALID = 1015,             // "Order Cancelled with %d Positions\n"
	CMSG_ORDIMPORT_ORD_OK_VALID_INVALID = 1016,           // "Order with %d positions and %d invalid positions\n"
	CMSG_ORDIMPORT_ORD_OK_VALID = 1017,                   // "Order with %d positions\n"
	CMSG_ORDIMPORT_SERVICETYPE_NOTFOUND = 1018,           // "Service Type %s not found"
	CMSG_ORDIMPORT_SERVICE_NOTFOUND = 1019,               // "Service %s does not exist or not assigned to Service Type %s"
	CMSG_ORDIMPORT_VAT_RATE_MUST = 1020,                  // "VAT rate must be 0 = FULLTAX or 1 = HALFTAX or included in taxrates table"
	CMSG_ORDIMPORT_ARTCODE_QUANTITY_FAILED = 1021,        // "   ArticleCode %s with quantity %d failed  %s"
	CMSG_ORDIMPORT_ARTCODE_CONFIRMED_ORD_QUANTITY = 1022, // "   Position ordered quantity %ld confirmed quantity %ld ArticleCode %s  %s"
	CMSG_ORDIMPORT_MISSING_FIELD = 1023,                  // "Format reference column %d but input file contains only %d columns"
	CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE_FORMAT = 1024,       // "Unknown Field Type in Format"
	CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE = 1025,              // "Unknown field type"
	CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD_LINE = 1026,   // "Mandatory field %s not supplied in line %d"
	CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE_LINE = 1027,         // "Unknown Field Type in line %d" 
	CMSG_ORDIMPORT_ORD_CREATED_POSTIONS = 1028,			 // "%d Orders created with %d total Positions"
	CMSG_ORDIMPORT_CREATE_ORD_OUTOF_SESSION_BRANCH = 1029, // "Trying to create order in branch %d, outside user session branch %d"
	CMSG_ORDIMPORT_SUCCESS_FETCH_ORDERS = 1030,			  // "Successfully fetched %i orders for a total of %i rows"
	CMSG_ORDIMPORT_FAIL_FETCH_ORDERS = 1031,				  // "Failed Fetching Orders: %i valid orders, %i invalid orders, %i bad rows detected"
	CMSG_ORDIMPORT_STATUS = 1032,						  // "Status"
	CMSG_ORDIMPORT_REMARKS = 1033,				          // "Remarks"
	CMSG_ORDIMPORT_ORDER_NR = 1034,						  // "Order Nr"
	CMSG_ORDIMPORT_GETFORMAT_FAILURE = 1035,				  // "Failed to get Format ID= %i - %s"
	CMSG_ORDIMPORT_FAILURE_VALIDATE_INT = 1036,			  // "Failed to validate Integer Field! current value '%s'"
	CMSG_ORDIMPORT_FAILURE_VALIDATE_DOUBLE = 1037,	      // "Failed to validate double Field! format [xxxx,xxx] current value '%s'"
	CMSG_ORDIMPORT_FAILURE_VALIDATE_DATE = 1038,	          // "Failed to validate date Field! format [dd.mm.yyyy] current value '%s'"
	CMSG_ORDIMPORT_FAILURE_VALIDATE_NUMSTRING = 1039,      // "Failed to validate numeric string Field! current value '%s'"
	CMSG_ORDIMPORT_USED_FORMAT = 1040,				      // "Proccessing file using format %ld: %s"	
	CMSG_ORDIMPORT_OPEN_FILE_ERROR = 1041,				  // "Can't open file %s (possible file not found or missing permissions)"
	CMSG_ORDIMPORT_CREATE_ORDERS_FAILED = 1042,            // "Fatal Error on creation of orders - see details in report file  %s"
	CMSG_ORDIMPORT_IMPORT_FORMAT_FAILED = 1043,            // "Can't import File '%s', using Format %ld - '%s' - see details in report file '%s'"
	CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD = 1044         // "Failed to validate Field [" + importfieldname + "]: " + fieldErrMsg + "\n"
};

enum OrdImpReturnCodeEnum
{
	OrdImpRCSuccess = 0,
	OrdImpRCFormatNotFound = 1,
	OrdImpRCInputFileFailed = 2,
	OrdImpRCReportFileFailed = 3,
	OrdImpRCCreateOrdersError = 4,
	OrdImpRCWrongFormat = 5
};

extern std::map< OrdImpMessagesEnum, std::string > OrdImpMessagesMapDE;
extern std::map< OrdImpMessagesEnum, std::string > OrdImpMessagesMapEN;

class pxSession;
class pxOrder;

class CSCOrderImport
{
	typedef struct T_STRING {
		std::string Field;
		std::string strField;
		short IsGrouping;
	} t_string;

	typedef struct T_SHORT {
		short Field;
		std::string strField;
		short IsGrouping;
	} t_short;

	typedef struct T_INT {
		int Field;
		std::string strField;
		short IsGrouping;
	} t_int;

	typedef struct T_DOUBLE {
		double Field;
		std::string strField;
		short IsGrouping;
	} t_double;

	typedef struct T_BOOL {
		double Field;
		std::string strField;
		short IsGrouping;
	} t_bool;

	typedef struct T_FELDER {
		t_short branchno;
		t_int customerno;
		t_string ordertype;
		t_string pickingtype;
		t_string bookingtype;
		t_string orderremark;
		t_string articlecode;
		t_int orderqty;
		t_string posremark;
		t_double aep;
		t_double gep;
		t_double porto;
		t_string articledescription;
		t_double dicountpercentage;
		t_short vatlevel;
		t_string headremark;
		t_int datevaluta;
		t_int datedelayeddelivery;
		t_string orderlabel;
		t_short restdelivery;
		t_string servicetype;
		t_string service;
	} t_felder;

	class t_postion {
	public:
		t_postion() {
			lineNo = 0;
			articleNo = 0;
			orderqty = 0;
			posremark = "";
			aep = 0.0;
			gep = 0.0;
			porto = 0.0;
			dicountpercentage = 0.0;
			restdelivery = 0;
		}
		void set(t_felder &values) 
		{
			articlecode = values.articlecode.Field;
			orderqty = values.orderqty.Field;
			posremark = values.posremark.Field;
			aep = values.aep.Field;
			gep = values.gep.Field;
			porto = values.porto.Field;
			articledescription = values.articledescription.Field;
			dicountpercentage = values.dicountpercentage.Field;
			servicetype = values.servicetype.Field;
			service = values.service.Field;
			restdelivery = values.restdelivery.Field;

			str_articlecode = values.articlecode.strField;
			str_orderqty = values.orderqty.strField;
			str_posremark = values.posremark.strField;
			str_aep = values.aep.strField;
			str_gep = values.gep.strField;
			str_porto = values.porto.strField;
			str_articledescription = values.articledescription.strField;
			str_dicountpercentage = values.dicountpercentage.strField;
			str_servicetype = values.servicetype.strField;
			str_service = values.service.strField;
			str_restdelivery = values.restdelivery.strField;
		}
		void get(t_felder& values)
		{
			values.articlecode.Field = articlecode;
			values.orderqty.Field = orderqty;
			values.posremark.Field = posremark;
			values.aep.Field = aep;
			values.gep.Field = gep;
			values.porto.Field = porto;
			values.articledescription.Field = articledescription;
			values.dicountpercentage.Field = dicountpercentage;
			values.servicetype.Field = servicetype;
			values.service.Field = service;
			values.restdelivery.Field = restdelivery;

			values.articlecode.strField = str_articlecode;
			values.orderqty.strField = str_orderqty;
			values.posremark.strField = str_posremark;
			values.aep.strField = str_aep;
			values.gep.strField = str_gep;
			values.porto.strField = str_porto;
			values.articledescription.strField = str_articledescription;
			values.dicountpercentage.strField = str_dicountpercentage;
			values.servicetype.strField = str_servicetype;
			values.service.strField = str_service;
			values.restdelivery.strField = str_restdelivery;
		}
		// computed/generated fields
		int lineNo;
		int articleNo;

		// position fields
		std::string articlecode;
		int orderqty;
		std::string posremark;
		double aep;
		double gep;
		double porto;
		std::string articledescription;
		double dicountpercentage;
		std::string servicetype;
		std::string service;
		short restdelivery;

		// csv parsed fields values
		std::string str_articlecode;
		std::string str_orderqty;
		std::string str_posremark;
		std::string str_aep;
		std::string str_gep;
		std::string str_porto;
		std::string str_articledescription;
		std::string str_dicountpercentage;
		std::string str_servicetype;
		std::string str_service;
		std::string str_restdelivery;

		// additonal validation columns
		std::string	validationStatus; // { "Ok", "Warnings", "Errors" }
		std::string	validationRemarks; // list of warning, errors messages, separated by end of line \n marker for better errors readability in output csv
	};

	class t_order {
	public:
		t_order() {
			lineNo = 0;
			OrderNr = 0;
			validationStatus = "";
			validationRemarks = "";
			closingRemarks = "";

			customerno = 0;
			branchno = 0;
			ordertype = "";
			pickingtype = "";
			bookingtype = "";
			orderremark = "";
			headremark = "";
			datevaluta = 0;
			datedelayeddelivery = 0;
			orderlabel = "";
			servicetype = "";
			service = "";
		}
		void set(t_felder& values)
		{
			customerno = values.customerno.Field;
			branchno = values.branchno.Field;
			ordertype = values.ordertype.Field;
			pickingtype = values.pickingtype.Field;
			bookingtype = values.bookingtype.Field;
			orderremark = values.orderremark.Field;
			headremark = values.headremark.Field;
			datevaluta = values.datevaluta.Field;
			datedelayeddelivery = values.datedelayeddelivery.Field;
			orderlabel = values.orderlabel.Field;
			servicetype = values.servicetype.Field;
			service = values.service.Field;

			str_customerno = values.customerno.strField;
			str_branchno = values.branchno.strField;
			str_ordertype = values.ordertype.strField;
			str_pickingtype = values.pickingtype.strField;
			str_bookingtype = values.bookingtype.strField;
			str_orderremark = values.orderremark.strField;
			str_headremark = values.headremark.strField;
			str_datevaluta = values.datevaluta.strField;
			str_datedelayeddelivery = values.datedelayeddelivery.strField;
			str_orderlabel = values.orderlabel.strField;
			str_servicetype = values.servicetype.strField;
			str_service = values.service.strField;
		}
		void get(t_felder& values)
		{
			values.customerno.Field = customerno;
			values.branchno.Field = branchno;
			values.ordertype.Field = ordertype;
			values.pickingtype.Field = pickingtype;
			values.bookingtype.Field = bookingtype;
			values.orderremark.Field = orderremark;
			values.headremark.Field = headremark;
			values.datevaluta.Field = datevaluta;
			values.datedelayeddelivery.Field = datedelayeddelivery;
			values.orderlabel.Field = orderlabel;
			values.servicetype.Field = servicetype;
			values.service.Field = service;

			values.customerno.strField = str_customerno;
			values.branchno.strField = str_branchno;
			values.ordertype.strField = str_ordertype;
			values.pickingtype.strField = str_pickingtype;
			values.bookingtype.strField = str_bookingtype;
			values.orderremark.strField = str_orderremark;
			values.headremark.strField = str_headremark;
			values.datevaluta.strField = str_datevaluta;
			values.datedelayeddelivery.strField = str_datedelayeddelivery;
			values.orderlabel.strField = str_orderlabel;
			values.servicetype.strField = str_servicetype;
			values.service.strField = str_service;
		}

		// computed/generated fields
		int lineNo;

		// order fields
		int customerno;
		short branchno;
		std::string ordertype;
		std::string pickingtype;
		std::string bookingtype;
		std::string orderremark;
		std::string headremark;
		int datevaluta;
		int datedelayeddelivery;
		std::string orderlabel;
		std::string servicetype;
		std::string service;

		// csv parsed fields values
		std::string str_customerno;
		std::string str_branchno;
		std::string str_ordertype;
		std::string str_pickingtype;
		std::string str_bookingtype;
		std::string str_orderremark;
		std::string str_headremark;
		std::string str_datevaluta;
		std::string str_datedelayeddelivery;
		std::string str_orderlabel;
		std::string str_servicetype;
		std::string str_service;
		// additonal validation columns
		std::string	validationStatus; // { "Ok", "Warnings", "Errors" }
		std::string	validationRemarks; // list of warning, errors messages, separated by end of line \n marker for better errors readability in output csv
		std::string	closingRemarks; // list of messages, warnings, errors messages generated while closing the order, separated by end of line \n marker for better errors readability in output csv
		long	    OrderNr;
		// list of order positions
		std::vector<t_postion> listPositions;
	};

public:
	CSCOrderImport(pxSession &ps);
	virtual ~CSCOrderImport();
	int GenerateOrders(const std::string& input, const std::string& output, const std::string& orgfile, const std::string& reportfile, int FormatID, const std::string& FormatName, const std::string& language = "DE");
	int FetchOrders();
	bool CreateOrders();
	bool GetFormat();
	int OpenFile();
	int CloseFile();
	int OpenLogFile();
	int WriteLogFile();
	int CloseLogFile();
	int OpenOrder();
	int CloseOrder();
	int WritePos(bool isService = false);
	int WriteTextPos();
	int FillStruct();
	bool GetRow(int orderIdx, int posIdx, std::vector<std::string>& outRow);
	void InitFelder();
	void CopyFelder();
	bool CheckGrouping();
	bool ExportOrders(bool onlyFaulty = false);
	bool CsvGetNextRow(std::vector<std::string>& curRow, bool &emptyRow);
	const std::string& GetMessage(OrdImpMessagesEnum messageID);
	// typed validations functions
	bool IsInteger32(const char *input, std::string& errMsg);
	bool IsDate(const char* input, std::string& errMsg); // dd.mm.yyyy format
	bool IsDouble(const char* input, std::string& errMsg); // nnnn,nnn format
	bool IsNumericString(const char* input, std::string& errMsg); // should contain only numeric char after trimming

protected:
	bool CsvGetNextColumn(char* out, size_t maxOutSize, bool* newRow = NULL, bool* overLength = NULL);
	char CsvGetNextByte();
	int	formatMaxPosition;
	std::map<int, std::string> mapFieldIDToName;
	std::string m_input;
	std::string m_orgfile;
	std::vector< std::vector<std::string> > headRows; // store rows before the start data line
	std::vector<std::string> curCSVRow;
	basar::VarString m_output;
	basar::Int32 m_FormatID;
	pxSession *psession;                           //Pointer auf die Session
	std::ifstream inputfile;
	std::ofstream outputfile;
	basar::VarString m_line;
	bool m_bWriteLog;
	bool m_bOrderOpen;
	bool m_bSwitchOrder;
	libcsc::parameter::ICSCOrderImportCSVFormatsPtr m_format;
	libcsc::parameter::ICSCOrderImportFieldsCollectionPtr m_fieldtypes;
	t_felder m_Felder;
	t_felder m_Felder_old;

	int ordercount;
	int orderposcount;
	int orderposread;
	int totalposcount;

	short m_count;

	pxOrder      *order;                       //Auftrag

	std::map< OrdImpMessagesEnum, std::string > *curMessagesMap;
	// memory staging validation
	std::vector<t_order> m_listOrders;
	char reportCsvFileName[256];

	// csv parser
	bool isEOF;
	bool lastCharIsDelimiter;
	int  lineCount;
	int  lastAvailableByte;
	char csvDelimiter;
	char currByte;
};

#endif // GUARD_AAPSERV_CSC_ORDER_IMPORT_H
