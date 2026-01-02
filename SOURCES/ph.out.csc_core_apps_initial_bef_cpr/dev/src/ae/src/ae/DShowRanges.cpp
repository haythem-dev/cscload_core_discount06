// DShowRanges.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "rangelist.h"
#include <ranges.h>
#include <artsel.h>
#include "DShowRanges.h"
#include "DRangeDetails.h"
#include "RangeListctrl.h"


// CDShowRanges-Dialogfeld

IMPLEMENT_DYNAMIC(CDShowRanges, CDialog)
CDShowRanges::CDShowRanges(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDShowRanges::IDD, pParent), CPageBrowser(0)
{
    m_ListCtl = new CRangeListCtrl;
    assert(m_ListCtl);
}

CDShowRanges::~CDShowRanges()
{
}

void CDShowRanges::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, *m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDShowRanges, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnLvnKeydownList1)
END_MESSAGE_MAP()


// CDShowRanges-Meldungshandler

BOOL CDShowRanges::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_ListCtl->init();

    DWORD dwOldBits = m_ListCtl->GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl->SetExtendedStyle(dwOldBits);

    //Variablen
    CRANGELIST range;
    CDISCOUNTGROUP discgrp;
    CARTINF artikel;
    int index;
    char str[81];
    int rc = SRV_OK;
    char error_msg[81];
    int first = 1;
    int iGrpSave = 0;
    ppString descript;
    CString values;
    int iRabOK = 1;

    ::buf_default((void *)&range.s, RANGELIST_BES, RANGELIST_ANZ);

    CLetterMan kb;
    for (;;)
    {
        if (AeGetApp()->IsBG())
        {
            rc = ::ServerNr(PIPE_AE_SRV, AasrvGetRangesBG, (void*)&range.s, RANGELIST_BES, RANGELIST_ANZ, error_msg);
        }
        else
        {
            rc = ::ServerNr(PIPE_AE_SRV, AasrvGetRanges, (void*)&range.s, RANGELIST_BES, RANGELIST_ANZ, error_msg);
        }
        if (rc != SRV_OK)
            break;
        first = 0;
        index = m_ListCtl->GetItemCount();
        if (m_ListCtl->InsertItem(index, "") == -1)
            return FALSE;
        m_ListCtl->SetItemText(index, RL_COL_KB, kb.Next());
        if (iGrpSave != range.s.DISCOUNTGRPNO)
        {
            if (AeGetApp()->IsBG())
            {
                for (int bg = 0;bg < m_ListCtl->GetItemCount(); bg++)
                {
                    if (atoi(m_ListCtl->GetItemText(bg, RL_COL_GRPNO)) == iGrpSave)
                    {
                        if (iRabOK)
                        {
                            m_ListCtl->setItemColor(bg, RGB(0, 0, 0), RGB(0, 255, 0));
                        }
                        else
                        {
                            m_ListCtl->setItemColor(bg, RGB(0, 0, 0), RGB(255, 0, 0));
                        }
                    }
                }
            }
            discgrp.SetBranchno(AeGetApp()->VzNr_Kunde());
            discgrp.SetDiscountgrpno(range.s.DISCOUNTGRPNO);
            discgrp.Selgroup();
            m_ListCtl->SetItemText(index, RL_COL_GRPNAME, discgrp.GetDescription(descript));
            iGrpSave = range.s.DISCOUNTGRPNO;
            iRabOK = 1;
        }
        m_ListCtl->SetItemText(index, RL_COL_GRPNO, _ltoa(range.s.DISCOUNTGRPNO, str, 10));
        m_ListCtl->SetItemText(index, RL_COL_ARTNO, _ltoa(range.s.ARTICLENO, str, 10));
        m_ListCtl->SetItemText(index, RL_COL_BASEQTY, _ltoa(range.s.BASEQTY, str, 10));
        m_ListCtl->SetItemText(index, RL_COL_QTY, _ltoa(range.s.ANZAHL, str, 10));
        if (range.s.BASEQTY > 0)
        {
            m_ListCtl->SetItemText(index, RL_COL_QTY_DIFF, _ltoa((range.s.ANZAHL - range.s.BASEQTY), str, 10));
        }
        else
        {
            m_ListCtl->SetItemText(index, RL_COL_QTY_DIFF, "0");
        }
        values.Format("%0.0f", range.s.BASE_VALUE);
        m_ListCtl->SetItemText(index, RL_COL_BASEVALUE, values);
        values.Format("%0.2f", range.s.ORDVALNET);
        m_ListCtl->SetItemText(index, RL_COL_VALUE, values);
        if (range.s.BASE_VALUE > 0.01)
        {
            values.Format("%0.2f", (range.s.ORDVALNET - range.s.BASE_VALUE));
            m_ListCtl->SetItemText(index, RL_COL_VALUE_DIFF, values);
        }
        else
        {
            m_ListCtl->SetItemText(index, RL_COL_VALUE_DIFF, "0.00");
        }
        values.Format("%0.2f", range.s.DISCOUNTVALUEPCT);
        m_ListCtl->SetItemText(index, RL_COL_DISCVALUE, values);
        m_ListCtl->SetItemText(index, RL_COL_DISCQTY, _ltoa(range.s.DISCOUNTQTY, str, 10));
        m_ListCtl->SetItemText(index, RL_COL_DISCARTICLE, _ltoa(range.s.DISCOUNTARTICLE, str, 10));
        if (range.s.DISCOUNTARTICLE > 0)
        {
            artikel.s.ARTIKEL_NR = range.s.DISCOUNTARTICLE;
            artikel.s.FILIALNR = AeGetApp()->VzNr();
            artikel.Server(AatartInf_art_nr);
            if (artikel.rc == SRV_OK)
            {
                m_ListCtl->SetItemText(index, RL_COL_DISCARTNAME, artikel.s.ARTIKEL_NAME);
            }
        }
        if (AeGetApp()->IsHR() && range.s.ARTICLENO !=0)
        {
            artikel.s.ARTIKEL_NR = range.s.ARTICLENO;
            artikel.s.FILIALNR = AeGetApp()->VzNr();
            artikel.Server(AatartInf_art_nr);
            if (artikel.rc == SRV_OK)
            {
                m_ListCtl->SetItemText(index, RL_COL_DISCARTNAME, artikel.s.ARTIKEL_NAME);
            }
        }
        if (range.s.BASEQTY > 0)
        {
            if (range.s.ANZAHL >= range.s.BASEQTY)
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(0, 255, 0));
            }
            else
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 0, 0));
                iRabOK = 0;
            }
        }
        else if (range.s.BASE_VALUE > 0.01)
        {
            if (range.s.ORDVALNET >= range.s.BASE_VALUE)
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(0, 255, 0));
            }
            else
            {
                m_ListCtl->setItemColor(index, RGB(0, 0, 0), RGB(255, 0, 0));
                iRabOK = 0;
            }
        }
    }
    if (first)
    {
        if (rc == -2)
        {
            MsgBoxOK(error_msg);
        }
        else
        {
            MsgBoxOK(AETXT_NO_RANGES);
        }
        CDialogMultiLang::OnCancel();
    }

    UpdateData(FALSE);
    m_ListCtl->SetFocus();
    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDShowRanges::OnOK()
{
    int pos = m_ListCtl->GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }

    CDRangeDetails details;
    details.m_CRangeNr = m_ListCtl->GetItemText(pos, RL_COL_GRPNO);
    details.m_CRangeName = m_ListCtl->GetItemText(pos, RL_COL_GRPNAME);
    if (details.m_CRangeNr == "0")  // CPR-250101 if GRPNO=0 do nothing
    {
        return;
    }
    if (details.m_CRangeName.IsEmpty())
    {
        for (int newpos = pos-1; newpos >= 0; newpos--)
        {
            details.m_CRangeName = m_ListCtl->GetItemText(newpos, RL_COL_GRPNAME);
            if (!details.m_CRangeName.IsEmpty())
            {
                pos = newpos;
                break;
            }
        }
    }
    if (atoi(m_ListCtl->GetItemText(pos, RL_COL_BASEQTY)) > 0)
    {
        details.m_CSMin = CResString::ex().getStrTblText(AETXT_MIN_QTY);
        details.m_CMin = m_ListCtl->GetItemText(pos, RL_COL_BASEQTY);
        details.m_CDone = m_ListCtl->GetItemText(pos, RL_COL_QTY);
        details.m_CDiff = m_ListCtl->GetItemText(pos, RL_COL_QTY_DIFF);
    }
    else if (atoi(m_ListCtl->GetItemText(pos, RL_COL_BASEVALUE)) > 0.01)
    {
        details.m_CSMin = CResString::ex().getStrTblText(AETXT_MIN_VALUE);
        details.m_CMin = m_ListCtl->GetItemText(pos, RL_COL_BASEVALUE);
        details.m_CDone = m_ListCtl->GetItemText(pos, RL_COL_VALUE);
        details.m_CDiff = m_ListCtl->GetItemText(pos, RL_COL_VALUE_DIFF);
    }
    else
    {
        details.m_CSMin.Empty();
        details.m_CMin.Empty();
        details.m_CDone.Empty();
        details.m_CDiff.Empty();
    }
    details.m_sBranchNo = AeGetApp()->VzNr_Kunde();
    details.DoModal();
}

void CDShowRanges::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnOK();
    *pResult = 0L;
}

void CDShowRanges::OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    OnKeydownList(pNMHDR, pResult, *m_ListCtl, true, false);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InRange(pLVKeyDow->wVKey, m_ListCtl->GetItemCount()))
    {
        OnOK();
    }
}
