// DAeStatusAe.cpp : implementation file
//

#include "stdafx.h"
#include <callback.h>
#include <auftraginfo.h>
#include "DAeStatusAe.h"
#include "aeorderstat.h"
#include "DRrNotDone.h"
#include "vbcount.h"
#include <controlling.h>
#include "DKommiChange.h"
#include "MainFrm.h"

#define AEST_AUSG_STATUS        1   //Timeridentifikation
#define AEST_AKT_ZEIT       60000   //eine Minute
#define AEST_ALARM              2   //Timeridentifikation for Beep
#define AEST_ALARM_ZEIT      1500   //1,5 Sekunden
#define AEST_ANZAHL_ALARM      10
#define AEST_MAXMIN_ALARM      10
#define MAX_SELECT             10
#define HIGH_MIN               10

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     9

static COLUMNS_TYPES Columns[] =
{
    0,  "",  60, LVCFMT_RIGHT,
    1,  "",  46, LVCFMT_LEFT,
    2,  "",  60, LVCFMT_RIGHT,
    3,  "", 180, LVCFMT_LEFT,
    4,  "", 160, LVCFMT_LEFT,
    5,  "",  60, LVCFMT_LEFT,
    6,  "",  40, LVCFMT_RIGHT,
    7,  "",  40, LVCFMT_RIGHT,
    8,  "",  80, LVCFMT_RIGHT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDAeStatusAe dialog


CDAeStatusAe::CDAeStatusAe(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeStatusAe::IDD, pParent)
{
    m_CStringComboBox = _T("");
    m_cTasks = _T("");
    m_Sort1 = _T("");
    m_Sort2 = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_AUF_NR);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_POS);
    Columns[7].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_TRM);

}


void CDAeStatusAe::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_RR, m_CBRr);
    DDX_Control(pDX, IDC_BUTTON_KC, m_CBKc);
    DDX_Control(pDX, IDC_COMBO_MINUTEN, m_CComboMinuten);
    DDX_Control(pDX, IDC_LIST2, m_ListCtl_Zur);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_CBString(pDX, IDC_COMBO_MINUTEN, m_CStringComboBox);
    DDX_Text(pDX, IDC_STATIC_TASKS, m_cTasks);
}


BEGIN_MESSAGE_MAP(CDAeStatusAe, CDialogMultiLang)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_CHECK_ALARM, OnCheckAlarm)
    ON_BN_CLICKED(IDC_CHECK_SORT, OnCheckSort)
    ON_BN_CLICKED(IDC_BUTTON_RR, OnButtonRr)
    ON_BN_CLICKED(IDC_BUTTON_KC, OnButtonKc)
    ON_WM_CTLCOLOR()
    ON_WM_DESTROY()
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnLvnColumnclickList1)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, OnLvnColumnclickList2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAeStatusAe message handlers

