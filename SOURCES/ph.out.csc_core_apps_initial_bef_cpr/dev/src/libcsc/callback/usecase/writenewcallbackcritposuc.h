/*
 * writenewcallbackcritposuc.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_IBT_UC_WRITENEWCALLBACKCRITPOSUC_H
#define GUARD_LIBCSC_IBT_UC_WRITENEWCALLBACKCRITPOSUC_H

#include "callback/repository/irepositoryptr.h"
#include "callback/domainmodule/icritposptr.h"
#include "callback/domainmodule/inewcallbackcritposptr.h"
#include <libbasar_definitions.h>
#include <base/irunnable.h>

namespace libcsc {
namespace callback {
namespace uc {

class WriteNewCallbackCritPosUC : public base::IRunnable
{
public:
    WriteNewCallbackCritPosUC();
    virtual ~WriteNewCallbackCritPosUC();

    void injectRepository(repo::IRepositoryPtr repository);
    void setNewCritPos(domMod::INewCallbackCritPosPtr newCallbackCritPos);
    void run();

private:
    repo::IRepositoryPtr m_Repository;
    basar::Int32 m_CallbackNo;
    basar::Int16 m_StatusNo;
    domMod::ICritPosPtr m_CritPos;
};

typedef boost::shared_ptr<WriteNewCallbackCritPosUC> WriteNewCallbackCritPosUCPtr;

} // end namespace uc
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_UC_WRITENEWCALLBACKCRITPOSUC_H
