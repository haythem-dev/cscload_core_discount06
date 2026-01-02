/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXORDTYP.HPP
Internal Order Type Classes.

REVISION HISTORY

17 August 1995 V1.10 REV 00 written by Dietmar Schloetel.
*/

#ifndef PXORDTYP_INC
#define PXORDTYP_INC

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAGART;

class pxOrderType : public pxDBRecord
{
public:

#include "pxotdef.h"

                      virtual  ~pxOrderType();
                      pxOrderType(pxSession *session);
                      pxOrderType(const pxOrderType& src);
                      pxOrderType(pxSession *session, const pxOrderType* src);
                      pxOrderType(pxSession *session, const nString& KdAuftragArt);
                      pxOrderType(pxSession *session, const nString& KdAuftragArt,const short BranchNo);
                      pxOrderType(pxSession *session, const nString& KdAuftragArt,
                                  DBAccessMode mode);

    pxOrderType&      operator=(const pxOrderType& src);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    int              Compare(const nString& kdaufart) const;

    bool              IsNormal             () const
                      {return (Category() == Normal            );}
    bool              IsBuyBack            () const
                      {return (Category() == BuyBack           );}
    bool              IsService            () const
                      {return (Category() == Service           );}
    bool              IsTest               () const
                      {return (Category() == Test              );}
    bool              IsQuery     () const
                      {return (Category() == Query);}
    bool              IsTens               () const
                      {return (Category() == Tens              );}
    bool              IsTransfer           () const
                      {return (Category() == Transfer          );}
    bool              IsScheduleQuantity   () const
                      {return (Category() == ScheduleQuantity  );}
    bool              IsActive3000         () const
                      {return (Category() == Active3000        );}
    bool              IsActive4000         () const
                      {return (Category() == Active4000        );}
    bool              IsTimeOrdered        () const
                      {return (Category() == TimeOrdered       );}
    bool              IsOmgSwiss           () const
                      {return (Category() == OmgSwiss          );}
    bool              IsUnoTransfer        () const
                      {return (Category() == UnoTransfer       );}
    bool              IsScheduleOrder      () const
                      {return (Category() == ScheduleOrder     );}
    bool              IsIndustrieDispo      () const
                      {return (Category() == IndustrieDispo     );}
    bool              IsDispoTransfer      () const
                      {return (Category() == DispoTransfer     );}
    bool              IsSpecial   () const
                      {return (Category() == Special);}
    // some french queries
    bool              IsShortBusiness      () const
                      {return (Category() == ShortBusiness     );}
    bool              IsShortLineBusiness      () const
                      {return (Category() == ShortLineBusiness );}
    bool              IsGenerika          () const
                      {return (Category() == Generika          );}
    bool              IsGenerikaOne        () const
                      {return (Category() == GenerikaOne       );}
    bool              IsGenerikaTwo        () const
                      {return (Category() == GenerikaTwo       );}
    bool              IsGenerikaThree      () const
                      {return (Category() == GenerikaThree     );}
    bool              IsPrismaOrder        () const
                      {return (Category() == PrismaOrder       );}
    bool              IsOverDrive          () const
                      {return (Category() == OverDrive         );}
    bool              IsPhoenixMagic       () const
                      {return (Category() == PhoenixMagic      );}
    bool              IsBatch              () const
                      {return (Category() == Batch             );}
    bool              IsDiscountAccount    () const
                      {return (Category() == DiscountAccount   );}
    bool              IsTenderOrder        () const
                      {return (Category() == TenderOrder       );}
    bool              IsTenderInvoice      () const
                      {return (Category() == TenderInvoice     );}
    bool              IsCashOrder         () const
                      {return (Category() == CashOrder         );}
    bool              IsManualPromotion   () const
                      {return (Category() == ManualPromotion   );}
    bool              IsRetailSalesOrder  () const
                      {return (Category() == RetailSalesOrder  );}
    bool              IsBountyOrder       () const
                      {return (Category() == BountyOrder       );}
    bool              IsDestructionOrder  () const
                      {return (Category() == DestructionOrder  );}
    bool              IsQuarantineOrder   () const
                      {return (Category() == QuarantineOrder   );}
    bool              IsChargeRecallOrder () const
                      {return (Category() == ChargeRecallOrder );}
    bool              IsPrivateProductRangeOrder () const
                      {return (Category() == PrivateProductRange );}
    bool              IsCollectiveOrder () const
                      {return (Category() == CollectiveOrder );}
    bool              IsFreeConditionOrder() const
                      {return (Category() == FreeConditionOrder );}
    bool              IsChronicIllnessOrder () const
                      {return (Category() == ChronicIllness);}
    // some french queries
    bool              IsProformaOrder() const
                      {return (Category() == ProformaOrder);}