BOOL CDAeStatusAe::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();
    m_bAlarmTimer = FALSE;
    m_bAlarm = FALSE;
    SetTimer(AEST_AUSG_STATUS, AEST_AKT_ZEIT , NULL);

    // Add the columns.
    if (   !CListCtrlHelper::AddColumns(Columns, m_ListCtl)
        || !CListCtrlHelper::AddColumns(Columns, m_ListCtl_Zur) )
    {
        return FALSE;
    }

    AllgSetColumnWidthUser(m_ListCtl, "CAeStatusAe", KEY_PATH, NUM_COLUMNS);
    AllgSetColumnWidthUser(m_ListCtl_Zur, "CAeStatusAe2", KEY_PATH, NUM_COLUMNS);

    if (!GetAeUser().IsMehrVz())
    {
        GetDlgItem(IDC_CHECK_ALARM)->ShowWindow(SW_HIDE);
    }

    AusgabeDaten();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDAeStatusAe::AusgabeDaten()
{
    CString CStr;
    CString CStr1;
    ppString CStr2;
    CAUFSTATUS aufstatus;
    CVBCOUNT vbcount;
    CTASKCONTROL taskcontrol;

    LookforRr();
    LookforKc();
    BeginWaitCursor();
    // nase ANZ_ER wird zweckentfremdet für VZ-Nr benutzt
    aufstatus.s.ANZ_ER = IsDlgButtonChecked(IDC_CHECK_ALLE_VZ) ? 0 : AeGetApp()->VzNr();
    vbcount.s.ANZ_ER = aufstatus.s.ANZ_ER;
    aufstatus.Server(AaauftStatusae);
    vbcount.s.ANZ_IE = IsDlgButtonChecked(IDC_CHECK_ALLE_VZ) ? 0 : AeGetApp()->VzNr();
    vbcount.Server(AaauftSel_vbcount);
    EndWaitCursor();

    //Kontrolle on Hintergrundprozesse schlafen
    if (   (aufstatus.s.ANZ_ER >= AEST_ANZAHL_ALARM)
        || (aufstatus.s.ANZ_IK >= AEST_ANZAHL_ALARM)
        || (aufstatus.s.ANZ_BF >= AEST_ANZAHL_ALARM)
        || (aufstatus.s.ANZ_GD >= AEST_ANZAHL_ALARM)
        || (aufstatus.s.PHONMIN >= AEST_MAXMIN_ALARM)
        || (aufstatus.s.PARAMIN >= AEST_MAXMIN_ALARM)
        || (aufstatus.s.SERAMIN >= AEST_MAXMIN_ALARM))
    {
        Alarm();
    }
    else
        Alarm(FALSE);

    CStr.Format("%ld", aufstatus.s.ANZ_IE);
    GetDlgItem(IDC_STATIC_IE)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_IAEN);
    GetDlgItem(IDC_STATIC_INAEND)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_ZU);
    GetDlgItem(IDC_STATIC_ZU)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_ER);
    GetDlgItem(IDC_STATIC_ER)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_IK);
    GetDlgItem(IDC_STATIC_IK)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_BF);
    GetDlgItem(IDC_STATIC_BF)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_FA);
    if (!GetAeUser().AnzFilialUms())
        CStr = "xxxxx";
    GetDlgItem(IDC_STATIC_FA)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_GD);
    GetDlgItem(IDC_STATIC_GD)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_ST);
    GetDlgItem(IDC_STATIC_ST)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_DD);
    GetDlgItem(IDC_STATIC_DD)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.FAKTUR_ZEILEN);
    if (!GetAeUser().AnzFilialUms())
        CStr = "xxxxx";
    GetDlgItem(IDC_STATIC_ZLN)->SetWindowText(CStr);
    CStr.Format("%ld", aufstatus.s.ANZ_WANNEN);
    if (!GetAeUser().AnzFilialUms())
        CStr = "xxxxx";
    GetDlgItem(IDC_STATIC_WANNEN)->SetWindowText(CStr);
    CStr.Format("%ld %s", aufstatus.s.FAKTUR_WERT,CResString::ex().getStrTblText(AETXT_DM).GetString());
    if (!GetAeUser().AnzFilialUms())
        CStr = "xxxxx";
    GetDlgItem(IDC_STATIC_UMSATZ)->SetWindowText(CStr);
    CStr.Format("%ld %s", aufstatus.s.WERT_AND_NL,CResString::ex().getStrTblText(AETXT_DM).GetString());
    if (!GetAeUser().AnzFilialUms())
        CStr = "xxxxx";
    GetDlgItem(IDC_STATIC_UMS_AND_NL)->SetWindowText(CStr);

    // ausgabe verbund aufträge
    CStr.Format("%ld", vbcount.s.ANZ_IE);
    GetDlgItem(IDC_STATIC_VB_IE)->SetWindowText(CStr);
    CStr.Format("%ld", vbcount.s.ANZ_ER);
    GetDlgItem(IDC_STATIC_VB_ER)->SetWindowText(CStr);
    CStr.Format("%ld", vbcount.s.ANZ_ST);
    GetDlgItem(IDC_STATIC_VB_ST)->SetWindowText(CStr);
    CStr.Format("%ld", vbcount.s.ANZ_GD);
    GetDlgItem(IDC_STATIC_VB_GD)->SetWindowText(CStr);

    // ausgabe offene aufträge
    CStr.Format("%ld/%ld", aufstatus.s.PHONANZ, aufstatus.s.PHONMIN);
    GetDlgItem(IDC_STATIC_PHONETIK)->SetWindowText(CStr);
    CStr.Format("%ld/%ld", aufstatus.s.PARAANZ, aufstatus.s.PARAMIN);
    GetDlgItem(IDC_STATIC_PARALLEL)->SetWindowText(CStr);
    CStr.Format("%ld/%ld", aufstatus.s.SERAANZ, aufstatus.s.SERAMIN);
    GetDlgItem(IDC_STATIC_SERIEL)->SetWindowText(CStr);

    CStr.Empty();
    CStr1.Empty();
    taskcontrol.SetVertriebszentrumnr(AeGetApp()->VzNr());
    for (;;)
    {
        if (!taskcontrol.CheckTimes())
        {
            CStr1 += taskcontrol.GetProgrammname(CStr2);
            CStr1 += ' ';
        }
        else
            break;
    }
    taskcontrol.CloseCursor();
    if (!CStr1.IsEmpty())
    {
        CStr.Format(CResString::ex().getStrTblText(IDS_ATT_NOT_ACTIV), CStr1.GetString());
        Alarm();
    }
    else
    {
        CStr.Empty();
    }
    GetDlgItem(IDC_STATIC_TASKS)->SetWindowText(CStr);

    if (aufstatus.s.PHONANZ != 0 || aufstatus.s.PARAANZ != 0 || aufstatus.s.SERAMIN != 0)
       ShowDiffToTime();
    // ende ausgabe offene aufträge
    AusgabeListBox(&m_ListCtl, AEORD_IN_ERFASSUNG);
    AusgabeListBox(&m_ListCtl_Zur, AEORD_ZURUECKGESTELLT);
}

