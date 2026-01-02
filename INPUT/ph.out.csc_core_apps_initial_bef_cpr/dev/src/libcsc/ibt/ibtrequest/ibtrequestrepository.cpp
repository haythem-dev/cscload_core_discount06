#include "ibtrequestrepository.h"
#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>
#include <parameter/ibranchparametergetter.h>
#include <libbasarcmnutil_exceptions.h>
#include <logger/loggerpool.h>

#include "ibtrequestsqlmapper.h"
#include "ibtrequest.h"
#include "iibtrequestfactoryptr.h"
#include "discount/ibtrequestdiscountsqlmapper.h"
#include "remark/ibtrequestremarksqlmapper.h"

namespace libcsc
{
namespace ibt
{
IbtRequestRepository::IbtRequestRepository()
{
}

IbtRequestRepository::~IbtRequestRepository()
{
    m_Accessor.reset();
}

void IbtRequestRepository::injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory )
{
    m_TransactionFactory = transactionFactory;
}

void IbtRequestRepository::injectAccessor( persistence::IAccessorPtr accessor )
{
    m_Accessor = accessor;
}

void IbtRequestRepository::reset()
{
    m_IbtRequests.clear();
}

IIbtRequestPtr IbtRequestRepository::findIbtRequestByKey( const IbtRequestKey & key )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::findIbtRequestByKey()" );

    IbtRequestPtr ibtRequest( createRequest() );

    try
    {
        basar::db::sql::ResultsetRef resultset = m_Accessor->select( IbtRequestSqlMapper::getSelectSQL( key ) );
        if( resultset.next() )
        {
            IbtRequestSqlMapper mapper( ibtRequest, resultset );
            mapper.map();
            m_IbtRequests.push_back( ibtRequest );

            resultset = m_Accessor->select( IbtRequestDiscountSqlMapper::getSelectSQL( ibtRequest->getIbtRequestId() ) );
            while( resultset.next() )
            {
                IbtRequestDiscountPtr ibtRequestDiscount( createRequestDiscount() );
                IbtRequestDiscountSqlMapper dMapper( ibtRequestDiscount, resultset );
                dMapper.map();
                ibtRequest->m_Discounts.push_back( ibtRequestDiscount );
            }

            resultset = m_Accessor->select( IbtRequestRemarkSqlMapper::getSelectSQL( ibtRequest->getIbtRequestId() ) );
            while( resultset.next() )
            {
                IbtRequestRemarkPtr ibtRequestRemark( createRequestRemark() );
                IbtRequestRemarkSqlMapper rMapper( ibtRequestRemark, resultset );
                rMapper.map();
                ibtRequest->m_Remarks.push_back( ibtRequestRemark );
            }
        }
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
        throw;
    }

    std::stringstream ss;
    ss << "IbtRequestRepository::findIbtRequestByKey(): ibtRequest == \n" << *ibtRequest;
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ibtRequest;
}

IIbtRequestPtr IbtRequestRepository::findIbtRequestById( const basar::Int32 id )
{
    IbtRequestPtr ibtRequest( createRequest() );

    try
    {
        basar::db::sql::ResultsetRef resultset = m_Accessor->select( IbtRequestSqlMapper::getSelectSQL( id ) );
        if( resultset.next() )
        {
            IbtRequestSqlMapper mapper( ibtRequest, resultset );
            mapper.map();
            m_IbtRequests.push_back( ibtRequest );

            resultset = m_Accessor->select( IbtRequestDiscountSqlMapper::getSelectSQL( ibtRequest->getIbtRequestId() ) );
            while( resultset.next() )
            {
                IbtRequestDiscountPtr ibtRequestDiscount( createRequestDiscount() );
                IbtRequestDiscountSqlMapper dMapper( ibtRequestDiscount, resultset );
                dMapper.map();
                ibtRequest->m_Discounts.push_back( ibtRequestDiscount );
            }

            resultset = m_Accessor->select( IbtRequestRemarkSqlMapper::getSelectSQL( ibtRequest->getIbtRequestId() ) );
            while( resultset.next() )
            {
                IbtRequestRemarkPtr ibtRequestRemark( createRequestRemark() );
                IbtRequestRemarkSqlMapper rMapper( ibtRequestRemark, resultset );
                rMapper.map();
                ibtRequest->m_Remarks.push_back( ibtRequestRemark );
            }
        }
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
        throw;
    }

    std::stringstream ss;
    ss << "IbtRequestRepository::findIbtRequestByKey(): ibtRequest == \n" << *ibtRequest;
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ibtRequest;
}


