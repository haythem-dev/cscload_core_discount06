// EditDate.h : header file
//
// spezielles Edit-Feld zur Eingabe des Datums

/////////////////////////////////////////////////////////////////////////////
// CEditDate window
#ifndef _EDITDATE_
#define _EDITDATE_

class CEditDate : public CEdit
{
// Construction
public:
    CEditDate(long datum = 0);

// Attributes
public:
    long m_lDatum;
    CString m_csDatum;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    CString GetDateChar();
    long GetDateLong();
    void SetDateChar(CString);
    void SetDateLong(long);

// Implementation
public:
    virtual ~CEditDate();

    // Generated message map functions
protected:
    afx_msg void OnChar(UINT c,UINT l,UINT f);
    DECLARE_MESSAGE_MAP()

protected:
    bool CheckCentury();
    void CheckDatum();
};

#endif
