#ifndef GUARD_LIBCSC_IBT_I_IBTRESPONSE_REPOSITORY_H
#define GUARD_LIBCSC_IBT_I_IBTRESPONSE_REPOSITORY_H

#include <ibt/ibtresponse/iibtresponsefactory.h>

namespace libcsc
{
namespace ibt
{
class IIbtResponseRepository : public IIbtResponseFactory
{
public:
	virtual ~IIbtResponseRepository() {};
    
	virtual IIbtResponsePtr findIbtResponse( const basar::Int32 ibtOrderNo, const basar::Int32 ibtPosNo ) = 0;

	virtual void saveIbtResponse( IIbtResponsePtr ibtResponse ) = 0;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTRESPONSE_REPOSITORY_H
