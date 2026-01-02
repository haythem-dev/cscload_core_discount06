/******************************************************************************/
/*                                                                            */
/* header  : AufPosRab.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:47:46 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* AufPosRab: Select **********************************************************/

/* AufPosRab::SelList *********************************************************/

retClient Aufposrab_SelList(aufposrabS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Aufposrab_SelList";
    exec sql begin declare section;
    aufposrabS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList0 cursor with hold for
                  select akdauftragposrab.datum,
                     akdauftragposrab.kdauftragnr,
                     akdauftragposrab.posnr,
                     akdauftragposrab.DiscountType,
                     akdauftragposrab.DiscountValuePct,
                     akdauftragposrab.PharmacyGroupId,
                     akdauftragposrab.paymenttargetno,
                     akdauftragposrab.DiscountValPctMan
                from AKDAUFTRAGPOSRAB
                  where akdauftragposrab.datum	 =	:d->DATUM	 and
                        akdauftragposrab.kdauftragnr	 =	:d->KDAUFTRAGNR	
                        order by akdauftragposrab.posnr,akdauftragposrab.paymenttargetno;
        exec sql open CSelList0;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList0" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList0;
        return CheckSql( fun, stError, "%s", "close CSelList0" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList0 into :d->DATUM,
                     :d->KDAUFTRAGNR,
                     :d->POSNR,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTVALUEPCT,
                     :d->PHARMACYGROUPID,
                     :d->PAYMENTTARGETNO,
                     :d->DISCOUNTVALPCTMAN;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList0" )) == IS_ERROR )
        return rc;
    return rc;
}



/* AufPosRab: Insert **********************************************************/



/* AufPosRab: Update **********************************************************/



/* AufPosRab: Select **********************************************************/



/* AufPosRab: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : AuftragWerte.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:47:48 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* AuftragWerte: Select *******************************************************/

/* AuftragWerte::SelWerte *****************************************************/

retClient Auftragwerte_SelWerte(auftragwerteS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Auftragwerte_SelWerte";
    exec sql begin declare section;
    auftragwerteS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kdauftragwerte.kdauftragnr,
                     kdauftragwerte.OrdValFTaxFSDisc,
                     kdauftragwerte.OrdValLTaxFSDisc,
                     kdauftragwerte.OrdValFTaxHFDisc,
                     kdauftragwerte.OrdValLTaxHFDisc,
                     kdauftragwerte.OrdValFTaxRSDisc,
                     kdauftragwerte.OrdValLTaxRSDisc
                into :d->KDAUFTRAGNR,
                     :d->ORDVALFTAXFSDISC,
                     :d->ORDVALLTAXFSDISC,
                     :d->ORDVALFTAXHFDISC,
                     :d->ORDVALLTAXHFDISC,
                     :d->ORDVALFTAXRSDISC,
                     :d->ORDVALLTAXRSDISC
                from KDAUFTRAGWERTE
              where kdauftragwerte.kdauftragnr	 =	:d->KDAUFTRAGNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* AuftragWerte: Insert *******************************************************/



/* AuftragWerte: Update *******************************************************/



/* AuftragWerte: Select *******************************************************/



/* AuftragWerte: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : AuftragWerteAlt.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:47:50 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* AuftragWerteAlt: Select ****************************************************/

/* AuftragWerteAlt::SelWerte **************************************************/

retClient Auftragwertealt_SelWerte(auftragwertealtS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Auftragwertealt_SelWerte";
    exec sql begin declare section;
    auftragwertealtS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select akdauftragwerte.datum,
                     akdauftragwerte.kdauftragnr,
                     akdauftragwerte.OrdValFTaxFSDisc,
                     akdauftragwerte.OrdValLTaxFSDisc,
                     akdauftragwerte.OrdValFTaxHFDisc,
                     akdauftragwerte.OrdValLTaxHFDisc,
                     akdauftragwerte.OrdValFTaxRSDisc,
                     akdauftragwerte.OrdValLTaxRSDisc
                into :d->DATUM,
                     :d->KDAUFTRAGNR,
                     :d->ORDVALFTAXFSDISC,
                     :d->ORDVALLTAXFSDISC,
                     :d->ORDVALFTAXHFDISC,
                     :d->ORDVALLTAXHFDISC,
                     :d->ORDVALFTAXRSDISC,
                     :d->ORDVALLTAXRSDISC
                from AKDAUFTRAGWERTE
              where akdauftragwerte.datum	 =	:d->DATUM	 and
                    akdauftragwerte.kdauftragnr	 =	:d->KDAUFTRAGNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* AuftragWerteAlt: Insert ****************************************************/



/* AuftragWerteAlt: Update ****************************************************/



/* AuftragWerteAlt: Select ****************************************************/



/* AuftragWerteAlt: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckOrderIV.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:47:52 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* CheckOrderIV: Select *******************************************************/



/* CheckOrderIV: Insert *******************************************************/



/* CheckOrderIV: Update *******************************************************/



/* CheckOrderIV: Select *******************************************************/



/* CheckOrderIV: Other ********************************************************/

/* CheckOrderIV::SelKonsig ****************************************************/

retClient Checkorderiv_SelKonsig(checkorderivS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "CheckOrderIV_SelKonsig";
    exec sql begin declare section;
    checkorderivS *d;
    int iID = 0; /* indicator */
    exec sql end declare section;

    d = a;

    exec sql select kdauftragpos.kdauftragnr into :d->KDAUFTRAGNR
       indicator :iID
       from kdauftrag,kdauftragpos,artikelzentral,seporderartgrp where
         kdauftrag.kdauftragnr = :d->KDAUFTRAGNR and
         kdauftragpos.kdauftragnr = kdauftrag.kdauftragnr and
         kdauftragpos.posnr = 1 and
         kdauftragpos.artikel_nr = artikelzentral.artikel_nr and
         kdauftrag.filialnr = seporderartgrp.branchno and
         artikelzentral.konsig_partner_nr = seporderartgrp.manufacturerno and
         seporderartgrp.artgrp = 15;
    if ( (rc=CheckSql( fun, stError, "%s", "select kdauftagnr" )) != IS_OK )
       return rc; 
    else if ( iID < 0 )
    {
       d->KDAUFTRAGNR = 0;
       return 0;
    } 
    return 0;
}

/* CheckOrderIV::SelManu ******************************************************/

retClient Checkorderiv_SelManu(checkorderivS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "CheckOrderIV_SelManu";
    exec sql begin declare section;
    checkorderivS *d;
    int iID = 0; /* indicator */
    exec sql end declare section;

    d = a;

    exec sql select kdauftragpos.kdauftragnr into :d->KDAUFTRAGNR
       indicator :iID
       from kdauftrag,kdauftragpos,artikelzentral,seporderartgrp where
         kdauftrag.kdauftragnr = :d->KDAUFTRAGNR and
         kdauftragpos.kdauftragnr = kdauftrag.kdauftragnr and
         kdauftragpos.posnr = 1 and
         kdauftragpos.artikel_nr = artikelzentral.artikel_nr and
         kdauftrag.filialnr = seporderartgrp.branchno and
         artikelzentral.hersteller_nr = seporderartgrp.manufacturerno and
         seporderartgrp.artgrp = 14;
    if ( (rc=CheckSql( fun, stError, "%s", "select kdauftagnr" )) != IS_OK )
       return rc; 
    else if ( iID < 0 )
    {
       d->KDAUFTRAGNR = 0;
       return 0;
    } 
    return 0;
}



/******************************************************************************/
/*                                                                            */
/* header  : CollectiveOrders.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:47:58 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* CollectiveOrders: Select ***************************************************/



/* CollectiveOrders: Insert ***************************************************/



/* CollectiveOrders: Update ***************************************************/



/* CollectiveOrders: Select ***************************************************/



/* CollectiveOrders: Other ****************************************************/

/* CollectiveOrders::SelCVOrder ***********************************************/

retClient Collectiveorders_SelCVOrder(collectiveordersS *a, tError *stError, bool bIsTrans)
{
    exec sql begin declare section;

    long cvOrderNo;
    char cvKdAuftragStat[17];
    long cvCreateDate;
    long cvDeliveryDate;
    long cvIdfno;
    char cvDeviceName[9];
    char cvTourID[7];
    char cvNameApo[41];
    char cvPLZ[10];
    char cvKdOrderType[3];
    char cvKoType[2];
    char cvBookingType[2];
    int cvRepresentative;
    long cvCntPos;
    long cvCntPosDafue;
    long cvCntAlphaText;
    char cvCustClass[4];
    long cvTimeDEPM;
    int cvSalesCentrumNo;
    long cvCustNo;
    char cvCause[17];
    char cvVIP[1];
    char cvTournee[4];

    int cursorPos;
    int i;

    char sqlStmt[4000];

    exec sql end declare section;

    int anz = 0;
    retClient rc = IS_OK;
    char *fun = "Collectiveorders_SelCVOrder";

    // first time this is called define the sql and the cursor. 
    //The next time the cursor is still defined and can be used.
    if ( a->FETCH_REL == SET_OPEN )
    {
        // The sql will be put together partwise
        if(a->ARTIKEL_NR > 0) //also use kdauftragpos, but not always because there could be performance issues
        {
            sprintf(sqlStmt,"%s", 
            "Select kdauftrag.kdauftragnr, kdauftrag.kdauftragstat, kdauftragereignis.datum, kdauftrag.datumauslieferung, kdauftrag.IdfNr, "
            "kdauftrag.geraetname, kdauftrag.tourid, kunde.nameapo, kunde.postleitzahl, kdauftrag.kdauftragart, "
            "kdauftrag.koart, kdauftrag.buchart, kunde.kdgruppe, kdauftrag.anzpos, kdauftrag.anzposdafue, "
            "kdauftrag.anzalphatext, kunde.kzkdklasse, kdauftrag.zeitendepm, kdauftrag.vertriebszentrumnr, "
            "kdauftrag.KundenNr, kdauftrag.zugrund, kundeschalter.skdvipkunde, kundeschalter.skdtournee "
            "from kdauftrag, kunde, kdauftragereignis, kundeschalter, kdauftragpos where " 
            "kdauftrag.kdauftragstat like '00010000000%' and " 
            "kdauftrag.VertriebszentrumNr = kunde.VertriebszentrumNr and " 
            "kdauftrag.KundenNr = kunde.KundenNr and "
            "kunde.KundenNr = kundeschalter.KundenNr and kunde.vertriebszentrumnr = kundeschalter.vertriebszentrumnr and ");
        }
        else
        {
            sprintf(sqlStmt,"%s", 
            "Select kdauftrag.kdauftragnr, kdauftrag.kdauftragstat, kdauftragereignis.datum, kdauftrag.datumauslieferung, kdauftrag.IdfNr, "
            "kdauftrag.geraetname, kdauftrag.tourid, kunde.nameapo, kunde.postleitzahl, kdauftrag.kdauftragart, "
            "kdauftrag.koart, kdauftrag.buchart, kunde.kdgruppe, kdauftrag.anzpos, kdauftrag.anzposdafue, "
            "kdauftrag.anzalphatext, kunde.kzkdklasse, kdauftrag.zeitendepm, kdauftrag.vertriebszentrumnr, "
            "kdauftrag.KundenNr, kdauftrag.zugrund, kundeschalter.skdvipkunde, kundeschalter.skdtournee "
            "from kdauftrag, kunde, kdauftragereignis, kundeschalter where " 
            "kdauftrag.kdauftragstat like '00010000000%' and " 
            "kdauftrag.VertriebszentrumNr = kunde.VertriebszentrumNr and " 
            "kdauftrag.KundenNr = kunde.KundenNr and "
            "kunde.KundenNr = kundeschalter.KundenNr and kunde.vertriebszentrumnr = kundeschalter.vertriebszentrumnr and ");
        }
        sprintf(sqlStmt,"%s (kdauftrag.ZUGrund[13] = '0' or "
        "(select count(*) from kdauftragpos p, artikelzentral, seporderartgrp where "
        "kdauftrag.kdauftragnr = p.kdauftragnr and "
        "p.artikel_nr = artikelzentral.artikel_nr and "
        "p.posnr = 1 and "
        "kdauftrag.filialnr = seporderartgrp.branchno and "
        "artikelzentral.hersteller_nr = seporderartgrp.manufacturerno and "
        "seporderartgrp.artgrp = 14 ) = 0 ) and ",sqlStmt);
        sprintf(sqlStmt,"%s (kdauftrag.ZUGrund[14] = '0' or "
        "(select count(*) from kdauftragpos p, artikelzentral, seporderartgrp where "
        "kdauftrag.kdauftragnr = p.kdauftragnr and "
        "p.posnr = 1 and "
        "p.artikel_nr = artikelzentral.artikel_nr and "
        "kdauftrag.filialnr = seporderartgrp.branchno and "
        "artikelzentral.konsig_partner_nr = seporderartgrp.manufacturerno and "
        "seporderartgrp.artgrp = 15 ) = 0 ) and ",sqlStmt);

        //Begin to add strings with values. These here are allways needed.
        sprintf(sqlStmt,"%s kdauftrag.FilialNr = %ld and ",sqlStmt,a->FILIALNR);
        sprintf(sqlStmt,"%s kdauftrag.VertriebsZentrumNr = %ld and ",sqlStmt,a->VERTRIEBSZENTRUMNR);

        //do an rtrim for like
        //somewhere several " " are added to fill the string till the max length is reached, 
        //but the like doesnt work if this is done, so remove the unnecessary blanks.
        for(i=strlen(a->KDAUFTRAGART)-1;i>=0;i--)
        {
            if(a->KDAUFTRAGART[i]==' ')
            {
                a->KDAUFTRAGART[i]=0x00;
            } 
            else
            {
                break;
            }
        }
        if(strlen(a->KDAUFTRAGART) > 0)
        {
            if(strcmp(a->KDAUFTRAGART,"CV") == 0)
            {
                // only CV22 (koart, buchart) = not finished CV orders
                sprintf(sqlStmt,"%s kdauftrag.kdauftragart = 'CV' and kdauftrag.koart != 0 and kdauftrag.buchart != 0 and ",sqlStmt);
            }
            else
            {
                sprintf(sqlStmt,"%s kdauftrag.kdauftragart != 'CV' and ",sqlStmt);
            }
        }

        //Add strings with values depending on the user input
        if(a->ERSTELLDATUM != 0)
        {
            sprintf(sqlStmt,"%s kdauftragereignis.datum = %ld and ",sqlStmt,a->ERSTELLDATUM);
        }
        if (a->LIEFERDATUM != 0)
        {
            sprintf(sqlStmt, "%s kdauftrag.datumauslieferung = %ld and ", sqlStmt, a->LIEFERDATUM);
        }

        if(a->KDAUFTRAGNR != 0)
        {
            sprintf(sqlStmt,"%s kdauftrag.kdauftragnr = %ld and ",sqlStmt,a->KDAUFTRAGNR);
        }

        if(a->KUNDENNR != 0)
        {
            sprintf(sqlStmt,"%s kdauftrag.KundenNr = %ld and ",sqlStmt,a->KUNDENNR);
        }

        //do an rtrim for like 
        //somewhere several " " are added to fill the string till the max length is reached, 
        //but the like doesnt work if this is done, so remove the unnecessary blanks.
        for(i=strlen(a->SKDVIPKUNDE)-1;i>=0;i--)
        {
            if(a->SKDVIPKUNDE[i]==' ')
            {
                a->SKDVIPKUNDE[i]=0x00;
            }
            else
            {
                break;
            }
        }
        if(strlen(a->SKDVIPKUNDE) > 0)
        {
            if(strcmp(a->SKDVIPKUNDE,"Y") == 0)
            {
                sprintf(sqlStmt,"%s kundeschalter.skdvipkunde = 1 and ",sqlStmt);
            }
            else
            {
                sprintf(sqlStmt,"%s kundeschalter.skdvipkunde = 0 and ",sqlStmt);
            }
        }

        //do an rtrim for like
        //somewhere several " " are added to fill the string till the max length is reached, 
        //but the like doesnt work if this is done, so remove the unnecessary blanks.
        for(i=strlen(a->KZKDKLASSE)-1;i>=0;i--)
        {
            if(a->KZKDKLASSE[i]==' ')
            {
                a->KZKDKLASSE[i]=0x00;
            }
            else
            {
                break;
            }
        }
        if(strlen(a->KZKDKLASSE) > 0)
        {
            sprintf(sqlStmt,"%s kunde.kzkdklasse like '%s' and ",sqlStmt,a->KZKDKLASSE);
        }

        //do an rtrim for like
        //somewhere several " " are added to fill the string till the max length is reached, 
        //but the like doesnt work if this is done, so remove the unnecessary blanks.
        for(i=strlen(a->POSTLEITZAHL)-1;i>=0;i--)
        {
            if(a->POSTLEITZAHL[i]==' ')
            {
                a->POSTLEITZAHL[i]=0x00;
            }
            else
            {
                break;
            }
        }
        if(strlen(a->POSTLEITZAHL) > 0)
        {
            //Search the first 2 numbers of the PLZ
            sprintf(sqlStmt,"%s substring(kunde.postleitzahl from 1 for 2) = '%s' and ",sqlStmt,a->POSTLEITZAHL);
        }

        if(a->PERSONALNRVERTR > 0)
        {
            sprintf(sqlStmt,"%s kunde.personalnrvertr = %ld and ",sqlStmt,a->PERSONALNRVERTR);
        }

        if(a->ARTIKEL_NR > 0)
        {
            sprintf(sqlStmt,"%s kdauftragpos.artikel_nr = %ld and kdauftragpos.kdauftragnr = kdauftrag.kdauftragnr and ",sqlStmt,a->ARTIKEL_NR);
        }
        // warehouse group is defined in TOURNEE, can be a string, therefore do a rtrim as well
        for (i = strlen(a->SKDTOURNEE) - 1; i >= 0; i--)
        {
            if (a->SKDTOURNEE[i] == ' ')
            {
                a->SKDTOURNEE[i] = 0x00;
            }
            else
            {
                break;
            }
        }
        if (strlen(a->SKDTOURNEE) > 0)
        {
            sprintf(sqlStmt,"%s kundeschalter.skdtournee = '%s' and ",sqlStmt,a->SKDTOURNEE);
        }

        sprintf(sqlStmt,"%s %s",sqlStmt, "kdauftragereignis.kdauftragnr = kdauftrag.kdauftragnr and " 
        "kdauftragereignis.datum||kdauftragereignis.zeit = " 
        "(Select MIN((datum||zeit)) from kdauftragereignis where ereignisart = 1 and " 
        "kdauftragnr = kdauftrag.kdauftragnr) and " 
        "kdauftragereignis.ereignisart = 1 order by ");

        //add order by depending on the user input
        switch(a->ANZPOS)
        {
            case 0:
            {
                sprintf(sqlStmt,"%s kdauftrag.kdauftragnr",sqlStmt);
                break;
            }
            case 1:
            {
                sprintf(sqlStmt,"%s kunde.kzkdklasse, kundeschalter.skdvipkunde",sqlStmt);
                break;
            }
            case 2:
            {
                sprintf(sqlStmt,"%s kunde.personalnrvertr",sqlStmt);
                break;
            }
            case 3:
            {
                sprintf(sqlStmt,"%s kdauftragereignis.datum",sqlStmt);
                break;
            }
            case 4:
            {
                sprintf(sqlStmt,"%s kdauftrag.KundenNr",sqlStmt);
                break;
            }
            case 5:
            {
                sprintf(sqlStmt,"%s kdauftrag.logisticvolume",sqlStmt);
                break;
            }
            case 6:
            {
                sprintf(sqlStmt,"%s kunde.postleitzahl",sqlStmt);
                break;
            }
        }

        // Prepare is needed for dynamic esql
        EXEC SQL PREPARE DynQuery FROM :sqlStmt;

        //declare cursor for later usage
        EXEC SQL declare CVOrder SCROLL CURSOR with hold for DynQuery;

        //open cursor here, so it will be done only one time
        EXEC SQL open CVOrder;

        //error checks
        if ( ( rc=CheckSql( fun, stError, "%s", "open CVOrder" ) ) != IS_OK )
        {
            return rc;
        }
    }

    //when the end is reached, the dade generated header wil call a close
    if ( a->FETCH_REL == SET_CLOSE )
    {
        EXEC SQL close CVOrder;
        return CheckSql( fun, stError, "%s", "close CVOrder" );
    }

    cursorPos = a->ANZ_ERFASST;

    //fetch one data line from the db
    EXEC SQL fetch ABSOLUTE :cursorPos CVOrder into :cvOrderNo, :cvKdAuftragStat, :cvCreateDate, :cvDeliveryDate, :cvIdfno, :cvDeviceName, :cvTourID, 
    :cvNameApo, :cvPLZ, :cvKdOrderType,  :cvKoType, :cvBookingType, :cvRepresentative, :cvCntPos, :cvCntPosDafue, 
    :cvCntAlphaText, :cvCustClass, :cvTimeDEPM, :cvSalesCentrumNo, :cvCustNo, :cvCause, :cvVIP, :cvTournee;

    if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVOrder" ) ) != IS_OK )
    {
        return rc;
    }

    //fill values from the sql to the given struct
    a->KDAUFTRAGNR = cvOrderNo;
    strcpy(a->KDAUFTRAGSTAT, cvKdAuftragStat);
    a->ERSTELLDATUM = cvCreateDate;
    a->LIEFERDATUM = cvDeliveryDate;
    a->IDFNR = cvIdfno;
    strcpy(a->GERAETNAME, cvDeviceName);
    strcpy(a->TOURID, cvTourID);
    strcpy(a->NAMEAPO, cvNameApo);
    strcpy(a->POSTLEITZAHL, cvPLZ);
    strcpy(a->KDAUFTRAGART, cvKdOrderType);
    strcpy(a->KOART, cvKoType);
    strcpy(a->BUCHART, cvBookingType);
    a->PERSONALNRVERTR = cvRepresentative;
    a->ANZPOS = cvCntPos;
    a->ANZPOSDAFUE = cvCntPosDafue;
    a->ANZALPHATEXT = cvCntAlphaText;
    strcpy(a->KZKDKLASSE, cvCustClass);
    a->ZEITENDEPM = cvTimeDEPM;
    a->VERTRIEBSZENTRUMNR = cvSalesCentrumNo;
    a->KUNDENNR = cvCustNo;
    strcpy(a->ZUGRUND, cvCause);
    strcpy(a->SKDVIPKUNDE, cvVIP);
    strcpy(a->SKDTOURNEE, cvTournee);

    return rc;
}

/* CollectiveOrders::SelCVOrderCount ******************************************/

retClient Collectiveorders_SelCVOrderCount(collectiveordersS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

long cvCount;
int cursorPos;
char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Collectiveorders_SelCVOrderCount";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise

  sprintf(sqlStmt, 
  "Select count(*) "
  "from kdauftrag, kunde where " 
  "kdauftrag.kdauftragstat like '00010000000_1%%' and "
  "kdauftrag.vertriebszentrumnr = %ld and "
  "kdauftrag.kundennr = %ld and "
  "kunde.vertriebszentrumnr = kdauftrag.vertriebszentrumnr and "
  "kunde.kundennr = kdauftrag.kundennr", a->VERTRIEBSZENTRUMNR,a->KUNDENNR);

   if(a->KDAUFTRAGNR != 0)
   {
      sprintf(sqlStmt,"%s and kdauftrag.kdauftragnr = %ld ",sqlStmt,a->KDAUFTRAGNR);
   }

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVOrderCount SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVOrderCount;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVOrderCount" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVOrderCount;
    return CheckSql( fun, stError, "%s", "close CVOrderCount" );
}

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE 1 CVOrderCount into :cvCount;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVOrderCount" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->ANZPOS = cvCount;

return rc;
}

/* CollectiveOrders::SelCVOrderDE *********************************************/

retClient Collectiveorders_SelCVOrderDE(collectiveordersS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

long cvOrderNo;
long cvIdfNo;
long cvBranchNo;
char cvTourID[7];
char cvKdOrderType[3];
char cvKoType[2];
char cvBookingType[2];
char cvNameApo[41];
char cvPlace[31];

int cursorPos;

char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Collectiveorders_SelCVOrderDE";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise

  sprintf(sqlStmt,"Select kdauftrag.kdauftragnr, kdauftrag.idfnr, kdauftrag.vertriebszentrumnr, kdauftrag.tourid, "
  "kdauftrag.kdauftragart, kdauftrag.koart, kdauftrag.buchart, kunde.ort, kunde.nameapo "
  "from kdauftrag, kunde where " 
  "kdauftrag.kdauftragstat like '00010000000_1%%' and "
  "kdauftrag.vertriebszentrumnr = %ld and "
  "kdauftrag.kundennr = %ld and "
  "kunde.vertriebszentrumnr = kdauftrag.vertriebszentrumnr and "
  "kunde.kundennr = kdauftrag.kundennr",a->VERTRIEBSZENTRUMNR,a->KUNDENNR);

   if(a->KDAUFTRAGNR != 0)
   {
      sprintf(sqlStmt,"%s and kdauftrag.kdauftragnr = %ld ",sqlStmt,a->KDAUFTRAGNR);
   }

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVOrderDE SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVOrderDE;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVOrderDE" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVOrderDE;
    return CheckSql( fun, stError, "%s", "close CVOrderDE" );
}

cursorPos = a->ANZ_ERFASST;

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE :cursorPos CVOrderDE into :cvOrderNo, :cvIdfNo, :cvBranchNo, :cvTourID, :cvKdOrderType,
:cvKoType, :cvBookingType, :cvPlace, :cvNameApo;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVOrderDE" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->KDAUFTRAGNR = cvOrderNo;
a->IDFNR = cvIdfNo;
a->VERTRIEBSZENTRUMNR = cvBranchNo;
strcpy(a->TOURID,cvTourID);
strcpy(a->KDAUFTRAGART,cvKdOrderType);
strcpy(a->KOART,cvKoType);
strcpy(a->BUCHART,cvBookingType);
strcpy(a->ORT,cvPlace);
strcpy(a->NAMEAPO,cvNameApo);

return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : KNDPPFLAG.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:00 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* KNDPPFLAG: Select **********************************************************/



/* KNDPPFLAG: Insert **********************************************************/



/* KNDPPFLAG: Update **********************************************************/



/* KNDPPFLAG: Select **********************************************************/



/* KNDPPFLAG: Other ***********************************************************/

/* KNDPPFLAG::GetZurueckFlag **************************************************/

retClient Kndppflag_GetZurueckFlag(kndppflagS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

char cvFlag[2];
int cursorPos;
char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Kndppflag_GetZurueckFlag";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise

   sprintf(sqlStmt,"Select skdauftragzurueck from KUNDESCHALTER where kundeschalter.idfnr = %ld and kundeschalter.VertriebszentrumNr = %ld",a->IDFNR,a->VERTRIEBSZENTRUMNR);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery2 FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVGetFlag SCROLL CURSOR with hold for DynQuery2;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVGetFlag;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVGetFlag" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVGetFlag;
    return CheckSql( fun, stError, "%s", "close CVGetFlag" );
}

//fetch one data line from the db
EXEC SQL fetch CVGetFlag into :cvFlag;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVGetFlag" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
strcpy(a->SKDAUFTRAGZURUECK,cvFlag);

return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : PosChange.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:03 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* PosChange: Select **********************************************************/

/* PosChange::SelList *********************************************************/

retClient Poschange_SelList(poschangeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Poschange_SelList";
    exec sql begin declare section;
    poschangeS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList3 cursor with hold for
                  select kdauftragposchange.kdauftragnr,
                     kdauftragposchange.posnr,
                     kdauftragposchange.mengebestellt,
                     kdauftragposchange.mengebestaetigt,
                     kdauftragposchange.menge_alt,
                     kdauftragposchange.swchecked,
                     kunde.nameapo,
                     kunde.VertriebszentrumNr,
                     kdauftrag.InvoiceNumber,
                     artikelzentral.artikel_name,
                     artikelzentral.artikel_langname
                from KDAUFTRAGPOSCHANGE, KDAUFTRAG, ARTIKELZENTRAL, KUNDE, KDAUFTRAGPOS
                  where kdauftragposchange.swchecked	<=	:d->SWCHECKED and
                        kdauftragposchange.kdauftragnr	 =	kdauftrag.kdauftragnr and
                        kdauftragposchange.kdauftragnr	 =	kdauftragpos.kdauftragnr and
                        kdauftragposchange.posnr	 =	kdauftragpos.posnr and
                        kdauftragpos.artikel_nr	 =	artikelzentral.artikel_nr and
                        kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        kunde.VertriebszentrumNr	 =	kdauftrag.VertriebszentrumNr and
                        kunde.KundenNr	 =	kdauftrag.KundenNr
                        order by kunde.nameapo, kdauftragposchange.kdauftragnr, kdauftragposchange.posnr;
        exec sql open CSelList3;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList3" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList3;
        return CheckSql( fun, stError, "%s", "close CSelList3" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList3 into :d->KDAUFTRAGNR,
                     :d->POSNR,
                     :d->MENGEBESTELLT,
                     :d->MENGEBESTAETIGT,
                     :d->MENGE_ALT,
                     :d->SWCHECKED,
                     :d->NAMEAPO,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->INVOICENUMBER,
                     :d->ARTIKEL_NAME,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList3" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PosChange: Insert **********************************************************/



/* PosChange: Update **********************************************************/

/* PosChange::Update **********************************************************/

retClient Poschange_Update(poschangeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Poschange_Update";
    exec sql begin declare section;
    poschangeS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate4 cursor with hold for
              select swchecked
               from KDAUFTRAGPOSCHANGE
              where kdauftragposchange.kdauftragnr	 =	:d->KDAUFTRAGNR	 and
                    kdauftragposchange.posnr	 =	:d->POSNR
              for update;
    exec sql open CUpdate4;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate4" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate4;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate4" ) ) != IS_OK )
            break;
        exec sql update kdauftragposchange set swchecked = :d->SWCHECKED where current of CUpdate4;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate4" ) ) != IS_OK )
            break;
        break;
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            if ( bInTrans )
            {
                if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                    return rc;
            }
        }
    }
    return rc;
}



