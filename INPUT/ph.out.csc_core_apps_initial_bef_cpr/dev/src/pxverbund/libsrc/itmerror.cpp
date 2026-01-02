#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxorder.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxoeparm.hpp"
#include "tourassignmentutil.hpp"
#include "types/messagecodeenum.inc"
#include <sstream>

/*----------------------------------------------------------------------------*/
/*  This function returns an errornumber and an errormessage in the callers   */
/*  messsage area.                                                            */
/*  Take care: this function just works on a well constructed pxOrderItem     */
/*  object.                                                                   */
/*----------------------------------------------------------------------------*/
int pxOrderItem::GetError(char*  message)
{
    int num = 0;                         /* contains section number */	

    pxCustBase&       customer   = *(Order().Customer());	
/*----------------------------------------------------------------------------*/
/*  First check the article state                                             */
/*----------------------------------------------------------------------------*/
    switch ( ArtState() )
    {
		case ArtStateNotInTender:
		{
			num = CMSG_ITM_ARTICLE_NOT_IN_TENDER;
			break;
		}

       case ArtStateNotFound :
       {			
			if( !ArtBase()->IsGoodState() )
			{
				num = CMSG_SDC_NR_UNBEKANNT;
			}
			else if( ArtBase()->IsNotSaleable() )	
			{
				num = CMSG_SDC_AUSSER_HANDEL;
			}
			else
			{
				num = CMSG_SDC_NICHT_GEFUEHRT;
			}			
			break;
       }

       case ArtStateInvalidDigit:
       {
          num = CMSG_SDC_NICHT_NUMERISCH;
          break;
       }

       case ArtStateInvalidCheckDigit:
       {
          num = CMSG_SDC_PRUEFZIFFER_FALSCH;
          break;
       }

       case ArtStateNotAuthorized:
       {
          num = CMSG_SDC_NICHT_BERECHTIGT;
          if (Session()->isBulgaria())
          {
			if (!ArtBase()->IsGoodState() )
                break;
             if ( ArtBase_->ArtClass().IsOpiat() )
             {
                if ( !customer.ArtClass().IsOpiat() )
                   num = CMSG_SDC_CUSTOMER_NONARCOTICS;
             }
          }
          break;
       }
       case ArtStateNotCertificated:
       {
          num = CMSG_SDC_ARTIKEL_NO_CERTIFICAT;
          break;
       }
       case ArtStateTransportExclusion:
       {
		   num = CMSG_ART_TRANSPORT_EXCLUSION;
           break;
       }
	   case ArtStateNoBatchProvided:
       {
		   num = CMSG_SDC_NO_BATCH_PROVIDED;
           break;
       }
	   case ArtStateBatchGivenButNotProvided:
       {
		   num = CMSG_SDC_BATCH_GIVEN_BUT_NOT_PERMITTED;
           break;
       }
	   case ArtStateDesiredBatchGivenOnlyFixedAllowed:
       {
		   num = CMSG_SDC_DESIRED_BATCH_GIVEN_ONLY_FIXED_ALLOWED;
           break;
       }
	   case ArtStateFixedBatchGivenButNotAllowed:
       {
		   num = CMSG_SDC_FIXED_BATCH_GIVEN_BUT_NOT_ALLOWED;
           break;
       }
	   case ArtStateBatchProcessingNotPossible:
       {
		   num = CMSG_SDC_BATCH_PROCESSING_NOT_POSSIBLE;
           break;
       }
       case ArtStatePriceLimitCompViolationNHIFPriceMWPRefPrice:
       {
           num = CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE;
           break;
       }
       case ArtStatePriceLimitCompViolationMWPAndRefPrice:
       {
           num = CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE;
           break;
       }
       case ArtStatePriceLimitDeletion:
       {
           num = CMSG_ITM_PRICE_LIMIT_PRODUCT_PRICE_DELETION;
           break;
       }
       case ArtStatePriceLimitMWPExceedance:
       {
           num = CMSG_ITM_PRICE_LIMIT_MWP_EXCEEDANCE;
           break;
       }

       default:
       {
          num = CMSG_SDC_DEFAULT;
          break;
       }
    }

    if  ( num != CMSG_SDC_DEFAULT )
    {
       nMessage answer (CMsgStream(), num, 0);
       sprintf(message,answer.String());
       return num;
    }

/*----------------------------------------------------------------------------*/
/*  Then check the quantity state                                             */
/*----------------------------------------------------------------------------*/
    num = 0;
    if (IsQStateNotOnHand())
    {
        num = CMSG_SDC_FEHLT_ZUR_ZEIT;
        if ( ArtBase() && ArtBase()->IsGoodState() )
        {
            if (ArtBase()->ArtFlags().IsAusserHandel())
            {
                num = CMSG_SDC_AUSSER_HANDEL;
            }
			else if (ArtBase()->IsKontingentPPE())
			{
				num = CMSG_SDC_QUOTA_ARTICLE_SUPPLIER;
			}
			else if (ArtBase()->ArtFlags().IsNichtLieferbarHersteller())
            {
                num = CMSG_SDC_NICHT_GELIEFERT_HERSTELLER;
            }
            else if (ArtBase()->ArtFlags().IsNichtGeliefertHersteller())
            {
                num = CMSG_SDC_NICHT_LIEFERBAR_HERSTELLER;
            }
            else if (ArtBase()->ArtFlags().IsNichtUeberGrossHandel())
            {
                num = CMSG_SDC_NUR_DIREKT;
            }
            else if (!ArtBase()->ArtFlags().IsArtikelGefuehrt())
            {
                num = CMSG_SDC_NICHT_GEFUEHRT;
            }
            else if (Session()->isBulgaria())
            {
                if ( IsQuotaExeeded() )
                {
                    num = CMSG_SDC_ARTQUOTA_EXEEDED;
                }
            }
        }
    }
    else if (IsQStateAlternate())
    {
       num = CMSG_SDC_AUSWEICHARTIKEL_GEBUCHT;
    }
    else if (IsQStateTenderQtyExceeded() )
    {
       num = CMSG_ITM_TENDERQTY_EXCEEDED;
    }

    if ( IsDisponieren() )
    {
        num = CMSG_SDC_PURCHASEORDER;
    }
    if ( IsNachliefern() )
    {
        num = CMSG_SDC_RESTDELIVERY;
    }
    if ( IsMengenErhoehung())
    {
        num = CMSG_SDC_QUANTITYRAISED;
    }
    if ( IsAuxPosted())
    {
        num = CMSG_SDC_AUXPOSTED;
    }
    if ( IsAuxPostPossible())
    {
        num = CMSG_SDC_AUXPOSTPOSSIBLE;
    }
    if ( IsReimportArtikel())
    {
        num = (Order().isMSV3Order() || Order().IsMSV3InfoOrder()) && !customer.Flags().IsReimportArtikel() ? CMSG_ART_REIMPORT_PROPOSAL : CMSG_SDC_REIMPORTARTIKEL;
    }
    if ( IsRebateAccountExceeded() && Session()->isBulgaria() )
    {
        num = CMSG_SDC_CSTDISCACC_EXCEEDED;
    }
    if ( IsNoNarcoticsDiscAcc() && Session()->isBulgaria() )
    {
        num = CMSG_SDC_NONARCOTIC_DISCACC_ORDER;
    }

    if ( num >0 )
    {
       /* Get the txt from message file */
       nMessage answer (CMsgStream(), num, 0);
       sprintf(message,answer.String());
       num = (num*100) + Session()->LanguageCode();
    }

    return num;
}
/*----------------------------------------------------------------------------*/
/*  This function returns an errornumber and an errormessage in the callers   */
/*  messsage area.                                                            */
/*  Take care: this function just works on a well constructed pxOrderItem     */
/*  object.                                                                   */
/*----------------------------------------------------------------------------*/
int pxOrderItem::GetLackReason(char* message)
{
    int num = 0;                         /* contains section number */

    pxCustBase&       customer   = *(Order().Customer());
/*----------------------------------------------------------------------------*/
/*  First check the article state                                             */
/*----------------------------------------------------------------------------*/
    switch ( ArtState() )
    {
       case ArtStateNotFound :
       {
          if (ArtBase_->IsNotSaleable() )
             num = CMSG_SDC_AUSSER_HANDEL;
          else
             num = CMSG_SDC_NR_UNBEKANNT;
          break;
       }

       case ArtStateInvalidDigit:
       {
          num = CMSG_SDC_NICHT_NUMERISCH;
          break;
       }

       case ArtStateInvalidCheckDigit:
       {
          num = CMSG_SDC_PRUEFZIFFER_FALSCH;
          break;
       }

       case ArtStateNotAuthorized:
       {
          num = CMSG_SDC_NICHT_BERECHTIGT;
          if (Session()->isBulgaria())
          {
             if (!ArtBase() || !ArtBase()->IsGoodState() )
                break;
             if ( ArtBase_->ArtClass().IsOpiat() )
             {
                if ( !customer.ArtClass().IsOpiat() )
                   num = CMSG_SDC_CUSTOMER_NONARCOTICS;
             }
          }
          break;
       }
       case ArtStateNotCertificated:
       {
          num = CMSG_SDC_ARTIKEL_NO_CERTIFICAT;
          break;
       }
       case ArtStatePriceLimitCompViolationNHIFPriceMWPRefPrice:
       {
           num = CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_NHIFPRICE_MWP_REFPRICE;
           break;
       }
       case ArtStatePriceLimitCompViolationMWPAndRefPrice:
       {
           num = CMSG_ITM_PRICE_LIMIT_COMPLIANCE_VIOLATION_MWP_AND_REFPRICE;
           break;
       }
       case ArtStatePriceLimitDeletion:
       {
           num = CMSG_ITM_PRICE_LIMIT_PRODUCT_PRICE_DELETION;
           break;
       }
       case ArtStatePriceLimitMWPExceedance:
       {
           num = CMSG_ITM_PRICE_LIMIT_MWP_EXCEEDANCE;
           break;
       }
       default:
       {
          num = CMSG_SDC_DEFAULT;
          break;
       }
    }

    if  ( num != CMSG_SDC_DEFAULT )
    {
       nMessage answer (CMsgStream(), num, 0);
       sprintf(message,answer.String());
       return num;
    }

/*----------------------------------------------------------------------------*/
/*  Then check the quantity state                                             */
/*----------------------------------------------------------------------------*/
    num = 0;
    if (IsQStateNotOnHand())
    {
        num = CMSG_SDC_FEHLT_ZUR_ZEIT;
        if ( ArtBase() && ArtBase()->IsGoodState() )
        {
			if (ArtBase()->ArtFlags().IsAusserHandel())
			{
				num = CMSG_SDC_AUSSER_HANDEL;
			}
            else if (ArtBase()->IsKontingentPPE())
            {
                num = CMSG_SDC_QUOTA_ARTICLE_SUPPLIER;
            }
            else if (ArtBase()->ArtFlags().IsNichtLieferbarHersteller())
            {
                num = CMSG_SDC_NICHT_GELIEFERT_HERSTELLER;
            }
            else if (ArtBase()->ArtFlags().IsNichtGeliefertHersteller())
            {
                num = CMSG_SDC_NICHT_LIEFERBAR_HERSTELLER;
            }
            else if (ArtBase()->ArtFlags().IsNichtUeberGrossHandel())
            {
                num = CMSG_SDC_NUR_DIREKT;
            }
            else if (!ArtBase()->ArtFlags().IsArtikelGefuehrt())
            {
                num = CMSG_SDC_NICHT_GEFUEHRT;
            }
            else if (Session()->isBulgaria())
            {
                if ( IsQuotaExeeded() )
                {
                    num = CMSG_SDC_ARTQUOTA_EXEEDED;
                }
            }
        }
    }
    else if (IsQStateAlternate())
    {
        num = CMSG_SDC_AUSWEICHARTIKEL_GEBUCHT;
    }


    if ( num >0 )
    {
       /* Get the txt from message file */
       nMessage answer (CMsgStream(), num, 0);
       sprintf(message,answer.String());
       num = (num*100) + Session()->LanguageCode();
    }

    return num;
}

