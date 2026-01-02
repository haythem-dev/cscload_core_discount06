#ifndef PXCUSTSTOCKRESERVED_INC
#define PXCUSTSTOCKRESERVED_INC

#include "pxbase/pxrecord.hpp"
#include "types/reservationtypeenum.inc"
#include <libbasarcmnutil_datetime.h>

struct tCSTSTOCKRESERVED;

/*----------------------------------------------------------------------------*/
/* class pxCustStockReserved                                                  */
/*----------------------------------------------------------------------------*/
class pxCustStockReserved : public pxDBRecord
{
public:
	pxCustStockReserved(pxCustStockReserved& src);
	pxCustStockReserved(pxSession *session);
	pxCustStockReserved(pxSession *session, tCSTSTOCKRESERVED& src);
	pxCustStockReserved(pxSession *session, const short BranchNo, const long CustomerNo,
		const long ArticleNo, const basar::DateTime& FromDateTime, const ReservationTypeEnum ReservType);
	virtual  ~pxCustStockReserved();

private:
	//!  Assigns the values of 'src' to self and returns a reference to it.
	pxCustStockReserved&   operator=(const pxCustStockReserved& src);

	//!  Assigns the values of the record structure 'src' to self and returns a
	//!  reference to self.
	pxCustStockReserved&   operator=(const tCSTSTOCKRESERVED& src);

	pxCustStockReserved& AssignFrom(const tCSTSTOCKRESERVED& src);
	tCSTSTOCKRESERVED&   AssignTo(tCSTSTOCKRESERVED& dest) const;
public:

	virtual  int      CompareTo(const nCollectable *that, void *p, const long lparm) const;
	virtual  int      Get(DBAccessMode mode = cDBGET_READONLY);
	virtual  int      Put();
	virtual  int      Delete();

	virtual  int      Read(const void *record);
	virtual  int      ReadLock(const void *record);
	virtual  int      Insert(const void *record);
	virtual  int      Update(const void *record);
	virtual  int      Delete(const void *record);
	virtual  long     AddQuantity(const long q);
	virtual  long     SubQuantity(const long q);

	//  Queries:
	short					BranchNo() const		{return BranchNo_;		}
	long					CustomerNo() const		{return CustomerNo_;	}
	long					ArticleNo() const		{return ArticleNo_;		}
	long					ReservedQty() const		{return ReservedQty_;	}
	const basar::DateTime&	DateTimeFrom() const	{return DateTimeFrom_;	}
	const basar::DateTime&	DateTimeTo() const		{return DateTimeTo_;	}
	long					KdAuftragNr() const		{return KdAuftragNr_;	}
	ReservationTypeEnum		ReservType() const		{return ReservType_;	}

//  Field Updates:
    void					SetReservedQty(const long q)					{ ReservedQty_ = q;			}
    void					SetKdAuftragNr(const long orderno)				{ KdAuftragNr_ = orderno;	}
    void					SetDateTimeFrom(const basar::DateTime& date)	{ DateTimeFrom_ = date;		}
    void					SetDateTimeTo(const basar::DateTime& date)		{ DateTimeTo_ = date;		}
protected:
	void        Init();

	short				BranchNo_;		//!< Branchnumber
	long				CustomerNo_;	//!< Customernumber
	long				ArticleNo_;		//!< Article number
	long				ReservedQty_;	//!< reserved quantity
	basar::DateTime		DateTimeFrom_;	//!< Date from
	basar::DateTime		DateTimeTo_;	//!< Date to
	long				KdAuftragNr_;	//!< KdAuftragNr
	ReservationTypeEnum	ReservType_;	//!< Reservtype
private:
    friend class pxCustStockReservedList;
};

/*----------------------------------------------------------------------------*/
/* class pxCustStockReservedList                                              */
/*----------------------------------------------------------------------------*/
class pxCustStockReservedList : public nDBRecordSet, public nDListCollect
{
public:
							pxCustStockReservedList(pxSession* session);
	virtual					~pxCustStockReservedList();

	pxSession*				Session();

	size_t					SelectAllReservations(const short BranchNo, const long ArticleNo);

	size_t					SelectCustomerReservations(const short BranchNo, const long ArticleNo, const long CustomerNo);

	size_t					SelectOldReservations (const short BranchNo, const basar::DateTime& DateTimeTo);

	void					Clear()        {nDBRecordSet::Clear();}

	virtual nCollectable*	AddToList(const void *record, const int row);
	virtual int				GetNext(const void* record, const int cursorid);
	virtual int				StartBrowse(const void *keys, const int cursorid);
	virtual int				EndBrowse(const int cursorid);

private:
    friend class pxCustStockReservedListIter;
};

/*----------------------------------------------------------------------------*/
/* class pxCustStockReservedListIter                                          */
/*----------------------------------------------------------------------------*/
class pxCustStockReservedListIter : public nDListCollectIter
{
public:
    pxCustStockReservedListIter(pxCustStockReservedList& list) : nDListCollectIter(list) {}
    virtual  ~pxCustStockReservedListIter() {}
};
#endif
