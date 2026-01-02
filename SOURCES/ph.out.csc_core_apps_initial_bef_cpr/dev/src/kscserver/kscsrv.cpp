/* Kscsrv.cpp */
#undef TRANSCLASS

/*****************************************************************************/
/* Includes                                                                  */
/*****************************************************************************/

#include "bufkon.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include "kscsrvdata.h"
#include "articleinquiry.h"
#include "articleinquirybulk.h"
#include "texte.h"
#include "pxorder.hpp"
#include "pxxmit.hpp"
#include "pxcountrycodes.hpp"
#include "pxxmldefs.h"
#include "pxarticletext.hpp"
#include "pxdelpos.hpp"
#include "pxarticleinfo.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcustinf.hpp"
#include "pxparameter.hpp"
#include "pxoeparm.hpp"
#include "pxbranch.hpp"
#include "pxcstot.hpp"
#include "kscsrv.h"
#include "seralog.hpp"
#include "artcodes.h"
#include "promotions.h"
#include "auftraginfo.h"
#include "lackdefines.h"
#include "pxstockbulkinquiry.hpp"
#include "tourinfo.hpp"
#include "aarufpl.h"
#include "pxartmas.hpp"
#include "tourassignmentutil.hpp"
#include "tourmanager.hpp"
#include "pxsuppldeliveryinfo.hpp"
#include "pxorderremarks.hpp"
#include <pxbase/pxconstants.hpp>
#include <libbasarcmnutil_datetime.h>
#include <libbasarcmnutil_i18nstring.h>

#include "pxeventreason.hpp"
#include <base/irunnable.h>

#include <signal.h>
#include "allg.h"
#ifndef WIN32
#include <sys/time.h>
#include <sys/resource.h>
#else
#include <process.h>
#endif
#include <logger/loggerconfig.h>
#include <pxordervalues.hpp>
#include <pxtxtdoc.hpp>
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"

#ifdef __cplusplus
extern "C" {
#endif
int kscartSel_NoByCode(artcodesS *d, char *error_msg);
int kscartSel_Preferred(artcodesS *d, char *error_msg);
int kscSel_Promotion(promotionsS *d, char *error_msg);
int kscProlink_Insert(prolinkS *d, char *error_msg);
int kscProlinkact_Insert(prolinkactS *d, char *error_msg);
int kscCheck_Callplan(struct RUFPTAG *d, char *error_msg);
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
/* Definitionen                                                              */
/*****************************************************************************/
#define NOT_FOUND        1
#define FILE_NOT_FOUND   1

/*****************************************************************************/
/* Globale Variablen                                                         */
/*****************************************************************************/
static pxOrderTransmit *ps;                     //Pointer auf die Session
static nSeraLog *logdat;                        //Pointer auf Seralog
static pxParameter *locklevelparam;
long UID;
#ifdef WIN32
static  int testpid;
#else
static  pid_t testpid;
#endif

/*
        level 0 : kein Seralog
        level 1 : nur Auftraege
        level 2 : auch Anfragen, aber nur minimal
        level 3 : alles
*/
static long sLogLevel;
static long sMinLogLevel;
static pxOrderItemList   *oItemList;                   //Liste von Positionen

int KscsrvConvUmlaut(char *d, int maxlen);
void initLog4Cplus();
void transferDeliveryInformation( struct N_KSCSRVDATA *d, pxOrderItem* orderitem, bool isAvailabilityRequest = false );
void transferOrderDeliveryInformation( struct N_KSCSRVDATA *d );
long getArticleNoFromCode( struct N_KSCSRVDATA *d, char *error_msg );
void openLogWithDummyIdf(long const minLogLevel);
void writeLog(const std::stringstream& logtext);
basar::I18nString getCurrentTimeHMS();
void emptyStringstream(std::stringstream& logtext);
void writeEndCloseLogOnUnknownError(std::stringstream& logtext);
void writeEndCloseLogOnBasarException(std::stringstream& logtext, basar::Exception const& ex);
void writeEndCloseLog(const std::stringstream& logtext);
void allgStrCopy(char* target, libcsc::VarString const source, unsigned max);

/*****************************************************************************/
/** Session                                                                 **/
/*****************************************************************************/

/*****************************************************************************/
/* Oeffnen einer Serversitzung                                               */
/*****************************************************************************/
int KscsrvOpensession(struct N_KSCSRVDATA *d, char *error_msg)
{
    char inipath[256+1];
    char ini_file[256+1];

    d->LACKREASON = 0;
    sLogLevel = 1;

    const char* WWS_INI = getenv("INI_PATH");
    if (WWS_INI == NULL)
    {
        strcpy(&inipath[0], "../ini");
    }
    else
    {
        strcpy(&inipath[0], WWS_INI);
    }

#ifdef WIN32
    testpid = _getpid();
#else
    testpid = getpid();
#endif

#ifdef WIN32
    sprintf(&ini_file[0], "%s\\kscserver.ini", &inipath[0]);
#else
    sprintf(ini_file, "%s/kscserver.ini", inipath);
#endif
    ps = new pxOrderTransmit(&ini_file[0]);
    logdat = new nSeraLog();
    if ( ! (ps->IsGoodState()) )
    {
        if( (d->LACKREASON = ps->ErrorNumber()) == -1)    //Fehler beim Oeffnen der Pipe
        {
            AllgStrCopy(&d->TEXT[0], TXT_KEINE_ASPIPE_VERB, MAX_ERROR_MSG_AE);
            return 6;
        }
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        return 6;
    }

    ps->Session()->Device()->Name(&d->DEVICENAME[0]);
    if (!strncmp("CSCBATCH", &d->DEVICENAME[0], 7) || (!strncmp("ABBA", &d->DEVICENAME[0], 4)))
    {
        ps->Session()->Device()->Type(pxDVC_FILE);
    }
    else
    {
        ps->Session()->Device()->Type(pxDVC_DCT_SERIAL);
    }
    ps->Session()->PersonnelNo(d->UID);
    ps->Session()->UsersFilialNr(d->BRANCHNO);
    ps->SetTransmissionType(pxOrderTransmit :: tDCT_Serial);

    if(d->BRANCHNO != 0)
    {
        pxBranch CustBranch(ps->Session(), d->BRANCHNO);
        if (CustBranch.IsGoodState())
        {
            *(ps->Session()->Branch()) = CustBranch;
        }
        else
        {
            return 6;
        }
    }

    AllgStrToUpper(&d->DEVICENAME[0]);
    nString cDeviceName;
    cDeviceName = &d->DEVICENAME[0];
    cDeviceName.Strip();

    d->PID = testpid;

    ps->Session()->SetSubDeviceType(cDeviceName);
    return 0;
}

/*****************************************************************************/
/* Schliessen einer Serversitzung                                            */
/*****************************************************************************/
int KscsrvClosesession(struct N_KSCSRVDATA *d, char *error_msg)
{
    d->LACKREASON = 0;
    delete ps;
    error_msg[0] = '\0';

    return 0;
}

/*****************************************************************************/
/** Auftrag                                                                 **/
/*****************************************************************************/

/*****************************************************************************/
/* Oeffnen eines Auftrages                                                   */
/*****************************************************************************/
int KscsrvOpenorder(struct N_KSCSRVDATA *d, char *error_msg)
{
    ps->Reset();
    nTime now;
    d->LACKREASON = 0;
    ps->SetTransmissionType(pxOrderTransmit :: tDCT_Serial);
    d->LACKREASON = 0;
    nString tourid;             // ein String-Objekt
    nString logtext;             // ein String-Objekt
    ps->NewOrder(d->ORDERNO);
    if (ps->Order() ==  NULL )
    {
        AllgStrCopy(error_msg, TXT_AUFTR_NICHT_OFFEN , MAX_ERROR_MSG_AE);
        {
            return -2 ;
        }
    }
    ps->Order()->OpenOrder(cDBOPEN_INSERT);
    if ( ! (ps->Order()->IsGoodState()) )
    {
        AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->Order()->ErrorNumber();
        if(ps->Order()->ErrorNumber() == CMSG_ORD_ROUTE_NOMORE)
        {
            tourid = ps->Order()->TourId();
            ps->Order()->SetNextValidRoute(tourid);
        }
        else
        {
            AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
            d->LACKREASON = ps->Order()->ErrorNumber();
            if(sLogLevel > 0)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      OpenOrder Error ";
                logtext += ps->ErrorMsg();
                logdat->Write(logtext);
                if(d->LACKREASON != CMSG_ORD_ROUTE_NOMORE)
                {
                    logdat->End();
                    logdat->CloseSeralog();
                    return 6;
                }
            }
        }
    }
    return 0;
}

/*****************************************************************************/
/* Prüfen Referenznummer vorhanden                                           */
/*****************************************************************************/
int KscsrvCheckReference(struct N_KSCSRVDATA *d, char *error_msg)
{
    int rc;
    if (d->SCHECKDOUBLE[0] != '1') return 0;
    d->LACKREASON = 0;
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    rc = pxCheckReferenceNr(ps, d->BRANCHNO, d->CUSTOMERNO, &d->REMARKS[0]);
    if (rc != 0)
    {
        AllgStrCopy(&d->TEXT[0], &d->REMARKS[0], MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->REMARKS[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = rc;
        ps->SetDoubleOrder();
        return 1;
    }
    return 0;
}

/*****************************************************************************/
/* Oeffnen eines neuen Auftrages                                             */
/*****************************************************************************/
int KscsrvNeworder(struct N_KSCSRVDATA *d, char *error_msg)
{
    nTime now;
    pxCustBase* customer;
    short AlterVZ = 0;
    nString logtext;             // ein String-Objekt
    nString cVZ;                 // ein String-Objekt
    nString cOrder;              // ein String-Objekt
    nString cTerminal;           // ein String-Objekt
    nString cPid;                // ein String-Objekt
    nString cOt;                 // ein String-Objekt
    nString cSt;                 // ein String-Objekt
    nString cBt;                 // ein String-Objekt
    nString cDD;                 // ein String-Objekt
    char cCustomer[8];
    long lCustomerno;
    d->LACKREASON = 0;
    short sBranchno;
    locklevelparam = ps->GetLockLevelParam();
    if(locklevelparam == NULL)
        sLogLevel = 1;
    else
        sLogLevel = locklevelparam->Wert();
    sprintf(&cCustomer[0], "%ld", d->CUSTOMERNO);
    sprintf(cTerminal, "%4.4s", (char*)ps->Session()->Device()->Name());
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    if (sLogLevel > 0)
    {
        if(sLogLevel == 1)
            sLogLevel = 2;
        logdat->Start();
        logdat->SetIDFNr(&cCustomer[0]);
        logdat->SetTerminalID((char*)cTerminal);
        logdat->Open();
        logdat->WriteList();
        cVZ = ps->Session()->Branch()->FilialNr();
        cVZ.Trim(2,nString::cLEADING,'0');
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  OpenOrder Branchno: " + cVZ + " Customer: " + &cCustomer[0];
        logtext += " OrderType: ";
        logtext += &d->KINDOFORDER[0];
        if(d->SHIPMENTTYPE[0] != ' ')
        {
            logtext += " ShippingType: ";
            logtext += &d->SHIPMENTTYPE[0];
        }
        if(d->BOOKINGTYPE[0] != ' ')
        {
            logtext += " BookingType: ";
            logtext += &d->BOOKINGTYPE[0];
        }
        if(d->SCHECKDOUBLE[0] == '1')
        {
            logtext += " CheckDouble";
            logtext += &d->REMARKS[0];
        }
        if(d->DELIVERYDATE > 0)
        {
            logtext += " DeliveryDate ";
            sprintf(cDD, "%ld", d->DELIVERYDATE);
            logtext += cDD;
        }
        logdat->Write(logtext);
    }
    ps->SetTransmissionType(pxOrderTransmit :: tDCT_Serial);


    sBranchno = ps->Session()->Branch()->FilialNr();
    if (d->SWNOROUTING == 0)
    {
        AlterVZ = ps->CustomerRouting(d->CUSTOMERNO);
    }
    if(AlterVZ > 0)
    {
        sBranchno = AlterVZ;
        cVZ = AlterVZ;
        cVZ.Trim(2,nString::cLEADING,'0');
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      routed Branchno: " + cVZ;
            logdat->Write(logtext);
        }
    }
    cOt = &d->KINDOFORDER[0];
    lCustomerno = ps->getCustomerSpecialsUWIDFNr(sBranchno, d->CUSTOMERNO, cOt);
    if(lCustomerno == 0)
    {
        lCustomerno = d->CUSTOMERNO;
    }
    else
    {
        sprintf(&cCustomer[0], "%ld", lCustomerno);
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      Customerno changed to: ";
            logtext += &cCustomer[0];
            logdat->Write(logtext);
        }
    }

    if (!ps->IsNewOrder(sBranchno))
    {
        strcpy(error_msg, " ");  // uninterresant
        if (sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenOrder Out of Time ";
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return -5;
    }

    if (ps->Session()->isBulgaria())
    {
        if( d->REMARKS[0] != ' ' )
        {
            const int rc = pxCheckReferenceNr(ps, sBranchno, lCustomerno, &d->REMARKS[0]);
            if (rc != 0)
            {
                AllgStrCopy(&d->TEXT[0], &d->REMARKS[0], MAX_ERROR_MSG_AE);
                d->LACKREASON = rc;
                if(sLogLevel > 0)
                {
                    logtext = now.AsString("%H:%M:%S");
                    logtext += "      OpenOrder Error check reference";
                    logtext += ps->ErrorMsg();
                    logdat->Write(logtext);
                    logdat->End();
                    logdat->CloseSeralog();
                }
                return 6;
            }
        }
    }

    // setze Kunde
    customer = ps->CustomerId(lCustomerno, sBranchno);
    if (customer == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenOrder Error no customer";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return 6;
    }

    if(d->SHIPMENTTYPE[0] != ' ' || d->BOOKINGTYPE[0] != ' ')
    {
        if(d->SHIPMENTTYPE[0] == ' ') d->SHIPMENTTYPE[0] = '0'; //to make shure that at least 0
        if(d->BOOKINGTYPE[0] == ' ') d->BOOKINGTYPE[0] = '0';       //to make shure that at least 0
        if (ps->SubOrderType(&d->KINDOFORDER[0], &d->REMARKS[0], d->SHIPMENTTYPE[0], d->BOOKINGTYPE[0], static_cast<OriginTypeEnum>(d->BATCHSCHREIBEN), &d->SUB_ORDER_TYPE[0], d->DELIVERYDATE) == NULL)
        {
            AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
            d->LACKREASON = ps->ErrorNumber();
            if(sLogLevel > 0)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      OpenOrder Error ordertype";
                logtext += ps->ErrorMsg();
                logdat->Write(logtext);
                logdat->End();
                logdat->CloseSeralog();
            }
            return 6;
        }
    }
    else
    {
        if (ps->SubOrderType(&d->KINDOFORDER[0], &d->SUB_ORDER_TYPE[0], d->DELIVERYDATE) == NULL)
        {
            AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
            d->LACKREASON = ps->ErrorNumber();
            if(sLogLevel > 0)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      OpenOrder Error ordertype";
                logtext += ps->ErrorMsg();
                logdat->Write(logtext);
                logdat->End();
                logdat->CloseSeralog();
            }
            return 6;
        }
    }
    if(!ps->Order()->IsGoodState())
    {
        AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->Order()->ErrorNumber();
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenOrder Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            if(d->LACKREASON != CMSG_ORD_ROUTE_NOMORE)
            {
                logdat->End();
                logdat->CloseSeralog();
                return 6;
            }
        }
        if (!ps->Session()->isBulgaria())
        {
            if( d->REMARKS[0] != ' ' )
            {
                KscsrvCheckReference(d, error_msg);
                ps->Order()->SetReferenceNr(&d->REMARKS[0]);
            }
        }
        else
        {
            if( d->REMARKS[0] != ' ' )
            {
                ps->Order()->SetReferenceNr(&d->REMARKS[0]);
                if ( (d->LACKREASON = pxInsertReferenceNr(ps,
                                      ps->Order()->Customer()->Vertriebszentrum(),
                                      ps->Order()->Customer()->KundenNr(),
                                      ps->Order()->ReferenceNr() )) != 0)
                {
                    AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
                    if(sLogLevel > 1)
                    {
                        logtext = now.AsString("%H:%M:%S");
                        logtext += "      Insert Reference Error ";
                        logtext += ps->Order()->ErrorMsg();
                        logdat->Write(logtext);
                        logdat->End();
                        logdat->CloseSeralog();
                    }
                    return 6;
                }
            }
        }
        AllgStrCopy(&d->PHARMACYNAME[0], ps->Order()->Customer()->NameApo(), L_KSCSRVDATA_PHARMACYNAME);
        d->ORDERNO = ps->Order()->KdAuftragNr();
        if(sLogLevel > 0)
        {
            cOrder = d->ORDERNO;
            cOrder.Trim(6,nString::cLEADING,'0');
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out: OpenOrder Customer: ";
            logtext += &d->PHARMACYNAME[0];
            logtext += " OrderNo: ";
            logtext += cOrder;
            logdat->Write(logtext);
        }
        return 6;
    }
    if (!ps->Session()->isBulgaria())
    {
        if( d->REMARKS[0] != ' ' )
        {
            KscsrvCheckReference(d, error_msg);
            ps->Order()->SetReferenceNr(&d->REMARKS[0]);
        }
    }
    else
    {
        if( d->REMARKS[0] != ' ' )
        {
            ps->Order()->SetReferenceNr(&d->REMARKS[0]);
            if ( (d->LACKREASON = pxInsertReferenceNr(ps,
                                  ps->Order()->Customer()->Vertriebszentrum(),
                                  ps->Order()->Customer()->KundenNr(),
                                  ps->Order()->ReferenceNr() )) != 0)
            {
                AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
                if(sLogLevel > 1)
                {
                    logtext = now.AsString("%H:%M:%S");
                    logtext += "      Insert Reference Error ";
                    logtext += ps->Order()->ErrorMsg();
                    logdat->Write(logtext);
                    logdat->End();
                    logdat->CloseSeralog();
                }
                return 6;
            }
        }
    }
    AllgStrCopy(&d->PHARMACYNAME[0], ps->Order()->Customer()->NameApo(), L_KSCSRVDATA_PHARMACYNAME);

    if (ps->Session()->isSwitzerland())
    {
        pxGenericOrderRemarkList remarklist(ps->Session());
        nString remarks = &d->REMARKS[0];
        if (false == remarks.IsEmpty())
        {
            remarklist.AddOrderRemark(ps->Order()->KdAuftragNr(), 0, eOrderReferenceXML, &d->REMARKS[0]);
            remarklist.ChangeOrderRemark(ps->Order()->KdAuftragNr(), 0, eOrderReferenceXML, &d->REMARKS[0]);
        }
    }


    d->ORDERNO = ps->Order()->KdAuftragNr();
    d->PID = testpid;
    if(sLogLevel > 0)
    {
        cOrder = d->ORDERNO;
        cOrder.Trim(6,nString::cLEADING,'0');
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out: OpenOrder Customer: ";
        logtext += &d->PHARMACYNAME[0];
        logtext += " OrderNo: ";
        logtext += cOrder;
        logdat->Write(logtext);
    }

    initLog4Cplus();
    return 0;
}

/*****************************************************************************/
/* Oeffnen eines neuen Auftrages mit Uebergabe VZ-Nr                         */
/*****************************************************************************/
int KscsrvNeworderVz(struct N_KSCSRVDATA* d, char* error_msg)
{
    if(ps->Session()->Branch()->FilialNr() != d->BRANCHNO)
    {
        pxBranch  CustBranch(ps->Session(),d->BRANCHNO);
        if (CustBranch.IsGoodState())
        {
            *(ps->Session()->Branch()) = CustBranch;
        }
        else
        {
            return -1;
        }
    }
    return KscsrvNeworder(d, error_msg);
}

