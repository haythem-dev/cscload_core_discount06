
/* Error  -33020  on esqlc-compiling tpldzentknd.ec */

#include "libtpld/struct.h"
#include "libtpld/cobolbuf.h"

static struct AUFB aufb[] = { DKKUL_SATZ };

struct AUFB* GetDkkulSatz()
{
    return aufb;
}

int GetDkkulSatzanzahl()
{
    return SATZANZAHL( aufb );
}
