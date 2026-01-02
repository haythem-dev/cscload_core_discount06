#pragma once

#include "cremamailaddresses.h"

class DCremaMail : public CDialogMultiLang
{
    //DECLARE_DYNAMIC(DCremaMail)

    enum { IDD = IDD_MANAGE_CREMA_MAIL };
    enum EMAILTYPES { NONE = -1, FULLMAIL, INFOMAIL };

public:
    DCremaMail(short branchNo, CWnd* pParent = NULL);
    ~DCremaMail();

protected:
    void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    BOOL OnInitDialog();

private:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnCmbSelectionChanged();
    afx_msg void OnBtnClickedClose();
    afx_msg void OnBtnClickedAddMail();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBtnClickedDeleteMail();
    afx_msg void OnEnChangeEdMail();
    afx_msg void OnListItemChanged(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBtnClickedGVL();
    afx_msg void OnBtnClickedGVLFull();
    afx_msg void OnBtnClickedGVLInfo();
    afx_msg void OnBtnClickedGVLSave();

    void SetupComboBox();
    void SetupList();

    bool validateMail( const char* mail );
    void updateTable();
    void clearInputFields();
    void setGVLAccordingToSelectionTable();

    void switchToInsertMode();
    bool SaveGVL();
    bool CheckEmailType(EMAILTYPES emailType);
    int InsertType(short type);
    int AddEmail(CCREMAEMAILADDRESSES addresses);

private:
    CComboBox m_cboMailGroup;
    CListCtrl m_lstMails;
    CButton   m_btnClose;
    CButton   m_btnAddMail;
    CButton   m_btnCancel;
    CButton   m_btnDeleteMail;
    CButton   m_ckInfoMail;
    CButton   m_ckNormalMail;
    CButton   m_ckGVLMail;
    CButton   m_ckGVLMailFull;
    CButton   m_ckGVLMailInfo;
    CButton   m_btnGVLSave;
    CEdit     m_edMail;

    short     m_BranchNo;
    int       m_mailID;
};
