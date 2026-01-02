#include "articlesubstitutionutil.hpp"
#include "pxsess.hpp"
#include "pxorder.hpp"
#include "pxitem.hpp"
#include "pxdevice.hpp"
#include "pxcstbas.hpp"
#include "pxcstot.hpp"
#include "pxcustomerflags.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxcomtyp.hpp"
#include "pxoeparm.hpp"
#include "pxartbas.hpp"
#include "pxartflg.hpp"
#include "pxartalt.hpp"
#include "pxartrip.hpp"
#include "pxstockbooking.hpp"
#include <logger/loggerpool.h>
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

/*############################################################################################################################*/
/*                                       P U B L I C                                                                          */
/*############################################################################################################################*/

/***************************************************************************************************************************/
ArticleSubstitutionUtil::ArticleSubstitutionUtil( pxOrderItem* item )
    : m_Item( item )
{
    m_Order = &(item->Order());
    m_Session = item->Session();

    resetVars();
}

/***************************************************************************************************************************/
ArticleSubstitutionUtil::~ArticleSubstitutionUtil()
{
    m_Order = NULL;             // don´t delete order object!
    m_Item = NULL;              // don't delete item object
    m_Session = NULL;           // don't delete session object
}

/***************************************************************************************************************************/
void ArticleSubstitutionUtil::resetVars()
{
    m_SubstituteArticleNo = 0L;
    m_bSubstitutionArticleNoPassive = false;
    m_CodeBlocage         = ' ';
    m_BookingFlags        = 0;
    m_BookingType         = 0;
    m_ActionCode          = 0;
    m_RequiredQuantity    = 0L;
}

/***************************************************************************************************************************/
void ArticleSubstitutionUtil::injectBookingFlags( int flags )
{
    this->m_BookingFlags = flags;
}

/***************************************************************************************************************************/
void ArticleSubstitutionUtil::injectBookingType( int btype)
{
    this->m_BookingType = btype;
}

void ArticleSubstitutionUtil::injectRequiredQuantity(long quantity)
{
    m_RequiredQuantity = quantity;
}

