#include "csvrow.h"

namespace libcsc_deli
{
namespace infrastructure
{
namespace csv
{
    std::istream& operator >> ( std::istream& str, csv::CSVRow& data )
    {
        data.readNextRow( str );
        return str;
    }

    std::ostream& operator << ( std::ostream& str, const csv::CSVRow& data )
    {
	    if( ! data.empty() )
        {
            csv::CSVRow::iterator i = data.begin();
		    str << *i;
            ++i;
		    for( ; i != data.end(); ++i )
            {
			    str << data.m_Seperator << *i;
		    }
	    }

	    return str;
    }

    void CSVRow::readNextRow( std::istream& str )
    {
	    try {
		    std::string line;
		    std::getline( str, line );

		    std::stringstream lineStream( line );
		    std::string cell;

		    m_Data.clear();
		    while( std::getline( lineStream, cell, m_Seperator ) )
            {
			    m_Data.push_back( cell.c_str() );
            }
	    } 
        catch( std::exception& )
        {
		    // avoid throwing error on EOF
		    if( !str.eof() )
            {
			    throw;
            }
	    }
    }

    void CSVRow::insert( const basar::VarString& data )
	{
		m_Data.push_back( data );
	}
    
    void CSVRow::insert( const basar::Int32 number )
    {
        basar::VarString data;
        data.itos( number );

        insert( data );
    }

} // end namespace csv
} // end namespace infrastructure
} // end namespace libcsc_deli
