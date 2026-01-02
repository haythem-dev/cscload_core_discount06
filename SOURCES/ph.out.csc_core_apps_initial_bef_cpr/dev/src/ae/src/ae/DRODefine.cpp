// DRODefine.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "ROListctrl.h"
#include <string.h>
#include "DRODefine.h"


// CDRODefine-Dialogfeld

IMPLEMENT_DYNAMIC(CDRODefine, CDialog)
CDRODefine::CDRODefine(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRODefine::IDD, pParent)
{
    m_List1 = new CROListCtrl;
    assert(m_List1);
    m_cVon = _T("");
    m_cBis = _T("");
    m_dSumme = 0.0;
    m_dGut = 0.0;
    m_bFertig = false;
}

CDRODefine::~CDRODefine()
{
    delete m_List1;
    m_List1 = 0;
}

void CDRODefine::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_VON, m_cVon);
    DDX_Text(pDX, IDC_EDIT_BIS, m_cBis);
    DDX_Control(pDX, IDC_LIST1, *m_List1);
}


BEGIN_MESSAGE_MAP(CDRODefine, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DONE, OnButtonDone)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedListCtrl)
    ON_MESSAGE(WM_CALCRO, OnCalcSumme)
END_MESSAGE_MAP()


// CDRODefine-Meldungshandler

BOOL CDRODefine::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_List1->init();
    m_List1->SetExtendedStyle(m_List1->GetExtendedStyle() | LVS_EX_GRIDLINES);        // Grid
    m_pldisc.clear();
    ppString Typ;
    CString Text;
    CCSTDISCACC Discacc;        //Rabattkontosaetze
    COLORREF bg = RGB(200, 200, 0);
    COLORREF fg = RGB(0, 0, 0);
    ::buf_default((void*)&Discacc.s, CSTDISCACC_BES, CSTDISCACC_ANZ);
    BeginWaitCursor();
    for (;;)
    {
        char error_msg[81];
        int rc=::ServerNr(PIPE_AE_SRV, AasrvGetROMembers,(void*)&Discacc.s, CSTDISCACC_BES, CSTDISCACC_ANZ, error_msg);
        if (rc != 0)
            break;
        if (Discacc.GetBalance() == 0)
            continue;
        Discacc.GetVouchertyp(Typ);
        if (!strncmp(Typ, "GU", 2))
        {
            m_dGut += Discacc.GetBalance();
        }
        else
        {
            m_pldisc.insert(m_pldisc.end(), Discacc.GetStruct());
        }
    }
    if (m_pldisc.empty())
    {
        CDialogMultiLang::OnCancel();
        return FALSE;
    }
    CLetterMan kb;
    for (m_itdisc = m_pldisc.begin(); m_itdisc < m_pldisc.end(); m_itdisc++)
    {
        int index = m_List1->GetItemCount();
        if (m_List1->InsertItem(index, "") == -1)
        {
            return TRUE;
        }
        m_List1->SetCheck(index, TRUE);
        Text.Format("%d", m_itdisc->PRIORITY);
        m_List1->SetItemText(index, RO_LC_COL_BENUTZEN, kb.Next());
        m_List1->SetItemText(index, RO_LC_COL_PRIORITAET, Text);
        m_List1->SetItemText(index, RO_LC_COL_RECHNR, m_itdisc->INVOICENUMBER);
        Text = DDMMYYYYStringFromDateLong(m_itdisc->DATE);
        m_List1->SetItemText(index, RO_LC_COL_DATUM, Text);
        m_List1->SetItemText(index, RO_LC_COL_RECH_TYP, m_itdisc->VOUCHERTYP);
        Text.Format("%0.2lf",m_itdisc->INVOICEAMOUNT);
        m_List1->SetItemText(index, RO_LC_COL_WERT, Text);
        Text.Format("%0.2lf",m_itdisc->INVOICEPAID);
        m_List1->SetItemText(index, RO_LC_COL_BEZAHLT, Text);
        Text.Format("%0.2lf",m_itdisc->BALANCE);
        m_List1->SetItemText(index, RO_LC_COL_RABATT, Text);
        Text.Format("%d",m_itdisc->PAYMENTARGET);
        m_List1->SetItemText(index, RO_LC_COL_TAGE_ZAHLUNG, Text);
    }
    CString cSum;
    cSum.Format("%0.2lf", m_dGut);
    GetDlgItem(IDC_EDIT_GUT)->SetWindowText(cSum);
    m_bFertig = true;
    CalcSumme();

    m_List1->setColumnColor(RO_LC_COL_PRIORITAET, fg, bg);
    EndWaitCursor();

    CenterWindow(AeGetApp()->m_pViewEing);

    CListCtrlHelper::SetFocusSelectedFocused(*m_List1, 0);

    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

