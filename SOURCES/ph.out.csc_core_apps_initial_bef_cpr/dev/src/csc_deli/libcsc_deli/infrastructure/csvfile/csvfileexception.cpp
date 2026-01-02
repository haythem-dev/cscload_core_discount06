#include "csvfileexception.h"

namespace libcsc_deli
{
namespace infrastructure
{
namespace csv
{

CSVFileException::CSVFileException( const basar::ExceptInfo & sInfo)
: BaseException( sInfo, "CSVFileException" )
{
}

CSVFileException::~CSVFileException()
{
}

} //end namespace csv
} // end namespace infrastructure
} // end namespace libcsc_deli
