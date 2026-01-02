// DAttachPartner.cpp : implementation file
//

#include "stdafx.h"
#include "DAttachPartner.h"
#include <callback.h>

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     5

static COLUMNS_TYPES Columns[] =
{
    0,  "",     20,     LVCFMT_LEFT,
    1,  "",     200,    LVCFMT_LEFT,
    2,  "",     200,    LVCFMT_LEFT,
    3,  "",     0,      LVCFMT_LEFT,
    4,  "",     0,      LVCFMT_LEFT,
    -1, "",     0,      0
};


/////////////////////////////////////////////////////////////////////////////
// CDAttachPartner dialog


CDAttachPartner::CDAttachPartner(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAttachPartner::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_RRPARTNER);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_RUECKRUFGRUND);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    m_lStartNoCallback = 0;
    m_lEndNoCallback = 100;
}


void CDAttachPartner::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_VZ, m_CB_Vz);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_LIST2, m_List2);
}


BEGIN_MESSAGE_MAP(CDAttachPartner, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEF, OnButtonDef)
    ON_BN_CLICKED(IDC_BUTTON_UNDEF, OnButtonUndef)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
    ON_BN_CLICKED(IDC_CHECK_VZ, OnCheckVz)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAttachPartner message handlers

void CDAttachPartner::OnButtonDef()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        int index = m_List2.GetItemCount();

        if (m_List2.InsertItem(index, m_List1.GetItemText(pos, 0)) == -1)
        {
            EndWaitCursor();
            return;
        }

        for (int iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
        {
            m_List2.SetItemText(index, iSubItem, m_List1.GetItemText(pos, iSubItem));
        }

        m_List1.DeleteItem(pos);
    }

    GetDlgItem(IDC_BUTTON_UNDEF)->EnableWindow();
}

void CDAttachPartner::OnButtonUndef()
{
    int pos = m_List2.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        int index = m_List1.GetItemCount();

        if (m_List1.InsertItem(index, m_List2.GetItemText(pos, 0)) == -1)
        {
            EndWaitCursor();
            return;
        }

        for (int iSubItem = 1; iSubItem < NUM_COLUMNS; iSubItem++)
        {
            m_List1.SetItemText(index, iSubItem, m_List2.GetItemText(pos, iSubItem));
        }

        m_List2.DeleteItem(pos);
    }

    GetDlgItem(IDC_BUTTON_DEF)->EnableWindow();
}

BOOL CDAttachPartner::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    DWORD dwOldBits;

    // Add the columns to List1.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List1.SetExtendedStyle(dwOldBits);

    // Add the columns to List2.
    if (!CListCtrlHelper::AddColumns(Columns, m_List2))
    {
        return FALSE;
    }

    dwOldBits = m_List2.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List2.SetExtendedStyle(dwOldBits);

    m_lUid = GetAeUser().GetUID();
    m_lStartNoCallback = AeGetApp()->StartNoCallback();
    m_lEndNoCallback = m_lStartNoCallback + 100;

    if (AeGetApp()->IsKundeHome())
    {
        m_CB_Vz.SetCheck(TRUE);

    }

    if (!GetAeUser().IsMehrVz())
    {
        AeGetApp()->IsKundeHome = true;
        m_CB_Vz.SetCheck(TRUE);
        m_CB_Vz.EnableWindow(FALSE);
    }

    FillList();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAttachPartner::OnOK()
{
    CCALLBACKATTACH attach;
    CString Listname;
    CString Listtext;
    int i;
    attach.SetUid(m_lUid);
    attach.SetRegionnr(AeGetApp()->VzNr());
    attach.SetVertriebszentrumnr(AeGetApp()->VzNr());
    attach.SetFilialnr(AeGetApp()->VzNr());
    BeginWaitCursor();

    for (;;)
    {
        if (AeGetApp()->IsKundeHome())
        {
            attach.SelVz();
        }
        else
        {
            attach.Sel();
        }

        if (attach.rc == SRV_SQLNOTFOUND)
        {
            attach.CloseCursor();
            break;
        }

        if (attach.GetCallbackpartno() > m_lStartNoCallback && attach.GetCallbackpartno() < m_lEndNoCallback) //nicht mehr gültige Einträge erhalten, dass vorhandene Rückrufe noch bearbeitet werden können
        {
            attach.Delete();
        }
    }

    for (i = 0; i < m_List2.GetItemCount(); i++)
    {
        attach.SetUid(m_lUid);
        attach.SetVertriebszentrumnr(static_cast<short>(atoi(m_List2.GetItemText(i, 0))));
        attach.SetCallbackpartno(atoi(m_List2.GetItemText(i, 3)));
        attach.SetFilialnr(AeGetApp()->VzNr());
        attach.SetReasonno(static_cast<short>(atoi(m_List2.GetItemText(i, 4))));
        attach.Insert();
    }

    CDialogMultiLang::OnOK();
}

