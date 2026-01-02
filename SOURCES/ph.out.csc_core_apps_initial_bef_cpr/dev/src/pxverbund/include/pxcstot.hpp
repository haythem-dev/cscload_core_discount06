/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Customer order type classes.

REVISION HISTORY

18 August 1995 V1.00 REV 00 written by Dietmar Schloetel.
*/

#ifndef PXCSTOT_INC
#define PXCSTOT_INC

#include "pxordtyp.hpp"

struct tAUFTRAGARTKD;

class pxCustOrderType : public pxOrderType
{
public:
    virtual           ~pxCustOrderType();
					  pxCustOrderType(pxSession *S);
                      pxCustOrderType(const pxCustOrderType& src);
                      pxCustOrderType(pxSession *s, const nString& Auftragart,
                                      const short VZNr,
                                      const long KdNr);
                      pxCustOrderType(pxSession *s,const nString& Auftragart,
                                      const short VZNr,
                                      const long KdNr,
                                      DBAccessMode mode);

    pxCustOrderType&  operator=(const pxCustOrderType& src);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);	
    virtual  int     Put();

    int           getCustomerOrderType( const short VZNr, const long KdNr, const nString& Auftragart );
    const nString&    getDefaultOrderLabel() const;
    bool              isDefaultOrderLabel( const nString& orderlabel ) const;
    bool              isAllowedForMSV3() const;
    bool              isPartialDeliveryAllowed() const;
    bool              isUsageOfCustomOrderLabelsAllowed() const;


    // Queries:
    long              KdNr() const      {return KundenNr_;}
    short             Vertriebszentrum() const {return VertriebszentrumNr_;}
    short             OrderLabelCount() const  {return OrderLabelCount_;}
    short             SWMSV3()          const  {return SWMSV3_         ;}
    short             SWPartDel()       const  {return SWPartDel_      ;}
    const nString&    OrderIdentificatio() const {return OrderIdentificatio_; }

protected:
    pxCustOrderType&  operator=(const tAUFTRAGARTKD& src);
    friend
    pxCustOrderType&  Assign(pxCustOrderType& dest, const tAUFTRAGARTKD& src);
    friend
    tAUFTRAGARTKD&    Assign(tAUFTRAGARTKD& dest, const pxCustOrderType& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    void              Init();
    virtual  bool     IsEqual(const nCollectable *itemp) const
                      {return (CompareTo(itemp,(void*)this,0L) == 0);}
    virtual  bool     IsMSV3() const
                      {return SWMSV3_ == 1;}
    virtual  bool     IsPartDel() const
                      {return SWPartDel_ == 1;}
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);

    short            VertriebszentrumNr_;     // Vertriebszentrum
    long             KundenNr_;               // Kundennummer
    short            OrderLabelCount_;        // OrderLabelCount
    short            SWMSV3_;                 // msv3 Schalter
    short            SWPartDel_;              // partial delivery
    nString           OrderIdentificatio_;     // auftragsidentification

private:
    friend class pxCustOrderTypeList;
};

class pxCustOrderTypeList : public nDListCollect, public nDBRecordSet
{
public:
                      pxCustOrderTypeList(pxSession *session);
    virtual           ~pxCustOrderTypeList() {Clear();}

    size_t            Build(const short VZNr, const long KdNr);
    void              Clear()        {nDBRecordSet::Clear();}
    pxCustOrderType*  Find(const nString& KdAuftragArt,const short VZNr, const long KdNr);
    pxCustOrderType*  GetDefault() const;
    pxCustOrderType*  AddDefault(const short VZNr, const long KdNr);
    pxCustOrderType*  NewItem(const nString& key, const short VZNr, const long KdNr);
    size_t            Select( const short VZNr, const long KdNr, const int c = cDEFAULT);
    pxSession*        Session()         {return (pxSession*) DataBase();}
protected:

    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxCustOrderTypeListIter;
};


class pxCustOrderTypeListIter : public nDListCollectIter
{
public:
    pxCustOrderTypeListIter(pxCustOrderTypeList& list)
                            : nDListCollectIter(list) {;}
    virtual  ~pxCustOrderTypeListIter() {;}
};

#endif
