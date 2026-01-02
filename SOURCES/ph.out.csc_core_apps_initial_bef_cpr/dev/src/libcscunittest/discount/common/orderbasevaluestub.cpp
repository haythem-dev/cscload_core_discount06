#include "cmnut.h"
#include "orderbasevaluestub.h"

namespace libcscUnitTest
{
namespace discount
{
OrderBaseValueStub::OrderBaseValueStub( 
	const basar::Int16 branchno,
	const basar::Int32 customerno,
	const basar::Int32 orderno,
	const basar::VarString& orderType,
	const basar::Int32 positionno,
	const basar::Int32 articleno,
	const basar::Int32 itemqty,
	const basar::Decimal & itemprice,
	const basar::Decimal & itemvalue,
	const basar::Decimal & rikvalue,
	const basar::VarString & itemlist
		)
: m_BranchNo( branchno ),
  m_CustomerNo( customerno ),
  m_OrderNo( orderno ),
  m_OrderType ( orderType ),
  m_PositionNo( positionno ),
  m_ArticleNo( articleno ),
  m_ItemQty( itemqty ),
  m_ItemPrice( itemprice ),
  m_ItemValue( itemvalue ),
  m_RiKValue( rikvalue ),
  m_ItemList( itemlist )
{
}

OrderBaseValueStub::~OrderBaseValueStub()
{
}

void OrderBaseValueStub::setOrderItem( pxOrderItem * )
{
}

basar::Int16 OrderBaseValueStub::getBranchNo() const
{
	return m_BranchNo;
}

basar::Int32 OrderBaseValueStub::getCustomerNo() const
{
	return m_CustomerNo;
}

basar::Int32 OrderBaseValueStub::getOrderNo() const
{
	return m_OrderNo;
}

basar::VarString OrderBaseValueStub::getOrderType() const
{
	return m_OrderType;
}

basar::Int32 OrderBaseValueStub::getPositionNo() const
{
	return m_PositionNo;
}

basar::Int32 OrderBaseValueStub::getArticleNo() const
{
	return m_ArticleNo;
}

basar::Int32 OrderBaseValueStub::getItemQty() const
{
	return m_ItemQty;
}

const basar::Decimal OrderBaseValueStub::getItemPrice() const
{
	return m_ItemPrice;
}

const basar::Decimal OrderBaseValueStub::getItemValue() const
{
	return m_ItemValue;
}

const basar::Decimal OrderBaseValueStub::getExFactoryPrice() const
{
	return basar::Decimal(0);
}

const basar::Decimal OrderBaseValueStub::getRiKValue() const
{
	return m_RiKValue;
}

bool OrderBaseValueStub::isTaxSpannenCheckNecessary() const
{
	return false;
}

bool OrderBaseValueStub::isRezeptPflichtig() const
{
	return false;
}

bool OrderBaseValueStub::isApothekenPflichtig() const
{
	return false;
}

bool OrderBaseValueStub::isCalcNetPrice() const
{
	return true;
}

char OrderBaseValueStub::getCustomerRXAFlag() const
{
	return ' ';
}

const libcsc::discount::IArticleClassificationGetterPtr OrderBaseValueStub::getArticleClassification() const
{
	return libcsc::discount::IArticleClassificationGetterPtr();
}

const libcsc::discount::OrderItemBaseValueCollectionPtr OrderBaseValueStub::getOrderItemBaseValueCollection() const
{
	return libcsc::discount::OrderItemBaseValueCollectionPtr();
}

pxOrder * OrderBaseValueStub::getOrderPtr() const
{
	return NULL;
}

pxOrderItem * OrderBaseValueStub::getOrderItemPtr() const
{
	return NULL;
}

std::ostream & OrderBaseValueStub::toStream( std::ostream & strm /* = std::cout */  ) const
{
	return strm;
}

} // end namespace discount
} // end namespace libcscUnitTest

