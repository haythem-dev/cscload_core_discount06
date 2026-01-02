#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATION_ARTICLERESERVATION_SQLMAPPER_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATION_ARTICLERESERVATION_SQLMAPPER_H

#include "articlereservationmapperbase.h"
#include <stockbooking/reservation/iarticlereservationptr.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace stockbooking {

class ArticleReservationSQLMapper : public ArticleReservationMapperBase
{
public:
	ArticleReservationSQLMapper(ArticleReservationPtr articleReservation, const basar::db::sql::ResultsetRef resultSet);
	virtual ~ArticleReservationSQLMapper();

	static const basar::VarString getSelectSQL(const basar::Int16& branchNo, const basar::Int32& articleNo );
	static const basar::VarString getUpdateSQL(const IArticleReservationPtr articleReservation );
	static const basar::VarString getInsertSQL(const IArticleReservationPtr articleReservation );
	static const basar::VarString getDeleteSQL( const IArticleReservationPtr articleReservation );


protected:
	virtual void doMap();

private:
	ArticleReservationSQLMapper(const ArticleReservationSQLMapper&);
	ArticleReservationSQLMapper & operator=(const ArticleReservationSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATION_ARTICLERESERVATION_SQLMAPPER_H
