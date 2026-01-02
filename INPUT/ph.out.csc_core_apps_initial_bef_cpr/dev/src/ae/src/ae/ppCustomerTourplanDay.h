#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCustomerTourplanDay.h
   Author: A.Schmidt-Rehschuh
   made  : 24.05.2000
                            >No changes in this text may be made<
   declaration:
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppCustomerDisplay.h"

class CMCUSTOMERTOURPLANDAY;

class ppCustomerTourplanDay : public ppDadeScroll<CMCUSTOMERTOURPLANDAY>, virtual public ppError
{
public: //constructor
    ppCustomerTourplanDay(const ppCustomerDisplay* pCustomer);
    ~ppCustomerTourplanDay();

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage();                                 //start to fill the next page
    bool SetPreviousPage();                             //set to previous page
    bool GetNext();                                     //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public:
    const char* GetCurrentTourID(const ppTime& t, const short sMinutes);

public: //Data: Set- and Getmethodes
    void SetVertriebsZentrumNr(const short s);
    void SetKundenNr(const long l);

    //Get-Methodes
    const long  GetKundenNr() const;
    const short GetVertriebsZentrumNr() const;
    const char* GetTourID();
    const char* GetPreparedTourID();
    const ppBool GetIstVerbundTour() const;

protected: //data-members
    CMCUSTOMERTOURPLANDAY* m_srvCustomer;
    CMCUSTOMERTOURPLANDAY* m_srvCustomerUP;
    ppString m_str;
};
