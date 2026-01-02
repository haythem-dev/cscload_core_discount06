#define BUF_DESC
#include <stdio.h>
#include "bufkon.h"
#include <string.h>
#include "kscsrvdata.h"
#include "articleinquiry.h"
#include "articleinquirybulk.h"
#include <logger/loggerpool.h>


extern long UID;

int KscsrvGetArticleStockBulk(struct N_ARTICLEINQUIRYBULK *d,char *error_msg);
int KscsrvGetArticleAvailabilityBulk(struct N_ARTICLEINQUIRYBULK *d,char *error_msg);
int KscsrvGetArticleInfoCode(struct N_ARTICLEINQUIRY *d,char *error_msg);
int KscsrvWriteProLink(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvChangeReference(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvSetROParam(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvGetProforma(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvProformaorder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvSetBTMLicense(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvSetTourId(struct N_KSCSRVDATA *d,char *error_msg);
//int KscsrvSetTenderContractId(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvSetTenderNo(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvOpensession(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvClosesession(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvOpenorder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvNeworder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvCloseorder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvChangeOrdBem(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvWritepos(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvInsKopfZlnAuf(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvCheckReference(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvInsertReference(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvOpenorderInternetOrderno(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvPostponeorderinternet(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvCloseorderInternet(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvWritetextpos(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvPostponeorder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvCancelorder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvChangeorder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvAddCallback(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvCheckDoubleOrder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvNeworderVz(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvOpenInfoOrder(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvGetArticleInfo(struct N_ARTICLEINQUIRY *d,char *error_msg);
int KscsrvGetArticleInquiry(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvSetBatchOrderTyp(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvSetdelayeddate(struct N_KSCSRVDATA *d,char *error_msg);
int KscsrvGetArticleStock(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvCloseorderDebtLimit(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvCancelorderDebtLimit(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvNeworderMSV3(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvSetValueDate(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvSetOrderInfoDetails(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvSetTurnOverOrigin(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvSetRelationNo(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvGetArticleManufacturer(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvGetApprovalData(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvWriteDispoItem(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvIsExportPermitted(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvChangeDeliveryTour(struct N_KSCSRVDATA *d, char *error_msg);
int KscsrvChangePaymentToCashOrder(struct N_KSCSRVDATA*, char *error_msg);

int handleResult(int rc, void* stru, char* out, int* out_len, char* error_msg, struct buf_desc bd[], size_t anz)
{
    if (rc < 0)
    {
        strcpy(out, error_msg);
        *out_len = strlen(out) + 1;
    }
    else
    {
        *out_len = buf_kon(TO_UEB, stru, out, bd, anz);
    }
    return rc;
}

/* function definitions for WEPSEL */
/*  FKT_SELEKT  */
int FktvertFkt_selekt(int fkt_nr,char *in,char *out,int *out_len)
{
    /*  fkt_selekt  */
    
    /* fkt_nr = Nummer der auszufuehrenden Funktion */
    /* in     = Dateneingabe der Funktion */
    /* out    = Ergebnis der Funktion bei rc==-1 Fehlertext */
    int rc;
    char error_msg[81];
    
#ifdef __ONLY_DISTRIBUTE__
    if ( fkt_nr >= DADE_FUNCTION_NO )
    {
       return DistributorFunPublic( fkt_nr, in, out, out_len );
    }
#endif /*__ONLY_DISTRIBUTE__*/
    
    switch(fkt_nr)
    {
    case 750: // KscsrvChangePaymentToCashOrder
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvChangePaymentToCashOrder(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 749:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvChangeDeliveryTour(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 748: // KscsrvIsExportPermitted
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char*)&d, in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvIsExportPermitted(&d, error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 747: // KscsrvWriteDispoItem
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvWriteDispoItem(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 746: // KscsrvGetApprovalData
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvGetApprovalData(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 745: // KscsrvGetArticleManufacturer
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvGetArticleManufacturer(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 744: // KscsrvSetRelationNo
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetRelationNo(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 743: // KscsrvSetTurnOverOrigin
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetTurnOverOrigin(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 742: // GetArticleStockBulk
        {
            struct N_ARTICLEINQUIRYBULK d;
            buf_kon(FROM_UEB, (char *)&d,in, ARTICLEINQUIRYBULK_BES, ARTICLEINQUIRYBULK_ANZ);
            rc = KscsrvGetArticleStockBulk(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTICLEINQUIRYBULK_BES, ARTICLEINQUIRYBULK_ANZ);
        }
    case 741: // GetArticleAvailabilityBulk
        {
            struct N_ARTICLEINQUIRYBULK d;
            buf_kon(FROM_UEB, (char *)&d,in, ARTICLEINQUIRYBULK_BES, ARTICLEINQUIRYBULK_ANZ);
            rc = KscsrvGetArticleAvailabilityBulk(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTICLEINQUIRYBULK_BES, ARTICLEINQUIRYBULK_ANZ);
        }
    /*
    case 740: // SetTenderContractId
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetTenderContractId(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
        */
    case 739: // SetOrderInfoDetails
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetOrderInfoDetails(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 738:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetValueDate(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 737:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvNeworderMSV3(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 736:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvCancelorderDebtLimit(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 735:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvCloseorderDebtLimit(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 734:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvGetArticleStock(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 733:
        {
            struct N_ARTICLEINQUIRY d;
            buf_kon(FROM_UEB, (char *)&d,in, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
            rc = KscsrvGetArticleInfoCode(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
        }
    case 732:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvWriteProLink(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 731:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvChangeReference(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 730:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetROParam(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 729:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvGetProforma(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 728:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvProformaorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 727:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetBTMLicense(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 726:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetTourId(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 725:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetTenderNo(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 724:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetBatchOrderTyp(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 723:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvSetdelayeddate(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 722:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvGetArticleInquiry(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 721:
        {
            struct N_ARTICLEINQUIRY d;
            buf_kon(FROM_UEB, (char *)&d,in, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
            rc = KscsrvGetArticleInfo(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
        }
    case 720:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvOpenInfoOrder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 719:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvNeworderVz(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 718:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvCheckDoubleOrder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 717:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvAddCallback(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 716:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvChangeorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 715:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvCancelorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 714:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvPostponeorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 713:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvWritetextpos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 712:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvCloseorderInternet(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 711:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvPostponeorderinternet(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 710:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvOpenorderInternetOrderno(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 709:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvInsertReference(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 708:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvCheckReference(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 707:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvInsKopfZlnAuf(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 706:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvWritepos(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 705:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvChangeOrdBem(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 704:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvCloseorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 703:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvNeworder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 702:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvOpenorder(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 701:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvClosesession(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    case 700:
        {
            struct N_KSCSRVDATA d;
            buf_kon(FROM_UEB, (char *)&d,in, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
            rc = KscsrvOpensession(&d,error_msg);
            return handleResult(rc, (char*)&d, out, out_len, error_msg, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
        }
    default:
        sprintf(out,"FktvertFkt_selekt: %d",fkt_nr);
        *out_len=strlen(out)+1;
        return -1; /* Fehler */
    }
}

int FktvertPuffer_anp (char *WriteBuf, char *ReadBuf, int /*a_lng*/)
{
    int out_len;
    int fkt_nr;

    sscanf(ReadBuf, "%4d", &fkt_nr);
    int rc = FktvertFkt_selekt(fkt_nr, ReadBuf+4, WriteBuf+1, &out_len);
    switch (rc)
    {
    case -1:
        *WriteBuf = 'F';
        /* schwerwiegende Fehler werden in die Log-Datei eingetragen */
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), WriteBuf + 1);
        break;
    case -2:    /* Warnung */
        *WriteBuf = 'W';
        break;
    case -5:    /* Keine neuen Aufträge */
        *WriteBuf = 'X';
        break;
    case 1:    /* SQLNOTFOUND */
        *WriteBuf = '1';
        break;
    case 2:    /* FETCH wurde unterbrochen (max.Anzahl) */
        *WriteBuf = '2';
        *(WriteBuf+1) = '\0';
        break;
    case 3:    /* Warnung */
        *WriteBuf = '3'; /* schneller FETCH (perm. Schreiben in die Pipe) */
        break;
    case 4:    /* Warnung */
        *WriteBuf = '4'; /* für User gesperrter Zugriff */
        break;
    case 5:    /* Warnung */
        *WriteBuf = '5'; /* Key bereits vorhanden */
        break;
    case 6:    /* Warnung */
        *WriteBuf = '6'; /* Auftrag bereits vorhanden */
        break;
    default:
        *WriteBuf = '0';   /* normales Ergebnis (select bzw. fetch usw.) */
        break;
    }
    return out_len+1;
}
