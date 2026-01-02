#include "csvorderimportrepository.h"
#include <parameter/csvorderimport/cscorderimportfieldssqlmapper.h>
#include <parameter/csvorderimport/cscorderimportfields.h>
#include <parameter/csvorderimport/cscorderimportcsvformatssqlmapper.h>
#include <parameter/csvorderimport/cscorderimportcsvformats.h>
#include <parameter/csvorderimport/cscorderimportcsvcolumnssqlmapper.h>
#include <parameter/csvorderimport/icscorderimportcsvcolumnsptr.h>
#include <parameter/csvorderimport/cscorderimportcsvcolumns.h>
#include <persistence/iaccessor.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace parameter {

CSVOrderImportRepository::CSVOrderImportRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::CSVOrderImportRepository()");
}

CSVOrderImportRepository::~CSVOrderImportRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::~CSVOrderImportRepository()");

	m_SelectCSCOrderImportCSVFieldsAccessor.reset(); 
	m_SelectCSCOrderImportFormatsAccessor.reset();
	m_InsertCSCOrderImportFormatsAccessor.reset();
	m_UpdateCSCOrderImportFormatsAccessor.reset();
	m_DeleteCSCOrderImportFormatsAccessor.reset();
	m_SelectCSCOrderImportCSVColumnsAccessor.reset();
	m_InsertCSCOrderImportCSVColumnsAccessor.reset();
	m_DeleteCSCOrderImportCSVColumnsAccessor.reset();

}

void CSVOrderImportRepository::reset()
{
	m_CSCOrderImportFieldsList.reset();
	m_CSCOrderImportCSVFormatsList.reset();
}

void CSVOrderImportRepository::injectSelectCSCOrderImportCSVFieldsAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::injectSelectCSCOrderImportCSVFieldsAccessor()");

	m_SelectCSCOrderImportCSVFieldsAccessor = accessor;
}

void CSVOrderImportRepository::injectSelectCSCOrderImportCSVFormatsAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::injectSelectCSCOrderImportCSVFormatsAccessor()");
	m_SelectCSCOrderImportFormatsAccessor = accessor;
}

void CSVOrderImportRepository::injectInsertCSCOrderImportCSVFormatsAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::injectInsertCSCOrderImportCSVFormatsAccessor()");
	m_InsertCSCOrderImportFormatsAccessor = accessor;
}

void CSVOrderImportRepository::injectUpdateCSCOrderImportCSVFormatsAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::injectUpdateCSCOrderImportCSVFormatsAccessor()");
	m_UpdateCSCOrderImportFormatsAccessor = accessor;
}

void CSVOrderImportRepository::injectDeleteCSCOrderImportCSVFormatsAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::injectDeleteCSCOrderImportCSVFormatsAccessor()");
	m_DeleteCSCOrderImportFormatsAccessor = accessor;
}

void CSVOrderImportRepository::injectSelectCSCOrderImportCSVColumnsAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::injectSelectCSCOrderImportCSVColumnsAccessor()");
	m_SelectCSCOrderImportCSVColumnsAccessor = accessor;
}

void CSVOrderImportRepository::injectInsertCSCOrderImportCSVColumnsAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::injectInsertCSCOrderImportCSVColumnsAccessor()");
	m_InsertCSCOrderImportCSVColumnsAccessor = accessor;
}

void CSVOrderImportRepository::injectDeleteCSCOrderImportCSVColumnsAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::injectDeleteCSCOrderImportCSVColumnsAccessor()");
	m_DeleteCSCOrderImportCSVColumnsAccessor = accessor;
}

