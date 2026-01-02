#include <sstream>
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxorder.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxocldef.h"
#include "pxoclpar.hpp"
#include "pxtaskcl.hpp"
#include "pxconstimecollect.hpp"
#include "pxcustrouteconstime.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxrouteconstime.hpp"
#include "pxorderperiod.hpp"
#include "pxordevt.hpp"
#include "pxoeparm.hpp"
#include "pxttype.hpp"
#include "tourutil.hpp"
#include "pxcremamail.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include <util/configfilereader.h>
#include "pxparameter.hpp"

#include <logger/loggerconfig.h>
#include <logger/loggerpool.h>
#include <util/configfilereader.h>
#ifndef WIN32
#include "gitversioninfo.h"
#endif


#include <libbasarcmnutil_cmdline.h>

#ifdef WIN32
#include <windows.h>
#include <io.h>
#include <direct.h>
#define F_OK 00
#define W_OK 02
#else
extern "C" {
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
}
#endif

#include <signal.h>

extern "C"
{
    extern const char versioninfo[];
}


#define PROGRAM "aaorderclose  "
bool STOP_PROGRAM = false;

void OnTermination(int /*signum*/)
{
    STOP_PROGRAM = true;
}

extern bool pxGlobalIBTNoTimeCheck;

void doCloseOrder( pxOrder* order, bool checkDDNotClose );
bool isCloseConsolidatedOrder( pxOrder* order, long tourSeconds, long consolidationDuration, long consolidationEndTime, long minPickingDuration, long numberLinesClose);
bool lastChanceClosureForMSV3(pxOrder* order, long tourSeconds, long consolidationDuration, long consolidationEndTime, long minPickingDuration, long numberLinesClose);
bool hasReachedMinPickingDuration( pxOrder* order, long tourSeconds, long minPickingDuration );
bool hasToBeChecked( pxOrder* order, pxOrderEntryParamPtr param );
bool getDDOrderEarlyCloseToggle(pxSession& session, short filialNr);
bool skipDDOrderEarlyClose(pxOrderEntryParamPtr param, pxOrder* order, bool ddOrderEarlyCloseSkipConfigured);

void prepareOrderEntryParameters( pxOrder* order );
void prepareCustomerParameters( pxOrder* order );

void cancelDeferredCremaOrders(pxSession& session, pxOrderCloseParamList& oclList, const pxOrderEntryParamPtr param, const short branchNo);

void PrintLogEvent( int orderno, const char* text );
void PrintLogEventError(int orderno, const char* text);
void initLog4Cplus( pxOrder * order );
void resetLogStream( std::stringstream& logstr );

int main(int argc, char **argv)
{
    basar::cmnutil::CmdLineTokenizer args;
    args.setCmdLine(argc, argv);

#ifndef WIN32
    if (args.isParam("-version"))
    {
        std::cout << versioninfo << std::endl;
        std::cout << GitVersionInfo::instance() << std::endl;
        exit( 0 );
    }
#endif

    std::stringstream logstr; // stringstream for logging purposes

    basar::VarString branchNoStr;
    args.getValOfParam("-v", branchNoStr);
    short filiale = static_cast<short>(branchNoStr.stoi());

    if (filiale == 0)
    {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "%s -vVSE_Nr\n\n",PROGRAM );
        return 0;
    }

    char* envir = getenv("INI_PATH");
    basar::VarString inifile;
    if (NULL != envir)
    {
        inifile.format("%s/aaordclose%02d.ini", envir, filiale);
    }
    else
    {
        inifile.format("../aaordclose%02d.ini", filiale);
    }

#ifdef WIN32
    if (_access(inifile.c_str(), F_OK) == -1)
#else
    if (access(inifile.c_str(), F_OK) == -1)
