#ifndef GUARD_LIBCSC_ORDER_PARAMETER_GETTER_H
#define GUARD_LIBCSC_ORDER_PARAMETER_GETTER_H

#include <parameter/iorderparametergetter.h>

class pxOrder;

namespace libcsc
{
namespace parameter
{
class OrderParameterGetter : public IOrderParameterGetter
{
public:
	OrderParameterGetter( const pxOrder * order );
	virtual ~OrderParameterGetter();

	virtual bool isInfoOrder() const;

private:
	const pxOrder *	m_Order;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_ORDER_PARAMETER_GETTER_H
