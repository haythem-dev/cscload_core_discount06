#ifndef GUARD_LIBCSC_STOCKBOOKING_LONGTERMLACK_REPOSITORY_H
#define GUARD_LIBCSC_STOCKBOOKING_LONGTERMLACK_REPOSITORY_H

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// include section
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ilongtermlackdeleter.h"
#include "ilongtermlackchecker.h"

#include <libbasar_definitions.h>
#include <persistence/iaccessorptr.h>
#include <persistence/isqlparameterbinderptr.h>


namespace libcsc {
namespace stockbooking {

    class LongTermLackRepository : public ILongTermLackDeleter, public ILongTermLackChecker
    {
        public:
            LongTermLackRepository();
            virtual ~LongTermLackRepository();

            virtual void                deleteLongTermLack(const basar::Int32 articleNo);
            virtual bool                isLongTermLack(const basar::Int32 articleNo) const;

	        virtual void                injectCheckerLongTermLackAccessor( persistence::IAccessorPtr );
	        virtual void                injectDeleteLongTermLackAccessor( persistence::IAccessorPtr );

        private:
            LongTermLackRepository( const LongTermLackRepository& );
            LongTermLackRepository& operator=( const LongTermLackRepository& );

            //////////////////////////////////////////////////////////////////
            // private member variables
            //////////////////////////////////////////////////////////////////
            persistence::IAccessorPtr   m_DeleteLongTermLackAccessor;
            persistence::IAccessorPtr   m_CheckerLongTermLackAccessor;
    };

} // end namespace stockbooking
} // end namespace libcsc

#endif

