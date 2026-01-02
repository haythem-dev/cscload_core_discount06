//----------------------------------------------------------------------------------------------------//
// include guard
//----------------------------------------------------------------------------------------------------//
#pragma once

//----------------------------------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------------------------------//
#include <collectivorders.h>
#include <vector>
#include <list>

//----------------------------------------------------------------------------------------------------//
// suing section
//----------------------------------------------------------------------------------------------------//
using std::vector;
using std::list;

//----------------------------------------------------------------------------------------------------//
// class section
//----------------------------------------------------------------------------------------------------//
class CDAeSammelAuft : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDAeSammelAuft)

public:
    CDAeSammelAuft(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual ~CDAeSammelAuft();

    enum { IDD = IDD_AE_SAMMEL_AUFTRAG };

//-----------------------------------------------------------------//
// methods
//-----------------------------------------------------------------//
public:
    virtual BOOL OnInitDialog();
    void         Erfassen();
    void         showCollOrderGrp(CComboBox* pCbo = 0, bool newLoad = false);
    afx_msg void OnBnClickedButtonKnd();
    afx_msg void OnBnClickedButtonKndDel();
    afx_msg void OnBnClickedButtonArt();
    afx_msg void OnBnClickedButtonArtDel();
    afx_msg void OnNMDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedButtonZu();
    afx_msg void OnBnClickedBtNewLoad();
    afx_msg void OnBnClickedBtNewCustGrp();
    afx_msg void OnCbnSelchangeCboCustGrps();

protected:
    // methods
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    DECLARE_MESSAGE_MAP()

private:
    // typedefs
    typedef vector<long> DISPLAYED_MEMBERS;

    // methods
    BOOL OpenOrder(long lcustomer);
    void CloseOrder();
    void WritePositions(long lmenge, long larticleno);
    void collectDisplayedMembers();
    void saveCustGrpbyRigth();

//-----------------------------------------------------------------//
// members
//-----------------------------------------------------------------//
public:
    // public members
    CListCtrl m_ListCtl;
    CListCtrl m_ListCtl2;

private:
    // private member
    long m_lCountCustomer;
    long m_lCountArticle;
    long m_lStatus;
    long m_lOrgStatus;
    long m_lValuta;

    CString m_CBemerkung;
    CString m_CKoArt;
    CString m_CBuArt;
    CString m_CAufArt;
    CString m_curCustGrp;

    CComboBox         m_cboCustGrps;
    DISPLAYED_MEMBERS m_displayedMems;
};
