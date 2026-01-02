//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBCSC_UTILS_XMLCONFIGREADERPTR_H
#define GUARD_LIBCSC_UTILS_XMLCONFIGREADERPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_utils
{    
	class XmlConfigReader;
    typedef boost::shared_ptr<libcsc_utils::XmlConfigReader> XmlConfigReaderPtr;
}

#endif // GUARD_LIBCSC_UTILS_XMLCONFIGREADERPTR_H
