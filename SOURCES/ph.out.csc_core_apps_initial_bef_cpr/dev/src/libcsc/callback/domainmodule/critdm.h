/*
 * critdm.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CRITDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CRITDM_H

#include "icritptr.h"
#include "icrit.h"

namespace libcsc {
namespace callback {

namespace repo {
class CritMapper;
}

namespace domMod {

class CritDM : public ICrit
{
    // because of OR mapping
    friend class repo::CritMapper;

public:
    virtual ~CritDM();

    static ICritPtr create();

    virtual Int32 const& getCritNo() const;
    virtual Int16 const& getBranchNo() const;
    virtual Int32 const& getCustomerNo() const;
    virtual Int16 const& getCstBranchNo() const;
    virtual Int32 const& getDate() const;
    virtual Int32 const& getTime() const;
    virtual Int32 const& getUId() const;
    virtual VarString const& getTitle() const;
    virtual Int16 const& getCritLevel() const;

public:
    virtual void setCritNo(Int32 const& critNo);
    virtual void setBranchNo(Int16 const& branchNo);
    virtual void setCustomerNo(Int32 const& customerNo);
    virtual void setCstBranchNo(Int16 const& cstBranchNo);
    virtual void setDate(Int32 const& date);
    virtual void setTime(Int32 const& time);
    virtual void setUId(Int32 const& uid);
    virtual void setTitle(VarString const& title);
    virtual void setCritLevel(Int16 const& critLevel);

    virtual std::ostream& toStream(std::ostream& strm = std::cout) const;

protected:
    CritDM();

private:
    Int32 m_CritNo;
    Int16 m_BranchNo;
    Int32 m_CustomerNo;
    Int16 m_CstBranchNo;
    Int32 m_Date;
    Int32 m_Time;
    Int32 m_UId;
    VarString m_Title;
    Int16 m_CritLevel;

    CritDM(const CritDM&);
    CritDM& operator=(const CritDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CRITDM_H
