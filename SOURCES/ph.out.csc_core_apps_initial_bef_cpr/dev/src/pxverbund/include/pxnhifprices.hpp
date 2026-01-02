#ifndef PXNHIFPRICES_GUARD
#define PXNHIFPRICES_GUARD

#include "pxbase/pxrecord.hpp"
#include <money.hpp>
#include <date.hpp>
#include "inhifpricegetter.h"

struct tNHIFPRICES;

class pxNHIFPrices : public pxDBRecord, public csc::pricing::INHIFPriceGetter

    
{
    public:
        virtual           ~pxNHIFPrices();
        pxNHIFPrices(pxNHIFPrices& src);
        pxNHIFPrices(pxSession *session);
        pxNHIFPrices(pxSession *session, const nString& HealthFundCodeHospital);

        pxNHIFPrices&           operator=(const pxNHIFPrices& src);
        pxNHIFPrices&           operator=(const tNHIFPRICES& src);

        virtual const nMoney&   getNHIFPrice() const;
        virtual  int            Get(DBAccessMode mode = cDBGET_READONLY);
        //virtual  int          Put();
        virtual  int            Read(const void *record);
        //virtual  int          ReadLock(const void *record);
        //virtual  int          Insert(const void *record);
        //virtual  int          Update(const void *record);

        //  Queries:
        const nString&   HealthFundCodeHospital() const { return HealthFundCodeHospital_; }
        const nDate&     DateValidFrom()          const { return DateValidFrom_;       }
        const nMoney&    NHIFPrice()              const { return NHIFPrice_;   }

//  Updates:
protected:
	pxNHIFPrices(pxSession *session, tNHIFPRICES& src);
    void              Init();
    friend
		pxNHIFPrices&       Assign(pxNHIFPrices& dest, const tNHIFPRICES& src);
    friend
		tNHIFPRICES&    Assign(tNHIFPRICES& dest, const pxNHIFPrices& src);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    nString          HealthFundCodeHospital_;
	nDate            DateValidFrom_;
    nMoney           NHIFPrice_;

private:
	pxNHIFPrices();
};

#endif // PXNHIFPRICES_GUARD
