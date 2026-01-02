#ifndef GUARD_LIBCSC_IBT_I_IBTREQUEST_REPOSITORY_H
#define GUARD_LIBCSC_IBT_I_IBTREQUEST_REPOSITORY_H

#include <ibt/ibtrequest/iibtrequestfactory.h>
#include <ibt/ibtrequest/iibtrequestptr.h>
#include <ibt/ibtrequest/ibtrequestkey.h>
#include <ibt/ibtrequest/ibtrequestprocessingstateenum.h>

namespace libcsc
{
namespace ibt
{
class IIbtRequestRepository : public IIbtRequestFactory
{
public:
	virtual ~IIbtRequestRepository() {};

	virtual void reset() = 0;

	virtual IIbtRequestPtr findIbtRequestByKey( const IbtRequestKey & key ) = 0;
	virtual IIbtRequestPtr findIbtRequestById( const basar::Int32 id ) = 0;
	virtual void reloadIbtRequest( IIbtRequestPtr iibtRequest ) = 0;
	virtual IIbtRequestCollectionPtr findByPattern( const basar::Int16 branchNo, const IbtRequestProcessingStateEnum state ) = 0;
	virtual void saveIbtRequest( IIbtRequestPtr iibtRequest ) = 0;
	virtual void deleteIbtRequest( IIbtRequestPtr iibtRequest ) = 0;

	virtual IIbtRequestPtr createRequest( const IbtRequestKey & key ) = 0;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUEST_REPOSITORY_H
