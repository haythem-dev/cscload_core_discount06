// DReserve.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include <artsel.h>
#include "DArtDef.h"
#include "DReserve.h"

#define MAXIMUM_PROZENT     100


// CDReserve-Dialogfeld

IMPLEMENT_DYNAMIC(CDReserve, CDialog)
CDReserve::CDReserve(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDReserve::IDD, pParent)
    , m_CPZN(_T(""))
    , m_CEKG(_T(""))
    , m_CMax(_T(""))
    , m_CProzent(_T(""))
    , m_CBestand(_T(""))
    , m_CBestandAct(_T(""))
    , m_bBst(FALSE)
{
    m_Funktion = 0;
}

CDReserve::~CDReserve()
{
}

void CDReserve::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PZN, m_edit_PZN);
    DDX_Text(pDX, IDC_EDIT_PZN, m_CPZN);
    DDX_Control(pDX, IDC_EDIT_EKG, m_edit_EKG);
    DDX_Text(pDX, IDC_EDIT_EKG, m_CEKG);
    DDX_Control(pDX, IDC_EDIT_MAX, m_edit_Max);
    DDX_Text(pDX, IDC_EDIT_MAX, m_CMax);
    DDX_Control(pDX, IDC_EDIT_PCT, m_edit_Prozent);
    DDX_Text(pDX, IDC_EDIT_PCT, m_CProzent);
    DDX_Control(pDX, IDC_EDIT_BESTAND, m_edit_Bestand);
    DDX_Text(pDX, IDC_EDIT_BESTAND, m_CBestand);
    DDX_Control(pDX, IDC_CHECK_BST, m_CB_Bst);
    DDX_Check(pDX, IDC_CHECK_BST, m_bBst);
    DDX_Text(pDX, IDC_EDIT_BESTAND_ACT, m_CBestandAct);
}


BEGIN_MESSAGE_MAP(CDReserve, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_INS, OnBnClickedButtonIns)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnBnClickedButtonUpd)
    ON_BN_CLICKED(IDC_BUTTON_PZN, OnBnClickedButtonPzn)
    ON_EN_CHANGE(IDC_EDIT_PZN, OnEnChangeEditPzn)
    ON_EN_CHANGE(IDC_EDIT_EKG, OnEnChangeEditEkg)
    ON_EN_CHANGE(IDC_EDIT_PCT, OnEnChangeEditPct)
END_MESSAGE_MAP()


// CDReserve-Meldungshandler

BOOL CDReserve::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_UPD)->EnableWindow(FALSE);
    CheckDlgButton(IDC_CHECK_BST,FALSE);
    GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_SHOW);
    if (m_Funktion == 0)
    {
        GetDlgItem(IDC_EDIT_BESTAND_ACT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_BESTAND_ACT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_BESTAND)->ShowWindow(SW_HIDE);
    }
    else
    {
        if (m_Funktion == 1)
        {
            this->SetWindowText(CResString::ex().getStrTblText(AETXT_RESERVE_ABS));
        }
        else if (m_Funktion == 3)
        {
            this->SetWindowText(CResString::ex().getStrTblText(AETXT_RESERVE_ZERT));
        }
        else if (m_Funktion == 4)
        {
            this->SetWindowText(CResString::ex().getStrTblText(AETXT_RESERVE_BPZ));
        }
        else
        {
            this->SetWindowText(CResString::ex().getStrTblText(AETXT_RESERVE_CHARGE));
        }
        GetDlgItem(IDC_EDIT_BESTAND)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_BESTAND)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_MAX)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_PCT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PCT)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_CHECK_BST)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_HIDE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDReserve::OnBnClickedOk()
{
    UpdateData();
    if (m_CPZN.IsEmpty())
    {
        MsgBoxOK(IDP_NO_PZN);
        m_edit_PZN.SetFocus();
        m_edit_PZN.SetSel(0, -1, FALSE);
        m_edit_PZN.SetSel(-1, 0, FALSE);      //Selektion aufheben
        return;
    }
    BeginWaitCursor();
    CARTAESEL code;
    strcpy(code.s.ARTICLE_CODE, m_CPZN);
    code.s.CODE_TYPE = 0;
    code.Server(AatartSel_NoByCode);
    if (code.rc != SRV_OK)
    {
        MsgBoxOK(AETXT_NO_ARTICLECODE);
        m_edit_PZN.SetFocus();
        EndWaitCursor();
        return;
    }
    EndWaitCursor();
    m_Reserve.SetBranchno(AeGetApp()->VzNr());
    m_Reserve.SetArticleno(code.s.ARTIKEL_NR);
    if (m_Funktion == 1)
    {
        m_Reserve.SetReservtype(2);
    }
    else if (m_Funktion == 3)
    {
        m_Reserve.SetReservtype(3);
    }
    else if (m_Funktion == 4)
    {
        m_Reserve.SetReservtype(4);
    }
    else if (m_Funktion == 5)
    {
        m_Reserve.SetReservtype(5);
    }
    else
    {
        m_Reserve.SetReservtype(0);
    }
    if (!m_Reserve.SelArt())
    {
        ppString csEKG;
        m_CEKG = m_Reserve.GetPharmacygroupid(csEKG);
        m_CMax.Format("%ld", m_Reserve.GetMaxqty());
        m_CProzent.Format("%d", m_Reserve.GetReservepct());
        m_CBestand.Format("%ld", m_Reserve.GetReservedqty());
        GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(TRUE);
        if (m_Funktion != 0)    //Bei prozentualer Reservierung kein Update, sondern delete und insert wegen automatischer Bestandsreservierung
        {
            GetDlgItem(IDC_BUTTON_UPD)->EnableWindow(TRUE);
        }
        GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_HIDE);
        if (m_Funktion == 1 || m_Funktion == 3 || m_Funktion == 4)
        {
            CARTINF best;
            best.s.ARTIKEL_NR = m_Reserve.GetArticleno();
            best.s.FILIALNR = AeGetApp()->VzNr();
            best.Server(AatartInf_art_nr);
            if (best.rc < SRV_OK)
                return;
            long lBestand = best.s.BESTAND + m_Reserve.GetReservedqty();
            m_CBestandAct.Format("%ld", lBestand);
        }
        UpdateData(FALSE);
    }
    else
    {
        MsgBoxOK(IDS_NO_ENTRY, MB_ICONINFORMATION);
    }
}

