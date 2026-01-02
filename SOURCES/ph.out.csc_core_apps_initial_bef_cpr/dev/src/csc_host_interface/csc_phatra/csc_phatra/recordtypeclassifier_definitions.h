//----------------------------------------------------------------------------
/*! \file		
 *  \brief		definitions RecordTypeClassifier
 *  \author		Steffen Heinlein
 *  \date		02.07.2012
 */
//----------------------------------------------------------------------------

#ifndef GUARD_UTIL_RECORDTYPECLASSIFIER_DEFINITIONS_H
#define GUARD_UTIL_RECORDTYPECLASSIFIER_DEFINITIONS_H

#include <set>

namespace util
{
namespace recordtypes
{	
	const basar::VarString RECORDTYPE_CHANGEORDERITEM( "AP" ); // Übertragung Mengenänderungen PHARMOS in kdauftragpos
	const basar::VarString RECORDTYPE_ARTICLEINFOGOODSIN( "AW" ); // Artikelinformationen Wareneingang
	const basar::VarString RECORDTYPE_STOPSELLINGOFARTICLE( "BL" ); // Artikel auf nicht verkaufsfähig setzen		
	const basar::VarString RECORDTYPE_STORAGERECONCILIATIONPREWHOLESALE( "BO" ); // Satzart BO = LR im Prewholesale
	const basar::VarString RECORDTYPE_CHANGEIBTSTOCKLEVEL( "BV" ); // Lagerortänderungen Verbund
	const basar::VarString RECORDTYPE_CODEBLOCAGE( "CB" ); // CodeBlocage FR	
	const basar::VarString RECORDTYPE_BATCH( "CH" ); // Artikelcharge
	const basar::VarString RECORDTYPE_DEALERVOLUMETOTAL( "D1" ); // DealerUmsatz BG
	const basar::VarString RECORDTYPE_DEALERVOLUMEELECTRONIC( "D2" ); // DealerUmsatz BG
	const basar::VarString RECORDTYPE_DEALERVOLUMEEXCLUSIVETOTAL( "D3" ); // DealerUmsatz BG
	const basar::VarString RECORDTYPE_DEALERVOLUMEEXCLUSIVEELECTRONIC( "D4" ); // DealerUmsatz BG
	const basar::VarString RECORDTYPE_CREDITLIMITCUSTOMERRETURN( "GU" ); // Gutschriften erhöhen das Kreditlimit GU
	const basar::VarString RECORDTYPE_CREDITLIMITCHAIN( "K1" ); // Kreditlimit BG
	const basar::VarString RECORDTYPE_CREDITLIMITGROUP( "KG" ); // Kreditlimit BG
	const basar::VarString RECORDTYPE_CREDITLIMITCUSTOMER( "K2" ); // Kreditlimit BG
	const basar::VarString RECORDTYPE_PICKINGLACK( "KD" ); // Lagerdefekt bei Kommi
	const basar::VarString RECORDTYPE_CREDITLIMIT( "KK" ); // Kreditlimit BG
	const basar::VarString RECORDTYPE_DISCOUNTACCOUNT( "KR" ); // RabattSaldo BG	
	const basar::VarString RECORDTYPE_CHANGEARTICLEDETAILS( "LO" ); // Lagerortänderungen	
	const basar::VarString RECORDTYPE_STORAGERECONCILIATION( "LR" ); // Satzart LR Lagerrevision
	const basar::VarString RECORDTYPE_PERPETUALSTOCKTAKING( "PI" ); // Satzart PI Permanente Inventur
	const basar::VarString RECORDTYPE_CHANGEQUARANTINE( "QA" ); // Satzart QA Quarantäne-Änderung
	const basar::VarString RECORDTYPE_CUSTOMERRETURN( "RK" ); // Kundenretoure RK
	const basar::VarString RECORDTYPE_IMPORTINVOICENO( "RN" ); // Import Rechnungsnummer für Auftragsart PF und TO in RS	
	const basar::VarString RECORDTYPE_TENDERCHANGECUSTOMERRETURN( "RT" ); // Retoure zu Tender
	const basar::VarString RECORDTYPE_INVOICECANCELLATION( "ST" ); // Rechnungsstorno 
	const basar::VarString RECORDTYPE_TRANSFERQUARANTINE( "TR" ); // Transfer aus Quarantäne
	const basar::VarString RECORDTYPE_EXPIRYDATE( "VD" ); // Verfalldaten aus Permanenter Inventur VD
	const basar::VarString RECORDTYPE_IBTGOODS( "VB" ); // Verbundware VB
	const basar::VarString RECORDTYPE_BATCHINCONSISTENCY( "WC" ); // Satzart WC Chargenunstimmigkeiten
	const basar::VarString RECORDTYPE_GOODSIN( "WE" ); // Wareneingang WE
//	const basar::VarString RECORDTYPE_RETURNPREDELIVEREDARTICLE( "ZT" ); // Retoure zu Vorrausbezug ZT		
	const basar::VarString RECORDTYPE_CHANGEARTICLEMASTERDATA( "ZP" ); // Stammdatenänderungen aus ZDP
}
} // namespace util

//----------------------------------------------------------------------------

#endif // GUARD_UTIL_RECORDTYPECLASSIFIER_DEFINITIONS_H

//----------------------------------------------------------------------------

