#include <customer/articleinfo/articleinfo.h>

namespace libcsc {
namespace customer {

ArticleInfo::ArticleInfo()
{
}

ArticleInfo::~ArticleInfo()
{
}

basar::Int16 ArticleInfo::getBranchNo() const
{
    return m_BranchNo;
}

basar::Int32 ArticleInfo::getArticleNo() const
{
    return m_ArticleNo;
}

basar::VarString ArticleInfo::getEAN() const
{
    return m_EAN;
}

basar::VarString ArticleInfo::getName() const
{
    return m_Name;
}

basar::VarString ArticleInfo::getAlternateName() const
{
    return m_AlternateName;
}

basar::VarString ArticleInfo::getManufacturerName() const
{
    return m_ManufacturerName;
}

basar::Decimal ArticleInfo::getBasePrice() const
{
    return m_BasePrice;
}

basar::Decimal ArticleInfo::getVatPercentage() const
{
    return m_VatPercentage;
}

bool ArticleInfo::getPositiveList() const
{
    return m_PositiveList;
}

bool ArticleInfo::getActiveFlag() const
{
    return m_ActiveFlag;
}

bool ArticleInfo::getBlockedFlag() const
{
    return m_BlockedFlag;
}

basar::Date ArticleInfo::getCreationDate() const
{
    return m_CreationDate;
}

basar::Date ArticleInfo::getChangeDate() const
{
    return m_ChangeDate;
}

basar::VarString ArticleInfo::getArtInfoText() const
{
    return m_ArtInfoText;
}

bool ArticleInfo::getColdChainFlag() const
{
    return m_ColdChainFlag;
}

bool ArticleInfo::getNarcoticFlag() const
{
    return m_NarcoticFlag;
}

basar::Date ArticleInfo::getAvailableFrom() const
{
    return m_AvailableFrom;
}

bool ArticleInfo::getQuotaPPE() const
{
    return m_QuotaPPE;
}

} // end namespace customer
} // end namespace libcsc

