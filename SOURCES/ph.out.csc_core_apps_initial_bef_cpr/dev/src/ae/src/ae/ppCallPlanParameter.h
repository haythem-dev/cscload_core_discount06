#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCallPlanParameter.h
   Author: A.Schmidt-Rehschuh
   made  : 17.04.2000
                            >No changes in this text may be made<
   declaration:

*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppError.h"

class CMCALLPARAMATER;

class ppCallPlanParameter : public ppDadeScroll<CMCALLPARAMATER>, virtual public ppError
{
public: //constructor
    ppCallPlanParameter(const ppString& strPath = "c:\\ppErrorMsg",
                        const short sLanguage = 1);
    ppCallPlanParameter(const short sBranch,
                        const ppString& strPath  = "c:\\ppErrorMsg",
                        const short sLanguage = 1);
    ~ppCallPlanParameter();

public: //check changes
    bool IsChanged();
    void Restore();

public: //unique selection from data
    bool GetUni();
    bool Update();
    bool Insert();
    bool Delete();                                      //if delete is succesful all data set to zero

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage();                                 //start to fill the next page
    bool SetPreviousPage();                             //set to previous page
    bool GetNext();        //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public: //Data: Set- and Getmethodes
    void SetVertriebsZentrumNr(const short s);
    void SetRufzeitVerschieben(const short s);
    void SetAnzrufWiederholung(const short s);
    void SetUmkrufWiederholung(const short s);
    void SetZeitfensterAuftrag(const short s);
    void SetZeitAnzPosAuftrag(const short s);
    void SetKabrufWiederholung(const short s);
    void SetLoginID(const long l);
    void SetAnzRufVerschieben(const short s);
    void SetMinRufVerschieben(const short s);
    void SetCallplanStartStop(const ppBool& b);
    void SetStopStartZeit(const ppTime& t);
    // GetMethodes
    const short GetVertriebsZentrumNr() const;
    const short GetRufzeitVerschieben() const;
    const short GetAnzrufWiederholung() const;
    const short GetUmkrufWiederholung() const;
    const short GetKabrufWiederholung() const;
    const short GetZeitfensterAuftrag() const;
    const short GetZeitAnzPosAuftrag() const;
    const long GetLoginID() const;
    const ppDate GetDate() const;
    const ppTime GetTime() const;
    const short GetRufabweichungPH() const;
    const short GetRufabweichungDP() const;
    const short GetRufabweichungDS() const;
    const short GetAnzRufVerschieben() const;
    const short GetMinRufVerschieben() const;
    const ppBool GetCallplanStartStop() const;
    const ppTime GetStopStartZeit() const;

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
    CMCALLPARAMATER* m_srvParameter;
    CMCALLPARAMATER* m_srvParameterUP;

protected: //methodes
    bool IsInitialized();
};
