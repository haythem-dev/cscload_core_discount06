/*(c)
 ********************* PHARMX Customer Order Entry Server *********************


    Embedded SQL for C application


    FILE: tdiscount.c (.sqc)

    Database functions




    FUNCTIONS:

        pxDiscountStartBrowse  declare and open Cursor
        pxDiscountGetNext      get next record
        pxDiscountEndBrowse    close cursor
        pxDiscountRead         get one record
        pxDiscountReadLock     get one record with lock
        pxDiscountInsert       Insert record
        pxDiscountUpdate       Update record
        pxDiscountDelete       Delete record


REVISION HISTORY

25 Jun 2004 V1.00 REV 00 written by Ysbrand Bouma

*/


#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <pxrecord.h>       /* all record structures */
#include "pxdbfunc.h"
#include "pxdbxx.h"
#include "ndefs.h"
#include "tpromotions.h"
#include <pxenv.h>
#include <tdiscount.h>
#include <keys.h>

/* Global variables */
extern int  functionnr;

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountStartBrowse                                   */
/*                                                                   */
/*      Declare and Open a Cursor   (general)                        */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxDiscountStartBrowse
(
     struct tDISCOUNT* record,
     int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNT * recordp;
#ifdef MCtdiscount
    char matchcode[20];
#endif
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNT*10+F_StartBrowse;
    recordp = (struct C_DISCOUNT *) record;

    if (!(sizeof(struct C_DISCOUNT) == sizeof(struct tDISCOUNT)))
       return cDBXR_DEFINITION;


#ifdef MCtdiscount
    strcpy(matchcode,recordp->MCtdiscount);
    while(matchcode[strlen(matchcode)-1] == ' ')
          matchcode[strlen(matchcode)-1] = 0;
    strcat(matchcode,"%");
#endif

#ifndef pxDATABASE_INFORMIX
    EXEC SQL SET CURSORTYPE CUR_BROWSE;
#endif

    EXEC SQL DECLARE C1 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    DWtdiscount
    and  CUSTOMERNO = 0
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C0 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C2 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where BRANCHNO     = :recordp->BRANCHNO
    and   ARTICLENO    = :recordp->ARTICLENO
    and   DISCOUNTTYPE = :recordp->DISCOUNTTYPE
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C3 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNT.DISCOUNTGRPNO    = :recordp->DISCOUNTGRPNO
    and  (DISCOUNT.CUSTOMERNO       = :recordp->CUSTOMERNO
    or   (DISCOUNT.PHARMACYGROUPID  = '000'
    and   DISCOUNT.CUSTOMERNO       =  0)
    or    DISCOUNT.PHARMACYGROUPID in (SELECT CUSTOMERPHARMACYGR.PHARMACYGROUPID
    from  CUSTOMERPHARMACYGR
    where DISCOUNT.BRANCHNO         = CUSTOMERPHARMACYGR.BRANCHNO
    and   CUSTOMERPHARMACYGR.CUSTOMERNO  = :recordp->CUSTOMERNO))
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C4 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT, CUSTOMERPHARMACYGR
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = :recordp->ARTICLENO
	and   DISCOUNT.DISCOUNTGRPNO   = 0
	and   DISCOUNT.MANUFACTURERNO  = 0
    and   CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO
    and   DISCOUNT.BRANCHNO        = CUSTOMERPHARMACYGR.BRANCHNO
    and   DISCOUNT.PHARMACYGROUPID = CUSTOMERPHARMACYGR.PHARMACYGROUPID
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C5 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where BRANCHNO        = :recordp->BRANCHNO
    and   ARTICLENO       = :recordp->ARTICLENO
    and   DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
    and   PHARMACYGROUPID = :recordp->PHARMACYGROUPID
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C6 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where BRANCHNO        = :recordp->BRANCHNO
    and   ARTICLENO       = :recordp->ARTICLENO
    and   CUSTOMERNO      = :recordp->CUSTOMERNO
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


    EXEC SQL DECLARE C7 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where BRANCHNO        = :recordp->BRANCHNO
    and   CUSTOMERNO      = :recordp->CUSTOMERNO
    and   MANUFACTURERNO  = :recordp->MANUFACTURERNO
    and   DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
    and   DISCOUNTGRPNO   = :recordp->DISCOUNTGRPNO
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


    EXEC SQL DECLARE C8 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from ARTICLEGROUP INNER JOIN DISCOUNT ON DISCOUNT.ARTCATEGORYNO = ARTICLEGROUP.ARTCATEGORYNO
    where ARTICLEGROUP.ARTICLENO    = :recordp->ARTICLENO
    and   DISCOUNT.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNT.CUSTOMERNO       = :recordp->CUSTOMERNO
    and   DISCOUNT.DISCOUNTTYPE     = :recordp->DISCOUNTTYPE
    and   DISCOUNT.DISCOUNTGRPNO    = :recordp->DISCOUNTGRPNO
    and   DISCOUNT.PROMOTION_NO    = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


    EXEC SQL DECLARE C9 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where BRANCHNO        = :recordp->BRANCHNO
    and   CUSTOMERNO      = :recordp->CUSTOMERNO
    and   DISCOUNT.ARTICLENO = 0
    and   MANUFACTURERNO  = 0
    and   DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
    and   DISCOUNTGRPNO   = :recordp->DISCOUNTGRPNO
    and   DISCOUNT.ARTCATEGORYNO    = 0
    and   DISCOUNT.PROMOTION_NO    = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


   EXEC SQL DECLARE C10 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
        from CUSTOMERPHARMACYGR INNER JOIN DISCOUNT ON DISCOUNT.BRANCHNO=CUSTOMERPHARMACYGR.BRANCHNO and DISCOUNT.PHARMACYGROUPID=CUSTOMERPHARMACYGR.PHARMACYGROUPID
        where CUSTOMERPHARMACYGR.BRANCHNO    = :recordp->BRANCHNO
        and   CUSTOMERPHARMACYGR.CUSTOMERNO  = :recordp->CUSTOMERNO
    and   DISCOUNT.ARTICLENO                 = :recordp->ARTICLENO
    and   DISCOUNT.DISCOUNTTYPE              = :recordp->DISCOUNTTYPE
    and   DISCOUNT.DISCOUNTGRPNO             = :recordp->DISCOUNTGRPNO
    and   MANUFACTURERNO                     = :recordp->MANUFACTURERNO
    and   DISCOUNT.ARTCATEGORYNO             = 0
    and   DISCOUNT.PROMOTION_NO              = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


    EXEC SQL DECLARE C11 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
        inner join DISCOUNTGRP ON DISCOUNTGRP.BRANCHNO = DISCOUNT.BRANCHNO and DISCOUNTGRP.DISCOUNTGRPNO = DISCOUNT.DISCOUNTGRPNO
        inner join DISCOUNTGRPMEM ON DISCOUNTGRPMEM.BRANCHNO = DISCOUNT.BRANCHNO and DISCOUNTGRPMEM.DISCOUNTGRPNO = DISCOUNT.DISCOUNTGRPNO
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = 0
    and   DISCOUNT.CUSTOMERNO      = :recordp->CUSTOMERNO
    and   DISCOUNT.DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
        and   DISCOUNTGRP.DISCOUNTGRPTYPE = 1
        and   DISCOUNTGRPMEM.ARTICLENO = :recordp->ARTICLENO
    and (DISCOUNT.ARTCATEGORYNO=0 or DISCOUNT.ARTCATEGORYNO in (SELECT artcategoryno from articlegroup where ARTICLENO= :recordp->ARTICLENO))
    and   DISCOUNT.PROMOTION_NO    = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C12 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
        inner join DISCOUNTGRP ON DISCOUNTGRP.BRANCHNO = DISCOUNT.BRANCHNO and DISCOUNTGRP.DISCOUNTGRPNO = DISCOUNT.DISCOUNTGRPNO
        inner join DISCOUNTGRPMEM ON DISCOUNTGRPMEM.BRANCHNO = DISCOUNT.BRANCHNO and DISCOUNTGRPMEM.DISCOUNTGRPNO = DISCOUNT.DISCOUNTGRPNO
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = 0
    and   DISCOUNT.DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
        and   DISCOUNTGRP.DISCOUNTGRPTYPE = 2
        and   DISCOUNTGRPMEM.ARTICLENO = :recordp->ARTICLENO
        and   DISCOUNT.CUSTOMERNO= :recordp->CUSTOMERNO
        and   DISCOUNT.PHARMACYGROUPID='000'
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


    EXEC SQL DECLARE C13 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = :recordp->ARTICLENO
    and   DISCOUNT.CUSTOMERNO      = 0
    and   DISCOUNT.DISCOUNTSPEC    = 10
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C14 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
        inner join DISCOUNTGRP ON DISCOUNTGRP.BRANCHNO = DISCOUNT.BRANCHNO and DISCOUNTGRP.DISCOUNTGRPNO = DISCOUNT.DISCOUNTGRPNO
        inner join DISCOUNTGRPMEM ON DISCOUNTGRPMEM.BRANCHNO = DISCOUNT.BRANCHNO and DISCOUNTGRPMEM.DISCOUNTGRPNO = DISCOUNT.DISCOUNTGRPNO
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = 0
    and   DISCOUNT.DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
        and   DISCOUNTGRP.DISCOUNTGRPTYPE = 2
        and   DISCOUNTGRPMEM.ARTICLENO = :recordp->ARTICLENO
        and   DISCOUNT.CUSTOMERNO= 0
        and   (DISCOUNT.PHARMACYGROUPID='000' or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C15 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   (DISCOUNT.ARTICLENO=0 or DISCOUNT.ARTICLENO= :recordp->ARTICLENO)
    and   DISCOUNT.DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
    and   DISCOUNT.MANUFACTURERNO  = :recordp->MANUFACTURERNO
        and   DISCOUNT.CUSTOMERNO      = :recordp->CUSTOMERNO
        and   (DISCOUNT.PHARMACYGROUPID='000' or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
    and (DISCOUNT.ARTCATEGORYNO=0 or DISCOUNT.ARTCATEGORYNO in (SELECT artcategoryno from articlegroup where ARTICLENO= :recordp->ARTICLENO))
    and   DISCOUNT.PROMOTION_NO    = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C16 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   (DISCOUNT.ARTICLENO=0 or DISCOUNT.ARTICLENO= :recordp->ARTICLENO)
    and   DISCOUNT.DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
    and   DISCOUNT.MANUFACTURERNO  = :recordp->MANUFACTURERNO
        and   DISCOUNT.CUSTOMERNO      = 0
        and   (DISCOUNT.PHARMACYGROUPID='000' or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
    and (DISCOUNT.ARTCATEGORYNO=0 or DISCOUNT.ARTCATEGORYNO in (SELECT artcategoryno from articlegroup where ARTICLENO= :recordp->ARTICLENO))
    and   DISCOUNT.PROMOTION_NO    = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

   EXEC SQL DECLARE C17 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = :recordp->ARTICLENO
    and   DISCOUNT.CUSTOMERNO      = :recordp->CUSTOMERNO
        and   DISCOUNT.DISCOUNTGRPNO   = 0
    and   DISCOUNT.DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
    and   DISCOUNT.MANUFACTURERNO  = 0
    and   DISCOUNT.PROMOTION_NO    = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

   EXEC SQL DECLARE C18 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = :recordp->ARTICLENO
    and   DISCOUNT.CUSTOMERNO      = 0
    and   (DISCOUNT.PHARMACYGROUPID='000' or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
        and   DISCOUNT.DISCOUNTGRPNO   = 0
    and   DISCOUNT.DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
    and   DISCOUNT.MANUFACTURERNO  = 0
    and   DISCOUNT.PROMOTION_NO    = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


    EXEC SQL DECLARE C19 CURSOR FOR
        SELECT
        DISCOUNT_LISTE, PROMOTIONS_LISTE
    from DISCOUNT
    left outer join promotions on promotions.promotion_no=discount.promotion_no
    where DISCOUNT.BRANCHNO = :recordp->BRANCHNO
    and DISCOUNT.PROMOTION_NO > 0
    and promotions.promotion_type=3
        and DISCOUNT.DISCOUNTGRPNO = 0
        and DISCOUNT.ARTICLENO = :recordp->ARTICLENO
    and DISCOUNT.CUSTOMERNO =:recordp->CUSTOMERNO
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
    UNION
        SELECT
        DISCOUNT_LISTE, PROMOTIONS_LISTE
    from DISCOUNT
    left outer join promotions on promotions.promotion_no=discount.promotion_no
    where DISCOUNT.BRANCHNO = :recordp->BRANCHNO
    and DISCOUNT.PROMOTION_NO > 0
    and promotions.promotion_type=3
        and DISCOUNT.DISCOUNTGRPNO = 0
        and DISCOUNT.MANUFACTURERNO in (SELECT hersteller_nr from artikelzentral where artikel_nr =:recordp->ARTICLENO)
    and DISCOUNT.CUSTOMERNO =:recordp->CUSTOMERNO
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
        order by promotions.priority, discount.baseqty ASC
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


    EXEC SQL DECLARE C20 CURSOR FOR
        SELECT
        DISCOUNT_LISTE, PROMOTIONS_LISTE
    from DISCOUNT
    left outer join promotions on promotions.promotion_no=discount.promotion_no
    where DISCOUNT.BRANCHNO = :recordp->BRANCHNO
    and DISCOUNT.PROMOTION_NO > 0
    and promotions.promotion_type=3
        and DISCOUNT.DISCOUNTGRPNO = 0
        and DISCOUNT.ARTICLENO = :recordp->ARTICLENO
    and ((DISCOUNT.CUSTOMERNO=0 and DISCOUNT.PHARMACYGROUPID='000') or DISCOUNT.PHARMACYGROUPID in (select pharmacygroupid from customerpharmacygr where branchno= :recordp->BRANCHNO  and customerno= :recordp->CUSTOMERNO))
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
    UNION
        SELECT
        DISCOUNT_LISTE, PROMOTIONS_LISTE
    from DISCOUNT
    left outer join promotions on promotions.promotion_no=discount.promotion_no
    where DISCOUNT.BRANCHNO = :recordp->BRANCHNO
    and DISCOUNT.PROMOTION_NO > 0
    and promotions.promotion_type=3
        and DISCOUNT.DISCOUNTGRPNO = 0
        and DISCOUNT.MANUFACTURERNO in (SELECT hersteller_nr from artikelzentral where artikel_nr =:recordp->ARTICLENO)
    and ((DISCOUNT.CUSTOMERNO=0 and DISCOUNT.PHARMACYGROUPID='000') or DISCOUNT.PHARMACYGROUPID in (select pharmacygroupid from customerpharmacygr where branchno= :recordp->BRANCHNO  and customerno= :recordp->CUSTOMERNO))
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
        order by promotions.priority, discount.baseqty ASC
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


    EXEC SQL DECLARE C21 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
        inner join DISCOUNTGRP ON DISCOUNTGRP.BRANCHNO = DISCOUNT.BRANCHNO and DISCOUNTGRP.DISCOUNTGRPNO = DISCOUNT.DISCOUNTGRPNO
        inner join DISCOUNTGRPMEM ON DISCOUNTGRPMEM.BRANCHNO = DISCOUNT.BRANCHNO and DISCOUNTGRPMEM.DISCOUNTGRPNO = DISCOUNT.DISCOUNTGRPNO
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = 0
    and   DISCOUNT.DISCOUNTTYPE    = :recordp->DISCOUNTTYPE
    and   DISCOUNTGRP.DISCOUNTGRPTYPE = 1
    and   DISCOUNTGRPMEM.ARTICLENO = :recordp->ARTICLENO
    and   DISCOUNT.CUSTOMERNO      = 0
    and   (DISCOUNT.PHARMACYGROUPID='000' or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
    and (DISCOUNT.ARTCATEGORYNO=0 or DISCOUNT.ARTCATEGORYNO in (SELECT artcategoryno from articlegroup where ARTICLENO= :recordp->ARTICLENO))
    and   DISCOUNT.PROMOTION_NO    = 0
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif

    EXEC SQL DECLARE C22 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT INNER JOIN ARTICLEGROUP ON ARTICLEGROUP.ARTCATEGORYNO = DISCOUNT.ARTCATEGORYNO
    where DISCOUNT.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNT.CUSTOMERNO       = 0
    and   (DISCOUNT.PHARMACYGROUPID ='000' or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO = :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO ))
    and   (DISCOUNT.ARTICLENO = 0 or DISCOUNT.ARTICLENO = :recordp->ARTICLENO)
    and   (DISCOUNT.MANUFACTURERNO = 0 or DISCOUNT.MANUFACTURERNO in (select hersteller_nr from artikelzentral where artikel_nr = :recordp->ARTICLENO))
    and   (DISCOUNT.DISCOUNTGRPNO=0 or DISCOUNTGRPNO in (select dgrpmem.discountgrpno from discountgrpmem dgrpmem inner join discountgrp dgrp on dgrp.branchno=dgrpmem.branchno and dgrp.discountgrpno=dgrpmem.discountgrpno where dgrpmem.branchno = :recordp->BRANCHNO and dgrpmem.articleno = :recordp->ARTICLENO and dgrp.discountgrptype=1))
    and   DISCOUNT.PROMOTION_NO    = 0
    and   ARTICLEGROUP.ARTICLENO    = :recordp->ARTICLENO
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif


   EXEC SQL DECLARE C23 CURSOR FOR
   SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO        = :recordp->ARTICLENO
    and   DISCOUNT.DISCOUNTTYPE     = 0
    and   DISCOUNT.DISCOUNTGRPNO    = 0
    and   DISCOUNT.MANUFACTURERNO   = 0
    and   ((DISCOUNT.CUSTOMERNO = 0 and DISCOUNT.PHARMACYGROUPID='000') or DISCOUNT.CUSTOMERNO = :recordp->CUSTOMERNO or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
    and   DISCOUNT.PROMOTION_NO    > 0
    and   (DISCOUNT.DISCOUNTSPEC = 0 or DISCOUNT.DISCOUNTSPEC = :recordp->DISCOUNTSPEC)
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
    UNION
    SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO        = 0
    and   DISCOUNT.DISCOUNTTYPE     = 0
    and   DISCOUNT.MANUFACTURERNO   = 0
    and   DISCOUNT.DISCOUNTGRPNO in (select dg.DISCOUNTGRPNO from DISCOUNTGRP dg INNER JOIN DISCOUNTGRPMEM dgm on dgm.BRANCHNO=dg.BRANCHNO and dgm.DISCOUNTGRPNO=dg.DISCOUNTGRPNO where dg.BRANCHNO= :recordp->BRANCHNO and dg.DISCOUNTGRPTYPE=0 and dgm.ARTICLENO= :recordp->ARTICLENO)
    and   ((DISCOUNT.CUSTOMERNO = 0 and DISCOUNT.PHARMACYGROUPID='000') or DISCOUNT.CUSTOMERNO = :recordp->CUSTOMERNO or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
    and   DISCOUNT.PROMOTION_NO    > 0
    and   (DISCOUNT.DISCOUNTSPEC = 0 or DISCOUNT.DISCOUNTSPEC = :recordp->DISCOUNTSPEC)
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
    UNION
    SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO        = 0
    and   DISCOUNT.DISCOUNTTYPE     = 0
    and   DISCOUNT.MANUFACTURERNO   = 0
    and   DISCOUNT.DISCOUNTGRPNO in (select dg.DISCOUNTGRPNO from DISCOUNTGRP dg INNER JOIN DISCOUNTGRPMEM dgm on dgm.BRANCHNO=dg.BRANCHNO and dgm.DISCOUNTGRPNO=dg.DISCOUNTGRPNO INNER JOIN ARTIKELZENTRAL az on az.HERSTELLER_NR=dgm.MANUFACTURERNO where dg.BRANCHNO= :recordp->BRANCHNO and dg.DISCOUNTGRPTYPE=0 and az.ARTIKEL_NR= :recordp->ARTICLENO)
    and   ((DISCOUNT.CUSTOMERNO = 0 and DISCOUNT.PHARMACYGROUPID='000') or DISCOUNT.CUSTOMERNO = :recordp->CUSTOMERNO or DISCOUNT.PHARMACYGROUPID in (SELECT PHARMACYGROUPID from CUSTOMERPHARMACYGR where CUSTOMERPHARMACYGR.BRANCHNO= :recordp->BRANCHNO and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
    and   DISCOUNT.PROMOTION_NO    > 0
    and   (DISCOUNT.DISCOUNTSPEC = 0 or DISCOUNT.DISCOUNTSPEC = :recordp->DISCOUNTSPEC)
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C24 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO         = :recordp->BRANCHNO
    and   DISCOUNT.PROMOTION_NO     = :recordp->PROMOTION_NO
    and   DISCOUNT.DISCOUNTGRPNO    = 0
    and  (DISCOUNT.ARTICLENO = 0    or DISCOUNT.ARTICLENO  = :recordp->ARTICLENO)
    and  (DISCOUNT.CUSTOMERNO = 0   or DISCOUNT.CUSTOMERNO = :recordp->CUSTOMERNO)
    and  (DISCOUNT.MANUFACTURERNO = 0 or DISCOUNT.MANUFACTURERNO in (select hersteller_nr from artikelzentral where artikel_nr = :recordp->ARTICLENO))
    and  ((DISCOUNT.PHARMACYGROUPID  = '000'
    and   DISCOUNT.CUSTOMERNO       =  0)
    or    DISCOUNT.PHARMACYGROUPID in (SELECT CUSTOMERPHARMACYGR.PHARMACYGROUPID
    from  CUSTOMERPHARMACYGR
    where DISCOUNT.BRANCHNO         = CUSTOMERPHARMACYGR.BRANCHNO
    and   CUSTOMERPHARMACYGR.CUSTOMERNO  = :recordp->CUSTOMERNO))
        and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))

#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
    EXEC SQL DECLARE C25 CURSOR FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where DISCOUNT.BRANCHNO        = :recordp->BRANCHNO
    and   DISCOUNT.ARTICLENO       = :recordp->ARTICLENO
	and   DISCOUNT.CUSTOMERNO      = 0  
	and   DISCOUNT.DISCOUNTGRPNO   = 0
	and   DISCOUNT.MANUFACTURERNO  = 0
    and   (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
    FOR BROWSE;
#else
     ;
#endif
	EXEC SQL DECLARE C26 CURSOR FOR
		SELECT
		DISCOUNT_LISTE
	from DISCOUNT
	where DISCOUNT.BRANCHNO  = :recordp->BRANCHNO
	and   DISCOUNT.ARTICLENO = :recordp->ARTICLENO
	and  ((DISCOUNT.CUSTOMERNO = :recordp->CUSTOMERNO and   DISCOUNT.PHARMACYGROUPID = '000')
		or    (DISCOUNT.CUSTOMERNO = 0
	    and DISCOUNT.PHARMACYGROUPID in(SELECT CUSTOMERPHARMACYGR.PHARMACYGROUPID
	    from  CUSTOMERPHARMACYGR
	    where DISCOUNT.BRANCHNO = CUSTOMERPHARMACYGR.BRANCHNO
	    and   CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO)))
	and (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))
#ifndef pxDATABASE_INFORMIX
        FOR BROWSE;
#else
        ;
#endif
	EXEC SQL DECLARE C27 CURSOR FOR
		SELECT
		DISCOUNT_LISTE
	from DISCOUNT
	where DISCOUNT.BRANCHNO = :recordp->BRANCHNO
	and DISCOUNT.ARTICLENO = : recordp->ARTICLENO
    and (DISCOUNT.CUSTOMERNO = :recordp->CUSTOMERNO
    or (DISCOUNT.PHARMACYGROUPID = '000'
    and DISCOUNT.CUSTOMERNO = 0)
    or DISCOUNT.PHARMACYGROUPID in (SELECT CUSTOMERPHARMACYGR.PHARMACYGROUPID
    from  CUSTOMERPHARMACYGR
    where DISCOUNT.BRANCHNO = CUSTOMERPHARMACYGR.BRANCHNO
    and CUSTOMERPHARMACYGR.CUSTOMERNO = :recordp->CUSTOMERNO))
        and (DISCOUNT.DATEFROM <= TO_CHAR(today, '%Y%m%d') AND DISCOUNT.DATETO >= TO_CHAR(today, '%Y%m%d'))

#ifndef pxDATABASE_INFORMIX
		FOR BROWSE;
#else
		;
#endif

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL OPEN C0;
          break;
       case cCRSDISCOUNT_DISCOUNTTYPE       :
          EXEC SQL OPEN C2;
          break;
       case cCRSDISCOUNT_DISCOUNTGRP        :
          EXEC SQL OPEN C3;
          break;
       case cCRSDISCOUNT_JOIN_CSTPHARMGRP   :
          EXEC SQL OPEN C4;
          break;
       case cCRSDISCOUNT_SHORT_LIST         :
          EXEC SQL OPEN C5;
          break;
       case cCRSDISCOUNT_BRARTCUST         :
          EXEC SQL OPEN C6;
          break;
       case cCRSDISCOUNT_BRMANCUST      :
          EXEC SQL OPEN C7;
          break;
       case cCRSDISCOUNT_BRMANCUSTARTGRP_0      :
          EXEC SQL OPEN C8;
          break;
       case cCRSDISCOUNT_BRCUST      :
          EXEC SQL OPEN C9;
          break;
       case cCRSDISCOUNT_BRCUSTGRP      :
          EXEC SQL OPEN C10;
          break;
       case cCRSDISCOUNT_BRARTMAN_0:
          EXEC SQL OPEN C11;
          break;
       case cCRSDISCOUNT_BRSINGLEART_0:
          EXEC SQL OPEN C12;
          break;
       case cCRSDISCOUNT_BRSINGLEART_1:
          EXEC SQL OPEN C14;
          break;
       case cCRSDISCOUNT_BROCCASIONS:
          EXEC SQL OPEN C13;
          break;
       case cCRSDISCOUNT_BRARTMANUFACTURER_0:
          EXEC SQL OPEN C15;
          break;
       case cCRSDISCOUNT_BRARTMANUFACTURER_1:
          EXEC SQL OPEN C16;
          break;
       case cCRSDISCOUNT_BRART_0:
          EXEC SQL OPEN C17;
          break;
       case cCRSDISCOUNT_BRART_1:
          EXEC SQL OPEN C18;
          break;
       case cCRSDISCOUNT_BRPROMOTION_0:
          EXEC SQL OPEN C19;
          break;
       case cCRSDISCOUNT_BRPROMOTION_1:
          EXEC SQL OPEN C20;
          break;
       case cCRSDISCOUNT_BRARTMAN_1:
          EXEC SQL OPEN C21;
          break;
       case cCRSDISCOUNT_BRMANCUSTARTGRP_1      :
          EXEC SQL OPEN C22;
          break;
       case cCRSDISCOUNT_BRALLPROMOTIONS      :
          EXEC SQL OPEN C23;
          break;
       case cCRSDISCOUNT_BRPROMOTIONNO      :
          EXEC SQL OPEN C24;
          break;
       case cCRSDISCOUNT_BRCUSTGRP_0        :
          EXEC SQL OPEN C25;
          break;
	   case cCRSDISCOUNT_JOIN_CSTPHARMGRP_1:
		   EXEC SQL OPEN C26;
		   break;
       case cCRSDISCOUNT_JOIN_CSTPHARMGRP_2:
		   EXEC SQL OPEN C27;
		   break;
       default:
          EXEC SQL OPEN C1;
          break;
    }
    if (SQLCODE == 0)        return 0;
    if (SQLCODE == 100)      return cDBXR_NOTFOUND;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountGetNext                                       */
/*                                                                   */
/*      Fetch for a Cursor   (general)                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxDiscountGetNext
(
    struct tDISCOUNT* record,
    int browseid
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNT * recordp;
    EXEC SQL END   DECLARE SECTION;

    functionnr = F_DISCOUNT*10+F_GetNext;
    recordp = (struct C_DISCOUNT *) record;

    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL FETCH C0
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_DISCOUNTTYPE       :
          EXEC SQL FETCH C2
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_DISCOUNTGRP        :
          EXEC SQL FETCH C3
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_JOIN_CSTPHARMGRP   :
          EXEC SQL FETCH C4
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_SHORT_LIST         :
          EXEC SQL FETCH C5
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRARTCUST         :
          EXEC SQL FETCH C6
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRMANCUST         :
          EXEC SQL FETCH C7
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRMANCUSTARTGRP_0:
          EXEC SQL FETCH C8
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRCUST         :
          EXEC SQL FETCH C9
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRCUSTGRP         :
          EXEC SQL FETCH C10
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRARTMAN_0:
          EXEC SQL FETCH C11
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRSINGLEART_0:
          EXEC SQL FETCH C12
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRSINGLEART_1:
          EXEC SQL FETCH C14
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BROCCASIONS:
          EXEC SQL FETCH C13
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRARTMANUFACTURER_0:
          EXEC SQL FETCH C15
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRARTMANUFACTURER_1:
          EXEC SQL FETCH C16
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRART_0:
          EXEC SQL FETCH C17
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRART_1:
          EXEC SQL FETCH C18
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRPROMOTION_0:
          EXEC SQL FETCH C19
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRPROMOTION_1:
          EXEC SQL FETCH C20
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRARTMAN_1:
          EXEC SQL FETCH C21
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRMANCUSTARTGRP_1:
          EXEC SQL FETCH C22
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRALLPROMOTIONS:
          EXEC SQL FETCH C23
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRPROMOTIONNO:
          EXEC SQL FETCH C24
          into DISCOUNT_ZEIGER(recordp);
          break;
       case cCRSDISCOUNT_BRCUSTGRP_0:
          EXEC SQL FETCH C25
          into DISCOUNT_ZEIGER(recordp);
          break;
	   case cCRSDISCOUNT_JOIN_CSTPHARMGRP_1:
		   EXEC SQL FETCH C26
		   into DISCOUNT_ZEIGER(recordp);
		   break;
       case cCRSDISCOUNT_JOIN_CSTPHARMGRP_2:
		   EXEC SQL FETCH C27
		   into DISCOUNT_ZEIGER(recordp);
           break;
       default:
          EXEC SQL FETCH C1
          into DISCOUNT_ZEIGER(recordp);
          break;
    }
    if (SQLCODE == 0)    return 0;
    if (SQLCODE == 100)  return cDBXR_ENDOFDATA;
    return cDBXR_IOERROR;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountEndBrowse                                     */
/*                                                                   */
/*      Close a Cursor   (general)                                   */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxDiscountEndBrowse
(
    int browseid
)
{
    functionnr = F_DISCOUNT*10+F_EndBrowse;

    /* close the cursor */
    switch (browseid)
    {
       case cCRS_NOWHERE:
          EXEC SQL CLOSE C0;
          break;
       case cCRSDISCOUNT_DISCOUNTTYPE       :
          EXEC SQL CLOSE C2;
          break;
       case cCRSDISCOUNT_DISCOUNTGRP        :
          EXEC SQL CLOSE C3;
          break;
       case cCRSDISCOUNT_JOIN_CSTPHARMGRP   :
          EXEC SQL CLOSE C4;
          break;
       case cCRSDISCOUNT_SHORT_LIST         :
          EXEC SQL CLOSE C5;
          break;
       case cCRSDISCOUNT_BRARTCUST         :
          EXEC SQL CLOSE C6;
          break;
       case cCRSDISCOUNT_BRMANCUST         :
          EXEC SQL CLOSE C7;
          break;
       case cCRSDISCOUNT_BRMANCUSTARTGRP_0:
          EXEC SQL CLOSE C8;
          break;
       case cCRSDISCOUNT_BRCUST         :
          EXEC SQL CLOSE C9;
          break;
       case cCRSDISCOUNT_BRCUSTGRP         :
          EXEC SQL CLOSE C10;
          break;
       case cCRSDISCOUNT_BRARTMAN_0:
          EXEC SQL CLOSE C11;
          break;
       case cCRSDISCOUNT_BRSINGLEART_0:
          EXEC SQL CLOSE C12;
          break;
       case cCRSDISCOUNT_BRSINGLEART_1:
          EXEC SQL CLOSE C14;
          break;
       case cCRSDISCOUNT_BROCCASIONS:
          EXEC SQL CLOSE C13;
          break;
       case cCRSDISCOUNT_BRARTMANUFACTURER_0:
          EXEC SQL CLOSE C15;
          break;
       case cCRSDISCOUNT_BRARTMANUFACTURER_1:
          EXEC SQL CLOSE C16;
          break;
       case cCRSDISCOUNT_BRART_0:
          EXEC SQL CLOSE C17;
          break;
       case cCRSDISCOUNT_BRART_1:
          EXEC SQL CLOSE C18;
          break;
       case cCRSDISCOUNT_BRPROMOTION_0:
          EXEC SQL CLOSE C19;
          break;
       case cCRSDISCOUNT_BRPROMOTION_1:
          EXEC SQL CLOSE C20;
          break;
       case cCRSDISCOUNT_BRARTMAN_1:
          EXEC SQL CLOSE C21;
          break;
       case cCRSDISCOUNT_BRMANCUSTARTGRP_1:
          EXEC SQL CLOSE C22;
          break;
       case cCRSDISCOUNT_BRALLPROMOTIONS:
          EXEC SQL CLOSE C23;
          break;
       case cCRSDISCOUNT_BRPROMOTIONNO:
          EXEC SQL CLOSE C24;
          break;
       case cCRSDISCOUNT_BRCUSTGRP_0:
          EXEC SQL CLOSE C25;
          break;
	   case cCRSDISCOUNT_JOIN_CSTPHARMGRP_1:
		   EXEC SQL CLOSE C26;
		   break;
	   case cCRSDISCOUNT_JOIN_CSTPHARMGRP_2:
		   EXEC SQL CLOSE C27;
		   break;
       default:
          EXEC SQL CLOSE C1;
          break;
    }
    return 0;
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountRead                                          */
/*                                                                   */
/*      Get one record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxDiscountRead
(
    struct tDISCOUNT* record
#ifdef SKtdiscount
    , int keyid               /* keyid if read with sec key possible */
#endif
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNT*10+F_Read;
    recordp = (struct C_DISCOUNT *) record;

#ifdef SKtdiscount
    switch (keyid)
    {
     case 1:
     EXEC SQL SELECT
        DISCOUNT_LISTE
     into DISCOUNT_ZEIGER(recordp)
     from DISCOUNT
     where SKtdiscount;
     break;
    default:
#endif

    EXEC SQL SELECT
        DISCOUNT_LISTE
     into DISCOUNT_ZEIGER(recordp)
     from DISCOUNT
     where PKtdiscount;

#ifdef SKtdiscount
    }
#endif
    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }

}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountReadLock                                      */
/*                                                                   */
/*      Get one record with lock                                     */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxDiscountReadLock
(
    struct tDISCOUNT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNT*10+F_ReadLock;
    recordp = (struct C_DISCOUNT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL DECLARE tdiscount_U1 CURSOR WITH HOLD FOR
        SELECT
        DISCOUNT_LISTE
    from DISCOUNT
    where PKtdiscount
    FOR UPDATE;
    EXEC SQL OPEN tdiscount_U1;
    if (SQLCODE == 0)
    {
      EXEC SQL FETCH tdiscount_U1
      into DISCOUNT_ZEIGER(recordp)
      ;
    }
#else
    EXEC SQL SELECT
         DISCOUNT_LISTE
    into DISCOUNT_ZEIGER(recordp)
    from DISCOUNT    HOLDLOCK
    where PKtdiscount;
#endif


    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 1)                /* found, but more than 1 exists */
       {
          return cDBXR_ISDUPLICATE;
       }
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }

}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountUpdate                                        */
/*                                                                   */
/*      Update  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxDiscountUpdate
(
    struct tDISCOUNT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNT*10+F_Update;
    recordp = (struct C_DISCOUNT *) record;


#ifdef pxDATABASE_INFORMIX

    EXEC SQL UPDATE
    DISCOUNT
    SET
    DISCOUNT_UPDATE(recordp)
    where current of tdiscount_U1
    ;
    if (SQLCODE == 0)
    {
      EXEC SQL CLOSE tdiscount_U1;
    }
#else

    EXEC SQL UPDATE
    DISCOUNT
    SET
    DISCOUNT_UPDATE(recordp)
    where PKtdiscount;
#endif

    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       return cDBXR_IOERROR;
    }
}
/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountInsert                                       */
/*                                                                   */
/*      Insert  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, 1 if error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/
int pxDiscountInsert
(
    struct tDISCOUNT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNT*10+F_Insert;
    recordp = (struct C_DISCOUNT *) record;

    EXEC SQL INSERT INTO
    DISCOUNT
    (DISCOUNT_LISTE)
    VALUES ( DISCOUNT_ZEIGER(recordp) );

/*  EXEC SQL INSERT INTO
    DISCOUNT
    VALUES ( DISCOUNT_ZEIGER(recordp) );   */


    if (SQLCODE == 0)
    {
       return 0;
    }
    if (SQLCODE == -2601)
    {
       return cDBXR_ISDUPLICATE;
    }
    return cDBXR_IOERROR;
}

/*-------------------------------------------------------------------*/
/*                                                                   */
/*  FUNCTION: pxDiscountDelete                                        */
/*                                                                   */
/*      delete  record                                               */
/*                                                                   */
/*  PARAMETERS:                                                      */
/*                                                                   */
/*      record buffer                                                */
/*                                                                   */
/*  RETURNS: 0 if successful, else error                             */
/*                                                                   */
/*  COMMENTS:                                                        */
/*                                                                   */
/*-------------------------------------------------------------------*/

int pxDiscountDelete
(
    struct tDISCOUNT* record
)
{
    EXEC SQL BEGIN DECLARE SECTION;
    struct C_DISCOUNT * recordp;
    EXEC SQL END DECLARE SECTION;

    functionnr = F_DISCOUNT*10+F_Delete;
    recordp = (struct C_DISCOUNT *) record;

    EXEC SQL DELETE FROM
    DISCOUNT
    where PKtdiscount;

    if (SQLCODE == 0)
    {
       return 0;
    }
    else
    {
       if (SQLCODE == 100)
          return cDBXR_NOTFOUND;
       return cDBXR_IOERROR;
    }
}
