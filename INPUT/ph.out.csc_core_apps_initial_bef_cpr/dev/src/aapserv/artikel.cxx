/******************************************************************************/
/*                                                                            */
/* header  : ArtBuyingOptions.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:28 2022                                         */
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
#include "artikel.h"

/* ArtBuyingOptions: Select ***************************************************/

/* ArtBuyingOptions::SelBuyingOptions *****************************************/

retClient Artbuyingoptions_SelBuyingOptions(artbuyingoptionsS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artbuyingoptions_SelBuyingOptions";
    exec sql begin declare section;
    artbuyingoptionsS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelzentral.artikel_nr,
                     artikelzentral.etartklasse1,
                     artikelzentral.kzPsychoStoffe
                into :d->ARTIKEL_NR,
                     :d->ETARTKLASSE1,
                     :d->KZPSYCHOSTOFFE
                from artikelzentral
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtBuyingOptions: Insert ***************************************************/



/* ArtBuyingOptions: Update ***************************************************/



/* ArtBuyingOptions: Select ***************************************************/



/* ArtBuyingOptions: Other ****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtCharge.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:30 2022                                         */
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
#include "artikel.h"

/* ArtCharge: Select **********************************************************/

/* ArtCharge::SelList *********************************************************/

retClient Artcharge_SelList(artchargeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artcharge_SelList";
    exec sql begin declare section;
    artchargeS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList1 cursor with hold for
                  select articlecharge.BranchNo,
                     articlecharge.ArticleNo,
                     articlecharge.ExpiryDate,
                     articlecharge.ChargenNr,
                     articlecharge.stock,
                     articlecharge.StateCharge
                from ARTICLECHARGE
                  where ArticleCharge.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleCharge.ArticleNo	 =	:d->ARTICLENO and
                        ArticleCharge.StateCharge	 =	'2'
                        order by ArticleCharge.ExpiryDate;
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
                     :d->ARTICLENO,
                     :d->EXPIRYDATE,
                     :d->CHARGENNR,
                     :d->STOCK,
                     :d->STATECHARGE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList1" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArtCharge::SelListQua ******************************************************/

retClient Artcharge_SelListQua(artchargeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artcharge_SelListQua";
    exec sql begin declare section;
    artchargeS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListQua2 cursor with hold for
                  select articlecharge.BranchNo,
                     articlecharge.ArticleNo,
                     articlecharge.ExpiryDate,
                     articlecharge.ChargenNr,
                     articlecharge.stock,
                     articlecharge.StateCharge
                from ARTICLECHARGE
                  where ArticleCharge.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleCharge.ArticleNo	 =	:d->ARTICLENO and
                        ArticleCharge.StateCharge	 =	'8'
                        order by ArticleCharge.ExpiryDate;
        exec sql open CSelListQua2;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListQua2" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListQua2;
        return CheckSql( fun, stError, "%s", "close CSelListQua2" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListQua2 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->EXPIRYDATE,
                     :d->CHARGENNR,
                     :d->STOCK,
                     :d->STATECHARGE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListQua2" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtCharge: Insert **********************************************************/



/* ArtCharge: Update **********************************************************/



/* ArtCharge: Select **********************************************************/



/* ArtCharge: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtInfBG.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:32 2022                                         */
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
#include "artikel.h"

/* ArtInfBG: Select ***********************************************************/

/* ArtInfBG::SelArtInfBG ******************************************************/

retClient Artinfbg_SelArtInfBG(artinfbgS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artinfbg_SelArtInfBG";
    exec sql begin declare section;
    artinfbgS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelzentral.artikel_nr,
                     artikelzentral.HealthFundCode,
                     artikelzentral.artikel_langname
                into :d->ARTIKEL_NR,
                     :d->HEALTHFUNDCODE,
                     :d->ARTIKEL_LANGNAME
                from ARTIKELZENTRAL
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtInfBG: Insert ***********************************************************/



/* ArtInfBG: Update ***********************************************************/



/* ArtInfBG: Select ***********************************************************/



/* ArtInfBG: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtInsert.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:35 2022                                         */
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
#include "artikel.h"

/* ArtInsert: Select **********************************************************/

/* ArtInsert::SelBeilage ******************************************************/

retClient Artinsert_SelBeilage(artinsertS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artinsert_SelBeilage";
    exec sql begin declare section;
    artinsertS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelBeilage4 cursor with hold for
                  select artinfotext.ArticleNo,
                     artinfotext.ArtInfoType,
                     artinfotext.SequenceNo,
                     artinfotext.InfoText
                from ARTINFOTEXT
                  where ArtInfoText.ArticleNo	 =	:d->ARTICLENO	 and
                        ArtInfoText.ArtInfoType	 =	:d->ARTINFOTYPE	
                        order by ArtInfoText.SequenceNo;
        exec sql open CSelBeilage4;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelBeilage4" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelBeilage4;
        return CheckSql( fun, stError, "%s", "close CSelBeilage4" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelBeilage4 into :d->ARTICLENO,
                     :d->ARTINFOTYPE,
                     :d->SEQUENCENO,
                     :d->INFOTEXT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelBeilage4" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtInsert: Insert **********************************************************/

/* ArtInsert::Insert **********************************************************/

retClient Artinsert_Insert(artinsertS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artinsert_Insert";
    exec sql begin declare section;
    artinsertS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into artinfotext (ArticleNo,
                     ArtInfoType,
                     SequenceNo,
                     InfoText)
        values (:d->ARTICLENO,
                     :d->ARTINFOTYPE,
                     :d->SEQUENCENO,
                     :d->INFOTEXT);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert artinfotext" ) ) != IS_OK )
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



/* ArtInsert: Update **********************************************************/



/* ArtInsert: Select **********************************************************/

/* ArtInsert::Delete **********************************************************/

retClient Artinsert_Delete(artinsertS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Artinsert_Delete";
    exec sql begin declare section;
    artinsertS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete5 cursor with hold for
              select ArticleNo,
                     ArtInfoType,
                     SequenceNo,
                     InfoText
               from ARTINFOTEXT
              where ArtInfoText.ArticleNo	 =	:d->ARTICLENO	 and
                    ArtInfoText.ArtInfoType	 =	:d->ARTINFOTYPE
              for update;
    exec sql open CDelete5;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete5" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete5;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete5" ) ) != IS_OK )
            break;
        exec sql delete from artinfotext where current of CDelete5;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete5" ) ) != IS_OK )
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



/* ArtInsert: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtLangName.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:36 2022                                         */
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
#include "artikel.h"

/* ArtLangName: Select ********************************************************/

/* ArtLangName::SelLangname ***************************************************/

retClient Artlangname_SelLangname(artlangnameS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artlangname_SelLangname";
    exec sql begin declare section;
    artlangnameS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelzentral.artikel_nr,
                     artikelzentral.artikel_langname
                into :d->ARTIKEL_NR,
                     :d->ARTIKEL_LANGNAME
                from ARTIKELZENTRAL
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtLangName: Insert ********************************************************/



/* ArtLangName: Update ********************************************************/



/* ArtLangName: Select ********************************************************/



/* ArtLangName: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtPrice.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:38 2022                                         */
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
#include "artikel.h"

/* ArtPrice: Select ***********************************************************/

/* ArtPrice::SelPrice *********************************************************/

retClient Artprice_SelPrice(artpriceS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artprice_SelPrice";
    exec sql begin declare section;
    artpriceS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelpreis.artikel_nr,
                     artikelpreis.preisekapo,
                     artikelpreis.preisekgrosso,
                     artikelpreis.preis_typ
                into :d->ARTIKEL_NR,
                     :d->PREISEKAPO,
                     :d->PREISEKGROSSO,
                     :d->PREIS_TYP
                from ARTIKELPREIS
              where artikelpreis.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    artikelpreis.preis_typ	 =	:d->PREIS_TYP;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtPrice: Insert ***********************************************************/



/* ArtPrice: Update ***********************************************************/



/* ArtPrice: Select ***********************************************************/



/* ArtPrice: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtPsycho.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:40 2022                                         */
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
#include "artikel.h"

/* ArtPsycho: Select **********************************************************/

/* ArtPsycho::SelArticle ******************************************************/

retClient Artpsycho_SelArticle(artpsychoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artpsycho_SelArticle";
    exec sql begin declare section;
    artpsychoS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelzentral.artikel_nr,
                     artikelzentral.etartklasse1,
                     artikelzentral.kzPsychoStoffe
                into :d->ARTIKEL_NR,
                     :d->ETARTKLASSE1,
                     :d->KZPSYCHOSTOFFE
                from artikelzentral
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtPsycho: Insert **********************************************************/



/* ArtPsycho: Update **********************************************************/



/* ArtPsycho: Select **********************************************************/



/* ArtPsycho: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArticleAgentGroup.cxx                                            */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:49 2022                                         */
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
#include "artikel.h"

/* ArticleAgentGroup: Select **************************************************/

/* ArticleAgentGroup::SelAgent ************************************************/

retClient Articleagentgroup_SelAgent(articleagentgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Articleagentgroup_SelAgent";
    exec sql begin declare section;
    articleagentgroupS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelzentral.wirkstoff_nr
                into :d->WIRKSTOFF_NR
                from ARTIKELZENTRAL
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArticleAgentGroup::SelArtikel **********************************************/

retClient Articleagentgroup_SelArtikel(articleagentgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Articleagentgroup_SelArtikel";
    exec sql begin declare section;
    articleagentgroupS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelpreis.preisekapo,
                     artikellokal.filialnr,
                     artikelzentral.artikel_nr,
                     artikellokal.bestand,
                     artikelzentral.darreichform,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name,
                     artikelzentral.wirkstoff_nr,
                     artikelzentral.artikel_langname
                into :d->PREISEKAPO,
                     :d->FILIALNR,
                     :d->ARTIKEL_NR,
                     :d->BESTAND,
                     :d->DARREICHFORM,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME,
                     :d->WIRKSTOFF_NR,
                     :d->ARTIKEL_LANGNAME
                from ARTIKELZENTRAL, ARTIKELLOKAL, ARTIKELPREIS
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    artikellokal.filialnr	 =	:d->FILIALNR	 and
                    artikelzentral.artikel_nr	 =	artikellokal.artikel_nr and
                    artikelpreis.artikel_nr	 =	artikelzentral.artikel_nr and
                    artikelpreis.preis_typ	 =	0;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArticleAgentGroup::SelList *************************************************/

retClient Articleagentgroup_SelList(articleagentgroupS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Articleagentgroup_SelList";
    exec sql begin declare section;
    articleagentgroupS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList11 cursor with hold for
                  select artikelpreis.preisekapo,
                     artikellokal.filialnr,
                     artikelzentral.artikel_nr,
                     artikellokal.bestand,
                     artikelzentral.darreichform,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name,
                     artikelzentral.wirkstoff_nr,
                     artikelzentral.artikel_langname
                from ARTIKELZENTRAL, ARTIKELLOKAL, ARTIKELPREIS
                  where artikelzentral.wirkstoff_nr	 =	:d->WIRKSTOFF_NR	 and
                        artikellokal.filialnr	 =	:d->FILIALNR	 and
                        artikelzentral.artikel_nr	 =	artikellokal.artikel_nr and
                        artikelpreis.artikel_nr	 =	artikelzentral.artikel_nr and
                        artikelpreis.preis_typ	 =	0;
        exec sql open CSelList11;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList11" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList11;
        return CheckSql( fun, stError, "%s", "close CSelList11" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList11 into :d->PREISEKAPO,
                     :d->FILIALNR,
                     :d->ARTIKEL_NR,
                     :d->BESTAND,
                     :d->DARREICHFORM,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME,
                     :d->WIRKSTOFF_NR,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList11" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArticleAgentGroup: Insert **************************************************/



/* ArticleAgentGroup: Update **************************************************/



/* ArticleAgentGroup: Select **************************************************/



/* ArticleAgentGroup: Other ***************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArticleLpprReimb.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:51 2022                                         */
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
#include "artikel.h"

/* ArticleLpprReimb: Select ***************************************************/

/* ArticleLpprReimb::SelListArt ***********************************************/

retClient Articlelpprreimb_SelListArt(articlelpprreimbS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Articlelpprreimb_SelListArt";
    exec sql begin declare section;
    articlelpprreimbS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListArt12 cursor with hold for
                  select articlelpprcomb.ArticleNo,
                     articlelpprcomb.code_lppr,
                     lpprreimb.DateFrom,
                     lpprreimb.reimbursement_val,
                     lpprreimb.lppr_desc,
                     articlelpprcomb.reimbcalcflag
                from articlelpprcomb,lpprreimb
                  where ArticleLpprComb.ArticleNo	 =	:d->ARTICLENO	 and
                        ArticleLpprComb.code_lppr	 =	LpprReimb.code_lppr;
        exec sql open CSelListArt12;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListArt12" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListArt12;
        return CheckSql( fun, stError, "%s", "close CSelListArt12" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListArt12 into :d->ARTICLENO,
                     :d->CODE_LPPR,
                     :d->DATEFROM,
                     :d->REIMBURSEMENT_VAL,
                     :d->LPPR_DESC,
                     :d->REIMBCALCFLAG;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListArt12" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArticleLpprReimb: Insert ***************************************************/



/* ArticleLpprReimb: Update ***************************************************/



/* ArticleLpprReimb: Select ***************************************************/



/* ArticleLpprReimb: Other ****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArticleQuotaDetail.cxx                                           */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:44:54 2022                                         */
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
#include "artikel.h"

/* ArticleQuotaDetail: Select *************************************************/



/* ArticleQuotaDetail: Insert *************************************************/



/* ArticleQuotaDetail: Update *************************************************/



/* ArticleQuotaDetail: Select *************************************************/



/* ArticleQuotaDetail: Other **************************************************/

/* ArticleQuotaDetail::SelCount ***********************************************/

retClient Articlequotadetail_SelCount(articlequotadetailS *a, tError *stError, bool bIsTrans)
{
  retClient rc = IS_OK;
  bool bInTrans = FALSE;
  char *fun = "Artikelquotadetail_GetCount";
  exec sql begin declare section;
  articlequotadetailS *d;
  exec sql end declare section;

  d = a;

  if ( bIsTrans ); /*only because preprozessor*/

  exec sql select count(*) into :d->CUSTOMERNO from articlequota
            where branchno = :d->BRANCHNO;
  if ( CheckSql( fun, stError, "%s", "select count(*)" ) == IS_ERROR )
     d->CUSTOMERNO = 0; 

  return (retClient)IS_OK;
}

/* ArticleQuotaDetail::SelKumVzDetail *****************************************/

retClient Articlequotadetail_SelKumVzDetail(articlequotadetailS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Artikelquotadetail_SelKumVzDetail";
exec sql begin declare section;
articlequotadetailS *d;
exec sql end declare section;

d = a;

if ( a->FETCH_REL == SET_OPEN )
{
   exec sql declare CSelKumVzDetail0 cursor with hold for
    select count(*),
        q.ArticleNo,
        q.Validity,
        z.Artikel_name,
        z.Einheit,
        q.Quota,
        k.kzkdklasse[1]
     from articlequota q,artikelzentral z,kunde k
     where q.BranchNo = :d->BRANCHNO
     and q.articleno = z.artikel_nr
     and q.customerno = k.kundennr
     and q.branchno = k.vertriebszentrumnr
     group by 
        q.ArticleNo,
        q.Validity,
        z.Artikel_name,
        z.Einheit,
        q.Quota,
        k.kzkdklasse[1]
     order by artikel_name,einheit;
   exec sql open CSelKumVzDetail0;
   if ( ( rc=CheckSql( fun, stError, "%s", "open CSelKumVzDetail0" ) ) != IS_OK )
     return rc;
}

if ( a->FETCH_REL == SET_CLOSE )
{
   if ( bIsTrans )
   {
     if ( ( rc = Commit( fun, stError ) ) != IS_OK )
       return rc;
   }
   exec sql close CSelKumVzDetail0;
     return CheckSql( fun, stError, "%s", "close CSelKumVzDetail0" );
}

if ( bIsTrans )
{
   if ( ( rc = Begin( fun, stError ) ) != IS_OK )
     return rc;
}
exec sql fetch CSelKumVzDetail0 into :d->CUSTOMERNO,
   :d->ARTICLENO,
   :d->VALIDITY,
   :d->ARTIKEL_NAME,
   :d->EINHEIT,
   :d->QUOTA,
   :d->KZKDKLASSE;
if ((rc=CheckSql( fun, stError, "%s", "fetch CSelKumVzDetail0" )) == IS_ERROR )
   return rc;
return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : ArticleQuotaEKG.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:00 2022                                         */
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
#include "artikel.h"

/* ArticleQuotaEKG: Select ****************************************************/

/* ArticleQuotaEKG::SelArticle ************************************************/

retClient Articlequotaekg_SelArticle(articlequotaekgS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Articlequotaekg_SelArticle";
    exec sql begin declare section;
    articlequotaekgS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelArticle13 cursor with hold for
                  select articlequota.BranchNo,
                     pharmacygroups.group_name,
                     articlequota.ArticleNo,
                     articlequota.Quota,
                     articlequota.KumQty,
                     articlequota.Validity,
                     articlequota.DateUpdate,
                     articlequota.uid_anlage,
                     articlequota.DateFrom,
                     articlequota.DateTo,
                     articlequota.PharmacyGroupId,
                     articlequota.sNoBatchChange,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from ARTICLEQUOTA, ARTIKELZENTRAL, outer PHARMACYGROUPS
                  where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleQuota.ArticleNo	 =	:d->ARTICLENO	 and
                        ArticleQuota.PharmacyGroupId	 =	PharmacyGroups.PharmacyGroupId and
                        ArticleQuota.ArticleNo	 =	artikelzentral.artikel_nr and
                        ArticleQuota.CustomerNo	 =	0 and
                        ArticleQuota.sNoBatchChange	>=	:d->SNOBATCHCHANGE;
        exec sql open CSelArticle13;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelArticle13" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelArticle13;
        return CheckSql( fun, stError, "%s", "close CSelArticle13" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelArticle13 into :d->BRANCHNO,
                     :d->GROUP_NAME,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelArticle13" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArticleQuotaEKG::SelListEKG ************************************************/

retClient Articlequotaekg_SelListEKG(articlequotaekgS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Articlequotaekg_SelListEKG";
    exec sql begin declare section;
    articlequotaekgS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListEKG14 cursor with hold for
                  select articlequota.BranchNo,
                     pharmacygroups.group_name,
                     articlequota.ArticleNo,
                     articlequota.Quota,
                     articlequota.KumQty,
                     articlequota.Validity,
                     articlequota.DateUpdate,
                     articlequota.uid_anlage,
                     articlequota.DateFrom,
                     articlequota.DateTo,
                     articlequota.PharmacyGroupId,
                     articlequota.sNoBatchChange,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from ARTICLEQUOTA, ARTIKELZENTRAL, outer PHARMACYGROUPS
                  where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleQuota.PharmacyGroupId	 =	:d->PHARMACYGROUPID	 and
                        ArticleQuota.ArticleNo	 =	artikelzentral.artikel_nr and
                        ArticleQuota.PharmacyGroupId	 =	PharmacyGroups.PharmacyGroupId and
                        ArticleQuota.CustomerNo	 =	0 and
                        ArticleQuota.sNoBatchChange	>=	:d->SNOBATCHCHANGE;
        exec sql open CSelListEKG14;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListEKG14" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListEKG14;
        return CheckSql( fun, stError, "%s", "close CSelListEKG14" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListEKG14 into :d->BRANCHNO,
                     :d->GROUP_NAME,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListEKG14" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArticleQuotaEKG: Insert ****************************************************/

/* ArticleQuotaEKG::Insert ****************************************************/

retClient Articlequotaekg_Insert(articlequotaekgS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Articlequotaekg_Insert";
    exec sql begin declare section;
    articlequotaekgS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
       d->DATEUPDATE = AllgGetDate();
    exec sql insert into articlequota (BranchNo,
                     ArticleNo,
                     Quota,
                     KumQty,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange)
        values (:d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert articlequota" ) ) != IS_OK )
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



/* ArticleQuotaEKG: Update ****************************************************/

/* ArticleQuotaEKG::Update ****************************************************/

retClient Articlequotaekg_Update(articlequotaekgS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Articlequotaekg_Update";
    exec sql begin declare section;
    articlequotaekgS *d;
    exec sql end declare section;

    d = a;

       d->DATEUPDATE = AllgGetDate();


    exec sql declare CUpdate15 cursor with hold for
              select BranchNo,
                     ArticleNo,
                     Quota,
                     KumQty,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange
               from ARTICLEQUOTA
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO	 and
                    ArticleQuota.PharmacyGroupId	 =	:d->PHARMACYGROUPID	 and
                    ArticleQuota.CustomerNo	 =	0
              for update;
    exec sql open CUpdate15;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate15" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate15;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate15" ) ) != IS_OK )
            break;
        exec sql update articlequota set BranchNo = :d->BRANCHNO,
                     ArticleNo = :d->ARTICLENO,
                     Quota = :d->QUOTA,
                     KumQty = :d->KUMQTY,
                     Validity = :d->VALIDITY,
                     DateUpdate = :d->DATEUPDATE,
                     uid_anlage = :d->UID_ANLAGE,
                     DateFrom = :d->DATEFROM,
                     DateTo = :d->DATETO,
                     PharmacyGroupId = :d->PHARMACYGROUPID,
                     sNoBatchChange = :d->SNOBATCHCHANGE where current of CUpdate15;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate15" ) ) != IS_OK )
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



/* ArticleQuotaEKG: Select ****************************************************/

/* ArticleQuotaEKG::Delete ****************************************************/

retClient Articlequotaekg_Delete(articlequotaekgS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Articlequotaekg_Delete";
    exec sql begin declare section;
    articlequotaekgS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete16 cursor with hold for
              select BranchNo,
                     ArticleNo,
                     Quota,
                     KumQty,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange
               from ARTICLEQUOTA
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO	 and
                    ArticleQuota.CustomerNo	 =	0
              for update;
    exec sql open CDelete16;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete16" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete16;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete16" ) ) != IS_OK )
            break;
        exec sql delete from articlequota where current of CDelete16;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete16" ) ) != IS_OK )
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

/* ArticleQuotaEKG::DeleteAllEKG **********************************************/

retClient Articlequotaekg_DeleteAllEKG(articlequotaekgS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Articlequotaekg_DeleteAllEKG";
    exec sql begin declare section;
    articlequotaekgS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteAllEKG17 cursor with hold for
              select BranchNo,
                     ArticleNo,
                     Quota,
                     KumQty,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange
               from ARTICLEQUOTA
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.PharmacyGroupId	 =	:d->PHARMACYGROUPID	 and
                    ArticleQuota.CustomerNo	 =	0
              for update;
    exec sql open CDeleteAllEKG17;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteAllEKG17" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteAllEKG17;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteAllEKG17" ) ) != IS_OK )
            break;
        exec sql delete from articlequota where current of CDeleteAllEKG17;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteAllEKG17" ) ) != IS_OK )
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



/* ArticleQuotaEKG: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArticleTax.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:02 2022                                         */
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
#include "artikel.h"

/* ArticleTax: Select *********************************************************/

/* ArticleTax::SelTax *********************************************************/

retClient Articletax_SelTax(articletaxS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Articletax_SelTax";
    exec sql begin declare section;
    articletaxS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select taxrates.salestaxrate,
                     artikelzentral.artikel_nr
                into :d->SALESTAXRATE,
                     :d->ARTIKEL_NR
                from ARTIKELZENTRAL, TAXRATES
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    TaxRates.TaxLevel	 =	artikelzentral.TaxLevel;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArticleTax: Insert *********************************************************/



/* ArticleTax: Update *********************************************************/



/* ArticleTax: Select *********************************************************/



/* ArticleTax: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtikelLPPR.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:04 2022                                         */
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
#include "artikel.h"

/* ArtikelLPPR: Select ********************************************************/

/* ArtikelLPPR::SelList *******************************************************/

retClient Artikellppr_SelList(artikellpprS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikellppr_SelList";
    exec sql begin declare section;
    artikellpprS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList19 cursor with hold for
                  select articlelppr.ArticleNo,
                     articlelppr.reimbursement_type,
                     articlelppr.ReimbursementPrice,
                     articlelppr.code_lppr,
                     articlelppr.reimbursement_perc
                from ARTICLELPPR
                  where ArticleLPPR.ArticleNo	 =	:d->ARTICLENO;
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
        return rc;
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList19 into :d->ARTICLENO,
                     :d->REIMBURSEMENT_TYPE,
                     :d->REIMBURSEMENTPRICE,
                     :d->CODE_LPPR,
                     :d->REIMBURSEMENT_PERC;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList19" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtikelLPPR: Insert ********************************************************/



/* ArtikelLPPR: Update ********************************************************/



/* ArtikelLPPR: Select ********************************************************/



/* ArtikelLPPR: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtikelQuota.cxx                                                 */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:16 2022                                         */
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
#include "artikel.h"

/* ArtikelQuota: Select *******************************************************/

/* ArtikelQuota::SelListAllNoBat **********************************************/

retClient Artikelquota_SelListAllNoBat(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelquota_SelListAllNoBat";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListAllNoBat20 cursor with hold for
                  select articlequota.BranchNo,
                     articlequota.CustomerNo,
                     kunde.matchcode,
                     articlequota.ArticleNo,
                     articlequota.Quota,
                     articlequota.KumQty,
                     articlequota.Validity,
                     articlequota.DateUpdate,
                     articlequota.uid_anlage,
                     articlequota.sDafueQuota,
                     articlequota.DateFrom,
                     articlequota.DateTo,
                     articlequota.PharmacyGroupId,
                     articlequota.sNoBatchChange,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from ARTICLEQUOTA, ARTIKELZENTRAL, KUNDE
                  where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleQuota.ArticleNo	 =	artikelzentral.artikel_nr and
                        ArticleQuota.BranchNo	 =	kunde.VertriebszentrumNr and
                        ArticleQuota.CustomerNo	 =	kunde.KundenNr and
                        ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA and
                        ArticleQuota.sNoBatchChange	 =	'1';
        exec sql open CSelListAllNoBat20;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListAllNoBat20" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListAllNoBat20;
        return CheckSql( fun, stError, "%s", "close CSelListAllNoBat20" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListAllNoBat20 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MATCHCODE,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->SDAFUEQUOTA,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListAllNoBat20" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArtikelQuota::SelListArt ***************************************************/

retClient Artikelquota_SelListArt(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelquota_SelListArt";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListArt21 cursor with hold for
                  select articlequota.BranchNo,
                     articlequota.CustomerNo,
                     kunde.matchcode,
                     articlequota.ArticleNo,
                     articlequota.Quota,
                     articlequota.KumQty,
                     articlequota.Validity,
                     articlequota.DateUpdate,
                     articlequota.uid_anlage,
                     articlequota.sDafueQuota,
                     articlequota.DateFrom,
                     articlequota.DateTo,
                     articlequota.PharmacyGroupId,
                     articlequota.sNoBatchChange,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from ARTICLEQUOTA, ARTIKELZENTRAL, outer KUNDE
                  where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleQuota.ArticleNo	 =	:d->ARTICLENO and
                        ArticleQuota.ArticleNo	 =	artikelzentral.artikel_nr and
                        ArticleQuota.BranchNo	 =	kunde.VertriebszentrumNr and
                        ArticleQuota.CustomerNo	 =	kunde.KundenNr and
                        ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA and
                        ArticleQuota.sNoBatchChange	>=	:d->SNOBATCHCHANGE;
        exec sql open CSelListArt21;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListArt21" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListArt21;
        return CheckSql( fun, stError, "%s", "close CSelListArt21" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListArt21 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MATCHCODE,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->SDAFUEQUOTA,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListArt21" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArtikelQuota::SelListArtNoBat **********************************************/

retClient Artikelquota_SelListArtNoBat(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelquota_SelListArtNoBat";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListArtNoBat22 cursor with hold for
                  select articlequota.BranchNo,
                     articlequota.CustomerNo,
                     kunde.matchcode,
                     articlequota.ArticleNo,
                     articlequota.Quota,
                     articlequota.KumQty,
                     articlequota.Validity,
                     articlequota.DateUpdate,
                     articlequota.uid_anlage,
                     articlequota.sDafueQuota,
                     articlequota.DateFrom,
                     articlequota.DateTo,
                     articlequota.PharmacyGroupId,
                     articlequota.sNoBatchChange,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from ARTICLEQUOTA, ARTIKELZENTRAL, KUNDE
                  where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleQuota.ArticleNo	 =	:d->ARTICLENO and
                        ArticleQuota.ArticleNo	 =	artikelzentral.artikel_nr and
                        ArticleQuota.BranchNo	 =	kunde.VertriebszentrumNr and
                        ArticleQuota.CustomerNo	 =	kunde.KundenNr and
                        ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA and
                        ArticleQuota.sNoBatchChange	 =	'1';
        exec sql open CSelListArtNoBat22;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListArtNoBat22" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListArtNoBat22;
        return CheckSql( fun, stError, "%s", "close CSelListArtNoBat22" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListArtNoBat22 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MATCHCODE,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->SDAFUEQUOTA,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListArtNoBat22" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArtikelQuota::SelListKnd ***************************************************/

retClient Artikelquota_SelListKnd(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelquota_SelListKnd";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListKnd23 cursor with hold for
                  select articlequota.BranchNo,
                     articlequota.CustomerNo,
                     kunde.matchcode,
                     articlequota.ArticleNo,
                     articlequota.Quota,
                     articlequota.KumQty,
                     articlequota.Validity,
                     articlequota.DateUpdate,
                     articlequota.uid_anlage,
                     articlequota.sDafueQuota,
                     articlequota.DateFrom,
                     articlequota.DateTo,
                     articlequota.PharmacyGroupId,
                     articlequota.sNoBatchChange,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from ARTICLEQUOTA, ARTIKELZENTRAL, KUNDE
                  where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleQuota.CustomerNo	 =	:d->CUSTOMERNO and
                        ArticleQuota.ArticleNo	 =	artikelzentral.artikel_nr and
                        ArticleQuota.BranchNo	 =	kunde.VertriebszentrumNr and
                        ArticleQuota.CustomerNo	 =	kunde.KundenNr and
                        ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA and
                        ArticleQuota.sNoBatchChange	>=	:d->SNOBATCHCHANGE;
        exec sql open CSelListKnd23;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListKnd23" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListKnd23;
        return CheckSql( fun, stError, "%s", "close CSelListKnd23" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListKnd23 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MATCHCODE,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->SDAFUEQUOTA,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListKnd23" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArtikelQuota::SelListKndNoBat **********************************************/

retClient Artikelquota_SelListKndNoBat(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelquota_SelListKndNoBat";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListKndNoBat24 cursor with hold for
                  select articlequota.BranchNo,
                     articlequota.CustomerNo,
                     kunde.matchcode,
                     articlequota.ArticleNo,
                     articlequota.Quota,
                     articlequota.KumQty,
                     articlequota.Validity,
                     articlequota.DateUpdate,
                     articlequota.uid_anlage,
                     articlequota.sDafueQuota,
                     articlequota.DateFrom,
                     articlequota.DateTo,
                     articlequota.PharmacyGroupId,
                     articlequota.sNoBatchChange,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from ARTICLEQUOTA, ARTIKELZENTRAL, KUNDE
                  where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleQuota.CustomerNo	 =	:d->CUSTOMERNO and
                        ArticleQuota.ArticleNo	 =	artikelzentral.artikel_nr and
                        ArticleQuota.BranchNo	 =	kunde.VertriebszentrumNr and
                        ArticleQuota.CustomerNo	 =	kunde.KundenNr and
                        ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA and
                        ArticleQuota.sNoBatchChange	 =	'1';
        exec sql open CSelListKndNoBat24;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListKndNoBat24" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListKndNoBat24;
        return CheckSql( fun, stError, "%s", "close CSelListKndNoBat24" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListKndNoBat24 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MATCHCODE,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->SDAFUEQUOTA,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListKndNoBat24" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArtikelQuota::SelQuota *****************************************************/

retClient Artikelquota_SelQuota(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelquota_SelQuota";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select articlequota.BranchNo,
                     articlequota.CustomerNo,
                     kunde.matchcode,
                     articlequota.ArticleNo,
                     articlequota.Quota,
                     articlequota.KumQty,
                     articlequota.Validity,
                     articlequota.DateUpdate,
                     articlequota.uid_anlage,
                     articlequota.sDafueQuota,
                     articlequota.DateFrom,
                     articlequota.DateTo,
                     articlequota.PharmacyGroupId,
                     articlequota.sNoBatchChange,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->MATCHCODE,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->SDAFUEQUOTA,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME
                from ARTICLEQUOTA, ARTIKELZENTRAL, KUNDE
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.CustomerNo	 =	:d->CUSTOMERNO	 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO and
                    ArticleQuota.ArticleNo	 =	artikelzentral.artikel_nr and
                    ArticleQuota.BranchNo	 =	kunde.VertriebszentrumNr and
                    ArticleQuota.CustomerNo	 =	kunde.KundenNr and
                    ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtikelQuota: Insert *******************************************************/

/* ArtikelQuota::Insert *******************************************************/

retClient Artikelquota_Insert(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelquota_Insert";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select kdgruppe from kunde
where Vertriebszentrumnr = :d->BRANCHNO and
Kundennr = :d->CUSTOMERNO and
Kdgruppe in ("13","18");
if ( ( rc=CheckSql( fun, stError, "%s", "Select KdGruppe" ) ) == IS_ERROR )
return rc;
else if ( ( rc=CheckSql( fun, stError, "%s", "Select KdGruppe" ) ) != IS_NOTFOUND )
{
sprintf( stError->spError, "Not Allowed" );
if ( bIsTrans )
{
if ( ( rc = Commit( fun, stError ) ) != IS_OK )
return rc;
}
return -5;
}
d->DATEUPDATE = AllgGetDate();
    exec sql insert into articlequota (BranchNo,
                     CustomerNo,
                     ArticleNo,
                     Quota,
                     KumQty,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     sDafueQuota,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange)
        values (:d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->ARTICLENO,
                     :d->QUOTA,
                     :d->KUMQTY,
                     :d->VALIDITY,
                     :d->DATEUPDATE,
                     :d->UID_ANLAGE,
                     :d->SDAFUEQUOTA,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->PHARMACYGROUPID,
                     :d->SNOBATCHCHANGE);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert articlequota" ) ) != IS_OK )
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



/* ArtikelQuota: Update *******************************************************/

/* ArtikelQuota::Update *******************************************************/

retClient Artikelquota_Update(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Artikelquota_Update";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

       d->DATEUPDATE = AllgGetDate();


    exec sql declare CUpdate26 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     ArticleNo,
                     Quota,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     sDafueQuota,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange
               from articlequota
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.CustomerNo	 =	:d->CUSTOMERNO	 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO and
                    ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA
              for update;
    exec sql open CUpdate26;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate26" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate26;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate26" ) ) != IS_OK )
            break;
        exec sql update articlequota set BranchNo = :d->BRANCHNO,
                     CustomerNo = :d->CUSTOMERNO,
                     ArticleNo = :d->ARTICLENO,
                     Quota = :d->QUOTA,
                     Validity = :d->VALIDITY,
                     DateUpdate = :d->DATEUPDATE,
                     uid_anlage = :d->UID_ANLAGE,
                     sDafueQuota = :d->SDAFUEQUOTA,
                     DateFrom = :d->DATEFROM,
                     DateTo = :d->DATETO,
                     PharmacyGroupId = :d->PHARMACYGROUPID,
                     sNoBatchChange = :d->SNOBATCHCHANGE where current of CUpdate26;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate26" ) ) != IS_OK )
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



/* ArtikelQuota: Select *******************************************************/

/* ArtikelQuota::Delete *******************************************************/

retClient Artikelquota_Delete(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Artikelquota_Delete";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete27 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     ArticleNo,
                     Quota,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     sDafueQuota,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange
               from articlequota
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.CustomerNo	 =	:d->CUSTOMERNO	 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO and
                    ArticleQuota.Validity	 =	:d->VALIDITY and
                    ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA
              for update;
    exec sql open CDelete27;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete27" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete27;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete27" ) ) != IS_OK )
            break;
        exec sql delete from articlequota where current of CDelete27;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete27" ) ) != IS_OK )
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

/* ArtikelQuota::DeleteAllArt *************************************************/

retClient Artikelquota_DeleteAllArt(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Artikelquota_DeleteAllArt";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteAllArt28 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     ArticleNo,
                     Quota,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     sDafueQuota,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange
               from articlequota
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO and
                    ArticleQuota.Validity	 =	:d->VALIDITY and
                    ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA
              for update;
    exec sql open CDeleteAllArt28;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteAllArt28" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteAllArt28;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteAllArt28" ) ) != IS_OK )
            break;
        exec sql delete from articlequota where current of CDeleteAllArt28;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteAllArt28" ) ) != IS_OK )
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

/* ArtikelQuota::DeleteAllKnd *************************************************/

retClient Artikelquota_DeleteAllKnd(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    int iTrans = 0;
    char *fun = "Artikelquota_DeleteAllKnd";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDeleteAllKnd29 cursor with hold for
              select BranchNo,
                     CustomerNo,
                     ArticleNo,
                     Quota,
                     Validity,
                     DateUpdate,
                     uid_anlage,
                     sDafueQuota,
                     DateFrom,
                     DateTo,
                     PharmacyGroupId,
                     sNoBatchChange
               from articlequota
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.CustomerNo	 =	:d->CUSTOMERNO and
                    ArticleQuota.Validity	 =	:d->VALIDITY and
                    ArticleQuota.ArticleNo not in
                    (select articleno from maxarticlequota) and
                    ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA
              for update;
    exec sql open CDeleteAllKnd29;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDeleteAllKnd29" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDeleteAllKnd29;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDeleteAllKnd29" ) ) != IS_OK )
            break;
        exec sql delete from articlequota where current of CDeleteAllKnd29;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDeleteAllKnd29" ) ) != IS_OK )
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



/* ArtikelQuota: Other ********************************************************/

/* ArtikelQuota::CheckQuota ***************************************************/

retClient Artikelquota_CheckQuota(artikelquotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelquota_CheckQuota";
    exec sql begin declare section;
    artikelquotaS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
       d->DATEFROM = AllgGetDate();

        exec sql declare CCheckQuota1 cursor with hold for
				select  (articlequota.Quota - articlequota.KumQty),
                     articlequota.CustomerNo
                from ARTICLEQUOTA
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.CustomerNo	 =	:d->CUSTOMERNO	 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO    and
                    ArticleQuota.Datefrom	<=	:d->DATEFROM     and
                    ArticleQuota.Dateto	        >=	:d->DATEFROM     and
		    ArticleQuota.pharmacygroupid =	' '	
		union select (articlequota.Quota - articlequota.KumQty),
                     articlequota.CustomerNo
                from ARTICLEQUOTA
              where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO and
                    ArticleQuota.Datefrom	<=	:d->DATEFROM     and
                    ArticleQuota.Dateto	        >=	:d->DATEFROM     and
                    ArticleQuota.sDafueQuota	 =	:d->SDAFUEQUOTA and
		    ArticleQuota.pharmacygroupid in
		    (select pharmacygroupid
		    from customerpharmacygr
		    where customerpharmacygr.branchno = :d->BRANCHNO and
		    customerno = :d->CUSTOMERNO )
		    order by 1;
        exec sql open CCheckQuota1;
	    if ((rc = CheckSql( fun, stError, "%s", "open CCheckQuota1" )) == IS_ERROR )
		    return rc;
	}
    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        return rc;
    }


    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CCheckQuota1 into :d->QUOTA,
                     :d->CUSTOMERNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CCheckQuota" )) == IS_ERROR )
	   return rc;
    if (d->QUOTAINHERITANCE)
    {
	if (SQLCODE == 100 && a->FETCH_REL == SET_OPEN )
	{
	    exec sql select articlequota.Quota,articlequota.CustomerNo
                into :d->QUOTA,:d->CUSTOMERNO
		from ARTICLEQUOTA
		where ArticleQuota.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleQuota.CustomerNo	 =	0		 and
                    ArticleQuota.ArticleNo	 =	:d->ARTICLENO    and
                    ArticleQuota.Datefrom	<=	:d->DATEFROM     and
                    ArticleQuota.Dateto		>=	:d->DATEFROM	 and
		    ArticleQuota.pharmacygroupid = ' ';
	}
    }
    if ((rc=CheckSql( fun, stError, "%s", "fetch CCheckQuota1" )) == IS_ERROR )
	   return rc;
    return rc;
}

/* ArtikelQuota::SelKumVz *****************************************************/

retClient Artikelquota_SelKumVz(artikelquotaS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "Artikelquota_SelKumVz";
exec sql begin declare section;
artikelquotaS *d;
exec sql end declare section;

d = a;

if ( a->FETCH_REL == SET_OPEN )
{
   exec sql declare CSelKumVz0 cursor with hold for
     select count(*),
        ArticleNo,
        Validity,
        Artikel_name,
        Einheit
     from articlequota,artikelzentral
     where ArticleQuota.BranchNo = :d->BRANCHNO
     and ArticleQuota.sDafueQuota = :d->SDAFUEQUOTA
     and ArticleQuota.articleno = artikelzentral.artikel_nr
     and ArticleQuota.sNoBatchChange >= :d->SNOBATCHCHANGE
     group by articleno,validity,artikel_name,einheit
     order by artikel_name,einheit;

   exec sql open CSelKumVz0;
   if ( ( rc=CheckSql( fun, stError, "%s", "open CSelKumVz0" ) ) != IS_OK )
     return rc;
}

if ( a->FETCH_REL == SET_CLOSE )
{
   if ( bIsTrans )
   {
     if ( ( rc = Commit( fun, stError ) ) != IS_OK )
       return rc;
   }
   exec sql close CSelKumVz0;
     return CheckSql( fun, stError, "%s", "close CSelKumVz0" );
}

if ( bIsTrans )
{
   if ( ( rc = Begin( fun, stError ) ) != IS_OK )
     return rc;
}
exec sql fetch CSelKumVz0 into :d->CUSTOMERNO,
   :d->ARTICLENO,
   :d->VALIDITY,
   :d->ARTIKEL_NAME,
   :d->EINHEIT;
if ((rc=CheckSql( fun, stError, "%s", "fetch CSelKumVz0" )) == IS_ERROR )
   return rc;
return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : ArtikelQuotaPf.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:23 2022                                         */
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
#include "artikel.h"

/* ArtikelQuotaPf: Select *****************************************************/



/* ArtikelQuotaPf: Insert *****************************************************/



/* ArtikelQuotaPf: Update *****************************************************/



/* ArtikelQuotaPf: Select *****************************************************/



/* ArtikelQuotaPf: Other ******************************************************/

/* ArtikelQuotaPf::CopyQuota **************************************************/

retClient Artikelquotapf_CopyQuota(artikelquotapfS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Artikelquotapf_CopyQupta";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
short sBranchno;
long lArticleno;
long lQuota;
long lDateFrom;
long lDateTo;
char cValidity[2];
char cDafueQuota[2];
char cNoBatchChange[2];
artikelquotapfS *d;
exec sql end declare section;

d = a;
exec sql declare CSelcopyquota cursor with hold for
  select branchno,articleno,quota,validity,sdafuequota,datefrom,dateto,snobatchchange
  from articlequota
  where
  branchno = :d->BRANCHNO and
  customerno = :d->CUSTOMERNO and
  ArticleQuota.sDafueQuota = :d->SDAFUEQUOTA;
exec sql open CSelcopyquota;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
d->DATEUPDATE = AllgGetDate();
for(;;)
{
  exec sql fetch CSelcopyquota into :sBranchno,:lArticleno,:lQuota,:cValidity,:cDafueQuota,:lDateFrom,:lDateTo,:cNoBatchChange;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelcopyquota;" ) ) != IS_OK )
    break;
  exec sql insert into articlequota
  (Branchno,Customerno,Articleno,Quota,Validity,DateUpdate,Uid_Anlage,sDafueQuota,DateFrom,DateTo,sNoBatchChange)
  values
  (:sBranchno,:d->WERT,:lArticleno,:lQuota,:cValidity,:d->DATEUPDATE,:d->UID_ANLAGE,:cDafueQuota,:lDateFrom,:lDateTo,:cNoBatchChange);
  if ( ( rc=CheckSql( fun, stError,  "%s", "insert CSelcopyquota;" ) ) != IS_OK )
  {
    if(rc == IS_EXISTS) continue;
    else break;
  }
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* ArtikelQuotaPf::DeleteKundeEKG *********************************************/

retClient Artikelquotapf_DeleteKundeEKG(artikelquotapfS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Artikelquotapf_DeleteKundeEKG";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
artikelquotapfS *d;
exec sql end declare section;

d = a;
exec sql declare CSelArtikelquotaDelEK1 cursor with hold for
  select customerno
  from customerpharmacygr
  where
  branchno = :d->BRANCHNO and
  pharmacygroupid = :d->KZKDKLASSE;
exec sql open CSelArtikelquotaDelEK1;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;

for(;;)
{
  exec sql fetch CSelArtikelquotaDelEK1 into :d->CUSTOMERNO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotaDelEK1;" ) ) != IS_OK )
    break;
  exec sql delete from articlequota
  where
    BranchNo = :d->BRANCHNO
  and 
    CustomerNo = :d->CUSTOMERNO
  and
    Articleno = :d->ARTICLENO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "delete CSelArtikelquotaDelEK1;" ) ) == IS_NOTFOUND ) continue;
  if ( rc != IS_OK ) break;
  count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* ArtikelQuotaPf::InsertKlasse ***********************************************/

retClient Artikelquotapf_InsertKlasse(artikelquotapfS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Artikelquotapf_InsertKlasse";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
artikelquotapfS *d;
exec sql end declare section;

d = a;
exec sql declare CSelArtikelquotapf0 cursor with hold for
  select kundennr
  from kunde
  where
  vertriebszentrumnr = :d->BRANCHNO and
  kzkdklasse like :d->KZKDKLASSE and
  (originalfilialnr = 0 or
  originalfilialnr = vertriebszentrumnr ) and
  kdgruppe not in ("09","13","18");
exec sql open CSelArtikelquotapf0;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
d->DATEUPDATE = AllgGetDate();
for(;;)
{
  exec sql fetch CSelArtikelquotapf0 into :d->CUSTOMERNO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotapf0;" ) ) != IS_OK )
    break;
  exec sql insert into articlequota(
    BranchNo,
    CustomerNo,
    ArticleNo,
    Quota,
    KumQty,
    Validity,
    DateUpdate,
    Uid_Anlage,
    sDafueQuota,
    DateFrom,
    DateTo,
    sNoBatchChange)
  values(
    :d->BRANCHNO,
    :d->CUSTOMERNO,
    :d->ARTICLENO,
    :d->QUOTA,
    0,
    :d->VALIDITY,
    :d->DATEUPDATE,
    :d->UID_ANLAGE,
    :d->SDAFUEQUOTA,
    :d->DATEFROM,
    :d->DATETO,
    :d->SNOBATCHCHANGE);
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotapf0;" ) ) != IS_OK )
  {
    if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
      break;
    else
      continue;
  }
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* ArtikelQuotaPf::InsertKlasse09 *********************************************/

retClient Artikelquotapf_InsertKlasse09(artikelquotapfS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Artikelquotapf_InsertKlasse09";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
artikelquotapfS *d;
exec sql end declare section;

d = a;
exec sql declare CSelArtikelquotapf2 cursor with hold for
  select kundennr
  from kunde
  where
  vertriebszentrumnr = :d->BRANCHNO and
  kzkdklasse like :d->KZKDKLASSE and
  (originalfilialnr = 0 or
  originalfilialnr = vertriebszentrumnr ) and
  kdgruppe not in ("13","18");
exec sql open CSelArtikelquotapf2;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
d->DATEUPDATE = AllgGetDate();
for(;;)
{
  exec sql fetch CSelArtikelquotapf2 into :d->CUSTOMERNO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotapf2;" ) ) != IS_OK )
    break;
  exec sql insert into articlequota(
    BranchNo,
    CustomerNo,
    ArticleNo,
    Quota,
    KumQty,
    Validity,
    DateUpdate,
    Uid_Anlage,
    sDafueQuota,
    DateFrom,
    DateTo,
    sNoBatchChange)
  values(
    :d->BRANCHNO,
    :d->CUSTOMERNO,
    :d->ARTICLENO,
    :d->QUOTA,
    0,
    :d->VALIDITY,
    :d->DATEUPDATE,
    :d->UID_ANLAGE,
    :d->SDAFUEQUOTA,
    :d->DATEFROM,
    :d->DATETO,
    :d->SNOBATCHCHANGE);
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotapf2;" ) ) != IS_OK )
  {
    if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
      break;
    else
      continue;
  }
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* ArtikelQuotaPf::InsertKundeEKG *********************************************/

retClient Artikelquotapf_InsertKundeEKG(artikelquotapfS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Artikelquotapf_InsertKundeEKG";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
artikelquotapfS *d;
exec sql end declare section;

d = a;
exec sql declare CSelArtikelquotaEK0 cursor with hold for
  select customerno
  from customerpharmacygr
  where
  branchno = :d->BRANCHNO and
  pharmacygroupid = :d->KZKDKLASSE;
exec sql open CSelArtikelquotaEK0;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
d->DATEUPDATE = AllgGetDate();
for(;;)
{
  exec sql fetch CSelArtikelquotaEK0 into :d->CUSTOMERNO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotaEK0;" ) ) != IS_OK )
    break;
  exec sql insert into articlequota(
    BranchNo,
    CustomerNo,
    ArticleNo,
    Quota,
    KumQty,
    Validity,
    DateUpdate,
    Uid_Anlage,
    sDafueQuota,
    DateFrom,
    DateTo,
    sNoBatchChange)
  values(
    :d->BRANCHNO,
    :d->CUSTOMERNO,
    :d->ARTICLENO,
    :d->QUOTA,
    0,
    :d->VALIDITY,
    :d->DATEUPDATE,
    :d->UID_ANLAGE,
    :d->SDAFUEQUOTA,
    :d->DATEFROM,
    :d->DATETO,
    :d->SNOBATCHCHANGE);
  if ( ( rc=CheckSql( fun, stError,  "%s", "insert articlequota;" ) ) != IS_OK )
  {
    if(sqlca.sqlcode != -239 && sqlca.sqlcode != -268)
      break;
    else
      continue;
  }
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* ArtikelQuotaPf::UpdateKundeEKG *********************************************/

retClient Artikelquotapf_UpdateKundeEKG(artikelquotapfS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Artikelquotapf_UpdateKundeEKG";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
artikelquotapfS *d;
exec sql end declare section;

d = a;
exec sql declare CSelArtikelquotaEK1 cursor with hold for
  select customerno
  from customerpharmacygr
  where
  branchno = :d->BRANCHNO and
  pharmacygroupid = :d->KZKDKLASSE;
exec sql open CSelArtikelquotaEK1;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
d->DATEUPDATE = AllgGetDate();
for(;;)
{
  exec sql fetch CSelArtikelquotaEK1 into :d->CUSTOMERNO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotaEK1;" ) ) != IS_OK )
    break;
  exec sql update articlequota
  set Quota = :d->QUOTA,
  DateUpdate = :d->DATEUPDATE,
  DateFrom = :d->DATEFROM,
  DateTo = :d->DATETO,
  Uid_Anlage = :d->UID_ANLAGE,
  sNoBatchChange = :d->SNOBATCHCHANGE
  where
    BranchNo = :d->BRANCHNO
  and 
    CustomerNo = :d->CUSTOMERNO
  and
    Articleno = :d->ARTICLENO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "update CSelArtikelquotaEK1;" ) ) != IS_OK ) break;
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* ArtikelQuotaPf::UpdateQuota ************************************************/

retClient Artikelquotapf_UpdateQuota(artikelquotapfS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Artikelquotapf_UpdateQupta";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
artikelquotapfS *d;
exec sql end declare section;

d = a;
exec sql declare CSelArtikelquotapf1 cursor with hold for
  select kundennr
  from kunde
  where
  vertriebszentrumnr = :d->BRANCHNO and
  kzkdklasse like :d->KZKDKLASSE and
  kdgruppe not in ("09","13","18") and
  (originalfilialnr = 0 or
  originalfilialnr = vertriebszentrumnr );
exec sql open CSelArtikelquotapf1;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
d->DATEUPDATE = AllgGetDate();
for(;;)
{
  exec sql fetch CSelArtikelquotapf1 into :d->CUSTOMERNO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotapf1;" ) ) != IS_OK )
    break;
  exec sql update articlequota
  set Quota = :d->QUOTA,
  DateUpdate = :d->DATEUPDATE,
  Uid_Anlage = :d->UID_ANLAGE,
  sNoBatchChange = :d->SNOBATCHCHANGE
  where
    BranchNo = :d->BRANCHNO
  and 
    CustomerNo = :d->CUSTOMERNO
  and
    Articleno = :d->ARTICLENO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "update CSelArtikelquotapf1;" ) ) != IS_OK ) break;
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}

/* ArtikelQuotaPf::UpdateQuota09 **********************************************/

retClient Artikelquotapf_UpdateQuota09(artikelquotapfS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
retClient rc2;
char *fun = "Artikelquotapf_UpdateQupta09";
int iTrans = 0;
int count = 0;
exec sql begin declare section;
artikelquotapfS *d;
exec sql end declare section;

d = a;
exec sql declare CSelArtikelquotapf3 cursor with hold for
  select kundennr
  from kunde
  where
  vertriebszentrumnr = :d->BRANCHNO and
  kzkdklasse like :d->KZKDKLASSE and
  kdgruppe not in ("13","18") and
  (originalfilialnr = 0 or
  originalfilialnr = vertriebszentrumnr );
exec sql open CSelArtikelquotapf3;
if ( ( rc = Begin( fun, stError ) ) != IS_OK )
  return rc;
d->DATEUPDATE = AllgGetDate();
for(;;)
{
  exec sql fetch CSelArtikelquotapf3 into :d->CUSTOMERNO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CSelArtikelquotapf3;" ) ) != IS_OK )
    break;
  exec sql update articlequota
  set Quota = :d->QUOTA,
  DateUpdate = :d->DATEUPDATE,
  Uid_Anlage = :d->UID_ANLAGE,
  sNoBatchChange = :d->SNOBATCHCHANGE
  where
    BranchNo = :d->BRANCHNO
  and 
    CustomerNo = :d->CUSTOMERNO
  and
    Articleno = :d->ARTICLENO;
  if ( ( rc=CheckSql( fun, stError,  "%s", "update CSelArtikelquotapf3;" ) ) != IS_OK ) break;
  else count++;
  if ( ( iTrans++ % 500 ) == 0 )
  {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
      return rc;
    if ( ( rc = Begin( fun, stError ) ) != IS_OK )
      return rc;
  }
}
if ( rc < 0 )
{
  exec sql rollback work;
  return rc;
}
if ( ( rc2 = Commit( fun, stError ) ) != IS_OK )
  return rc2;
d->CUSTOMERNO = count;
return rc == IS_NOTFOUND ? (retClient)0 : (retClient)rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : ArtikelReserve.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:36 2022                                         */
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
#include "artikel.h"

/* ArtikelReserve: Select *****************************************************/

/* ArtikelReserve::SelArt *****************************************************/

retClient Artikelreserve_SelArt(artikelreserveS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelreserve_SelArt";
    exec sql begin declare section;
    artikelreserveS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select articlereservation.BranchNo,
                     articlereservation.PharmacyGroupId,
                     articlereservation.ArticleNo,
                     articlereservation.ReservType,
                     articlereservation.MaxQty,
                     articlereservation.ReservedQty,
                     articlereservation.ReservePct
                into :d->BRANCHNO,
                     :d->PHARMACYGROUPID,
                     :d->ARTICLENO,
                     :d->RESERVTYPE,
                     :d->MAXQTY,
                     :d->RESERVEDQTY,
                     :d->RESERVEPCT
                from ArticleReservation
              where ArticleReservation.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleReservation.ArticleNo	 =	:d->ARTICLENO and
                    ArticleReservation.ReservType	 =	:d->RESERVTYPE;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

/* ArtikelReserve::SelArtKnd **************************************************/

retClient Artikelreserve_SelArtKnd(artikelreserveS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelreserve_SelArtKnd";
    exec sql begin declare section;
    artikelreserveS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select articlereservation.BranchNo,
                     articlereservation.PharmacyGroupId,
                     articlereservation.ArticleNo,
                     articlereservation.ReservType,
                     articlereservation.MaxQty,
                     articlereservation.ReservedQty,
                     articlereservation.ReservePct
                into :d->BRANCHNO,
                     :d->PHARMACYGROUPID,
                     :d->ARTICLENO,
                     :d->RESERVTYPE,
                     :d->MAXQTY,
                     :d->RESERVEDQTY,
                     :d->RESERVEPCT
                from ARTICLERESERVATION, CUSTOMERPHARMACYGR
              where ArticleReservation.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleReservation.ArticleNo	 =	:d->ARTICLENO	 and
                    customerpharmacygr.BranchNo	 =	ArticleReservation.BranchNo and
                    customerpharmacygr.PharmacyGroupId	 =	ArticleReservation.PharmacyGroupId and
                    customerpharmacygr.CustomerNo	 =	:d->CUSTOMERNO and
                    ArticleReservation.ReservType	 =	:d->RESERVTYPE;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtikelReserve: Insert *****************************************************/

/* ArtikelReserve::Insert *****************************************************/

retClient Artikelreserve_Insert(artikelreserveS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelreserve_Insert";
    exec sql begin declare section;
    artikelreserveS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into articlereservation (BranchNo,
                     PharmacyGroupId,
                     ArticleNo,
                     ReservType,
                     MaxQty,
                     ReservedQty,
                     ReservePct)
        values (:d->BRANCHNO,
                     :d->PHARMACYGROUPID,
                     :d->ARTICLENO,
                     :d->RESERVTYPE,
                     :d->MAXQTY,
                     :d->RESERVEDQTY,
                     :d->RESERVEPCT);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert articlereservation" ) ) != IS_OK )
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



/* ArtikelReserve: Update *****************************************************/

/* ArtikelReserve::Update *****************************************************/

retClient Artikelreserve_Update(artikelreserveS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Artikelreserve_Update";
    exec sql begin declare section;
    artikelreserveS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate32 cursor with hold for
              select BranchNo,
                     PharmacyGroupId,
                     ArticleNo,
                     ReservType,
                     MaxQty,
                     ReservedQty,
                     ReservePct
               from ArticleReservation
              where ArticleReservation.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleReservation.ArticleNo	 =	:d->ARTICLENO	 and
                    ArticleReservation.PharmacyGroupId	 =	:d->PHARMACYGROUPID	 and
                    ArticleReservation.ReservType	 =	:d->RESERVTYPE
              for update;
    exec sql open CUpdate32;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate32" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate32;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate32" ) ) != IS_OK )
            break;
        exec sql update articlereservation set BranchNo = :d->BRANCHNO,
                     PharmacyGroupId = :d->PHARMACYGROUPID,
                     ArticleNo = :d->ARTICLENO,
                     ReservType = :d->RESERVTYPE,
                     MaxQty = :d->MAXQTY,
                     ReservedQty = :d->RESERVEDQTY,
                     ReservePct = :d->RESERVEPCT where current of CUpdate32;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate32" ) ) != IS_OK )
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



/* ArtikelReserve: Select *****************************************************/

/* ArtikelReserve::Delete *****************************************************/

retClient Artikelreserve_Delete(artikelreserveS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Artikelreserve_Delete";
    exec sql begin declare section;
    artikelreserveS *d;
    exec sql end declare section;

    d = a;

    exec sql update artikellokal
set artikellokal.bestand = artikellokal.bestand + (select
articlereservation.reservedqty from articlereservation
where articlereservation.branchno = :d->BRANCHNO
and articlereservation.articleno = :d->ARTICLENO)
where artikellokal.filialnr = :d->BRANCHNO
and artikellokal.artikel_nr = :d->ARTICLENO;
    exec sql declare CDelete33 cursor with hold for
              select BranchNo,
                     PharmacyGroupId,
                     ArticleNo,
                     ReservType,
                     MaxQty,
                     ReservedQty,
                     ReservePct
               from ArticleReservation
              where ArticleReservation.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleReservation.ArticleNo	 =	:d->ARTICLENO	 and
                    ArticleReservation.PharmacyGroupId	 =	:d->PHARMACYGROUPID	 and
                    ArticleReservation.ReservType	 =	:d->RESERVTYPE
              for update;
    exec sql open CDelete33;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete33" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete33;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete33" ) ) != IS_OK )
            break;
        exec sql delete from articlereservation where current of CDelete33;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete33" ) ) != IS_OK )
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



/* ArtikelReserve: Other ******************************************************/

/* ArtikelReserve::InsertBestand **********************************************/

retClient Artikelreserve_InsertBestand(artikelreserveS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelreserve_Insert";
    exec sql begin declare section;
    artikelreserveS *d;
    long lBestand;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select bestand into :lBestand from artikellokal
       where artikel_nr = :d->ARTICLENO
       and   filialnr = :d->BRANCHNO;
    d->RESERVEDQTY = lBestand * d->RESERVEPCT / 100;
    if(d->RESERVEDQTY > d->MAXQTY) d->RESERVEDQTY = d->MAXQTY;
    lBestand = lBestand - d->RESERVEDQTY;
    exec sql insert into articlereservation (BranchNo,
                     PharmacyGroupId,
                     ArticleNo,
                     ReservType,
                     MaxQty,
                     ReservedQty,
                     ReservePct)
        values (:d->BRANCHNO,
                     :d->PHARMACYGROUPID,
                     :d->ARTICLENO,
                     :d->RESERVTYPE,
                     :d->MAXQTY,
                     :d->RESERVEDQTY,
                     :d->RESERVEPCT);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert articlereservation" ) ) != IS_OK )
    {
        if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
        {
            exec sql rollback work;
            return rc;
        }
        return rc;
    }
    exec sql update artikellokal
       set bestand = :lBestand
       where artikel_nr = :d->ARTICLENO
       and   filialnr = :d->BRANCHNO;

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}

/* ArtikelReserve::ReservStockAbs *********************************************/

retClient Artikelreserve_ReservStockAbs(artikelreserveS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelreserve_Insert";
    int kzupd;
    exec sql begin declare section;
    artikelreserveS *d;
    long lBestand;
    long lBestandReserv;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select bestand into :lBestand from artikellokal
       where artikel_nr = :d->ARTICLENO
       and   filialnr = :d->BRANCHNO;
    exec sql select ReservedQty into :lBestandReserv from articlereservation
       where articleno = :d->ARTICLENO
       and   branchno = :d->BRANCHNO
       and   reservtype = :d->RESERVTYPE;
    if(SQLCODE == SQLNOTFOUND)
    {
       lBestandReserv = 0;
       kzupd = 0;
    }
    else
    {
       kzupd = 1;
    }
    lBestand = lBestandReserv + lBestand;
    if(d->RESERVEDQTY > lBestand)
    {
       lBestandReserv = lBestand;
       lBestand = 0;
    }
    else
    {
       lBestand = lBestand - d->RESERVEDQTY;
       lBestandReserv = d->RESERVEDQTY;
    }
    d->RESERVEDQTY = lBestandReserv;
    if(kzupd == 1)
    {
       exec sql update articlereservation
          set   PharmacyGroupId = :d->PHARMACYGROUPID,
                ReservType = :d->RESERVTYPE,
                MaxQty = :d->RESERVEDQTY,
                ReservedQty = :d->RESERVEDQTY,
                ReservePct = :d->RESERVEPCT
          where articleno = :d->ARTICLENO
          and   branchno = :d->BRANCHNO
          and   reservtype = :d->RESERVTYPE;
       if ( ( rc = CheckSql( fun, stError,  "%s", "update articlereservation" ) ) != IS_OK )
       {
          if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
          {
            exec sql rollback work;
            return rc;
          }
          return rc;
       }
    }
    else
    {
       exec sql insert into articlereservation (BranchNo,
                     PharmacyGroupId,
                     ArticleNo,
                     ReservType,
                     MaxQty,
                     ReservedQty,
                     ReservePct)
        values (:d->BRANCHNO,
                     :d->PHARMACYGROUPID,
                     :d->ARTICLENO,
                     :d->RESERVTYPE,
                     :d->RESERVEDQTY,
                     :d->RESERVEDQTY,
                     :d->RESERVEPCT);
       if ( ( rc = CheckSql( fun, stError,  "%s", "insert articlereservation" ) ) != IS_OK )
       {
          if ( bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND) )
          {
            exec sql rollback work;
            return rc;
          }
          return rc;
       }
    }
    exec sql update artikellokal
       set bestand = :lBestand
       where artikel_nr = :d->ARTICLENO
       and   filialnr = :d->BRANCHNO;

    if ( bIsTrans )
    {
        if ( ( rc = Commit( fun, stError ) ) != IS_OK )
            return rc;
    }
    return rc;
}

/* ArtikelReserve::SelListBestand *********************************************/

retClient Artikelreserve_SelListBestand(artikelreserveS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "ArtikelReserve_SelListBestand";
    exec sql begin declare section;
    artikelreserveS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListBst0 cursor with hold for
                 select articlereservation.BranchNo,
                     articlereservation.PharmacyGroupId,
                     articlereservation.ArticleNo,
                     articlereservation.ReservType,
                     artikellokal.Bestand,
                     articlereservation.ReservedQty,
                     articlereservation.ReservePct
                from ArticleReservation,Artikellokal
              where ArticleReservation.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleReservation.ReservType = :d->RESERVTYPE and
                    ArticleReservation.ArticleNo =	artikellokal.artikel_nr and
                    ArticleReservation.BranchNo	 =	artikellokal.filialnr
                    order by articlereservation.ArticleNo;
        exec sql open CSelListBst0;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListBst0" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListBst0;
        return CheckSql( fun, stError, "%s", "close CSelListBst0" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListBst0 into :d->BRANCHNO,
                     :d->PHARMACYGROUPID,
                     :d->ARTICLENO,
                     :d->RESERVTYPE,
                     :d->MAXQTY,
                     :d->RESERVEDQTY,
                     :d->RESERVEPCT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListBst0" )) == IS_ERROR )
        return rc;
    return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : ArtikelText.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:38 2022                                         */
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
#include "artikel.h"

/* ArtikelText: Select ********************************************************/

/* ArtikelText::Select ********************************************************/

retClient Artikeltext_Select(artikeltextS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikeltext_Select";
    exec sql begin declare section;
    artikeltextS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select articletext.BranchNo,
                     articletext.textkey,
                     articletext.text,
                     articletext.displayonscreen,
                     articletext.TextHospital
                into :d->BRANCHNO,
                     :d->TEXTKEY,
                     :d->TEXT,
                     :d->DISPLAYONSCREEN,
                     :d->TEXTHOSPITAL
                from ARTICLETEXT
              where articletext.BranchNo	 =	:d->BRANCHNO	 and
                    articletext.textkey	 =	:d->TEXTKEY	 and
                    articletext.displayonscreen	 =	"1";
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtikelText: Insert ********************************************************/



/* ArtikelText: Update ********************************************************/



/* ArtikelText: Select ********************************************************/



/* ArtikelText: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : ArtikelVerfall.cxx                                               */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:40 2022                                         */
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
#include "artikel.h"

/* ArtikelVerfall: Select *****************************************************/

/* ArtikelVerfall::CheckShortExpiry *******************************************/

retClient Artikelverfall_CheckShortExpiry(artikelverfallS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Artikelverfall_CheckShortExpiry";
    exec sql begin declare section;
    artikelverfallS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikellagerort.filialnr,
                     artikellagerort.artikel_nr,
                     artikellagerort.datumverfall
                into :d->FILIALNR,
                     :d->ARTIKEL_NR,
                     :d->DATUMVERFALL
                from artikellagerort
              where artikellagerort.filialnr	 =	:d->FILIALNR	 and
                    artikellagerort.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    artikellagerort.datumverfall	<	:d->DATUMVERFALL	 and
                    artikellagerort.datumverfall	>	0;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* ArtikelVerfall: Insert *****************************************************/



/* ArtikelVerfall: Update *****************************************************/



/* ArtikelVerfall: Select *****************************************************/



/* ArtikelVerfall: Other ******************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : AticleAux.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:43 2022                                         */
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
#include "artikel.h"

/* AticleAux: Select **********************************************************/

/* AticleAux::SelList *********************************************************/

retClient Aticleaux_SelList(aticleauxS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Aticleaux_SelList";
    exec sql begin declare section;
    aticleauxS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList36 cursor with hold for
                  select articleauxbranch.BranchNo,
                     articleauxbranch.ArticleNo,
                     articleauxbranch.Ranking,
                     articleauxbranch.AuxBranchNo
                from ARTICLEAUXBRANCH
                  where ArticleAuxBranch.BranchNo	 =	:d->BRANCHNO	 and
                        ArticleAuxBranch.ArticleNo	 =	:d->ARTICLENO;
        exec sql open CSelList36;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList36" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList36;
        return CheckSql( fun, stError, "%s", "close CSelList36" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList36 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->RANKING,
                     :d->AUXBRANCHNO;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList36" )) == IS_ERROR )
        return rc;
    return rc;
}



/* AticleAux: Insert **********************************************************/

/* AticleAux::Insert **********************************************************/

retClient Aticleaux_Insert(aticleauxS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Aticleaux_Insert";
    exec sql begin declare section;
    aticleauxS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into articleauxbranch (BranchNo,
                     ArticleNo,
                     Ranking,
                     AuxBranchNo)
        values (:d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->RANKING,
                     :d->AUXBRANCHNO);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert articleauxbranch" ) ) != IS_OK )
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



/* AticleAux: Update **********************************************************/

/* AticleAux::Update **********************************************************/

retClient Aticleaux_Update(aticleauxS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Aticleaux_Update";
    exec sql begin declare section;
    aticleauxS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate37 cursor with hold for
              select BranchNo,
                     ArticleNo,
                     Ranking,
                     AuxBranchNo
               from ARTICLEAUXBRANCH
              where ArticleAuxBranch.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleAuxBranch.ArticleNo	 =	:d->ARTICLENO	 and
                    ArticleAuxBranch.AuxBranchNo	 =	:d->AUXBRANCHNO
              for update;
    exec sql open CUpdate37;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate37" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate37;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate37" ) ) != IS_OK )
            break;
        exec sql update articleauxbranch set BranchNo = :d->BRANCHNO,
                     ArticleNo = :d->ARTICLENO,
                     Ranking = :d->RANKING,
                     AuxBranchNo = :d->AUXBRANCHNO where current of CUpdate37;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate37" ) ) != IS_OK )
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



/* AticleAux: Select **********************************************************/

/* AticleAux::Delete **********************************************************/

retClient Aticleaux_Delete(aticleauxS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Aticleaux_Delete";
    exec sql begin declare section;
    aticleauxS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete38 cursor with hold for
              select BranchNo,
                     ArticleNo,
                     Ranking,
                     AuxBranchNo
               from ARTICLEAUXBRANCH
              where ArticleAuxBranch.BranchNo	 =	:d->BRANCHNO	 and
                    ArticleAuxBranch.ArticleNo	 =	:d->ARTICLENO	 and
                    ArticleAuxBranch.AuxBranchNo	 =	:d->AUXBRANCHNO
              for update;
    exec sql open CDelete38;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete38" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete38;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete38" ) ) != IS_OK )
            break;
        exec sql delete from articleauxbranch where current of CDelete38;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete38" ) ) != IS_OK )
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



/* AticleAux: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CCode.cxx                                                        */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:47 2022                                         */
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
#include "artikel.h"

/* CCode: Select **************************************************************/

/* CCode::Sel *****************************************************************/

retClient Ccode_Sel(ccodeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Ccode_Sel";
    exec sql begin declare section;
    ccodeS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSel39 cursor with hold for
                  select countrycodes.BranchNo,
                     countrycodes.InfoCode,
                     countrycodes.ArticleActiv,
                     countrycodes.AuxDelivery,
                     countrycodes.SeraCode,
                     countrycodes.PrintCode,
                     countrycodes.XMLCode,
                     countrycodes.XMLText
                from COUNTRYCODES
                  where CountryCodes.BranchNo	 =	:d->BRANCHNO;
        exec sql open CSel39;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSel39" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSel39;
        return CheckSql( fun, stError, "%s", "close CSel39" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSel39 into :d->BRANCHNO,
                     :d->INFOCODE,
                     :d->ARTICLEACTIV,
                     :d->AUXDELIVERY,
                     :d->SERACODE,
                     :d->PRINTCODE,
                     :d->XMLCODE,
                     :d->XMLTEXT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSel39" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CCode: Insert **************************************************************/

/* CCode::Insert **************************************************************/

retClient Ccode_Insert(ccodeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Ccode_Insert";
    exec sql begin declare section;
    ccodeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into countrycodes (BranchNo,
                     InfoCode,
                     ArticleActiv,
                     AuxDelivery,
                     SeraCode,
                     PrintCode,
                     XMLCode,
                     XMLText)
        values (:d->BRANCHNO,
                     :d->INFOCODE,
                     :d->ARTICLEACTIV,
                     :d->AUXDELIVERY,
                     :d->SERACODE,
                     :d->PRINTCODE,
                     :d->XMLCODE,
                     :d->XMLTEXT);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert countrycodes" ) ) != IS_OK )
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



/* CCode: Update **************************************************************/

/* CCode::Update **************************************************************/

retClient Ccode_Update(ccodeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Ccode_Update";
    exec sql begin declare section;
    ccodeS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate40 cursor with hold for
              select BranchNo,
                     InfoCode,
                     ArticleActiv,
                     AuxDelivery,
                     SeraCode,
                     PrintCode,
                     XMLCode,
                     XMLText
               from COUNTRYCODES
              where CountryCodes.BranchNo	 =	:d->BRANCHNO	 and
                    CountryCodes.InfoCode	 =	:d->INFOCODE
              for update;
    exec sql open CUpdate40;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate40" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate40;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate40" ) ) != IS_OK )
            break;
        exec sql update countrycodes set BranchNo = :d->BRANCHNO,
                     InfoCode = :d->INFOCODE,
                     ArticleActiv = :d->ARTICLEACTIV,
                     AuxDelivery = :d->AUXDELIVERY,
                     SeraCode = :d->SERACODE,
                     PrintCode = :d->PRINTCODE,
                     XMLCode = :d->XMLCODE,
                     XMLText = :d->XMLTEXT where current of CUpdate40;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate40" ) ) != IS_OK )
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



/* CCode: Select **************************************************************/

/* CCode::Delete **************************************************************/

retClient Ccode_Delete(ccodeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "Ccode_Delete";
    exec sql begin declare section;
    ccodeS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete41 cursor with hold for
              select BranchNo,
                     InfoCode,
                     ArticleActiv,
                     AuxDelivery,
                     SeraCode,
                     PrintCode,
                     XMLCode,
                     XMLText
               from COUNTRYCODES
              where CountryCodes.BranchNo	 =	:d->BRANCHNO	 and
                    CountryCodes.InfoCode	 =	:d->INFOCODE
              for update;
    exec sql open CDelete41;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete41" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete41;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete41" ) ) != IS_OK )
            break;
        exec sql delete from countrycodes where current of CDelete41;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete41" ) ) != IS_OK )
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



/* CCode: Other ***************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckImexblockExist.cxx                                          */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:48 2022                                         */
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
#include "artikel.h"

/* CheckImexblockExist: Select ************************************************/

/* CheckImexblockExist::SelExist **********************************************/

retClient Checkimexblockexist_SelExist(checkimexblockexistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkimexblockexist_SelExist";
    exec sql begin declare section;
    checkimexblockexistS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select imexblock.ArticleNo
                into :d->ARTICLENO
                from IMEXBLOCK
              where ImexBlock.ArticleNo	 =	:d->ARTICLENO	 and
                    ImexBlock.imex_mode	 =	0;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckImexblockExist: Insert ************************************************/



/* CheckImexblockExist: Update ************************************************/



/* CheckImexblockExist: Select ************************************************/



/* CheckImexblockExist: Other *************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckImportArticle.cxx                                           */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:50 2022                                         */
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
#include "artikel.h"

/* CheckImportArticle: Select *************************************************/

/* CheckImportArticle::SelImport **********************************************/

retClient Checkimportarticle_SelImport(checkimportarticleS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkimportarticle_SelImport";
    exec sql begin declare section;
    checkimportarticleS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelzentral.artikel_nr,
                     artikelzentral.ImportArticle
                into :d->ARTIKEL_NR,
                     :d->IMPORTARTICLE
                from artikelzentral
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    artikelzentral.ImportArticle	 =	1;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckImportArticle: Insert *************************************************/



/* CheckImportArticle: Update *************************************************/



/* CheckImportArticle: Select *************************************************/



/* CheckImportArticle: Other **************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CheckListe5Zentral.cxx                                           */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:51 2022                                         */
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
#include "artikel.h"

/* CheckListe5Zentral: Select *************************************************/

/* CheckListe5Zentral::IsListe5 ***********************************************/

retClient Checkliste5zentral_IsListe5(checkliste5zentralS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Checkliste5zentral_IsListe5";
    exec sql begin declare section;
    checkliste5zentralS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelzentral.artikel_nr
                into :d->ARTIKEL_NR
                from ARTIKELZENTRAL
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    artikelzentral.Liste_5	 =	1;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CheckListe5Zentral: Insert *************************************************/



/* CheckListe5Zentral: Update *************************************************/



/* CheckListe5Zentral: Select *************************************************/



/* CheckListe5Zentral: Other **************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : CodeblocageInfo.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:53 2022                                         */
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
#include "artikel.h"

/* CodeblocageInfo: Select ****************************************************/

/* CodeblocageInfo::SelText ***************************************************/

retClient Codeblocageinfo_SelText(codeblocageinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Codeblocageinfo_SelText";
    exec sql begin declare section;
    codeblocageinfoS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select countrycodes.PrintCode,
                     artikellokal.filialnr,
                     artikellokal.artikel_nr
                into :d->PRINTCODE,
                     :d->FILIALNR,
                     :d->ARTIKEL_NR
                from ARTIKELLOKAL, COUNTRYCODES
              where artikellokal.filialnr	 =	:d->FILIALNR	 and
                    artikellokal.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    CountryCodes.BranchNo	 =	artikellokal.filialnr and
                    CountryCodes.InfoCode	 =	artikellokal.codeblocage and
                    (artikellokal.artikelaktiv	!=	'1' or
                    artikellokal.bestand	 =	0);
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* CodeblocageInfo: Insert ****************************************************/



/* CodeblocageInfo: Update ****************************************************/



/* CodeblocageInfo: Select ****************************************************/



/* CodeblocageInfo: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : DispoInfo.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:55 2022                                         */
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
#include "artikel.h"

/* DispoInfo: Select **********************************************************/

/* DispoInfo::SelDispoInfo ****************************************************/

retClient Dispoinfo_SelDispoInfo(dispoinfoS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Dispoinfo_SelDispoInfo";
    exec sql begin declare section;
    dispoinfoS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        ppGMakeToLike( d->BEZEICHNUNG, L_DISPOINFO_BEZEICHNUNG );
        exec sql declare CSelDispoInfo46 cursor with hold for
                  select tellist.bezeichnung,
                     tellist.dispo_hinweis,
                     tellist.bemerkung,
                     tellist.pzn,
                     artikelzentral.artikel_nr,
                     artikelzentral.hersteller_nr
                from TELLIST, ARTIKELZENTRAL
                  where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR	 and
                        tellist.pzn	 =	artikelzentral.hersteller_nr and
                        tellist.bezeichnung	like	:d->BEZEICHNUNG;
        exec sql open CSelDispoInfo46;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelDispoInfo46" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelDispoInfo46;
        return CheckSql( fun, stError, "%s", "close CSelDispoInfo46" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelDispoInfo46 into :d->BEZEICHNUNG,
                     :d->DISPO_HINWEIS,
                     :d->BEMERKUNG,
                     :d->PZN,
                     :d->ARTIKEL_NR,
                     :d->HERSTELLER_NR;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelDispoInfo46" )) == IS_ERROR )
        return rc;
    return rc;
}



/* DispoInfo: Insert **********************************************************/



/* DispoInfo: Update **********************************************************/



/* DispoInfo: Select **********************************************************/



/* DispoInfo: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : Hersteller.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:56 2022                                         */
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
#include "artikel.h"

/* Hersteller: Select *********************************************************/

/* Hersteller::SelHersteller **************************************************/

retClient Hersteller_SelHersteller(herstellerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Hersteller_SelHersteller";
    exec sql begin declare section;
    herstellerS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select herstel.name,
                     artikelzentral.artikel_nr
                into :d->NAME,
                     :d->ARTIKEL_NR
                from artikelzentral, herstel
              where artikelzentral.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    artikelzentral.hersteller_nr	 =	herstel.hersteller_nr;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Hersteller: Insert *********************************************************/



/* Hersteller: Update *********************************************************/



/* Hersteller: Select *********************************************************/



/* Hersteller: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : LpprCode.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:58 2022                                         */
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
#include "artikel.h"

/* LpprCode: Select ***********************************************************/

/* LpprCode::Sel **************************************************************/

retClient Lpprcode_Sel(lpprcodeS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Lpprcode_Sel";
    exec sql begin declare section;
    lpprcodeS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select lpprcode.code_lppr,
                     lpprcode.reimbursement_val
                into :d->CODE_LPPR,
                     :d->REIMBURSEMENT_VAL
                from LPPRCODE
              where LPPRCode.code_lppr	 =	:d->CODE_LPPR;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* LpprCode: Insert ***********************************************************/



/* LpprCode: Update ***********************************************************/



/* LpprCode: Select ***********************************************************/



/* LpprCode: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : MaxArticleQuota.cxx                                              */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:45:59 2022                                         */
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
#include "artikel.h"

/* MaxArticleQuota: Select ****************************************************/

/* MaxArticleQuota::SelMax ****************************************************/

retClient Maxarticlequota_SelMax(maxarticlequotaS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Maxarticlequota_SelMax";
    exec sql begin declare section;
    maxarticlequotaS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select maxarticlequota.ArticleNo,
                     maxarticlequota.MaxQuota
                into :d->ARTICLENO,
                     :d->MAXQUOTA
                from MaxArticleQuota
              where MaxArticleQuota.ArticleNo	 =	:d->ARTICLENO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* MaxArticleQuota: Insert ****************************************************/



/* MaxArticleQuota: Update ****************************************************/



/* MaxArticleQuota: Select ****************************************************/



/* MaxArticleQuota: Other *****************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : Occasion.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:01 2022                                         */
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
#include "artikel.h"

/* Occasion: Select ***********************************************************/

/* Occasion::SelList **********************************************************/

retClient Occasion_SelList(occasionS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Occasion_SelList";
    exec sql begin declare section;
    occasionS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList50 cursor with hold for
                  select customerpharmacygr.CustomerNo,
                     discount.ArticleNo,
                     customerpharmacygr.BranchNo,
                     discount.DiscountValuePct
                from CUSTOMERPHARMACYGR, DISCOUNT
                  where customerpharmacygr.BranchNo	 =	:d->BRANCHNO	 and
                        customerpharmacygr.CustomerNo	 =	:d->CUSTOMERNO	 and
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        Discount.PharmacyGroupId	 =	customerpharmacygr.PharmacyGroupId and
                        Discount.DiscountSpec	 =	10;
        exec sql open CSelList50;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList50" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList50;
        return CheckSql( fun, stError, "%s", "close CSelList50" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList50 into :d->CUSTOMERNO,
                     :d->ARTICLENO,
                     :d->BRANCHNO,
                     :d->DISCOUNTVALUEPCT;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList50" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Occasion: Insert ***********************************************************/



/* Occasion: Update ***********************************************************/



/* Occasion: Select ***********************************************************/



/* Occasion: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PharmGrp.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:04 2022                                         */
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
#include "artikel.h"

/* PharmGrp: Select ***********************************************************/

/* PharmGrp::Sel **************************************************************/

retClient Pharmgrp_Sel(pharmgrpS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Pharmgrp_Sel";
    exec sql begin declare section;
    pharmgrpS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select first 1
pharmacygroups.PharmacyGroupId,
pharmacygroups.group_name,
pharmacygroups.group_type,
pharmacygroups.percent,
pharmacygroups.contribution,
pharmacygroups.CustomerNo,
pharmacygroups.omg_own_cont,
pharmacygroups.price_basis_purch,
pharmacygroups.reclaim_omg_disc,
pharmacygroups.specialgroup,
pharmacygroups.specialgrouprefno,
pharmacygroups.grouping_vis,
pharmacygroups.BranchNo
                into :d->PHARMACYGROUPID,
:d->GROUP_NAME,
:d->GROUP_TYPE,
:d->PERCENT,
:d->CONTRIBUTION,
:d->CUSTOMERNO,
:d->OMG_OWN_CONT,
:d->PRICE_BASIS_PURCH,
:d->RECLAIM_OMG_DISC,
:d->SPECIALGROUP,
:d->SPECIALGROUPREFNO,
:d->GROUPING_VIS,
:d->BRANCHNO
                from PHARMACYGROUPS
              where PharmacyGroups.PharmacyGroupId	 =	:d->PHARMACYGROUPID and
                    (PharmacyGroups.BranchNo	 =	:d->BRANCHNO
                    or 
                    PharmacyGroups.BranchNo	=	0)
                    order by PharmacyGroups.BranchNo desc;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PharmGrp: Insert ***********************************************************/



/* PharmGrp: Update ***********************************************************/



/* PharmGrp: Select ***********************************************************/



/* PharmGrp: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PreisAnzTyp.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:06 2022                                         */
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
#include "artikel.h"

/* PreisAnzTyp: Select ********************************************************/

/* PreisAnzTyp::SelPreis ******************************************************/

retClient Preisanztyp_SelPreis(preisanztypS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Preisanztyp_SelPreis";
    exec sql begin declare section;
    preisanztypS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select artikelpreis.artikel_nr,
                     artikelpreis.preisekapo,
                     artikelpreis.preisekgrosso,
                     artikelpreis.preisekgrossona,
                     artikelpreis.preis_typ
                into :d->ARTIKEL_NR,
                     :d->PREISEKAPO,
                     :d->PREISEKGROSSO,
                     :d->PREISEKGROSSONA,
                     :d->PREIS_TYP
                from ARTIKELPREIS
              where artikelpreis.artikel_nr	 =	:d->ARTIKEL_NR	 and
                    artikelpreis.preis_typ	 =	:d->PREIS_TYP;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PreisAnzTyp: Insert ********************************************************/



/* PreisAnzTyp: Update ********************************************************/



/* PreisAnzTyp: Select ********************************************************/



/* PreisAnzTyp: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PriceHist.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:08 2022                                         */
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
#include "artikel.h"

/* PriceHist: Select **********************************************************/

/* PriceHist::Sel *************************************************************/

retClient Pricehist_Sel(pricehistS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Pricehist_Sel";
    exec sql begin declare section;
    pricehistS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSel53 cursor with hold for
                  select pricehistory.artikel_nr,
                     pricehistory.datumgueltigab,
                     pricehistory.grosso,
                     pricehistory.Aep,
                     pricehistory.avp
                from PRICEHISTORY
                  where PriceHistory.artikel_nr	 =	:d->ARTIKEL_NR	
                        order by PriceHistory.datumgueltigab;
        exec sql open CSel53;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSel53" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSel53;
        return CheckSql( fun, stError, "%s", "close CSel53" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSel53 into :d->ARTIKEL_NR,
                     :d->DATUMGUELTIGAB,
                     :d->GROSSO,
                     :d->AEP,
                     :d->AVP;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSel53" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PriceHist: Insert **********************************************************/



/* PriceHist: Update **********************************************************/



/* PriceHist: Select **********************************************************/



/* PriceHist: Other ***********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : PromoAnz.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:10 2022                                         */
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
#include "artikel.h"

/* PromoAnz: Select ***********************************************************/

/* PromoAnz::SelPromo *********************************************************/

retClient Promoanz_SelPromo(promoanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Promoanz_SelPromo";
    exec sql begin declare section;
    promoanzS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select promotions.promotion_no,
                     promotions.name,
                     promotions.description,
                     promotions.promotion_type
                into :d->PROMOTION_NO,
                     :d->NAME,
                     :d->DESCRIPTION,
                     :d->PROMOTION_TYPE
                from PROMOTIONS
              where Promotions.promotion_no	 =	:d->PROMOTION_NO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* PromoAnz: Insert ***********************************************************/



/* PromoAnz: Update ***********************************************************/



/* PromoAnz: Select ***********************************************************/



/* PromoAnz: Other ************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : REIMPORT.cxx                                                     */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:12 2022                                         */
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
#include "artikel.h"

/* REIMPORT: Select ***********************************************************/



/* REIMPORT: Insert ***********************************************************/



/* REIMPORT: Update ***********************************************************/



/* REIMPORT: Select ***********************************************************/



/* REIMPORT: Other ************************************************************/

/* REIMPORT::SelAuswahl *******************************************************/

retClient Reimport_SelAuswahl(reimportS *a, tError *stError, bool bIsTrans)
{
 retClient rc = IS_OK;
 char *fun = "Reimport_SelAuswahl";
/*  GLOBALE C-VARIABLEN  */
extern char ARTIKELZENTRAL_SPRACHE[20];
extern int FREMDSPRACHE;
 exec sql begin declare section;
  reimportS *d;
  extern short FilialNr;
  long lDate;
  short iReihe;
  char szBuf[512];
 exec sql end declare section;

 d = a;

 if ( a->FETCH_REL == SET_OPEN )
 {
  lDate = ppGGetDate();
  exec sql drop table t_reimp_nr;
  exec sql select artikel_nr_altern,reihenfolge from artikelreimport
  where artikelreimport.artikel_nr = :d->PZN
  into temp t_reimp_nr;

  exec sql declare CSelReimp0 cursor with hold for
  select
   artikelzentral.artikel_nr,
   artikelzentral.darreichform,
   artikelzentral.einheit,
   artikelzentral.artikel_name,
   artikellokal.bestand,
   artikelpreis.preisekapo,
   t_reimp_nr.reihenfolge
  from
   artikelzentral,
   artikellokal,
   artikelpreis,
   t_reimp_nr
  where artikelzentral.artikel_nr = t_reimp_nr.artikel_nr_altern
  and artikellokal.artikel_nr = t_reimp_nr.artikel_nr_altern
  and artikelpreis.artikel_nr = t_reimp_nr.artikel_nr_altern
  and artikellokal.filialnr = :FilialNr
  and artikelpreis.datumgueltigab <= :lDate
  and artikelpreis.datumgueltigbis >= :lDate
  and artikellokal.bestand > 0
  and artikellokal.artikelaktiv = '1'
  order by t_reimp_nr.reihenfolge;

  if ( ( rc=CheckSql( fun, stError, "%s", "select artikelnr" ) ) != IS_OK )
    return rc;
  exec sql open CSelReimp0;
  if ( ( rc=CheckSql( fun, stError, "%s", "open CSelReimp0" ) ) != IS_OK )
    return rc;
  if (FREMDSPRACHE)
  {
   strcpy( szBuf, "select " ); 
   strcat( szBuf, "darreichform " );
   strcat( szBuf, ",einheit " );
   strcat( szBuf, ",artikel_name " );
   strcat( szBuf, "from " );
   strcat( szBuf, ARTIKELZENTRAL_SPRACHE );
   strcat( szBuf, " where artikel_nr = ?" );
   exec sql prepare SEL_SPRACHEREIMP from :szBuf;
  }
 }

 if ( a->FETCH_REL == SET_CLOSE )
 {
   if ( bIsTrans )
   {
    if ( ( rc = Commit( fun, stError ) ) != IS_OK )
     return rc;
   }
   exec sql drop table t_reimp_nr;
   exec sql close CSelReimp0;
   return CheckSql( fun, stError, "%s", "close CSelReimp0" );
 }

 if ( bIsTrans )
 {
  if ( ( rc = Begin( fun, stError ) ) != IS_OK )
   return rc;
 }
 exec sql fetch CSelReimp0
 into
  :d->PZN,
  :d->DARREICHFORM,
  :d->EINHEIT,
  :d->ARTIKEL_NAME,
  :d->BESTAND,
  :d->PREISEKAPO,
  :iReihe;
 if ((rc=CheckSql( fun, stError, "%s", "fetch CSelReimp0" )) == IS_ERROR )
  return rc;
 if (FREMDSPRACHE)
 {
  EXEC SQL execute SEL_SPRACHEREIMP into :d->DARREICHFORM,:d->EINHEIT,:d->ARTIKEL_NAME using :d->PZN;
 }
 return rc;
}



/******************************************************************************/
/*                                                                            */
/* header  : Steller.cxx                                                      */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:15 2022                                         */
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
#include "artikel.h"

/* Steller: Select ************************************************************/

/* Steller::SelList ***********************************************************/

retClient Steller_SelList(stellerS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Steller_SelList";
    exec sql begin declare section;
    stellerS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList55 cursor with hold for
                  select artcompack.article_no_pack,
                     artcompack.article_no_element,
                     artcompack.Quantity,
                     artikellokal.filialnr,
                     artikellokal.bestand,
                     artikelzentral.darreichform,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name,
                     artikelzentral.artikel_langname
                from ARTCOMPACK, ARTIKELZENTRAL, ARTIKELLOKAL
                  where ArtComPack.article_no_pack	 =	:d->ARTICLE_NO_PACK	 and
                        artikellokal.filialnr	 =	:d->FILIALNR	 and
                        artikelzentral.artikel_nr	 =	ArtComPack.article_no_element and
                        artikellokal.artikel_nr	 =	ArtComPack.article_no_element
                        order by artikelzentral.artikel_langname;
        exec sql open CSelList55;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList55" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList55;
        return CheckSql( fun, stError, "%s", "close CSelList55" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList55 into :d->ARTICLE_NO_PACK,
                     :d->ARTICLE_NO_ELEMENT,
                     :d->QUANTITY,
                     :d->FILIALNR,
                     :d->BESTAND,
                     :d->DARREICHFORM,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME,
                     :d->ARTIKEL_LANGNAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList55" )) == IS_ERROR )
        return rc;
    return rc;
}



/* Steller: Insert ************************************************************/



/* Steller: Update ************************************************************/



/* Steller: Select ************************************************************/



/* Steller: Other *************************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : StellerTyp.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:17 2022                                         */
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
#include "artikel.h"

/* StellerTyp: Select *********************************************************/

/* StellerTyp::SelTyp *********************************************************/

retClient Stellertyp_SelTyp(stellertypS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Stellertyp_SelTyp";
    exec sql begin declare section;
    stellertypS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select cpvalidityperiod.article_no_pack,
                     cpvalidityperiod.DateFrom,
                     cpvalidityperiod.DateTo,
                     cpvalidityperiod.compack_type
                into :d->ARTICLE_NO_PACK,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->COMPACK_TYPE
                from CPVALIDITYPERIOD
              where CPValidityPeriod.article_no_pack	 =	:d->ARTICLE_NO_PACK;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* StellerTyp: Insert *********************************************************/



/* StellerTyp: Update *********************************************************/



/* StellerTyp: Select *********************************************************/



/* StellerTyp: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : StockReservation.cxx                                             */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:20 2022                                         */
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
#include "artikel.h"

/* StockReservation: Select ***************************************************/

/* StockReservation::SelList **************************************************/

retClient Stockreservation_SelList(stockreservationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Stockreservation_SelList";
    exec sql begin declare section;
    stockreservationS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList57 cursor with hold for
                  select cststockreserved.BranchNo,
                     cststockreserved.CustomerNo,
                     cststockreserved.ArticleNo,
                     cststockreserved.ReservedQty,
                     cststockreserved.DateFrom,
                     cststockreserved.TimeFrom,
                     cststockreserved.DateTo,
                     cststockreserved.TimeTo,
                     cststockreserved.kdauftragnr,
                     cststockreserved.ReservType
                from CSTSTOCKRESERVED
                  where CstStockReserved.BranchNo	 =	:d->BRANCHNO	 and
                        CstStockReserved.ArticleNo	 =	:d->ARTICLENO	 and
                        CstStockReserved.ReservType	in	(7,8,9,10,11,12)
                        order by CstStockReserved.DateFrom, CstStockReserved.kdauftragnr;
        exec sql open CSelList57;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList57" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList57;
        return CheckSql( fun, stError, "%s", "close CSelList57" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList57 into :d->BRANCHNO,
                     :d->CUSTOMERNO,
                     :d->ARTICLENO,
                     :d->RESERVEDQTY,
                     :d->DATEFROM,
                     :d->TIMEFROM,
                     :d->DATETO,
                     :d->TIMETO,
                     :d->KDAUFTRAGNR,
                     :d->RESERVTYPE;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList57" )) == IS_ERROR )
        return rc;
    return rc;
}

retClient Stockreservation_SelListAll(stockreservationS* a, tError* stError, bool bIsTrans)
{

    retClient rc = IS_OK;
    char* fun = "Stockreservation_SelList";
    exec sql begin declare section;
    stockreservationS* d;
    long articleno = 0;
    exec sql end declare section;

    d = a;
    
    
    if (a->FETCH_REL == SET_OPEN)
    {
        exec sql select articleno into : articleno from articlecodes where article_code = : d->ARTICLE_CODE and preferred_flag = 1;

        exec sql declare CSelList59 cursor with hold for
            select cststockreserved.BranchNo,
            cststockreserved.CustomerNo,
            (select article_code from articlecodes where articleno = cststockreserved.ArticleNo and preferred_flag = 1) article_code,
            cststockreserved.ArticleNo,
            cststockreserved.ReservedQty,
            cststockreserved.DateFrom,
            cststockreserved.TimeFrom,
            cststockreserved.DateTo,
            cststockreserved.TimeTo,
            cststockreserved.kdauftragnr,
            cststockreserved.ReservType
            from CSTSTOCKRESERVED
        where 1=1
            and ((cststockreserved.BranchNo = :d->BRANCHNO) or (:d->BRANCHNO = 0))
            and ((cststockreserved.CustomerNo = :d->CUSTOMERNO) or (:d->CUSTOMERNO = 0))
            and ((cststockreserved.ArticleNo = :articleno) or (:articleno = 0))
            and ((cststockreserved.ReservType = :d->RESERVTYPE) or ((:d->RESERVTYPE = 0) and (cststockreserved.ReservType in (7, 8, 9, 10, 11, 12))))
            and ((cststockreserved.kdauftragnr = :d->KDAUFTRAGNR) or (:d->KDAUFTRAGNR = 0))
            and ((cststockreserved.DateFrom >= :d->DATEFROM) or (:d->DATEFROM = 0))
            and ((cststockreserved.DateFrom <= :d->DATETO) or (:d->DATETO = 0))
            order by cststockreserved.DateFrom, cststockreserved.kdauftragnr;

        exec sql open CSelList59;
        if ((rc = CheckSql(fun, stError, "%s", "open CSelList59")) != IS_OK)
            return rc;
    }
    if (a->FETCH_REL == SET_CLOSE)
    {
        if (bIsTrans)
        {
            if ((rc = Commit(fun, stError)) != IS_OK)
                return rc;
        }
        exec sql close CSelList59;
        exec sql free  CSelList59;
        return CheckSql(fun, stError, "%s", "close CSelList59");
    }
    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }
    exec sql fetch CSelList59 into :d->BRANCHNO,
        :d->CUSTOMERNO,
        :d->ARTICLE_CODE,
        :d->ARTICLENO,
        :d->RESERVEDQTY,
        :d->DATEFROM,
        :d->TIMEFROM,
        :d->DATETO,
        :d->TIMETO,
        :d->KDAUFTRAGNR,
        :d->RESERVTYPE;
    if ((rc = CheckSql(fun, stError, "%s", "fetch CSelList59")) == IS_ERROR)
        return rc;
    return rc;
}
/* StockReservation::SelSum ***************************************************/

retClient Stockreservation_SelSum(stockreservationS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "Stockreservation_SelSum";
    exec sql begin declare section;
    stockreservationS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select nvl (sum( CstStockReserved.ReservedQty) , 0 )
                into :d->RESERVEDQTY
                from CSTSTOCKRESERVED
              where CstStockReserved.BranchNo	 =	:d->BRANCHNO	 and
                    CstStockReserved.ArticleNo	 =	:d->ARTICLENO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}

retClient Stockreservation_DeleteEntry(stockreservationS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char* fun = "Stockreservation_DeleteEntry";
    int kzupd = 0;
    
    exec sql begin declare section;
        stockreservationS* d;
        long lBestand;
        long lreservedqty;
        long lreservetype;
        long llreservedqty;
        bool kdAuftragExists = false;
        bool lisStorno = false;
        char* lkdAuftragstate = "";
    exec sql end declare section;
    
    d = a;
    lreservetype = d->RESERVTYPE;
    lreservedqty = d->RESERVEDQTY;
    if (d->KDAUFTRAGNR == 0) 
    {
        kdAuftragExists = false;
    }
    else 
    {
        exec sql select kdauftragstat into : lkdAuftragstate from kdAuftrag
        where kdauftragnr = : d->KDAUFTRAGNR;
        if (SQLCODE != SQLNOTFOUND)
        {
            kdAuftragExists = true;
            if (lkdAuftragstate[9] == '1') 
            {
                lisStorno = true;
            }
        }
    }
    // start transaction here, since we start blocking tables. Blocks not needed for selecting the data
    if ((rc = Begin(fun, stError)) != IS_OK) 
    {
        return rc;
    }
    else 
    {
        bInTrans = true;
    }
    if (lreservetype == 7 || lreservetype == 8)
    {
        if ((!kdAuftragExists && d->KDAUFTRAGNR != 0) || (kdAuftragExists && lkdAuftragstate[7] == '1')) //state == AEORD_POS_BEREIT_ZUR_FAKTUR
        {
            
           exec sql declare CDeleteNaliepos cursor with hold for
                select nachlieferpos.KDAUFTRAGNR,
                nachlieferpos.POSNR,
                nachlieferpos.DATUM,
                nachlieferpos.POSTYP
                from nachlieferpos
            where nachlieferpos.kdauftragnr = :d->KDAUFTRAGNR;
            
            exec sql open CDeleteNaliepos;
            
            
            if ((rc = CheckSql(fun, stError, "%s", "open CDeleteNaliepos")) != IS_OK)
            {
                Rollback(fun, stError);
                return rc;
            }
            exec sql fetch CDeleteNaliepos;
            if ((rc = CheckSql(fun, stError, "%s", "fetch CDeleteNaliepos")) != IS_OK)
            {
                Rollback(fun, stError);
                return rc;
            }
            //exec sql delete from nachlieferpos where current of CDeleteNaliepos;
            if ((rc = CheckSql(fun, stError, "%s", "delete CDeleteNaliepos")) != IS_OK)
            {
                Rollback(fun, stError);
                return rc;
            }
            exec sql close CDeleteNaliepos;
        }
    }

    //update artikellokal menge
    if (lisStorno && (lreservetype == 7 || lreservetype == 9 || lreservetype == 11))
    { //update artikellokal.menge
        exec sql select bestand into : lBestand from artikellokal
        where artikel_nr = : d->ARTICLENO
        and filialnr = : d->BRANCHNO;
        if (SQLCODE == SQLNOTFOUND)
        {
            return IS_NOTFOUND;
        }
        else
        {
            kzupd = 1;
        }
        lBestand = lreservedqty + lBestand;
        if (kzupd == 1)
        {
            exec sql update artikellokal
                set bestand = :lBestand
            where artikel_nr = : d->ARTICLENO
            and filialnr = : d->BRANCHNO;
            if ((rc = CheckSql(fun, stError, "%s", "update artikellokal")) != IS_OK)
            {
                if (bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND))
                {
                    Rollback(fun, stError);
                    return rc;
                }
            }
        }
    }
    //update articlereservation reservedqty
    else if (lisStorno && (lreservetype == 8 || lreservetype == 10 || lreservetype == 12))
    {
        exec sql select reservedqty  into : llreservedqty from articlereservation
        where articleno = : d->ARTICLENO
        and branchno = : d->BRANCHNO;
        if (SQLCODE == SQLNOTFOUND)
        {
            return IS_NOTFOUND;
        }
        else
        {
            kzupd = 1;
        }
        llreservedqty = llreservedqty + lreservedqty;
        if (kzupd == 1)
        {
            exec sql update articlereservation
                set reservedqty = :llreservedqty
            where articleno = : d->ARTICLENO
            and branchno = : d->BRANCHNO;
            if ((rc = CheckSql(fun, stError, "%s", "update articlereservation")) != IS_OK)
            {
                if (bIsTrans && (rc < IS_OK || rc > IS_NOTFOUND))
                {
                    Rollback(fun, stError);
                    return rc;
                }
            }
        }
    }

        exec sql declare CDelete35 cursor with hold for
            select  BranchNo,
            CustomerNo,
            ArticleNo,
            ReservedQty,
            DateFrom,
            TimeFrom,
            DateTo,
            TimeTo,
            kdauftragnr,
            ReservType
            from CstStockReserved
        where CstStockReserved.BranchNo = :d->BRANCHNO 
          and CstStockReserved.ArticleNo = :d->ARTICLENO 
          and CstStockReserved.CustomerNo = :d->CUSTOMERNO
            for update;

        exec sql open CDelete35;

    if ((rc = CheckSql(fun, stError, "%s", "open CDelete35")) != IS_OK)
    {
        Rollback(fun, stError);
        return rc;
    }
    
    
    exec sql fetch CDelete35;
    if ((rc = CheckSql(fun, stError, "%s", "fetch CDelete35")) != IS_OK)
    {
        Rollback(fun, stError);
        return rc;
    }
    exec sql delete from cststockreserved where current of CDelete35;
    if ((rc = CheckSql(fun, stError, "%s", "delete CDelete35")) != IS_OK)                
    {
        Rollback(fun, stError);
        return rc;
    }
    
    if (rc == IS_OK) {
        Commit(fun, stError);
    }
    exec sql close CDelete35;
    return rc;

}

/* StockReservation: Insert ***************************************************/



/* StockReservation: Update ***************************************************/



/* StockReservation: Select ***************************************************/



/* StockReservation: Other ****************************************************/

/* Stockreservation SelCstStockReservation */
retClient Stockreservation_SelCstStockReservation(stockreservationS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_SelCstStockReservation";

    exec sql begin declare section;
    stockreservationS* d;
    exec sql end declare section;

    d = a;

    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    exec sql
        select cststockreserved.branchno,
               cststockreserved.customerno,
               cststockreserved.articleno,
               articlecodes.article_code,
               cststockreserved.reservedqty,
               cststockreserved.datefrom,
               cststockreserved.timefrom,
               cststockreserved.kdauftragnr,
               cststockreserved.reservtype
          into :d->BRANCHNO,
               :d->CUSTOMERNO,
               :d->ARTICLENO,
               :d->ARTICLE_CODE,
               :d->RESERVEDQTY,
               :d->DATEFROM,
               :d->TIMEFROM,
               :d->KDAUFTRAGNR,
               :d->RESERVTYPE
          from cststockreserved
		left join articlecodes on articlecodes.articleno = cststockreserved.articleno and articlecodes.preferred_flag = 1
         where cststockreserved.branchno = :d->BRANCHNO
         and cststockreserved.customerno = : d->CUSTOMERNO
             and cststockreserved.ARTICLENO = : d->ARTICLENO
             --and articlecodes.code_type = 16
             --and articlecodes.articleno = cststockreserved.articleno
             and cststockreserved.reservtype = : d->RESERVTYPE
             and cststockreserved.kdauftragnr = : d->KDAUFTRAGNR
             and cststockreserved.datefrom = : d->DATEFROM;

    rc = CheckSql(fun, stError, "select %s", fun);

    return rc;
}

/* Stockreservation SelNachlieferpos */

retClient Stockreservation_SelNachlieferPos(stockreservationnachlieferposS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_SelNachlieferPos";
    exec sql begin declare section;
    stockreservationnachlieferposS* d;
    exec sql end declare section;
    
    d = a;
    if (a->FETCH_REL == SET_OPEN)
    {
        exec sql declare CSelNachlieferPos cursor with hold for
            select nachlieferpos.KDAUFTRAGNR,
            nachlieferpos.POSNR,
            nachlieferpos.DATUM,
            nachlieferpos.POSTYP,
            nachlieferpos.IDFNR,
            nachlieferpos.ARTIKEL_NR,
            nachlieferpos.MENGE,
            nachlieferpos.STATUS
            from NACHLIEFERPOS
             where ((nachlieferpos.KDAUFTRAGNR = :d->KDAUFTRAGNR) or (:d->KDAUFTRAGNR = 0))
               and nachlieferpos.IDFNR = :d->IDFNR
               and nachlieferpos.ARTIKEL_NR = :d->ARTIKEL_NR
               and nachlieferpos.POSTYP = 5;

        exec sql open CSelNachlieferPos;
        if ((rc = CheckSql(fun, stError, "open %s", fun)) != IS_OK)
            return rc;
    }
    
    if (a->FETCH_REL == SET_CLOSE)
    {
        if (bIsTrans)
        {
            if ((rc = Commit(fun, stError)) != IS_OK)
                return rc;
        }
        exec sql close CSelNachlieferPos;
        rc = CheckSql(fun, stError, "close %s", fun);
        exec sql free CSelNachlieferPos;
        return rc;
    }

    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }
    exec sql fetch CSelNachlieferPos into : d->KDAUFTRAGNR,
        : d->POSNR,
        : d->DATUM,
        : d->POSTYP,
        : d->IDFNR,
        : d->ARTIKEL_NR,
        : d->MENGE,
        : d->STATUS;
    
    rc = CheckSql(fun, stError, "fetch %s", fun); 
    return rc;
}

retClient Stockreservation_SelArtikelLokal(stockreservationartikellokalS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_SelArtikelLokal";

    exec sql begin declare section;
      stockreservationartikellokalS* d;
    exec sql end declare section;

    d = a;

    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    exec sql 
     select artikellokal.FILIALNR,
            artikellokal.ARTIKEL_NR,
            artikellokal.BESTAND,
            artikellokal.LAGERBEREICHNR,
            artikellokal.STATIONNR,
            artikellokal.LAGERFACHNR
       into :d->FILIALNR,
            :d->ARTIKEL_NR,
            :d->BESTAND,
            :d->LAGERBEREICHNR,
            :d->STATIONNR,
            :d->LAGERFACHNR
       from ARTIKELLOKAL
      where artikellokal.FILIALNR = :d->FILIALNR
          and artikellokal.ARTIKEL_NR = : d->ARTIKEL_NR;
        
    rc = CheckSql(fun, stError, "select %s", fun);
    return rc;
}

retClient Stockreservation_SelArticleReserv(stockreservationarticlereservS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_SelArticleReserv";

    exec sql begin declare section;
      stockreservationarticlereservS* d;
    exec sql end declare section;
    
    d = a;

    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    exec sql 
     select articlereservation.BRANCHNO,
            articlereservation.PHARMACYGROUPID,
            articlereservation.ARTICLENO,
            articlereservation.RESERVTYPE,
            articlereservation.MAXQTY,
            articlereservation.RESERVEDQTY
       into :d->BRANCHNO,
            :d->PHARMACYGROUPID,
            :d->ARTICLENO,
            :d->RESERVTYPE,
            :d->MAXQTY,
            :d->RESERVEDQTY
       from articlereservation
      where articlereservation.BRANCHNO = :d->BRANCHNO
        and articlereservation.ARTICLENO = :d->ARTICLENO
        and articlereservation.RESERVTYPE = :d->RESERVTYPE;

    rc = CheckSql(fun, stError, "select %s", fun);
    return rc;
}

retClient Stockreservation_SelIBTRequet(stockreservationibtrequestS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_SelIBTRequet";

    exec sql begin declare section;
    stockreservationibtrequestS* d;
    exec sql end declare section;

    d = a;

    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    exec sql
        select ibtrequest.IBTREQUESTID,
               ibtrequest.BRANCHNO,
               ibtrequest.IBTBRANCHNO,
               ibtrequest.CSCORDERNO,
               ibtrequest.CUSTOMERNO,
               ibtrequest.IBTCUSTOMERNO,
               ibtrequest.PROCESSINGSTATE,
               ibtrequest.ARTICLENO,
               ibtrequest.QUANTITY
          into :d->IBTREQUESTID,
               :d->BRANCHNO,
               :d->IBTBRANCHNO,
               :d->CSCORDERNO,
               :d->CUSTOMERNO,
               :d->IBTCUSTOMERNO,
               :d->PROCESSINGSTATE,
               :d->ARTICLENO,
               :d->QUANTITY
          from ibtrequest
         where ibtrequest.IBTBRANCHNO = :d->IBTBRANCHNO
           and ibtrequest.IBTCUSTOMERNO = :d->IBTCUSTOMERNO
           and ibtrequest.ARTICLENO = :d->ARTICLENO
           and cast(to_char(ibtrequest.CREATIONDATETIME, '%Y%m%d') as int) = :d->DATEFROM
           and cast(to_char(ibtrequest.CREATIONDATETIME, '%H%M%S') as int) = :d->TIMEFROM;

    rc = CheckSql(fun, stError, "select %s", fun);
    return rc;
}

retClient Stockreservation_UpdateArtikelLokal(stockreservationartikellokalS* a, tError* stError, bool bIsTrans)
{
    // we are only updating the "BESTAND" here. no other fields affacted
    //PK = artikelnr + filialnr

    retClient rc = IS_OK;
    char* fun = "Stockreservation_UpdateArtikelLokal";

    exec sql begin declare section;
      stockreservationartikellokalS* d;
    exec sql end declare section;

    d = a;

    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    exec sql 
        update artikellokal 
           set artikellokal.bestand = :d->BESTAND
         where artikellokal.ARTIKEL_NR = :d->ARTIKEL_NR
           and artikellokal.FILIALNR = :d->FILIALNR;
    
    if (bIsTrans && rc < 0)
    {
        rc = Rollback(fun, stError);
    }
    if (bIsTrans && rc == IS_OK) {
        rc = Commit(fun, stError);
    }
    
    return rc;
}
retClient Stockreservation_UpdateArticleReservation(stockreservationarticlereservS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char* fun = "Stockreservation_UpdateArticleReservation";

    exec sql begin declare section;
       stockreservationarticlereservS* d;
    exec sql end declare section;

    d = a;


    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }
    exec sql 
        update articlereservation 
           set reservedqty = :d->RESERVEDQTY
         where articlereservation.ARTICLENO = :d->ARTICLENO
           and articlereservation.branchno = :d->BRANCHNO
           and articlereservation.reservtype = :d->RESERVTYPE;

    if (bIsTrans && rc < 0)
    {
        rc = Rollback(fun, stError);
    }
    if (bIsTrans && rc == IS_OK) {
        rc = Commit(fun, stError);
    }

    return rc;
}

retClient Stockreservation_DeleteNachlieferPos(stockreservationnachlieferposS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_DeleteNachlieferPos";

    exec sql begin declare section;
        stockreservationnachlieferposS* d;
    exec sql end declare section;

    d = a;
    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    exec sql 
        delete from NACHLIEFERPOS
        where((nachlieferpos.KDAUFTRAGNR = :d->KDAUFTRAGNR) or (:d->KDAUFTRAGNR = 0))
          and nachlieferpos.IDFNR = :d->IDFNR
          and nachlieferpos.ARTIKEL_NR = :d->ARTIKEL_NR
          and nachlieferpos.POSTYP = 5;

    rc = CheckSql(fun, stError, "delete %s", fun);
    return rc;
}

retClient Stockreservation_DeleteIbtRequest(stockreservationibtrequestS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_DeleteIbtRequest";

    exec sql begin declare section;
    stockreservationibtrequestS* d;
    exec sql end declare section;

    d = a;
    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    exec sql
        delete from IBTREQUEST
         where ibtrequest.ibtrequestid = :d->IBTREQUESTID;

    rc = CheckSql(fun, stError, "delete %s", fun);
    return rc;
}

retClient Stockreservation_DeleteCstStockReservedEntry(stockreservationS* a, tError* stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_DeleteCstStockReservedEntry";

    exec sql begin declare section;
        stockreservationS* d;
    exec sql end declare section;

    d = a;
    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    exec sql
        delete from CSTSTOCKRESERVED
         where cststockreserved.branchno = :d->BRANCHNO
           and cststockreserved.customerno = :d->CUSTOMERNO
           and cststockreserved.ARTICLENO = :d->ARTICLENO
           and cststockreserved.reservtype = :d->RESERVTYPE
           and cststockreserved.kdauftragnr = :d->KDAUFTRAGNR
           and cststockreserved.datefrom = :d->DATEFROM;

    rc = CheckSql(fun, stError, "delete %s", fun);
    return rc;
}

retClient Stockreservation_SelOrder(stockreservationorderS* a, tError* stError, bool bIsTrans) 
{
    retClient rc = IS_OK;
    char* fun = "Stockreservation_SelOrder";
    
    exec sql begin declare section;
        stockreservationorderS* d;
        long lCountKdauftrag = 0; // needed to decide wether we have an active entry or one from archive
    exec sql end declare section;


    d = a;
    d->DATUM = 0; // inialize for select from kdauftrag

    if (bIsTrans)
    {
        if ((rc = Begin(fun, stError)) != IS_OK)
            return rc;
    }

    // determine if order is archived or not
    exec sql select count(*)
               into :lCountKdauftrag
               from kdauftrag
              where KDAUFTRAGNR = :d->KDAUFTRAGNR;
                

    if (lCountKdauftrag > 0) 
    {
       exec sql 
         select kdauftrag.KDAUFTRAGNR,
                kdauftrag.KDAUFTRAGSTAT,
                kdauftrag.IDFNR,
                kdauftrag.FILIALNR,
                kdauftrag.KDAUFTRAGART,
                kdauftrag.KUNDENNR,
                kdauftrag.ZUGRUND
           into :d->KDAUFTRAGNR,
                :d->KDAUFTRAGSTAT,
                :d->IDFNR,
                :d->FILIALNR,
                :d->KDAUFTRAGART
                :d->KUNDENNR,
                :d->ZUGRUND
           from kdauftrag
       where kdauftrag.KDAUFTRAGNR = :d->KDAUFTRAGNR;

       rc = CheckSql(fun, stError, "select %s", fun);
    }
    else
    {
        exec sql
            select first 1 
                   akdauftrag.DATUM,
                   akdauftrag.KDAUFTRAGNR,
                   akdauftrag.KDAUFTRAGSTAT,
                   akdauftrag.IDFNR,
                   akdauftrag.FILIALNR,
                   akdauftrag.KDAUFTRAGART,
                   akdauftrag.KUNDENNR,
                   akdauftrag.ZUGRUND
              into :d->DATUM,
                   :d->KDAUFTRAGNR,
                   :d->KDAUFTRAGSTAT,
                   :d->IDFNR,
                   :d->FILIALNR,
                   :d->KDAUFTRAGART
                   :d->KUNDENNR,
                   :d->ZUGRUND
              from akdauftrag
             where akdauftrag.KDAUFTRAGNR = : d->KDAUFTRAGNR
               and akdauftrag.FILIALNR = : d->FILIALNR
               and akdauftrag.KUNDENNR = : d->KUNDENNR
             order by akdauftrag.DATUM desc;

        rc = CheckSql(fun, stError, "select archive %s", fun);
    }
    return rc;
}

/******************************************************************************/
/*                                                                            */
/* header  : SupplInfo.cxx                                                    */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:22 2022                                         */
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
#include "artikel.h"

/* SupplInfo: Select **********************************************************/



/* SupplInfo: Insert **********************************************************/



/* SupplInfo: Update **********************************************************/



/* SupplInfo: Select **********************************************************/



/* SupplInfo: Other ***********************************************************/

/* SupplInfo::SelSuppInfo *****************************************************/

retClient Supplinfo_SelSuppInfo(supplinfoS *a, tError *stError, bool bIsTrans)
{
retClient rc = IS_OK;
char *fun = "SupplInfo_SelSuppInfo";
static int iOpen = 1;
exec sql begin declare section;
supplinfoS *d;
exec sql end declare section;

d = a;
if (iOpen) /* beim ersten mal oder bei neu deklarieren */
{
	iOpen = 0;
	EXEC SQL declare CFetch_suppinfo cursor with hold for
	select
	SupplDeliveryInfo.AvailabilityInfo,
	CAST(TO_CHAR(SupplDeliveryInfo.predictedavaildate, '%Y%m%d') AS INT) ,
	CAST(TO_CHAR(SupplDeliveryInfo.availabledate, '%Y%m%d') AS INT)
	from SUPPLDELIVERYINFO
	where SUPPLDELIVERYINFO.ARTICLENO = :d->ARTICLENO;

	if (sqlca.sqlcode < 0 )
	{
		iOpen = 1;
		sprintf(stError->spError, " AatartSel_suppinfo declare Cursor %ld/%ld",
		sqlca.sqlcode,sqlca.sqlerrd[1]);
		return 1;
	}
	EXEC SQL open CFetch_suppinfo;
	if (sqlca.sqlcode < 0 )
	{
		iOpen = 1;
		sprintf(stError->spError, " AatartSel_suppinfo: open CFetch_suppinfo %ld/%ld", sqlca.sqlcode,sqlca.sqlerrd[1]);
		return 1;
	}
}

for(;;)
{
	EXEC SQL fetch CFetch_suppinfo
	into
	:d->AVAILABILITYINFO,
	:d->PROGLIEFERDATUM,
	:d->LIEFERDATUM;
	if (sqlca.sqlcode == SQLNOTFOUND)
	{
		iOpen = 1;
		return 1;
	}
	if (sqlca.sqlcode < 0 )
	{
		iOpen = 1;
		sprintf(stError->spError, " AatartSel_suppinfo: fetch CFetch_suppinfo %ld/%ld",
		sqlca.sqlcode, sqlca.sqlerrd[1]);
		return 1;
	}
	if(a->PROGLIEFERDATUM > 30001231 && a->LIEFERDATUM > 30001231) continue;
	else break;
}
return 0;
}



/******************************************************************************/
/*                                                                            */
/* header  : delayedart.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:25 2022                                         */
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
#include "artikel.h"

/* delayedart: Select *********************************************************/

/* delayedart::Sel ************************************************************/

retClient delayedart_Sel(delayedartS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "delayedart_Sel";
    exec sql begin declare section;
    delayedartS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql select delayeddeliveryart.BranchNo,
                     delayeddeliveryart.narcotic,
                     delayeddeliveryart.coldchain,
                     delayeddeliveryart.cool08,
                     delayeddeliveryart.cool20
                into :d->BRANCHNO,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20
                from delayeddeliveryart
              where delayeddeliveryart.BranchNo	 =	:d->BRANCHNO;
    if ((rc = CheckSql( fun, stError, "%s", "unique select" )) == IS_ERROR )
        return rc;
    return rc;
}



/* delayedart: Insert *********************************************************/

/* delayedart::Insert *********************************************************/

retClient delayedart_Insert(delayedartS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "delayedart_Insert";
    exec sql begin declare section;
    delayedartS *d;
    exec sql end declare section;

    d = a;

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql insert into delayeddeliveryart (BranchNo,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20)
        values (:d->BRANCHNO,
                     :d->NARCOTIC,
                     :d->COLDCHAIN,
                     :d->COOL08,
                     :d->COOL20);
    if ( ( rc = CheckSql( fun, stError,  "%s", "insert delayeddeliveryart" ) ) != IS_OK )
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



/* delayedart: Update *********************************************************/

/* delayedart::Update *********************************************************/

retClient delayedart_Update(delayedartS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "delayedart_Update";
    exec sql begin declare section;
    delayedartS *d;
    exec sql end declare section;

    d = a;



    exec sql declare CUpdate60 cursor with hold for
              select BranchNo,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20
               from delayeddeliveryart
              where delayeddeliveryart.BranchNo	 =	:d->BRANCHNO
              for update;
    exec sql open CUpdate60;
    if ( ( rc=CheckSql( fun, stError, "%s", "open CUpdate60" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CUpdate60;
        if ( ( rc=CheckSql( fun, stError, "%s", "fetch CUpdate60" ) ) != IS_OK )
            break;
        exec sql update delayeddeliveryart set BranchNo = :d->BRANCHNO,
                     narcotic = :d->NARCOTIC,
                     coldchain = :d->COLDCHAIN,
                     cool08 = :d->COOL08,
                     cool20 = :d->COOL20 where current of CUpdate60;
        if ( ( rc=CheckSql( fun, stError, "%s", "update CUpdate60" ) ) != IS_OK )
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



/* delayedart: Select *********************************************************/

/* delayedart::Delete *********************************************************/

retClient delayedart_Delete(delayedartS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    bool bInTrans = false;
    char *fun = "delayedart_Delete";
    exec sql begin declare section;
    delayedartS *d;
    exec sql end declare section;

    d = a;

    exec sql declare CDelete61 cursor with hold for
              select BranchNo,
                     narcotic,
                     coldchain,
                     cool08,
                     cool20
               from delayeddeliveryart
              where delayeddeliveryart.BranchNo	 =	:d->BRANCHNO
              for update;
    exec sql open CDelete61;
    if ( ( rc=CheckSql( fun, stError,  "%s", "open CDelete61" ) ) != IS_OK )
        return rc;
    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
        bInTrans = true;
    }
    for(;;)
    {
        exec sql fetch CDelete61;
        if ( ( rc=CheckSql( fun, stError,  "%s", "fetch CDelete61" ) ) != IS_OK )
            break;
        exec sql delete from delayeddeliveryart where current of CDelete61;
        if ( ( rc=CheckSql( fun, stError,  "%s", "delete CDelete61" ) ) != IS_OK )
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



/* delayedart: Other **********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : discountanz.cxx                                                  */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:37 2022                                         */
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
#include "artikel.h"

/* discountanz: Select ********************************************************/

/* discountanz::SelList *******************************************************/

retClient discountanz_SelList(discountanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "discountanz_SelList";
    exec sql begin declare section;
    discountanzS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList62 cursor with hold for
                  select discount.BranchNo,
                     discount.ArticleNo,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     discount.GrpDiscountTyp,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountType,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountQtyPct,
                     discount.SurchargePct,
                     discount.PharmGrpExcluded,
                     discount.FixedPrice,
                     discount.RefundPct,
                     discount.InternalDiscount,
                     discount.DiscountArticle,
                     discount.UpdateSign,
                     discount.base_value,
                     discount.base_mult_std_qty,
                     discount.no_multiple_qty,
                     discount.FixedDiscountValue,
                     discount.manufacturerno,
                     discount.artcategoryno,
                     discount.paymenttargetno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.paymenttermtype,
                     discount.targetqty,
                     discount.exceedancepct,
                     discount.article_no_pack,
                     discount.refundvalue,
                     discount.promotion_no,
                     discount.DiscountApplyTo,
                     discount.DiscountCalcFrom
                from DISCOUNT
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.ArticleNo	 =	:d->ARTICLENO and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate
                        order by Discount.BaseQty,Discount.paymenttargetno;
        exec sql open CSelList62;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList62" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList62;
        return CheckSql( fun, stError, "%s", "close CSelList62" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList62 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->GRPDISCOUNTTYP,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTQTYPCT,
                     :d->SURCHARGEPCT,
                     :d->PHARMGRPEXCLUDED,
                     :d->FIXEDPRICE,
                     :d->REFUNDPCT,
                     :d->INTERNALDISCOUNT,
                     :d->DISCOUNTARTICLE,
                     :d->UPDATESIGN,
                     :d->BASE_VALUE,
                     :d->BASE_MULT_STD_QTY,
                     :d->NO_MULTIPLE_QTY,
                     :d->FIXEDDISCOUNTVALUE,
                     :d->MANUFACTURERNO,
                     :d->ARTCATEGORYNO,
                     :d->PAYMENTTARGETNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PAYMENTTERMTYPE,
                     :d->TARGETQTY,
                     :d->EXCEEDANCEPCT,
                     :d->ARTICLE_NO_PACK,
                     :d->REFUNDVALUE,
                     :d->PROMOTION_NO,
                     :d->DISCOUNTAPPLYTO,
                     :d->DISCOUNTCALCFROM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList62" )) == IS_ERROR )
        return rc;
    return rc;
}

/* discountanz::SelListCst ****************************************************/

retClient discountanz_SelListCst(discountanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "discountanz_SelListCst";
    exec sql begin declare section;
    discountanzS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListCst63 cursor with hold for
                  select discount.BranchNo,
                     discount.ArticleNo,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     discount.GrpDiscountTyp,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountType,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountQtyPct,
                     discount.SurchargePct,
                     discount.PharmGrpExcluded,
                     discount.FixedPrice,
                     discount.RefundPct,
                     discount.InternalDiscount,
                     discount.DiscountArticle,
                     discount.UpdateSign,
                     discount.base_value,
                     discount.base_mult_std_qty,
                     discount.no_multiple_qty,
                     discount.FixedDiscountValue,
                     discount.manufacturerno,
                     discount.artcategoryno,
                     discount.paymenttargetno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.paymenttermtype,
                     discount.targetqty,
                     discount.exceedancepct,
                     discount.article_no_pack,
                     discount.refundvalue,
                     discount.promotion_no,
                     discount.DiscountApplyTo,
                     discount.DiscountCalcFrom
                from DISCOUNT
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.ArticleNo	 =	0 and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate  and
                        Discount.CustomerNo	 =	:d->CUSTOMERNO;
        exec sql open CSelListCst63;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListCst63" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListCst63;
        return CheckSql( fun, stError, "%s", "close CSelListCst63" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListCst63 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->GRPDISCOUNTTYP,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTQTYPCT,
                     :d->SURCHARGEPCT,
                     :d->PHARMGRPEXCLUDED,
                     :d->FIXEDPRICE,
                     :d->REFUNDPCT,
                     :d->INTERNALDISCOUNT,
                     :d->DISCOUNTARTICLE,
                     :d->UPDATESIGN,
                     :d->BASE_VALUE,
                     :d->BASE_MULT_STD_QTY,
                     :d->NO_MULTIPLE_QTY,
                     :d->FIXEDDISCOUNTVALUE,
                     :d->MANUFACTURERNO,
                     :d->ARTCATEGORYNO,
                     :d->PAYMENTTARGETNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PAYMENTTERMTYPE,
                     :d->TARGETQTY,
                     :d->EXCEEDANCEPCT,
                     :d->ARTICLE_NO_PACK,
                     :d->REFUNDVALUE,
                     :d->PROMOTION_NO,
                     :d->DISCOUNTAPPLYTO,
                     :d->DISCOUNTCALCFROM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListCst63" )) == IS_ERROR )
        return rc;
    return rc;
}

/* discountanz::SelListCstEKG *************************************************/

retClient discountanz_SelListCstEKG(discountanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "discountanz_SelListCstEKG";
    exec sql begin declare section;
    discountanzS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListCstEKG64 cursor with hold for
                  select discount.BranchNo,
                     discount.ArticleNo,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     discount.GrpDiscountTyp,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountType,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountQtyPct,
                     discount.SurchargePct,
                     discount.PharmGrpExcluded,
                     discount.FixedPrice,
                     discount.RefundPct,
                     discount.InternalDiscount,
                     discount.DiscountArticle,
                     discount.UpdateSign,
                     discount.base_value,
                     discount.base_mult_std_qty,
                     discount.no_multiple_qty,
                     discount.FixedDiscountValue,
                     discount.manufacturerno,
                     discount.artcategoryno,
                     discount.paymenttargetno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.paymenttermtype,
                     discount.targetqty,
                     discount.exceedancepct,
                     discount.article_no_pack,
                     discount.refundvalue,
                     discount.promotion_no,
                     discount.DiscountApplyTo,
                     discount.DiscountCalcFrom
                from DISCOUNT
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.ArticleNo	 =	0 and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate  and
                        Discount.PharmacyGroupId	 in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO);
        exec sql open CSelListCstEKG64;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListCstEKG64" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListCstEKG64;
        return CheckSql( fun, stError, "%s", "close CSelListCstEKG64" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListCstEKG64 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->GRPDISCOUNTTYP,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTQTYPCT,
                     :d->SURCHARGEPCT,
                     :d->PHARMGRPEXCLUDED,
                     :d->FIXEDPRICE,
                     :d->REFUNDPCT,
                     :d->INTERNALDISCOUNT,
                     :d->DISCOUNTARTICLE,
                     :d->UPDATESIGN,
                     :d->BASE_VALUE,
                     :d->BASE_MULT_STD_QTY,
                     :d->NO_MULTIPLE_QTY,
                     :d->FIXEDDISCOUNTVALUE,
                     :d->MANUFACTURERNO,
                     :d->ARTCATEGORYNO,
                     :d->PAYMENTTARGETNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PAYMENTTERMTYPE,
                     :d->TARGETQTY,
                     :d->EXCEEDANCEPCT,
                     :d->ARTICLE_NO_PACK,
                     :d->REFUNDVALUE,
                     :d->PROMOTION_NO,
                     :d->DISCOUNTAPPLYTO,
                     :d->DISCOUNTCALCFROM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListCstEKG64" )) == IS_ERROR )
        return rc;
    return rc;
}

/* discountanz::SelListDG *****************************************************/

retClient discountanz_SelListDG(discountanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "discountanz_SelListDG";
    exec sql begin declare section;
    discountanzS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListDG65 cursor with hold for
                  select discount.BranchNo,
                     discount.ArticleNo,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     discount.GrpDiscountTyp,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountType,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountQtyPct,
                     discount.SurchargePct,
                     discount.PharmGrpExcluded,
                     discount.FixedPrice,
                     discount.RefundPct,
                     discount.InternalDiscount,
                     discount.DiscountArticle,
                     discount.UpdateSign,
                     discount.base_value,
                     discount.base_mult_std_qty,
                     discount.no_multiple_qty,
                     discount.FixedDiscountValue,
                     discount.manufacturerno,
                     discount.artcategoryno,
                     discount.paymenttargetno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.paymenttermtype,
                     discount.targetqty,
                     discount.exceedancepct,
                     discount.article_no_pack,
                     discount.refundvalue,
                     discount.promotion_no,
                     discount.DiscountApplyTo,
                     discount.DiscountCalcFrom
                from DISCOUNT, discountgrpmem
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        discountgrpmem.articleno	 =	:d->ARTICLENO and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate  and
                        Discount.BranchNo	 =	discountgrpmem.branchno and
                        discount.discountgrpno = discountgrpmem.discountgrpno
                        order by Discount.BaseQty,Discount.paymenttargetno;
        exec sql open CSelListDG65;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListDG65" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListDG65;
        return CheckSql( fun, stError, "%s", "close CSelListDG65" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListDG65 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->GRPDISCOUNTTYP,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTQTYPCT,
                     :d->SURCHARGEPCT,
                     :d->PHARMGRPEXCLUDED,
                     :d->FIXEDPRICE,
                     :d->REFUNDPCT,
                     :d->INTERNALDISCOUNT,
                     :d->DISCOUNTARTICLE,
                     :d->UPDATESIGN,
                     :d->BASE_VALUE,
                     :d->BASE_MULT_STD_QTY,
                     :d->NO_MULTIPLE_QTY,
                     :d->FIXEDDISCOUNTVALUE,
                     :d->MANUFACTURERNO,
                     :d->ARTCATEGORYNO,
                     :d->PAYMENTTARGETNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PAYMENTTERMTYPE,
                     :d->TARGETQTY,
                     :d->EXCEEDANCEPCT,
                     :d->ARTICLE_NO_PACK,
                     :d->REFUNDVALUE,
                     :d->PROMOTION_NO,
                     :d->DISCOUNTAPPLYTO,
                     :d->DISCOUNTCALCFROM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListDG65" )) == IS_ERROR )
        return rc;
    return rc;
}

/* discountanz::SelListGrp ****************************************************/

retClient discountanz_SelListGrp(discountanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "discountanz_SelListGrp";
    exec sql begin declare section;
    discountanzS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListGrp66 cursor with hold for
                  select discount.BranchNo,
                     discount.ArticleNo,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     discount.GrpDiscountTyp,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountType,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountQtyPct,
                     discount.SurchargePct,
                     discount.PharmGrpExcluded,
                     discount.FixedPrice,
                     discount.RefundPct,
                     discount.InternalDiscount,
                     discount.DiscountArticle,
                     discount.UpdateSign,
                     discount.base_value,
                     discount.base_mult_std_qty,
                     discount.no_multiple_qty,
                     discount.FixedDiscountValue,
                     discount.manufacturerno,
                     discount.artcategoryno,
                     discount.paymenttargetno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.paymenttermtype,
                     discount.targetqty,
                     discount.exceedancepct,
                     discount.article_no_pack,
                     discount.refundvalue,
                     discount.promotion_no,
                     discount.DiscountApplyTo,
                     discount.DiscountCalcFrom
                from DISCOUNT
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.ArticleNo	 =	:d->ARTICLENO	 and
                        (Discount.CustomerNo	 =	:d->CUSTOMERNO	 or
                        (Discount.CustomerNo	 =	0 and
                        ( Discount.PharmacyGroupId = '000' or
                        (Discount.PharmacyGroupId	 in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO) ) or
                        Discount.CustomerNo	=	:d->CUSTOMERNO ) and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate  and
                        ( Discount.PharmGrpExcluded = '000' or
                        (Discount.PharmGrpExcluded	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) ) and
                        ( Discount.PharmGrpExcl_2 = '000' or
                        (Discount.PharmGrpExcl_2	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) ) and
                        ( Discount.PharmGrpExcl_3 = '000' or
                        (Discount.PharmGrpExcl_3	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) ) ) )
                        order by Discount.BaseQty,Discount.paymenttargetno;
        exec sql open CSelListGrp66;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListGrp66" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListGrp66;
        return CheckSql( fun, stError, "%s", "close CSelListGrp66" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListGrp66 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->GRPDISCOUNTTYP,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTQTYPCT,
                     :d->SURCHARGEPCT,
                     :d->PHARMGRPEXCLUDED,
                     :d->FIXEDPRICE,
                     :d->REFUNDPCT,
                     :d->INTERNALDISCOUNT,
                     :d->DISCOUNTARTICLE,
                     :d->UPDATESIGN,
                     :d->BASE_VALUE,
                     :d->BASE_MULT_STD_QTY,
                     :d->NO_MULTIPLE_QTY,
                     :d->FIXEDDISCOUNTVALUE,
                     :d->MANUFACTURERNO,
                     :d->ARTCATEGORYNO,
                     :d->PAYMENTTARGETNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PAYMENTTERMTYPE,
                     :d->TARGETQTY,
                     :d->EXCEEDANCEPCT,
                     :d->ARTICLE_NO_PACK,
                     :d->REFUNDVALUE,
                     :d->PROMOTION_NO,
                     :d->DISCOUNTAPPLYTO,
                     :d->DISCOUNTCALCFROM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListGrp66" )) == IS_ERROR )
        return rc;
    return rc;
}

/* discountanz::SelListGrpHerst ***********************************************/

retClient discountanz_SelListGrpHerst(discountanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "discountanz_SelListGrpHerst";
    exec sql begin declare section;
    discountanzS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListGrpHerst67 cursor with hold for
                  select discount.BranchNo,
                     discount.ArticleNo,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     discount.GrpDiscountTyp,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountType,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountQtyPct,
                     discount.SurchargePct,
                     discount.PharmGrpExcluded,
                     discount.FixedPrice,
                     discount.RefundPct,
                     discount.InternalDiscount,
                     discount.DiscountArticle,
                     discount.UpdateSign,
                     discount.base_value,
                     discount.base_mult_std_qty,
                     discount.no_multiple_qty,
                     discount.FixedDiscountValue,
                     discount.manufacturerno,
                     discount.artcategoryno,
                     discount.paymenttargetno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.paymenttermtype,
                     discount.targetqty,
                     discount.exceedancepct,
                     discount.article_no_pack,
                     discount.refundvalue,
                     discount.promotion_no,
                     discount.DiscountApplyTo,
                     discount.DiscountCalcFrom
                from DISCOUNT
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.manufacturerno	 =	:d->MANUFACTURERNO	 and
                        ( Discount.PharmacyGroupId = '000' or
                        (Discount.PharmacyGroupId	 in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO) ) or
                        Discount.CustomerNo	=	:d->CUSTOMERNO ) and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate  and
                        ( Discount.PharmGrpExcluded = '000' or
                        (Discount.PharmGrpExcluded	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) ) and
                        ( Discount.PharmGrpExcl_2 = '000' or
                        (Discount.PharmGrpExcl_2	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) ) and
                        ( Discount.PharmGrpExcl_3 = '000' or
                        (Discount.PharmGrpExcl_3	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) )
                        order by Discount.BaseQty,Discount.paymenttargetno;
        exec sql open CSelListGrpHerst67;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListGrpHerst67" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListGrpHerst67;
        return CheckSql( fun, stError, "%s", "close CSelListGrpHerst67" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListGrpHerst67 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->GRPDISCOUNTTYP,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTQTYPCT,
                     :d->SURCHARGEPCT,
                     :d->PHARMGRPEXCLUDED,
                     :d->FIXEDPRICE,
                     :d->REFUNDPCT,
                     :d->INTERNALDISCOUNT,
                     :d->DISCOUNTARTICLE,
                     :d->UPDATESIGN,
                     :d->BASE_VALUE,
                     :d->BASE_MULT_STD_QTY,
                     :d->NO_MULTIPLE_QTY,
                     :d->FIXEDDISCOUNTVALUE,
                     :d->MANUFACTURERNO,
                     :d->ARTCATEGORYNO,
                     :d->PAYMENTTARGETNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PAYMENTTERMTYPE,
                     :d->TARGETQTY,
                     :d->EXCEEDANCEPCT,
                     :d->ARTICLE_NO_PACK,
                     :d->REFUNDVALUE,
                     :d->PROMOTION_NO,
                     :d->DISCOUNTAPPLYTO,
                     :d->DISCOUNTCALCFROM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListGrpHerst67" )) == IS_ERROR )
        return rc;
    return rc;
}

/* discountanz::SelListHerst **************************************************/

retClient discountanz_SelListHerst(discountanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "discountanz_SelListHerst";
    exec sql begin declare section;
    discountanzS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelListHerst68 cursor with hold for
                  select discount.BranchNo,
                     discount.ArticleNo,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     discount.GrpDiscountTyp,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountType,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountQtyPct,
                     discount.SurchargePct,
                     discount.PharmGrpExcluded,
                     discount.FixedPrice,
                     discount.RefundPct,
                     discount.InternalDiscount,
                     discount.DiscountArticle,
                     discount.UpdateSign,
                     discount.base_value,
                     discount.base_mult_std_qty,
                     discount.no_multiple_qty,
                     discount.FixedDiscountValue,
                     discount.manufacturerno,
                     discount.artcategoryno,
                     discount.paymenttargetno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.paymenttermtype,
                     discount.targetqty,
                     discount.exceedancepct,
                     discount.article_no_pack,
                     discount.refundvalue,
                     discount.promotion_no,
                     discount.DiscountApplyTo,
                     discount.DiscountCalcFrom
                from DISCOUNT
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        Discount.manufacturerno	 =	:d->MANUFACTURERNO and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate
                        order by Discount.BaseQty,Discount.paymenttargetno;
        exec sql open CSelListHerst68;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelListHerst68" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelListHerst68;
        return CheckSql( fun, stError, "%s", "close CSelListHerst68" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelListHerst68 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->GRPDISCOUNTTYP,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTQTYPCT,
                     :d->SURCHARGEPCT,
                     :d->PHARMGRPEXCLUDED,
                     :d->FIXEDPRICE,
                     :d->REFUNDPCT,
                     :d->INTERNALDISCOUNT,
                     :d->DISCOUNTARTICLE,
                     :d->UPDATESIGN,
                     :d->BASE_VALUE,
                     :d->BASE_MULT_STD_QTY,
                     :d->NO_MULTIPLE_QTY,
                     :d->FIXEDDISCOUNTVALUE,
                     :d->MANUFACTURERNO,
                     :d->ARTCATEGORYNO,
                     :d->PAYMENTTARGETNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PAYMENTTERMTYPE,
                     :d->TARGETQTY,
                     :d->EXCEEDANCEPCT,
                     :d->ARTICLE_NO_PACK,
                     :d->REFUNDVALUE,
                     :d->PROMOTION_NO,
                     :d->DISCOUNTAPPLYTO,
                     :d->DISCOUNTCALCFROM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelListHerst68" )) == IS_ERROR )
        return rc;
    return rc;
}

/* discountanz::SellListGrpDG *************************************************/

retClient discountanz_SellListGrpDG(discountanzS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "discountanz_SellListGrpDG";
    exec sql begin declare section;
    discountanzS *d;
    long lDate;
    exec sql end declare section;

    d = a;

    lDate = ppGGetDate();
    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSellListGrpDG69 cursor with hold for
                  select discount.BranchNo,
                     discount.ArticleNo,
                     discount.DiscountGrpNo,
                     discount.PharmacyGroupId,
                     discount.CustomerNo,
                     discount.GrpDiscountTyp,
                     discount.DateFrom,
                     discount.DateTo,
                     discount.BaseQty,
                     discount.DiscountSpec,
                     discount.DiscountType,
                     discount.DiscountQty,
                     discount.DiscountValuePct,
                     discount.DiscountQtyPct,
                     discount.SurchargePct,
                     discount.PharmGrpExcluded,
                     discount.FixedPrice,
                     discount.RefundPct,
                     discount.InternalDiscount,
                     discount.DiscountArticle,
                     discount.UpdateSign,
                     discount.base_value,
                     discount.base_mult_std_qty,
                     discount.no_multiple_qty,
                     discount.FixedDiscountValue,
                     discount.manufacturerno,
                     discount.artcategoryno,
                     discount.paymenttargetno,
                     discount.grossprofitpct,
                     discount.addondiscountok,
                     discount.paymenttermtype,
                     discount.targetqty,
                     discount.exceedancepct,
                     discount.article_no_pack,
                     discount.refundvalue,
                     discount.promotion_no,
                     discount.DiscountApplyTo,
                     discount.DiscountCalcFrom
                from DISCOUNT, discountgrpmem
                  where Discount.BranchNo	 =	:d->BRANCHNO	 and
                        discountgrpmem.articleno = :d->ARTICLENO and
                        Discount.BranchNo	 =	discountgrpmem.BranchNo and
                        discount.discountgrpno = discountgrpmem.discountgrpno and
                        ( Discount.PharmacyGroupId = '000' or
                        (Discount.PharmacyGroupId	 in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO) ) or
                        Discount.CustomerNo	=	:d->CUSTOMERNO ) and
                        Discount.DateFrom	<=	:lDate  and
                        Discount.DateTo	>=	:lDate  and
                        ( Discount.PharmGrpExcluded = '000' or
                        (Discount.PharmGrpExcluded	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) ) and
                        ( Discount.PharmGrpExcl_2 = '000' or
                        (Discount.PharmGrpExcl_2	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) ) and
                        ( Discount.PharmGrpExcl_3 = '000' or
                        (Discount.PharmGrpExcl_3	not in (select customerpharmacygr.PharmacyGroupId from customerpharmacygr
                        where
                        Discount.BranchNo	 =	customerpharmacygr.BranchNo and
                        customerpharmacygr.CustomerNo	=	:d->CUSTOMERNO ) ) )
                        order by Discount.BaseQty,Discount.paymenttargetno;
        exec sql open CSellListGrpDG69;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSellListGrpDG69" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSellListGrpDG69;
        return CheckSql( fun, stError, "%s", "close CSellListGrpDG69" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSellListGrpDG69 into :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->DISCOUNTGRPNO,
                     :d->PHARMACYGROUPID,
                     :d->CUSTOMERNO,
                     :d->GRPDISCOUNTTYP,
                     :d->DATEFROM,
                     :d->DATETO,
                     :d->BASEQTY,
                     :d->DISCOUNTSPEC,
                     :d->DISCOUNTTYPE,
                     :d->DISCOUNTQTY,
                     :d->DISCOUNTVALUEPCT,
                     :d->DISCOUNTQTYPCT,
                     :d->SURCHARGEPCT,
                     :d->PHARMGRPEXCLUDED,
                     :d->FIXEDPRICE,
                     :d->REFUNDPCT,
                     :d->INTERNALDISCOUNT,
                     :d->DISCOUNTARTICLE,
                     :d->UPDATESIGN,
                     :d->BASE_VALUE,
                     :d->BASE_MULT_STD_QTY,
                     :d->NO_MULTIPLE_QTY,
                     :d->FIXEDDISCOUNTVALUE,
                     :d->MANUFACTURERNO,
                     :d->ARTCATEGORYNO,
                     :d->PAYMENTTARGETNO,
                     :d->GROSSPROFITPCT,
                     :d->ADDONDISCOUNTOK,
                     :d->PAYMENTTERMTYPE,
                     :d->TARGETQTY,
                     :d->EXCEEDANCEPCT,
                     :d->ARTICLE_NO_PACK,
                     :d->REFUNDVALUE,
                     :d->PROMOTION_NO,
                     :d->DISCOUNTAPPLYTO,
                     :d->DISCOUNTCALCFROM;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSellListGrpDG69" )) == IS_ERROR )
        return rc;
    return rc;
}



/* discountanz: Insert ********************************************************/



/* discountanz: Update ********************************************************/



/* discountanz: Select ********************************************************/



/* discountanz: Other *********************************************************/



/******************************************************************************/
/*                                                                            */
/* header  : stockentry.cxx                                                   */
/* Author  : produced by DADE 6.22.2                                          */
/* made    : Fri Jun 17 13:46:39 2022                                         */
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
#include "artikel.h"

/* stockentry: Select *********************************************************/

/* stockentry::SelList ********************************************************/

retClient stockentry_SelList(stockentryS *a, tError *stError, bool bIsTrans)
{
    retClient rc = IS_OK;
    char *fun = "stockentry_SelList";
    exec sql begin declare section;
    stockentryS *d;
    exec sql end declare section;

    d = a;

    if ( a->FETCH_REL == SET_OPEN )
    {
        exec sql declare CSelList70 cursor with hold for
                  select stockentry.date,
                     stockentry.BranchNo,
                     stockentry.ArticleNo,
                     artikellokal.bestand,
                     artikelzentral.einheit,
                     artikelzentral.artikel_name
                from stockentry,artikelzentral,artikellokal
                  where StockEntry.date	 =	:d->DATE	 and
                        StockEntry.BranchNo	 =	:d->BRANCHNO	 and
                        artikellokal.filialnr	 =	StockEntry.BranchNo and
                        artikellokal.artikel_nr	 =	StockEntry.ArticleNo and
                        artikelzentral.artikel_nr	 =	StockEntry.ArticleNo
                        order by artikelzentral.artikel_name, artikelzentral.einheit;
        exec sql open CSelList70;
        if ( ( rc=CheckSql( fun, stError, "%s", "open CSelList70" ) ) != IS_OK )
            return rc;
    }

    if ( a->FETCH_REL == SET_CLOSE )
    {
        if ( bIsTrans )
        {
            if ( ( rc = Commit( fun, stError ) ) != IS_OK )
                return rc;
        }
        exec sql close CSelList70;
        return CheckSql( fun, stError, "%s", "close CSelList70" );
    }

    if ( bIsTrans )
    {
        if ( ( rc = Begin( fun, stError ) ) != IS_OK )
            return rc;
    }
    exec sql fetch CSelList70 into :d->DATE,
                     :d->BRANCHNO,
                     :d->ARTICLENO,
                     :d->BESTAND,
                     :d->EINHEIT,
                     :d->ARTIKEL_NAME;
    if ((rc=CheckSql( fun, stError, "%s", "fetch CSelList70" )) == IS_ERROR )
        return rc;
    return rc;
}



/* stockentry: Insert *********************************************************/



/* stockentry: Update *********************************************************/



/* stockentry: Select *********************************************************/



/* stockentry: Other **********************************************************/



