// aeview.cpp : implementation file
//

#include "stdafx.h"
#include "AeView.h"
#include "DKritik.h"
#include "DKndWahl.h"
#include "DAendFil.h"
#include <callback.h>
#include "DCallbackItem.h"
#include "DCallbackFetch.h"
#include "DRrMessage.h"
#include "DVbLief.h"
#include "DVbBuchen.h"
#include <mailsystem.h>
#include "DAeMailUser.h"
#include <touren.h>
#include <artikel.h>
#include "DMailMessage.h"
#include "DMailNew.h"
#include "DMailControl.h"
#include "CUCustomerTimes.h"
#include "DAeAnzFeiertage.h"
#include "DTourAnz.h"
#include "DChooseFiliale.h"
#include "DAeKundeVerbundFiliale.h"
#include "DAeArtVerbundFiliale.h"
#include "DTelListUpd.h"
#include <controlling.h>
#include "DSprachAuswahl.h"
#include "DTelNr.h"
#include "DTourSperr.h"
#include "DArtikelQuota.h"
#include "DQuotaKlasse.h"
#include "DQuotaSum.h"
#include "DDelayedArt.h"
#include "DSeperateOrder.h"
#include "DSeperateGrp.h"
#include "DSepGrpCst.h"
#include "DDelayedCst.h"
#include "DDelayedCstAll.h"
#include <filialpartner.h>
#include "DBranchInfo.h"
#include "DForbidden.h"
#include "DReserve.h"
#include "DReserveAnz.h"
#include "DAeSammelAuft.h"
#include "DOffenAuft.h"
#include "DCountrCodes.h"
#include "DDistressRouting.h"
#include "DVaVerbund.h"
#include <processcheck.h>
#include "DBeilage.h"
#include "DKommiChange.h"
#include "DUserInfo.h"
#include "DNewUserInfo.h"
#include "DEncloserTimes.h"
#include "DPromoQuota.h"
#include "DCollectiveOrders.h"
#include "DCollectiveOrdersDE.h"
#include "DOrderPeriod.h"
#include "DCremaMail.h"
#include "DNewCallback.h"
#include "DCstBranchInfoUpd.h"
#include "DSubTypeSettings.h"
#include "DCallbackRemarks.h"
#include "DCstTours.h"
#include "DddSpecialList.h"
#include "DExtraTourReasons.h"
#include "DAeCSVImport.h"
#include "ParameterChanges.h"


#define AEV_RR              1       //Timeridentifikation
#define AEV_MAIL            2       //Timeridentifikation
#define AEV_USER_INFO       3       //Timeridentifikation
#define AEV_USER_INFO_KILL  4       //Timeridentifikation
#define AEV_LOG_PARAM       5       //Timeridentifikation
#define AEV_AKT_ZEIT        180000  //3 Minuten

/////////////////////////////////////////////////////////////////////////////
// CAeView

IMPLEMENT_DYNCREATE(CAeView, CView)

CAeView::CAeView()
{
    m_bWithBrowse = false;
    m_pDlg = new CDRrMessage(this);
    m_pDlgMail = new CDMailMessage(this);
    m_pDlgUserInfo = new CDUserInfo(this);
}

CAeView::~CAeView()
{
    delete m_pDlg;  // löscht Fenster, falls nicht bereits geschehen
    delete m_pDlgMail;  // löscht Fenster, falls nicht bereits geschehen
    delete m_pDlgUserInfo;  // löscht Fenster, falls nicht bereits geschehen
}


