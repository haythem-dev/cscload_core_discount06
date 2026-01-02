#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVROW_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVROW_H

#include <sstream>
#include <vector>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc_deli
{
namespace infrastructure
{
namespace csv
{

    class CSVRow
    {
	    friend std::istream& operator >> ( std::istream& str, csv::CSVRow& data );
	    friend std::ostream& operator << ( std::ostream& str, const csv::CSVRow& data );

    public:
	    explicit CSVRow( const char seperator ) : m_Seperator( seperator )
	    {
	    }

	    const basar::VarString& operator [] ( std::size_t index ) const
	    {
		    return m_Data[index];
	    }

	    std::size_t size() const
	    {
		    return m_Data.size();
	    }

	    bool empty() const
	    {
		    return m_Data.empty();
	    }

	    typedef std::vector<basar::VarString> RowData;
	    void setData( const RowData& data )
	    {
		    m_Data = data;
	    }

	    void insert( const basar::VarString& );
        void insert( const basar::Int32      );

	    typedef RowData::const_iterator iterator;
	    iterator begin() const
	    {
		    return m_Data.begin();
	    }

	    iterator end() const
	    {
		    return m_Data.end();
	    }

    private:
	    void readNextRow( std::istream& );

    private:
	    CSVRow& operator = ( const CSVRow& );

    private:
	    const char                  m_Seperator;
	    RowData                     m_Data;
    };

} // end namespace csv
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVROW_H