/*****************************************************************************/
/* Oeffnen eines Info-Auftrages mit Uebergabe VZ-Nr                         */
/*****************************************************************************/
int KscsrvOpenInfoOrder(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;             // ein String-Objekt
    nString cVZ;                 // ein String-Objekt
    nString cOrder;              // ein String-Objekt
    char cTerminal[5];                   // ein String-Objekt
    short AlterVZ = 0;
    pxCustBase* customer;
    char cCustomer[8];
    d->LACKREASON = 0;
    sprintf(&cCustomer[0], "%ld", d->CUSTOMERNO);
    ps->SetTransmissionType(pxOrderTransmit :: tDCT_Serial);
    if(ps->Session()->Branch()->FilialNr() != d->BRANCHNO)
    {
        pxBranch  CustBranch(ps->Session(),d->BRANCHNO);
        if (CustBranch.IsGoodState())
        {
            *(ps->Session()->Branch()) = CustBranch;
        }
        else
        {
            return -1;
        }
    }
    locklevelparam = ps->GetLockLevelParam();
    if(locklevelparam == NULL)
        sLogLevel = 1;
    else
        sLogLevel = locklevelparam->Wert();

    if (d->SWNOROUTING == 0)
    {
        AlterVZ = ps->CustomerRouting(d->CUSTOMERNO);
    }
    if(sLogLevel > 1)
    {
        sprintf(&cTerminal[0], "%4.4s", (char*) ps->Session()->Device()->Name());
        logdat->Start();
        logdat->SetIDFNr(&cCustomer[0]);
        logdat->SetTerminalID(&cTerminal[0]);
        logdat->Open();
        logdat->WriteList();
        cVZ = d->BRANCHNO;
        cVZ.Trim(2,nString::cLEADING,'0');
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  OpenInfoOrder Branchno: ";
        logtext += cVZ;
        logtext += " Customer: ";
        logtext += &cCustomer[0];
        logdat->Write(logtext);
    }

    // setze Kunde
    if ( AlterVZ >0 )
    {
        cVZ = AlterVZ;
        cVZ.Trim(2,nString::cLEADING,'0');
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      routed Branchno: " + cVZ;
            logdat->Write(logtext);
        }
        customer = ps->CustomerId(d->CUSTOMERNO, AlterVZ);
    }
    else
    {
        customer = ps->CustomerId(d->CUSTOMERNO);
    }
    if(customer == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->REMARKS[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenInfoOrder Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return 6;
    }
    if (ps->NewOrderInfo() == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenInfoOrder Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return 6;
    }
    if(!ps->Order()->IsGoodState())
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenOrder Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            if(d->LACKREASON != CMSG_ORD_ROUTE_NOMORE)
            {
                logdat->End();
                logdat->CloseSeralog();
                return 6;
            }
        }
        AllgStrCopy(&d->PHARMACYNAME[0], ps->Order()->Customer()->NameApo(), L_KSCSRVDATA_PHARMACYNAME);
        char aInfoLevel[2];
        aInfoLevel[0] = ps->Order()->Customer()->XMLInfoLevel();
        aInfoLevel[1] = '\0';
        d->INFOLEVEL = static_cast<short>(atoi(&aInfoLevel[0]));
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out: OpenInfoOrder Customer: ";
            logtext += &d->PHARMACYNAME[0];
            logdat->Write(logtext);
        }
        return 6;
    }
    AllgStrCopy(&d->PHARMACYNAME[0], ps->Order()->Customer()->NameApo(), L_KSCSRVDATA_PHARMACYNAME);
    char aInfoLevel[2];
    aInfoLevel[0] = ps->Order()->Customer()->XMLInfoLevel();
    aInfoLevel[1] = '\0';
    d->INFOLEVEL = static_cast<short>(atoi(&aInfoLevel[0]));
    d->PID = testpid;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out: OpenInfoOrder Customer: ";
        logtext += &d->PHARMACYNAME[0];
        logdat->Write(logtext);
    }

    initLog4Cplus();
    return 0;
}

/*****************************************************************************/
/* Schliessen des aktuellen Auftrages                                        */
/*****************************************************************************/
int KscsrvCloseorder(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;             // ein String-Objekt
    char cWertLieferung[11];
    nString cAnzPos;
    nString cOrder;
    nString cTour;
    nString cDeliveryBranch;
    nString cAnzAlphaText;  //nase von ohne bestand auf alpha, bitte prüfen
    nString cAnzPosDafueFehler;
    char cDatumAuslieferung[11];
    long lDatumAuslieferung;
    d->LACKREASON = 0;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  CloseOrder";
        logdat->Write(logtext);
    }
    now.SetNow();

    if (!ps->Order()->ReferenceNr().IsEmpty())
    {
        if (!ps->Session()->isBulgaria())
        {
            if ( (d->LACKREASON = pxInsertReferenceNr(ps,
                                  ps->Order()->Customer()->Vertriebszentrum(),
                                  ps->Order()->Customer()->KundenNr(),
                                  ps->Order()->ReferenceNr() )) != 0)
            {
                AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
                if(sLogLevel > 1)
                {
                    logtext = now.AsString("%H:%M:%S");
                    logtext += "      CloseOrder Error ";
                    logtext += ps->Order()->ErrorMsg();
                    logdat->Write(logtext);
                    logdat->End();
                    logdat->CloseSeralog();
                }
                AllgStrCopy(error_msg, &d->REMARKS[0], MAX_ERROR_MSG_AE);
                return 6;
            }
        }
    }

    transferOrderDeliveryInformation(d);
    lDatumAuslieferung = ps->Order()->DatumAuslieferung().GetYYYYMMDD();
    d->CUSTOMERNO = ps->Order()->Customer()->KundenNr();


    d->VALUEOFORDER         = ps->Order()->WertLieferung();
    d->LINESOFORDER         = ps->Order()->AnzPos();
    d->TEXTLINES            = ps->Order()->AnzAlphaText();  //nase von ohne bestand auf alpha, bitte prüfen
    d->LACKLINES            = ps->Order()->AnzPosDafueFehler();
    d->WERTNETTO_FV         = ps->Order()->GetValueNetCash(FREESALE_PRICE);
    d->WERTTAX_FV           = ps->Order()->GetValueSalesTax(FREESALE_PRICE);
    d->WERTNETTO_KK         = ps->Order()->GetValueNetCash(HEALTHFUND_PRICE);
    d->WERTTAX_KK           = ps->Order()->GetValueSalesTax(HEALTHFUND_PRICE);
    d->WERTNETTO_EH         = ps->Order()->GetValueNetCash(RETAIL_PRICE);
    d->VALRESTCL            = ps->Order()->Customer()->RestCreditLimit();
    if ( ps->Order()->OrderValues() )
    {
        d->ORDVALFTAXFS         = ps->Order()->OrderValues()->OrdValFtaxFS();
        d->ORDVALFTAXFSDISC     = ps->Order()->OrderValues()->OrdValFtaxFSDisc();
        d->ORDVALFTAXHF         = ps->Order()->OrderValues()->OrdValFtaxHF();
        d->ORDVALFTAXHFDISC     = ps->Order()->OrderValues()->OrdValFtaxHFDisc();
        d->ORDVALFTAXRS         = ps->Order()->OrderValues()->OrdValFtaxRS();
        d->ORDVALFTAXRSDISC     = ps->Order()->OrderValues()->OrdValFtaxRSDisc();
        d->ORDVALLTAXFS         = ps->Order()->OrderValues()->OrdValLtaxFS();
        d->ORDVALLTAXFSDISC     = ps->Order()->OrderValues()->OrdValLtaxFSDisc();
        d->ORDVALLTAXHF         = ps->Order()->OrderValues()->OrdValLtaxHF();
        d->ORDVALLTAXHFDISC     = ps->Order()->OrderValues()->OrdValLtaxHFDisc();
        d->ORDVALLTAXRS         = ps->Order()->OrderValues()->OrdValLtaxRS();
        d->ORDVALLTAXRSDISC     = ps->Order()->OrderValues()->OrdValLtaxRSDisc();
        d->TAXVALFTAXFS         = ps->Order()->OrderValues()->TaxValFtaxFS();
        d->TAXVALFTAXFSDISC     = ps->Order()->OrderValues()->TaxValFtaxFSDisc();
        d->TAXVALFTAXHF         = ps->Order()->OrderValues()->TaxValFtaxHF();
        d->TAXVALFTAXHFDISC     = ps->Order()->OrderValues()->TaxValFtaxHFDisc();
        d->TAXVALFTAXRS         = ps->Order()->OrderValues()->TaxValFtaxRS();
        d->TAXVALFTAXRSDISC     = ps->Order()->OrderValues()->TaxValFtaxRSDisc();
        d->TAXVALLTAXFS         = ps->Order()->OrderValues()->TaxValLtaxFS();
        d->TAXVALLTAXFSDISC     = ps->Order()->OrderValues()->TaxValLtaxFSDisc();
        d->TAXVALLTAXHF         = ps->Order()->OrderValues()->TaxValLtaxHF();
        d->TAXVALLTAXHFDISC     = ps->Order()->OrderValues()->TaxValLtaxHFDisc();
        d->TAXVALLTAXRS         = ps->Order()->OrderValues()->TaxValLtaxRS();
        d->TAXVALLTAXRSDISC     = ps->Order()->OrderValues()->TaxValLtaxRSDisc();
    }

    d->DELIVERYBRANCHNO = ps->Order()->FilialNr();

    PriceTypeEnum priceType = RETAIL_PRICE;
    if(ps->Order()->CountPriceTypeItems(FREESALE_PRICE))
    {
        priceType = FREESALE_PRICE;
    }
    else if (ps->Order()->CountPriceTypeItems(HEALTHFUND_PRICE))
    {
        priceType = HEALTHFUND_PRICE;
    }

    if(ps->Order()->Customer()->IsCashPayer(priceType,ps->Order()))
    {
        d->SWCASH[0] = '1';
    }
    else
    {
        d->SWCASH[0] = '0';
    }
    d->ORDERNO = ps->Order()->KdAuftragNr();
    cOrder = d->ORDERNO;
    cOrder.Trim(6,nString::cLEADING,'0');
    cTour += ps->Order()->TourId();
    nString bem;
    if( ps->Order()->IsSendOrderDouble() )
    {
        bem = ps->GetMessageText(CMSG_ORD_DOUBLE_ORDER);
        d->LACKREASON = CMSG_ORD_DOUBLE_ORDER;
        AllgStrCopy(&d->TEXT[0], bem, MAX_ERROR_MSG_AE);
    }
    if(ps->Order()->IsChangedToCashOrder())
    {
        bem = ps->GetMessageText(CMSG_ORD_CHANGED_TO_CASHORDER);
        d->LACKREASON = CMSG_ORD_CHANGED_TO_CASHORDER;
        AllgStrCopy(&d->TEXT[0], bem, MAX_ERROR_MSG_AE);
        d->SWCASH[0] = '1';
    }
    if(ps->End() != 0)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      CloseOrder Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return 6;
    }
    strncpy(&d->POSTPONEREASON[0], GetOrderZugrund(ps, d->ORDERNO), L_KSCSRVDATA_POSTPONEREASON);
    sprintf(&cWertLieferung[0], "%10.2f", d->VALUEOFORDER);
    cAnzPos = d->LINESOFORDER;
    cAnzPos.Trim(6,nString::cLEADING,'0');
    cAnzAlphaText = d->TEXTLINES;
    cAnzAlphaText.Trim(6,nString::cLEADING,'0');
    cAnzPosDafueFehler = d->LACKLINES;
    cAnzPosDafueFehler.Trim(6,nString::cLEADING,'0');
    sprintf(&cDatumAuslieferung[0], "%02ld.%02ld.%04ld",
            d->TOURDATE%100,
            d->TOURDATE/100%100,
            d->TOURDATE/10000);
    cDeliveryBranch = d->DELIVERYBRANCHNO;
    cDeliveryBranch.Trim(2,nString::cLEADING,'0');
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out: CloseOrder Order: ";
        logtext += cOrder;
        logtext += " Tour: ";
        logtext += cTour;
        logtext += " Lieferdatum: ";
        logtext += &cDatumAuslieferung[0];
        logtext += " Value of Order: ";
        logtext += &cWertLieferung[0];
        logtext += " Lines of Order: ";
        logtext += cAnzPos;
        logtext += " Textlines of Order: ";
        logtext += cAnzAlphaText;
        logtext += " Lacklines of Order: ";
        logtext += cAnzPosDafueFehler;
        logtext += " Value of Order: ";
        logtext += &cWertLieferung[0];
        logtext += " from Branchno: ";
        logtext += cDeliveryBranch;
        logdat->Write(logtext);
        if( !bem.IsEmpty() )
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      CloseOrder Error ";
            logtext += bem;
            logdat->Write(logtext);
        }
        logdat->End();
        logdat->CloseSeralog();
    }
    if( !bem.IsEmpty() )
    {
        return 6;
    }
    if (ps->Session()->isCroatia()
            && lDatumAuslieferung == 0
            && d->VALUEOFORDER > 0
            && d->LINESOFORDER > 0) //nur am gleichen Tag und mit gueltigen Zeilen
    {
        struct RUFPTAG ruf;
        ruf.FILIALNR = d->DELIVERYBRANCHNO;
        ruf.RUFZEIT = atoi(&d->TOURID[0]) / 100;
        ruf.IDFNR = d->CUSTOMERNO;
        kscCheck_Callplan(&ruf, error_msg);
    }
    return 0;
}

/*****************************************************************************/
/* Aendern der Auftragsbemerkung                                             */
/*****************************************************************************/
int KscsrvChangeOrdBem(struct N_KSCSRVDATA *d, char * /*error_msg*/)
{
    nTime now;
    nString text;             // ein String-Objekt
    nString logtext;
    d->LACKREASON = 0;
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    text = &d->REMARKS[0];
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  OrderBem";
        logtext += text;
        logdat->Write(logtext);
        ps->OrderRemarks(text);
    }
    return 0;
}

/*****************************************************************************/
/** Auftragsposition                                                        **/
/*****************************************************************************/

/*****************************************************************************/
/* bucht eine neue Position auf den aktuellen Auftrag mit Rückmeldung der Restmenge */
/*****************************************************************************/
int KscsrvWritepos(struct N_KSCSRVDATA *d, char *error_msg)
{
    artcodesS codes;

    nTime now;
    nString cArtikel;
    nString cEAN;
    nString logtext;
    nString cSeqNo;
    nString cPreisTyp;
    char cMenge[5];
    char cNatra[5];
    bool auxDel = false;
    bool restDel = false;
    bool dispo = false;
    bool partDel = false;
    int iPicking,iBooking;
    char huelse[8];
    long lAufnr;
    double dLegallPrice;
    double LogZuschlag;
    pxOrderItem* orderitem;
    pxCountryCodes* CC = NULL;
    d->LACKREASON = 0;
    memset(&codes.ARTICLE_CODE[0], ' ', L_ARTCODES_ARTICLE_CODE);
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    codes.CODE_TYPE = 0;
    if(d->ARTICLE_CODE[0] != ' ')
    {
        sprintf(&codes.ARTICLE_CODE[0], "%*.*s", L_ARTCODES_ARTICLE_CODE, L_ARTCODES_ARTICLE_CODE, &d->ARTICLE_CODE[0]);
        kscartSel_NoByCode(&codes, error_msg);
        AllgEntfSpaces(&codes.ARTICLE_CODE[0]);
        if(codes.ARTICLENO == 0)
        {
            if (strlen(&codes.ARTICLE_CODE[0]) > 7)
            {
                codes.ARTICLENO = 9999999;
            }
            else
            {
                codes.ARTICLENO = atol(&codes.ARTICLE_CODE[0]);
            }
        }
        d->ARTICLENO = codes.ARTICLENO;
        cArtikel = d->ARTICLENO;
        cArtikel.Trim(7,nString::cLEADING,'0');
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  WritePos ";
            logtext += " ARTICLE_CODE: ";
            logtext += &codes.ARTICLE_CODE[0];
        }
    }
    else if(d->ARTICLENO == 0)
    {
        cArtikel = ps->ConvertEan2Pzn(&d->EAN[0]);
        d->ARTICLENO = atol(cArtikel);
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  WritePos ";
            logtext += " EAN: ";
            logtext += &d->EAN[0];
        }
    }
    else
    {
        cArtikel = d->ARTICLENO;
        cArtikel.Trim(7,nString::cLEADING,'0');
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  WritePos ";
            logtext += " PZN: ";
            logtext += cArtikel;
        }
    }
    if(codes.ARTICLE_CODE[0] == ' ')
    {
        codes.ARTICLENO = d->ARTICLENO;
        kscartSel_Preferred(&codes, error_msg);
    }
    sprintf(&cMenge[0], "%04ld", d->ORDERQTY);
    if(d->SWAUX[0] == '1') auxDel = true;
    if(d->SWRESTDELIVERY[0] == '1') restDel = true;
    if(d->SWDISPO[0] == '1') dispo = true;
    if(d->SWPARTDELIVERY[0] == '1') partDel = true;
    const PriceTypeEnum priceType = static_cast<PriceTypeEnum>(d->PREIS_TYP);
    lAufnr = d->ORDERSEQUENZNO;
    cSeqNo = d->ORDERSEQUENZNO;
    cSeqNo.Trim(2,nString::cLEADING,'0');
    cPreisTyp = d->PREIS_TYP;

    AllgEntfSpaces(&d->XMLLINEREFERENCE[0]);
    nString nStrRef = &d->XMLLINEREFERENCE[0];

    AllgEntfSpaces(&d->XMLTEXT[0]);
    nString nStrLineRef = &d->XMLTEXT[0];

    if(sLogLevel > 1)
    {
        logtext += " Quantity: ";
        logtext += &cMenge[0];
        logtext += " AUX: ";
        logtext += &d->SWAUX[0];
        logtext += " RESTDELIVERY: ";
        logtext += &d->SWRESTDELIVERY[0];
        logtext += " DISPO: ";
        logtext += &d->SWDISPO[0];
        logtext += " SWPARTDELIVERY: ";
        logtext += &d->SWPARTDELIVERY[0];
        logtext += " SEQUENZNO: ";
        logtext += cSeqNo;
        logtext += " PREIS_TYP: ";
        logtext += cPreisTyp;
        logtext += " REFERENCE: ";
        logtext += nStrRef;
        if(d->QTYNATRA > 0)
        {
            sprintf(&cNatra[0], "%04ld", d->QTYNATRA);
            logtext += " Natra: ";
            logtext += &cNatra[0];
        }
        logdat->Write(logtext);
    }

    if(ps->Session()->IsSubDeviceTypeOf(MSV3))  //MSV3
    {
        sprintf(&huelse[0], "%c", ps->Order()->KoArt());
        iPicking = atoi(&huelse[0]);
        sprintf(&huelse[0], "%c", ps->Order()->BuchArt());
        iBooking = atoi(&huelse[0]);
        ps->OrderTypeMSV3( ps->Order()->KdAuftragArt(),
                           ps->Order()->OrderLabel(),
                           iPicking,
                           iBooking);
    }
    else
    {
        ps->OrderType(ps->Order()->KdAuftragArt(),lAufnr);
    }
    if (ps->Session()->isBulgaria())
    {
        nString bem;
        if(priceType == HEALTHFUND_PRICE && !ps->Order()->Customer()->IsHealthFundAuthorized())
        {
            bem = ps->GetMessageText(CMSG_SDC_NO_PERMISSION_HEALTHFUND);
            d->LACKREASON = CMSG_SDC_NO_PERMISSION_HEALTHFUND;
            AllgStrCopy(&d->TEXT[0], bem, MAX_ERROR_MSG_AE);
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      WritePos Error ";
                logtext += bem;
                logdat->Write(logtext);
            }
            return 6;
        }
        if(priceType == RETAIL_PRICE && !ps->Order()->Customer()->Flags().IsRetailPermit())
        {
            bem = ps->GetMessageText(CMSG_SDC_NO_PERMISSION_RETAIL);
            d->LACKREASON = CMSG_SDC_NO_PERMISSION_RETAIL;
            AllgStrCopy(&d->TEXT[0], bem, MAX_ERROR_MSG_AE);
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      WritePos Error ";
                logtext += bem;
                logdat->Write(logtext);
            }
            return 6;
        }
        oItemList = ps->Order()->ItemList();
        orderitem = oItemList->FindArticle(atol(cArtikel), priceType);
        if (orderitem == NULL)
        {
            if( d->PHARMPURCHPRICE > 0.0 || d->MANUALPRICE > 0.0 || d->MANUELDISCPCT > 0.0 || d->QTYNATRA > 0 )
            {
                orderitem = ps->NewOrderItem_13(d->ARTICLENO,d->ORDERQTY,nStrRef(),nStrLineRef(),auxDel,restDel,dispo,partDel,priceType,d->PHARMPURCHPRICE,d->MANUALPRICE,d->MANUELDISCPCT, d->QTYNATRA);
            }
            else
            {
                orderitem = ps->NewOrderItem_12(d->ARTICLENO,d->ORDERQTY,nStrRef(),nStrLineRef(),auxDel,restDel,dispo,partDel,priceType);
            }
        }
        else
        {
            long neu;
            if (orderitem->Open() == nSTATE_GOOD)
            {
                neu = orderitem->MengeBestellt() + atol(&cMenge[0]);
                orderitem->OrderQuantity(neu,0,0);
            }
        }
    }
    else
    {
        if(d->PHARMPURCHPRICE > 0.0 || d->MANUALPRICE > 0.0 || d->MANUELDISCPCT > 0.0 || d->QTYNATRA > 0)
        {
            orderitem = ps->NewOrderItem_13(d->ARTICLENO,d->ORDERQTY,nStrRef(),nStrLineRef(),auxDel,restDel,dispo,partDel,priceType,d->PHARMPURCHPRICE,d->MANUALPRICE,d->MANUELDISCPCT, d->QTYNATRA);
        }
        else
        {
            orderitem = ps->NewOrderItem_12(d->ARTICLENO,d->ORDERQTY,nStrRef(),nStrLineRef(),auxDel,restDel,dispo,partDel,priceType);
        }
    }

    AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
    d->LACKREASON = ps->ErrorNumber();

    if (ps->Session()->isBulgaria())
    {
        if (orderitem == NULL && d->LACKREASON == 30051)
        {
            /*          nString ot = "CO";
                        ps->Order()->OrderType(ot,'0','0');
                        if ( ! (ps->Order()->IsGoodState()) )
                        {
                                AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
                                return 6;
                        }
                        ps->Order()->SetChangedToCashOrder();
            */
            ps->Order()->SetChangedToCashOrder();
            ps->Order()->SetOrderToCashAe();  //Neu: Ändern auf Barzahlung
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      WritePos Error ";
                logtext += ps->ErrorMsg();
                logdat->Write(logtext);
            }

            if(d->PHARMPURCHPRICE > 0.0 || d->MANUALPRICE > 0.0 || d->MANUELDISCPCT > 0.0 || d->QTYNATRA > 0)
            {
                orderitem = ps->NewOrderItem_13(d->ARTICLENO,d->ORDERQTY,nStrRef(),nStrLineRef(),auxDel,restDel,dispo,partDel,priceType,d->PHARMPURCHPRICE,d->MANUALPRICE,d->MANUELDISCPCT, d->QTYNATRA);
            }
            else
            {
                orderitem = ps->NewOrderItem_12(d->ARTICLENO,d->ORDERQTY,nStrRef(),nStrLineRef(),auxDel,restDel,dispo,partDel,priceType);
            }
        }
    }

    if (orderitem == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      WritePos Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
        }
        return 6;
    }
    if (ps->Session()->isBulgaria())
    {
        if(d->BATCHNO[0] != ' ')
        {
            orderitem->StoreDesiredBatchInfo(&d->BATCHNO[0]); //Keine FixBatch verarbeitung (NON GOAL DACH BATCHTRACKING)
        }
    }

    d->ORDERNO = orderitem->Order().KdAuftragNr();
    transferDeliveryInformation( d, orderitem, false );

