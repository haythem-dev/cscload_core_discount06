// DVerbBestaet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDVerbBestaet dialog
#include <vector>
#include "IBTListctrl.h"
using namespace std;

class CDVerbBestaet : public CDialogMultiLang
{
// Construction
public:
    CDVerbBestaet(CWnd* pParent = NULL);   // standard constructor
    virtual ~CDVerbBestaet();

    long m_VerbMenge;
    short m_VerbFiliale;

public:
    void SetIsActive(const bool& isActive = true) { m_bIsActive = isActive; }
    const int& GetCount() const { return m_iCount; }
    const short GetActiveVBFiliale() const { return m_VerbFiliale; }
    // Dialog Data
    enum { IDD = IDD_AE_VERBUND_POS };
    CComboBox m_ComboVerbund;
    CString m_CDarreichform;
    CString m_CArtEinh;
    CString m_CArtName;
    CString m_CArtNr;
    CString m_CBestMenge;
    CString m_CBestand;
    CString m_VerbundZeitenKnd;
    CString m_CArtCode;
    CIBTListCtrl* m_List1;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnVerbund();
    DECLARE_MESSAGE_MAP()

// Implementation
protected:
    bool m_bIsActive;
    int m_iCount;
    vector<CString> m_vList;
};
