/*  Do not allow to include the file more than once                           */
#ifndef PXDBXX_DOTH
#define PXDBXX_DOTH

#include "pxrecord.h"

/*----------------------------------------------------------------------------*/
/*  Manifest cursor identification constants.                                 */
/*----------------------------------------------------------------------------*/
#define cCRS_DEFAULT                 1  /* the default for any browse */
#define cCRS_NOWHERE            0xFFFF  /* browse entire table (no where clause) */

#define cCRS_DARREICHFORM            2
#define cCRS_PACKGROESSE             3
#define cCRS_GROESSE_FORM            4

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing kdauftragpostour                                 */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdKdAuftragPosTour
{
    cKDAUFTRAGPOSTOUR_DEFAULT= 1,                   // cursor for restriction orderno, posno
    cKDAUFTRAGPOSTOUR_ORDER = 2                     // cursor for restriction orderno
} tCrsIdKdAuftragPosTour;


/*----------------------------------------------------------------------------*/
/*  IBTBranches Cursor id's for browsing the ibt branches                       */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdIBTBranches
{
    cIBTBRANCHES_DEFAULT= 1,                        // cursor for ibt selection from ibtbranches (get only entries for specific ibt branch)
    cIBTBRANCHES_ALLENTRIES = 2,                    // cursor for ibt selection from ibtbranches (get all entries)
    cIBTBRANCHES_RELEVANTNLEVELIBTBRANCHES = 3,     // get N-Level-IBT branch entries
    cIBTBRANCHES_NLEVELIBT = 4,                     // cursor for ibt selection from ibtbranches for NLevelIBT (get only entries for specific ibt branch and nlevelibttype)
    cIBTBRANCHES_NLEVELIBTARTICLENO = 5             // cursor for ibt selecction from ibtbranches for NLevelIBT by articleno
} tCrsIdIBTBranches;

/*----------------------------------------------------------------------------*/
/*  CustomerBusinessHours Cursor id's for browsing the business hours of a customer */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdCustomerBusinessHours
{
    cCUSTOMERBUSINESSHOURS_DEFAULT= 1           // cursor for business hours selection from kdbetriebsende
} tCrsIdCustomerBusinessHours;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the customer tours                               */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdCustomerTour
{
    cCUSTOMERTOUR_DEFAULT = 1,      // tours from tourplantag
    cCUSTOMERTOUR_WHOLEWEEK = 2,    // tours from tourplantagwoche
    cCUSTOMERTOUR_BYTOURID = 3,     // specific tour from tourplantag
    cCUSTOMERTOUR_BYTOURIDWEEK = 4  // specific tour from tourplantagwoche
} tCrsIdCustomerTour;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the article base table.                          */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdArtBase
{
    cCRSART_MatchCode            =  1,  /* like match code                    */
    cCRSART_Darreichform         =  2,
    cCRSART_PackGroesse          =  4,
    cCRSART_NormPackung          =  8

}   tCRSID_ARTBASE;

/*----------------------------------------------------------------------------*/
//  Cursor id's for browsing the artikelpreis table
/*----------------------------------------------------------------------------*/
typedef enum CrsIdArtPrice
{
    cCRS_TARTBPRTYPE        =  2

}   tCRSID_ARTPRICE;


/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the article store location table.                */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdArtStoreLoc
{
    cCRSART_STO_ArtikelNr            =  1,  /* default */
    cCRSART_STO_ArtikelNrFilialNr    =  2
}   tCRSID_ARTSTORELOC;


/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the customer order table.                        */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdOrder
{
    cCRSORD_IDFNr                =  1,  /* ==  customer number                */
    cCRSORD_GeraetName           =  2,
    cCRSORD_TourId               =  4,
    cCRSORD_FilialNr             =  8,
    cCRSORD_PersonalNr           = 16,
    cCRSORD_KdAuftragStat        = 32,  /* like order state                   */
    cCRSORD_KundenNr             = 64,
    cCRSORD_VertriebszentrumNr   = 128,
    cCRSORD_SelectModeEven       = 256,
    cCRSORD_SelectModeOdd        = 512,
    cCRSORD_ZuGrund              = 1024,
    cCRSORD_BatchAuftragNr       = 2048,
    cCRSORD_KdAuftragArt         = 4096,
    cCRSORD_OrderPeriodID        = 8192,
    cCRSORD_AUTOMATICCLOSURE     = 16384
}   tCRSID_ORDER;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the articlereservation table                       */
/*----------------------------------------------------------------------------*/
typedef enum CrsArticleReservation
{
    cCRSARTICLERESERVATION_Default              = 1, /* branchno, articleno, pharmacygroupid */
    cCRSARTICLERESERVATION_AllReservations      = 2  /* branchno, articleno */
} tCRSID_ARTICLERESERVATION;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the invoice queue table                          */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdInvoiceQueue
{
    cCRSINVQ_KdAuftragNr             =  1,  /* default */
    cCRSINVQ_AuftragNrKo             =  2,
    cCRSINVQ_LagerBereichNr          =  4

}   tCRSID_InvoiceQueue;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the delivery pos table                           */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdDeliveryPos
{
    cCRSDELPOS_POSTYP                =  1,  /* == PosTyp */
    cCRSDELPOS_IDFNR                 =  2,  /* == IDFNr  */
    cCRSDELPOS_IDFNRPOSTYP           =  4,  /* == IDFNr + PosTyp  */
    cCRSDELPOS_ORDERDATUM            =  8,  /* == Auftragnr + Datum  */
    cCRSDELPOS_ORDDATPOSTYP          = 16,  /* == Auftragnr + Datum + Postyp */
    cCRSDELPOS_VZIDFARTPOSTYP        = 32,  /* == VZ+IDFNr + ArtikelNr + Postyp */
    cCRSDELPOS_ARTPOSTYPVZ           = 64,  /* == Artikel_Nr + Postyp + VZ*/
    cCRSDELPOS_IDFNRPOSTYP35         = 128, /* == IDFNr + VZ + PosTyp 3und5 */
    cCRSDELPOS_ARTPOSTYPVZOTYPE      = 256, /* == Artikel_Nr + Postyp + VZ + OrderType*/
    cCRSDELPOS_ORDERVZIDFNROTYPE          = 512  /* == Auftragnr + Artikel_Nr + VZ + OrderType*/
}   tCRSID_DeliveryPos;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the tourplantag table                            */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdTourPtg
{
    cCRSTOURPTG_ISAUXREM             =  2   /* == ISTVERBUND */

}   tCRSID_TOURPTG;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the discount                                     */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdDiscount
{
    cCRSDISCOUNT_DISCOUNTTYPE        =  2,   /* == Branchno + ArticleNo + Discounttype */
    cCRSDISCOUNT_DISCOUNTGRP         =  4,   /* == Branchno + Discountgrp */
    cCRSDISCOUNT_JOIN_CSTPHARMGRP    =  8,   /* == Branchno + Articleno + CustomerNo Join with
                                                   Customerpharmacygr*/
    cCRSDISCOUNT_SHORT_LIST          = 16,   /* == Branchno + Articleno + Discounttype +
                                                   Customerpharmacygr*/
    cCRSDISCOUNT_BRARTCUST           = 32,   /* == Branchno + Articleno + CustomerNo*/
    cCRSDISCOUNT_BRMANCUST           = 64,   /* == Branchno + Articleno + CustomerNo + ManufacturerNo*/
    cCRSDISCOUNT_BRMANCUSTARTGRP_0   = 128,   /* == Branchno + Customerno for customer group */
    cCRSDISCOUNT_BRCUST              = 256,   /* == Branchno + Customerno for customer group */
    cCRSDISCOUNT_BRCUSTGRP           = 512,   /* == Branchno + Customerno for customer group */
    cCRSDISCOUNT_BRARTMAN_0          =1024,   /* == Branchno + Article in discountgrpmem (special manufacturer) */
    cCRSDISCOUNT_BRSINGLEART_0       =2048,   /* == Branchno + Article in discountgrpmem (single articles) */
    cCRSDISCOUNT_BRSINGLEART_1       =4096,   /* == Branchno + Article in discountgrpmem (single articles) */
    cCRSDISCOUNT_BROCCASIONS         =8192,   /* == Branchno + Article + discountspec=10 (Occasions) */
    cCRSDISCOUNT_BRARTMANUFACTURER_0 =16384,  // branchno + manufacturerno + customerno
    cCRSDISCOUNT_BRARTMANUFACTURER_1 =32768,  // branchno + manufacturerno
    cCRSDISCOUNT_BRART_0             =65536,  // branchno + articleno + customerno
    cCRSDISCOUNT_BRART_1             =131072, // branchno + articleno
    cCRSDISCOUNT_BRPROMOTION_0       =262144, // branchno + promotionno + customerno
    cCRSDISCOUNT_BRPROMOTION_1       =524288, // branchno + promotionno
    cCRSDISCOUNT_BRARTMAN_1          =1048576,// branchno + article in discountgrpmem (special manufacturer)
    cCRSDISCOUNT_BRMANCUSTARTGRP_1   =2097152,// branchno + customerno for customer group
    cCRSDISCOUNT_BRALLPROMOTIONS     =4194304,// all promotions (for positions and ranges)
    cCRSDISCOUNT_BRPROMOTIONNO       =8388608, // branchno, promotionno
    cCRSDISCOUNT_BRCUSTGRP_0         =16777216, // branchno, articleno, customerno, pharmacygroupid= 000, discountgrpno = 0
    cCRSDISCOUNT_JOIN_CSTPHARMGRP_1  =33554432,  // Branchno + Articleno + CustomerNo or CustomerNo = 0 and Join with Customerpharmacygr
    cCRSDISCOUNT_JOIN_CSTPHARMGRP_2  =67108864 // Branchno + Articleno + CustomerNo= 0 or pharmacygroupid= 000 and Join with Customerpharmacygr
}   tCRSID_DISCOUNT;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the discountgrpmem                               */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdDiscountGrpMem
{
    cCRSGRPMEM_GRPMEMBERS            =  2,  /* == Branchno + DiscountGrpNo */
    cCRSGRPMEM_GRPMANUFACTURER       =  4,  /* == Branchno + ManufacturerNo*/
    cCRSGRPMEM_GRPARTMANUFACTURER    =  8   /* == Branchno + ArticleNo + ManufacturerNo*/

}   tCRSID_GRPMEM;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the discountgrpmem                               */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdDiscountPharmaGrp
{
    cCRSPHARMAGRP_GRPBRANCH           =  2   /* == Branchno */

}   tCRSID_PHARMAGRP;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the Narctransactiotransfer                       */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdNarcTransfer
{
    cCRSNARCTRANSFER_ORDERPOS         =  2, /* == Orderno + PosNo */
    cCRSNARCTRANSFER_ORDERART         =  4   /* == Branchno + Orderno */

}   tCRSID_NARCTRANSFER;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the Positionparking                              */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdPosParking
{
    cCRSPOSPARKING_ORDERTODAY         =  2   /* == BranchNo+CustomerNo+ArtikelNo+Today+OrderNo */

}   tCRSID_POSPARKING;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the Parameter                                    */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdParameter
{
    cCRSPARAMETER_MINT                =  2   /* == Filailnr+Programmname+Zweck+Paramtername */

}   tCRSID_PARAMETER;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the ArtikelNummern                               */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdArtikelNummern
{
    cCRSARTNUM_PZN                    =  2,  /* == via PZN */
    cCRSARTNUM_ARTIKELNR              =  4   /* == via ARTIKELNR */

}   tCRSID_ARTNUM;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the KdAuftragPosRab                              */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdPosRab
{
    cCRSPOSRAB_KDAUFTRAGNR            =  2  /* == via KdAuftragNr */
}   tCRSID_POSRAB;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the countrycodes table                           */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdCountryCodes
{
    cCRSCOUNTRYCODES_XMLCODE          =  2   /* == XMLCODE */

}   tCRSID_COUNTRYCODES;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the tourplanconstime table                       */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdTourplanConsTime
{
    cCRSTPLCONSTIME_CTIMEPSTATE       =  2   /* == Constime < currentime */
                                         /* and ProcessState == 0 */
}   tCRSID_TPLCONSTIME;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the tourconstime table                           */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdTourConsTime
{
    cCRSTCONSTIME_CTIMEPSTATE         =  2   /* == Constime < currentime */
                                         /* and ProcessState == 0 */
}   tCRSID_TCONSTIME;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the tourplantagwoche                             */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdTourPLTWoche
{
    cCRSTPLTWOCHE_DAYTYPE             =  2,  /* VZ+KundenNr+Daytype */
    cCRSTPLTWOCHE_IBT                 =  4   /* VZ+KundenNr+IstVerbundTour */

}   tCRSID_TPLWOCHE;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the ordercriteria                                */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdOrdCriteria
{
    cCRORDERTYPCSTPHARMGRP            =  2,  /* VZ+ArticleNo+Ordertype+
                                                PharmacyGroupId          */
    cCRMANUFACTNOCSTNO                =  4,  /* VZ+ArticleNo+ManufactureNo+
                                                CustomerNo               */
    cCRORDERTYPLIMITACTION            =  8   /* VZ+Ordertype+Limitaction*/

}   tCRSID_ORDCRITERIA;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the tenderhead                                   */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the tenderprogress                               */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdTenderProgress
{
    cCRTPGTENDERNOARTICLENO              =  2,   /* TenderNo, ArticleNo  */
    cCRTPGTENDERNOTENDERNO               =  4    /* KdAuftragNr, Orderdate, Articleno */
}   tCRSID_TENDERPROGRESS;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the tenderpos                                    */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdTenderPos
{
    cCRTPTENDERNOSTATE                   =  2   /* TenderNo,TenderState  */
}   tCRSID_TENDERPOS;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the CstDiscAcc                                   */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdCstDiscAcc
{
    cCRCDACUSTOMERNO                     =  2,   /* BranchNo,CustomerNo,DateFrom,DateTo */
    cCRCDAMAINCSTNO                      =  4,   /* MainCstNo,DateFrom,DateTo   */
    cCRCDAKDAUFTRAGNR                    =  8,   /* KdAuftragNr   */
    cCRCDACUSTOMERNOVOUCHERTYP           =  16,  /* BranchNo,CustomerNo,DateFrom,DateTo,Vouchertype*/
    cCRCDAMAINCSTNOVOUCHERTYP            =  32   /* MainCstNo,DateFrom,DateTo,Vouchertyp   */
}   tCRSID_CSTDISCACC;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the discountgrp                                  */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdCustOrderNumber
{
    cCRSCUSTORDERNUM                     =  2   /* BranchNo,Customerno,ordervalue,CustomerOrderNo  */
}   tCRSID_CUSTORDERNUM;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the discountgrp                                  */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdDiscountGrp
{
    cCRSDISCOUNTGRPTYPE                  =  2   /* BranchNo,Type,Customerno  */
}   tCRSID_DISCOUNTGRP;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the promotionquota                               */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdPromotionQuota
{
    cCRSPROMOTION_BR_PRO_ART             =  2   /* BranchNo,PromotionNo,ArticleNo */
}   tCRSID_PROMOTIONQUOTA;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the promotionquotacst                            */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdPromotionQuotaCst
{
    cCRSPROMOTIONCST_BR_PRO_CST_ART       =  2   /* BranchNo,PromotionNo,CustomerNo,ArticleNo */
}   tCRSID_PROMOTIONQUOTACST;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the customersurcharge                            */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdCustomerSurcharge
{
    cCRSCUSTOMERSURCHARGE_BR_CST_MAN      =  2   /* BranchNo,CustomerNo,ManufacturerNo */
}   tCRSID_CUSTOMERSURCHARGE;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the articlecode                                  */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdArticleCodes
{
    cCRSARTICLENO_PREFERRED                =  2,
    cCRSARTICLENO_CODETYPE                 =  3,
    cCRSARTICLENO                          =  4
}   tCRSID_ARTICLECODES;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the vartikellokal                                */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdVartikelLokal
{
    cCRS_IBTBRANCHES                       =   39,        // select über ibtbranches
    cCRS_IBTBRANCHES_NLEVELIBT             =   40,        // select über ibtbranches für N-Level-Verbund
    cCRS_IBTBRANCHES_NLEVELIBT_INACTIVE    =   41         // select über ibtbranches für N-Level-Verbund und inaktives VB-Zeitfenster
}   tCRSID_VARTIKELLOKAL;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the manufacturergroup                            */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdManufacturerGroup
{
    cCRSKONSIGPARTNERNR                =  2
}   tCRSID_MANUFACTURERGROUP;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the discount                                     */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdDebtMail
{
    cCRSDEBTMAIL_GETDATAFORPERCENTAGE        =  2, /* Input percentage, branchNo, levelType */
    cCRSDEBTMAIL_GETDATAFORAMOUNT            =  3, /* Input amount, branchNo */
    cCRSDEBTMAIL_GETDATAFORLEVEL             =  4,
    cCRSDEBTMAIL_CHECKWASSEND_ORDER          =  6, /* Input kdauftragnr, datum */
    cCRSDEBTMAIL_GETTYPEFORPERCENTAGE        =  8, /* Input percentage */
    cCRSDEBTMAIL_GETTYPEFORAMOUNT            =  9, /* Input amount */
    cCRSDEBTMAIL_GETMAILADDRESSES            =  10, /* Input smtpusergrouid */
    cCRSDEBTMAIL_GETAPPROVALSNEEDED          =  11,
    cCRSDEBTMAIL_GETGVLMAIL                  =  12,
    cCRSDEBTMAIL_CHECKWASSEND_AMOUNT_PARTNER =  13,
    cCRSDEBTMAIL_CHECKWASSEND_WARNING_PARTNER =  14,
    cCRSDEBTMAIL_GET_WARNING_PARTNER_VZS     =  15,
    cCRSDEBTMAIL_GET_DEFERRED_ORDERS         =  16,
    cCRSDEBTMAIL_GETMAILDATAFORUUID          =  18,
    cCRSDEBTMAIL_GETLANGUAGEFORPARTNER       =  19,
    cCRSDEBTMAIL_GETGUIDFORORDERNO           =  20,
    cCRSDEBTMAIL_GETSMTPSERVER               =  21
}   tCRSID_DEBTMAIL;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the kdauftrag for MSV3                           */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdMSV3Order
{
    cCRSMSV3ORDER_GETDISTINCTORDERLABEL      =  2
}   tCRSID_MSV3ORDER;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the promotionscale                                */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdPromotionScale
{
    cCRS_BASEPROMOTION                       =    2        // promotionscale(BasePromotion)
}   tCRSID_BASEPROMOTION;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the orderremarktypes                             */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdOrderRemarkTypes
{
    cCRSORDERREMARKTYPES_GETALLORDERREMARKTYPES = 2,
    cCRSORDERREMARKTYPES_GETHEADERORDERREMARKTYPES = 4,
    cCRSORDERREMARKTYPES_GETLINEORDERREMARKTYPES = 6
} tCrsIdOrderRemarkTypes;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the orderremarktypes                             */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdOrderRemarks
{
    cCRSORDERREMARKS_GETALLORDERREMARKS = 2,
    cCRSORDERREMARKS_GETALLORDERLINEREMARKS = 3,
    cCRSORDERREMARKS_GETALLORDERREMARKSBYTYPE = 4,
    cCRSORDERREMARKS_GETALLORDERLINEREMARKSBYTYPE = 5
} tCrsIdOrderRemarks;

