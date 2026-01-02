#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"
#include "pxdiscount.hpp"
#include "pxitemdiscount.hpp"
#include "persistence/iaccessorptr.h"
#include "persistence/accessor.h"
#include "persistence/connection.h"

#include "discount/basevalues/discountbasevalue/discountbasevaluerepositoryptr.h"
#include "discount/basevalues/discountbasevalue/discountbasevaluerepository.h"
#include "discount/basevalues/discountbasevalue/discountbasevaluecollectionptr.h"
#include "discount/basevalues/discountbasevalue/discountbasevaluecollection.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"

class DiscountFixture
{
public:
    short branchno;
    long articleno;
    long customerno;
    pxItemDiscount* itemDiscount;
    SessionUtil* session;

    DiscountFixture()
        : branchno(5), articleno(106), customerno(9674467), itemDiscount(NULL), session(NULL)
    {
        // Setup: Initialize shared resources
        session = new SessionUtil(branchno);
        itemDiscount = new pxItemDiscount(session->get(), 9999999, 1, 0, "");
    }

    ~DiscountFixture()
    {
        // Teardown: Clean up resources
        delete itemDiscount;
        delete session;
    }
};

SUITE(DiscountTests)
{
    TEST_FIXTURE(DiscountFixture, TestCreateItemDiscount)
    {
        // Test creating a new item discount
        itemDiscount->SetDiscountValuePct(5.0);
        CHECK_EQUAL(0, itemDiscount->Put());
    }

    TEST_FIXTURE(DiscountFixture, TestReadItemDiscount)
    {
        // Test reading an existing item discount
        CHECK_EQUAL(0, itemDiscount->Get());
        CHECK_EQUAL(5.0, itemDiscount->DiscountValuePct());
    }

    TEST_FIXTURE(DiscountFixture, TestUpdateItemDiscount)
    {
        // Test updating an existing item discount
        session->get()->nDBBeginTransaction();
        itemDiscount->Get(cDBGET_FORUPDATE);
        itemDiscount->SetDiscountValuePct(10.0);
        CHECK_EQUAL(0, itemDiscount->Put());
        session->get()->nDBCommit();

        // Verify the update
        itemDiscount->Get();
        CHECK_EQUAL(10.0, itemDiscount->DiscountValuePct());
    }

    TEST_FIXTURE(DiscountFixture, TestReadDiscountList)
    {
        // Test reading a list of discounts using pxDiscountList
        nString pharmacygroup("250");
        pxDiscountList discountList(session->get());
        CHECK_EQUAL(1UL, discountList.Select(branchno, 0L, 16, pharmacygroup));
        CHECK(discountList.Entries() > 0UL);
    }

    TEST_FIXTURE(DiscountFixture, TestDeleteItemDiscount)
    {
        // Test deleting an existing item discount
        CHECK_EQUAL(0, itemDiscount->Delete());

        // Verify the deletion
        CHECK(itemDiscount->Get() != 0);
    }



    class OrderBaseValueStub : public libcsc::discount::IOrderBaseValueGetter
    {
    public:
        OrderBaseValueStub(
            const basar::Int16 branchno,
            const basar::Int32 customerno,
            const basar::Int32 orderno,
            const basar::VarString& orderType,
            const basar::Int32 positionno,
            const basar::Int32 articleno,
            const basar::Int32 itemqty,
            const basar::Decimal& itemprice,
            const basar::Decimal& itemvalue,
            const basar::Decimal& rikvalue,
            const basar::VarString& itemlist
        )
            : m_BranchNo(branchno),
              m_CustomerNo(customerno),
              m_OrderNo(orderno),
              m_OrderType(orderType),
              m_PositionNo(positionno),
              m_ArticleNo(articleno),
              m_ItemQty(itemqty),
              m_ItemPrice(itemprice),
              m_ItemValue(itemvalue),
              m_RiKValue(rikvalue),
              m_ItemList(itemlist)
        {
        }
        virtual ~OrderBaseValueStub() {}

        virtual void setOrderItem(pxOrderItem* /*orderItem*/) {}

        virtual basar::Int16 getBranchNo() const { return m_BranchNo; }
        virtual basar::Int32 getCustomerNo() const { return m_CustomerNo; }
        virtual basar::Int32 getOrderNo() const { return m_OrderNo; }
        virtual basar::Int32 getPositionNo() const { return m_PositionNo; }
        virtual basar::Int32 getArticleNo() const { return m_ArticleNo; }
        virtual basar::Int32 getItemQty() const { return m_ItemQty; } // baseqty
        virtual const basar::Decimal getItemPrice() const { return m_ItemPrice; } // baseprice
        virtual const basar::Decimal getItemValue() const { return m_ItemValue; } // baseprice * basqty 
        virtual const basar::Decimal getRiKValue() const { return m_RiKValue; } // baseprice * menge_natra  
        virtual const libcsc::discount::IArticleClassificationGetterPtr getArticleClassification() const { return libcsc::discount::IArticleClassificationGetterPtr(); }
        virtual const libcsc::discount::OrderItemBaseValueCollectionPtr getOrderItemBaseValueCollection() const { return libcsc::discount::OrderItemBaseValueCollectionPtr(); }
        virtual pxOrder* getOrderPtr() const { return NULL; }
        virtual pxOrderItem* getOrderItemPtr() const { return NULL; }
        virtual std::ostream& toStream(std::ostream& strm = std::cout) const { return strm; }
        //DEPricing
        virtual basar::VarString getOrderType() const { return m_OrderType; }
        virtual const basar::Decimal getExFactoryPrice() const { return basar::Decimal(0); } // GEP 
        virtual bool isTaxSpannenCheckNecessary() const { return false; }
        virtual bool isRezeptPflichtig() const { return false; }
        virtual bool isApothekenPflichtig() const { return false; }
        virtual bool isCalcNetPrice() const { return true; }
        virtual char getCustomerRXAFlag() const { return ' '; }
        //DEPricing

    private:
        OrderBaseValueStub(const OrderBaseValueStub&);
        OrderBaseValueStub& operator=(const OrderBaseValueStub&);

        basar::Int16	m_BranchNo;
        basar::Int32	m_CustomerNo;
        basar::Int32	m_OrderNo;
        basar::VarString m_OrderType;
        basar::Int32	m_PositionNo;
        basar::Int32	m_ArticleNo;
        basar::Int32	m_ItemQty;
        basar::Decimal	m_ItemPrice;
        basar::Decimal	m_ItemValue;
        basar::Decimal	m_RiKValue;
        basar::VarString m_ItemList;
    };



    TEST_FIXTURE(DiscountFixture, TestFindByArticle)
    {
        // Test finding a discount base value by article
        libcsc::discount::DiscountBaseValueRepositoryPtr repository(new libcsc::discount::DiscountBaseValueRepository());
        repository->injectSingleSelectAccessor(libcsc::persistence::IAccessorPtr(new libcsc::persistence::Accessor(session->get()->GetConnection()->getDbSqlConnection())));
        repository->injectMultiSelectAccessor(libcsc::persistence::IAccessorPtr(new libcsc::persistence::Accessor(session->get()->GetConnection()->getDbSqlConnection())));
        repository->setIsGermany();
		libcsc::discount::IOrderBaseValueGetterPtr s(
            new OrderBaseValueStub(branchno, customerno, 9999999, basar::VarString("NO"), 1, articleno, 1, basar::Decimal(10.0), basar::Decimal(10.0), basar::Decimal(0.0),
                basar::VarString())
        );
        libcsc::discount::DiscountBaseValueCollectionPtr discounts = repository->findByArticle(s);
		CHECK(discounts->getCollection().size() >= 1UL);
    }
}
