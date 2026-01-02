/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxCustBaseInformation Class

REVISION HISTORY

23 April   2008 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCUSTBASEINFORMATION_INC
   #define PXCUSTBASEINFORMATION_INC

#include "pxbase/pxrecord.hpp"

struct tKNDAUSKU;

class pxCustBaseInformation : public pxDBRecord
{

public:

// constructors:
                pxCustBaseInformation(pxCustBaseInformation& src);
                pxCustBaseInformation(pxSession *session);
                pxCustBaseInformation(pxSession *session, tKNDAUSKU& src);
                pxCustBaseInformation(pxSession *session, const pxCustBaseInformation* src);
                pxCustBaseInformation(pxSession *session, const short BranchNo, const long KundenNr);
// destructor:
                virtual  ~pxCustBaseInformation();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustBaseInformation&   operator=(const pxCustBaseInformation& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustBaseInformation&   operator=(const tKNDAUSKU& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustBaseInformation&
                Assign(pxCustBaseInformation& dest, const tKNDAUSKU& src);
    friend   tKNDAUSKU&
                Assign(tKNDAUSKU& dest, const pxCustBaseInformation& src);

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);

//  Field updates


//  Queries:
    short            VertriebszentrumNr()       {return VertriebszentrumNr_      ;}
    long             KundenNr()                 {return KundenNr_                ;}
    double          EilbotenZuschlag()         {return EilbotenZuschlag_        ;}
    double          DispoGebuehr()             {return DispoGebuehr_            ;}
    double          BTMGebuehr()               {return BTMGebuehr_              ;}
    double          DokuGebuehr()              {return DokuGebuehr_             ;}
    double          LogistikAufschlag()        {return LogistikAufschlag_       ;}

protected:
    void        Init();

    short      VertriebszentrumNr_  ;    // Branchnumber
    long       KundenNr_            ;    // Kundennummer
    double    EilbotenZuschlag_    ;    // Eilbotenzuschlag
    double    DispoGebuehr_        ;    // Dispogebuehr
    double    BTMGebuehr_          ;    // BTM Gebuehr
    double    DokuGebuehr_         ;    // Doku Gebuehr
    double    LogistikAufschlag_   ;    // Logistikaufschlag

private:


};
#endif