void CDAeStatusAe::ShowDiffToTime()
{
    CAUFSTPLAN aufstplan;
    CString csOutput;
    int iCount;
     // nase RUFZEITGEAENDERT wird zweckentfremdet für VZ-Nr benutzt
    if (!IsDlgButtonChecked(IDC_CHECK_ALLE_VZ))
        aufstplan.s.RUFZEITGEAENDERT = AeGetApp()->VzNr();
    else
        aufstplan.s.RUFZEITGEAENDERT = 0;

    BeginWaitCursor();
    m_CComboMinuten.ResetContent();
    for (iCount = 0; iCount < MAX_SELECT; iCount++)
    {
        aufstplan.s.FETCH_REL = 1;
        aufstplan.Server(AaauftStatplan_sel);
        if (aufstplan.rc != SRV_OK)
            break;
        if (aufstplan.s.RUFZEITGEAENDERT < HIGH_MIN)
            continue;
        csOutput.Format("%s %03ldMin IDF:%07ld", aufstplan.s.ANRUFART, aufstplan.s.RUFZEITGEAENDERT, aufstplan.s.IDFNR);
        m_CComboMinuten.InsertString(iCount, csOutput);
    }

    if (iCount > 0)
        m_CComboMinuten.SetCurSel(0);

    aufstplan.s.FETCH_REL = 0;
    aufstplan.Server(AaauftStatplan_sel);
    EndWaitCursor();
}

