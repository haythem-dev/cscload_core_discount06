/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOrderValues methods.

REVISION HISTORY

08 March 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxordervalues.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxartbas.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderValues :: pxOrderValues
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderValues :: pxOrderValues
(
    pxOrderValues& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGWERTE structure to construct this instance.                 */
/*----------------------------------------------------------------------------*/
pxOrderValues :: pxOrderValues
(
    pxSession   *session,
    tKDAUFTRAGWERTE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderValues :: pxOrderValues
(
    pxSession *session,
   const pxOrderValues *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
       (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderValues :: pxOrderValues
(
    pxSession    *session,
    long         KdAuftragNr          // KdAuftragnr

)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_  = KdAuftragNr;
    InitOrderValues();
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderValues :: ~pxOrderValues()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGWERTE structure.     */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGWERTE&
Assign
(
    tKDAUFTRAGWERTE&           dest,
    const pxOrderValues&       src
)
{
    dest.KdAuftragNr              = src.KdAuftragNr_            ;

    dest.OrdValFtaxFSDisc         = src.OrderValueTaxFSDisc_[pxOrderValues::FullTax];
    dest.OrdValFtaxFS             = src.OrderValueTaxFSShip_[pxOrderValues::FullTax];
    dest.OrdValLtaxFSDisc         = src.OrderValueTaxFSDisc_[pxOrderValues::LowTax];
    dest.OrdValLtaxFS             = src.OrderValueTaxFSShip_[pxOrderValues::LowTax];
        dest.TaxValFtaxFSDisc         = src.TaxValueFSDisc_[pxOrderValues::FullTax];
    dest.TaxValFtaxFS             = src.TaxValueFSShip_[pxOrderValues::FullTax];
    dest.TaxValLtaxFSDisc         = src.TaxValueFSDisc_[pxOrderValues::LowTax];
    dest.TaxValLtaxFS             = src.TaxValueFSShip_[pxOrderValues::LowTax];

    dest.OrdValFtaxHFDisc         = src.OrderValueTaxHFDisc_[pxOrderValues::FullTax];
    dest.OrdValFtaxHF             = src.OrderValueTaxHFShip_[pxOrderValues::FullTax];
    dest.OrdValLtaxHFDisc         = src.OrderValueTaxHFDisc_[pxOrderValues::LowTax];
    dest.OrdValLtaxHF             = src.OrderValueTaxHFShip_[pxOrderValues::LowTax];
    dest.TaxValFtaxHFDisc         = src.TaxValueHFDisc_[pxOrderValues::FullTax];
    dest.TaxValFtaxHF             = src.TaxValueHFShip_[pxOrderValues::FullTax];
    dest.TaxValLtaxHFDisc         = src.TaxValueHFDisc_[pxOrderValues::LowTax];
    dest.TaxValLtaxHF             = src.TaxValueHFShip_[pxOrderValues::LowTax];

    dest.OrdValFtaxRSDisc         = src.OrderValueTaxRTDisc_[pxOrderValues::FullTax];
    dest.OrdValFtaxRS             = src.OrderValueTaxRTShip_[pxOrderValues::FullTax];
    dest.OrdValLtaxRSDisc         = src.OrderValueTaxRTDisc_[pxOrderValues::LowTax];
    dest.OrdValLtaxRS             = src.OrderValueTaxRTShip_[pxOrderValues::LowTax];
    dest.TaxValFtaxRSDisc         = src.TaxValueRTDisc_[pxOrderValues::FullTax];
    dest.TaxValFtaxRS             = src.TaxValueRTShip_[pxOrderValues::FullTax];
    dest.TaxValLtaxRSDisc         = src.TaxValueRTDisc_[pxOrderValues::LowTax];
    dest.TaxValLtaxRS             = src.TaxValueRTShip_[pxOrderValues::LowTax];

	dest.OrdValNtaxFSDisc         = src.OrderValueTaxFSDisc_[pxOrderValues::NoTax];
	dest.OrdValNtaxFS             = src.OrderValueTaxFSShip_[pxOrderValues::NoTax];
	dest.OrdValNtaxHFDisc         = src.OrderValueTaxHFDisc_[pxOrderValues::NoTax];
	dest.OrdValNtaxHF             = src.OrderValueTaxHFShip_[pxOrderValues::NoTax];
	dest.OrdValNtaxRSDisc         = src.OrderValueTaxRTDisc_[pxOrderValues::NoTax];
	dest.OrdValNtaxRS             = src.OrderValueTaxRTShip_[pxOrderValues::NoTax];
	dest.TaxValNtaxFSDisc         = src.TaxValueFSDisc_[pxOrderValues::NoTax];
	dest.TaxValNtaxFS             = src.TaxValueFSShip_[pxOrderValues::NoTax];
	dest.TaxValNtaxHFDisc         = src.TaxValueHFDisc_[pxOrderValues::NoTax];
	dest.TaxValNtaxHF             = src.TaxValueHFShip_[pxOrderValues::NoTax];
	dest.TaxValNtaxRSDisc         = src.TaxValueRTDisc_[pxOrderValues::NoTax];
	dest.TaxValNtaxRS             = src.TaxValueRTShip_[pxOrderValues::NoTax];




    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGWERTE structure to               */
/*  a pxOrderValues object.                                                   */
/*----------------------------------------------------------------------------*/
pxOrderValues&
Assign
(
    pxOrderValues&              dest,
    const tKDAUFTRAGWERTE&    src
)
{
    dest.KdAuftragNr_              = src.KdAuftragNr            ;

    dest.OrderValueTaxFSDisc_[pxOrderValues::FullTax]   = src.OrdValFtaxFSDisc       ;
    dest.OrderValueTaxFSShip_[pxOrderValues::FullTax]   = src.OrdValFtaxFS           ;
    dest.OrderValueTaxFSDisc_[pxOrderValues::LowTax]    = src.OrdValLtaxFSDisc       ;
    dest.OrderValueTaxFSShip_[pxOrderValues::LowTax]    = src.OrdValLtaxFS           ;
    dest.TaxValueFSDisc_[pxOrderValues::FullTax]     = src.TaxValFtaxFSDisc       ;
    dest.TaxValueFSShip_[pxOrderValues::FullTax]     = src.TaxValFtaxFS           ;
    dest.TaxValueFSDisc_[pxOrderValues::LowTax]      = src.TaxValLtaxFSDisc       ;
    dest.TaxValueFSShip_[pxOrderValues::LowTax]      = src.TaxValLtaxFS           ;

    dest.OrderValueTaxHFDisc_[pxOrderValues::FullTax]          = src.OrdValFtaxHFDisc       ;
    dest.OrderValueTaxHFShip_[pxOrderValues::FullTax]              = src.OrdValFtaxHF           ;
    dest.OrderValueTaxHFDisc_[pxOrderValues::LowTax]        = src.OrdValLtaxHFDisc       ;
    dest.OrderValueTaxHFShip_[pxOrderValues::LowTax]            = src.OrdValLtaxHF           ;
    dest.TaxValueHFDisc_[pxOrderValues::FullTax]          = src.TaxValFtaxHFDisc       ;
    dest.TaxValueHFShip_[pxOrderValues::FullTax]            = src.TaxValFtaxHF           ;
    dest.TaxValueHFDisc_[pxOrderValues::LowTax]      = src.TaxValLtaxHFDisc       ;
    dest.TaxValueHFShip_[pxOrderValues::LowTax]          = src.TaxValLtaxHF           ;

        dest.OrderValueTaxRTDisc_[pxOrderValues::FullTax]      = src.OrdValFtaxRSDisc       ;
    dest.OrderValueTaxRTShip_[pxOrderValues::FullTax]      = src.OrdValFtaxRS           ;
    dest.OrderValueTaxRTDisc_[pxOrderValues::LowTax]      = src.OrdValLtaxRSDisc       ;
    dest.OrderValueTaxRTShip_[pxOrderValues::LowTax]             = src.OrdValLtaxRS           ;
    dest.TaxValueRTDisc_[pxOrderValues::FullTax]        = src.TaxValFtaxRSDisc       ;
    dest.TaxValueRTShip_[pxOrderValues::FullTax]            = src.TaxValFtaxRS           ;
    dest.TaxValueRTDisc_[pxOrderValues::LowTax]        = src.TaxValLtaxRSDisc       ;
    dest.TaxValueRTShip_[pxOrderValues::LowTax]          = src.TaxValLtaxRS           ;

	dest.OrderValueTaxFSDisc_[pxOrderValues::NoTax] = src.OrdValNtaxFSDisc;
	dest.OrderValueTaxFSShip_[pxOrderValues::NoTax] = src.OrdValNtaxFS;
	dest.OrderValueTaxHFDisc_[pxOrderValues::NoTax] = src.OrdValNtaxHFDisc;
	dest.OrderValueTaxHFShip_[pxOrderValues::NoTax] = src.OrdValNtaxHF;
	dest.OrderValueTaxRTDisc_[pxOrderValues::NoTax] = src.OrdValNtaxRSDisc;
	dest.OrderValueTaxRTShip_[pxOrderValues::NoTax] = src.OrdValNtaxRS;
	dest.TaxValueFSDisc_[pxOrderValues::NoTax]      = src.TaxValNtaxFSDisc;
	dest.TaxValueFSShip_[pxOrderValues::NoTax]      = src.TaxValNtaxFS;
	dest.TaxValueHFDisc_[pxOrderValues::NoTax]      = src.TaxValNtaxHFDisc;
	dest.TaxValueHFShip_[pxOrderValues::NoTax]      = src.TaxValNtaxHF;
	dest.TaxValueRTDisc_[pxOrderValues::NoTax]      = src.TaxValNtaxRSDisc;
	dest.TaxValueRTShip_[pxOrderValues::NoTax]      = src.TaxValNtaxRS;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderValues :: Init()
{
    tKDAUFTRAGWERTE    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGWERTE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGWERTE struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxOrderValues&
pxOrderValues :: operator=( const pxOrderValues& src)
{
    tKDAUFTRAGWERTE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGWERTE structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderValues&
pxOrderValues :: operator=( const tKDAUFTRAGWERTE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderValues list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderValues :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderValues *that = (pxOrderValues*)That;
    int   retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
              : (KdAuftragNr_ > KdAuftragNr_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CalcOrderValuers                                                          */
/*----------------------------------------------------------------------------*/
int
pxOrderValues :: CalcOrderValues
(
    pxOrderItem* item
)
{
    short TaxLevel = 0;

    if ( item->ArtBase() && item->ArtBase()->IsGoodState() )
    {
       TaxLevel = item->ArtBase()->TaxLevel();
    }

        if(TaxLevel >= MAXTAXLEVEL)
                return 1;

        if(item->IsPriceTypeFreeSale())              // FV
        {
                OrderValueFSDisc_[TaxLevel]             += item->WertNetto();
                OrderValueFSShip_[TaxLevel]     += item->ShipValue();
                TaxValueFSDisc_[TaxLevel]        = OrderValueFSDisc_[TaxLevel] * item->SalesTaxRate()/100.0;
                TaxValueFSShip_[TaxLevel]        = OrderValueFSShip_[TaxLevel] * item->SalesTaxRate()/ 100.0;
                OrderValueTaxFSDisc_[TaxLevel]   = OrderValueFSDisc_[TaxLevel] + TaxValueFSDisc_[TaxLevel];
                OrderValueTaxFSShip_[TaxLevel]   = OrderValueFSShip_[TaxLevel] + TaxValueFSShip_[TaxLevel];
    }// if(item->IsPriceTypeFreeSale())

    if(item->IsPriceTypeHealthFund())            // KK
        {
                OrderValueHFDisc_[TaxLevel]             += item->WertNetto();
                OrderValueHFShip_[TaxLevel]     += item->ShipValue();
                TaxValueHFDisc_[TaxLevel]     = OrderValueHFDisc_[TaxLevel] * item->SalesTaxRate()/100.0;
                TaxValueHFShip_[TaxLevel]     = OrderValueHFShip_[TaxLevel] * item->SalesTaxRate()/100.0;
                OrderValueTaxHFDisc_[TaxLevel]   = OrderValueHFDisc_[TaxLevel] + TaxValueHFDisc_[TaxLevel];
                OrderValueTaxHFShip_[TaxLevel]   = OrderValueHFShip_[TaxLevel] + TaxValueHFShip_[TaxLevel];
    }// if(item->IsPriceTypeHealthFund())

    if(item->IsPriceTypeRetail())                               // EH
        {
                OrderValueRTDisc_[TaxLevel]             += item->WertNetto();
                OrderValueRTShip_[TaxLevel]     += item->ShipValue();
                TaxValueRTDisc_[TaxLevel]     = OrderValueRTDisc_[TaxLevel] * item->SalesTaxRate()/100.0;
                TaxValueRTShip_[TaxLevel]     = OrderValueRTShip_[TaxLevel] * item->SalesTaxRate()/100.0;
                OrderValueTaxRTDisc_[TaxLevel]   = OrderValueRTDisc_[TaxLevel] + TaxValueRTDisc_[TaxLevel];
                OrderValueTaxRTShip_[TaxLevel]   = OrderValueRTShip_[TaxLevel] + TaxValueRTShip_[TaxLevel];
    }// if(item->IsPriceTypeRetail())


    SetDirty();
    return 0;
}// CalcOrderValues

/*----------------------------------------------------------------------------*/
/*  ReduceOrderValues                                                          */
/*----------------------------------------------------------------------------*/
int
pxOrderValues :: ReduceOrderValues
(
    pxOrderItem* item,
    long        Qty
)
{
    pxCustBase&       customer = *(item->Order().Customer());
    bool  GrossoPreis = customer.CustomerGroupFlagsList()->isGroupBasePriceGEP();
    short TaxLevel = 0;
	if ( item->ArtBase() && item->ArtBase()->IsGoodState() )
    {
       TaxLevel = item->ArtBase()->TaxLevel();
    }

        if(TaxLevel >= MAXTAXLEVEL)
                return 1;

        if(item->IsPriceTypeFreeSale())              // FV
        {
                OrderValueFSDisc_[TaxLevel]      = OrderValueTaxFSDisc_[TaxLevel];
                OrderValueFSShip_[TaxLevel]      = OrderValueTaxFSShip_[TaxLevel];
                OrderValueFSDisc_[TaxLevel]     -= TaxValueFSDisc_[TaxLevel];
                OrderValueFSShip_[TaxLevel]     -= TaxValueFSShip_[TaxLevel];
                OrderValueFSDisc_[TaxLevel]     -= item->PreisFaktur() * (double)Qty;
                if (GrossoPreis)
                {
                   OrderValueFSShip_[TaxLevel]  -= item->PreisEKGrosso() * (double)Qty;
                }
                else
                {
                   OrderValueFSShip_[TaxLevel]  -= item->PreisEKApo() * (double)Qty;
                }
                TaxValueFSDisc_[TaxLevel]        = OrderValueFSDisc_[TaxLevel] * item->SalesTaxRate()/100.0;
                TaxValueFSShip_[TaxLevel]        = OrderValueFSShip_[TaxLevel] * item->SalesTaxRate()/ 100.0;
                OrderValueTaxFSDisc_[TaxLevel]   = OrderValueFSDisc_[TaxLevel] + TaxValueFSDisc_[TaxLevel];
                OrderValueTaxFSShip_[TaxLevel]   = OrderValueFSShip_[TaxLevel] + TaxValueFSShip_[TaxLevel];
    }// if(item->IsPriceTypeFreeSale())

    if(item->IsPriceTypeHealthFund())            // KK
        {
                OrderValueHFDisc_[TaxLevel]      = OrderValueTaxHFDisc_[TaxLevel];
                OrderValueHFShip_[TaxLevel]      = OrderValueTaxHFShip_[TaxLevel];
                OrderValueHFDisc_[TaxLevel]     -= TaxValueHFDisc_[TaxLevel];
                OrderValueHFShip_[TaxLevel]     -= TaxValueHFShip_[TaxLevel];
                OrderValueHFDisc_[TaxLevel]     -= item->PreisFaktur() * (double)Qty;
                if (GrossoPreis)
                {
                   OrderValueHFShip_[TaxLevel]  -= item->PreisEKGrosso() * (double)Qty;
                }
                else
                {
                   OrderValueHFShip_[TaxLevel]  -= item->PreisEKApo() * (double)Qty;
                }
                TaxValueHFDisc_[TaxLevel]     = OrderValueHFDisc_[TaxLevel] * item->SalesTaxRate()/100.0;
                TaxValueHFShip_[TaxLevel]     = OrderValueHFShip_[TaxLevel] * item->SalesTaxRate()/100.0;
                OrderValueTaxHFDisc_[TaxLevel]   = OrderValueHFDisc_[TaxLevel] + TaxValueHFDisc_[TaxLevel];
                OrderValueTaxHFShip_[TaxLevel]   = OrderValueHFShip_[TaxLevel] + TaxValueHFShip_[TaxLevel];
    }// if(item->IsPriceTypeHealthFund())

    if(item->IsPriceTypeRetail())                               // EH
        {
                OrderValueRTDisc_[TaxLevel]      =  OrderValueTaxRTDisc_[TaxLevel];
                OrderValueRTShip_[TaxLevel]              =      OrderValueTaxRTShip_[TaxLevel];
                OrderValueRTDisc_[TaxLevel]     -=  TaxValueRTDisc_[TaxLevel];
                OrderValueRTShip_[TaxLevel]     -=      TaxValueRTShip_[TaxLevel];
                OrderValueRTDisc_[TaxLevel]     -= item->PreisFaktur() * (double)Qty;
                if (GrossoPreis)
                {
                   OrderValueRTShip_[TaxLevel]  -= item->PreisEKGrosso() * (double)Qty;
                }
                else
                {
                   OrderValueRTShip_[TaxLevel]  -= item->PreisEKApo() * (double)Qty;
                }
                TaxValueRTDisc_[TaxLevel]     = OrderValueRTDisc_[TaxLevel] * item->SalesTaxRate()/100.0;
                TaxValueRTShip_[TaxLevel]     = OrderValueRTShip_[TaxLevel] * item->SalesTaxRate()/100.0;
                OrderValueTaxRTDisc_[TaxLevel]   = OrderValueRTDisc_[TaxLevel] + TaxValueRTDisc_[TaxLevel];
                OrderValueTaxRTShip_[TaxLevel]   = OrderValueRTShip_[TaxLevel] + TaxValueRTShip_[TaxLevel];
    }// if(item->IsPriceTypeRetail())


    SetDirty();
    return 0;
}// CalcOrderValues

/*----------------------------------------------------------------------------*/
/*  InitOrderValues                                                           */
/*----------------------------------------------------------------------------*/
int
pxOrderValues :: InitOrderValues
(
)
{
    OrdValFtaxFSDisc_  = pxConstants::mZero;
    OrdValFtaxFS_      = pxConstants::mZero;
    TaxValFtaxFSDisc_  = pxConstants::mZero;
    TaxValFtaxFS_      = pxConstants::mZero;
    OrdValLtaxFSDisc_  = pxConstants::mZero;
    OrdValLtaxFS_      = pxConstants::mZero;
    TaxValLtaxFSDisc_  = pxConstants::mZero;
    TaxValLtaxFS_      = pxConstants::mZero;
    OrdValFtaxHFDisc_  = pxConstants::mZero;
    OrdValFtaxHF_      = pxConstants::mZero;
    TaxValFtaxHFDisc_  = pxConstants::mZero;
    TaxValFtaxHF_      = pxConstants::mZero;
    OrdValLtaxHFDisc_  = pxConstants::mZero;
    OrdValLtaxHF_      = pxConstants::mZero;
    TaxValLtaxHFDisc_  = pxConstants::mZero;
    TaxValLtaxHF_      = pxConstants::mZero;
    OrdValFtaxRSDisc_  = pxConstants::mZero;
    OrdValFtaxRS_      = pxConstants::mZero;
    TaxValFtaxRSDisc_  = pxConstants::mZero;
    TaxValFtaxRS_      = pxConstants::mZero;
    OrdValLtaxRSDisc_  = pxConstants::mZero;
    OrdValLtaxRS_      = pxConstants::mZero;
    TaxValLtaxRSDisc_  = pxConstants::mZero;
    TaxValLtaxRS_      = pxConstants::mZero;
	OrdValNtaxFSDisc_  = pxConstants::mZero;
	OrdValNtaxFS_      = pxConstants::mZero;
	OrdValNtaxHFDisc_  = pxConstants::mZero;
	OrdValNtaxHF_      = pxConstants::mZero;
	OrdValNtaxRSDisc_  = pxConstants::mZero;
	OrdValNtaxRS_      = pxConstants::mZero;
	TaxValNtaxFSDisc_  = pxConstants::mZero;
	TaxValNtaxFS_      = pxConstants::mZero;
	TaxValNtaxHFDisc_  = pxConstants::mZero;
	TaxValNtaxHF_      = pxConstants::mZero;
	TaxValNtaxRSDisc_  = pxConstants::mZero;
	TaxValNtaxRS_      = pxConstants::mZero;


    for(int i=0; i<MAXTAXLEVEL; i++)
        {
                OrderValueFSDisc_[i]=pxConstants::mZero;      // Order value for freesales items based on discounted prices (FS)
                OrderValueFSShip_[i]=pxConstants::mZero;      // Order value for freesales items based on normal prices (FS)
                TaxValueFSDisc_[i]=pxConstants::mZero;        // Tax value for freesales items based on discounted prices (FS)
                TaxValueFSShip_[i]=pxConstants::mZero;        // Tax value for freesales items based on normal prices (FS)
                OrderValueTaxFSDisc_[i]=pxConstants::mZero;
                OrderValueTaxFSShip_[i]=pxConstants::mZero;

                OrderValueHFDisc_[i]=pxConstants::mZero;      // Order value for health fund items based on discounted prices (HF)
                OrderValueHFShip_[i]=pxConstants::mZero;      // Order value for health fund items based on normal prices (HF)
                TaxValueHFDisc_[i]=pxConstants::mZero;        // Tax value for health fund  items based on discounted prices (HF)
                TaxValueHFShip_[i]=pxConstants::mZero;        // Tax value for health fund  items based on normal prices (HF)
                OrderValueTaxHFDisc_[i]=pxConstants::mZero;
                OrderValueTaxHFShip_[i]=pxConstants::mZero;

                OrderValueRTDisc_[i]=pxConstants::mZero;      // Order value for retail items based on discounted prices (RT)
                OrderValueRTShip_[i]=pxConstants::mZero;      // Order value for retail items based on normal prices (RT)
                TaxValueRTDisc_[i]=pxConstants::mZero;        // Tax value for retail  items based on discounted prices (RT)
                TaxValueRTShip_[i]=pxConstants::mZero;        // Tax value for retail  items based on normal prices (RT)
                OrderValueTaxRTDisc_[i]=pxConstants::mZero;
                OrderValueTaxRTShip_[i]=pxConstants::mZero;
        }// for i

    return 0;
}


/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderValuesList :: pxOrderValuesList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxOrderValuesList :: Select
(
    const int     count_
)
{
    tKDAUFTRAGWERTE fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGWERTE));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxOrderValuesList :: Select
(
    const long    KdAuftragNr,
    const int     count_
)
{
    tKDAUFTRAGWERTE fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGWERTE));  // zero out entire record buffer
    fil.KdAuftragNr = KdAuftragNr;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderValuesList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxOrderValues' object:
    pxOrderValues *objectp = new pxOrderValues(Session(), *(tKDAUFTRAGWERTE*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderValues :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGWERTE record;
    memset(&record, 0, sizeof(tKDAUFTRAGWERTE));
    record.KdAuftragNr = KdAuftragNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLEQUOTA struct
   /* else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_AQUOT_ENTRY_NOTFOUND, BranchNo_, CustomerNo_, ArticleNo_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderValues :: Put
(
)
{
    tKDAUFTRAGWERTE record;
    memset(&record, 0, sizeof(tKDAUFTRAGWERTE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGWERTE));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderValues :: Delete
(
)
{
    tKDAUFTRAGWERTE record;
    memset(&record, 0, sizeof(tKDAUFTRAGWERTE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderValues :: Read
(
    const void  *record
)
{
    return pxOrderValuesRead((tKDAUFTRAGWERTE*)record);
}

int
pxOrderValues :: ReadLock
(
    const void  *record
)
{
    return pxOrderValuesReadLock((tKDAUFTRAGWERTE*)record);
}

int
pxOrderValues :: Update
(
    const void  *record
)
{
    return pxOrderValuesUpdate((tKDAUFTRAGWERTE*)record);
}

int
pxOrderValues :: Delete
(
    const void  *record
)
{
    return pxOrderValuesDelete((tKDAUFTRAGWERTE*)record);
}

int
pxOrderValues :: Insert
(
    const void  *record
)
{
    return pxOrderValuesInsert((tKDAUFTRAGWERTE*)record);
}

int
pxOrderValuesList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderValuesEndBrowse(cursorid);
}


int
pxOrderValuesList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxOrderValuesGetNext((tKDAUFTRAGWERTE*)record, cursorid);
}

int
pxOrderValuesList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderValuesStartBrowse((tKDAUFTRAGWERTE*)keys, cursorid);
}