#endif
    {
        if (NULL != envir)
        {
            inifile.format("%s/aaordclose.ini", envir);
        }
        else
        {
            inifile = "../aaordclose%02d.ini";
        }
    }

    resetLogStream(logstr);
    logstr << "Using ini file " << inifile;
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), logstr.str());

    // Read in port and more
    libcsc::util::ConfigFileReader reader(inifile, libcsc::util::ConfigFileReader::CONFIG_FORMAT_INI);
    if (false == reader.read())
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), "Cannot read ini file");
        return 99;
    }

    int sleepsecs = reader.getInt("Session.Interval");
    if (sleepsecs == 0)
    {
        sleepsecs = 60;
    }

    // Write starting
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Starting");

    // Open the session.
    pxSession session(inifile, filiale);
    session.OpenDBConnection();
    if ( ! (session.IsGoodState()) )
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), session.ErrorMsg());
        return 99;
    }

    session.SetSubDeviceType(session.Device()->Name());

    nString key;
    pxTimeTypeList *timelist = NULL;
    timelist = new pxTimeTypeList( &session);
    timelist->Select(Type_ADS_CLOSE_FOR_AOCL, key, filiale);
    if (!timelist->Entries() )
    {
        delete timelist;
        timelist = NULL;
    }

    signal(SIGTERM, OnTermination);
    // Main Loop
    while ( ! STOP_PROGRAM )
    {
        //Check operation time
        if ( timelist )
        {
            nDate today;
            if ( !timelist->FindDayOfWeek( today.GetDayOfWeek() ) )
            {
                timelist->Select(Type_ADS_CLOSE_FOR_AOCL, key, filiale);
                if (!timelist->Entries() )
                {
                    delete timelist;
                    timelist = NULL;
                }
            }
            if ( timelist )
            {
                if ( !timelist->TimeInWindow() )
                {
#ifdef WIN32
                    Sleep( sleepsecs * 1000 );
#else
                    sleep( sleepsecs );
#endif
                    continue;
                }
            }
        }
        // write taskcontrol
        session.nDBBeginTransaction(cDBTransSet);
        nString  prog(PROGRAM);                // Programname
        nTime now;
        pxTaskControl tc(&session,filiale,prog);
        tc.TaskControl(now);
        if ( !tc.IsGoodState() )
        {
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), tc.ErrorMsg());
        }
        session.nDBCommit(cDBTransSet);

        // read paraauftragbearb
        session.resetOrderEntryParam();
        pxOrderEntryParamPtr para = session.getOrderEntryParam(filiale);
        if ( ! (para->IsGoodState()) )
        {
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), tc.ErrorMsg());
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), "No Database Connection");
            STOP_PROGRAM = true;
            continue;
        }

        // try to find entry for end ordercosolidation time(Zeitarten 9)
        nString keyend;
        pxTimeTypeList *tlist = NULL;
        tlist = new pxTimeTypeList( &session);
        tlist->Select(Type_ADS_END_CONSOLIDATION, keyend, filiale);
        if (!tlist->Entries() )
        {
            delete tlist;
            tlist = NULL;
        }

        if ( tlist )
        {
            para->SetAuftragZusammenHHH( (((pxTimeType*)(tlist->At(0)))->WindowEnd().GetHHMMSS())/100 );
        }

        nClock currenttime;
        long cdaysecs = currenttime.GetDaySeconds();
        long numberLinesClose = para->AnzPosClose();

        long AzuHHH = para->AuftragZusammenHHH();
        nString sAzuHHH;
        sAzuHHH = AzuHHH;
        AzuHHH = ( (sAzuHHH.Length() < 3 ) ? AzuHHH * 10000 : AzuHHH * 100);
        nClock tAzuHHH(AzuHHH);
        long   tAzuHHHsecs = tAzuHHH.GetDaySeconds();

        long AzuMMM = para->AuftragZusammenMMM() * 60;
        long minPickingDuration = para->DurchlaufNormal() * 60;

        // read kdauftragendezeit
        pxOrderCloseParamList closeparamlist(&session);
        closeparamlist.Select(filiale);
        pxOrderCloseParam* cl_entry;


        // Must we change cOCL_MODE_INTERNAL to cOCL_MODE_ONCE
        pxOrderCloseParamListIter oc_iter(closeparamlist);
        while ((cl_entry = (pxOrderCloseParam*)++oc_iter) != NULL)
        {
            if (cl_entry->IsCloseModeInternal())
            {
                if (cl_entry->AbschlussZeit() > currenttime)
                {
                    // We must do a rollback
                    cl_entry->nDBBeginTransaction(cDBTransRecord);

                    tKDAUFTRAGENDEZEIT kdende;
                    Assign(kdende, *cl_entry);

                    // Delete it from DB
                    if (pxAuftragEndeZeitDelete(&kdende) == 0 && cl_entry->SetModeOnce())
                    {
                        Assign(kdende, *cl_entry);

                        // Write new one
                        if (pxAuftragEndeZeitInsert(&kdende) == 0)
                        {
                            // Delete from list.
                            closeparamlist.Remove((nCollectable*)cl_entry);

                            // Insert new one into list
                            tKDAUFTRAGENDEZEIT cst_ord_end;
                            Assign(cst_ord_end, *cl_entry);
                            closeparamlist.AddToList((void*)&cst_ord_end, 0);

                            // Begin from first entry
                            oc_iter.Reset();

                            cl_entry->nDBCommit();
                        }
                        else
                        {
                            cl_entry->nDBRollBack();
                        }
                    }
                    else
                    {
                        cl_entry->nDBRollBack();
                    }
                }
            }
        }

        int i = 0;
        while ( i != 2 )
        {
            session.resetSepOrderArtGroupList(); // read split criteria for each loop

            pxOrderList orderlist(&session);
            orderlist.SelectForAutomaticClosure(filiale, "0000%", Order::EntryDeferred, Order::NOT_Invoiced, Order::NOT_Cancelled, Order::NOT_ProblemClearance, Order::cStateLast);

            pxOrderListIter orderiter(orderlist);
            pxOrder* order = NULL;
            pxGlobalIBTNoTimeCheck = true;
            nTime currentime;

            resetLogStream(logstr);
            logstr << "====> Found " << orderlist.Entries() << " order(s) to be checked.";
            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), logstr.str());

            const bool skipDDOrderEarlyCloseToggle = getDDOrderEarlyCloseToggle(session, filiale);

            while ((order = (pxOrder*)++orderiter) != NULL)
            {
                PrintLogEvent( order->KdAuftragNr(), "Checking Order" );


                // do basic checks if the order has to be processed
                if( !hasToBeChecked( order, para ) ) { continue; }

                // Get tour
                long tour = TourUtil::getTourIdAsHHMM( order->TourId() );
                nClock ctour(tour * 100);
                long toursecs = ctour.GetDaySeconds();



                // Has the order a valid tour
                // SR-16006860 - Verbund-Shuttle-Aufträge auch abschliessen wenn DatumAuslieferung gleich Aktuelles Datum
                if (tour > 0 || ( (order->KoArt() == '2') && order->BatchSchreiben() == cORTYPE_INDUSTRIAL_RETURN ) || TourUtil::isNullOrCurrentDate(order->DatumAuslieferung()) )
                {
                    if (order->BatchSchreiben() > 0)
                    {
                        // check min picking time for interbranchtransfer orders
                        if( hasReachedMinPickingDuration( order, toursecs, minPickingDuration ) &&  order->BatchSchreiben() == cORTYPE_AUXILIARY )
                        {
                            order->OpenOrder(cDBOPEN_INSERT);
                            if ( order->IsGoodState() )
                            {
                                order->RouteClearKippZeit();
                                prepareOrderEntryParameters( order );
                                prepareCustomerParameters( order );

                                if( "VBIMPORT" == order->GeraetName() )
                                {
                                    order->ClearProblemClearance();
                                }

                                PrintLogEvent( order->KdAuftragNr(), "CLOSE due to first check on min picking duration" );
                                order->AAClose(Order::EntryClosed);
                                if ( order->IsEntryDeferred() )
                                {
                                    PrintLogEvent( order->KdAuftragNr(), "CLOSE due to first check on min picking duration but DEFERRED!!!" );
                                }
                            }
                        }
                        else
                        {
                            // Closeparam entry Loop
                            oc_iter.Reset();
                            while ((cl_entry = (pxOrderCloseParam*)++oc_iter) != NULL)
                            {
                                if ( order->BatchSchreiben() == cl_entry->BatchSchreiben() && order->HerkunftFiliale() == cl_entry->HerkunftsFilialNr() )
                                {
                                    switch ((OCLMODE)cl_entry->AbschlussModus())
                                    {
                                        case cOCL_MODE_ONCE :
                                        case cOCL_MODE_PERMANENT :
                                            if (currenttime <= cl_entry->AbschlussZeit())
                                            {
                                                break;
                                            }
                                            // fallthrough
                                        case cOCL_MODE_IMMEDIATE :
                                            {
                                                // Open the order for update
                                                order->OpenOrder(cDBOPEN_INSERT);
                                                if ( !order->IsGoodState() )
                                                {
                                                    break;
                                                }

                                                order->RouteClearKippZeit();
                                                prepareOrderEntryParameters( order );
                                                prepareCustomerParameters( order );

                                                if( "VBIMPORT" == order->GeraetName() )
                                                {
                                                    order->ClearProblemClearance();
                                                }

                                                resetLogStream(logstr);
                                                logstr << "ORDER: " << order->KdAuftragNr() << "EVENT: CLOSE order due to KDAuftragEndeZeit: FilialNr:" << cl_entry->FilialNr()
                                                        << "|BatchSchreiben:" << cl_entry->BatchSchreiben() << "|HerkunftFiliale:" << cl_entry->HerkunftsFilialNr()
                                                        << "|AbschlussModus:" << cl_entry->AbschlussModus() << "|AbschlussZeit:" << cl_entry->AbschlussZeit().GetHHMMSS();
                                                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), logstr.str());

                                                PrintLogEvent( order->KdAuftragNr(), "CLOSE due to kdauftragendezeit" );
                                                order->AAClose(Order::EntryClosed);
                                                if ( order->IsEntryDeferred() )
                                                {
                                                    PrintLogEvent( order->KdAuftragNr(), "CLOSE due to kdauftragendezeit but DEFERRED!!!" );
                                                }
                                            }
                                        case cORTYPE_UNKNOWN :
                                        default:
                                            break;
                                    }
                                }

                                if( order->IsEntryClosed() )
                                {
                                    break;
                                }
                            }
                        }
                    }
                    /*----------------------------------------------------------------------------*/
                    /*              Close Orders with delayeddelivery, generated automaticly by   */
                    /*              orderentry  (non video and stock receipt                      */
                    /*----------------------------------------------------------------------------*/
                    else if ( order->DatumAuslieferung() != pxConstants::NullDate && order->AnzPos() > 0 && 
                        ( order->IsVerzoegerAusgeliefert() && !skipDDOrderEarlyClose(para, order, skipDDOrderEarlyCloseToggle)))
                    {
                        if( order->Customer() != NULL )
                        {
                            PrintLogEvent( order->KdAuftragNr(), "CLOSE DelayedDelivery" );
                            doCloseOrder( order, true );
                        }
                    }
                    /*----------------------------------------------------------------------------*/
                    /*              Close Orders for Customers with Orderconsolidation and        */
                    /*              XML-Order and Versnadapotheke and not appendable              */
                    /*----------------------------------------------------------------------------*/
                    else if( order->Customer() != NULL && order->Customer()->Flags().IsAuftragZusammen() &&
                            order->AnzPos() > 0 && order->Customer()->Flags().IsVersandApo() && order->IsDoNotAppend() )
                    {
                        if( order->DatumAuslieferung() != pxConstants::NullDate )
                        {
                            PrintLogEvent( order->KdAuftragNr(), "CLOSE DoNotAppend for Webshop (1) " );
                            doCloseOrder( order, true );
                        }
                        else
                        {
                            PrintLogEvent( order->KdAuftragNr(), "CLOSE DoNotAppend for Webshop (2) " );
                            doCloseOrder( order, true );
                        }
                    }
                    /*----------------------------------------------------------------------------*/
                    /*              Close consolidated orders                                     */
                    /*----------------------------------------------------------------------------*/
                    else if( isCloseConsolidatedOrder(order, toursecs, AzuMMM, tAzuHHHsecs, minPickingDuration, numberLinesClose) )
                    {
                        if( order->DatumAuslieferung() != pxConstants::NullDate )
                        {
                            PrintLogEvent( order->KdAuftragNr(), "CLOSE OrderConsolidation (1)" );
                            doCloseOrder( order, true );
                        }
                        else
                        {
                            PrintLogEvent( order->KdAuftragNr(), "CLOSE OrderConsolidation (2)" );
                            doCloseOrder( order, true );
                        }
                    }
                    /*----------------------------------------------------------------------------*/
                    /*              Close Orders with delayed delivery generated by orderentry    */
                    /*              (video orders)                                                */
                    /*----------------------------------------------------------------------------*/
                    else if( order->DatumAuslieferung() != pxConstants::NullDate)
                    {
                        if( order->Customer() != NULL && order->AnzPos() > 0 )
                        {
                            if (session.isFrance())
                            {
                                if( (cdaysecs > tAzuHHHsecs) || ((cdaysecs + AzuMMM) > toursecs) || (order->KoArt() != '0') )
                                {
                                    PrintLogEvent( order->KdAuftragNr(), "CLOSE FR Orders" );
                                    doCloseOrder( order, false );
                                }
                            }
                            else
                            {
                                if (skipDDOrderEarlyClose(para, order, skipDDOrderEarlyCloseToggle))
                                {
                                    PrintLogEvent(order->KdAuftragNr(), "Keep Order open becasue of skipDDOrderEarlyClose");
                                }
                                else
                                {
                                    PrintLogEvent(order->KdAuftragNr(), "CLOSE Orders");
                                    doCloseOrder(order, false);
                                }
                            }
                        }
                        else
                        {
                            PrintLogEvent( order->KdAuftragNr(), "NOCLOSE Orders" );
                        }
                    }
                    /*----------------------------------------------------------------------------*/
                    /*              Close MSV3 orders which should be closed                      */
                    /*----------------------------------------------------------------------------*/
                    else if (lastChanceClosureForMSV3(order, toursecs, AzuMMM, tAzuHHHsecs, minPickingDuration, numberLinesClose))
                    {
                        if (order->DatumAuslieferung() != pxConstants::NullDate)
                        {
                            PrintLogEventError(order->KdAuftragNr(), "CLOSE lastChanceClosureForMSV3 (1)");
                            doCloseOrder(order, true);
                        }
                        else
                        {
                            PrintLogEventError(order->KdAuftragNr(), "CLOSE lastChanceClosureForMSV3 (2)");
                            doCloseOrder(order, true);
                        }
                    }
                }
            }

            // Free storage
            orderlist.Clear();
            i++;
