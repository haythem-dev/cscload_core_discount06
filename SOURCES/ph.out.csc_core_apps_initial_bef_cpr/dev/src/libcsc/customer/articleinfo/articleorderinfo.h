#ifndef GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFO_H
#define GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFO_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class ArticleOrderInfo
{
    // because of OR mapping
    friend class ArticleOrderInfoMapperBase;

public:
    ArticleOrderInfo();
    virtual ~ArticleOrderInfo();

    virtual basar::Int32 getArticleOrderDate() const;
    virtual basar::Int32 getArticleGoodsReceiptTargetDate() const;
    virtual bool getIsArticleOrderEffective() const;

private:
    basar::Int32 m_ArticleOrderDate;
    basar::Int32 m_ArticleGoodsReceiptTargetDate;
    bool m_IsArticleOrderEffective;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFO_H
