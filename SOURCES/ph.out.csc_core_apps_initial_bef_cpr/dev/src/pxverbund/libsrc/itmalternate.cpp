#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxarticlecodes.hpp"

/*----------------------------------------------------------------------------*/
/* changeArtBaseToSubstitutionArticle:                                        */
/*----------------------------------------------------------------------------*/
int  pxOrderItem :: changeArtBaseToSubstitutionArticle(const long SubstitutionArticleNo, const long QOrdered)
{
	if ( ArtBase_ )
	{
		ArtBase_->Put();        // unlock current article
		delete ArtBase_;        // delete artbase object
		ArtBase_  = NULL;       // set pointer to 0
		ArtikelNr_ = SubstitutionArticleNo;  //new product number
		// read and lock alternate product base object
		if (! ArtBase(cDBGET_FORUPDATE) || !ArtBase_->IsGoodState() )
		{
			FehlerArtikel_ = ArtStateNotFound;
			MengeBestellt_ = QOrdered;
			PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
			HandleError();                   // product or return the error
			return ErrorState();
		}
	}
	return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* setOrderItemAlternateRemarks      :                                        */
/*----------------------------------------------------------------------------*/
int pxOrderItem :: setOrderItemAlternateRemarks( const long ArticleNoOrdered, const short MessageNo) 
{
	 long articleno = 0;
     pxArticleCodes* ArtCode = NULL;
     ArtCode = GetArticleCode( ArticleNoOrdered);
     if (ArtCode)
     {
		articleno = atoi(ArtCode->ArticleCode());
     }
     else
     {
        articleno = ArtikelNr_;
     }
     // get canned message.
     nMessage text(CMsgStream(), MessageNo, articleno, 0);
	 nString bem = text.String();
     bem.Compress('\n');
     Bemerkungen(bem);
	 return ErrorState();
}
