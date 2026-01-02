/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxHoliDay Class.

REVISION HISTORY

19 May 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXHOLIDAY_INC
#define PXHOLIDAY_INC

#include "pxbase/pxrecord.hpp"

class nDate;
struct tFEIERTAG;

class pxHoliDay : public pxDBRecord
{

public:


// constructors:
                pxHoliDay(pxHoliDay& src);
                pxHoliDay(pxSession *session);
                pxHoliDay(pxSession *session, tFEIERTAG& src);
                pxHoliDay(pxSession *session, const pxHoliDay* src);
                pxHoliDay(pxSession *session, const short FilialNr, const short Modus, const short Tag);
// destructor:
                virtual  ~pxHoliDay();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxHoliDay&   operator=(const pxHoliDay& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxHoliDay&   operator=(const tFEIERTAG& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxHoliDay&
                Assign(pxHoliDay& dest, const tFEIERTAG& src);
    friend   tFEIERTAG&
                Assign(tFEIERTAG& dest, const pxHoliDay& src);

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

//  Queries:
    short            FilialNr()           {return FilialNr_           ;}
    short            Modus   ()           {return Modus_              ;}
    short            Tag     ()           {return Tag_                ;}
    short            VonJahr ()           {return Von_Jahr_           ;}
    short            BisJahr ()           {return Bis_Jahr_           ;}
    long             Datum   ()           {return Datum_              ;}

protected:
    void        Init();

    short      FilialNr_          ;      // Branchnumber
    short      Modus_             ;      // Modus
    short      Tag_               ;      // Tag
    short      Von_Jahr_          ;      // ab
    short      Bis_Jahr_          ;      // bis
    long       Datum_             ;      // Datum (YYYYMMDD)

private:
    friend class pxHoliDayList;

};

class pxHoliDayList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxHoliDayList(pxSession *session);
//  destructor:
                virtual ~pxHoliDayList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short FilialNr,const int     count = 50);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int      GetNext(const void* record, const int cursorid);
    virtual  int      StartBrowse(const void *keys, const int cursorid);
    virtual  int      EndBrowse(const int cursorid);
    pxHoliDay*        Find( const short Modus, const short Tag, const short VZ);
    pxHoliDay*        Find( const long datum, const short VZ);
    short             Find( const short BranchNo);
    bool              CheckDateForHoliday( const nDate& date, const short VZ );
    long              CalculateNextWorkDay( const nDate& date, const short VZ );
    int               CalculateDates();
protected:

private:
    friend class pxHoliDayListIter;
};

class pxHoliDayListIter : public nDListCollectIter
{

public:
// constructors:
    pxHoliDayListIter(pxHoliDayList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxHoliDayListIter() {;}
};
#endif
