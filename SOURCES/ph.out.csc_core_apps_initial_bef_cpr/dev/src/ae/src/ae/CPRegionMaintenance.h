//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPRegionMaintenance.h
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//--- include ----------------------------------------------------------------//

#include "ppRegion.h"

//----------------------------------------------------------------------------//
//--- class CCPRegionMaintenance (dialog) ------------------------------------//
//----------------------------------------------------------------------------//

class CCPRegionMaintenance : public CDialogMultiLang, CPageBrowser
{
public: // Construction
    CCPRegionMaintenance(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_CP_REGION_MAINTANANCE };
    CListCtrl m_ListCtl;
    CComboBox m_CComboBoxRegionPartNo;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg void OnRadio3();
    afx_msg void OnButtonNew();
    afx_msg void OnButtonDelete();
    afx_msg void OnKeydownListRegion(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnClickListRegion(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

protected: //members
    ppRegion        m_Region;
    unsigned int    m_nColumnsCount;
    unsigned int    m_iPos;
    bool            m_bIsNotfound;

protected: //methodes
    void FillComboBox();
    bool SetListHeader();
    bool SetValueIntoList(const char& chSelector = AeGetApp()->Letter_A());
    virtual bool GetPage(const int nKzUpDown = NEXT_PG);
    bool GetPosition(const bool bShowErrorMsg=true);
    void GetData();
    bool CheckPassword();
    void SetComboData();
};
