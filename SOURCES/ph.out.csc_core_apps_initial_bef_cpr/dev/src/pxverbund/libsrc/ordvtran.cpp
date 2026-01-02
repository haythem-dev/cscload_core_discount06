#include "pxordvtr.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxcstbas.hpp"
#include "pxcstot.hpp"
#include "csccustomer.hpp"

/*----------------------------------------------------------------------------*/
pxOrderValidTrans::pxOrderValidTrans( pxSession* session )
    :pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
pxOrderValidTrans::pxOrderValidTrans( pxOrderValidTrans& src )
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
pxOrderValidTrans::pxOrderValidTrans( pxSession* session, tAUFTRAGARTKOMB& src )
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
pxOrderValidTrans::pxOrderValidTrans( pxSession* session, const pxOrderValidTrans* srcp )
    : pxDBRecord(session)
{
    Init();
    if (srcp != NULL) (*this) = *srcp;
}

/*----------------------------------------------------------------------------*/
pxOrderValidTrans::pxOrderValidTrans( pxSession* session, nString& KdAuftragArt, short VertriebszentrumNr, DBAccessMode mode)
    : pxDBRecord(session)
{
    Init();
    KdAuftragArt_ = KdAuftragArt;
    VertriebszentrumNr_ = VertriebszentrumNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
tAUFTRAGARTKOMB& Assign( tAUFTRAGARTKOMB& dest, const pxOrderValidTrans& src )
{
    dest.KdAuftragArt[0] = ' ';
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);
    dest.KoArt = src.KoArt_;
    dest.BuchArt = src.BuchArt_;
    dest.TourId[0] = ' ';
    src.TourId_.GetData(dest.TourId);
    dest.VertriebszentrumNr = src.VertriebszentrumNr_;
	dest.CalcExpressDeliveryCharge = src.CalcExpressDeliveryCharge_;
    return dest;
}

/*----------------------------------------------------------------------------*/
pxOrderValidTrans& Assign( pxOrderValidTrans& dest, const tAUFTRAGARTKOMB& src )
{
    dest.KdAuftragArt_  = src.KdAuftragArt;
    dest.KoArt_   = src.KoArt;
    dest.BuchArt_   = src.BuchArt;
    dest.TourId_ = src.TourId;
	dest.CalcExpressDeliveryCharge_ = src.CalcExpressDeliveryCharge;

    nString copyOfTour(dest.TourId_);
    copyOfTour.Strip();
    if (copyOfTour.IsEmpty()) dest.TourId_.Clear();
    dest.VertriebszentrumNr_ = src.VertriebszentrumNr;

    return dest;
}

