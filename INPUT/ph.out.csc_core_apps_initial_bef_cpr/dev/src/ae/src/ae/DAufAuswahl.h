#pragma once

#include <atltime.h>

// CDAufAuswahl dialog

class CDAufAuswahl : public CDialogMultiLang, CPageBrowser
{
    DECLARE_DYNAMIC(CDAufAuswahl)

public:
    CDAufAuswahl(CWnd* pParent = NULL, const bool bDirectSelect=false);   // standard constructor
    virtual ~CDAufAuswahl();
    long GetAufNr() { return m_AufNr; }     // Rückgabe der Auftrtagsnummer

    enum { IDD = IDD_AE_AUF_AUSWAHL };
    CEdit   m_EditOrderNrFili;
    CEdit   m_EditOrderNrFiliOnly;
    CButton m_CheckVz;
    CButton m_CheckAktuell;
    CButton m_CheckHistory;
    CEdit   m_EditPzn;
    CEdit   m_EditRechnNr;
    CEdit   m_EditDatum;
    CEdit   m_EditTermID;
    CEdit   m_EditOrderNr;
    CEdit   m_EditOrderNrOnly;
    CEdit   m_EditTour;
    CEdit   m_EditKndNr;
    CListCtrl m_ListCtl;
    CString m_KndNr;
    CString m_Tour;
    CComboBox m_ComboKdAArt;
    int     m_ComboStatus;
    CString m_COrderNr;
    CString m_COrderNrOnly;
    CString m_CTermID;
    CString m_CDatum;
    CString m_RechnNr;
    CString m_CPzn;
    CString m_COrderNrFili;
    CString m_COrderNrFiliOnly;
    CString m_SapReferenceNo;
    CEdit m_EditSapReferenceNo;
    CStatic m_StaticSapReferenceNo;
    long m_lKndNr;
    long m_IdfNr;
    short m_VzNr;
    CImageList m_ImageSmall;
    CString m_Sort;
    CComboBox m_Combobox_Status;
    CComboBox m_Combobox_Branchno;
    CDateTimeCtrl m_DT_DD;
    CTime m_CT_DD;
    CString m_Regionliste;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);         // Fuellen der Listbox
    BOOL CheckCriteria();                                        // Check ob eine Einschränkung aktiv ist (sonst keine Anzeige)
    void CloseCursor();                                          // DB-Cursor schliessen
    long GetStatus(int StatLisPos, CString& COrdStat);           // Ermittlung des ausgewählten Status
    void MarkListPosChar(int Letter);                            // Markierung einer Position in der Listbox (Buchstabe)
    long GetAuftrNr(CString& Status, CString& VZ, CString& ZuGrund); // liefert AufNr und Status
    void SetAuftrNr();                                           // setzt AufNr und OnOK
    long m_AufNr;                                                // Auftragsnummer
    long m_Funktion;                                             // Funktion, mit der selektiert wird
    long m_Datum;                                                // Datum bei älteren Aufträgen
    bool m_bDirectSelect;                                        // vor Anzeige Select ausführen!
    bool m_bSelProforma;                                         // Anzeigen nicht befriedigte Proforma-Auftraege
    long m_ActDatum;                                             // aktuelle Datum
    bool m_bMSV3;                                                // Auftrag kam per MSV3

    // Generated message map functions
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnButtonKnd();
    afx_msg void OnChangeEditIdf();
    afx_msg void OnChangeEditTour();
    afx_msg void OnKeydownListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDblclkListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnChangeEditAuftrNr();
    afx_msg void OnChangeEditAuftrNrOnly();
    afx_msg void OnDestroy();
    afx_msg void OnChangeEditDatum();
    afx_msg void OnButtonDruck();
    afx_msg void OnChangeEditRechnNr();
    afx_msg void OnButtonPzn();
    afx_msg void OnChangeEditPzn();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnCheckVz();
    afx_msg void OnButtonSelect();
    afx_msg void OnChangeEditAuftrNrFili();
    afx_msg void OnChangeEditAuftrNrFiliOnly();
    afx_msg void OnCbnSelchangeComboStatus();
    afx_msg void OnLvnColumnclickListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonProforma();
    afx_msg void OnCheckAktuell();
    afx_msg void OnCheckHistory();
    afx_msg void OnChangeEditSapReferenceNo();
    afx_msg LRESULT OnHookFkt( WPARAM wParam, LPARAM lParam );
    DECLARE_MESSAGE_MAP()

private:
    static int GetAufTypToValue(double aufTyp6Value, double aufTyp7Value, double aufTyp8Value);

    bool FillServerRequest(AUSTINF& austinf);
    void ReadCustomer(AUSTINF& austinf);
    bool IsProforma(long orderno);
    void FormatResultLine(AUSTINF& austinf, char* kb, CStringArray& s);
    CString FormatRelationNo(short relationNoType, AUSTINF& austinf);
    void GetOrderTypeAndVseState(AUSTINF& austinf, CString state, int& vseState, int& ordertype);
    void OpenOrderInformationDlg(bool bNoOpen, int pos, long ldatum, CString orderlabel);
    bool IsDeferredOrRecording(CString status);
};
