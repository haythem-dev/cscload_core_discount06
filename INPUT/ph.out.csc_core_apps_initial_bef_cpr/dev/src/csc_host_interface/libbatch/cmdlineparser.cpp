//-------------------------------------------------------------------------------------------------//
/*! \file commandlineparser.cpp
 *  \brief definition of class CommandlineParser
 *  \author Dirk Kapusta
 *  \date 21.10.2008
 *  \version 00.00.00.01 first version
 */ 
//-------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libbasarcmnutil.h>
#include "cmdlineparser.h"
#include "cmdlineexception.h"
#include "loggerpool.h"
#include "classinfo_macros.h"

#ifdef WIN32
	#pragma warning (push)
		#pragma warning(disable: 4127 4189 4244 4251 4311 4312 4511 4512 4800)
	#include <QtCore/QCoreApplication>
	#pragma warning (pop)
#else
	#include <QtCore/QCoreApplication>
#endif

//-------------------------------------------------------------------------------------------------//
// using declaration section
//-------------------------------------------------------------------------------------------------//
using basar::VarString;

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace libBatch
{
namespace cmdLine
{

/*! \throw CommandlineException */
CmdLineParser::CmdLineParser()
: m_Logger( LoggerPool::LoggerCmdLine )
{
	METHODNAME_DEF( CmdLineParser, CommandLineParser_std )
	BLOG_TRACE_METHOD( m_Logger, fun );

	if( NULL == QCoreApplication::instance() )
	{
        std::stringstream ss; ss << "ERROR: QCoreApplication is not instantiated yet!";
        throw CmdLineException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	m_ArgumentList = QCoreApplication::arguments();
}

/*! \throw no throw */
CmdLineParser::CmdLineParser( basar::Int32 argc, char **argv )
: m_Logger( LoggerPool::LoggerCmdLine )
{
	METHODNAME_DEF( CmdLineParser, CmdLineParser )
	BLOG_TRACE_METHOD( m_Logger, fun );

	QCoreApplication *pApp = QCoreApplication::instance();
	if( NULL == pApp )
	{
		pApp = new QCoreApplication( argc, argv );
	}
	
	m_ArgumentList = QCoreApplication::arguments();
}

/*! \throw no throw */
CmdLineParser::~CmdLineParser()
{
	METHODNAME_DEF( CmdLineParser, ~CmdLineParser )
	BLOG_TRACE_METHOD( m_Logger, fun );

	m_ArgumentList.clear();
}

/*! \throw CommandlineException */
bool CmdLineParser::getMandatoryVarString( basar::ConstString paramName, basar::VarString &value ) const
{
	METHODNAME_DEF( CmdLineParser, getMandatoryVarString )
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool ret = this->getVarString( paramName, value );

	if( !ret )
	{
        std::stringstream ss; ss << "ERROR: Parameter <" << paramName << "> is not set!";
        throw CmdLineException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	return ret;
}

/*! \throw CommandlineException */
bool CmdLineParser::getMandatoryInt16( basar::ConstString paramName, basar::Int16 &value ) const
{
	METHODNAME_DEF( CmdLineParser, getMandatoryInt16 )
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool ret = this->getInt16( paramName, value );

	if( !ret )
	{
		std::stringstream ss; ss << "ERROR: Parameter <" << paramName << "> is not set or value cannot be converted to basar::Int16!";
        throw CmdLineException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	return ret;
}

/*! \throw CommandlineException */
bool CmdLineParser::getMandatoryInt32( basar::ConstString paramName, basar::Int32 &value ) const
{
	METHODNAME_DEF( CmdLineParser, getMandatoryInt32 )
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool ret = this->getInt32( paramName, value );

	if( !ret )
	{
        std::stringstream ss; ss << "ERROR: Parameter <" << paramName << "> is not set or value cannot be converted to basar::Int32!";
        throw CmdLineException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	return ret;
}

/*! \throw CommandlineException */
bool CmdLineParser::getMandatoryDate( basar::ConstString paramName, basar::Date &value ) const
{
	METHODNAME_DEF( CmdLineParser, getMandatoryDate )
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool ret = this->getDate( paramName, value );

	if( !ret )
	{
        std::stringstream ss; ss << "ERROR: Parameter <" << paramName << "> is not set or value cannot be converted to basar::Date, use YYYYMMDD!";
        throw CmdLineException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	return ret;
}

/*! \throw CommandlineException */
bool CmdLineParser::getMandatoryDateTime( basar::ConstString paramName, basar::DateTime &value ) const
{
	METHODNAME_DEF( CmdLineParser, getMandatoryDateTime )
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool ret = this->getDateTime( paramName, value );

	if( !ret )
	{
        std::stringstream ss; ss << "ERROR: Parameter <" << paramName << "> is not set or value cannot be converted to basar::DateTime, use YYYYMMDDHHMM or YYYYMMDD!";
        throw CmdLineException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	return ret;
}

/*! \throw CommandlineException */
bool CmdLineParser::getMandatoryVarStrings( basar::ConstString paramName, std::vector<basar::VarString> &value ) const
{
	METHODNAME_DEF( CmdLineParser, getMandatoryVarStrings )
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool ret = this->getVarStrings( paramName, value );

	if( !ret )
	{
        std::stringstream ss; ss << "ERROR: Parameter <" << paramName << "> is not set!";
        throw CmdLineException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
	}

	return ret;
}

/*! \throw no throw */
bool CmdLineParser::getVarString( basar::ConstString paramName, basar::VarString &value ) const
{
	METHODNAME_DEF( CmdLineParser, getVarString )
	BLOG_TRACE_METHOD( m_Logger, fun );

	bool ret = this->getValOfParam( paramName, value );

	return ret;
}

/*! \throw no throw */
bool CmdLineParser::getInt16( basar::ConstString paramName, basar::Int16 &value ) const
{
	METHODNAME_DEF( CmdLineParser, getInt16 )
	BLOG_TRACE_METHOD( m_Logger, fun );

	basar::VarString temp;
	bool ret = this->getValOfParam( paramName, temp );
	ret &= temp.isDigit();

	if( ret )
	{
		basar::Int16 iTemp;

		try
		{
			iTemp = static_cast<basar::Int16>( temp.stoi() );
		}
		catch( ... )
		{
			return false;
		}

		value = iTemp;
	}

	return ret;
}

/*! \throw no throw */
bool CmdLineParser::getInt32( basar::ConstString paramName, basar::Int32 &value ) const
{
	METHODNAME_DEF( CmdLineParser, getInt32 )
	BLOG_TRACE_METHOD( m_Logger, fun );

	basar::VarString temp;
	bool ret = this->getValOfParam( paramName, temp );
	ret &= temp.isDigit();

	if( ret )
	{
		basar::Int32 iTemp;

		try
		{
			iTemp = static_cast<basar::Int32>( temp.stoi() );
		}
		catch( ... )
		{
			return false;
		}

		value = iTemp;
	}

	return ret;
}

/*! \throw no throw */
bool CmdLineParser::getDate( basar::ConstString paramName, basar::Date &value ) const
{
	METHODNAME_DEF( CmdLineParser, getDate )
	BLOG_TRACE_METHOD( m_Logger, fun );

	basar::VarString temp;
	bool ret = this->getValOfParam( paramName, temp );
	ret &= temp.isDigit();

	if( ret )
	{
		basar::Date dTemp;

		try
		{
			basar::Int32 iTemp;

			if( 8 == temp.length() )
			{
				iTemp = temp.stoi();
				dTemp = basar::Date( iTemp );
			}
			else
			{
				return false;
			}
		}
		catch( ... )
		{
			return false;
		}

		value = dTemp;
	}

	return ret;
}

/*! \throw no throw */
bool CmdLineParser::getDateTime( basar::ConstString paramName, basar::DateTime &value ) const
{
	METHODNAME_DEF( CmdLineParser, getDateTime )
	BLOG_TRACE_METHOD( m_Logger, fun );

	basar::VarString temp;
	bool ret = this->getValOfParam( paramName, temp );
	ret &= temp.isDigit();

	if( ret )
	{
		basar::DateTime dtTemp;
		
		try
		{
			basar::Int32 iDate = 0;
			basar::Int32 iTime = 0;

			if( 12 == temp.length() )
			{
				basar::VarString strDate = temp.substr( 0, 8 );
				basar::VarString strTime = temp.substr( 8, 4 );
				iDate = strDate.stoi();
				iTime = strTime.stoi();
				iTime *= 100000;
				dtTemp = basar::DateTime( iDate, iTime );
			}
			else if( 8 == temp.length() )
			{
				iDate = temp.stoi();
				iTime = 0;
				dtTemp = basar::DateTime( iDate, iTime );
			}	
			else
			{
				return false;
			}
		}
		catch( ... )
		{
			return false;
		}

		value = dtTemp;
	}

	return ret;
}

/*! \throw no throw */
bool CmdLineParser::getVarStrings( basar::ConstString paramName, std::vector<basar::VarString> &value ) const
{
	METHODNAME_DEF( CmdLineParser, getVarStrings )
	BLOG_TRACE_METHOD( m_Logger, fun );

	int index = m_ArgumentList.indexOf( paramName );
	bool ret = ( -1 != index );

	if( ret )
	{
		index++;
		if( index < m_ArgumentList.count() )
		{
			do
			{
				value.push_back( m_ArgumentList[ index ].toLatin1().data() );
				index++;
			}
			while( index < m_ArgumentList.count() );
		}
		else
		{
			ret = false;
		}
	}

	return ret;
}

/*! \throw no throw */
bool CmdLineParser::isParam( basar::ConstString paramName ) const
{
	METHODNAME_DEF( CmdLineParser, isParam )
	BLOG_TRACE_METHOD( m_Logger, fun );
	bool ret = ( -1 != static_cast<basar::Int32>( m_ArgumentList.indexOf( paramName ) ) );
	return ret;
}

/*! \throw no throw */
basar::VarString CmdLineParser::applicationFilePath() const
{
	METHODNAME_DEF( CmdLineParser, applicationFilePath )
	BLOG_TRACE_METHOD( m_Logger, fun );

	return QCoreApplication::applicationFilePath().toLocal8Bit().constData();
}

/*! \throw no throw */
bool CmdLineParser::getValOfParam( basar::ConstString paramName, basar::VarString &value ) const
{
	METHODNAME_DEF( CmdLineParser, getValOfParam )
	BLOG_TRACE_METHOD( m_Logger, fun );

	basar::Int32 index = static_cast<basar::Int32>( m_ArgumentList.indexOf( paramName ) );  
	bool ret = ( -1 != index );

	std::string test = m_ArgumentList.at(1).toStdString();

	if( ret )
	{
		index++;
		if( index < m_ArgumentList.count() )
		{
			value = m_ArgumentList[ index ].toLatin1().data();
		}
		else
		{
			ret = false;
		}
	}

	return ret;
}

/*! \throw no throw */
CmdLineParser::operator const basar::VarString() const
{
    METHODNAME_DEF( CmdLineParser, (operator const basar::VarString()) )
	BLOG_TRACE_METHOD( m_Logger, fun );

    std::stringstream ss; ss << "\"" << m_ArgumentList.join( "\" \"" ).toLatin1().data() << "\"";
	return ss.str().c_str();
}
/*! \throw no throw */
bool CmdLineParser::existArguments() const
{
    METHODNAME_DEF( CmdLineParser, existArguments )
	BLOG_TRACE_METHOD( m_Logger, fun );

    return 1 < m_ArgumentList.count();
}

} // end namespace cmdLine
} // end namespace libBatch

