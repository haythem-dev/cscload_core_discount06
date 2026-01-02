#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCustomerCallPlanTour.h
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000
                            >No changes in this text may be made<
   declaration:
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppError.h"
#include "ppCustomerDisplay.h"

class CMCUSTOMERCALLPLANTOUR;

class ppCustomerCallPlanTour : public ppDadeScroll<CMCUSTOMERCALLPLANTOUR>, virtual public ppError
{
public: //constructor
    ppCustomerCallPlanTour(const ppCustomerDisplay* pCustomer,
                           const ppString& strPath = "c:\\ppErrorMsg",
                           const short sLanguage = 1);
    ~ppCustomerCallPlanTour();

public: //check changes
    bool IsChanged();
    void Restore();

public:
    const char* GetCurrentTourID(const ppTime& t, const short sMinutes);

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage();                                 //start to fill the next page
    bool SetPreviousPage();                             //set to previous page
    bool GetNext();                                     //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public: //Data: Set- and Getmethodes
    void SetVertriebsZentrumNr(const short s);
    void SetKundenNr(const long l);
    void SetWeekday(const ppDayType::t_day eDay);
    void SetDatumKommi(const long l);

    // GetMethodes
    const short GetVertriebsZentrumNr() const;
    const short GetKundenNr() const;
    const char* GetTourID();
    const char* GetPreparedTourID();
    const short GetWeekday();
    const short GetFilialNr() const;
    const ppDate GetDatumKommi() const;
    const ppBool GetIstVerbundTour() const;
    const ppTime& GetTourIDTime(const ppString& csTourID="");

protected: //data-members
    CMCUSTOMERCALLPLANTOUR* m_srvTour;
    CMCUSTOMERCALLPLANTOUR* m_srvTourUP;
    const ppCustomerDisplay* m_pCustomer;
    ppString m_str;
    ppTime m_Time;

protected: //methodes
    bool IsInitialized();

private:
    ppCustomerCallPlanTour(const ppCustomerCallPlanTour& cpt);
};