#ifdef WIN32
            Sleep( 3 * 1000 );
#else
            sleep( 3 );
#endif
        }

        cancelDeferredCremaOrders(session, closeparamlist, para, filiale);



        // Must we change cOCL_MODE_ONCE to cOCL_MODE_INTERNAL
        oc_iter.Reset();
        while ((cl_entry = (pxOrderCloseParam*)++oc_iter) != NULL)
        {
            if (cl_entry->IsCloseModeOnce())
            {
                if (cl_entry->AbschlussZeit() < currenttime)
                {
                    cl_entry->nDBBeginTransaction(cDBTransRecord);
                    tKDAUFTRAGENDEZEIT kdende;
                    Assign(kdende, *cl_entry);
                    if( pxAuftragEndeZeitDelete(&kdende) == 0 && cl_entry->SetModeInternal() )
                    {
                        Assign(kdende, *cl_entry);
                        if( pxAuftragEndeZeitInsert(&kdende) != 0 )
                        {
                            cl_entry->SetModeOnce();
                            cl_entry->nDBRollBack();
                        }
                        else
                        {
                            cl_entry->nDBCommit();
                        }
                    }
                    else
                    {
                        cl_entry->nDBRollBack();
                    }
                }
            }
        }

        /*----------------------------------------------------------------------------*/
        /*  Look for entries within the ConsTimeCollectList CTList.                   */
        /*  If available, so delete each entrie from the Database and clear the list  */
        /*  for next use                                                              */
        /*----------------------------------------------------------------------------*/
        /*pxConsTimeCollect*  collectp = NULL;
        pxConsTimeCollectListIter cursor(*CTList);
        pxCustRouteConsTime*     custentry  = NULL;     // customer routeconstime entry
        pxRouteConsTime*         routeentry = NULL;     // Routconstime entry
        if ( CTList->Entries() )
        {
            while( (collectp = (pxConsTimeCollect*)++cursor) != NULL )
            {
                session.nDBBeginTransaction(cDBTransRecord);
                if( collectp->CustomerNo() == 0 )        // = common Routconstime entry
                {
                    routeentry = new pxRouteConsTime(&session,collectp->BranchNo(),collectp->TourId(), collectp->DatumKommi(),collectp->ConsTime());
                    if( routeentry->IsGoodState() )
                    {
                        routeentry->SetEntryDone();
                        routeentry->Put();
                        if( routeentry->IsGoodState() )
                        {
                            session.nDBCommit(cDBTransRecord);
                            delete cursor.Remove();
                        }
                        else
                        {
                            session.nDBRollBack();
                        }
                    }
                }
                else
                {
                    custentry = new pxCustRouteConsTime(&session,collectp->BranchNo(), collectp->CustomerNo(),collectp->TourId(), collectp->DatumKommi(),collectp->ConsTime());
                    if (custentry->IsGoodState() )
                    {
                        custentry->SetEntryDone();
                        custentry->Put();
                        if ( custentry->IsGoodState() )
                        {
                            session.nDBCommit(cDBTransRecord);
                            delete cursor.Remove();
                        }
                        else
                        {
                            session.nDBRollBack();
                        }
                    }
                }
            }
        }*/

        /*----------------------------------------------------------------------------*/
        /*  Look for entries within the TourPlanConsTime and TourConsTime Table for   */
        /*  entries which constime < cuurentime and the procsesstate == 0             */
        /*----------------------------------------------------------------------------*/
    /*  pxCustRouteConsTimeList  CconstimeList(&session);
        pxCustRouteConsTimeListIter cit(CconstimeList);
        pxRouteConsTimeList      RconstimeList(&session);
        pxRouteConsTimeListIter  rit(RconstimeList);
        nClock nun;               // current time
        nDate  today;             // to day
        RconstimeList.Select(filiale,today,nun,'0');
        CconstimeList.Select(filiale,today,nun,'0');

        if ( CconstimeList.Entries() )
        {
            while ( (custentry = (pxCustRouteConsTime*)++cit) != NULL )
            {
                session.nDBBeginTransaction(cDBTransRecord);
                custentry->SetEntryDone();
                custentry->Put();
                if ( custentry->IsGoodState() )
                {
                    session.nDBCommit(cDBTransRecord);
                    delete cit.Remove();
                }
                else
                {
                    session.nDBRollBack();
                }
            }
        }

        if( RconstimeList.Entries() )
        {
            while ( (routeentry = (pxRouteConsTime*)++rit) != NULL )
            {
                session.nDBBeginTransaction(cDBTransRecord);
                routeentry->SetEntryDone();
                routeentry->Put();
                if ( routeentry->IsGoodState() )
                {
                    session.nDBCommit(cDBTransRecord);
                    delete rit.Remove();
                }
                else
                {
                    session.nDBRollBack();
                }
            }
        }
        */
