/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxdealervolume.hpp
DEALERVOLUME  class

REVISION HISTORY

17 August 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXDEALERVOLUME_INC
   #define PXDEALERVOLUME_INC

#include "pxbase/pxrecord.hpp"
#include <date.hpp>
#include <clock.hpp>
#include <money.hpp>

struct tDEALERVOLUME;

class pxDealerVolume : public pxDBRecord
{

public:

// constructors:
                pxDealerVolume(pxDealerVolume& src);
                pxDealerVolume(pxSession *session);
                pxDealerVolume(pxSession *session, tDEALERVOLUME& src);
                pxDealerVolume(pxSession *session, const pxDealerVolume* src);
                pxDealerVolume(pxSession *session, short BranchNo,
                                                   long  Uid, nDate& date,
                                                   long  InVoiceNo );

// destructor:
                virtual  ~pxDealerVolume();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxDealerVolume&   operator=(const pxDealerVolume& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxDealerVolume&   operator=(const tDEALERVOLUME& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxDealerVolume&
                Assign(pxDealerVolume& dest, const tDEALERVOLUME& src);
    friend   tDEALERVOLUME&
                Assign(tDEALERVOLUME& dest, const pxDealerVolume& src);

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
//    void              SetBalance(double balance) { Balance_ = balance; SetDirty();}


//  Queries:
    short          BranchNo()     {return BranchNo_             ;}
    long           Uid()          {return Uid_                  ;}
    long           InVoiceNo()    {return InVoiceNo_            ;}
    long           OrderNoVSE()   {return OrderNoVSE_           ;}
    long           OrderNoKSC()   {return OrderNoKSC_           ;}
    nDate&          DateInVoice()  {return DateInVoice_          ;}
    nClock&         TimeInVoice()  {return TimeInVoice_          ;}
    nMoney          InVoiceVolume(){return InVoiceVolume_        ;}
    nMoney          Volume1()      {return Volume1_              ;}
    nMoney          Volume2()      {return Volume2_              ;}
    nMoney          Volume3()      {return Volume3_              ;}
    nMoney          Volume4()      {return Volume4_              ;}
    long           CustomerNo()   {return CustomerNo_           ;}
    char           VolumeSTate()  {return VolumeState_          ;}

// Set Methodes
    void            SetOrderNoVSE( long OrderNoVSE)
                    { OrderNoVSE_ = OrderNoVSE; SetDirty(); }
    void            SetOrderNoKSC( long OrderNoKSC)
                    { OrderNoKSC_ = OrderNoKSC; SetDirty(); }
    void            SetTimeInVoice( nClock& TimeInVoice)
                    { TimeInVoice_ = TimeInVoice; SetDirty(); }
    void            SetInVoiceVolume( nMoney& InVoiceVolume)
                    { InVoiceVolume_ = InVoiceVolume; SetDirty(); }
    void            SetVolume1( nMoney& Volume1)
                    { Volume1_ = Volume1; SetDirty(); }
    void            SetVolume2( nMoney& Volume2)
                    { Volume2_ = Volume2; SetDirty(); }
    void            SetVolume3( nMoney& Volume3)
                    { Volume3_ = Volume3; SetDirty(); }
    void            SetVolume4( nMoney& Volume4)
                    { Volume4_ = Volume4; SetDirty(); }
    void            SetCustomerNo( long CustomerNo)
                    { CustomerNo_ = CustomerNo; SetDirty(); }
    void            SetVolumeState( char VolumeState)
                    { VolumeState_ = VolumeState; SetDirty(); }

protected:
    void        Init();

    short      BranchNo_           ;      // Branch Number
    long       Uid_                ;      // User Id
    long       InVoiceNo_          ;      // Invoice number
    long       OrderNoVSE_         ;      // Order number VSE(Pharmos) side
    long       OrderNoKSC_         ;      // Order number KSC(Order Entry) side
    nDate       DateInVoice_        ;      // Date Invoice
    nClock      TimeInVoice_        ;      // Time Invoice
    nMoney      InVoiceVolume_      ;      // Invoice volume
    nMoney      Volume1_            ;      // Volume1
    nMoney      Volume2_            ;      // Volume2
    nMoney      Volume3_            ;      // Volume3
    nMoney      Volume4_            ;      // Volume4
    long       CustomerNo_         ;      // CustomerNo
    char       VolumeState_        ;      // OrderState 0 = ok 1 = storno

private:
    friend class pxDealerVolumeList;
};

class pxDealerVolumeList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxDealerVolumeList(pxSession *session);
//  destructor:
                virtual ~pxDealerVolumeList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const short BranchNo,
                         const long  Uid,
                         const int   count  = 100
                       );

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxDealerVolumeListIter;
};

class pxDealerVolumeListIter : public nDListCollectIter
{

public:
// constructors:
    pxDealerVolumeListIter(pxDealerVolumeList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxDealerVolumeListIter() {;}
};
#endif
