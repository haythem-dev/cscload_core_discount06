// aeview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAeView view
#pragma once
class CDRrMessage;
class CDMailMessage;
class CDUserInfo;

#include "NMDText.h"

class CAeView : public CView
{
protected:
    afx_msg void OnContextMenu(CWnd*, CPoint point);
    afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnHelpHitTest(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGoodbye(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnGoodbyeMail(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnKillTimer(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnActTimer(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnReNew(WPARAM wParam, LPARAM lParam);
    CAeView();           // protected constructor used by dynamic creation
    DECLARE_DYNCREATE(CAeView)

protected:
    virtual BOOL PreTranslateMessage(MSG* pMsg);

    virtual void OnDraw(CDC* pDC);      // overridden to draw this view

    virtual ~CAeView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

    afx_msg void OnFileAuswFil();
    afx_msg void OnInformationenKundenkontakte();
    afx_msg void OnUpdateInformationenKundenkontakte(CCmdUI* pCmdUI);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnBrowserZurck();
    afx_msg void OnUpdateBrowserZurck(CCmdUI* pCmdUI);
    afx_msg void OnBrowserHome();
    afx_msg void OnUpdateBrowserHome(CCmdUI* pCmdUI);
    afx_msg void OnInformationenCallback();
    afx_msg void OnUpdateInformationenCallback(CCmdUI* pCmdUI);
    afx_msg void OnInformationenCallbackDo();
    afx_msg void OnUpdateInformationenCallbackDo(CCmdUI* pCmdUI);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnInformationenVblief();
    afx_msg void OnUpdateInformationenVblief(CCmdUI* pCmdUI);
    afx_msg void OnAuftragVerbund();
    afx_msg void OnUpdateAuftragVerbund(CCmdUI* pCmdUI);
    afx_msg void OnAuftragDefekte();
    afx_msg void OnUpdateAuftragDefekte(CCmdUI* pCmdUI);
    afx_msg void OnAbschlSperre();
    afx_msg void OnUpdateAbschlSperre(CCmdUI* pCmdUI);
    afx_msg void OnAbschlSperreWeg();
    afx_msg void OnUpdateAbschlSperreWeg(CCmdUI* pCmdUI);
    afx_msg void OnMailGroups();
    afx_msg void OnUpdateMailGroups(CCmdUI* pCmdUI);
    afx_msg void OnMailNew();
    afx_msg void OnUpdateMailNew(CCmdUI* pCmdUI);
    afx_msg void OnMailControl();
    afx_msg void OnUpdateMailControl(CCmdUI* pCmdUI);
    afx_msg void OnParAnrufsteuerung();
    afx_msg void OnUpdateParAnrufsteuerung(CCmdUI* pCmdUI);
    afx_msg void OnPflegeKunde();
    afx_msg void OnUpdatePflegeKunde(CCmdUI* pCmdUI);
    afx_msg void OnPflegeFeiertage();
    afx_msg void OnUpdatePflegeFeiertage(CCmdUI* pCmdUI);
    afx_msg void OnPflegeTouren();
    afx_msg void OnUpdatePflegeTouren(CCmdUI* pCmdUI);
    afx_msg void OnUpdateFileAuswFil(CCmdUI* pCmdUI);
    afx_msg void OnPflegeKundeVbfilialen();
    afx_msg void OnUpdatePflegeKundeVbfilialen(CCmdUI* pCmdUI);
    afx_msg void OnAbschluAnruftreiberumk();
    afx_msg void OnUpdateAbschluAnruftreiberumk(CCmdUI* pCmdUI);
    afx_msg void OnAbschluAnruftreiberumkStoppen();
    afx_msg void OnUpdateAbschluAnruftreiberumkStoppen(CCmdUI* pCmdUI);
    afx_msg void OnAbschluAnruftreiberumkStatus();
    afx_msg void OnUpdateAbschluAnruftreiberumkStatus(CCmdUI* pCmdUI);
    afx_msg void OnPflegeInfoliste();
    afx_msg void OnUpdatePflegeInfoliste(CCmdUI* pCmdUI);
    afx_msg void OnFileAuswSprache();
    afx_msg void OnUpdateFileAuswSprache(CCmdUI* pCmdUI);
    afx_msg void OnPflegeTelefonnr();
    afx_msg void OnUpdatePflegeTelefonnr(CCmdUI* pCmdUI);
    afx_msg void OnPflegeToursperre();
    afx_msg void OnUpdatePflegeToursperre(CCmdUI* pCmdUI);
    afx_msg void OnPflegeQuota();
    afx_msg void OnUpdatePflegeQuota(CCmdUI* pCmdUI);
    afx_msg void OnPflegeQuotaKlasse();
    afx_msg void OnUpdatePflegeQuotaKlasse(CCmdUI* pCmdUI);
    afx_msg void OnPflegeQuotaInf();
    afx_msg void OnUpdatePflegeQuotaInf(CCmdUI* pCmdUI);
    afx_msg void OnPflegeArtikel();
    afx_msg void OnUpdatePflegeArtikel(CCmdUI* pCmdUI);
    afx_msg void OnVerzKundeEinzel();
    afx_msg void OnUpdateVerzKundeEinzel(CCmdUI* pCmdUI);
    afx_msg void OnVerzKundeAlle();
    afx_msg void OnUpdateVerzKundeAlle(CCmdUI* pCmdUI);
    afx_msg void OnPflegeBranchinfo();
    afx_msg void OnUpdatePflegeBranchinfo(CCmdUI* pCmdUI);
    afx_msg void OnPflegeForbidden();
    afx_msg void OnUpdatePflegeForbidden(CCmdUI* pCmdUI);
    afx_msg void OnPflegeReserve();
    afx_msg void OnUpdatePflegeReserve(CCmdUI* pCmdUI);
    afx_msg void OnInformationenReserviert();
    afx_msg void OnUpdateInformationenReserviert(CCmdUI* pCmdUI);
    afx_msg void OnAuftragSammel();
    afx_msg void OnUpdateAuftragSammel(CCmdUI* pCmdUI);
    afx_msg void OnListenOffeneauftr();
    afx_msg void OnUpdateListenOffeneauftr(CCmdUI* pCmdUI);
    afx_msg void OnPflegeCountrycode();
    afx_msg void OnUpdatePflegeCountrycode(CCmdUI* pCmdUI);
    afx_msg void OnPflegeNotfall();
    afx_msg void OnUpdatePflegeNotfall(CCmdUI* pCmdUI);
    afx_msg void OnPflegeVa();
    afx_msg void OnUpdatePflegeVa(CCmdUI* pCmdUI);
    afx_msg void OnSeperaterauftragGenerell();
    afx_msg void OnUpdateSeperaterauftragGenerell(CCmdUI* pCmdUI);
    afx_msg void OnSeperaterauftragKundenspezifisch();
    afx_msg void OnUpdateSeperaterauftragKundenspezifisch(CCmdUI* pCmdUI);
    afx_msg void OnPflegeArtikelVbfilialen();
    afx_msg void OnUpdatePflegeArtikelVbfilialen(CCmdUI* pCmdUI);
    afx_msg void OnPflegeQuotaEkg();
    afx_msg void OnUpdatePflegeQuotaEkg(CCmdUI* pCmdUI);
    afx_msg void OnPflegeReservePct();
    afx_msg void OnUpdatePflegeReservePct(CCmdUI* pCmdUI);
    afx_msg void OnPflegeReserveAbs();
    afx_msg void OnUpdatePflegeReserveAbs(CCmdUI* pCmdUI);
    afx_msg void OnPflegeBeilage();
    afx_msg void OnUpdatePflegeBeilage(CCmdUI* pCmdUI);
    afx_msg void OnPflegeQuotaKndEkg();
    afx_msg void OnUpdatePflegeQuotaKndEkg(CCmdUI* pCmdUI);
    afx_msg void OnPflegeReserveZert();
    afx_msg void OnUpdatePflegeReserveZert(CCmdUI* pCmdUI);
    afx_msg void OnPflegeReserveBPZ();
    afx_msg void OnUpdatePflegeReserveBPZ(CCmdUI* pCmdUI);
    afx_msg void OnBearbKommiChange();
    afx_msg void OnUpdateBearbKommiChange(CCmdUI* pCmdUI);
    afx_msg void OnUserInfo();
    afx_msg void OnUpdateUserInfo(CCmdUI* pCmdUI);
    afx_msg void OnPflegeEncloser();
    afx_msg void OnUpdatePflegeEncloser(CCmdUI* pCmdUI);
    afx_msg void OnListenPromoquota();
    afx_msg void OnUpdateListenPromoquota(CCmdUI* pCmdUI);
    afx_msg void OnAuftragCollectivordersanzeigen();
    afx_msg void OnUpdateAuftragCollectivordersanzeigen(CCmdUI* pCmdUI);
    afx_msg void OnBnClickedBtnSearch();
    afx_msg void OnPflegeReserveCharge();
    afx_msg void OnUpdatePflegeReserveCharge(CCmdUI* pCmdUI);
    afx_msg void OnExtrasSchrift();
    afx_msg void OnUpdateExtrasSchrift(CCmdUI* pCmdUI);
    afx_msg void CAeView::OnBestellfensterPflegen();
    afx_msg void CAeView::OnUpdateBestellfensterPflegen(CCmdUI* pCmdUI);
    afx_msg void OnPflegeCstbranchinfo();
    afx_msg void OnUpdatePflegeCstbranchinfo(CCmdUI* pCmdUI);
    afx_msg void OnPflegeOrigintypesettings();
    afx_msg void OnUpdatePflegeOrigintypesettings(CCmdUI* pCmdUI);
    afx_msg void OnPflegeCremaRecipientMail();
    afx_msg void CAeView::OnUpdatePflegeCremaRecipientMail(CCmdUI* pCmdUI);
    afx_msg void OnPflegeCbRemarks();
    afx_msg void OnUpdatePflegeCbRemarks(CCmdUI* pCmdUI);
    afx_msg void OnPflegeBearbeitenkundentouren();
    afx_msg void OnUpdatePflegeBearbeitenkundentouren(CCmdUI* pCmdUI);
    afx_msg void OnVerzSpecial();
    afx_msg void OnUpdateVerzSpecial(CCmdUI* pCmdUI);
    afx_msg void OnPflegeExtratourreasons();
    afx_msg void OnUpdatePflegeExtratourreasons(CCmdUI* pCmdUI);
    afx_msg void OnAuftragCsvImport();
    afx_msg void OnUpdateAuftragCsvImport(CCmdUI* pCmdUI);
    afx_msg void OnViewNoCritics();
    afx_msg void OnUpdateViewNoCritics(CCmdUI* pCmdUI);
    afx_msg void OnViewNoBranchinfo();
    afx_msg void OnUpdateViewNoBranchinfo(CCmdUI* pCmdUI);
    afx_msg void OnInformationenShowParaChange();
    afx_msg void OnUpdateInformationenShowParaChange(CCmdUI* pCmdUI);
    DECLARE_MESSAGE_MAP()

private:
    bool m_bWithBrowse;
    CDRrMessage* m_pDlg;
    CDMailMessage* m_pDlgMail;
    CDUserInfo* m_pDlgUserInfo;
    CNMDText m_dlgText;
};
