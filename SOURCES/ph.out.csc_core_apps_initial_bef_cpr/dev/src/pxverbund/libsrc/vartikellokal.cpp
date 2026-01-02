#include "pxvartikellokal.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "tourmanager.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <ibt/articlequotachecker/iarticlequotachecker.h>

extern bool pxGlobalIBTNoTimeCheck;

/*----------------------------------------------------------------------------*/
bool pxVartikelLokal::matchesIBTQtyAvailabilityPercentage( const long requestedQty ) const
{
    long qtyNeededForSatisfaction = static_cast<long>(requestedQty * (this->IBTQtyAvailabilityPercentage_ / 100.0));
    if( this->Bestand() >= qtyNeededForSatisfaction )
    {
        return true;
    }
    return false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
short pxVartikelLokal::getNLevelIBTTypeId() const
{
    return NLevelIBTTypeID_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
short pxVartikelLokal::getIBTQtyAvailabilityPercentage() const
{
    return IBTQtyAvailabilityPercentage_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
short pxVartikelLokal::getIBTType() const
{
    return this->VerbundArtikel() - '0';
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
char pxVartikelLokal::VerbundArtikel() const
{
    return VerbundArtikel_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxVartikelLokal::Bestand() const
{
    return Bestand_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxVartikelLokal::ArtikelNr() const
{
    return ArtikelNr_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
short pxVartikelLokal::FilialNr() const
{
    return FilialNr_;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
long pxVartikelLokal::SetQuantity( const long q)
{
    Bestand_ = q;
    SetDirty();
    return q;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxVartikelLokal::pxVartikelLokal( pxSession* session )
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
pxVartikelLokal::pxVartikelLokal( pxSession* session, tVARTIKELLOKAL& src )
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
pxVartikelLokal::pxVartikelLokal( pxSession* session, long ArtikelNrL, short FilialNr, DBAccessMode mode)
    : pxDBRecord(session)
{
    Init();
    ArtikelNr_ = ArtikelNrL;
    FilialNr_ =  FilialNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
pxVartikelLokal::pxVartikelLokal( pxVartikelLokal& src )
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
pxVartikelLokal::~pxVartikelLokal()
{
}

/*----------------------------------------------------------------------------*/
tVARTIKELLOKAL& Assign( tVARTIKELLOKAL& dest, const pxVartikelLokal& src )
{
    dest.FilialNr = src.FilialNr_;
    dest.ArtikelNr = src.ArtikelNr_;
    dest.Bestand = src.Bestand_;
    dest.Artikelaktiv = src.Artikelaktiv_;
    dest.VerbundArtikel = src.VerbundArtikel_;
    dest.IBTQtyAvailabilityPercentage = src.IBTQtyAvailabilityPercentage_;
    dest.NLevelIBTTypeID = src.NLevelIBTTypeID_;
    return dest;
}

/*----------------------------------------------------------------------------*/
pxVartikelLokal& Assign( pxVartikelLokal& dest, const tVARTIKELLOKAL& src)
{
    dest.FilialNr_ = src.FilialNr;
    dest.ArtikelNr_ = src.ArtikelNr;
    dest.Bestand_ = src.Bestand;
    dest.Artikelaktiv_ = src.Artikelaktiv;
    dest.VerbundArtikel_ = src.VerbundArtikel;
    dest.Bestand_ = ( (dest.Bestand_ < 0) ? 0 : dest.Bestand_ );
    dest.NLevelIBTTypeID_ = src.NLevelIBTTypeID;
    dest.IBTQtyAvailabilityPercentage_ = src.IBTQtyAvailabilityPercentage;
    return dest;
}

/*----------------------------------------------------------------------------*/
void pxVartikelLokal::Init()
{
    tVARTIKELLOKAL    record;
    memset(&record, 0 , sizeof(tVARTIKELLOKAL));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
pxVartikelLokal& pxVartikelLokal::operator=( const pxVartikelLokal& src )
{
    tVARTIKELLOKAL record;
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
pxVartikelLokal& pxVartikelLokal::operator=( const tVARTIKELLOKAL& src )
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int pxVartikelLokal::Get( DBAccessMode mode )
{
    tVARTIKELLOKAL record;
    memset(&record, 0, sizeof(tVARTIKELLOKAL));
    record.ArtikelNr = ArtikelNr_;
    record.FilialNr = FilialNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval) (*this)= record;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxVartikelLokal list objects being inserted in the                */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int pxVartikelLokal::CompareTo( const nCollectable *That, void * /* p */, const long /* lparm */ ) const
{
    pxVartikelLokal *that = (pxVartikelLokal*)That;
    int retval = (ArtikelNr_ == that->ArtikelNr_) ? 0 : (ArtikelNr_ > that->ArtikelNr_ ? 1 : -1);
    return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
nDate pxVartikelLokal::getIBTDeliveryDateTime( pxOrder* order )
{
    pxArtBase* artbase = pxArtBase::CreateArticle( Session(), this->ArtikelNr(), order->FilialNr() );
    TourManager tourman( Session(), order->KdAuftragNr(), order->FilialNr(), order->IDFNr(), &order->CommType(), order->KdAuftragArt() );
    tourman.injectArticle( artbase );
    tourman.injectDeliveryDate( order->DatumAuslieferung() );
    tourman.injectDesiredTourId( order->TourId() );
    tourman.injectIBTBranchNo( this->FilialNr() );
    tourman.injectNLevelIBTType( this->getNLevelIBTTypeId() );
    TourInfo ti = tourman.determineTour();
    delete artbase; artbase = NULL;
    if( ti.getTourFound() )
    {
        return ti.getCustomerDeliveryDateTimeMin();
    }
    return TourUtil::getNullDate();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
nDate pxVartikelLokal::getIBTDeliveryDateTime( pxOrder* order, bool& deliverypossible  )
{
    pxArtBase* artbase = pxArtBase::CreateArticle( Session(), this->ArtikelNr(), order->FilialNr() );

    TourManager tourman( Session(), order->KdAuftragNr(), order->FilialNr(), order->IDFNr(), &order->CommType(), order->KdAuftragArt() );

    tourman.injectArticle( artbase );	
    tourman.injectDeliveryDate( order->DatumAuslieferung() );
    tourman.injectDesiredTourId( order->TourId() );
    tourman.injectIBTBranchNo( this->FilialNr() );
    tourman.injectNLevelIBTType( this->getNLevelIBTTypeId() );
	tourman.injectIBTTypeArticle( artbase->getIBTType() );	

    TourInfo ti = tourman.determineTour();
    delete artbase; artbase = NULL;

    if( ti.getTourFound() )
    {		
		deliverypossible = true;
		return ti.getCustomerDeliveryDateTimeMin();        
    }

	deliverypossible = false;
    return TourUtil::getNullDate();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxVartikelLokal::applyArticleQuota(const short branchno)
{
	basar::Int32 remainingQuotaQty = 0;
    if( this->Session()->getIbtComponentManager()->getArticleQuotaChecker()->isArticleQuotaAvailable( branchno, this->FilialNr(), this->ArtikelNr(), remainingQuotaQty ) )
	{
		if(this->Bestand_ > remainingQuotaQty)
		{
			this->Bestand_ = remainingQuotaQty;
		}
	}
}
/*----------------------------------------------------------------------------*/
