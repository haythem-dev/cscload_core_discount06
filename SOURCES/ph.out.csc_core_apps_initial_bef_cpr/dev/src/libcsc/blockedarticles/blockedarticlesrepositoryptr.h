#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESREPOSITORYPTR_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESREPOSITORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace blockedarticles {

	class BlockedArticlesRepository;
	typedef boost::shared_ptr<BlockedArticlesRepository> BlockedArticlesRepositoryPtr;

} // namespace blockedarticles
} // namespace libcsc

#endif // GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESREPOSITORYPTR_H