void CDReserve::OnBnClickedButtonIns()
{
    UpdateData();
    if (m_CPZN.IsEmpty())
    {
        MsgBoxOK(IDP_NO_PZN);
        m_edit_PZN.SetFocus();
        m_edit_PZN.SetSel(0, -1, FALSE);
        m_edit_PZN.SetSel(-1, 0, FALSE);        //Selektion aufheben
        return;
    }
    if (m_CEKG.IsEmpty())
    {
        MsgBoxOK(AETXT_MUSS_EKG);
        m_edit_EKG.SetFocus();
        m_edit_EKG.SetSel(0, -1, FALSE);
        m_edit_EKG.SetSel(-1, 0, FALSE);        //Selektion aufheben
        return;
    }
    if (m_Funktion == 0)
    {
        if (m_CProzent.IsEmpty())
        {
            MsgBoxOK(AETXT_MUSS_PROZENT);
            m_edit_Prozent.SetFocus();
            m_edit_Prozent.SetSel(0, -1, FALSE);
            m_edit_Prozent.SetSel(-1, 0, FALSE);    //Selektion aufheben
            return;
        }
    }
    else
    {
        if (m_CBestand.IsEmpty())
        {
            MsgBoxOK(AETXT_MUSS_MENGE);
            m_edit_Bestand.SetFocus();
            m_edit_Bestand.SetSel(0, -1, FALSE);
            m_edit_Bestand.SetSel(-1, 0, FALSE);    //Selektion aufheben
            return;
        }
    }
    m_Reserve.SetBranchno(AeGetApp()->VzNr());
    BeginWaitCursor();
    CARTAESEL code;
    strcpy(code.s.ARTICLE_CODE, m_CPZN);
    code.s.CODE_TYPE = 0;
    code.Server(AatartSel_NoByCode);
    if (code.rc != SRV_OK)
    {
        MsgBoxOK(AETXT_NO_ARTICLECODE);
        m_edit_PZN.SetFocus();
        EndWaitCursor();
        return;
    }
    EndWaitCursor();
    m_Reserve.SetArticleno(code.s.ARTIKEL_NR);
    m_Reserve.SetPharmacygroupid(m_CEKG);
    if (m_Funktion == 0)
    {
        m_Reserve.SetReservtype(0);
        m_Reserve.SetMaxqty(atol(m_CMax));
        m_Reserve.SetReservepct(static_cast<short>(atoi(m_CProzent)));
        if (IsDlgButtonChecked(IDC_CHECK_BST))
        {
            if (!m_Reserve.InsertBestand())
            {
                GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(TRUE);
                GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
                GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_HIDE);
                MsgBoxOK(IDP_INSERTED, MB_ICONINFORMATION);
            }
        }
        else
        {
            if (!m_Reserve.Insert())
            {
                GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(TRUE);
                GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
                GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_HIDE);
                MsgBoxOK(IDP_INSERTED, MB_ICONINFORMATION);
            }
        }
    }
    else
    {
        m_Reserve.SetMaxqty(0);
        m_Reserve.SetReservepct(0);
        m_Reserve.SetReservedqty(atol(m_CBestand));
        if (m_Funktion == 1)
        {
            m_Reserve.SetReservtype(2);
        }
        else if (m_Funktion == 3)
        {
            m_Reserve.SetReservtype(3);
        }
        else if (m_Funktion == 4)
        {
            m_Reserve.SetReservtype(4);
        }
        else
        {
            m_Reserve.SetReservtype(5);
        }
        if (!m_Reserve.ReservStockAbs())
        {
            GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_UPD)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
            GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_HIDE);
            MsgBoxOK(IDP_INSERTED, MB_ICONINFORMATION);
        }
    }
}