IIbtRequestCollectionPtr IbtRequestRepository::findByPattern( const basar::Int16 branchNo, const IbtRequestProcessingStateEnum state )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::findByPattern()" );

    m_IbtRequests.clear();
    IIbtRequestCollectionPtr requests( new IIbtRequestCollection() );
    basar::Int32 counter = 0;

    try
    {
        basar::db::sql::ResultsetRef resultset = m_Accessor->select( IbtRequestSqlMapper::getMultiSelectSQL( branchNo, state ) );
        while( resultset.next() )
        {
            ++counter;
            IbtRequestPtr ibtRequest( createRequest() );
            IbtRequestSqlMapper mapper( ibtRequest, resultset );
            mapper.map();
            m_IbtRequests.push_back( ibtRequest );
        }

        IbtRequestCollection::iterator iter = m_IbtRequests.begin();
        for( ; iter != m_IbtRequests.end(); ++iter )
        {
            IbtRequestPtr ibtRequest( *iter );

            resultset = m_Accessor->select( IbtRequestDiscountSqlMapper::getSelectSQL( ibtRequest->getIbtRequestId() ) );
            while( resultset.next() )
            {
                IbtRequestDiscountPtr ibtRequestDiscount( createRequestDiscount() );
                IbtRequestDiscountSqlMapper mapper( ibtRequestDiscount, resultset );
                mapper.map();
                ibtRequest->m_Discounts.push_back( ibtRequestDiscount );
            }

            resultset = m_Accessor->select( IbtRequestRemarkSqlMapper::getSelectSQL( ibtRequest->getIbtRequestId() ) );
            while( resultset.next() )
            {
                IbtRequestRemarkPtr ibtRequestRemark( createRequestRemark() );
                IbtRequestRemarkSqlMapper mapper( ibtRequestRemark, resultset );
                mapper.map();
                ibtRequest->m_Remarks.push_back( ibtRequestRemark );
            }

            requests->push_back( ibtRequest );
        }

        m_IbtRequests.clear();
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
        throw;
    }

    std::stringstream ss;
    ss << "IbtRequestRepository::findByPattern(): " << counter << " request(s) found\n";
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return requests;
}

void IbtRequestRepository::reloadIbtRequest( IIbtRequestPtr iibtRequest )
{
    IbtRequestPtr ibtRequest = boost::dynamic_pointer_cast<IbtRequest>( iibtRequest );
    reloadIbtRequest( ibtRequest );
}

void IbtRequestRepository::reloadIbtRequest( IbtRequestPtr ibtRequest )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::reloadIbtRequest()" );

    try
    {
        basar::db::sql::ResultsetRef resultset = m_Accessor->select( IbtRequestSqlMapper::getSelectSQL( ibtRequest ) );
        if( resultset.next() )
        {
            IbtRequestSqlMapper mapper( ibtRequest, resultset );
            mapper.map();

            ibtRequest->m_Discounts.clear();
            resultset = m_Accessor->select( IbtRequestDiscountSqlMapper::getSelectSQL( ibtRequest->getIbtRequestId() ) );
            while( resultset.next() )
            {
                IbtRequestDiscountPtr ibtRequestDiscount( createRequestDiscount() );
                IbtRequestDiscountSqlMapper dMapper( ibtRequestDiscount, resultset );
                dMapper.map();
                ibtRequest->m_Discounts.push_back( ibtRequestDiscount );
            }

            ibtRequest->m_Remarks.clear();
            resultset = m_Accessor->select( IbtRequestRemarkSqlMapper::getSelectSQL( ibtRequest->getIbtRequestId() ) );
            while( resultset.next() )
            {
                IbtRequestRemarkPtr ibtRequestRemark( createRequestRemark() );
                IbtRequestRemarkSqlMapper rMapper( ibtRequestRemark, resultset );
                rMapper.map();
                ibtRequest->m_Remarks.push_back( ibtRequestRemark );
            }
        }
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
        throw;
    }

    std::stringstream ss;
    ss << "IbtRequestRepository::reloadIbtRequest(): ibtRequest == \n" << *ibtRequest;
    BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
}

void IbtRequestRepository::saveIbtRequest( IIbtRequestPtr iibtRequest )
{
    IbtRequestPtr ibtRequest = boost::dynamic_pointer_cast<IbtRequest>( iibtRequest );
    saveIbtRequest( ibtRequest );
}

