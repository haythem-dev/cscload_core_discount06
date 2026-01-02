#include "pxlockaccessordecorator.h"

#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <libbasardbsql.h>

#include <pxdbxx.h>

// informix client sdk: Get name of connection which is currently active
// TODO remove when BASAR returns internal connection name
extern "C" char* ifx_getcur_conn_name();


namespace lock
{
	PxLockAccessorDecorator::PxLockAccessorDecorator( libLockManager::accessor::ILockAccessorPtr accessor,
		const basar::VarString internalConnName,
		const basar::VarString lockConnName) :
		m_Accessor( accessor ),
		m_internalConnectionName(internalConnName),
		m_lockConnectionName(lockConnName)
	{
		BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorDecorator::PxLockAccessorDecorator");
	}

	PxLockAccessorDecorator::~PxLockAccessorDecorator()
	{
		BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorDecorator::~PxLockAccessorDecorator");
	}

	void PxLockAccessorDecorator::setLockConnection()
	{
		if (m_lockConnectionName != ifx_getcur_conn_name())
		{
			pxSetCurrentDb( m_lockConnectionName.c_str() );
		}
	}

	void PxLockAccessorDecorator::setInternalConnection()
	{
		if (m_internalConnectionName != ifx_getcur_conn_name())
		{
			pxSetCurrentDb( m_internalConnectionName.c_str() );
		}
	}

	bool PxLockAccessorDecorator::findByKey( const libLockManager::IKey& key )
	{
		BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorDecorator::findByKey");

		bool ret = false;
		try
		{
			setLockConnection();
			ret = m_Accessor->findByKey( key );
			setInternalConnection();
		}
		catch(...)
		{
			setInternalConnection();
			throw;
		}

		return ret;
	}

	void PxLockAccessorDecorator::save( const libLockManager::ILockEntry& lockEntry )
	{
		BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorDecorator::save");

		try
		{
			setLockConnection();
			m_Accessor->save( lockEntry );
			setInternalConnection();
		}
		catch(...)
		{
			setInternalConnection();
			throw;
		}
	}

	void PxLockAccessorDecorator::erase( const libLockManager::IKey& key )
	{
		BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorDecorator::erase");

		try
		{
			setLockConnection();
			m_Accessor->erase( key );
			setInternalConnection();
		}
		catch(...)
		{
			setInternalConnection();
			throw;
		}
	}

	void PxLockAccessorDecorator::forceErase( const libLockManager::IKey& key )
	{
		BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorDecorator::forceErase");

		try
		{
			setLockConnection();
			m_Accessor->forceErase( key );
			setInternalConnection();
		}
		catch(...)
		{
			setInternalConnection();
			throw;
		}
	}

	void PxLockAccessorDecorator::eraseStaleLocks()
	{
		BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorDecorator::eraseStaleLocks");

		try
		{
			setLockConnection();
			m_Accessor->eraseStaleLocks();
			setInternalConnection();
		}
		catch(...)
		{
			setInternalConnection();
			throw;
		}
	}
	
	void PxLockAccessorDecorator::injectErrorHandler(libLockManager::accessor::ILockAccessorErrorHandlerPtr errorHandler)
	{
		BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "PxLockAccessorDecorator::injectErrorHandler");
		
		m_Accessor->injectErrorHandler(errorHandler);
	}
	
} // end namespace lock
