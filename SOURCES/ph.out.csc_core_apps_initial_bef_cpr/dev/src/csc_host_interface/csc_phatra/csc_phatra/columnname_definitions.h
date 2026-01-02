//--------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Steffen Heinlein
 *  \date       09.07.2012
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_COLUMNNAMES_COLUMNNAME_DEFINITIONS_H
#define GUARD_COLUMNNAMES_COLUMNNAME_DEFINITIONS_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------//
namespace columnnames
{
	namespace pharmostransaction
	{
		const basar::VarString BRANCHNO( "branchno" );
		const basar::VarString CREATIONDATETIME( "creationdatetime" );
		const basar::VarString VSEOFFSET( "vseoffset" );
		const basar::VarString PROCESSINGSTATUS( "processingstate" );
		const basar::VarString PROCESSEDTIMESTAMP( "processedtimestamp" );
		const basar::VarString TRANSFERREDTIMESTAMP( "transferredtimestamp" );
		const basar::VarString DATASETSEQUENCENO( "datasetsequenceno" );
		const basar::VarString RECORDTYPE( "recordtype" );
		const basar::VarString CUSTOMERNO( "customerno" );
		const basar::VarString BOOKINGTYPE( "bookingtype" );
		const basar::VarString USERID( "userid" );
		const basar::VarString INVOICENO( "invoiceno" );
		const basar::VarString INVOICETIMESTAMP( "invoicetimestamp" );
		const basar::VarString CUSTOMERORDERNO( "customerorderno" );
		const basar::VarString CSCORDERNO( "cscorderno" );
		const basar::VarString TURNOVER( "turnover" );
		const basar::VarString PAYMENTDATE( "paymentdate" );
		const basar::VarString PAYMENTTYPE( "paymenttype" );
		const basar::VarString PRICETYPE( "pricetype" );
		const basar::VarString CHAINNO( "chainno" );
		const basar::VarString REMAININGDISCACCVALUE( "remainingdiscaccvalue" );
		const basar::VarString INVOICEVALUE( "invoicevalue" );
		const basar::VarString DISCACCOPERATIONNO( "discaccoperationno" );
		const basar::VarString PRIORITY( "priority" );
		const basar::VarString VOUCHERTYPE( "vouchertype" );
		const basar::VarString ARTICLENO( "articleno" );
		const basar::VarString BATCH( "batch" );
		const basar::VarString EXPIRYDATE( "expirydate" );
		const basar::VarString QUANTITY( "quantity" );
		const basar::VarString DEBITVALUE( "debitvalue" );
		const basar::VarString LIMITVALUE( "limitvalue" );
		const basar::VarString SUPPLIERNO( "supplierno" );
		const basar::VarString PURCHASEORDERNO( "purchaseorderno" );
		const basar::VarString COSTPRICE( "costprice" );
		const basar::VarString STORAGELOCATION( "storagelocation" );
		const basar::VarString STORAGEAREA( "storagearea" );
		const basar::VarString STATIONNO( "stationno" );
		const basar::VarString EXPIRYDATECHANGEFLAG( "expirydatechangeflag" );
		const basar::VarString STORAGELOCATIONCHANGEFLAG( "storagelocationchangeflag" );
		const basar::VarString COSTPRICECHANGEFLAG( "costpricechangeflag" );
		const basar::VarString PHARMACYPURCHASEPRICECHANGEFLAG( "pharmacypurchasepricechangeflag" );
		const basar::VarString PHARMACYSELLPRICECHANGEFLAG( "pharmacysellpricechangeflag" );
		const basar::VarString PHARMACYPURCHASEPRICE( "pharmacypurchaseprice" );
		const basar::VarString PHARMACYSELLPRICE( "pharmacysellprice" );
		const basar::VarString IBTBRANCHNO( "ibtbranchno" );
		const basar::VarString CODEBLOCAGE( "codeblocage" );
		const basar::VarString QUANTITYNATRA( "quantitynatra" );
		const basar::VarString ORDERPOSITIONNO( "orderpositionno" );
		const basar::VarString DAILYCLOSING( "dailyclosing" );
		const basar::VarString ORIGIN( "origin" );
		const basar::VarString ORDERSUPPLIERNO( "ordersupplierno" );
	}

