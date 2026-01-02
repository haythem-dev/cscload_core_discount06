#ifndef GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOMAPPERBASE_H
#define GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOMAPPERBASE_H

#include <libbasar_definitions.h>
#include "cscorderpossplittinfo.h"
#include "cscorderpossplittinfoptr.h"
#include "icscorderpossplittinfoptr.h"

namespace libcsc {
namespace cscorderpos {
namespace repo {

class CSCOrderposSplittinfoMapperBase
{
    public:
        CSCOrderposSplittinfoMapperBase(domMod::ICSCOrderposSplittinfoPtr splittinfo);

        void map();
        static void setClean(domMod::CSCOrderposSplittinfoPtr splittinfo);

    protected:
        virtual ~CSCOrderposSplittinfoMapperBase();

        virtual void doMap() = 0;

        void setCscOrderNo(basar::Int32 const cscorderno);
        void setCscOrderPosNo(basar::Int32 const cscorderposno);
        void setSplittType(SplittTypeEnum const splittype);
        void setOriginal(SplittOriginTypeEnum const original);
        void setOrderNo(basar::Int32 const orderno);
        void setOrderPosNo(basar::Int32 const orderposno);

    private:
        domMod::CSCOrderposSplittinfo& m_Splittinfo;

        CSCOrderposSplittinfoMapperBase& operator=(CSCOrderposSplittinfoMapperBase const&);
};

} // end namespace repo
} // end namespace cscorderpos
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERPOS_REPO_CSCORDERPOSSPLITTINFOMAPPERBASE_H