#ifdef WIN32
        Sleep( sleepsecs * 1000 );
#else
        sleep( sleepsecs );
#endif
    }

    // Write ending
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Ending");
    return 0;
}

/*----------------------------------------------------------------------------*/
/* Gets branch toggle value AllowConsDD i.e. allow consolidation of DD orders */
/* For delayed delivery should be kept order open till HBZ or BFE-------------*/
/*----------------------------------------------------------------------------*/
bool getDDOrderEarlyCloseToggle(pxSession& session, short filialNr)
{    
    //Parameteres for getting branchAllowingDelayedOrderConsoldation flag
    nString programName("orderclosebatch");
    nString objective_ConsolDelDeliv("AllowConsDD");
    nString paramName_AllowConsDelDeliv("AllowConsDD");

    //Check if the branch is allowing delayed delivery orders to be consolidated
    pxParameter* allowConsDDParam = new pxParameter(&session, filialNr, programName, objective_ConsolDelDeliv, paramName_AllowConsDelDeliv);
    allowConsDDParam->Get(cDBGET_READONLY);
    if (1 == allowConsDDParam->Wert())
    {
        return true;
    }

    return false;
}

/*-------------------------------------------------------------------------*/
/* Checks if delayed delivery should be kept order open till HBZ or BFE----*/
/* The consolidation must be allowed at levels Branch, customer, Order Type*/
/* and AllowConsDD flag must be true.                                      */               
/*-------------------------------------------------------------------------*/
bool skipDDOrderEarlyClose(pxOrderEntryParamPtr param, pxOrder* order,  bool ddOrderEarlyCloseSkipConfigured)
{
    char logmsgbuffer[1024];
    sprintf(logmsgbuffer, "skipDDOrderEarlyClose config values -> Toggle Level:%d | Branch Level:%d | Customer Level:%d | OrderType Level:%d", ddOrderEarlyCloseSkipConfigured, param->IsOrderConsolidation(), order->Customer()->Flags().IsAuftragZusammen(), order->OrderType().IsOrderCons());
    PrintLogEvent(order->KdAuftragNr(), logmsgbuffer);

    if (order->KoArt() == '2' || order->KoArt() == '3') // SR-25011582, do not skip orders with kommiart 2 and 3 )
    {
        return false;
    }

    if (ddOrderEarlyCloseSkipConfigured &&
        order->Customer()->Flags().IsAuftragZusammen() &&
        param->IsOrderConsolidation()
        && order->OrderType().IsOrderCons())
    {
        return true;
    }
    return false;

}


