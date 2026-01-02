#include "customerdatamapperbase.h"
#include "customerdata.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace msv3 {

CustomerDataMapperBase::CustomerDataMapperBase(CustomerDataPtr customerData) :
	m_CustomerData(customerData)
{
}

CustomerDataMapperBase::~CustomerDataMapperBase()
{
}

void CustomerDataMapperBase::map()
{
	doMap();
}

void CustomerDataMapperBase::setXmlInfoLevel(const basar::Int32& xmlinfolevel)
{
	m_CustomerData->setXmlInfoLevel(xmlinfolevel);
	m_CustomerData->m_XmlInfoLevel.setClean();
}

void CustomerDataMapperBase::setClean()
{
	m_CustomerData->m_XmlInfoLevel.setClean();
}

} // end namespace msv3
} // end namespace libcsc