//  orderitem->setXMLReferences( nStrRef(), nStrLineRef() ); // set XML order reference and XML order line reference in orderremarks

    AllgEntfSpaces(&d->REMARKS[0]);
    if(orderitem->MengeNachgeliefert() > 0)
    {
        if(ps->Order()->BatchSchreiben() > 0)
        {
            nString nStr = &d->REMARKS[0];
            orderitem->CscBatchCheckOrderPos(d->QTYNATRA, nStr);
        }
    }
    else if (strlen(&d->REMARKS[0]) > 0)    //Bemerkung für die Position setzen
    {
        nString nStr = &d->REMARKS[0];
        orderitem->Bemerkungen( nStr );
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  WritePos ";
            logtext += "      Remark: ";
            logtext += nStr;
            logdat->Write(logtext);
        }
    }

    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out: WritePos ";
    }
    if(orderitem->ArtBase() != NULL && orderitem->ArtBase()->IsGoodState() )
    {
        short TextKey = 0;
        pxArticleText* ptext = NULL;
        TextKey = orderitem->ArtBase()->TextKey();
        if(TextKey > 0)
        {
            ptext = new pxArticleText(ps->Session(),TextKey);
            if ( !ptext->Get(cDBGET_READONLY))
            {
                strncpy(&d->ARTICLETEXT[0],
                        ptext->Text(),
                        L_KSCSRVDATA_ARTICLETEXT);
            }
            delete ptext;
        }
        strncpy(&d->ARTICLENAME[0],
                orderitem->ArtBase()->Bezeichnung(),
                L_KSCSRVDATA_ARTICLENAME);
        strncpy(&d->ARTIKEL_LANGNAME[0],
                orderitem->ArtBase()->ArtikelLangname(),
                L_KSCSRVDATA_ARTIKEL_LANGNAME);
        strncpy(&d->ARTICLEUNIT[0],
                orderitem->ArtBase()->Einheit(),
                L_KSCSRVDATA_ARTICLEUNIT);
        strncpy(&d->HANDOUT[0],
                orderitem->ArtBase()->Darreichform(),
                L_KSCSRVDATA_HANDOUT);
        if(ps->Order()->Customer()->PreWholeTyp() == '1')
        {
            if((d->CODEBLOCAGE[0] = orderitem->ArtBase()->CodeBlocage()) != 'P')
            {
                d->CODEBLOCAGE[0] = '0';
            }
        }
        else
        {
            if(orderitem->TotalIBTQuantity() > 0) // if(orderitem->MengeVerbund() > 0)
            {
                d->CODEBLOCAGE[0] = 'T';
            }
            else
            {
                d->CODEBLOCAGE[0] = orderitem->ArtBase()->CodeBlocage();
            }
        }
        if(sLogLevel > 1)
        {
            logtext += " Name: ";
            logtext += &d->ARTICLENAME[0];
            logtext += " Unit: ";
            logtext += &d->ARTICLEUNIT[0];
            logtext += " Handout: ";
            logtext += &d->HANDOUT[0];
            logtext += " CodeBlocage: ";
            logtext += &d->CODEBLOCAGE[0];
        }
    }
    else
    {
        d->CODEBLOCAGE[0] = '2';
        if(sLogLevel > 1)
        {
            logtext += " CodeBlocage: ";
            logtext += &d->CODEBLOCAGE[0];
        }
    }
    if(sLogLevel > 1)
    {
        logdat->Write(logtext);
    }
    if(ps->Order()->Customer()->PreWholeTyp() == '1')
    {
        nString cQTY;
        nString cQTYLack;
        if(d->CODEBLOCAGE[0] != 'P')
        {
            d->DELIVERYQTY = orderitem->MengeGeliefert();
            cQTY = d->DELIVERYQTY;
            cQTY.Trim(5,nString::cLEADING,'0');
            cQTYLack = 0L;
            cQTYLack.Trim(5,nString::cLEADING,'0');
        }
        else
        {
            d->QTYLACK = orderitem->MengeBestellt();
            d->LACKREASON = orderitem->GetError(&d->TEXT[0]);
            cQTY = 0L;
            cQTY.Trim(5,nString::cLEADING,'0');
            cQTYLack = d->QTYLACK;
            cQTYLack.Trim(5,nString::cLEADING,'0');
        }
        if(sLogLevel > 1)
        {
            logtext += " Name: ";
            logtext += &d->ARTICLENAME[0];
            logtext += " Unit: ";
            logtext += &d->ARTICLEUNIT[0];
            logtext += " Handout: ";
            logtext += &d->HANDOUT[0];
            logtext += " CodeBlocage: ";
            logtext += &d->CODEBLOCAGE[0];
            logdat->Write(logtext);
            logtext = now.AsString("%H:%M:%S");
            logtext += "               delivery Qty: ";
            logtext += cQTY;
            logtext += " lack Qty: ";
            logtext += cQTYLack;
            logdat->Write(logtext);
        }
    }
    else
    {
        if (d->QTYNATRA > 0)
        {
            d->QTYLACK = (d->ORDERQTY + d->QTYNATRA - orderitem->MengeGeliefert() - orderitem->TotalIBTQuantity()) - //orderitem->MengeVerbund()) -
                orderitem->MengeNachgeliefert() - orderitem->MengeDisponiert();
        }
        else
        {
            d->QTYLACK = (d->ORDERQTY + orderitem->MengeNatra() - orderitem->MengeGeliefert() - orderitem->TotalIBTQuantity()) - //orderitem->MengeVerbund()) -
                orderitem->MengeNachgeliefert() - orderitem->MengeDisponiert();
        }

        if(d->QTYLACK < 0) d->QTYLACK = 0;
        d->AUXQTY = orderitem->TotalIBTQuantity(); // d->AUXQTY = orderitem->MengeVerbund();
        d->RESTDELIVERYQTY = orderitem->MengeNachgeliefert();
        d->DELIVERYQTY = orderitem->MengeGeliefert();
        d->DISPOQTY = orderitem->MengeDisponiert();
        d->QTYNATRA = orderitem->MengeNatra();
        d->AUXBRANCHNO = ps->Order()->AuxFil();
        if(     (orderitem->IsQStateAlternate() ||
                 orderitem->IsReimportArtikel()) )
        {
            codes.ARTICLENO = orderitem->ArtikelNr();
//           kscartSel_Preferred(&codes, error_msg);
            strncpy(&d->ARTICLE_CODEORG[0], &d->ARTICLE_CODE[0], L_ARTCODES_ARTICLE_CODE);
            strncpy(&d->ARTICLE_CODE[0], orderitem->ArticleCode(), L_ARTCODES_ARTICLE_CODE);
//            strncpy(d->ARTICLE_CODE,codes.ARTICLE_CODE,L_ARTCODES_ARTICLE_CODE);
//            orderitem->SetArticleCodeValues(codes.CODE_TYPE, codes.ARTICLE_CODE,true);
            d->ARTICLENOORG = d->ARTICLENO;
            d->ARTICLENO = orderitem->ArtikelNr();
            nString cArtikelNo;
            nString cArtikelNoOrg;
            cArtikelNo = d->ARTICLENO;
            cArtikelNo.Trim(7,nString::cLEADING,'0');
            cArtikelNoOrg = d->ARTICLENOORG;
            cArtikelNoOrg.Trim(7,nString::cLEADING,'0');
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "               PZN: ";
                logtext += cArtikelNo;
                logtext += " PZN-ORG: ";
                logtext += cArtikelNoOrg;
                logdat->Write(logtext);
            }
            strncpy(&d->EANORG[0], ps->ConvertPzn2Ean(d->ARTICLENOORG, 13), L_KSCSRVDATA_EAN);
            pxArticleInfo* ArtInfo = orderitem->ArticleInfoRequest(d->ARTICLENOORG, orderitem->MengeBestaetigt());
            if (ArtInfo != NULL)
            {
                strncpy(&d->ARTICLENAMEORG[0],
                        ArtInfo->ArtBase()->Bezeichnung(),
                        L_KSCSRVDATA_ARTICLENAMEORG);
                strncpy(&d->ARTICLEUNITORG[0],
                        ArtInfo->ArtBase()->Einheit(),
                        L_KSCSRVDATA_ARTICLEUNITORG);
                strncpy(&d->HANDOUTORG[0],
                        ArtInfo->ArtBase()->Darreichform(),
                        L_KSCSRVDATA_HANDOUTORG);
                d->PHARMPURCHPRICEORG = ArtInfo->PreisEKApo();
                //d->CUSTPURCHPRICEORG = ArtInfo->PreisEKApoNetto();
                //if(d->CUSTPURCHPRICEORG == 0)
                d->CUSTPURCHPRICEORG = ArtInfo->PreisEKApo();
                d->PHARMSELLPRICEORG = ArtInfo->PreisVKApo();
                d->LPPR_PRICEORG = orderitem->ReimbursementPrice(d->ARTICLENOORG, '2');
                d->TFR_PRICEORG = orderitem->ReimbursementPrice(d->ARTICLENOORG, '1');
                d->TAXRATEORG = ArtInfo->SalesTaxRate();
                d->CODEBLOCAGEORG[0] = ArtInfo->CodeBlocage();
                if (ps->Session()->isFrance() || ps->Session()->isFrancePrewhole())
                {
                    CC = ps->CountryCodesInfo(ps->Order()->FilialNr(), &d->CODEBLOCAGEORG[0]);
                    if (CC != NULL)
                    {
                        strncpy(&d->SERACODEORG[0], CC->SeraCode(), L_KSCSRVDATA_SERACODEORG);
                        strncpy(&d->XMLCODEORG[0], CC->XMLCode(), L_KSCSRVDATA_XMLCODEORG);
                        strncpy(&d->XMLTEXTORG[0], CC->XMLText(), L_KSCSRVDATA_XMLTEXTORG);
                        delete CC;
                    }
                }
            }
        }
        else
        {
            orderitem->SetArticleCodeValues(codes.CODE_TYPE, &codes.ARTICLE_CODE[0], true);
        }

        d->LACKREASON = orderitem->GetError(&d->TEXT[0]);
        d->ERRORNO = orderitem->GetLackReason(&d->FEHLTEXT[0]);
    }
//    AllgStrCopy(&d->TOURID[0], ps->Order()->TourId(), L_KSCSRVDATA_TOURID);
    d->PHARMPURCHPRICE = orderitem->PreisEKApo();
    d->PREISFAKTUR = orderitem->InvoiceValue();     // Rabattierter Preis
    d->CUSTPURCHPRICE = orderitem->PreisEKApoNetto();
    d->PREISEKGROSSO = orderitem->PreisEKGrosso();
    d->MARGIN = orderitem->getMarginGepAep();
    d->DISCOUNTVALUEPCT = orderitem->GetDiscountValuePct();
    if(d->CUSTPURCHPRICE == 0)
        d->CUSTPURCHPRICE = orderitem->PreisEKApo();

    dLegallPrice = (double)orderitem->GetLegallBreizhPrice();
    if(dLegallPrice > 0)
    {
        d->PHARMPURCHPRICE = dLegallPrice;
        d->CUSTPURCHPRICE = dLegallPrice;
    }

    d->PHARMSELLPRICE = orderitem->getPharmacySellPrice();
    d->BASEPRICE = orderitem->BasePrice();
    LogZuschlag = orderitem->GetLogisticAddition();
    if(LogZuschlag > 0)
    {
        d->LOGISTICSADDITION = d->BASEPRICE * LogZuschlag / 100;
    }
    else
    {
        d->LOGISTICSADDITION = 0;
    }
    d->LPPR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'2');
    d->TFR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'1');
    cEAN = ps->ConvertPzn2Ean(orderitem->ArtikelNr(),13);
    if(!cEAN.IsEmpty())
    {
        strncpy(&d->EAN[0], cEAN, L_KSCSRVDATA_EAN);
    }
    d->QTYRESERVATION = orderitem->MengeReserviert();
    d->EXPIRYDATE = orderitem->ArticleExpireDate();
    d->TAXRATE = orderitem->SalesTaxRate();

    // orderno and position no needed for SalesWeb FR
    d->PID = orderitem->PosNr();

    if (ps->Session()->isFrance() || ps->Session()->isFrancePrewhole())
    {
        if(d->LACKREASON != 0)
        {
            CC = ps->CountryCodesInfo(ps->Order()->FilialNr(), &d->CODEBLOCAGE[0]);
            if(CC != NULL)
            {
                strncpy(&d->SERACODE[0], CC->SeraCode(), L_KSCSRVDATA_SERACODE);
                strncpy(&d->XMLCODE[0], CC->XMLCode(), L_KSCSRVDATA_XMLCODE);
                strncpy(&d->XMLTEXT[0], CC->XMLText(), L_KSCSRVDATA_XMLTEXT);
                delete CC;
            }
        }
    }
    else if (ps->Session()->Country() == "AU" || ps->Session()->isGermany())
    {
        nString xmlcode;             // ein String-Objekt
        xmlcode = d->LACKREASON / 100;
        xmlcode.Trim(L_KSCSRVDATA_XMLCODE, nString::cLEADING, '0');
        strncpy(&d->XMLCODE[0], xmlcode, L_KSCSRVDATA_XMLCODE);
        if(d->LACKREASON != 0)
        {
            CC = ps->CountryCodesInfo(ps->Order()->FilialNr(), &d->XMLCODE[0], static_cast<short>(pxCountryCodes::CCT_XMLCODE));
            if (CC != NULL)
            {
                strncpy(&d->SERACODE[0], CC->SeraCode(), L_KSCSRVDATA_SERACODE);
                strncpy(&d->XMLTEXT[0], CC->XMLText(), L_KSCSRVDATA_XMLTEXT);
                strncpy(&d->LACKREASONCTYCODE[0], CC->InfoCode(), L_KSCSRVDATA_LACKREASONCTYCODE);
                delete CC;
            }
        }
    }
    if (sLogLevel > 1)
    {
        nString cQTY;
        nString cQTYLack;
        nString cAUXQTY;
        nString cAUXBRANCHNO;
        nString cRESTQTY;
        nString cDISPOQTY;
        nString cQTYNATRA;
        char cPHARMPURCHPRICE[11];
        char cCUSTPURCHPRICE[11];
        char cPHARMSELLPRICE[11];
        char cLPPR_PRICE[11];
        char cTFR_PRICE[11];
        char cBASEPRICE[11];
        char cEXPIRYDATE[11];
        char cTAXRATE[11];
        char cLOGISTICSADDITION[11];
        cQTY = d->DELIVERYQTY;
        cQTY.Trim(5, nString::cLEADING, '0');
        cQTYLack = d->QTYLACK;
        cQTYLack.Trim(5, nString::cLEADING, '0');
        cAUXQTY = d->AUXQTY;
        cAUXQTY.Trim(5, nString::cLEADING, '0');
        cRESTQTY = d->RESTDELIVERYQTY;
        cRESTQTY.Trim(5, nString::cLEADING, '0');
        cDISPOQTY = d->DISPOQTY;
        cDISPOQTY.Trim(5, nString::cLEADING, '0');
        cQTYNATRA = d->QTYNATRA;
        cQTYNATRA.Trim(5, nString::cLEADING, '0');
        cAUXBRANCHNO = d->AUXBRANCHNO;
        cAUXBRANCHNO.Trim(2, nString::cLEADING, '0');
        logtext = now.AsString("%H:%M:%S");
        logtext += "               delivery Qty: ";
        logtext += cQTY;
        logtext += " lack Qty: ";
        logtext += cQTYLack;
        logtext += " rest Qty: ";
        logtext += cRESTQTY;
        logtext += " dispo Qty: ";
        logtext += cDISPOQTY;
        logtext += " Natra Qty: ";
        logtext += cQTYNATRA;
        logtext += " aux Qty: ";
        logtext += cAUXQTY;
        logtext += " Branch: ";
        logtext += cAUXBRANCHNO;
        logdat->Write(logtext);
        sprintf(&cPHARMPURCHPRICE[0], "%10.2f", d->PHARMPURCHPRICE);
        sprintf(&cCUSTPURCHPRICE[0], "%10.2f", d->CUSTPURCHPRICE);
        sprintf(&cPHARMSELLPRICE[0], "%10.2f", d->PHARMSELLPRICE);
        sprintf(&cLPPR_PRICE[0], "%10.2f", d->LPPR_PRICE);
        sprintf(&cTFR_PRICE[0], "%10.2f", d->TFR_PRICE);
        sprintf(&cBASEPRICE[0], "%10.2f", d->BASEPRICE);
        sprintf(&cLOGISTICSADDITION[0], "%10.2f", d->LOGISTICSADDITION);
        sprintf(&cEXPIRYDATE[0], "%02ld.%02ld.%04ld",
            d->EXPIRYDATE % 100,
            d->EXPIRYDATE / 100 % 100,
            d->EXPIRYDATE / 10000);
        sprintf(&cTAXRATE[0], "%10.2f", d->TAXRATE);
        logtext = now.AsString("%H:%M:%S");
        logtext += "               AEP: ";
        logtext += &cPHARMPURCHPRICE[0];
        logtext += " Netto: ";
        logtext += &cCUSTPURCHPRICE[0];
        logtext += " AVP: ";
        logtext += &cPHARMSELLPRICE[0];
        logtext += " LPPR: ";
        logtext += &cLPPR_PRICE[0];
        logtext += " TFR: ";
        logtext += &cTFR_PRICE[0];
        logtext += " BASE: ";
        logtext += &cBASEPRICE[0];
        logtext += " LOG: ";
        logtext += &cLOGISTICSADDITION[0];
        logtext += " TAX: ";
        logtext += &cTAXRATE[0];
        logtext += " Verfall: ";
        logtext += &cEXPIRYDATE[0];
        logdat->Write(logtext);
        logtext = now.AsString("%H:%M:%S");
        logtext += "               SeraCode: ";
        logtext += &d->SERACODE[0];
        logtext += " XMLCode: ";
        logtext += &d->XMLCODE[0];
        logtext += " XMLText: ";
        logtext += &d->XMLTEXT[0];
        logdat->Write(logtext);
        if(d->ARTICLENOORG > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "               Org-Name: ";
            logtext += &d->ARTICLENAMEORG[0];
            logtext += " Org-Unit: ";
            logtext += &d->ARTICLEUNITORG[0];
            logtext += " Org-Handout: ";
            logtext += &d->HANDOUTORG[0];
            logtext += " Org-CodeBlocage: ";
            logtext += &d->CODEBLOCAGEORG[0];
            logdat->Write(logtext);
            sprintf(&cPHARMPURCHPRICE[0], "%10.2f", d->PHARMPURCHPRICEORG);
            sprintf(&cCUSTPURCHPRICE[0], "%10.2f", d->CUSTPURCHPRICEORG);
            sprintf(&cPHARMSELLPRICE[0], "%10.2f", d->PHARMSELLPRICEORG);
            sprintf(&cLPPR_PRICE[0], "%10.2f", d->LPPR_PRICEORG);
            sprintf(&cTFR_PRICE[0], "%10.2f", d->TFR_PRICEORG);
            sprintf(&cTAXRATE[0], "%10.2f", d->TAXRATE);
            logtext = now.AsString("%H:%M:%S");
            logtext += "               Org-AEP: ";
            logtext += &cPHARMPURCHPRICE[0];
            logtext += " Org-Netto: ";
            logtext += &cCUSTPURCHPRICE[0];
            logtext += " Org-AVP: ";
            logtext += &cPHARMSELLPRICE[0];
            logtext += " Org-LPPR: ";
            logtext += &cLPPR_PRICE[0];
            logtext += " Org-TFR: ";
            logtext += &cTFR_PRICE[0];
            logtext += " OrgTAX: ";
            logtext += &cTAXRATE[0];
            logtext += " Verfall: ";
            logtext += &cEXPIRYDATE[0];
            logdat->Write(logtext);
            logtext = now.AsString("%H:%M:%S");
            logtext += "               Org-SeraCode: ";
            logtext += &d->SERACODEORG[0];
            logtext += " Org-XMLCode: ";
            logtext += &d->XMLCODEORG[0];
            logtext += " Org-XMLText: ";
            logtext += &d->XMLTEXTORG[0];
            logdat->Write(logtext);
        }
    }
    return 0;
}

/*****************************************************************************/
/* Fügt eine Kopf bzw. Fusszeile ein                                         */
/*****************************************************************************/
int KscsrvInsKopfZlnAuf(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    nString nStr = &d->REMARKS[0];
    nString logtext;
    nString text;
    d->LACKREASON = 0;
    text = &d->REMARKS[0];
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  InsKopf: ";
        logtext += text;
        logdat->Write(logtext);
    }
    d->LACKREASON = 0;

    if (ps->Order() != NULL)
    {
        pxTextDoc* headp = ps->Order()->HeadText();
        headp->NewLine(text);
    }

    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* Schreiben Referenznummer                                                  */
