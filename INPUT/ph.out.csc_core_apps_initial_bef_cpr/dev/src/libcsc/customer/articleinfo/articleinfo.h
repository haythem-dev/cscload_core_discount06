#ifndef GUARD_LIBCSC_CUSTOMER_ARTICLEINFO_H
#define GUARD_LIBCSC_CUSTOMER_ARTICLEINFO_H

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_decimal.h>
#include <libbasarcmnutil_date.h>

namespace libcsc {
namespace customer {

class ArticleInfo
{
    // because of OR mapping
    friend class ArticleInfoMapperBase;

public:
    ArticleInfo();
    virtual ~ArticleInfo();

    virtual basar::Int16            getBranchNo() const;
    virtual basar::Int32            getArticleNo() const;
    virtual basar::VarString        getEAN() const;
    virtual basar::VarString        getName() const;
    virtual basar::VarString        getAlternateName() const;
    virtual basar::VarString        getManufacturerName() const;
    virtual basar::Decimal          getBasePrice() const;
    virtual basar::Decimal          getVatPercentage () const;
    virtual bool                    getPositiveList() const;
    virtual bool                    getActiveFlag() const;
    virtual bool                    getBlockedFlag() const;
    virtual basar::Date             getCreationDate() const;
    virtual basar::Date             getChangeDate() const;
    virtual basar::VarString        getArtInfoText() const;
    virtual bool                    getColdChainFlag() const;
    virtual bool                    getNarcoticFlag() const;
    virtual basar::Date             getAvailableFrom() const;
    virtual bool                    getQuotaPPE() const;

private:
    basar::Int16        m_BranchNo;
    basar::Int32        m_ArticleNo;
    basar::VarString    m_EAN;
    basar::VarString    m_Name;
    basar::VarString    m_AlternateName;
    basar::VarString    m_ManufacturerName;
    basar::Decimal      m_BasePrice;
    basar::Decimal      m_VatPercentage;
    bool                m_PositiveList;
    bool                m_ActiveFlag;
    bool                m_BlockedFlag;
    basar::Date         m_CreationDate;
    basar::Date         m_ChangeDate;
    basar::Date         m_AvailableFrom;
    basar::VarString    m_ArtInfoText;
    bool                m_ColdChainFlag;
    bool                m_NarcoticFlag;
    bool                m_QuotaPPE;

};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ARTICLEINFO_H
