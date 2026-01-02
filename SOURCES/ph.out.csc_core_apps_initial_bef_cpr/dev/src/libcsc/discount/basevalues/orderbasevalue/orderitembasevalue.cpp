#include "orderitembasevalue.h"
#include "orderitembasevaluecollection.h"
#include <logger/loggerpool.h>
#include <discount/orderpositiondiscountprocessed/orderpositiondiscountprocessedrepository.h>
#include <libbasarcmnutil_i18nstring.h>

#include <pxorder.hpp>
#include <pxitem.hpp>
#include <pxartprc.hpp>
#include <pxartbas.hpp>
#include <pxcstot.hpp>
#include <pxcstbas.hpp>
#include <pxcustomerflags.hpp>

namespace libcsc
{
namespace discount
{
OrderItemBaseValue::OrderItemBaseValue( pxOrderItem* orderItem )
: m_OrderItem( orderItem ),
  m_Order( orderItem->getOrder() )
{
}

OrderItemBaseValue::OrderItemBaseValue( pxOrder* order )
: m_OrderItem( NULL ),
  m_Order( order )
{
}

OrderItemBaseValue::~OrderItemBaseValue()
{
}

void OrderItemBaseValue::injectArticleClassificationRepository( ArticleClassificationRepositoryPtr articleClassificationRepository )
{
    m_ArticleClassificationRepository = articleClassificationRepository;
}

void OrderItemBaseValue::injectOrderPositionDiscountProcessedRepository( OrderPositionDiscountProcessedRepositoryPtr orderPositionDiscountProcessedRepository )
{
    m_OrderPositionDiscountProcessedRepository = orderPositionDiscountProcessedRepository;
}

void OrderItemBaseValue::setOrderItem( pxOrderItem* orderItem )
{
    m_OrderItem = orderItem;
}

basar::Int16 OrderItemBaseValue::getBranchNo() const
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderItemBaseValue(), "OrderItemBaseValue::getBranchNo()" );

    return m_Order->FilialNr();
}

basar::Int32 OrderItemBaseValue::getCustomerNo() const
{
    return m_Order->KundenNr();
}

basar::Int32 OrderItemBaseValue::getOrderNo() const
{
    return m_Order->KdAuftragNr();
}

basar::VarString OrderItemBaseValue::getOrderType() const
{
    return m_Order->KdAuftragArt()();
}


basar::Int32 OrderItemBaseValue::getPositionNo() const
{
    return m_OrderItem->PosNr();
}

basar::Int32 OrderItemBaseValue::getArticleNo() const
{
    return m_OrderItem->ArtikelNr();
}

basar::Int32 OrderItemBaseValue::getItemQty() const
{
    if (m_OrderItem->MengeBestelltOrg() > 0)
    {
        return m_OrderItem->MengeBestelltOrg();
    }
    return m_OrderItem->MengeBestellt();
}

const basar::Decimal OrderItemBaseValue::getItemPrice() const
{
	// I-23023318 when using basar::Decimal( m_OrderItem->PreisEKApo() ) ex: 2.05 it is converted to 2,0499999999999998 so changed to below
	
	basar::Decimal price(m_OrderItem->PreisEKApo());
    price.round(2);
	return price;
    //return basar::Decimal( m_OrderItem->PreisEKApo() );
}

const basar::Decimal OrderItemBaseValue::getItemValue() const
{
    return getItemPrice() * getItemQty();
}

const basar::Decimal OrderItemBaseValue::getExFactoryPrice() const
{
    return basar::Decimal( m_OrderItem->ArtPriceList()->GetPreisEKGrosso() );
}

const basar::Decimal OrderItemBaseValue::getRiKValue() const
{
    return getItemPrice() * m_OrderItem->MengeNatra();
}

bool OrderItemBaseValue::isTaxSpannenCheckNecessary() const
{
    return (
        true == m_OrderItem->ArtBase()->ArtClass().IsRezeptPflichtig() &&
        true == m_OrderItem->ArtBase()->IsTaxPflichtigRX()
        );
}

