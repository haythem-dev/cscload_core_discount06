/******************************************************************************/
/*                                                                            */
/* header  : CheckDFReason.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:03 2022                                         */
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
#include "orders.h"

/* CheckDFReason: Select ******************************************************/

/* CheckDFReason::SelEvent ****************************************************/

retClient Checkdfreason_SelEvent(checkdfreasonS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkdfreason_SelEvent";
    exec sql begin declare section;
    checkdfreasonS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select first 1 kdauftragereignis.EventCode, EventReasons.EventDescription
                into :d->EVENTCODE	,:d->EVENTDESCRIPTION
                from KDAUFTRAGEREIGNIS, outer EVENTREASONS
              where kdauftragereignis.kdauftragnr	 =	:d->KDAUFTRAGNR	 and
                    kdauftragereignis.ereignisart	 =	3 and
                    kdauftragereignis.EventCode	 =	EventReasons.EventCode 
                    order by kdauftragereignis.datum desc, kdauftragereignis.zeit desc;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckDFReason: Insert ******************************************************/



/* CheckDFReason: Update ******************************************************/



/* CheckDFReason: Select ******************************************************/



/* CheckDFReason: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckKLReleased.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:05 2022                                         */
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
#include "orders.h"

/* CheckKLReleased: Select ****************************************************/

/* CheckKLReleased::SelReleased ***********************************************/

retClient Checkklreleased_SelReleased(checkklreleasedS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkklreleased_SelReleased";
    exec sql begin declare section;
    checkklreleasedS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select Distinct kdauftragdebtrel.kdauftragnr,
                     kdauftragdebtrel.IsReleased
                into :d->KDAUFTRAGNR,
                     :d->ISRELEASED
                from kdauftragdebtrel
              where kdauftragdebtrel.kdauftragnr	 =	:d->KDAUFTRAGNR	 and
                    kdauftragdebtrel.IsReleased	 =	1;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckKLReleased: Insert ****************************************************/



/* CheckKLReleased: Update ****************************************************/



/* CheckKLReleased: Select ****************************************************/



/* CheckKLReleased: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckOrderNoDD.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:06 2022                                         */
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
#include "orders.h"

/* CheckOrderNoDD: Select *****************************************************/

/* CheckOrderNoDD::CheckNoDD **************************************************/

retClient Checkordernodd_CheckNoDD(checkordernoddS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkordernodd_CheckNoDD";
    exec sql begin declare section;
    checkordernoddS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select cscorderflags.cscorderno
                into :d->CSCORDERNO
                from cscorderflags
              where cscorderflags.cscorderno	 =	:d->CSCORDERNO	 and
                    cscorderflags.nodelayeddelivery	 =	1;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckOrderNoDD: Insert *****************************************************/



/* CheckOrderNoDD: Update *****************************************************/



/* CheckOrderNoDD: Select *****************************************************/



/* CheckOrderNoDD: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckOrderZerod.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:08 2022                                         */
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
#include "orders.h"

/* CheckOrderZerod: Select ****************************************************/

/* CheckOrderZerod::SelAufwert ************************************************/

retClient Checkorderzerod_SelAufwert(checkorderzerodS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkorderzerod_SelAufwert";
    exec sql begin declare section;
    checkorderzerodS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kdauftragwerte.OrdValFTaxFSDisc
+ kdauftragwerte.OrdValFTaxFS
+ kdauftragwerte.OrdValLTaxFSDisc
+ kdauftragwerte.OrdValLTaxFS
+ kdauftragwerte.OrdValFTaxHFDisc
+ kdauftragwerte.OrdValFTaxHF
+ kdauftragwerte.OrdValLTaxHFDisc
+ kdauftragwerte.OrdValLTaxHF
+ kdauftragwerte.OrdValFTaxRSDisc
+ kdauftragwerte.OrdValFTaxRS
+ kdauftragwerte.OrdValLTaxRSDisc
+ kdauftragwerte.OrdValLTaxRS
                into :d->ORDVALFTAXFS
                from KDAUFTRAGWERTE
              where kdauftragwerte.kdauftragnr	 =	:d->KDAUFTRAGNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckOrderZerod: Insert ****************************************************/



/* CheckOrderZerod: Update ****************************************************/



/* CheckOrderZerod: Select ****************************************************/



/* CheckOrderZerod: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckOrderZerodOld.cxx                                           */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:09 2022                                         */
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
#include "orders.h"

/* CheckOrderZerodOld: Select *************************************************/

/* CheckOrderZerodOld::SelAufwert *********************************************/

retClient Checkorderzerodold_SelAufwert(checkorderzerodoldS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkorderzerodold_SelAufwert";
    exec sql begin declare section;
    checkorderzerodoldS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select akdauftragwerte.OrdValFTaxFSDisc
+ akdauftragwerte.OrdValFTaxFS
+ akdauftragwerte.OrdValLTaxFSDisc
+ akdauftragwerte.OrdValLTaxFS
+ akdauftragwerte.OrdValFTaxHFDisc
+ akdauftragwerte.OrdValFTaxHF
+ akdauftragwerte.OrdValLTaxHFDisc
+ akdauftragwerte.OrdValLTaxHF
+ akdauftragwerte.OrdValFTaxRSDisc
+ akdauftragwerte.OrdValFTaxRS
+ akdauftragwerte.OrdValLTaxRSDisc
+ akdauftragwerte.OrdValLTaxRS
                into :d->ORDVALFTAXFS
                from AKDAUFTRAGWERTE
              where akdauftragwerte.datum	 =	:d->DATUM	 and
                    akdauftragwerte.kdauftragnr	 =	:d->KDAUFTRAGNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckOrderZerodOld: Insert *************************************************/



/* CheckOrderZerodOld: Update *************************************************/



/* CheckOrderZerodOld: Select *************************************************/



/* CheckOrderZerodOld: Other **************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckOrderlabel.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:11 2022                                         */
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
#include "orders.h"

/* CheckOrderlabel: Select ****************************************************/



/* CheckOrderlabel: Insert ****************************************************/



/* CheckOrderlabel: Update ****************************************************/



/* CheckOrderlabel: Select ****************************************************/



/* CheckOrderlabel: Other *****************************************************/

/* CheckOrderlabel::SelLabelType **********************************************/

retClient Checkorderlabel_SelLabelType(checkorderlabelS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "CheckOrderlabel_SelLabelType";
exec sql begin declare section;
 checkorderlabelS *d;
 char kdauftragart[3];
 char orderlabel[41];
 char stdorderlabel[41];
 long kundennr;
 short vertriebszentrumnr;
exec sql end declare section;

d = a;

 exec sql select 
 kdauftrag.orderlabel,
 kdauftrag.kdauftragart,
 kdauftrag.kundennr,
 kdauftrag.vertriebszentrumnr
 into
  :orderlabel,
  :kdauftragart,
  :kundennr,
  :vertriebszentrumnr
 from kdauftrag
 where kdauftrag.kdauftragnr = :d->KDAUFTRAGNR;

if ( ( rc=CheckSql( fun, stError, "%s", "select orderlabel" ) ) != IS_OK )
 return rc;

if(orderlabel[0] == ' ')
{
	d->ORDERLABELTYP = 0;
	return 0;
}

 exec sql select auftragartkd.orderidentificatio
 into :stdorderlabel
 from auftragartkd
 where auftragartkd.vertriebszentrumnr = :vertriebszentrumnr
 and auftragartkd.kundennr = :kundennr
 and auftragartkd.kdauftragart = :kdauftragart;

if ( ( rc=CheckSql( fun, stError, "%s", "select standard orderlabel" ) ) != IS_OK )
 return rc;

AllgEntfSpaces( stdorderlabel );
AllgEntfSpaces( orderlabel );
if(!strcmp(stdorderlabel,orderlabel))
{
	d->ORDERLABELTYP = 1;
}
else
{
	d->ORDERLABELTYP = 2;
}
return 0;
}



/******************************************************************************/
/*                                                                            */
/* header  : Driver.cxx                                                       */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:13 2022                                         */
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
#include "orders.h"

/* Driver: Select *************************************************************/

/* Driver::SelAct *************************************************************/

retClient Driver_SelAct(driverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Driver_SelAct";
    exec sql begin declare section;
    driverS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select cstpaymentlist.InvoiceNumber,
                     driverlist.DriverName,
                     cstpaymentlist.DriverID
                into :d->INVOICENUMBER,
                     :d->DRIVERNAME,
                     :d->DRIVERID
                from kdauftrag, CSTPAYMENTLIST, DRIVERLIST
              where kdauftrag.kdauftragnr	 =	:d->KDAUFTRAGNR	 and
                    kdauftrag.VertriebszentrumNr	 =	CstPaymentList.BranchNo and
                    kdauftrag.KundenNr	 =	CstPaymentList.CustomerNo and
                    kdauftrag.InvoiceNumber	 =	CstPaymentList.InvoiceNumber and
                    CstPaymentList.BranchNo	 =	DriverList.BranchNo and
                    CstPaymentList.DriverID	 =	DriverList.DriverID and
                    CstPaymentList.SequenceNo	 =	0 and
                    DriverList.DriverID	 >	0;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* Driver::SelOld *************************************************************/

retClient Driver_SelOld(driverS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Driver_SelOld";
    exec sql begin declare section;
    driverS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select cstpaymentlist.InvoiceNumber,
                     driverlist.DriverName,
                     cstpaymentlist.DriverID
                into :d->INVOICENUMBER,
                     :d->DRIVERNAME,
                     :d->DRIVERID
                from AKDAUFTRAG, CSTPAYMENTLIST, DRIVERLIST
              where akdauftrag.datum	 =	:d->DATUM	 and
                    akdauftrag.kdauftragnr	 =	:d->KDAUFTRAGNR	 and
                    akdauftrag.VertriebszentrumNr	 =	CstPaymentList.BranchNo and
                    akdauftrag.KundenNr	 =	CstPaymentList.CustomerNo and
                    akdauftrag.InvoiceNumber	 =	CstPaymentList.InvoiceNumber and
                    CstPaymentList.BranchNo	 =	DriverList.BranchNo and
                    CstPaymentList.DriverID	 =	DriverList.DriverID and
                    CstPaymentList.SequenceNo	 =	0 and
                    DriverList.DriverID	 >	0;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Driver: Insert *************************************************************/



/* Driver: Update *************************************************************/



/* Driver: Select *************************************************************/



/* Driver: Other **************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : InvoiceNos.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:15 2022                                         */
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
#include "orders.h"

/* InvoiceNos: Select *********************************************************/

/* InvoiceNos::SelList ********************************************************/

retClient Invoicenos_SelList(invoicenosS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Invoicenos_SelList";
    exec sql begin declare section;
    invoicenosS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList7 cursor with hold for
                  select orderremarks.cscorderno,
                     orderremarks.remarktext
                from orderremarks
                  where orderremarks.cscorderno	 =	:d->CSCORDERNO	 and
                        orderremarks.remarktype	 =	4
                        order by orderremarks.textnumber;
        exec sql open CSelList7;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList7" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList7;
        return CheckSql( fun, stError, "%s", "close CSelList7" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList7 into :d->CSCORDERNO,
                     :d->REMARKTEXT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList7" )) == IS_ERROR )
        return rc;
    return rc;
}



/* InvoiceNos: Insert *********************************************************/



/* InvoiceNos: Update *********************************************************/



/* InvoiceNos: Select *********************************************************/



/* InvoiceNos: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : InvoiceNosOld.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:16 2022                                         */
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
#include "orders.h"

/* InvoiceNosOld: Select ******************************************************/

/* InvoiceNosOld::SelList *****************************************************/

retClient Invoicenosold_SelList(invoicenosoldS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Invoicenosold_SelList";
    exec sql begin declare section;
    invoicenosoldS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList8 cursor with hold for
                  select aorderremarks.datum,
                     aorderremarks.cscorderno,
                     aorderremarks.remarktext
                from aorderremarks
                  where aorderremarks.cscorderno	 =	:d->CSCORDERNO	 and
                        aorderremarks.datum	 =	:d->DATUM	 and
                        aorderremarks.remarktype	 =	4
                        order by aorderremarks.textnumber;
        exec sql open CSelList8;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList8" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList8;
        return CheckSql( fun, stError, "%s", "close CSelList8" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList8 into :d->DATUM,
                     :d->CSCORDERNO,
                     :d->REMARKTEXT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList8" )) == IS_ERROR )
        return rc;
    return rc;
}



/* InvoiceNosOld: Insert ******************************************************/



/* InvoiceNosOld: Update ******************************************************/



/* InvoiceNosOld: Select ******************************************************/



/* InvoiceNosOld: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : OrderPeriod.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:29 2022                                         */
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
#include "orders.h"

/* OrderPeriod: Select ********************************************************/



/* OrderPeriod: Insert ********************************************************/



/* OrderPeriod: Update ********************************************************/



/* OrderPeriod: Select ********************************************************/



/* OrderPeriod: Other *********************************************************/

/* OrderPeriod::CheckOPOverLap ************************************************/

retClient Orderperiod_CheckOPOverLap(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

short cvOverLaps;

char sqlStmt[1500];

exec sql end declare section;

retClient rc = IS_OK;
char *fun = "Collectiveorders_CheckOPOverLap";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
  sprintf(sqlStmt,
"select count(*) as overlaps from orderperiod op  "
"inner join orderperiodtime opt on op.id = opt.order_period_id "
"where tourid = '%s' and branchno = %ld and customerno = %ld and weekday = %ld "
"and ((%ld between fromtime and totime) or (%ld between fromtime and totime)); ",
a->TOURID, a->BRANCHNO, a->CUSTOMERNO, a->WEEKDAY, a->FROMTIME, a->TOTIME);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVCheckOPOverLap SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVCheckOPOverLap;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVCheckOPOverLap" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVCheckOPOverLap;
    return CheckSql( fun, stError, "%s", "close CVCheckOPOverLap " );
}

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE 1 CVCheckOPOverLap into :cvOverLaps;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVCheckOPOverLap" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->ANZ_ERFASST = cvOverLaps;

return rc;
}

/* OrderPeriod::DelOPOPTForDay ************************************************/

retClient Orderperiod_DelOPOPTForDay(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_DelOPOPTForDay";

exec sql begin declare section;

orderperiodS *d;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
EXEC SQL BEGIN WORK;

  EXEC SQL
    Delete from orderperiodtime where order_period_id = (Select ID from orderperiod where weekday = :d->WEEKDAY 
           and customerno = :d->CUSTOMERNO and tourid = :d->TOURID and branchno = :d->BRANCHNO);

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "delete OPT") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL
    Delete from orderperiod where weekday = :d->WEEKDAY and customerno = :d->CUSTOMERNO and tourid = :d->TOURID and branchno = :d->BRANCHNO;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "delete OP") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* OrderPeriod::DeleteOPAndOPT ************************************************/

retClient Orderperiod_DeleteOPAndOPT(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_DeleteOPAndOPT";

exec sql begin declare section;

orderperiodS *d;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
EXEC SQL BEGIN WORK;

EXEC SQL
    Delete from orderperiod where id = :d->ID;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "delete OP") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

  EXEC SQL
    Delete from orderperiodtime where order_period_id = :d->ID;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "delete OPT") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* OrderPeriod::DeleteOPForDay ************************************************/

retClient Orderperiod_DeleteOPForDay(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_DelOPForDay";

exec sql begin declare section;

orderperiodS *d;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
EXEC SQL BEGIN WORK;

   EXEC SQL
    Delete from orderperiod where weekday = :d->WEEKDAY and customerno = :d->CUSTOMERNO and tourid = :d->TOURID and branchno = :d->BRANCHNO;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "delete OP") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* OrderPeriod::DeleteOPT *****************************************************/

retClient Orderperiod_DeleteOPT(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_DeleteOPT";

exec sql begin declare section;

orderperiodS *d;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
EXEC SQL BEGIN WORK;

  EXEC SQL
    Delete from orderperiodtime where id = :d->ORDER_PERIOD_ID;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "delete OPT") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* OrderPeriod::DeleteOPTForDay ***********************************************/

retClient Orderperiod_DeleteOPTForDay(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_DelOPTForDay";

exec sql begin declare section;

orderperiodS *d;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
EXEC SQL BEGIN WORK;

  EXEC SQL
    Delete from orderperiodtime where order_period_id = (Select ID from orderperiod where weekday = :d->WEEKDAY 
           and customerno = :d->CUSTOMERNO and tourid = :d->TOURID and branchno = :d->BRANCHNO);

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "delete OPT") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* OrderPeriod::InsertOPAndOPT ************************************************/

retClient Orderperiod_InsertOPAndOPT(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_InsertOPAndOPT";

exec sql begin declare section;

orderperiodS *d;

int serialIDFromInsert;
int idFromExistingParent;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
EXEC SQL BEGIN WORK;

  idFromExistingParent = -1;

  EXEC SQL
	SELECT id
	INTO :idFromExistingParent
	FROM orderperiod
	WHERE customerno = :d->CUSTOMERNO and branchno = :d->BRANCHNO and tourid = :d->TOURID and weekday = :d->WEEKDAY;

  if (idFromExistingParent == 0 || idFromExistingParent == -1 )
  {
	  EXEC SQL
		INSERT INTO orderperiod(customerno,branchno,tourid,weekday)
		VALUES(:d->CUSTOMERNO,:d->BRANCHNO,:d->TOURID,:d->WEEKDAY);

	   //error checks
	   if ( ( rc=CheckSql( fun, stError, "%s", "insert OP") ) != IS_OK )
	   {
		   EXEC SQL ROLLBACK WORK;
		   return rc;
	   }
	  serialIDFromInsert = sqlca.sqlerrd[1];//only possible if no error occured
	  a->ID = serialIDFromInsert;
  }
  else
  {
	serialIDFromInsert = idFromExistingParent;
        a->ID = serialIDFromInsert;
  }

  EXEC SQL
    INSERT INTO orderperiodtime(fromtime, totime, order_period_id, maintime, changedate)
    VALUES(:d->FROMTIME, :d->TOTIME, :serialIDFromInsert, :d->MAINTIME, year(current)*10000+month(current)*100+day(current));

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "insert OPT") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* OrderPeriod::InsertOPT *****************************************************/

retClient Orderperiod_InsertOPT(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_InsertOPT";

exec sql begin declare section;

orderperiodS *d;

int serialIDFromInsert;

exec sql end declare section;

d = a;

if ( a->FETCH_REL == SET_OPEN )
{
  EXEC SQL BEGIN WORK;

  EXEC SQL
    INSERT INTO orderperiodtime(fromtime, totime, order_period_id, maintime, changedate)
    VALUES(:d->FROMTIME, :d->TOTIME, :d->ID, :d->MAINTIME, year(current)*10000+month(current)*100+day(current));

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "insert OPT") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* OrderPeriod::SelConsTime ***************************************************/

retClient Orderperiod_SelConsTime(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

long cvConsTime;

int cursorPos;
long date;

char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "OrderPeriod_SelConsTime";

date = ppGGetDate();

// first time this is called define the sql and the cursor. 
// The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
  sprintf(sqlStmt,
"select constime from tourplanconstime where tourid = '%s' and vertriebszentrumnr = %ld and kundennr = %ld and datumkommi = %ld "
"union "
"select constime from tourconstime where tourid = '%s' and filialnr = %ld and datumkommi = %ld ",
a->TOURID, a->BRANCHNO, a->CUSTOMERNO, date, 
a->TOURID, a->BRANCHNO, date);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVTourConsTime SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVTourConsTime;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVTourConsTime") ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVTourConsTime;
    return CheckSql( fun, stError, "%s", "close CVTourConsTime" );
}

cursorPos = a->ANZ_ERFASST;

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE :cursorPos CVTourConsTime into :cvConsTime;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVTourConsTime" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->CONSTIME = cvConsTime;

return rc;
}

/* OrderPeriod::SelHighKippTime ***********************************************/

retClient Orderperiod_SelHighKippTime(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

long cvKippTime;

int cursorPos;
long date;

char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Collectiveorders_SelHighKippTime";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise
   date = ppGGetDate();

  sprintf(sqlStmt,
"select kippzeit from tourplantag where kundennr = %ld and vertriebszentrumnr=%ld and tm_date=%ld and tourid = '%s' and kippzeit > 0 "
"union "
"select kippzeit from tour where tourid = '%s' and datumkommi=%ld and filialnr=%ld and kippzeit > 0 "
"union "
"select tourenkippzeit from kunde where kundennr = %ld and filialnr=%ld and tourenkippzeit > 0 "
"union "
"select kippzeit from paraauftrager where filialnr = %ld and kippzeit > 0;",
a->CUSTOMERNO, a->BRANCHNO,date,a->TOURID,
a->TOURID,date,a->BRANCHNO, 
a->CUSTOMERNO, a->BRANCHNO, 
a->BRANCHNO);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVSelHighKippTime SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVSelHighKippTime;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVSelHighKippTime" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVSelHighKippTime;
    return CheckSql( fun, stError, "%s", "close CVSelHighKippTime" );
}
cursorPos = a->ANZ_ERFASST;

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE :cursorPos CVSelHighKippTime into :cvKippTime;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVSelHighKippTime" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->KIPPZEIT = cvKippTime;

return rc;
}

/* OrderPeriod::SelOPChildCount ***********************************************/

retClient Orderperiod_SelOPChildCount(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

int cvChildCount;
int cursorPos;
char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Collectiveorders_SelOPChildCount";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise
  sprintf(sqlStmt,
     "select count(id) from orderperiodtime where order_period_id = %ld ",
         a->ID);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVSelOPChildCount SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVSelOPChildCount;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVSelOPChildCount" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVSelOPChildCount;
    return CheckSql( fun, stError, "%s", "close CVSelOPChildCount" );
}

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE 1 CVSelOPChildCount into :cvChildCount;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVSelOPChildCount" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->ANZ_ERFASST = cvChildCount;

return rc;
}

/* OrderPeriod::SelOPWeekdays *************************************************/

retClient Orderperiod_SelOPWeekdays(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

int cvWeekDay;
int cursorPos;
int cvID;
char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Collectiveorders_SelOPWeekdays";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
  // The sql will be put together partwise
  sprintf(sqlStmt,
"Select id, weekday from orderperiod where customerno = %ld and branchno = %ld and tourid = '%s'",
a->CUSTOMERNO, a->BRANCHNO, a->TOURID);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVSelOPWeekdays SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVSelOPWeekdays;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVSelOPWeekdays" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVSelOPWeekdays;
    return CheckSql( fun, stError, "%s", "close CVSelOPWeekdays" );
}
cursorPos = a->ANZ_ERFASST;

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE :cursorPos CVSelOPWeekdays into :cvID, :cvWeekDay;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVSelOPWeekdays" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->WEEKDAY = cvWeekDay;
a->ID = cvID;

return rc;
}

/* OrderPeriod::SelTimesLastTour **********************************************/

retClient Orderperiod_SelTimesLastTour(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

int cvEndTourTime;
int cursorPos;
char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Collectiveorders_SelTimesLastTour";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise
  sprintf(sqlStmt,
     "select totime from orderperiodtime opt "
     "inner join orderperiod op "
     "on op.id = opt.order_period_id "
     "where customerno = %ld and branchno = %ld and tourid = '%s' and weekday = %ld",
         a->CUSTOMERNO, a->BRANCHNO, a->TOURID, a->WEEKDAY);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVSelTimesLastTour SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVSelTimesLastTour;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVSelTimesLastTour" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVSelTimesLastTour;
    return CheckSql( fun, stError, "%s", "close CVSelTimesLastTour" );
}
cursorPos = a->ANZ_ERFASST;

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE :cursorPos CVSelTimesLastTour into :cvEndTourTime;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVSelTimesLastTour" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->TOTIME = cvEndTourTime;

return rc;
}

/* OrderPeriod::SelTourData ***************************************************/

retClient Orderperiod_SelTourData(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

long cvID;
long cvTimeFrom;
long cvTimeTo;
long cvMainTime;
char cvTourID[7];
int cvDay;
int cvOpID;
int cvIdfNo;

int cursorPos;

char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
int i;
retClient rc = IS_OK;
char *fun = "OrderPeriod_SelTourData";

// first time this is called define the sql and the cursor. 
// The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise

  sprintf(sqlStmt,
  "select op.id, op.tourid, op.weekday, op.customerno, opt.fromtime, opt.totime, opt.id, opt.maintime "
  "from orderperiod op "
  "inner join orderperiodtime opt on op.id=opt.order_period_id " 
  "where op.branchno = %ld", a->BRANCHNO);

   if(a->CUSTOMERNO != 0)
   {
      sprintf(sqlStmt,"%s and op.customerno = %ld ",sqlStmt,a->CUSTOMERNO);
   }

   if(a->WEEKDAY != -1)
   {
      sprintf(sqlStmt,"%s and op.weekday = %ld ",sqlStmt,a->WEEKDAY);
   }

   //do an rtrim for like
   //somewhere several " " are added to fill the string till the max length is reached, 
   //but the like doesnt work if this is done, so remove the unnecessary blanks.
   for(i=strlen(a->TOURID)-1;i>=0;i--)
   {
      if(a->TOURID[i]==' ')
      {
	a->TOURID[i]=0x00;
      }
      else
      {
	break;
      }
   }
   if(strlen(a->TOURID) > 0)
   {
      sprintf(sqlStmt,"%s and op.tourid = '%s' ",sqlStmt,a->TOURID);
   }
   
   if(a->ANZ_FAKTUR > 0)
   {
		char orderByClause[250];
		int params[3];
		
		memset(orderByClause,0,250);
		
		//get the three sort params from the decimal mask
		params[0] = a->ANZ_FAKTUR/100;//get first param let intiger cast remove decimal places
		params[1] = a->ANZ_FAKTUR/10%10;//remove last number, then get remaining last number
		params[2] = a->ANZ_FAKTUR%10;//get last number
		
		sprintf(orderByClause," order by ");
		for(i=0;i<3;i++)
		{
			switch(params[i])
			{
				case 1:
					sprintf(orderByClause,"%s Tourid, ", orderByClause);
					break;
				case 2:
					sprintf(orderByClause,"%s weekday, ", orderByClause);
					break;
				case 3:
					sprintf(orderByClause,"%s fromtime, ", orderByClause);
					break;
				case 0:
				default:
					//nothing entered
					break;
			}
		}
		orderByClause[strlen(orderByClause)-2]=0x00;
                sprintf(sqlStmt,"%s %s",sqlStmt,orderByClause);
   }
   else
   {
       sprintf(sqlStmt,"%s order by weekday, fromtime, totime, tourid ",sqlStmt);
   }

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVOrderPeriod SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVOrderPeriod;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVOrderPeriod" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVOrderPeriod;
    return CheckSql( fun, stError, "%s", "close CVOrderPeriod" );
}

cursorPos = a->ANZ_ERFASST;

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE :cursorPos CVOrderPeriod into :cvID, :cvTourID, :cvDay, :cvIdfNo, :cvTimeFrom,
:cvTimeTo, :cvOpID, :cvMainTime;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVOrderPeriod" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->ID = cvID;
a->FROMTIME = cvTimeFrom;
a->TOTIME = cvTimeTo;
strcpy(a->TOURID,cvTourID);
a->WEEKDAY = cvDay;
a->ORDER_PERIOD_ID = cvOpID;
a->MAINTIME = cvMainTime;
a->CUSTOMERNO = cvIdfNo;

return rc;
}

/* OrderPeriod::SelTourForIDF *************************************************/

retClient Orderperiod_SelTourForIDF(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

char cvTourID[7];
char cvActiveFlag[2];
int cursorPos;
char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Collectiveorders_SelTourForIDF";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise
  sprintf(sqlStmt,
"select case when count(tourid) > 1 then '0' else '1' end, tourid from ( "
"select tourid from potentialcustomertours where branchno = %ld and customerno= %ld "
"union all "
"select tourid FROM tourplantagwoche where vertriebszentrumnr= %ld and kundennr= %ld "
") "
"group by tourid;",
a->BRANCHNO, a->CUSTOMERNO, a->BRANCHNO, a->CUSTOMERNO);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVSelTourForIDF SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVSelTourForIDF;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVSelTourForIDF" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVSelTourForIDF;
    return CheckSql( fun, stError, "%s", "close CVSelTourForIDF" );
}
cursorPos = a->ANZ_ERFASST;

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE :cursorPos CVSelTourForIDF into :cvActiveFlag, :cvTourID;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVSelTourForIDF" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
strcpy(a->TOURID, cvTourID);
strcpy(a->TOURINAKTIV, cvActiveFlag);

return rc;
}

