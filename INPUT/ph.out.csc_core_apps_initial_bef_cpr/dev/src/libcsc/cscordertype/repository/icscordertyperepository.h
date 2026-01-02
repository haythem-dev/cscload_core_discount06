#ifndef GUARD_LIBCSC_I_CSCORDERTYPE_REPOSITORY_H
#define GUARD_LIBCSC_I_CSCORDERTYPE_REPOSITORY_H

#include <libbasar_definitions.h>
#include <cscordertype/icscordertypeptr.h>
#include <cscordertype/cscordertypecollectionptr.h>

namespace libcsc
{
namespace cscordertype
{
class ICSCOrderTypeRepository
{
public:
	virtual ~ICSCOrderTypeRepository() {}

	virtual void reset() = 0;

	virtual ICSCOrderTypePtr createOrderType() const = 0;
	virtual CSCOrderTypeCollectionPtr findOrderTypes( const basar::Int16 branchNo ) const = 0;
	virtual ICSCOrderTypePtr findOrderType( const basar::Int16 branchNo, const basar::VarString & orderType ) const = 0;
	virtual void saveOrderType( const ICSCOrderTypePtr orderType ) const = 0;
	virtual void deleteOrderType( const ICSCOrderTypePtr orderType ) const = 0;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_CSCORDERTYPE_REPOSITORY_H
