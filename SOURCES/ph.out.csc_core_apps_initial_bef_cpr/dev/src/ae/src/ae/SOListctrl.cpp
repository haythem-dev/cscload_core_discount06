/*----------------------------------------------------------------------------*/
// Includes
/*----------------------------------------------------------------------------*/
#include "stdafx.h"

#include "SOListctrl.h"

#include <assert.h>

/**---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*/
bool CSOListCtrl::init()
{
    insertCol(COL_KB,              CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE),  LVCFMT_LEFT,    30);
    insertCol(COL_AMGE,            CResString::ex().getStrTblText(AETXT_AMGE),           LVCFMT_RIGHT,   40);
    insertCol(COL_BMGE,            CResString::ex().getStrTblText(AETXT_BMGE),           LVCFMT_RIGHT,   40);
    insertCol(COL_NRME,            CResString::ex().getStrTblText(AETXT_NRME),           LVCFMT_RIGHT,   30);
    insertCol(COL_VERBME,          CResString::ex().getStrTblText(AETXT_VERBME),         LVCFMT_RIGHT,   25);
    insertCol(COL_UMGESCHL,        CResString::ex().getStrTblText(AETXT_ART_UMGESCHL),   LVCFMT_RIGHT,   20);
    insertCol(COL_EINHEIT,         CResString::ex().getStrTblText(AETXT_EINHEIT),        LVCFMT_RIGHT,   50);
    insertCol(COL_FU,              CResString::ex().getStrTblText(AETXT_FU),             LVCFMT_CENTER,  30);
    insertCol(COL_ARTIKELNAME,     CResString::ex().getStrTblText(AETXT_ARTIKELNAME),    LVCFMT_LEFT,   120);
    insertCol(COL_DAF,             CResString::ex().getStrTblText(AETXT_DAF),            LVCFMT_CENTER,  30);
    insertCol(COL_KENNZEICHEN,     CResString::ex().getStrTblText(AETXT_KZ_KENNZEICHEN), LVCFMT_CENTER,  30);
    insertCol(COL_PA,              CResString::ex().getStrTblText(AETXT_PA),             LVCFMT_CENTER,  30);
    insertCol(COL_PNR,             CResString::ex().getStrTblText(AETXT_PNR),            LVCFMT_RIGHT,   35);
    insertCol(COL_ARTICLE_CODE,    CResString::ex().getStrTblText(AETXT_ARTICLE_CODE),   LVCFMT_RIGHT,   60);
    insertCol(COL_VERBUND,         CResString::ex().getStrTblText(AETXT_VERBUND),        LVCFMT_CENTER,  20);
    insertCol(COL_PREIS, CResString::ex().getStrTblText(AeGetApp()->IsBG() ? AETXT_PREIS : AETXT_AEP), LVCFMT_RIGHT, 50);
    insertCol(COL_RABATT,          CResString::ex().getStrTblText(AETXT_RABATT),         LVCFMT_RIGHT,   50);
    insertCol(COL_RABATT_MAN,      CResString::ex().getStrTblText(AETXT_RABATT_MAN),     LVCFMT_RIGHT,   50);
    insertCol(COL_AVP,             CResString::ex().getStrTblText(AETXT_AVP),            LVCFMT_RIGHT,   50);
    insertCol(COL_BEMERK,          CResString::ex().getStrTblText(IDS_BEMERK),           LVCFMT_LEFT,   200);
    insertCol(COL_FILI,            " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_CHARGE,          CResString::ex().getStrTblText(AETXT_CHARGE),         LVCFMT_LEFT,     0);
    insertCol(COL_PROMOTYP,        " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_PROMONR,         " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_PHARMACYGROUPID, " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_DISCOUNTGRPNO,   " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_BASEQTY,         " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_BASE_VALUE,      " ",                                                  LVCFMT_RIGHT,    0);
    insertCol(COL_PZN,             CResString::ex().getStrTblText(AETXT_PZN),            LVCFMT_RIGHT,   60);

    return VListCtrl::init();
}

void CSOListCtrl::refreshItem(const int)
{
}

bool CSOListCtrl::isColNumber(const int) const
{
    return false;
}

bool CSOListCtrl::isColEditable(const int) const
{
    return false;
}

UINT CSOListCtrl::getLimitText(const int) const
{
    return 0;
}
