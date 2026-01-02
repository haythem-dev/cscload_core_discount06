/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxOrderPosChange Class.

REVISION HISTORY

23 Sep 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDERPOSCHANGE_INC
   #define PXORDERPOSCHANGE_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGPOSCHANGE;

class pxOrderPosChange : public pxDBRecord
{

public:


// constructors:
                pxOrderPosChange(pxOrderPosChange& src);
                pxOrderPosChange(pxSession *session);
                pxOrderPosChange(pxSession *session, tKDAUFTRAGPOSCHANGE& src);
                pxOrderPosChange(pxSession *session, const long KdAuftragNr, const long PosNr);
// destructor:
                virtual  ~pxOrderPosChange();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderPosChange&   operator=(const pxOrderPosChange& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderPosChange&   operator=(const tKDAUFTRAGPOSCHANGE& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderPosChange&
                Assign(pxOrderPosChange& dest, const tKDAUFTRAGPOSCHANGE& src);
    friend   tKDAUFTRAGPOSCHANGE&
                Assign(tKDAUFTRAGPOSCHANGE& dest, const pxOrderPosChange& src);

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
    long          KdAuftragNr()           {return KdAuftragNr_     ;}
    long          PosNr()                 {return PosNr_           ;}
    long          MengeBestellt()         {return MengeBestellt_   ;}
    long          MengeBestaetigt()       {return MengeBestaetigt_ ;}
    long          MengeAlt()              {return MengeAlt_        ;}
    char          SWChecked()             {return SWChecked_       ;}

//  Field Updates:
    void           SetMengeBestellt(long q)   {MengeBestellt_ = q;SetDirty()  ;}
    void           SetMengeBestaetigt(long q) {MengeBestaetigt_ = q;SetDirty();}
    void           SetMengeAlt(long q)        {MengeAlt_ = q;SetDirty()       ;}
    void           SetSWChecked(char s)       {SWChecked_ = s;SetDirty()      ;}

protected:
    void        Init();

    long          KdAuftragNr_;           // Ordernumber
    long          PosNr_;                 // PosNr
    long          MengeBestellt_;         // Menge Bestellt
    long          MengeBestaetigt_;       // Menge Bestaetigt
    long          MengeAlt_;              // Menge Bestaetigt alt
    char          SWChecked_;             // SWChecked

private:
    friend class pxOrderPosChangeList;

};

class pxOrderPosChangeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxOrderPosChangeList(pxSession *session);
//  destructor:
                virtual ~pxOrderPosChangeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const long KdAuftragNr, const long PosNr = 0, const int count = 500);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:
    friend class pxOrderPosChangeListIter;
};

class pxOrderPosChangeListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderPosChangeListIter(pxOrderPosChangeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderPosChangeListIter() {;}
};
#endif
