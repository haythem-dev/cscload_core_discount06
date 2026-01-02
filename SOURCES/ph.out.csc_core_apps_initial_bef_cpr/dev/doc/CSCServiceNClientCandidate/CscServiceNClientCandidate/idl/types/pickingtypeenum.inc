#ifndef GUARD_PICKINGTYPE_ENUM_H
#define GUARD_PICKINGTYPE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumerate the shipment types.                                             */
/*----------------------------------------------------------------------------*/
enum PickingTypeEnum
{
	ShipNormal       = 0,            // Normale Kommissionierung
	ShipDisposal     = 1,            // Keine Kommi, Auslieferung mit normaler Tour
	ShipNone         = 2,            // Keine   Kommissionierung
	ShipUrgent       = 3,            // Eil, Beipack
	ShipUrgentExtra  = 4,            // Eil, Extra
	ShipSpecial      = 5,            // Sonder, normale Abwicklung
	ShipSpecialExtra = 6,            // Sonder, Eil Beipack
	ShipSpecialSuper = 7,            // Sonder, Eil Beipack
	ShipDeliveryNote = 8             // Nur Lieferschein
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_PICKINGTYPE_ENUM_H
