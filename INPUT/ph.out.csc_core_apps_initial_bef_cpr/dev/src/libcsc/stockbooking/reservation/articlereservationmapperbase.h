#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATION_ARTICLERESERVATION_MAPPER_BASE_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATION_ARTICLERESERVATION_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include "articlereservationptr.h"

namespace libcsc {
namespace stockbooking {

class ArticleReservationMapperBase
{
public:
	ArticleReservationMapperBase(ArticleReservationPtr articleReservation);

	void			map();
protected:
	virtual ~ArticleReservationMapperBase();

	virtual void	doMap() = 0;

	void setBranchNo( const basar::Int16& branchNo );
	void setPharmacyGroupId(const basar::VarString& pharmacyGroupId );
	void setArticleNo(const basar::Int32& articleNo);
	void setReservType( const basar::Int16& reservType );
	void setMaxQty(const basar::Int32& maxQty);
	void setReservedQty(const basar::Int32& reservedQty);
	void setReservePct(const basar::Int16& reservepct);

private:
	ArticleReservationPtr m_ArticleReservation;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATION_ARTICLERESERVATION_MAPPER_BASE_H