/* PosChange: Select **********************************************************/



/* PosChange: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PosChangeHist.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:07 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* PosChangeHist: Select ******************************************************/

/* PosChangeHist::SelList *****************************************************/

retClient Poschangehist_SelList(poschangehistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Poschangehist_SelList";
    exec sql begin declare section;
    poschangehistS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList5 cursor with hold for
                  select akdauftragposchang.datum,
                     akdauftragposchang.kdauftragnr,
                     akdauftragposchang.posnr,
                     akdauftragposchang.mengebestellt,
                     akdauftragposchang.mengebestaetigt,
                     akdauftragposchang.menge_alt,
                     akdauftragposchang.swchecked,
                     kunde.nameapo,
                     kunde.VertriebszentrumNr,
                     akdauftrag.InvoiceNumber,
                     artikelzentral.artikel_name,
                     artikelzentral.artikel_langname
                from AKDAUFTRAG, AKDAUFTRAGPOSCHANG, AKDAUFTRAGPOS, ARTIKELZENTRAL, KUNDE
                  where akdauftragposchang.datum	=	:d->DATUM	 and
                        akdauftragposchang.swchecked	<=	:d->SWCHECKED	 and
                        akdauftragposchang.datum	=	akdauftrag.datum	and
                        akdauftragposchang.datum	=	akdauftragpos.datum	and
                        akdauftragposchang.kdauftragnr	 =	akdauftrag.kdauftragnr and
                        akdauftragposchang.kdauftragnr	 =	akdauftragpos.kdauftragnr and
                        akdauftragposchang.posnr	 =	akdauftragpos.posnr and
                        akdauftragpos.artikel_nr	 =	artikelzentral.artikel_nr and
                        kunde.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR	 and
                        kunde.VertriebszentrumNr	 =	akdauftrag.VertriebszentrumNr and
                        kunde.KundenNr	 =	akdauftrag.KundenNr
                        order by akdauftragposchang.datum, kunde.nameapo, akdauftragposchang.kdauftragnr, akdauftragposchang.posnr;
        exec sql open CSelList5;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList5" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList5;
        return CheckSql( fun, stError, "%s", "close CSelList5" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList5 into :d->DATUM,
                     :d->KDAUFTRAGNR,
                     :d->POSNR,
                     :d->MENGEBESTELLT,
                     :d->MENGEBESTAETIGT,
                     :d->MENGE_ALT,
                     :d->SWCHECKED,
                     :d->NAMEAPO,
                     :d->VERTRIEBSZENTRUMNR,
                     :d->INVOICENUMBER,
                     :d->ARTIKEL_NAME,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList5" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PosChangeHist: Insert ******************************************************/



/* PosChangeHist: Update ******************************************************/

/* PosChangeHist::Update ******************************************************/

retClient Poschangehist_Update(poschangehistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Poschangehist_Update";
    exec sql begin declare section;
    poschangehistS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate6 cursor with hold for
              select swchecked
               from AKDAUFTRAGPOSCHANG
              where akdauftragposchang.datum	 =	:d->DATUM	 and
                    akdauftragposchang.kdauftragnr	 =	:d->KDAUFTRAGNR	 and
                    akdauftragposchang.posnr	 =	:d->POSNR
              for update;
    exec sql open CUpdate6;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate6" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate6;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate6" ) ) != IS_OK )
            break;
        exec sql update akdauftragposchang set swchecked = :d->SWCHECKED where current of CUpdate6;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate6" ) ) != IS_OK )
            break;
        break;
    }

    if ( bIsTrans && rc < 0 )
    {
        exec sql rollback work;
        return rc;
    }
    else if ( bIsTrans )
    {
        if ( bIsTrans )
        {
            if ( bInTrans )
            {
                if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                    return rc;
            }
        }
    }
    return rc;
}



