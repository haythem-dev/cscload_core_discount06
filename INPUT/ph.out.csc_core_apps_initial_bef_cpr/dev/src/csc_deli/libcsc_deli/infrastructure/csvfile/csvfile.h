#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVFILE_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVFILE_H

#include <fstream>

#include "csviterator.h"
#include "csvrow.h"

namespace libcsc_deli
{
namespace infrastructure
{
namespace csv
{

    class CSVFile
    {
    public:
        CSVFile( const basar::VarString& fileName, const char separator = ',', bool createNewFile = false );
        ~CSVFile();

	    typedef CSVIterator iterator;
	    iterator       begin();
	    iterator       end();

	    void           createHeadings( const CSVRow& headings );
	    void           withHeadings(); // call this if CSV file has headings
	    CSVRow         getHeadings();

	    void           append( const CSVRow& row );
	    char           separator() const;
	    std::size_t    colCount() const;

	    std::streamoff fileSize();
	    bool           empty();  // file empty?
        bool           exists(); // does file exist?

    private:
        // forbidden
        CSVFile(const CSVFile& );
        CSVFile& operator = ( const CSVFile& );

	    std::fstream   m_File;
	    const char     m_Separator;
	    bool           m_hasHeadings;
	    std::size_t    m_Columns;
    };

} // end namespace csv
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVFILE_H
