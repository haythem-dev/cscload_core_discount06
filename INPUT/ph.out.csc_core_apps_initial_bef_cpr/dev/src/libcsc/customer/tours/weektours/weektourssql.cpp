#include <customer/tours/weektours/weektourssql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
    namespace customer {

        WeekToursSql::WeekToursSql()
        {
        }

        WeekToursSql::~WeekToursSql()
        {
        }

        const basar::VarString WeekToursSql::getAllCustomerToursForWeekQuery(const basar::Int16 branchNo, const basar::Int32 customerNo)
        {
            std::stringstream sSql;
            sSql <<
                "select "
                "tptw.tourid, "
                "tptw.weekday, "
                "tptw.fahrtzeit, "
                "tptw.kdauftragart as ordertype, "
                "tptw.istverbundtour as isibttour, "
                "tptw.isbtm as isbtmtour, "
                "tptw.iskk as iskktour, "
                "tptw.isk08 as isk08tour, "
                "tptw.isk20 as isk20tour, "
                "tptw.returnstour as isreturnstour, "
                "NVL(opt.fromtime,0) as orderperiodfromtime, "
                "NVL(opt.totime,0) as orderperiodtotime, "
                "NVL(opt.maintime,0) as orderperiodmaintime "
                "from tourplantagwoche tptw "
                "left join orderperiod op on op.branchno = tptw.vertriebszentrumnr and op.customerno = tptw.kundennr and op.tourid = tptw.tourid and op.weekday = tptw.weekday "
                "left join orderperiodtime opt on opt.order_period_id = op.id "
                "where vertriebszentrumnr = " << branchNo << " "
                "and kundennr = " << customerNo << "; ";

            return sSql.str();
        }

    } // end namespace customer
} // end namespace libcsc
