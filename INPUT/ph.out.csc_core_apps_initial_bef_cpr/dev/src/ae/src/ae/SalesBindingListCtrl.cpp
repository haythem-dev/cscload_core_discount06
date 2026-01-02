#include "StdAfx.h"
#include "SalesBindingListCtrl.h"
#include "ListCtrlHelper.h"


static COLUMNS_TYPES SpaltenBindungen[] =
{
    0,  "", 200, LVCFMT_LEFT,
    1,  "",  80, LVCFMT_LEFT,
    2,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

#define NUM_SPALT_BIND 3


CSalesBindingListCtrl::CSalesBindingListCtrl()
{
}

bool CSalesBindingListCtrl::SetActive(long lEtartklasse1, bool bPsycho)
{
    SpaltenBindungen[0].Columns = CResString::ex().getStrTblText(AETXT_VERTRIEBS_BINDUNG);
    SpaltenBindungen[1].Columns = CResString::ex().getStrTblText(AETXT_GESETZT);
    SpaltenBindungen[2].Columns = "Feldname";

    if (!CListCtrlHelper::AddColumns(SpaltenBindungen, *this))
    {
        return false;
    }

    DeleteAllItems();

    UINT uiBindings[8];
    GetBindingsByCountry(&uiBindings[0]);

    WriteBindingLines(&uiBindings[0], lEtartklasse1, bPsycho);

    return true;
}

void CSalesBindingListCtrl::GetBindingsByCountry(UINT uiBindings[8])
{
    if (AeGetApp()->IsAT())
    {
        uiBindings[0] = AETXT_AT_BINDUNG8;
        uiBindings[1] = AETXT_AT_BINDUNG9;
        uiBindings[2] = AETXT_AT_BINDUNG10;
        uiBindings[3] = AETXT_AT_BINDUNG11;
        uiBindings[4] = AETXT_AT_BINDUNG12;
        uiBindings[5] = AETXT_AT_BINDUNG13;
        uiBindings[6] = AETXT_AT_BINDUNG14;
        uiBindings[7] = AETXT_AT_BINDUNG15;
    }
    else if (AeGetApp()->IsBG())
    {
        uiBindings[0] = AETXT_BG_BINDUNG8;
        uiBindings[1] = AETXT_BG_BINDUNG9;
        uiBindings[2] = AETXT_BG_BINDUNG10;
        uiBindings[3] = AETXT_BG_BINDUNG11;
        uiBindings[4] = AETXT_BG_BINDUNG12;
        uiBindings[5] = AETXT_BG_BINDUNG13;
        uiBindings[6] = AETXT_BG_BINDUNG14;
        uiBindings[7] = AETXT_BG_BINDUNG15;
    }
    else if (AeGetApp()->IsCH())
    {
        uiBindings[0] = AETXT_CH_BINDUNG8;
        uiBindings[1] = AETXT_CH_BINDUNG9;
        uiBindings[2] = AETXT_CH_BINDUNG10;
        uiBindings[3] = AETXT_CH_BINDUNG11;
        uiBindings[4] = AETXT_CH_BINDUNG12;
        uiBindings[5] = AETXT_CH_BINDUNG13;
        uiBindings[6] = AETXT_CH_BINDUNG14;
        uiBindings[7] = AETXT_CH_BINDUNG15;
    }
    else if (AeGetApp()->IsFR())
    {
        uiBindings[0] = AETXT_FR_BINDUNG8;
        uiBindings[1] = AETXT_FR_BINDUNG9;
        uiBindings[2] = AETXT_FR_BINDUNG10;
        uiBindings[3] = AETXT_FR_BINDUNG11;
        uiBindings[4] = AETXT_FR_BINDUNG12;
        uiBindings[5] = AETXT_FR_BINDUNG13;
        uiBindings[6] = AETXT_FR_BINDUNG14;
        uiBindings[7] = AETXT_FR_BINDUNG15;
    }
    else if (AeGetApp()->IsHR())
    {
        uiBindings[0] = AETXT_HR_BINDUNG8;
        uiBindings[1] = AETXT_HR_BINDUNG9;
        uiBindings[2] = AETXT_HR_BINDUNG10;
        uiBindings[3] = AETXT_HR_BINDUNG11;
        uiBindings[4] = AETXT_HR_BINDUNG12;
        uiBindings[5] = AETXT_HR_BINDUNG13;
        uiBindings[6] = AETXT_HR_BINDUNG14;
        uiBindings[7] = AETXT_HR_BINDUNG15;
    }
    else if (AeGetApp()->IsRS())
    {
        uiBindings[0] = AETXT_RS_BINDUNG8;
        uiBindings[1] = AETXT_RS_BINDUNG9;
        uiBindings[2] = AETXT_RS_BINDUNG10;
        uiBindings[3] = AETXT_RS_BINDUNG11;
        uiBindings[4] = AETXT_RS_BINDUNG12;
        uiBindings[5] = AETXT_RS_BINDUNG13;
        uiBindings[6] = AETXT_RS_BINDUNG14;
        uiBindings[7] = AETXT_RS_BINDUNG15;
    }
    else
    {
        uiBindings[0] = AETXT_DE_BINDUNG8;
        uiBindings[1] = AETXT_DE_BINDUNG9;
        uiBindings[2] = AETXT_DE_BINDUNG10;
        uiBindings[3] = AETXT_DE_BINDUNG11;
        uiBindings[4] = AETXT_DE_BINDUNG12;
        uiBindings[5] = AETXT_DE_BINDUNG13;
        uiBindings[6] = AETXT_DE_BINDUNG14;
        uiBindings[7] = AETXT_DE_BINDUNG15;
    }
}

void CSalesBindingListCtrl::WriteBindingLines(const UINT uiBindings[8], const long lEtartklasse1, const bool bPsycho)
{
    char etartklasse1[16 + 1];
    AllgBitleiste2Char((Bitleiste)lEtartklasse1, etartklasse1);

    CString binding;

    binding = CResString::ex().getStrTblText(AETXT_GESUNDHSCH);
    WriteLine(binding, (etartklasse1[0] == '1'));

    binding = CResString::ex().getStrTblText(AETXT_GIFTIG);
    WriteLine(binding, (etartklasse1[1] == '1'));

    binding = CResString::ex().getStrTblText(AETXT_SEHRGIFTIG);
    WriteLine(binding, (etartklasse1[2] == '1'));

    binding = CResString::ex().getStrTblText(AETXT_REZEPTPFLICHTIG);
    WriteLine(binding, (etartklasse1[3] == '1'));

    binding = CResString::ex().getStrTblText(AETXT_APOTHEKENPFLICHTIG);
    WriteLine(binding, (etartklasse1[4] == '1'));

    binding = CResString::ex().getStrTblText(AETXT_TAXPFLICHT);
    WriteLine(binding, (etartklasse1[5] == '1'));

    binding = CResString::ex().getStrTblText(AETXT_BTM);
    WriteLine(binding, (etartklasse1[6] == '1'));

    binding = CResString::ex().getStrTblText(AETXT_TIERARZNEI);
    WriteLine(binding, (etartklasse1[7] == '1'));

    binding = CResString::ex().getStrTblText(uiBindings[0]);
    WriteLine(binding, (etartklasse1[8] == '1'));

    binding = CResString::ex().getStrTblText(uiBindings[1]);
    WriteLine(binding, (etartklasse1[9] == '1'));

    binding = CResString::ex().getStrTblText(uiBindings[2]);
    WriteLine(binding, (etartklasse1[10] == '1'));

    binding = CResString::ex().getStrTblText(uiBindings[3]);
    WriteLine(binding, (etartklasse1[11] == '1'));

    binding = CResString::ex().getStrTblText(uiBindings[4]);
    WriteLine(binding, (etartklasse1[12] == '1'));

    binding = CResString::ex().getStrTblText(uiBindings[5]);
    WriteLine(binding, (etartklasse1[13] == '1'));

    binding = CResString::ex().getStrTblText(uiBindings[6]);
    WriteLine(binding, (etartklasse1[14] == '1'));

    binding = CResString::ex().getStrTblText(uiBindings[7]);
    WriteLine(binding, (etartklasse1[15] == '1'));

    binding = CResString::ex().getStrTblText(AETXT_PSYCHO);
    WriteLine(binding, bPsycho);
}

// bYesNo: yes=true, no=false
void CSalesBindingListCtrl::WriteLine(CString binding, bool bYesNo)
{
    const static CString yes = CResString::ex().getStrTblText(AETXT_JA);
    const static CString no = CResString::ex().getStrTblText(AETXT_NEIN);

    int index = GetItemCount();
    if (InsertItem(index, binding) == -1)
    {
        return;
    }
    SetItemText(index, 1, bYesNo ? yes : no);
}