void CDAeStatusAe::AusgabeListBox(CListCtrl *list, CString Status)
{
    CString ATour;
    CString CStr;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    CAUSTINF austinf;
    austinf.s.FETCH_REL = 1;
    austinf.s.KDAUFTRAGNR = 0;
    memset(austinf.s.ZUGRUND,' ', L_AUFTRAG_ZUGRUND);
    austinf.s.ZUGRUND[0] = '%';
    if (!IsDlgButtonChecked(IDC_CHECK_ALLE_VZ))
        austinf.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    else austinf.s.VERTRIEBSZENTRUMNR = 0;
    austinf.s.REGIONNR = AeGetApp()->VzNr();
    AllgStrCopy(austinf.s.GERAETNAME, "%", L_AUSTINF_GERAETNAME);
    AllgStrCopy(austinf.s.KDAUFTRAGSTAT, Status, L_AUSTINF_KDAUFTRAGSTAT);
    strcpy(austinf.s.TOURID, "%");
    strcpy(austinf.s.KDAUFTRAGART, "%");
    if (Status == AEORD_IN_ERFASSUNG)
        strcpy(austinf.s.SORTFIELD, m_Sort1);
    else
        strcpy(austinf.s.SORTFIELD, m_Sort2);
    austinf.s.FETCH_REL = 1;
    austinf.s.DATUM = 0; //nur aktuelle Auftraege
    list->DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        austinf.Server(AaauftSelzurauft);
        austinf.s.FETCH_REL = 1;              //normaler Fetch
        if (austinf.rc != SRV_OK)
        {
            break;
        }
        //Ausgabe in die Listbox
        CStr.Format("%d", austinf.s.KDAUFTRAGNR);
        s[0] = CStr;
        CStr.Format("%s%s%s", austinf.s.KDAUFTRAGART, austinf.s.KOART, austinf.s.BUCHART);
        s[1] = CStr;
        CStr.Format("%d", austinf.s.IDFNR);
        s[2] = CStr;
        AllgEntfSpaces(austinf.s.NAMEAPO);
        AllgEntfSpaces(austinf.s.NAMEINHABER);
        s[3] = austinf.s.NAMEAPO;
        if (AeGetApp()->IsHR())
        {
            s[3] += " ";
            s[3] += austinf.s.NAMEINHABER;
        }
        AllgEntfSpaces(austinf.s.ORT);
        s[4] = austinf.s.ORT;
        AllgEntfSpaces( austinf.s.TOURID );
        if (atol(austinf.s.TOURID))
        {
            ATour.Format("%2.2s:%2.2s/%2.2s", austinf.s.TOURID, austinf.s.TOURID + 2, austinf.s.TOURID + 4);
        }
        else
        {
            ATour = "";
        }
        s[5] = ATour;
        CStr.Format("%ld", austinf.s.ANZPOS);
        s[6] = CStr;
        AllgEntfSpaces(austinf.s.GERAETNAME);
        s[8] = austinf.s.GERAETNAME;
        char timeStr[81];
        austinf.s.ZEITERSTEGUELTIGK /= 1000;
        s[7]= ppGTimeLongToCharHHMM(austinf.s.ZEITERSTEGUELTIGK, timeStr);

        if (!CListCtrlHelper::AppendItem(*list, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    austinf.s.FETCH_REL = 0;
    austinf.Server(AaauftSelzurauft);   /* Close Cursor */
    EndWaitCursor();
}

void CDAeStatusAe::OnOK()
{
    AusgabeDaten();
}

void CDAeStatusAe::OnCancel()
{
    CDialogMultiLang::OnOK();
}

void CDAeStatusAe::Alarm(int bAlarm)
{
    if (bAlarm == TRUE && m_bAlarm == FALSE)
    {
        GetDlgItem(IDC_CHECK_ALARM)->ShowWindow(SW_SHOW);
        CheckDlgButton(IDC_CHECK_ALARM,TRUE);
        SetTimer(AEST_ALARM, AEST_ALARM_ZEIT , NULL);
        m_bAlarmTimer = TRUE;
        m_bAlarm = TRUE;
    }
    else if (bAlarm == FALSE)
    {
        GetDlgItem(IDC_CHECK_ALARM)->ShowWindow(FALSE);
        if (m_bAlarmTimer)
            KillTimer(AEST_ALARM);
        m_bAlarmTimer = FALSE;
        m_bAlarm = FALSE;
    }
}

void CDAeStatusAe::OnTimer(UINT nIDEvent)
{
    if (nIDEvent == AEST_AUSG_STATUS)
        AusgabeDaten();
    if (nIDEvent == AEST_ALARM)
    {
        if (!AeGetApp()->IsNoBeep())
            Beep(1000, 1000);
    }
    CDialogMultiLang::OnTimer(nIDEvent);
}

void CDAeStatusAe::OnCheckAlarm()
{
    if (!IsDlgButtonChecked(IDC_CHECK_ALARM))
    {
        if (m_bAlarmTimer)
            KillTimer(AEST_ALARM);
        m_bAlarmTimer = FALSE;
    }
    else
    {
        if (!m_bAlarmTimer)
            SetTimer(AEST_ALARM, AEST_ALARM_ZEIT, NULL);
        m_bAlarmTimer = TRUE;
    }
}

void CDAeStatusAe::OnCheckSort()
{
    if (IsDlgButtonChecked(IDC_CHECK_SORT))
    {
        SortList(5);        // Sortieren nach 6. Listbox-Feld (Tour)
    }
    else
    {
        SortList(0);        // Sortieren nach 1. Listbox-Feld (Auftrag-nr)
    }
}

void CDAeStatusAe::SortList(int sortfield)
{
    CString feld;
    CString feld1;
    CString feld2;
    int x;
    int y;
    int lastchange;
    int max;
    if ((lastchange = m_ListCtl.GetItemCount()) > 1)
    {
        for (;;)
        {
            max = lastchange;
            if (max <= 1)
                break;
            lastchange = 0;
            for (x = 0; x < max; x++)
            {
                feld = m_ListCtl.GetItemText(x, sortfield);     //ohne Wert nach hinten
                if (feld.IsEmpty())
                    feld = "99999999";
                feld1.Format("%08s", feld.GetString());
                feld = m_ListCtl.GetItemText(x + 1, sortfield);
                if (feld.IsEmpty())
                    feld = "99999999";
                feld2.Format("%08s", feld.GetString());

                if (feld1 > feld2)
                {
                    lastchange = x;
                    for (y = 0; y < NUM_COLUMNS; y++)
                    {
                        feld = m_ListCtl.GetItemText(x + 1, y);
                        m_ListCtl.SetItemText(x + 1, y, m_ListCtl.GetItemText(x, y));
                        m_ListCtl.SetItemText(x, y, feld);
                    }
                }
            }
        }
    }
    if ((lastchange = m_ListCtl_Zur.GetItemCount()) > 1)
    {
        for (;;)
        {
            max = lastchange;
            if (max < 1)
                break;
            lastchange = 0;
            for (x = 0; x < max; x++)
            {
                feld = m_ListCtl_Zur.GetItemText(x, sortfield);     //ohne Wert nach hinten
                if (feld.IsEmpty())
                    feld = "99999999";
                feld1.Format("%08s", feld.GetString());
                feld = m_ListCtl_Zur.GetItemText(x + 1, sortfield);
                if (feld.IsEmpty())
                    feld = "99999999";
                feld2.Format("%08s", feld.GetString());

                if (feld1 > feld2)
                {
                    lastchange = x;
                    for (y = 0; y < NUM_COLUMNS; y++)
                    {
                        feld = m_ListCtl_Zur.GetItemText(x + 1, y);
                        m_ListCtl_Zur.SetItemText(x + 1, y, m_ListCtl_Zur.GetItemText(x, y));
                        m_ListCtl_Zur.SetItemText(x, y, feld);
                    }
                }
            }
        }
    }
}

void CDAeStatusAe::OnButtonRr()
{
    CDRrNotDone dlgRrNotDone;
    dlgRrNotDone.DoModal();
}

void CDAeStatusAe::OnButtonKc()
{
    CDKommiChange dlgKommiChange;
    dlgKommiChange.DoModal();
}

void CDAeStatusAe::LookforRr()
{
    int kzda;
    ppString hilfe;
    ppString hilfe2;
    ppString hilfe3;
    char error_msg[81];
    if (AeGetApp()->IsNewCallback())
    {
        m_callbacknew.SetVertriebszentrumnr(AeGetApp()->VzNr());
        m_callbacknew.SetRegionnr(AeGetApp()->VzNr());
        if (AeGetApp()->IsKundeHome())
            m_callbacknew.SelAllNotDoneVz();    //nicht bearbeitete Rückrufe vorhanden
        else
            m_callbacknew.SelAllNotDone();      //nicht bearbeitete Rückrufe vorhanden
        if (m_callbacknew.rc == SRV_OK)
        {
            m_CBRr.ShowWindow(SW_SHOW);
            m_pl.clear();
            for (;;)
            {
                m_pl.insert(m_pl.end(), m_callbacknew.GetCallbackno());
                kzda = 0;
                for (m_itold = m_plold.begin(); m_itold < m_plold.end(); m_itold++)
                {
                    if (m_callbacknew.GetCallbackno() == *m_itold)
                    {
                        kzda = 1;
                        break;
                    }
                }
                if (kzda == 0)       // Eintrag neu ?
                {
                    if (AeGetApp()->IsRRNotDone())
                    {
                        CString CStr;
                        CStr.Format(CResString::ex().getStrTblText(IDS_RR_NOT_YET_DONE),
                            m_callbacknew.GetNameapo(hilfe),
                            m_callbacknew.GetOrt(hilfe2),
                            AllgDatumLong2CharTTMMJJ(m_callbacknew.GetCallbackdatewished(), error_msg),
                            AllgZeit2CharHHMM(m_callbacknew.GetCallbacktimewished() * 100),
                            m_callbacknew.GetDivisionname(hilfe3));
                        MsgBoxOK(CStr);
                    }
                }
                if (AeGetApp()->IsKundeHome())
                    m_callbacknew.SelAllNotDoneVz();    //nicht bearbeitete Rückrufe vorhanden
                else
                    m_callbacknew.SelAllNotDone();      //nicht bearbeitete Rückrufe vorhanden
                if (m_callbacknew.rc == SRV_SQLNOTFOUND)
                {
                    m_plold.clear();
                    for (m_it = m_pl.begin(); m_it < m_pl.end(); m_it++)
                    {
                        m_plold.insert(m_plold.end(), *m_it);
                    }
                    break;
                }
            }
        }
        else m_CBRr.ShowWindow(SW_HIDE);
        if (AeGetApp()->IsKundeHome())
            m_callbacknew.SelAllNotDoneVz(0);   //CloseCursor
        else
            m_callbacknew.SelAllNotDone(0);     //CloseCursor
    }
    else
    {
        m_callback.SetVertriebszentrumnr(AeGetApp()->VzNr());
        m_callback.SetRegionnr(AeGetApp()->VzNr());
        if (AeGetApp()->IsKundeHome())
            m_callback.SelAllNotDoneVz();   //nicht bearbeitete Rückrufe vorhanden
        else
            m_callback.SelAllNotDone();     //nicht bearbeitete Rückrufe vorhanden
        if (m_callback.rc == SRV_OK)
        {
            m_CBRr.ShowWindow(SW_SHOW);
            m_pl.clear();
            for (;;)
            {
                m_pl.insert(m_pl.end(), m_callback.GetCallbackno());
                kzda = 0;
                for (m_itold = m_plold.begin(); m_itold < m_plold.end(); m_itold++)
                {
                    if (m_callback.GetCallbackno() == *m_itold)
                    {
                        kzda = 1;
                        break;
                    }
                }
                if (kzda == 0)       // Eintrag neu ?
                {
                    if (AeGetApp()->IsRRNotDone())
                    {
                        CString CStr;
                        CStr.Format(CResString::ex().getStrTblText(IDS_RR_NOT_YET_DONE),
                            m_callback.GetNameapo(hilfe),
                            m_callback.GetOrt(hilfe2),
                            AllgDatumLong2CharTTMMJJ(m_callback.GetCallbackdatewished(), error_msg),
                            AllgZeit2CharHHMM(m_callback.GetCallbacktimewished() * 100),
                            m_callback.GetCallbackpartner(hilfe3));
                        MsgBoxOK(CStr);
                    }
                }
                if (AeGetApp()->IsKundeHome())
                    m_callback.SelAllNotDoneVz();   //nicht bearbeitete Rückrufe vorhanden
                else
                    m_callback.SelAllNotDone();     //nicht bearbeitete Rückrufe vorhanden
                if (m_callback.rc == SRV_SQLNOTFOUND)
                {
                    m_plold.clear();
                    for (m_it = m_pl.begin(); m_it < m_pl.end(); m_it++)
                    {
                        m_plold.insert(m_plold.end(), *m_it);
                    }
                    break;
                }
            }
        }
        else
            m_CBRr.ShowWindow(SW_HIDE);
        if (AeGetApp()->IsKundeHome())
            m_callback.SelAllNotDoneVz(0);  //CloseCursor
        else
            m_callback.SelAllNotDone(0);    //CloseCursor
    }
}

HBRUSH CDAeStatusAe::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_TASKS)
        pDC->SetTextColor(RGB(200, 0, 0));
    return hbr;
}

