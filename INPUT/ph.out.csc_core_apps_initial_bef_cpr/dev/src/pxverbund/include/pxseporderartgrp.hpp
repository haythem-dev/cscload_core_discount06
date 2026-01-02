/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxSepOrderArtGroup Class

REVISION HISTORY

16 March   2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXSEPORDERARTGRP_INC
   #define PXSEPORDERARTGRP_INC

#include "pxbase/pxrecord.hpp"

struct tSEPORDERARTGRP;

class pxSepOrderArtGroup : public pxDBRecord
{

public:

/*----------------------------------------------------------------------------*/
/*  Enumerations and manifest constants.                                      */
/*----------------------------------------------------------------------------*/
    //enum SeparateTypes
    //{
    //   // State definitions:
    //   SEPARATE_OPIAT,                  // 0 separate opiat article from an order
    //   SEPARATE_RES_HOSPITAL,           // 1 separate reserve hospital article
    //   SEPARATE_COOLER                  // 2 separate cooler  article
    //};

    enum SepOrdArtGrp
    {
       // Article Group definitions:
       SEP_GROUP_NARCOTIC,              // 0 article Group Narcotics
       SEP_GROUP_COLDCHAIN,             // 1 article Group KK
       SEP_GROUP_COOL08,                // 2 article Group K8
       SEP_GROUP_COOL20,                // 3 article Group K20
       SEP_GROUP_RES_HOSPITAL,          // 4 article Group Reserve Hospital
       SEP_GROUP_CONTAINER,             // 5 article Group Container
       SEP_GROUP_BIG_VOLUME,            // 6 article Group Big Volume
       SEP_GROUP_ZYTOSTATIC,            // 7 article Group Zytostatic
       SEP_GROUP_AUXDELIVERY,           // 8 article Group Auxdelivery
       SEP_GROUP_POSITIVLIST,           // 9 article Group PositivList(RS)
       SEP_GROUP_HEALTHFUND,            // 10 Separate HEALTHFUND positions(BG)(KK)
       SEP_GROUP_RETAIL,                // 11 Separate RETAIL positions(BG)(EV)
       SEP_GROUP_LISTFIVE,              // 12 Separate LISTFIVE positions(BG)
       SEP_GROUP_CAP,                   // 13 Separate Cap Position(IvryLab)
       SEP_GROUP_MANUFACTURER,          // 14 Separate Manufacturer positions (IvryLab inventory)
       SEP_GROUP_KONSIG_PARTNER,        // 15 Separate Konsignationspartner positions (IvryLab inventory)
       SEP_GROUP_PSYCHO                 // 16 Separate Psychotrop positions
    };

// constructors:
                pxSepOrderArtGroup(pxSepOrderArtGroup& src);
                pxSepOrderArtGroup(pxSession *session);
                pxSepOrderArtGroup(pxSession *session, tSEPORDERARTGRP& src);
                pxSepOrderArtGroup(pxSession *session, const pxSepOrderArtGroup* src);
// destructor:
                virtual  ~pxSepOrderArtGroup();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxSepOrderArtGroup&   operator=(const pxSepOrderArtGroup& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxSepOrderArtGroup&   operator=(const tSEPORDERARTGRP& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxSepOrderArtGroup&
                Assign(pxSepOrderArtGroup& dest, const tSEPORDERARTGRP& src);
    friend   tSEPORDERARTGRP&
                Assign(tSEPORDERARTGRP& dest, const pxSepOrderArtGroup& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

//  Field updates

//  Queries:
    short            BranchNo()                 {return BranchNo_      ;}
    short            ArtGrp()                   {return ArtGrp_        ;}
    nString&          KdAuftragArt()             {return KdAuftragArt_  ;}
    char             KoArt()                    {return KoArt_         ;}
    char             BuchArt()                  {return BuchArt_       ;}
    char             DeferOrder()               {return DeferOrder_    ;}
    long             ManufacturerNo()           {return ManufacturerNo_;}

    bool              IsNarCotic()         const {return ArtGrp_ ==  (short) SEP_GROUP_NARCOTIC     ;}
    bool              IsColdChain()        const {return ArtGrp_ ==  (short) SEP_GROUP_COLDCHAIN    ;}
    bool              IsCool08()           const {return ArtGrp_ ==  (short) SEP_GROUP_COOL08       ;}
    bool              IsCool20()           const {return ArtGrp_ ==  (short) SEP_GROUP_COOL20       ;}
    bool              IsResHospital()      const {return ArtGrp_ ==  (short) SEP_GROUP_RES_HOSPITAL ;}
    bool              IsContainer()        const {return ArtGrp_ ==  (short) SEP_GROUP_CONTAINER    ;}
    bool              IsBigVolume()        const {return ArtGrp_ ==  (short) SEP_GROUP_BIG_VOLUME   ;}
    bool              IsZytoStatics()      const {return ArtGrp_ ==  (short) SEP_GROUP_ZYTOSTATIC   ;}
    bool              IsAuxDelivery()      const {return ArtGrp_ ==  (short) SEP_GROUP_AUXDELIVERY  ;}
    bool              IsHealthFund()       const {return ArtGrp_ ==  (short) SEP_GROUP_HEALTHFUND   ;}
    bool              IsRetail()           const {return ArtGrp_ ==  (short) SEP_GROUP_RETAIL       ;}
    bool              IsListFive()         const {return ArtGrp_ ==  (short) SEP_GROUP_LISTFIVE     ;}
    bool              IsCap()              const {return ArtGrp_ ==  (short) SEP_GROUP_CAP          ;}
    bool              IsManufacturer()     const {return ArtGrp_ ==  (short) SEP_GROUP_MANUFACTURER ;}
    bool              IsKonsigPartner()    const {return ArtGrp_ ==  (short) SEP_GROUP_KONSIG_PARTNER ;}
    bool              IsPsycho()           const {return ArtGrp_ ==  (short) SEP_GROUP_PSYCHO       ;}
    bool              IsDeferOrder()       const {return DeferOrder_  == '1'                         ;}
    bool              IsCloseOrder()       const {return DeferOrder_  == '0'                         ;}

protected:
    void        Init();

    short      BranchNo_         ;       // Branchnumber
    short      ArtGrp_           ;       // Article Group
    nString    KdAuftragArt_     ;       // Kunde Auftrag Art
    char       KoArt_            ;       // Kommissionierungsart
    char       BuchArt_          ;       // Buchungsart
    char       DeferOrder_       ;       // Defer Order
    long       ManufacturerNo_   ;       // ManufacturerNo / KonsigPartnerNo

private:
    friend class pxSepOrderArtGroupList;
};

class pxSepOrderArtGroupList : public nDBRecordSet, public nDListCollect
{
public:

//  constructors:
                pxSepOrderArtGroupList(pxSession *session);
//  destructor:
                virtual ~pxSepOrderArtGroupList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short BranchNo,const int     count = 50);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                        AddToList(const void *record, const int row);
    virtual  int       GetNext(const void* record, const int cursorid);
    virtual  int       StartBrowse(const void *keys, const int cursorid);
    virtual  int       EndBrowse(const int cursorid);
    short              Find( const short BranchNo);
    pxSepOrderArtGroup* Find( const short BranchNo, const short ArtGroup);

private:
    friend class pxSepOrderArtGroupListIter;
};

class pxSepOrderArtGroupListIter : public nDListCollectIter
{
public:
// constructors:
    pxSepOrderArtGroupListIter(pxSepOrderArtGroupList& list) : nDListCollectIter(list) {}
// destructor:
    virtual ~pxSepOrderArtGroupListIter() {}
};

#endif
