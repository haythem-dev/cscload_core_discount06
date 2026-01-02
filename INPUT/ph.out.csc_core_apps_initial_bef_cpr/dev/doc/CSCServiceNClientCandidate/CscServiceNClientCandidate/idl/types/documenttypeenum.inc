#ifndef GUARD_DOCUMENTTYPE_ENUM_H
#define GUARD_DOCUMENTTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp documents.types
namespace csharp Documents.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumerate the shipment types.                                             */
/*----------------------------------------------------------------------------*/
enum DocumentTypeEnum
{
	UndefinedDocType	= 0,
	Invoice				= 1,	// Beleg zur Sammelrechnung
	ReturnAdvice		= 2,	// Retouren Avis
	BatchChangeAdvice	= 3		// BatchChangeAdvice
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_DOCUMENTTYPE_ENUM_H
