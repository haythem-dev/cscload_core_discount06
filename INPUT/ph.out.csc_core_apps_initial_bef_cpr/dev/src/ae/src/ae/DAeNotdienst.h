#pragma once

// DAeNotdienst.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeNotdienst

class CDAeNotdienst : public CDialogMultiLang
{
// Konstruktion
public:
    CDAeNotdienst(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
    enum { IDD = IDD_AE_NOTDIENST };
    CEdit m_editVz;
    CListCtrl m_ListCtl;
    CTime m_Datum;


// Überschreibungen
    // Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

// Implementierung
protected:

    // Generierte Nachrichtenzuordnungsfunktionen
    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    virtual void OnOK();
    afx_msg void OnChangeEditVz();
    afx_msg void OnButtonPrint();
    afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

protected: //data-members
    long m_ldatum;
    short m_sVzNr;
    CString m_csTag;
    CMCUSTOMEREMERGENCYSERVICEPLAN m_srvServicePlan;

private:
    CString FormatColumn(int column, CString text);
};
