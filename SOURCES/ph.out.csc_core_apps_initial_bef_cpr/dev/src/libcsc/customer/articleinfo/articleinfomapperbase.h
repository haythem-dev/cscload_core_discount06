#ifndef GUARD_LIBCSC_CUSTOMER_ARTICLEINFOMAPPERBASE_H
#define GUARD_LIBCSC_CUSTOMER_ARTICLEINFOMAPPERBASE_H

#include <customer/articleinfo/articleinfoptr.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class ArticleInfoMapperBase
{
public:
    ArticleInfoMapperBase(ArticleInfoPtr articleInfo);

    void map();
    void mapArtInfoText();

protected:
    virtual ~ArticleInfoMapperBase();
    
    virtual void doMap() = 0;
    virtual void doMapArtInfoText() = 0;

    void setBranchNo(const basar::Int16 branchNo);
    void setArticleNo(const basar::Int32 articleNo);
    void setEAN(const basar::VarString& ean);
    void setName(const basar::VarString& name);
    void setAlternateName(const basar::VarString& alternateName);
    void setManufacturerName(const basar::VarString& maunfacuturerName);
    void setBasePrice(const basar::Decimal& basePrice);
    void setVatPercentage(const basar::Decimal& vatPercentage);
    void setPositiveList(bool positiveList);
    void setActiveFlag(bool activeFlag);
    void setBlockedFlag(bool blockedFlag);
    void setCreationDate(const basar::Date& creationDate);
    void setChangeDate(const basar::Date& changeDate);
    void setAvailableFrom(const basar::Date& availableFrom);

    void appendArtInfoText(const basar::VarString& text);

    void setColdChainFlag(bool coldChainFlag);
    void setNarcoticFlag(bool narcoticFlag);
    void setQuotaPPE(bool quotaPPE);

private:
    ArticleInfoPtr m_ArticleInfo;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ARTICLEINFOMAPPERBASE_H
