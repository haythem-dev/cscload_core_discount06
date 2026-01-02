// DKritikUpd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDKritikUpd dialog
#include <callback.h>
#include "CallbackStatusManager.h"

class CDKritikUpd : public CDialogMultiLang
{
    // Construction
public:
    CDKritikUpd(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDKritikUpd() {}

    enum { IDD = IDD_AE_KRITIK_UPD };

    CEdit        m_EditReaktion;
    CEdit        m_EditReference;
    CEdit        m_EditStatus;
    CComboBox    m_ComboStatus;

    CString m_CKundenName;
    CString m_CApotheke;
    CString m_CPlz;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CTelefon;
    CString m_CKurzwahl;
    CString m_CIdf;
    CString m_CReaktion;
    CString m_CTitel;
    CString m_CDatum;
    CString m_CUser;
    CString m_CZeit;
    CString m_CList;
    long m_lKritiknr;
    short m_sVzNr;
    long m_lRRNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnDestroy();
    afx_msg void OnButtonRr();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnChangeEditReaktion();
    DECLARE_MESSAGE_MAP()

    CCallbackStatusManager  m_CallbackStatusManager;
    CCALLBACKITEMS          m_RRItem;
};
