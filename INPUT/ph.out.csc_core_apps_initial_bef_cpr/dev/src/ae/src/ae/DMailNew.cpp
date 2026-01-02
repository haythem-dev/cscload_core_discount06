// DMailNew.cpp : implementation file
//

#include "stdafx.h"
#include <mailsystem.h>
#include "DMailNew.h"

/////////////////////////////////////////////////////////////////////////////
// CDMailNew dialog


CDMailNew::CDMailNew(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDMailNew::IDD, pParent)
{
    m_CDatum = _T("");
    m_CText = _T("");
    m_CZeit = _T("");
}


void CDMailNew::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADIO_TIP, m_CBTip);
    DDX_Control(pDX, IDC_EDIT_ZEIT, m_Edit_Zeit);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_Edit_Text);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_Edit_Datum);
    DDX_Control(pDX, IDC_COMBO_GRUPPE, m_Combo_Group);
    DDX_Text(pDX, IDC_EDIT_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_CText);
    DDX_Text(pDX, IDC_EDIT_ZEIT, m_CZeit);
}


BEGIN_MESSAGE_MAP(CDMailNew, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
    ON_EN_CHANGE(IDC_EDIT_ZEIT, OnChangeEditZeit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMailNew message handlers

void CDMailNew::OnChangeEditDatum()
{
    AllgDatumKontr(&m_Edit_Datum,ALGF_FORM_DATUM_TTMMJJ);
}

void CDMailNew::OnChangeEditText()
{
    AllgLaengeKontr(&m_Edit_Text, 240,AeGetApp()->Modus());
}

void CDMailNew::OnChangeEditZeit()
{
    AllgWertKontr(&m_Edit_Zeit, MAXIMUM_END_ZEIT);
}

void CDMailNew::OnOK()
{
    long datum;
    long groupno;
    long newsno;
    int id;         //ID of the checked radio button

    UpdateData();
    if (m_CText.IsEmpty())
    {
        MsgBoxOK(IDP_MAIL_TEXT);
        m_Edit_Text.SetFocus();
        m_Edit_Text.SetSel(0, -1, FALSE);
        return;
    }
    if ((datum = AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ)) < 0)
    {
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
        return;
    }
    if (zeit.s.DATUM > datum)
    {
        MsgBoxOK(IDP_MAIL_IN_PAST);
        m_Edit_Datum.SetFocus();
        m_Edit_Datum.SetSel(0, -1, FALSE);
        return;
    }
    else if (zeit.s.DATUM == datum && zeit.s.ZEIT > atol(m_CZeit))
    {
        MsgBoxOK(IDP_MAIL_IN_PAST);
        m_Edit_Zeit.SetFocus();
        m_Edit_Zeit.SetSel(0, -1, FALSE);
        return;
    }
    groupno = m_pl.at(m_Combo_Group.GetCurSel()).No;
    CMAILUSERS user;
    CMAILITEMS items;
    CMAILMESSAGE message;

    //Prioritaet bestimmen
    id = GetCheckedRadioButton(IDC_RADIO_TIP, IDC_RADIO_WARNUNG);
    switch (id)
    {
    case IDC_RADIO_TIP:
        message.SetPriority(0);
        break;
    case IDC_RADIO_INFO:
        message.SetPriority(1);
        break;
    case IDC_RADIO_HINWEIS:
        message.SetPriority(2);
        break;
    case IDC_RADIO_WICHTIG:
        message.SetPriority(3);
        break;
    default:
        message.SetPriority(4);
        break;
    }
    message.SetMessage(m_CText);
    message.SetTm_date(datum);
    message.SetTm_time(atol(m_CZeit) * 100);
    message.SetUid(GetAeUser().GetUID());
    message.SetFilialnr((GetAeUser().GetUser()).FILIALNR);
    message.Insert();
    newsno = message.GetNewsno();
    user.SetGroupno(groupno);
    for (;;)
    {
        if (user.SelAll() != 0)
            break;
        items.SetFilialnr(user.GetFilialnr());
        items.SetUid(user.GetUid());
        items.SetNewsno(newsno);
        items.Insert();
    }
    user.CloseCursor();

    CDialogMultiLang::OnOK();
}

BOOL CDMailNew::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CMAILGROUP mailGroup;
    struct gruppe group;
    m_pl.clear();
    BeginWaitCursor();
    for (;;)
    {
        mailGroup.SelMailGroup();
        if (mailGroup.rc == SRV_SQLNOTFOUND)
        {
            mailGroup.CloseCursor();
            break;
        }
        group.No = mailGroup.GetGroupno();
        mailGroup.GetGroupname(group.Name);
        m_pl.insert(m_pl.end(), group);
        m_Combo_Group.AddString(group.Name.c_str());
    }
    m_Combo_Group.SetCurSel(0);

    zeit.Server(AafilGetdatetime);
    m_CDatum = DDMMYYYYStringNoDotsFromDateLong(zeit.s.DATUM);
    zeit.s.ZEIT = zeit.s.ZEIT / 100;
    m_CZeit.Format("%04ld", zeit.s.ZEIT);
    EndWaitCursor();
    CheckRadioButton(IDC_RADIO_TIP, IDC_RADIO_WARNUNG, IDC_RADIO_TIP);
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