/*****************************************************************************/
int KscsrvInsertReference(struct N_KSCSRVDATA* d, char* error_msg)
{
    d->LACKREASON = 0;
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    const int rc = pxInsertReferenceNr(ps, d->BRANCHNO, d->CUSTOMERNO, &d->REMARKS[0]);
    if (rc != 0)
    {
        AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = rc;
        return 6;
    }
    return 0;
}

/*****************************************************************************/
/* Oeffnen fuer Internet zurueckgestellten Auftrag                           */
/*****************************************************************************/
int KscsrvOpenorderInternetOrderno(struct N_KSCSRVDATA* d, char* error_msg)
{
    ps->Reset();
    nTime now;
    d->LACKREASON = 0;
    ps->SetTransmissionType(pxOrderTransmit :: tDCT_Serial);
    ps->NewOrder(d->ORDERNO);
    if (ps->Order() ==  NULL )
    {
        AllgStrCopy(&d->TEXT[0], TXT_AUFTR_NICHT_OFFEN , MAX_ERROR_MSG_AE);
        {
            return 6 ;
        }
    }
    ps->Order()->OpenOrder(cDBOPEN_INSERT);
    if ( ! (ps->Order()->IsGoodState()) )
    {
        AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->Order()->ErrorNumber();
        if( ps->Order()->IsFatalErrorState() || ps->Order()->IsAbendState() )
        {
            return -1;
        }
        else
        {
            if(ps->Order()->IsChangeable())
            {
                AllgStrCopy(&d->TEXT[0],  ps->Order()->ErrorMsg(), L_KSCSRVDATA_TEXT);
                return 0;
            }
            return 6;
        }
    }
    nString logtext;             // ein String-Objekt
    nString cOrder;              // ein String-Objekt
    nString cTerminal;           // ein String-Objekt
    char cCustomer[8];
    sprintf(&cCustomer[0], "%ld", ps->Order()->Customer()->KundenNr());
    sprintf(cTerminal, "%4.4s", (char*)ps->Session()->Device()->Name());
    if(sLogLevel > 0)
    {
        sLogLevel = 1;
        logdat->Start();
        logdat->SetIDFNr(&cCustomer[0]);
        logdat->SetTerminalID(cTerminal());
        logdat->Open();
        logdat->WriteList();
        cOrder = d->ORDERNO;
        cOrder.Trim(6,nString::cLEADING,'0');
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  OpenOrderOrderno Orderno: " + cOrder;
        logdat->Write(logtext);
    }

    initLog4Cplus();
    return 0;
}

/*****************************************************************************/
/* Zurückstellen Auftrag fuer Internet                                       */
/*****************************************************************************/
int KscsrvPostponeorderinternet(struct N_KSCSRVDATA* d, char* error_msg)
{
    d->LACKREASON = 0;
    ps->SetNotCloseOrder();
    ps->Order()->SetDefferedForInternet();
    ps->Order()->SetAuftragVomXML();
    return KscsrvCloseorder(d, error_msg);
}

/*****************************************************************************/
/* Schliessen Internetauftrag                                                */
/*****************************************************************************/
int KscsrvCloseorderInternet(struct N_KSCSRVDATA* d, char* error_msg)
{
    d->LACKREASON = 0;
    if(!ps->Order()->IsCallBack())
        ps->Order()->ClearProblemClearance();
    ps->Order()->ClearDefferedForInternet();
    ps->Order()->SetAuftragVomXML();
    KscsrvCloseorder(d, error_msg);
    return 0;
}

/*****************************************************************************/
/* Schreiben Textpostition                                                   */
/*****************************************************************************/
int KscsrvWritetextpos(struct N_KSCSRVDATA* d, char* error_msg)
{
    nString text;             // ein String-Objekt
    nTime now;
    nString logtext;
    d->LACKREASON = 0;
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    text = &d->REMARKS[0];
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  WriteText: ";
        logtext += text;
        logdat->Write(logtext);
    }
    d->LACKREASON = 0;
    ps->NewOrderTextItem(text);
    error_msg[0] = '\0';
    return 0;
}


void KscStructToDispoItem(tDISPOITEM* di, struct N_KSCSRVDATA* d)
{
     di->Bezeichnung            = &d->ARTICLENAME[0];
     di->Einheit                = &d->ARTICLEUNIT[0];
     di->Darreichform           = &d->HANDOUT[0];
     di->Bemerkungen            = &d->REMARKS[0];
     di->PreisEKApo             = d->PHARMPURCHPRICE;
     di->PreisEKGrosso          = d->PREISEKGROSSO;
     di->MengeBestellt          = d->ORDERQTY;
     di->TaxPflichtig           = true;//TODO check kann in gui eingestellt werden, alter code setzt aber immer 1
     di->WarenGruppeEigen       = "99999";
     di->UrsprungAuftragnr      = d->ORDERNOORIGIN;
     di->UrsprungPosnr          = d->POSNOORIGIN;
     di->GebuehrBearb           = d->POSTAGE;
     di->MWSTSchluessel         = (d->TAXRATE == 1) ? HALFTAX : FULLTAX;

}
/*****************************************************************************/
/* Schreibt Dispo-postition                                                  */
/*****************************************************************************/
int KscsrvWriteDispoItem(struct N_KSCSRVDATA* d, char* error_msg)
{
    nString text;             // ein String-Objekt
    nTime now;
    nString logtext;
    tDISPOITEM  di;

    KscStructToDispoItem(&di, d);

    ps->ClearError();

    ps->Order()->NewOrderItem_15(di, pxOrderItem::PurchaseOrder);
    if ( ! (ps->IsGoodState()) )
    {
       AllgStrCopy(error_msg, ps->ErrorMsg(), MAX_ERROR_MSG_AE);
       if (ps->IsFatalErrorState() || ps->IsAbendState())
       {
          return -1;
       }
       else
       {
           return -2;
       }
    }

    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  WriteDispoItem: ";
        logtext += text;
        logdat->Write(logtext);
    }
     return 0;
}

/*****************************************************************************/
/* Zurueckstellen Auftrag                                                  */
/*****************************************************************************/
int KscsrvPostponeorder(struct N_KSCSRVDATA* d, char* error_msg)
{
    d->LACKREASON = 0;
    if(ps->Order()->BatchSchreiben() == cORTYPE_UNKNOWN || ps->Order()->BatchSchreiben() == cORTYPE_TRANSFER)
    {
        ps->SetNotCloseOrder();
    }
    KscsrvCloseorder(d, error_msg);
    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* Stornieren Auftrag                                                        */
/*****************************************************************************/
int KscsrvCancelorder(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    d->LACKREASON = 0;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  CancelOrder ";
        logdat->Write(logtext);
    }
    d->ORDERNO = ps->Order()->KdAuftragNr();
    if(ps->CancelTransmission() != 0)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      CancelOrder Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        logdat->End();
        logdat->CloseSeralog();
        return 6;
    }
    logdat->End();
    logdat->CloseSeralog();
    return 0;
}

/*****************************************************************************/
/* Aendern Auftragsart                                                       */
/*****************************************************************************/
int KscsrvChangeorder(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    d->LACKREASON = 0;
    nString aufart;             // ein String-Objekt
    nString subart;             // ein String-Objekt
    aufart = &d->KINDOFORDER[0];
    subart = &d->SUB_ORDER_TYPE[0];
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  ChangeOrder ";
        logtext += " AArt: ";
        logtext += aufart;
        logtext += " SubType: ";
        logtext += subart;
        logtext += " KoArt: ";
        logtext += &d->SHIPMENTTYPE[0];
        logtext += " BuArt: ";
        logtext += &d->BOOKINGTYPE[0];
        logdat->Write(logtext);
    }
    if (ps->Order()->AnzPos() > 0)
    {
        if (ps->SubOrderType(&d->KINDOFORDER[0], &d->SUB_ORDER_TYPE[0], d->DELIVERYDATE) == NULL)
        //if (ps->SubOrderType(d->KINDOFORDER,d->SUB_ORDER_TYPE) == NULL)
        {
            AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
            AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
            d->LACKREASON = ps->ErrorNumber();
            if(sLogLevel > 0)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      ChangeOrder Error ";
                logtext += ps->ErrorMsg();
                logdat->Write(logtext);
                logdat->End();
                logdat->CloseSeralog();
            }
            return 6;
        }
    }
    ps->Order()->OrderType(aufart, d->SHIPMENTTYPE[0], d->BOOKINGTYPE[0], subart);
    if ( ! (ps->Order()->IsGoodState()) )
    {
        AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->Order()->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out: ChangeOrder ";
            logtext += "      ChangeOrder Error ";
            logtext += ps->Order()->ErrorMsg();
            logdat->Write(logtext);
        }
        return 6;
    }
    return 0;
}

/*****************************************************************************/
/* Einfuegen Rueckruf                                                        */
/*****************************************************************************/
int KscsrvAddCallback(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  Add Callback ";
        logdat->Write(logtext);
    }
    d->LACKREASON = 0;
    ps->CallBack();
    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* Pruefen Auftrag schon vorhanden                                           */
/*****************************************************************************/
int KscsrvCheckDoubleOrder(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  Check Double Order ";
        logdat->Write(logtext);
    }
    d->LACKREASON = 0;
    const int rc = ps->Order()->CheckDoubleOrder(&d->TEXT[0]);
    if (rc != 0)
    {
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out: Double Order set";
            logdat->Write(logtext);
        }
        d->LACKREASON = rc;
        ps->SetDoubleOrder();
        return 6;
    }
    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* Artikel-Ampel-Info                                                        */
/*****************************************************************************/
int KscsrvGetArticleInfo(struct N_ARTICLEINQUIRY* d, char* error_msg)
{
    nTime now;
    nString logtext;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  GetArticleInfo ";
    }
    pxOrderItem* orderitem;
    int i,lack;
    long lArtnr;
    char huelse[8];
    char* pInfo = &d->INFOBLOCK[0];
    if(sLogLevel > 1)
    {
        for(i = 1; i < 251; i++)
        {
            sprintf(&huelse[0], "%7.7s", pInfo);
            lArtnr = atol(&huelse[0]);
            if(lArtnr == 0) break;
            if( (i%10) == 0 )
            {
                logdat->Write(logtext);
                logtext = now.AsString("%H:%M:%S");
                logtext += "                     ";
            }
            logtext += &huelse[0];
            logtext += "   ";
            pInfo += 8;
        }
        logdat->Write(logtext);
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out:                 ";
        pInfo = &d->INFOBLOCK[0];
    }
    for(i = 1; i < 251; i++)
    {
        sprintf(&huelse[0], "%7.7s", pInfo);
        if(sLogLevel > 1)
        {
            if( (i%10) == 0 )
            {
                logdat->Write(logtext);
                logtext = now.AsString("%H:%M:%S");
                logtext += "                     ";
            }
        }
        lArtnr = atol(&huelse[0]);
        if(lArtnr == 0) break;
        if(sLogLevel > 1)
        {
            logtext += &huelse[0];
        }
        orderitem = ps->ItemQuery(lArtnr, 0);
        if (orderitem != NULL)
        {
            if(orderitem->MengeGeliefert() > 0)
            {
                pInfo[7] = '0';
                if(sLogLevel > 1)
                {
                    logtext += " 0 ";
                }
            }
            else
            {
                lack = orderitem->GetError(error_msg);
                if (lack > 100000) lack /= 100;
                GetLackCodebyReason(lack, &huelse[0]);
                pInfo[7] = huelse[0];
                if(sLogLevel > 1)
                {
                    logtext += " ";
                    logtext += huelse[0];
                    logtext += " ";
                }
            }
        }
        else
        {
            pInfo[7] = '2';
            if(sLogLevel > 1)
            {
                logtext += " 2 ";
            }
        }
        pInfo += 8;
    }
    if(sLogLevel > 1)
    {
        logdat->Write(logtext);
    }
    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* Artikel-Ampel-Info nach Code                                              */
/*****************************************************************************/
int KscsrvGetArticleInfoCode(struct N_ARTICLEINQUIRY* d, char* error_msg)
{
    artcodesS codes;
    nTime now;
    nString logtext;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  GetArticleInfoCode ";
    }
    pxOrderItem* orderitem;
    int i,lack;
    long lArtnr;
    char huelse[8];
    char* pInfo = &d->INFOBLOCK[0];
    if(sLogLevel > 1)
    {
        for(i = 1; i < 151; i++)
        {
            if(pInfo[0] == ' ') break;
            sprintf(&codes.ARTICLE_CODE[0], "%*.*s", L_ARTCODES_ARTICLE_CODE, L_ARTCODES_ARTICLE_CODE, pInfo);
            kscartSel_NoByCode(&codes, error_msg);
            lArtnr = codes.ARTICLENO;
            if( (i%10) == 0 )
            {
                logdat->Write(logtext);
                logtext = now.AsString("%H:%M:%S");
                logtext += "                     ";
            }
            logtext += &codes.ARTICLE_CODE[0];
            logtext += "   ";
            pInfo += 26;
        }
        logdat->Write(logtext);
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out:                 ";
        pInfo = &d->INFOBLOCK[0];
    }
    for(i = 1; i < 151; i++)
    {
        if(pInfo[0] == ' ') break;
        sprintf(&codes.ARTICLE_CODE[0], "%*.*s", L_ARTCODES_ARTICLE_CODE, L_ARTCODES_ARTICLE_CODE, pInfo);
        kscartSel_NoByCode(&codes, error_msg);
        lArtnr = codes.ARTICLENO;
        if(sLogLevel > 1)
        {
            if( (i%10) == 0 )
            {
                logdat->Write(logtext);
                logtext = now.AsString("%H:%M:%S");
                logtext += "                     ";
            }
        }
        if(sLogLevel > 1)
        {
            logtext += &codes.ARTICLE_CODE[0];
        }
        orderitem = ps->ItemQuery(lArtnr, 0);
        if (orderitem != NULL)
        {
            if(orderitem->MengeGeliefert() > 0)
            {
                pInfo[25] = '0';
                if(sLogLevel > 1)
                {
                    logtext += " 0 ";
                }
            }
            else
            {
                lack = orderitem->GetError(error_msg);
                if (lack > 100000) lack = lack/100;
                GetLackCodebyReason(lack, &huelse[0]);
                pInfo[25] = huelse[0];
                if(sLogLevel > 1)
                {
                    logtext += " ";
                    logtext += huelse[0];
                    logtext += " ";
                }
            }
        }
        else
        {
            pInfo[25] = '2';
            if(sLogLevel > 1)
            {
                logtext += " 2 ";
            }
        }
        pInfo += 26;
    }
    if(sLogLevel > 1)
    {
        logdat->Write(logtext);
    }
    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* BULK-Verfügbarkeitsanfragen über neues Buchungsmodul                      */
/*****************************************************************************/

int KscsrvGetArticleAvailabilityBulk(struct N_ARTICLEINQUIRYBULK* d,char* /*error_msg*/)
{
    if (ps->Session()->Branch()->FilialNr() != d->BRANCHNO)
    {
        pxBranch CustBranch(ps->Session(), d->BRANCHNO);
        if (CustBranch.IsGoodState())
        {
            *(ps->Session()->Branch()) = CustBranch;
        }
        else
        {
            return -1;
        }
    }

    pxStockBulkInquiry bulkInquiry(ps);
    bulkInquiry.setBranchAndCustomer(d->BRANCHNO, d->CUSTOMERNO);
    basar::VarString articleList = &d->INFOBLOCK[0];
    articleList.trim();
    basar::VarString result = bulkInquiry.getArticleAvailability(articleList);
    AllgStrCopy(&d->INFOBLOCK[0], result.c_str(), L_ARTICLEINQUIRYBULK_INFOBLOCK);
    return 0;
}

/*****************************************************************************/
/* BULK-Bestandsanfragen über neues Buchungsmodul                            */
/*****************************************************************************/

int KscsrvGetArticleStockBulk(struct N_ARTICLEINQUIRYBULK* d, char* /*error_msg*/)
{
    if (ps->Session()->Branch()->FilialNr() != d->BRANCHNO)
    {
        pxBranch CustBranch(ps->Session(), d->BRANCHNO);
        if (CustBranch.IsGoodState())
        {
            *(ps->Session()->Branch()) = CustBranch;
        }
        else
        {
            return -1;
        }
    }

    pxStockBulkInquiry bulkInquiry(ps);
    bulkInquiry.setBranchAndCustomer(d->BRANCHNO, d->CUSTOMERNO);
    basar::VarString articleList = &d->INFOBLOCK[0];
    articleList.trim();
    basar::VarString result = bulkInquiry.getArticleStock(articleList);
    AllgStrCopy(&d->INFOBLOCK[0], result.c_str(), L_ARTICLEINQUIRYBULK_INFOBLOCK);
    return 0;
}

