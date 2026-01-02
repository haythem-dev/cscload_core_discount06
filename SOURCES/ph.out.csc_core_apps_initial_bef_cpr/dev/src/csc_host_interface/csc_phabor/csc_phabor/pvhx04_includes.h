#ifndef GUARD_PVHX04_INCLUDES_H
#define GUARD_PVHX04_INCLUDES_H


	    #include <date.hpp>
	    #include <database.hpp>
	    #include <pxxmit.hpp>
		#include <pxoclpar.hpp>
	    #include <pxiartik.hpp>
	    #include <pxorder.hpp>
	    #include <pxstkrev.hpp>
	    #include <pxartsto.hpp>
		#include <pxdealervolume.hpp>  //for recordtypedealervolumneelectronic
		#include <pxnarctransfer.hpp> //for narcotics
	    #include <pxtaskcl.hpp>
	    #include <pxstockentry.hpp>
	    #include <pxgoodsdeldefs.h>
	    #include <pxparameter.hpp>
	    #include <pxarticlecharge.hpp>
		#include <pxorderposchange.hpp>//for recordtypechangeorderitem
        #include <pxartoldprice.hpp> //for recordtypechangearticledetails
        #include <pxartprc.hpp> //for recordtypechangearticledetails
	    #include <csignal>
		#include <pxdellog.hpp>
		#include <pxoeparm.hpp>
		#include <pxstockbooking.hpp>
		#include <types/origintypeenum.inc>
		
#ifndef WIN32
		#include <sys/types.h>
		#include <unistd.h>
		#include <errno.h>	    
#endif // #ifndef WIN32

	    #include "pxvbsession.h"
		#include "pxordertransmitptr.h"
		#include "pxorderentryparamptr.h"


#endif

// svn://denu1s150/marathon/orderentry/lu62/trunk/dev/src/pvhx01

