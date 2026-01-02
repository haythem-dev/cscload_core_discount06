#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxcstbas.hpp"
#include "pxrangecollect.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxRangeCollect :: pxRangeCollect
(
    const short BranchNo,              // Branchnumber
    const long  DiscountGrpNo,         // DiscountGrpNo
    const long  PosNr,                 // Positionnumber
    const long  ArticleNo,             // Positionnumber
    const long  Quantity,              // Quantity
    const long  QtyPack,               // QtyPack
    const long  ManufacturerNo,        // ManufacturerNo
    double      ShipValue,             // ShipValue
    const long  ArtCategoryNo,         // Article Groupno
    const PriceTypeEnum PreisTyp       // PreisTyp
)
{
    BranchNo_         = BranchNo;
    DiscountGrpNo_    = DiscountGrpNo;
    PosNr_            = PosNr;
    ArticleNo_        = ArticleNo;
    Quantity_         = Quantity;
    QtyPack_          = QtyPack;
    ManufacturerNo_   = ManufacturerNo;
    ShipValue_        = ShipValue;
    ArtCategoryNo_    = ArtCategoryNo;
    PreisTyp_         = PreisTyp;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRangeCollect :: pxRangeCollect
(
    const pxRangeCollect& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRangeCollect :: ~pxRangeCollect()
{
    ;
}
/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxRangeCollect&
pxRangeCollect :: operator=( const pxRangeCollect& src)
{
    BranchNo_         = src.BranchNo_;
    DiscountGrpNo_    = src.DiscountGrpNo_;
    PosNr_            = src.PosNr_;
    ArticleNo_        = src.ArticleNo_;
    Quantity_         = src.Quantity_;
    QtyPack_          = src.QtyPack_;
    ManufacturerNo_   = src.ManufacturerNo_;
    ShipValue_        = src.ShipValue_;
    ArtCategoryNo_    = src.ArtCategoryNo_;
    PreisTyp_         = src.PreisTyp_;
    InvoiceValue_     = src.InvoiceValue_;
    NaturalRebateValue_ = src.NaturalRebateValue_;
    return *this;
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo, DiscountGrpNo                                                   */
/*----------------------------------------------------------------------------*/
int
pxRangeCollect :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxRangeCollect *that = (pxRangeCollect*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                  : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (DiscountGrpNo_ == that->DiscountGrpNo_) ? 0
                  : (DiscountGrpNo_ > that->DiscountGrpNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRangeCollectList :: Clear()
{

    pxRangeCollect  *curp;
    pxRangeCollectListIter cursor(*this);
    while ( (curp = (pxRangeCollect*) ++cursor) != NULL )
    {
       cursor.Remove();
       delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/*  SumQtyCollect returns sum of ordered quantity depend on ArticleNo and     */
/*  DiscountGrpNo                                                             */
/*----------------------------------------------------------------------------*/
long
pxRangeCollectList :: SumQtyCollect
(
    const long ArticleNo,
    const long DiscountGrpNo
)
{
    long sum = 0;
    pxRangeCollect  *curp;
    pxRangeCollectListIter cursor(*this);
    while ( (curp = (pxRangeCollect*) ++cursor) != NULL )
    {
       if (curp->ArticleNo() == ArticleNo && curp->DiscountGrpNo() == DiscountGrpNo )
       {
          sum += curp->Quantity();
       }
    }
    return sum;
}
/*----------------------------------------------------------------------------*/
/*  SumShipValue  returns sum of ordered quantity depend on ArticleNo and     */
/*  DiscountGrpNo                                                             */
/*----------------------------------------------------------------------------*/
double
pxRangeCollectList :: SumShipValue
(
    const long ManufacturerNo,
    const long DiscountGrpNo
)
{
    double sum = 0;
    pxRangeCollect  *curp;
    pxRangeCollectListIter cursor(*this);
    while ( (curp = (pxRangeCollect*) ++cursor) != NULL )
    {
       if (curp->ManufacturerNo() == ManufacturerNo && curp->DiscountGrpNo() == DiscountGrpNo )
       {
          sum += curp->ShipValue();
       }
    }
    return sum;
}
/*----------------------------------------------------------------------------*/
/*  ArticleSumShipValue returns sum of ordered quantity depend on ArticleNo   */
/*  and  DiscountGrpNo                                                        */
/*----------------------------------------------------------------------------*/
double
pxRangeCollectList :: ArticleSumShipValue
(
    const long ArticleNo,
    const long DiscountGrpNo
)
{
    double sum = 0;
    pxRangeCollect  *curp;
    pxRangeCollectListIter cursor(*this);
    while ( (curp = (pxRangeCollect*) ++cursor) != NULL )
    {
       if (curp->ArticleNo() == ArticleNo && curp->DiscountGrpNo() == DiscountGrpNo  )
       {
          sum += curp->ShipValue();
       }
    }
    return sum;
}

/*----------------------------------------------------------------------------*/
/*  SumInvoiceValue returns sum of the discount group invoice value depend on */
/*  DiscountGrpNo                                                             */
/*----------------------------------------------------------------------------*/
double
pxRangeCollectList :: SumInvoiceValue
(
    const long DiscountGrpNo
)
{
    double sum = 0;
    pxRangeCollect  *curp;
    pxRangeCollectListIter cursor(*this);
    while ( (curp = (pxRangeCollect*) ++cursor) != NULL )
    {
       if (curp->DiscountGrpNo() == DiscountGrpNo )
       {
          sum += curp->InvoiceValue();
       }
    }
    return sum;
}

/*----------------------------------------------------------------------------*/
/*  Find return entryp depend on articleno and discountgrpno                  */
/*----------------------------------------------------------------------------*/
pxRangeCollect*
pxRangeCollectList :: Find
(
    const long ArticleNo,
    const long DiscountGrpNo
)
{
    pxRangeCollect *curp = NULL;             // ptr to current entry
    pxRangeCollectListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxRangeCollect*) ++cursor) != NULL )
    {
       if (curp->ArticleNo() == ArticleNo && curp->DiscountGrpNo() == DiscountGrpNo )
       {
          break;
       }
    }
    return curp;
}
/*----------------------------------------------------------------------------*/
/* DeleteInvalidEntries delete all entries corredponding to DiscountGrpNo     */
/*----------------------------------------------------------------------------*/
int
pxRangeCollectList :: DeleteInvalidEntries
(
    const long DiscountGrpNo,
	const PriceTypeEnum PreisTyp
)
{
    int retval = 0;
    pxRangeCollect *curp = NULL;             // ptr to current entry
    pxRangeCollectListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxRangeCollect*) ++cursor) != NULL )
    {
       if (curp->DiscountGrpNo() == DiscountGrpNo  && curp->PreisTyp() == PreisTyp )
       {
          delete cursor.Remove();
       }
    }
    return retval;
}
