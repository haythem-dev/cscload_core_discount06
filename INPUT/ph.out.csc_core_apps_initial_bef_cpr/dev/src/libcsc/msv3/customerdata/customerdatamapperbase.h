#ifndef GUARD_LIBCSC_MSV3_CUSTOMERDATAMAPPER_BASE_H
#define GUARD_LIBCSC_MSV3_CUSTOMERDATAMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "customerdataptr.h"

namespace libcsc {
namespace msv3 {

class CustomerDataMapperBase
{
public:
	CustomerDataMapperBase(CustomerDataPtr customerData);

	void			map();	

protected:
	virtual ~CustomerDataMapperBase();

	virtual void	doMap() = 0;	
	
	virtual void	setXmlInfoLevel(const basar::Int32& xmlinfolevel);	

	virtual void	setClean();

//private:
	CustomerDataPtr m_CustomerData;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_CUSTOMERDATAMAPPER_BASE_H
