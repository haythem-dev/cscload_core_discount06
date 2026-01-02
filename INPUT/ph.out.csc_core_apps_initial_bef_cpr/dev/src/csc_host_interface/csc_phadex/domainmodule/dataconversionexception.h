#ifndef GUARD_CSC_PHADEX_DATACONVERSION_EXCEPTION_H
#define GUARD_CSC_PHADEX_DATACONVERSION_EXCEPTION_H

#include <libbasarcmnutil_exceptions.h>

namespace csc_phadex
{
namespace exception
{
    class DataConversionException : public basar::Exception
    {
        public:
            /*! \brief std constructor */
            DataConversionException( const basar::ExceptInfo& sInfo )
            : basar::cmnutil::BasarException( sInfo, "DataConversion" )
            {};

            /*! \brief std-destructor */
            ~DataConversionException(){};

        private:
            //!< forbidden
            DataConversionException();
    };

} // end namespace exception
} // end namespace csc_phabor

#endif // GUARD_CSC_PHADEX_DATACONVERSION_EXCEPTION_H


