// DParKondGrp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDParKondGrp dialog

class CDParKondGrp : public CDialogMultiLang
{
private:
    CListCtrl m_ListCtl;

// Construction
public:
    CDParKondGrp(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_PAR_KONDGRP };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void ReadDataInListBox();
    void AddPosToList(long KndGrp, CString KText);

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonDel();
    afx_msg void OnButtonNeu();
    afx_msg void OnButtonUpd();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDParKondGrpUpd dialog

class CDParKondGrpUpd : public CDialogMultiLang
{
protected:
    CEdit   m_EditGrpNr;
    CEdit   m_EditBezeichnung;

public:
    CString m_CBezeichnung;
    long    m_lGrpNr;
    BOOL    m_bUpdate;                         // Schalter ob Update oder Insert

// Construction
public:
    CDParKondGrpUpd(CWnd* pParent = NULL);  // standard constructor

    enum { IDD = IDD_AE_PAR_KONDGRP_UPD };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnChangeEditBezeichnung();
    afx_msg void OnChangeEditGrpnr();
    DECLARE_MESSAGE_MAP()
};
