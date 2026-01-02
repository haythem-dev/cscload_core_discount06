// DVerbBestaet.cpp : implementation file
//

#include "stdafx.h"
#include "DVerbBestaet.h"

/////////////////////////////////////////////////////////////////////////////
// CDVerbBestaet dialog


CDVerbBestaet::CDVerbBestaet(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDVerbBestaet::IDD, pParent)
    , m_CArtCode(_T(""))
{
    m_CDarreichform = _T("");
    m_CArtEinh = _T("");
    m_CArtName = _T("");
    m_CArtNr = _T("");
    m_CBestMenge = _T("");
    m_CBestand = _T("");
    m_VerbundZeitenKnd = _T("");
    m_VerbMenge           = 0;
    m_VerbFiliale         = 0;
    m_iCount              = 0;
    m_bIsActive     = true;
    m_List1 = new CIBTListCtrl;
    assert(m_List1);
}

CDVerbBestaet::~CDVerbBestaet()
{
    delete m_List1;
    m_List1 = 0;
}

void CDVerbBestaet::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_VERB_FILIALE, m_ComboVerbund);
    DDX_Text(pDX, IDC_ART_DARR, m_CDarreichform);
    DDX_Text(pDX, IDC_ART_EINH, m_CArtEinh);
    DDX_Text(pDX, IDC_ART_NAME, m_CArtName);
    DDX_Text(pDX, IDC_ART_NR, m_CArtNr);
    DDX_Text(pDX, IDC_BEST_MENGE, m_CBestMenge);
    DDX_Text(pDX, IDC_BESTAND, m_CBestand);
    DDX_Text(pDX, IDC_STATIC_VERB_ZEIT, m_VerbundZeitenKnd);
    DDX_Text(pDX, IDC_ART_CODE, m_CArtCode);
    DDX_Control(pDX, IDC_LIST1, *m_List1);
}


BEGIN_MESSAGE_MAP(CDVerbBestaet, CDialogMultiLang)
    ON_BN_CLICKED(ID_VERBUND, OnVerbund)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDVerbBestaet message handlers

BOOL CDVerbBestaet::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CAUFALTLAGORT aufaltlagort;
    CString cstr;
    int pos = 0;
    m_iCount = 0;
    m_ComboVerbund.Clear();
    m_List1->init();

    aufaltlagort.s.ARTIKEL_NR = atol (m_CArtNr);

    if (AeGetApp()->IsNLevelIBTCst())
    {
        CString Text;

        DWORD dwOldBits = m_List1->GetExtendedStyle();
        dwOldBits |= LVS_EX_FULLROWSELECT;
        m_List1->SetExtendedStyle(dwOldBits);
        GetDlgItem(IDC_STATIC_VB)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_VB)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_VERB_FILIALE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_VERB_FILIALE)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_LISTE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_LISTE)->EnableWindow(TRUE);
        GetDlgItem(IDC_LIST1)->ShowWindow(SW_SHOW);
        //GetDlgItem(IDC_LIST1)->EnableWindow(TRUE);
        m_List1->DeleteAllItems();
        for (;;)
        {
            aufaltlagort.Server(AasrvGetVerbMoegl);
            if (aufaltlagort.rc != SRV_OK)
                break;
            else if (aufaltlagort.s.FILIALNR == m_VerbFiliale)
                pos = m_iCount;
            int index = m_List1->GetItemCount();
            m_List1->InsertItem(index, "");
            AeGetApp()->GetBranchName(aufaltlagort.s.FILIALNR, Text);
            m_List1->SetItemText(index, COL_IBT_BRANCHNAME, Text);
            Text.Format("%d", aufaltlagort.s.FILIALNR);
            m_List1->SetItemText(index, COL_IBT_FILI, Text);
            Text.Format("%d", aufaltlagort.s.BESTAND);
            m_List1->SetItemText(index, COL_IBT_BESTAND, Text);
            AllgEntfSpaces(aufaltlagort.s.IBTTYPENAME);
            m_List1->SetItemText(index, COL_IBT_TYPE, aufaltlagort.s.IBTTYPENAME);
            Text = DDMMYYYYStringFromDateLong(aufaltlagort.s.DELIVERYDATEIBT);
            m_List1->SetItemText(index, COL_IBT_DATUM, Text);
            Text.Format("%d:%02d", aufaltlagort.s.DELIVERYTIMEIBT / 100, aufaltlagort.s.DELIVERYTIMEIBT % 100);
            m_List1->SetItemText(index, COL_IBT_ZEIT, Text);
            ++m_iCount;
        }
        if (m_iCount == 0)
        {
            OnCancel();
            return TRUE;
        }

        if ((atol(m_List1->GetItemText(pos, COL_IBT_BESTAND)) + atol(m_CBestand)) < atol(m_CBestMenge))
        {
            m_List1->setItemColor(pos, RGB(0, 0, 0), RGB(255, 0, 0));
        }
        else
        {
            m_List1->setItemColor(pos, RGB(0, 0, 0), RGB(0, 255, 0));
        }
    }
    else
    {
        if (m_bIsActive)
        {
           m_vList.clear();
           for (;;)
           {
              aufaltlagort.Server(AasrvGetVerbMoegl);
              if (aufaltlagort.rc != SRV_OK)
                 break;
              else if (aufaltlagort.s.FILIALNR == m_VerbFiliale)
                 pos = m_iCount;
              cstr.Format("%d %ld", aufaltlagort.s.FILIALNR, aufaltlagort.s.BESTAND);
              m_ComboVerbund.AddString(cstr);
              m_vList.insert(m_vList.end(), cstr);
              ++m_iCount;
           }
        }
        else
        {
           vector<CString>::iterator iPtr = m_vList.begin();
           for (; iPtr != m_vList.end(); iPtr++)
           {
              if (atoi(*iPtr) == m_VerbFiliale)
              {
                 m_vList.erase(iPtr--);
                 continue;
              }
              m_ComboVerbund.AddString(*iPtr);
              ++m_iCount;
           }
        }

        if (m_iCount == 0)
        {
            OnCancel();
            return TRUE;
        }
        m_ComboVerbund.SetCurSel(pos);
        m_ComboVerbund.SetTopIndex(pos);
    }
    CenterWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDVerbBestaet::OnOK()
{
}

void CDVerbBestaet::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDVerbBestaet::OnVerbund()
{
    if (!AeGetApp()->IsNLevelIBTCst())
    {
        CString cstr;
        m_ComboVerbund.GetLBText(m_ComboVerbund.GetCurSel(), cstr);
        m_VerbFiliale = (short)atol(cstr);
    }
    CDialogMultiLang::OnOK();
}
