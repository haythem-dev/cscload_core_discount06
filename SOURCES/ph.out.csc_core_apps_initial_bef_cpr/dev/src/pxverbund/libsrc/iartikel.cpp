#include "pxiartik.hpp"
#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxartpackunit.hpp"
#include "pxbartik.hpp"
#include "pxartalt.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"

pxArtBase*
pxArtBase :: CopyArticle
(
pxArtBase * ArtBase
)
{
    pxBArtikel * ba;
    ba = new pxBArtikel((pxBArtikel&)*ArtBase);
    return ba;
}

pxArtBase *
pxArtBase :: CreateArticle
(
    pxSession *session,
    long ArtikelNr,
    short FilialNr,
    DBAccessMode mode
)
{
	std::stringstream s;
	s << "pxBArtikel::CreateArticle(ArtikelNr=" << ArtikelNr << ", FilialNr=" << FilialNr << ", mode=" << mode << ")";
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), s.str());

    pxBArtikel * pxba;
    pxba = new pxBArtikel(session, ArtikelNr, FilialNr , mode);
    return pxba;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxBArtikel :: pxBArtikel
(
    pxBArtikel& src
)
    : pxErrorLoggable()
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxBArtikel :: pxBArtikel
(
    pxSession   *session,
    long    ArtikelNrL,                // Read via this type
    short   FilialNr,                  // Read in this filiale
    DBAccessMode mode
)
     : pxErrorLoggable()
{
    //Init();
    ArtikelNr_ = ArtikelNrL;
    FilialNr_ = FilialNr;
    Session_ = session;
    ArtikelMast_ = NULL;
    ArtikelMastFr_ = NULL;
    ArtikelFil_ = NULL;
    PackageUnitList_ = NULL;
    ArtSpecialCond_ = NULL;
	IBTBranchArticleConfigPtr_ = NULL;
    Sprache_.Clear();
    Sprache_ = "DE";
    Get(mode);
}


/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxBArtikel :: ~pxBArtikel()
{
    if (ArtikelMast_ != NULL)
    {
       delete ArtikelMast_;
       ArtikelMast_ = NULL;
    }
    if (ArtikelMastFr_ != NULL)
    {
       delete ArtikelMastFr_;
       ArtikelMastFr_ = NULL;
    }
    if (ArtikelFil_ != NULL)
    {
       delete ArtikelFil_;
       ArtikelFil_ = NULL;
    }
    if (PackageUnitList_ != NULL)
    {
       delete PackageUnitList_;
       PackageUnitList_ = NULL;
    }
    if (ArtSpecialCond_ != NULL)
    {
       delete ArtSpecialCond_;
       ArtSpecialCond_ = NULL;
    }
    if (IBTBranchArticleConfigPtr_ != NULL)
    {
       delete IBTBranchArticleConfigPtr_;
       IBTBranchArticleConfigPtr_ = NULL;
    }

}
/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxBArtikel :: Init()
{
    ArtikelMast_   = new pxArtMaster(Session());
    ArtikelMastFr_ = new pxArtMasterFr(Session());
    ArtikelFil_    = new pxArtFiliale(Session());
    Sprache_.Clear();
    Sprache_ = "DE";

}

/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity on hand. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxBArtikel :: SubQuantity
(
    const long q
)
{
    return ArtikelFil_->SubQuantity(q);
}

/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity on hand. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxBArtikel :: AddQuantity
(
    const long q
)
{
    return ArtikelFil_->AddQuantity(q);
}

/*----------------------------------------------------------------------------*/
/*  Set quantity q. Returns quantity added.                                   */
/*----------------------------------------------------------------------------*/
long
pxBArtikel::SetQuantity
(
    const long q
)
{
    return ArtikelFil_->SetQuantity(q);
}

/*----------------------------------------------------------------------------*/

