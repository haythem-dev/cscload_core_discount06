#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCustomerCallPlanDay.h
   Author: A.Schmidt-Rehschuh
   made  : 28.04.2000
                            >No changes in this text may be made<
   declaration:
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppCustomerDisplay.h"
#include "ppCallPlanEvents.h"

class CMCUSTOMERCALLPLANDAY;

class ppCustomerCallPlanDay : public ppDadeScroll<CMCUSTOMERCALLPLANDAY>, public ppCallPlanEvents, virtual public ppError
{
public:
    enum t_calltyp
    {
        c_normal   = 0,
        c_ready    = 1,
        c_rejected = 2
    };

public: //constructor
    ppCustomerCallPlanDay(const short sBranchNo,
                          const ppString& strPath = "c:\\ppErrorMsg",
                          const short sLanguage = 1);
    ppCustomerCallPlanDay(const ppCustomerCallPlanDay& right);
    ~ppCustomerCallPlanDay();

public: //check changes
    bool IsChanged();
    void Restore();
    void Clear();

public: //unique selection from data
    bool GetUni();
    bool Update(const bool bPostbone = false);
    bool UpdateDirect();
    bool SetCallToFree();
    bool Insert();
    bool Delete();                                      //if delete is succesful all data set to zero

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage(const t_calltyp eTyp = c_normal);  //start to fill the next page
    bool SetPreviousPage();                              //set to previous page
    bool GetNext(const t_calltyp eTyp = c_normal);      //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public: //Data: Set- and Getmethodes
    void SetKundenNr(const long l);
    void SetIdfnr(const long l);
    void SetVertriebsZentrumNr(const short s);
    void SetDatum(const long l);
    void SetUrRufzeit(const ppTime t);
    void SetRufzeit(const ppTime& t);
    void SetUmkStatus(const short s);
    void SetAnrufStatus(const t_callstate s);
    void SetAnrufZaehler(const short s);
    void SetTourID(const ppString& str);
    void SetTagNr(const short s);
    void SetSTourDefinitiv(const ppBool& b);
    void SetRufProtokoll(const t_callrecord e);
    void SetRufSteuerung(const t_calltime eCallTime);
    void SetRufEinstellung(const ppBool& b);
    void SetUID(const long l);
    void SetAnrufEreignis(const t_cEvents eEvent);
    void SetSkdAnrufGenerell(const ppBool& b);

    //Get-Methodes
    const long  GetKundenNr() const;
    const short GetVertriebsZentrumNr() const;
    const long  GetIdfNr() const;
    const char* GetNameApo();
    const char* GetOrt();
    const char* GetTelNr();
    const char* GetTelKurzWahl();
    const char* GetKzKDKlasse();
    const long GetDatum() const;
    const ppTime& GetUrRufzeit();
    const ppTime& GetRufzeit();
    const short GetUmkStatus() const;
    const t_callstate GetAnrufStatus() const;
    const short GetPoolNr() const;
    const short GetAnrufZaehler() const;
    const short GetModemPoolNr() const;
    const short GetTagNr() const;
    const char* GetTourID();
    const char* GetPreparedTourID();
    const ppBool GetSTourDefinitiv() const;
    const char GetAnruftyp() const;
    const t_callrecord GetRufProtokoll() const;
    const t_calltime GetRufSteuerung() const;
    const char GetRufEinstellung() const;
    const ppBool GetSkdAnrufGenerell() const;

protected: //data-members
    CMCUSTOMERCALLPLANDAY* m_srvCustomer;
    CMCUSTOMERCALLPLANDAY* m_srvCustomerUP;
    ppString m_strBuf;
    ppTime m_TimeBuf;
    t_callstate m_Callstate;
    long m_lCallTime;
    long m_lIdfNr;
    long m_lUID;
    bool m_bIsInitialized;
    bool m_bEndSession;
    short m_sBranchNo;

protected: //methodes
    bool IsInitialized(const bool bIsUpdate=false);
    void SetHistoryData();
    void UnSetHistoryData();
    bool CheckCurrentCall(CMCUSTOMERCALLPLANDAY* srvCheck, const bool bPostbone);
};
