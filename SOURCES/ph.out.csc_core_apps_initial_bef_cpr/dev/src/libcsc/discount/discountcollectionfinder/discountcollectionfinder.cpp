//-------------------------------------------------------------------------------------------------//
/*! \file
*   \brief
*   \author b.bischof@phoenixgroup.eu
*   \date   03.11.2021
*/
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "discountcollectionfinder.h"

#include <discount/basevalues/discountbasevalue/idiscountbasevaluerepository.h>
#include <discount/basevalues/orderbasevalue/orderitembasevalue.h>
#include <discount/basevalues/discountbasevalue/discountbasevaluecollection.h>

#include <pxorder.hpp>

#include <logger/loggerpool.h>
#include <util/loggingutils.h>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <discount/basevalues/discountbasevalue/discountbasevalue.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc
{
    namespace discount
    {
        //--------------------------------------------------------------------------------------------------//
        // object definition section
        //--------------------------------------------------------------------------------------------------//
        DiscountCollectionFinder::DiscountCollectionFinder()
        {
            BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCollectionFinder::DiscountCollectionFinder()") ;
        }

        DiscountCollectionFinder::~DiscountCollectionFinder()
        {
            BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), "DiscountCollectionFinder::~DiscountCollectionFinder()");
        }

        void DiscountCollectionFinder::injectDiscountBaseValueRepository( IDiscountBaseValueRepositoryPtr discountBaseValueRepository )
        {
            BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountCollectionFinder::injectDiscountBaseValueRepository()");

            m_DiscountBaseValueRepository = discountBaseValueRepository;
        }

        void DiscountCollectionFinder::injectFilters(const DiscountFilterList& filters)
        {
            BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountCollectionFinder::injectFilters()");

            m_Filters = filters;
        }

        const DiscountBaseValueList& DiscountCollectionFinder::find( pxOrder* order, long articleNo, int qty, double* pharmacyPurchasePrice )
        {
            METHODNAME_DEF( DiscountCollectionFinder, find(...) )       
            BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountCalc(), fun );

            clear();

            if( NULL == order )
            {
                throw exceptions::InvalidParameterException ( basar::ExceptInfo(fun, "pxOrder is NULL!", __FILE__, __LINE__ ) );
            }   

            if (false == order->IsDiscountable())
            {
                return m_DiscountWorkingList;
            }
           
            DiscountBaseValueCollectionPtr discountBaseValueCollection;

            boost::scoped_ptr< pxOrderItem > orderItem(order->ItemDiscountInfo(articleNo)); // orderItem has to be deleted (within this method) after use 
            if( NULL == orderItem.get() )
            {
                return m_DiscountWorkingList;
            }

            orderItem->MengeBestellt(qty);
            orderItem->GetBasePrices(orderItem->PreisTyp());
            if (0 != pharmacyPurchasePrice)
            {
                *pharmacyPurchasePrice = static_cast<double>(orderItem->PreisEKApo());
            }

            IOrderBaseValueGetterPtr orderItemBaseValue = boost::make_shared<OrderItemBaseValue>( orderItem.get() );
            //m_DiscountBaseValueRepository->get()->clear();
            discountBaseValueCollection = m_DiscountBaseValueRepository->findByArticle(orderItemBaseValue);

            m_DiscountWorkingList = discountBaseValueCollection->getCollection();

            const log4cplus::Logger logger = LoggerPool::getLoggerDiscountCalc();

            BLOG_INFO( logger, "START DISCOUNT_FILTERING: " );

            int i = (int)m_DiscountWorkingList.size(); ++i; --i;
            for (size_t index = 0; index < m_Filters.size(); ++index)
            {
                m_Filters[index]->execute(m_DiscountWorkingList, orderItemBaseValue);

            }

            BLOG_INFO(logger, "ENDE DISCOUNT_FILTERING: ");

            return m_DiscountWorkingList;
        }

        void DiscountCollectionFinder::clear()
        {
            m_DiscountWorkingList.clear();
            m_DiscountBaseValueRepository->get()->clear();
        }

        const DiscountBaseValueList& DiscountCollectionFinder::get() const
        {
            BLOG_TRACE_METHOD(LoggerPool::getLoggerDiscountCalc(), "DiscountCollectionFinder::get()");
            
            return m_DiscountWorkingList;
        }

    } // namespace discount
} // namespace libcsc
