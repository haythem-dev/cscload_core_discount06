#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVFILEEXCEPTION_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVFILEEXCEPTION_H

#include <libutil/exception.h>

namespace libcsc_deli
{
namespace infrastructure
{
namespace csv
{

    class CSVFileException : public libutil::exceptions::BaseException
    {
    public:
	    CSVFileException( const basar::ExceptInfo & );
	    virtual ~CSVFileException();

    private:
	    //forbidden
	    CSVFileException();
    };

} //end namespace csv
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CSV_CSVFILEEXCEPTION_H
