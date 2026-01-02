#include <customer/articleinfo/articleinfomapperbase.h>
#include <customer/articleinfo/articleinfo.h>

namespace libcsc {
namespace customer {

ArticleInfoMapperBase::ArticleInfoMapperBase(ArticleInfoPtr articleInfo)
: m_ArticleInfo(articleInfo)
{
}

ArticleInfoMapperBase::~ArticleInfoMapperBase()
{
}

void ArticleInfoMapperBase::map()
{
    doMap();
}

void ArticleInfoMapperBase::mapArtInfoText()
{
    doMapArtInfoText();
}

void ArticleInfoMapperBase::setBranchNo( const basar::Int16 branchNo )
{
    m_ArticleInfo->m_BranchNo = branchNo;
}

void ArticleInfoMapperBase::setArticleNo(const basar::Int32 articleNo)
{
    m_ArticleInfo->m_ArticleNo = articleNo;
}

void ArticleInfoMapperBase::setEAN(const basar::VarString& ean)
{
    m_ArticleInfo->m_EAN = ean;
}

void ArticleInfoMapperBase::setName(const basar::VarString& name)
{
    m_ArticleInfo->m_Name = name;
}

void ArticleInfoMapperBase::setAlternateName(const basar::VarString & alternateName)
{
    m_ArticleInfo->m_AlternateName = alternateName;
}

void ArticleInfoMapperBase::setManufacturerName(const basar::VarString& manfacturerName)
{
    m_ArticleInfo->m_ManufacturerName = manfacturerName;
}

void ArticleInfoMapperBase::setBasePrice(const basar::Decimal& basePrice)
{
    m_ArticleInfo->m_BasePrice = basePrice;
}

void ArticleInfoMapperBase::setVatPercentage(const basar::Decimal& vatPercentage)
{
    m_ArticleInfo->m_VatPercentage = vatPercentage;
}

void ArticleInfoMapperBase::setPositiveList(bool positiveList)
{
    m_ArticleInfo->m_PositiveList = positiveList;
}

void ArticleInfoMapperBase::setActiveFlag(bool activeFlag)
{
    m_ArticleInfo->m_ActiveFlag = activeFlag;
}

void ArticleInfoMapperBase::setBlockedFlag(bool blockedFlag)
{
    m_ArticleInfo->m_BlockedFlag = blockedFlag;
}

void ArticleInfoMapperBase::setCreationDate(const basar::Date& creationDate)
{
    m_ArticleInfo->m_CreationDate = creationDate;
}

void ArticleInfoMapperBase::setChangeDate(const basar::Date& changeDate)
{
    m_ArticleInfo->m_ChangeDate = changeDate;
}

void ArticleInfoMapperBase::setAvailableFrom(const basar::Date& availableFrom)
{
    m_ArticleInfo->m_AvailableFrom = availableFrom;
}

void ArticleInfoMapperBase::appendArtInfoText(const basar::VarString& text)
{
    m_ArticleInfo->m_ArtInfoText += text;
}

void ArticleInfoMapperBase::setColdChainFlag(bool coldChainFlag)
{
    m_ArticleInfo->m_ColdChainFlag = coldChainFlag;
}

void ArticleInfoMapperBase::setNarcoticFlag(bool narcoticFlag)
{
    m_ArticleInfo->m_NarcoticFlag = narcoticFlag;
}

void ArticleInfoMapperBase::setQuotaPPE(bool quotaPPE)
{
    m_ArticleInfo->m_QuotaPPE = quotaPPE;
}


} // end namespace customer
} // end namespace libcsc

