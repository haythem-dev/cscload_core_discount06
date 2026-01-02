//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  convenience macros for logging YIterator
 *  \author Bjoern Bischof
 *  \date   25.05.2010
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_LOG_MACROS_H
#define GUARD_LOG_MACROS_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <sstream>
#include <iomanip>

//----------------------------------------------------------------------------//
// define declaration section
//----------------------------------------------------------------------------// 

#ifdef NDEBUG
	#define CHECK_EXECUTABILITY( yit, logger, fun ) void()
#else
	#define CHECK_EXECUTABILITY( yit, logger, fun )           \
			{                                                 \
				if( !executable ){                            \
					std::stringstream os;                     \
					os << std::endl << fun << ": ";           \
					if( yit.isNull() ){                       \
						os << "YIterator is Null()!";         \
					} else if( yit.isEnd() ){                 \
						os << "YIterator is end()!";          \
					} else {                                  \
						yit.toStream( os );                   \
					}                                         \
					BLOG_DEBUG( logger, os.str().c_str() );   \
				}                                             \
			}
#endif // NDEBUG
    
#endif // GUARD_LOG_MACROS_H