/* ------------------------------------------------------------------------- */
/* do basic checks if the order has to be processed or not                   */
/* ------------------------------------------------------------------------- */
bool hasToBeChecked( pxOrder* order, pxOrderEntryParamPtr param )
{
    // do not close orders with 0 items
    if( !(order->AnzPos() > 0) )
    {
        PrintLogEvent( order->KdAuftragNr(), "NOCLOSE AnzPos not > 0" );
        return false;
    }

    // customer not good
    if( NULL == order->Customer() )
    {
        PrintLogEvent( order->KdAuftragNr(), "NOCLOSE NULL-Customer" );
        return false;
    }

    // order type not good
    order->OrderType(order->KdAuftragArt(),order->KoArt(), order->BuchArt());
    if ( !order->IsGoodState())
    {
        PrintLogEvent( order->KdAuftragNr(), "NOCLOSE BadState due to OrderType" );
        return false;
    }

    // ignore order if OverDriveCondition has been set
    if( order->IsOverDriveCondition() )
    {
        PrintLogEvent( order->KdAuftragNr(), "NOCLOSE IsOverDriveCondition" );
        return false;
    }

    // ignore separated defect orders
    if( order->IsSepDefectOrder() )
    {
        PrintLogEvent( order->KdAuftragNr(), "NOCLOSE IsSepDefectOrder" );
        return false;
    }

    // do not close orders that have been created within the last seconds (SR-14006785)
    {
        nTime currentime;
        nTime orderDateTimeCreated = order->DateTimeCreated();
        if( order->DatumAuslieferung() == pxConstants::NullDate )
        {
            if ( currentime.GetSecs() < ((orderDateTimeCreated.GetSecs()) + param->ConsolidationDelay() ))
            {
                PrintLogEvent( order->KdAuftragNr(), "NOCLOSE ShortlyCreated" );
                return false;
            }
        }
    }

    // do not close orders with ordertype CV22
    {
        nString aufArt;
        char koArt;
        char buchArt;
        aufArt = order->KdAuftragArt();
        koArt = order->KoArt();
        buchArt = order->BuchArt();
        aufArt = aufArt+(nString)koArt+(nString)buchArt;
        if( aufArt == cCOLLECTIVORDER22 )
        {
            PrintLogEvent( order->KdAuftragNr(), "NOCLOSE OrderType CV22" );
            return false;
        }
    }

    return true;
}

