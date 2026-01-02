#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESTPTR_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESTPTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace blockedarticles {

	class BlockedArticles;

	typedef boost::shared_ptr<BlockedArticles> BlockedArticlesPtr;

	typedef std::list<BlockedArticlesPtr> BlockedArticlesCollection;

	typedef boost::shared_ptr<BlockedArticlesCollection> BlockedArticlesCollectionPtr;

} // namespace blockedarticles
} // namespace libcsc

#endif // GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESTPTR_H
