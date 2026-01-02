#ifndef GUARD_RETURNACCEPTANCECHECKRESULT_ENUM_H
#define GUARD_RETURNACCEPTANCECHECKRESULT_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

enum ReturnAcceptanceCheckResultEnum
{
	Accepted						= 0,	// RA = RetoureAkzeptiert
	AcceptedWithCallback			= 1,	// RR = RetoureAkzeptiertRueckspracheNoetig
	AcceptedWithoutReturnDelivery	= 2,	// RK = RetoureAkzeptiertKeineRuecksendungNoetig
	QuantityExceeded				= 3,	// AM = MengeUeberschritten
	ReturnDeadlineExceeded			= 4,	// AR = RueckgabefristUeberschritten
	NotAccepted						= 5,	// AK = KeineRuecknahme
	ArticleNotOnInvoice				= 6,	// AP = PznInLieferscheinnummerNichtEnthalten
	UnknownInvoiceNo				= 7		// AL = LieferscheinnummerUnbekannt
}


// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"


#endif // GUARD_RETURNACCEPTANCECHECKRESULT_ENUM_H
