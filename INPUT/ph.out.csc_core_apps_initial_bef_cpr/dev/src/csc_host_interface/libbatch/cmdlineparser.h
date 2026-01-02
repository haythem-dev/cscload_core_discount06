//---------------------------------------------------------------------------//
/*! \file commandlineparser.h
 *  \brief declaration of class CommandlineParser
 *  \author Dirk Kapusta
 *  \date 21.10.2008
 *  \version 00.00.00.01 first version
 */ //-----------------------------------------------------------------------//
#ifndef GUARD_LIBBATCH_CMDLINE_PARSER_H
#define GUARD_LIBBATCH_CMDLINE_PARSER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <vector>

#ifdef WIN32
	#pragma warning (push)
	#pragma warning(disable: 4127 4189 4244 4251 4311 4312 4511 4512 4800)
	#include <QtCore/QStringList>
	#pragma warning (pop)
#else
	#include <QtCore/QStringList>
#endif


//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace libBatch
{
namespace cmdLine
{

//---------------------------------------------------------------------------//
/*! \brief helper class for parsing command line options
 *  \author Dirk Kapusta
 *  \date 22.09.2008
 *  \version 00.00.00.01 first version
 */ //-----------------------------------------------------------------------//
class CmdLineParser
{
public:
	/*! \brief  Default c'tor
	    \pre QCoreApplication must be instantiated
		\throw CommandlineException */
	CmdLineParser();
	/*! \brief  Default c'tor with commandline arguments \n \throw no-throw */
	CmdLineParser( basar::Int32 argc, char **argv );
	/*! \brief  D'tor \n \throw no-throw */
	~CmdLineParser();

    bool existArguments() const;

	/*! \brief get mandatory basar::VarString \n \throw CommandlineException */
	bool getMandatoryVarString( basar::ConstString paramName, basar::VarString &value ) const;
	/*! \brief get mandatory basar::Int16 \n \throw CommandlineException */
	bool getMandatoryInt16( basar::ConstString paramName, basar::Int16 &value ) const;
	/*! \brief get mandatory basar::Int32 \n \throw CommandlineException */
	bool getMandatoryInt32( basar::ConstString paramName, basar::Int32 &value ) const;
	/*! \brief get mandatory basar::Date \n \throw CommandlineException */
	bool getMandatoryDate( basar::ConstString paramName, basar::Date &value ) const;
	/*! \brief get mandatory basar::DateTime \n \throw CommandlineException */
	bool getMandatoryDateTime( basar::ConstString paramName, basar::DateTime &value ) const;
	/*! \brief get mandatory basar::VarStrings \n \throw CommandlineException */
	bool getMandatoryVarStrings( basar::ConstString paramName, std::vector<basar::VarString> &value ) const;

	/*! \brief get basar::VarString \n \throw no throw */
	bool getVarString( basar::ConstString paramName, basar::VarString &value ) const;
	/*! \brief get basar::Int16 \n \throw no throw */
	bool getInt16( basar::ConstString paramName, basar::Int16 &value ) const;
	/*! \brief get basar::Int32 \n \throw no throw */
	bool getInt32( basar::ConstString paramName, basar::Int32 &value ) const;
	/*! \brief get basar::Date \n \throw no throw */
	bool getDate( basar::ConstString paramName, basar::Date &value ) const;
	/*! \brief get basar::DateTime \n \throw no throw */
	bool getDateTime( basar::ConstString paramName, basar::DateTime &value ) const;
	/*! \brief get basar::VarStrings \n \throw no throw */
	bool getVarStrings( basar::ConstString paramName, std::vector<basar::VarString> &value ) const;

	/*! \brief returns true if parameter is set \n \throw no throw */
	bool isParam( basar::ConstString paramName ) const;
	/*! \brief returns application file path including the binarys name \n \throw no throw */
	basar::VarString applicationFilePath() const;

	operator const basar::VarString() const;

protected:
    ////////////////////////////////
    // methods
    ////////////////////////////////
    /*! \brief get value as basar::VarString \n \throw no throw */
	bool getValOfParam( basar::ConstString paramName, basar::VarString &value ) const;

    ////////////////////////////////
    // variables
    ////////////////////////////////
	QStringList		            m_ArgumentList;

private:
    ////////////////////////////////
    // methods
    ////////////////////////////////
	CmdLineParser( const CmdLineParser & r );
	CmdLineParser &	operator = ( const CmdLineParser & r );

    ////////////////////////////////
    // variables
    ////////////////////////////////
    const log4cplus::Logger&    m_Logger;
};

} // end namespace cmdLine
} // end namespace libBatch

#endif // end GUARD_LIBBATCH_CMDLINE_PARSER_H
