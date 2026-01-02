/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXCUSTOMERSPECIALS
Customer Specials  Class.

*/

#ifndef PXCUSTOMERSPECIALS_INC
#define PXCUSTOMERSPECIALS_INC

#include "pxbase/pxrecord.hpp"

struct tCUSTOMERSPECIALS;

class pxCustomerSpecials : public pxDBRecord
{
public:


// destructor:
    virtual           ~pxCustomerSpecials();
// constructors:
                      pxCustomerSpecials(pxCustomerSpecials& src);
                      pxCustomerSpecials(pxSession *session);
                      pxCustomerSpecials(pxSession *session, const pxCustomerSpecials* src);
                      pxCustomerSpecials(pxSession *session, short BranchNo, long CustomerNo, short WeekDay,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxCustomerSpecials&      operator=(const pxCustomerSpecials& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

//  Queries:

    short             BranchNo        () {return BranchNo_;                       }
    long              CustomerNo      () {return CustomerNo_;                     }
    long              UW_IDF          () {return UW_IDF_;                         }
    nString&          UW_Tour         () {return UW_Tour_;                        }
    short             WeekDay         () {return WeekDay_;                        }
    char              Activ           () {return Activ_;                          }

    bool              IsActiv() { return Activ_ == '1';  }

protected:
                      pxCustomerSpecials(pxSession *session, tCUSTOMERSPECIALS& src);
    pxCustomerSpecials&      operator=(const tCUSTOMERSPECIALS& src);
    friend
    pxCustomerSpecials&      Assign(pxCustomerSpecials& dest, const tCUSTOMERSPECIALS& src);
    friend
    tCUSTOMERSPECIALS&    Assign(tCUSTOMERSPECIALS& dest, const pxCustomerSpecials& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

protected:
    void              Init();


    short         BranchNo_       ;            // Filialnummer
    long          CustomerNo_     ;            // Customerno
    long          UW_IDF_         ;            // Überweiser IDFNr
    nString       UW_Tour_        ;            // Überweiser Tour
    short         WeekDay_        ;            // Wochentag
    char          Activ_          ;             // Aktiv 0/1

private:
    friend class pxCustomerSpecialsList;
};

class pxCustomerSpecialsList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxCustomerSpecialsList() {Clear();}
                      pxCustomerSpecialsList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const short BranchNo, const long CustomerNo, const int count = cDEFAULT);
    size_t            SelectFirstUWIDF(const short BranchNo, const long CustomerNo, const int count = cDEFAULT);
    size_t            SelectUWIDF(const short BranchNo, const long UE_IDF, const int count = cDEFAULT);
	pxCustomerSpecials* FindActivDow( const short dow);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxCustomerSpecialsListIter;
};

class pxCustomerSpecialsListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustomerSpecialsListIter(pxCustomerSpecialsList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustomerSpecialsListIter() {;}

};

#endif
