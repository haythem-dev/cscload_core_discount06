// DKommiChange.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <auftraginfo.h>
#include "KCListctrl.h"
#include "DInfAnzAuft.h"
#include "DKommiChange.h"


// CDKommiChange-Dialogfeld

IMPLEMENT_DYNAMIC(CDKommiChange, CDialog)
CDKommiChange::CDKommiChange(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDKommiChange::IDD, pParent)
{
    m_List1 = new CKCListCtrl;
    assert(m_List1);
    m_CT_Datum = 0;
    m_SelDate = 0;
}

CDKommiChange::~CDKommiChange()
{
    delete m_List1;
    m_List1 = 0;
}

void CDKommiChange::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATUM, m_DT_Datum);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATUM, m_CT_Datum);
    DDX_Control(pDX, IDC_CHECK_ALLE, m_CheckAlle);
    DDX_Control(pDX, IDC_CHECK_DATUM, m_CheckDatum);
    DDX_Control(pDX, IDC_LIST1, *m_List1);
}


BEGIN_MESSAGE_MAP(CDKommiChange, CDialogMultiLang)
    ON_BN_CLICKED(IDC_CHECK_DATUM, OnCheckDatum)
    ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
    ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
    ON_BN_CLICKED(IDC_BUTTON_AUFTRAG, OnButtonAuftrag)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedListCtrl)
END_MESSAGE_MAP()


// CDKommiChange-Meldungshandler

BOOL CDKommiChange::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_List1->init();
    m_List1->SetExtendedStyle(m_List1->GetExtendedStyle() | LVS_EX_GRIDLINES );        // Grid
    CTM zeit;

    zeit.Server(AafilGetdatetime);
    CTime end = CTimeFromDateLongMinTime(zeit.s.DATUM);
    CTimeSpan y(3600, 0, 0, 0);
    CTime ctime = end - y;
    m_DT_Datum.SetRange(&ctime, &end);
    m_DT_Datum.SetTime(&end);
    if (GetAeUser().IsCheckPickingChange())
    {
        GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(TRUE);
        GetDlgItem(IDC_BUTTON_UPDATE)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_BUTTON_UPDATE)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_UPDATE)->ShowWindow(SW_HIDE);
    }

    CenterWindow();
    GetPage();
    CListCtrlHelper::SetFocusSelectedFocused(*m_List1, 0);

    return FALSE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDKommiChange::GetPage()
{
    int index;
    CPOSCHANGE actchange;
    CPOSCHANGEHIST histchange;
    actchange.SetVertriebszentrumnr(AeGetApp()->VzNr());
    histchange.SetVertriebszentrumnr(AeGetApp()->VzNr());
    actchange.SetSwchecked('0');
    histchange.SetSwchecked('0');
    if (IsDlgButtonChecked(IDC_CHECK_ALLE))
    {
        actchange.SetSwchecked('1');
        histchange.SetSwchecked('1');
    }
    if (IsDlgButtonChecked(IDC_CHECK_DATUM))
    {
        histchange.SetDatum(m_CT_Datum.GetYear() * 10000 +
                            m_CT_Datum.GetMonth() * 100 +
                            m_CT_Datum.GetDay());
        m_SelDate = histchange.GetDatum();
    }
    else
    {
        m_SelDate = 0;
    }
    ppString cText;
    CString Hilfe;
    m_List1->DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (IsDlgButtonChecked(IDC_CHECK_DATUM))
        {
            if (histchange.SelList() != SRV_OK)
                break;
        }
        else
        {
            if (actchange.SelList() != SRV_OK)
                break;
        }
        index = m_List1->GetItemCount();
        if (m_List1->InsertItem(index, "") == -1)
        {
            return;
        }
        if (IsDlgButtonChecked(IDC_CHECK_DATUM))
        {
            m_List1->SetCheck(index, histchange.GetSwchecked() == '1' ? TRUE : FALSE);
            m_List1->SetItemText(index, KC_COL_CHECK, kb.Next());
            Hilfe.Format("%d", histchange.GetKdauftragnr());
            m_List1->SetItemText(index, KC_COL_AUF_NR, Hilfe);
            histchange.GetNameapo(cText);
            m_List1->SetItemText(index, KC_COL_KUNDE, cText);
            if (AeGetApp()->IsBG())
            {
                histchange.GetArtikel_langname(cText);
            }
            else
            {
                histchange.GetArtikel_name(cText);
            }
            m_List1->SetItemText(index, KC_COL_ARTIKEL, cText);
            Hilfe.Format("%d", histchange.GetMengebestellt());
            m_List1->SetItemText(index, KC_COL_BESTELLT, Hilfe);
            Hilfe.Format("%d", histchange.GetMengebestaetigt());
            m_List1->SetItemText(index, KC_COL_BESTAETIGT, Hilfe);
            Hilfe.Format("%d", histchange.GetMenge_alt());
            m_List1->SetItemText(index, KC_COL_MENGE_ALT, Hilfe);
            histchange.GetInvoicenumber(cText);
            m_List1->SetItemText(index, KC_COL_RECHNUNG, cText);
            Hilfe.Format("%d", histchange.GetPosnr());
            m_List1->SetItemText(index, KC_COL_POSNR, Hilfe);
        }
        else
        {
            m_List1->SetCheck(index, actchange.GetSwchecked() == '1' ? TRUE : FALSE);
            m_List1->SetItemText(index, KC_COL_CHECK, kb.Next());
            Hilfe.Format("%d", actchange.GetKdauftragnr());
            m_List1->SetItemText(index, KC_COL_AUF_NR, Hilfe);
            actchange.GetNameapo(cText);
            m_List1->SetItemText(index, KC_COL_KUNDE, cText);
            if (AeGetApp()->IsBG())
            {
                actchange.GetArtikel_langname(cText);
            }
            else
            {
                actchange.GetArtikel_name(cText);
            }
            m_List1->SetItemText(index, KC_COL_ARTIKEL, cText);
            Hilfe.Format("%d", actchange.GetMengebestellt());
            m_List1->SetItemText(index, KC_COL_BESTELLT, Hilfe);
            Hilfe.Format("%d", actchange.GetMengebestaetigt());
            m_List1->SetItemText(index, KC_COL_BESTAETIGT, Hilfe);
            Hilfe.Format("%d", actchange.GetMenge_alt());
            m_List1->SetItemText(index, KC_COL_MENGE_ALT, Hilfe);
            actchange.GetInvoicenumber(cText);
            m_List1->SetItemText(index, KC_COL_RECHNUNG, cText);
            Hilfe.Format("%d", actchange.GetPosnr());
            m_List1->SetItemText(index, KC_COL_POSNR, Hilfe);
        }
    }
    UpdateData(FALSE);
}

