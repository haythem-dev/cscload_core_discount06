#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCustomerCallPlan.h
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000
                            >No changes in this text may be made<
   declaration:
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppCustomerDisplay.h"
#include "ppCallPlanEvents.h"

class CMCUSTOMERCALLPLAN;

class ppCustomerCallPlan : public ppDadeScroll<CMCUSTOMERCALLPLAN>, public ppCallPlanEvents, virtual public ppError
{
public:
    enum t_calltype
    {
        t_is_normal   = 0,
        t_is_special  = 1,
        t_is_notcall  = 2,
        t_is_disabled = 3
    };

    enum t_type
    {
        c_normal = 0,
        c_print  = 1
    };

public: //constructor
    ppCustomerCallPlan(const ppCustomerDisplay* pCustomer, const ppDayType& Day = 0);
    ~ppCustomerCallPlan();

public: //check changes
    bool IsChanged();
    void Restore();

public: //unique selection from data
    bool GetUni();
    bool Update();
    bool Insert();
    bool Delete();                                      //if delete is succesful all data set to zero
    bool DeleteGeneral();                               //delete completly one type of Calltype
    bool UpdateGeneral();                               //update completly one type of Calltype
    bool InsertGeneral();                               //insert completly one type of Calltype
    bool DeleteGeneralWithoutSaturday();                //delete completly one type of Calltype
    bool UpdateGeneralWithoutSaturday();                //update completly one type of Calltype
    bool InsertGeneralWithoutSaturday();                //insert completly one type of Calltype
    bool DestroyCompletly();                            //delete all entry of customer!
    bool EnableCompletly(const bool bEnable);           //dis/enabled all calls of a customer
    bool CheckAllDisabled();

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage(const t_type eTyp = c_normal);     //start to fill the next page
    bool SetPreviousPage();                             //set to previous page
    bool GetNext(const t_type eTyp = c_normal);         //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public: //Data: Set- and Getmethodes
    void SetOldTime(const long lOldTime);
    void SetUrRufzeit(const long lUrRufzeit);
    void SetRufProtokoll(const t_callrecord rufProtokoll);
    void SetRufProtokoll(const ppString& rufProtokoll);
    void SetRufSteuerung(const t_calltime eCallTime);
    void SetPoolNr(const short sPoolNr);
    void SetModemPoolNr(const short sModemPoolNr);
    void SetRufEinstellung(const ppBool& bRufEinstellung);
    void SetDoNotCall(const ppBool& bDoNotCall);
    void SetSpecialCall(const ppBool& bSpecialCall);
    void SetNormalCall(const ppBool& bNormalCall = true);
    void SetCallDisabled(const ppBool& bCallDisabled);
    void SetTourID(const ppString& tourID);
    void SetSkdAnrufGenerell(const ppBool& bSkdanrufgenerell);
    void SetAllCallsAreDisabled(const bool bAllCallsAreDisabled);
    void SetLoginID(const long loginID);
    void SetBemerkung(const ppString& bemerkung);
    // GetMethodes
    const ppCustomerDisplay* GetCustomer() const;
    const long  GetKundenNr() const;
    const short GetVertriebsZentrumNr() const;
    const long GetUrRufzeit() const;
    const char* GetRufProtokollText() const;
    const t_callrecord GetRufProtokoll() const;
    const t_calltime GetRufSteuerung() const;
    const short GetPoolNr() const;
    const short GetModemPoolNr() const;
    const ppBool GetRufEinstellung() const;
    const bool GetDoNotCall() const;
    const bool GetSpecialCall() const;
    const bool GetNormalCall() const;
    const ppBool GetCallDisabled() const;
    const char* GetAnrufTyp() const;
    const long GetLoginID() const;
    const short GetTagNr() const;
    const char* GetTourID();
    const ppBool GetSkdAnrufGenerell() const;
    const bool IsAllCallsAreDisabled() const;
    const char* GetBemerkung();

protected: //data-members
    const ppCustomerDisplay* m_pCustomer;
    CMCUSTOMERCALLPLAN* m_srvCustomer;
    CMCUSTOMERCALLPLAN* m_srvCustomerUP;
    char m_szaCallRecord[4][3];
    char m_szaCallType[4][21];
    bool m_bIsTimeChange;
    bool m_bAllCallsAreDisabled;
    ppString m_str;

protected: //methodes
    void SetCallDisabledAll();
    bool IsInitialized();
};