/* OrderPeriod::SelWeekdays4Tour **********************************************/

retClient Orderperiod_SelWeekdays4Tour(orderperiodS *a, tError *stError, bool bIsTrans)
{
exec sql begin declare section;

int cvWeekDay;
int cursorPos;
char sqlStmt[1500];

exec sql end declare section;

int anz = 0;
retClient rc = IS_OK;
char *fun = "Collectiveorders_SelWeekdays4Tour";

// first time this is called define the sql and the cursor. 
//The next time the cursor is still defined and can be used.
if ( a->FETCH_REL == SET_OPEN )
{
   // The sql will be put together partwise
  sprintf(sqlStmt,
"select distinct(weekday) from tourplantagwoche where kundennr = %ld and vertriebszentrumnr = %ld and tourid = '%s'",
a->CUSTOMERNO, a->BRANCHNO, a->TOURID);

   // Prepare is needed for dynamic esql
   EXEC SQL PREPARE DynQuery FROM :sqlStmt;

   //declare cursor for later usage
   EXEC SQL declare CVSelWeekdays4Tour SCROLL CURSOR with hold for DynQuery;

   //open cursor here, so it will be done only one time
   EXEC SQL open CVSelWeekdays4Tour;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "open CVSelWeekdays4Tour" ) ) != IS_OK )
   {
      return rc;
   }
}

