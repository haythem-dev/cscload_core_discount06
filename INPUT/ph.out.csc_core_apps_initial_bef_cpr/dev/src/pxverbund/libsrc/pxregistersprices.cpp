#include "pxregistersprices.hpp"
#include "tregistersprices.h"
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxRegistersPrices::pxRegistersPrices()
{
    Init();
}

pxRegistersPrices::pxRegistersPrices
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
pxRegistersPrices::pxRegistersPrices
(
	pxRegistersPrices& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLELPPR structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxRegistersPrices::pxRegistersPrices
(
    pxSession   *session,
	tREGISTERSPRICES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRegistersPrices::pxRegistersPrices
(
    pxSession* session,
	const nString& MinistryProductCode                // Read via this type
)
    : pxDBRecord(session)
{
    Init();
	MinistryProductCode_ = MinistryProductCode;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRegistersPrices::~pxRegistersPrices()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLELPPR structure.        */
/*----------------------------------------------------------------------------*/
tREGISTERSPRICES&
Assign
(
	tREGISTERSPRICES&     dest,
    const pxRegistersPrices&  src
)
{
	dest.MinistryProductCode[0] = ' ';
	src.MinistryProductCode_.GetData(dest.MinistryProductCode);
	dest.DateValidFrom       = src.DateValidFrom_.GetYYYYMMDD();
	dest.MaxWholeSalePrice   = src.MaxWholesalePrice_;
	dest.ReferencePrice      = src.ReferencePrice_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLELPPR structure to a                */
/*  pxArticleLppr object.                                                     */
/*----------------------------------------------------------------------------*/
pxRegistersPrices&
Assign
(
	pxRegistersPrices&          dest,
    const tREGISTERSPRICES& src
)
{
    dest.MinistryProductCode_ = src.MinistryProductCode;
	dest.MinistryProductCode_.Strip();
	dest.DateValidFrom_       = nDate(src.DateValidFrom);
	dest.MaxWholesalePrice_   = src.MaxWholeSalePrice;
	dest.ReferencePrice_      = src.ReferencePrice;
	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRegistersPrices:: Init()
{
	tREGISTERSPRICES    record;
    memset(&record, 0 , sizeof(tREGISTERSPRICES));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTICLELPPR struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxRegistersPrices&
pxRegistersPrices :: operator=( const pxRegistersPrices& src)
{
	tREGISTERSPRICES    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLELPPR structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxRegistersPrices&
pxRegistersPrices :: operator=( const tREGISTERSPRICES& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxRegistersPrices:: Get
(
    DBAccessMode mode
)

{
	tREGISTERSPRICES record;
    memset(&record, 0, sizeof(tREGISTERSPRICES));
    Assign(record, *this);              // resolve keys
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tARTICLELPPR struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
//int
//pxRegistersPrices:: Put
//(
//)
//
//{
//	tARTICLEPRICELIMITATION record;
//    memset(&record, 0, sizeof(tREGISTERSPRICES));
//    Assign(record, *this);
//    return nDBWrite(&record, sizeof(tREGISTERSPRICES));
//}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxRegistersPrices:: Read
(
    const void  *record
)
{
    return pxRegistersPricesRead((tREGISTERSPRICES*)record);
}

//int pxRegistersPrices::ReadLock(const void* /*record*/)
//{
//    return cDBXR_ISDOWN;                // not implemented
//}
//
//int pxRegistersPrices::Update(const void* /*record*/)
//{
//    return cDBXR_ISDOWN;                // not implemented
//}
//
//int pxRegistersPrices::Insert(const void* /*record*/)
//{
//	return cDBXR_ISDOWN;                // not implemented
//}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArticleLppr list objects being inserted in the following ascending */
/*  sequence:    ArticleNo, DatumGueltigAb, DatumGueltigBis.                  */
/*----------------------------------------------------------------------------*/
int
pxRegistersPrices:: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
	pxRegistersPrices *that = (pxRegistersPrices*)That;

    int retval = (MinistryProductCode_	== that->MinistryProductCode_) ? 0
               : (MinistryProductCode_ > that->MinistryProductCode_ ? 1 : -1);
    return retval;
}

const nMoney& pxRegistersPrices::getMaxWholesalePrice() const
{
    return MaxWholesalePrice();
}

const nMoney& pxRegistersPrices::getReferencePrice() const
{
    return ReferencePrice();
}
