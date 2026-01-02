#pragma once


// CDSeperatUpd-Dialogfeld

class CDSeperatUpd : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDSeperatUpd)

public:
    CDSeperatUpd(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDSeperatUpd();

    enum { IDD = IDD_AE_SEPERAT_UPD };
    CComboBox m_Cobox_Grp;
    CComboBox m_Cobox_AArt;
    CComboBox m_Cobox_KoArt;
    CComboBox m_Cobox_BuArt;
    CButton m_CB_Defer;
    CString m_cAArt;
    CString m_cKoArt;
    CString m_cBuArt;
    short m_sGruppe;
    short m_sFunktion;  //0 = Update, 1 = Insert
    short m_sKind;      //0 = Generell, 1 = Customer
    int   m_iKndNr;
    CStringArray* m_Gruppen;
    CSEPORDERGRP* m_SepOrder;
    CCSTSEPORDER* m_SepOrderCst;
    BOOL m_bDefer;
    BOOL m_bSaveDefer;
    CEdit m_edit_Herst;
    CString m_cHerst;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnCbnSelchangeComboGrp();
    DECLARE_MESSAGE_MAP()
};
