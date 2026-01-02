#ifndef PXSUPPLDELIVERYINFO_INC
#define PXSUPPLDELIVERYINFO_INC

#include "pxbase/pxrecord.hpp"
#include "libbasarcmnutil_date.h"
#include "libbasarcmnutil_bstring.h"

struct tSUPPLDELIVERYINFO;

class pxSupplDeliveryInfo : public pxDBRecord
{
public:
	pxSupplDeliveryInfo(pxSession *session);
	pxSupplDeliveryInfo(const pxSupplDeliveryInfo& src);
	pxSupplDeliveryInfo(pxSession *session,tSUPPLDELIVERYINFO& src);
	pxSupplDeliveryInfo(pxSession *session,
		const long  ArtikelNr,
		DBAccessMode mode = cDBGET_READONLY);
	virtual  ~pxSupplDeliveryInfo();

	pxSupplDeliveryInfo&   operator=(const pxSupplDeliveryInfo& src);
	pxSupplDeliveryInfo&   operator=(const tSUPPLDELIVERYINFO& src);

	friend   pxSupplDeliveryInfo&  Assign(pxSupplDeliveryInfo& dest, const tSUPPLDELIVERYINFO& src);
    friend   tSUPPLDELIVERYINFO&   Assign(tSUPPLDELIVERYINFO& dest, const pxSupplDeliveryInfo& src);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    //virtual  int     Put();
    //virtual  int     Delete();

    virtual  int     Read(const void *record);
    //virtual  int     Insert(const void *record);
    //virtual  int     Delete(const void *record);

// Queries:
	long					Id() { return Id_;  }
	long					ArticleNo() { return ArticleNo_; }
	const basar::VarString&	AvailabilityInfo() { return AvailabilityInfo_; }
	const basar::Date&		PredictedAvailDate() { return PredictedAvailDate_; }
	const basar::Date&		AvailableDate() { return AvailableDate_; }

protected:
	void				Init();

	long				Id_;
    long				ArticleNo_;       // Artikelnummer
	basar::VarString	AvailabilityInfo_;
	basar::Date			PredictedAvailDate_;
	basar::Date			AvailableDate_;
private:
};


#endif