BEGIN_MESSAGE_MAP(CAeView, CView)
    ON_WM_CONTEXTMENU()
    ON_COMMAND(ID_FILE_AUSW_FIL, OnFileAuswFil)
    ON_COMMAND(ID_INFORMATIONEN_KUNDENKONTAKTE, OnInformationenKundenkontakte)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_KUNDENKONTAKTE, OnUpdateInformationenKundenkontakte)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_COMMAND(ID_BROWSER_ZURCK, OnBrowserZurck)
    ON_UPDATE_COMMAND_UI(ID_BROWSER_ZURCK, OnUpdateBrowserZurck)
    ON_COMMAND(ID_BROWSER_HOME, OnBrowserHome)
    ON_UPDATE_COMMAND_UI(ID_BROWSER_HOME, OnUpdateBrowserHome)
    ON_COMMAND(ID_INFORMATIONEN_CALLBACK, OnInformationenCallback)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_CALLBACK, OnUpdateInformationenCallback)
    ON_COMMAND(ID_INFORMATIONEN_CALLBACK_DO, OnInformationenCallbackDo)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_CALLBACK_DO, OnUpdateInformationenCallbackDo)
    ON_WM_TIMER()
    ON_COMMAND(ID_INFORMATIONEN_VBLIEF, OnInformationenVblief)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_VBLIEF, OnUpdateInformationenVblief)
    ON_COMMAND(ID_AUFTRAG_VERBUND, OnAuftragVerbund)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_VERBUND, OnUpdateAuftragVerbund)
    ON_COMMAND(ID_AUFTRAG_DEFEKTE, OnAuftragDefekte)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_DEFEKTE, OnUpdateAuftragDefekte)
    ON_COMMAND(ID_ABSCHL_SPERRE, OnAbschlSperre)
    ON_UPDATE_COMMAND_UI(ID_ABSCHL_SPERRE, OnUpdateAbschlSperre)
    ON_COMMAND(ID_ABSCHL_SPERRE_WEG, OnAbschlSperreWeg)
    ON_UPDATE_COMMAND_UI(ID_ABSCHL_SPERRE_WEG, OnUpdateAbschlSperreWeg)
    ON_COMMAND(ID_MAIL_GROUPS, OnMailGroups)
    ON_UPDATE_COMMAND_UI(ID_MAIL_GROUPS, OnUpdateMailGroups)
    ON_COMMAND(ID_MAIL_NEW, OnMailNew)
    ON_UPDATE_COMMAND_UI(ID_MAIL_NEW, OnUpdateMailNew)
    ON_COMMAND(ID_MAIL_CONTROL, OnMailControl)
    ON_UPDATE_COMMAND_UI(ID_MAIL_CONTROL, OnUpdateMailControl)
    ON_COMMAND(ID_PFLEGE_KUNDE, OnPflegeKunde)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_KUNDE, OnUpdatePflegeKunde)
    ON_COMMAND(ID_PFLEGE_FEIERTAGE, OnPflegeFeiertage)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_FEIERTAGE, OnUpdatePflegeFeiertage)
    ON_COMMAND(ID_PFLEGE_TOUREN, OnPflegeTouren)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_TOUREN, OnUpdatePflegeTouren)
    ON_UPDATE_COMMAND_UI(ID_FILE_AUSW_FIL, OnUpdateFileAuswFil)
    ON_COMMAND(ID_PFLEGE_KUNDE_VBFILIALEN, OnPflegeKundeVbfilialen)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_KUNDE_VBFILIALEN, OnUpdatePflegeKundeVbfilialen)
    ON_COMMAND(ID_PFLEGE_INFOLISTE, OnPflegeInfoliste)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_INFOLISTE, OnUpdatePflegeInfoliste)
    ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
    ON_MESSAGE(WM_HELPHITTEST, OnHelpHitTest)
    ON_MESSAGE(WM_GOODBYE, OnGoodbye)
    ON_MESSAGE(WM_GOODBYEMAIL, OnGoodbyeMail)
    ON_MESSAGE(WM_KILLTIMER, OnKillTimer)
    ON_MESSAGE(WM_ACTTIMER, OnActTimer)
    ON_COMMAND(ID_FILE_AUSW_SPRACHE, OnFileAuswSprache)
    ON_UPDATE_COMMAND_UI(ID_FILE_AUSW_SPRACHE, OnUpdateFileAuswSprache)
    ON_COMMAND(ID_PFLEGE_TELEFONNR, OnPflegeTelefonnr)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_TELEFONNR, OnUpdatePflegeTelefonnr)
    ON_MESSAGE(WM_RENEW, OnReNew)
    ON_COMMAND(ID_PFLEGE_TOURSPERRE, OnPflegeToursperre)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_TOURSPERRE, OnUpdatePflegeToursperre)
    ON_COMMAND(ID_PFLEGE_QUOTA, OnPflegeQuota)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_QUOTA, OnUpdatePflegeQuota)
    ON_COMMAND(ID_PFLEGE_QUOTA_KLASSE, OnPflegeQuotaKlasse)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_QUOTA_KLASSE, OnUpdatePflegeQuotaKlasse)
    ON_COMMAND(ID_PFLEGE_QUOTA_INF, OnPflegeQuotaInf)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_QUOTA_INF, OnUpdatePflegeQuotaInf)
    ON_COMMAND(ID_PFLEGE_ARTIKEL, OnPflegeArtikel)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_ARTIKEL, OnUpdatePflegeArtikel)
    ON_COMMAND(ID_VERZ_KUNDE_EINZEL, OnVerzKundeEinzel)
    ON_UPDATE_COMMAND_UI(ID_VERZ_KUNDE_EINZEL, OnUpdateVerzKundeEinzel)
    ON_COMMAND(ID_VERZ_KUNDE_ALLE, OnVerzKundeAlle)
    ON_UPDATE_COMMAND_UI(ID_VERZ_KUNDE_ALLE, OnUpdateVerzKundeAlle)
    ON_COMMAND(ID_PFLEGE_BRANCHINFO, OnPflegeBranchinfo)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_BRANCHINFO, OnUpdatePflegeBranchinfo)
    ON_COMMAND(ID_PFLEGE_FORBIDDEN, OnPflegeForbidden)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_FORBIDDEN, OnUpdatePflegeForbidden)
    ON_COMMAND(ID_PFLEGE_RESERVE, OnPflegeReserve)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_RESERVE, OnUpdatePflegeReserve)
    ON_COMMAND(ID_INFORMATIONEN_RESERVIERT, OnInformationenReserviert)
    ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_RESERVIERT, OnUpdateInformationenReserviert)
    ON_COMMAND(ID_AUFTRAG_SAMMEL, OnAuftragSammel)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_SAMMEL, OnUpdateAuftragSammel)
    ON_COMMAND(ID_LISTEN_OFFENEAUFTR, OnListenOffeneauftr)
    ON_UPDATE_COMMAND_UI(ID_LISTEN_OFFENEAUFTR, OnUpdateListenOffeneauftr)
    ON_COMMAND(ID_PFLEGE_COUNTRYCODE, OnPflegeCountrycode)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_COUNTRYCODE, OnUpdatePflegeCountrycode)
    ON_COMMAND(ID_PFLEGE_NOTFALL, OnPflegeNotfall)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_NOTFALL, OnUpdatePflegeNotfall)
    ON_COMMAND(ID_PFLEGE_VA, OnPflegeVa)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_VA, OnUpdatePflegeVa)
    ON_COMMAND(ID_SEPERATERAUFTRAG_GENERELL, OnSeperaterauftragGenerell)
    ON_UPDATE_COMMAND_UI(ID_SEPERATERAUFTRAG_GENERELL, OnUpdateSeperaterauftragGenerell)
    ON_COMMAND(ID_SEPERATERAUFTRAG_KUNDENSPEZIFISCH, OnSeperaterauftragKundenspezifisch)
    ON_UPDATE_COMMAND_UI(ID_SEPERATERAUFTRAG_KUNDENSPEZIFISCH, OnUpdateSeperaterauftragKundenspezifisch)
    ON_COMMAND(ID_PFLEGE_ARTIKEL_VBFILIALEN, OnPflegeArtikelVbfilialen)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_ARTIKEL_VBFILIALEN, OnUpdatePflegeArtikelVbfilialen)
    ON_COMMAND(ID_PFLEGE_QUOTA_EKG, OnPflegeQuotaEkg)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_QUOTA_EKG, OnUpdatePflegeQuotaEkg)
    ON_COMMAND(ID_PFLEGE_RESERVE_PCT, OnPflegeReservePct)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_RESERVE_PCT, OnUpdatePflegeReservePct)
    ON_COMMAND(ID_PFLEGE_RESERVE_ABS, OnPflegeReserveAbs)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_RESERVE_ABS, OnUpdatePflegeReserveAbs)
    ON_COMMAND(ID_PFLEGE_BEILAGE, OnPflegeBeilage)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_BEILAGE, OnUpdatePflegeBeilage)
    ON_COMMAND(ID_PFLEGE_QUOTA_KND_EKG, OnPflegeQuotaKndEkg)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_QUOTA_KND_EKG, OnUpdatePflegeQuotaKndEkg)
    ON_COMMAND(ID_PFLEGE_RESERVE_ZERTIFIKAT, OnPflegeReserveZert)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_RESERVE_ZERTIFIKAT, OnUpdatePflegeReserveZert)
    ON_COMMAND(ID_PFLEGE_RESERVE_BPZ, OnPflegeReserveBPZ)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_RESERVE_BPZ, OnUpdatePflegeReserveBPZ)
    ON_COMMAND(ID_BEARB_KOMMI_CHANGE, OnBearbKommiChange)
    ON_UPDATE_COMMAND_UI(ID_BEARB_KOMMI_CHANGE, OnUpdateBearbKommiChange)
    ON_COMMAND(ID_MAIL_BROADCAST, OnUserInfo)
    ON_UPDATE_COMMAND_UI(ID_MAIL_BROADCAST, OnUpdateUserInfo)
    ON_COMMAND(ID_PFLEGE_ENCLOSER, OnPflegeEncloser)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_ENCLOSER, OnUpdatePflegeEncloser)
    ON_COMMAND(ID_LISTEN_PROMOQUOTA, OnListenPromoquota)
    ON_UPDATE_COMMAND_UI(ID_LISTEN_PROMOQUOTA, OnUpdateListenPromoquota)
    ON_COMMAND(ID_AUFTRAG_COLLECTIVORDERSANZEIGEN, OnAuftragCollectivordersanzeigen)
    ON_UPDATE_COMMAND_UI(ID_AUFTRAG_COLLECTIVORDERSANZEIGEN, OnUpdateAuftragCollectivordersanzeigen)
    ON_COMMAND(ID_PFLEGE_RESERVE_CHARGE, OnPflegeReserveCharge)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_RESERVE_CHARGE, OnUpdatePflegeReserveCharge)
    ON_COMMAND(ID_EXTRAS_SCHRIFT, OnExtrasSchrift)
    ON_UPDATE_COMMAND_UI(ID_EXTRAS_SCHRIFT, OnUpdateExtrasSchrift)
    ON_COMMAND(ID_PFLEGE_BESTELLFENSTERPFLEGEN, OnBestellfensterPflegen)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_BESTELLFENSTERPFLEGEN, OnUpdateBestellfensterPflegen)
    ON_COMMAND(ID_PFLEGE_CSTBRANCHINFO, OnPflegeCstbranchinfo)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_CSTBRANCHINFO, OnUpdatePflegeCstbranchinfo)
    ON_COMMAND(ID_PFLEGE_ORIGINTYPESETTINGS, OnPflegeOrigintypesettings)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_ORIGINTYPESETTINGS, OnUpdatePflegeOrigintypesettings)
    ON_COMMAND(ID_PFLEGE_CREMA_RECIPIENT_MAIL, OnPflegeCremaRecipientMail)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_CREMA_RECIPIENT_MAIL, OnUpdatePflegeCremaRecipientMail)
    ON_COMMAND(ID_PFLEGE_CB_REMARKS, &CAeView::OnPflegeCbRemarks)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_CB_REMARKS, &CAeView::OnUpdatePflegeCbRemarks)
    ON_COMMAND(ID_PFLEGE_BEARBEITENKUNDENTOUREN, &CAeView::OnPflegeBearbeitenkundentouren)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_BEARBEITENKUNDENTOUREN, &CAeView::OnUpdatePflegeBearbeitenkundentouren)
    ON_COMMAND(ID_VERZ_SPECIAL, &CAeView::OnVerzSpecial)
    ON_UPDATE_COMMAND_UI(ID_VERZ_SPECIAL, &CAeView::OnUpdateVerzSpecial)
    ON_COMMAND(ID_PFLEGE_EXTRATOURREASONS, &CAeView::OnPflegeExtratourreasons)
    ON_UPDATE_COMMAND_UI(ID_PFLEGE_EXTRATOURREASONS, &CAeView::OnUpdatePflegeExtratourreasons)
        ON_COMMAND(ID_AUFTRAG_CSV_IMPORT, &CAeView::OnAuftragCsvImport)
        ON_UPDATE_COMMAND_UI(ID_AUFTRAG_CSV_IMPORT, &CAeView::OnUpdateAuftragCsvImport)
        ON_COMMAND(ID_VIEW_NO_CRITICS, &CAeView::OnViewNoCritics)
        ON_UPDATE_COMMAND_UI(ID_VIEW_NO_CRITICS, &CAeView::OnUpdateViewNoCritics)
        ON_COMMAND(ID_VIEW_NO_BRANCHINFO, &CAeView::OnViewNoBranchinfo)
        ON_UPDATE_COMMAND_UI(ID_VIEW_NO_BRANCHINFO, &CAeView::OnUpdateViewNoBranchinfo)
        ON_COMMAND(ID_INFORMATIONEN_SHOW_PARA_CHANGE, &CAeView::OnInformationenShowParaChange)
        ON_UPDATE_COMMAND_UI(ID_INFORMATIONEN_SHOW_PARA_CHANGE, &CAeView::OnUpdateInformationenShowParaChange)
        END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAeView drawing

