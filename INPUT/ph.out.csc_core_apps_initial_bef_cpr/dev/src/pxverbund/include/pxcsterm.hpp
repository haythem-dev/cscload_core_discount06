/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXCSTERM.HPP
Customer terms class.

REVISION HISTORY

23 Oct 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#ifndef PXCSTERM_DOTH
#define PXCSTERM_DOTH

#include "pxbase/pxrecord.hpp"

struct tKUNDEKONDI;

class pxCustTerms : public pxDBRecord
{

public:
    virtual           ~pxCustTerms();
                      pxCustTerms(pxSession *session);
                      pxCustTerms(pxCustTerms& src);
                      pxCustTerms(pxSession *session, short VZNR, long KdNr,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxCustTerms&   operator=(const pxCustTerms& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

//  Queries:
    long             IDFNr()              const    {return IDFNr_;             }
    short            VertriebszentrumNr() const    {return VertriebszentrumNr_;}
    long             KundenNr()           const    {return KundenNr_;          }
    double           BuendelRundungProz() const    {return BuendelRundungProz_;}
    short            TagAutoValuta()      const    {return TagAutoValuta_;     }
    short            ValutaTageMax()      const    {return ValutaTageMax_;     }

protected:
                pxCustTerms(pxSession *session, tKUNDEKONDI& src);
    pxCustTerms&   operator=(const tKUNDEKONDI& src);
    friend pxCustTerms& Assign(pxCustTerms& dest, const tKUNDEKONDI& src);
    friend tKUNDEKONDI&  Assign(tKUNDEKONDI& dest, const pxCustTerms& src);
    virtual  int     Read(const void *record);
    void              Init();

    long       IDFNr_;                 // Kundennummer IDF
    short      VertriebszentrumNr_;    // VZ
    long       KundenNr_;              // Kundennummer
    double     BuendelRundungProz_;    // Buendel Rundung Prozent
    short      TagAutoValuta_;         // Tag ab wann valuta Monate gilt
    short      ValutaTageMax_;         // Maximal anzahl Tage Valuta (CR)

private:
    friend class pxCustTermsList;
};

class pxCustTermsList : public nDListCollect, public nDBRecordSet
{

public:
    virtual           ~pxCustTermsList() {Clear();}
                      pxCustTermsList(pxSession *session);

    pxSession*        Session()       { return (pxSession*) DataBase();}
    size_t            Select ( const int count = 3000 );
    void              Clear()        {nDBRecordSet::Clear();}

protected:
    size_t            Select ( tKUNDEKONDI *a,  const int count = 3000 );
    virtual  int     EndBrowse(const int cursorid);
    virtual  nCollectable* AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);

private:
    friend class pxCustTermsListIter;
};

class pxCustTermsListIter : public nDListCollectIter
{

public:
    pxCustTermsListIter(pxCustTermsList& list) : nDListCollectIter(list) {;}
    virtual  ~pxCustTermsListIter() {;}
};

#endif
