/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxGeneralCalcAvp Class.

REVISION HISTORY

06 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXGENERALCALC_INC
   #define PXGENERALCALC_INC


#include "pxbase/pxrecord.hpp"
#include "types/pricetypeenum.inc"

struct tGENERALCALCAVP;

class pxGeneralCalcAvp : public pxDBRecord
{

public:


// constructors:
                pxGeneralCalcAvp(pxGeneralCalcAvp& src);
                pxGeneralCalcAvp(pxSession *session);
                pxGeneralCalcAvp(pxSession *session, tGENERALCALCAVP& src);
                pxGeneralCalcAvp(pxSession *session, const short PriceGroup, const PriceTypeEnum PreisTyp);
// destructor:
                virtual  ~pxGeneralCalcAvp();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxGeneralCalcAvp&   operator=(const pxGeneralCalcAvp& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxGeneralCalcAvp&   operator=(const tGENERALCALCAVP& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxGeneralCalcAvp&
                Assign(pxGeneralCalcAvp& dest, const tGENERALCALCAVP& src);
    friend   tGENERALCALCAVP&
                Assign(tGENERALCALCAVP& dest, const pxGeneralCalcAvp& src);

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

    short         PriceGroup()           {return PriceGroup_           ;}
    PriceTypeEnum PreisTyp()             {return PreisTyp_             ;}
    double        PercentPreScript()     {return PercentPreScript_     ;}
    double        PercentNoPerScript()   {return PercentNoPerScript_   ;}

//  Field Updates:


protected:
    void        Init();

    short         PriceGroup_;            // Price_Group
    PriceTypeEnum PreisTyp_;              // PreisTyp
    double        PercentPreScript_;      // PercentPreScript
    double        PercentNoPerScript_;    // PercentNoPerScript

private:
    friend class pxGeneralCalcAvpList;

};

class pxGeneralCalcAvpList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxGeneralCalcAvpList(pxSession *session);
//  destructor:
                virtual ~pxGeneralCalcAvpList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}
    pxGeneralCalcAvp* Find(const short PriceGroup, const PriceTypeEnum PreisTyp);

    size_t      Select ( const int count = 100);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:
    friend class pxGeneralCalcAvpListIter;
};

class pxGeneralCalcAvpListIter : public nDListCollectIter
{

public:
// constructors:
    pxGeneralCalcAvpListIter(pxGeneralCalcAvpList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxGeneralCalcAvpListIter() {;}
};
#endif
