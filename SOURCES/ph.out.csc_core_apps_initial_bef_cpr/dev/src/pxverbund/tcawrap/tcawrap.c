#include "tcawrap.h"
#include <tcaapi.h>

//------------------------------------------------------------------------------

void initTcaChild()
{
#ifndef WIN32	// initialise tcACCESS shared libraries; needed by forked children processes
	hpbmlchinit();
#endif
}

