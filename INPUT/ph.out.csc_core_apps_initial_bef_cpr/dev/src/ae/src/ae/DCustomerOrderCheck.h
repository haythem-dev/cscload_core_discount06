#pragma once

// DCustomerOrderCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
//  DCustomerOrderCheck dialog


class  DCustomerOrderCheck : public CDialogMultiLang, CPageBrowser
{
    DECLARE_DYNAMIC(DCustomerOrderCheck)

// Construction
public:
     DCustomerOrderCheck(CWnd* pParent = NULL);   // standard constructor

protected:
    CDateTimeCtrl   m_DateTimePicker;                   //Zeitauswahlfeld-Control-Member
    CListCtrl       m_ListCustomerOrderCheckTable;      //ListCtrl-Control-Member
    CComboBox       m_combo_Status;                     //Status-Combobox-Control-Member
    CEdit           m_edit_Customer;                    //Kunde-Textfeld-Control-Member
    CString         m_cstr_combo_Status;                //Member für Inhalt des Kunden-Textfelds

    int             m_iZeilenListCtrl;                  //Anzahl der Zeilen im ListCtrl

    CStringArray    m_cStringArrayStatusTextShort;      //Dummy für im ListCtrl angezeigte Texte für die Stati (Kurzform)

    long            m_lKdnr;                            //IDF-Nummer
    int             m_icheckordertime;                  //Prüfzeit Kundenauftrag
    short           m_sorderstatus;                     //Status

private:
    CCUSTOMERORDERCHECK m_CustomerOrderCheck;           //Dade-Member

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    //DDX/DDV support

    afx_msg void OnOK();                                            //Button Selektieren
    afx_msg void OnSelectKunde();                                   //Button Auswahl Kunde
    afx_msg void OnKeydownListCtrl(NMHDR* pNMHDR, LRESULT* pResult);//Behandlung Tastatur-Ereignis im ListCtrl
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);        //Behandlung Tastatur-Ereignis im Dialog

    virtual bool GetPage(const int nKzUpDown = NEXT_PG);  // Selekt und List-Box mit Eintraegen versorgen
    void MarkListPosChar(int Letter);           // Markierung einer Position in der Listbox (nach Buchstabe)
    void CloseCursor();                         // DB-Cursor schliessen

    virtual BOOL OnInitDialog();

    enum { IDD = IDD_AE_CUSTOMER_ORDER_CHECK };

    DECLARE_MESSAGE_MAP()
};
