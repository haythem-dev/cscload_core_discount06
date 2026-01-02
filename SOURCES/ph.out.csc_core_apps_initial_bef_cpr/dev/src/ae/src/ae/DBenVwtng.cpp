// DBenVwtng.cpp : implementation file
//

#include "stdafx.h"
#include "DRechteAa.h"
#include "DBenVwtng.h"
#include "DKontrPwd.h"

/////////////////////////////////////////////////////////////////////////////
// CDBenVwtng dialog


CDBenVwtng::CDBenVwtng(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBenVwtng::IDD, pParent)
{
    m_CKennung = _T("");
}


void CDBenVwtng::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_KENNUNG, m_EditKennung);
    DDX_Text(pDX, IDC_KENNUNG, m_CKennung);
}


BEGIN_MESSAGE_MAP(CDBenVwtng, CDialogMultiLang)
    ON_BN_CLICKED(ID_BEN_LOESCH, OnBenLoesch)
    ON_BN_CLICKED(ID_BEN_NEU, OnBenNeu)
    ON_BN_CLICKED(ID_BEN_PWD, OnBenPwd)
    ON_BN_CLICKED(ID_RECHTE_AA, OnRechteAa)
    ON_EN_CHANGE(IDC_KENNUNG, OnChangeKennung)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBenVwtng message handlers

BOOL CDBenVwtng::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CAeUser& currentAeUser = GetAeUser(); //aktueller User
    CDKontrPwd dlgKontrPwd;
    CString CPwd = currentAeUser.GetPasswd();
    dlgKontrPwd.m_Pwd = CPwd;
    if (!currentAeUser.UpdUser() || dlgKontrPwd.DoModal() != IDOK)    //Kennungen stimmen überein
    {
        CDialogMultiLang::EndDialog(0);
        return TRUE;  // return TRUE  unless you set the focus to a control
    }

    GetDlgItem(ID_BEN_NEU)->EnableWindow(FALSE);
    GetDlgItem(ID_BEN_LOESCH)->EnableWindow(FALSE);
    GetDlgItem(ID_BEN_PWD)->EnableWindow(FALSE);
    GetDlgItem(ID_RECHTE_AA)->EnableWindow(FALSE);
    GetDlgItem(ID_RECHTE_EK)->EnableWindow(FALSE);
    GetDlgItem(ID_RECHTE_WE)->EnableWindow(FALSE);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDBenVwtng::OnBenLoesch()
{
    if (MsgBoxYesNo(IDP_SOLL_SPERR) == IDYES)
    {
        m_User.DeleteUserDB();
    }
}

void CDBenVwtng::OnBenNeu()
{
    if (m_User.NewUserDB(m_CKennung))
    {
        GetDlgItem(ID_BEN_NEU)->EnableWindow(FALSE);
        GetDlgItem(ID_BEN_LOESCH)->EnableWindow(TRUE);
        GetDlgItem(ID_BEN_PWD)->EnableWindow(FALSE);
        GetDlgItem(ID_RECHTE_AA)->EnableWindow(TRUE);
        GetDlgItem(ID_RECHTE_EK)->EnableWindow(FALSE);
        GetDlgItem(ID_RECHTE_WE)->EnableWindow(FALSE);
    }
}

void CDBenVwtng::OnBenPwd()
{
    if (MsgBoxYesNo(IDP_SOLL_INIT) == IDYES)
        m_User.InitPassword();
}

void CDBenVwtng::OnRechteAa()
{
   CDRechteAa dlgRechteAa;
   dlgRechteAa.m_User = m_User;
   if (dlgRechteAa.DoModal() == IDOK)
        m_User = dlgRechteAa.m_User;
}

void CDBenVwtng::OnOK()
{
    if (!UpdateData())
        return;
    if (m_User.InitUser(m_CKennung))
    {
        GetDlgItem(ID_BEN_NEU)->EnableWindow(FALSE);
        GetDlgItem(ID_BEN_LOESCH)->EnableWindow();
        GetDlgItem(ID_BEN_PWD)->EnableWindow();
        GetDlgItem(ID_RECHTE_AA)->EnableWindow();
    }
    else
    {
        GetDlgItem(ID_BEN_NEU)->EnableWindow();
        GetDlgItem(ID_BEN_LOESCH)->EnableWindow(FALSE);
        GetDlgItem(ID_BEN_PWD)->EnableWindow(FALSE);
        GetDlgItem(ID_RECHTE_AA)->EnableWindow(FALSE);
    }
    m_User.SetUIDAnlage(GetAeUser().GetUID());
}

void CDBenVwtng::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDBenVwtng::OnChangeKennung()
{
    AllgLaengeKontr(&m_EditKennung, L_AEPWD_PASSWORD,AeGetApp()->Modus());
}