/*****************************************************************************/
/* Anfordern der Artikelinformation unter Beruecksichtigung der Kundenbedingungen */
/*****************************************************************************/
int KscsrvGetArticleInquiry(struct N_KSCSRVDATA* d, char* error_msg)
{
    artcodesS codes;
    nTime now;
    nString cArtikel;
    nString cEAN;
    nString logtext;
//  char cMenge[5];
    double dLegallPrice;
    double LogZuschlag;
    pxOrderItem* orderitem;
    pxCountryCodes* CC = NULL;
    d->LACKREASON = 0;
    if(d->ARTICLE_CODE[0] != ' ')
    {
        sprintf(&codes.ARTICLE_CODE[0], "%*.*s", L_ARTCODES_ARTICLE_CODE, L_ARTCODES_ARTICLE_CODE, &d->ARTICLE_CODE[0]);
        kscartSel_NoByCode(&codes, error_msg);
        d->ARTICLENO = codes.ARTICLENO;
        cArtikel = d->ARTICLENO;
        cArtikel.Trim(7,nString::cLEADING,'0');
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  ArticleInfo ";
            logtext += " ARTICLE_CODE: ";
            logtext += &codes.ARTICLE_CODE[0];
        }
    }
    else if(d->ARTICLENO == 0)
    {
        d->ARTICLENO = atol(ps->ConvertEan2Pzn(&d->EAN[0]));
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  ArticleInfo ";
            logtext += " EAN: ";
            logtext += &d->EAN[0];
        }
    }
    else
    {
        cArtikel = d->ARTICLENO;
        cArtikel.Trim(7, nString::cLEADING, '0');
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  ArticleInfo ";
            logtext += " PZN: ";
            logtext += cArtikel;
        }
    }
    if(sLogLevel > 1)
    {
        logdat->Write(logtext);
    }

    orderitem = ps->ItemQuery(d->ARTICLENO,d->ORDERQTY);

    AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
    AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
    d->LACKREASON = ps->Order()->ErrorNumber();

    if (orderitem == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      ArticleInfo Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
        }
        return 6;
    }

    if(sLogLevel > 2)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out: ArticleInfo ";
    }
    if(orderitem->ArtBase() != NULL && orderitem->ArtBase()->IsGoodState())
    {
        short TextKey = 0;
        pxArticleText* ptext = NULL;
        TextKey = orderitem->ArtBase()->TextKey();
        if(TextKey > 0)
        {
            ptext = new pxArticleText(ps->Session(), TextKey);
            if ( !ptext->Get(cDBGET_READONLY))
            {
                strncpy(&d->ARTICLETEXT[0],
                        ptext->Text(),
                        L_KSCSRVDATA_ARTICLETEXT);
            }
            delete ptext;
        }
        strncpy(&d->ARTICLENAME[0],
                orderitem->ArtBase()->Bezeichnung(),
                L_KSCSRVDATA_ARTICLENAME);
        strncpy(&d->ARTICLEUNIT[0],
                orderitem->ArtBase()->Einheit(),
                L_KSCSRVDATA_ARTICLEUNIT);
        strncpy(&d->HANDOUT[0],
                orderitem->ArtBase()->Darreichform(),
                L_KSCSRVDATA_HANDOUT);
        if(ps->Order()->Customer()->PreWholeTyp() == '1')
        {
            d->CODEBLOCAGE[0] = orderitem->ArtBase()->CodeBlocage();
            if(d->CODEBLOCAGE[0] != 'P')
            {
                d->CODEBLOCAGE[0] = '0';
            }
        }
        else
        {
            d->CODEBLOCAGE[0] = orderitem->ArtBase()->CodeBlocage();
        }
        if(sLogLevel > 2)
        {
            logtext += " Name: ";
            logtext += &d->ARTICLENAME[0];
            logtext += " Unit: ";
            logtext += &d->ARTICLEUNIT[0];
            logtext += " Handout: ";
            logtext += &d->HANDOUT[0];
            logtext += " CodeBlocage: ";
            logtext += &d->CODEBLOCAGE[0];
        }
    }
    else
    {
        d->CODEBLOCAGE[0] = '2';
        if(sLogLevel > 2)
        {
            logtext += " CodeBlocage: ";
            logtext += &d->CODEBLOCAGE[0];
        }
    }
    if(sLogLevel > 2)
    {
        logdat->Write(logtext);
        logtext = now.AsString("%H:%M:%S");
        logtext += "                  ";
    }

    transferDeliveryInformation( d, orderitem, true );

    d->PHARMPURCHPRICE = orderitem->PreisEKApo();
    d->PREISFAKTUR = orderitem->InvoiceValue();     // Rabattierter Preis
    d->CUSTPURCHPRICE = orderitem->PreisEKApoNetto();
    if(d->CUSTPURCHPRICE == 0)
        d->CUSTPURCHPRICE = orderitem->PreisEKApo();
    d->BASEPRICE = orderitem->BasePrice();
    d->MARGIN = orderitem->getMarginGepAep();
    LogZuschlag = orderitem->GetLogisticAddition();
    if(LogZuschlag > 0)
    {
        //if( Angebotstyp = "A" )
        //{
        //  d->LOGISTICSADDITION = (orderitem->PreisEKApo() * LogZuschlag / 100);
        //}
        //else
        //{
        d->LOGISTICSADDITION = d->BASEPRICE * LogZuschlag / 100;
        //}
    }
    else
    {
        d->LOGISTICSADDITION = 0;
    }

    dLegallPrice = (double)orderitem->GetLegallBreizhPrice();
    if(dLegallPrice > 0)
    {
        d->PHARMPURCHPRICE = dLegallPrice;
        d->CUSTPURCHPRICE = dLegallPrice;
    }

    d->PHARMSELLPRICE = orderitem->getPharmacySellPrice();
    d->LPPR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'2');
    d->TFR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'1');
    //d->QTYRESERVATION = orderitem->PreisVKApo();
    if ( ps->Order()->Customer()->IsNoInfoLevel()  ||
         ps->Order()->Customer()->IsInfoLevelLow() ||
         d->ORDERQTY == 0 )
    {
        if(orderitem->MengeGeliefert() > 0) d->AVAILABLE[0] = '1';
        else d->AVAILABLE[0] = '0';
        if(sLogLevel > 2)
        {
            logtext += "AVAILABLE ";
            logtext += &d->AVAILABLE[0];
        }
    }
    else
    {
        d->QTYLACK = (d->ORDERQTY -
                      orderitem->MengeGeliefert() -
                      //orderitem->MengeVerbund()) -
                      orderitem->MengeMoeglich()) -
                      orderitem->MengeNachgeliefert() -
                      orderitem->MengeDisponiert();
        if(d->QTYLACK < 0) d->QTYLACK = 0;
        d->AUXQTY = orderitem->TotalIBTQuantity(); // d->AUXQTY = orderitem->MengeVerbund();
        d->AUXQTYPOSSIBLE = orderitem->MengeMoeglich();
        d->RESTDELIVERYQTY = orderitem->MengeNachgeliefert();
        if ( d->RESTDELIVERYQTY == 0 )
        {
            if (orderitem->IsRestDeliveryPossible())
            {
                d->RESTDELIVERYQTY = d->QTYLACK;
                d->QTYLACK = 0;
            }
        }
        d->DELIVERYQTY = orderitem->MengeGeliefert();
        d->DISPOQTY = orderitem->MengeDisponiert();
        d->QTYNATRA = orderitem->MengeNatra();
        d->AUXBRANCHNO = ps->Order()->AuxFil();
        if(sLogLevel > 2)
        {
            nString cQTY;
            nString cQTYLack;
            nString cAUXQTY;
            nString cAUXBRANCHNO;
            nString cRESTQTY;
            nString cDISPOQTY;
            nString cQTYNATRA;
            cQTY = d->DELIVERYQTY;
            cQTY.Trim(5, nString::cLEADING, '0');
            cQTYLack = d->QTYLACK;
            cQTYLack.Trim(5, nString::cLEADING, '0');
            cAUXQTY = d->AUXQTY;
            cAUXQTY.Trim(5, nString::cLEADING, '0');
            cRESTQTY = d->RESTDELIVERYQTY;
            cRESTQTY.Trim(5, nString::cLEADING, '0');
            cDISPOQTY = d->DISPOQTY;
            cDISPOQTY.Trim(5, nString::cLEADING, '0');
            cQTYNATRA = d->QTYNATRA;
            cQTYNATRA.Trim(5, nString::cLEADING, '0');
            cAUXBRANCHNO = d->AUXBRANCHNO;
            cAUXBRANCHNO.Trim(2, nString::cLEADING, '0');
            logtext = now.AsString("%H:%M:%S");
            logtext += "               delivery Qty: ";
            logtext += cQTY;
            logtext += " lack Qty: ";
            logtext += cQTYLack;
            logtext += " rest Qty: ";
            logtext += cRESTQTY;
            logtext += " dispo Qty: ";
            logtext += cDISPOQTY;
            logtext += " Natra Qty: ";
            logtext += cQTYNATRA;
            logtext += " aux Qty: ";
            logtext += cAUXQTY;
            logtext += " Branch: ";
            logtext += cAUXBRANCHNO;
            logdat->Write(logtext);
        }
    }
    if(sLogLevel > 2)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += "                  ";
    }
    strncpy(&d->EAN[0], ps->ConvertPzn2Ean(orderitem->ArtikelNr(), 13), L_KSCSRVDATA_EAN);
    d->QTYRESERVATION = orderitem->MengeReserviert();
    if (ps->Session()->isSwitzerland())
    {
        if(ps->Order()->Customer()->Flags().ExpiryInfo() == '1'
                || ps->Order()->Customer()->Flags().ExpiryInfo() == '3' )
        {
            d->EXPIRYDATE = orderitem->ArticleExpireDate();
        }
        else
        {
            d->EXPIRYDATE = 0;
        }
    }
    else
    {
        d->EXPIRYDATE = orderitem->ArticleExpireDate();
    }
    d->TAXRATE = orderitem->SalesTaxRate();
    if(     (orderitem->IsQStateAlternate() ||
             orderitem->IsReimportArtikel()) )
//              orderitem->MengeBestaetigt() > 0 )
    {
        codes.ARTICLENO = orderitem->ArtikelNr();
        kscartSel_Preferred(&codes, error_msg);
        strncpy(&d->ARTICLE_CODEORG[0], &d->ARTICLE_CODE[0], L_ARTCODES_ARTICLE_CODE);
        strncpy(&d->ARTICLE_CODE[0], &codes.ARTICLE_CODE[0], L_ARTCODES_ARTICLE_CODE);
        d->ARTICLENOORG = d->ARTICLENO;
        d->ARTICLENO = orderitem->ArtikelNr();
        if(sLogLevel > 2)
        {
            nString cArtikelNo;
            nString cArtikelNoOrg;
            cArtikelNo = d->ARTICLENO;
            cArtikelNo.Trim(7, nString::cLEADING, '0');
            cArtikelNoOrg = d->ARTICLENOORG;
            cArtikelNoOrg.Trim(7, nString::cLEADING, '0');
            logtext = now.AsString("%H:%M:%S");
            logtext += "               PZN: ";
            logtext += cArtikelNo;
            logtext += " PZN-ORG: ";
            logtext += cArtikelNoOrg;
            logdat->Write(logtext);
        }
        strncpy(&d->EANORG[0], ps->ConvertPzn2Ean(d->ARTICLENOORG, 13), L_KSCSRVDATA_EAN);
        pxArticleInfo* ArtInfo = orderitem->ArticleInfoRequest(d->ARTICLENOORG,orderitem->MengeBestaetigt());
        if (ArtInfo != NULL)
        {
            strncpy(&d->ARTICLENAMEORG[0], ArtInfo->ArtBase()->Bezeichnung(), L_KSCSRVDATA_ARTICLENAMEORG);
            strncpy(&d->ARTICLEUNITORG[0], ArtInfo->ArtBase()->Einheit(), L_KSCSRVDATA_ARTICLEUNITORG);
            strncpy(&d->HANDOUTORG[0], ArtInfo->ArtBase()->Darreichform(), L_KSCSRVDATA_HANDOUTORG);
            d->PHARMPURCHPRICEORG = ArtInfo->PreisEKApo();
            //d->CUSTPURCHPRICEORG = ArtInfo->PreisEKApoNetto();
            //if(d->CUSTPURCHPRICEORG == 0)
            d->CUSTPURCHPRICEORG = ArtInfo->PreisEKApo();
            /*
                dLegallPrice = (double)ArtInfo->GetLegallBreizhPrice();
                if(dLegallPrice > 0)
                {
                        d->PHARMPURCHPRICEORG = dLegallPrice;
                        d->CUSTPURCHPRICEORG = dLegallPrice;
                }
            */
            d->PHARMSELLPRICEORG = ArtInfo->PreisVKApo();
            d->LPPR_PRICEORG = orderitem->ReimbursementPrice(d->ARTICLENOORG, '2');
            d->TFR_PRICEORG = orderitem->ReimbursementPrice(d->ARTICLENOORG, '1');
            d->TAXRATEORG = ArtInfo->SalesTaxRate();
            d->CODEBLOCAGEORG[0] = ArtInfo->CodeBlocage();
            if (ps->Session()->isFrance() || ps->Session()->isFrancePrewhole())
            {
                CC = ps->CountryCodesInfo(ps->Order()->FilialNr(), &d->CODEBLOCAGEORG[0]);
                if(CC != NULL)
                {
                    strncpy(&d->SERACODEORG[0], CC->SeraCode(), L_KSCSRVDATA_SERACODEORG);
                    strncpy(&d->XMLCODEORG[0], CC->XMLCode(), L_KSCSRVDATA_XMLCODEORG);
                    strncpy(&d->XMLTEXTORG[0], CC->XMLText(), L_KSCSRVDATA_XMLTEXTORG);
                    delete CC;
                }
            }
        }
    }
    d->LACKREASON = orderitem->GetError(&d->TEXT[0]);
    if (ps->Session()->isFrance() || ps->Session()->isFrancePrewhole())
    {
        CC = ps->CountryCodesInfo(ps->Order()->FilialNr(), &d->CODEBLOCAGE[0]);
        if(CC != NULL)
        {
            strncpy(&d->SERACODE[0], CC->SeraCode(), L_KSCSRVDATA_SERACODE);
            strncpy(&d->XMLCODE[0], CC->XMLCode(), L_KSCSRVDATA_XMLCODE);
            strncpy(&d->XMLTEXT[0], CC->XMLText(), L_KSCSRVDATA_XMLTEXT);
            delete CC;
        }
    }
    else if (ps->Session()->Country() == "AU" || ps->Session()->isGermany())
    {
        nString xmlcode;             // ein String-Objekt
        xmlcode = d->LACKREASON / 100;
        xmlcode.Trim(L_KSCSRVDATA_XMLCODE, nString::cLEADING, '0');
        strncpy(&d->XMLCODE[0], xmlcode, L_KSCSRVDATA_XMLCODE);
        if(d->LACKREASON != 0)
        {
            CC = ps->CountryCodesInfo(ps->Order()->FilialNr(), &d->XMLCODE[0], static_cast<short>(pxCountryCodes::CCT_XMLCODE));
            if(CC != NULL)
            {
                strncpy(&d->SERACODE[0], CC->SeraCode(), L_KSCSRVDATA_SERACODE);
                strncpy(&d->XMLTEXT[0], CC->XMLText(), L_KSCSRVDATA_XMLTEXT);
                strncpy(&d->LACKREASONCTYCODE[0], CC->InfoCode(), L_KSCSRVDATA_LACKREASONCTYCODE);
                delete CC;
            }
        }
    }
    if(sLogLevel > 2)
    {
        char cPHARMPURCHPRICE[11];
        char cCUSTPURCHPRICE[11];
        char cPHARMSELLPRICE[11];
        char cLPPR_PRICE[11];
        char cTFR_PRICE[11];
        char cBASEPRICE[11];
        char cEXPIRYDATE[11];
        char cTAXRATE[11];
        char cLOGISTICSADDITION[11];
        sprintf(&cPHARMPURCHPRICE[0], "%10.2f", d->PHARMPURCHPRICE);
        sprintf(&cCUSTPURCHPRICE[0], "%10.2f", d->CUSTPURCHPRICE);
        sprintf(&cPHARMSELLPRICE[0], "%10.2f", d->PHARMSELLPRICE);
        sprintf(&cLOGISTICSADDITION[0], "%10.2f", d->LOGISTICSADDITION);
        sprintf(&cLPPR_PRICE[0], "%10.2f", d->LPPR_PRICE);
        sprintf(&cTFR_PRICE[0], "%10.2f", d->TFR_PRICE);
        sprintf(&cBASEPRICE[0], "%10.2f", d->BASEPRICE);
        sprintf(&cEXPIRYDATE[0], "%02ld.%02ld.%04ld",
                d->EXPIRYDATE%100,
                d->EXPIRYDATE/100%100,
                d->EXPIRYDATE/10000);
        sprintf(&cTAXRATE[0], "%10.2f", d->TAXRATE);
        logtext = now.AsString("%H:%M:%S");
        logtext += "               AEP: ";
        logtext += &cPHARMPURCHPRICE[0];
        logtext += " Netto: ";
        logtext += &cCUSTPURCHPRICE[0];
        logtext += " AVP: ";
        logtext += &cPHARMSELLPRICE[0];
        logtext += " LPPR: ";
        logtext += &cLPPR_PRICE[0];
        logtext += " TFR: ";
        logtext += &cTFR_PRICE[0];
        logtext += " BASE: ";
        logtext += &cBASEPRICE[0];
        logtext += " LOG: ";
        logtext += &cLOGISTICSADDITION[0];
        logtext += " TAX: ";
        logtext += &cTAXRATE[0];
        logtext += " Verfall: ";
        logtext += &cEXPIRYDATE[0];
        logdat->Write(logtext);
        logtext = now.AsString("%H:%M:%S");
        logtext += "               SeraCode: ";
        logtext += &d->SERACODE[0];
        logtext += " XMLCode: ";
        logtext += &d->XMLCODE[0];
        logtext += " XMLText: ";
        logtext += &d->XMLTEXT[0];
        logdat->Write(logtext);
        if(d->ARTICLENOORG > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "               Org-Name: ";
            logtext += &d->ARTICLENAMEORG[0];
            logtext += " Org-Unit: ";
            logtext += &d->ARTICLEUNITORG[0];
            logtext += " Org-Handout: ";
            logtext += &d->HANDOUTORG[0];
            logtext += " Org-CodeBlocage: ";
            logtext += &d->CODEBLOCAGEORG[0];
            logdat->Write(logtext);
            sprintf(&cPHARMPURCHPRICE[0], "%10.2f", d->PHARMPURCHPRICEORG);
            sprintf(&cCUSTPURCHPRICE[0], "%10.2f", d->CUSTPURCHPRICEORG);
            sprintf(&cPHARMSELLPRICE[0], "%10.2f", d->PHARMSELLPRICEORG);
            sprintf(&cTFR_PRICE[0], "%10.2f", d->TFR_PRICEORG);
            sprintf(&cTAXRATE[0], "%10.2f", d->TAXRATE);
            logtext = now.AsString("%H:%M:%S");
            logtext += "               Org-AEP: ";
            logtext += &cPHARMPURCHPRICE[0];
            logtext += " Org-Netto: ";
            logtext += &cCUSTPURCHPRICE[0];
            logtext += " Org-AVP: ";
            logtext += &cPHARMSELLPRICE[0];
            logtext += " Org-LPPR: ";
            logtext += &cLPPR_PRICE[0];
            logtext += " Org-TFR: ";
            logtext += &cTFR_PRICE[0];
            logtext += " OrgTAX: ";
            logtext += &cTAXRATE[0];
            logtext += " Verfall: ";
            logtext += &cEXPIRYDATE[0];
            logdat->Write(logtext);
            logtext = now.AsString("%H:%M:%S");
            logtext += "               Org-SeraCode: ";
            logtext += &d->SERACODEORG[0];
            logtext += " Org-XMLCode: ";
            logtext += &d->XMLCODEORG[0];
            logtext += " Org-XMLText: ";
            logtext += &d->XMLTEXTORG[0];
            logdat->Write(logtext);
        }
    }
    pxSupplDeliveryInfo deliveryInfo(ps, orderitem->ArtikelNr());
    deliveryInfo.Get();
    if (deliveryInfo.IsGoodState())
    {
        d->PREDICTEDAVAILABILITYDATE = deliveryInfo.PredictedAvailDate().getDate();
    }
    strncpy(&d->LACKREASONLIST[0], orderitem->GetLackReasonList().c_str(), L_KSCSRVDATA_LACKREASONLIST);
    return 0;
}

/*****************************************************************************/
/* Setzen Datum verzögerte Auslieferung                                      */
/*****************************************************************************/
int KscsrvSetdelayeddate(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    nString cTOURDATE;
    cTOURDATE.Trim(10, nString::cLEADING, '0');
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  SetDate ";
        sprintf((char*) cTOURDATE,"%02ld.%02ld.%04ld",
                d->TOURDATE%100,
                d->TOURDATE/100%100,
                d->TOURDATE/10000);
        logtext += cTOURDATE;
        logdat->Write(logtext);
    }
    nDate actdate;
    nDate deldate(d->TOURDATE);
    if(actdate < deldate)
    {
        if ( ps->Order()->OrderType().IsNoDD() )
        {
            ps->Order()->SetDatumAuslieferung(0);
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += " Out:  Not allowed for this ordertype ";
                logdat->Write(logtext);
            }
        }
        else if(ps->Order()->AnzPos() == 0)
        {
            ps->Order()->SetDatumAuslieferung(d->TOURDATE);
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += " Out:  Set To ";
                sprintf((char*) cTOURDATE,"%02ld.%02ld.%04ld",
                        d->TOURDATE%100,
                        d->TOURDATE/100%100,
                        d->TOURDATE/10000);
                logtext += cTOURDATE;
                logdat->Write(logtext);
            }
            ps->Order()->SetDeliveryDatePreset();
        }
        else if(ps->Order()->DatumAuslieferung() != deldate)
        {
            ps->Order()->SetDatumAuslieferung(d->TOURDATE);
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += " Out:  Set To ";
                sprintf((char*) cTOURDATE,"%02ld.%02ld.%04ld",
                        d->TOURDATE%100,
                        d->TOURDATE/100%100,
                        d->TOURDATE/10000);
                logtext += cTOURDATE;
                logdat->Write(logtext);
            }
            ps->Order()->SetDeliveryDatePreset();
        }
    }
    else
    {
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:  Not Set (equal today) ";
            logdat->Write(logtext);
        }
    }
    if ( ! (ps->Order()->IsGoodState()) )
    {
        AllgStrCopy(error_msg, ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
        if( ps->Order()->IsFatalErrorState() || ps->Order()->IsAbendState() )
        {
            return -1;
        }
        else
        {
            return -2;
        }
    }
    return 0;
}

/*****************************************************************************/
/* Setzen Batchschreiben                                                     */
/*****************************************************************************/
int KscsrvSetBatchOrderTyp(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    nString cValueDate;
    nString cBatchschreiben;
    nString cBranchnoorg;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:   SetBatchOrderTyp ";
        cValueDate = d->VALUTADATUM;
        cValueDate.Trim(8, nString::cLEADING, '0');
        logtext += cValueDate;
        logtext += " Batchschreiben: ";
        cBatchschreiben = d->BATCHSCHREIBEN;
        cBatchschreiben.Trim(2, nString::cLEADING, '0');
        logtext += cBatchschreiben;
        logtext += " BranchnoOrg: ";
        cBranchnoorg = d->BRANCHNOORIGIN;
        cBranchnoorg.Trim(2, nString::cLEADING, '0');
        logtext += cBranchnoorg;
        logdat->Write(logtext);
    }
    nString jobno;
    nDate datum(d->VALUTADATUM);
    pxCustOrderInfo *orderinfo = NULL;
    ps->Order()->BatchSchreiben(static_cast<OriginTypeEnum>(d->BATCHSCHREIBEN));
    ps->Order()->HerkunftFiliale(d->BRANCHNOORIGIN);
    if(static_cast<nTime>(datum) <= now)
    {
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:   ValueDate not set < Actdate";
            logdat->Write(logtext);
        }
    }
    if ( d->BATCHSCHREIBEN == cORTYPE_TRANSFER ||
            d->BATCHSCHREIBEN == cORTYPE_BATCH_TRANSFER)
    {
        const short mAuto = ps->Order()->OrderType().ValMonthsAuto();
        if (d->VALUTADATUM > 0)
        {
            datum.AddMonth(mAuto);
            ps->Order()->ValDate(datum);
            ps->Order()->SetDatumValutaBatch(ps->Order()->DatumValuta());
        }
        else
        {
            if (mAuto > 0)
            {
                ps->Order()->ValDateMonAuto(mAuto);
            }
        }
    }
    if(ps->Order()->DatumValuta() == pxConstants::NullDate)
    {
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:   ValueDate not set";
            logdat->Write(logtext);
        }
    }
    else
    {
        ps->Order()->SetDatumValutaBatch(datum);
        if (ps->Session()->isBulgaria())
        {
            ps->Order()->SetOrderWithTimeForPayment();
            if ( ! (ps->Order()->IsGoodState()) )
            {
                if(sLogLevel > 1)
                {
                    logtext = now.AsString("%H:%M:%S");
                    logtext += " Out:   ValueDate not set: KL";
                    logdat->Write(logtext);
                }
                error_msg[0] = '\0';
                return 0;
            }
        }
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:   ValueDate set correctly";
            logdat->Write(logtext);
        }
    }
    orderinfo = new pxCustOrderInfo((ps->Session()));
    orderinfo->CheckMembers();
    orderinfo->SetOrderNr(ps->Order()->KdAuftragNr());
    orderinfo->SetEdiLieferSchein(d->EDILIEFERSCHEIN[0]);
    orderinfo->SetBatchOrderNr(d->ORDERNOORIGIN);
    jobno = &d->JOBNO[0];
    orderinfo->SetKdAuftragBestellNr(jobno);
    orderinfo->Put();
    delete orderinfo;
    orderinfo = NULL;
    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
// KscsrvSetTenderNo
/*****************************************************************************/
int KscsrvSetTenderNo(struct N_KSCSRVDATA* d, char* error_msg)
{
    ps->Order()->SetTenderNo(d->TENDERNO);
    error_msg[0] = '\0';
    return 0;
}// KscsrvSetTenderNo

