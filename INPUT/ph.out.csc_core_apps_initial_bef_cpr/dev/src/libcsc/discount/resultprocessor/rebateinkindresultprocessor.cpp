#include "discount/resultprocessor/rebateinkindresultprocessor.h"
#include "discount/orderpositiondiscount/iorderpositiondiscountrepository.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include <discount/basevalues/orderbasevalue/orderitembasevaluecollection.h>
#include <logger/loggerpool.h>
#include <discount/calculator/discountcalculatortypemapper.h>

#include <libbasarcmnutil_i18nstring.h>

#include <pxorder.hpp>

#include "pxsess.hpp"
#include "pxstockbooking.hpp"
#include "pxartbas.hpp"
#include "pxartmas.hpp"

namespace libcsc
{
namespace discount
{
RebateInKindResultProcessor::RebateInKindEntry::RebateInKindEntry( 
	const DiscountCalculatorTypeEnum _origin,
	const libcsc::Int32 _articleNo,
	pxOrderItem * _orderItem,
	const RebateInKindValue & _rebateInKindValue,
	const DiscountResultBaseValue & _baseValue
		)
: origin( _origin ),
  articleNo( _articleNo ),
  orderItem( _orderItem ),
  rebateInKindValue( _rebateInKindValue ),
  baseValue( _baseValue ) 
{
}

RebateInKindResultProcessor::RebateInKindEntry::RebateInKindEntry( const RebateInKindResultProcessor::RebateInKindEntry & rhs )
: origin( rhs.origin ),
  articleNo( rhs.articleNo ),
  orderItem( rhs.orderItem ),
  rebateInKindValue( rhs.rebateInKindValue ),
  baseValue( rhs.baseValue )
{
}

bool RebateInKindResultProcessor::RebateInKindEntry::operator<( const RebateInKindResultProcessor::RebateInKindEntry & rhs ) const
{
	if( origin == rhs.origin )
	{
		return articleNo < rhs.articleNo;
	}
	return ( origin < rhs.origin );
}



RebateInKindResultProcessor::RebateInKindResultProcessor()
{
}

RebateInKindResultProcessor::~RebateInKindResultProcessor()
{
}

void RebateInKindResultProcessor::inject( IOrderPositionDiscountRepositoryPtr repository )
{
	m_Repository = repository;
}

void RebateInKindResultProcessor::process( 
	const DiscountCalculatorTypeEnum calcType, 
	const IOrderBaseValueGetterPtr baseValueGetter, 
	const DiscountCalculatorResult & calcResult 
		)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "RebateInKindResultProcessor::process()" );

	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "CalculatorType: ";
		DiscountCalculatorTypeMapper::toStream( ss, calcType );
		ss << ", CalculatorResult: ";
		if( calcResult.isUnset() )
		{
			ss << "<UNSET>";
		}
		else
		{
			ss << calcResult;
		}
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );

		ss.str( "" );
		ss << "baseValueGetter->getOrderPtr()->getNumberOfPositions(): " << baseValueGetter->getOrderPtr()->getNumberOfPositions();
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	if( calcResult.isUnset() )
	{
		BLOG_TRACE( LoggerPool::getLoggerDiscountCalc(), "Result is unset, skipping this result" );
		return;
	}

	processRebateInKind( calcType, baseValueGetter, calcResult );
}

void RebateInKindResultProcessor::reset()
{
	m_RebateInKinds.clear();
	m_OrderBaseValueGetter = IOrderBaseValueGetterPtr();
}

void RebateInKindResultProcessor::save()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "RebateInKindResultProcessor::save()" );

	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "m_RebateInKinds.size(): " << m_RebateInKinds.size() << std::endl;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	RebateInKindCollection::const_iterator iter = m_RebateInKinds.begin();
	for( ; iter != m_RebateInKinds.end(); ++iter )
	{
		const RebateInKindEntry rebateInKind( *iter );

		if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
		{
			std::stringstream ss;
			ss << "rebateInKind.rebateInKindValue: " << rebateInKind.rebateInKindValue << std::endl;
			LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
		}

		processRebateInKind( rebateInKind );
	}
}

