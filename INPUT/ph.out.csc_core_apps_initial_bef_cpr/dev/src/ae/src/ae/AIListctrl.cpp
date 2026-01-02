/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "AIListctrl.h"

#include <assert.h>


bool CAIListCtrl::init()
{
    insertCol(COL_AI_KB,              CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE),  LVCFMT_LEFT,    30);
    insertCol(COL_AI_AMGE,            CResString::ex().getStrTblText(AETXT_AMGE),           LVCFMT_RIGHT,   40);
    insertCol(COL_AI_BMGE,            CResString::ex().getStrTblText(AETXT_BMGE),           LVCFMT_RIGHT,   40);
    insertCol(COL_AI_NRME,            CResString::ex().getStrTblText(AETXT_NRME),           LVCFMT_RIGHT,   30);
    insertCol(COL_AI_VERBME,          CResString::ex().getStrTblText(AETXT_VERBME),         LVCFMT_RIGHT,   25);
    insertCol(COL_AI_VBTYP,           CResString::ex().getStrTblText(AETXT_VB_TYP),         LVCFMT_RIGHT,   25);
    insertCol(COL_AI_UMGESCHL,        CResString::ex().getStrTblText(AETXT_ART_UMGESCHL),   LVCFMT_RIGHT,   20);
    insertCol(COL_AI_EINHEIT,         CResString::ex().getStrTblText(AETXT_EINHEIT),        LVCFMT_RIGHT,   50);
    insertCol(COL_AI_FU,              CResString::ex().getStrTblText(AETXT_FU),             LVCFMT_CENTER,  30);
    insertCol(COL_AI_ARTIKELNAME,     CResString::ex().getStrTblText(AETXT_ARTIKELNAME),    LVCFMT_LEFT,   120);
    insertCol(COL_AI_DAF,             CResString::ex().getStrTblText(AETXT_DAF),            LVCFMT_CENTER,  30);
    insertCol(COL_AI_KENNZEICHEN,     CResString::ex().getStrTblText(AETXT_KZ_KENNZEICHEN), LVCFMT_CENTER,  30);
    insertCol(COL_AI_PA,              CResString::ex().getStrTblText(AETXT_PA),             LVCFMT_CENTER,  30);
    insertCol(COL_AI_PNR,             CResString::ex().getStrTblText(AETXT_PNR),            LVCFMT_RIGHT,   35);
    insertCol(COL_AI_ARTICLE_CODE,    CResString::ex().getStrTblText(AETXT_ARTICLE_CODE),   LVCFMT_RIGHT,   60);
    insertCol(COL_AI_VERBUND,         CResString::ex().getStrTblText(AETXT_VERBUND),        LVCFMT_CENTER,  20);
    insertCol(COL_AI_PREIS, CResString::ex().getStrTblText(AeGetApp()->IsBG() ? AETXT_PREIS : AETXT_AEP), LVCFMT_RIGHT, 50);
    insertCol(COL_AI_PREISFAKTUR,     CResString::ex().getStrTblText(AETXT_PREISFAKTUR),    LVCFMT_RIGHT,   50);
    insertCol(COL_AI_RABATT,          CResString::ex().getStrTblText(AETXT_RABATT),         LVCFMT_RIGHT,   50);
    insertCol(COL_AI_RABATT_MAN,      CResString::ex().getStrTblText(AETXT_RABATT_MAN),     LVCFMT_RIGHT,   50);
    insertCol(COL_AI_AVP,             CResString::ex().getStrTblText(AETXT_AVP),            LVCFMT_RIGHT,   50);
    insertCol(COL_AI_BEMERK,          CResString::ex().getStrTblText(IDS_BEMERK),           LVCFMT_LEFT,   200);
    insertCol(COL_AI_FILI,            " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_AI_CHARGE,          CResString::ex().getStrTblText(AETXT_CHARGE),         LVCFMT_LEFT,     0);
    insertCol(COL_AI_PROMOTYP,        " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_AI_PROMONR,         " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_AI_PHARMACYGROUPID, " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_AI_DISCOUNTGRPNO,   " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_AI_BASEQTY,         " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_AI_BASE_VALUE,      " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_AI_PZN,             CResString::ex().getStrTblText(AETXT_PZN),            LVCFMT_RIGHT,   60);
    insertCol(COL_AI_DELIVERYDATE,    CResString::ex().getStrTblText(AETXT_DELIVERYDATE),   LVCFMT_LEFT,    80);
    insertCol(COL_AI_DELIVERYTIME,    CResString::ex().getStrTblText(AETXT_DELIVERYTIME),   LVCFMT_LEFT,    60);
    insertCol(COL_AI_NATRABESTELLT,   CResString::ex().getStrTblText(AETXT_NATRABESTELLT),  LVCFMT_LEFT,    60);

    return VListCtrl::init();
}

void CAIListCtrl::refreshItem(const int /*iItem*/)
{
}

bool CAIListCtrl::isColNumber(const int /*iCol*/) const
{
    return false;
}

bool CAIListCtrl::isColEditable(const int /*iCol*/) const
{
    return false;
}

UINT CAIListCtrl::getLimitText(const int /*iCol*/) const
{
    return 0;
}