void CAeView::OnDraw(CDC* pDC)
{
    if (m_bWithBrowse)
    {
        CView::OnDraw(pDC);
        return;
    }

    //Hintergrundfarbe erhalten
    pDC->SetBkMode(::GetSysColor(COLOR_WINDOW));
    //Koordinatensystem festlegen
    pDC->SetMapMode(MM_ISOTROPIC); //Aspect 1:1
    CRect rect;
    GetClientRect(rect);

    //Korrektur für Abweichungen vom Quadrat
    if (rect.right > rect.bottom)
    {
        int d = (rect.right - rect.bottom) / 2;
        rect.left += d;
        rect.right -= d;
    }

    else
    {
        int d = (rect.bottom - rect.right) / 2;
        rect.top += d;
        rect.bottom -= d;
    }

    pDC->SetWindowOrg(0, 0);
    pDC->SetWindowExt(1000, 1000);
    pDC->SetViewportOrg(rect.left, rect.top);
    pDC->SetViewportExt(rect.Width(), rect.Height());

    /*******************************************************************************
        HAGEDA
    *******************************************************************************/
    if (AeGetApp()->VzNr() == 21)
    {
        //Schwarzen Kreis in die Mitte
        CPen MyPen (PS_SOLID, 3, RGB(0, 0, 0));
        CPen* pOldPen = pDC->SelectObject(&MyPen);

        //Schrift HAGEDA in rot darüber
        CFont BoldFont;
        BoldFont.CreateFont(150, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, ANSI_CHARSET,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_ROMAN, NULL);
        CFont* pOldFont = pDC->SelectObject(&BoldFont);
        pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
        pDC->SetTextColor(RGB(255, 0, 0));
        int dxWidth[] = {90, 90, 90, 90, 90, 90};
        pDC->ExtTextOut(500, 350, ETO_OPAQUE, CRect(0, 0, 0, 0), "hageda", 6, dxWidth);
        int dxWidth2[] = {70, 70, 90, 120, 90, 90};
        pDC->ExtTextOut(500, 500, ETO_OPAQUE, CRect(0, 0, 0, 0), "stumpf", 6, dxWidth2);

        //"Auftragserfassungssystem"
        CFont OLFont;
        OLFont.CreateFont(135, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, ANSI_CHARSET,
                          OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                          DEFAULT_PITCH | FF_ROMAN, NULL);
        pDC->SelectObject(&OLFont)->DeleteObject();
        pDC->SetTextColor(RGB(0, 0, 0));
        pDC->TextOut(500, 800, CResString::ex().getStrTblText(AETXT_AUFTRAGSERF_SYSTEM));

        //Name der Niederlassung
        CFont ThinFont;
        CString FilialName = AeGetApp()->FilialName();
        ThinFont.CreateFont(80, 0, 0, 0, FW_LIGHT, 0, 0, 0, ANSI_CHARSET,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_ROMAN, NULL);
        pDC->SelectObject(&ThinFont)->DeleteObject();
        pDC->TextOut(500, 950, FilialName);

        //Name und Ort der Apotheke von HiPath
        if (AeGetApp()->m_ProCenter.GetHiPathKndNr() != 0)
        {
            CFont SemiboldFont;
            CString cApotheke = AeGetApp()->ApothekeName();
            SemiboldFont.CreateFont(30, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, ANSI_CHARSET,
                                    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                    DEFAULT_PITCH | FF_ROMAN, NULL);
            pDC->SetTextColor(RGB(0, 0, 255));
            pDC->SelectObject(&SemiboldFont)->DeleteObject();
            pDC->TextOut(500, 80, cApotheke);
        }

        CString FilName;
        FilName.Format("HAGEDA-STUMPF-AE %s", FilialName.GetString());
        AeGetApp()->m_pMainWnd->SetWindowText(FilName);
        //Werkzeuge freigeben
        pDC->SelectObject(pOldPen)->DeleteObject();
        pDC->SelectObject(pOldFont)->DeleteObject();
    }

    /*******************************************************************************
        PHOENIX
    *******************************************************************************/
    else
    {
        // bulgarisch? -> RUSSIAN_CHARSET
        BYTE charset = (AeGetApp()->Modus() == 1) ? RUSSIAN_CHARSET : ANSI_CHARSET;

        //Schwarzen Kreis in die Mitte
        CPen MyPen (PS_SOLID, 3, RGB(0, 0, 0));
        CPen* pOldPen = pDC->SelectObject(&MyPen);

        //Schrift PHOSIX in grün darüber
        CFont BoldFont;
        BoldFont.CreateFont(150, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, charset,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_ROMAN, NULL);
        CFont* pOldFont = pDC->SelectObject(&BoldFont);
        pDC->SetTextAlign(TA_CENTER | TA_BOTTOM);
        pDC->SetTextColor(RGB(49, 142, 96));
        int dxWidth[] = {110, 130, 130, 120, 120, 80, 100};
        CString csFirma = CResString::ex().getStrTblText(AETXT_PHOENIX_KURZ);
        int iLen = csFirma.GetLength();
        pDC->ExtTextOut(500, 400, ETO_OPAQUE, CRect(0, 0, 0, 0), csFirma, iLen, dxWidth);

        //"Auftragserfassungssystem"
        CFont OLFont;
        OLFont.CreateFont(135, 0, 0, 0, FW_EXTRABOLD, 0, 0, 0, charset,
                          OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                          DEFAULT_PITCH | FF_ROMAN, NULL);
        pDC->SelectObject(&OLFont)->DeleteObject();
        pDC->SetTextColor(RGB(0, 0, 0));
        pDC->TextOut(500, 800, CResString::ex().getStrTblText(AETXT_AUFTRAGSERF_SYSTEM));

        //Name der Niederlassung
        CFont ThinFont;
        CString FilialName = AeGetApp()->FilialName();
        ThinFont.CreateFont(80, 0, 0, 0, FW_LIGHT, 0, 0, 0, charset,
                            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_ROMAN, NULL);
        pDC->SelectObject(&ThinFont)->DeleteObject();
        pDC->TextOut(500, 950, FilialName);

        //Name und Ort der Apotheke von HiPath
        if (AeGetApp()->m_ProCenter.GetHiPathKndNr() != 0)
        {
            CFont SemiboldFont;
            CString cApotheke = AeGetApp()->ApothekeName();
            SemiboldFont.CreateFont(50, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0, charset,
                                    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                                    DEFAULT_PITCH | FF_ROMAN, NULL);
            pDC->SetTextColor(RGB(0, 0, 255));
            pDC->SelectObject(&SemiboldFont)->DeleteObject();
            cApotheke.TrimRight();
            pDC->TextOut(1, 80, cApotheke);
            cApotheke = AeGetApp()->Ort();
            cApotheke.TrimRight();
            pDC->TextOut(1, 140, cApotheke);
        }

        CString FilName;
        FilName.Format("PHOENIX-AE %s", FilialName.GetString());
        AeGetApp()->m_pMainWnd->SetWindowText(FilName);
        //Werkzeuge freigeben
        pDC->SelectObject(pOldPen)->DeleteObject();
        pDC->SelectObject(pOldFont)->DeleteObject();
    }
}