void RebateInKindResultProcessor::save4ever()
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "RebateInKindResultProcessor::save()");

	if (LoggerPool::getLoggerDiscountCalc().isEnabledFor(log4cplus::TRACE_LOG_LEVEL))
	{
		std::stringstream ss;
		ss << "m_RebateInKinds.size(): " << m_RebateInKinds.size() << std::endl;
		LoggerPool::getLoggerDiscountCalc().forcedLog(log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__);
	}

	RebateInKindCollection::const_iterator iter = m_RebateInKinds.begin();
	for (; iter != m_RebateInKinds.end(); ++iter)
	{
		const RebateInKindEntry rebateInKind(*iter);

		if (LoggerPool::getLoggerDiscountCalc().isEnabledFor(log4cplus::TRACE_LOG_LEVEL))
		{
			std::stringstream ss;
			ss << "rebateInKind.rebateInKindValue: " << rebateInKind.rebateInKindValue << std::endl;
			LoggerPool::getLoggerDiscountCalc().forcedLog(log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__);
		}

		processRebateInKind(rebateInKind, CE_ORDERDISCOUNTCALCUC);
	}
}

void RebateInKindResultProcessor::processRebateInKind( 
	const DiscountCalculatorTypeEnum calcType, 
	const IOrderBaseValueGetterPtr baseValueGetter, 
	const DiscountCalculatorResult & calcResult 
		)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "RebateInKindResultProcessor::processRebateInKind( .., .., .. )" );

	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "calcResult: " << calcResult << std::endl;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	m_OrderBaseValueGetter = baseValueGetter;
	RebateInKindValueCollection::const_iterator iter = calcResult.rebateInKindArticles.begin();
	for( ; iter != calcResult.rebateInKindArticles.end(); ++iter )
	{
		const RebateInKindValue rebateInKind( *iter );
		m_RebateInKinds.insert( RebateInKindEntry( calcType, rebateInKind.articleNo, baseValueGetter->getOrderItemPtr(), rebateInKind, calcResult.baseValue ) );
	}
}

void RebateInKindResultProcessor::processRebateInKind(
	const RebateInKindEntry & rebateInKindEntry, basar::Int32 mode
		)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "RebateInKindResultProcessor::processRebateInKind( const RebateInKindEntry & )" );

	m_OrderBaseValueGetter->setOrderItem( rebateInKindEntry.orderItem );
	const RebateInKindValue & rebateInKind( rebateInKindEntry.rebateInKindValue );
	const DiscountCalculatorTypeEnum calcType = rebateInKindEntry.origin;
