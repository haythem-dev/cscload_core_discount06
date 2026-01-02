/******************************************************************************/
/*                                                                            */
/* header  : CheckDistress.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:11 2022                                         */
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
#include "controlling.h"

/* CheckDistress: Select ******************************************************/

/* CheckDistress::IsInWork ****************************************************/

retClient Checkdistress_IsInWork(checkdistressS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkdistress_IsInWork";
    exec sql begin declare section;
    checkdistressS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select parameter.filialnr
                into :d->FILIALNR
                from PARAMETER
              where Parameter.filialnr	 =		 :d->FILIALNR	 and
                    Parameter.ProgrammName	 =	"NOTFALL";
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckDistress: Insert ******************************************************/



/* CheckDistress: Update ******************************************************/



/* CheckDistress: Select ******************************************************/



/* CheckDistress: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CstSepOrder.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:15 2022                                         */
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
#include "controlling.h"

/* CstSepOrder: Select ********************************************************/

/* CstSepOrder::SelList *******************************************************/

retClient Cstseporder_SelList(cstseporderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstseporder_SelList";
    exec sql begin declare section;
    cstseporderS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList1 cursor with hold for
                  select cstseporderartgrp.BranchNo,
                     cstseporderartgrp.CustomerNo,
                     cstseporderartgrp.ArtGrp,
                     cstseporderartgrp.kdauftragart,
                     cstseporderartgrp.koart,
                     cstseporderartgrp.buchart,
                     cstseporderartgrp.DeferOrder
                from CSTSEPORDERARTGRP
                  where CstSepOrderArtGrp.BranchNo	 =	:d->BRANCHNO	 and
                        CstSepOrderArtGrp.CustomerNo	 =	:d->CUSTOMERNO;
        exec sql open CSelList1;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList1" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList1;
        return CheckSql( fun, stError, "%s", "close CSelList1" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList1 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->ARTGRP,
                     :d->KDAUFTRAGART,
                     :d->KOART,
                     :d->BUCHART,
                     :d->DEFERORDER;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList1" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CstSepOrder: Insert ********************************************************/

/* CstSepOrder::Insert ********************************************************/

retClient Cstseporder_Insert(cstseporderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Cstseporder_Insert";
    exec sql begin declare section;
    cstseporderS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into cstseporderartgrp (BranchNo,
                     CustomerNo,
                     ArtGrp,
                     kdauftragart,
                     koart,
                     buchart,
                     DeferOrder)
        values (:d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->ARTGRP,
                     :d->KDAUFTRAGART,
                     :d->KOART,
                     :d->BUCHART,
                     :d->DEFERORDER);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert cstseporderartgrp" ) ) != IS_OK )
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



/* CstSepOrder: Update ********************************************************/

/* CstSepOrder::Update ********************************************************/

retClient Cstseporder_Update(cstseporderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Cstseporder_Update";
    exec sql begin declare section;
    cstseporderS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate2 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     ArtGrp,
                     kdauftragart,
                     koart,
                     buchart,
                     DeferOrder
               from CSTSEPORDERARTGRP
              where CstSepOrderArtGrp.BranchNo	 =	:d->BRANCHNO	 and
                    CstSepOrderArtGrp.CustomerNo	 =	:d->CUSTOMERNO	 and
                    CstSepOrderArtGrp.ArtGrp	 =	:d->ARTGRP
              for update;
    exec sql open CUpdate2;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate2" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate2;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate2" ) ) != IS_OK )
            break;
        exec sql update cstseporderartgrp set BranchNo = :d->BRANCHNO,
                     CustomerNo = :d->CUSTOMERNO,
                     ArtGrp = :d->ARTGRP,
                     kdauftragart = :d->KDAUFTRAGART,
                     koart = :d->KOART,
                     buchart = :d->BUCHART,
                     DeferOrder = :d->DEFERORDER where current of CUpdate2;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate2" ) ) != IS_OK )
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



/* CstSepOrder: Select ********************************************************/

/* CstSepOrder::Delete ********************************************************/

retClient Cstseporder_Delete(cstseporderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Cstseporder_Delete";
    exec sql begin declare section;
    cstseporderS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete3 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     ArtGrp,
                     kdauftragart,
                     koart,
                     buchart,
                     DeferOrder
               from CSTSEPORDERARTGRP
              where CstSepOrderArtGrp.BranchNo	 =	:d->BRANCHNO	 and
                    CstSepOrderArtGrp.CustomerNo	 =	:d->CUSTOMERNO	 and
                    CstSepOrderArtGrp.ArtGrp	 =	:d->ARTGRP
              for update;
    exec sql open CDelete3;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete3" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete3;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete3" ) ) != IS_OK )
            break;
        exec sql delete from cstseporderartgrp where current of CDelete3;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete3" ) ) != IS_OK )
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
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc;
}