/*************************************************************************/
// KscsrvSetTourId
/*************************************************************************/
int KscsrvSetTourId(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    nString tourid = &d->TOURID[0]; // ein String-Objekt
    nDate actdate;
    nDate deldate(d->TOURDATE);
    deldate = ps->Order()->DatumAuslieferung();
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += "In    SetTourId ";
        logtext += tourid;
        logdat->Write(logtext);
    }
    if(!ps->Order()->IsValidRoute(tourid))
    {
        if(actdate < deldate)
        {
            if(ps->Order()->IsDeliveryDatePreset())
            {
                ps->Order()->SetNextValidRoute(tourid);
            }
        }
        else
        {
            ps->Order()->SetNextValidRoute(tourid);
        }
    }
    else
    {
        if(actdate < deldate)
        {
            if(ps->Order()->IsDeliveryDatePreset())
            {
                ps->Order()->getTourAssignmentUtil()->resetInjections();
                ps->Order()->getTourAssignmentUtil()->injectDesiredTourId( tourid );
                ps->Order()->getTourAssignmentUtil()->assignTour();
            }
        }
        else
        {
            ps->Order()->getTourAssignmentUtil()->resetInjections();
            ps->Order()->getTourAssignmentUtil()->injectDesiredTourId(tourid);
            ps->Order()->getTourAssignmentUtil()->assignTour();
        }
    }
    AllgStrCopy(&d->TOURID[0], ps->Order()->TourId(), L_KSCSRVDATA_TOURID);
    d->TOURDATE = ps->Order()->DatumAuslieferung().GetYYYYMMDD();
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += "OUT     SetTourId ";
        logtext += &d->TOURID[0];
        logdat->Write(logtext);
    }
    error_msg[0] = '\0';
    return 0;
}// KscsrvSetTourId

/*************************************************************************/
// KscsrvSetBTMLicense
/*************************************************************************/
int KscsrvSetBTMLicense(struct N_KSCSRVDATA* d, char* error_msg)
{
    nString btmlicense;             // ein String-Objekt
    btmlicense = &d->BTMFORMULARNR[0];
    ps->Order()->SetBTMFormularNr(d->DATUMBTM, btmlicense);
    error_msg[0] = '\0';
    return 0;
}// KscsrvSetBTMLicense

/*****************************************************************************/
/* Holen der endgueltigen Positionen aktuellen Auftrages                     */
/*****************************************************************************/
int KscsrvGetProforma(struct N_KSCSRVDATA* d, char* error_msg)
{
//  static int maxanz = 0;
    static size_t anz = 0;
    nString cEAN;
    double dLegallPrice;
    double LogZuschlag;
    nTime now;
    nString logtext;
    promotionsS promo;
    error_msg[0] = '\0';
    if (!anz)
    {
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:   GetProforma ";
            logdat->Write(logtext);
        }
        ps->EndProforma();
        oItemList = ps->Order()->ItemListProforma();
        if (ps->Session()->isFrance())
        {
            anz = ps->Order()->FirstTransPos();
        }
    }

    pxOrderItem* orderitem = dynamic_cast<pxOrderItem*>(oItemList->At(anz));
    if (orderitem != NULL)
    {
        if(orderitem->ArtBase() != NULL && orderitem->ArtBase()->IsGoodState())
        {
            const short TextKey = orderitem->ArtBase()->TextKey();
            if(TextKey > 0)
            {
                pxArticleText* ptext = new pxArticleText(ps->Session(), TextKey);
                if (!ptext->Get(cDBGET_READONLY))
                {
                    strncpy(&d->ARTICLETEXT[0], ptext->Text(), L_KSCSRVDATA_ARTICLETEXT);
                }
                delete ptext;
            }
            strncpy(&d->ARTICLENAME[0], orderitem->ArtBase()->Bezeichnung(), L_KSCSRVDATA_ARTICLENAME);
            strncpy(&d->ARTIKEL_LANGNAME[0], orderitem->ArtBase()->ArtikelLangname(), L_KSCSRVDATA_ARTIKEL_LANGNAME);
            strncpy(&d->ARTICLEUNIT[0], orderitem->ArtBase()->Einheit(), L_KSCSRVDATA_ARTICLEUNIT);
            strncpy(&d->HANDOUT[0], orderitem->ArtBase()->Darreichform(), L_KSCSRVDATA_HANDOUT);

            if( orderitem->TotalIBTQuantity() > 0 ) //if(orderitem->MengeVerbund() > 0)
            {
                d->CODEBLOCAGE[0] = 'T';
            }
            else
            {
                d->CODEBLOCAGE[0] = orderitem->ArtBase()->CodeBlocage();
            }
        }
        else
        {
            d->CODEBLOCAGE[0] = '2';
        }
        strncpy(&d->XMLLINEREFERENCE[0], orderitem->XMLLinereference(), L_KSCSRVDATA_XMLLINEREFERENCE);
        d->ORDERQTY = orderitem->MengeBestellt();
        if (orderitem->MengeBestelltNatra() > 0)
        {
            d->QTYLACK = (d->ORDERQTY +
                orderitem->MengeBestelltNatra() -
                orderitem->MengeGeliefert() -
                orderitem->TotalIBTQuantity()) - // orderitem->MengeVerbund()) -
                orderitem->MengeNachgeliefert() -
                orderitem->MengeDisponiert();
        }
        else
        {
            d->QTYLACK = (d->ORDERQTY +
                orderitem->MengeNatra() -
                orderitem->MengeGeliefert() -
                orderitem->TotalIBTQuantity()) - // orderitem->MengeVerbund()) -
                orderitem->MengeNachgeliefert() -
                orderitem->MengeDisponiert();
        }
        if(d->QTYLACK < 0) d->QTYLACK = 0;
        d->AUXQTY = orderitem->TotalIBTQuantity(); // d->AUXQTY = orderitem->MengeVerbund();
        d->RESTDELIVERYQTY = orderitem->MengeNachgeliefert();
        d->DELIVERYQTY = orderitem->MengeGeliefert();
        d->DISPOQTY = orderitem->MengeDisponiert();
        d->QTYNATRA = orderitem->MengeNatra();
        d->AUXBRANCHNO = ps->Order()->AuxFil();
        //d->AUXBRANCHNO = orderitem->VerbundFilialNr();
        if (    (orderitem->IsQStateAlternate() ||
                 orderitem->IsReimportArtikel()) )
           //&& orderitem->MengeBestaetigt() > 0 )
        {
            d->ARTICLENOORG = d->ARTICLENO;
            d->ARTICLENO = orderitem->ArtikelNr();
            nString cArtikelNo;
            cArtikelNo = d->ARTICLENO;
            cArtikelNo.Trim(7, nString::cLEADING, '0');
            nString cArtikelNoOrg;
            cArtikelNoOrg = d->ARTICLENOORG;
            cArtikelNoOrg.Trim(7, nString::cLEADING, '0');
            strncpy(&d->EANORG[0], ps->ConvertPzn2Ean(d->ARTICLENOORG, 13), L_KSCSRVDATA_EAN);
            pxArticleInfo* ArtInfo = orderitem->ArticleInfoRequest(d->ARTICLENOORG,orderitem->MengeBestaetigt());
            if (ArtInfo != NULL)
            {
                strncpy(&d->ARTICLENAMEORG[0], ArtInfo->ArtBase()->Bezeichnung(), L_KSCSRVDATA_ARTICLENAMEORG);
                strncpy(&d->ARTICLEUNITORG[0], ArtInfo->ArtBase()->Einheit(), L_KSCSRVDATA_ARTICLEUNITORG);
                strncpy(&d->HANDOUTORG[0], ArtInfo->ArtBase()->Darreichform(), L_KSCSRVDATA_HANDOUTORG);
                d->PHARMPURCHPRICEORG = ArtInfo->PreisEKApo();
                //d->CUSTPURCHPRICEORG = ArtInfo->PreisEKApoNetto();
                //if(d->CUSTPURCHPRICEORG == 0)
                d->CUSTPURCHPRICEORG = ArtInfo->PreisEKApo();
                d->PHARMSELLPRICEORG = ArtInfo->PreisVKApo();
                d->LPPR_PRICEORG = orderitem->ReimbursementPrice(d->ARTICLENOORG, '2');
                d->TFR_PRICEORG = orderitem->ReimbursementPrice(d->ARTICLENOORG, '1');
                d->TAXRATEORG = ArtInfo->SalesTaxRate();
                d->CODEBLOCAGEORG[0] = ArtInfo->CodeBlocage();
            }
        }
        else
        {
            d->ARTICLENO = orderitem->ArtikelNr();
        }

        d->LACKREASON = orderitem->GetError(&d->TEXT[0]);
        d->PREISFAKTUR = orderitem->PreisFaktur();     // Rabattierter Preis
        d->PHARMPURCHPRICE = orderitem->PreisEKApo();
        d->CUSTPURCHPRICE = orderitem->PreisEKApoNetto();
        d->PREISEKGROSSO = orderitem->PreisEKGrosso();
        d->MARGIN = orderitem->getMarginGepAep();
        d->DISCOUNTVALUEPCT = orderitem->DiscountValPctProforma();
        if(d->CUSTPURCHPRICE == 0)
            d->CUSTPURCHPRICE = orderitem->PreisEKApo();

        dLegallPrice = (double)orderitem->GetLegallBreizhPrice();
        if(dLegallPrice > 0)
        {
            d->PHARMPURCHPRICE = dLegallPrice;
            d->CUSTPURCHPRICE = dLegallPrice;
        }

        d->PHARMSELLPRICE = orderitem->getPharmacySellPrice();
        d->BASEPRICE = orderitem->BasePrice();
        LogZuschlag = orderitem->GetLogisticAddition();
        if(LogZuschlag > 0)
        {
            d->LOGISTICSADDITION = d->BASEPRICE * LogZuschlag / 100;
        }
        else
        {
            d->LOGISTICSADDITION = 0;
        }
        d->LPPR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'2');
        d->TFR_PRICE = orderitem->ReimbursementPrice(orderitem->ArtikelNr(),'1');
        cEAN = ps->ConvertPzn2Ean(orderitem->ArtikelNr(),13);
        if(!cEAN.IsEmpty())
        {
            strncpy(&d->EAN[0], cEAN, L_KSCSRVDATA_EAN);
        }
        d->QTYRESERVATION = orderitem->MengeReserviert();
        if (ps->Session()->isSwitzerland())
        {
            if(ps->Order()->Customer()->Flags().ExpiryInfo() == '1'
                    || ps->Order()->Customer()->Flags().ExpiryInfo() == '3' )
            {
                d->EXPIRYDATE = orderitem->ArticleExpireDate();
            }
            else
            {
                d->EXPIRYDATE = 0;
            }
        }
        else
        {
            d->EXPIRYDATE = orderitem->ArticleExpireDate();
        }
        d->TAXRATE = orderitem->SalesTaxRate();
        d->PROMOTYP = orderitem->PromoTyp();
        if(d->PROMOTYP == 0)    //wenn keine Target , ueberpruefen ob produktpromo
        {
            if(orderitem->IsSperreRabattManuell())
            {
                d->PROMOTYP = 2;
            }
        }
        if (ps->Session()->isBulgaria())
        {
            if(orderitem->PromotionNo() > 0)
            {
                promo.PROMOTION_NO = d->PROMONO = orderitem->PromotionNo();
                kscSel_Promotion(&promo,error_msg);
                sprintf(&d->PROMONAME[0], "%*.*s", L_PROMOTIONS_NAME, L_PROMOTIONS_NAME, &promo.NAME[0]);
            }
            else
            {
                d->PROMONO = 0;
                d->PROMONAME[0] = '\0';
            }
        }

        // orderno and position no needed for SalesWeb FR
        d->ORDERNO = orderitem->Order().KdAuftragNr();
        d->PID = orderitem->PosNr();

        ++anz;
        return 0;
    }
    else
    {
        anz = 0;
        return 1;
    }
}


/*****************************************************************************/
/* Oeffnen eines neuen Auftrages                                             */
/*****************************************************************************/
int KscsrvProformaorder(struct N_KSCSRVDATA* d, char* /*error_msg*/)
{
    nTime now;
    pxCustBase* customer;
    short AlterVZ = 0;
    nString logtext;             // ein String-Objekt
    nString cVZ;                 // ein String-Objekt
    nString cOrder;              // ein String-Objekt
    nString cTerminal;           // ein String-Objekt
    char cCustomer[8];
    d->LACKREASON = 0;
    sprintf(&cCustomer[0], "%ld", d->CUSTOMERNO);
    sprintf(cTerminal, "%4.4s", (char*)ps->Session()->Device()->Name());
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    ps->SetTransmissionType(pxOrderTransmit :: tDCT_Serial);

    if(ps->Session()->Branch()->FilialNr() != d->BRANCHNO)
    {
        pxBranch  CustBranch(ps->Session(),d->BRANCHNO);
        if (CustBranch.IsGoodState())
        {
            *(ps->Session()->Branch()) = CustBranch;
        }
        else
        {
            return -1;
        }
    }
    if (d->SWNOROUTING == 0)
    {
        AlterVZ = ps->CustomerRouting(d->CUSTOMERNO);
    }

    if (ps->Session()->isBulgaria())
    {
        if( d->REMARKS[0] != ' ' )
        {
            const int rc = pxCheckReferenceNr(ps, d->BRANCHNO, d->CUSTOMERNO, &d->REMARKS[0]);
            if (rc != 0)
            {
                AllgStrCopy(&d->TEXT[0], &d->REMARKS[0], MAX_ERROR_MSG_AE);
                d->LACKREASON = rc;
                return 6;
            }
        }
    }

    // setze Kunde
    if ( AlterVZ >0 )
    {
        cVZ = AlterVZ;
        cVZ.Trim(2, nString::cLEADING, '0');
        customer = ps->CustomerId(d->CUSTOMERNO, AlterVZ);
    }
    else
    {
        customer = ps->CustomerId(d->CUSTOMERNO);
    }
    if(customer == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        return 6;
    }

    if (ps->NewOrderProforma() == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        return 6;
    }
    if(!ps->Order()->IsGoodState())
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenOrder Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return 6;
    }
    AllgStrCopy(&d->PHARMACYNAME[0], ps->Order()->Customer()->NameApo(), L_KSCSRVDATA_PHARMACYNAME);
    d->ORDERNO = ps->Order()->KdAuftragNr();
    d->PID = testpid;
    return 0;
}

/*************************************************************************/
// KscsrvSetROParam
/*************************************************************************/
int KscsrvSetROParam(struct N_KSCSRVDATA* d, char* error_msg)
{
    char huelse[5];
    nTime now;
    nString logtext;
    sprintf(&huelse[0], "%1.1s", &d->KZROKETTE[0]);
    if(sLogLevel > 1)
    {
        char ausgabe[11];
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  SetROParam ";
        logtext += " Kette: ";
        logtext += &d->KZROKETTE[0];
        logtext += " Von: ";
        sprintf(&ausgabe[0], "%ld", d->DATUMROVON);
        logtext += &ausgabe[0];
        logtext += " Bis: ";
        sprintf(&ausgabe[0], "%ld", d->DATUMROBIS);
        logtext += &ausgabe[0];
        logdat->Write(logtext);
    }
    ps->Order()->CancelRebateOrder();
    ps->Order()->SetROChain(static_cast<short>(atoi(&huelse[0])));
    ps->Order()->SetRODateFrom(d->DATUMROVON);
    ps->Order()->SetRODateTo(d->DATUMROBIS);
    if(ps->Order()->SyncCstDiscAccVse() == 0)
    {
        AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->Order()->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:  SetROParam fehlgeschlagen ";
            logtext += ps->Order()->ErrorMsg();
            logdat->Write(logtext);
        }
        return 6;
    }
    else
    {
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:  SetROParam erfolgreich ";
            logdat->Write(logtext);
        }
        return 0;
    }
}// KscsrvSetROParam

/*****************************************************************************/
/* Aendern der Referenznummer Webshop Serbia                                 */
/*****************************************************************************/
int KscsrvChangeReference(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString text;             // ein String-Objekt
    nString logtext;
    d->LACKREASON = 0;
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    text = &d->REMARKS[0];
    text.Trim(9);
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  ReferenceNo";
        logtext += text;
        logdat->Write(logtext);
    }
    ps->Order()->SetXMLReferenceNo(text);
    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* KscsrvSetOrderInfoDetails                                                 */
/*****************************************************************************/
int KscsrvSetOrderInfoDetails(struct N_KSCSRVDATA* d, char* error_msg)
{
    nString pharmacyorderno;
    pharmacyorderno.Trim(8);
    pharmacyorderno = d->ORDERNO;
    pharmacyorderno.Trim(8);

    nString customertour;
    customertour.Trim(10);
    customertour = &d->XMLLINEREFERENCE[0];
    customertour.Trim(10);

    nString typeofdispatch;
    typeofdispatch.Trim(2);
    typeofdispatch = &d->POSTPONEREASON[0];
    typeofdispatch.Trim(2);

    const long pharmacyprocessid = d->PID;
    const long pharmacycustomerno = d->CUSTOMERNO;

    ps->NewCustOrderInfoPolymed( pharmacyorderno, pharmacycustomerno, customertour, typeofdispatch, pharmacyprocessid );
    ps->PutCustOrderInfo( ps->Order()->KdAuftragNr() );
    error_msg[0] = '\0';

    return 0;
}

/*****************************************************************************/
/* Schreiben Prolink-Eintrag fuer TI                                         */
/*****************************************************************************/
int KscsrvWriteProLink(struct N_KSCSRVDATA* d, char* error_msg)
{
    int rc;
    nTime now;
    nString text;             // ein String-Objekt
    nString datum;            // ein String-Objekt
    nString kdaufnr;          // ein String-Objekt
    nString rechnr;           // ein String-Objekt
    nString logtext;
    const long ldatumact = now.GetYear()*10000 + now.GetMonth()*100 + now.GetDay();
    d->LACKREASON = 0;
    KscsrvConvUmlaut(&d->REMARKS[0], L_KSCSRVDATA_REMARKS);
    text = &d->REMARKS[0];
    text.Trim(15);
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  SetProlink";
        logtext += " TO Datum:";
        sprintf(datum,"%ld",d->TOURDATE);
        logtext += datum;
        logtext += " AufNr:";
        sprintf(kdaufnr,"%ld",d->ORDERNOORIGIN);
        logtext += kdaufnr;
        logtext += " RechNr:";
        logtext += text;
        logdat->Write(logtext);
    }
    ps->Order()->WriteProLink(d->TOURDATE,text,d->ORDERNOORIGIN);
    if(ldatumact > d->TOURDATE)
    {
        prolinkS pro;
        prolinkS* old;
        old = &pro;
        pro.DATUM = d->TOURDATE;
        pro.DATEPROFORMA = d->TOURDATE;
        pro.KDAUFTRAGNR = d->ORDERNOORIGIN;
        pro.KDAUFTRAGNRPRO = d->ORDERNOORIGIN;
        strcpy(&pro.INVOICENUMBERPRO[0], text);
        strcpy(&pro.INVOICENUMBER[0], " ");
        rc = kscProlink_Insert(old, error_msg);
    }
    else
    {
        prolinkactS proact;
        prolinkactS* act;
        act = &proact;
        proact.DATEPROFORMA = d->TOURDATE;
        proact.KDAUFTRAGNR = d->ORDERNOORIGIN;
        proact.KDAUFTRAGNRPRO = d->ORDERNOORIGIN;
        strcpy(&proact.INVOICENUMBERPRO[0], text);
        strcpy(&proact.INVOICENUMBER[0], " ");
        rc = kscProlinkact_Insert(act, error_msg);
    }
    if (rc < 0)
        return rc;

    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* Anfordern der Artikelbestands unter Beruecksichtigung der Kundenbedingungen */
