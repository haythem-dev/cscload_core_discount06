#include "csvfile.h"
#include "csvfileexception.h"
#include <exception>

namespace libcsc_deli
{
namespace infrastructure
{
namespace csv
{

    CSVFile::CSVFile( const basar::VarString& fileName, const char separator, bool createNewFile ) :
	    m_Separator( separator ), m_hasHeadings( false ), m_Columns( 0 )
    {
        m_File.open( fileName.c_str(), std::fstream::in );
	    if( m_File.is_open() )
	    {
            if( createNewFile ) // we want to create a new file but there's already one
            {
                m_File.close();
                std::remove( fileName.c_str() ); // remove it and open again
                m_File.open( fileName.c_str(), std::ios::out );
            }
            else
            {
                // read column count from first line in file
                // Notice: this class assumes that each file's row has exactly the same count
		        m_Columns = begin()->size();
            }
	    }
        else
        {
            if( createNewFile )
            {
                // file doesn't exist yet, so create one
		        m_File.clear();
		        m_File.open( fileName.c_str(), std::ios::out );
            }
	    }

	    m_File.exceptions( std::ios::failbit | std::ios::badbit );
    }

    CSVFile::~CSVFile()
    {
	    m_File.close();
    }

    CSVIterator CSVFile::begin()
    {
	    m_File.clear();
	    m_File.seekg( 0, std::ios::beg );

	    CSVIterator iterator( m_File, separator() );
	    if( m_hasHeadings )
        {
		    ++iterator;
        }

	    return iterator;
    }

    CSVIterator CSVFile::end()
    {
	    return CSVIterator( separator() );
    }

    void CSVFile::append( const CSVRow& row )
    {
	    // Set column count to row column count if file is empty.
	    // After row count has been set this function isn't allowed to
	    // be called with rows which size doesn't match row count.
	    if( m_Columns == 0 && ! row.empty() )
        {
		    m_Columns = row.size();
        }

	    try {
		    if( row.size() == m_Columns )
            {
			    m_File.seekg( 0, std::ios::end );
                m_File << row << std::endl;
		    }
            else
            {
			    throw CSVFileException( basar::ExceptInfo( "CSVFile::append",
					    "row.size() doesn't match column count", __FILE__, __LINE__ ) );
		    }
	    } 
        catch (std::exception& e)
        {
		    throw CSVFileException( basar::ExceptInfo( "CSVFile::append", e.what(), __FILE__, __LINE__ ) );
	    }
    }

    void CSVFile::withHeadings()
    {
	    m_hasHeadings = true;
    }

    char CSVFile::separator() const
    {
	    return m_Separator;
    }

    void CSVFile::createHeadings( const CSVRow& headings )
    {
	    try {
		    if( m_Columns == 0 && ! m_hasHeadings )
            {
			    m_File << headings << std::endl;
			    m_hasHeadings = true;
		    }
            else
            {
			    basar::VarString msg = "Cannot create headings for existing, non-empty file";
			    throw CSVFileException( basar::ExceptInfo( "CSVFile::createHeadings", msg, __FILE__, __LINE__ ) );
		    }
	    } catch( std::exception& e ) {
		    throw CSVFileException( basar::ExceptInfo( "CSVFile::createHeadings", e.what(), __FILE__, __LINE__ ) );
	    }
    }

    CSVRow CSVFile::getHeadings()
    {
	    if( ! m_hasHeadings )
        {
		    basar::VarString msg = "CSV file has no headings";
		    throw CSVFileException( basar::ExceptInfo( "CSVFile::getHeadings",msg, __FILE__, __LINE__ ) );
	    }

	    CSVRow row( separator() );
	    m_File.seekg( 0, std::ios::beg );
	    m_File >> row;

	    return row;
    }

    std::size_t CSVFile::colCount() const
    {
	    return m_Columns;
    }

    std::streamoff CSVFile::fileSize()
    {
	    m_File.seekg( 0, std::ios_base::beg );
	    std::streamoff begin_pos = m_File.tellg();
	    m_File.seekg( 0, std::ios_base::end );

	    return m_File.tellg() - begin_pos;
    }

    bool CSVFile::empty()
    {
	    return fileSize() == 0;
    }

    bool CSVFile::exists()
    {
        return m_File.is_open();
    }

} //end namespace csv
} // end namespace infrastructure
} // end namespace libcsc_deli