//	pxArtBase* discountArtBase = NULL;

	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "rebateInKind: " << rebateInKind << std::endl;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}
	
	// determine position number of RiK article
	basar::Int32 rebInKindPosNo = 0;
	bool isNewItem = ( m_OrderBaseValueGetter->getPositionNo() > m_OrderBaseValueGetter->getOrderPtr()->getNumberOfPositions() );
	if (isPositionDiscountCalculatorType(calcType))
	{
		if (rebateInKind.articleNo == rebateInKindEntry.baseValue.articleNo)
		{
			// rebate in kind with same article no
			rebInKindPosNo = m_OrderBaseValueGetter->getPositionNo();
		}
		else
		{
			if( isNewItem )
			{
				// new pxOrderItem isn't in the list already
				rebInKindPosNo = m_OrderBaseValueGetter->getOrderPtr()->getNumberOfPositions() + 2;
			}
			else
			{
				rebInKindPosNo = findRebateInKindPos( calcType );
				if( rebInKindPosNo == 0 
				 && rebateInKindEntry.orderItem->LinkPosNr() > 0)
				{
					pxOrderItem* linkedItem = (pxOrderItem*)m_OrderBaseValueGetter->getOrderPtr()->ItemList()->At(rebateInKindEntry.orderItem->LinkPosNr() - 1);
					rebInKindPosNo = linkedItem->PosNr();
				}
				
				if( rebInKindPosNo == 0 )
				{
					rebInKindPosNo = m_OrderBaseValueGetter->getOrderPtr()->getNumberOfPositions() + 1;
				}
			}
		}
	}
	  
	basar::Int32 positionNo = 0;
	if( DiscountSource::DST_POSITION == rebateInKind.source.type )
	{
		positionNo = rebateInKind.source.number;
	}
	OrderPositionDiscountPtr orderPositionDiscount;
	if( 0 == positionNo )
	{
		orderPositionDiscount = m_Repository->getOrderPositionDiscount( positionNo, getDiscountMode( calcType, true ), rebInKindPosNo, m_OrderBaseValueGetter->getOrderNo());
	}
	else
	{
		orderPositionDiscount = m_Repository->getOrderPositionDiscount( positionNo, getDiscountMode( calcType, true ) );
	}
	
	// Prevent writing orderpositiondiscount entry on book restdelivery item(Auflösung Nachlieferposition(just for better understanding) )
	if ( m_OrderBaseValueGetter->getOrderItemPtr()->IsBookRestDelivery() )
	{
		orderPositionDiscount->setRebateInKindPositionNo(-1);		// prevent writing orderpositiondiscount entry("Krüke"
		return;														// and leave 
	}

	// Prevent writing orderpositiondiscount entry for non valid products(just for better understanding) )
	if (m_OrderBaseValueGetter->getOrderItemPtr()->IsArtStateNotFound())
	{
		orderPositionDiscount->setRebateInKindPositionNo(-1);		// prevent writing orderpositiondiscount entry("Krüke"
		return;														// and leave 
	}

	// TODO: for debugging only - remove
	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "OrderPositionDiscount before: " << ( *orderPositionDiscount ) << std::endl;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	basar::Int32 compResult = compareDiscountValues( *orderPositionDiscount, rebateInKindEntry.rebateInKindValue );
	if( 0 == compResult )
	{
		if( orderPositionDiscount->getPositionNo().isClean() )
		{
			orderPositionDiscount->setDiscountQty( rebateInKind.quantity );
			m_OrderBaseValueGetter->getOrderItemPtr()->SetDiscountArticleNo( rebateInKind.articleNo );
			m_OrderBaseValueGetter->getOrderItemPtr()->SetMengeNatraDiscountArticle( rebateInKind.quantity );
			return;
		}
	}
	else if( 0 < compResult )
	{
		// new rebate has a smaller cash value, so skip it
		BLOG_TRACE( LoggerPool::getLoggerDiscountCalc(), "Skipping Rebate in Kind" );
		if( orderPositionDiscount->getPositionNo().isDirty() )
		{
			m_Repository->erase( orderPositionDiscount );
		}
		return;
	}

	// TODO: for debugging only - remove
	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "orderPositionDiscount->getRebateInKindPositionNo: " << orderPositionDiscount->getRebateInKindPositionNo() << std::endl;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	// we got a better RiK
	if(		   orderPositionDiscount->getRebateInKindPositionNo().isClean() 
		&& 0 < orderPositionDiscount->getRebateInKindPositionNo() )
	{
		if( orderPositionDiscount->getPositionNo() == orderPositionDiscount->getRebateInKindPositionNo() )
		{
			// clear RiK quantity
			m_OrderBaseValueGetter->getOrderItemPtr()->RollBackOrderPosition();
            m_OrderBaseValueGetter->getOrderItemPtr()->OrderQuantity( m_OrderBaseValueGetter->getOrderItemPtr()->MengeBestellt(), 0, m_OrderBaseValueGetter->getOrderItemPtr()->MengeBestellt() );
		}
		else
		{
			// cancel the old rubber duck item
			m_OrderBaseValueGetter->getOrderPtr()->ItemList()->GetItem( orderPositionDiscount->getRebateInKindPositionNo() )->CancelItem( pxOrderItem::CancelOptionDefault );
			m_Repository->erase( orderPositionDiscount );
			orderPositionDiscount = m_Repository->getOrderPositionDiscount( positionNo, getDiscountMode( calcType, true ), orderPositionDiscount->getRebateInKindPositionNo(), m_OrderBaseValueGetter->getOrderNo());
		}
	}

	orderPositionDiscount->setRebateInKindPositionNo(rebInKindPosNo);
	orderPositionDiscount->setRebateInKindOrderNo(m_OrderBaseValueGetter->getOrderNo());

	// create item
	orderPositionDiscount->setOrderNo( m_OrderBaseValueGetter->getOrderNo() );
	if( isPositionDiscountCalculatorType( calcType ) && mode == CE_POSITIONDISCOUNTCALCUC)     //test mode = 0 ( called during position calculation)
	{
		if( rebateInKind.articleNo == rebateInKindEntry.baseValue.articleNo )
		{
			// rebate in kind with same article no
			if( rebateInKind.isManufacturerRebate )
			{
				//basar::Int32 oldQuantity = m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraHerst();
				//m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraHerst( oldQuantity + rebateInKind.quantity );
				m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraHerst(rebateInKind.quantity);
			}
			else
			{
				//basar::Int32 oldQuantity = m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraGrossH();
				//m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraGrossH( oldQuantity + rebateInKind.quantity );
				m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraGrossH(rebateInKind.quantity);
			}
		}
		else
		{
			// rubber duck ;)
			m_OrderBaseValueGetter->getOrderItemPtr()->SetDiscountArticleNo( rebateInKind.articleNo );
			m_OrderBaseValueGetter->getOrderItemPtr()->SetMengeNatraDiscountArticle( rebateInKind.quantity );
		}

		if( libcsc::LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
		{
			std::stringstream ss;
			ss << "item->PosNr()=<" << m_OrderBaseValueGetter->getOrderItemPtr()->PosNr();
			ss << ">, item->ArtikelNr()=<" << m_OrderBaseValueGetter->getOrderItemPtr()->ArtikelNr();
			ss << ">, item->DiscountArticleNo()=<" << m_OrderBaseValueGetter->getOrderItemPtr()->DiscountArticleNo();
			ss << ">, item->MengeNatraDiscountArticle()=<" << m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraDiscountArticle();
			ss << ">, item->MengeNatraGrossH()=<" << m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraGrossH();
			ss << ">, item->MengeNatraHerst()=<" << m_OrderBaseValueGetter->getOrderItemPtr()->MengeNatraHerst() << ">";
			libcsc::LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
		}
	}
	else
	{
	/*	// check availibilty on rebate article. 
		long AvailableQtyDiscountArticle = 0;
		discountArtBase = pxArtBase::CreateArticle(m_OrderBaseValueGetter->getOrderItemPtr()->Session(), m_OrderBaseValueGetter->getOrderItemPtr()->DiscountArticleNo(), m_OrderBaseValueGetter->getOrderPtr()->FilialNr());
		if (discountArtBase->IsGoodState())
		{
			AvailableQtyDiscountArticle = (m_OrderBaseValueGetter->getOrderItemPtr()->Session())->getStockBooking()->GetAvailableQtyInStock(*discountArtBase);
		}
		delete discountArtBase;
     */
		pxOrderItem * pxItem = m_OrderBaseValueGetter->getOrderPtr()->ItemList()->getItemInhibitManualUpdateByArticleNo( rebateInKind.articleNo ); // does not fit
		if( NULL == pxItem )
		{
		/*	if ( AvailableQtyDiscountArticle < rebateInKind.quantity )
			{
				orderPositionDiscount->setRebateInKindPositionNo(-1);		// prevent writing orderpositiondiscount entry("Krüke"
				return;
			}
			*/
			// article isn't in the list, create a new one
			// TODO: DK use DiscountBaseValue::getDiscountSpec() as priceType
			m_OrderBaseValueGetter->getOrderPtr()->RangeDiscountArticle( rebateInKind.articleNo, rebateInKind.quantity, 0, false, DiscCategory_Common, ""); // TODO FN
			pxItem = m_OrderBaseValueGetter->getOrderPtr()->ItemList()->getItemInhibitManualUpdateByArticleNo(rebateInKind.articleNo);
			if (NULL == pxItem)
			{
				orderPositionDiscount->setRebateInKindPositionNo(-1);		// prevent writing orderpositiondiscount entry("Krüke"
				return;
			}
			orderPositionDiscount->setRebateInKindPositionNo( m_OrderBaseValueGetter->getOrderPtr()->getNumberOfPositions() );
		}
		else
		{
			// article is in list already, add quantities
			// Ok this is now a test, because we must prevent generating duplicate key on table orderpositiondiscount(Pharmos DKPRA)
			// we book the same discountarticle 
		/*	if (AvailableQtyDiscountArticle < rebateInKind.quantity)
			{
				orderPositionDiscount->setRebateInKindPositionNo(-1);		// prevent writing orderpositiondiscount entry("Krüke"
				return;
			}
		*/
			m_OrderBaseValueGetter->getOrderPtr()->RangeDiscountArticle(rebateInKind.articleNo, rebateInKind.quantity, 0, false, DiscCategory_Common, ""); // TODO FN
			pxOrderItem * pxItemSecond = m_OrderBaseValueGetter->getOrderPtr()->ItemList()->getItemInhibitManualUpdateByArticleNo(rebateInKind.articleNo);
			if (NULL == pxItemSecond)
			{
				orderPositionDiscount->setRebateInKindPositionNo(-1);		// prevent writing orderpositiondiscount entry("Krüke"
				return;
			}
			orderPositionDiscount->setRebateInKindPositionNo(m_OrderBaseValueGetter->getOrderPtr()->getNumberOfPositions());

			//pxItem->OrderQuantityRange_RangeArticle( pxItem->MengeBestellt(), pxItem->MengeNatra() + rebateInKind.quantity, pxItem->MengeBestellt() );
			//orderPositionDiscount->setRebateInKindPositionNo( pxItem->PosNr() );
		}
	}

	orderPositionDiscount->setDiscountValue( libcsc::Decimal::zero() );
	orderPositionDiscount->setDiscountPercent( libcsc::Decimal::zero() );
	orderPositionDiscount->setPharmacyGroupId( basar::VarString());
	orderPositionDiscount->setDiscountQty( rebateInKind.quantity );
		
	
	// TODO: for debugging only - remove
	if( LoggerPool::getLoggerDiscountCalc().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "OrderPositionDiscount after: " << ( *orderPositionDiscount ) << std::endl;
		LoggerPool::getLoggerDiscountCalc().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}
}