ICSCOrderImportFieldsCollectionPtr CSVOrderImportRepository::findCSCOrderImportCSVFields()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::findCSCOrderImportCSVFields()");

	if (NULL == m_CSCOrderImportFieldsList.get())
	{
		m_CSCOrderImportFieldsList = boost::make_shared<ICSCOrderImportFieldsCollection>();
		try
		{
			basar::db::sql::ResultsetRef resultset = m_SelectCSCOrderImportCSVFieldsAccessor->select(CSCOrderImportFieldsSQLMapper::getSelectSQL());
			while (resultset.next())
			{
				CSCOrderImportFieldsPtr importfield = boost::make_shared<CSCOrderImportFields>();
				CSCOrderImportFieldsSQLMapper mapper(importfield, resultset);
				mapper.map();
				m_CSCOrderImportFieldsList->push_back(importfield);
			}
		}
		catch (basar::Exception &)
		{
			throw;
		}
	}
	return m_CSCOrderImportFieldsList;
}

ICSCOrderImportCSVFormatsPtr CSVOrderImportRepository::getEmptyCSCOrderImportCSVFormats()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::getEmptyCSCOrderImportCSVFormats()");

	return boost::make_shared<CSCOrderImportCSVFormats>();
}

void CSVOrderImportRepository::saveCSCOrderImportCSVFormats(ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::saveCSCOrderImportCSVFormats()");
	try
	{
		if (CSCOrderImportCSVFormats->isInsertable())
		{
			m_InsertCSCOrderImportFormatsAccessor->execute(CSCOrderImportCSVFormatsSQLMapper::getInsertSQL(CSCOrderImportCSVFormats));
			CSCOrderImportCSVFormats->setCSCOrderImportFormatID(static_cast<basar::Int32>(m_InsertCSCOrderImportFormatsAccessor->getLastInsertedSerial()));
		}
		else if (CSCOrderImportCSVFormats->isUpdatable())
		{
			m_UpdateCSCOrderImportFormatsAccessor->execute(
				CSCOrderImportCSVFormatsSQLMapper::getUpdateSQL(CSCOrderImportCSVFormats)
			);
		}
		ICSCOrderImportCSVColumnsCollection::const_iterator it;
		it = CSCOrderImportCSVFormats->getCSCOrderImportCSVColums()->begin();
		while (it != CSCOrderImportCSVFormats->getCSCOrderImportCSVColums()->end())
		{
			if ((*it)->isInsertable())
			{
				saveCSCOrderImportCSVColumns(*it);
			}
			else if ((*it)->isMarkedForDeletion())
			{
				deleteCSCOrderImportCSVColumnsByKey((*it)->getColumnNo(), (*it)->getCscOrderImportFormatId());
			}
			++it;
		}
	}
	catch( basar::Exception & )
	{
		throw;
	}
}