void CDAttachPartner::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDAttachPartner::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDAttachPartner::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonDef();
    *pResult = 0L;
}

void CDAttachPartner::OnDblclkList2(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonUndef();
    *pResult = 0L;
}

void CDAttachPartner::OnCheckVz()
{
    AeGetApp()->IsKundeHome = IsDlgButtonChecked(IDC_CHECK_VZ) ? true : false;

    FillList();
}

void CDAttachPartner::FillList()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    CCALLBACKATTACH attach;
    CCALLBACKPARTNER partner;
    CCALLBACKDIVISION division;
    CCALLBACKREASONS reasons;
    CString Listname;
    short sDivisionno;
    short sReasonno;
    short sBranchNo;
    ppString DivisionName;
    ppString ReasonName;
    struct partners m_p;
    pl.clear();
    attach.SetUid(m_lUid);
    attach.SetRegionnr(AeGetApp()->VzNr());
    attach.SetVertriebszentrumnr(AeGetApp()->VzNr());
    attach.SetFilialnr(AeGetApp()->VzNr());
    m_List1.DeleteAllItems();
    m_List2.DeleteAllItems();
    BeginWaitCursor();

    if (AeGetApp()->IsNewCallback())
    {
        division.SetRegionnr(AeGetApp()->VzNr());
        division.SetBranchno(AeGetApp()->VzNr());
        division.SetCallbackstart(m_lStartNoCallback);
        division.SetCallbackend(m_lEndNoCallback);

        for (;;)
        {
            if (AeGetApp()->IsKundeHome())
            {
                division.SelList();
            }
            else
            {
                division.SelListAll();
            }

            if (division.rc == SRV_SQLNOTFOUND)
            {
                division.CloseCursor();
                break;
            }

            division.GetDivisionname(DivisionName);
            reasons.SetBranchno(division.GetBranchno());
            reasons.SetCallbackdivisionno(division.GetCallbackdivisionno());

            for (;;)
            {
                reasons.SelList();

                if (reasons.rc == SRV_SQLNOTFOUND)
                {
                    reasons.CloseCursor();
                    break;
                }

                s[0].Format("%d", division.GetBranchno());
                s[1] = DivisionName;
                s[2] = reasons.GetCallbackreason(ReasonName);
                s[3].Format("%d", division.GetCallbackdivisionno());
                s[4].Format("%d", reasons.GetReasonno());

                if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
                {
                    EndWaitCursor();
                    return;
                }
            }
        }
    }
    else
    {
        partner.SetRegionnr(AeGetApp()->VzNr());
        partner.SetVertriebszentrumnr(AeGetApp()->VzNr());

        for (;;)
        {
            if (AeGetApp()->IsKundeHome())
            {
                partner.SelectAllVz();
            }
            else
            {
                partner.SelectAll();
            }

            if (partner.rc == SRV_SQLNOTFOUND)
            {
                partner.CloseCursor();
                break;
            }

            s[0].Format("%d", partner.GetVertriebszentrumnr());
            s[1] = partner.GetCallbackpartner(DivisionName);
            s[2].Empty();
            s[3].Format("%d", partner.GetCallbackpartno());
            s[4].Empty();

            if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
            {
                EndWaitCursor();
                return;
            }
        }
    }

    for (;;)
    {
        if (AeGetApp()->IsKundeHome())
        {
            attach.SelVz();
        }
        else
        {
            attach.Sel();
        }

        if (attach.rc == SRV_SQLNOTFOUND)
        {
            attach.CloseCursor();
            break;
        }

        sDivisionno = (short)attach.GetCallbackpartno();
        sReasonno = attach.GetReasonno();
        sBranchNo = attach.GetVertriebszentrumnr();

        for (int pos = 0 ; pos < m_List1.GetItemCount(); pos++)
        {
            if (sDivisionno == atol(m_List1.GetItemText(pos, 3)) && sBranchNo == atol(m_List1.GetItemText(pos, 0)) && sReasonno == atol(m_List1.GetItemText(pos, 4)))
            {
                CListCtrlHelper::SetItemStateSelected(m_List1, pos);
                OnButtonDef();
                break;
            }
        }
    }

    if (m_List1.GetItemCount() == 0)
    {
        GetDlgItem(IDC_BUTTON_DEF)->EnableWindow(FALSE);
    }
    else
    {
        GetDlgItem(IDC_BUTTON_DEF)->EnableWindow(TRUE);
    }
    CListCtrlHelper::SetFocusSelected(m_List2, 0);

    if (m_List2.GetItemCount() == 0)
    {
        GetDlgItem(IDC_BUTTON_UNDEF)->EnableWindow(FALSE);
    }
    else
    {
        GetDlgItem(IDC_BUTTON_UNDEF)->EnableWindow(TRUE);
    }
    CListCtrlHelper::SetFocusSelected(m_List1, 0);

    EndWaitCursor();
}