basar::Int32 RebateInKindResultProcessor::findRebateInKindPos(DiscountCalculatorTypeEnum calcType) const
{
	basar::Int32 rebInKindPosNo = 0;
	pxSession* session = m_OrderBaseValueGetter->getOrderPtr()->Session();
	libcsc::discount::IOrderPositionDiscountRepositoryPtr opdRepository = session->getOrderPositionDiscountRepository();
	libcsc::discount::OrderPositionDiscountListPtr discountListPointer = opdRepository->findByID(m_OrderBaseValueGetter->getOrderNo());
	libcsc::discount::OrderPositionDiscountList::const_iterator iter1 = discountListPointer->begin();
	for (; iter1 != discountListPointer->end(); ++iter1)
	{
		if (m_OrderBaseValueGetter->getPositionNo() != (*iter1)->getPositionNo() 
		 || getDiscountMode(calcType, true) != (*iter1)->getDiscountMode().get())
		{
			continue;
		}

		if ((*iter1)->isRebateInKind())
		{
			rebInKindPosNo = (*iter1)->getRebateInKindPositionNo();
			break;
		}
	}
	return rebInKindPosNo;
}

basar::Int32 RebateInKindResultProcessor::compareDiscountValues( 
	const OrderPositionDiscount & orderPositionDiscount,
	const RebateInKindValue & rebateInKindValue
		) const
{
	if( orderPositionDiscount.getRebateInKindPositionNo().isUnset() )
	{
		return -1;
	}
	if( rebateInKindValue.articlePrice.isUnset() )
	{
		return 1;
	}

	basar::Decimal lhs( m_OrderBaseValueGetter->getOrderItemBaseValueCollection()->getRiKValue( orderPositionDiscount.getRebateInKindPositionNo() ) );
	basar::Decimal rhs( basar::Decimal( rebateInKindValue.articlePrice ) * rebateInKindValue.quantity );

	lhs.round( 2 );
	rhs.round( 2 );

	if( lhs < rhs )
	{
		return -1;
	}
	else if( lhs > rhs )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

} // end namespace discount
} // end namespace libcsc
