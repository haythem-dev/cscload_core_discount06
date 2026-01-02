#pragma once


// CDCallbackReason-Dialogfeld

class CDCallbackReason : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDCallbackReason)

public:
    CDCallbackReason(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDCallbackReason();
    void SetVzNr(const short sVz) { m_sVzNr = sVz; }
    const short GetVzNr() const { return m_sVzNr; }
    CString m_Mailadr;
    CString m_Reason;
    short m_sPartnerNo;         // Partnernumer
    short m_ReasonNo;           // Rueckrufgrund
    bool m_new;                 // Kennz. ob insert oder update
    BOOL m_bOnlyMail;           // Kennz. nur Mail senden - kein RR
    bool m_bMainMailAdr;        // Kennz. bei Division mailadr vorhanden

// Dialogfelddaten
    enum { IDD = IDD_AE_CALLBACK_REASONS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    short m_sVzNr;

    afx_msg void OnChangeEditMail();
    DECLARE_MESSAGE_MAP()

private:
    bool m_ShowOnlyMailChk;
};