void CSVOrderImportRepository::deleteCSCOrderImportCSVFormats(ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::deleteCSCOrderImportCSVFormats()");

	try
	{
		m_DeleteCSCOrderImportFormatsAccessor->execute(
			CSCOrderImportCSVFormatsSQLMapper::getDeleteSQL(CSCOrderImportCSVFormats->getCSCOrderImportFormatID())
		);
		deleteCSCOrderImportCSVColumnsByID(CSCOrderImportCSVFormats->getCSCOrderImportFormatID());
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

void CSVOrderImportRepository::findCSCOrderImportCSVColumns(CSCOrderImportCSVFormatsPtr CSVFormats)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::findCSCOrderImportCSVColumns()");

	try
	{
		basar::db::sql::ResultsetRef resultset = m_SelectCSCOrderImportCSVColumnsAccessor->select(
			CSCOrderImportCSVColumnsSQLMapper::getSelectSQLByCscOrderImportFormatId(CSVFormats->getCSCOrderImportFormatID()) );
		while (resultset.next())
		{
			CSCOrderImportCSVColumnsPtr format_grp = boost::make_shared<CSCOrderImportCSVColumns>();
			CSCOrderImportCSVColumnsSQLMapper mapper(format_grp, resultset);
			mapper.map();
			CSVFormats->m_CSCOrderImportCSVColums->push_back(format_grp);
		}
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

void CSVOrderImportRepository::saveCSCOrderImportCSVColumns(ICSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::saveCSCOrderImportCSVColumns()");
	try
	{
		if (CSCOrderImportCSVColumns->isInsertable())
		{
			m_InsertCSCOrderImportCSVColumnsAccessor->execute(CSCOrderImportCSVColumnsSQLMapper::getInsertSQL(CSCOrderImportCSVColumns));
		}
	}
	catch( basar::Exception & )
	{
		throw;
	}
}

void CSVOrderImportRepository::deleteCSCOrderImportCSVColumnsByKey(const basar::Int16& ColumnNo,const basar::Int32& CscOrderImportFormatId)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::deleteCSCOrderImportCSVColumnsByKey()");
	try
	{
		m_DeleteCSCOrderImportCSVColumnsAccessor->execute(
			CSCOrderImportCSVColumnsSQLMapper::getDeleteSQLByKey(ColumnNo, CscOrderImportFormatId)
		);
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

void CSVOrderImportRepository::deleteCSCOrderImportCSVColumnsByID(const basar::Int32& CscOrderImportFormatId)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::deleteCSCOrderImportCSVColumnsByID()");
	try
	{
		m_DeleteCSCOrderImportCSVColumnsAccessor->execute(
			CSCOrderImportCSVColumnsSQLMapper::getDeleteSQLByCscOrderImportFormatId(CscOrderImportFormatId)
		);
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

ICSCOrderImportCSVFormatsCollectionPtr CSVOrderImportRepository::findCSCOrderImportCSVFormats()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::readCSCOrderImportCSVFormats()");

	if (NULL == m_CSCOrderImportCSVFormatsList.get())
	{
		m_CSCOrderImportCSVFormatsList = boost::make_shared<ICSCOrderImportCSVFormatsCollection>();

		basar::db::sql::ResultsetRef resultset = m_SelectCSCOrderImportFormatsAccessor->select(
			CSCOrderImportCSVFormatsSQLMapper::getSelectSQL()
		);
		while (resultset.next())
		{
			CSCOrderImportCSVFormatsPtr cscOrderImportCSVFormats = boost::make_shared<CSCOrderImportCSVFormats>();
			CSCOrderImportCSVFormatsSQLMapper mapper(cscOrderImportCSVFormats, resultset);
			mapper.map();
			findCSCOrderImportCSVColumns(cscOrderImportCSVFormats);

			m_CSCOrderImportCSVFormatsList->push_back(cscOrderImportCSVFormats);
		}
	}

	return m_CSCOrderImportCSVFormatsList;
}

ICSCOrderImportCSVFormatsPtr CSVOrderImportRepository::findCSCOrderImportCSVFormatsById(const basar::Int32& id)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSVOrderImportRepository::findCSCOrderImportCSVFormatsById()");

	ICSCOrderImportCSVFormatsPtr format;
	findCSCOrderImportCSVFormats();
	for (unsigned int i = 0;i < m_CSCOrderImportCSVFormatsList->size();i++)
	{
		if (m_CSCOrderImportCSVFormatsList->at(i)->getCSCOrderImportFormatID() == id)
		{
			format = m_CSCOrderImportCSVFormatsList->at(i);
			break;
		}
	}
	return format;
}

bool CSVOrderImportRepository::areMandatoryFieldsSet(ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats)
{
	findCSCOrderImportCSVFields();

	// iterate throught all fields
	ICSCOrderImportFieldsCollection::const_iterator fieldIt = m_CSCOrderImportFieldsList->begin();
	while (fieldIt != m_CSCOrderImportFieldsList->end())
	{
		// if field is mandatory, search for this field in format
		if (true == (*fieldIt)->isImportMandatory())
		{
			if (false == CSCOrderImportCSVFormats->containsColumn((*fieldIt)->getFieldNameId()))
			{
				return false;
			}
		}
		++fieldIt;
	}
	return true;
}

} // end namespace parameter
} // end namespace libcsc