/* CstSepOrder: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : DealerUmsatz.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:18 2022                                         */
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
#include "controlling.h"

/* DealerUmsatz: Select *******************************************************/

/* DealerUmsatz::SelList ******************************************************/

retClient Dealerumsatz_SelList(dealerumsatzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Dealerumsatz_SelList";
    exec sql begin declare section;
    dealerumsatzS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList4 cursor with hold for
                  select dealervolume.BranchNo,
                     dealervolume.uid,
                     dealervolume.InvoiceNo,
                     dealervolume.OrderNoVSE,
                     dealervolume.OrderNoKSC,
                     dealervolume.DateInvoice,
                     dealervolume.TimeInvoice,
                     dealervolume.InvoiceVolume,
                     dealervolume.Volume1,
                     dealervolume.Volume2,
                     dealervolume.Volume3,
                     dealervolume.Volume4
                from DealerVolume
                  where DealerVolume.BranchNo	 =	:d->BRANCHNO	 and
                        DealerVolume.uid	 =	:d->UID	 and
                        DealerVolume.DateInvoice	>=	:d->DATEINVOICE	 and
                        DealerVolume.DateInvoice	<=	:d->TIMEINVOICE
                        order by DealerVolume.DateInvoice, DealerVolume.TimeInvoice;
        exec sql open CSelList4;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList4" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList4;
        return CheckSql( fun, stError, "%s", "close CSelList4" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList4 into :d->BRANCHNO,
                     :d->UID,
                     :d->INVOICENO,
                     :d->ORDERNOVSE,
                     :d->ORDERNOKSC,
                     :d->DATEINVOICE,
                     :d->TIMEINVOICE,
                     :d->INVOICEVOLUME,
                     :d->VOLUME1,
                     :d->VOLUME2,
                     :d->VOLUME3,
                     :d->VOLUME4;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList4" )) == IS_ERROR )
        return rc;
    return rc;
}



/* DealerUmsatz: Insert *******************************************************/



/* DealerUmsatz: Update *******************************************************/



/* DealerUmsatz: Select *******************************************************/



/* DealerUmsatz: Other ********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ForbiddenWords.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:22 2022                                         */
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
#include "controlling.h"

/* ForbiddenWords: Select *****************************************************/

/* ForbiddenWords::SelWordList ************************************************/

retClient Forbiddenwords_SelWordList(forbiddenwordsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Forbiddenwords_SelWordList";
    exec sql begin declare section;
    forbiddenwordsS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelWordList5 cursor with hold for
                  select forbiddenwords.BranchNo,
                     forbiddenwords.ForbiddenWord,
                     forbiddenwords.DateFrom,
                     forbiddenwords.DateTo
                from FORBIDDENWORDS
                  where ForbiddenWords.BranchNo	 =	:d->BRANCHNO;
        exec sql open CSelWordList5;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelWordList5" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelWordList5;
        return CheckSql( fun, stError, "%s", "close CSelWordList5" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelWordList5 into :d->BRANCHNO,
                     :d->FORBIDDENWORD,
                     :d->DATEFROM,
                     :d->DATETO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelWordList5" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ForbiddenWords::SelWords ***************************************************/

retClient Forbiddenwords_SelWords(forbiddenwordsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Forbiddenwords_SelWords";
    exec sql begin declare section;
    forbiddenwordsS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelWords6 cursor with hold for
                  select forbiddenwords.BranchNo,
                     forbiddenwords.ForbiddenWord,
                     forbiddenwords.DateFrom,
                     forbiddenwords.DateTo
                from FORBIDDENWORDS
                  where ForbiddenWords.BranchNo	 =	:d->BRANCHNO	 and
                        ( ForbiddenWords.DateFrom	 >	:lDate  or
                        ForbiddenWords.DateTo	 <	:lDate );
        exec sql open CSelWords6;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelWords6" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelWords6;
        return CheckSql( fun, stError, "%s", "close CSelWords6" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelWords6 into :d->BRANCHNO,
                     :d->FORBIDDENWORD,
                     :d->DATEFROM,
                     :d->DATETO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelWords6" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ForbiddenWords: Insert *****************************************************/

/* ForbiddenWords::Insert *****************************************************/

retClient Forbiddenwords_Insert(forbiddenwordsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Forbiddenwords_Insert";
    exec sql begin declare section;
    forbiddenwordsS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->FORBIDDENWORD);
    if ( *d->FORBIDDENWORD == '\0' )
        strcpy( d->FORBIDDENWORD, " " );
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into forbiddenwords (BranchNo,
                     ForbiddenWord,
                     DateFrom,
                     DateTo)
        values (:d->BRANCHNO,
                     :d->FORBIDDENWORD,
                     :d->DATEFROM,
                     :d->DATETO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert forbiddenwords" ) ) != IS_OK )
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



/* ForbiddenWords: Update *****************************************************/

/* ForbiddenWords::UpdateWord *************************************************/

retClient Forbiddenwords_UpdateWord(forbiddenwordsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Forbiddenwords_UpdateWord";
    exec sql begin declare section;
    forbiddenwordsS *d;
    exec sql end declare section;

    d = a;

    ppGStripLast(d->FORBIDDENWORD);
    if ( *d->FORBIDDENWORD == '\0' )
        strcpy( d->FORBIDDENWORD, " " );


    exec sql declare CUpdateWord7 cursor with hold for
              select BranchNo,
                     ForbiddenWord,
                     DateFrom,
                     DateTo
               from FORBIDDENWORDS
              where ForbiddenWords.BranchNo	 =	:d->BRANCHNO	 and
                    ForbiddenWords.ForbiddenWord	 =	:d->FORBIDDENWORD
              for update;
    exec sql open CUpdateWord7;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdateWord7" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdateWord7;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdateWord7" ) ) != IS_OK )
            break;
        exec sql update forbiddenwords set BranchNo = :d->BRANCHNO,
                     ForbiddenWord = :d->FORBIDDENWORD,
                     DateFrom = :d->DATEFROM,
                     DateTo = :d->DATETO where current of CUpdateWord7;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdateWord7" ) ) != IS_OK )
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



/* ForbiddenWords: Select *****************************************************/

/* ForbiddenWords::DeleteWord *************************************************/

retClient Forbiddenwords_DeleteWord(forbiddenwordsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Forbiddenwords_DeleteWord";
    exec sql begin declare section;
    forbiddenwordsS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteWord8 cursor with hold for
              select BranchNo,
                     ForbiddenWord,
                     DateFrom,
                     DateTo
               from FORBIDDENWORDS
              where ForbiddenWords.BranchNo	 =	:d->BRANCHNO	 and
                    ForbiddenWords.ForbiddenWord	 =	:d->FORBIDDENWORD
              for update;
    exec sql open CDeleteWord8;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteWord8" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteWord8;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteWord8" ) ) != IS_OK )
            break;
        exec sql delete from forbiddenwords where current of CDeleteWord8;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteWord8" ) ) != IS_OK )
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
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc;
}



/* ForbiddenWords: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : InvoiceNumber.cxx                                                */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:24 2022                                         */
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
#include "controlling.h"

/* InvoiceNumber: Select ******************************************************/

/* InvoiceNumber::GetNumber ***************************************************/

retClient Invoicenumber_GetNumber(invoicenumberS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Invoicenumber_GetNumber";
    exec sql begin declare section;
    invoicenumberS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kdauftrag.kdauftragnr,
                     kdauftrag.InvoiceNumber
                into :d->KDAUFTRAGNR,
                     :d->INVOICENUMBER
                from KDAUFTRAG
              where kdauftrag.kdauftragnr	 =	:d->KDAUFTRAGNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* InvoiceNumber: Insert ******************************************************/



/* InvoiceNumber: Update ******************************************************/



/* InvoiceNumber: Select ******************************************************/



/* InvoiceNumber: Other *******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : InvoiceNumberOld.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:25 2022                                         */
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
#include "controlling.h"

/* InvoiceNumberOld: Select ***************************************************/

/* InvoiceNumberOld::GetNumber ************************************************/

retClient Invoicenumberold_GetNumber(invoicenumberoldS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Invoicenumberold_GetNumber";
    exec sql begin declare section;
    invoicenumberoldS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select akdauftrag.datum,
                     akdauftrag.kdauftragnr,
                     akdauftrag.InvoiceNumber
                into :d->DATUM,
                     :d->KDAUFTRAGNR,
                     :d->INVOICENUMBER
                from AKDAUFTRAG
              where akdauftrag.datum	 =	:d->DATUM	 and
                    akdauftrag.kdauftragnr	 =	:d->KDAUFTRAGNR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* InvoiceNumberOld: Insert ***************************************************/



/* InvoiceNumberOld: Update ***************************************************/



/* InvoiceNumberOld: Select ***************************************************/



/* InvoiceNumberOld: Other ****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : Parameter.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:28 2022                                         */
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
#include "controlling.h"

/* Parameter: Select **********************************************************/

/* Parameter::SelParameter ****************************************************/

retClient Parameter_SelParameter(parameterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Parameter_SelParameter";
    exec sql begin declare section;
    parameterS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select parameter.filialnr,
                     parameter.ProgrammName,
                     parameter.zweck,
                     parameter.parameterName,
                     parameter.Auspraegung,
                     parameter.wert
                into :d->FILIALNR,
                     :d->PROGRAMMNAME,
                     :d->ZWECK,
                     :d->PARAMETERNAME,
                     :d->AUSPRAEGUNG,
                     :d->WERT
                from PARAMETER
              where Parameter.filialnr	 =	:d->FILIALNR	 and
                    Parameter.ProgrammName	 =	:d->PROGRAMMNAME	 and
                    Parameter.zweck	 =	:d->ZWECK	 and
                    Parameter.parameterName	 =	:d->PARAMETERNAME;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* Parameter::SelZweck ********************************************************/

retClient Parameter_SelZweck(parameterS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Parameter_SelZweck";
    exec sql begin declare section;
    parameterS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select parameter.filialnr,
                     parameter.ProgrammName,
                     parameter.zweck,
                     parameter.parameterName,
                     parameter.Auspraegung,
                     parameter.wert
                into :d->FILIALNR,
                     :d->PROGRAMMNAME,
                     :d->ZWECK,
                     :d->PARAMETERNAME,
                     :d->AUSPRAEGUNG,
                     :d->WERT
                from PARAMETER
              where Parameter.filialnr	 =	:d->FILIALNR	 and
                    Parameter.ProgrammName	 =	:d->PROGRAMMNAME	 and
                    Parameter.zweck	 =	:d->ZWECK;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Parameter: Insert **********************************************************/



/* Parameter: Update **********************************************************/



/* Parameter: Select **********************************************************/



/* Parameter: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : SepOrder.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:32 2022                                         */
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
#include "controlling.h"

/* SepOrder: Select ***********************************************************/

/* SepOrder::Sel **************************************************************/

retClient Seporder_Sel(seporderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Seporder_Sel";
    exec sql begin declare section;
    seporderS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select seporderart.BranchNo,
                     seporderart.narcotic,
                     seporderart.coldchain,
                     seporderart.cool08,
                     seporderart.cool20,
                     seporderart.ReserveHospital,
                     seporderart.DeferOrder
                into :d->BRANCHNO,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20,
                     :d->RESERVEHOSPITAL,
                     :d->DEFERORDER
                from SEPORDERART
              where SepOrderArt.BranchNo	 =	:d->BRANCHNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* SepOrder: Insert ***********************************************************/

/* SepOrder::Insert ***********************************************************/

retClient Seporder_Insert(seporderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Seporder_Insert";
    exec sql begin declare section;
    seporderS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into seporderart (BranchNo,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20,
                     ReserveHospital,
                     DeferOrder)
        values (:d->BRANCHNO,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20,
                     :d->RESERVEHOSPITAL,
                     :d->DEFERORDER);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert seporderart" ) ) != IS_OK )
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



/* SepOrder: Update ***********************************************************/

/* SepOrder::Update ***********************************************************/

retClient Seporder_Update(seporderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Seporder_Update";
    exec sql begin declare section;
    seporderS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate14 cursor with hold for
              select BranchNo,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20,
                     ReserveHospital,
                     DeferOrder
               from SEPORDERART
              where SepOrderArt.BranchNo	 =	:d->BRANCHNO
              for update;
    exec sql open CUpdate14;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate14" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate14;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate14" ) ) != IS_OK )
            break;
        exec sql update seporderart set BranchNo = :d->BRANCHNO,
                     narcotic = :d->NARCOTIC,
                     coldchain = :d->COLDCHAIN,
                     cool08 = :d->COOL08,
                     cool20 = :d->COOL20,
                     ReserveHospital = :d->RESERVEHOSPITAL,
                     DeferOrder = :d->DEFERORDER where current of CUpdate14;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate14" ) ) != IS_OK )
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



/* SepOrder: Select ***********************************************************/

/* SepOrder::Delete ***********************************************************/

retClient Seporder_Delete(seporderS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Seporder_Delete";
    exec sql begin declare section;
    seporderS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete15 cursor with hold for
              select BranchNo,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20,
                     ReserveHospital,
                     DeferOrder
               from SEPORDERART
              where SepOrderArt.BranchNo	 =	:d->BRANCHNO
              for update;
    exec sql open CDelete15;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete15" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete15;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete15" ) ) != IS_OK )
            break;
        exec sql delete from seporderart where current of CDelete15;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete15" ) ) != IS_OK )
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
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc;
}



/* SepOrder: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : SepOrderGrp.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:38 2022                                         */
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
#include "controlling.h"

/* SepOrderGrp: Select ********************************************************/

/* SepOrderGrp::Sel ***********************************************************/

retClient Sepordergrp_Sel(sepordergrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Sepordergrp_Sel";
    exec sql begin declare section;
    sepordergrpS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSel16 cursor with hold for
                  select seporderartgrp.BranchNo,
                     seporderartgrp.ArtGrp,
                     seporderartgrp.kdauftragart,
                     seporderartgrp.koart,
                     seporderartgrp.buchart,
                     seporderartgrp.DeferOrder,
                     seporderartgrp.manufacturerno
                from SEPORDERARTGRP
                  where SepOrderArtGrp.BranchNo	 =	:d->BRANCHNO;
        exec sql open CSel16;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSel16" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSel16;
        return CheckSql( fun, stError, "%s", "close CSel16" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSel16 into :d->BRANCHNO,
                     :d->ARTGRP,
                     :d->KDAUFTRAGART,
                     :d->KOART,
                     :d->BUCHART,
                     :d->DEFERORDER,
                     :d->MANUFACTURERNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSel16" )) == IS_ERROR )
        return rc;
    return rc;
}



/* SepOrderGrp: Insert ********************************************************/

/* SepOrderGrp::Insert ********************************************************/

retClient Sepordergrp_Insert(sepordergrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Sepordergrp_Insert";
    exec sql begin declare section;
    sepordergrpS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into seporderartgrp (BranchNo,
                     ArtGrp,
                     kdauftragart,
                     koart,
                     buchart,
                     DeferOrder,
                     manufacturerno)
        values (:d->BRANCHNO,
                     :d->ARTGRP,
                     :d->KDAUFTRAGART,
                     :d->KOART,
                     :d->BUCHART,
                     :d->DEFERORDER,
                     :d->MANUFACTURERNO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert seporderartgrp" ) ) != IS_OK )
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



/* SepOrderGrp: Update ********************************************************/

/* SepOrderGrp::Update ********************************************************/

retClient Sepordergrp_Update(sepordergrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Sepordergrp_Update";
    exec sql begin declare section;
    sepordergrpS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate17 cursor with hold for
              select BranchNo,
                     ArtGrp,
                     kdauftragart,
                     koart,
                     buchart,
                     DeferOrder,
                     manufacturerno
               from SEPORDERARTGRP
              where SepOrderArtGrp.BranchNo	 =	:d->BRANCHNO	 and
                    SepOrderArtGrp.ArtGrp	 =	:d->ARTGRP and
                    SepOrderArtGrp.manufacturerno	 =	:d->MANUFACTURERNO
              for update;
    exec sql open CUpdate17;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate17" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate17;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate17" ) ) != IS_OK )
            break;
        exec sql update seporderartgrp set BranchNo = :d->BRANCHNO,
                     ArtGrp = :d->ARTGRP,
                     kdauftragart = :d->KDAUFTRAGART,
                     koart = :d->KOART,
                     buchart = :d->BUCHART,
                     DeferOrder = :d->DEFERORDER,
                     manufacturerno = :d->MANUFACTURERNO where current of CUpdate17;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate17" ) ) != IS_OK )
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



/* SepOrderGrp: Select ********************************************************/

/* SepOrderGrp::Delete ********************************************************/

retClient Sepordergrp_Delete(sepordergrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Sepordergrp_Delete";
    exec sql begin declare section;
    sepordergrpS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete18 cursor with hold for
              select BranchNo,
                     ArtGrp,
                     kdauftragart,
                     koart,
                     buchart,
                     DeferOrder,
                     manufacturerno
               from SEPORDERARTGRP
              where SepOrderArtGrp.BranchNo	 =	:d->BRANCHNO	 and
                    SepOrderArtGrp.ArtGrp	 =	:d->ARTGRP and
                    SepOrderArtGrp.manufacturerno	 =	:d->MANUFACTURERNO
              for update;
    exec sql open CDelete18;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete18" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete18;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete18" ) ) != IS_OK )
            break;
        exec sql delete from seporderartgrp where current of CDelete18;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete18" ) ) != IS_OK )
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
            retClient rc2;
            if ( bInTrans )
            {
                if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
                    return rc2;
            }
        }
    }
    return rc;
}



