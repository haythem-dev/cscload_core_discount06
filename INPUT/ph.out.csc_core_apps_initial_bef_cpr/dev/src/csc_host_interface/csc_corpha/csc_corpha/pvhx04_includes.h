#ifndef PVHX04_INCLUDES_H
#define PVHX04_INCLUDES_H

#include "pxxmit.hpp"
#include "pxtaskcl.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include "string.hpp"
#include "pxnarctransfer.hpp"
#include "pxordercalcmode.hpp"
#include "pxorderposcalcmode.hpp"
#include "pxorderprolink.hpp"
#include "pxstkrev.hpp"
#include "pxorderposchange.hpp"
#include "pxoeparm.hpp"
#include "types/origintypeenum.inc"

#ifndef WIN32
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#endif

enum TransactionLevel{ SINGLE_RECORD, MULTI_RECORD };

#endif // PVHX04_INCLUDES_H