bool OrderItemBaseValue::isRezeptPflichtig() const
{
    return m_OrderItem->ArtBase()->ArtClass().IsRezeptPflichtig();
}

bool OrderItemBaseValue::isApothekenPflichtig() const
{
    return m_OrderItem->ArtBase()->ArtClass().IsApothekenPflichtig();
}

bool OrderItemBaseValue::isCalcNetPrice() const
{
    return m_Order->OrderType().IsCalcNetPrice();
}

char OrderItemBaseValue::getCustomerRXAFlag() const
{
    return m_Order->Customer()->Flags().RXAFlag();
}


const IArticleClassificationGetterPtr OrderItemBaseValue::getArticleClassification() const
{
    if( NULL == m_ArticleClassificationGetter.get() )
    {
        getOrderItemBaseValueCollection();
        m_ArticleClassificationRepository->setOrderItemBaseValues( m_OrderItemBaseValueCollection );
        m_ArticleClassificationGetter = m_ArticleClassificationRepository;
    }

    return m_ArticleClassificationGetter;
}

const OrderItemBaseValueCollectionPtr OrderItemBaseValue::getOrderItemBaseValueCollection() const
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerOrderItemBaseValue(), "OrderItemBaseValue::getOrderItemBaseValueCollection()" );

    if( NULL == m_OrderItemBaseValueCollection.get() )
    {
        m_OrderItemBaseValueCollection = OrderItemBaseValueCollectionPtr( new OrderItemBaseValueCollection() );
        IOrderPositionDiscountProcessedCollectionPtr processedPositions = m_OrderPositionDiscountProcessedRepository->findByID( m_Order->KdAuftragNr() );

        pxOrderItemListIter iter( *m_Order->ItemList() );
        ++iter;
        pxOrderItem* item = dynamic_cast<pxOrderItem *>( iter.Current() );
        while( item != NULL )
        {
            if( !processedPositions->contains( item->PosNr() ) )
            {
                OrderItemBaseValuePtr orderItemBaseValue( new OrderItemBaseValue( item ) );
                m_OrderItemBaseValueCollection->insert( orderItemBaseValue->getArticleNo(), orderItemBaseValue );
            }

            ++iter;
            item = dynamic_cast<pxOrderItem *>( iter.Current() );
        }

        if( LoggerPool::getLoggerOrderItemBaseValue().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
        {
            std::stringstream ss;
            ss << "OrderItemBaseValue::getOrderItemBaseValueCollection(): " << std::endl;
            OrderItemBaseValueCollection::const_iterator it = m_OrderItemBaseValueCollection->begin();
            for( ; it != m_OrderItemBaseValueCollection->end(); ++it )
            {
                ss << *it->second << std::endl;
            }

            LoggerPool::getLoggerOrderItemBaseValue().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
        }
    }

    return m_OrderItemBaseValueCollection;
}

pxOrder* OrderItemBaseValue::getOrderPtr() const
{
    return m_Order;
}

pxOrderItem* OrderItemBaseValue::getOrderItemPtr() const
{
    return m_OrderItem;
}

std::ostream& OrderItemBaseValue::toStream( std::ostream& strm /*= std::cout*/ ) const
{
    strm << "branchNo=<" << getBranchNo() << ">";
    strm << ", customerNo=<" << getCustomerNo() << ">";
    strm << ", orderNo=<" << getOrderNo() << ">";
    strm << ", positionNo=<" << getPositionNo() << ">";
    strm << ", articleNo=<" << getArticleNo() << ">";
    strm << ", itemQty=<" << getItemQty() << ">";
    strm << ", itemPrice=<" << getItemPrice().toString().c_str() << ">";
    strm << ", itemValue=<" << getItemValue().toString().c_str() << ">";
    return strm;
}

} // end namespace discount
} // end namespace libcsc