/*****************************************************************************/
int KscsrvGetArticleStock(struct N_KSCSRVDATA* d, char* error_msg)
{
    artcodesS codes;
    nTime now;
    nString cArtikel;
    nString cEAN;
    nString logtext;
    pxOrderItem* orderitem;
    pxCountryCodes* CC = NULL;
    d->LACKREASON = 0;
    sprintf(&codes.ARTICLE_CODE[0], "%*.*s", L_ARTCODES_ARTICLE_CODE, L_ARTCODES_ARTICLE_CODE, &d->ARTICLE_CODE[0]);
    kscartSel_NoByCode(&codes, error_msg);
    d->ARTICLENO = codes.ARTICLENO;
    cArtikel = d->ARTICLENO;
    cArtikel.Trim(7,nString::cLEADING,'0');
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  ArticleInfo ";
        logtext += " ARTICLE_CODE: ";
        logtext += &codes.ARTICLE_CODE[0];
        logdat->Write(logtext);
    }

    orderitem = ps->NewOrderItemInfo(d->ARTICLENO, d->ORDERQTY);

    AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
    AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
    d->LACKREASON = ps->Order()->ErrorNumber();

    if (orderitem == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      ArticleInfo Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
        }
        return 6;
    }

    if(sLogLevel > 2)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out: ArticleInfo ";
    }
    if(orderitem->ArtBase() != NULL && orderitem->ArtBase()->IsGoodState())
    {
        short TextKey = 0;
        pxArticleText* ptext = NULL;
        TextKey = orderitem->ArtBase()->TextKey();
        if(TextKey > 0)
        {
            ptext = new pxArticleText(ps->Session(), TextKey);
            if ( !ptext->Get(cDBGET_READONLY))
            {
                strncpy(&d->ARTICLETEXT[0], ptext->Text(), L_KSCSRVDATA_ARTICLETEXT);
            }
            delete ptext;
        }
        strncpy(&d->ARTICLENAME[0], orderitem->ArtBase()->Bezeichnung(), L_KSCSRVDATA_ARTICLENAME);
        strncpy(&d->ARTICLEUNIT[0], orderitem->ArtBase()->Einheit(), L_KSCSRVDATA_ARTICLEUNIT);
        strncpy(&d->HANDOUT[0], orderitem->ArtBase()->Darreichform(), L_KSCSRVDATA_HANDOUT);
        if(ps->Order()->Customer()->PreWholeTyp() == '1')
        {
            d->CODEBLOCAGE[0] = orderitem->ArtBase()->CodeBlocage();
            if (d->CODEBLOCAGE[0] != 'P')
            {
                d->CODEBLOCAGE[0] = '0';
            }
        }
        else
        {
            d->CODEBLOCAGE[0] = orderitem->ArtBase()->CodeBlocage();
        }
        if(sLogLevel > 2)
        {
            logtext += " Name: ";
            logtext += &d->ARTICLENAME[0];
            logtext += " Unit: ";
            logtext += &d->ARTICLEUNIT[0];
            logtext += " Handout: ";
            logtext += &d->HANDOUT[0];
            logtext += " CodeBlocage: ";
            logtext += &d->CODEBLOCAGE[0];
        }
    }
    else
    {
        d->CODEBLOCAGE[0] = '2';
        if(sLogLevel > 2)
        {
            logtext += " CodeBlocage: ";
            logtext += &d->CODEBLOCAGE[0];
        }
    }
    if(sLogLevel > 2)
    {
        logdat->Write(logtext);
        logtext = now.AsString("%H:%M:%S");
        logtext += "                  ";
    }
    if ( ps->Order()->Customer()->IsNoInfoLevel()  ||
         ps->Order()->Customer()->IsInfoLevelLow() ||
         d->ORDERQTY == 0 )
    {
        d->AVAILABLE[0] = (orderitem->MengeGeliefert() > 0) ? '1' : '0';
        if(sLogLevel > 2)
        {
            logtext += "AVAILABLE ";
            logtext += &d->AVAILABLE[0];
        }
    }
    else
    {
        if(orderitem->MengeGeliefert() == 0) d->LACKREASON = orderitem->GetError(&d->TEXT[0]);
        if(orderitem->MengeGeliefert() > d->ORDERQTY ) orderitem->MengeGeliefert(d->ORDERQTY);
        d->QTYLACK = (d->ORDERQTY -
                      orderitem->MengeGeliefert() -
                      orderitem->MengeMoeglich()) -
                      orderitem->MengeNachgeliefert() -
                      orderitem->MengeDisponiert();
        if(d->QTYLACK < 0) d->QTYLACK = 0;
        d->AUXQTY = orderitem->MengeMoeglich();
        d->RESTDELIVERYQTY = orderitem->MengeNachgeliefert();
        if ( d->RESTDELIVERYQTY == 0 )
        {
            if (orderitem->IsRestDeliveryPossible())
            {
                d->RESTDELIVERYQTY = d->QTYLACK;
                d->QTYLACK = 0;
            }
        }
        d->DELIVERYQTY = orderitem->MengeGeliefert();
        d->DISPOQTY = orderitem->MengeDisponiert();
        d->QTYNATRA = orderitem->MengeNatra();
        d->AUXBRANCHNO = ps->Order()->AuxFil();
        if(sLogLevel > 2)
        {
            nString cQTY;
            nString cQTYLack;
            nString cAUXQTY;
            nString cAUXBRANCHNO;
            nString cRESTQTY;
            nString cDISPOQTY;
            nString cQTYNATRA;
            cQTY = d->DELIVERYQTY;
            cQTY.Trim(5,nString::cLEADING,'0');
            cQTYLack = d->QTYLACK;
            cQTYLack.Trim(5,nString::cLEADING,'0');
            cAUXQTY = d->AUXQTY;
            cAUXQTY.Trim(5,nString::cLEADING,'0');
            cRESTQTY = d->RESTDELIVERYQTY;
            cRESTQTY.Trim(5,nString::cLEADING,'0');
            cDISPOQTY = d->DISPOQTY;
            cDISPOQTY.Trim(5,nString::cLEADING,'0');
            cQTYNATRA = d->QTYNATRA;
            cQTYNATRA.Trim(5,nString::cLEADING,'0');
            cAUXBRANCHNO = d->AUXBRANCHNO;
            cAUXBRANCHNO.Trim(2,nString::cLEADING,'0');
            logtext = now.AsString("%H:%M:%S");
            logtext += "               delivery Qty: ";
            logtext += cQTY;
            logtext += " lack Qty: ";
            logtext += cQTYLack;
            logtext += " rest Qty: ";
            logtext += cRESTQTY;
            logtext += " dispo Qty: ";
            logtext += cDISPOQTY;
            logtext += " Natra Qty: ";
            logtext += cQTYNATRA;
            logtext += " aux Qty: ";
            logtext += cAUXQTY;
            logtext += " Branch: ";
            logtext += cAUXBRANCHNO;
            logdat->Write(logtext);
        }
    }
    if(sLogLevel > 2)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += "                  ";
    }
    if (ps->Session()->isSwitzerland())
    {
        if (   ps->Order()->Customer()->Flags().ExpiryInfo() == '1'
            || ps->Order()->Customer()->Flags().ExpiryInfo() == '3' )
        {
            d->EXPIRYDATE = orderitem->ArticleExpireDate();
        }
        else
        {
            d->EXPIRYDATE = 0;
        }
    }
    else
    {
        d->EXPIRYDATE = orderitem->ArticleExpireDate();
    }
    d->TAXRATE = orderitem->SalesTaxRate();
    d->LACKREASON = orderitem->GetError(&d->TEXT[0]);
    if (ps->Session()->isFrance() || ps->Session()->isFrancePrewhole())
    {
        CC = ps->CountryCodesInfo(ps->Order()->FilialNr(), &d->CODEBLOCAGE[0]);
        if(CC != NULL)
        {
            strncpy(&d->SERACODE[0], CC->SeraCode(), L_KSCSRVDATA_SERACODE);
            strncpy(&d->XMLCODE[0], CC->XMLCode(), L_KSCSRVDATA_XMLCODE);
            strncpy(&d->XMLTEXT[0], CC->XMLText(), L_KSCSRVDATA_XMLTEXT);
            delete CC;
        }
    }
    else if (ps->Session()->Country() == "AU" || ps->Session()->isGermany())
    {
        nString xmlcode;             // ein String-Objekt
        xmlcode = d->LACKREASON/100;
        xmlcode.Trim(L_KSCSRVDATA_XMLCODE, nString::cLEADING, '0');
        strncpy(&d->XMLCODE[0], xmlcode, L_KSCSRVDATA_XMLCODE);
        if(d->LACKREASON != 0)
        {
            CC = ps->CountryCodesInfo(ps->Order()->FilialNr(), &d->XMLCODE[0], static_cast<short>(pxCountryCodes::CCT_XMLCODE));
            if(CC != NULL)
            {
                strncpy(&d->SERACODE[0], CC->SeraCode(), L_KSCSRVDATA_SERACODE);
                strncpy(&d->XMLTEXT[0], CC->XMLText(), L_KSCSRVDATA_XMLTEXT);
                strncpy(&d->LACKREASONCTYCODE[0], CC->InfoCode(), L_KSCSRVDATA_LACKREASONCTYCODE);
                delete CC;
            }
        }
    }

    pxSupplDeliveryInfo deliveryInfo(ps, orderitem->ArtikelNr());
    deliveryInfo.Get();
    if (deliveryInfo.IsGoodState())
    {
        d->PREDICTEDAVAILABILITYDATE = deliveryInfo.PredictedAvailDate().getDate();
    }
    strncpy(&d->LACKREASONLIST[0], orderitem->GetLackReasonList().c_str(), L_KSCSRVDATA_LACKREASONLIST);
    return 0;
}

/*****************************************************************************/
/* Schliessen eines Auftrages bei Kreditlimitueberschreitung      */
/*****************************************************************************/
int KscsrvCloseorderDebtLimit(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nDate today;
    nString logtext;             // ein String-Objekt
    char cWertLieferung[11];
    nString cAnzPos;
    nString cOrder;
    nString cTour;
    nString cDeliveryBranch;
    nString cAnzAlphaText;  //nase von ohne bestand auf alpha, bitte prüfen
    nString cAnzPosDafueFehler;
    char cDatumAuslieferung[11];
    const basar::Int16 branchNo = ps->Order()->Customer()->Vertriebszentrum();
    const basar::Int32 orderNo = ps->Order()->KdAuftragNr();
    nString reason = &d->TEXT[0];
    nString comment = &d->ARTICLETEXT[0];
    nString user = &d->REMARKS[0];
    nString guid = &d->XMLTEXT[0];
    nString url = &d->XMLTEXTORG[0];
    ps->Order()->ClearError();
    ps->Order()->ClearProblemClearance();

    ps->Order()->SetReleaseInfos(reason, comment, user, Order::CLOSE, guid, url);
    if(ps->Order()->IsCremaReleased())
    {
        ps->Order()->SetNoDebtLimitCheck();
        d->LACKREASON = 0;
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  CloseOrderKL";
            logdat->Write(logtext);
        }
        if(ps->Order()->DatumAuslieferung() <= today)   //Tour ist bei verzögerter Auslieferung bereits korrekt SR-16030276
        {
            ps->Order()->SetNextValidRouteNormal((nString)"000000"); //immer nächste gültige Tour
        }

        transferOrderDeliveryInformation(d);
        d->ORDERNO = ps->Order()->KdAuftragNr();
        cOrder = d->ORDERNO;
        cOrder.Trim(6, nString::cLEADING, '0');
        cTour += ps->Order()->TourId();
        nString bem;

        ps->Order()->Close(Order::EntryClosed, Order::cClose_UnConditional);
        if ( ! (ps->Order()->IsGoodState()) )
        {
            AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
            AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
            d->LACKREASON = ps->ErrorNumber();
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      CloseOrderKL Error ";
                logtext += ps->ErrorMsg();
                logdat->Write(logtext);
                logdat->End();
                logdat->CloseSeralog();
            }
            return 6;
        }
        else
        {
            ps->Order()->DeleteCremaMail(orderNo, branchNo);
        }
        sprintf(&cWertLieferung[0], "%10.2f", d->VALUEOFORDER);
        cAnzPos = d->LINESOFORDER;
        cAnzPos.Trim(6, nString::cLEADING, '0');
        cAnzAlphaText = d->TEXTLINES;
        cAnzAlphaText.Trim(6, nString::cLEADING, '0');
        cAnzPosDafueFehler = d->LACKLINES;
        cAnzPosDafueFehler.Trim(6, nString::cLEADING, '0');
        sprintf(&cDatumAuslieferung[0], "%02ld.%02ld.%04ld",
                d->TOURDATE%100,
                d->TOURDATE/100%100,
                d->TOURDATE/10000);
        cDeliveryBranch = d->DELIVERYBRANCHNO;
        cDeliveryBranch.Trim(2, nString::cLEADING, '0');
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out: CloseOrderKL Order: ";
            logtext += cOrder;
            logtext += " Tour: ";
            logtext += cTour;
            logtext += " Lieferdatum: ";
            logtext += &cDatumAuslieferung[0];
            logtext += " Value of Order: ";
            logtext += &cWertLieferung[0];
            logtext += " Lines of Order: ";
            logtext += cAnzPos;
            logtext += " Textlines of Order: ";
            logtext += cAnzAlphaText;
            logtext += " Lacklines of Order: ";
            logtext += cAnzPosDafueFehler;
            logtext += " Value of Order: ";
            logtext += &cWertLieferung[0];
            logtext += " from Branchno: ";
            logtext += cDeliveryBranch;
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
    }
    else//No error, but fill data for application above
    {
        // Werte merken, die nach erfolgreichem Zurückstellen wieder gesetzt werden ...
        ps->Order()->RevertCancelDebtLimitSumDayTurnOver();
        const short approvalsNeeded = static_cast<short>(ps->Order()->ApprovalsNeeded());
        const int lackreason = ps->Order()->ErrorNumber();
        nString msg = ps->Order()->ErrorString();

        ps->Order()->ClearError();

        // Auftrag darf nicht in IE stehen bleiben, sondern muss wieder zurückgestellt werden (DF) !!!
        ps->Order()->SetProblemClearance();
        ps->Order()->SetEventCode(pxEventReason::CremaVotingInProcess);
        ps->Order()->Close( Order::EntryDeferred );

        if (d->LACKREASON == 0)
        {
            d->APPROVALPERSONSNEEDED = approvalsNeeded;
            d->LACKREASON = lackreason;
            AllgStrCopy(&d->TEXT[0], msg, MAX_ERROR_MSG_AE);
        }
    }
    return 0;
}

/*****************************************************************************/
/* Stornieren eines Auftrages bei Kreditlimitueberschreitung                 */
/*****************************************************************************/
int KscsrvCancelorderDebtLimit(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    const basar::Int16 branchNo = ps->Order()->Customer()->Vertriebszentrum();
    const basar::Int32 orderNo = ps->Order()->KdAuftragNr();

    nString reason = &d->TEXT[0];
    nString comment = &d->ARTICLETEXT[0];
    nString user = &d->REMARKS[0];
    nString guid = &d->XMLTEXT[0];
    nString url = &d->XMLTEXTORG[0];

    ps->Order()->ClearError();
    ps->Order()->ClearProblemClearance();

    ps->Order()->SetReleaseInfos(reason, comment, user, Order::CANCEL, guid, url);

    if (ps->Order()->IsCremaReleased())
    {
        ps->Order()->SetNoDebtLimitCheck();
        d->LACKREASON = 0;
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " In:  CancelOrderKL ";
            logdat->Write(logtext);
        }
        if(ps->CancelTransmission() != 0)
        //if(ps->Order()->Cancel(pxDVC_UNDEFINED,pxOrder::cCancel_UnConditional) != 0)
        {
            AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
            AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
            d->LACKREASON = ps->ErrorNumber();
            if(sLogLevel > 1)
            {
                logtext = now.AsString("%H:%M:%S");
                logtext += "      CancelOrderKL Error ";
                logtext += ps->ErrorMsg();
                logdat->Write(logtext);
                logdat->End();
                logdat->CloseSeralog();
            }
            logdat->End();
            logdat->CloseSeralog();
            return 6;
        }
        else
        {
            ps->Order()->DeleteCremaMail(orderNo, branchNo);
        }
        logdat->End();
        logdat->CloseSeralog();
    }
    else//No error, but fill data for application above
    {
        // Werte merken, die nach erfolgreichem Zurückstellen wieder gesetzt werden ...
        ps->Order()->RevertCancelDebtLimitSumDayTurnOver();
        const short approvalsNeeded = static_cast<short>(ps->Order()->ApprovalsNeeded());
        const int lackreason = ps->Order()->ErrorNumber();
        nString msg = ps->Order()->ErrorString();

        ps->Order()->ClearError();

        // Auftrag darf nicht in IE stehen bleiben, sondern muss wieder zurückgestellt werden (DF) !!!
        ps->Order()->SetProblemClearance();
        ps->Order()->SetEventCode(pxEventReason::CremaVotingInProcess );
        ps->Order()->Close( Order::EntryDeferred );

        if (d->LACKREASON == 0)
        {
            d->APPROVALPERSONSNEEDED = approvalsNeeded;
            d->LACKREASON = lackreason;
            AllgStrCopy(&d->TEXT[0], msg, MAX_ERROR_MSG_AE);
        }
    }
    logdat->End();
    logdat->CloseSeralog();
    return 0;
}

/*****************************************************************************/
/* Oeffnen eines neuen Auftrages MSV3                                        */
/*****************************************************************************/
int KscsrvNeworderMSV3(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    pxCustBase* customer;
    short AlterVZ = 0;
    nString logtext;
    nString cVZ;
    nString cOrder;
    nString cTerminal;
    nString cPid;
    int iPicking,iBooking;
    char huelse[8];
    char cCustomer[8];
    d->LACKREASON = 0;
    if(ps->Session()->Branch()->FilialNr() != d->BRANCHNO)
    {
        pxBranch  CustBranch(ps->Session(), d->BRANCHNO);
        if (CustBranch.IsGoodState())
        {
            *(ps->Session()->Branch()) = CustBranch;
        }
        else
        {
            return -1;
        }
    }
    locklevelparam = ps->GetLockLevelParam();
    if(locklevelparam == NULL)
        sLogLevel = 1;
    else
        sLogLevel = locklevelparam->Wert();
    sprintf(&cCustomer[0], "%ld", d->CUSTOMERNO);
    sprintf(cTerminal, "%4.4s", (char*)ps->Session()->Device()->Name());
    if(sLogLevel > 0)
    {
        if(sLogLevel == 1) sLogLevel = 2;
        logdat->Start();
        logdat->SetIDFNr(&cCustomer[0]);
        logdat->SetTerminalID((char*)cTerminal);
        logdat->Open();
        logdat->WriteList();
        cVZ = ps->Session()->Branch()->FilialNr();
        cVZ.Trim(2,nString::cLEADING,'0');
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  OpenOrder Branchno: " + cVZ + " Customer: " + &cCustomer[0];
        sprintf(cPid,"%05d", testpid);
        logtext += " PID=";
        logtext += cPid;
        logdat->Write(logtext);
    }
    ps->SetTransmissionType(pxOrderTransmit::tDCT_Serial);

    if (d->SWNOROUTING == 0)
    {
        AlterVZ = ps->CustomerRouting(d->CUSTOMERNO);
    }

    // setze Kunde
    if (AlterVZ > 0)
    {
        cVZ = AlterVZ;
        cVZ.Trim(2, nString::cLEADING, '0');
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      routed Branchno: " + cVZ;
            logdat->Write(logtext);
        }
        customer = ps->CustomerId(d->CUSTOMERNO, AlterVZ);
    }
    else
    {
        customer = ps->CustomerId(d->CUSTOMERNO);
    }
    if(customer == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenOrder Error no customer";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return 6;
    }

    sprintf(&huelse[0], "%1.1s", &d->SHIPMENTTYPE[0]);
    iPicking = atoi(&huelse[0]);
    sprintf(&huelse[0], "%1.1s", &d->BOOKINGTYPE[0]);
    iBooking = atoi(&huelse[0]);

    if (ps->OrderTypeMSV3(&d->KINDOFORDER[0], &d->ORDERLABEL[0], iPicking, iBooking) == NULL)
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenOrder Error MSV3";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return 6;
    }
    if(!ps->Order()->IsGoodState())
    {
        AllgStrCopy(&d->TEXT[0], ps->Order()->ErrorMsg(), MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->Order()->ErrorNumber();
        if(sLogLevel > 0)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      OpenOrder Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            if(d->LACKREASON != CMSG_ORD_ROUTE_NOMORE)
            {
                logdat->End();
                logdat->CloseSeralog();
                return 6;
            }
        }
        AllgStrCopy(&d->PHARMACYNAME[0], ps->Order()->Customer()->NameApo(), L_KSCSRVDATA_PHARMACYNAME);
        d->ORDERNO = ps->Order()->KdAuftragNr();
        if(sLogLevel > 0)
        {
            cOrder = d->ORDERNO;
            cOrder.Trim(6,nString::cLEADING,'0');
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out: OpenOrder Customer: ";
            logtext += &d->PHARMACYNAME[0];
            logtext += " OrderNo: ";
            logtext += cOrder;
            logdat->Write(logtext);
        }
        return 6;
    }
    AllgStrCopy(&d->PHARMACYNAME[0], ps->Order()->Customer()->NameApo(), L_KSCSRVDATA_PHARMACYNAME);
    d->ORDERNO = ps->Order()->KdAuftragNr();
    AllgStrCopy(&d->ORDERLABEL[0], ps->Order()->OrderLabel(), L_KSCSRVDATA_ORDERLABEL);
    d->PID = testpid;
    if(sLogLevel > 0)
    {
        cOrder = d->ORDERNO;
        cOrder.Trim(6,nString::cLEADING,'0');
        logtext = now.AsString("%H:%M:%S");
        logtext += " Out: OpenOrder Customer: ";
        logtext += &d->PHARMACYNAME[0];
        logtext += " OrderNo: ";
        logtext += cOrder;
        logdat->Write(logtext);
    }

    initLog4Cplus();
    return 0;
}

