#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCustomerVacation.h
   Author: R.Imschweiler
   made  : 15.08.2001
                            >No changes in this text may be made<
   declaration:
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppError.h"

class CMCUSTOMERVACATION;

class ppCustomerVacation : public ppDadeScroll<CMCUSTOMERVACATION>, virtual public ppError
{
public: //constructor
    ppCustomerVacation(const ppString& strPath = "c:\\ppErrorMsg",
                        const short sLanguage = 1);
    ppCustomerVacation(const short sBranch,
                        const ppString& strPath  = "c:\\ppErrorMsg",
                        const short sLanguage = 1);
    ~ppCustomerVacation();

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
    void SetDatumgueltigab(const long l);
    void SetDatumgueltigbis(const long l);
    // GetMethodes
    const short GetVertriebsZentrumNr() const;
    const long GetKundennr() const;
    const long GetDatumgueltigab() const;
    const long GetDatumgueltigbis() const;

    // GetLengthMethodes
    const ppFieldLength LengthVertriebsZentrumNr() const;
    const ppFieldLength LengthRufzeitVerschieben() const;
    const ppFieldLength LengthAnzrufWiederholung() const;
    const ppFieldLength LengthZeitfensterAuftrag() const;
    const ppFieldLength LengthZeitAnzPosAuftrag() const;
    const ppFieldLength LengthLoginID() const;
    const ppFieldLength LengthDate() const;
    const ppFieldLength LengthTime() const;

protected: //data-members
    CMCUSTOMERVACATION* m_srvVacation;
    CMCUSTOMERVACATION* m_srvVacationUP;

protected: //methodes
    bool IsInitialized();

private:
    ppCustomerVacation(const ppCustomerVacation& cv);
};
