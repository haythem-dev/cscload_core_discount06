#include "version.h"

#ifdef NDEBUG
#define PROJECTCONFIG	"rel"
#else
#define PROJECTCONFIG	"dbg"
#endif

const char versioninfo[] = "@(#) kscclientwrapper " KSCCLIENTWRAPPER_VERSION " " PROJECTCONFIG;
