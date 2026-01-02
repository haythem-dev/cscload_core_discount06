#include "pxitem.hpp"
#include "articlesubstitutionutil.hpp"

/*----------------------------------------------------------------------------*/
/*  IBTSubstitution: this methode is called in itmentry.cpp after             */
/*  PostOrderQuantity. If param.AutoIBTSubst() == 1, it checks                */
/*  MengeBestaetigt_,MengeVerbund() for the current Artikel                   */
/*  If MengeBestaetig_ == 0 and MengeVerbund() == 0, it tries to find an      */
/*  Alternate(substution) article. If found, we do PostOrderQuantity for      */
/*  substution article.                                                       */
/*  Please take for a well constructed pxOrderItem object.                    */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: IBTSubstitution
(
    const long  Menge,                 // desired product quantity
    const long  MengeNatra,            // quantity in kind
    const long  MengeNachfrage,        // quantity in kind
    BookingType  btype,                 // item/quantity booking type
    int          flags,                 // internal posting flags
    short      /*AuxFil*/             // auxdelivery company
)
{
    long subArticleNo = 0;
	pxOrderItem::BookingType bookingType;
	getArticleSubstitutionUtil()->resetVars();
	getArticleSubstitutionUtil()->injectBookingFlags(flags);
	getArticleSubstitutionUtil()->injectBookingType((int)btype);
	getArticleSubstitutionUtil()->injectActionCode(ArticleSubstitutionUtil::SUBSTITUTE_FORIBT);
	if ( getArticleSubstitutionUtil()->isSubstitutionNecessary( this->ArtBase_) )
	{
		subArticleNo = getArticleSubstitutionUtil()->getSubstituteArticleNo();
		if ( subArticleNo > 0 )
		{
			this->changeArtBaseToSubstitutionArticle( subArticleNo, Menge);
			if (!IsGoodState() )
			{
				return ErrorState();
			}
			// test/
			if ( getIBTQuantityInStock( Menge, -1, flags ) )
			{
				MengeBestellt_ = 0;                  // set in PostOrderQuantity
				bookingType =  AuxDelivery;                // post from the first auxcompany
				PostOrderQuantity(Menge, MengeNatra, MengeNachfrage, bookingType, flags, cDEFAULT);
				if ( IsGoodState() )
				{
					if ( MengeBestaetigt() > 0 )
					{
						SetFehlerMenge((short)pxOrderItem::QStateAlternate);
					}
				}
			}
		}
	}
	return ErrorState();
}