int
pxBArtikel :: Get
(
    DBAccessMode mode
)
{
	std::stringstream s;
	s << "pxBArtikel::Get(" << mode << ") ArtikelNr=" << ArtikelNr_ << ", FilialNr=" << FilialNr_;
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), s.str());
    /* ArtikelMast_ = new pxArtMaster (Session(),ArtikelNr_, mode);*/
    if ( ArtikelMast_ != NULL )
        delete ArtikelMast_;
    ArtikelMast_ = new pxArtMaster (Session(),ArtikelNr_);
    if ( !ArtikelMast_->IsGoodState())
    {
        Error()      = ArtikelMast_->Error();
        ArtikelFil_  = new pxArtFiliale(Session());
    }
    else
    {
        long l6,l7,l8,l9,l10;
        ArtikelMast_->ArtMFlags().Export(l6,l7,l8,l9,l10);

        if ( ArtikelFil_ != NULL )
           delete ArtikelFil_;
        ArtikelFil_  = new pxArtFiliale (Session(),ArtikelNr_, FilialNr_, mode);
        if ( !ArtikelFil_->IsGoodState())
        {
            Error() = ArtikelFil_->Error();

            // Set ArtikelGefuehrt
            ETArtSchalter_.Import(l6,l7,l8,l9,l10);
            ETArtSchalter_.ClearArtikelGefuehrt();
            //ETArtSchalter_.SetNichtGeliefertHersteller();
        }
        else
        {
            long l1,l2,l3,l4,l5 ;
            ArtikelFil_->ArtFFlags().Export(l1,l2,l3,l4,l5);
            ETArtSchalter_.Import(l1|l6,l2|l7,l3|l8,l4|l9,l5|l10);

			if (Session()->isSwitzerland())
            {
               if ( ArtikelMastFr_ != NULL )
                  delete ArtikelMastFr_;
               ArtikelMastFr_ = new pxArtMasterFr (Session(),ArtikelNr_);
               if ( !ArtikelMastFr_->IsGoodState())
               {
                  delete ArtikelMastFr_;
                  ArtikelMastFr_ = NULL;
               }
            }
            if (Session()->isBulgaria())
            {
               if ( ArtSpecialCond_ != NULL )
                  delete ArtSpecialCond_;
               ArtSpecialCond_ = new pxArtSpecialCond(Session(),ArtikelNr_);
               if ( !ArtSpecialCond_->IsGoodState())
               {
                  delete ArtSpecialCond_;
                  ArtSpecialCond_ = NULL;
               }
            }
        }
    }

    return 0;
}

/*----------------------------------------------------------------------------*/

int
pxBArtikel :: Put
(
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxBArtikel::Put()");
    int retval = ArtikelFil_->Put();

	if (retval)
       Error() = ArtikelFil_->Error();
    return retval;
}

/*----------------------------------------------------------------------------*/

void
pxBArtikel :: UnLock
(
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxBArtikel::UnLock()");

    ArtikelFil_->UnLock();
}

/*----------------------------------------------------------------------------*/

bool
pxBArtikel :: IsActive
(
)
{
    return ArtikelMast_->IsActive() && ArtikelFil_->IsActive();
}

/*----------------------------------------------------------------------------*/

bool
pxBArtikel :: IsDirty
(
)
{
    return ArtikelFil_->IsDirty();
}

/*----------------------------------------------------------------------------*/

bool
pxBArtikel :: IsLocked
(
)
{
    return ArtikelFil_->IsLocked();
}

/*----------------------------------------------------------------------------*/

bool
pxBArtikel :: IsLockHeld()
{
    return ArtikelFil_->IsLockHeld();
}

/*----------------------------------------------------------------------------*/

bool
pxBArtikel :: IsOpen()
{
    return ArtikelFil_->IsOpen();
}

