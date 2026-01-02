#include <customer/articleinfo/articleorderinfo.h>

namespace libcsc {
namespace customer {

ArticleOrderInfo::ArticleOrderInfo()
{
    m_ArticleOrderDate = 0;
    m_ArticleGoodsReceiptTargetDate = 0;
}

ArticleOrderInfo::~ArticleOrderInfo()
{
}

basar::Int32 ArticleOrderInfo::getArticleOrderDate() const
{
    return m_ArticleOrderDate;
}

basar::Int32 ArticleOrderInfo::getArticleGoodsReceiptTargetDate() const
{
    return m_ArticleGoodsReceiptTargetDate;
}

bool ArticleOrderInfo::getIsArticleOrderEffective() const
{
    return m_IsArticleOrderEffective;
}

} // end namespace customer
} // end namespace libcsc
