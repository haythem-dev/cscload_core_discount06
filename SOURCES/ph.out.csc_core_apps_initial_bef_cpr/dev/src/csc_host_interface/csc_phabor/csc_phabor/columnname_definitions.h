//--------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Julian Machata
 *  \date       16.10.2012
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------//

#ifndef GUARD_COLUMNNAMES_COLUMNNAME_DEFINITIONS_H
#define GUARD_COLUMNNAMES_COLUMNNAME_DEFINITIONS_H

//--------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------//
#include "cmndm.h"

//--------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------//
namespace columnnames
{
	namespace pharmosbatchorderhead
	{
		const basar::VarString BRANCHNO					( "branchno"				);
		const basar::VarString CREATIONDATETIME			( "creationdatetime"		);
		const basar::VarString VSEOFFSET				( "vseoffset"				);
		const basar::VarString PROCESSINGSTATUS			( "processingstate"			);
		const basar::VarString PROCESSEDTIMESTAMP		( "processedtimestamp"		);
		const basar::VarString TRANSFERREDTIMESTAMP		( "transferredtimestamp"	);
		const basar::VarString POSITIONCOUNT			( "positioncount"			);
		const basar::VarString TRANSFERORDERNO			( "transferorderno"			);
		const basar::VarString BATCHORDERNO				( "batchorderno"			);
		const basar::VarString ORDERTYPE				( "ordertype"				);
		const basar::VarString PICKINGTYPE				( "pickingtype"				);
		const basar::VarString BOOKINGTYPE				( "bookingtype"				);
		const basar::VarString CUSTOMERNO				( "customerno"				);
		const basar::VarString INTERNALCUSTOMERNO		( "internalcustomerno"		);
		const basar::VarString INFOTEXT					( "infotext"				);
		const basar::VarString ORIGINTYPE				( "origintype"				);
		const basar::VarString ORIGINBRANCHNO			( "originbranchno"			);
		const basar::VarString CUSTOMERFLAG				( "customerflag"			);
		const basar::VarString VALUEDATE				( "valuedate"				);
		const basar::VarString DELIVERYDATE				( "deliverydate"			);
		const basar::VarString SAPDELIVERYNOTE			( "sapdeliverynote"			);
		const basar::VarString EDIDELIVERYNOTEFLAG		( "edideliverynoteflag"		);
		const basar::VarString PARENTCOMPANYFLAG		( "parentcompanyflag"		);
		const basar::VarString CSCORDERNO				( "cscorderno"				);
		const basar::VarString VALDATADDMONTH			( "valdataddmonth"			);
	}

	namespace pharmosbatchorderpos
	{
		const basar::VarString BRANCHNO 				( "branchno"				);                
		const basar::VarString CREATIONDATETIME 		( "creationdatetime"		);        
		const basar::VarString VSEOFFSET 				( "vseoffset"				);               
		const basar::VarString PROCESSINGSTATE 			( "processingstate"			);         
		const basar::VarString PROCESSEDTIMESTAMP 		( "processedtimestamp"		);      
		const basar::VarString TRANSFERREDTIMESTAMP		( "transferredtimestamp"	);    
		const basar::VarString TRANSFERORDERNO 			( "transferorderno"			);         
		const basar::VarString TRANSFERORDERPOSNO 		( "transferorderposno"		);      
		const basar::VarString BATCHORDERNO 			( "batchorderno"			);            
		const basar::VarString BATCHORDERPOSNO 			( "batchorderposno"			);         
		const basar::VarString BATCHSTATE				( "batchstate"				);              
		const basar::VarString ARTICLENO				( "articleno"				);               
		const basar::VarString ORDERQTY					( "orderqty"				);                
		const basar::VarString QTYINKIND 				( "qtyinkind"				);               
		const basar::VarString ORIGINBRANCHNO 			( "originbranchno"			);          
		const basar::VarString ORIGINCUSTOMERNO 		( "origincustomerno"		);        
		const basar::VarString POSITIONTEXT 			( "positiontext"			);            
		const basar::VarString IBTRECORDTYPE 			( "ibtrecordtype"			);           
		const basar::VarString IBTPARTNER2				( "ibtpartner2"				);             
		const basar::VarString IBTPARTNER3 				( "ibtpartner3"				);             
		const basar::VarString SALEINCREASEFLAG 		( "saleincreaseflag"		);        
		const basar::VarString ORIGINCUSTOMERORDERNO 	( "origincustomerorderno"	);   
		const basar::VarString ORIGINCUSTOMERORDERPOSNO	( "origincustomerorderposno");
		const basar::VarString IBTTYPE 					( "ibttype"					);                 
		const basar::VarString SUBSEQUENTDELIVERYQTY 	( "subsequentdeliveryqty"	);   
		const basar::VarString NOBOOKINGFLAG			( "nobookingflag"			);           
		const basar::VarString PARENTCOMPANYFLAG 		( "parentcompanyflag"		);       
		const basar::VarString EDIDELIVERYNOTE 			( "edideliverynote"			);         
		const basar::VarString EDIBATCHORDERNO 			( "edibatchorderno"			);         
		const basar::VarString ARTICLECODE 				( "articlecode"				);             
		const basar::VarString ARTICLETYPE 				( "articletype"				);             
		const basar::VarString RECORDTYPE				( "recordtype"				);
		const basar::VarString PHARMACYPURCHASEPRICE	( "pharmacypurchaseprice"   );
		const basar::VarString DISCOUNTPERCENTAGE		( "discountpercentage"		);
		const basar::VarString INVOICEPRICE				( "invoiceprice"			);
		const basar::VarString LINEVALUE				( "linevalue"				);
		const basar::VarString PIECEDISCOUNTVALUE		( "piecediscountvalue"		);
		const basar::VarString PRICEZERO				( "pricezero"				);
	}														  

