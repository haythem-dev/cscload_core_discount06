// DTourUpd.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DTourUpd.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDTourUpd


CDTourUpd::CDTourUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTourUpd::IDD, pParent)
{
    m_csBemerkung = _T("");
    m_csFolge = _T("");
    m_csTour = _T("");
    m_csZeit = _T("");
}


void CDTourUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_KA, m_Combo_KA);
    DDX_Text(pDX, IDC_STATIC_BEMERKUNG, m_csBemerkung);
    DDX_Text(pDX, IDC_STATIC_FOLGE, m_csFolge);
    DDX_Text(pDX, IDC_STATIC_ID, m_csTour);
    DDX_Text(pDX, IDC_STATIC_ZEIT, m_csZeit);
}


BEGIN_MESSAGE_MAP(CDTourUpd, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDTourUpd

BOOL CDTourUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CPARKOART parkoart;
    CString text;
//   keine Vorgabe;0 normal;1 Disposition;2 keine Kommi;3 Eil-Beipack;4 Eil-Extra;5 Sonder-Kommi;6 Sonder-Kommi (Eil-Beipack);
    m_Combo_KA.ResetContent();
    m_Combo_KA.AddString(CResString::ex().getStrTblText(AETXT_KEINE_VORGABE));
    parkoart.s.BRANCHNO = m_sVz;
    BeginWaitCursor();
    for (;;)
    {
        parkoart.s.FETCH_REL  = 1;             //normaler Fetch
        parkoart.Server(AafilSelkoart);
        if (parkoart.rc == SRV_SQLNOTFOUND)
        {
            parkoart.s.FETCH_REL = 0;          //close Cursor
            parkoart.Server(AafilSelkoart);
            break;
        }
        AllgEntfSpaces(parkoart.s.BEZEICHNUNG);
        text.Format("%1.1s %s", parkoart.s.KOART, parkoart.s.BEZEICHNUNG);
        m_Combo_KA.AddString(text);
    } //Ende der for()-Schleife
    EndWaitCursor();
    m_Combo_KA.SetCurSel(m_sKA);
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDTourUpd::OnOK()
{
    CString KA;
    m_Combo_KA.GetLBText(m_Combo_KA.GetCurSel(),KA);
    KA = KA.Left(1);
    m_sKA = (KA == " ") ? 0 : static_cast<short>(atoi(KA) + 1);

    CDialogMultiLang::OnOK();
}
