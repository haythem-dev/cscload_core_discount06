#include "pxnhifprices.hpp"
#include "tnhifprices.h"
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxNHIFPrices::pxNHIFPrices()
{
    Init();
}

pxNHIFPrices::pxNHIFPrices
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
pxNHIFPrices::pxNHIFPrices
(
	pxNHIFPrices& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLELPPR structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxNHIFPrices::pxNHIFPrices
(
    pxSession   *session,
	tNHIFPRICES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxNHIFPrices::pxNHIFPrices
(
    pxSession* session,
	const nString& HealthFundCodeHospital                // Read via this type
)
    : pxDBRecord(session)
{
    Init();
	HealthFundCodeHospital_ = HealthFundCodeHospital;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxNHIFPrices::~pxNHIFPrices()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLELPPR structure.        */
/*----------------------------------------------------------------------------*/
tNHIFPRICES&
Assign
(
	tNHIFPRICES&     dest,
    const pxNHIFPrices&  src
)
{
	dest.HealthFundCodeHospital[0] = ' ';
	src.HealthFundCodeHospital_.GetData(dest.HealthFundCodeHospital);
	dest.DateValidFrom       = src.DateValidFrom_.GetYYYYMMDD();
	dest.NHIFPrice   = src.NHIFPrice_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLELPPR structure to a                */
/*  pxArticleLppr object.                                                     */
/*----------------------------------------------------------------------------*/
pxNHIFPrices&
Assign
(
	pxNHIFPrices&          dest,
    const tNHIFPRICES& src
)
{
    dest.HealthFundCodeHospital_ = src.HealthFundCodeHospital;
	dest.HealthFundCodeHospital_.Strip();
	dest.DateValidFrom_       = nDate(src.DateValidFrom);
	dest.NHIFPrice_   = src.NHIFPrice;
	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxNHIFPrices:: Init()
{
	tNHIFPRICES    record;
    memset(&record, 0 , sizeof(tNHIFPRICES));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTICLELPPR struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxNHIFPrices&
pxNHIFPrices :: operator=( const pxNHIFPrices& src)
{
	tNHIFPRICES    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLELPPR structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxNHIFPrices&
pxNHIFPrices :: operator=( const tNHIFPRICES& src)
{
    return Assign(*this, src);
}

const nMoney& pxNHIFPrices::getNHIFPrice() const
{
    return NHIFPrice();
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxNHIFPrices:: Get
(
    DBAccessMode mode
)

{
	tNHIFPRICES record;
    memset(&record, 0, sizeof(tNHIFPRICES));
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
pxNHIFPrices:: Read
(
    const void  *record
)
{
    return pxNHIFPricesRead((tNHIFPRICES*)record);
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
pxNHIFPrices:: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
	pxNHIFPrices *that = (pxNHIFPrices*)That;

    int retval = (HealthFundCodeHospital_ == that->HealthFundCodeHospital_) ? 0
               : (HealthFundCodeHospital_ > that->HealthFundCodeHospital_ ? 1 : -1);
    return retval;
}
