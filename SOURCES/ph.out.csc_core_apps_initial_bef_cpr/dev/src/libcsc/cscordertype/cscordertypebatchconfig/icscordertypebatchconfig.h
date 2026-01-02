#ifndef GUARD_LIBCSC_I_CSCORDERTYPE_BATCHCONFIG_H
#define GUARD_LIBCSC_I_CSCORDERTYPE_BATCHCONFIG_H

#include <libbasar_definitions.h>
#include <datatypes/int16.h>
#include <datatypes/boolean.h>
#include <datatypes/varstring.h>
#include <base/istreamable.h>

namespace libcsc
{
namespace cscordertype
{
class ICSCOrderTypeBatchConfig : public base::IStreamable
{
public:
	virtual ~ICSCOrderTypeBatchConfig() {};

	virtual const libcsc::Int16 & getBranchNo() const = 0;
	virtual const libcsc::VarString & getOrderType() const = 0;
	virtual const libcsc::Bool & getAllowDesiredBatch() const = 0;
	virtual const libcsc::Bool & getAllowFixedBatch() const = 0;
	virtual const libcsc::Bool & getForbidUserChange() const = 0;

	virtual void setBranchNo( const basar::Int16 branchno ) = 0;
	virtual void setOrderType( const basar::VarString & orderType ) = 0;
	virtual void setAllowDesiredBatch( const bool allowDesiredBatch ) = 0;
	virtual void setAllowFixedBatch( const bool allowFixedBatch ) = 0;
	virtual void setForbidUserChange( const bool forbidUserChange ) = 0;
};

} // namespace cscordertype
} // namespace libcsc

#endif // GUARD_LIBCSC_I_CSCORDERTYPE_BATCHCONFIG_H
