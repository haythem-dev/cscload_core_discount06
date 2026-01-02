#ifndef GUARD_LIBCSC_IBT_IBTREQUESTKEY_H
#define GUARD_LIBCSC_IBT_IBTREQUESTKEY_H

#include <libbasar_definitions.h>

namespace libcsc
{
namespace ibt
{
struct IbtRequestKey
{
    IbtRequestKey(
		const basar::Int16 _branchNo = 0, 
		const basar::Int32 _cscOrderNo = 0, 
		const basar::Int32 _cscOrderPosNo = 0//, 
//		const basar::Int16 _ibtBranchNo = 0
			)
        : branchNo( _branchNo ), cscOrderNo( _cscOrderNo ), cscOrderPosNo( _cscOrderPosNo )//, ibtBranchNo( _ibtBranchNo )
    {
    }

    basar::Int16 branchNo;
    basar::Int32 cscOrderNo;
    basar::Int32 cscOrderPosNo;
//    basar::Int16 ibtBranchNo;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTKEY_H
