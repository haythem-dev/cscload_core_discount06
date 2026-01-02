//(c)---------- Customer service program -------------------------------------//
/*
   Source: NMDtEXT.h
   Author: A.Schmidt-Rehschuh
   made  : 30.04.2002

   declaration:
   Dialog: Statusanzeige
*/

#pragma once

//----------------------------------------------------------------------------//
//--- class CNMDText (not modal dialog) --------------------------------------//
//----------------------------------------------------------------------------//

class CNMDText : public CDialogMultiLang
{
protected:
    #define LINE_FEED "\r\n"
    #define NEW_LINE  "\n"

public: // Construction
    CNMDText(const ppString& strText = "wait...");   // Standardkonstruktor

public: // methodes
    void SetText(const ppString& strText);
    bool AddMessage(const ppString& strMessage);
    void StartMessage();
    void EndMessage();
    void ClearMessage();

    enum { IDD = IDD_NMDTEXT };
    CButton m_CButtonOK;
    CEdit m_CEditMsg;

    virtual BOOL DestroyWindow();
    virtual BOOL Create();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    virtual void OnOK();
    DECLARE_MESSAGE_MAP()

protected: //methodes
    void ShowButton();
    void AddMessage();
    void SetEditSize();
    void SetText();
    void CleanEdit();

protected: //members
    ppString m_strText;
    ppString m_strMessage;
    bool m_bIsStart;
    bool m_bIsInit;
};
