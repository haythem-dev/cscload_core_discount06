//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       26.12.2010
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_PROPERTIES_PROPERTY_DEFINITIONS_H
#define GUARD_PROPERTIES_PROPERTY_DEFINITIONS_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include <libbasarproperty.h>

//--------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------//
namespace properties
{
	namespace pharmostransaction
	{
		CONST_PROPERTY_DESCRIPTION(	BRANCHNO,							"branchno",								basar::INT16 )
		CONST_PROPERTY_DESCRIPTION( CREATIONDATETIME,					"creationdatetime",						basar::DATETIME )
		CONST_PROPERTY_DESCRIPTION( VSEOFFSET,							"vseoffset",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( PROCESSINGSTATUS,					"processingstate",						basar::STRING )
		CONST_PROPERTY_DESCRIPTION( PROCESSEDTIMESTAMP,					"processedtimestamp",					basar::DATETIME )
		CONST_PROPERTY_DESCRIPTION( TRANSFERREDTIMESTAMP,				"transferredtimestamp",					basar::DATETIME )
		CONST_PROPERTY_DESCRIPTION( DATASETSEQUENCENO,					"datasetsequenceno",					basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( RECORDTYPE,							"recordtype",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	CUSTOMERNO,							"customerno",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	BOOKINGTYPE,						"bookingtype",							basar::INT16 )
		CONST_PROPERTY_DESCRIPTION(	USERID,								"userid",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION(	INVOICENO,							"invoiceno",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	INVOICETIMESTAMP,					"invoicetimestamp",						basar::DATETIME )
		CONST_PROPERTY_DESCRIPTION(	CUSTOMERORDERNO,					"customerorderno",						basar::INT32 )
		CONST_PROPERTY_DESCRIPTION(	CSCORDERNO,							"cscorderno",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	TURNOVER,							"turnover",								basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	PAYMENTDATE,						"paymentdate",							basar::DATE )
		CONST_PROPERTY_DESCRIPTION(	PAYMENTTYPE,						"paymenttype",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	PRICETYPE,							"pricetype",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	CHAINNO,							"chainno",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION(	REMAININGDISCACCVALUE,				"remainingdiscaccvalue",				basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	INVOICEVALUE,						"invoicevalue",							basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	DISCACCOPERATIONNO,					"discaccoperationno",					basar::INT32 )
		CONST_PROPERTY_DESCRIPTION(	PRIORITY,							"priority",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION(	VOUCHERTYPE,						"vouchertype",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	ARTICLENO,							"articleno",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION(	BATCH,								"batch",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	EXPIRYDATE,							"expirydate",							basar::DATE )
		CONST_PROPERTY_DESCRIPTION(	QUANTITY,							"quantity",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION(	DEBITVALUE,							"debitvalue",							basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	LIMITVALUE,							"limitvalue",							basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	SUPPLIERNO,							"supplierno",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION(	PURCHASEORDERNO,					"purchaseorderno",						basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	COSTPRICE,							"costprice",							basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	STORAGELOCATION,					"storagelocation",						basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	STORAGEAREA,						"storagearea",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	STATIONNO,							"stationno",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	EXPIRYDATECHANGEFLAG,				"expirydatechangeflag",					basar::INT16 )
		CONST_PROPERTY_DESCRIPTION(	STORAGELOCATIONCHANGEFLAG,			"storagelocationchangeflag",			basar::INT16 )
		CONST_PROPERTY_DESCRIPTION(	COSTPRICECHANGEFLAG,				"costpricechangeflag",					basar::INT16 )
		CONST_PROPERTY_DESCRIPTION(	PHARMACYPURCHASEPRICECHANGEFLAG,	"pharmacypurchasepricechangeflag",		basar::INT16 )
		CONST_PROPERTY_DESCRIPTION(	PHARMACYSELLPRICECHANGEFLAG,		"pharmacysellpricechangeflag",			basar::INT16 )
		CONST_PROPERTY_DESCRIPTION(	PHARMACYPURCHASEPRICE,				"pharmacypurchaseprice",				basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	PHARMACYSELLPRICE,					"pharmacysellprice",					basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	IBTBRANCHNO,						"ibtbranchno",							basar::INT16 )
		CONST_PROPERTY_DESCRIPTION(	CODEBLOCAGE,						"codeblocage",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION( QUANTITYNATRA,						"quantitynatra",						basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( ORDERPOSITIONNO,					"orderpositionno",						basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( DAILYCLOSING,						"dailyclosing",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( ORIGIN,								"origin",								basar::INT16 )
		CONST_PROPERTY_DESCRIPTION( ORDERSUPPLIERNO,					"ordersupplierno",						basar::INT32 )
	}

	namespace dkbvz
	{
		CONST_PROPERTY_DESCRIPTION( DX01DATE,							"kbvzdx01date",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( RECORDOFFSET,						"kbvzoffset",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( CSCPROCESSINGSTATUS,				"kbvzksc",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION( CSCPROCESSINGTIME,					"kbvzksctime",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( DX01PROCESSINGTIME,					"kbvzdx01time",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( SEQUENCENO,							"kbvzlfdnr",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZFIL,							"kbvzfil",								basar::INT16 )
		CONST_PROPERTY_DESCRIPTION( KBVZPZN,							"kbvzpzn",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZMENG,							"kbvzmeng",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZBUKZ,							"kbvzbukz",								basar::INT16 )
		CONST_PROPERTY_DESCRIPTION( KBVZART,							"kbvzart",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZTIME,							"kbvztime",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZDATE,							"kbvzdate",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZLGFNR,							"kbvzlgfnr",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZKSCANR,							"kbvzkscanr",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZLGNR,							"kbvzlgnr",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZSTAT,							"kbvzstat",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZET3,							"kbvzet3",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZWBER,							"kbvzwber",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZVERF,							"kbvzverf",								basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZP1POS,							"kbvzp1pos",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZGEP,							"kbvzgep",								basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION( KBVZAEP,							"kbvzaep",								basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION( KBVZAVP,							"kbvzavp",								basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION(	KBVZKVERF,							"kbvzkverf",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	KBVZKLGFNR,							"kbvzklgfnr",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	KBVZKGEP,							"kbvzkgep",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	KBVZKAEP,							"kbvzkaep",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	KBVZKAVP,							"kbvzkavp",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION(	KBVZMFIL,							"kbvzmfil",								basar::INT16 )
		CONST_PROPERTY_DESCRIPTION( KBVZSTATUS,							"kbvzstatus",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZEXPORT,							"kbvzexport",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZWERT,							"kbvzwert",								basar::DECIMAL )
		CONST_PROPERTY_DESCRIPTION( KBVZCLOSA,							"kbvzclosa",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZCLOZEIT,						"kbvzclozeit",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZCLOANR,							"kbvzcloanr",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZCLOPOS,							"kbvzclopos",							basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZCHARGE,							"kbvzcharge",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZBATCH,							"kbvzbatch",							basar::STRING )
		CONST_PROPERTY_DESCRIPTION( KBVZTADATUM,                        "kbvztadatum",                          basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( KBVZBESLANR,						"kbvzbeslanr",							basar::INT32 )
	}

	namespace ctransfercsc
	{
		CONST_PROPERTY_DESCRIPTION( ZDPHOST,							"zdphost",								basar::STRING )
		CONST_PROPERTY_DESCRIPTION( ZDPDATABASE,						"zdpdatabase",							basar::STRING )

		CONST_PROPERTY_DESCRIPTION( TRANSFERID,                         "transferid",                           basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( ENTRYDATETIME,                      "entrydatetime",                        basar::DATETIME )
		CONST_PROPERTY_DESCRIPTION( ARTICLENO,                          "articleno",                            basar::INT32 )
		CONST_PROPERTY_DESCRIPTION( FIELDNAME,                          "fieldname",                            basar::STRING )
		CONST_PROPERTY_DESCRIPTION( FIELDVALUE,                         "fieldvalue",                           basar::STRING )
		CONST_PROPERTY_DESCRIPTION( PROCESSEDFLAG,                      "processedflag",                        basar::INT16 )
	}

} // end namespace properties

#endif // GUARD_PROPERTIES_PROPERTY_DEFINITIONS_H