//when the end is reached, the dade generated header wil call a close
if ( a->FETCH_REL == SET_CLOSE )
{
    EXEC SQL close CVSelWeekdays4Tour;
    return CheckSql( fun, stError, "%s", "close CVSelWeekdays4Tour" );
}
cursorPos = a->ANZ_ERFASST;

//fetch one data line from the db
EXEC SQL fetch ABSOLUTE :cursorPos CVSelWeekdays4Tour into :cvWeekDay;

if ( ( rc=CheckSql( fun, stError, "%s", "fetch CVSelWeekdays4Tour" ) ) != IS_OK )
{
    return rc;
}

//fill values from the sql to the given struct
a->WEEKDAY = cvWeekDay;

return rc;
}

/* OrderPeriod::UpdateTime ****************************************************/

retClient Orderperiod_UpdateTime(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_UpdateTime";

exec sql begin declare section;

orderperiodS *d;
int cursorPos;
int idFromExistingParent;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
  EXEC SQL BEGIN WORK;
  
  idFromExistingParent = -1;

  EXEC SQL
	SELECT id
	INTO :idFromExistingParent
	FROM orderperiod
	WHERE customerno = :d->CUSTOMERNO and branchno = :d->BRANCHNO and tourid = :d->TOURID and weekday = :d->WEEKDAY;
	
  if( idFromExistingParent == 0 || idFromExistingParent == -1 )
  {
	  EXEC SQL
		UPDATE orderperiod 
		SET tourid = :d->TOURID, weekday = :d->WEEKDAY
		WHERE id = :d->ID;

	   //error checks
	   if ( ( rc=CheckSql( fun, stError, "%s", "Update OrderPeriod") ) != IS_OK )
	   {
		   EXEC SQL ROLLBACK WORK;
		   return rc;
	   }
  }
  else
  {
	d->ID = idFromExistingParent;
  }
  
  EXEC SQL
    UPDATE orderperiodtime 
    SET fromtime = :d->FROMTIME, totime = :d->TOTIME, maintime = :d->MAINTIME, changedate = year(current)*10000+month(current)*100+day(current)
    WHERE order_period_id = :d->ID;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "Update OrderPeriodTime") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}

