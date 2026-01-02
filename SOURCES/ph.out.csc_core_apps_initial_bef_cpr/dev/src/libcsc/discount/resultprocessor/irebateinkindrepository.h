#ifndef GUARD_LIBCSC_I_REBATE_IN_KIND_REPOSITORY_H
#define GUARD_LIBCSC_I_REBATE_IN_KIND_REPOSITORY_H


namespace libcsc
{
namespace discount
{
class IRebateInKindRepository
{
public:
	virtual ~IRebateInKindRepository() {}

	virtual void reset() = 0;
	virtual void save() = 0;
	virtual void save4ever() = 0;
};

} // end namespace discount
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_REBATE_IN_KIND_REPOSITORY_H
