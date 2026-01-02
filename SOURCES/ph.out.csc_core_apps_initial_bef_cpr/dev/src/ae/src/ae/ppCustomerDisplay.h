#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCustomerDisplay.h
   Author: A.Schmidt-Rehschuh
   made  : 03.02.2000
                            >No changes in this text may be made<
   declaration:
   Customer-Base-Class
*/

#include "ppError.h"
#include "ppDataTypes.h"

class CMCUSTOMERDISPLAY;

class ppCustomerDisplay : virtual public ppError
{
public:
    enum t_adress
    {
        t_mister  = 1,
        t_miss    = 2,
        t_mrs     = 3,
        t_company = 4
    };

public: //constructor
    ppCustomerDisplay(const ppString& strPath = "c:\\ppErrorMsg",
                      const short sLanguage = 1);
    ppCustomerDisplay(const short sSaleCenterNo,
                      const long lCustomerNo,
                      const ppString& strPath = "c:\\ppErrorMsg",
                      const short sLanguage = 1);
    ~ppCustomerDisplay();

public: //check changes
    bool IsChanged();
    void Restore();

public: //unique selection from data
    bool GetUni();
    bool Update(); //only telephono.
    bool UpdPropetries(); //only kundeschalter!
    const ppCustomerDisplay* m_pCustomer;

public: //Data: Set- and Getmethodes
    const long GetIdfNr() const;
    const char* GetNameApo();
    const char* GetNameInhaber();
    const char* GetStrasse();
    const char* GetOrt();
    const char* GetPostleitZahl();
    const short GetFilialNr() const;
    const short GetVertriebsZentrumNr() const;
    const long GetKundenNr() const;
    const t_adress GetAnredeKz() const;
    const char* GetTelnr();
    const char* GetTelnrDafue();
    const char* GetTelKurzwahl();
    const ppBool GetSkdKundeAeGesperrt() const;
    const ppBool GetSkdAnrufGenerell() const;

    void SetVertriebsZentrumNr(short t);
    void SetKundenNr(long t);
    void SetTelnr(const ppString& s);
    void SetTelnrDafue(const ppString& s);
    void SetTelKurzwahl(const ppString& s);
    void SetSkdAnrufGenerell(const ppBool& b);

protected:
    bool IsInitialized();

protected: //data-members
    CMCUSTOMERDISPLAY* m_srvCustomer;
    CMCUSTOMERDISPLAY* m_srvCustomerUP;

protected: //data-members
    ppString m_str;

private:
    ppCustomerDisplay(const ppCustomerDisplay& cd);
};
