#ifndef GUARD_LIBCSC_I_ORDER_PARAMETER_GETTER_H
#define GUARD_LIBCSC_I_ORDER_PARAMETER_GETTER_H

namespace libcsc
{
namespace parameter
{
class IOrderParameterGetter
{
public:
	virtual ~IOrderParameterGetter() {}

	virtual bool isInfoOrder() const = 0;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_ORDER_PARAMETER_GETTER_H