void IbtRequestRepository::saveIbtRequest( IbtRequestPtr ibtRequest )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::saveIbtRequest()" );

    persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
    try
    {
        if( IbtRequestSqlMapper::isInsertable( ibtRequest ) )
        {
            m_Accessor->execute( IbtRequestSqlMapper::getInsertSQL( ibtRequest ) );
            ibtRequest->setIbtRequestId( static_cast<basar::Int32>(m_Accessor->getLastInsertedSerial()) );
            setIbtRequestDiscountsSerial( ibtRequest );
            setIbtRequestRemarksSerial( ibtRequest );
        }
        else if( IbtRequestSqlMapper::isUpdatable( ibtRequest ) )
        {
            m_Accessor->execute( IbtRequestSqlMapper::getUpdateSQL( ibtRequest ) );
        }

        ibtRequest->setClean();
        saveIbtRequestDiscounts( ibtRequest );
        saveIbtRequestRemarks( ibtRequest );
        guard.commit();
    }
    catch( const basar::Exception & e )
    {
        guard.rollback();
        std::stringstream ss;
        ss << "IbtRequestRepository::saveIbtRequest(): " << e.what().c_str();
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
        throw;
    }
}

void IbtRequestRepository::setIbtRequestDiscountsSerial( IbtRequestPtr ibtRequest )
{
    basar::Int32 serial = ibtRequest->getIbtRequestId();
    IIbtRequestDiscountCollection::const_iterator iter = ibtRequest->getDiscounts().begin();
    for( ; iter != ibtRequest->getDiscounts().end(); ++iter )
    {
        IbtRequestDiscountPtr ibtRequestDiscount = boost::dynamic_pointer_cast<IbtRequestDiscount>( *iter );
        ibtRequestDiscount->setIbtRequestId( serial );
    }
}

void IbtRequestRepository::setIbtRequestRemarksSerial( IbtRequestPtr ibtRequest )
{
    basar::Int32 serial = ibtRequest->getIbtRequestId();
    IIbtRequestRemarkCollection::const_iterator iter = ibtRequest->getRemarks().begin();
    for( ; iter != ibtRequest->getRemarks().end(); ++iter )
    {
        IbtRequestRemarkPtr ibtRequestRemark = boost::dynamic_pointer_cast<IbtRequestRemark>( *iter );
        ibtRequestRemark->setIbtRequestId( serial );
    }
}

void IbtRequestRepository::saveIbtRequestDiscounts( IbtRequestPtr ibtRequest )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::saveIbtRequestDiscounts()" );

    try
    {
        IIbtRequestDiscountCollection::const_iterator iter = ibtRequest->getDiscounts().begin();
        for( ; iter != ibtRequest->getDiscounts().end(); ++iter )
        {
            IbtRequestDiscountPtr ibtRequestDiscount = boost::dynamic_pointer_cast<IbtRequestDiscount>( *iter );
            if( IbtRequestDiscountSqlMapper::isInsertable( ibtRequestDiscount ) )
            {
                m_Accessor->execute( IbtRequestDiscountSqlMapper::getInsertSQL( ibtRequestDiscount ) );
            }
            else if( IbtRequestDiscountSqlMapper::isUpdatable( ibtRequestDiscount ) )
            {
                m_Accessor->execute( IbtRequestDiscountSqlMapper::getUpdateSQL( ibtRequestDiscount ) );
            }

            ibtRequestDiscount->setClean();
        }
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
        throw;
    }
}

void IbtRequestRepository::saveIbtRequestRemarks( IbtRequestPtr ibtRequest )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::saveIbtRequestRemarks()" );

    try
    {
        IIbtRequestRemarkCollection::const_iterator iter = ibtRequest->getRemarks().begin();
        for( ; iter != ibtRequest->getRemarks().end(); ++iter )
        {
            IbtRequestRemarkPtr ibtRequestRemark = boost::dynamic_pointer_cast<IbtRequestRemark>( *iter );
            if( IbtRequestRemarkSqlMapper::isInsertable( ibtRequestRemark ) )
            {
                m_Accessor->execute( IbtRequestRemarkSqlMapper::getInsertSQL( ibtRequestRemark ) );
            }
            else if( IbtRequestRemarkSqlMapper::isUpdatable( ibtRequestRemark ) )
            {
                m_Accessor->execute( IbtRequestRemarkSqlMapper::getUpdateSQL( ibtRequestRemark ) );
            }

            ibtRequestRemark->setClean();
        }
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
        throw;
    }
}

void IbtRequestRepository::deleteIbtRequest( IIbtRequestPtr iibtRequest )
{
    IbtRequestPtr ibtRequest = boost::dynamic_pointer_cast<IbtRequest>( iibtRequest );
    deleteIbtRequest( ibtRequest );
}

