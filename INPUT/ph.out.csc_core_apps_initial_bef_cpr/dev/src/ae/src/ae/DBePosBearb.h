#pragma once

// DBePosBearb.h : header file
//
#include "IBTlistctrl.h"
#include "DBePosBearbData.h"
#include "DBePosBearbPresenter.h"
#include "DBePosBearbModel.h"

class CDBePosBearbPresenter;

/////////////////////////////////////////////////////////////////////////////
// CDBePosBearb dialog

class CDBePosBearb : public CDialogMultiLang
{
// Construction
public:
    CDBePosBearb(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDBePosBearb();


public:
    long    m_Menge;        //zu verbuchende Menge
    long    m_MengeNatra;   //zu verbuchende Menge Natra
    long    m_BestMengeNatra;   //Bestellmenge Natra
    long    m_KndNr;
    long    m_IdfNr;

// Dialog Data
    enum { IDD = IDD_AE_BEST_POS_BEARB };
    CListBox  m_ListOffBest;
    CComboBox m_ComboVerbund;
    CEdit   m_EditLiefMenge;
    CEdit   m_EditLiefMengeNatra;
    CEdit   m_EditBemerkung;
    CString m_CBemerkung;
    CString m_CArtName;
    CString m_CArtEinh;
    long    m_LiefMenge;
    long    m_LiefMengeNatra;
    CString m_CDarreichform;
    CString m_VerbundZeitKnd;
    CIBTListCtrl* m_List1;
    CString m_CArtCode;

protected:
    CDBePosBearbData m_Data;
    CDBePosBearbPresenter m_Presenter;
    CDBePosBearbModel m_Model;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnChangeEdittext();
    afx_msg void OnChangeEditLiefMenge();
    afx_msg void OnChangeEditLiefMengeNatra();
    afx_msg void OnButtonDispo();
    afx_msg void OnButtonNachLf();
    virtual void OnOK();
    afx_msg void OnButtonZugesagt();
    afx_msg void OnCheckVerbund();
    afx_msg void OnSelchangeComboVerbFiliale();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnBnClickedVerbund();
    afx_msg void OnBnClickedCancel2();

    long GetMengeVerbund() { return m_Data.m_lMengeVerbund; }

    void SetBestMenge(long lBestMenge) { m_Data.m_lBestMenge = lBestMenge; }
    long GetBestMenge() { return m_Data.m_lBestMenge; }
    void SetBestMengeStr(const CString& formatString, long lBestMenge) { m_Data.m_strBestMenge.Format(formatString, lBestMenge); }
    const CString& GetBestMengeStr() { return m_Data.m_strBestMenge; }

    void SetIgnoreNoWafo(bool bIgnoreNoWafo) { m_Data.m_bIgnoreNoWafo = bIgnoreNoWafo; }
    void SetKndMussKopfBem(bool bKndMussKopfBem) { m_Data.m_bKndMussKopfBem = bKndMussKopfBem; }

    void SetArtNr(const CString& rArtNr) { m_Data.m_strArtNr = rArtNr; }
    void SetBestand(const CString& rBestand) { m_Data.m_strBestand = rBestand; }
    void SetBestand(const CString& formatString, long lBestand) { m_Data.m_strBestand.Format(formatString, lBestand); }

    void SetBestMengeNatra(const CString& formatString, long lBestMengeNatra) { m_Data.m_strBestMengeNatra.Format(formatString, lBestMengeNatra); }
    const CString& GetBestMengeNatra() { return m_Data.m_strBestMengeNatra; }

    void SetVerbMenge(long lVerbMenge) { m_Data.m_lVerbMenge = lVerbMenge; }
    void SetVerbFiliale(short sVerbFiliale) { m_Data.m_sVerbFiliale = sVerbFiliale; }
    short GetVerbFiliale() { return m_Data.m_sVerbFiliale; }

    void SetPosStat(long lPosStat) { m_Data.m_lPosState = lPosStat; }
    long GetPosStat() { return m_Data.m_lPosState; }

private:
    void InitVerbund();
    void DeaktVerbund();
    void SetVerbund(bool bVerbund = true);
    void CheckVerbund();
};
