#include <customer/articleinfo/articleorderinfomapperbase.h>
#include <customer/articleinfo/articleorderinfo.h>

namespace libcsc {
namespace customer {

ArticleOrderInfoMapperBase::ArticleOrderInfoMapperBase(ArticleOrderInfoPtr articleOrderInfo)
: m_ArticleOrderInfo(articleOrderInfo)
{
}

ArticleOrderInfoMapperBase::~ArticleOrderInfoMapperBase()
{
}

void ArticleOrderInfoMapperBase::map()
{
    doMap();
}

void ArticleOrderInfoMapperBase::setArticleOrderDate(const basar::Int32& articleOrderDate)
{
    m_ArticleOrderInfo->m_ArticleOrderDate = articleOrderDate;
}

void ArticleOrderInfoMapperBase::setArticleGoodsReceiptTargetDate(const basar::Int32& articleGoodsReceiptTargetDate)
{
    m_ArticleOrderInfo->m_ArticleGoodsReceiptTargetDate = articleGoodsReceiptTargetDate;
}

void ArticleOrderInfoMapperBase::setIsArticleOrderEffective(const bool isArticleOrderEffective)
{
    m_ArticleOrderInfo->m_IsArticleOrderEffective = isArticleOrderEffective;
}

} // end namespace customer
} // end namespace libcsc
