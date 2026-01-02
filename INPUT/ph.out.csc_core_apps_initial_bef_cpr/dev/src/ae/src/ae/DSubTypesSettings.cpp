// DSubTypesSettings.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <orders.h>
#include "DSubTypesSettings.h"


// CDSubTypesSettingsUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDSubTypesSettingsUpd, CDialog)
CDSubTypesSettingsUpd::CDSubTypesSettingsUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSubTypesSettingsUpd::IDD, pParent)
    , m_bInsert(FALSE)
    , m_bAktiv(FALSE)
    , m_bMerge(FALSE)
    , m_csEndeZeit(_T(""))
    , m_csDuration(_T(""))
    , m_csOrigin(_T(""))
    , m_sBranchNo(0)
{
}

CDSubTypesSettingsUpd::~CDSubTypesSettingsUpd()
{
}

void CDSubTypesSettingsUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_ORIGIN, m_ComboOrigin);
    DDX_Check(pDX, IDC_CHECK_AKTIV, m_bAktiv);
    DDX_Check(pDX, IDC_CHECK_MERGE, m_bMerge);
    DDX_Text(pDX, IDC_EDIT_ENDEZEIT, m_csEndeZeit);
    DDX_Text(pDX, IDC_EDIT_DURATION, m_csDuration);
    DDX_Control(pDX, IDC_EDIT_ENDEZEIT, m_editEndeZeit);
    DDX_Control(pDX, IDC_EDIT_DURATION, m_editDuration);
}


BEGIN_MESSAGE_MAP(CDSubTypesSettingsUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_ENDEZEIT, OnEnChangeEditEndezeit)
    ON_EN_CHANGE(IDC_EDIT_DURATION, OnEnChangeEditDuration)
END_MESSAGE_MAP()


// CDSubTypesSettingsUpd-Meldungshandler

BOOL CDSubTypesSettingsUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    if (m_bInsert)
    {
        CString combotext;
        ppString device;
        CORIGINTYPESETTINGSPF settings;
        settings.SetBranchno(m_sBranchNo);
        bool bNotFound = TRUE;

        for (;;)
        {
            if (settings.SelListNotDefined() != SRV_OK)
            {
                break;
            }

            bNotFound = FALSE;
            combotext.Format("%d %s", settings.GetOrigintype(), settings.GetOrigindevice(device));
            m_ComboOrigin.AddString(combotext);
        }

        if (bNotFound)
        {
            MsgBoxOK( AETXT_NOMORE_ENTRIES );
            CDialogMultiLang::OnCancel();
            return TRUE;
        }
    }
    else
    {
        m_ComboOrigin.AddString(m_csOrigin);
    }

    m_ComboOrigin.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSubTypesSettingsUpd::OnOK()
{
    UpdateData();
    CString origin;
    CORIGINTYPESETTINGSPF settings;
    settings.SetBranchno(m_sBranchNo);
    settings.SetEndofordercons(atol(m_csEndeZeit));
    settings.SetOrderconsduration(atol(m_csDuration));

    if (m_bMerge)
    {
        settings.SetIsorderconsolidation(1);
    }
    else
    {
        settings.SetIsorderconsolidation(0);
    }

    if (m_bAktiv)
    {
        settings.SetSettingactivated(1);
    }
    else
    {
        settings.SetSettingactivated(0);
    }

    m_ComboOrigin.GetLBText(m_ComboOrigin.GetCurSel(), origin);
    settings.SetOrigintype( static_cast<short>(atoi(origin)) );

    if (m_bInsert)
    {
        settings.Insert();
    }
    else
    {
        settings.Update();
    }

    CDialogMultiLang::OnOK();
}

void CDSubTypesSettingsUpd::OnEnChangeEditEndezeit()
{
    AllgWertKontr(&m_editEndeZeit, MAXIMUM_END_ZEIT);
}

void CDSubTypesSettingsUpd::OnEnChangeEditDuration()
{
    AllgWertKontr(&m_editDuration, MAXIMUM_ZUSAMMENZEIT);
}