void CDKommiChange::OnCheckDatum()
{
    if (IsDlgButtonChecked(IDC_CHECK_DATUM))
    {
        GetDlgItem(IDC_DATETIMEPICKER_DATUM)->EnableWindow(TRUE);
        GetDlgItem(IDC_DATETIMEPICKER_DATUM)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_DATETIMEPICKER_DATUM)->EnableWindow(FALSE);
        GetDlgItem(IDC_DATETIMEPICKER_DATUM)->ShowWindow(SW_HIDE);
    }
}

void CDKommiChange::OnButtonRefresh()
{
    UpdateData();
    GetPage();
}

void CDKommiChange::OnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    if ((pNMLV->uChanged & LVIF_STATE) == LVIF_STATE)   // Status-Änderung
    {
        UINT uiNewState = (pNMLV->uNewState & LVIS_STATEIMAGEMASK);
        UINT uiOldState = (pNMLV->uOldState & LVIS_STATEIMAGEMASK);

        if (uiOldState != uiNewState)
        {
            switch (uiNewState >> 12)
            {
            case 0x0001:    // uncheck
            {
                if ((uiOldState >> 12) == 0x02)
                {
                    CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, pNMLV->iItem);
                }
            }

            break;

            case 0x0002:    // check
            {
                CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, pNMLV->iItem);
            }
            break;

            case 0x0000:    // kommt aus InsertItem()
            default:
                assert(0);
                break;
            }
        }
    }

    *pResult = 0L;
}

void CDKommiChange::OnButtonUpdate()
{
    UpdateData();
    for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
    {
        if (m_SelDate > 0)
        {
            CPOSCHANGEHIST histchange;
            histchange.SetSwchecked(m_List1->GetCheck(pos) ? '1' : '0');
            histchange.SetDatum(m_SelDate);
            histchange.SetKdauftragnr(atol(m_List1->GetItemText(pos, KC_COL_AUF_NR)));
            histchange.SetPosnr(atoi(m_List1->GetItemText(pos, KC_COL_POSNR)));
            histchange.Update();
        }
        else
        {
            CPOSCHANGE actchange;
            actchange.SetSwchecked(m_List1->GetCheck(pos) ? '1' : '0');
            actchange.SetKdauftragnr(atol(m_List1->GetItemText(pos, KC_COL_AUF_NR)));
            actchange.SetPosnr(atoi(m_List1->GetItemText(pos, KC_COL_POSNR)));
            actchange.Update();
        }
    }
    GetPage();
}

void CDKommiChange::OnButtonAuftrag()
{
    int pos = m_List1->GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    CDInfAnzAuft dlgInfAnzAuft;
    dlgInfAnzAuft.m_AuftrNr = atol(m_List1->GetItemText(pos, KC_COL_AUF_NR));
    dlgInfAnzAuft.m_Datum = m_SelDate;
    if (dlgInfAnzAuft.m_AuftrNr != 0)
    {
        dlgInfAnzAuft.DoModal();
    }
}
