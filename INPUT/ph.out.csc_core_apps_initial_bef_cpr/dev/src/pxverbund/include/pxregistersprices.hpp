#ifndef PXREGISTERSPRICES_GUARD
#define PXREGISTERSPRICES_GUARD

#include "pxbase/pxrecord.hpp"
#include <money.hpp>
#include <date.hpp>
#include <iregisterspricegetter.h>

struct tREGISTERSPRICES;

class pxRegistersPrices : public pxDBRecord, public csc::pricing::IRegisterPriceGetter
{
    public:
        virtual           ~pxRegistersPrices();
	    pxRegistersPrices(pxRegistersPrices& src);
	    pxRegistersPrices(pxSession *session);
	    pxRegistersPrices(pxSession *session, const nString& MinistryProductCode);

	    pxRegistersPrices&          operator=(const pxRegistersPrices& src);
	    pxRegistersPrices&          operator=(const tREGISTERSPRICES& src);

        virtual const nMoney&       getMaxWholesalePrice() const;
        virtual const nMoney&       getReferencePrice() const;

        virtual  int                Get(DBAccessMode mode = cDBGET_READONLY);
        //virtual  int     Put();
        virtual  int                Read(const void *record);
        //virtual  int     ReadLock(const void *record);
        //virtual  int     Insert(const void *record);
        //virtual  int     Update(const void *record);

    //  Queries:
        const nString&              MinistryProductCode() const { return MinistryProductCode_; }
	    const nDate&                DateValidFrom()       const { return DateValidFrom_;       }
	    const nMoney&               MaxWholesalePrice()   const { return MaxWholesalePrice_;   }
	    const nMoney&               ReferencePrice()      const { return ReferencePrice_;      }

    //  Updates:
    protected:
	    pxRegistersPrices(pxSession *session, tREGISTERSPRICES& src);
        void                        Init();
        friend pxRegistersPrices&   Assign(pxRegistersPrices& dest, const tREGISTERSPRICES& src);
        friend tREGISTERSPRICES&    Assign(tREGISTERSPRICES& dest, const pxRegistersPrices& src);
        virtual  int                CompareTo(const nCollectable *that, void *p, const long lparm) const;

        nString                     MinistryProductCode_;
	    nDate                       DateValidFrom_;
        nMoney                      MaxWholesalePrice_;
	    nMoney                      ReferencePrice_;

    private:
        pxRegistersPrices();
};

#endif // PXREGISTERSPRICES_GUARD