/* OrderPeriod::UpdateTimeSingle **********************************************/

retClient Orderperiod_UpdateTimeSingle(orderperiodS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "OrderPeriod_UpdateTimeSingle";

exec sql begin declare section;

orderperiodS *d;
int cursorPos;
int idFromExistingParent;

exec sql end declare section;

d = a;

//SO that the sql wont be called twice upon closecorsor which gets called automatically
if ( a->FETCH_REL == SET_OPEN )
{
  EXEC SQL BEGIN WORK;
  
  EXEC SQL
    UPDATE orderperiodtime 
    SET fromtime = :d->FROMTIME, totime = :d->TOTIME, maintime = :d->MAINTIME, changedate = year(current)*10000+month(current)*100+day(current)
    WHERE id = :d->ORDER_PERIOD_ID;

   //error checks
   if ( ( rc=CheckSql( fun, stError, "%s", "UpdateTimeSingle") ) != IS_OK )
   {
       EXEC SQL ROLLBACK WORK;
       return rc;
   }

   EXEC SQL COMMIT WORK;
}
return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : OriginTypeSettingsPf.cxx                                         */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:34 2022                                         */
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
#include "orders.h"

/* OriginTypeSettingsPf: Select ***********************************************/

/* OriginTypeSettingsPf::SelList **********************************************/

retClient Origintypesettingspf_SelList(origintypesettingspfS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Origintypesettingspf_SelList";
    exec sql begin declare section;
    origintypesettingspfS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList9 cursor with hold for
                  select origintypesettings.OriginType,
                     origintypesettings.SettingActivated,
                     oeorigintypes.OriginDevice,
                     origintypesettings.BranchNo,
                     origintypesettings.IsOrderConsolidation,
                     origintypesettings.EndOfOrderCons,
                     origintypesettings.OrderConsDuration
                from ORIGINTYPESETTINGS, OEORIGINTYPES
                  where OriginTypeSettings.BranchNo	 =	:d->BRANCHNO	 and
                        OriginTypeSettings.OriginType	 =	OEOriginTypes.OriginType;
        exec sql open CSelList9;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList9" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList9;
        return CheckSql( fun, stError, "%s", "close CSelList9" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList9 into :d->ORIGINTYPE,
                     :d->SETTINGACTIVATED,
                     :d->ORIGINDEVICE,
                     :d->BRANCHNO,
                     :d->ISORDERCONSOLIDATION,
                     :d->ENDOFORDERCONS,
                     :d->ORDERCONSDURATION;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList9" )) == IS_ERROR )
        return rc;
    return rc;
}



/* OriginTypeSettingsPf: Insert ***********************************************/

/* OriginTypeSettingsPf::Insert ***********************************************/

retClient Origintypesettingspf_Insert(origintypesettingspfS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Origintypesettingspf_Insert";
    exec sql begin declare section;
    origintypesettingspfS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into origintypesettings (OriginType,
                     SettingActivated,
                     BranchNo,
                     IsOrderConsolidation,
                     EndOfOrderCons,
                     OrderConsDuration)
        values (:d->ORIGINTYPE,
                     :d->SETTINGACTIVATED,
                     :d->BRANCHNO,
                     :d->ISORDERCONSOLIDATION,
                     :d->ENDOFORDERCONS,
                     :d->ORDERCONSDURATION);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert origintypesettings" ) ) != IS_OK )
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



/* OriginTypeSettingsPf: Update ***********************************************/

/* OriginTypeSettingsPf::Update ***********************************************/

retClient Origintypesettingspf_Update(origintypesettingspfS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Origintypesettingspf_Update";
    exec sql begin declare section;
    origintypesettingspfS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate10 cursor with hold for
              select OriginType,
                     SettingActivated,
                     BranchNo,
                     IsOrderConsolidation,
                     EndOfOrderCons,
                     OrderConsDuration
               from ORIGINTYPESETTINGS
              where OriginTypeSettings.BranchNo	 =	:d->BRANCHNO	 and
                    OriginTypeSettings.OriginType	 =	:d->ORIGINTYPE
              for update;
    exec sql open CUpdate10;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate10" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate10;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate10" ) ) != IS_OK )
            break;
        exec sql update origintypesettings set OriginType = :d->ORIGINTYPE,
                     SettingActivated = :d->SETTINGACTIVATED,
                     BranchNo = :d->BRANCHNO,
                     IsOrderConsolidation = :d->ISORDERCONSOLIDATION,
                     EndOfOrderCons = :d->ENDOFORDERCONS,
                     OrderConsDuration = :d->ORDERCONSDURATION where current of CUpdate10;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate10" ) ) != IS_OK )
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



/* OriginTypeSettingsPf: Select ***********************************************/

/* OriginTypeSettingsPf::Delete ***********************************************/

retClient Origintypesettingspf_Delete(origintypesettingspfS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Origintypesettingspf_Delete";
    exec sql begin declare section;
    origintypesettingspfS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete11 cursor with hold for
              select OriginType,
                     SettingActivated,
                     BranchNo,
                     IsOrderConsolidation,
                     EndOfOrderCons,
                     OrderConsDuration
               from ORIGINTYPESETTINGS
              where OriginTypeSettings.BranchNo	 =	:d->BRANCHNO	 and
                    OriginTypeSettings.OriginType	 =	:d->ORIGINTYPE
              for update;
    exec sql open CDelete11;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete11" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete11;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete11" ) ) != IS_OK )
            break;
        exec sql delete from origintypesettings where current of CDelete11;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete11" ) ) != IS_OK )
            break;
        if ( ( iTrans++ % 500 ) == 0 )
        {
            if ( bIsTrans )
            {
                if ( bInTrans )
                {
                    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                        return rc;
                }
            }
            if ( bIsTrans )
            {
                if ( ( rc = Begin( fun, stError ) ) != IS_OK )
                    return rc;
                bInTrans = true;
            }
        }
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
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}



