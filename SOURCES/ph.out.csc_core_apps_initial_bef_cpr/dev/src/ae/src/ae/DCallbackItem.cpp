// DCallbackItem.cpp : implementation file
//

#include "stdafx.h"
#include "AeFView.h"
#include <kritiksatz.h>
#include <callback.h>
#include "DCallbackItem.h"
#include "CallbackStatusManager.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 80, LVCFMT_LEFT,
    2,  "", 80, LVCFMT_LEFT,
    3,  "", 80, LVCFMT_LEFT,
    4,  "",  0, LVCFMT_LEFT,    //Tageswert (0-6) + Anfangszeit versteckt
    5,  "",  0, LVCFMT_LEFT,    //Tageswert (0-6) + Endeszeit versteckt
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDCallbackItem dialog


CDCallbackItem::CDCallbackItem(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCallbackItem::IDD, pParent)
{
    m_CGrund = _T("");
    m_bKundeWunsch = FALSE;
    m_CTitel = _T("");
    m_CDatumCalc = _T("");
    m_CZeitCalc = _T("");
    m_CWotag = _T("");
    m_CMax = _T("");
    m_lKritiknr = 0;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TAG);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEGIN);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ENDE);
}


void CDCallbackItem::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATETIMEPICKER_RR_ZEIT, m_DT_Zeit);
    DDX_Control(pDX, IDC_DATETIMEPICKER_RR_DATUM, m_DT_Datum);
    DDX_Control(pDX, IDC_EDIT_WOTAG, m_EditWotag);
    DDX_Control(pDX, IDC_EDIT_MAX, m_EditMax);
    DDX_Control(pDX, IDC_EDIT_RR_ZEIT_CALC, m_EditZeitCalc);
    DDX_Control(pDX, IDC_EDIT_RR_DATUM_CALC, m_EditDatumCalc);
    DDX_Control(pDX, IDC_EDIT_TITEL, m_EditTitel);
    DDX_Control(pDX, IDC_COMBO_PARTNER, m_ComboPartner);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_EDIT_GRUND, m_EditGrund);
    DDX_Control(pDX, IDC_CHECK_KUNDE_WUNSCH, m_CBKundeWunsch);
    DDX_Text(pDX, IDC_EDIT_GRUND, m_CGrund);
    DDX_Check(pDX, IDC_CHECK_KUNDE_WUNSCH, m_bKundeWunsch);
    DDX_Text(pDX, IDC_EDIT_TITEL, m_CTitel);
    DDX_Text(pDX, IDC_EDIT_RR_DATUM_CALC, m_CDatumCalc);
    DDX_Text(pDX, IDC_EDIT_RR_ZEIT_CALC, m_CZeitCalc);
    DDX_Text(pDX, IDC_EDIT_WOTAG, m_CWotag);
    DDX_Text(pDX, IDC_EDIT_MAX, m_CMax);
    DDX_Control(pDX, IDC_EDIT_REFERENCE, m_EditReference);
}


BEGIN_MESSAGE_MAP(CDCallbackItem, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_GRUND, OnChangeEditGrund)
    ON_CBN_SELCHANGE(IDC_COMBO_PARTNER, OnSelchangeComboPartner)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_RR_DATUM, OnDatetimechangeDatetimepickerRrDatum)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCallbackItem message handlers

void CDCallbackItem::OnChangeEditGrund()
{
    AllgLaengeKontr(&m_EditGrund, L_KRITIKPOS_KRITIKTEXT, L_KRITIKPOS_KRITIKTEXT, AeGetApp()->Modus());
}