typedef enum CrsIdDebtRel
{
    cCRSDEBTREL_GETRELEASEFLAGFORORDER        =  2, /* Input kdauftragnr */
    cCRSDEBTREL_GETAPPROVALDATAFORORDER       =  4, /* Input kdauftragnr */
    cCRSDEBTREL_GETDATAFORMAXRELCOUNT         =  6, /* Input kdauftragnr */
    cCRSDEBTREL_CHECKUSERVOTE                 =  8, /* Input kdauftragnr */
    cCRSDEBTREL_CHECKVOTE                     =  10, /* Input kdauftragnr */
    cCRSDEBTREL_SELECTFORCOPY                 =  12,
    cCRSDEBTREL_INSERT                        =  20,
    cCRSDEBTREL_INSERT_COPY_OF                =  21
}   tCRSID_DEBTREL;

typedef enum CrsIdArticleQuota
{
    cCRSARTICLEQUOTA_ORIGINAL                 = 2,  // select via branchno,articleno, customerno
    cCRSARTICLEQUOTA_BASIC                    = 4   // select via branchno, articleno, customerno = 0 and pharmacygroupid = "" or "000"
}   tCRSID_ARTICLEQUOTA;

typedef enum CrsIdOERestrictions
{
    cCRSOERESTRICTIONS_OVERALL                = 2  // select via branchno,restrictiontype, restrictionvalue,origintype
}   tCRSID_OERESTRICTIONS;

typedef enum CrsIdArtikelAltern
{
    cCRSARTIKELALTERN_FORWARD                 = 2, // select via artikel_nr and Filialnr
    cCRSARTIKELALTERN_REVERSE                 = 4  // select via artikel_nr_altern and Filialnr
}   tCRSID_ARTIKELALTERN;

typedef enum CrsIdCustomerSpecials
{
    cCRSCUSTOMERSPECIALS_FIRST_UW_IDF         = 2, // select first 1 branchno, customerno, uw_idf > 0
    cCRSCUSTOMERSPECIALS_UW_IDF               = 4  // select via branchno, uw_idf
}   tCRSID_CRSCUSTOMERSPECIALS;

typedef enum CrsIdOrderRelationNoTypes
{
    cCRSORDERRELATIONNOTYPES = 2
} tCrsIdOrderRelationNoTypes;

typedef enum CrsIdOrderRelationNo
{
    cCRSORDERRELATIONNO_GETORDERRELATIONNO = 2,
    cCRSORDERRELATIONNO_GETBYTYPE          = 4
} tCrsIdOrderRelationNo;

typedef enum CrsIdCustomerRouting
{
    cCRSCUSTOMERROUTING_HASROUTINGSTARTINGTODAY = 2,
    cCRSCUSTOMERROUTING_ISROUTED = 4
} tCrsIdCustomerRouting;

/*----------------------------------------------------------------------------*/
/*  Cursor id's for browsing the delayeddeliverycst                           */
/*----------------------------------------------------------------------------*/
typedef enum CrsIdDelayedDeliveryCst
{
    cCRDELDELIVERYCST_NOTUSETOURMANAGER_2   =  2,    /* Branchno, CustomerNo > 0 and datefrom = 0 or CustomerNo = 0 and datefrom > 0, WeekDay, Activ = 1   */
    cCRDELDELIVERYCST_USETOURMANAGER_2      =  4,    /* BranchNo, Cutomerno = 0 , Weekday, Activ = 1 and datefrom > 0 and dateto > 0 */
    cCRDELDELIVERYCST_USETOURMANAGER_DATE_2 =  6
}   tCrsId_DelayedDeliveryCst;