/////////////////////////////////////////////////////////////////////////////
// CAeView diagnostics

#ifdef _DEBUG
void CAeView::AssertValid() const
{
    CView::AssertValid();
}

void CAeView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAeView message handlers

void CAeView::OnContextMenu(CWnd*, CPoint point)
{
    // CG: This function was added by the Pop-up Menu component

    CMenu menu;
    VERIFY(menu.LoadMenu(CG_IDR_POPUP_AE_VIEW));

    CMenu* pPopup = menu.GetSubMenu(0);
    ASSERT(pPopup != NULL);

    CWnd* pWndPopupOwner = this;

    while (pWndPopupOwner->GetStyle() & WS_CHILD)
    {
        pWndPopupOwner = pWndPopupOwner->GetParent();
    }

    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
                           pWndPopupOwner);
}

BOOL CAeView::PreTranslateMessage(MSG* pMsg)
{
    // CG: This block was added by the Pop-up Menu component
    {
        // Shift+F10: show pop-up menu.
        if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) && // If we hit a key and
                (pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||  // it's Shift+F10 OR
                (pMsg->message == WM_CONTEXTMENU))                                  // Natural keyboard key
        {
            CRect rect;
            GetClientRect(rect);
            ClientToScreen(rect);

            CPoint point = rect.TopLeft();
            point.Offset(5, 5);
            OnContextMenu(NULL, point);

            return TRUE;
        }
    }

    return CView::PreTranslateMessage(pMsg);
}

LRESULT CAeView::OnCommandHelp(WPARAM /*wParam*/, LPARAM lParam)
{
    if (lParam == 0)
    {
        lParam = HID_BASE_RESOURCE + IDR_AETYPE;
    }

    AfxGetApp()->WinHelp(lParam);
    return TRUE;
}

LRESULT CAeView::OnHelpHitTest(WPARAM /*wParam*/, LPARAM lParam)
{
    if (LOWORD(lParam) > 10)
    {
        MessageBeep(MB_OK);    //nase Spaßanwendung
    }

    return HID_BASE_RESOURCE + IDR_AETYPE ;
}

void CAeView::OnFileAuswFil()
{
    CDAendFil dlgAendFil;
    dlgAendFil.DoModal();
    Invalidate();
}

