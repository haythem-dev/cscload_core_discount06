#ifndef GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_H
#define GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_H

#include <cscordertype/cscordertypebatchconfig/icscordertypebatchconfig.h>
#include <datatypes/propertycollection.h>

namespace libcsc
{
namespace cscordertype
{
class CSCOrderTypeBatchConfig : public ICSCOrderTypeBatchConfig
{
    // because of OR mapping
    friend class CSCOrderTypeBatchConfigMapperBase;

public:
    CSCOrderTypeBatchConfig();
    virtual ~CSCOrderTypeBatchConfig();

	virtual const libcsc::Int16 & getBranchNo() const;
	virtual const libcsc::VarString & getOrderType() const;
	virtual const libcsc::Bool & getAllowDesiredBatch() const;
	virtual const libcsc::Bool & getAllowFixedBatch() const;
	virtual const libcsc::Bool & getForbidUserChange() const;

	virtual void setBranchNo( const basar::Int16 branchno );
	virtual void setOrderType( const basar::VarString & orderType );
	virtual void setAllowDesiredBatch( const bool allowDesiredBatch );
	virtual void setAllowFixedBatch( const bool allowFixedBatch );
	virtual void setForbidUserChange( const bool forbidUserChange );

	virtual std::ostream & toStream( std::ostream & strm /* = std::cout */ ) const;

	void setClean();
	bool containsDirty() const;

private:
    CSCOrderTypeBatchConfig( const CSCOrderTypeBatchConfig & );
    CSCOrderTypeBatchConfig & operator=( const CSCOrderTypeBatchConfig & );

    libcsc::Int16 m_BranchNo;
    libcsc::VarString m_OrderType;
	libcsc::Bool m_AllowDesiredBatch;
	libcsc::Bool m_AllowFixedBatch;
	libcsc::Bool m_ForbidUserChange;
	libcsc::PropertyCollection	m_PropertyCollection;
};

} // namespace cscordertype
} // namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_H