/*----------------------------------------------------------------------------*/
/*  PackageUnitList: select entrie from articlepackunit                       */
/*----------------------------------------------------------------------------*/
pxArtPackUnitList*
pxBArtikel :: PackageUnitList
(
)
{
    if ( PackageUnitList_ )
       return PackageUnitList_;

    PackageUnitList_ = new pxArtPackUnitList(Session());
    PackageUnitList_->Select(ArtikelNr_);
    if (!PackageUnitList_->IsGoodState() )
    {
       delete PackageUnitList_;
       PackageUnitList_ = NULL;
    }
    return PackageUnitList_;
}
/*----------------------------------------------------------------------------*/
/*  CheckCodeBlocage:.                                                        */
/*  if codeblocage changes on stockreceipt, so mark article                   */
/*  depend on entry within table countrycodes selected by the new codeblocage */
/*  It returns ErrorState                                                     */
/*----------------------------------------------------------------------------*/
int
pxBArtikel :: CheckCodeBlocage
(
    const char  cb
)
{
    int retval = 0;
    retval = ArtikelFil_->CheckCodeBlocage( cb );
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Bezeichnung:     .                                                        */
/*  Normaly we return ArtikelMast_->Bezeichnung(), but for the Swiss          */
/*  apllication we return for the french speaking customer                    */
/*  ArtikelMastFr_->Bezeichnung (if available)                                */
/*----------------------------------------------------------------------------*/
const nString&
pxBArtikel :: Bezeichnung
(
) const
{
    if ( ArtikelMastFr_ != NULL  && Sprache_ == "FR")
    {
       return ArtikelMastFr_->Bezeichnung();
    }
    return ArtikelMast_->Bezeichnung();
}
/*----------------------------------------------------------------------------*/
/*  Einheit:     .                                                            */
/*  Normaly we return ArtikelMast_->Einheit(), but for the Swiss              */
/*  apllication we return for the french speaking customer                    */
/*  ArtikelMastFr_->Einheit() (if available)                                  */
/*----------------------------------------------------------------------------*/
const nString&
pxBArtikel :: Einheit
(
) const
{
    if ( ArtikelMastFr_ != NULL  && Sprache_ == "FR")
    {
       return ArtikelMastFr_->Einheit();
    }
    return ArtikelMast_->Einheit();
}
/*----------------------------------------------------------------------------*/
/*  Darreichform:                                                             */
/*  Normaly we return ArtikelMast_->Darreichform(), but for the Swiss         */
/*  apllication we return for the french speaking customer                    */
/*  ArtikelMastFr_->Darreichform() (if available)                             */
/*----------------------------------------------------------------------------*/
const nString&
pxBArtikel :: Darreichform
(
) const
{
    if ( ArtikelMastFr_ != NULL  && Sprache_ == "FR")
    {
       return ArtikelMastFr_->Darreichform();
    }
    return ArtikelMast_->Darreichform();
}
/*----------------------------------------------------------------------------*/
/*  InvoiceRebatePct:                                                         */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns InvoiceRebatePct from the pxArtSpecialCond entry(if available) */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: InvoiceRebatePct
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->InvoiceRebatePct() : pxConstants::dZero;
}
/*----------------------------------------------------------------------------*/
/*  RebateInKindPct:                                                          */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns RebateInKindPct from the pxArtSpecialCond entry(if available)  */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: RebateInKindPct
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->RebateInKindPct() : pxConstants::dZero;
}
/*----------------------------------------------------------------------------*/
/*  AnnualInvRebPct:                                                          */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns AnnualInvRebPct from the pxArtSpecialCond entry(if available)  */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: AnnualInvRebPct
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->AnnualInvRebPct() : pxConstants::dZero;
}
/*----------------------------------------------------------------------------*/
/*  AnnualRebIKPct:                                                           */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns AnnualRebIKPct from the pxArtSpecialCond entry(if available)   */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: AnnualRebIKPct
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->AnnualRebIKPct() : pxConstants::dZero;
}
/*----------------------------------------------------------------------------*/
/*  CustRebRedPct:                                                            */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns CustRebRedPct from the pxArtSpecialCond entry(if available)    */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: CustRebRedPct
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->CustRebRedPct() : pxConstants::dZero;
}
/*----------------------------------------------------------------------------*/
/*  HiReimBursement:                                                          */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns HiReimBursement from the pxArtSpecialCond entry(if available)  */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: HiReimBursement
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->HiReimBursement() : pxConstants::dZero;
}

/*----------------------------------------------------------------------------*/
/*  SupplHiReimb:                                                             */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns SupplHiReimb from the pxArtSpecialCond entry(if available)     */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: SupplHiReimb
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->SupplHiReimb() : pxConstants::dZero;
}

/*----------------------------------------------------------------------------*/
/*  SupplFsReimb:                                                             */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns SupplFsReimbfrom the pxArtSpecialCond entry(if available)     */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: SupplFsReimb
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->SupplFsReimb() : pxConstants::dZero;
}
/*----------------------------------------------------------------------------*/
/*  SupplDiscountPct:                                                         */
/*  This is a methode base an Object pxArtSpecialCond which pointer is located*/
/*  wihin the Artbase object.                                                 */
/*  It returns SupplDiscountPct from the pxArtSpecialCond entry(if available) */
/*  otherwise 0.0                                                             */
/*----------------------------------------------------------------------------*/
double
pxBArtikel :: SupplDiscountPct
(
) const
{
    return  (ArtSpecialCond_ != NULL ) ? ArtSpecialCond_->SupplDiscountPct() : pxConstants::dZero;
}
/*----------------------------------------------------------------------------*/
/*  IBTBranchArticleConfig                                                       */
/*----------------------------------------------------------------------------*/
IBTBranchArticleConfig* pxBArtikel::getIBTBranchArticleConfigPtr()
{
	if ( NULL == IBTBranchArticleConfigPtr_ )
	{
		IBTBranchArticleConfigPtr_ = new IBTBranchArticleConfig(this->Session(), this->FilialNr(), this->ArtikelNr());
		if ( !IBTBranchArticleConfigPtr_->Get() )
		{
			delete IBTBranchArticleConfigPtr_;
			IBTBranchArticleConfigPtr_ = NULL;
		}
	}	
	return  IBTBranchArticleConfigPtr_;
}

