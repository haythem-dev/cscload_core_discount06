#ifndef GUARD_LIBCSC_CUSTOMER_PAYMENTCONDITIONSSQL_H
#define GUARD_LIBCSC_CUSTOMER_PAYMENTCONDITIONSSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
    namespace customer {

        class PaymentConditionsSql
        {
        public:
            ~PaymentConditionsSql();

            static const basar::VarString GetPaymentConditionsFlagsQuery(const basar::Int16 branchNo,
                const basar::Int32 customerNo);

        private:
            PaymentConditionsSql();
            PaymentConditionsSql& operator=(const PaymentConditionsSql&);
        };

    } // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_PAYMENTCONDITIONSSQL_H