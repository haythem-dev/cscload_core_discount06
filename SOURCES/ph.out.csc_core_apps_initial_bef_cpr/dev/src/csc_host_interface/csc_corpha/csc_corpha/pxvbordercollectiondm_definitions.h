//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  
 *  \author		Steffen Heinlein
 *  \date		09.10.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERCOLLECTIONDM_DEFINITIONS_H
#define GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERCOLLECTIONDM_DEFINITIONS_H

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace corpha
{
namespace pxVerbund
{	
//	static const basar::Int32 MAXTRANSFERREDORDERS( 100 );
//	static const basar::Int32 MAXTRANSFERREDORDERSSORTTOURID( 20 );
	enum OrderSelectionMode{ ALLORDERNUMBERS = -1, EVENORDERNUMBERS = 0, ODDORDERNUMBERS = 1 };

} // end namespace pxVerbund
} // end namespace corpha
} // end namespace domMod

#endif // GUARD_DOMMOD_CORPHA_PXVERBUND_PXVBORDERCOLLECTIONDM_DEFINITIONS_H
