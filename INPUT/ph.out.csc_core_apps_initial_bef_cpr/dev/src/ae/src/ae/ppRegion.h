#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppRegion.h
   Author: A.Schmidt-Rehschuh
   made  : 21.07.2000
                            >No changes in this text may be made<
   declaration:
   Customer-Base-Class
*/

#include "ppdadescroll.h"
#include "ppdatatypes.h"
#include "pperror.h"

class CMREGION;
class ppRegion : public ppDadeScroll<CMREGION>, virtual public ppError
{
public:
    enum t_region
    {
        r_salecenter  = 1,
        r_modem       = 2,
        r_ksc         = 3,
        r_out_of_area
    };

public: //constructor
    ppRegion(const ppString& strPath = "c:\\ppErrorMsg",
             const short sLanguage = 1);

    ppRegion(const short sRegionNo,
             const t_region eRegion,
             const ppString& strPath = "c:\\ppErrorMsg",
             const short sLanguage = 1);
    ~ppRegion();

public: //unique selection from data
    bool Insert();
    bool Delete();

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage();                                 //start to fill the next page
    bool SetPreviousPage();                             //set to previous page
    bool GetNext();                                     //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public: //Data: Set- and Getmethodes
    void SetRegionNr(const short sSaleCenterNo);
    void SetRegionenTyp(const t_region eRegion);
    void SetLoginID(const long l);
    void SetRegionTeilNr(const short s);
    //Get-Methodes
    const short GetRegionNr() const;
    const short GetRegionTeilNr() const;
    const ppRegion::t_region GetRegionenTyp() const;
    const char* GetName();
    const ppDate GetDate() const;
    const ppTime GetTime() const;
    const long GetLoginID() const;

protected:
    bool IsInitialized();

protected: //data-members
    CMREGION* m_srvRegion;
    CMREGION* m_srvRegionUP;
    ppString  m_str;
};
