#ifndef GUARD_BOOKINGTYPE_ENUM_H
#define GUARD_BOOKINGTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration for stock account transaction codes.                          */
/*----------------------------------------------------------------------------*/
enum BookingTypeEnum
{
	StockDebitAndDemand     = 0,    // Bestand abbuchen, Bedarf kumulieren
	StockNoTransaction      = 2,    // Keine Bestands-/Bedarfskontenbewegung
	StockDebit              = 3,    // Bestand abbuchen, Bedarf nicht kumulieren
	StockDemand             = 4,    // Keine Bestandsbewegung, Bedarf kumulieren
	StockReturn             = 8,    // Bestand zubuchen (Retoure)
	StockAccountCorrection  = 9     // Absolute Bestandskorrektur
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_BOOKINGTYPE_ENUM_H