/*****************************************************************************/
/* Setzen Valutadatum                                                        */
/*****************************************************************************/
int KscsrvSetValueDate(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    nString cValueDate;
    nString cBatchschreiben;
    nString cBranchnoorg;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:   SetValueDate ";
        cValueDate = d->VALUTADATUM;
        cValueDate.Trim(8,nString::cLEADING,'0');
        logtext += cValueDate;
        logtext += " Batchschreiben: ";
        cBatchschreiben = d->BATCHSCHREIBEN;
        cBatchschreiben.Trim(2,nString::cLEADING,'0');
        logtext += cBatchschreiben;
        logtext += " BranchnoOrg: ";
        cBranchnoorg = d->BRANCHNOORIGIN;
        cBranchnoorg.Trim(2,nString::cLEADING,'0');
        logtext += cBranchnoorg;
        logdat->Write(logtext);
    }
    nDate datum(d->VALUTADATUM);
    ps->Order()->BatchSchreiben(static_cast<OriginTypeEnum>(d->BATCHSCHREIBEN));
    ps->Order()->HerkunftFiliale(d->BRANCHNOORIGIN);


    if(static_cast<nTime>(datum) <= now)
    {
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:   ValueDate not set < Actdate";
            logdat->Write(logtext);
        }
        error_msg[0] = '\0';
        return 0;
    }
    if ( d->BATCHSCHREIBEN == cORTYPE_TRANSFER ||
            d->BATCHSCHREIBEN == cORTYPE_BATCH_TRANSFER)
    {
        const short mAuto = ps->Order()->OrderType().ValMonthsAuto();
        if (d->VALUTADATUM > 0 )
        {
            datum.AddMonth(mAuto);
            ps->Order()->ValDate(datum);
            ps->Order()->SetDatumValutaBatch(ps->Order()->DatumValuta());
        }
        else
        {
            if (mAuto > 0)
            {
                ps->Order()->ValDateMonAuto(mAuto);
            }
        }
    }
    if(ps->Order()->DatumValuta() == pxConstants::NullDate)
    {
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:   ValueDate not set";
            logdat->Write(logtext);
        }
    }
    else
    {
        //ps->Order()->SetDatumValutaBatch(datum);
        if (ps->Session()->isBulgaria())
        {
            ps->Order()->SetOrderWithTimeForPayment();
            if ( ! (ps->Order()->IsGoodState()) )
            {
                if(sLogLevel > 1)
                {
                    logtext = now.AsString("%H:%M:%S");
                    logtext += " Out:   ValueDate not set: KL";
                    logdat->Write(logtext);
                }
                error_msg[0] = '\0';
                return 0;
            }
        }
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += " Out:   ValueDate set correctly";
            logdat->Write(logtext);
        }
    }
    error_msg[0] = '\0';

    return 0;
}

/*****************************************************************************/
/* Setzen Herkunft                                                           */
/*****************************************************************************/
int KscsrvSetTurnOverOrigin(struct N_KSCSRVDATA* /*d*/, char* error_msg)
{
    nTime now;
    nString logtext;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:   SetTurnOverOrigin ";
        logdat->Write(logtext);
    }
    ps->Order()->SetTurnOverOrigin();
    error_msg[0] = '\0';

    return 0;
}

/*****************************************************************************/
/* Abrufer der Approval Daten für einen Auftrag                              */
/*****************************************************************************/
int KscsrvGetApprovalData(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString logtext;
    short ApprovalMax=0;
    short ApprovalCancel = 0;
    short ApprovalClose = 0;

    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  GetAppprovalData";
        logdat->Write(logtext);
    }

    ps->Order()->GetReleaseApprovalValues(d->ORDERNO, d->BRANCHNO, ApprovalMax, ApprovalCancel, ApprovalClose);

    if ( ! (ps->Order()->IsGoodState()) )
    {
        AllgStrCopy(&d->TEXT[0], ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        AllgStrCopy(error_msg, &d->TEXT[0], MAX_ERROR_MSG_AE);
        d->LACKREASON = ps->ErrorNumber();
        if(sLogLevel > 1)
        {
            logtext = now.AsString("%H:%M:%S");
            logtext += "      GetAppprovalData Error ";
            logtext += ps->ErrorMsg();
            logdat->Write(logtext);
            logdat->End();
            logdat->CloseSeralog();
        }
        return 6;
    }

    d->APPROVALCANCEL = ApprovalCancel;
    d->APPROVALCLOSE = ApprovalClose;
    d->APPROVALPERSONSNEEDED = ApprovalMax;

    if(sLogLevel > 1)
    {
        std::stringstream ss;
        ss << now.AsString("%H:%M:%S");
        ss << " Out: GetAppprovalData ApprovalMax: ";
        ss << ApprovalMax;
        ss << " ApprovalCancel: ";
        ss << ApprovalCancel;
        ss << " ApprovalClose: ";
        ss << ApprovalClose;
                logtext = ss.str().c_str();
        logdat->Write(logtext);
        logdat->End();
        logdat->CloseSeralog();
    }
    return 0;
}

/*****************************************************************************/
/* Konvertieren Umlaute                                                      */
/*****************************************************************************/
int KscsrvConvUmlaut(char* d, int maxlen)
{
    int rc = 0;
    if (ps->Session()->isBulgaria())
    {
        return rc;
    }
    char buf[2048];
    AllgEntfSpaces( d );
    //int len = strlen( d );
    int i = 0;
    int y = 0;
    for( ; y < maxlen; i++) //Umwandlug Umlaute
    {
        if(d[i] == 'Ä')
        {
            buf[y] = 'A';
            if(y++ < maxlen) buf[y] = 'E';
            rc++;
        }
        else if(d[i] == 'Ö')
        {
            buf[y] = 'O';
            if(y++ < maxlen) buf[y] = 'E';
            rc++;
        }
        else if(d[i] == 'Ü')
        {
            buf[y] = 'U';
            if(y++ < maxlen) buf[y] = 'E';
            rc++;
        }
        else if(d[i] == 'ä')
        {
            buf[y] = 'a';
            if(y++ < maxlen) buf[y] = 'e';
            rc++;
        }
        else if(d[i] == 'ö')
        {
            buf[y] = 'o';
            if(y++ < maxlen) buf[y] = 'e';
            rc++;
        }
        else if(d[i] == 'ü')
        {
            buf[y] = 'u';
            if(y++ < maxlen) buf[y] = 'e';
            rc++;
        }
        else if(d[i] == 'ß')
        {
            buf[y] = 's';
            if(y++ < maxlen) buf[y] = 's';
            rc++;
        }
        else buf[y] = d[i];
        y++;
    }
    buf[y] = '\0';
    strcpy(d, &buf[0]);
    return rc;
}


void initLog4Cplus()
{
    basar::Int16 branchno = 0;
    basar::Int32 orderno = 0;
    basar::Int32 customerno = 0;

    if( NULL != ps->Order() )
    {
        branchno = ps->Order()->Customer()->Vertriebszentrum();
        orderno = ps->Order()->KdAuftragNr();
        customerno = ps->Order()->Customer()->KundenNr();
    }

    libcsc::LoggerConfig config( "kscserver" );
    config.doConfigure( branchno, orderno, customerno );
}


/*****************************************************************************/
/* versorgen Tourinformationen in Übergabestruktur                           */
/*****************************************************************************/
void transferDeliveryInformation(struct N_KSCSRVDATA* d, pxOrderItem* orderitem, bool isAvailabilityRequest /*= false*/)
{
    d->TIMEDELIVERY     = 0;
    d->TOURDATE         = 0;
    d->DELIVERYDATE     = 0;
    d->KARENZZEIT       = 0;
    d->DELIVERYTIMEIBT  = 0;
    d->TOURDATEIBT      = 0;
    d->DELIVERYDATEIBT  = 0;
    d->IBTTYPE          = 0;
    d->KARENZZEITIBT    = 0;

    if (orderitem->ArtBase() != NULL && orderitem->ArtBase()->IsGoodState())
    {
        const TourInfo* ti = orderitem->getItemTourInformation();
        if (ti->getTourFound())
        {
            d->TIMEDELIVERY = orderitem->getItemDeliveryTime(*d->TOURID);
            d->DELIVERYDATE = orderitem->getItemDeliveryDate();
            d->TOURDATE = orderitem->getItemTourDate();
            d->KARENZZEIT = orderitem->getItemDeliveryTimeBuffer();
            AllgStrCopy(&d->TOURID[0], orderitem->TourId(), L_KSCSRVDATA_TOURID);
        }
    }
    if (isAvailabilityRequest)
    {
        if (orderitem->TotalIBTQuantity() > 0 || orderitem->MengeMoeglich() > 0)
        {
            d->DELIVERYTIMEIBT = orderitem->getItemDeliveryTime(*d->TOURIDIBT, true);
            d->TOURDATEIBT = orderitem->getItemTourDate(true);
            d->DELIVERYDATEIBT = orderitem->getItemDeliveryDate(true);
            d->IBTTYPE = orderitem->IBTType();
            if (orderitem->IsDayIBT())
            {
                d->IBTTYPE = 4;
            }
            d->KARENZZEITIBT = orderitem->getItemDeliveryTimeBuffer(true);
            AllgStrCopy(&d->TOURIDIBT[0], orderitem->TourIdIBT(), L_KSCSRVDATA_TOURIDIBT);
        }
    }
    else
    {
        if (orderitem->TotalIBTQuantity() > 0) //if(orderitem->MengeVerbund() > 0)
        {
            d->DELIVERYTIMEIBT = orderitem->getItemDeliveryTime(*d->TOURIDIBT, true);
            d->TOURDATEIBT = orderitem->getItemTourDate(true);
            d->DELIVERYDATEIBT = orderitem->getItemDeliveryDate(true);
            d->IBTTYPE = orderitem->IBTType();
            if (orderitem->IsDayIBT())
            {
                d->IBTTYPE = 4;
            }
            d->KARENZZEITIBT = orderitem->getItemDeliveryTimeBuffer(true);
            AllgStrCopy(&d->TOURIDIBT[0], orderitem->TourIdIBT(), L_KSCSRVDATA_TOURIDIBT);
        }
    }
}

/*****************************************************************************/
/* versorgen Tourinformationen in Übergabestruktur auf Orderebene            */
/*****************************************************************************/
void transferOrderDeliveryInformation(struct N_KSCSRVDATA* d)
{
    d->TOURDATE             = 0;
    d->DELIVERYDATE         = 0;
    d->TIMEDELIVERY         = 0;
    d->KARENZZEIT           = 0;
    d->ACTTOURCLOSINGDATE   = 0;
    d->ACTTOURCLOSINGTIME   = 0;
    d->NEXTTOURCLOSINGDATE  = 0;
    d->NEXTTOURCLOSINGTIME  = 0;
    d->NEXTTOURDELIVERYDATE = 0;
    d->NEXTTOURDELIVERYTIME = 0;

    nDate closingDateTime;
    nDate deliveryDateTime;

    TourInfo* currentTourInfo = ps->Order()->getTourInformation();
    if (currentTourInfo->getTourFound())
    {
        AllgStrCopy(&d->TOURID[0], currentTourInfo->getTourID(), L_KSCSRVDATA_TOURID);
        closingDateTime = currentTourInfo->getTourClosingDateTime();
        deliveryDateTime = currentTourInfo->getCustomerDeliveryDateTimeMin();

        d->TOURDATE         = currentTourInfo->getTourDate().GetYYYYMMDD();
        d->DELIVERYDATE     = deliveryDateTime.GetYYYYMMDD();
        d->TIMEDELIVERY     = deliveryDateTime.GetHours() * 100 + deliveryDateTime.GetMinutes();
        d->KARENZZEIT       = currentTourInfo->getDeliveryTimeBuffer();

        d->ACTTOURCLOSINGDATE   = closingDateTime.GetYYYYMMDD();
        d->ACTTOURCLOSINGTIME   = closingDateTime.GetHours() * 100 + closingDateTime.GetMinutes();

    }

    TourInfo followingTourInfo = ps->Order()->getTourAssignmentUtil()->getTourManager()->determineFollowingTour( currentTourInfo );
    if (followingTourInfo.getTourFound())
    {
        closingDateTime = followingTourInfo.getTourClosingDateTime();
        deliveryDateTime = followingTourInfo.getCustomerDeliveryDateTimeMin();

        d->NEXTTOURCLOSINGDATE  = closingDateTime.GetYYYYMMDD();
        d->NEXTTOURCLOSINGTIME  = closingDateTime.GetHours() * 100 + closingDateTime.GetMinutes();
        d->NEXTTOURDELIVERYDATE = deliveryDateTime.GetYYYYMMDD();
        d->NEXTTOURDELIVERYTIME = deliveryDateTime.GetHours() * 100 + deliveryDateTime.GetMinutes();
    }

}

/*****************************************************************************/
/* get internal articleno                                                    */
/*****************************************************************************/
long getArticleNoFromCode(struct N_KSCSRVDATA *d, char *error_msg) // DONESH: getArticleNoFromCode - Neue Methode zur Ermittlung der internen PZN
{
    long retval = 0;
    bool articlenofound = false;

    artcodesS codes;
    memset(&codes.ARTICLE_CODE[0], ' ', L_ARTCODES_ARTICLE_CODE);
    codes.CODE_TYPE = 0;

    if( d->ARTICLE_CODE[0] != ' ' )
    {
        sprintf(&codes.ARTICLE_CODE[0], "%*.*s", L_ARTCODES_ARTICLE_CODE, L_ARTCODES_ARTICLE_CODE, &d->ARTICLE_CODE[0]);
        kscartSel_NoByCode(&codes, error_msg);
        if(codes.ARTICLENO == 0)
        {
            if(strlen(&codes.ARTICLE_CODE[0]) > 7)
            {
                codes.ARTICLENO = 9999999;
            }
            else
            {
                codes.ARTICLENO = atol(&codes.ARTICLE_CODE[0]);
                retval = codes.ARTICLENO;
                articlenofound = true;
            }
        }
        else
        {
            retval = codes.ARTICLENO;
            articlenofound = true;
        }
    }

    if(!articlenofound)
    {
        nString cArtikel(ps->ConvertEan2Pzn(&d->EAN[0]));
        retval = atol(cArtikel);
    }

    if(codes.ARTICLE_CODE[0] == ' ')
    {
        codes.ARTICLENO = retval;
        kscartSel_Preferred(&codes, error_msg);
    }

    return retval;
}

/*****************************************************************************/
/* Setzen externe Verweisnummer                                              */
/*****************************************************************************/
int KscsrvSetRelationNo(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    nString cRelationNo;             // ein String-Objekt
    nString cRelationNoType;             // ein String-Objekt
    nString logtext;
    d->LACKREASON = 0;
    if(sLogLevel > 1)
    {
        logtext = now.AsString("%H:%M:%S");
        logtext += " In:  RelationNo";
        cRelationNo = d->RELATIONNO;
        cRelationNo.Trim(10, nString::cLEADING, '0');
        logtext += cRelationNo;
        logtext += " RelationNoType: ";
        cRelationNoType = d->RELATIONNOTYPE;
        cRelationNoType.Trim(5, nString::cLEADING, '0');
        logtext += cRelationNoType;
        logdat->Write(logtext);
    }
    if(d->RELATIONNOTYPE == 1)  //momentan nur Bestellnr
    {
        ps->Order()->setPurchaseOrderNo(d->RELATIONNO);
    }
    //ps->Order()->SetRelationno(d->RELATIONNO,d->RELATIONNOTYPE);
    error_msg[0] = '\0';
    return 0;
}

/*****************************************************************************/
/* Herstellernummer zu Artikel ermitteln                                     */
/*****************************************************************************/
int KscsrvGetArticleManufacturer(struct N_KSCSRVDATA* d, char* error_msg)  // DONESH: KscsrvGetArticleManufacturer - Neue Methode zur Ermittlung der HerstellerNr für KSCServer
{
    d->PID = 0;
    const long articleno = getArticleNoFromCode(d, error_msg);
    if( articleno > 0 )
    {
        pxArtMaster pxam(ps->Session(), articleno);
        pxam.Get();
        if ( !pxam.IsGoodState() )
        {
            return -2; // pxArtMaster not good state
        }
        d->PID = pxam.HerstellerNr();
    }
    else
    {
        return -1; // internal articleno not available
    }
    return 0;
}

/*****************************************************************************/
/* Checks if article may be exported to customer's country                   */
/*****************************************************************************/
// Input data: BRANCHNO, CUSTOMERNO, ARTICLENO
// Output data: INFOLEVEL: 1=permitted, 0=forbidden
int KscsrvIsExportPermitted(struct N_KSCSRVDATA* d, char* error_msg)
{
    nTime now;
    std::stringstream ss;
    int result = RC_OK;

    sLogLevel = 2;  //TODO REMOVE
    if (sLogLevel > 1)
    {
        logdat->Start();
        logdat->SetIDFNr("1");
        logdat->SetTerminalID("sba");
        logdat->Open();
        logdat->WriteList();
        ss << (const char*)now.AsString("%H:%M:%S")
           << " In:  IsExportPermitted "
           << " BranchNo: " << d->BRANCHNO
           << " CustomerNo: " << d->CUSTOMERNO
           << " ArticleNo: " << d->ARTICLENO;
        logdat->Write(ss.str().c_str());
    }

    ps->ClearError();
    d->INFOLEVEL = ps->isExportPermitted(d->BRANCHNO, d->CUSTOMERNO, d->ARTICLENO) ? 1 : 0;
    if (!ps->IsGoodState())
    {
        AllgStrCopy(error_msg, ps->ErrorMsg(), MAX_ERROR_MSG_AE);
        if (sLogLevel > 1)
        {
            ss.clear();
            ss << (const char*)now.AsString("%H:%M:%S")
               << "      IsExportPermitted Error " << error_msg;
            logdat->Write(ss.str().c_str());
        }
        result = (ps->IsFatalErrorState() || ps->IsAbendState()) ? RC_FATAL_ERR : RC_WARNING_1;
    }

    if (sLogLevel > 1)
    {
        logdat->End();
        logdat->CloseSeralog();
    }
    return result;
}


/*****************************************************************************/
/* Tour und Datum Auslieferung                                               */
/*****************************************************************************/
int KscsrvChangeDeliveryTour(struct N_KSCSRVDATA* d, char* error_msg)
{
    error_msg[0] = '\0';
    nDate desiredDate(d->TOURDATE);
    nString desiredTour(&d->TOURID[0]);

    if (ps->Order()->OrderType().IsNoDD())
    {
        desiredDate = TourUtil::getNullDate();
    } // no delayed delivery for order type

    if (ps->Order()->DatumAuslieferung() == desiredDate && ps->Order()->TourId() == desiredTour)
    {
        return 0;
    }

    if (TourUtil::isDateInTheFuture(desiredDate))
    {
        ps->Order()->SetDatumAuslieferung(d->TOURDATE);
    }

    nString tourid(&d->TOURID[0]);
    if (!ps->Order()->IsValidRoute(tourid))
    {
        tourid = "";
    }

    if (ps->Order()->getTourAssignmentUtil()->isTourValidForDate(tourid))
    {
        ps->Order()->getTourAssignmentUtil()->resetInjections();
        ps->Order()->getTourAssignmentUtil()->injectDesiredTourId(tourid);
        ps->Order()->getTourAssignmentUtil()->assignTour();
    }

    // Bulgaria does not want to use the requested tour if it´s not on the desired date (today), than use next assignable tour instead
    if ( ps->Session()->isBulgaria() )
    {
        if (!TourUtil::isNullOrCurrentDate(ps->Order()->DatumAuslieferung()) &&  desiredDate != TourUtil::getNullDate() )
        {
            if (ps->Order()->DatumAuslieferung().GetYYYYMMDD() != desiredDate.GetYYYYMMDD())
            {
                ps->Order()->SetDatumAuslieferung(0);
                ps->Order()->getTourAssignmentUtil()->resetInjections();
                ps->Order()->getTourAssignmentUtil()->assignTour();
            }
        }
    }

    AllgStrCopy(&d->TOURID[0], ps->Order()->TourId(), L_KSCSRVDATA_TOURID);
    d->TOURDATE = ps->Order()->DatumAuslieferung().GetYYYYMMDD();
    return 0;
}

/*****************************************************************************/
/* Change payment type to 'cash'                                             */
/*****************************************************************************/
int KscsrvChangePaymentToCashOrder(struct N_KSCSRVDATA*, char* error_msg)
{
    error_msg[0] = '\0';

    int rc = RC_OK;

    sMinLogLevel = 2;
    std::stringstream logtext;
    logtext << getCurrentTimeHMS() << " In:  ChangePaymentToCashOrder";
    writeLog(logtext);
    emptyStringstream(logtext);
    logtext << getCurrentTimeHMS() << " ChangePaymentToCashOrder: ";

    if (ps->Order() == NULL)
    {
        logtext << "Error: No order";
        rc = RC_FATAL_ERR;
    }
    else
    {
        ps->Order()->SetChangedToCashOrder();
        ps->Order()->SetOrderToCashAe();
        logtext << "Out";
    }

    writeEndCloseLog(logtext);

    return rc;
}

/*****************************************************************************/
/* Common log helpers                                                        */
/*****************************************************************************/
void openLogWithDummyIdf(long const minLogLevel)
{
    if (sLogLevel < minLogLevel)
    {
        sMinLogLevel = 0;
        return;
    }
    sMinLogLevel = minLogLevel;
    logdat->SetIDFNr("1"); // Dummy for SeraLog
    logdat->Open();
}

void writeLog(const std::stringstream& logtext)
{
    if (sLogLevel < sMinLogLevel)
    {
        return;
    }
    logdat->Write(logtext.str().c_str());
}

basar::I18nString getCurrentTimeHMS()
{
    return basar::Time::getCurrent().toString("%H:%M:%S");
}

void emptyStringstream(std::stringstream& logtext)
{
    logtext.clear();
    logtext.str("");
}

void writeEndCloseLogOnUnknownError(std::stringstream& logtext)
{
    logtext << " Unknown error";
    writeEndCloseLog(logtext);
}

void writeEndCloseLogOnBasarException(std::stringstream& logtext, basar::Exception const& ex)
{
    logtext << "basar exception: " << ex.what();
    writeEndCloseLog(logtext);
}

void writeEndCloseLog(const std::stringstream& logtext)
{
    if (sLogLevel < sMinLogLevel)
    {
        return;
    }
    logdat->Write(logtext.str().c_str());
    logdat->End();
    logdat->CloseSeralog();
}

/*****************************************************************************/
/* Common string helpers                                                     */
/*****************************************************************************/
void allgStrCopy(char* target, libcsc::VarString const source, unsigned max)
{
    AllgStrCopy(target, static_cast<basar::VarString>(source).c_str(), max);
}
