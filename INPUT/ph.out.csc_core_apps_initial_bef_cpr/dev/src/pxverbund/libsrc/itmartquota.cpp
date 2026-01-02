#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxbranch.hpp"
#include "pxorder.hpp"
#include "pxarticlequota.hpp"
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/*  CheckArtQuota: this methode checks the customers articlequota entry for   */
/*  the current Article. Take care for a well constructed pxOrderItem object. */
/*  Return values:  Q if there is no entry or the quota is not exeeded.       */
/*                  Rest if Q > rest                                          */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: CheckArtQuota
(
    const long Q
)
{
    long  retval = Q;
    long  rest = 0;
    ClearQuotaExeeded();
    if ( ArtQuota() )
    {
        rest = m_ArticleQuota.get()->Quota() - m_ArticleQuota.get()->KumQty();
        rest = ((rest < 0) ? 0 : rest);
        retval = ((rest >= retval) ? retval : rest );
        if (retval == 0)
        {
          SetQuotaExeeded();           // mark for auxdeilvery etc ...
        }
    }

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  UndoArtQuota: decrements accumulated ordered quantity by MengeAbgebucht_  */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoArtQuota
(
    const long  Menge
)
{
    int retval = 0;
    if (!m_ArticleQuota.get() )
    {
       ArtQuota(cDBGET_FORUPDATE);
    }
    else
    {
        m_ArticleQuota.get()->Get(cDBGET_FORUPDATE);
    }
    if (m_ArticleQuota.get())
    {
       if ( Menge > 0 )
       {
          retval = m_ArticleQuota.get()->SubQuantity(Menge);
//          m_ArticleQuota.get()->Put();
       }
       else
       {
          retval = m_ArticleQuota.get()->SubQuantity(MengeAbgebucht_+ MengeVerbund());
       }
       m_ArticleQuota.get()->Put();
    }

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  UpdateArtquota:  adds MengeAbgebucht+MengeVerbund of this item entry      */
/*  to the accumulated member KumQty of the customer ArticleQuota entry.      */
/*  After that, the articleauota entry returns to the database                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UpdateArtQuota
(
)
{
    int rest = 0;
    if ( ArtQuota() )
    {
        rest = m_ArticleQuota.get()->Quota() - m_ArticleQuota.get()->KumQty();
        rest = ((rest < 0) ? 0 : rest);
        m_ArticleQuota.get()->AddQuantity( MengeAbgebucht_ + MengeVerbund());
        m_ArticleQuota.get()->Put();
        Error() = m_ArticleQuota.get()->Error();
        if ( IsQuotaExeeded())
        {
           if ( (MengeAbgebucht_ + MengeVerbund() >  0) && (rest < MengeBestellt_))
           {
              SetMengenKontigentDefekt();
           }
           else
           if ( rest == 0 )
           {
              SetMengenKontigentDefekt();
           }
        }
        if ( IsGoodState() )
        {
            m_ArticleQuota.reset();
        }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  CancelArtquota:  subtracts MengeAbgebucht+MengeVerbund of this item entry */
/*  from the accumulated member KumQty of the customer ArticleQuota entry.    */
/*  After that, the articleauota entry returns to the database                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CancelArtQuota
(
)
{
    if ( ArtQuota() )
    {
        m_ArticleQuota.get()->Get();             // read again prevents differences
        m_ArticleQuota.get()->SubQuantity( MengeAbgebucht_ + MengeVerbund());
        m_ArticleQuota.get()->Put();
        Error() = m_ArticleQuota.get()->Error();
       // ClearMengenKontigentDefekt();
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  CheckRemoteArticleQuota:                                                  */
/*  this methode is used for article inquiry and checks the quoata for this   */
/*  article and the inter branch customer account(BGANR_EK) depend on QToPost */
/*  Returns 0 if quota exceeded, or quantity free for this order's customer.  */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: CheckRemoteArticleQuota
(
    const short BranchNo,
    const long  QToPost
)
{
    long retval = QToPost;              //  return value
    long rest   = 0;
    long BGANr  = Order_->Session()->Branch()->BGANr_EK();

    pxArticleQuota RemArtQuota(Session(), BranchNo, BGANr, ArtikelNr_);
    if (RemArtQuota.FindQuotaEntry(cDBGET_READONLY))  //  get and lock it from the database
    {
       return retval;               // nothing to do
    }

    // now do inventory update on RemArtQuota_
    rest = RemArtQuota.Quota() - RemArtQuota.KumQty();
    rest = ((rest < 0) ? 0 : rest);
    retval = ((rest >= retval) ? retval : rest );
    return retval;
}