/* ------------------------------------------------------------------------- */
/* check if order has reached the min picking duration                       */
/* ------------------------------------------------------------------------- */
bool hasReachedMinPickingDuration( pxOrder* order, long tourSeconds, long minPickingDuration )
{
    if( TourUtil::isNullOrCurrentDate( order->DatumAuslieferung() ) )
    {
        nClock currenttime;
        if( (currenttime.GetDaySeconds() + minPickingDuration) > tourSeconds )
        {
            return true;
        }
    }
    return false;
}

/* ------------------------------------------------------------------------- */
/* check MSV3 order period end time and main time                            */
/* CR 15D001 Anpassung Automatischer Auftragsabschluss für MSV3              */
/* ------------------------------------------------------------------------- */

bool checkMSV3OrderPeriod(pxOrder* order)
{
    nDate today;
    nClock now;

    if (!order->isMSV3Order())
        return false;
    if (!order->Param()->IsMSV3OrderPeriodClosureActivated())
        return false;

    pxOrderPeriod orderPeriod(order->Session(), order->OrderPeriodID());
    orderPeriod.Get();
    if (!orderPeriod.IsGoodState())
        return false;
    if (orderPeriod.WeekDay() != today.GetDayOfWeek())
        return false;

    nClock adjustment(order->Param()->MSV3ClosureTimeAdjustment() * 100);
    nClock startTime(orderPeriod.FromTime() * 100);
    nClock mainTime(orderPeriod.MainTime() * 100);
    nClock endTime(orderPeriod.ToTime() * 100);

    // Ende des Bestellfensters + evtl. Karenzzeit erreicht
    if (now > endTime + adjustment)
    {
        PrintLogEvent( order->KdAuftragNr(), "TRUE = checkMSV3OrderPeriod: order period end reached for MSV3 order" );
        return true;
    }

    // Hauptbestellzeit des Bestellfensters + evtl. Karenzzeit
    // Achtung: Auftrag muss vor Hauptbestellzeit eröffnet worden sein, sonst Auftragszusammenführung bis Ende Bestellfenster
    if (now > mainTime + adjustment && mainTime > startTime)
    {
        // CR 15D130 B DE Automatischer Abschluss MSV3 Aufträge nach Hauptbestellzeitpunkt
        if (order->Customer()->Flags().IsNoOrderConsAfterMot())
        {
            PrintLogEvent(order->KdAuftragNr(), "TRUE == kundeschalter.NoOrderConsAfterMot" );
            return true;
        }
		if (order->DatumAuslieferung() != pxConstants::NullDate)
		{
			// DD orders are always opened before main time
			PrintLogEvent(order->KdAuftragNr(), "TRUE = checkMSV3OrderPeriod: order period main time reached for MSV3 DD order");
            return true;
		}
        pxOrderEventList orderEventList(order->Session());
        orderEventList.Select(order->KdAuftragNr(), Order::EntryInProgress,100);
        pxOrderEventListIter it(orderEventList);
        pxOrderEvent* event = NULL;
        while ((event = (pxOrderEvent*)++it) != NULL)
        {
            // finde Auftrageröffnung von heute und vergleiche, ob vor Hauptbestellzeit
            if (event->Date() == today && event->Clock() <= mainTime + adjustment)
            {
                PrintLogEvent( order->KdAuftragNr(), "TRUE = checkMSV3OrderPeriod: order period main time reached for MSV3 order" );
                return true;
            }
        }
    }
    return false;
}

/* ------------------------------------------------------------------------- */
/* check if MSV3 order has to be closed                                      */
/* ------------------------------------------------------------------------- */
bool lastChanceClosureForMSV3(pxOrder* order,
    long tourSeconds,
    long consolidationDuration,             // Durchlaufzeit Auftragszusammenführung (paraauftragberarb.auftragzusammenmmm)
    long consolidationEndTime,              // Endezeit Auftragszusammenführung (paraauftragbearb.auftragzusammenhhh)
    long minPickingDuration,                // Lagerdurchlaufzeit (paraauftragbearb.durchlaufnormal)
    long numberLinesClose)                  // Anzahl Positionen für autom. Abschluss       
{
    // just for MSV3 orders!!!
    if (!order->isMSV3Order())
    {
        return false;
    }

    // get current time
    nClock currenttime;

    order->OrderType(order->KdAuftragArt(), order->KoArt(), order->BuchArt());
    if (!order->IsGoodState())
    {
        PrintLogEvent(order->KdAuftragNr(), "FALSE = lastChanceClosureForMSV3: BadState due to OrderType");
        return false;
    }

    std::string tourid(order->TourId());
    char logmsgbuffer[1024];
    sprintf(logmsgbuffer, "lastChanceClosureForMSV3 Parameters -> TourID:%s | CurrentTime:%ld | TourSecs:%ld | ConsDuration:%ld | ConsEndTime:%ld | MinPickingDuration:%ld | NumberLinesClose:%ld", tourid.c_str(), currenttime.GetDaySeconds(), tourSeconds, consolidationDuration, consolidationEndTime, minPickingDuration, numberLinesClose);
    PrintLogEvent(order->KdAuftragNr(), logmsgbuffer);

    // close consolidated order for customers with different consolidation times
    nString tour = order->TourId();

    // close consolidated orders due to end of order consolidation for the current day
    if ( currenttime.GetDaySeconds() > consolidationEndTime)
    {
        PrintLogEvent(order->KdAuftragNr(), "TRUE = lastChanceClosureForMSV3: End of order consolidation");
        return true;
    }

    // close MSV3 orders if minimum duration for picking is reached
    if ((currenttime.GetDaySeconds() + minPickingDuration) > tourSeconds)
    {
        PrintLogEvent(order->KdAuftragNr(), "TRUE = lastChanceClosureForMSV3: MinPickingDuration reached for MSV3 order");
        return true;
    }
    if (checkMSV3OrderPeriod(order))
    {
        return true;
    }

    // close due to number of order lines in order
    if (numberLinesClose > 0)
    {
        if (order->AnzPos() >= numberLinesClose)
        {
            PrintLogEvent(order->KdAuftragNr(), "TRUE = lastChanceClosureForMSV3: numberLinesClose reached");
            return true;
        }
    }

    PrintLogEvent(order->KdAuftragNr(), "FALSE = lastChanceClosureForMSV3: no reason to close");
    return false;
}

