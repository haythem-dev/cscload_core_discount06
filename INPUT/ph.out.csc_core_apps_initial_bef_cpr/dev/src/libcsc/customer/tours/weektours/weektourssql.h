#ifndef GUARD_LIBCSC_CUSTOMER_WEEKTOURSSQL_H
#define GUARD_LIBCSC_CUSTOMER_WEEKTOURSSQL_H

#include <string>
#include <libbasar_definitions.h>

namespace libcsc {
    namespace customer {

        class WeekToursSql
        {
        public:
            ~WeekToursSql();

            // Create your SQL statement getters here ...
            // e.g.:
            static const basar::VarString getAllCustomerToursForWeekQuery(const basar::Int16 branchNo, const basar::Int32 customerNo);

        private:
            WeekToursSql();
            WeekToursSql& operator=(const WeekToursSql&);
        };

    } // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_WEEKTOURSSQL_H
