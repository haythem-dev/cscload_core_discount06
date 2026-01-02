#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppCallPlanLoad.h
   Author: R.von-der-Gruen
   made  : 07.07.2000
                            >No changes in this text may be made<
   declaration:
   Customer-Base-Class
*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppError.h"

class CMCALLPLANLOAD;

class ppCallPlanLoad : public ppDadeScroll<CMCALLPLANLOAD>, virtual public ppError
{
public: //constructor
    ppCallPlanLoad(const ppString& strPath = "c:\\ppErrorMsg",
                      const short sLanguage = 1);
    ppCallPlanLoad(const short sSaleCenterNo,
                      const long lDatum,
                      const ppString& strPath = "c:\\ppErrorMsg",
                      const short sLanguage = 1);
    ~ppCallPlanLoad();

public: //list selection from data, page-scrolling
    bool StartBrowse();                     //start to fill list
    bool GetNext();                         //get data from list
    bool SetNextPage();                     //start to fill the next page
    bool SetElement(const unsigned nPos);   //get an element from list and set to classmembers

public: //check row
    const bool IsAvailable() const;

public: //unique selection from data
    bool GetUni(const bool bAlways = false);
    bool Update();
    bool Delete();
    bool Insert();

public: //Data: Set- and Getmethodes
    void SetVertriebsZentrumNr(const short s);
    void SetDatum(const ppDate& l);
    void SetWochentag(const short s);
    void SetLadeDatum(const ppDate& l);
    void SetLadeVZ(const short s);
    void SetBundesland(const ppString& str);
    void SetTourID(const ppString& str);
    void SetLadeZeitAb(const ppTime t);
    void SetLadeZeitBis(const ppTime t);

    const short     GetVertriebsZentrumNr() const;
    const ppDate    GetDatum() const;
    const ppDayType GetWochenTag();
    const ppDate    GetLadeDatum() const;
    const short     GetLadeVZ();
    const char*     GetBundesLand();
    const char*     GetTourID();
    const ppTime    GetLadeZeitAb() const;
    const ppTime    GetLadeZeitBis() const;

protected:
    bool IsInitialized();
    bool IsDataAvailable();

protected: //data-members
    CMCALLPLANLOAD* m_srvCallPlanLoad;
    CMCALLPLANLOAD* m_srvCallPlanLoadUP;

protected: //data-members
    ppString m_str;
    bool     m_bIsAvailable;
};