BOOL CDCallbackItem::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    m_saDay.SetSize(7);
    m_saDay.SetAt(0, CResString::ex().getStrTblText(IDS_SUNDAY));
    m_saDay.SetAt(1, CResString::ex().getStrTblText(IDS_MONDAY));
    m_saDay.SetAt(2, CResString::ex().getStrTblText(IDS_TUESDAY));
    m_saDay.SetAt(3, CResString::ex().getStrTblText(IDS_WEDNESDAY));
    m_saDay.SetAt(4, CResString::ex().getStrTblText(IDS_THURSDAY));
    m_saDay.SetAt(5, CResString::ex().getStrTblText(IDS_FRIDAY));
    m_saDay.SetAt(6, CResString::ex().getStrTblText(IDS_SATURDAY));

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    if (AeGetApp()->IsCBStatusUsed())
    {
        m_EditReference.SetLimitText(L_CALLBACKITEMS_REFERENCE);
    }
    else
    {
        GetDlgItem(IDC_STATIC_REFERENCE)->ShowWindow(SW_HIDE);
        m_EditReference.ShowWindow(SW_HIDE);
    }

    struct partners partners;
    pl.clear();
    partner.SetVertriebszentrumnr(AeGetApp()->VzNr());
    partner.SetRegionnr(AeGetApp()->VzNr());
    BeginWaitCursor();
    for (;;)
    {
        if ((CAeDoc*)((CAeFView*)AeGetApp()->m_pViewEing)->GetDocument()->IsModified())
        {
            partner.SetVertriebszentrumnr(AeGetApp()->VzNr_Kunde());
            partner.SelectAllVz();
        }
        else if (AeGetApp()->IsKundeHome())
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
        partners.No = partner.GetCallbackpartno();
        partner.GetCallbackpartner(partners.Name);
        partners.rr_time = partner.GetCallbacktime();
        pl.insert(pl.end(), partners);
        m_ComboPartner.AddString(partners.Name.c_str());
    }
    m_ComboPartner.SetCurSel(0);
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    CTime ctime = CTimeFromDateLongAndHour(1, zeit.s.DATUM);
    CTimeSpan y(365, 0, 0, 0);
    CTime end = ctime + y;
    m_DT_Datum.SetRange(&ctime, &end);
    GetOfficeTimes();
    if (!m_CGrund.IsEmpty())
    {
        m_DT_Zeit.SetFocus();
    }
    if (m_CTitel.IsEmpty())
    {
        m_CTitel = CResString::ex().getStrTblText(AETXT_RUECKRUF);
        m_EditTitel.SetFocus();
        m_EditTitel.SetSel(0, -1, FALSE);
    }
    else
    {
        m_EditTitel.EnableWindow(FALSE);
    }
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCallbackItem::OnOK()
{
    char error_msg[81];
    long datum;
    long rrzeit;
    long wtag;
    int time_ok;
    int x;
    CString WochenTag;
    CString str;
    CString vonzeit;
    CString biszeit;
    UpdateData();
    BeginWaitCursor();
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    CTime czeit;
    m_DT_Zeit.GetTime(czeit);
    rrzeit = (czeit.GetHour() * 100 + czeit.GetMinute());
    CTime ctime;
    m_DT_Datum.GetTime(ctime);
    datum = (ctime.GetYear() * 10000 + ctime.GetMonth() * 100 + ctime.GetDay());
    if (zeit.s.DATUM == datum && zeit.s.ZEIT > rrzeit * 100)
    {
        MsgBoxOK(IDP_RR_IN_PAST);
        m_DT_Zeit.SetFocus();
        return;
    }
    wtag = AllgGetWeekDay(datum, error_msg);
    WochenTag = m_saDay.GetAt(wtag);
    time_ok = 0;
    for (int i = 0; i < m_ListCtl.GetItemCount(); i++)
    {
        if (WochenTag == m_ListCtl.GetItemText(i, 1))
        {
            vonzeit.Empty();
            biszeit.Empty();
            str = m_ListCtl.GetItemText(i, 2);
            for (x = 0; x < str.GetLength(); x++)
            {
                if (str.GetAt(x) == ':')
                    continue;
                else
                    vonzeit += str.GetAt(x);
            }
            str = m_ListCtl.GetItemText(i, 3);
            for (x = 0; x < str.GetLength(); x++)
            {
                if (str.GetAt(x) == ':')
                    continue;
                else
                    biszeit += str.GetAt(x);
            }
            if (rrzeit >= atol(vonzeit) && rrzeit <= atol(biszeit))
            {
                time_ok = 1;
                break;
            }
        }
    }
    if (time_ok == 0)
    {
        MsgBoxOK(IDP_RR_OUT_OFFICE);
        m_DT_Zeit.SetFocus();
        return;
    }
    if (m_CGrund.IsEmpty())
    {
        MsgBoxOK(IDP_RR_NO_REASON);
        m_EditGrund.SetFocus();
        m_EditGrund.SetSel(0, -1, FALSE);
        return;
    }
    if (m_lKritiknr == 0)       // nock kein Kopfsatz
    {
        CKRITIKKOPF kopf;
        kopf.s.IDFNR = m_lIdf;
        kopf.s.KUNDENNR = m_lIdf;
        kopf.s.UID = GetAeUser().GetUID();
        kopf.s.FILIALNR = AeGetApp()->VzNr();
        kopf.s.VERTRIEBSZENTRUMNR = m_sVz;
        AllgStrCopy(kopf.s.TITEL, m_CTitel, L_KRITIKKOPF_TITEL);
        kopf.Server(AakritikSchreibe_kopf);
        m_lKritiknr = kopf.s.KRITIKNR;
    }

    long callbackpartno = 0L;
    short callbacktime = 0;
    GetSelectedPartner(callbackpartno, callbacktime);

    CKRITIKPOS kritikpos;
    kritikpos.s.KRITIKNR = m_lKritiknr;
    kritikpos.s.KZPOSART[0] = '1';
    kritikpos.s.UID = GetAeUser().GetUID();
    kritikpos.s.FILIALNR = AeGetApp()->VzNr();
    AllgStrCopy(kritikpos.s.KRITIKTEXT, m_CGrund, LS_KRITIKPOS_KRITIKTEXT);
    kritikpos.Server(AakritikSchreibe_pos);
    m_lPosNr = kritikpos.s.POSNR;
    m_Callbackitem.SetCallbackpartno(callbackpartno);
    m_Callbackitem.SetKritiknr(m_lKritiknr);
    m_Callbackitem.SetPosnr(kritikpos.s.POSNR);
    m_Callbackitem.SetKzposart(kritikpos.s.KZPOSART[0]);
    m_Callbackitem.SetPosnr_done(0);
    m_Callbackitem.SetCallbacktimewished(rrzeit);
    m_Callbackitem.SetCallbackdatewished(datum);
    m_Callbackitem.SetCallbacktime(callbacktime);
    m_Callbackitem.SetState(m_bKundeWunsch ? '1' : '0');
    if (AeGetApp()->IsCBStatusUsed())
    {
        TCHAR strRefernce[L_CALLBACKITEMS_REFERENCE + 1];
        m_EditReference.GetWindowText(strRefernce, L_CALLBACKITEMS_REFERENCE + 1);
        m_Callbackitem.SetReference(strRefernce);
        CCallbackStatusManager callbackStatusManager;
        m_Callbackitem.SetStatusId(callbackStatusManager.GetOpenStatusID());
    }
    else
    {
        m_Callbackitem.SetStatusId(0);
    }
    m_Callbackitem.SetLockkz('0');
    m_Callbackitem.InsertWithNewNo();

    CDialogMultiLang::OnOK();
}

