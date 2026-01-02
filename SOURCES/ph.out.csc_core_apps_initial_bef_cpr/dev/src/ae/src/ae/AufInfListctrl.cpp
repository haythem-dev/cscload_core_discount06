/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "AufInfListctrl.h"

#include <assert.h>

/**---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*/
bool CAufInfListCtrl::init()
{
    insertCol(COL_AMGE,         CResString::ex().getStrTblText(AETXT_AMGE),           LVCFMT_LEFT,    50);
    insertCol(COL_BMGE,         CResString::ex().getStrTblText(AETXT_BMGE),           LVCFMT_RIGHT,   35);
    insertCol(COL_NRME,         CResString::ex().getStrTblText(AETXT_NRME),           LVCFMT_RIGHT,   30);
    insertCol(COL_VERBME,       CResString::ex().getStrTblText(AETXT_VERBME),         LVCFMT_RIGHT,   30);
    insertCol(COL_UMGESCHL,     CResString::ex().getStrTblText(AETXT_ART_UMGESCHL),   LVCFMT_RIGHT,   20);
    insertCol(COL_EINHEIT,      CResString::ex().getStrTblText(AETXT_EINHEIT),        LVCFMT_RIGHT,   55);
    insertCol(COL_FU,           CResString::ex().getStrTblText(AETXT_FU),             LVCFMT_CENTER,  30);
    insertCol(COL_ARTIKELNAME,  CResString::ex().getStrTblText(AETXT_ARTIKELNAME),    LVCFMT_LEFT,   120);
    insertCol(COL_DAF,          CResString::ex().getStrTblText(AETXT_DAF),            LVCFMT_CENTER,  40);
    insertCol(COL_PA,           CResString::ex().getStrTblText(AETXT_PA),             LVCFMT_CENTER,  30);
    insertCol(COL_PNR,          CResString::ex().getStrTblText(AETXT_PNR),            LVCFMT_RIGHT,   35);
    insertCol(COL_CONT,         CResString::ex().getStrTblText(AETXT_CONT),           LVCFMT_RIGHT,   25);
    insertCol(COL_ARTICLECODE,  CResString::ex().getStrTblText(AETXT_ARTICLE_CODE),   LVCFMT_RIGHT,   70);
    insertCol(COL_PZN,          CResString::ex().getStrTblText(AETXT_ARTIKEL_NR),     LVCFMT_RIGHT,   60);
    insertCol(COL_VERBUND,      CResString::ex().getStrTblText(AETXT_VERBUND),        LVCFMT_CENTER,  20);
    insertCol(COL_VERBUNDFIL,   CResString::ex().getStrTblText(AETXT_VERBFIL),        LVCFMT_CENTER,  35);
    insertCol(COL_KENNZEICHEN,  CResString::ex().getStrTblText(AETXT_KZ_KENNZEICHEN), LVCFMT_RIGHT,   40);
    insertCol(COL_PREIS,        CResString::ex().getStrTblText(AETXT_PREIS),          LVCFMT_RIGHT,   40);
    insertCol(COL_PREISFAKTUR,  CResString::ex().getStrTblText(AETXT_PREISFAKTUR),    LVCFMT_RIGHT,   40);
    insertCol(COL_AVP,          CResString::ex().getStrTblText(AETXT_AVP),            LVCFMT_RIGHT,   40);
    insertCol(COL_PCT,          CResString::ex().getStrTblText(AETXT_RABATT),         LVCFMT_RIGHT,   45);
    insertCol(COL_BEMERK,       CResString::ex().getStrTblText(IDS_BEMERK),           LVCFMT_LEFT,   200);
    insertCol(COL_FILI,         " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_PREISTYP,     CResString::ex().getStrTblText(AETXT_PREIS_TYP),      LVCFMT_LEFT,     0);
    insertCol(COL_PROMONO,      CResString::ex().getStrTblText(AETXT_PROMO_NR),       LVCFMT_RIGHT,   45);
    insertCol(COL_PROMONAME,    CResString::ex().getStrTblText(AETXT_PROMOTION),      LVCFMT_LEFT,   200);
    insertCol(COL_ETPOS,        CResString::ex().getStrTblText(AETXT_POS_SPLITT),     LVCFMT_LEFT,     0);
    insertCol(COL_PROMOTYP,     CResString::ex().getStrTblText(AETXT_PROMOTYP),       LVCFMT_LEFT,     0);
    insertCol(COL_PRODQUOTA,    CResString::ex().getStrTblText(AETXT_PROD_QUOTA),     LVCFMT_LEFT,     0);
    insertCol(COL_VBTYP,        CResString::ex().getStrTblText(AETXT_VB_TYP),         LVCFMT_RIGHT,   25);
    insertCol(COL_DELIVERYDATE, CResString::ex().getStrTblText(AETXT_DELIVERYDATE),   LVCFMT_LEFT,    80);
    insertCol(COL_DELIVERYTIME, CResString::ex().getStrTblText(AETXT_DELIVERYTIME),   LVCFMT_LEFT,    60);
    insertCol(COL_PREISFREE,    CResString::ex().getStrTblText(AETXT_FREE_PRICE),     LVCFMT_LEFT,     0);
    insertCol(COL_PCTMAN,       CResString::ex().getStrTblText(AETXT_PCT_MAN),        LVCFMT_LEFT,     0);

    return VListCtrl::init();
}

void CAufInfListCtrl::refreshItem(const int /*iItem*/)
{
}

bool CAufInfListCtrl::isColNumber(const int /*iCol*/) const
{
    return false;
}

bool CAufInfListCtrl::isColEditable(const int /*iCol*/) const
{
    return false;
}

UINT CAufInfListCtrl::getLimitText(const int /*iCol*/) const
{
    return 0;
}
