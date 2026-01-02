#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCustomerCallPlanDayHist.h
   Author: A.Schmidt-Rehschuh
   made  : 28.04.2000
                            >No changes in this text may be made<
   declaration:
*/

#include "ppCustomerCallPlanDay.h"

class CMCUSTOMERCALLPLANDAYHIST;

class ppCustomerCallPlanDayHist : public ppDadeScroll<CMCUSTOMERCALLPLANDAYHIST>, public ppCallPlanEvents, virtual public ppError
{
public: //constructor
    ppCustomerCallPlanDayHist(const ppCustomerCallPlanDay* pCallPlanDay);
    ~ppCustomerCallPlanDayHist();

public: //list selection from data, page-scrolling
    bool StartBrowse();                     //start to fill list
    bool SetNextPage();                     //start to fill the next page
    bool SetPreviousPage();                 //set to previous page
    bool GetNext();                         //get data from list
    bool SetElement(const unsigned nPos);   //get an element from list and set to classmembers

public: //Data: Set- and Getmethodes
    void SetKundenNr(const long l);
    void SetVertriebsZentrumNr(const short s);
    void SetDatum(const long l);
    void SetUrRufzeit(const ppTime& t);

    //Get-Methodes
    const long  GetKundenNr() const;
    const short GetVertriebsZentrumNr() const;
    const long GetDatum() const;
    const ppTime& GetUrRufzeit();
    const ppTime& GetRufzeit();
    const short GetUmkStatus() const;
    const t_callstate GetAnrufStatus() const;
    const t_cEvents GetEreignis() const;
    const short GetFilialNr() const;
    const long GetModemNr() const;
    const ppTime GetUhrzeit() const;
    const char* GetGeraeteID();
    const char* GetUser();
    const char* GetEventMsg() const;

protected: //data-members
    CMCUSTOMERCALLPLANDAYHIST* m_srvCustomer;
    CMCUSTOMERCALLPLANDAYHIST* m_srvCustomerUP;
    const ppCustomerCallPlanDay* m_pCallPlanDay;
    ppString m_strBuf;
    ppTime m_TimeBuf;

protected: //methodes
    bool IsInitialized();
};
