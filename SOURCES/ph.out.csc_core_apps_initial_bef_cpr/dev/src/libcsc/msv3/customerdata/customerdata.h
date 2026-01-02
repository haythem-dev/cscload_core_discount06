#ifndef GUARD_LIBCSC_MSV3_CUSTOMERDATA_H
#define GUARD_LIBCSC_MSV3_CUSTOMERDATA_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>

#include "../pxverbund/include/types/xmlinfolevelenum.inc"

namespace libcsc {
namespace msv3 {

class CustomerData
{
	// because of OR mapping
	friend class CustomerDataMapperBase;
	friend class CustomerDataSQLMapper;

public:
	CustomerData(libcsc::Int16 branchNo, libcsc::Int32 customerNo);
	virtual ~CustomerData();

	virtual const libcsc::Int16&		getBranchNo() const;
	virtual const libcsc::Int32&		getCustomerNo() const;	
	virtual XMLInfoLevelEnum			getInfoLevel() const;
	
	virtual bool						isClean();
	virtual bool						isDirty();
	virtual void						setClean();

protected:	
	virtual void						setXmlInfoLevel(const libcsc::Int32& xmlinfolevel);

private:	
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::Int32						m_XmlInfoLevel;		
};

} // namespace msv3
} // namespace libcsc

#endif // GUARD_LIBCSC_MSV3_CUSTOMERDATA_H