void CDReserve::OnBnClickedButtonDel()
{
    UpdateData();
    m_Reserve.SetBranchno(AeGetApp()->VzNr());
    if (m_Funktion == 1)
    {
        m_Reserve.SetReservtype(2);
    }
    else if (m_Funktion == 3)
    {
        m_Reserve.SetReservtype(3);
    }
    else if (m_Funktion == 4)
    {
        m_Reserve.SetReservtype(4);
    }
    else if (m_Funktion == 5)
    {
        m_Reserve.SetReservtype(5);
    }
    else
    {
        m_Reserve.SetReservtype(0);
    }
    if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
    {
        BeginWaitCursor();
        CARTAESEL code;
        strcpy(code.s.ARTICLE_CODE,m_CPZN);
        code.s.CODE_TYPE = 0;
        code.Server(AatartSel_NoByCode);
        if (code.rc != SRV_OK)
        {
            MsgBoxOK(AETXT_NO_ARTICLECODE);
            m_edit_PZN.SetFocus();
            EndWaitCursor();
            return;
        }
        EndWaitCursor();
        m_Reserve.SetArticleno(code.s.ARTIKEL_NR);
        if (!m_Reserve.Delete())
        {
            GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_UPD)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_INS)->EnableWindow(TRUE);
            GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_SHOW);
            MsgBoxOK(IDP_DELETED, MB_ICONINFORMATION);
        }
    }
}

void CDReserve::OnBnClickedButtonUpd()
{
    UpdateData();
    m_Reserve.SetPharmacygroupid(m_CEKG);
    if (m_Funktion == 0)
    {
        m_Reserve.SetMaxqty(atol(m_CMax));
        m_Reserve.SetReservepct(static_cast<short>(atoi(m_CProzent)));
        m_Reserve.SetReservtype(0);
        if (!m_Reserve.Update())
        {
            MsgBoxOK(IDS_SET_CHANGED, MB_ICONINFORMATION);
            GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
            GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_HIDE);
        }
    }
    else
    {
        m_Reserve.SetMaxqty(0);
        m_Reserve.SetReservepct(0);
        m_Reserve.SetReservedqty(atol(m_CBestand));
        if (m_Funktion == 1)
        {
            m_Reserve.SetReservtype(2);
        }
        else if (m_Funktion == 3)
        {
            m_Reserve.SetReservtype(3);
        }
        else if (m_Funktion == 4)
        {
            m_Reserve.SetReservtype(4);
        }
        else
        {
            m_Reserve.SetReservtype(5);
        }
        if (!m_Reserve.ReservStockAbs())
        {
            GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_UPD)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_INS)->EnableWindow(FALSE);
            GetDlgItem(IDC_CHECK_BST)->ShowWindow(SW_HIDE);
            MsgBoxOK(IDS_SET_CHANGED, MB_ICONINFORMATION);
            m_CBestand.Format("%ld", m_Reserve.GetReservedqty());
            CARTINF best;
            best.s.ARTIKEL_NR = m_Reserve.GetArticleno();
            best.s.FILIALNR = AeGetApp()->VzNr();
            best.Server(AatartInf_art_nr);
            if (best.rc < SRV_OK)
                return;
            long lBestand = best.s.BESTAND + m_Reserve.GetReservedqty();
            m_CBestandAct.Format("%ld", lBestand);
            UpdateData(FALSE);
        }
    }
}

void CDReserve::OnBnClickedButtonPzn()
{
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() != IDOK)
        return;
    m_CPZN.Format("%ld", dlgArtDef.GetArtNr());
    GetDlgItem(IDC_EDIT_PZN)->SetWindowText(dlgArtDef.GetArticleCode());
    m_edit_PZN.SetFocus();
    m_edit_PZN.SetSel(0, -1, FALSE);
    m_edit_PZN.SetSel(-1, 0, FALSE);      //Selektion aufheben
}

void CDReserve::OnEnChangeEditPzn()
{
    GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_UPD)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_INS)->EnableWindow(TRUE);
}

void CDReserve::OnEnChangeEditEkg()
{
    AllgLaengeKontr(&m_edit_EKG, L_ARTIKELRESERVE_PHARMACYGROUPID, AeGetApp()->Modus());
}

void CDReserve::OnEnChangeEditPct()
{
    AllgWertKontr(&m_edit_Prozent, MAXIMUM_PROZENT);
}
