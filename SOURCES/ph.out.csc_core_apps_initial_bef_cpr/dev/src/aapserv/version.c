#include "pxverbund_version.h"

#define PROJECTNAME		"zaapunix"

#ifdef NDEBUG
#define PROJECTCONFIG	"rel"
#else
#define PROJECTCONFIG	"dbg"
#endif

const char versioninfo[] = "@(#)" PROJECTNAME " v " CSC_CORE_APPLICATIONS_VERSION " " PROJECTCONFIG;

#include <libbasar_pkgversion.h>

const char BASAR_versioninfo[] = "@(#)" PRODUCT_NAME " v " PRODUCT_MAJORNO "."PRODUCT_MINORNO "." PRODUCT_EXTENSION "." PRODUCT_BUILDNO PRODUCT_CONFIG;
