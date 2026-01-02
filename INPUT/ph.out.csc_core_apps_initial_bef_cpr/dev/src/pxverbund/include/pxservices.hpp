/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXSERVICES
Services Class.


*/

#ifndef SERVICES_INC
   #define SERVICES_INC

#include "pxbase/pxrecord.hpp"

struct tSERVICES;

class pxServices : public pxDBRecord
{
public:


// destructor:
    virtual           ~pxServices();
// constructors:
                      pxServices(pxServices& src);
                      pxServices(pxSession *session);
                      pxServices(pxSession *session, short ServiceNo,
                                  DBAccessMode mode = cDBGET_READONLY);

    pxServices&      operator=(const pxServices& src);
//  Assigns the values of 'src' to self and returns a reference to it.
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();

//  Queries:

    short            ServiceNo()       {return Service_No_;                   }
    nString&         Name     ()       {return Name_;                         }
    short            ServiceTypeNo()   {return ServiceTypeNo_;                }


protected:
                      pxServices(pxSession *session, tSERVICES& src);
    pxServices&      operator=(const tSERVICES& src);
    friend
    pxServices&      Assign(pxServices& dest, const tSERVICES& src);
    friend
    tSERVICES&    Assign(tSERVICES& dest, const pxServices& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    void              Init();

    short            Service_No_;      // Service Number
    nString          Name_;            // Name of service
    short            ServiceTypeNo_;   // Service Type Number

private:
    friend class pxServicesList;
};

class pxServicesList : public nDBRecordSet, public nDListCollect
{

public:
                      virtual ~pxServicesList() {Clear();}
                      pxServicesList(pxSession *session);
//  member functions:
    void              Clear()           {nDBRecordSet::Clear();}
    size_t            Select(const int count = cDEFAULT);
    size_t            Select(const short ServiceNo, const int count = cDEFAULT);
    pxSession*        Session()         { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxServicesListIter;
};

class pxServicesListIter : public nDListCollectIter
{

public:
// constructors:
    pxServicesListIter(pxServicesList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxServicesListIter() {;}

};

#endif