void IbtRequestRepository::deleteIbtRequest( IbtRequestPtr ibtRequest )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::deleteIbtRequest()" );

    persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
    try
    {
        if( IbtRequestSqlMapper::isDeletable( ibtRequest ) )
        {
            m_Accessor->execute( IbtRequestSqlMapper::getDeleteSQL( ibtRequest ) );
        }

        deleteIbtRequestDiscounts( ibtRequest );
        deleteIbtRequestRemarks( ibtRequest );
        guard.commit();
        m_IbtRequests.remove( ibtRequest );
        ibtRequest.reset();
    }
    catch( const basar::Exception & e )
    {
        guard.rollback();
        std::stringstream ss;
        ss << "IbtRequestRepository::deleteIbtRequest(): " << e.what().c_str();
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
        throw;
    }
}

void IbtRequestRepository::deleteIbtRequestDiscounts( IbtRequestPtr ibtRequest )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::deleteIbtRequestDiscounts()" );

    try
    {
        IIbtRequestDiscountCollection::const_iterator iter = ibtRequest->getDiscounts().begin();
        for( ; iter != ibtRequest->getDiscounts().end(); ++iter )
        {
            IbtRequestDiscountPtr ibtRequestDiscount = boost::dynamic_pointer_cast<IbtRequestDiscount>( *iter );
            if( IbtRequestDiscountSqlMapper::isDeletable( ibtRequestDiscount ) )
            {
                m_Accessor->execute( IbtRequestDiscountSqlMapper::getDeleteSQL( ibtRequestDiscount ) );
            }
        }
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
        throw;
    }
}

void IbtRequestRepository::deleteIbtRequestRemarks( IbtRequestPtr ibtRequest )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestRepository::deleteIbtRequestRemarks()" );

    try
    {
        IIbtRequestRemarkCollection::const_iterator iter = ibtRequest->getRemarks().begin();
        for( ; iter != ibtRequest->getRemarks().end(); ++iter )
        {
            IbtRequestRemarkPtr ibtRequestRemark = boost::dynamic_pointer_cast<IbtRequestRemark>( *iter );
            if( IbtRequestRemarkSqlMapper::isDeletable( ibtRequestRemark ) )
            {
                m_Accessor->execute( IbtRequestRemarkSqlMapper::getDeleteSQL( ibtRequestRemark ) );
            }
        }
    }
    catch( const basar::Exception & e )
    {
        BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
        throw;
    }
}

IIbtRequestPtr IbtRequestRepository::createRequest( const IbtRequestKey & key )
{
    IbtRequestPtr ibtRequest( createRequest() );
    ibtRequest->setBranchNo( key.branchNo );
    ibtRequest->setCscOrderNo( key.cscOrderNo );
    ibtRequest->setCscOrderPosNo( key.cscOrderPosNo );
    //ibtRequest->setIbtBranchNo( key.ibtBranchNo );
    m_IbtRequests.push_back( ibtRequest );
    return ibtRequest;
}

IbtRequestPtr IbtRequestRepository::createRequest()
{
    IbtRequestPtr ibtRequest( new IbtRequest() );
    ibtRequest->injectRequestFactory( shared_from_this() );
    return ibtRequest;
}

IIbtRequestDiscountPtr IbtRequestRepository::createRequestDiscount( IbtRequestPtr ibtRequest, const IbtRequestDiscountTypeEnum discountType, const basar::Int16 paymentTargetNo ) const
{
    IbtRequestDiscountPtr ibtRequestDiscount( createRequestDiscount() );

    if( false == ibtRequest->getIbtRequestId().isUnset() )
    {
        ibtRequestDiscount->setIbtRequestId( ibtRequest->getIbtRequestId() );
    }
    ibtRequestDiscount->setDiscountType( discountType );
    ibtRequestDiscount->setPaymentTargetNo( paymentTargetNo );

    ibtRequest->m_Discounts.push_back( ibtRequestDiscount );
    return ibtRequestDiscount;
}

IbtRequestDiscountPtr IbtRequestRepository::createRequestDiscount() const
{
    return IbtRequestDiscountPtr( new IbtRequestDiscount() );
}

IIbtRequestRemarkPtr IbtRequestRepository::createRequestRemark( IbtRequestPtr ibtRequest, const IbtRequestRemarkLevelEnum remarkLevel, const OrderRemarkTypeEnum remarkType ) const
{
    IbtRequestRemarkPtr ibtRequestRemark( createRequestRemark() );

    if( false == ibtRequest->getIbtRequestId().isUnset() )
    {
        ibtRequestRemark->setIbtRequestId( ibtRequest->getIbtRequestId() );
    }
    ibtRequestRemark->setRemarkLevel( remarkLevel );
    ibtRequestRemark->setRemarkType( remarkType );

    ibtRequest->m_Remarks.push_back( ibtRequestRemark );
    return ibtRequestRemark;
}

IbtRequestRemarkPtr IbtRequestRepository::createRequestRemark() const
{
    return IbtRequestRemarkPtr( new IbtRequestRemark() );
}

} // end namespace ibt
} // end namespace libcsc
