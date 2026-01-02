#include "cscorderflagsrepository.h"
#include "logger/loggerpool.h"
#include "cscorder/cscorderflags/cscorderflags.h"
#include "cscorder/cscorderflags/cscorderflagsptr.h"
#include "cscorderflagssqlmapper.h"
#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>

namespace libcsc {
namespace cscorder {
namespace repo {

CSCOrderFlagsRepository::CSCOrderFlagsRepository()    
{
}

CSCOrderFlagsRepository::~CSCOrderFlagsRepository()
{
	m_DeleteAccessor.reset();
	m_InsertAccessor.reset();
    m_UpdateAccessor.reset();
	m_FindAccessor.reset();
}  	

void CSCOrderFlagsRepository::injectDeleteAccessor(persistence::IAccessorPtr accessor)
{
	m_DeleteAccessor = accessor;    
}

void CSCOrderFlagsRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
{
	m_InsertAccessor = accessor;    
}

void CSCOrderFlagsRepository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
{
	m_UpdateAccessor = accessor;    
}

void CSCOrderFlagsRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

void CSCOrderFlagsRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
    m_TransactionFactory = transactionFactory;
}

bool CSCOrderFlagsRepository::saveCSCOrderFlags(domMod::ICSCOrderFlagsPtr cscOrderFlags)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCOrderFlagsRepository::saveCSCOrderFlags()");	
    
	persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();

	std::stringstream tmp;
	tmp << "CSCOrderFlagsRepository::saveCSCOrderFlags (" << cscOrderFlags->getCscOrderNo() << ") ";
	
	basar::VarString query = "";
    try
    {
        guard.begin();
        {            
			if( CSCOrderFlagsSqlMapper::isInsertable( cscOrderFlags ) )            
            {			                				
				query = CSCOrderFlagsSqlMapper::getInsertSQL();
				m_InsertAccessor->execute(query, CSCOrderFlagsSqlMapper::getInsertSqlParameterBinder(cscOrderFlags));                				
            }            
			else if (CSCOrderFlagsSqlMapper::isUpdatable( cscOrderFlags ) )
            {   
				query = CSCOrderFlagsSqlMapper::getUpdateSQL();
				m_UpdateAccessor->execute(query, CSCOrderFlagsSqlMapper::getUpdateSqlParameterBinder(cscOrderFlags));
            }            
        }
        guard.commit();	

		cscOrderFlags->setClean();
		
		tmp << " done for OrderNo " << cscOrderFlags->getCscOrderNo();				
		BLOG_TRACE(LoggerPool::getLoggerOrder(), tmp.str().c_str());
    }
	catch(libcsc::exceptions::PropertyUnsetException const& exc )
	{
        guard.rollback();
        std::stringstream ss;
		ss << "CSCOrderFlagsRepository::saveCSCOrderFlags(" << cscOrderFlags->getCscOrderNo() << "): " << exc.what().c_str() << " ( " <<  query.c_str() << " ) ";
		BLOG_ERROR(LoggerPool::getLoggerOrder(), ss.str().c_str());
        return false;
	}
	catch(libcsc::exceptions::CSCExceptionBase const& exc )
	{
        guard.rollback();
        std::stringstream ss;
        ss << "CSCOrderFlagsRepository::saveCSCOrderFlags(" << cscOrderFlags->getCscOrderNo() << "): " << exc.what().c_str() << " ( " <<  query.c_str() << " ) ";
		BLOG_ERROR(LoggerPool::getLoggerOrder(), ss.str().c_str());
        return false;
	}
	catch (basar::Exception const& exc)
    {
        guard.rollback();
        std::stringstream ss;
        ss << "CSCOrderFlagsRepository::saveCSCOrderFlags(" << cscOrderFlags->getCscOrderNo() << "): " << exc.what().c_str() << " ( " <<  query.c_str() << " ) ";
		BLOG_ERROR(LoggerPool::getLoggerOrder(), ss.str().c_str());
        return false;
    }
    return true;
}

bool CSCOrderFlagsRepository::deleteCSCOrderFlags(basar::Int32 const& cscorderno)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerOrder(), "CSCOrderFlagsRepository::deleteCSCOrderFlags()");

	if (cscorderno <= 0)
    {
        return true;
    }

    persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
    try
    {
        guard.begin();
		{                        
			m_DeleteAccessor->execute(CSCOrderFlagsSqlMapper::getDeleteSQL(cscorderno));            
        }
        guard.commit();
    }
    catch (basar::Exception const& exc)
    {
        guard.rollback();
        std::stringstream ss;
        ss << "CSCOrderFlagsRepository::deleteCSCOrderFlags(): " << exc.what().c_str();
		BLOG_ERROR(LoggerPool::getLoggerOrder(), ss.str().c_str());
        return false;
    }
    return true;
}

domMod::ICSCOrderFlagsPtr CSCOrderFlagsRepository::findCSCOrderFlags(const basar::Int32 cscorderno)
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerOrder(), "CSCOrderFlagsRepository::findCSCOrderFlags" );
				
    try
    {   
		std::stringstream tmp;
		tmp << "CSCOrderFlagsRepository::findCSCOrderFlags (" << cscorderno << ") ";
		
		domMod::CSCOrderFlagsPtr cscOrderFlags = domMod::CSCOrderFlagsPtr( new domMod::CSCOrderFlags() );			            
		basar::db::sql::ResultsetRef resultset = m_FindAccessor->select( repo::CSCOrderFlagsSqlMapper::getSelectSQL(cscorderno) );
        if( resultset.next() ) // full caching
        {									
			repo::CSCOrderFlagsSqlMapper mapper( cscOrderFlags, resultset );
            mapper.map();			                        
			tmp << " Record found and mapped.";
        }		
		else
		{
			tmp << " No Record found.";
		}

		tmp << " OrderNo: " << cscOrderFlags->getCscOrderNo() << " NoDelayedDelivery " << cscOrderFlags->isNoDelayedDelivery();		
		BLOG_TRACE(LoggerPool::getLoggerOrder(), tmp.str().c_str());

		return cscOrderFlags;
    }
    catch( basar::Exception & e)
    {
		std::stringstream s;        
		s << "findCSCOrderFlags ERROR at processing cscorderno < " << cscorderno << " > when reading CSCOrderFlags: " << e.what();
		BLOG_ERROR(LoggerPool::getLoggerOrder(), s.str());
		throw;
    }    
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