/*----------------------------------------------------------------------------*/
int pxOrderValidTrans::CompareTo( const nCollectable* That, void* /* p */, const long /* lparm */ ) const
{
    pxOrderValidTrans *that = (pxOrderValidTrans*)That;
	int retval = 0;

    if( 0 == retval ) retval = (VertriebszentrumNr_ == that->VertriebszentrumNr_) ? 0 : (VertriebszentrumNr_ >  that->VertriebszentrumNr_  ? 1 : -1);
	if( 0 == retval ) retval = (CalcExpressDeliveryCharge_ == that->CalcExpressDeliveryCharge_) ? 0 : (CalcExpressDeliveryCharge_ >  that->CalcExpressDeliveryCharge_ ? 1 : -1);	
    if( 0 == retval ) retval = (KdAuftragArt_ == that->KdAuftragArt_) ? 0 : (KdAuftragArt_ >  that->KdAuftragArt_  ? 1 : -1);
    if( 0 == retval ) retval = (KoArt_ == that->KoArt_) ? 0 : (KoArt_ >  that->KoArt_  ? 1 : -1);    
	if( 0 == retval ) retval = (BuchArt_ == that->BuchArt_) ? 0 : (BuchArt_ >  that->BuchArt_  ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
void
pxOrderValidTrans :: Init()
{
    tAUFTRAGARTKOMB    record;
    memset(&record, 0 , sizeof(tAUFTRAGARTKOMB));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
bool pxOrderValidTrans::isCalcExpressDeliveryCharge() const
{
	if( this->CalcExpressDeliveryCharge_ != 1 )
	{
		return false;
	}
	return true;
}

/*----------------------------------------------------------------------------*/
const nString& pxOrderValidTrans::KdAuftragArt() const
{
	return KdAuftragArt_;
}

/*----------------------------------------------------------------------------*/
char pxOrderValidTrans::BuchArt() const
{ 
	return BuchArt_; 
}

/*----------------------------------------------------------------------------*/
char pxOrderValidTrans::KoArt() const 
{ 
	return KoArt_; 
}

/*----------------------------------------------------------------------------*/
const nString& pxOrderValidTrans::TourId() const
{ 
	return TourId_; 
}

/*----------------------------------------------------------------------------*/
short pxOrderValidTrans::VertriebszentrumNr() const
{
	return VertriebszentrumNr_; 
}

/*----------------------------------------------------------------------------*/
/*virtual*/ int pxOrderValidTrans::Insert(const void *record) 
{ 
	return pxAufArtKombInsert((tAUFTRAGARTKOMB*)record); 
}

/*----------------------------------------------------------------------------*/
/*virtual*/ int pxOrderValidTrans::Update(const void* /*record*/) // no update, because all columns are key values
{ 
	return 1; 
}

/*----------------------------------------------------------------------------*/
/*virtual*/ int pxOrderValidTrans::Read(const void *record) 
{ 
	return pxAufArtKombRead((tAUFTRAGARTKOMB*)record); 
}

/*----------------------------------------------------------------------------*/								
/*virtual*/ int pxOrderValidTrans::ReadLock(const void *record) 
{ 
	return pxAufArtKombReadLock((tAUFTRAGARTKOMB*)record); 
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tAUFTRAGARTKOMB     */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxOrderValidTrans&
pxOrderValidTrans :: operator=( const pxOrderValidTrans& src)
{
    tAUFTRAGARTKOMB    record;              // used to export the data of 'src'
    memset(&record, 0 , sizeof(tAUFTRAGARTKOMB));
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tAUFTRAGARTKOMB structure to this instance.      */
/*----------------------------------------------------------------------------*/
pxOrderValidTrans&
pxOrderValidTrans :: operator=( const tAUFTRAGARTKOMB& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderValidTrans :: Get
(
    DBAccessMode mode
)

{
    tAUFTRAGARTKOMB record;
    memset(&record, 0, sizeof(tAUFTRAGARTKOMB));
    Assign(record, *this);
    int retval = ( mode == cDBGET_FORUPDATE )
                  ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;         // import the data from tAUFTRAGARTKOMB struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderValidTrans :: Put
(
)

{
    tAUFTRAGARTKOMB record;
    memset(&record, 0, sizeof(tAUFTRAGARTKOMB));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tAUFTRAGARTKOMB));
}

/*----------------------------------------------------------------------------*/
/*  List constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderValidTransList :: pxOrderValidTransList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Select all rows.                                                          */
/*----------------------------------------------------------------------------*/
size_t
pxOrderValidTransList :: Select
(
    const short   VertriebszentrumNr
)
{
    tAUFTRAGARTKOMB record;
    memset(&record, 0, sizeof(tAUFTRAGARTKOMB));
    record.VertriebszentrumNr = VertriebszentrumNr;
    int cursorid = cCRS_DEFAULT;       // set cursor id
    nDBSelect(&record, cursorid, cDEFAULT);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderValidTransList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxOrderValidTrans *objectp = new pxOrderValidTrans(Session(), *(tAUFTRAGARTKOMB*)record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Find a unique Entry in the List                                           */
/*----------------------------------------------------------------------------*/
pxOrderValidTrans*
pxOrderValidTransList :: Find
(
    const nString&  OrderType,
    const int       CommiType,
    const int       StockTrans,
    const short    VZNr
)   const
{
    pxOrderValidTrans *item;
    pxOrderValidTransListIter it(*(pxOrderValidTransList*)this);
    nString s(OrderType);               // guarantee constness
    s.ToUpper();                        // before

  //  while ( (item =  (pxOrderValidTrans*) ++it) && item->KdAuftragArt_ <= s )
    while ( (item = (pxOrderValidTrans*) ++it) != NULL )
    {
       if ( (item->KdAuftragArt_ == s) &&
            (CommiType == cDEFAULT || CommiType  == (item->KoArt_ - '0') || (CommiType - '0') == (item->KoArt_ - '0')) &&
            (StockTrans == cDEFAULT || StockTrans == (item->BuchArt_ - '0') || (StockTrans - '0') == (item->BuchArt_ - '0')) &&
             item->VertriebszentrumNr_ == VZNr )
         return item;                  // found

    }
    return NULL;                        // not found, return NULL pointer
}


/*----------------------------------------------------------------------------*/
/*  Find an order type under respect of the order types allowed for a         */
/*  customer.                                                                 */
/*----------------------------------------------------------------------------*/
pxOrderValidTrans*
pxOrderValidTransList :: Find
(
    pxCustBase&     customer,
    const nString&  OrderType,
    const int       CommiType,
    const int       StockTrans
)   const
{
    pxOrderValidTrans    *vtp = NULL;
    pxCustOrderType      *otp;
    pxCustOrderType      *defaultp;
    nString s(OrderType);

    nString stdocs(customer.StdAufKoBuart());  //Standard ordertyp,Commitype and Stocktrans
    stdocs.ToUpper();
    stdocs.Strip();
    nString stdot;
    if ( !stdocs.IsEmpty() )
       stdot = stdocs(0,2);                  //Standard ordertype

    pxCustOrderTypeList  *otlp = customer.OrderTypeList();
    int ct         = ( CommiType > 0 ) ? CommiType : cDEFAULT;
    int st         = ( StockTrans > 0 ) ? StockTrans : cDEFAULT;
    pxDevice *dvcp = ((pxOrderValidTransList*)this)->Session()->Device();
    otp = defaultp = otlp->GetDefault();

    s.ToUpper();
    s.Strip();
    if ( s.IsEmpty() )                  // then must assign a default or standard
    {
       ct = st = cDEFAULT;
       if ( defaultp )
          s = defaultp->KdAuftragArt();

       if ( ! stdocs.IsEmpty() )        // the customer has a standard ordertype
       {
           otp = otlp->Find(stdot, customer.Vertriebszentrum(), customer.KundenNr());
          if (otp)
          {
             vtp = Find(stdot, (int) *( (char*) stdocs+2),
                               (int) *( (char*) stdocs+3),customer.Vertriebszentrum() );
             if ( dvcp->IsDCT() && !otp->IsValidViaDCT() )
                vtp = NULL;             // order type not valid for DCT
          }
       }

       if ( dvcp->IsDCT() && !vtp )     // there is  no standard defined
       {
          if ( !defaultp->IsDefault() ) // defaultp is not default ordertype
          {
              otp = otlp->AddDefault(customer.Vertriebszentrum(), customer.KundenNr());
             if (otp)
                s   = otp->KdAuftragArt();
          }
       }
    }


    if ( !vtp && ((otp = otlp->Find(s, customer.Vertriebszentrum(), customer.KundenNr())) != NULL) )
    {                                   // ensure type is valid for customer
       vtp = Find(s, ct, st,customer.Vertriebszentrum());
       if ( dvcp->IsDCT() && !otp->IsValidViaDCT() )
          vtp = NULL;                   // order type not valid for DCT
    }
    return vtp;
}

/*----------------------------------------------------------------------------*/
/*  Find an order type under respect of the order types allowed for a         */
/*  customer.                                                                 */
/*----------------------------------------------------------------------------*/
pxOrderValidTrans* pxOrderValidTransList::FindByCustomer( CSCCustomer* customer, const nString& OrderType, const int /*CommiType*/, const int /*StockTrans*/) 
{
	if( NULL == customer )
	{
		return NULL;
	}	

	pxOrderValidTrans* retval = NULL; 
	nString orderType( OrderType ); orderType.ToUpper(); orderType.Strip();		
	nString defaultOrderTypeComb = customer->getDefaultOrderTypeCombination();
	nString defaultOrderType = customer->getDefaultOrderType();
//	int pickingType = ( CommiType > 0 ) ? CommiType : cDEFAULT;
//	int bookingType = ( StockTrans > 0 ) ? StockTrans : cDEFAULT;	
	pxCustOrderTypeList* ordertypelist = customer->getCustomerOrderTypeList();
	pxDevice* device = Session()->Device();	
	pxCustOrderType* custOrderType = ordertypelist->GetDefault();
	pxCustOrderType* defaultCustOrderType = ordertypelist->GetDefault();

	if( orderType.IsEmpty() )
	{
//		pickingType = cDEFAULT;
//		bookingType = cDEFAULT;
		if( defaultCustOrderType )
		{
			orderType = defaultCustOrderType->KdAuftragArt();
		}

		if( !defaultOrderTypeComb.IsEmpty() )
		{
            custOrderType = ordertypelist->Find(defaultOrderType, customer->getBranchNo(), customer->getCustomerNo());
			if (custOrderType)
			{				
				if( !(device->IsDCT() && !custOrderType->IsValidViaDCT()) )
				{
					retval = this->Find( defaultOrderType, (int)*( (char*)defaultOrderTypeComb + 2 ), (int)*( (char*)defaultOrderTypeComb + 3 ), customer->getBranchNo() );
				}
			}
		}
	}

	if( !orderType.IsEmpty() )
	{
		if( device->IsDCT() && NULL == retval )
		{
			if( !defaultCustOrderType->IsDefault() )
			{
                custOrderType = ordertypelist->AddDefault(customer->getBranchNo(), customer->getCustomerNo());
				if (custOrderType)
				{
					orderType = custOrderType->KdAuftragArt();
				}
			}
		}
	}

	if( !retval )
	{
        custOrderType = ordertypelist->Find(orderType, customer->getBranchNo(), customer->getCustomerNo());
		if (custOrderType)
		{
			if( device->IsDCT() && !custOrderType->IsValidViaDCT() )
			{
				retval = NULL;
			}
		}
	}

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Find the BranchNo within this list                                        */
/*----------------------------------------------------------------------------*/
short pxOrderValidTransList::Find( const short BranchNo ) 
{
    short branchno = 0;
    pxOrderValidTransListIter cursor(*this);
    pxOrderValidTrans   *temp;
    while ( (temp = (pxOrderValidTrans*) ++cursor) != NULL )
    {
       if ( temp->VertriebszentrumNr_ ==  BranchNo )
       {
          branchno = temp->VertriebszentrumNr_;
          break;
       }
    }

    return branchno;
}

int pxOrderValidTransList::EndBrowse(const int cursorid)
{
    return pxAufArtKombEndBrowse(cursorid);
}

int pxOrderValidTransList::GetNext(const void* record, const int cursorid)
{
    return pxAufArtKombGetNext((tAUFTRAGARTKOMB*)record, cursorid);
}

int pxOrderValidTransList::StartBrowse(const void *keys, const int cursorid)
{
    return pxAufArtKombStartBrowse((tAUFTRAGARTKOMB*)keys, cursorid);
}
