/* callksc.c: c-api for order system */

#define BUF_DESC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <kscsrvdata.h>
#include <kscsrvfkt.h>

#include <pplib/ppgeneric.h>
#include <pplib/bufkon.h>
#include <pplib/sockclient.h>

#include "orderinfo.h"
#include "articleinquiry.h"
#include "articleinquirybulk.h"
#include "articleinfostruct.h"
#include "articleinfostructcode.h"
#include "callksc.h"

typedef enum { false = 0, true = 1 } bool;

#define KSC_PORT          6600      /* port number order system kscserver*/

int ServNr;
int iCheckDouble = 0;
int iNoRouting = 0;
char error_msg[81];
char LogFile[81];
char SystemLogFile[81];

void CopyInfo(kscsrvdataS *d,orderinfoS *Info);
void PutArticleInfo(articleinquiryS *d,stArticleInfo *Info);
void ConvertArticleInfo(articleinquiryS *d,stArticleInfo *Info);
void PutArticleInfoCode(articleinquiryS *d,stArticleInfoCode *Info);
void ConvertArticleInfoCode(articleinquiryS *d,stArticleInfoCode *Info);

static bool CheckPrinting( const unsigned char cp )
{
   if ( cp < ' ' || cp > 0x7f )
      return false;
   return true;
}