    // Queries related to conditions and terms
    bool              IsCalcDisInKind() const
                      {return (SKdAuftragartNatra_ == '1');}
    bool              IsCalcBaseDisInKind() const
                      {return (SKdAuftragartBANR_  == '1');}
    bool              IsCalcNetPrice() const
                      {return (SKdAuftragartNetto_ == '1');}
    bool              IsDiscountable() const
                      {return (Discountable_ == '1');}
    bool              IsNoValidity() const
                      {return (SKdAuftragartValS_  == '1');}
    bool              IsDisInKindEnterable() const
                      {return (DisInKindEnterable_ == '1');}
    bool              IsAuxDelInhibit() const
                      {return (SKdAuftragartVerbund_ == '1');}
    bool              IsDelayedDelivery() const
                      {return (SKdAuftragartDD_ == '1');}

    // Queries related to misc switches:
    bool              IsDefault() const
                      {return (Default_ == '1');}
    bool              IsGlobal() const
                      {return (Global_ == '1');}
    bool              IsValidViaDCT() const
                      {return (ValidViaDCT_ == '1');}
    bool              IsValidViaVideo() const
                      {return (ValidViaVideo_ == '1');}
    bool              IsMustSubOrder() const
                      {return (MustSubOrder_ == '1');}
    bool              IsFreePrice() const
                      {return (FreePrice_ == '1');}
    bool              IsOrderCons() const
                      {return (OrderCons_ == '1');}
    bool              IsRestDel() const
                      {return (RestDel_ == '1');}
    bool              IsNoQuota() const
                      {return (NoQuota_ == '1');}
    bool              IsNoPartQty() const
                      {return (NoPartQty_ == '1');}
    bool              IsDeferOrder() const
                      {return (DeferOrder_ == '1');}
    bool              IsServiceOrder() const
                      {return (ServiceOrder_ == '1');}
    bool              IsNoDD() const
                      {return (NoDD_ == '1');}
    bool              IsOnlyEH() const
                      {return (OnlyEH_ == '1');}
    bool              IsSNoPromotions() const
                      {return (SNoPromotions_ == 1);}
    bool              IsSDefaultKennung() const
                      {return (SDefaultKennung_ == 1);}
    bool              IsSAlwaysRestDel() const
                      {return (SAlwaysRestDel_ == 1);}
    bool              IsSStockreservation() const
                      {return (SStockreservation_ == 1);}

    int              ValMonths() const
                      {return ValutaMonate_;}
    nString&          Bezeichnung()
                      {return Bezeichnung_;}
    tOrderTypeCode    Category() const
                      {return Category_;}

    short             ValMonthsAuto() const
                      {return ValutaMonAuto_;}

