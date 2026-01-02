#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppSaleCenter.h
   Author: A.Schmidt-Rehschuh
   made  : 29.08.2000
                            >No changes in this text may be made<
   declaration:
   Customer-Base-Class
*/

#include "ppdadescroll.h"
#include "pperror.h"

class CMSALECENTER;
class ppSaleCenter : public ppDadeScroll<CMSALECENTER>, virtual public ppError
{
public: //constructor
    ppSaleCenter(const ppString& strPath = "c:\\ppErrorMsg",
                 const short sLanguage = 1);

    ~ppSaleCenter();

public: //list selection from data, page-scrolling
    bool StartBrowse();                                 //start to fill list
    bool SetNextPage();                                 //start to fill the next page
    bool SetPreviousPage();                             //set to previous page
    bool GetNext();                                     //get data from list
    bool SetElement(const unsigned nPos);               //get an element from list and set to classmembers

public: //Data: Set- and Getmethodes
    //Get-Methodes
    const short GetFilialNr() const;
    const char* GetName();

protected: //data-members
    CMSALECENTER* m_srvSaleCenter;
    CMSALECENTER* m_srvSaleCenterUP;
    ppString m_str;
};
