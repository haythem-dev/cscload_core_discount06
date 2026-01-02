/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxCstSepOrderArtGroup Class

REVISION HISTORY

09 December 2008 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCSTSEPORDERARTGRP_INC
   #define PXCSTSEPORDERARTGRP_INC

#include "pxbase/pxrecord.hpp"

struct tCSTSEPORDERARTGRP;

class pxCstSepOrderArtGroup : public pxDBRecord
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

    //enum SepOrdArtGrp
    //{
    //   // Article Group definitions:
    //   SEP_GROUP_NARCOTIC,              // 0 article Group Narcotics
    //   SEP_GROUP_COLDCHAIN,             // 1 article Group KK
    //   SEP_GROUP_COOL08,                // 2 article Group K8
    //   SEP_GROUP_COOL20,                // 3 article Group K20
    //   SEP_GROUP_RES_HOSPITAL,          // 4 article Group Reserve Hospital
    //   SEP_GROUP_CONTAINER,             // 5 article Group Container
    //   SEP_GROUP_BIG_VOLUME,            // 6 article Group Big Volume
    //   SEP_GROUP_ZYTOSTATIC,            // 7 article Group Zytostatic
    //   SEP_GROUP_AUXDELIVERY,           // 8 article Group Auxdelivery
    //   SEP_GROUP_POSITIVLIST            // 9 article Group PositivList(RS)
    //};

// constructors:
                pxCstSepOrderArtGroup(pxCstSepOrderArtGroup& src);
                pxCstSepOrderArtGroup(pxSession *session);
                pxCstSepOrderArtGroup(pxSession *session, tCSTSEPORDERARTGRP& src);
                pxCstSepOrderArtGroup(pxSession *session, const pxCstSepOrderArtGroup* src);
// destructor:
                virtual  ~pxCstSepOrderArtGroup();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxCstSepOrderArtGroup&   operator=(const pxCstSepOrderArtGroup& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxCstSepOrderArtGroup&   operator=(const tCSTSEPORDERARTGRP& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.

/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxCstSepOrderArtGroup&
                Assign(pxCstSepOrderArtGroup& dest, const tCSTSEPORDERARTGRP& src);
    friend   tCSTSEPORDERARTGRP&
                Assign(tCSTSEPORDERARTGRP& dest, const pxCstSepOrderArtGroup& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

//  Field updates


//  Queries:
    short            BranchNo()                 {return BranchNo_      ;}
    long             CustomerNo()               {return CustomerNo_    ;}
    short            ArtGrp()                   {return ArtGrp_        ;}
    nString&         KdAuftragArt()             {return KdAuftragArt_  ;}
    char             KoArt()                    {return KoArt_         ;}
    char             BuchArt()                  {return BuchArt_       ;}
    char             DeferOrder()               {return DeferOrder_    ;}

    //bool              IsNarCotic()         const {return ArtGrp_ ==  (short) SEP_GROUP_NARCOTIC     ;}
    //bool              IsColdChain()        const {return ArtGrp_ ==  (short) SEP_GROUP_COLDCHAIN    ;}
    //bool              IsCool08()           const {return ArtGrp_ ==  (short) SEP_GROUP_COOL08       ;}
    //bool              IsCool20()           const {return ArtGrp_ ==  (short) SEP_GROUP_COOL20       ;}
    //bool              IsResHospital()      const {return ArtGrp_ ==  (short) SEP_GROUP_RES_HOSPITAL ;}
    //bool              IsContainer()        const {return ArtGrp_ ==  (short) SEP_GROUP_CONTAINER    ;}
    //bool              IsBigVolume()        const {return ArtGrp_ ==  (short) SEP_GROUP_BIG_VOLUME   ;}
    //bool              IsZytoStatics()      const {return ArtGrp_ ==  (short) SEP_GROUP_ZYTOSTATIC   ;}
    //bool              IsAuxDelivery()      const {return ArtGrp_ ==  (short) SEP_GROUP_AUXDELIVERY  ;}
    //bool              IsDeferOrder()       const {return DeferOrder_  == '1'                        ;}
    //bool              IsCloseOrder()       const {return DeferOrder_  == '0'                        ;}

protected:
    void        Init();

    short      BranchNo_         ;       // Branchnumber
    long       CustomerNo_       ;       // CustomerNo
    short      ArtGrp_           ;       // Article Group
    nString    KdAuftragArt_     ;       // Kunde Auftrag Art
    char       KoArt_            ;       // Kommissionierungsart
    char       BuchArt_          ;       // Buchungsart
    char       DeferOrder_       ;       // Defer Order

private:
    friend class pxCstSepOrderArtGroupList;

};

class pxCstSepOrderArtGroupList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxCstSepOrderArtGroupList(pxSession *session);
//  destructor:
                virtual ~pxCstSepOrderArtGroupList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const short BranchNo, const long CustomerNo, const int count = 50);
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  nCollectable*
                        AddToList(const void *record, const int row);
    virtual  int       GetNext(const void* record, const int cursorid);
    virtual  int       StartBrowse(const void *keys, const int cursorid);
    virtual  int       EndBrowse(const int cursorid);
    short              Find( const short BranchNo);
    pxCstSepOrderArtGroup* Find( const short BranchNo, const long CustomerNo, const short ArtGroup);

protected:

private:
    friend class pxCstSepOrderArtGroupListIter;
};

class pxCstSepOrderArtGroupListIter : public nDListCollectIter
{

public:
// constructors:
    pxCstSepOrderArtGroupListIter(pxCstSepOrderArtGroupList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCstSepOrderArtGroupListIter() {;}
};

#endif
