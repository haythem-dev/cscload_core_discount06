#pragma once
// daufinf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDAufInf dialog

#include <atltime.h>

class CDAufInf : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDAufInf(CWnd* pParent = NULL, const bool bDirectSelect = false); // standard constructor
    long GetAufNr() { return m_AufNr; }     // Rückgabe der Auftrtagsnummer

// Dialog Data
    enum { IDD = IDD_AE_AUF_INF };
    CEdit   m_EditOrderNrFili;
    CButton m_CheckVz;
    CEdit   m_EditPzn;
    CEdit   m_EditLauftnr;
    CEdit   m_EditRechnNr;
    CEdit   m_EditDatum;
    CEdit   m_EditTermID;
    CEdit   m_EditOrderNr;
    CEdit   m_EditTour;
    CEdit   m_EditKndNr;
    CListCtrl m_ListCtl;
    CString m_KndNr;
    CString m_Tour;
    CComboBox m_ComboKdAArt;
    int     m_ComboStatus;
    CString m_COrderNr;
    CString m_CTermID;
    CString m_CDatum;
    CString m_RechnNr;
    CString m_CLauftnr;
    CString m_CPzn;
    CString m_COrderNrFili;
    long m_lKndNr;
    long m_IdfNr;
    short m_VzNr;
    CImageList m_ImageSmall;
    CString m_Sort;

// Overrides
    // ClassWizard generated virtual function overrides
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);    // Fuellen der Listbox
    void CloseCursor();                                     // DB-Cursor schliessen
    long GetStatus(int statLisPos, CString& ordStatus);     // Ermittlung des ausgewählten Status
    void MarkListPosChar(int Letter);                       // Markierung einer Position in der Listbox (Buchstabe)
    long GetAuftrNr(CString& Status, CString& VZ, CString& ZuGrund); // liefert AufNr und Status
    void SetAuftrNr();                                      // setzt AufNr und OnOK
    long m_AufNr;                                           // Auftragsnummer
    long m_Funktion;                                        // Funktion, mit der selektiert wird
    long m_Datum;                                           // Datum bei älteren Aufträgen
    bool m_bDirectSelect;                                   // vor Anzeige Select ausführen!
    bool m_bSelProforma;                                    // Anzeigen nicht befriedigte Proforma-Auftraege
    long m_ActDatum;                                        // aktuelle Datum
    bool m_bMSV3;                                           // Auftrag kam per MSV3

    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnButtonKnd();
    afx_msg void OnChangeEditIdf();
    afx_msg void OnChangeEditTour();
    afx_msg void OnKeydownListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnChangeEditAuftrNr();
    afx_msg void OnDestroy();
    afx_msg void OnChangeEditDatum();
    afx_msg void OnButtonDruck();
    afx_msg void OnChangeEditRechnNr();
    afx_msg void OnChangeEditLauftNr();
    afx_msg void OnButtonPzn();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnCheckVz();
    afx_msg void OnButtonSelect();
    afx_msg void OnChangeEditAuftrNrFili();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

public:
    CComboBox m_Combobox_Status;
    CDateTimeCtrl m_DT_DD;
    CTime m_CT_DD;
    afx_msg void OnCbnSelchangeComboStatus();
    afx_msg void OnLvnColumnclickListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonProforma();

private:
    void FormatRelationNo(CString& ivcNo, short relationNoType, long orderno);
    static int GetAufTypToValue(double aufTyp6Value, double aufTyp7Value, double aufTyp8Value);
};