/***************************************************************************************************************************/
void ArticleSubstitutionUtil::injectActionCode( short actioncode )
{
    this->m_ActionCode = actioncode;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::isSubstituteNewProduct()
{
    return m_ActionCode ==  SUBSTITUTE_NEWPRODUCT;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::isSubstituteReverse()
{
    return m_ActionCode ==  SUBSTITUTE_REVERSE;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::isSubstituteForward()
{
    return m_ActionCode ==  SUBSTITUTE_FORWARD;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::isSubstituteForIBT()
{
    return m_ActionCode ==  SUBSTITUTE_FORIBT;
}

bool ArticleSubstitutionUtil::isSubstituteReImport()
{
    return m_ActionCode == SUBSTITUTE_REIMPORT;
}


/***************************************************************************************************************************/
long ArticleSubstitutionUtil::getSubstituteArticleNo() const
{
    return m_SubstituteArticleNo;
}

bool ArticleSubstitutionUtil::isSubstitutionArticleNoPassive() const
{
    return m_bSubstitutionArticleNoPassive;
}

/***************************************************************************************************************************/
char ArticleSubstitutionUtil::getCodeBlocage() const
{
    return m_CodeBlocage;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::isSubstitutionNecessary(pxArtBase* article)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::isSubstitutionNecessary()");

    if (article == NULL)
    {
        return false;
    }

    if (m_BookingType == pxOrderItem::AuxDelivery)
    {
        return false;
    }

    if (this->m_Order->OrderType().IsChronicIllnessOrder()) {
        return false;
    }


    if (this->isSubstituteNewProduct() && isNewProductSubstitutionNecessary(article))
    {
        return NewProductSubtitution(article->ArtikelNr());
    }

    if (this->isSubstituteReverse() && isReverseSubstitutionNecessary(article))
    {
        return ReverseSubstitution(article->ArtikelNr());
    }

    if (this->isSubstituteForward() && isForwardSubstitutionNecessary(article))
    {
        return ForwardSubstitution(article->ArtikelNr());
    }

    if (this->isSubstituteForIBT() && isIBTSubstitutionNecessary(article))
    {
        return IBTSubstitution(article->ArtikelNr());
    }

    if (isSubstituteReImport() && isReImportSubstitutionNecessary(article))
    {
        return ReImportSubstitution(article->ArtikelNr());
    }

    return false;
}

/*############################################################################################################################*/
/*                                       P R I V A T E                                                                        */
/*############################################################################################################################*/
bool ArticleSubstitutionUtil::isReverseSubstitutionNecessary(  pxArtBase* article)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::isReverseSubstitutionNecessary()");

    bool retval = true;
    if ( !m_Session->isFrance() )
    {
        return retval = false;
    }

    if ( m_Order->Customer()->KdGruppe() == "09" )
    {
        return retval = false;
    }

    if ( !article->IsMedicalProduct() )
    {
        return retval = false;
    }

    if ( m_Order->Param()->ReverseSubstitutionDays() == 0 )
    {
        return retval = false;
    }

    return retval;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::isNewProductSubstitutionNecessary(  pxArtBase* article)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::isNewProductSubstitutionNecessary()");

    bool retval = false;
    if ( m_Session->Device()->IsVideo() )
    {
        return retval = false;
    }
    if (!m_Session->isFrance() )
    {
        return retval;
    }

    if ( article->IsNewProduct() )
    {
        retval = true;
    }
    return retval;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::isForwardSubstitutionNecessary(  pxArtBase* article)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::isForwardSubstitutionNecessary()");
    bool retval = false;
    if ( m_Session->Device()->IsVideo() )
    {
        return retval = false;
    }

    //if (!(m_Order->Customer()->Flags().IsNoSubstitution()) && article->ArtFlags().IsNachfolgeArtikel() && m_Item->PointerArtQuota() == NULL && !(m_BookingFlags & bPOST_IBTPOSREBOOK))
    if ( !(m_Order->Customer()->Flags().IsNoSubstitution())
         && article->ArtFlags().IsNachfolgeArtikel()
         && false == m_Item->hasArticleQuota()
         && !(m_BookingFlags & bPOST_IBTPOSREBOOK) )
    {
        retval = true;
    }
    return retval;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::isIBTSubstitutionNecessary(  pxArtBase* article)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::isIBTSubstitutionNecessary()");
    bool retval = false;
    if ( !m_Order->Param()->IsAutoIBTSubst())       // just if wanted
    {
       return retval;
    }

    if ( m_Item->IsAuxPosted() )                   // if already IBT
    {
       return retval;
    }

    if ( m_Item->MengeBestaetigt() > 0 )           // position booked
    {
       return retval;
    }

    //if ( !( m_Order->Customer()->Flags().IsNoSubstitution()) && article->ArtFlags().IsNachfolgeArtikel() && m_Item->PointerArtQuota() == NULL && !(m_BookingFlags & bPOST_IBTPOSREBOOK) )
    if (!(m_Order->Customer()->Flags().IsNoSubstitution())
        && article->ArtFlags().IsNachfolgeArtikel()
        && false == m_Item->hasArticleQuota()
        && !(m_BookingFlags & bPOST_IBTPOSREBOOK))
    {
        retval = true;
    }
    return retval;
}

bool ArticleSubstitutionUtil::isReImportSubstitutionNecessary(pxArtBase* article)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::isReImportSubstitutionNecessary()");
    bool retval = false;
    if (m_Session->Device()->IsVideo() || m_Order->Customer()->Flags().IsNoSubstitution())
    {
        return false;
    }

    if (   article->ArtFlags().IsArtikelVerKnuepft()
        && !m_Item->hasArticleQuota()
        && !(m_BookingFlags & bPOST_NO_DEBIT)
        && !(m_BookingFlags & bPOST_IBTPOSREBOOK))
    {
        retval = true;
    }
    return retval;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::NewProductSubtitution( long articleno)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::NewProductSubtitution()");

    return ForwardSubstitution(articleno);
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::ForwardSubstitution( long articleno)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::ForwardSubstitution()");
    bool retval = false;

    // Get alternate list with own article number.
    pxArtAlternList alterlist(this->m_Session);
    alterlist.SelectForward(articleno, m_Order->Customer()->Vertriebszentrum());
    pxArtAlternListIter alterniter(alterlist);
    pxArtAltern* alter;

    // Search until found or empty list.
    while ((alter = (pxArtAltern*) ++alterniter) != NULL)
    {
        if ( getArticleBookInformation(  alter->ArtikelAlternNr(),  m_Order->Customer()->Vertriebszentrum()) )
        {
            m_SubstituteArticleNo = alter->ArtikelAlternNr();
            m_Item->SetFehlerMenge((short)pxOrderItem::QStateAlternate);
            retval = true;
            break;
        }
    }
    return retval;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::ReverseSubstitution( long articleno)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::ReverseSubstitution()");
    bool retval = false;
    if ( !m_Session->isFrance() )
        return retval;

    // Get alternate list with own article number.
    pxArtAlternList alterlist(m_Item->Session());
    alterlist.SelectReverse(articleno, m_Order->Customer()->Vertriebszentrum());
    pxArtAlternListIter alterniter(alterlist);
    pxArtAltern* alter;

    // Search until found or empty list.
    while ((alter = (pxArtAltern*) ++alterniter) != NULL)
    {
        if ( getArticleBookInformation(  alter->ArtikelNr(),  m_Order->Customer()->Vertriebszentrum()) )
        {
            m_SubstituteArticleNo = alter->ArtikelNr();
            m_Item->SetFehlerMenge((short)pxOrderItem::QStateAlternate);
            retval = true;
            break;
        }
    }
    return retval;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::IBTSubstitution( long articleno)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::IBTSubstitution()");
    bool retval = false;

    // Get alternate list with own article number.
    pxArtAlternList alterlist(this->m_Session);
    alterlist.Select(articleno, m_Order->Customer()->Vertriebszentrum());
    pxArtAlternListIter alterniter(alterlist);
    pxArtAltern* alter;

    // Search until found or empty list.
    while ((alter = (pxArtAltern*) ++alterniter) != NULL)
    {
        if ( checkSubstitutionArticle(  alter->ArtikelAlternNr(),  m_Order->Customer()->Vertriebszentrum()) )
        {
            m_SubstituteArticleNo = alter->ArtikelAlternNr();
            retval = true;
            break;
        }
    }
    return retval;
}

bool ArticleSubstitutionUtil::ReImportSubstitution(long articleno)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::ReImportSubstitution()");

    pxArtReImportList riplist(m_Session);
    riplist.Select(articleno);

    if (riplist.Entries() == 0)
    {
        return false;
    }

    boost::shared_ptr<pxArtReImportList> riplistpassiv = boost::shared_ptr<pxArtReImportList>(riplist.Build(pxArtReImportList::cREIMPDefault));
    riplist.Shrink(pxArtReImportList::cREIMPAktiv);

    if (findReImportArticle(riplist))
    {
        return true;
    }

    if ((m_Item->ArtikelNrPassiv() == 0) && findReImportArticle(*riplistpassiv))
    {
        m_bSubstitutionArticleNoPassive = true;
        return true;
    }

    return false;
}

bool ArticleSubstitutionUtil::findReImportArticle(pxArtReImportList& riplist)
{
    pxArtReImportListIter ripit(riplist);
    pxArtReImport* entry;
    boost::shared_ptr<pxArtBase> ReImportArtBase;

    while ((entry = (pxArtReImport*)++ripit) != NULL)
    {
        ReImportArtBase = boost::shared_ptr<pxArtBase>(pxArtBase::CreateArticle(m_Session, entry->ArtikelAlternNr(), m_Order->FilialNr(), cDBGET_READONLY));
        if (   (ReImportArtBase != NULL)
            && (m_Session->getStockBooking()->GetAvailableQtyInStock(*ReImportArtBase) >= m_RequiredQuantity) )
        {
            m_SubstituteArticleNo = ReImportArtBase->ArtikelNr();
            return true;
        }
    }
    return false;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::getArticleBookInformation( const long articleno, const  short branchno )
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::getArticleBookInformation()");
    bool retval = true;
    nDate today;
    pxArtBase* articleAltern = NULL;
    articleAltern = pxArtBase::CreateArticle(m_Session, articleno, branchno);   // read only

    if ( !(articleAltern->IsGoodState()) )
    {
        this->Error() = articleAltern->Error();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerArticleSubstitution(), ErrorMsg());

        delete articleAltern;
        return retval = false;
    }

    if ( this->isSubstituteReverse() )
    {
        if ( (articleAltern->DateOutOfTrade() + m_Order->Param()->ReverseSubstitutionDays() ) <  today )
        {
            delete articleAltern;
            return retval = false;
        }
    }

    if ( m_Item->GetQtyInStock(articleAltern) == 0 )
    {
        ExternalCondition( m_Session->CMsgStream(), CMSG_ART_SUBSTARTICLE_NOSTOCK, articleno );
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerArticleSubstitution(), ErrorMsg());

        delete articleAltern;
        return retval = false;
    }
    retval = checkSubstitutionArticle( articleno, branchno );
    if ( articleAltern )
    {
        delete articleAltern;
    }
    return retval;
}

