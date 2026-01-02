#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_IBLOCKEDARTICLESREPOSITORYPTR_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_IBLOCKEDARTICLESREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace blockedarticles {

	class IBlockedArticlesRepository;

	typedef boost::shared_ptr<IBlockedArticlesRepository> IBlockedArticlesRepositoryPtr;

} // namespace blockedarticles
} // namespace libcsc

#endif // GUARD_LIBCSC_BLOCKEDARTICLES_IBLOCKEDARTICLESREPOSITORYPTR_H
