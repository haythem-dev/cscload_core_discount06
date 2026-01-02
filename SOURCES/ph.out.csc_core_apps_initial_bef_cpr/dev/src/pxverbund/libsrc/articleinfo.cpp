/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxArticleInfo:

REVISION HISTORY

30 June 2007 V1.00 REV 00 written by Ysbrand Bouma
*/
#include "pxarticleinfo.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxartprc.hpp"
#include "pxartsto.hpp"
#include "pxtaxrates.hpp"

/*----------------------------------------------------------------------------*/
/*  Constructor for pxArticleInfo object                                      */
/*----------------------------------------------------------------------------*/
pxArticleInfo :: pxArticleInfo
(
    pxSession*  session,
    short      BranchNo,
    long       ArticleNo,
    long       Qty
)
{

    Init();
    Session_   = session;
    BranchNo_  = BranchNo;
    ArticleNo_ = ArticleNo;
    Qty_       = Qty;
}
/*----------------------------------------------------------------------------*/
/*  Destructor  for pxArticleInfo                                             */
/*----------------------------------------------------------------------------*/
pxArticleInfo :: ~pxArticleInfo
()
{
    if (ArtBase_)
       delete ArtBase_;
    if (ArtPrice_)
       delete ArtPrice_;
}

/*----------------------------------------------------------------------------*/
/*  Init                                                                      */
/*----------------------------------------------------------------------------*/
void
pxArticleInfo :: Init()
{
    ArtBase_     = NULL;
    ArtPrice_    = NULL;
}
/*----------------------------------------------------------------------------*/
/*  Is Good State ?                                                           */
/*----------------------------------------------------------------------------*/
bool
pxArticleInfo :: IsGoodState()
{
    return ArtBase_ != NULL && ArtBase_->IsGoodState() &&
           ArtPrice_ != NULL && ArtPrice_->IsGoodState();
}

/*----------------------------------------------------------------------------*/
/*  Build                                                                     */
/*----------------------------------------------------------------------------*/
int
pxArticleInfo :: Build
(
    nString& Sprache
)
{
    int  retval = 0;
    if ( !ArtBase_ )
    {
       ArtBase_ = pxArtBase::CreateArticle(Session_,ArticleNo_,BranchNo_, cDBGET_READONLY );
    }
    if ( ArtBase_ )
    {
       ArtBase_->SetSprache(Sprache);
       SalesTaxRate(ArtBase_->TaxLevel());
       CodeBlocage_  = ArtBase_->CodeBlocage();
    }
    if ( !ArtPrice_ )
    {
       pxArtPriceList* pricelist = new pxArtPriceList(Session_);
       pricelist->Select(ArticleNo_);
       pricelist->DeleteExpired();       // remove expired prices, so only
       if ( pricelist->Entries() > 0 )
       {
          ArtPrice_ = new pxArtPrice( *((pxArtPrice*)pricelist->RemoveAt(0))); // 1 entry should remain
       }
       pricelist->Clear();
       delete pricelist;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* ArticleExpireDate : returns the expiredate of the current article object   */
/* Returnvalues: YYYYMMDD if DatumVerfall exits within table                  */
/*               ArtikelLagerOrt                                              */
/*               otherwise  zero                                              */
/* Take care for a well constructed pxArticleInfo object                      */
/*----------------------------------------------------------------------------*/
long
pxArticleInfo :: ArticleExpireDate
(
)
{
    long expiredate = 0;
    pxArtStoreLoc*      storeloc = NULL;
    if ( ArtBase_ )
    {
       storeloc = new pxArtStoreLoc(Session_, ArticleNo_, ArtBase_->FilialNr(),
                                    ArtBase_->LagerBereichNr(),
                                    ArtBase_->LagerFachNr());
       if ( storeloc->IsGoodState())
       {
          long a = storeloc->DatumVerfall();    // comes as YYMM
          if (a == 0 )                           // no date
          {
             delete storeloc;
             return  expiredate;
          }
          long b = a/100;                       // = YY
          expiredate = 2000;
          expiredate = (( expiredate+b)*10000) + ((a%100)*100)+1;
          delete storeloc;
       }
    }
    return  expiredate;
}

/*----------------------------------------------------------------------------*/
/*  Set SaleTaxRate                                                           */
/*----------------------------------------------------------------------------*/
void
pxArticleInfo :: SalesTaxRate
(
    const short TaxLevel
)
{
    pxTaxRates* taxrate = Session_->TaxRatesList()->Find(TaxLevel);
    if (taxrate)
    {
       SalesTaxRate_ = taxrate->SalesTaxRate();
    }
}

nMoney
pxArticleInfo :: PreisEKApo
(
)
{
	return ArtPrice_->PreisEKApo();
}

nMoney
pxArticleInfo :: PreisVKApo
(
)
{
	return ArtPrice_->PreisVKApo();
}

nMoney
pxArticleInfo :: PreisEKGrosso
(
)
{
	return ArtPrice_->PreisEKGrosso();
}

nMoney
pxArticleInfo :: PreisEKGrossoNA()
{
	return ArtPrice_->PreisEKGrossoNA();
}
