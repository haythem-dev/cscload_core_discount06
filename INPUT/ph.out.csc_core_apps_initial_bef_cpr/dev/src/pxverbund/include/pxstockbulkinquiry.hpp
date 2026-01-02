/***************************************************************************************************************************/

#ifndef PXSTOCKBULKINQUIRY_INC
#define PXSTOCKBULKINQUIRY_INC

/***************************************************************************************************************************/

#include "pxerrorloggable.hpp"
#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <boost/shared_ptr.hpp>

/***************************************************************************************************************************/

class pxSession;
class pxStockBooking;
class pxCustBase;
class pxArticleChargeList;
class pxArtReservationList;

/***************************************************************************************************************************/

class pxStockBulkInquiry : public pxErrorLoggable
{
	static const basar::UInt32 MAX_OUTPUT_LEN		= 4001;

	static const basar::Int32 ERR_INPUT_TOO_LONG	= -1;
	static const basar::Int32 ERR_OUTPUT_TOO_LONG	= -2;

public:
	pxStockBulkInquiry(pxSession* session);
	virtual ~pxStockBulkInquiry();

	void						setBranchAndCustomer(const basar::Int16 branchNo, const basar::Int32 customerNo = 0); 
	basar::VarString			getArticleStock(const basar::VarString& queryString);
	basar::Int32				getArticleStockSingle(const basar::VarString& articleCode); // public for Thrift
	pxArticleChargeList*		getArticleStockBatchSingle(const basar::VarString& articleCode); // public for Thrift
	pxArtReservationList*		getArticleReservationListSingle(const basar::VarString& articleCode); // public for Thrift

	basar::VarString			getArticleAvailability(const basar::VarString& queryString);
	bool						getArticleAvailabilitySingle(const basar::VarString& articleCode); // public for Thrift


private:
	basar::cmnutil::CollBString	getArticleAvailabilityColl(const basar::cmnutil::CollBString& queryArticles);
	basar::cmnutil::CollBString	getArticleStockColl(const basar::cmnutil::CollBString& queryArticles);

	basar::Int32				convertArticleCodeToArticleNo(const basar::VarString& articlecode);

	pxSession*					m_Session;
	boost::shared_ptr<pxStockBooking>	m_Booking;
	basar::Int16				m_BranchNo;
	pxCustBase*					m_Customer;
	pxArticleChargeList*		m_ArticleChargeList;
	pxArtReservationList*		m_ArticleReservationList;
};

/***************************************************************************************************************************/

#endif // PXSTOCKBULKINQUIRY_INC

/***************************************************************************************************************************/
