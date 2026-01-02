#include "customerdata.h"

namespace libcsc {
namespace msv3 {

CustomerData::CustomerData(libcsc::Int16 branchNo, libcsc::Int32 customerNo)
	: m_BranchNo(branchNo), m_CustomerNo(customerNo)
{
}

CustomerData::~CustomerData()
{
}

const Int16& CustomerData::getBranchNo() const
{
	return m_BranchNo;
}

const Int32& CustomerData::getCustomerNo() const
{
	return m_CustomerNo;
}

XMLInfoLevelEnum CustomerData::getInfoLevel() const
{
	switch( m_XmlInfoLevel )
	{		
		case 4:
			return SpecificNoLimits;
		case 3:
			return Reservation;
		case 2:
			return Specific;
		case 1:
			return Unspecific;
		case 0:
		default:
			return NoPermission;
	}
}

void CustomerData::setXmlInfoLevel(const Int32& xmlinfolevel)
{
	m_XmlInfoLevel = xmlinfolevel;
}

bool CustomerData::isClean()
{
	return m_XmlInfoLevel.isClean();	
}

bool CustomerData::isDirty()
{
	return m_XmlInfoLevel.isDirty();
}

void CustomerData::setClean()
{
	m_XmlInfoLevel.setClean();
}

} // namespace msv3
} // namespace libcsc
