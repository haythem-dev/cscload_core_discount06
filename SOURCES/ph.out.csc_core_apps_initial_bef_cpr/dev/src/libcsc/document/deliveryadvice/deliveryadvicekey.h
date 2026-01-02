#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_KEY_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_KEY_H

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasar_definitions.h>
#include <list>

namespace libcsc {
namespace document {

struct DeliveryAdviceKey
{
    DeliveryAdviceKey(
		const basar::Int16 _branchNo = 0,
		const basar::Int32 _customerNo = 0,
		const basar::Date _deliveryAdviceDate = basar::Date(0),
		const basar::VarString _deliveryAdviceNo = "",
		const basar::Int32 _cscOrderNo = 0) :
		branchNo(_branchNo),
		customerNo( _customerNo),
		deliveryAdviceDate(_deliveryAdviceDate),
		deliveryAdviceNo(_deliveryAdviceNo),
		cscOrderNo(_cscOrderNo)
    {
    }

    basar::Int16 		branchNo;
    basar::Int32		customerNo;
    basar::Date			deliveryAdviceDate;
    basar::VarString	deliveryAdviceNo;	// either search by deliveryadviceno...
	basar::Int32		cscOrderNo;			// ... or by CSC orderno
};

typedef std::list<DeliveryAdviceKey> DeliveryAdviceKeyCollection;

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_KEY_H
