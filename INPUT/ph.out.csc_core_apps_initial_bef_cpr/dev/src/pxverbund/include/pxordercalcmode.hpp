/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxOrderCalcMode Class.

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDERCALCMODE_INC
   #define PXORDERCALCMODE_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGRECHART;

class pxOrderCalcMode : public pxDBRecord
{

public:


// constructors:
                pxOrderCalcMode(pxOrderCalcMode& src);
                pxOrderCalcMode(pxSession *session);
                pxOrderCalcMode(pxSession *session, tKDAUFTRAGRECHART& src);
                pxOrderCalcMode(pxSession *session, const long KdAuftragNr);
// destructor:
                virtual  ~pxOrderCalcMode();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxOrderCalcMode&   operator=(const pxOrderCalcMode& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxOrderCalcMode&   operator=(const tKDAUFTRAGRECHART& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxOrderCalcMode&
                Assign(pxOrderCalcMode& dest, const tKDAUFTRAGRECHART& src);
    friend   tKDAUFTRAGRECHART&
                Assign(tKDAUFTRAGRECHART& dest, const pxOrderCalcMode& src);

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

    short         Print()                {return Print_           ;}
    short         DeductionAep()         {return DeductionAep_    ;}
    short         DeductionAvp()         {return DeductionAvp_    ;}
    short         WithColumnNr()         {return WithColumnNr_    ;}
    short         ByEmail()              {return ByEmail_         ;}
    long          KdAuftragNr()          {return KdAuftragNr_     ;}

//  Field Updates:
    void           SetPrint(short Print)
                   {Print_ = Print; SetDirty();}
    void           SetDeductionAep(short DeductionAep)
                   {DeductionAep_ = DeductionAep; SetDirty();}
    void           SetDeductionAvp(short DeductionAvp)
                   {DeductionAvp_ = DeductionAvp; SetDirty();}
    void           SetWithColumnNr(short WithColumnNr)
                   {WithColumnNr_ = WithColumnNr; SetDirty();}
    void           SetByEmail(short ByEmail)
                   {ByEmail_ = ByEmail; SetDirty();}

protected:
    void        Init();

    short         Print_;                 // Print
    short         DeductionAep_;          // DeductionAep
    short         DeductionAvp_;          // DeductionAvp
    short         WithColumnNr_;          // WithColumnNr
    short         ByEmail_;               // ByEmail
    long          KdAuftragNr_;           // Ordernumber

private:
    friend class pxOrderCalcModeList;

};

class pxOrderCalcModeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxOrderCalcModeList(pxSession *session);
//  destructor:
                virtual ~pxOrderCalcModeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const long KdAuftragNr, const int count = 100);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:
    friend class pxOrderCalcModeListIter;
};

class pxOrderCalcModeListIter : public nDListCollectIter
{

public:
// constructors:
    pxOrderCalcModeListIter(pxOrderCalcModeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxOrderCalcModeListIter() {;}
};
#endif
