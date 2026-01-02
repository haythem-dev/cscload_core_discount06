#ifndef GUARD_IARTICLESTOCKBOOKING_HPP
#define GUARD_IARTICLESTOCKBOOKING_HPP

#include <database.hpp>

class IArticleStockBooking
{
public:
	virtual 		~IArticleStockBooking() {}
	virtual int     Get(DBAccessMode mode = cDBGET_READONLY) = 0;
	virtual int     Put() = 0;

	virtual long	ArtikelNr() const = 0;
	virtual short	FilialNr() const = 0;
	
	virtual nError& Error() = 0;
	virtual bool    IsGoodState() = 0;

	virtual long	AddQuantity(const long q) = 0;
	virtual long	SubQuantity(const long q) = 0;
	virtual long	SetQuantity(const long q) = 0;
	virtual long	GetQuantity() const = 0;
};

#endif // GUARD_IARTICLESTOCKBOOKING_HPP
