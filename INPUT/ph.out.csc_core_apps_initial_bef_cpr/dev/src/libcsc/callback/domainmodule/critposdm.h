/*
 * critposdm.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CRITPOSDM_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CRITPOSDM_H

#include "icritposptr.h"
#include "icritpos.h"

namespace libcsc {
namespace callback {

namespace repo {
class CritPosMapper;
}

namespace domMod {

class CritPosDM : public ICritPos
{
    // because of OR mapping
    friend class repo::CritPosMapper;

public:
    virtual ~CritPosDM();

    static ICritPosPtr create();

    virtual Int32 const& getPosNo() const;
    virtual VarString const& getPosTypeTag() const;
    virtual Int32 const& getCritNo() const;
    virtual VarString const& getText() const;
    virtual Int32 const& getUId() const;
    virtual Int16 const& getBranchNo() const;
    virtual Int32 const& getDate() const;
    virtual Int32 const& getTime() const;
    virtual VarString const& getWindowsUserId() const;
    virtual Int16 const& getSourceApplication() const;

public:
    virtual void setPosNo(Int32 const& posNo);
    virtual void setPosTypeTag(VarString const& posTypeTag);
    virtual void setCritNo(Int32 const& critNo);
    virtual void setText(VarString const& text);
    virtual void setUId(Int32 const& uId);
    virtual void setBranchNo(Int16 const& branchNo);
    virtual void setDate(Int32 const& date);
    virtual void setTime(Int32 const& time);
    virtual void setWindowsUserId(VarString const& windowsUserId);
    virtual void setSourceApplication(Int16 const& sourceApplication);

    virtual std::ostream& toStream(std::ostream& strm = std::cout) const;

protected:
    CritPosDM();

private:
    Int32 m_PosNo;
    VarString m_PosTypeTag;
    Int32 m_CritNo;
    VarString m_Text;
    Int32 m_UId;
    Int16 m_BranchNo;
    Int32 m_Date;
    Int32 m_Time;
    VarString m_WindowsUserId;
    Int16 m_SourceApplication;

    CritPosDM(const CritPosDM&);
    CritPosDM& operator=(const CritPosDM&);
};

} // namespace domMod
} // namespace callback
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CRITPOSDM_H
