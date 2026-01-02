//-------------------------------------------------------------------------------------------------------------------//
/*! \file		
 *  \brief		main interface for domain module of cicsorderheads (cics file VSAM.PHARMOSBATCHORDERPOS)
 *  \author		Julian Machata
 *  \date		17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "batchordertransformer.h"
#include "property_definitions.h"
#include "pharmosbatchorderposacc_definitions.h"
#include "cscbatchorderdm_definitions.h"

namespace domMod 
{		
namespace batchOrder
{
namespace core
{
//-------------------------------------------------------------------------------------------------------------------//
BatchOrderTransformer::BatchOrderTransformer(const libcsc_utils::ICSC_LoggerPtr csc_logger )
: m_CSC_Logger( csc_logger )
{
	METHODNAME_DEF( BatchOrderTransformer, BatchOrderTransformer );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
BatchOrderTransformer::~BatchOrderTransformer()
{		
	METHODNAME_DEF( BatchOrderTransformer, ~BatchOrderTransformer );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderTransformer::transformCics2Ifx ( domMod::batchOrder::core::BatchOrderPtr sourceCICS, domMod::batchOrder::core::BatchOrderPtr targetIFX )
{
	METHODNAME_DEF( BatchOrderTransformer, transformCics2Ifx );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	transformHead( sourceCICS->getOrderHead()     , targetIFX->getOrderHead()      );
	transformPos ( sourceCICS->getOrderPositions(), sourceCICS->getOrderHead(), targetIFX->getOrderPositions() );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderTransformer::transformHead ( basar::db::aspect::AccessorPropertyTable_YIterator yitCicsHead, basar::db::aspect::AccessorPropertyTable_YIterator yitIfxHead )
{
	METHODNAME_DEF( BatchOrderTransformer, transformHead );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
 
	yitIfxHead.setInt32   ( properties::pharmosbatchorderhead::VSEOFFSET			, yitCicsHead.getInt32  ( properties::dkbazk::RECORDOFFSET					));	
	yitIfxHead.setInt32   ( properties::pharmosbatchorderhead::BATCHORDERNO			, yitCicsHead.getInt32  ( properties::dkbazk::KBAZKANR						)); 
	yitIfxHead.setInt32   ( properties::pharmosbatchorderhead::TRANSFERORDERNO		, yitCicsHead.getInt32  ( properties::dkbazk::KBAZKLFDANR					));
	yitIfxHead.setInt32   ( properties::pharmosbatchorderhead::CUSTOMERNO			, yitCicsHead.getInt32  ( properties::dkbazk::KBAZKIDF						));	
	yitIfxHead.setInt32   ( properties::pharmosbatchorderhead::INTERNALCUSTOMERNO	, yitCicsHead.getInt32  ( properties::dkbazk::KBAZKIKNR						));	
	yitIfxHead.setInt16   ( properties::pharmosbatchorderhead::ORIGINBRANCHNO		, strToInt16 ( yitCicsHead.getString ( properties::dkbazk::KBAZKUFIL		)));
	yitIfxHead.setString  ( properties::pharmosbatchorderhead::CUSTOMERFLAG			, yitCicsHead.getString ( properties::dkbazk::KBAZKKUKZ						));	
	yitIfxHead.setInt16   ( properties::pharmosbatchorderhead::BRANCHNO				, yitCicsHead.getInt16  ( properties::dkbazk::KBAZKFIL						));	
	yitIfxHead.setInt32   ( properties::pharmosbatchorderhead::POSITIONCOUNT		, yitCicsHead.getInt32  ( properties::dkbazk::KBAZKPOSLINES					)); 
	yitIfxHead.setString  ( properties::pharmosbatchorderhead::ORIGINTYPE			, yitCicsHead.getString ( properties::dkbazk::KBAZKHART						));	
	yitIfxHead.setString  ( properties::pharmosbatchorderhead::SAPDELIVERYNOTE		, yitCicsHead.getString ( properties::dkbazk::KBAZKSAPDELNO					));	
	yitIfxHead.setString  ( properties::pharmosbatchorderhead::PARENTCOMPANYFLAG	, yitCicsHead.getString ( properties::dkbazk::KBAZKKZSHA 					));
	yitIfxHead.setString  ( properties::pharmosbatchorderhead::EDIDELIVERYNOTEFLAG	, yitCicsHead.getString ( properties::dkbazk::KBAZKEDILS 					));
	yitIfxHead.setDate    ( properties::pharmosbatchorderhead::DELIVERYDATE			, intDate2BasarDate ( yitCicsHead.getInt32  ( properties::dkbazk::KBAZKLIEFDAT )));
	yitIfxHead.setInt16   ( properties::pharmosbatchorderhead::VALDATADDMONTH		, yitCicsHead.getInt16  ( properties::dkbazk::KBAZKADDMONTH					));

	// add month logic
	basar::Date valueDate = intDate2BasarDate ( yitCicsHead.getInt32  ( properties::dkbazk::KBAZKAVAL ));
	valueDate.addDays(30 * yitIfxHead.getInt16(properties::pharmosbatchorderhead::VALDATADDMONTH));
	yitIfxHead.setDate    ( properties::pharmosbatchorderhead::VALUEDATE			, valueDate);

	yitIfxHead.setString  ( properties::pharmosbatchorderhead::ORDERTYPE			, yitCicsHead.getString ( properties::dkbazk::KBAZKAART						));	
	yitIfxHead.setString  ( properties::pharmosbatchorderhead::PICKINGTYPE			, yitCicsHead.getString ( properties::dkbazk::KBAZKKART						)); 
	yitIfxHead.setString  ( properties::pharmosbatchorderhead::BOOKINGTYPE			, yitCicsHead.getString ( properties::dkbazk::KBAZKBART						));	
	yitIfxHead.setString  ( properties::pharmosbatchorderhead::INFOTEXT				, yitCicsHead.getString ( properties::dkbazk::KBAZKTEXT						)); 
	yitIfxHead.setDateTime( properties::pharmosbatchorderhead::TRANSFERREDTIMESTAMP	, basar::DateTime() );
}

//-------------------------------------------------------------------------------------------------------------------//
void BatchOrderTransformer::transformPos  ( basar::db::aspect::AccessorPropertyTableRef yitCicsPosPropTab, basar::db::aspect::AccessorPropertyTable_YIterator yitCicsHead, basar::db::aspect::AccessorPropertyTableRef yitIfxPosPropTab )
{
	METHODNAME_DEF( BatchOrderTransformer, transformPos );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	yitIfxPosPropTab.clear();
 
	basar::db::aspect::AccessorPropertyTable_YIterator yitCicsPos = yitCicsPosPropTab.begin();

	for ( ; !yitCicsPos.isEnd(); yitCicsPos++ ){

		basar::db::aspect::AccessorPropertyTable_YIterator yitIfxPos = addPos( yitIfxPosPropTab );

		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::VSEOFFSET				 , yitCicsPos.getInt32  ( properties::dkbazp::RECORDOFFSET					));
		yitIfxPos.setInt16   ( properties::pharmosbatchorderpos::BRANCHNO				 , yitCicsPos.getInt16  ( properties::dkbazp::KBAZPFIL 						));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::BATCHORDERPOSNO		 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPPOS						));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::BATCHORDERNO			 , yitCicsHead.getInt32 ( properties::dkbazk::KBAZKANR 						));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::TRANSFERORDERNO		 , yitCicsHead.getInt32 ( properties::dkbazk::KBAZKLFDANR					));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::TRANSFERORDERPOSNO		 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPLFDPOS 					));
		yitIfxPos.setDateTime( properties::pharmosbatchorderpos::TRANSFERREDTIMESTAMP	 , basar::DateTime() );
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::BATCHSTATE				 , yitCicsPos.getString ( properties::dkbazp::KBAZPKSC						));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::ARTICLENO				 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPPZN						));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::ORDERQTY				 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPBESMG					));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::QTYINKIND				 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPMGOB 					));
		yitIfxPos.setInt16   ( properties::pharmosbatchorderpos::ORIGINBRANCHNO			 , yitCicsPos.getInt16  ( properties::dkbazp::KBAZPUFIL 					));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::ORIGINCUSTOMERNO		 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPUIDF 					));
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::POSITIONTEXT			 , yitCicsPos.getString ( properties::dkbazp::KBAZPPTEXT 					));
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::IBTRECORDTYPE			 , yitCicsPos.getString ( properties::dkbazp::KBAZPVBSART					));
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::IBTPARTNER2			 , yitCicsPos.getString ( properties::dkbazp::KBAZPVBPART2					));
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::IBTPARTNER3			 , yitCicsPos.getString ( properties::dkbazp::KBAZPVBPART3					));
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::SALEINCREASEFLAG		 , yitCicsPos.getString ( properties::dkbazp::KBAZPABVKE 					));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERNO	 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPKAUFNR 					));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERPOSNO, yitCicsPos.getInt32  ( properties::dkbazp::KBAZPKPOSNR					));
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::IBTTYPE				 , yitCicsPos.getString ( properties::dkbazp::KBAZPVBA 						));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::SUBSEQUENTDELIVERYQTY	 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPNLMG 					));
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::NOBOOKINGFLAG			 , yitCicsPos.getString ( properties::dkbazp::KBAZPNULLKZ					));
		yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::EDIBATCHORDERNO		 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPBATCHNR					));
		yitIfxPos.setString  ( properties::pharmosbatchorderpos::ARTICLECODE			 , yitCicsPos.getString ( properties::dkbazp::KBAZPARTCODE					));		
		//yitIfxPos.setInt32   ( properties::pharmosbatchorderpos::ARTICLETYPE			 , yitCicsPos.getInt32  ( properties::dkbazp::KBAZPARTTYPE					));
		yitIfxPos.setInt16   ( properties::pharmosbatchorderpos::RECORDTYPE			     , yitCicsPos.getInt16  ( properties::dkbazp::KBAZSA                        ));
		yitIfxPos.setDecimal ( properties::pharmosbatchorderpos::PHARMACYPURCHASEPRICE	 , yitCicsPos.getDecimal(properties::dkbazp::KBAZSALEPRICE					));    
		yitIfxPos.setDecimal ( properties::pharmosbatchorderpos::DISCOUNTPERCENTAGE		 , yitCicsPos.getDecimal(properties::dkbazp::KBAZDISCRATE 					));     
		yitIfxPos.setDecimal ( properties::pharmosbatchorderpos::INVOICEPRICE			 , yitCicsPos.getDecimal(properties::dkbazp::KBAZINVPRICE 					));      
		yitIfxPos.setDecimal ( properties::pharmosbatchorderpos::LINEVALUE				 , yitCicsPos.getDecimal(properties::dkbazp::KBAZLINEVAL  					));     
		yitIfxPos.setDecimal ( properties::pharmosbatchorderpos::PIECEDISCOUNTVALUE		 , yitCicsPos.getDecimal(properties::dkbazp::KBAZREBATEVAL					));       
		yitIfxPos.setInt16   ( properties::pharmosbatchorderpos::PRICEZERO				 , yitCicsPos.getInt16  (properties::dkbazp::KBAZPREISNULL					));   
	}
}	

//-------------------------------------------------------------------------------------------------------------------//
basar::Date BatchOrderTransformer::intDate2BasarDate ( basar::Int32 valDate	)
{                                  
	METHODNAME_DEF( BatchOrderTransformer, intDate2BasarDate );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	
	using namespace domMod::batchOrder::processing::cscBatchOrderDM;
	
    basar::Date ret;
	ret.setInvalid();
  
	if (valDate > 0)
	{
		if (valDate < VSE_DATE_FILLER) // only 6 digit date
		{
			valDate += VSE_CENTURY_DEF;
		}
		ret = basar::Date(valDate);
	}
   
   return ret;
}
	
//-------------------------------------------------------------------------------------------------------------------//
basar::Int16 BatchOrderTransformer::strToInt16 ( basar::I18nString strInt )
{
	METHODNAME_DEF( BatchOrderTransformer, strToInt16 );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	basar::Decimal  decConvert ( 0 );  

	if ( strInt.isDigit() ){
		decConvert.fromString( strInt );
	}

	return decConvert.toInt16();								
}		

//-------------------------------------------------------------------------------------------------------------------//
basar::db::aspect::AccessorPropertyTable_YIterator BatchOrderTransformer::addPos( basar::db::aspect::AccessorPropertyTableRef propTab )
{
	METHODNAME_DEF( BatchOrderTransformer, addPos );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	return propTab.insert(basar::FOR_INSERT);	
}	

} // namespace core
} // namespace batchOrder
} // namespace domMod
