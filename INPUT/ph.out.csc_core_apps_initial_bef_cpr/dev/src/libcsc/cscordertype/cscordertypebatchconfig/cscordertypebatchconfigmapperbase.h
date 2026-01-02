#ifndef GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_MAPPER_BASE_H
#define GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include <cscordertype/cscordertypebatchconfig/cscordertypebatchconfigptr.h>

namespace libcsc 
{
namespace cscordertype
{
class CSCOrderTypeBatchConfigMapperBase
{
public:
    CSCOrderTypeBatchConfigMapperBase( CSCOrderTypeBatchConfigPtr batchConfig );

    void map();

protected:
    virtual ~CSCOrderTypeBatchConfigMapperBase();

    virtual void doMap() = 0;

	void setBranchNo( const basar::Int16 branchno );
	void setOrderType( const basar::VarString & orderType );
	void setAllowDesiredBatch( const bool allowDesiredBatch );
	void setAllowFixedBatch( const bool allowFixedBatch );
	void setForbidUserChange( const bool forbidUserChange );

private:
    CSCOrderTypeBatchConfigPtr	m_BatchConfig;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_MAPPER_BASE_H
