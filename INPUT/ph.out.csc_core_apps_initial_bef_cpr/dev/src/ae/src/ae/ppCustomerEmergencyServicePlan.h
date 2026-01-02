#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCustomerEmergencyServicePlan.h
   Author: R.Imschweiler
   made  : 09.05.2001
                            >No changes in this text may be made<
   declaration:
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppError.h"

class CMCUSTOMEREMERGENCYSERVICEPLAN;

class ppCustomerEmergencyServicePlan : public ppDadeScroll<CMCUSTOMEREMERGENCYSERVICEPLAN>, virtual public ppError
{
public: //constructor
    ppCustomerEmergencyServicePlan(const ppString& strPath = "c:\\ppErrorMsg",
                        const short sLanguage = 1);
    ppCustomerEmergencyServicePlan(const short sBranch,
                        const ppString& strPath  = "c:\\ppErrorMsg",
                        const short sLanguage = 1);
    ~ppCustomerEmergencyServicePlan();

public: //check changes
    bool IsChanged();
    void Restore();

public: //unique selection from data
    bool GetUni();
    bool SelList();
    bool SelListHist();
    bool Update();
    bool Insert();
    bool Delete();                                      //if delete is succesful all data set to zero

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage();                                 //start to fill the next page
    bool SetPreviousPage();                             //set to previous page
    bool GetNext();                                     //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public: //Data: Set- and Getmethodes
    void SetVertriebsZentrumNr(const short s);
    void SetKundennr(const long l);
    void SetDatum(const long l);
    void SetUhrzeitvon(const long l);
    void SetUhrzeitbis(const long l);
    void SetIsbtm(const short s);
    void SetIskk(const short s);
    void SetIsk08(const short s);
    void SetIsk20(const short s);
    void SetBemerkungen(const char* str);
    // GetMethodes
    const short GetVertriebsZentrumNr() const;
    const long GetKundennr() const;
    const long GetDatum() const;
    const long GetUhrzeitvon() const;
    const long GetUhrzeitbis() const;
    const short GetIsbtm();
    const short GetIskk();
    const short GetIsk08();
    const short GetIsk20();
    const char* GetBemerkungen();

    // GetLengthMethodes
    const ppFieldLength LengthVertriebsZentrumNr() const;
    const ppFieldLength LengthRufzeitVerschieben() const;
    const ppFieldLength LengthAnzrufWiederholung() const;
    const ppFieldLength LengthZeitfensterAuftrag() const;
    const ppFieldLength LengthZeitAnzPosAuftrag() const;
    const ppFieldLength LengthLoginID() const;
    const ppFieldLength LengthDate() const;
    const ppFieldLength LengthTime() const;
    const ppFieldLength LengthBemerkungen() const;

protected: //data-members
    CMCUSTOMEREMERGENCYSERVICEPLAN* m_srvServicePlan;
    CMCUSTOMEREMERGENCYSERVICEPLAN* m_srvServicePlanUP;
    ppString m_strBuf;

protected: //methodes
    bool IsInitialized();

private:
    ppCustomerEmergencyServicePlan(const ppCustomerEmergencyServicePlan& cesp);
};