/* SepOrderGrp: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : TaskControl.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:40 2022                                         */
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
#include "controlling.h"

/* TaskControl: Select ********************************************************/



/* TaskControl: Insert ********************************************************/



/* TaskControl: Update ********************************************************/



/* TaskControl: Select ********************************************************/



/* TaskControl: Other *********************************************************/

/* TaskControl::CheckTimes ****************************************************/

retClient Taskcontrol_CheckTimes(taskcontrolS *a, tError *stError, bool bIsTrans)
{
#include <time.h>
    retClient rc = IS_OK;
    char *fun = "Taskcontrol_SelList";
    exec sql begin declare section;
    taskcontrolS *d;
    long acttime;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
      time_t long_time;
      time( &long_time );
      acttime = long_time;
      exec sql declare CSelListTC cursor with hold for
                select taskcontrol.VertriebszentrumNr,
                     taskcontrol.ProgrammName,
                     taskcontrol.ZeitUnix
                from TaskControl,Parameter
                where TaskControl.VertriebszentrumNr	 =	:d->VERTRIEBSZENTRUMNR
                      and Parameter.filialnr = TaskControl.VertriebszentrumNr
                      and Parameter.ProgrammName = taskcontrol.ProgrammName
                      and TaskControl.ZeitUnix < :acttime - parameter.wert * 60;
      exec sql open CSelListTC;
      if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListTC" ) ) != IS_OK )
        return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
       if ( bIsTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
      exec sql close CSelListTC;
      return CheckSql( fun, stError, "%s", "close CSelListTC" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelListTC into :d->VERTRIEBSZENTRUMNR,
                     :d->PROGRAMMNAME,
                     :d->ZEITUNIX;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListTC" )) == IS_ERROR )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : Taxes.cxx                                                        */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:42 2022                                         */
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
#include "controlling.h"

/* Taxes: Select **************************************************************/

/* Taxes::SelList *************************************************************/

retClient Taxes_SelList(taxesS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Taxes_SelList";
    exec sql begin declare section;
    taxesS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList19 cursor with hold for
                  select taxrates.TaxLevel,
                     taxrates.salestaxrate,
                     taxrates.DefaultTax
                from TAXRATES
                  where TaxRates.TaxLevel	>=	0
                        order by TaxRates.TaxLevel;
        exec sql open CSelList19;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList19" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList19;
        return CheckSql( fun, stError, "%s", "close CSelList19" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList19 into :d->TAXLEVEL,
                     :d->SALESTAXRATE,
                     :d->DEFAULTTAX;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList19" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Taxes: Insert **************************************************************/



/* Taxes: Update **************************************************************/



/* Taxes: Select **************************************************************/



/* Taxes: Other ***************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : customerordercheck.cxx                                           */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:45 2022                                         */
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
#include "controlling.h"

/* customerordercheck: Select *************************************************/



/* customerordercheck: Insert *************************************************/



/* customerordercheck: Update *************************************************/



/* customerordercheck: Select *************************************************/



/* customerordercheck: Other **************************************************/

/* customerordercheck::SelList ************************************************/

retClient customerordercheck_SelList(customerordercheckS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "CustomerOrderCheck_SelList";
    exec sql begin declare section;
    customerordercheckS* d;
    int iCustomernoVon;
    int iCustomernoBis;
    short sOrderstatusVon;
    short sOrderstatusBis;
    exec sql end declare section;

    d = a;

    if(a->CUSTOMERNO== 0)
    {
	iCustomernoVon = 0;
	iCustomernoBis = 99999999;
    }
    else
    {
	iCustomernoVon  = iCustomernoBis = a->CUSTOMERNO;
    }
    if(a->ORDERSTATUS == -1)
    {
	sOrderstatusVon = 0;
	sOrderstatusBis = 99;
    }
    else
    {
	sOrderstatusVon = sOrderstatusBis = a->ORDERSTATUS;
    }
    if ( a->FETCH_REL == SET_OPEN )
    {
      exec sql declare CSelListCOrderChk cursor with hold for
                select customerordercheck.BranchNo,
                       customerordercheck.CustomerNo,
                       customerordercheck.checkordertime,
                       customerordercheck.orderstatus,
                       kunde.nameapo,
                       kunde.ort,
                       kunde.postleitzahl,
                       kunde.VertriebszentrumNr,
                       kunde.KundenNr
                from customerordercheck, kunde
                where customerordercheck.BranchNo	 =	:d->BRANCHNO	 and
                      customerordercheck.CustomerNo	 >=	:iCustomernoVon	 and
                      customerordercheck.CustomerNo	 <=	:iCustomernoBis	 and
                      customerordercheck.orderstatus	 >=	:sOrderstatusVon and
                      customerordercheck.orderstatus	 <=	:sOrderstatusBis and
                      customerordercheck.checkordertime	 >=	:d->CHECKORDERTIME	 and
                      customerordercheck.BranchNo	 =	kunde.VertriebszentrumNr and
                      customerordercheck.CustomerNo	 =	kunde.KundenNr
		order by  customerordercheck.CustomerNo, customerordercheck.checkordertime;
      exec sql open CSelListCOrderChk ;
      if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListCOrderChk" ) ) != IS_OK )
        return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
       if ( bIsTrans )
       {
          if ( ( rc = Commit( fun, stError ) ) != IS_OK )
             return rc;
       }
      exec sql close CSelListCOrderChk;
      return CheckSql( fun, stError, "%s", "close CSelListCOrderChk" );
    }

    if ( bIsTrans )
    {
       if ( ( rc = Begin( fun, stError ) ) != IS_OK )
          return rc;
    }
    exec sql fetch CSelListCOrderChk into
                    :d->BRANCHNO,
                    :d->CUSTOMERNO,
                    :d->CHECKORDERTIME,
                    :d->ORDERSTATUS,
                    :d->NAMEAPO,
                    :d->ORT,
                    :d->POSTLEITZAHL,
                    :d->VERTRIEBSZENTRUMNR,
                    :d->KUNDENNR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListCOrderChk" )) == IS_ERROR )
        return rc;


    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : lgtext.cxx                                                       */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:54:47 2022                                         */
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
#include "controlling.h"

/* lgtext: Select *************************************************************/

/* lgtext::Sel ****************************************************************/

retClient lgtext_Sel(lgtextS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "lgtext_Sel";
    exec sql begin declare section;
    lgtextS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSel20 cursor with hold for
                  select lgtextae.lgid,
                     lgtextae.appid,
                     lgtextae.grpid,
                     lgtextae.textid,
                     lgtextae.text
                from lgtextae
                  where lgtextae.lgid	 =	:d->LGID	 and
                        lgtextae.appid	 =	:d->APPID
                        order by lgtextae.grpid, lgtextae.textid;
        exec sql open CSel20;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSel20" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSel20;
        return CheckSql( fun, stError, "%s", "close CSel20" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSel20 into :d->LGID,
                     :d->APPID,
                     :d->GRPID,
                     :d->TEXTID,
                     :d->TEXT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSel20" )) == IS_ERROR )
        return rc;
    return rc;
}



/* lgtext: Insert *************************************************************/



/* lgtext: Update *************************************************************/



/* lgtext: Select *************************************************************/



/* lgtext: Other **************************************************************/

/* lgtext::SetLanguage ********************************************************/

retClient lgtext_SetLanguage(lgtextS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
rc = AafilSet_sprache(a, stError);
}