BOOL CDCallbackItem::GetOfficeTimes()
{
    //Variablen
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    UpdateData();

    //Anfangsinitialisierung durchfuehren
    long callbackpartno = 0L;
    short callbacktime = 0;
    GetSelectedPartner(callbackpartno, callbacktime);

    m_Callbacktime.SetCallbackpartno(callbackpartno);
    m_ListCtl.DeleteAllItems();
    m_rrzeit = callbacktime;
    m_CMax.Format("%d", m_rrzeit);
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; ; i++)
    {
        m_Callbacktime.SelectCallbackPartner();
        if (m_Callbacktime.rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        s[1] = m_saDay.GetAt(m_Callbacktime.GetOfficeday());
        s[2] = AllgZeit2CharHHMM((long)m_Callbacktime.GetBegintime());
        s[3] = AllgZeit2CharHHMM((long)m_Callbacktime.GetEndtime());
        s[4].Format("%01d%04ld", m_Callbacktime.GetOfficeday(), m_Callbacktime.GetBegintime());
        s[5].Format("%01d%04ld", m_Callbacktime.GetOfficeday(), m_Callbacktime.GetEndtime());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
    m_Callbacktime.CloseCursor();
    ComputeNextGoodTime();
    UpdateData(FALSE);
    return TRUE;
}


void CDCallbackItem::OnSelchangeComboPartner()
{
    GetOfficeTimes();
}

void CDCallbackItem::ComputeNextGoodTime()
{
    char error_msg[81];
    int maxeintrag;
    long acttime;
    long wtag;
    long lzeit;
    long difftag;
    BeginWaitCursor();
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    if (AllgAddTime(zeit.s.ZEIT, 500, &zeit.s.ZEIT) != 0)
        zeit.s.DATUM = AllgAddDate(zeit.s.DATUM, 1, error_msg);
    wtag = AllgGetWeekDay(zeit.s.DATUM, error_msg);
    lzeit = zeit.s.ZEIT / 100;
    acttime = zeit.s.ZEIT / 100 + wtag * 10000;
    maxeintrag = m_ListCtl.GetItemCount();
    for (int i = 0; i < maxeintrag; i++)
    {
        if ((acttime >= atol(m_ListCtl.GetItemText(i, 4)))
            && (acttime + m_rrzeit <= atol(m_ListCtl.GetItemText(i, 5))))
        {
            ComputeTime(zeit.s.DATUM, lzeit);
            return;
        }
    }
    for (int i = 0; i < maxeintrag; i++)
    {
        long lCallbackTime = atol(m_ListCtl.GetItemText(i, 4));
        if (acttime <= lCallbackTime)
        {
            lzeit = lCallbackTime % 10000;
            difftag = (lCallbackTime / 10000) - wtag;
            if (difftag < 0)
                difftag += 7;
            zeit.s.DATUM = AllgAddDate(zeit.s.DATUM, difftag, error_msg);
            ComputeTime(zeit.s.DATUM, lzeit);
            return;
        }
    }
    for (int i = 0; i < maxeintrag; i++)
    {
        long lCallbackTime = atol(m_ListCtl.GetItemText(i, 4));
        if (acttime <= lCallbackTime + 100000)
        {
            lzeit = lCallbackTime % 10000;
            difftag = (lCallbackTime / 10000) - wtag;
            difftag += 7;   //nächste Woche
            zeit.s.DATUM = AllgAddDate(zeit.s.DATUM, difftag, error_msg);
            ComputeTime(zeit.s.DATUM, lzeit);
            return;
        }
    }
    CTime ctime = CTimeFromDateTimeLongNoSeconds(zeit.s.DATUM, lzeit);
    m_DT_Datum.SetTime(&ctime);
    m_DT_Zeit.SetTime(&ctime);
    m_CDatumCalc.Empty();
    m_CZeitCalc.Empty();
    m_CWotag.Empty();
    MsgBoxOK(IDP_RR_NO_OFFICE);
}

void CDCallbackItem::ComputeTime(long lDate, long lTime)
{
    CTime ctime = CTimeFromDateTimeLongNoSeconds(lDate, lTime);
    m_DT_Datum.SetTime(&ctime);
    m_DT_Zeit.SetTime(&ctime);
    m_CDatumCalc = DDMMYYYYStringNoDotsFromDateLong(lDate);
    long lCompTime;
    AllgAddTime(lTime, m_rrzeit, &lCompTime);
    m_CZeitCalc.Format("%04ld", lCompTime);
    char error_msg[81];
    m_CWotag = m_saDay.GetAt(AllgGetWeekDay(lDate, error_msg));
}

void CDCallbackItem::OnDatetimechangeDatetimepickerRrDatum(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    CTime x;
    m_DT_Datum.GetTime(x);
    GetDlgItem(IDC_EDIT_WOTAG)->SetWindowText(m_saDay.GetAt(x.GetDayOfWeek() - 1));
    *pResult = 0L;
}

void CDCallbackItem::GetSelectedPartner(long& callbackpartno, short& callbacktime)
{
    int selectedPartner = m_ComboPartner.GetCurSel();
    if (!pl.empty() && (selectedPartner >= 0))
    {
        callbackpartno = pl.at(selectedPartner).No;
        callbacktime = pl.at(selectedPartner).rr_time;
    }
    else
    {
        callbackpartno = 0L;
        callbacktime = 0;
    }
}