/* ------------------------------------------------------------------------- */
/* check if order has to be closed due to consolidation                      */
/* ------------------------------------------------------------------------- */
bool isCloseConsolidatedOrder(  pxOrder* order,
                                long tourSeconds,
                                long consolidationDuration,             // Durchlaufzeit Auftragszusammenführung (paraauftragberarb.auftragzusammenmmm)
                                long consolidationEndTime,              // Endezeit Auftragszusammenführung (paraauftragbearb.auftragzusammenhhh)
                                long minPickingDuration,                // Lagerdurchlaufzeit (paraauftragbearb.durchlaufnormal)
                                long numberLinesClose)                  // Anzahl Positionen für autom. Abschluss       
{
    // get current time
    nClock currenttime;

    order->OrderType(order->KdAuftragArt(),order->KoArt(), order->BuchArt());
    if ( !order->IsGoodState())
    {
        PrintLogEvent( order->KdAuftragNr(), "FALSE = isCloseConsolidatedOrder: BadState due to OrderType" );
        return false;
    }

    // do not close orders for customers without order consolidation
    if( !order->IsOrderConsolidation() )
    {
        PrintLogEvent( order->KdAuftragNr(), "FALSE = isCloseConsolidatedOrder: No consolidated order" );
        return false;
    }

    std::string tourid(order->TourId());
    char logmsgbuffer[1024];
    sprintf( logmsgbuffer, "isCloseConsolidatedOrder Parameters -> TourID:%s | CurrentTime:%ld | TourSecs:%ld | ConsDuration:%ld | ConsEndTime:%ld | MinPickingDuration:%ld | NumberLinesClose:%ld", tourid.c_str(), currenttime.GetDaySeconds(), tourSeconds, consolidationDuration, consolidationEndTime, minPickingDuration, numberLinesClose );
    PrintLogEvent( order->KdAuftragNr(), logmsgbuffer );

    // close consolidated order for customers with different consolidation times
    nString tour = order->TourId();
    if( order->Customer()->ConsolidationTime( tour, order->DateTimeCreated() ) == 1 )
    {
        PrintLogEvent( order->KdAuftragNr(), "TRUE = isCloseConsolidatedOrder: ConsTime reached" );
        return true;
    }

    // close consolidated orders due to end of order consolidation for the current day
    if( currenttime.GetDaySeconds() > consolidationEndTime)
    {
        PrintLogEvent( order->KdAuftragNr(), "TRUE = isCloseConsolidatedOrder: End of order consolidation" );
        return true;
    }

    // close consolidated order due to duration for order consolidation
    if( !order->isMSV3Order() )
    {
        if( (currenttime.GetDaySeconds() + consolidationDuration) > tourSeconds )
        {
            PrintLogEvent( order->KdAuftragNr(), "TRUE = isCloseConsolidatedOrder: ConsDuration reached (and not MSV3)" );
            return true;
        }
    }

    // close MSV3 orders if minimum duration for picking is reached
    if( order->isMSV3Order() )
    {
        if (order->Session()->isAustria())
        {
            if( (currenttime.GetDaySeconds() + consolidationDuration) > tourSeconds )
            {
                PrintLogEvent( order->KdAuftragNr(), "TRUE = isCloseConsolidatedOrder: ConsDuration reached (and MSV3 Austria)" );
                return true;
            }
        }
        if( (currenttime.GetDaySeconds() + minPickingDuration) > tourSeconds )
        {
            PrintLogEvent( order->KdAuftragNr(), "TRUE = isCloseConsolidatedOrder: MinPickingDuration reached for MSV3 order" );
            return true;
        }
        if (checkMSV3OrderPeriod(order))
        {
            return true;
        }
    }


    // close due to number of order lines in order
    if( numberLinesClose > 0 )
    {
        if( order->AnzPos() >= numberLinesClose )
        {
            PrintLogEvent( order->KdAuftragNr(), "TRUE = isCloseConsolidatedOrder: numberLinesClose reached" );
            return true;
        }
    }

    PrintLogEvent( order->KdAuftragNr(), "FALSE = isCloseConsolidatedOrder: no reason to close" );
    return false;
}

/* ------------------------------------------------------------------------- */
/* close the current order                                                   */
/* ------------------------------------------------------------------------- */
void doCloseOrder( pxOrder* order, bool checkDDNotClose )
{
    if( checkDDNotClose && order->IsDDNotClose() )
    {
        PrintLogEvent( order->KdAuftragNr(), "doCloseOrder NOCLOSE checkDDNotClose" );
        return;
    }

    order->OpenOrder( cDBOPEN_INSERT );
    if( !order->IsGoodState() )
    {
        PrintLogEvent( order->KdAuftragNr(), "doCloseOrder NOCLOSE Order Not GoodState" );
        return;
    }
    initLog4Cplus( order );

    order->RouteClearKippZeit();
    prepareOrderEntryParameters( order );
    prepareCustomerParameters( order );

    // Try to close the order.
    if( order->AAClose(Order::EntryClosed) != 0 )
    {
        PrintLogEvent( order->KdAuftragNr(), "doCloseOrder CLOSE AAClose returned an error" );
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), order->ErrorMsg());

        order->AAClose( Order::EntryDeferred );
    }
}

