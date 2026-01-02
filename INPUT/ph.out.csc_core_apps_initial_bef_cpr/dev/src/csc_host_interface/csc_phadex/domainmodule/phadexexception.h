#ifndef GUARD_CSC_PHADEX_PHADEX_EXCEPTION_H
#define GUARD_CSC_PHADEX_PHADEX_EXCEPTION_H

#include <libbasarcmnutil_exceptions.h>

namespace csc_phadex
{
namespace exception
{
    class PhadexException : public basar::Exception
    {
        public:
            /*! \brief std constructor */
            PhadexException( const basar::ExceptInfo& sInfo )
            : basar::cmnutil::BasarException( sInfo, "PhadexException" )
            {};

            /*! \brief std-destructor */
            ~PhadexException(){};

        private:
            //!< forbidden
            PhadexException();
    };

} // end namespace exception
} // end namespace csc_phabor

#endif // GUARD_CSC_PHADEX_PHADEX_EXCEPTION_H


