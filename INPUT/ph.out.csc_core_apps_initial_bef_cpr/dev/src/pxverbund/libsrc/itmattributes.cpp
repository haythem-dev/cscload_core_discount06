/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxItemAttributes:
Used at XML Ordering System

REVISION HISTORY

30 August 2006 V1.00 REV 00 written by Ysbrand Bouma
*/
#include "pxitemattributes.hpp"


/*----------------------------------------------------------------------------*/
/*  Constructor for pxItemAttributes object                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxItemAttributes :: pxItemAttributes
(
    const  bool  AuxDel,
    const  bool  RestDel,
    const  bool  Dispo,
    const  bool  PartDel
)
{
    Init();
    AuxDel_   = AuxDel;
    RestDel_  = RestDel;
    Dispo_    = Dispo;
    PartDel_  = PartDel;
}

/*----------------------------------------------------------------------------*/
/*  Destructor  for direct booking object                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxItemAttributes :: ~pxItemAttributes()
{
}

/*----------------------------------------------------------------------------*/
/*  Init                                                                      */
/*----------------------------------------------------------------------------*/
void
pxItemAttributes :: Init()
{
    AuxDel_   = false;
    RestDel_  = false;
    Dispo_    = false;
    PartDel_  = false;
}