void CAeView::OnUpdateFileAuswFil(CCmdUI* pCmdUI)
{
    if (!GetAeUser().ChangeFiliale())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnInformationenKundenkontakte()
{
    CDKritik dlgKritik;
    dlgKritik.DoModal();
}

void CAeView::OnUpdateInformationenKundenkontakte(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

int CAeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
    {
        return -1;
    }

    SetTimer(AEV_RR, AEV_AKT_ZEIT , NULL);
    SetTimer(AEV_USER_INFO, AEV_AKT_ZEIT , NULL);
    SetTimer(AEV_MAIL, 1000 , NULL);
    SetTimer(AEV_LOG_PARAM, AEV_AKT_ZEIT, NULL);
    m_bWithBrowse = false;
    return 0;
}

void CAeView::OnSize(UINT nType, int cx, int cy)
{
    CView::OnSize(nType, cx, cy);

    if (m_bWithBrowse)
    {
        CRect rectClient;
        GetClientRect(rectClient);
    }
}

void CAeView::OnBrowserZurck()
{
    //m_Browser.GoBack();
}

void CAeView::OnUpdateBrowserZurck(CCmdUI* pCmdUI)
{
    if (!m_bWithBrowse)
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnBrowserHome()
{
    //m_Browser.Navigate("http://129.10.56.1/AnwDokuAe/Ae501.htm", NULL, NULL, NULL, NULL);
}

void CAeView::OnUpdateBrowserHome(CCmdUI* pCmdUI)
{
    if (!m_bWithBrowse)
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnInformationenCallback()
{
    CString CStr;
    CDKndWahl dlgKndWahl;

    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }

    CPARAUFBEARB paraaufbearb;
    paraaufbearb.s.FILIALNR = dlgKndWahl.GetKndVz();
    paraaufbearb.Server( AafilSelaufbearb );

    AeGetApp()->IsNewCallback = (paraaufbearb.s.SWNEWCALLBACK == 1);

    if (!AeGetApp()->IsNewCallback())
    {
        CDCallbackItem dlgCallbackItem;
        dlgCallbackItem.m_lIdf = dlgKndWahl.GetKndNr();
        dlgCallbackItem.m_sVz = dlgKndWahl.GetKndVz();
        dlgCallbackItem.DoModal();
    }
    else
    {
        CDNewCallback dlgNewCallback;
        dlgNewCallback.m_lIdf = dlgKndWahl.GetKndNr();
        dlgNewCallback.m_sBranchno = dlgKndWahl.GetKndVz();
        dlgNewCallback.DoModal();
    }

    AeGetApp()->IsNewCallback = AeGetApp()->IsNewCallbackHome();

}

void CAeView::OnUpdateInformationenCallback(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnInformationenCallbackDo()
{
    CDCallbackFetch dlgCallbackFetch;
    KillTimer(AEV_RR);
    dlgCallbackFetch.DoModal();
    SetTimer(AEV_RR, AEV_AKT_ZEIT , NULL);
}

void CAeView::OnUpdateInformationenCallbackDo(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnTimer(UINT nIDEvent)
{
    if (nIDEvent == AEV_RR)
    {
        if (!AeGetApp()->IsRRMeld())
        {
            return;
        }

        if (AeGetApp()->IsNewCallback())
        {
            CCALLBACKTODONEW todonew;
            todonew.SetFilialnr( AeGetApp()->VzNr() );
            todonew.SetVertriebszentrumnr( AeGetApp()->VzNr() );
            todonew.SetRegionnr( AeGetApp()->VzNr() );
            todonew.SetUid(GetAeUser().GetUID());

            if (AeGetApp()->IsKundeHome())
            {
                todonew.SelCallbackOpenVz(1);
            }
            else
            {
                todonew.SelCallbackOpen(1);
            }

            if (todonew.rc == SRV_SQLNOTFOUND)
            {
                if (AeGetApp()->IsKundeHome())
                {
                    todonew.SelCallbackOpenVz(0);
                }
                else
                {
                    todonew.SelCallbackOpen(0);
                }

                SetTimer(AEV_RR, AEV_AKT_ZEIT, NULL);
                return;
            }

            if (AeGetApp()->IsKundeHome())
            {
                todonew.SelCallbackOpenVz(0);
            }
            else
            {
                todonew.SelCallbackOpen(0);
            }
        }
        else
        {
            CCALLBACKTODO todo;
            todo.SetFilialnr( AeGetApp()->VzNr() );
            todo.SetVertriebszentrumnr( AeGetApp()->VzNr() );
            todo.SetRegionnr( AeGetApp()->VzNr() );
            todo.SetUid(GetAeUser().GetUID());

            if (AeGetApp()->IsKundeHome())
            {
                todo.SelCallbackOpenVz(1);
            }
            else
            {
                todo.SelCallbackOpen(1);
            }

            if (todo.rc == SRV_SQLNOTFOUND)
            {
                if (AeGetApp()->IsKundeHome())
                {
                    todo.SelCallbackOpenVz(0);
                }
                else
                {
                    todo.SelCallbackOpen(0);
                }

                SetTimer(AEV_RR, AEV_AKT_ZEIT, NULL);
                return;
            }

            if (AeGetApp()->IsKundeHome())
            {
                todo.SelCallbackOpenVz(0);
            }
            else
            {
                todo.SelCallbackOpen(0);
            }
        }

        KillTimer(nIDEvent);

        // Dialogfeld erstellen, sofern nicht vorhanden
        if (m_pDlg->GetSafeHwnd() == 0)
        {
            m_pDlg->Create();   // Dialogfeld anzeigen
        }
    }
    else if (nIDEvent == AEV_USER_INFO)
    {
        CUSERINFORMATION userinfo;

        userinfo.SetValidbranchno((GetAeUser().GetUser()).FILIALNR);
        userinfo.SelInfo();

        if (userinfo.rc != SRV_OK)
        {
            userinfo.CloseCursor(0);
            SetTimer(AEV_USER_INFO_KILL, AEV_AKT_ZEIT, NULL);
            return;
        }

        userinfo.CloseCursor(0);
        KillTimer(nIDEvent);
        // Dialogfeld erstellen, sofern nicht vorhanden
        CWnd* pActive = GetActiveWindow();

        if (m_pDlgUserInfo->GetSafeHwnd() == 0)
        {
            ppString text;
            long acttime = AeGetApp()->GetCurrentTime();
            long totime = userinfo.GetValidtimeto();
            long actsec = acttime % 100
                          + acttime / 100 % 100 * 60
                          + acttime / 10000 * 3600;
            long tosec = totime % 100
                         + totime / 100 % 100 * 60
                         + totime / 10000 * 3600;
            long diff = tosec - actsec;

            if (diff < 0)
            {
                diff = 10;
            }

            diff *= 1000;   //in millisecunden
            SetTimer(AEV_USER_INFO_KILL, diff , NULL);

            m_pDlgUserInfo->m_cUserInfo = userinfo.GetInfomessage(text);
            m_pDlgUserInfo->m_sPrio = userinfo.GetPriority();
            m_pDlgUserInfo->Create();   // Dialogfeld anzeigen
        }

        if (pActive != NULL)
        {
            pActive->SetActiveWindow();
        }
    }
    else if (nIDEvent == AEV_USER_INFO_KILL)
    {
        m_pDlgUserInfo->DestroyWindow();    // kein Problem, falls Fenster schon gelöscht
        KillTimer(nIDEvent);
        SetTimer(AEV_USER_INFO, AEV_AKT_ZEIT , NULL);
    }
    else if (nIDEvent == AEV_LOG_PARAM)
    {
        CPARAMETER para;        //Loglevel einlesen
        para.SetFilialnr(0);    //momentan filialunabhängig
        para.SetProgrammname("KSC");
        para.SetZweck("TRACE");
        para.SetParametername("LOGGING");
        if (!para.SelParameter())
        {
            AeGetApp()->m_AeLogging.SetLoggingLevel((short)para.GetWert());
        }
        KillTimer(nIDEvent);
        SetTimer(AEV_LOG_PARAM, AEV_AKT_ZEIT, NULL);
    }
    else
    {
        CMAILITEMS todo;

        todo.SetUid(GetAeUser().GetUID());
        todo.SetFilialnr((GetAeUser().GetUser()).FILIALNR);
        todo.SelOpenNews();

        if (todo.rc != SRV_OK)
        {
            todo.CloseCursor(0);
            SetTimer(AEV_MAIL, AEV_AKT_ZEIT, NULL);
            return;
        }

        todo.CloseCursor(0);
        KillTimer(nIDEvent);

        // Dialogfeld erstellen, sofern nicht vorhanden
        if (m_pDlgMail->GetSafeHwnd() == 0)
        {
            m_pDlgMail->m_lUid = todo.GetUid();
            m_pDlgMail->m_iFilialnr = todo.GetFilialnr();
            m_pDlgMail->m_lNewsno = todo.GetNewsno();
            m_pDlgMail->Create();   // Dialogfeld anzeigen
        }
    }

    CView::OnTimer(nIDEvent);
}

LRESULT CAeView::OnGoodbye(WPARAM wParam, LPARAM /*lParam*/)
{
    // Nachricht wird durch Schaltflächen OK und Abbrechen
    // des nichtmodalen Dialogfelds ausgelöst
    m_pDlg->DestroyWindow();    // kein Problem, falls Fenster schon gelöscht

    if (wParam == IDOK)
    {
        CDCallbackFetch dlgCallbackFetch;
        dlgCallbackFetch.DoModal();
    }

    SetTimer(AEV_RR, AEV_AKT_ZEIT , NULL);
    return 0L;
}

LRESULT CAeView::OnGoodbyeMail(WPARAM wParam, LPARAM /*lParam*/)
{
    // Nachricht wird durch Schaltflächen OK und Abbrechen
    // des nichtmodalen Dialogfelds ausgelöst
    m_pDlgMail->DestroyWindow();    // kein Problem, falls Fenster schon gelöscht

    if (wParam == IDOK)
    {
        SetTimer(AEV_MAIL, 500 , NULL);
    }
    else
    {
        SetTimer(AEV_MAIL, AEV_AKT_ZEIT , NULL);
    }

    return 0L;
}

LRESULT CAeView::OnKillTimer(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    // Nachricht wird beim Wechseln der
    // Filiale vor Closeasserver ausgelöst
    KillTimer(AEV_RR);
    KillTimer(AEV_MAIL);
    KillTimer(AEV_USER_INFO);
    KillTimer(AEV_USER_INFO_KILL);
    return 0L;
}

LRESULT CAeView::OnActTimer(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    // Nachricht wird beim Wechseln der
    // Filiale nach Openasserver ausgelöst
    SetTimer(AEV_MAIL, AEV_AKT_ZEIT , NULL);
    SetTimer(AEV_USER_INFO, AEV_AKT_ZEIT , NULL);
    SetTimer(AEV_RR, AEV_AKT_ZEIT , NULL);
    return 0L;
}

void CAeView::OnInformationenVblief()
{
    CDVbLief dlgVbLief;
    dlgVbLief.DoModal();
}

void CAeView::OnUpdateInformationenVblief(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnAuftragVerbund()
{
    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.DoModal();
}

void CAeView::OnUpdateAuftragVerbund(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnAuftragDefekte()
{
    CDVbBuchen dlgVbBuchen;
    dlgVbBuchen.m_ifunktion = 1;  // Erstellen Auftrag aus Defekten
    dlgVbBuchen.DoModal();
}

void CAeView::OnUpdateAuftragDefekte(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnAbschlSperre()
{
    CString CStr;
    CAUFIE aufie;
    aufie.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    aufie.s.ANZ_IE = 0; // Sperren ae für neue Aufträge
    aufie.Server(AaauftSperr_auft);

    if (aufie.rc == SRV_OK && aufie.s.ANZ_IE > 0)
    {
        CStr.Format(CResString::ex().getStrTblText(IDS_X_AUFTR_IN_ERF), aufie.s.ANZ_IE);
        MsgBoxOK(CStr);
    }
}

void CAeView::OnUpdateAbschlSperre(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsSperreAe())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnAbschlSperreWeg()
{
    CAUFIE aufie;
    aufie.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    aufie.s.ANZ_IE = 1; // wieder freigeben ae für neue Aufträge
    aufie.Server(AaauftSperr_auft);
}

void CAeView::OnUpdateAbschlSperreWeg(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsSperreAe())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnMailGroups()
{
    CDAeMailUser dlgAeMailUser;
    dlgAeMailUser.DoModal();
}

void CAeView::OnUpdateMailGroups(CCmdUI* pCmdUI)
{
    if (!GetAeUser().UpdMailUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnMailNew()
{
    CDMailNew dlgMailNew;
    dlgMailNew.DoModal();
}

void CAeView::OnUpdateMailNew(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsMessage())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnMailControl()
{
    CDMailControl dlgMailControl;
    dlgMailControl.DoModal();
}

void CAeView::OnUpdateMailControl(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsMessage())
    {
        pCmdUI->Enable(FALSE);
    }
}


void CAeView::OnPflegeKunde()
{
    CCUCustomerTimes dlgCustomerTimes;
    dlgCustomerTimes.DoModal();
}

void CAeView::OnUpdatePflegeKunde(CCmdUI* pCmdUI)
{
    if (!GetAeUser().UpdKndAufArt())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeFeiertage()
{
    CDChooseFiliale dlgChooseFiliale;
    CDAeAnzFeiertage dlgAeAnzFeiertage;

    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }

    dlgAeAnzFeiertage.SetVzNr(dlgChooseFiliale.m_FilialNr);
    dlgAeAnzFeiertage.DoModal();
}

void CAeView::OnUpdatePflegeFeiertage(CCmdUI* pCmdUI)
{
    if (!GetAeUser().Feiertage())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeTouren()
{
    CDTourAnz dlgTourAnz;
    dlgTourAnz.DoModal();
}

void CAeView::OnUpdatePflegeTouren(CCmdUI* pCmdUI)
{
    if (!GetAeUser().UpdKndAufArt())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeKundeVbfilialen()
{
    CDAeKundeVerbundFiliale dlgAeKundeVerbundFiliale;
    dlgAeKundeVerbundFiliale.DoModal();
}

void CAeView::OnUpdatePflegeKundeVbfilialen(CCmdUI* pCmdUI)
{
//  pCmdUI->Enable(FALSE);
    if (!GetAeUser().UpdKndAufArt())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeInfoliste()
{
    CDTelListUpd dlgTelListUpd;
    dlgTelListUpd.DoModal();
}

void CAeView::OnUpdatePflegeInfoliste(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsInfoPflege())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnFileAuswSprache()
{
    CString woher;
    woher = "CAeView::OnFileAuswSprache";
    CDSprachAuswahl dlgSprachAuswahl;
    CString csSprache;
    AeGetApp()->m_ProCenter.SetUserAtWork(woher, TRUE);
    csSprache = AeGetApp()->Language();
    dlgSprachAuswahl.DoModal();

    if (csSprache != AeGetApp()->Language())
    {
        AeGetApp()->ReInitDoc();
        AeGetApp()->InitOtherViews();

        CLGTEXT texte;
        texte.SetLgid(AeGetApp()->Language());
        texte.SetLanguage();
    }

    AeGetApp()->Modus = (csSprache == "BG" ? 1 : 0);

    AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
}

void CAeView::OnUpdateFileAuswSprache(CCmdUI* /*pCmdUI*/)
{
}

void CAeView::OnPflegeTelefonnr()
{
    CDTelNr dlgTelNr;
    dlgTelNr.DoModal();
}

void CAeView::OnUpdatePflegeTelefonnr(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

LRESULT CAeView::OnReNew(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
    Invalidate();
    UpdateWindow();
    return 0L;
}

void CAeView::OnPflegeToursperre()
{
    CString woher;
    woher = "CAeView::OnPflegeToursperre";
    CDTourSperr dlgTourSperr;
    AeGetApp()->m_ProCenter.SetUserAtWork(woher, TRUE);
    dlgTourSperr.DoModal();
    AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
}

void CAeView::OnUpdatePflegeToursperre(CCmdUI* pCmdUI)
{
    if (!GetAeUser().UpdKndAufArt())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeQuota()
{
    CDArtikelQuota dlgArtikelQuota;
    dlgArtikelQuota.DoModal();
}

void CAeView::OnUpdatePflegeQuota(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeQuota())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeQuotaKlasse()
{
    CDQuotaKlasse dlgQuotaKlasse;
    dlgQuotaKlasse.DoModal();
}

void CAeView::OnUpdatePflegeQuotaKlasse(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeQuota())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeQuotaInf()
{
    CDQuotaSum dlgQuotaSum;
    dlgQuotaSum.DoModal();
}

void CAeView::OnUpdatePflegeQuotaInf(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeQuota())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeArtikel()
{
    CDDelayedArt dlgDelayedArt;
    dlgDelayedArt.DoModal();
}

void CAeView::OnUpdatePflegeArtikel(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeDD())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnVerzKundeEinzel()
{
    CDDelayedCst dlgDelayedCst;
    dlgDelayedCst.DoModal();
}

void CAeView::OnUpdateVerzKundeEinzel(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeDD() || AeGetApp()->UseTourManagerCst() == 2)
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnVerzKundeAlle()
{
    CDDelayedCstAll dlgDelayedCstAll;
    dlgDelayedCstAll.DoModal();
}

void CAeView::OnUpdateVerzKundeAlle(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeDD() || AeGetApp()->UseTourManagerCst() == 2)
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeBranchinfo()
{
    CDBranchInfo dlgBranchInfo;
    dlgBranchInfo.DoModal();
}

void CAeView::OnUpdatePflegeBranchinfo(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeBranchInfo())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeForbidden()
{
    CDForbidden dlgForbidden;
    dlgForbidden.DoModal();
}

void CAeView::OnUpdatePflegeForbidden(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeForbidden())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeReserve()
{
    CDReserve dlgReserve;
    dlgReserve.DoModal();
}

void CAeView::OnUpdatePflegeReserve(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeReserve())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnInformationenReserviert()
{
    CDReserveAnz dlgReserveAnz;
    dlgReserveAnz.DoModal();
}

void CAeView::OnUpdateInformationenReserviert(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeReserve())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnAuftragSammel()
{
    CDAeSammelAuft dlgAeSammelAuft;
    dlgAeSammelAuft.DoModal();
}

void CAeView::OnUpdateAuftragSammel(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser() || GetAeUser().KeinPlan())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnListenOffeneauftr()
{
    CDOffenAuft dlgOffenAuft;
    dlgOffenAuft.DoModal();
}

void CAeView::OnUpdateListenOffeneauftr(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeCountrycode()
{
    CDCountrCodes dlgCountrCodes;
    dlgCountrCodes.DoModal();
}

void CAeView::OnUpdatePflegeCountrycode(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeCountry())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeNotfall()
{
    CDDistressRouting dlgDistressRouting;
    dlgDistressRouting.DoModal();
}

void CAeView::OnUpdatePflegeNotfall(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeNotfall())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeVa()
{
    CDVaVerbund dlgVaVerbund;
    dlgVaVerbund.DoModal();
}

void CAeView::OnUpdatePflegeVa(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeVAIdf())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnSeperaterauftragGenerell()
{
    CDSeperateGrp dlgSeperateGrp;
    dlgSeperateGrp.DoModal();
}

void CAeView::OnUpdateSeperaterauftragGenerell(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeSeparat())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnSeperaterauftragKundenspezifisch()
{
    CDSepGrpCst dlgSepGrpCst;
    dlgSepGrpCst.DoModal();
}

void CAeView::OnUpdateSeperaterauftragKundenspezifisch(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeSeparat())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeArtikelVbfilialen()
{
    CDAeArtVerbundFiliale dlgAeArtVerbundFiliale;
    dlgAeArtVerbundFiliale.DoModal();
}

void CAeView::OnUpdatePflegeArtikelVbfilialen(CCmdUI* pCmdUI)
{
    if (!GetAeUser().UpdKndAufArt())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeQuotaEkg()
{
    CDArtikelQuota dlgArtikelQuota;
    dlgArtikelQuota.m_bEKG = TRUE;
    dlgArtikelQuota.DoModal();
}

void CAeView::OnUpdatePflegeQuotaEkg(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeQuota())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeReservePct()
{
    CDReserve dlgReserve;
    dlgReserve.DoModal();
}

void CAeView::OnUpdatePflegeReservePct(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeReserve())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeReserveAbs()
{
    CDReserve dlgReserve;
    dlgReserve.m_Funktion = 1;
    dlgReserve.DoModal();
}

void CAeView::OnUpdatePflegeReserveAbs(CCmdUI* pCmdUI)
{
//  pCmdUI->Enable(FALSE);
    if (!GetAeUser().IsPflegeReserve())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeBeilage()
{
    CDBeilage dlgBeilage;
    dlgBeilage.DoModal();
}

void CAeView::OnUpdatePflegeBeilage(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsBeilageUp())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeQuotaKndEkg()
{
    CDQuotaKlasse dlgQuotaKlasse;
    dlgQuotaKlasse.m_iFunktion = 1;
    dlgQuotaKlasse.DoModal();
}

void CAeView::OnUpdatePflegeQuotaKndEkg(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeQuota())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeReserveZert()
{
    CDReserve dlgReserve;
    dlgReserve.m_Funktion = 3;
    dlgReserve.DoModal();
}

void CAeView::OnUpdatePflegeReserveZert(CCmdUI* pCmdUI)
{
//  pCmdUI->Enable(FALSE);
    if (!GetAeUser().IsPflegeReserveZert())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeReserveBPZ()
{
    CDReserve dlgReserve;
    dlgReserve.m_Funktion = 4;
    dlgReserve.DoModal();
}

void CAeView::OnUpdatePflegeReserveBPZ(CCmdUI* pCmdUI)
{
//  pCmdUI->Enable(FALSE);
    if (!GetAeUser().IsPflegeReserveBPZ())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnBearbKommiChange()
{
    CDKommiChange dlgKommiChange;
    dlgKommiChange.DoModal();
}

void CAeView::OnUpdateBearbKommiChange(CCmdUI* pCmdUI)
{
//  pCmdUI->Enable(FALSE);
    if (!GetAeUser().IsAeUser() && !GetAeUser().IsOnlyInfo())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnUserInfo()
{
    CDNewUserInfo dlgNewUserInfo;
    dlgNewUserInfo.DoModal();
}

void CAeView::OnUpdateUserInfo(CCmdUI* pCmdUI)
{
//  pCmdUI->Enable(FALSE);
    if (GetAeUser().IsUserInfoVz())
    {
        pCmdUI->Enable(TRUE);
    }
    else if (GetAeUser().IsUserInfoAll())
    {
        pCmdUI->Enable(TRUE);
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeEncloser()
{
    CDEncloserTimes dlgEncloserTimes;
    dlgEncloserTimes.DoModal();
}

void CAeView::OnUpdatePflegeEncloser(CCmdUI* pCmdUI)
{
    if (AeGetApp()->IsCH() || AeGetApp()->IsAT())
    {
        if (GetAeUser().IsPflegeEncloser())
        {
            pCmdUI->Enable(TRUE);
        }
        else
        {
            pCmdUI->Enable(FALSE);
        }
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnListenPromoquota()
{
    CDPromoQuota dlgPromoQuota;
    dlgPromoQuota.DoModal();
}

void CAeView::OnUpdateListenPromoquota(CCmdUI* pCmdUI)
{
    if (AeGetApp()->IsBG())
    {
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnAuftragCollectivordersanzeigen()
{
    if (AeGetApp()->IsDE())
    {
        CDCollectiveOrdersDE dlgCollectiveOrdersDE(0);
        dlgCollectiveOrdersDE.DoModal();
    }
    else
    {
        CDCollectiveOrders dlgCollectiveOrders(0);
        dlgCollectiveOrders.DoModal();
    }
}

void CAeView::OnBestellfensterPflegen()
{
    CDKndWahl dlgKndWahl;

    if (dlgKndWahl.DoModal() == IDOK)
    {
        CDOrderPeriod dlgOrderPeriod(dlgKndWahl.GetKndVz(), dlgKndWahl.GetKndNr(), 0);
        dlgOrderPeriod.DoModal();
    }
}

void CAeView::OnUpdateBestellfensterPflegen(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetAeUser().IsPflegeBestellFenster() ? TRUE : FALSE);
}

void CAeView::OnPflegeCremaRecipientMail()
{
    const short branchNo = AeGetApp()->FilialNr();
    DCremaMail dlgCremaMail(branchNo);
    dlgCremaMail.DoModal();
}

void CAeView::OnUpdatePflegeCremaRecipientMail(CCmdUI* pCmdUI)
{
    pCmdUI->Enable(GetAeUser().IsPflegeCremaMailAdr() ? TRUE : FALSE);
}

void CAeView::OnUpdateAuftragCollectivordersanzeigen(CCmdUI* pCmdUI)
{
    if (AeGetApp()->IsCollOrders() || AeGetApp()->IsDE())
    {
        if (GetAeUser().IsAeUser())
        {
            pCmdUI->Enable(TRUE);
        }
        else
        {
            pCmdUI->Enable(FALSE);
        }
    }
    else
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnPflegeReserveCharge()
{
    CDReserve dlgReserve;
    dlgReserve.m_Funktion = 5;
    dlgReserve.DoModal();
}

void CAeView::OnUpdatePflegeReserveCharge(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeReserveCharge())
    {
        pCmdUI->Enable(FALSE);
    }
}

void CAeView::OnExtrasSchrift()
{
    if (AeGetApp()->m_pMainWnd->GetMenu()->GetMenuState(ID_EXTRAS_SCHRIFT, MF_BYCOMMAND) == MF_CHECKED)
    {
        AeGetApp()->IsSchrift = false;  //check war vorher !!!
    }
    else
    {
        AeGetApp()->IsSchrift = true;   //check war vorher !!!
    }
}

void CAeView::OnUpdateExtrasSchrift(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsAeUser())
    {
        pCmdUI->Enable(FALSE);
    }
    else
    {
        pCmdUI->SetCheck(AeGetApp()->IsSchrift() ? 1 : 0);
    }
}

void CAeView::OnPflegeCstbranchinfo()
{
    CDCstBranchInfoUpd dlgCstBranchInfoUpd;
    dlgCstBranchInfoUpd.DoModal();
}

void CAeView::OnUpdatePflegeCstbranchinfo(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeBranchInfo())
        pCmdUI->Enable(FALSE);
}

void CAeView::OnPflegeOrigintypesettings()
{
    CDChooseFiliale dlgChooseFiliale;
    if (dlgChooseFiliale.DoModal() == IDCANCEL)
    {
        return;
    }
    CDSubTypeSettings dlgSubTypeSettings;
    dlgSubTypeSettings.m_sBranchNo = dlgChooseFiliale.m_FilialNr;
    dlgSubTypeSettings.DoModal();
}

void CAeView::OnUpdatePflegeOrigintypesettings(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeOrigintypesettings())
        pCmdUI->Enable(FALSE);
}

void CAeView::OnPflegeCbRemarks()
{
    CDCallbackRemarks dlgCallbackRemarks;
    dlgCallbackRemarks.DoModal();
}

void CAeView::OnUpdatePflegeCbRemarks(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeCBRemarks())
        pCmdUI->Enable(FALSE);
}


void CAeView::OnPflegeBearbeitenkundentouren()
{
    CDCstTours dlgCstTours;
    dlgCstTours.DoModal();
}


void CAeView::OnUpdatePflegeBearbeitenkundentouren(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeCstTours())
        pCmdUI->Enable(FALSE);
}


void CAeView::OnVerzSpecial()
{
    CDddSpecialList dlgSpecialList;
    dlgSpecialList.DoModal();
}


void CAeView::OnUpdateVerzSpecial(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeDD() || AeGetApp()->UseTourManagerCst() != 2)
    {
        pCmdUI->Enable(FALSE);
    }
}


void CAeView::OnPflegeExtratourreasons()
{
    CDExtraTourReasons dlgExtraTourReasons;
    dlgExtraTourReasons.DoModal();
}


void CAeView::OnUpdatePflegeExtratourreasons(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsPflegeExtraTourReasons())
    {
        pCmdUI->Enable(FALSE);
    }
}


void CAeView::OnAuftragCsvImport()
{
    CDAeCSVImport dlgAeCSVImport;
    dlgAeCSVImport.DoModal();
}


void CAeView::OnUpdateAuftragCsvImport(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsCSVImport())
    {
        pCmdUI->Enable(FALSE);
    }
}


void CAeView::OnViewNoCritics()
{
    if (AeGetApp()->m_pMainWnd->GetMenu()->GetMenuState(ID_VIEW_NO_CRITICS, MF_BYCOMMAND) == MF_CHECKED)
    {
        AeGetApp()->IsShowCritics = false;
    }
    else
    {
        AeGetApp()->IsShowCritics = true;
    }
}


void CAeView::OnUpdateViewNoCritics(CCmdUI* pCmdUI)
{
    if (!(AeGetApp()->IsDE() && !AeGetApp()->IsCH() && !AeGetApp()->IsAT()))
    {
        pCmdUI->Enable(FALSE);
    }
    else
    {
        if (AeGetApp()->IsShowCritics())
        {
            pCmdUI->SetCheck(1);
        }
        else
        {
            pCmdUI->SetCheck(0);
        }
    }
}


void CAeView::OnViewNoBranchinfo()
{
    if (AeGetApp()->m_pMainWnd->GetMenu()->GetMenuState(ID_VIEW_NO_BRANCHINFO, MF_BYCOMMAND) == MF_CHECKED)
    {
        AeGetApp()->IsShowBranchInfo = false;
    }
    else
    {
        AeGetApp()->IsShowBranchInfo = true;
    }
}


void CAeView::OnUpdateViewNoBranchinfo(CCmdUI* pCmdUI)
{
    //derzeit nicht gewünscht
    pCmdUI->Enable(FALSE);
}


void CAeView::OnInformationenShowParaChange()
{
    CParameterChanges dlgParameterChanges;
    dlgParameterChanges.DoModal();
}


void CAeView::OnUpdateInformationenShowParaChange(CCmdUI* pCmdUI)
{
    if (!GetAeUser().IsShowParamChanges())
    {
        pCmdUI->Enable(FALSE);
    }
}
