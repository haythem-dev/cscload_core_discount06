#ifndef GUARD_CSC_PHADEX_UNKNOWNRECORDTYPE_EXCEPTION_H
#define GUARD_CSC_PHADEX_UNKNOWNRECORDTYPE_EXCEPTION_H

#include <libbasarcmnutil_exceptions.h>

namespace csc_phadex
{
namespace exception
{
    class UnknownRecordTypeException : public basar::Exception
    {
        public:
            /*! \brief std constructor */
            UnknownRecordTypeException( const basar::ExceptInfo& sInfo )
            : basar::cmnutil::BasarException( sInfo, "UnknownRecordType" )
            {};

            /*! \brief std-destructor */
            ~UnknownRecordTypeException(){};

        private:
            //!< forbidden
            UnknownRecordTypeException();
    };

} // end namespace exception
} // end namespace csc_phabor

#endif // GUARD_CSC_PHADEX_UnknownRecordType_EXCEPTION_H


