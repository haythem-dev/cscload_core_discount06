#ifndef GUARD_PVHX01_INCLUDES_H
#define GUARD_PVHX01_INCLUDES_H


#include <pxxmit.hpp>
#include <pxartbas.hpp>
#include <pxcstbas.hpp>
#include <pxorder.hpp>
#include <pxstkrev.hpp>
#include <pxartsto.hpp>
#include <pxdealervolume.hpp>  //for recordtypedealervolumneelectronic
#include <pxnarctransfer.hpp> //for narcotics
#include <pxtaskcl.hpp>
#include <pxstockentry.hpp>
#include <pxgoodsdeldefs.h>
#include <pxorderposchange.hpp>//for recordtypechangeorderitem
#include <pxartoldprice.hpp> //for recordtypechangearticledetails
#include <pxartprc.hpp> //for recordtypechangearticledetails
#include <csignal>
#include <pxtenderprogress.hpp>
#include <pxoeparm.hpp>
#include <pxcstot.hpp>
#include <pxdebitlimit.hpp>
#include <pxstockbooking.hpp>
#include <pxorderremarks.hpp>
#include <articleaccountinfo.hpp>

#ifndef WIN32
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>	    
#endif

#include "pxvbdbconnection.h"
#include "pxvbsession.h"
#include "pxordertransmitptr.h"
#include "pxorderentryparamptr.h"
#include "pxtoteinfo.hpp"

#endif



