/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXTAXTAB.HPP
Customer Group Class.

REVISION HISTORY

13 Nov 1995 V1.00 REV 00 written by Peter Hoernich.
*/

#ifndef PXTAXTAB_INC
   #define PXTAXTAB_INC

#include "pxbase/pxrecord.hpp"

struct tTAXTAB;

class pxTaxTab : public pxDBRecord
{
public:
// destructor:
    virtual           ~pxTaxTab();
// constructors:
                      pxTaxTab(pxTaxTab& src);
                      pxTaxTab(pxSession *session);

    pxTaxTab&      operator=(const pxTaxTab& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    char           TaxArt()			{return TaxArt_;                    }
    long           TaxVonDm()			{return TaxVonDm_      ;}
    long           TaxProz()			{return TaxProz_      ;}
    long           TaxBetrag()			{return TaxBetrag_      ;}
    long           TaxFixpreis()		{return TaxFixpreis_      ;}
    long           TaxMaxBetrag()      {return TaxMaxBetrag_      ;}

protected:
	pxTaxTab(pxSession *session, tTAXTAB& src);
    pxTaxTab&      operator=(const tTAXTAB& src);
    
	friend
    pxTaxTab&      Assign(pxTaxTab& dest, const tTAXTAB& src);
    
	friend
    tTAXTAB&    Assign(tTAXTAB& dest, const pxTaxTab& src);
    
	virtual  int      CompareTo(const nCollectable *that, void *p, const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    char TaxArt_;    
	long TaxVonDm_;
    long TaxProz_;
    long TaxBetrag_;
    long TaxFixpreis_;
    long TaxMaxBetrag_;

private:
    friend class pxTaxTabList;
};

class pxTaxTabList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxTaxTabList() {Clear();}
                      pxTaxTabList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
	size_t            Select(const char TaxArt, const int TaxVonDm, const int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxTaxTabListIter;
};

class pxTaxTabListIter : public nDListCollectIter
{

public:
// constructors:
    pxTaxTabListIter(pxTaxTabList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxTaxTabListIter() {;}

};

#endif
