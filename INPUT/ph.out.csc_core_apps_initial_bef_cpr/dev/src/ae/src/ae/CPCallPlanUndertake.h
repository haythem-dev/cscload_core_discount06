//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCallPlanUndertake.h
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000

   declaration:
   Dialog: maintenance for callplan
*/

#pragma once

//--- include ----------------------------------------------------------------//

#include "ppDataTypes.h"
#include "ppcallplanundertake.h"
#include "ppCallPlanLoad.h"
#include "NMDProgress.h"


//----------------------------------------------------------------------------//
//--- class CCPCallPlanUndertake (dialog) ------------------------------------//
//----------------------------------------------------------------------------//

class CCPCallPlanUndertake : public CDialogMultiLang
{
public: // Construction
    CCPCallPlanUndertake(CWnd* pParent = NULL);   // standard constructor
    ~CCPCallPlanUndertake();

    enum { IDD = IDD_CP_CALLPLANUNDERTAKE };
    CDateTimeCtrl m_DateCtrl_LoadDate;
    CTime m_CTime_LoadDate;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnButtonAdministration();
    afx_msg void OnDatetimechangeDatetimeLoaddate(NMHDR* pNMHDR, LRESULT* pResult);
    DECLARE_MESSAGE_MAP()

protected: //members
    CNMDProgress        m_dlgProgress;
    ppCallPlanUndertake m_srvUndertake;
    ppCallPlanLoad*     m_psrvAdmin;
    bool                m_bIsUndertake;
    long                m_lLoadDate;
    CTime               m_actDate;

protected: //methodes
    bool CheckPassword();
    bool SetCurrentAdministration();
    void SetDlgText();
    bool CheckEntries(const bool bText=true, const bool bIsSera=true);
    bool LoadSeraPlan();
    bool LoadPhonPlan();
    bool LoadPlan(bool phonePlan);

protected: //show in progress
    void StartProgress(const CString& csText="");
    void EndProgress();
    void SetProgressCount(const int iPos);
};
