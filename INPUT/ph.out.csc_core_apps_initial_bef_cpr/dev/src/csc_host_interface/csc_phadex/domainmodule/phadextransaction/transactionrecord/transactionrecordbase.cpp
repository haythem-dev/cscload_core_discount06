#include "transactionrecordbase.h"
#include <domainmodule/dataconversionexception.h>
#include <domainmodule/phadextransaction/phadextransactiondm.h>
#include "loggerpool/csc_phadex_loggerpool.h"

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
TransactionRecordBase::TransactionRecordBase( IPhadexTransactionPtr phadexTransaction )
: m_PhadexTransaction( phadexTransaction ),
m_Logger( csc_phadex::LoggerPool::getLoggerDomModules() )
{
}

TransactionRecordBase::~TransactionRecordBase()
{
}

basar::Int16 TransactionRecordBase::getBranchno() const
{
    return m_PhadexTransaction->getBranchno();
}

const basar::DateTime & TransactionRecordBase::getCreationDateTime() const
{
    return m_PhadexTransaction->getCreationDateTime();
}

basar::Int16 TransactionRecordBase::getRecordType() const
{
    return m_PhadexTransaction->getRecordType();
}

basar::Int32 TransactionRecordBase::getRecordNo() const
{
    return m_PhadexTransaction->getRecordNo();
}

basar::Int16 TransactionRecordBase::getInt16( const basar::Int32 pos, const basar::Int32 len ) const
{
    METHODNAME_DEF( TransactionRecordBase, getInt16 );
    BLOG_TRACE_METHOD( m_Logger, fun );

    basar::VarString temp;
    try
    {
        temp = m_PhadexTransaction->getData().substr( pos, len );
        return static_cast<basar::Int16>( temp.stoi() );
    }
    catch ( ... )
    {
      std ::  stringstream ss;
      ss << "Error converting <" << temp.c_str() << "> to Int16!";
      throw csc_phadex :: exception :: DataConversionException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
    }
}

basar::Int32 TransactionRecordBase::getInt32( const basar::Int32 pos, const basar::Int32 len ) const
{
    METHODNAME_DEF( TransactionRecordBase, getInt32 );
    BLOG_TRACE_METHOD( m_Logger, fun );

    basar::VarString temp;
    try
    {
        temp = m_PhadexTransaction->getData().substr( pos, len );
        return static_cast<basar::Int32>( temp.stoi() );
    }
    catch ( ... )
    {
      std ::  stringstream ss;
      ss << "Error converting <" << temp.c_str() << "> to Int32!";
      throw csc_phadex :: exception :: DataConversionException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
    }
}

const basar::Date TransactionRecordBase::getDate( const basar::Int32 pos, const basar::Int32 len ) const
{
    METHODNAME_DEF( TransactionRecordBase, getDate );
    BLOG_TRACE_METHOD( m_Logger, fun );

    basar::VarString temp;

    try
    {
        temp = m_PhadexTransaction->getData().substr( pos, len );
        return basar::Date(temp.stoi());
    }
    catch ( ... )
    {
      std ::  stringstream ss;
      ss << "Error converting <" << temp.c_str() << "> to Date!";
      throw csc_phadex :: exception :: DataConversionException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
    }
}

const basar::DateTime TransactionRecordBase::getDateTime( const basar::Int32 pos, const basar::Int32 len ) const
{
    METHODNAME_DEF( TransactionRecordBase, getDateTime );
    BLOG_TRACE_METHOD( m_Logger, fun );

    basar::VarString temp;

    try
    {
        temp = m_PhadexTransaction->getData().substr( pos, len );
        return basar::DateTime(temp.stoi());
    }
    catch ( ... )
    {
      std ::  stringstream ss;
      ss << "Error converting <" << temp.c_str() << "> to DateTime!";
      throw csc_phadex :: exception :: DataConversionException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
    }
}

const basar::VarString TransactionRecordBase::getString( const basar::Int32 pos, const basar::Int32 len ) const
{
    METHODNAME_DEF( TransactionRecordBase, getString );
    BLOG_TRACE_METHOD( m_Logger, fun );

    basar::VarString temp;

    try
    {
        temp = m_PhadexTransaction->getData().substr( pos, len );
        return temp ;
    }
    catch ( ... )
    {
      std ::  stringstream ss;
      ss << "Error converting <" << temp.c_str() << "> to String!";
      throw csc_phadex :: exception :: DataConversionException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
    }
}

const basar::Decimal TransactionRecordBase::getDecimal( const basar::Int32 pos, const basar::Int32 len ) const
{
    METHODNAME_DEF( TransactionRecordBase, getDecimal );
    BLOG_TRACE_METHOD( m_Logger, fun );

    basar::VarString temp;

    try
    {
        temp = m_PhadexTransaction->getData().substr( pos, len );
        return static_cast<basar::Decimal>( temp.stof() );
    }
    catch ( ... )
    {
      std ::  stringstream ss;
      ss << "Error converting <" << temp.c_str() << "> to Decimal!";
      throw csc_phadex :: exception :: DataConversionException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
    }

}


} // end namespace phadexTransaction
} // end namespace domMod
} // end namespace csc_phadex