void CDRODefine::OnOK()
{
/*  int pos;
    int hilfe;
    pos = m_List1->GetNextItem(-1,LVNI_SELECTED);
    if ((hilfe = atoi(m_List1->GetItemText(pos, RO_LC_COL_PRIORITAET))) > 1)
    {
        MsgBoxOK(AETXT_0_UND_1);
        m_List1->SetItemText(pos, RO_LC_COL_PRIORITAET, "1");
        return;
    }
    if (pos < m_List1->GetItemCount() -1)
    {
        CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, pos+1);
        return;
    }
    OnButtonDone(); */
}

void CDRODefine::OnButtonDone()
{
    int pos = 0;
    char error_msg[81];
    CCSTDISCACC Discacc;        //Rabattkontosaetze
    ::buf_default((void*)&Discacc.s, CSTDISCACC_BES, CSTDISCACC_ANZ);
    for (m_itdisc = m_pldisc.begin(); m_itdisc < m_pldisc.end(); m_itdisc++, pos++)
    {
        if (!m_List1->GetCheck(pos) ||
            (atoi(m_List1->GetItemText(pos, RO_LC_COL_PRIORITAET)) != m_itdisc->PRIORITY))
        {
            Discacc.SetStruct(m_pldisc.at(pos));
            if (m_List1->GetCheck(pos))
            {
                Discacc.SetUpd_flag('1');
            }
            else
            {
                Discacc.SetUpd_flag('0');
            }
            Discacc.SetPriority(static_cast<short>(atoi(m_List1->GetItemText(pos, RO_LC_COL_PRIORITAET))));
            ::ServerNr(PIPE_AE_SRV, AasrvChangeROMembers, (void*)&Discacc.s, CSTDISCACC_BES, CSTDISCACC_ANZ, error_msg);
        }
    }
    CDialogMultiLang::OnOK();
}

void CDRODefine::CalcSumme()
{
    int actpos = m_List1->GetNextItem(-1, LVNI_SELECTED);
    m_dSumme = 0.0;
    for (int pos = 0; pos < m_List1->GetItemCount(); pos++)
    {
        if (m_List1->GetCheck(pos))
        {
            m_dSumme += atof(m_List1->GetItemText(pos, RO_LC_COL_RABATT));
        }
    }
    m_dSumme -= m_dGut;
    CString cSum;
    cSum.Format("%0.2lf", m_dSumme);
    GetDlgItem(IDC_EDIT_SUMME)->SetWindowText(cSum);

    CListCtrlHelper::SetFocusSelectedFocused(*m_List1, actpos);
    m_List1->setEdit(actpos, RO_LC_COL_BENUTZEN);
}

void CDRODefine::OnItemchangedListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
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
                if (m_bFertig) this->PostMessage(WM_CALCRO, 0, 0);
            }

            break;

            case 0x0002:    // check
            {
                CListCtrlHelper::SetItemStateSelectedFocused(*m_List1, pNMLV->iItem);
                if (m_bFertig) this->PostMessage(WM_CALCRO, 0, 0);
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

LRESULT CDRODefine::OnCalcSumme(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    if (m_bFertig)
        CalcSumme();
    return 0L;
}
