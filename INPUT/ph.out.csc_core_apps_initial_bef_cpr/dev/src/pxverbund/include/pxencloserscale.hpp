/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxencloserscale.hpp
ENCLOSERSCALE class

REVISION HISTORY

12 Dec 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXENDCLOSERSCALE_INC
   #define PXENCLOSERSCALE_INC

#include "pxbase/pxrecord.hpp"

struct tENCLOSERSCALE;

class pxEncloserScale : public pxDBRecord
{

public:

// constructors:
                pxEncloserScale(pxEncloserScale& src);
                pxEncloserScale(pxSession *session);
                pxEncloserScale(pxSession *session, tENCLOSERSCALE& src);
                pxEncloserScale(pxSession *session, const pxEncloserScale* src);
                pxEncloserScale(pxSession *session, short BranchNo,
                                                 long  CustomerNo,
                                                 short TimeDiff,
                                                 short MaxPositions);

// destructor:
                virtual  ~pxEncloserScale();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxEncloserScale&   operator=(const pxEncloserScale& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxEncloserScale&   operator=(const tENCLOSERSCALE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxEncloserScale&
                Assign(pxEncloserScale& dest, const tENCLOSERSCALE& src);
    friend   tENCLOSERSCALE&
                Assign(tENCLOSERSCALE& dest, const pxEncloserScale& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

// Update Fields

//  Queries:
    short          BranchNo()       {return BranchNo_             ;}
    long           CustomerNo()     {return CustomerNo_           ;}
    short          TimeDiff()       {return TimeDiff_             ;}
    short          MaxPositions()   {return MaxPositions_         ;}

// Set Methodes


protected:
    void        Init();

    short      BranchNo_           ;      // Branch Number
    long       CustomerNo_         ;      // Customer Number
    short      TimeDiff_           ;      // Timediff MM
    short      MaxPositions_       ;      // MaxPositions


private:
    friend class pxEncloserScaleList;
};

class pxEncloserScaleList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxEncloserScaleList(pxSession *session);
//  destructor:
                virtual ~pxEncloserScaleList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  CustomerNo,
                         const int   count  = 1000
                       );
// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);
    pxEncloserScale*  FindNearest( const long TimeSlot);


protected:

private:

    friend class pxEncloserScaleListIter;
};

class pxEncloserScaleListIter : public nDListCollectIter
{

public:
// constructors:
    pxEncloserScaleListIter(pxEncloserScaleList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxEncloserScaleListIter() {;}
};
#endif
