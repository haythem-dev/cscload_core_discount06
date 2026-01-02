#ifndef GUARD_LIBCSC_CREMA_GUIDATASQL_H
#define GUARD_LIBCSC_CREMA_GUIDATASQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace crema {

class GuiDataSql
{
public:
    ~GuiDataSql();

    static const basar::VarString getGuiDataQuery(const basar::Int16 branchNo, const basar::Int32 orderNo);

private:
    GuiDataSql();
    GuiDataSql& operator=(const GuiDataSql&);
};

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_GUIDATASQL_H
