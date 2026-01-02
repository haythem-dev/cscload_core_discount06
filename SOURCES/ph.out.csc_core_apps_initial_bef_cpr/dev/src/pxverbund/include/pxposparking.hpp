#ifndef PXPOSPARKING_INC
#define PXPOSPARKING_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>

struct tPOSITIONPARKING;

class pxPosParking : public pxDBRecord
{

public:
// constructors:
                pxPosParking(pxPosParking& src);
                pxPosParking(pxSession *session);
                pxPosParking(pxSession *session, tPOSITIONPARKING& src);
                pxPosParking(pxSession *session,
                             short BranchNo,
                             long  CustomerNo,
                             long  ArticleNo,
                             long  OrderNo,
                             long  OrderQty
                             );
// destructor:
                virtual  ~pxPosParking();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxPosParking&   operator=(const pxPosParking& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxPosParking&   operator=(const tPOSITIONPARKING& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxPosParking&
                Assign(pxPosParking& dest, const tPOSITIONPARKING& src);
    friend   tPOSITIONPARKING&
                Assign(tPOSITIONPARKING& dest, const pxPosParking& src);

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

//  Field updates

//  Queries:
    short             BranchNo()           {return BranchNo_          ;}
    long              CustomerNo()         {return CustomerNo_        ;}
    long              ArticleNo()          {return ArticleNo_         ;}
    nDate&            Date()               {return Date_              ;}
    long              OrderNoOrg()         {return OrderNoOrg_        ;}
    long              OrderQty()           {return OrderQty_          ;}

protected:
    void              Init();

    short             BranchNo_          ;      // Branch number
    long              CustomerNo_        ;      // Customernumber
    long              ArticleNo_         ;      // Article number
    nDate             Date_              ;      // Date
    long              OrderNoOrg_        ;      // Original ordnumber
    long              OrderQty_          ;      // Quantity ordered

private:
    friend class pxPosParkingList;
};

class pxPosParkingList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxPosParkingList(pxSession *session);
//  destructor:
                virtual ~pxPosParkingList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo, const long CustomerNo,
                         const long  ArticleNo, const int  count = 50 );
    size_t      Select ( const short BranchNo, const long CustomerNo,
                         const long  ArticleNo, const nDate& Date,
                         const long  OrderNo,  const int  count = 50 );
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxPosParkingListIter;
};

class pxPosParkingListIter : public nDListCollectIter
{

public:
// constructors:
    pxPosParkingListIter(pxPosParkingList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxPosParkingListIter() {;}
};
#endif