//--------------------------------------------------------------------------------------
int ConnectServer( const char *IniFile, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;

    int rc;
    int PortNo = -1;
    char* envir = NULL;
    char inifile[256];
    char line[251];
    char funktion[81];
    char wert[81];
    char gleich[81];
    char server[81];
    FILE* f_ini;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    envir = getenv("WWS_INI");
    if (envir != NULL)
    {
        sprintf(inifile,"%s/%s",envir,IniFile);
    }
    else
    {
        sprintf(inifile,"./%s",IniFile);
    }
    f_ini = fopen(inifile, "r");

    if (f_ini == NULL)
    {
        strcpy(Info->TEXT,"No Inifile found");
        return -1; /* File not found */
    }

    /* Read in port and more */
    while (fgets(line, 250, f_ini) != NULL)
    {
        sscanf(line, "%s %s %s", funktion, gleich, wert);
        if (!strcmp(funktion,"DeviceName"))
        {
            ppGStrCopy(d.DEVICENAME,wert,L_KSCSRVDATA_DEVICENAME );
        }
        else if (!strcmp(funktion,"UserName"))
        {
            ppGStrCopy(d.USERNAME,wert,L_KSCSRVDATA_USERNAME );
        }
        else if (!strcmp(funktion,"LogFile"))
        {
            strcpy(LogFile,wert);
        }
        else if (!strcmp(funktion,"Server"))
        {
            strcpy(server,wert);
        }
        else if (!strcmp(funktion,"SystemLogFile"))
        {
            strcpy(SystemLogFile,wert);
        }
        else if (!strcmp(funktion,"BranchNo"))
        {
            d.BRANCHNO = (short)atoi(wert);
        }
        else if (!strcmp(funktion,"PortNo"))
        {
            PortNo = atoi(wert);
        }
        else
        {
            strcpy(Info->TEXT,"No regular entry in ini");
            return -2; /* Ungültiger Eintrag in Ini-File */
        }
    }

    if(( ServNr = ppSGetNextFreeServNr(error_msg) ) < 0 )
        return ServNr;

    if ( PortNo < 0 || PortNo > 99999 )
       PortNo = KSC_PORT;
    if(( rc = ppSOpenSServerNr(ServNr, server, PortNo, error_msg) ) < 0 )
        return rc;

    d.UID = 0;

    rc = ServerNr(ServNr,KscsrvOpensession,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    if( rc != 0 )
    {
        CloseServerNr(ServNr, error_msg);
        return rc;
    }
#ifdef PPDEBUG
    printf("\nServerNummer ist: %d\n",ServNr);
#endif
    return ServNr;
}

//--------------------------------------------------------------------------------------
int ConnectServerNoIni( const char *DeviceName, const long UID, const int PortNo, const char *Server, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;

    int rc;
    char server[81];
    int port;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    ppGStrCopy(d.DEVICENAME,DeviceName,L_KSCSRVDATA_DEVICENAME );
    strcpy(server,Server);
    port = PortNo;

    if(( ServNr = ppSGetNextFreeServNr(error_msg) ) < 0 )
        return ServNr;

    if ( port < 0 || port > 99999 )
       port = KSC_PORT;
    if(( rc = ppSOpenSServerNr(ServNr, server, port, error_msg) ) < 0 )
        return rc;

    d.UID = UID;
    d.BRANCHNO = 0;

    rc = ServerNr(ServNr,KscsrvOpensession,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    if( rc != 0 )
    {
        CloseServerNr(ServNr, error_msg);
        return rc;
    }
#ifdef PPDEBUG
    printf("\nServerNummer ist: %d\n",ServNr);
#endif
    return ServNr;
}

//--------------------------------------------------------------------------------------
int DisconnectServer( orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;
    char error[256];

    /* close order session */
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    rc = ServerNr(ServNr,KscsrvClosesession,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    if( rc < 0 )
    {
        CloseServerNr(ServNr, error);
        return rc;
    }

    CopyInfo(&d,Info);
    /* close socket session */
    if(( rc = CloseServerNr(ServNr, error_msg) ) < 0 )
        return rc;

    return 0;
}

//--------------------------------------------------------------------------------------
int OpenOrder( const long CustomerNo, const char *OrderTyp, const char *SubOrderTyp, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    if(iCheckDouble == 1) d.SCHECKDOUBLE[0] = '1';
    iCheckDouble = 0;

    if (iNoRouting == 1) d.SWNOROUTING = 1;
    iNoRouting = 0;

    d.CUSTOMERNO = CustomerNo;
    ppGStrCopy(d.KINDOFORDER    ,OrderTyp,    L_KSCSRVDATA_KINDOFORDER      );
    ppGStrCopy(d.SUB_ORDER_TYPE ,SubOrderTyp, L_KSCSRVDATA_SUB_ORDER_TYPE   );
    /*rc = ServerNr(ServNr,AasrvCheckReference,(void *)&d,AUFTRAG_BES,AUFTRAG_ANZ,error_msg);
    if (rc != 0) return rc; */

    /* new order */
    rc = ServerNr(ServNr,KscsrvNeworder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nOpen Order rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int OpenInfoOrder( const short VzNr, const long CustomerNo, const short Infolevel, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    if(iCheckDouble == 1) d.SCHECKDOUBLE[0] = '1';
    iCheckDouble = 0;

    if (iNoRouting == 1) d.SWNOROUTING = 1;
    iNoRouting = 0;

    d.BRANCHNO = VzNr;
    d.CUSTOMERNO = CustomerNo;
    d.INFOLEVEL = Infolevel;
    /* new order */
    rc = ServerNr(ServNr,KscsrvOpenInfoOrder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int OpenOrderVz( const short VzNr, const long CustomerNo, const char *OrderTyp, const char *SubOrderTyp, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    if(iCheckDouble == 1) d.SCHECKDOUBLE[0] = '1';
    iCheckDouble = 0;

    if (iNoRouting == 1) d.SWNOROUTING = 1;
    iNoRouting = 0;

    d.BRANCHNO = VzNr;
    d.CUSTOMERNO = CustomerNo;
    ppGStrCopy(d.KINDOFORDER,    OrderTyp,    L_KSCSRVDATA_KINDOFORDER      );
    ppGStrCopy(d.SUB_ORDER_TYPE, SubOrderTyp, L_KSCSRVDATA_SUB_ORDER_TYPE   );
    /* new order */
    rc = ServerNr(ServNr,KscsrvNeworderVz,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nOpen Order rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetOrderType( const char *OrderTyp, const char *KoArt, const char *BuchArt, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy(d.KINDOFORDER,  OrderTyp, L_KSCSRVDATA_KINDOFORDER   );
    ppGStrCopy(d.SHIPMENTTYPE, KoArt,    L_KSCSRVDATA_SHIPMENTTYPE  );
    ppGStrCopy(d.BOOKINGTYPE,  BuchArt,  L_KSCSRVDATA_BOOKINGTYPE   );

    rc = ServerNr(ServNr,KscsrvChangeorder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nSetOrderType rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetOrderTypeSub( const char *OrderTyp, const char *KoArt, const char *BuchArt, const char *SubOrderTyp, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy(d.KINDOFORDER,    OrderTyp,    L_KSCSRVDATA_KINDOFORDER   );
    ppGStrCopy(d.SHIPMENTTYPE,   KoArt,       L_KSCSRVDATA_SHIPMENTTYPE  );
    ppGStrCopy(d.BOOKINGTYPE,    BuchArt,     L_KSCSRVDATA_BOOKINGTYPE   );
    ppGStrCopy(d.SUB_ORDER_TYPE, SubOrderTyp, L_KSCSRVDATA_SUB_ORDER_TYPE);

    rc = ServerNr(ServNr,KscsrvChangeorder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nSetOrderType rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int CloseOrder( const char *strText, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    if ( CheckPrinting(*strText) && *strText != ' ' )
    {
       buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
       ppGStrCopy( d.REMARKS, strText, L_KSCSRVDATA_REMARKS );
       rc = ServerNr(ServNr,KscsrvChangeOrdBem,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
       if ( rc < 0 )
           return rc;
    }

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    /* close order */
    rc = ServerNr(ServNr,KscsrvCloseorder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nCloseOrder rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int CancelOrder( orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    /* cancel order */
    rc = ServerNr(ServNr,KscsrvCancelorder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nCancelOrder rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int PostponeOrder( orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    /* new order */
    rc = ServerNr(ServNr,KscsrvPostponeorder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nPostponeOrder rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetOrderText( const char *text, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy(d.REMARKS, text, L_KSCSRVDATA_REMARKS );

    /* change order text */
    rc = ServerNr(ServNr,KscsrvChangeOrdBem,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nKscsrvChangeOrdBem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetOrderReference( const char *text, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy(d.REMARKS, text, L_KSCSRVDATA_REMARKS );

    /* change order text */
    rc = ServerNr(ServNr,KscsrvChangeReference,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nKscsrvChangeReference rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetOrderRelationNo( const long RelationNo, const short RelationNoType, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.RELATIONNO = RelationNo;
    d.RELATIONNOTYPE = RelationNoType;

    rc = ServerNr(ServNr,KscsrvSetRelationNo,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\KscsrvSetRelationNo rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetTenderNo( const int TenderNo, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.TENDERNO = TenderNo;
    rc = ServerNr(ServNr,KscsrvSetTenderNo,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\SetTenderNo rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}// SetTenderNo

//--------------------------------------------------------------------------------------
int SetBatchOrderTyp( const int BatchTyp,const short OriginBranch,const int ValutaDatum,const char *EdiLieferSchein,const char *JobNo, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.BATCHSCHREIBEN = BatchTyp;
    d.BRANCHNOORIGIN = OriginBranch;
    d.EDILIEFERSCHEIN[0] = EdiLieferSchein[0];
    d.VALUTADATUM = ValutaDatum;
    strncpy(d.JOBNO,JobNo,L_KSCSRVDATA_JOBNO);

    /* set batchschreiben */
    rc = ServerNr(ServNr,KscsrvSetBatchOrderTyp,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\KscsrvSetBatchOrderTyp rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderItem( const long Qty, const long number, const char* EAN, const int iAux, const int iRestDel, const int iDispo, const int iPartDel,
    const short sSeqNo, const int iIdfOrigin, const int iOrderNoOrigin,	const int iPosNoOrigin, const char* strText, orderinfoS* Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ARTICLENO = number;
    d.ORDERQTY = Qty;
    strncpy(d.EAN,EAN,L_KSCSRVDATA_EAN);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    if(iAux == YES) d.SWAUX[0] = '1';
    if(iRestDel == YES) d.SWRESTDELIVERY[0] = '1';
    if(iDispo == YES) d.SWDISPO[0] = '1';
    if(iPartDel == YES) d.SWPARTDELIVERY[0] = '1';
    d.ORDERSEQUENZNO = sSeqNo;
    d.IDFORIGIN = iIdfOrigin;
    d.ORDERNOORIGIN = iOrderNoOrigin;
    d.POSNOORIGIN = iPosNoOrigin;

    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderItemPT( const long Qty, const long number, const char *EAN, const int iAux, const int iRestDel, const int iDispo, const int iPartDel, const short sSeqNo, const int iIdfOrigin, const int iOrderNoOrigin, const int iPosNoOrigin, const int iPriceType, const char *strText, orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ARTICLENO = number;
    d.ORDERQTY = Qty;
    strncpy(d.EAN,EAN,L_KSCSRVDATA_EAN);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    if(iAux == YES) d.SWAUX[0] = '1';
    if(iRestDel == YES) d.SWRESTDELIVERY[0] = '1';
    if(iDispo == YES) d.SWDISPO[0] = '1';
    if(iPartDel == YES) d.SWPARTDELIVERY[0] = '1';
    d.ORDERSEQUENZNO = sSeqNo;
    d.IDFORIGIN = iIdfOrigin;
    d.ORDERNOORIGIN = iOrderNoOrigin;
    d.POSNOORIGIN = iPosNoOrigin;
    d.PREIS_TYP = (short)iPriceType;

    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderItemCode(const long Qty, const char *Code,
                 const int iAux,            /* auxiliary */
                 const int iRestDel,        /* restdelivery */
                 const int iDispo,          /* dispose */
                 const int iPartDel,        /* part delivery */
                 const short sSeqNo,        /* internal OrderNo */
                 const int iIdfOrigin,      /* interne IDF-Nummer */
                 const int iOrderNoOrigin,  /* Ursprungs Auftragsnummer */
                 const int iPosNoOrigin,    /* Ursprungs Positionsnummer */
                 const int iPriceType,      /* Preistyp */
                 const char *strText, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    if(iAux == YES) d.SWAUX[0] = '1';
    if(iRestDel == YES) d.SWRESTDELIVERY[0] = '1';
    if(iDispo == YES) d.SWDISPO[0] = '1';
    if(iPartDel == YES) d.SWPARTDELIVERY[0] = '1';
    d.ORDERSEQUENZNO = sSeqNo;
    d.IDFORIGIN = iIdfOrigin;
    d.ORDERNOORIGIN = iOrderNoOrigin;
    d.POSNOORIGIN = iPosNoOrigin;
    d.PREIS_TYP = (short)iPriceType;

    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderItemCodeRef(const long Qty, const char *Code,
                 const int iAux,            /* auxiliary */
                 const int iRestDel,        /* restdelivery */
                 const int iDispo,          /* dispose */
                 const int iPartDel,        /* part delivery */
                 const short sSeqNo,        /* internal OrderNo */
                 const int iIdfOrigin,      /* interne IDF-Nummer */
                 const int iOrderNoOrigin,  /* Ursprungs Auftragsnummer */
                 const int iPosNoOrigin,    /* Ursprungs Positionsnummer */
                 const int iPriceType,      /* Preistyp */
                 const char *strText,       /* Bermerkungstext */
                 const char *strRef,        /* Line Reference */
                 orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    strncpy(d.XMLLINEREFERENCE,strRef,L_KSCSRVDATA_XMLLINEREFERENCE);
    if(iAux == YES) d.SWAUX[0] = '1';
    if(iRestDel == YES) d.SWRESTDELIVERY[0] = '1';
    if(iDispo == YES) d.SWDISPO[0] = '1';
    if(iPartDel == YES) d.SWPARTDELIVERY[0] = '1';
    d.ORDERSEQUENZNO = sSeqNo;
    d.IDFORIGIN = iIdfOrigin;
    d.ORDERNOORIGIN = iOrderNoOrigin;
    d.POSNOORIGIN = iPosNoOrigin;
    d.PREIS_TYP = (short)iPriceType;

    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderItemRebateInKind(
                 const long Qty,			/* order quantity */
                 const long RebateInKind,	/* rebate in kind quantity */
                 const char *Code,
                 const int iAux,			/* auxiliary */
                 const int iRestDel,		/* restdelivery */
                 const int iDispo,      	/* dispose */
                 const int iPartDel,		/* part delivery */
                 const short sSeqNo,		/* internal OrderNo */
                 const int iIdfOrigin,      /* interne IDF-Nummer */
                 const int iOrderNoOrigin,  /* Ursprungs Auftragsnummer */
                 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
                 const int iPriceType,      /* Preistyp */
                 const char *strText,   	/* Bermerkungstext */
                 const char *strRef,		/* Line Reference */
                 const double dPriceAep,	/* neuer AEPreis */
                 const double dPrice,   	/* freier Preis */
                 const double dPCT,         /* freier Rabatt */
                 orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    strncpy(d.XMLLINEREFERENCE,strRef,L_KSCSRVDATA_XMLLINEREFERENCE);
    if(iAux == YES) d.SWAUX[0] = '1';
    if(iRestDel == YES) d.SWRESTDELIVERY[0] = '1';
    if(iDispo == YES) d.SWDISPO[0] = '1';
    if(iPartDel == YES) d.SWPARTDELIVERY[0] = '1';
    d.ORDERSEQUENZNO = sSeqNo;
    d.IDFORIGIN = iIdfOrigin;
    d.ORDERNOORIGIN = iOrderNoOrigin;
    d.POSNOORIGIN = iPosNoOrigin;
    d.PREIS_TYP = (short)iPriceType;
    d.PHARMPURCHPRICE = dPriceAep;
    d.MANUALPRICE = dPrice;
    d.MANUELDISCPCT = dPCT;
    d.QTYNATRA = RebateInKind;

    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderItemCodeRefFreeLineRef( const long Qty, const char *Code,
                                    const int iAux, 		/* auxiliary */
                                    const int iRestDel, 	/* restdelivery */
                                    const int iDispo,   	/* dispose */
                                    const int iPartDel, 	/* part delivery */
                                    const short sSeqNo, 	/* internal OrderNo */
                                    const int iIdfOrigin,   /* interne IDF-Nummer */
                                    const int iOrderNoOrigin, /* Ursprungs Auftragsnummer */
                                    const int iPosNoOrigin, /* Ursprungs Positionsnummer */
                                    const int iPriceType,   /* Preistyp */
                                    const char *strText,	/* Bermerkungstext */
                                    const char *strRef, 	/* Line Reference */
                                    const double dPriceAep, /* neuer AEPreis */
                                    const double dPrice,    /* freier Preis */
                                    const double dPCT,      /* freier Rabatt */
                                    const char *strLineRef, /* LineReference */
                                    orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    strncpy(d.XMLLINEREFERENCE,strRef,L_KSCSRVDATA_XMLLINEREFERENCE);
    strncpy(d.XMLTEXT,strLineRef,L_KSCSRVDATA_XMLTEXT);
    if(iAux == YES) d.SWAUX[0] = '1';
    if(iRestDel == YES) d.SWRESTDELIVERY[0] = '1';
    if(iDispo == YES) d.SWDISPO[0] = '1';
    if(iPartDel == YES) d.SWPARTDELIVERY[0] = '1';
    d.ORDERSEQUENZNO = sSeqNo;
    d.IDFORIGIN = iIdfOrigin;
    d.ORDERNOORIGIN = iOrderNoOrigin;
    d.POSNOORIGIN = iPosNoOrigin;
    d.PREIS_TYP = (short)iPriceType;
    d.PHARMPURCHPRICE = dPriceAep;
    d.MANUALPRICE = dPrice;
    d.MANUELDISCPCT = dPCT;


    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}


//--------------------------------------------------------------------------------------
int AddOrderItemCodeRefFree(const long Qty, const char *Code,
                 const int iAux,			/* auxiliary */
                 const int iRestDel,		/* restdelivery */
                 const int iDispo,      	/* dispose */
                 const int iPartDel,		/* part delivery */
                 const short sSeqNo,		/* internal OrderNo */
                 const int iIdfOrigin,      /* interne IDF-Nummer */
                 const int iOrderNoOrigin,  /* Ursprungs Auftragsnummer */
                 const int iPosNoOrigin,	/* Ursprungs Positionsnummer */
                 const int iPriceType,      /* Preistyp */
                 const char *strText,   	/* Bermerkungstext */
                 const char *strRef,		/* Line Reference */
                 const double dPriceAep,	/* neuer AEPreis */
                 const double dPrice,   	/* freier Preis */
                 const double dPCT,         /* freier Rabatt */
                 orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    strncpy(d.XMLLINEREFERENCE,strRef,L_KSCSRVDATA_XMLLINEREFERENCE);
    if(iAux == YES) d.SWAUX[0] = '1';
    if(iRestDel == YES) d.SWRESTDELIVERY[0] = '1';
    if(iDispo == YES) d.SWDISPO[0] = '1';
    if(iPartDel == YES) d.SWPARTDELIVERY[0] = '1';
    d.ORDERSEQUENZNO = sSeqNo;
    d.IDFORIGIN = iIdfOrigin;
    d.ORDERNOORIGIN = iOrderNoOrigin;
    d.POSNOORIGIN = iPosNoOrigin;
    d.PREIS_TYP = (short)iPriceType;
    d.PHARMPURCHPRICE = dPriceAep;
    d.MANUALPRICE = dPrice;
    d.MANUELDISCPCT = dPCT;

    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderItemCodeRab(const long Qty, const char *Code,
                 const int iAux,    		/* auxiliary */
                 const int iRestDel,		/* restdelivery */
                 const int iDispo,      	/* dispose */
                 const int iPartDel,		/* part delivery */
                 const short sSeqNo,		/* internal OrderNo */
                 const int iIdfOrigin,      /* interne IDF-Nummer */
                 const int iOrderNoOrigin,  /* Ursprungs Auftragsnummer */
                 const int iPosNoOrigin,    /* Ursprungs Positionsnummer */
                 const int iPriceType,      /* Preistyp */
                 const long lDiscQty,   	/* Naturalrabatt */
                 const double dPCT,         /* freier Rabatt */
                 const short sKindOfDiscount, /* Rabatttyp */
                 const char *strText, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    if(iAux == YES) d.SWAUX[0] = '1';
    if(iRestDel == YES) d.SWRESTDELIVERY[0] = '1';
    if(iDispo == YES) d.SWDISPO[0] = '1';
    if(iPartDel == YES) d.SWPARTDELIVERY[0] = '1';
    d.ORDERSEQUENZNO = sSeqNo;
    d.IDFORIGIN = iIdfOrigin;
    d.ORDERNOORIGIN = iOrderNoOrigin;
    d.POSNOORIGIN = iPosNoOrigin;
    d.PREIS_TYP = (short)iPriceType;
    d.MANUELDISCPCT = dPCT;
    d.SKINDOFDISCOUNT = sKindOfDiscount;
    d.QTYNATRA = lDiscQty;

    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderItemCodeBatch(const long Qty, const char* Code,
                 const char* BatchNo,   /* Chargen Nummer */
                 const int iPriceType,  /* Preistyp */
                 const char* strText, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);
    strncpy(d.BATCHNO,BatchNo,L_KSCSRVDATA_BATCHNO);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);
    d.PREIS_TYP = (short)iPriceType;

    /* new order */
    rc = ServerNr(ServNr,KscsrvWritepos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderItemCodeBatch rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddTextItem(const long Qty, const char *strText, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);

    rc = ServerNr(ServNr,KscsrvWritetextpos,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddTextItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddDispoItem(const long Qty,
                 const char *strRemarks,
                 const char *strDarreichform,
                 const char *strEinheit,
                 const char *strArtBez,
                 const double dPreiskgrosso,
                 const double dPreiskapo,
                 const double dMwstSchluessel,
                 const long lKdAuftragNr,
                 const long lPosNr,
                 const double dPorto,
                 orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    strncpy(d.REMARKS,strRemarks,L_KSCSRVDATA_REMARKS);
    strncpy(d.HANDOUT,strDarreichform, L_KSCSRVDATA_HANDOUT);
    strncpy(d.ARTICLEUNIT, strEinheit, L_KSCSRVDATA_ARTICLEUNIT);
    strncpy(d.ARTICLENAME, strArtBez, L_KSCSRVDATA_ARTICLENAME);
    d.PREISEKGROSSO = dPreiskgrosso;
    d.PHARMPURCHPRICE = dPreiskapo;
    d.TAXRATE         = dMwstSchluessel;
    d.ORDERNOORIGIN   = lKdAuftragNr;
    d.POSNOORIGIN     = lPosNr;
    d.POSTAGE         = dPorto;

    rc = ServerNr(ServNr,KscsrvWriteDispoItem,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\n AddDispoItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int OpenOrderReference(const long CustomerNo, const char *Reference, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    if(iCheckDouble == 1) d.SCHECKDOUBLE[0] = '1';
    iCheckDouble = 0;

    if (iNoRouting == 1) d.SWNOROUTING = 1;
    iNoRouting = 0;

    d.CUSTOMERNO = CustomerNo;
    strncpy(d.REMARKS,Reference,L_KSCSRVDATA_REMARKS);

    /* new order */
    rc = ServerNr(ServNr,KscsrvNeworder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    if (rc != 0)
    {
        CopyInfo(&d,Info);
        return rc;
    }
    rc = ServerNr(ServNr,KscsrvCheckReference,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    if (rc != 0)
    {
        return rc;
    }
#ifdef PPDEBUG
    printf("\nOpen Order rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    return rc;
}

//--------------------------------------------------------------------------------------
int OpenOrderReferenceVz(const short VzNr, const long CustomerNo, const char *Reference, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    if(iCheckDouble == 1) d.SCHECKDOUBLE[0] = '1';
    iCheckDouble = 0;

    if (iNoRouting == 1) d.SWNOROUTING = 1;
    iNoRouting = 0;

    d.CUSTOMERNO = CustomerNo;
    d.BRANCHNO = VzNr;
    strncpy(d.REMARKS,Reference,L_KSCSRVDATA_REMARKS);

    /* new order */
    rc = ServerNr(ServNr,KscsrvNeworderVz,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    if (rc != 0)
    {
        CopyInfo(&d,Info);
        return rc;
    }
    /*rc = ServerNr(ServNr,KscsrvCheckReference,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg); */
    CopyInfo(&d,Info);
    if (rc != 0)
    {
        return rc;
    }
#ifdef PPDEBUG
    printf("\nOpen Order rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    return rc;
}

//--------------------------------------------------------------------------------------
int OpenOrderReferenceVzType(const short VzNr, const long CustomerNo, const char* Reference, const char* OrderTyp,
    const char* KoArt, const char* BuchArt, const char* SubOrderTyp, orderinfoS* Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    if(iCheckDouble == 1) d.SCHECKDOUBLE[0] = '1';
    iCheckDouble = 0;

    if (iNoRouting == 1) d.SWNOROUTING = 1;
    iNoRouting = 0;

    d.CUSTOMERNO = CustomerNo;
    d.BRANCHNO = VzNr;
    strncpy(d.REMARKS,Reference,L_KSCSRVDATA_REMARKS);
    ppGStrCopy(d.KINDOFORDER,    OrderTyp,    L_KSCSRVDATA_KINDOFORDER   );
    ppGStrCopy(d.SHIPMENTTYPE,   KoArt,       L_KSCSRVDATA_SHIPMENTTYPE  );
    ppGStrCopy(d.BOOKINGTYPE,    BuchArt,     L_KSCSRVDATA_BOOKINGTYPE   );
    ppGStrCopy(d.SUB_ORDER_TYPE, SubOrderTyp, L_KSCSRVDATA_SUB_ORDER_TYPE);

    /* new order */
    rc = ServerNr(ServNr,KscsrvNeworderVz,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    if (rc != 0)
    {
        CopyInfo(&d,Info);
        return rc;
    }
    /*rc = ServerNr(ServNr,KscsrvCheckReference,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg); */
    CopyInfo(&d,Info);
    if (rc != 0)
    {
        return rc;
    }
#ifdef PPDEBUG
    printf("\nOpen Order rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    return rc;
}

//--------------------------------------------------------------------------------------
int OpenOrderReferenceVzTypeDate(const short VzNr, const long CustomerNo, const char *Reference, const char *OrderTyp, const char *KoArt, const char *BuchArt, const char *SubOrderTyp, const long DeliveryDate, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    if(iCheckDouble == 1) d.SCHECKDOUBLE[0] = '1';
    iCheckDouble = 0;

    if (iNoRouting == 1) d.SWNOROUTING = 1;
    iNoRouting = 0;

    d.CUSTOMERNO = CustomerNo;
    d.BRANCHNO = VzNr;
    d.DELIVERYDATE = DeliveryDate;
    strncpy(d.REMARKS,Reference,L_KSCSRVDATA_REMARKS);
    ppGStrCopy(d.KINDOFORDER,    OrderTyp,    L_KSCSRVDATA_KINDOFORDER   );
    ppGStrCopy(d.SHIPMENTTYPE,   KoArt,       L_KSCSRVDATA_SHIPMENTTYPE  );
    ppGStrCopy(d.BOOKINGTYPE,    BuchArt,     L_KSCSRVDATA_BOOKINGTYPE   );
    ppGStrCopy(d.SUB_ORDER_TYPE, SubOrderTyp, L_KSCSRVDATA_SUB_ORDER_TYPE);

    /* new order */
    rc = ServerNr(ServNr,KscsrvNeworderVz,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    if (rc != 0)
    {
        CopyInfo(&d,Info);
        return rc;
    }
    /*rc = ServerNr(ServNr,KscsrvCheckReference,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg); */
    CopyInfo(&d,Info);
    if (rc != 0)
    {
        return rc;
    }
#ifdef PPDEBUG
    printf("\nOpen Order rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    return rc;
}

//--------------------------------------------------------------------------------------
int CloseOrderInternet (const char *strText, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    strncpy(d.REMARKS,strText,L_KSCSRVDATA_REMARKS);

    if ( CheckPrinting(*strText) && *strText != ' ' )
    {
       rc = ServerNr(ServNr,KscsrvChangeOrdBem,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
       if ( rc < 0 )
       {
            CopyInfo(&d,Info);
           return rc;
       }
    }

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    /* close order */
    rc = ServerNr(ServNr,KscsrvCloseorderInternet,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nCloseOrderInternet rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int PostponeOrderInternet(orderinfoS *Info )
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    /* new order */
    rc = ServerNr(ServNr,KscsrvPostponeorderinternet,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nPostponeOrderInternet rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int OpenOrderInternetOrderno( const long lOrderNo, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    d.ORDERNO = lOrderNo;

    /* new order */
    rc = ServerNr(ServNr,KscsrvOpenorderInternetOrderno,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nOpenOrderInternetOrderno rc: %d, Auftrags-Nr: %d,%d\n",rc,d.KDAUFTRAGNR,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int OpenOrderOrderno( const long lOrderNo, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    d.ORDERNO = lOrderNo;

    /* new order */
    rc = ServerNr(ServNr,KscsrvOpenorder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nOpenOrderOrderno rc: %d, Auftrags-Nr: %d,%d\n",rc,d.KDAUFTRAGNR,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int AddOrderHeadItem(const char *strText, orderinfoS *Info)
{
    int rc;
    struct N_KSCSRVDATA d;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    ppGStrCopy( d.REMARKS, strText, L_KSCSRVDATA_REMARKS );

    rc = ServerNr(ServNr,KscsrvInsKopfZlnAuf,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nAddOrderHeadItem rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",strText);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetReferenceNo(const long CustomerNo, const char *Reference, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.CUSTOMERNO = CustomerNo;
    strncpy(d.REMARKS,Reference,L_KSCSRVDATA_REMARKS);

    rc = ServerNr(ServNr,KscsrvInsertReference,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int CheckDoubleOrder(orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    rc = ServerNr(ServNr,KscsrvCheckDoubleOrder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetCallback(orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    rc = ServerNr(ServNr,KscsrvAddCallback,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetDeliveryDate(const long Date, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.TOURDATE = Date;
    rc = ServerNr(ServNr,KscsrvSetdelayeddate,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int GetArticleInfo(stArticleInfo *Info)
{
    struct N_ARTICLEINQUIRY d;
    int rc;

    buf_default((void *) &d, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
    PutArticleInfo(&d,Info);
    rc = ServerNr(ServNr,KscsrvGetArticleInfo,(void *)&d,ARTICLEINQUIRY_BES,ARTICLEINQUIRY_ANZ,error_msg);
    ConvertArticleInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int GetArticleInfoCode(stArticleInfoCode *Info)
{
    struct N_ARTICLEINQUIRY d;
    int rc;

    buf_default((void *) &d, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
    PutArticleInfoCode(&d,Info);
    rc = ServerNr(ServNr,KscsrvGetArticleInfoCode,(void *)&d,ARTICLEINQUIRY_BES,ARTICLEINQUIRY_ANZ,error_msg);
    ConvertArticleInfoCode(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int GetArticleInquiry(const long Qty, const long number, const char *EAN, const short Infolevel, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ARTICLENO = number;
    d.ORDERQTY = Qty;
    d.INFOLEVEL = Infolevel;
    strncpy(d.EAN,EAN,L_KSCSRVDATA_EAN);

    rc = ServerNr(ServNr,KscsrvGetArticleInquiry,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int GetArticleInquiryCode(const long Qty, const char *Code, const short Infolevel, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    d.INFOLEVEL = Infolevel;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);

    rc = ServerNr(ServNr,KscsrvGetArticleInquiry,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int GetArticleStock(const long Qty, const char *Code, const short Infolevel, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.ORDERQTY = Qty;
    d.INFOLEVEL = Infolevel;
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);

    rc = ServerNr(ServNr,KscsrvGetArticleStock,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
void CopyInfo(kscsrvdataS *d,orderinfoS *Info)
{
    strncpy(Info->ARTICLEUNIT,d->ARTICLEUNIT,L_ORDERINFO_ARTICLEUNIT);
    strncpy(Info->ARTICLENAME,d->ARTICLENAME,L_ORDERINFO_ARTICLENAME);
    strncpy(Info->HANDOUT,d->HANDOUT,L_ORDERINFO_HANDOUT);
    strncpy(Info->EAN,d->EAN,L_ORDERINFO_EAN);
    strncpy(Info->TEXT,d->TEXT,L_ORDERINFO_TEXT);
    strncpy(Info->TOURID,d->TOURID,L_ORDERINFO_TOURID);
    strncpy(Info->TOURIDIBT,d->TOURIDIBT,L_ORDERINFO_TOURIDIBT);
    strncpy(Info->CODEBLOCAGE,d->CODEBLOCAGE,L_ORDERINFO_CODEBLOCAGE);
    strncpy(Info->LACKREASONCTYCODE,d->LACKREASONCTYCODE,L_ORDERINFO_LACKREASONCTYCODE);
    strncpy(Info->MANUFACTURERNAME,d->MANUFACTURERNAME,L_ORDERINFO_MANUFACTURERNAME);
    strncpy(Info->PHARMACYNAME,d->PHARMACYNAME,L_ORDERINFO_PHARMACYNAME);
    strncpy(Info->AVAILABLE,d->AVAILABLE,L_ORDERINFO_AVAILABLE);
    strncpy(Info->ARTICLEUNITORG,d->ARTICLEUNITORG,L_ORDERINFO_ARTICLEUNITORG);
    strncpy(Info->ARTICLENAMEORG,d->ARTICLENAMEORG,L_ORDERINFO_ARTICLENAMEORG);
    strncpy(Info->HANDOUTORG,d->HANDOUTORG,L_ORDERINFO_HANDOUTORG);
    strncpy(Info->EANORG,d->EANORG,L_ORDERINFO_EANORG);
    strncpy(Info->SERACODE,d->SERACODE,L_ORDERINFO_SERACODE);
    strncpy(Info->XMLCODE,d->XMLCODE,L_ORDERINFO_XMLCODE);
    strncpy(Info->XMLTEXT,d->XMLTEXT,L_ORDERINFO_XMLTEXT);
    strncpy(Info->LACKREASONCTYCODE,d->LACKREASONCTYCODE,L_ORDERINFO_LACKREASONCTYCODE);
    strncpy(Info->CODEBLOCAGEORG,d->CODEBLOCAGEORG,L_ORDERINFO_CODEBLOCAGEORG);
    strncpy(Info->SERACODEORG,d->SERACODEORG,L_ORDERINFO_SERACODEORG);
    strncpy(Info->XMLCODEORG,d->XMLCODEORG,L_ORDERINFO_XMLCODEORG);
    strncpy(Info->XMLTEXTORG,d->XMLTEXTORG,L_ORDERINFO_XMLTEXTORG);
    strncpy(Info->ARTICLETEXT,d->ARTICLETEXT,L_ORDERINFO_ARTICLETEXT);
    strncpy(Info->HEALTHFUNDCODE,d->HEALTHFUNDCODE,L_ORDERINFO_HEALTHFUNDCODE);
    strncpy(Info->ARTIKEL_LANGNAME,d->ARTIKEL_LANGNAME,L_ORDERINFO_ARTIKEL_LANGNAME);
    strncpy(Info->ARTICLE_CODE,d->ARTICLE_CODE,L_ORDERINFO_ARTICLE_CODE);
    strncpy(Info->ARTICLE_CODEORG,d->ARTICLE_CODEORG,L_ORDERINFO_ARTICLE_CODEORG);
    strncpy(Info->POSTPONEREASON,d->POSTPONEREASON,L_ORDERINFO_POSTPONEREASON);
    strncpy(Info->XMLLINEREFERENCE,d->XMLLINEREFERENCE,L_ORDERINFO_XMLLINEREFERENCE);
    strncpy(Info->PROMONAME,d->PROMONAME,L_ORDERINFO_PROMONAME);
    strncpy(Info->ORDERLABEL,d->ORDERLABEL,L_ORDERINFO_ORDERLABEL);
    strncpy(Info->FEHLTEXT,d->FEHLTEXT,L_ORDERINFO_FEHLTEXT);
    strncpy(Info->LACKREASONLIST,d->LACKREASONLIST, L_ORDERINFO_LACKREASONLIST);
    Info->ORDERQTY = d->ORDERQTY;
    Info->ORDERNO = d->ORDERNO;
    Info->QTYLACK = d->QTYLACK;
    Info->LACKREASON = d->LACKREASON;
    Info->AUXQTY = d->AUXQTY;
    Info->ARTICLENOORG = d->ARTICLENOORG;
    Info->AUXBRANCHNO = d->AUXBRANCHNO;
    Info->ORDERQTY = d->ORDERQTY;
    Info->RESTDELIVERYQTY = d->RESTDELIVERYQTY;
    Info->DISPOQTY = d->DISPOQTY;
    Info->DELIVERYQTY = d->DELIVERYQTY;
    Info->TOURDATE = d->TOURDATE;
    Info->PHARMPURCHPRICE = d->PHARMPURCHPRICE;
    Info->CUSTPURCHPRICE = d->CUSTPURCHPRICE;
    Info->PHARMSELLPRICE = d->PHARMSELLPRICE;
    Info->BASEPRICE = d->BASEPRICE;
    Info->TAXRATE = d->TAXRATE;
    Info->TAXVALUE = d->TAXVALUE;
    Info->EXPIRYDATE = d->EXPIRYDATE;
    Info->VALUEOFORDER = d->VALUEOFORDER;
    Info->LINESOFORDER = d->LINESOFORDER;
    Info->LACKLINES = d->LACKLINES;
    Info->TEXTLINES = d->TEXTLINES;
    Info->DATEOFUPDATE = d->DATEOFUPDATE;
    Info->QTYRESERVATION = d->QTYRESERVATION;
    Info->ARTICLENO = d->ARTICLENO;
    Info->LPPR_PRICE = d->LPPR_PRICE;
    Info->PHARMPURCHPRICEORG = d->PHARMPURCHPRICEORG;
    Info->CUSTPURCHPRICEORG = d->CUSTPURCHPRICEORG;
    Info->PHARMSELLPRICEORG = d->PHARMSELLPRICEORG;
    Info->TAXRATEORG = d->TAXRATEORG;
    Info->LPPR_PRICEORG = d->LPPR_PRICEORG;
    Info->DELIVERYBRANCHNO = d->DELIVERYBRANCHNO;
    Info->TFR_PRICE = d->TFR_PRICE;
    Info->TFR_PRICEORG = d->TFR_PRICEORG;
    Info->QTYNATRA = d->QTYNATRA;
    Info->LOGISTICSADDITION = d->LOGISTICSADDITION;
    Info->TIMEDELIVERY = d->TIMEDELIVERY;
    Info->PREISFAKTUR = d->PREISFAKTUR;
    Info->WERTNETTO_FV = d->WERTNETTO_FV;
    Info->WERTTAX_FV = d->WERTTAX_FV;
    Info->WERTNETTO_KK = d->WERTNETTO_KK;
    Info->WERTTAX_KK = d->WERTTAX_KK;
    Info->WERTNETTO_EH = d->WERTNETTO_EH;
    Info->WERTTAX_EH = d->WERTTAX_EH;
    Info->ORDVALFTAXFS = d->ORDVALFTAXFS;
    Info->ORDVALFTAXFSDISC = d->ORDVALFTAXFSDISC;
    Info->ORDVALFTAXHF = d->ORDVALFTAXHF;
    Info->ORDVALFTAXHFDISC = d->ORDVALFTAXHFDISC;
    Info->ORDVALFTAXRS = d->ORDVALFTAXRS;
    Info->ORDVALFTAXRSDISC = d->ORDVALFTAXRSDISC;
    Info->ORDVALLTAXFS = d->ORDVALLTAXFS;
    Info->ORDVALLTAXFSDISC = d->ORDVALLTAXFSDISC;
    Info->ORDVALLTAXHF = d->ORDVALLTAXHF;
    Info->ORDVALLTAXHFDISC = d->ORDVALLTAXHFDISC;
    Info->ORDVALLTAXRS = d->ORDVALLTAXRS;
    Info->ORDVALLTAXRSDISC = d->ORDVALLTAXRSDISC;
    Info->TAXVALFTAXFS = d->TAXVALFTAXFS;
    Info->TAXVALFTAXFSDISC = d->TAXVALFTAXFSDISC;
    Info->TAXVALFTAXHF = d->TAXVALFTAXHF;
    Info->TAXVALFTAXHFDISC = d->TAXVALFTAXHFDISC;
    Info->TAXVALFTAXRS = d->TAXVALFTAXRS;
    Info->TAXVALFTAXRSDISC = d->TAXVALFTAXRSDISC;
    Info->TAXVALLTAXFS = d->TAXVALLTAXFS;
    Info->TAXVALLTAXFSDISC = d->TAXVALLTAXFSDISC;
    Info->TAXVALLTAXHF = d->TAXVALLTAXHF;
    Info->TAXVALLTAXHFDISC = d->TAXVALLTAXHFDISC;
    Info->TAXVALLTAXRS = d->TAXVALLTAXRS;
    Info->TAXVALLTAXRSDISC = d->TAXVALLTAXRSDISC;
    Info->SWCASH[0] = d->SWCASH[0];
    Info->PREISEKGROSSO = d->PREISEKGROSSO;
    Info->DISCOUNTVALUEPCT = d->DISCOUNTVALUEPCT;
    Info->MARGIN = d->MARGIN;
    Info->VALRESTCL = d->VALRESTCL;
    Info->VALRESTDISCACC = d->VALRESTDISCACC;
    Info->MAXAVP = d->MAXAVP;
    Info->INFOLEVEL = d->INFOLEVEL;
    Info->DELIVERYTIMEIBT = d->DELIVERYTIMEIBT;
    Info->TOURDATEIBT = d->TOURDATEIBT;
    Info->PROMOTYP = d->PROMOTYP;
    Info->PID = d->PID;
    Info->PROMONO = d->PROMONO;
    Info->AUXQTYPOSSIBLE = d->AUXQTYPOSSIBLE;
    Info->ERRORNO = d->ERRORNO;
    Info->DELIVERYDATEIBT = d->DELIVERYDATEIBT;
    Info->DELIVERYDATE = d->DELIVERYDATE;
    Info->IBTTYPE = d->IBTTYPE;
    Info->ISDAYIBT = d->ISDAYIBT;
    Info->KARENZZEIT = d->KARENZZEIT;
    Info->KARENZZEITIBT = d->KARENZZEITIBT;
    Info->NEXTTOURCLOSINGTIME = d->NEXTTOURCLOSINGTIME;
    Info->ACTTOURCLOSINGTIME = d->ACTTOURCLOSINGTIME;
    Info->NEXTTOURDELIVERYTIME = d->NEXTTOURDELIVERYTIME;
    Info->RELATIONNO = d->RELATIONNO;
    Info->RELATIONNOTYPE = d->RELATIONNOTYPE;
    Info->APPROVALCANCEL = d->APPROVALCANCEL;
    Info->APPROVALCLOSE = d->APPROVALCLOSE;
    Info->APPROVALPERSONSNEEDED = d->APPROVALPERSONSNEEDED;
    Info->ACTTOURCLOSINGDATE = d->ACTTOURCLOSINGDATE;
    Info->NEXTTOURCLOSINGDATE = d->NEXTTOURCLOSINGDATE;
    Info->NEXTTOURDELIVERYDATE = d->NEXTTOURDELIVERYDATE;
    Info->POSTAGE = d->POSTAGE;
    Info->PREDICTEDAVAILABILITYDATE = d->PREDICTEDAVAILABILITYDATE;
}

void PutArticleInfo(articleinquiryS *d,stArticleInfo *Info)
{
    int i;
    char *pArt = d->INFOBLOCK;
    for(i = 0;i < 250; i++)
    {
        if(Info->Articles[i].ARTICLENO == 0) break;
        sprintf(pArt,"%07ld ",Info->Articles[i].ARTICLENO);
        pArt += 8;
    }
}

void ConvertArticleInfo(articleinquiryS *d,stArticleInfo *Info)
{
    int i;
    char *pArt = d->INFOBLOCK;
    char huelse[8];
    for(i = 0;i < 250; i++)
    {
        if(!strncmp(pArt,"       ",7)) break;
        sprintf(huelse,"%7.7s",pArt);
        Info->Articles[i].ARTICLENO = atol(huelse);
        Info->Articles[i].AVAILABLE = pArt[7];
        pArt += 8;
        }
}

void PutArticleInfoCode(articleinquiryS *d,stArticleInfoCode *Info)
{
    char tmp[26];
    int i;
    char *pArt = d->INFOBLOCK;
    for(i = 0;i < 150; i++)
    {
        sprintf(tmp, "%-25s", Info->ArticlesCode[i].ARTICLECODE);
        if(tmp[0] == ' ') break;
        sprintf(pArt,"%25s ",tmp);
        pArt += 26;
    }
}

void ConvertArticleInfoCode(articleinquiryS *d,stArticleInfoCode *Info)
{
    int i;
    char *pArt = d->INFOBLOCK;
    for(i = 0;i < 150; i++)
    {
        if(!strncmp(pArt,"       ",7)) break;
        sprintf(Info->ArticlesCode[i].ARTICLECODE,"%25.25s",pArt);
        Info->ArticlesCode[i].AVAILABLE = pArt[25];
        pArt += 26;
    }
}

//--------------------------------------------------------------------------------------
void SetCheckDouble()
{
    iCheckDouble = 1;
}

//-------Kein Routing-------------------------------------------------------------------
void SetNoRouting()
{
    iNoRouting = 1;
}

//--------------------------------------------------------------------------------------
int SetTourId(const char *TourId, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy(d.TOURID,TourId,L_KSCSRVDATA_TOURID);
    rc = ServerNr(ServNr,KscsrvSetTourId,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\SetTourId rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}// SetTourId

//--------------------------------------------------------------------------------------
int SetTourAndDeliveryDate(const long DeliveryDate, const char *TourId, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy(d.TOURID,TourId,L_KSCSRVDATA_TOURID);
    d.TOURDATE = DeliveryDate;
    rc = ServerNr(ServNr,KscsrvChangeDeliveryTour,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\SetTourAndDeliveryDate rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetBTMLicense(const long datum, const char *btmlicence, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy(d.BTMFORMULARNR,btmlicence,L_KSCSRVDATA_BTMFORMULARNR);
    d.DATUMBTM = datum;
    rc = ServerNr(ServNr,KscsrvSetBTMLicense,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\SetTourId rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}// SetBTMLicense

//--------------------------------------------------------------------------------------
int OpenProformaOrder(const short VzNr, const long CustomerNo, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    d.BRANCHNO = VzNr;
    d.CUSTOMERNO = CustomerNo;

    rc = ServerNr(ServNr,KscsrvProformaorder,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}//OpenProformaOrder

//--------------------------------------------------------------------------------------
int GetPositions( orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    rc = ServerNr(ServNr,KscsrvGetProforma,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}//OpenProformaOrder

//--------------------------------------------------------------------------------------
int SetROParam(const long DatumVon, const long DatumBis, const char *KzKette, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.KZROKETTE[0] = KzKette[0];
    d.DATUMROVON = DatumVon;
    d.DATUMROBIS = DatumBis;
    rc = ServerNr(ServNr,KscsrvSetROParam,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\SetTourId rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}// SetROParam

//--------------------------------------------------------------------------------------
int SetProLink  (const long KdauftragnrPro, const long DatumPro, const char *RechnrPro, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy( d.REMARKS, RechnrPro, L_KSCSRVDATA_REMARKS );
    d.ORDERNOORIGIN = KdauftragnrPro;
    d.TOURDATE = DatumPro;
    rc = ServerNr(ServNr,KscsrvWriteProLink,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
    return rc;
}// SetProLink

//--------------------------------------------------------------------------------------
int SetOrderInfoDetails (const long pharmacyorderno, const long pharmacycustomerno, const char* customertour, const char* typeofdispatch, const long processid, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc = 0;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    d.ORDERNO = pharmacyorderno;
    d.CUSTOMERNO = pharmacycustomerno;
    ppGStrCopy( d.XMLLINEREFERENCE, customertour, L_KSCSRVDATA_XMLLINEREFERENCE );
    ppGStrCopy( d.POSTPONEREASON, typeofdispatch, L_KSCSRVDATA_POSTPONEREASON );
    d.PID = processid;

    rc = ServerNr(ServNr,KscsrvSetOrderInfoDetails,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);

    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int CloseOrderDebtlimit (const char *strReason,const char *strComment,const char *strUser,const char *strGuid,const char *strUrl, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy( d.TEXT, strReason, L_KSCSRVDATA_TEXT );
    ppGStrCopy( d.ARTICLETEXT, strComment, L_KSCSRVDATA_ARTICLETEXT );
    ppGStrCopy( d.REMARKS, strUser, L_KSCSRVDATA_REMARKS );
    ppGStrCopy( d.XMLTEXT, strGuid, L_KSCSRVDATA_XMLTEXT );
    ppGStrCopy( d.XMLTEXTORG, strUrl, L_KSCSRVDATA_XMLTEXTORG );

    /* close order */
    rc = ServerNr(ServNr,KscsrvCloseorderDebtLimit,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nCloseOrder rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}// CloseOrderDebtlimit

//--------------------------------------------------------------------------------------
int CancelOrderDebtlimit (const char *strReason,const char *strComment,const char *strUser,const char *strGuid,const char *strUrl, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    ppGStrCopy( d.TEXT, strReason, L_KSCSRVDATA_TEXT );
    ppGStrCopy( d.ARTICLETEXT, strComment, L_KSCSRVDATA_ARTICLETEXT );
    ppGStrCopy( d.REMARKS, strUser, L_KSCSRVDATA_REMARKS );
    ppGStrCopy( d.XMLTEXT, strGuid, L_KSCSRVDATA_XMLTEXT );
    ppGStrCopy( d.XMLTEXTORG, strUrl, L_KSCSRVDATA_XMLTEXTORG );

    /* cancel order */
    rc = ServerNr(ServNr,KscsrvCancelorderDebtLimit,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nCloseOrder rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}// CancelOrderDebtlimit

//--------------------------------------------------------------------------------------
int GetApprovalData (const long orderNo, const short branchNo, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.BRANCHNO = branchNo;
    d.ORDERNO = orderNo;
    rc = ServerNr(ServNr,KscsrvGetApprovalData,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\nGetApprovalData rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}// CancelOrderDebtlimit

//--------------------------------------------------------------------------------------
int OpenOrderMSV3(const short VzNr,
                    const long CustomerNo,
                    const char *OrderTyp,
                    const char *KoArt,
                    const char *BuchArt,
                    const char *OrderLabel,
                    orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;
    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    if(iCheckDouble == 1) d.SCHECKDOUBLE[0] = '1';
    iCheckDouble = 0;

    if (iNoRouting == 1) d.SWNOROUTING = 1;
    iNoRouting = 0;

    d.CUSTOMERNO = CustomerNo;
    d.BRANCHNO = VzNr;
    sprintf(d.ORDERLABEL,"%-*.*s",L_KSCSRVDATA_ORDERLABEL,L_KSCSRVDATA_ORDERLABEL,OrderLabel);
    ppGStrCopy(d.KINDOFORDER,  OrderTyp, L_KSCSRVDATA_KINDOFORDER   );
    ppGStrCopy(d.SHIPMENTTYPE, KoArt,    L_KSCSRVDATA_SHIPMENTTYPE  );
    ppGStrCopy(d.BOOKINGTYPE,  BuchArt,  L_KSCSRVDATA_BOOKINGTYPE   );

    /* new order */
    rc = ServerNr(ServNr,KscsrvNeworderMSV3,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
    CopyInfo(&d,Info);
#ifdef PPDEBUG
    printf("\nOpen Order MSV3 rc: %d, Auftrags-Nr: %d,%d\n",rc,d.ORDERNO,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    if (rc != 0)
    {
        return rc;
    }
    return rc;
}// OpenOrderMSV3

//--------------------------------------------------------------------------------------
int SetValueDate(const int ValutaDatum, orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.VALUTADATUM = ValutaDatum;

    /* set batchschreiben */
    rc = ServerNr(ServNr,KscsrvSetValueDate,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\KscsrvSetValueDate rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

//--------------------------------------------------------------------------------------
int SetBatchValueDate(const int Batchschreiben,const short BranchNoOrigin,const int ValutaDatum,orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.BATCHSCHREIBEN = Batchschreiben;
    d.BRANCHNOORIGIN = BranchNoOrigin;
    d.VALUTADATUM = ValutaDatum;

    /* set batchschreiben */
    rc = ServerNr(ServNr,KscsrvSetValueDate,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);
#ifdef PPDEBUG
    printf("\KscsrvSetValueDate rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif
    CopyInfo(&d,Info);
    return rc;
}

/************************************************************************/
/* Bulk-Verfügbarkeitsanfrage                                           */
/* articles char[4000] semikolon-separierte Liste von Artikelnummern    */
/************************************************************************/
int GetArticleAvailabilityBulk(const short branchno, const long customerno, char* articleList)
{
    struct N_ARTICLEINQUIRYBULK d;
    int rc;

    if (strlen(articleList) > L_ARTICLEINQUIRYBULK_INFOBLOCK)
        return -1;

    buf_default((void *) &d, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
    d.BRANCHNO = branchno;
    d.CUSTOMERNO = customerno;
    ppGStrCopy(d.INFOBLOCK, articleList, L_ARTICLEINQUIRYBULK_INFOBLOCK);
    rc = ServerNr(ServNr, KscsrvGetArticleAvailabilityBulk, (void*)&d, ARTICLEINQUIRYBULK_BES,ARTICLEINQUIRYBULK_ANZ, error_msg);
    ppGStrCopy(articleList, d.INFOBLOCK, L_ARTICLEINQUIRYBULK_INFOBLOCK);
    return rc;
}

/************************************************************************/
/* Bulk-Bestandssanfrage                                                */
/* articles char[4000] semikolon-separierte Liste von Artikelnummern    */
/************************************************************************/
int GetArticleStockBulk(const short branchno, const long customerno, char* articleList)
{
    struct N_ARTICLEINQUIRYBULK d;
    int rc;

    if (strlen(articleList) > L_ARTICLEINQUIRYBULK_INFOBLOCK)
        return -1;

    buf_default((void *) &d, ARTICLEINQUIRY_BES, ARTICLEINQUIRY_ANZ);
    d.BRANCHNO = branchno;
    d.CUSTOMERNO = customerno;
    ppGStrCopy(d.INFOBLOCK, articleList, L_ARTICLEINQUIRYBULK_INFOBLOCK);
    rc = ServerNr(ServNr, KscsrvGetArticleStockBulk, (void*)&d, ARTICLEINQUIRYBULK_BES,ARTICLEINQUIRYBULK_ANZ, error_msg);
    ppGStrCopy(articleList, d.INFOBLOCK, L_ARTICLEINQUIRYBULK_INFOBLOCK);
    return rc;
}

/*************************************************************************/
// SetOrderInfoDetails
/*************************************************************************/
int SetTurnOverOrigin (orderinfoS *Info)
{
    struct N_KSCSRVDATA d;
    int rc = 0;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    rc = ServerNr(ServNr,KscsrvSetTurnOverOrigin,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);

    CopyInfo(&d,Info);
    return rc;
}

/*************************************************************************/
int GetManufacturerForArticle(const char *Code, orderinfoS *Info)
{
    int rc = 0;

    struct N_KSCSRVDATA d;

    buf_default((void *) &d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    strncpy(d.ARTICLE_CODE,Code,L_KSCSRVDATA_ARTICLE_CODE);

    rc = ServerNr(ServNr,KscsrvGetArticleManufacturer,(void *)&d,KSCSRVDATA_BES,KSCSRVDATA_ANZ,error_msg);

#ifdef PPDEBUG
    printf("\KscsrvGetArticleManufacturer rc: %d,Server: %d\n",rc,ServNr);
    if (rc < 0) printf ("%s\n",error_msg);
#endif

    CopyInfo(&d,Info);
    return rc;
}

int IsExportPermitted(const short branchNo, const long customerNo, const long articleNo, orderinfoS* info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void*)&d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);
    d.BRANCHNO = branchNo;
    d.CUSTOMERNO = customerNo;
    d.ARTICLENO = articleNo;

    rc = ServerNr(ServNr, KscsrvIsExportPermitted, (void*)&d, KSCSRVDATA_BES, KSCSRVDATA_ANZ, error_msg);
    CopyInfo(&d, info);
    return rc;
}

int ChangePaymentToCashOrder(orderinfoS* info)
{
    struct N_KSCSRVDATA d;
    int rc;

    buf_default((void*)&d, KSCSRVDATA_BES, KSCSRVDATA_ANZ);

    rc = ServerNr(ServNr, KscsrvChangePaymentToCashOrder, (void*)&d, KSCSRVDATA_BES, KSCSRVDATA_ANZ, error_msg);
    CopyInfo(&d, info);
    return rc;
}