/* ------------------------------------------------------------------------- */
/* prepare the order entry parameters                                        */
/* ------------------------------------------------------------------------- */
// todo remove when tourmanager active in FR
void prepareOrderEntryParameters( pxOrder* order )
{
    order->Param()->SetDurchlaufNormal(0);
    order->Param()->SetDurchlaufEilbote(0);
    order->Param()->SetTourenKippZeit(0);
}

/* ------------------------------------------------------------------------- */
/* prepare the customer parameters                                           */
/* ------------------------------------------------------------------------- */
void prepareCustomerParameters( pxOrder* order )
{
    tKUNDE kdrecord;
    memset(&kdrecord, 0, sizeof(tKUNDE));
    Assign( kdrecord, *(order->Customer()) );
    kdrecord.TourenKippZeit = 0;
    Assign( *(order->Customer()), kdrecord );
}

/* ------------------------------------------------------------------------- */
/* cancel deferred crema orders (credit limit)                               */
/* ------------------------------------------------------------------------- */
#include "libbasarcmnutil_datetime.h"
#include "libbasarcmnutil_timespan.h"
#include "libbasarcmnutil_i18nstring.h"

void cancelDeferredCremaOrders(pxSession& session, pxOrderCloseParamList& oclList, const pxOrderEntryParamPtr param, const short branchNo)
{
BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "cancelDeferredCremaOrders()");

    pxOrderCloseParam* ocl = oclList.FindBatchSchreiben(cORTYPE_CANCEL_CREMA_ORDER);
    nClock now;
    if (ocl == NULL)
    {
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "no kdauftragendezeit");
        return;
    }
    if (false == ocl->IsCloseModeOnce() || now < ocl->AbschlussZeit())
    {
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "no close mode once || < Abschlusszeit");
        return;
    }

    short timeCancelCremaOrder = param->TimeCancelCremaOrder();
    basar::cmnutil::TimeSpan cancelTimeSpan;
    basar::VarString fmt;

    // CPR-211062, udated to have days on hold period for order
    if (timeCancelCremaOrder > (short)23)
    {
        fmt.format("%d %02d:00:00.000", timeCancelCremaOrder / 24, timeCancelCremaOrder % 24);
    }
    else
    {
        fmt.format("0 %02d:00:00.000", timeCancelCremaOrder);
    }
    cancelTimeSpan.fromNormalizedString(fmt);

    pxCremaMailList orderList(&session);
    orderList.SelectDeferredCremaOrders(branchNo);

    pxCremaMailListIter iter(orderList);
    pxCremaMail*        entry;
    while ((entry = (pxCremaMail*)++iter) != NULL)
    {
        basar::cmnutil::DateTime deferDateTime(entry->SendDate(), entry->SendTime() * 1000);
        std::stringstream s;
        //s << "branchno=" << entry->BranchNo() << ", kdauftragnr=" << entry->KdAuftragNr() << ", senddate=" << entry->SendDate()
        //  << ", sendtime=" << entry->SendTime() << ",approvalpersonsneeded=" << entry->ApprovalPersonsNeeded() << std::endl;
        s << "check CREMA: " << deferDateTime << " + " << cancelTimeSpan;
        PrintLogEvent(entry->KdAuftragNr(), s.str().c_str());
        if (deferDateTime + cancelTimeSpan < basar::cmnutil::DateTime::getCurrent())
        {
            PrintLogEvent(entry->KdAuftragNr(), "cancel CREMA");
            pxOrder order(&session, entry->KdAuftragNr(), cDBGET_READONLY);
            if (false == order.IsGoodState())
            {
                BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), order.ErrorMsg());
                continue;
            }
            order.OpenOrder(cDBOPEN_INSERT);
            order.ClearError();
            order.ClearProblemClearance();
            order.SetReleaseInfos("Automatic cancellation", "", session.Device()->Name(), Order::CANCEL);
            order.SetNoDebtLimitCheck();
            order.CancelOrder(pxDVC_UNDEFINED, Order::cCancel_UnConditional);
            if (false == order.IsGoodState())
            {
                BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), order.ErrorMsg());
                continue;
            }
            entry->Delete();
        }
    }
}

/* ------------------------------------------------------------------------- */

void PrintLogEvent( int orderno, const char* text )
{
    std::stringstream ss;
    ss << "ORDER: " << orderno << " EVENT: " << text;
    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), ss.str());
}

void PrintLogEventError(int orderno, const char* text)
{
    std::stringstream ss;
    ss << "ORDER: " << orderno << " EVENT: " << text;
    BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), ss.str());
}

/* ------------------------------------------------------------------------- */

void initLog4Cplus( pxOrder * order )
{
    basar::Int16 branchno = 0;
    basar::Int32 orderno = 0;
    basar::Int32 customerno = 0;

    if( NULL != order )
    {
        branchno = order->Customer()->Vertriebszentrum();
        orderno = order->KdAuftragNr();
        customerno = order->Customer()->KundenNr();
    }
    libcsc::LoggerConfig config( "aaorderclose.R" );
    config.doConfigure( branchno, orderno, customerno );
}

/* ------------------------------------------------------------------------- */
void resetLogStream( std::stringstream& logstr )
{
    logstr.str(std::string());
}