    const nString&    KdAuftragArt() const
                      {return KdAuftragArt_;}
    short            BranchNo() const
                      {return BranchNo_;    }
    short            SNoPromotions() const
                      {return SNoPromotions_;    }
    short            SDefaultKennung() const
                      {return SDefaultKennung_;    }
    short            SAlwaysRestDel() const
                      {return SAlwaysRestDel_;    }
    short            SStockreservation() const
                      {return SStockreservation_;    }

//@CE
protected:
    pxOrderType&      operator=(const tKDAUFTRAGART& src);
    friend
    pxOrderType&      Assign(pxOrderType& dest, const tKDAUFTRAGART& src);
    friend
    tKDAUFTRAGART&    Assign(tKDAUFTRAGART& dest, const pxOrderType& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    void              Init();
    virtual  bool     IsEqual(const nCollectable *itemp) const;
    virtual  int      Insert(const void *record);
    virtual  int      Update(const void *record);
    virtual  int      Read(const void *record);
    virtual  int      ReadLock(const void *record);

    nString           KdAuftragArt_;    // Order type key string
    nString           Bezeichnung_;     // Order type Description
    int               ValutaMonate_;        // Erlaubte Valuta in Monaten
    unsigned char     SKdAuftragartNatra_;  // SKd Auftragart Natra rechnen
    unsigned char     SKdAuftragartNetto_;  // SKd Auftragart Nettoaktion rechnen
    unsigned char     SKdAuftragartBANR_;   // SKd Auftragart Basis Natra rechnen
    unsigned char     SKdAuftragartMonat_;  // SKd Auftragart Monatrab rechnen
    unsigned char     SKdAuftragartVerbund_; // SKd Auftragsart im Verbund
    unsigned char     SKdAuftragartValS_;   // SKd Auftragart Valutasperre
    unsigned char     SKdAuftragartDD_;     // SKd Auftragart Delayed Delivery
    short             ValutaMonAuto_;       // Valuta in Monaten zusätzlich

//  new members:
    unsigned char     Discountable_;    // order is discountable
    unsigned char     DisInKindEnterable_; // discount-in-kind quantity is enterable
    unsigned char     Default_;         // Default order category
    unsigned char     Global_;          // Global for all customers
    unsigned char     ValidViaDCT_;     // may be set when transmitted via DCT
    unsigned char     ValidViaVideo_;   // may be entered via video device
    short             BranchNo_;        // branch number
    unsigned char     MustSubOrder_;    // Dutyflag for SubOrderType
    unsigned char     FreePrice_;       // ordertype freeprice input
    unsigned char     OrderCons_;       // ordertype for consolidation
    unsigned char     RestDel_;         // ordertype for restdelivery
    unsigned char     NoQuota_;         // ordertype with no Quota
    unsigned char     NoPartQty_;       // ordertype No Partial Qty
    unsigned char     DeferOrder_;      // ordertype defer order general
    unsigned char     ServiceOrder_;    // ordertype service order
    unsigned char     NoDD_;            // ordertype no delayed delivery
    unsigned char     OnlyEH_;          // ordertype nur fue Einzelhandel
    short             SNoPromotions_;   // SNoPromotions
    short             SDefaultKennung_; // SDefaultKennung MSV3
    short             SAlwaysRestDel_;  // SAlwaysRestDel ignore customers definitions
    short             SStockreservation_; // SStockreservation

private:
    tOrderTypeCode     Category_;        // Category code
    void              Translate();
    friend class pxOrderTypeList;
};


class pxOrderTypeList : public nDListCollect, public nDBRecordSet
{
public:
    virtual           ~pxOrderTypeList()   {Clear();}
                      pxOrderTypeList(pxSession *session);

    void              Clear()              {nDBRecordSet::Clear();}
    pxOrderType*      NewItem(const nString& key, const short BranchNo);
    pxOrderType*      Find( const nString& KdAuftragArt,const short BranchNo = 0);
    short             Find( const short BranchNo );
    size_t            Select(short BranchNo = 0,const int c = cDEFAULT);
    pxSession*        Session()            { return (pxSession*) DataBase();}

protected:
    virtual
    nCollectable*     AddToList(const void *record, const int row);
    virtual  int      EndBrowse(const int cursorid);
    virtual  int      GetNext(const void* record, const int cursorid);
    virtual  int      StartBrowse(const void *keys, const int cursorid);

private:
    friend class pxOrderTypeListIter;
};

class pxOrderTypeListIter : public nDListCollectIter
{
public:
    pxOrderTypeListIter(pxOrderTypeList& list) : nDListCollectIter(list) {;}
    virtual  ~pxOrderTypeListIter() {;}
};


#endif