void CDAeStatusAe::LookforKc()
{
    CPOSCHANGE m_actchange;
    m_actchange.SetVertriebszentrumnr(AeGetApp()->VzNr());
    m_actchange.SetSwchecked('0');
    BeginWaitCursor();
    if (m_actchange.SelList() != SRV_OK)
    {
        m_CBKc.ShowWindow(SW_HIDE);
        m_CBKc.EnableWindow(FALSE);
    }
    else
    {
        m_CBKc.ShowWindow(SW_SHOW);
        m_CBKc.EnableWindow(TRUE);
    }
    m_actchange.SelList(0); //CloseCursor
}

void CDAeStatusAe::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int col = pNMListView->iSubItem;
    if (col == 0) m_Sort1 = "kdauftragnr";
    else if (col == 1) m_Sort1 = "kdauftragart";
    else if (col == 2) m_Sort1 = "kunde.idfnr";
    else if (col == 3) m_Sort1 = "kunde.nameapo";
    else if (col == 4) m_Sort1 = "kunde.ort";
    else if (col == 5) m_Sort1 = "tourid";
    else if (col == 6) m_Sort1 = "anzpos";
    else if (col == 8) m_Sort1 = "geraetname";
    else
    {
        *pResult = 0L;
        return;
    }
    AusgabeListBox(&m_ListCtl,AEORD_IN_ERFASSUNG);
    *pResult = 0L;
}

void CDAeStatusAe::OnLvnColumnclickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int col = pNMListView->iSubItem;
    if (col == 0) m_Sort2 = "kdauftragnr";
    else if (col == 1) m_Sort2 = "kdauftragart";
    else if (col == 2) m_Sort2 = "kunde.idfnr";
    else if (col == 3) m_Sort2 = "kunde.nameapo";
    else if (col == 4) m_Sort2 = "kunde.ort";
    else if (col == 5) m_Sort2 = "tourid";
    else if (col == 6) m_Sort2 = "anzpos";
    else if (col == 8) m_Sort2 = "geraetname";
    else
    {
        *pResult = 0L;
        return;
    }
    AusgabeListBox(&m_ListCtl_Zur,AEORD_ZURUECKGESTELLT);
    *pResult = 0L;
}

void CDAeStatusAe::OnDestroy()
{
    AllgWriteColumnWidthUser(m_ListCtl, "CAeStatusAe", KEY_PATH, NUM_COLUMNS);
    AllgWriteColumnWidthUser(m_ListCtl_Zur, "CAeStatusAe2", KEY_PATH, NUM_COLUMNS);
    CDialogMultiLang::OnDestroy();
}
