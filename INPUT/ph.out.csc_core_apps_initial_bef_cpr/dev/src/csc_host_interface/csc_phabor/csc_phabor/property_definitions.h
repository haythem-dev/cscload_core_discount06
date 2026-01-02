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
#include "cmndm.h"

//--------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------//
namespace properties
{
	namespace pharmosbatchorderhead
	{
		CONST_PROPERTY_DESCRIPTION(	BRANCHNO,					"branchno",					 basar::INT16		)
		CONST_PROPERTY_DESCRIPTION( CREATIONDATETIME,			"creationdatetime",			 basar::DATETIME	)
		CONST_PROPERTY_DESCRIPTION( VSEOFFSET,					"vseoffset",				 basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( PROCESSINGSTATUS,			"processingstate",			 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( PROCESSEDTIMESTAMP,			"processedtimestamp",		 basar::DATETIME	)
		CONST_PROPERTY_DESCRIPTION( TRANSFERREDTIMESTAMP,		"transferredtimestamp",		 basar::DATETIME	)
		CONST_PROPERTY_DESCRIPTION( POSITIONCOUNT,				"positioncount",			 basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( TRANSFERORDERNO,			"transferorderno",			 basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( BATCHORDERNO,				"batchorderno",				 basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	ORDERTYPE,					"ordertype",				 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	PICKINGTYPE,				"pickingtype",				 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	BOOKINGTYPE,				"bookingtype",				 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	CUSTOMERNO,					"customerno",				 basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	INTERNALCUSTOMERNO,			"internalcustomerno",		 basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	INFOTEXT,					"infotext",					 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	ORIGINTYPE,					"origintype",				 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	ORIGINBRANCHNO,				"originbranchno",			 basar::INT16		)
		CONST_PROPERTY_DESCRIPTION(	CUSTOMERFLAG,				"customerflag",				 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	VALUEDATE,					"valuedate",				 basar::DATE		)
		CONST_PROPERTY_DESCRIPTION(	VALDATADDMONTH,				"valudataddmonth",			 basar::INT16		)
		CONST_PROPERTY_DESCRIPTION(	DELIVERYDATE,				"deliverydate",				 basar::DATE		)
		CONST_PROPERTY_DESCRIPTION(	SAPDELIVERYNOTE,			"sapdeliverynote",			 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	EDIDELIVERYNOTEFLAG,		"edideliverynoteflag",		 basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( PARENTCOMPANYFLAG, 			"parentcompanyflag",		 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION( CSCORDERNO,		 			"cscorderno",				 basar::INT32		)	
	}

	namespace pharmosbatchorderpos
	{
		CONST_PROPERTY_DESCRIPTION(	BRANCHNO, 					"branchno",					 basar::INT16		)  
		CONST_PROPERTY_DESCRIPTION(	CREATIONDATETIME, 			"creationdatetime",			 basar::DATETIME	)	
		CONST_PROPERTY_DESCRIPTION( VSEOFFSET, 					"vseoffset",				 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION( PROCESSINGSTATE, 			"processingstate",			 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION( PROCESSEDTIMESTAMP, 		"processedtimestamp",		 basar::DATETIME	)	
		CONST_PROPERTY_DESCRIPTION( TRANSFERREDTIMESTAMP,		"transferredtimestamp",		 basar::DATETIME	)	
		CONST_PROPERTY_DESCRIPTION( TRANSFERORDERNO, 			"transferorderno",			 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION( TRANSFERORDERPOSNO, 		"transferorderposno",		 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION( BATCHORDERNO, 				"batchorderno",				 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION( BATCHORDERPOSNO, 			"batchorderposno",			 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION(	BATCHSTATE,					"batchstate",				 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION(	ARTICLENO,					"articleno",				 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION(	ORDERQTY,					"orderqty",					 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION(	QTYINKIND, 					"qtyinkind",				 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION(	ORIGINBRANCHNO, 			"originbranchno",			 basar::INT16		)	
		CONST_PROPERTY_DESCRIPTION(	ORIGINCUSTOMERNO, 			"origincustomerno",			 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION(	POSITIONTEXT, 				"positiontext",				 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION(	IBTRECORDTYPE, 				"ibtrecordtype",			 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION(	IBTPARTNER2,				"ibtpartner2",				 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION(	IBTPARTNER3, 				"ibtpartner3",				 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION( SALEINCREASEFLAG, 			"saleincreaseflag",			 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION( ORIGINCUSTOMERORDERNO, 		"origincustomerorderno",	 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION( ORIGINCUSTOMERORDERPOSNO,	"origincustomerorderposno",	 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION( IBTTYPE, 					"ibttype",					 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION( SUBSEQUENTDELIVERYQTY, 		"subsequentdeliveryqty",	 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION( NOBOOKINGFLAG,				"nobookingflag",			 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION(	EDIBATCHORDERNO, 			"edibatchorderno",			 basar::INT32		)	
		CONST_PROPERTY_DESCRIPTION(	ARTICLECODE, 				"articlecode",				 basar::STRING		)	
		CONST_PROPERTY_DESCRIPTION(	ARTICLETYPE, 				"articletype",				 basar::INT16		)	
		CONST_PROPERTY_DESCRIPTION( RECORDTYPE,                 "recordtype",                basar::INT16       )
		CONST_PROPERTY_DESCRIPTION( PHARMACYPURCHASEPRICE,		"pharmacypurchaseprice",	 basar::DECIMAL     )
		CONST_PROPERTY_DESCRIPTION( DISCOUNTPERCENTAGE,			"discountpercentage",	  	 basar::DECIMAL     )
		CONST_PROPERTY_DESCRIPTION( INVOICEPRICE,				"invoiceprice",				 basar::DECIMAL     )
		CONST_PROPERTY_DESCRIPTION( LINEVALUE,					"linevalue",	  			 basar::DECIMAL     )
		CONST_PROPERTY_DESCRIPTION( PIECEDISCOUNTVALUE,			"piecediscountvalue",		 basar::DECIMAL     )
		CONST_PROPERTY_DESCRIPTION( PRICEZERO,					"pricezero",				 basar::INT16       )
	}		

	namespace dkbazk
	{
		CONST_PROPERTY_DESCRIPTION(	RECORDOFFSET,			"kabazkkoffset",				basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZKANR,				"kabazkanr",					basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZKLFDANR, 			"kabazklfdanr",					basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZKDX05DATE, 			"kabazkdx50date",				basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZKIDF,				"kabazkidf",					basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZKIKNR,				"kabazkiknr",					basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZKUFIL,				"kabazkufil",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZKKUKZ,				"kabazkkukz",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZKFIL,				"kabazkfil",					basar::INT16		)
		CONST_PROPERTY_DESCRIPTION( KBAZKPOSLINES,			"kabazkposlines",				basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZKHART,				"kabazkhart",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZKSAPDELNO,			"kabazksapdelno",				basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZKLIEFDAT,			"kabazkliefdat",				basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZKAVAL,				"kabazkaval",					basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZKADDMONTH,			"kabazkaddmonth",				basar::INT16		)
		CONST_PROPERTY_DESCRIPTION(	KBAZKAART,				"kabazkaart",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZKKART,				"kabazkkart",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZKBART,				"kabazkbart",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZKTEXT,				"kabazktext",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZKKZSHA, 			"kabazpkzsha",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZKEDILS , 			"kabazpedils",					basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZKSTATUS , 			"kbazkstatus",					basar::STRING		)
	}	

	namespace dkbazp
	{
		CONST_PROPERTY_DESCRIPTION(	RECORDOFFSET,		"kabazpoffset",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPFIL, 			"kabazpfil",			basar::INT16		) 
		CONST_PROPERTY_DESCRIPTION( KBAZPPOS, 			"kabazppos",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZPLFDANR, 		"kabazplfdanr",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZPDX05DATE, 		"kabazpdx50date",		basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZPLFDPOS, 		"kabazplfdpos",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPKSC,			"kabazpksc",			basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPPZN,			"kabazppzn",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPBESMG,			"kabazpbesmg",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPMGOB, 			"kabazpmgob",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPUFIL, 			"kabazpufil",			basar::INT16		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPUIDF, 			"kabazpuidf",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPPTEXT, 		"kabazpptext",			basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPVBSART, 		"kabazpvbsart",			basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPVBPART2,		"kabazpvbpart2",		basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPVBPART3, 		"kabazpvbpart3",		basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZPABVKE, 		"kabazpabvke",			basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZPKAUFNR, 		"kabazpkaufnr",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZPKPOSNR,		"kabazpkposnr",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZPVBA, 			"kabazpvba",			basar::STRING		)
		CONST_PROPERTY_DESCRIPTION( KBAZPNLMG, 			"kabazpnlmg",			basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZPNULLKZ,		"kabazpnullkz",			basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPBATCHNR, 		"kabazpbatchnr",		basar::INT32		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPARTCODE, 		"kabazpartcode",		basar::STRING		)
		CONST_PROPERTY_DESCRIPTION(	KBAZPARTTYPE, 		"kabazparttype",		basar::INT32		)
		CONST_PROPERTY_DESCRIPTION( KBAZSA,             "kabazpsa",             basar::INT16        )
		CONST_PROPERTY_DESCRIPTION( KBAZSALEPRICE,		"kabazsaleprice",		basar::DECIMAL      )
		CONST_PROPERTY_DESCRIPTION( KBAZDISCRATE,		"kabazdiscrate",		basar::DECIMAL      )
		CONST_PROPERTY_DESCRIPTION( KBAZINVPRICE,		"kabazinvprice",		basar::DECIMAL      )
		CONST_PROPERTY_DESCRIPTION( KBAZLINEVAL,		"kabazlineval",			basar::DECIMAL      )
		CONST_PROPERTY_DESCRIPTION( KBAZREBATEVAL,		"kabazrebateval",		basar::DECIMAL      )
		CONST_PROPERTY_DESCRIPTION( KBAZPREISNULL,      "kabazpreisnull",       basar::INT16        )
	}

} // end namespace properties

#endif // GUARD_PROPERTIES_PROPERTY_DEFINITIONS_H