/*----------------------------------------------------------------------------*/
/*  Function prototypes.                                                      */
/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {                            /* Assume C declarations for C++      */
#endif


long pxSQLCode();
long pxISAMCode();
char* pxSQLMessage();
int pxFunctionNr();

int pxConnect();
int pxDisconnect();
int pxBegin();
int pxCommit();
int pxRollback();
void pxSetCurrentDb (const char * const);

int pxTourPlanTagStartBrowse ( struct tTOURPLANTAG* record, int browseid);
int pxTourPlanTagGetNext     ( struct tTOURPLANTAG* record, int browseid);
int pxTourPlanTagEndBrowse   ( int browseid);
int pxTourPlanTagRead        ( struct tTOURPLANTAG* record);
int pxTourPlanTagReadLock    ( struct tTOURPLANTAG* record);
int pxTourPlanTagUpdate      ( struct tTOURPLANTAG* record);
int pxTourPlanTagInsert      ( struct tTOURPLANTAG* record);
int pxTourPlanTagUpdate      ( struct tTOURPLANTAG* record);

int pxTourStartBrowse      ( struct tTOUR* record, int browseid);
int pxTourGetNext          ( struct tTOUR* record, int browseid);
int pxTourEndBrowse        ( int browseid);
int pxTourRead             ( struct tTOUR* record);
int pxTourReadLock         ( struct tTOUR* record);
int pxTourUpdate           ( struct tTOUR* record);
int pxTourInsert           ( struct tTOUR* record);
int pxTourDelete           ( struct tTOUR* record);

int pxAufArtKombStartBrowse ( struct tAUFTRAGARTKOMB* record, int browseid);
int pxAufArtKombGetNext     ( struct tAUFTRAGARTKOMB* record, int browseid);
int pxAufArtKombEndBrowse   ( int browseid);
int pxAufArtKombRead        ( struct tAUFTRAGARTKOMB* record);
int pxAufArtKombReadLock    ( struct tAUFTRAGARTKOMB* record);
int pxAufArtKombInsert      ( struct tAUFTRAGARTKOMB* record);
int pxAufArtKombUpdate      ( struct tAUFTRAGARTKOMB* record);
int pxAufArtKombDelete      ( struct tAUFTRAGARTKOMB* record);

int pxAuftragArtKdStartBrowse ( struct tAUFTRAGARTKD* record, int browseid);
int pxAuftragArtKdGetNext     ( struct tAUFTRAGARTKD* record, int browseid);
int pxAuftragArtKdEndBrowse   ( int browseid);
int pxAuftragArtKdRead        ( struct tAUFTRAGARTKD* record);
int pxAuftragArtKdReadLock    ( struct tAUFTRAGARTKD* record);
int pxAuftragArtKdUpdate      ( struct tAUFTRAGARTKD* record);
int pxAuftragArtKdInsert      ( struct tAUFTRAGARTKD* record);
int pxAuftragArtKdDelete      ( struct tAUFTRAGARTKD* record);

int pxBuchArtStartBrowse ( struct tBUCHUNGSART* record, int browseid);
int pxBuchArtGetNext     ( struct tBUCHUNGSART* record, int browseid);
int pxBuchArtEndBrowse   ( int browseid);
int pxBuchArtRead        ( struct tBUCHUNGSART* record);
int pxBuchArtReadLock    ( struct tBUCHUNGSART* record);
int pxBuchArtUpdate      ( struct tBUCHUNGSART* record);
int pxBuchArtInsert      ( struct tBUCHUNGSART* record);
int pxBuchArtDelete      ( struct tBUCHUNGSART* record);

int pxKommiArtStartBrowse ( struct tKOMMIARTEN* record, int browseid);
int pxKommiArtGetNext     ( struct tKOMMIARTEN* record, int browseid);
int pxKommiArtEndBrowse   ( int browseid);
int pxKommiArtRead        ( struct tKOMMIARTEN* record);
int pxKommiArtReadLock    ( struct tKOMMIARTEN* record);
int pxKommiArtUpdate      ( struct tKOMMIARTEN* record);
int pxKommiArtInsert      ( struct tKOMMIARTEN* record);
int pxKommiArtDelete      ( struct tKOMMIARTEN* record);

int pxAuftragArtStartBrowse ( struct tKDAUFTRAGART* record, int browseid);
int pxAuftragArtGetNext     ( struct tKDAUFTRAGART* record, int browseid);
int pxAuftragArtEndBrowse   ( int browseid);
int pxAuftragArtRead        ( struct tKDAUFTRAGART* record);
int pxAuftragArtReadLock    ( struct tKDAUFTRAGART* record);
int pxAuftragArtUpdate      ( struct tKDAUFTRAGART* record);
int pxAuftragArtInsert      ( struct tKDAUFTRAGART* record);
int pxAuftragArtDelete      ( struct tKDAUFTRAGART* record);

int pxAuftragEreignisStartBrowse ( struct tKDAUFTRAGEREIGNIS* record, int browseid);
int pxAuftragEreignisGetNext     ( struct tKDAUFTRAGEREIGNIS* record, int browseid);
int pxAuftragEreignisEndBrowse   ( int browseid);
int pxAuftragEreignisRead        ( struct tKDAUFTRAGEREIGNIS* record);
int pxAuftragEreignisReadLock    ( struct tKDAUFTRAGEREIGNIS* record);
int pxAuftragEreignisUpdate      ( struct tKDAUFTRAGEREIGNIS* record);
int pxAuftragEreignisInsert      ( struct tKDAUFTRAGEREIGNIS* record);
int pxAuftragEreignisDelete      ( struct tKDAUFTRAGEREIGNIS* record);

int pxAuftragStartBrowse ( struct tKDAUFTRAG* record, int browseid);
int pxAuftragGetNext     ( struct tKDAUFTRAG* record, int browseid);
int pxAuftragEndBrowse   ( int browseid);
int pxAuftragRead        ( struct tKDAUFTRAG* record);
int pxAuftragReadLock    ( struct tKDAUFTRAG* record);
int pxAuftragUpdate      ( struct tKDAUFTRAG* record);
int pxAuftragInsert      ( struct tKDAUFTRAG* record);
int pxAuftragDelete      ( struct tKDAUFTRAG* record);

int pxMArtikelStartBrowse ( struct tMARTIKEL* article, int browseid);
int pxMArtikelGetNext     ( struct tMARTIKEL* article, int browseid);
int pxMArtikelEndBrowse   ( int browseid);
int pxMArtikelRead        ( struct tMARTIKEL* article);
int pxMArtikelReadLock    ( struct tMARTIKEL* article);
int pxMArtikelUpdate      ( struct tMARTIKEL* article);
int pxMArtikelInsert      ( struct tMARTIKEL* article);
int pxMArtikelDelete      ( struct tMARTIKEL* article);

int pxFArtikelStartBrowse ( struct tFARTIKEL* article, int browseid);
int pxFArtikelGetNext     ( struct tFARTIKEL* article, int browseid);
int pxFArtikelEndBrowse   ( int browseid);
int pxFArtikelRead        ( struct tFARTIKEL* article);
int pxFArtikelReadLock    ( struct tFARTIKEL* article);
int pxFArtikelUpdate      ( struct tFARTIKEL* article);
int pxFArtikelInsert      ( struct tFARTIKEL* article);
int pxFArtikelDelete      ( struct tFARTIKEL* article);

int pxDispoArtikelStartBrowse ( struct tDISPOARTIKEL* article, int browseid);
int pxDispoArtikelGetNext     ( struct tDISPOARTIKEL* article, int browseid);
int pxDispoArtikelEndBrowse   ( int browseid);
int pxDispoArtikelRead        ( struct tDISPOARTIKEL* article);
int pxDispoArtikelReadLock    ( struct tDISPOARTIKEL* article);
int pxDispoArtikelUpdate      ( struct tDISPOARTIKEL* article);
int pxDispoArtikelInsert      ( struct tDISPOARTIKEL* article);
int pxDispoArtikelDelete      ( struct tDISPOARTIKEL* article);

int pxArtikelAlternStartBrowse ( struct tARTIKELALTERN* preis, int browseid);
int pxArtikelAlternGetNext     ( struct tARTIKELALTERN* preis, int browseid);
int pxArtikelAlternEndBrowse   ( int browseid);
int pxArtikelAlternRead        ( struct tARTIKELALTERN* preis);
int pxArtikelAlternReadLock    ( struct tARTIKELALTERN* preis);
int pxArtikelAlternUpdate      ( struct tARTIKELALTERN* preis);
int pxArtikelAlternInsert      ( struct tARTIKELALTERN* preis);
int pxArtikelAlternDelete      ( struct tARTIKELALTERN* preis);

int pxArtikelpreisStartBrowse ( struct tARTIKELPREIS* preis, int browseid);
int pxArtikelpreisGetNext     ( struct tARTIKELPREIS* preis, int browseid);
int pxArtikelpreisEndBrowse   ( int browseid);
int pxArtikelpreisRead        ( struct tARTIKELPREIS* preis);
int pxArtikelpreisReadLock    ( struct tARTIKELPREIS* preis);
int pxArtikelpreisUpdate      ( struct tARTIKELPREIS* preis);
int pxArtikelpreisInsert      ( struct tARTIKELPREIS* preis);
int pxArtikelpreisDelete      ( struct tARTIKELPREIS* preis);

//int pxArtikelMpreisStartBrowse ( struct tARTIKELMGPREIS* preis, int browseid);
//int pxArtikelMpreisGetNext     ( struct tARTIKELMGPREIS* preis, int browseid);
//int pxArtikelMpreisEndBrowse   ( int browseid);
//int pxArtikelMpreisRead        ( struct tARTIKELMGPREIS* preis);
//int pxArtikelMpreisReadLock    ( struct tARTIKELMGPREIS* preis);
//int pxArtikelMpreisUpdate      ( struct tARTIKELMGPREIS* preis);
//int pxArtikelMpreisInsert      ( struct tARTIKELMGPREIS* preis);
//int pxArtikelMpreisDelete      ( struct tARTIKELMGPREIS* preis);

//int pxArtikelNatraStartBrowse ( struct tARTIKELNATRA* preis, int browseid);
//int pxArtikelNatraGetNext     ( struct tARTIKELNATRA* preis, int browseid);
//int pxArtikelNatraEndBrowse   ( int browseid);
//int pxArtikelNatraRead        ( struct tARTIKELNATRA* preis);
//int pxArtikelNatraReadLock    ( struct tARTIKELNATRA* preis);
//int pxArtikelNatraUpdate      ( struct tARTIKELNATRA* preis);
//int pxArtikelNatraInsert      ( struct tARTIKELNATRA* preis);
//int pxArtikelNatraDelete      ( struct tARTIKELNATRA* preis);

int pxLagerortStartBrowse ( struct tARTIKELLAGERORT* ort, int browseid);
int pxLagerortGetNext     ( struct tARTIKELLAGERORT* ort, int browseid);
int pxLagerortEndBrowse   ( int browseid);
int pxLagerortRead        ( struct tARTIKELLAGERORT* ort);
int pxLagerortReadLock    ( struct tARTIKELLAGERORT* ort);
int pxLagerortUpdate      ( struct tARTIKELLAGERORT* ort);
int pxLagerortInsert      ( struct tARTIKELLAGERORT* ort);
int pxLagerortDelete      ( struct tARTIKELLAGERORT* ort);

int pxFilialeStartBrowse( struct tFILIALE* kunde, int browseid);
int pxFilialeGetNext( struct tFILIALE* kunde, int browseid);
int pxFilialeEndBrowse(int browseid);
int pxFilialeRead( struct tFILIALE* kunde);
int pxFilialeUpdate( struct tFILIALE* kunde);

int pxKundeStartBrowse  ( struct tKUNDE* kunde,int browseid);
int pxKundeGetNext      ( struct tKUNDE* kunde,int browseid);
int pxKundeEndBrowse    ( int browseid);
int pxKundeRead         ( struct tKUNDE* kunde);
int pxKundeReadLock     ( struct tKUNDE* kunde);
int pxKundeUpdate       ( struct tKUNDE* kunde);
int pxKundeInsert       ( struct tKUNDE* kunde);

int pxKundeBetriebStartBrowse( struct tKDBETRIEBSENDE* kunde, int browseid);
int pxKundeBetriebGetNext( struct tKDBETRIEBSENDE* kunde, int browseid);
int pxKundeBetriebEndBrowse(int browseid);
int pxKundeBetriebRead( struct tKDBETRIEBSENDE* kunde);
int pxKundeBetriebReadLock( struct tKDBETRIEBSENDE* kunde);
int pxKundeBetriebUpdate( struct tKDBETRIEBSENDE* kunde);
int pxKundeBetriebInsert( struct tKDBETRIEBSENDE* kunde);

int pxKundeKondiStartBrowse( struct tKUNDEKONDI* kunde, int browseid);
int pxKundeKondiGetNext( struct tKUNDEKONDI* kunde, int browseid);
int pxKundeKondiEndBrowse(int browseid);
int pxKundeKondiRead( struct tKUNDEKONDI* kunde);
int pxKundeKondiInsert( struct tKUNDEKONDI* kunde);

int pxKundeSchalterStartBrowse ( struct tKUNDESCHALTER* kunde, int browseid);
int pxKundeSchalterGetNext     ( struct tKUNDESCHALTER* kunde, int browseid);
int pxKundeSchalterEndBrowse   ( int browseid);
int pxKundeSchalterRead        ( struct tKUNDESCHALTER* kunde);
int pxKundeSchalterReadLock    ( struct tKUNDESCHALTER* kunde);
int pxKundeSchalterUpdate      ( struct tKUNDESCHALTER* kunde);
int pxKundeSchalterInsert      ( struct tKUNDESCHALTER* kunde);
int pxKundeSchalterDelete      ( struct tKUNDESCHALTER* kunde);

int pxNachLieferPosStartBrowse ( struct tNACHLIEFERPOS* position, int browseid);
int pxNachLieferPosGetNext     ( struct tNACHLIEFERPOS* position, int browseid);
int pxNachLieferPosEndBrowse   ( int browseid);
int pxNachLieferPosRead        ( struct tNACHLIEFERPOS* position);
int pxNachLieferPosReadLock    ( struct tNACHLIEFERPOS* position);
int pxNachLieferPosUpdate      ( struct tNACHLIEFERPOS* position);
int pxNachLieferPosInsert      ( struct tNACHLIEFERPOS* position);
int pxNachLieferPosDelete      ( struct tNACHLIEFERPOS* position);

int pxPositionStartBrowse( struct tKDAUFTRAGPOS* position, int browseid);
int pxPositionGetNext( struct tKDAUFTRAGPOS* position, int browseid);
int pxPositionEndBrowse(int browseid);
int pxPositionRead( struct tKDAUFTRAGPOS* position);
int pxPositionReadLock( struct tKDAUFTRAGPOS* position);
int pxPositionUpdate( struct tKDAUFTRAGPOS* position);
int pxPositionInsert( struct tKDAUFTRAGPOS* position);
int pxPositionDelete( struct tKDAUFTRAGPOS* position);

int pxParaAuftragBearbRead( struct tPARAAUFTRAGBEARB* record, const char* dbname);

//int pxKdKondGruppeStartBrowse( struct tKDKONDITIONGRUPPE* position, int browseid);
//int pxKdKondGruppeGetNext    ( struct tKDKONDITIONGRUPPE* position, int browseid);
//int pxKdKondGruppeEndBrowse  ( int browseid);
//int pxKdKondGruppeRead       ( struct tKDKONDITIONGRUPPE* position);
//int pxKdKondGruppeReadLock   ( struct tKDKONDITIONGRUPPE* position);
//int pxKdKondGruppeUpdate     ( struct tKDKONDITIONGRUPPE* position);
//int pxKdKondGruppeInsert     ( struct tKDKONDITIONGRUPPE* position);
//int pxKdKondGruppeDelete     ( struct tKDKONDITIONGRUPPE* position);

int pxKundenGruppeStartBrowse( struct tKUNDENGRUPPE* position, int browseid);
int pxKundenGruppeGetNext    ( struct tKUNDENGRUPPE* position, int browseid);
int pxKundenGruppeEndBrowse  ( int browseid);
int pxKundenGruppeRead       ( struct tKUNDENGRUPPE* position);
int pxKundenGruppeReadLock   ( struct tKUNDENGRUPPE* position);
int pxKundenGruppeUpdate     ( struct tKUNDENGRUPPE* position);
int pxKundenGruppeInsert     ( struct tKUNDENGRUPPE* position);
int pxKundenGruppeDelete     ( struct tKUNDENGRUPPE* position);

int pxFilialeStartBrowse  ( struct tFILIALE* position, int browseid);
int pxFilialeGetNext      ( struct tFILIALE* position, int browseid);
int pxFilialeEndBrowse    ( int browseid);
int pxFilialeRead         ( struct tFILIALE* position);
int pxFilialeReadLock     ( struct tFILIALE* position);
int pxFilialeUpdate       ( struct tFILIALE* position);
int pxFilialeInsert       ( struct tFILIALE* position);
int pxFilialeDelete       ( struct tFILIALE* position);

int pxAuftragBemStartBrowse ( struct tKDAUFTRAGBEM* position, int browseid);
int pxAuftragBemGetNext     ( struct tKDAUFTRAGBEM* position, int browseid);
int pxAuftragBemEndBrowse   ( int browseid);
int pxAuftragBemRead        ( struct tKDAUFTRAGBEM* position);
int pxAuftragBemReadLock    ( struct tKDAUFTRAGBEM* position);
int pxAuftragBemUpdate      ( struct tKDAUFTRAGBEM* position);
int pxAuftragBemInsert      ( struct tKDAUFTRAGBEM* position);
int pxAuftragBemDelete      ( struct tKDAUFTRAGBEM* position);

int pxZeitArtenStartBrowse     ( struct tZEITARTEN* record, int browseid);
int pxZeitArtenGetNext         ( struct tZEITARTEN* record, int browseid);
int pxZeitArtenEndBrowse       ( int browseid);
int pxZeitArtenRead            ( struct tZEITARTEN* record);
int pxZeitArtenReadLock        ( struct tZEITARTEN* record);
int pxZeitArtenUpdate          ( struct tZEITARTEN* record);
int pxZeitArtenInsert          ( struct tZEITARTEN* record);
int pxZeitArtenDelete          ( struct tZEITARTEN* record);


int pxAuftragEndeZeitStartBrowse ( struct tKDAUFTRAGENDEZEIT* record, int browseid);
int pxAuftragEndeZeitGetNext     ( struct tKDAUFTRAGENDEZEIT* record, int browseid);
int pxAuftragEndeZeitEndBrowse   ( int browseid);
int pxAuftragEndeZeitRead        ( struct tKDAUFTRAGENDEZEIT* record);
int pxAuftragEndeZeitReadLock    ( struct tKDAUFTRAGENDEZEIT* record);
int pxAuftragEndeZeitUpdate      ( struct tKDAUFTRAGENDEZEIT* record);
int pxAuftragEndeZeitInsert      ( struct tKDAUFTRAGENDEZEIT* record);
int pxAuftragEndeZeitDelete      ( struct tKDAUFTRAGENDEZEIT* record);

int pxNachLiefProtInsert         ( struct tNACHLIEFPROT* position);
int pxNachLiefProtRead           ( struct tNACHLIEFPROT* record );
int pxNachLiefProtReadLock       ( struct tNACHLIEFPROT* record );
int pxNachLiefProtUpdate         ( struct tNACHLIEFPROT* record );
int pxNachLiefProtDelete         ( struct tNACHLIEFPROT* record );
int pxNachLiefProtStartBrowse    ( struct tNACHLIEFPROT* record, int browseid);
int pxNachLiefProtGetNext        ( struct tNACHLIEFPROT* record, int browseid);
int pxNachLiefProtEndBrowse      ( int browseid);

int pxRArtikelRead              ( struct tFARTIKEL* position, char* Computer);
int pxRArtikelReadLock          ( struct tFARTIKEL* position, char* Computer);
int pxRArtikelUpdate            ( struct tFARTIKEL* record, char* Computer);

int pxComputerRead           ( struct tRECHNER* record);
int pxComputerStartBrowse    ( struct tRECHNER* record, int browseid);
int pxComputerGetNext        ( struct tRECHNER* record, int browseid);
int pxComputerEndBrowse      ( int browseid        );

int pxArtikelReimportStartBrowse ( struct tARTIKELREIMPORT* record, int browseid);
int pxArtikelReimportGetNext     ( struct tARTIKELREIMPORT* record, int browseid);
int pxArtikelReimportEndBrowse   ( int browseid);
int pxArtikelReimportRead        ( struct tARTIKELREIMPORT* record);

int pxLagerRevisionStartBrowse    ( struct tLAGERREVISION* record, int browseid);
int pxLagerRevisionGetNext        ( struct tLAGERREVISION* record, int browseid);
int pxLagerRevisionEndBrowse      ( int browseid);
int pxLagerRevisionRead           ( struct tLAGERREVISION* record);
int pxLagerRevisionReadLock       ( struct tLAGERREVISION* record);
int pxLagerRevisionUpdate         ( struct tLAGERREVISION* record);
int pxLagerRevisionInsert         ( struct tLAGERREVISION* record);
int pxLagerRevisionDelete         ( struct tLAGERREVISION* record);

int pxTaskControlStartBrowse      ( struct tTASKCONTROL* record, int browseid);
int pxTaskControlGetNext          ( struct tTASKCONTROL* record, int browseid);
int pxTaskControlEndBrowse        ( int browseid);
int pxTaskControlRead             ( struct tTASKCONTROL* record);
int pxTaskControlReadLock         ( struct tTASKCONTROL* record);
int pxTaskControlUpdate           ( struct tTASKCONTROL* record);
int pxTaskControlInsert           ( struct tTASKCONTROL* record);
int pxTaskControlDelete           ( struct tTASKCONTROL* record);

int pxCustOrderNumberStartBrowse  ( struct tCUSTOMERORDERNO* record, int browseid);
int pxCustOrderNumberGetNext      ( struct tCUSTOMERORDERNO* record, int browseid);
int pxCustOrderNumberEndBrowse    ( int browseid);
int pxCustOrderNumberRead         ( struct tCUSTOMERORDERNO* record);
int pxCustOrderNumberReadLock     ( struct tCUSTOMERORDERNO* record);
int pxCustOrderNumberUpdate       ( struct tCUSTOMERORDERNO* record);
int pxCustOrderNumberInsert       ( struct tCUSTOMERORDERNO* record);
int pxCustOrderNumberDelete       ( struct tCUSTOMERORDERNO* record);

int pxCustOrderInfoStartBrowse    ( struct tKDAUFTRAGINFO* record, int browseid);
int pxCustOrderInfoGetNext        ( struct tKDAUFTRAGINFO* record, int browseid);
int pxCustOrderInfoEndBrowse      ( int browseid);
int pxCustOrderInfoRead           ( struct tKDAUFTRAGINFO* record);
int pxCustOrderInfoReadLock       ( struct tKDAUFTRAGINFO* record);
int pxCustOrderInfoUpdate         ( struct tKDAUFTRAGINFO* record);
int pxCustOrderInfoInsert         ( struct tKDAUFTRAGINFO* record);
int pxCustOrderInfoDelete         ( struct tKDAUFTRAGINFO* record);

int pxArtikelNummernStartBrowse   ( struct tARTIKELNUMMERN* record,int browseid);
int pxArtikelNummernGetNext       ( struct tARTIKELNUMMERN* record,int browseid);
int pxArtikelNummernEndBrowse     ( int browseid);
int pxArtikelNummernRead          ( struct tARTIKELNUMMERN* record);
int pxArtikelNummernReadLock      ( struct tARTIKELNUMMERN* record);
int pxArtikelNummernUpdate        ( struct tARTIKELNUMMERN* record);
int pxArtikelNummernInsert        ( struct tARTIKELNUMMERN* record);
int pxArtikelNummernDelete        ( struct tARTIKELNUMMERN* record);


int pxCustRoutingStartBrowse      ( struct tCUSTOMERROUTING* record, int browseid);
int pxCustRoutingGetNext          ( struct tCUSTOMERROUTING* record, int browseid);
int pxCustRoutingEndBrowse        ( int browseid);
int pxCustRoutingRead             ( struct tCUSTOMERROUTING* record);
int pxCustRoutingReadLock         ( struct tCUSTOMERROUTING* record);
int pxCustRoutingUpdate           ( struct tCUSTOMERROUTING* record);
int pxCustRoutingInsert           ( struct tCUSTOMERROUTING* record);
int pxCustRoutingDelete           ( struct tCUSTOMERROUTING* record);

int pxCustPharmGroupStartBrowse   ( struct tCUSTOMERPHARMACYGR* record, int browseid);
int pxCustPharmGroupGetNext       ( struct tCUSTOMERPHARMACYGR* record, int browseid);
int pxCustPharmGroupEndBrowse     ( int browseid);
int pxCustPharmGroupRead          ( struct tCUSTOMERPHARMACYGR* record);
int pxCustPharmGroupReadLock      ( struct tCUSTOMERPHARMACYGR* record);
int pxCustPharmGroupUpdate        ( struct tCUSTOMERPHARMACYGR* record);
int pxCustPharmGroupInsert        ( struct tCUSTOMERPHARMACYGR* record);
int pxCustPharmGroupDelete        ( struct tCUSTOMERPHARMACYGR* record);

//int pxValidDiscInfoStartBrowse    ( struct tVALIDDISCOUNTINFO* record, int browseid, long CustomerNo);
//int pxValidDiscInfoGetNext        ( struct tVALIDDISCOUNTINFO* record, int browseid);
//int pxValidDiscInfoEndBrowse      ( int browseid);
//int pxValidDiscInfoRead           ( struct tVALIDDISCOUNTINFO* record);
//int pxValidDiscInfoReadLock       ( struct tVALIDDISCOUNTINFO* record);
//int pxValidDiscInfoUpdate         ( struct tVALIDDISCOUNTINFO* record);
//int pxValidDiscInfoInsert         ( struct tVALIDDISCOUNTINFO* record);
//int pxValidDiscInfoDelete         ( struct tVALIDDISCOUNTINFO* record);

int pxStockEntryStartBrowse       ( struct tSTOCKENTRY* record, int browseid);
int pxStockEntryGetNext           ( struct tSTOCKENTRY* record, int browseid);
int pxStockEntryEndBrowse         ( int browseid);
int pxStockEntryRead              ( struct tSTOCKENTRY* record);
int pxStockEntryReadLock          ( struct tSTOCKENTRY* record);
int pxStockEntryUpdate            ( struct tSTOCKENTRY* record);
int pxStockEntryInsert            ( struct tSTOCKENTRY* record);
int pxStockEntryDelete            ( struct tSTOCKENTRY* record);

int pxDebitLimitStartBrowse       ( struct tDEBTLIMIT* record, int browseid);
int pxDebitLimitGetNext           ( struct tDEBTLIMIT* record, int browseid);
int pxDebitLimitEndBrowse         ( int browseid);
int pxDebitLimitRead              ( struct tDEBTLIMIT* record);
int pxDebitLimitReadLock          ( struct tDEBTLIMIT* record);
int pxDebitLimitUpdate            ( struct tDEBTLIMIT* record);
int pxDebitLimitInsert            ( struct tDEBTLIMIT* record);
int pxDebitLimitDelete            ( struct tDEBTLIMIT* record);

int pxArticleQuotaStartBrowse     ( struct tARTICLEQUOTA* record, int browseid);
int pxArticleQuotaGetNext         ( struct tARTICLEQUOTA* record, int browseid);
int pxArticleQuotaEndBrowse       ( int browseid);
int pxArticleQuotaRead            ( struct tARTICLEQUOTA* record);
int pxArticleQuotaReadLock        ( struct tARTICLEQUOTA* record);
int pxArticleQuotaUpdate          ( struct tARTICLEQUOTA* record);
int pxArticleQuotaInsert          ( struct tARTICLEQUOTA* record);
int pxArticleQuotaDelete          ( struct tARTICLEQUOTA* record);

int pxParameterStartBrowse        ( struct tPARAMETER* record, int browseid);
int pxParameterGetNext            ( struct tPARAMETER* record, int browseid);
int pxParameterEndBrowse          ( int browseid);
int pxParameterRead               ( struct tPARAMETER* record);
int pxParameterReadLock           ( struct tPARAMETER* record);
int pxParameterUpdate             ( struct tPARAMETER* record);
int pxParameterInsert             ( struct tPARAMETER* record);
int pxParameterDelete             ( struct tPARAMETER* record);

int pxArticleTextStartBrowse      ( struct tARTICLETEXT* record, int browseid);
int pxArticleTextGetNext          ( struct tARTICLETEXT* record, int browseid);
int pxArticleTextEndBrowse        ( int browseid);
int pxArticleTextRead             ( struct tARTICLETEXT* record);
int pxArticleTextReadLock         ( struct tARTICLETEXT* record);
int pxArticleTextUpdate           ( struct tARTICLETEXT* record);
int pxArticleTextInsert           ( struct tARTICLETEXT* record);
int pxArticleTextDelete           ( struct tARTICLETEXT* record);

int pxCustDelDeliveryStartBrowse  ( struct tDELAYEDDELIVERYCST* record, int browseid);
int pxCustDelDeliveryGetNext      ( struct tDELAYEDDELIVERYCST* record, int browseid);
int pxCustDelDeliveryEndBrowse    ( int browseid);
int pxCustDelDeliveryRead         ( struct tDELAYEDDELIVERYCST* record);
int pxCustDelDeliveryReadLock     ( struct tDELAYEDDELIVERYCST* record);
int pxCustDelDeliveryUpdate       ( struct tDELAYEDDELIVERYCST* record);
int pxCustDelDeliveryInsert       ( struct tDELAYEDDELIVERYCST* record);
int pxCustDelDeliveryDelete       ( struct tDELAYEDDELIVERYCST* record);

int pxHoliDayStartBrowse          ( struct tFEIERTAG* record, int browseid);
int pxHoliDayGetNext              ( struct tFEIERTAG* record, int browseid);
int pxHoliDayEndBrowse            ( int browseid);
int pxHoliDayRead                 ( struct tFEIERTAG* record);
int pxHoliDayReadLock             ( struct tFEIERTAG* record);
int pxHoliDayUpdate               ( struct tFEIERTAG* record);
int pxHoliDayInsert               ( struct tFEIERTAG* record);
int pxHoliDayDelete               ( struct tFEIERTAG* record);

int pxDiscountStartBrowse         ( struct tDISCOUNT* record, int browseid);
int pxDiscountGetNext             ( struct tDISCOUNT* record, int browseid);
int pxDiscountEndBrowse           ( int browseid);
int pxDiscountRead                ( struct tDISCOUNT* record);


int pxArtReservationStartBrowse   ( struct tARTICLERESERVATION* record, int browseid);
int pxArtReservationGetNext       ( struct tARTICLERESERVATION* record, int browseid);
int pxArtReservationEndBrowse     ( int browseid);
int pxArtReservationRead          ( struct tARTICLERESERVATION* record);
int pxArtReservationReadLock      ( struct tARTICLERESERVATION* record);
int pxArtReservationUpdate        ( struct tARTICLERESERVATION* record);
int pxArtReservationInsert        ( struct tARTICLERESERVATION* record);
int pxArtReservationDelete        ( struct tARTICLERESERVATION* record);

int pxItemDiscountStartBrowse     ( struct tKDAUFTRAGPOSRAB* record, int browseid);
int pxItemDiscountGetNext         ( struct tKDAUFTRAGPOSRAB* record, int browseid);
int pxItemDiscountEndBrowse       ( int browseid);
int pxItemDiscountRead            ( struct tKDAUFTRAGPOSRAB* record);
int pxItemDiscountReadLock        ( struct tKDAUFTRAGPOSRAB* record);
int pxItemDiscountUpdate          ( struct tKDAUFTRAGPOSRAB* record);
int pxItemDiscountInsert          ( struct tKDAUFTRAGPOSRAB* record);
int pxItemDiscountDelete          ( struct tKDAUFTRAGPOSRAB* record);

int pxRangeStartBrowse            ( struct tDISCOUNTGRP* record, int browseid);
int pxRangeGetNext                ( struct tDISCOUNTGRP* record, int browseid);
int pxRangeEndBrowse              ( int browseid);
int pxRangeRead                   ( struct tDISCOUNTGRP* record);

int pxRangeMemberStartBrowse      ( struct tDISCOUNTGRPMEM* record, int browseid);
int pxRangeMemberGetNext          ( struct tDISCOUNTGRPMEM* record, int browseid);
int pxRangeMemberEndBrowse        ( int browseid);
int pxRangeMemberRead             ( struct tDISCOUNTGRPMEM* record);

int pxDiscountOrdTypStartBrowse   ( struct tDISCOUNTORDERTYP* record, int browseid);
int pxDiscountOrdTypGetNext       ( struct tDISCOUNTORDERTYP* record, int browseid);
int pxDiscountOrdTypEndBrowse     ( int browseid);
int pxDiscountOrdTypRead          ( struct tDISCOUNTORDERTYP* record);

int pxNarcTransferStartBrowse    ( struct tNARCTRANSACTIONTRANSFER* position, int browseid);
int pxNarcTransferGetNext        ( struct tNARCTRANSACTIONTRANSFER* position, int browseid);
int pxNarcTransferEndBrowse      ( int browseid);
int pxNarcTransferRead           ( struct tNARCTRANSACTIONTRANSFER* position);
int pxNarcTransferReadLock       ( struct tNARCTRANSACTIONTRANSFER* position);
int pxNarcTransferUpdate         ( struct tNARCTRANSACTIONTRANSFER* record);
int pxNarcTransferInsert         ( struct tNARCTRANSACTIONTRANSFER* position);
int pxNarcTransferDelete         ( struct tNARCTRANSACTIONTRANSFER* position);

int pxPosParkingStartBrowse      ( struct tPOSITIONPARKING* record, int browseid);
int pxPosParkingGetNext          ( struct tPOSITIONPARKING* record, int browseid);
int pxPosParkingEndBrowse        ( int browseid);
int pxPosParkingRead             ( struct tPOSITIONPARKING* record);
int pxPosParkingReadLock         ( struct tPOSITIONPARKING* record);
int pxPosParkingUpdate           ( struct tPOSITIONPARKING* record);
int pxPosParkingInsert           ( struct tPOSITIONPARKING* record);
int pxPosParkingDelete           ( struct tPOSITIONPARKING* record);


int pxArtPackUnitStartBrowse     ( struct tARTICLEPACKUNIT* record, int browseid);
int pxArtPackUnitGetNext         ( struct tARTICLEPACKUNIT* record, int browseid);
int pxArtPackUnitEndBrowse       ( int browseid);

int pxTourPlanTagWocheStartBrowse( struct tTOURPLANTAGWOCHE* record, int browseid);
int pxTourPlanTagWocheGetNext    ( struct tTOURPLANTAGWOCHE* record, int browseid);
int pxTourPlanTagWocheEndBrowse  ( int browseid);

int pxTourConsTimeStartBrowse    ( struct tTOURCONSTIME* record, int browseid);
int pxTourConsTimeGetNext        ( struct tTOURCONSTIME* record, int browseid);
int pxTourConsTimeEndBrowse      ( int browseid);
int pxTourConsTimeRead           ( struct tTOURCONSTIME* record);
int pxTourConsTimeReadLock       ( struct tTOURCONSTIME* record);
int pxTourConsTimeUpdate         ( struct tTOURCONSTIME* record);
int pxTourConsTimeInsert         ( struct tTOURCONSTIME* record);
int pxTourConsTimeDelete         ( struct tTOURCONSTIME* record);

int pxTourPlanConsTimeStartBrowse( struct tTOURPLANCONSTIME* record, int browseid);
int pxTourPlanConsTimeGetNext    ( struct tTOURPLANCONSTIME* record, int browseid);
int pxTourPlanConsTimeEndBrowse  ( int browseid);
int pxTourPlanConsTimeRead       ( struct tTOURPLANCONSTIME* record);
int pxTourPlanConsTimeReadLock   ( struct tTOURPLANCONSTIME* record);
int pxTourPlanConsTimeUpdate     ( struct tTOURPLANCONSTIME* record);
int pxTourPlanConsTimeInsert     ( struct tTOURPLANCONSTIME* record);
int pxTourPlanConsTimeDelete     ( struct tTOURPLANCONSTIME* record);

int pxTourPlanWocheStartBrowse   ( struct tTOURPLANWOCHE* record, int browseid);
int pxTourPlanWocheGetNext       ( struct tTOURPLANWOCHE* record, int browseid);
int pxTourPlanWocheEndBrowse     ( int browseid);
int pxTourPlanWocheRead          ( struct tTOURPLANWOCHE* record);
int pxTourPlanWocheReadLock      ( struct tTOURPLANWOCHE* record);
int pxTourPlanWocheUpdate        ( struct tTOURPLANWOCHE* record);
int pxTourPlanWocheInsert        ( struct tTOURPLANWOCHE* record);
int pxTourPlanWocheDelete        ( struct tTOURPLANWOCHE* record);

int pxSubOrderTypeRead              ( struct tDISCOUNTLIST* record);
int pxSubOrderTypeReadLock          ( struct tDISCOUNTLIST* record);

int pxCustDiscConditionStartBrowse  ( struct tCSTDISCOUNTCONT* record, int browseid);
int pxCustDiscConditionGetNext      ( struct tCSTDISCOUNTCONT* record, int browseid);
int pxCustDiscConditionEndBrowse    ( int browseid);
int pxCustDiscConditionRead         ( struct tCSTDISCOUNTCONT* record);
int pxCustDiscConditionReadLock     ( struct tCSTDISCOUNTCONT* record);


int pxTaxRatesStartBrowse           ( struct tTAXRATES* record, int browseid);
int pxTaxRatesGetNext               ( struct tTAXRATES* record, int browseid);
int pxTaxRatesEndBrowse             ( int browseid);

int pxSepOrderArtGroupStartBrowse   ( struct tSEPORDERARTGRP* record, int browseid);
int pxSepOrderArtGroupGetNext       ( struct tSEPORDERARTGRP* record, int browseid);
int pxSepOrderArtGroupEndBrowse     ( int browseid);

int pxArtOldPriceStartBrowse        ( struct tARTICLEOLDPRICE* preis, int browseid);
int pxArtOldPriceGetNext            ( struct tARTICLEOLDPRICE* preis, int browseid);
int pxArtOldPriceEndBrowse          ( int browseid);
int pxArtOldPriceRead               ( struct tARTICLEOLDPRICE* preis);
int pxArtOldPriceReadLock           ( struct tARTICLEOLDPRICE* preis);
int pxArtOldPriceUpdate             ( struct tARTICLEOLDPRICE* preis);
int pxArtOldPriceInsert             ( struct tARTICLEOLDPRICE* preis);
int pxArtOldPriceDelete             ( struct tARTICLEOLDPRICE* preis);

int pxCountryCodesStartBrowse       ( struct tCOUNTRYCODES* record, int browseid);
int pxCountryCodesGetNext           ( struct tCOUNTRYCODES* record, int browseid);
int pxCountryCodesEndBrowse         ( int browseid);
int pxCountryCodesRead              ( struct tCOUNTRYCODES* record);
int pxCountryCodesReadLock          ( struct tCOUNTRYCODES* record);
int pxCountryCodesUpdate            ( struct tCOUNTRYCODES* record);
int pxCountryCodesInsert            ( struct tCOUNTRYCODES* record);
int pxCountryCodesDelete            ( struct tCOUNTRYCODES* record);

int pxArticleLpprStartBrowse        ( struct tARTICLELPPR* preis, int browseid);
int pxArticleLpprGetNext            ( struct tARTICLELPPR* preis, int browseid);
int pxArticleLpprEndBrowse          ( int browseid);
int pxArticleLpprRead               ( struct tARTICLELPPR* preis);
int pxArticleLpprReadLock           ( struct tARTICLELPPR* preis);
int pxArticleLpprUpdate             ( struct tARTICLELPPR* preis);
int pxArticleLpprInsert             ( struct tARTICLELPPR* preis);
int pxArticleLpprDelete             ( struct tARTICLELPPR* preis);

int pxOrderCriteriaStartBrowse      ( struct tORDERCRITERIA* record, int browseid);
int pxOrderCriteriaGetNext          ( struct tORDERCRITERIA* record, int browseid);
int pxOrderCriteriaEndBrowse        ( int browseid);
int pxOrderCriteriaRead             ( struct tORDERCRITERIA* record);

int pxCustBaseInformationRead       ( struct tKNDAUSKU* record);
int pxCustBaseInformationReadLock   ( struct tKNDAUSKU* record);

int pxCstSepOrdArtGrpStartBrowse  ( struct tCSTSEPORDERARTGRP* record, int browseid);
int pxCstSepOrdArtGrpGetNext      ( struct tCSTSEPORDERARTGRP* record, int browseid);
int pxCstSepOrdArtGrpEndBrowse    ( int browseid);


int pxArticleGrpStartBrowse       ( struct tARTICLEGROUP* record,int browseid);
int pxArticleGrpGetNext           ( struct tARTICLEGROUP* record,int browseid);
int pxArticleGrpEndBrowse         ( int browseid);
int pxArticleGrpRead              ( struct tARTICLEGROUP* record);
int pxArticleGrpReadLock          ( struct tARTICLEGROUP* record);
int pxArticleGrpUpdate            ( struct tARTICLEGROUP* record);
int pxArticleGrpInsert            ( struct tARTICLEGROUP* record);
int pxArticleGrpDelete            ( struct tARTICLEGROUP* record);

int pxArtComPackStartBrowse       ( struct tARTCOMPACK* record, int browseid);
int pxArtComPackGetNext           ( struct tARTCOMPACK* record, int browseid);
int pxArtComPackEndBrowse         ( int browseid);

int pxCstDiscAccStartBrowse       ( struct tCSTDISCACC* record, int browseid, long DateTo);
int pxCstDiscAccGetNext           ( struct tCSTDISCACC* record, int browseid);
int pxCstDiscAccEndBrowse         ( int browseid);
int pxCstDiscAccRead              ( struct tCSTDISCACC* record);
int pxCstDiscAccReadLock          ( struct tCSTDISCACC* record);
int pxCstDiscAccUpdate            ( struct tCSTDISCACC* record);
int pxCstDiscAccInsert            ( struct tCSTDISCACC* record);
int pxCstDiscAccDelete            ( struct tCSTDISCACC* record);

int pxDealerVolumeStartBrowse     ( struct tDEALERVOLUME* record, int browseid);
int pxDealerVolumeGetNext         ( struct tDEALERVOLUME* record, int browseid);
int pxDealerVolumeEndBrowse       ( int browseid);
int pxDealerVolumeRead            ( struct tDEALERVOLUME* record);
int pxDealerVolumeReadLock        ( struct tDEALERVOLUME* record);
int pxDealerVolumeUpdate          ( struct tDEALERVOLUME* record);
int pxDealerVolumeInsert          ( struct tDEALERVOLUME* record);
int pxDealerVolumeDelete          ( struct tDEALERVOLUME* record);

int pxCPValidityPeriodStartBrowse ( struct tCPVALIDITYPERIOD* record, int browseid);
int pxCPValidityPeriodGetNext     ( struct tCPVALIDITYPERIOD* record, int browseid);
int pxCPValidityPeriodEndBrowse   ( int browseid);

int pxTenderHeadStartBrowse       ( struct tTENDERHEAD* record, int browseid);
int pxTenderHeadGetNext           ( struct tTENDERHEAD* record, int browseid);
int pxTenderHeadEndBrowse         ( int browseid);
int pxTenderHeadRead              ( struct tTENDERHEAD* record);
int pxTenderHeadReadLock          ( struct tTENDERHEAD* record);
int pxTenderHeadUpdate            ( struct tTENDERHEAD* record);
int pxTenderHeadInsert            ( struct tTENDERHEAD* record);
int pxTenderHeadDelete            ( struct tTENDERHEAD* record);

int pxTenderPosStartBrowse        ( struct tTENDERPOS* record, int browseid);
int pxTenderPosGetNext            ( struct tTENDERPOS* record, int browseid);
int pxTenderPosEndBrowse          ( int browseid);
int pxTenderPosRead               ( struct tTENDERPOS* record);
int pxTenderPosReadLock           ( struct tTENDERPOS* record);
int pxTenderPosUpdate             ( struct tTENDERPOS* record);
int pxTenderPosInsert             ( struct tTENDERPOS* record);
int pxTenderPosDelete             ( struct tTENDERPOS* record);

int pxTenderProgressStartBrowse   ( struct tTENDERPROGRESS* record, int browseid);
int pxTenderProgressGetNext       ( struct tTENDERPROGRESS* record, int browseid);
int pxTenderProgressEndBrowse     ( int browseid);
int pxTenderProgressRead          ( struct tTENDERPROGRESS* record);
int pxTenderProgressReadLock      ( struct tTENDERPROGRESS* record);
int pxTenderProgressUpdate        ( struct tTENDERPROGRESS* record);
int pxTenderProgressInsert        ( struct tTENDERPROGRESS* record);
int pxTenderProgressDelete        ( struct tTENDERPROGRESS* record);

int pxArMasterFrStartBrowse       ( struct tMARTIKELFR* record, int browseid);
int pxArMasterFrGetNext           ( struct tMARTIKELFR* record, int browseid);
int pxArMasterFrEndBrowse         ( int browseid);
int pxArMasterFrRead              ( struct tMARTIKELFR* record);
int pxArMasterFrReadLock          ( struct tMARTIKELFR* record);
int pxArMasterFrUpdate            ( struct tMARTIKELFR* record);
int pxArMasterFrInsert            ( struct tMARTIKELFR* record);
int pxArMasterFrDelete            ( struct tMARTIKELFR* record);

int pxOrderDiscAccStartBrowse     ( struct tKDAUFTRAGDISCACC* record, int browseid);
int pxOrderDiscAccGetNext         ( struct tKDAUFTRAGDISCACC* record, int browseid);
int pxOrderDiscAccEndBrowse       ( int browseid);
int pxOrderDiscAccRead            ( struct tKDAUFTRAGDISCACC* record);
int pxOrderDiscAccReadLock        ( struct tKDAUFTRAGDISCACC* record);
int pxOrderDiscAccUpdate          ( struct tKDAUFTRAGDISCACC* record);
int pxOrderDiscAccInsert          ( struct tKDAUFTRAGDISCACC* record);
int pxOrderDiscAccDelete          ( struct tKDAUFTRAGDISCACC* record);

int pxArtSpecialCondStartBrowse   ( struct tARTSPECIALCOND* record, int browseid);
int pxArtSpecialCondGetNext       ( struct tARTSPECIALCOND* record, int browseid);
int pxArtSpecialCondEndBrowse     ( int browseid);
int pxArtSpecialCondRead          ( struct tARTSPECIALCOND* record);
int pxArtSpecialCondReadLock      ( struct tARTSPECIALCOND* record);
int pxArtSpecialCondUpdate        ( struct tARTSPECIALCOND* record);
int pxArtSpecialCondInsert        ( struct tARTSPECIALCOND* record);
int pxArtSpecialCondDelete        ( struct tARTSPECIALCOND* record);

int pxPromotionsStartBrowse       ( struct tPROMOTIONS* record, int browseid);
int pxPromotionsGetNext           ( struct tPROMOTIONS* record, int browseid);
int pxPromotionsEndBrowse         ( int browseid);
int pxPromotionsRead              ( struct tPROMOTIONS* record);
int pxPromotionsReadLock          ( struct tPROMOTIONS* record);
int pxPromotionsUpdate            ( struct tPROMOTIONS* record);
int pxPromotionsInsert            ( struct tPROMOTIONS* record);
int pxPromotionsDelete            ( struct tPROMOTIONS* record);

int pxCstPaymentTermsStartBrowse  ( struct tCSTPAYMENTTERMS* record, int browseid);
int pxCstPaymentTermsGetNext      ( struct tCSTPAYMENTTERMS* record, int browseid);
int pxCstPaymentTermsEndBrowse    ( int browseid);
int pxCstPaymentTermsRead         ( struct tCSTPAYMENTTERMS* record);
int pxCstPaymentTermsReadLock     ( struct tCSTPAYMENTTERMS* record);
int pxCstPaymentTermsUpdate       ( struct tCSTPAYMENTTERMS* record);
int pxCstPaymentTermsInsert       ( struct tCSTPAYMENTTERMS* record);
int pxCstPaymentTermsDelete       ( struct tCSTPAYMENTTERMS* record);

int pxOrderValuesStartBrowse      ( struct tKDAUFTRAGWERTE* record, int browseid);
int pxOrderValuesGetNext          ( struct tKDAUFTRAGWERTE* record, int browseid);
int pxOrderValuesEndBrowse        ( int browseid);
int pxOrderValuesRead             ( struct tKDAUFTRAGWERTE* record);
int pxOrderValuesReadLock         ( struct tKDAUFTRAGWERTE* record);
int pxOrderValuesUpdate           ( struct tKDAUFTRAGWERTE* record);
int pxOrderValuesInsert           ( struct tKDAUFTRAGWERTE* record);
int pxOrderValuesDelete           ( struct tKDAUFTRAGWERTE* record);

int pxItemChargeStartBrowse       ( struct tKDAUFTRAGPOSCHARGE* record, int browseid);
int pxItemChargeGetNext           ( struct tKDAUFTRAGPOSCHARGE* record, int browseid);
int pxItemChargeEndBrowse         ( int browseid);
int pxItemChargeRead              ( struct tKDAUFTRAGPOSCHARGE* record);
int pxItemChargeReadLock          ( struct tKDAUFTRAGPOSCHARGE* record);
int pxItemChargeUpdate            ( struct tKDAUFTRAGPOSCHARGE* record);
int pxItemChargeInsert            ( struct tKDAUFTRAGPOSCHARGE* record);
int pxItemChargeDelete            ( struct tKDAUFTRAGPOSCHARGE* record);

int pxArticleChargeStartBrowse    ( struct tARTICLECHARGE* record, int browseid);
int pxArticleChargeGetNext        ( struct tARTICLECHARGE* record, int browseid);
int pxArticleChargeEndBrowse      ( int browseid);
int pxArticleChargeRead           ( struct tARTICLECHARGE*  record);
int pxArticleChargeReadLock       ( struct tARTICLECHARGE*  record);
int pxArticleChargeUpdate         ( struct tARTICLECHARGE*  record);
int pxArticleChargeInsert         ( struct tARTICLECHARGE*  record);
int pxArticleChargeDelete         ( struct tARTICLECHARGE*  record);

int pxOrderCalcModeStartBrowse    ( struct tKDAUFTRAGRECHART* record, int browseid);
int pxOrderCalcModeGetNext        ( struct tKDAUFTRAGRECHART* record, int browseid);
int pxOrderCalcModeEndBrowse      ( int browseid);
int pxOrderCalcModeRead           ( struct tKDAUFTRAGRECHART* record);
int pxOrderCalcModeReadLock       ( struct tKDAUFTRAGRECHART* record);
int pxOrderCalcModeUpdate         ( struct tKDAUFTRAGRECHART* record);
int pxOrderCalcModeInsert         ( struct tKDAUFTRAGRECHART* record);
int pxOrderCalcModeDelete         ( struct tKDAUFTRAGRECHART* record);

int pxOrderPosCalcModeStartBrowse ( struct tKDAUFTRPOSRECHART* record, int browseid);
int pxOrderPosCalcModeGetNext     ( struct tKDAUFTRPOSRECHART* record, int browseid);
int pxOrderPosCalcModeEndBrowse   ( int browseid);
int pxOrderPosCalcModeRead        ( struct tKDAUFTRPOSRECHART* record);
int pxOrderPosCalcModeReadLock    ( struct tKDAUFTRPOSRECHART* record);
int pxOrderPosCalcModeUpdate      ( struct tKDAUFTRPOSRECHART* record);
int pxOrderPosCalcModeInsert      ( struct tKDAUFTRPOSRECHART* record);
int pxOrderPosCalcModeDelete      ( struct tKDAUFTRPOSRECHART* record);

int pxGeneralCalcAvpStartBrowse   ( struct tGENERALCALCAVP* record, int browseid);
int pxGeneralCalcAvpGetNext       ( struct tGENERALCALCAVP* record, int browseid);
int pxGeneralCalcAvpEndBrowse     ( int browseid);
int pxGeneralCalcAvpRead          ( struct tGENERALCALCAVP* record);
int pxGeneralCalcAvpReadLock      ( struct tGENERALCALCAVP* record);
int pxGeneralCalcAvpUpdate        ( struct tGENERALCALCAVP* record);
int pxGeneralCalcAvpInsert        ( struct tGENERALCALCAVP* record);
int pxGeneralCalcAvpDelete        ( struct tGENERALCALCAVP* record);

int pxCstCalcAvpStartBrowse       ( struct tCSTCALCAVP* record, int browseid);
int pxCstCalcAvpGetNext           ( struct tCSTCALCAVP* record, int browseid);
int pxCstCalcAvpEndBrowse         ( int browseid);
int pxCstCalcAvpRead              ( struct tCSTCALCAVP* record);
int pxCstCalcAvpReadLock          ( struct tCSTCALCAVP* record);
int pxCstCalcAvpUpdate            ( struct tCSTCALCAVP* record);
int pxCstCalcAvpInsert            ( struct tCSTCALCAVP* record);
int pxCstCalcAvpDelete            ( struct tCSTCALCAVP* record);

int pxCstPrintStartBrowse         ( struct tCSTPRINT* record, int browseid);
int pxCstPrintGetNext             ( struct tCSTPRINT* record, int browseid);
int pxCstPrintEndBrowse           ( int browseid);
int pxCstPrintRead                ( struct tCSTPRINT* record);
int pxCstPrintReadLock            ( struct tCSTPRINT* record);
int pxCstPrintUpdate              ( struct tCSTPRINT* record);
int pxCstPrintInsert              ( struct tCSTPRINT* record);
int pxCstPrintDelete              ( struct tCSTPRINT* record);

int pxTaxTabStartBrowse         ( struct tTAXTAB* record, int browseid);
int pxTaxTabGetNext             ( struct tTAXTAB* record, int browseid);
int pxTaxTabEndBrowse           ( int browseid);
int pxTaxTabRead                ( struct tTAXTAB* record);
int pxTaxTabReadLock            ( struct tTAXTAB* record);
int pxTaxTabUpdate              ( struct tTAXTAB* record);
int pxTaxTabInsert              ( struct tTAXTAB* record);
int pxTaxTabDelete              ( struct tTAXTAB* record);


int pxKdAuftragPosRefundStartBrowse    ( struct tKDAUFTRAGPOSREFUND* record, int browseid);
int pxKdAuftragPosRefundGetNext        ( struct tKDAUFTRAGPOSREFUND* record, int browseid);
int pxKdAuftragPosRefundEndBrowse      ( int browseid);
int pxKdAuftragPosRefundRead           ( struct tKDAUFTRAGPOSREFUND* record);
int pxKdAuftragPosRefundReadLock       ( struct tKDAUFTRAGPOSREFUND* record);
int pxKdAuftragPosRefundUpdate         ( struct tKDAUFTRAGPOSREFUND* record);
int pxKdAuftragPosRefundInsert         ( struct tKDAUFTRAGPOSREFUND* record);
int pxKdAuftragPosRefundDelete         ( struct tKDAUFTRAGPOSREFUND* record);

int pxOrderPosPromoStartBrowse         ( struct tKDAUFTRAGPOSPROMO* record, int browseid);
int pxOrderPosPromoGetNext             ( struct tKDAUFTRAGPOSPROMO* record, int browseid);
int pxOrderPosPromoEndBrowse           ( int browseid);
int pxOrderPosPromoRead                ( struct tKDAUFTRAGPOSPROMO* record);
int pxOrderPosPromoReadLock            ( struct tKDAUFTRAGPOSPROMO* record);
int pxOrderPosPromoUpdate              ( struct tKDAUFTRAGPOSPROMO* record);
int pxOrderPosPromoInsert              ( struct tKDAUFTRAGPOSPROMO* record);
int pxOrderPosPromoDelete              ( struct tKDAUFTRAGPOSPROMO* record);

int pxOrderPosChangeStartBrowse        ( struct tKDAUFTRAGPOSCHANGE* record, int browseid);
int pxOrderPosChangeGetNext            ( struct tKDAUFTRAGPOSCHANGE* record, int browseid);
int pxOrderPosChangeEndBrowse          ( int browseid);
int pxOrderPosChangeRead               ( struct tKDAUFTRAGPOSCHANGE* record);
int pxOrderPosChangeReadLock           ( struct tKDAUFTRAGPOSCHANGE* record);
int pxOrderPosChangeUpdate             ( struct tKDAUFTRAGPOSCHANGE* record);
int pxOrderPosChangeInsert             ( struct tKDAUFTRAGPOSCHANGE* record);
int pxOrderPosChangeDelete             ( struct tKDAUFTRAGPOSCHANGE* record);

int pxArticleCodesStartBrowse          ( struct tARTICLECODES* record, int browseid);
int pxArticleCodesGetNext              ( struct tARTICLECODES* record, int browseid);
int pxArticleCodesEndBrowse            ( int browseid);
int pxArticleCodesRead                 ( struct tARTICLECODES* record);
int pxArticleCodesReadLock             ( struct tARTICLECODES* record);
int pxArticleCodesUpdate               ( struct tARTICLECODES* record);
int pxArticleCodesInsert               ( struct tARTICLECODES* record);
int pxArticleCodesDelete               ( struct tARTICLECODES* record);

int pxOrderProLinkStartBrowse          ( struct tKDAUFTRAGPROLINK* record, int browseid);
int pxOrderProLinkGetNext              ( struct tKDAUFTRAGPROLINK* record, int browseid);
int pxOrderProLinkEndBrowse            ( int browseid);
int pxOrderProLinkRead                 ( struct tKDAUFTRAGPROLINK* record);
int pxOrderProLinkReadLock             ( struct tKDAUFTRAGPROLINK* record);
int pxOrderProLinkUpdate               ( struct tKDAUFTRAGPROLINK* record);
int pxOrderProLinkInsert               ( struct tKDAUFTRAGPROLINK* record);
int pxOrderProLinkDelete               ( struct tKDAUFTRAGPROLINK* record);

int pxTenderCustomerStartBrowse        ( struct tTENDERCUSTOMER* record, int browseid);
int pxTenderCustomerGetNext            ( struct tTENDERCUSTOMER* record, int browseid);
int pxTenderCustomerEndBrowse          ( int browseid);
int pxTenderCustomerRead               ( struct tTENDERCUSTOMER* record);
int pxTenderCustomerReadLock           ( struct tTENDERCUSTOMER* record);
int pxTenderCustomerUpdate             ( struct tTENDERCUSTOMER* record);
int pxTenderCustomerInsert             ( struct tTENDERCUSTOMER* record);
int pxTenderCustomerDelete             ( struct tTENDERCUSTOMER* record);

int pxEncloserScaleStartBrowse         ( struct tENCLOSERSCALE* record, int browseid);
int pxEncloserScaleGetNext             ( struct tENCLOSERSCALE* record, int browseid);
int pxEncloserScaleEndBrowse           ( int browseid);
int pxEncloserScaleRead                ( struct tENCLOSERSCALE* record);
int pxEncloserScaleReadLock            ( struct tENCLOSERSCALE* record);
int pxEncloserScaleUpdate              ( struct tENCLOSERSCALE* record);
int pxEncloserScaleInsert              ( struct tENCLOSERSCALE* record);
int pxEncloserScaleDelete              ( struct tENCLOSERSCALE* record);

int pxPromotionQuotaStartBrowse        ( struct tPROMOTIONQUOTA* record, int browseid);
int pxPromotionQuotaGetNext            ( struct tPROMOTIONQUOTA* record, int browseid);
int pxPromotionQuotaEndBrowse          ( int browseid);
int pxPromotionQuotaRead               ( struct tPROMOTIONQUOTA* record);
int pxPromotionQuotaReadLock           ( struct tPROMOTIONQUOTA* record);
int pxPromotionQuotaUpdate             ( struct tPROMOTIONQUOTA* record);
int pxPromotionQuotaInsert             ( struct tPROMOTIONQUOTA* record);
int pxPromotionQuotaDelete             ( struct tPROMOTIONQUOTA* record);

int pxPromotionQuotaCstStartBrowse     ( struct tPROMOTIONQUOTACST* record, int browseid);
int pxPromotionQuotaCstGetNext         ( struct tPROMOTIONQUOTACST* record, int browseid);
int pxPromotionQuotaCstEndBrowse       ( int browseid);
int pxPromotionQuotaCstRead            ( struct tPROMOTIONQUOTACST* record);
int pxPromotionQuotaCstReadLock        ( struct tPROMOTIONQUOTACST* record);
int pxPromotionQuotaCstUpdate          ( struct tPROMOTIONQUOTACST* record);
int pxPromotionQuotaCstInsert          ( struct tPROMOTIONQUOTACST* record);
int pxPromotionQuotaCstDelete          ( struct tPROMOTIONQUOTACST* record);

int pxCustomerSurchargeStartBrowse     ( struct tCUSTOMERSURCHARGE* record, int browseid);
int pxCustomerSurchargeGetNext         ( struct tCUSTOMERSURCHARGE* record, int browseid);
int pxCustomerSurchargeEndBrowse       ( int browseid);
int pxCustomerSurchargeRead            ( struct tCUSTOMERSURCHARGE* record);
int pxCustomerSurchargeReadLock        ( struct tCUSTOMERSURCHARGE* record);
int pxCustomerSurchargeUpdate          ( struct tCUSTOMERSURCHARGE* record);
int pxCustomerSurchargeInsert          ( struct tCUSTOMERSURCHARGE* record);
int pxCustomerSurchargeDelete          ( struct tCUSTOMERSURCHARGE* record);

int pxVartikelLokalStartBrowse         ( struct tVARTIKELLOKAL* record, short timecheck, short useview, short weekday, long currenttime, int browseid);
int pxVartikelLokalGetNext             ( struct tVARTIKELLOKAL* record, int browseid);
int pxVartikelLokalEndBrowse           ( int browseid);

int pxManufacturerGroupStartBrowse     ( struct tMANUFACTURERGROUP* record,int browseid,short VzNr,long CustomerNo);
int pxManufacturerGroupGetNext         ( struct tMANUFACTURERGROUP* record,int browseid);
int pxManufacturerGroupEndBrowse       ( int browseid);
int pxManufacturerGroupRead            ( struct tMANUFACTURERGROUP* record);

int pxCremaMailStartBrowse            ( struct tCREMAMAIL* record, int browseid);
int pxCremaMailGetNext                ( struct tCREMAMAIL* record, int browseid);
int pxCremaMailEndBrowse              ( int browseid);
int pxCremaMailInsert                 ( struct tCREMAMAIL* record);
int pxCremaMailDelete                 ( struct tCREMAMAIL* record);

int pxKdauftragDebtRelStartBrowse      ( struct tKDAUFTRAGDEBTREL* record, int browseid);
int pxKdauftragDebtRelGetNext          ( struct tKDAUFTRAGDEBTREL* record, int browseid);
int pxKdauftragDebtRelEndBrowse        ( int browseid);
int pxKdauftragDebtRelRead             ( struct tKDAUFTRAGDEBTREL* record);
int pxKdauftragDebtRelReadLock         ( struct tKDAUFTRAGDEBTREL* record);
int pxKdauftragDebtRelUpdate           ( struct tKDAUFTRAGDEBTREL* record);
int pxKdauftragDebtRelInsert           ( struct tKDAUFTRAGDEBTREL* record);
int pxKdauftragDebtRelDelete           ( struct tKDAUFTRAGDEBTREL* record);

int pxMSV3OrderStartBrowse            ( struct tKDAUFTRAG* record, int browseid);
int pxMSV3OrderGetNext                ( struct tKDAUFTRAG* record, int browseid);
int pxMSV3OrderEndBrowse              ( int browseid);

int pxPromotionScaleStartBrowse        ( struct tPROMOTIONSCALE* record, int browseid);
int pxPromotionScaleGetNext            ( struct tPROMOTIONSCALE* record, int browseid);
int pxPromotionScaleEndBrowse          ( int browseid);
int pxPromotionScaleRead               ( struct tPROMOTIONSCALE* record);
int pxPromotionScaleReadLock           ( struct tPROMOTIONSCALE* record);
int pxPromotionScaleUpdate             ( struct tPROMOTIONSCALE* record);
int pxPromotionScaleInsert             ( struct tPROMOTIONSCALE* record);
int pxPromotionScaleDelete             ( struct tPROMOTIONSCALE* record);

int pxOrderRemarkTypesStartBrowse     ( struct tORDERREMARKTYPES* record, int browseid );
int pxOrderRemarkTypesGetNext         ( struct tORDERREMARKTYPES* record, int browseid );
int pxOrderRemarkTypesEndBrowse       ( int browseid );
int pxOrderRemarkTypesRead            ( struct tORDERREMARKTYPES* record );
int pxOrderRemarkTypesInsert          ( struct tORDERREMARKTYPES* record );

int pxGenericOrderRemarkStartBrowse   ( struct tORDERREMARKS* record, int browseid );
int pxGenericOrderRemarkGetNext       ( struct tORDERREMARKS* record, int browseid );
int pxGenericOrderRemarkEndBrowse     ( int browseid );
int pxGenericOrderRemarkRead          ( struct tORDERREMARKS* record );
int pxGenericOrderRemarkInsert        ( struct tORDERREMARKS* record );
int pxGenericOrderRemarkUpdate        ( struct tORDERREMARKS* record );
int pxGenericOrderRemarkDelete        ( struct tORDERREMARKS* record );

int pxCustomerGroupStartBrowse     ( struct tCUSTOMERGROUP* record, int browseid);
int pxCustomerGroupGetNext         ( struct tCUSTOMERGROUP* record, int browseid);
int pxCustomerGroupEndBrowse       ( int browseid);
int pxCustomerGroupRead            ( struct tCUSTOMERGROUP* record);
int pxCustomerGroupReadLock        ( struct tCUSTOMERGROUP* record);
int pxCustomerGroupUpdate          ( struct tCUSTOMERGROUP* record);
int pxCustomerGroupInsert          ( struct tCUSTOMERGROUP* record);
int pxCustomerGroupDelete          ( struct tCUSTOMERGROUP* record);

int pxCustomerGrpFlagsStartBrowse  ( struct tCUSTOMERGRPFLAGS* record, int browseid);
int pxCustomerGrpFlagsGetNext      ( struct tCUSTOMERGRPFLAGS* record, int browseid);
int pxCustomerGrpFlagsEndBrowse    ( int browseid);
int pxCustomerGrpFlagsRead         ( struct tCUSTOMERGRPFLAGS* record);
int pxCustomerGrpFlagsReadLock     ( struct tCUSTOMERGRPFLAGS* record);
int pxCustomerGrpFlagsUpdate       ( struct tCUSTOMERGRPFLAGS* record);
int pxCustomerGrpFlagsInsert       ( struct tCUSTOMERGRPFLAGS* record);
int pxCustomerGrpFlagsDelete       ( struct tCUSTOMERGRPFLAGS* record);

int pxCustGrpFlagTypesStartBrowse  ( struct tCUSTGRPFLAGTYPES* record, int browseid);
int pxCustGrpFlagTypesGetNext      ( struct tCUSTGRPFLAGTYPES* record, int browseid);
int pxCustGrpFlagTypesEndBrowse    ( int browseid);
int pxCustGrpFlagTypesRead         ( struct tCUSTGRPFLAGTYPES* record);
int pxCustGrpFlagTypesReadLock     ( struct tCUSTGRPFLAGTYPES* record);
int pxCustGrpFlagTypesUpdate       ( struct tCUSTGRPFLAGTYPES* record);
int pxCustGrpFlagTypesInsert       ( struct tCUSTGRPFLAGTYPES* record);
int pxCustGrpFlagTypesDelete       ( struct tCUSTGRPFLAGTYPES* record);

int CustomerTourStartBrowse     ( struct tCUSTOMERTOUR* record, const char* dbName, int browseid );
int CustomerTourGetNext         ( struct tCUSTOMERTOUR* record, int browseid );
int CustomerTourEndBrowse       ( int browseid );

int pxOeOriginTypesStartBrowse     ( struct tOEORIGINTYPES* record, int browseid);
int pxOeOriginTypesGetNext         ( struct tOEORIGINTYPES* record, int browseid);
int pxOeOriginTypesEndBrowse       ( int browseid);
int pxOeOriginTypesRead            ( struct tOEORIGINTYPES* record);
int pxOeOriginTypesReadLock        ( struct tOEORIGINTYPES* record);
int pxOeOriginTypesUpdate          ( struct tOEORIGINTYPES* record);
int pxOeOriginTypesInsert          ( struct tOEORIGINTYPES* record);
int pxOeOriginTypesDelete          ( struct tOEORIGINTYPES* record);

int pxOeRestrictionTypesStartBrowse( struct tOERESTRICTIONTYPES* record, int browseid);
int pxOeRestrictionTypesGetNext    ( struct tOERESTRICTIONTYPES* record, int browseid);
int pxOeRestrictionTypesEndBrowse  ( int browseid);
int pxOeRestrictionTypesRead       ( struct tOERESTRICTIONTYPES* record);
int pxOeRestrictionTypesReadLock   ( struct tOERESTRICTIONTYPES* record);
int pxOeRestrictionTypesUpdate     ( struct tOERESTRICTIONTYPES* record);
int pxOeRestrictionTypesInsert     ( struct tOERESTRICTIONTYPES* record);
int pxOeRestrictionTypesDelete     ( struct tOERESTRICTIONTYPES* record);

int pxOeRestrictionsStartBrowse    ( struct tORDERENTRYRESTRICTIONS* record, int browseid);
int pxOeRestrictionsGetNext        ( struct tORDERENTRYRESTRICTIONS* record, int browseid);
int pxOeRestrictionsEndBrowse      ( int browseid);
int pxOeRestrictionsRead           ( struct tORDERENTRYRESTRICTIONS* record);
int pxOeRestrictionsReadLock       ( struct tORDERENTRYRESTRICTIONS* record);
int pxOeRestrictionsUpdate         ( struct tORDERENTRYRESTRICTIONS* record);
int pxOeRestrictionsInsert         ( struct tORDERENTRYRESTRICTIONS* record);
int pxOeRestrictionsDelete         ( struct tORDERENTRYRESTRICTIONS* record);

int pxEventReasonStartBrowse       ( struct tEVENTREASONS* record, int browseid);
int pxEventReasonGetNext           ( struct tEVENTREASONS* record, int browseid);
int pxEventReasonEndBrowse         ( int browseid);
int pxEventReasonRead              ( struct tEVENTREASONS* record);
int pxEventReasonReadLock          ( struct tEVENTREASONS* record);
int pxEventReasonUpdate            ( struct tEVENTREASONS* record);
int pxEventReasonInsert            ( struct tEVENTREASONS* record);
int pxEventReasonDelete            ( struct tEVENTREASONS* record);

int pxOrderPosEventStartBrowse     ( struct tKDAUFTRAGPOSEREIGNIS* record, int browseid);
int pxOrderPosEventGetNext         ( struct tKDAUFTRAGPOSEREIGNIS* record, int browseid);
int pxOrderPosEventEndBrowse       ( int browseid);
int pxOrderPosEventRead            ( struct tKDAUFTRAGPOSEREIGNIS* record);
int pxOrderPosEventReadLock        ( struct tKDAUFTRAGPOSEREIGNIS* record);
int pxOrderPosEventUpdate          ( struct tKDAUFTRAGPOSEREIGNIS* record);
int pxOrderPosEventInsert          ( struct tKDAUFTRAGPOSEREIGNIS* record);
int pxOrderPosEventDelete          ( struct tKDAUFTRAGPOSEREIGNIS* record);

int pxToteInfoInsert               ( struct tTOTEINFO* record);

int KdAuftragPosTourStartBrowse( struct tKDAUFTRAGPOSTOUR* record, int browseid );
int KdAuftragPosTourGetNext( struct tKDAUFTRAGPOSTOUR* record, int browseid );
int KdAuftragPosTourEndBrowse( int browseid );
int KdAuftragPosTourRead( struct tKDAUFTRAGPOSTOUR* record );
int KdAuftragPosTourInsert( struct tKDAUFTRAGPOSTOUR* record );
int KdAuftragPosTourUpdate( struct tKDAUFTRAGPOSTOUR* record );
int KdAuftragPosTourDelete( struct tKDAUFTRAGPOSTOUR* record );
int KdAuftragPosTourDeleteIBT( struct tKDAUFTRAGPOSTOUR* record );

/* IBTBranches */
int IBTBranchesStartBrowse( struct tIBTBRANCHES* record, const char* dbNameLocal, const char* dbNameIBT, int browseid );
int IBTBranchesGetNext( struct tIBTBRANCHES* record, int browseid );
int IBTBranchesEndBrowse( int browseid );

/* CustomerBusinessHours */
int CustomerBusinessHoursStartBrowse( struct tCUSTOMERBUSINESSHOURS* record, const char* dbName, int browseid );
int CustomerBusinessHoursGetNext( struct tCUSTOMERBUSINESSHOURS* record, int browseid );
int CustomerBusinessHoursEndBrowse( int browseid );

/* CustomerSpecials */
int pxCustomerSpecialsStartBrowse       ( struct tCUSTOMERSPECIALS* record,int browseid);
int pxCustomerSpecialsGetNext           ( struct tCUSTOMERSPECIALS* record,int browseid);
int pxCustomerSpecialsEndBrowse         ( int browseid);
int pxCustomerSpecialsRead              ( struct tCUSTOMERSPECIALS* record);
int pxCustomerSpecialsReadLock          ( struct tCUSTOMERSPECIALS* record);
int pxCustomerSpecialsUpdate            ( struct tCUSTOMERSPECIALS* record);
int pxCustomerSpecialsInsert            ( struct tCUSTOMERSPECIALS* record);
int pxCustomerSpecialsDelete            ( struct tCUSTOMERSPECIALS* record);

/* OrderRelationNoTypes */
int pxOrderRelationNoTypesStartBrowse ( struct tORDERRELATIONNOTYPES* record, int browseid );
int pxOrderRelationNoTypesGetNext( struct tORDERRELATIONNOTYPES* record, int browseid );
int pxOrderRelationNoTypesEndBrowse( int browseid );
int pxOrderRelationNoTypesRead( struct tORDERRELATIONNOTYPES* record );

/* OrderRelationNo */
int pxOrderRelationNoStartBrowse( struct tORDERRELATIONNO* record, int browseid );
int pxOrderRelationNoGetNext( struct tORDERRELATIONNO* record, int browseid );
int pxOrderRelationNoEndBrowse( int browseid );
int pxOrderRelationNoRead( struct tORDERRELATIONNO* record );
int pxOrderRelationNoInsert( struct tORDERRELATIONNO* record );
int pxOrderRelationNoUpdate( struct tORDERRELATIONNO* record );
int pxOrderRelationNoDelete( struct tORDERRELATIONNO* record );

int pxPositionInfoRead                 ( struct tKDAUFTRAGPOS* position, char* Computer);

int pxServicesStartBrowse          ( struct tSERVICES* record, int browseid);
int pxServicesGetNext              ( struct tSERVICES* record, int browseid);
int pxServicesEndBrowse            ( int browseid);
int pxServicesRead                 ( struct tSERVICES* record);
int pxServicesReadLock             ( struct tSERVICES* record);
int pxServicesUpdate               ( struct tSERVICES* record);
int pxServicesInsert               ( struct tSERVICES* record);
int pxServicesDelete               ( struct tSERVICES* record);


int pxCustomerEmergencyServicePlanRead( struct tEMERGENCYSERVICEPLAN* record );

/* IBTBranchArticleConfig */
int pxIBTBranchArticleConfigRead( struct tIBTBRANCHARTICLECONFIG* record );

/* IBTAssortmentType */
int pxIBTAssortmentTypeStartBrowse  ( struct tIBTASSORTMENTTYPE* record, int browseid);
int pxIBTAssortmentTypeGetNext      ( struct tIBTASSORTMENTTYPE* record, int browseid);
int pxIBTAssortmentTypeEndBrowse    ( int browseid);
int pxIBTAssortmentTypeRead         ( struct tIBTASSORTMENTTYPE* record );

#ifdef __cplusplus
}                                       /* close C declarations for C++       */
#endif

#endif