/* PosChangeHist: Select ******************************************************/



/* PosChangeHist: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ProLink.cxx                                                      */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:10 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* ProLink: Select ************************************************************/

/* ProLink::SelProLink ********************************************************/

retClient Prolink_SelProLink(prolinkS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Prolink_SelProLink";
    exec sql begin declare section;
    prolinkS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select akdauftragprolink.datum,
                     akdauftragprolink.kdauftragnr,
                     akdauftragprolink.InvoiceNumberPro,
                     akdauftragprolink.InvoiceNumber,
                     akdauftragprolink.DateProforma,
                     akdauftragprolink.kdauftragnrpro
                into :d->DATUM,
                     :d->KDAUFTRAGNR,
                     :d->INVOICENUMBERPRO,
                     :d->INVOICENUMBER,
                     :d->DATEPROFORMA,
                     :d->KDAUFTRAGNRPRO
                from AKDAUFTRAGPROLINK
              where akdauftragprolink.datum	 =	:d->DATUM	 and
                    akdauftragprolink.kdauftragnr	 =	:d->KDAUFTRAGNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ProLink: Insert ************************************************************/

/* ProLink::Insert ************************************************************/

retClient Prolink_Insert(prolinkS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Prolink_Insert";
    exec sql begin declare section;
    prolinkS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into akdauftragprolink (datum,
                     kdauftragnr,
                     InvoiceNumberPro,
                     InvoiceNumber,
                     DateProforma,
                     kdauftragnrpro)
        values (:d->DATUM,
                     :d->KDAUFTRAGNR,
                     :d->INVOICENUMBERPRO,
                     :d->INVOICENUMBER,
                     :d->DATEPROFORMA,
                     :d->KDAUFTRAGNRPRO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert akdauftragprolink" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* ProLink: Update ************************************************************/



/* ProLink: Select ************************************************************/



/* ProLink: Other *************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ProLinkAct.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:48:13 2022                                         */
/* language: ESQL/C                                                           */
/*                                                                            */
/******************************************************************************/

/* INCLUDE ********************************************************************/

#ifndef _GENERATE_INCLUDE_
#define _GENERATE_INCLUDE_
#include <stdio.h>
#include <unistd.h>
exec sql include sqlca;
#include <dadedb.h>
#include <ppgeneric.h>
#include <allg.h>
#endif
#include "auftraginfo.h"

/* ProLinkAct: Select *********************************************************/

/* ProLinkAct::SelProLink *****************************************************/

retClient Prolinkact_SelProLink(prolinkactS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Prolinkact_SelProLink";
    exec sql begin declare section;
    prolinkactS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kdauftragprolink.kdauftragnr,
                     kdauftragprolink.InvoiceNumberPro,
                     kdauftragprolink.InvoiceNumber,
                     kdauftragprolink.DateProforma,
                     kdauftragprolink.kdauftragnrpro
                into :d->KDAUFTRAGNR,
                     :d->INVOICENUMBERPRO,
                     :d->INVOICENUMBER,
                     :d->DATEPROFORMA,
                     :d->KDAUFTRAGNRPRO
                from KDAUFTRAGPROLINK
              where kdauftragprolink.kdauftragnr	 =	:d->KDAUFTRAGNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ProLinkAct: Insert *********************************************************/

/* ProLinkAct::Insert *********************************************************/

retClient Prolinkact_Insert(prolinkactS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Prolinkact_Insert";
    exec sql begin declare section;
    prolinkactS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into kdauftragprolink (kdauftragnr,
                     InvoiceNumberPro,
                     InvoiceNumber,
                     DateProforma,
                     kdauftragnrpro)
        values (:d->KDAUFTRAGNR,
                     :d->INVOICENUMBERPRO,
                     :d->INVOICENUMBER,
                     :d->DATEPROFORMA,
                     :d->KDAUFTRAGNRPRO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert kdauftragprolink" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}



/* ProLinkAct: Update *********************************************************/



/* ProLinkAct: Select *********************************************************/



/* ProLinkAct: Other **********************************************************/



