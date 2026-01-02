// DCallbackWork.cpp : implementation file
//

#include "stdafx.h"
#include "DCallbackWork.h"
#include <callback.h>

/////////////////////////////////////////////////////////////////////////////
// CDCallbackWork dialog


CDCallbackWork::CDCallbackWork(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCallbackWork::IDD, pParent)
{
    m_CBis = _T("");
    m_CVon = _T("");
    m_CTag = _T("");
    m_CPartner = _T("");
    m_Tag = "Montag";
}


void CDCallbackWork::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_UPD, m_CBUpd);
    DDX_Control(pDX, IDC_BUTTON_NEW, m_CBNew);
    DDX_Control(pDX, IDC_BUTTON_DEL, m_CBDel);
    DDX_Control(pDX, IDC_COMBO_TAG, m_ComboTag);
    DDX_Control(pDX, IDC_EDIT_VON, m_EditVon);
    DDX_Control(pDX, IDC_EDIT_BIS, m_EditBis);
    DDX_Text(pDX, IDC_EDIT_BIS, m_CBis);
    DDX_Text(pDX, IDC_EDIT_VON, m_CVon);
    DDX_CBString(pDX, IDC_COMBO_TAG, m_CTag);
    DDX_Text(pDX, IDC_STATIC_PARTNER, m_CPartner);
}


BEGIN_MESSAGE_MAP(CDCallbackWork, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BIS, OnChangeEditBis)
    ON_EN_CHANGE(IDC_EDIT_VON, OnChangeEditVon)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCallbackWork message handlers

void CDCallbackWork::OnChangeEditBis()
{
    AllgWertKontr(&m_EditBis, MAXIMUM_END_ZEIT);
}

void CDCallbackWork::OnChangeEditVon()
{
    AllgWertKontr(&m_EditVon, MAXIMUM_END_ZEIT);
}

void CDCallbackWork::OnButtonDel()
{
    UpdateData();
    CCALLBACKTIME callbacktime;
    callbacktime.SetOfficeday(static_cast<short>(m_ComboTag.GetCurSel()) );
    callbacktime.SetBegintime(static_cast<short>(atoi(m_CVon)) );
    callbacktime.SetEndtime(static_cast<short>(atoi(m_CBis)) );
    callbacktime.SetCallbackpartno(m_lPartnerNo);
    callbacktime.DeleteCallbackTime();
    CDialogMultiLang::OnOK();
}

void CDCallbackWork::OnButtonNew()
{
    long std;
    long min;
    UpdateData();
    if (((std = atol(m_CVon) / 100) > 23) || ((min = atol(m_CVon) % 100) > 59))
    {
        MsgBoxOK(IDP_RR_ZEIT_FEHL);
        GetDlgItem(IDC_EDIT_VON)->SetFocus();
        return;
    }
    if (((std = atol(m_CBis) / 100) > 23) || ((min = atol(m_CBis) % 100) > 59))
    {
        MsgBoxOK(IDP_RR_ZEIT_FEHL);
        GetDlgItem(IDC_EDIT_BIS)->SetFocus();
        return;
    }
    if (atol(m_CVon) >= atol(m_CBis))
    {
        MsgBoxOK(IDP_RR_ZEIT_FEHL);
        GetDlgItem(IDC_EDIT_BIS)->SetFocus();
        return;
    }
    CCALLBACKTIME callbacktime;
    callbacktime.SetOfficeday(static_cast<short>(m_ComboTag.GetCurSel()));
    callbacktime.SetBegintime(static_cast<short>(atoi(m_CVon)));
    callbacktime.SetEndtime(static_cast<short>(atoi(m_CBis)));
    callbacktime.SetCallbackpartno(m_lPartnerNo);
    callbacktime.Insert();
    CDialogMultiLang::OnOK();
}

void CDCallbackWork::OnButtonUpd()
{
    UpdateData();
    long std;
    long min;
    if (((std = atol(m_CBis) / 100) > 23) || ((min = atol(m_CBis) % 100) > 59))
    {
        MsgBoxOK(IDP_RR_ZEIT_FEHL);
        GetDlgItem(IDC_EDIT_BIS)->SetFocus();
        return;
    }
    if (atol(m_CVon) >= atol(m_CBis))
    {
        MsgBoxOK(IDP_RR_ZEIT_FEHL);
        GetDlgItem(IDC_EDIT_BIS)->SetFocus();
        return;
    }
    CCALLBACKTIME callbacktime;
    callbacktime.SetOfficeday(static_cast<short>(m_ComboTag.GetCurSel()));
    callbacktime.SetBegintime(m_lVon);
    callbacktime.SetCallbackpartno(m_lPartnerNo);
    callbacktime.DeleteCallbackTime();
    callbacktime.SetEndtime(static_cast<short>(atoi(m_CBis)));
    callbacktime.SetBegintime(static_cast<short>(atoi(m_CVon)));
    callbacktime.Insert();
    CDialogMultiLang::OnOK();
}

BOOL CDCallbackWork::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    if (m_new)
    {
        m_CBUpd.ShowWindow(SW_HIDE);
        m_CBDel.ShowWindow(SW_HIDE);
    }
    else
    {
        m_CBNew.ShowWindow(SW_HIDE);
        m_ComboTag.EnableWindow(FALSE);
    }
    m_ComboTag.ResetContent();
    m_ComboTag.AddString(CResString::ex().getStrTblText(IDS_SUNDAY));
    m_ComboTag.AddString(CResString::ex().getStrTblText(IDS_MONDAY));
    m_ComboTag.AddString(CResString::ex().getStrTblText(IDS_TUESDAY));
    m_ComboTag.AddString(CResString::ex().getStrTblText(IDS_WEDNESDAY));
    m_ComboTag.AddString(CResString::ex().getStrTblText(IDS_THURSDAY));
    m_ComboTag.AddString(CResString::ex().getStrTblText(IDS_FRIDAY));
    m_ComboTag.AddString(CResString::ex().getStrTblText(IDS_SATURDAY));

    SetTag();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCallbackWork::SetTag()
{
    m_ComboTag.SelectString(-1, m_Tag);
}
