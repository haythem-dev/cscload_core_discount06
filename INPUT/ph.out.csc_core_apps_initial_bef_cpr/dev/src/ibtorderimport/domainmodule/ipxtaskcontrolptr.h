#ifndef GUARD_IBTORDERIMPORT_DOMMOD_IPXTASKCONTROLPTR_H
#define GUARD_IBTORDERIMPORT_DOMMOD_IPXTASKCONTROLPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace ibtorderimport {
namespace domMod {

	class IPxTaskControl;
	typedef boost::shared_ptr< IPxTaskControl > IPxTaskControlPtr;    

}
}

#endif // GUARD_IBTORDERIMPORT_DOMMOD_IPXTASKCONTROLPTR_H