	namespace dkbazk
	{
		const basar::VarString KBAZK_OFFSET		(	"KBAZ_OFFSET"	);
		const basar::VarString KBAZK_LFDANR		( 	"KBAZ_LFDANR"	);
		const basar::VarString KBAZK_DX05DATE	(	"KBAZ_DX05DATE"	);
		const basar::VarString KBAZK_POSLINES	( 	"KBAZ_POSLINES"	);
		const basar::VarString KBAZK_ANR		( 	"BAZ_ANR"		);
		const basar::VarString KBAZK_IDF		(	"BAZ_IDF"		);
		const basar::VarString KBAZK_IKNR		( 	"BAZ_IKNR"		);
		const basar::VarString KBAZK_UFIL		( 	"BAZ_UFILK"		);
		const basar::VarString KBAZK_KUKZ		( 	"BAZ_KUKZ"		);
		const basar::VarString KBAZK_FIL		( 	"BAZ_FIL"		);
		const basar::VarString KBAZK_HART		( 	"BAZ_HART"		);
		const basar::VarString KBAZK_SAPDELNO	( 	"BAZ_SAPDELNO"	);
		const basar::VarString KBAZK_LIEFDAT	(	"BAZ_LIEFDAT"	);
		const basar::VarString KBAZK_AVAL		(	"BAZ_AVAL"		);
		const basar::VarString KBAZK_SA			(	"BAZ_SA"		);
		const basar::VarString KBAZK_AART		(	"BAZ_AART"		);
		const basar::VarString KBAZK_KART		(	"BAZ_KART"		);
		const basar::VarString KBAZK_BART		(	"BAZ_BART"		);
		const basar::VarString KBAZK_TEXT		(	"BAZ_TEXT"		);
		const basar::VarString KBAZK_EDIDELNO	(	"BAZ_EDILSK"	);
		const basar::VarString KBAZK_KZSHA		( 	"BAZ_KZSHAK"	);	
		const basar::VarString KBAZK_EDILS		( 	"BAZ_EDILSK"	);
		const basar::VarString KBAZK_STATUS		( 	"BAZ_STATUS"	);
		const basar::VarString KBAZK_ADDMONTH	( 	"BAZ_ADDMONTH"	);
	}

	namespace dkbazp
	{
		const basar::VarString KBAZP_OFFSET		(	"KBAZ_OFFSET"	);	
		const basar::VarString KBAZP_LFDANR		( 	"KBAZ_LFDANR"	);	
		const basar::VarString KBAZP_DX50DATE	(	"KBAZ_DX05DATE"	);
		const basar::VarString KBAZP_LFDPOS		( 	"KBAZ_LFDPOS"	);	
		const basar::VarString KBAZP_KSC		(	"KBAZ_KSC"		);	
		const basar::VarString KBAZP_FIL		( 	"BAZ_FIL"		);	
		const basar::VarString KBAZP_POS		( 	"BAZ_POS"		);	
		const basar::VarString KBAZP_PZN		(	"BAZ_PZN"		);	
		const basar::VarString KBAZP_BESMG		(	"BAZ_BESMG"		);	
		const basar::VarString KBAZP_MGOB		( 	"BAZ_MGOB"		);	
		const basar::VarString KBAZP_UFIL		( 	"BAZ_UFIL"		);	
		const basar::VarString KBAZP_UIDF		( 	"BAZ_UIDF"		);	
		const basar::VarString KBAZP_PTEXT		( 	"BAZ_PTEXT"		);	
		const basar::VarString KBAZP_VBSART		( 	"BAZ_VBSART"	);	
		const basar::VarString KBAZP_VBPART2	(	"BAZ_VBPART2"	);	
		const basar::VarString KBAZP_VBPART3	( 	"BAZ_VBPART3"	);	
		const basar::VarString KBAZP_ABVKE		( 	"BAZ_ABVKE"		);	
		const basar::VarString KBAZP_KAUFNR		( 	"BAZ_KAUFNR"	);	
		const basar::VarString KBAZP_KPOSNR		(	"BAZ_KPOSNR"	);	
		const basar::VarString KBAZP_VBA		( 	"BAZ_VBA"		);	
		const basar::VarString KBAZP_NLMG		( 	"BAZ_NLMG"		);	
		const basar::VarString KBAZP_NULLKZ		(	"BAZ_NULLKZ"	);		
		const basar::VarString KBAZP_BATCHNR	( 	"BAZ_BATCHNR"	);	
		const basar::VarString KBAZP_ARTCODE	( 	"BAZ_ARTCODE"	);	
		const basar::VarString KBAZP_ARTTYPE	( 	"BAZ_ARTTYPE"	);	
		const basar::VarString KBAZP_SA         (   "BAZ_SA"        );
		const basar::VarString KBAZP_SALEPRICE	(	"BAZ_SALEPRICE" );
		const basar::VarString KBAZP_DISCRATE	(	"BAZ_DISCRATE"  );
		const basar::VarString KBAZP_INVPRICE	(	"BAZ_INVPRICE"  );
		const basar::VarString KBAZP_LINEVAL	(	"BAZ_LINEVAL"   );
		const basar::VarString KBAZP_REBATEVAL	(	"BAZ_REBATEVAL" );
		const basar::VarString KBAZP_PREISNULL	(	"BAZ_PREISNULL" );
	}	

} // end namespace columnnames

#endif // GUARD_COLUMNNAMES_COLUMNNAME_DEFINITIONS_H