/* OriginTypeSettingsPf: Other ************************************************/

/* OriginTypeSettingsPf::SelListNotDefined ************************************/

retClient Origintypesettingspf_SelListNotDefined(origintypesettingspfS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Origintypesettingspf_SelListNotDefined";
    exec sql begin declare section;
    origintypesettingspfS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListNotDefined1 cursor with hold for
                select oeorigintypes.OriginType,
                     oeorigintypes.OriginDevice
                from OEORIGINTYPES
                left join ORIGINTYPESETTINGS
                     on OriginTypeSettings.BranchNo = :d->BRANCHNO
                     and OriginTypeSettings.OriginType = OEOriginTypes.OriginType
                where OriginTypeSettings.OriginType is null
                order by oeorigintypes.OriginType;
        exec sql open CSelListNotDefined1;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListNotDefined1" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListNotDefined1;
        return CheckSql( fun, stError, "%s", "close CSelListNotDefined1" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListNotDefined1 into :d->ORIGINTYPE,
                     :d->ORIGINDEVICE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListNotDefined1" )) == IS_ERROR )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : RemarkTypes.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:35 2022                                         */
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
#include "orders.h"

/* RemarkTypes: Select ********************************************************/

/* RemarkTypes::SelList *******************************************************/

retClient Remarktypes_SelList(remarktypesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Remarktypes_SelList";
    exec sql begin declare section;
    remarktypesS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList12 cursor with hold for
                  select orderremarktypes.remarktype,
                     orderremarktypes.remarkname
                from orderremarktypes
                  where orderremarktypes.remarktype	>=	0
                        order by orderremarktypes.remarktype;
        exec sql open CSelList12;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList12" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList12;
        return CheckSql( fun, stError, "%s", "close CSelList12" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList12 into :d->REMARKTYPE,
                     :d->REMARKNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList12" )) == IS_ERROR )
        return rc;
    return rc;
}



/* RemarkTypes: Insert ********************************************************/



/* RemarkTypes: Update ********************************************************/



/* RemarkTypes: Select ********************************************************/



/* RemarkTypes: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : SpecialNumbers.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:37 2022                                         */
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
#include "orders.h"

/* SpecialNumbers: Select *****************************************************/

/* SpecialNumbers::SelNumber **************************************************/

retClient Specialnumbers_SelNumber(specialnumbersS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Specialnumbers_SelNumber";
    exec sql begin declare section;
    specialnumbersS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select orderrelationno.cscorderno,
                     orderrelationno.RelationNoType,
                     orderrelationno.RelationNo
                into :d->CSCORDERNO,
                     :d->RELATIONNOTYPE,
                     :d->RELATIONNO
                from orderrelationno
              where OrderRelationNo.cscorderno	 =	:d->CSCORDERNO	 and
                    OrderRelationNo.RelationNoType	 =	:d->RELATIONNOTYPE;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* SpecialNumbers: Insert *****************************************************/



/* SpecialNumbers: Update *****************************************************/



/* SpecialNumbers: Select *****************************************************/



/* SpecialNumbers: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : SpecialNumbersOld.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:59:39 2022                                         */
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
#include "orders.h"

/* SpecialNumbersOld: Select **************************************************/

/* SpecialNumbersOld::SelNumber ***********************************************/

retClient Specialnumbersold_SelNumber(specialnumbersoldS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Specialnumbersold_SelNumber";
    exec sql begin declare section;
    specialnumbersoldS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select aorderrelationno.date,
                     aorderrelationno.cscorderno,
                     aorderrelationno.RelationNoType,
                     aorderrelationno.RelationNo
                into :d->DATE,
                     :d->CSCORDERNO,
                     :d->RELATIONNOTYPE,
                     :d->RELATIONNO
                from aorderrelationno
              where AOrderRelationNo.cscorderno	 =	:d->CSCORDERNO	 and
                    AOrderRelationNo.RelationNoType	 =	:d->RELATIONNOTYPE and
                    AOrderRelationNo.date	 =	:d->DATE;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* SpecialNumbersOld: Insert **************************************************/



/* SpecialNumbersOld: Update **************************************************/



/* SpecialNumbersOld: Select **************************************************/



/* SpecialNumbersOld: Other ***************************************************/



