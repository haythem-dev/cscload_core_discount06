#ifndef GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFOMAPPERBASE_H
#define GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFOMAPPERBASE_H

#include <customer/articleinfo/articleorderinfoptr.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class ArticleOrderInfoMapperBase
{
public:
    ArticleOrderInfoMapperBase(ArticleOrderInfoPtr articleOrderInfo);

    void map();

protected:
    virtual ~ArticleOrderInfoMapperBase();
    
    virtual void doMap() = 0;

    void setArticleOrderDate(const basar::Int32& articleOrderDate);
    void setArticleGoodsReceiptTargetDate(const basar::Int32& articleGoodsReceiptTargetDate);
    void setIsArticleOrderEffective(const bool isArticleOrderEffective);

private:
    ArticleOrderInfoPtr m_ArticleOrderInfo;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFOMAPPERBASE_H
