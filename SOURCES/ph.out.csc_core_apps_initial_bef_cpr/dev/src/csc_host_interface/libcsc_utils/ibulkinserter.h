#ifndef GUARD_DOMMOD_IBULK_INSERTER_H
#define GUARD_DOMMOD_IBULK_INSERTER_H

#include <libbasarcmnutil_bstring.h>

namespace domMod 
{		
namespace util
{
class IBulkInserter
{
public:
	virtual ~IBulkInserter() {} 

	virtual void init() = 0;
	virtual void insert(
		const basar::VarString & sql
			) = 0;
	virtual void finish() = 0;
}; 

} // namespace util
} // namespace domMod

#endif // GUARD_DOMMOD_IBULK_INSERTER_H

