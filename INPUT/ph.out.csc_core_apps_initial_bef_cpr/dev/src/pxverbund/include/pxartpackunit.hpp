/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxArtPackUnit Class.

REVISION HISTORY

19 May 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTPACKUNIT_INC
   #define PXARTPACKUNIT_INC

#include "pxbase/pxrecord.hpp"

struct tARTICLEPACKUNIT;

class pxArtPackUnit : public pxDBRecord
{

public:


// constructors:
                pxArtPackUnit(pxArtPackUnit& src);
                pxArtPackUnit(pxSession *session);
                pxArtPackUnit(pxSession *session, tARTICLEPACKUNIT& src);
// destructor:
                virtual  ~pxArtPackUnit();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArtPackUnit&   operator=(const pxArtPackUnit& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArtPackUnit&   operator=(const tARTICLEPACKUNIT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArtPackUnit&
                Assign(pxArtPackUnit& dest, const tARTICLEPACKUNIT& src);
    friend   tARTICLEPACKUNIT&
                Assign(tARTICLEPACKUNIT& dest, const pxArtPackUnit& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

//  Queries:
    long             ArticleNo()          {return ArticleNo_          ;}
    long             PackingUnit()        {return PackingUnit_        ;}
    short            RoundPct   ()        {return RoundPct_           ;}

protected:
    void        Init();

    long             ArticleNo_          ;     // articlenumber
    long             PackingUnit_        ;     // Packing Unit (VE)
    short            RoundPct_           ;     // Rounding percentage

private:
    friend class pxArtPackUnitList;

};

class pxArtPackUnitList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxArtPackUnitList(pxSession *session);
//  destructor:
                virtual ~pxArtPackUnitList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const long ArticleNo, const int count = 50);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxArtPackUnitListIter;
};

class pxArtPackUnitListIter : public nDListCollectIter
{

public:
// constructors:
    pxArtPackUnitListIter(pxArtPackUnitList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArtPackUnitListIter() {;}
};
#endif
