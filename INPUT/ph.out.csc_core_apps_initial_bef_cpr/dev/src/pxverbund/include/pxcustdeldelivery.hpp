/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxCustDelDelivery Class.

REVISION HISTORY

16 May 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCUSTDELDELIVERY_INC
   #define PXCUSTDELDELIVERY_INC

#include "pxbase/pxrecord.hpp"
#include <clock.hpp>
#include <date.hpp>
#include "pxartbas.hpp"

struct tDELAYEDDELIVERYCST;

class pxCustDelDelivery : public pxDBRecord
{

public:


// constructors:
                pxCustDelDelivery(pxCustDelDelivery& src);
                pxCustDelDelivery(pxSession *session);
                pxCustDelDelivery(pxSession *session, tDELAYEDDELIVERYCST& src);
                pxCustDelDelivery(pxSession *session, const short BranchNo,
                                     const long CustomerNo, const short WeekDay);
// destructor:
                virtual  ~pxCustDelDelivery();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCustDelDelivery&   operator=(const pxCustDelDelivery& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCustDelDelivery&   operator=(const tDELAYEDDELIVERYCST& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCustDelDelivery&
                Assign(pxCustDelDelivery& dest, const tDELAYEDDELIVERYCST& src);
    friend   tDELAYEDDELIVERYCST&
                Assign(tDELAYEDDELIVERYCST& dest, const pxCustDelDelivery& src);

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
    short            BranchNo()           {return BranchNo_           ;}
    long             CustomerNo()         {return CustomerNo_         ;}
    short            WeekDay()            {return WeekDay_            ;}
    nClock&           Time()               {return Time_               ;}
    nString&          TourId()             {return TourId_             ;}
    char             Activ()              {return Activ_              ;}
    short            DelayedWeekDay()     {return DelayedWeekDay_     ;}

    bool              IsActiv()            const {return Activ_ == '1'     ;}
    bool              IsNarCotic()         const {return NarCotic_ == '1';  }
    bool              IsColdChain()        const {return ColdChain_ == '1'; }
    bool              IsCool08()           const {return Cool08_ == '1';    }
    bool              IsCool20()           const {return Cool20_ == '1';    }

	bool			isValidForArticle( pxArtBase* article ) const;

    nDate&          DateFrom()          {return DateFrom_         ;}
    nDate&          DateTo()            {return DateTo_           ;}


protected:
    void        Init();

    short      BranchNo_          ;      // Branchnumber
    long       CustomerNo_        ;      // CustomerNo
    short      WeekDay_           ;      // Day of Week
    nClock      Time_              ;      // Time from
    nString     TourId_            ;      // TourId
    char       Activ_             ;      // Kz Activ 0 or 1
    short      DelayedWeekDay_    ;      // Day of deleayed delivery
    char       NarCotic_          ;      // Narcotic Article
    char       ColdChain_         ;      // Coldchain Article
    char       Cool08_            ;      // Cool 08 Article
    char       Cool20_            ;      // Cool 20 Article
	nDate      DateFrom_          ;      // Date from
    nDate      DateTo_            ;      // Date to

private:
	//bool			delayDeliveryDespiteEmergencyService(const short branchno, const long customerno, pxArtBase* article) const; // Verzögerung trotz Notdienst?

    friend class pxCustDelDeliveryList;

};

class pxCustDelDeliveryList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCustDelDeliveryList(pxSession *session);
//  destructor:
                virtual ~pxCustDelDeliveryList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short BranchNo, const long CustomerNo, const short WeekDay, const bool withTransportExclusion = false,
                         const int     count = 50 );

	size_t      SelectForDate(const short BranchNo, const long CustomerNo, const long PickingDate, const short  WeekDay, const int count = 50);

	pxCustDelDelivery* getDelayedDelivery(const short BranchNo, const long CustomerNo, const short WeekDay, const bool withTransportExclusion, pxArtBase* article);
	pxCustDelDelivery* getDelayedDeliveryForDate(const short BranchNo, const long CustomerNo, const long PickingDate, const short WeekDay, pxArtBase* article);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxCustDelDeliveryListIter;
};

class pxCustDelDeliveryListIter : public nDListCollectIter
{

public:
// constructors:
    pxCustDelDeliveryListIter(pxCustDelDeliveryList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCustDelDeliveryListIter() {;}
};
#endif
