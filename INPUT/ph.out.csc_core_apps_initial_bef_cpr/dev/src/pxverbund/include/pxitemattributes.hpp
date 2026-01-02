/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXITEMATTRIBUTES
Used at this moment at the XML Ordering System

REVISION HISTORY

30 August 2006 V1.00 REV 00 written by Ysbarnd Bouma.
*/

#ifndef PXITEMATTRIBUTES_DOTH
#define PXITEMATTRIBUTES_DOTH

class pxItemAttributes
{
public:
	pxItemAttributes(const bool AuxDel, const bool RestDel, const bool Dispo, const bool PartDel);
	virtual  ~pxItemAttributes();

    bool       IsAuxDelivery()       {return AuxDel_;    }
    bool       IsRestDelivery()      {return RestDel_;   }
    bool       IsPurchaseOrder()     {return Dispo_;     }
    bool       IsPartialDelivery()   {return PartDel_;   }

protected:
    void        Init();

/*----------------------------------------------------------------------------*/
/*  Data members.                                                             */
/*----------------------------------------------------------------------------*/
    bool      AuxDel_;              // Auxdelivery
    bool      RestDel_;             // Restdelivery
    bool      Dispo_;               // Purchase Order
    bool      PartDel_;             // Subset
};
#endif
