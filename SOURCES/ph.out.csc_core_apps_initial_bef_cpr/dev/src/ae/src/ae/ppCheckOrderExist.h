#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCheckOrderExist.h
   Author: R.Imschweiler
   made  : 30.08.2002
                            >No changes in this text may be made<
   declaration:

*/

#include "ppDadeScroll.h"
#include "ppDataTypes.h"
#include "ppError.h"

class CCHECKORDEREXIST;

class ppCheckOrderExist : public ppDadeScroll<CCHECKORDEREXIST>, virtual public ppError
{
public: //constructor
    ppCheckOrderExist(const short sBranchNo,
                          const ppString& strPath = "c:\\ppErrorMsg",
                          const short sLanguage = 1);
    ppCheckOrderExist(const ppCheckOrderExist& right);
    ~ppCheckOrderExist();

public: //unique selection from data
    long GetOrder(short sVzNr, long lKundenNr, short sZeitdiff, short sAnz);

public: //Data: Set- and Getmethodes
    void SetKdauftragnr(const long kdauftragnr);
    void SetVertriebszentrumnr(const short vertriebszentrumnr);
    void SetKundennr(const long kundennr);
    void SetTm_time(const long time);

    //Get-Methodes
    const long GetKdauftragnr() const;
    const short GetVertriebszentrumnr() const;
    const long GetKundennr() const;
    const long GetTm_time() const;

protected: //data-members
    CCHECKORDEREXIST* m_srvCheckOrder;
    CCHECKORDEREXIST* m_srvCheckOrderUP;
    ppString m_strBuf;
    short m_sBranchNo;
};