	namespace dkbvz
	{
		const basar::VarString KBVZ_DX01DATE( "KBVZ_DX01DATE" );
		const basar::VarString KBVZ_OFFSET( "KBVZ_OFFSET" );
		const basar::VarString KBVZ_KSC( "KBVZ_KSC" );
		const basar::VarString KBVZ_KSCTIME( "KBVZ_KSCTIME" );
		const basar::VarString KBVZ_DX01TIME( "KBVZ_DX01TIME" );
		const basar::VarString KBVZ_LFDNR( "KBVZ_LFDNR" );
		const basar::VarString KBVZ_FIL( "KBVZ_FIL" );
		const basar::VarString KBVZ_PZN( "KBVZ_PZN" );
		const basar::VarString KBVZ_MENG( "KBVZ_MENG" );
		const basar::VarString KBVZ_BUKZ( "KBVZ_BUKZ" );
		const basar::VarString KBVZ_ART( "KBVZ_ART" );
		const basar::VarString KBVZ_TIME( "KBVZ_TIME" );
		const basar::VarString KBVZ_DATE( "KBVZ_DATE" );
		const basar::VarString KBVZ_LGFNR( "KBVZ_LGFNR" );
		const basar::VarString KBVZ_KSCANR( "KBVZ_KSCANR" );
		const basar::VarString KBVZ_LGNR( "KBVZ_LGNR" );
		const basar::VarString KBVZ_STAT( "KBVZ_STAT" );
		const basar::VarString KBVZ_ET3( "KBVZ_ET3" );
		const basar::VarString KBVZ_WBER( "KBVZ_WBER" );
		const basar::VarString KBVZ_VERF( "KBVZ_VERF" );
		const basar::VarString KBVZ_P1POS( "KBVZ_P1POS" );
		const basar::VarString KBVZ_GEP( "KBVZ_GEP" );
		const basar::VarString KBVZ_AEP( "KBVZ_AEP" );
		const basar::VarString KBVZ_AVP( "KBVZ_AVP" );
		const basar::VarString KBVZ_KVERF( "KBVZ_KVERF" );
		const basar::VarString KBVZ_KLGFNR( "KBVZ_KLGFNR" );
		const basar::VarString KBVZ_KGEP( "KBVZ_KGEP" );
		const basar::VarString KBVZ_KAEP( "KBVZ_KAEP" );
		const basar::VarString KBVZ_KAVP( "KBVZ_KAVP" );
		const basar::VarString KBVZ_MFIL( "KBVZ_MFIL" );
		const basar::VarString KBVZ_STATUS( "KBVZ_STATUS" );
		const basar::VarString KBVZ_EXPORT( "KBVZ_EXPORT" );
		const basar::VarString KBVZ_WERT( "KBVZ_WERT" );
		const basar::VarString KBVZ_CLO_SA( "KBVZ_CLO_SA" );
		const basar::VarString KBVZ_CLO_ZEIT( "KBVZ_CLO_ZEIT" );
		const basar::VarString KBVZ_CLO_ANR( "KBVZ_CLO_ANR" );
		const basar::VarString KBVZ_CLO_POS( "KBVZ_CLO_POS" );
		const basar::VarString KBVZ_CHARGE( "KBVZ_CHARGE" );
		const basar::VarString KBVZ_BATCH( "KBVZ_BATCH" );
		const basar::VarString KBVZ_TADATUM( "KBVZ_TADATUM" );
		const basar::VarString KBVZ_BESLANR("KBVZ_BESLANR");
	}

} // end namespace columnnames

#endif // GUARD_COLUMNNAMES_COLUMNNAME_DEFINITIONS_H

