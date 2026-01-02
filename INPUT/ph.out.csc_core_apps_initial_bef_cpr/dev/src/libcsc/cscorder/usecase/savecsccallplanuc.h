/*
 * savecsccallplanuc.h
 *
 *  Created on: 25.09.2021
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_IBT_UC_SAVECALLPLANUC_H
#define GUARD_LIBCSC_IBT_UC_SAVECALLPLANUC_H

#include "base/irunnable.h"
#include "cscorder/csccallplan/icsccallplanrepositoryptr.h"
#include "cscorder/csccallplan/icsccallplanptr.h"
#include <base/iint32result.h>

namespace libcsc {
namespace cscorder {
namespace uc {

class SaveCSCCallplanUC : public libcsc::base::IRunnable
{
public:
    SaveCSCCallplanUC();
    virtual ~SaveCSCCallplanUC();

    void injectRepository(repo::ICSCCallplanRepositoryPtr repository);
    void setCallplan(short branchno, int customerno, int timeto);
    void run();

private:
    repo::ICSCCallplanRepositoryPtr m_Repository;
    domMod::ICSCCallplanPtr m_Callplan;

    bool saveCallplan();
};

typedef boost::shared_ptr<SaveCSCCallplanUC> SaveCSCCallplanUCPtr;

} // end namespace uc
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_UC_SAVECALLPLANUC_H
