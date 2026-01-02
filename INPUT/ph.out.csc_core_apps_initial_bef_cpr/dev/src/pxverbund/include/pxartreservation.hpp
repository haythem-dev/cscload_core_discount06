/*----------------------------------------------------------------------------*/

#ifndef PXARTRESERVATION_INC
#define PXARTRESERVATION_INC

/*----------------------------------------------------------------------------*/

#include "pxbase/pxrecord.hpp"
#include "types/reservationtypeenum.inc"
#include <libbasarcmnutil_bstring.h>

/*----------------------------------------------------------------------------*/

struct tARTICLERESERVATION;

/*----------------------------------------------------------------------------*/

class pxArtReservation : public pxDBRecord
{

public:
    pxArtReservation(pxArtReservation& src);
    pxArtReservation(pxSession *session);
    pxArtReservation(pxSession *session, tARTICLERESERVATION& src);
    pxArtReservation(pxSession *session, const short BranchNo, const long ArticleNo);
    virtual ~pxArtReservation();

    pxArtReservation&   operator=(const pxArtReservation& src);
    pxArtReservation&   operator=(const tARTICLERESERVATION& src);

    friend   pxArtReservation&
                Assign(pxArtReservation& dest, const tARTICLERESERVATION& src);
    friend   tARTICLERESERVATION&
                Assign(tARTICLERESERVATION& dest, const pxArtReservation& src);

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

    long                    AddReservedQuantity(const long q);
    long                    SubReservedQuantity(const long q);
    long                    SetReservedQuantity(const long q);

    void                    SetReservType(const ReservationTypeEnum rt);
    void                    SetPharmacyGroupId( const basar::VarString& PharmacyGroupId );
    void                    SetReservePct( const short pct );
    void                    SetMaxQty( const long maxqty );

//  Queries:
    short                   GetBranchNo() const              {return BranchNo_        ;}
    const basar::VarString& GetPharmacyGroupId() const       {return PharmacyGroupId_ ;}
    long                    GetArticleNo() const             {return ArticleNo_       ;}
    ReservationTypeEnum     GetReservType() const            {return ReservType_      ;}
    long                    GetMaxQty() const                {return MaxQty_          ;}
    long                    GetReservedQty() const           {return ReservedQty_     ;}
    short                   GetReservePct() const            {return ReservePct_      ;}

    bool                    IsReserveForPharmGroup() const   {return ReservType_ == RESTYPE_PHARMACYGROUP;      }
    bool                    IsReserveNoSalesEffectiv() const {return ReservType_ == RESTYPE_NO_SALES_EFFECTIVE; }
    //bool                    IsReserveNoCertificate() const   {return ReservType_ == RESTYPE_NO_CERTIFICATE;     }
    //bool                    IsReserveNoPackageInsert() const {return ReservType_ == RESTYPE_NO_PACKAGE_INSERT;  }
    //bool                    IsReserveBatchRecall() const     {return ReservType_ == RESTYPE_BATCH_RECALL;       }

protected:
    void                    Init();

    short                   BranchNo_;              // Filialnummer
    basar::VarString        PharmacyGroupId_;       // Pharmacy Group Id
    long                    ArticleNo_;             // Article Number
    ReservationTypeEnum     ReservType_;            // Reserve Type
    long                    MaxQty_;                // Maximum Quantity
    long                    ReservedQty_;           // Maximum Quantity
    short                   ReservePct_;            // Percentage

private:
    friend class pxArtReservationList;

};

class pxArtReservationList : public nDBRecordSet, public nDListCollect
{
public:
							pxArtReservationList(pxSession *session);
	virtual					~pxArtReservationList() {Clear();}

	pxSession*				Session()       { return (pxSession*) DataBase();}

	size_t					Select (const short BranchNo,const long ArticleNo);
	pxArtReservation*		FindReservationType(const ReservationTypeEnum reservType);
	void					Clear()        {nDBRecordSet::Clear();}

	virtual nCollectable*	AddToList(const void *record, const int row);
	virtual int				GetNext(const void* record, const int cursorid);
	virtual int				StartBrowse(const void *keys, const int cursorid);
	virtual int				EndBrowse(const int cursorid);

private:
    friend class pxArtReservationListIter;
};

class pxArtReservationListIter : public nDListCollectIter
{
public:
    pxArtReservationListIter(pxArtReservationList& list) : nDListCollectIter(list) {}
    virtual  ~pxArtReservationListIter() {}
};
#endif
