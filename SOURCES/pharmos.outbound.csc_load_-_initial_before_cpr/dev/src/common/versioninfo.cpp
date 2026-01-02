#include "versioninfo.h"
#include "gitversioninfo.h"

#ifdef __cplusplus 
extern "C" {
#endif

void printVersion(const char* programVersion)
{
	std::cout << programVersion << std::endl;
	std::cout << GitVersionInfo::instance() << std::endl;
}

#ifdef __cplusplus 
}
#endif