/*----------------------------------------------------------------------------*/
/* Returns all errorcodes in a list                                           */
/*----------------------------------------------------------------------------*/
basar::VarString pxOrderItem::GetLackReasonList()
{
	std::stringstream s;
	static const char* const DELIMITER = ";";

	/*----------------------------------------------------------------------------*/
	/*  First check the article state                                             */
	/*----------------------------------------------------------------------------*/
	switch (ArtState())
	{
		case ArtStateNotFound :
			if (ArtBase_->IsNotSaleable())
			{
				s << CMSG_SDC_AUSSER_HANDEL << DELIMITER;
			}
			else
			{
				s << CMSG_SDC_NR_UNBEKANNT << DELIMITER;
			}
			break;
		case ArtStateInvalidDigit:
			s << CMSG_SDC_NICHT_NUMERISCH << DELIMITER;
			break;
		case ArtStateInvalidCheckDigit:
			s << CMSG_SDC_PRUEFZIFFER_FALSCH << DELIMITER;
			break;
		case ArtStateNotAuthorized:
			s << CMSG_SDC_NICHT_BERECHTIGT << DELIMITER;
			if (Session()->isBulgaria())
			{
				if (ArtBase()->IsGoodState() && ArtBase_->ArtClass().IsOpiat() && !Order().Customer()->ArtClass().IsOpiat())
				{
					s << CMSG_SDC_CUSTOMER_NONARCOTICS << DELIMITER;
				}
			}
			break;
		case ArtStateNotCertificated:
			s << CMSG_SDC_ARTIKEL_NO_CERTIFICAT << DELIMITER;
			break;
		default:
          break;
	}

	/*----------------------------------------------------------------------------*/
	/*  Then check the quantity state                                             */
	/*----------------------------------------------------------------------------*/
	if (IsQStateNotOnHand())
	{
		s << CMSG_SDC_FEHLT_ZUR_ZEIT << DELIMITER;
		if (ArtBase() && ArtBase()->IsGoodState())
		{
			if (ArtBase()->ArtFlags().IsAusserHandel())
			{
				s << CMSG_SDC_AUSSER_HANDEL << DELIMITER;
			}
            if (ArtBase()->IsKontingentPPE())
            {
                s << CMSG_SDC_QUOTA_ARTICLE_SUPPLIER << DELIMITER;
            }
            if (ArtBase()->ArtFlags().IsNichtLieferbarHersteller())
			{
				s << CMSG_SDC_NICHT_LIEFERBAR_HERSTELLER << DELIMITER;
			}
			if (ArtBase()->ArtFlags().IsNichtGeliefertHersteller())
			{
				s << CMSG_SDC_NICHT_GELIEFERT_HERSTELLER << DELIMITER;
			}
			if (ArtBase()->ArtFlags().IsNichtUeberGrossHandel())
			{
				s << CMSG_SDC_NUR_DIREKT << DELIMITER;
			}
			if (!ArtBase()->ArtFlags().IsArtikelGefuehrt())
			{
				s << CMSG_SDC_NICHT_GEFUEHRT << DELIMITER;
			}
			if (IsQuotaExeeded())
			{
				s << CMSG_SDC_ARTQUOTA_EXEEDED << DELIMITER;
			}
		}
	}
	if (IsQStateAlternate())
	{
		s << CMSG_SDC_AUSWEICHARTIKEL_GEBUCHT << DELIMITER;
	}
	if (IsQStateTenderQtyExceeded())
	{
		s << CMSG_ITM_TENDERQTY_EXCEEDED << DELIMITER;
	}
	if (IsDisponieren())
	{
		s << CMSG_SDC_PURCHASEORDER << DELIMITER;
	}
	if (IsNachliefern())
	{
		s << CMSG_SDC_RESTDELIVERY << DELIMITER;
	}
	if (IsMengenErhoehung())
	{
		s << CMSG_SDC_QUANTITYRAISED << DELIMITER;
	}
	if (IsAuxPosted())
	{
		s << CMSG_SDC_AUXPOSTED << DELIMITER;
	}
	if (IsAuxPostPossible())
	{
		s << CMSG_SDC_AUXPOSTPOSSIBLE << DELIMITER;
	}
	if (IsReimportArtikel())
	{
		s << CMSG_SDC_REIMPORTARTIKEL << DELIMITER;
	}
	if (IsRebateAccountExceeded() && Session()->isBulgaria())
	{
		s << CMSG_SDC_CSTDISCACC_EXCEEDED << DELIMITER;
	}
	if (IsNoNarcoticsDiscAcc() && Session()->isBulgaria())
	{
		s << CMSG_SDC_NONARCOTIC_DISCACC_ORDER << DELIMITER;
    }
	if (ArtBase_->IsAktivAndNotOnStore())
	{
		s << CMSG_SDC_PSEUDO_STORAGE_LOCATION << DELIMITER;
	}
	if (ArtBase_->ArtFlags().IsAuslaufArtikel())
	{
		s << CMSG_SDC_DISCONTINUED_ARTICLE << DELIMITER;
	}
	return s.str();
}