/***************************************************************************************************************************/
bool ArticleSubstitutionUtil::checkSubstitutionArticle(const long articleno, const  short branchno )
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerArticleSubstitution(), "ArticleSubstitutionUtil::checkSubstitutionArticle()");
    bool retval = true;
    pxArtBase* articleAltern = NULL;
    articleAltern = pxArtBase::CreateArticle(m_Session, articleno, branchno);   // read only

    if ( !(articleAltern->IsGoodState()) )
    {
        this->Error() = articleAltern->Error();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerArticleSubstitution(), ErrorMsg());

        delete articleAltern;
        return retval = false;
    }
    if ( articleAltern->ArtFlags().IsNotCertificated() )
    {
        ExternalCondition( m_Session->CMsgStream(), CMSG_ART_WITHOUT_CERTIFICATE, articleAltern->ArtikelNr() );
        BLOG_ERROR(libcsc::LoggerPool::getLoggerArticleSubstitution(), ErrorMsg());

        delete articleAltern;
        return retval = false;
    }
    // Authorization check (skipped if server's auto item posting is active):
    if ( !(m_BookingFlags & bPOST_AUTO_ITEM) &&
                !(m_Order->BatchSchreiben() == cORTYPE_AUXILIARY) &&
                !(articleAltern->ArtClass().IsAuthorized(m_Order->Customer()->ArtClass())) )
    {
        ExternalCondition(m_Session->CMsgStream(), CMSG_ITM_NOT_AUTHORIZED );
        BLOG_ERROR(libcsc::LoggerPool::getLoggerArticleSubstitution(), ErrorMsg());

        delete articleAltern;
        return retval = false;
    }

    if ( articleAltern->IsNotSaleable()                                          ||
         articleAltern->IsStopSelling()                                          ||
         (articleAltern->IsProduserQuota() &&
          (articleAltern->IsNotViaDCT() || articleAltern->IsNotViaXML())) )
    {
        delete articleAltern;
        return retval = false;
    }

    if ( !(m_BookingFlags & bPOST_AUTO_ITEM) && articleAltern->KonsigPartnerNr() > 0 &&
                 m_Order->Customer()->CustomerGroupFlagsList()->IsNoConsignmentPermission() )
    {
        ExternalCondition(m_Session->CMsgStream(), CMSG_ITM_NOT_AUTHORIZED );
        BLOG_ERROR(libcsc::LoggerPool::getLoggerArticleSubstitution(), ErrorMsg());

        delete articleAltern;
        return retval = false;
    }

    if ( !(m_BookingFlags & bPOST_AUTO_ITEM) &&
             !(m_Order->BatchSchreiben() == cORTYPE_AUXILIARY) &&
             (articleAltern->IsMedProdABGVerord()) && !( m_Order->Customer()->Flags().IsMedProdABGVerord()))
    {
        ExternalCondition(m_Session->CMsgStream(), CMSG_ITM_NOT_AUTHORIZED );
        BLOG_ERROR(libcsc::LoggerPool::getLoggerArticleSubstitution(), ErrorMsg());

        delete articleAltern;
        return retval = false;
    }

    // Check Psychotropical stuff:
    if ( !(m_BookingFlags & bPOST_AUTO_ITEM) &&
          !(m_Order->BatchSchreiben() == cORTYPE_AUXILIARY) &&
           (articleAltern->IsKzPsychoStoffe()) && !(m_Order->Customer()->IsPsychoAllowed()))
    {
        ExternalCondition(m_Session->CMsgStream(), CMSG_ITM_NOT_AUTHORIZED );
        BLOG_ERROR(libcsc::LoggerPool::getLoggerArticleSubstitution(), ErrorMsg());

        delete articleAltern;
        return retval = false;
    }
    if ( articleAltern )
    {
        delete articleAltern;
    }
    return retval;
}
