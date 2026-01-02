#include "kscclient_version.h"

#ifdef NDEBUG
#define PROJECTCONFIG	"rel"
#else
#define PROJECTCONFIG	"dbg"
#endif

const char versioninfo[] = "@(#) kscclient " KSCCLIENT_VERSION " " PROJECTCONFIG;
