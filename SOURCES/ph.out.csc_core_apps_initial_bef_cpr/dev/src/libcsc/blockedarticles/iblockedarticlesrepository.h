#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_IBLOCKEDARTICLESREPOSITORY_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_IBLOCKEDARTICLESREPOSITORY_H

#include <libbasar_definitions.h>

#include <blockedarticles/blockedarticlesptr.h>

namespace libcsc {
namespace blockedarticles {

	class IBlockedArticlesRepository
	{
	public:
		virtual ~IBlockedArticlesRepository() {}

		virtual BlockedArticlesCollectionPtr findBlockedArticles(basar::Int16 branchNo, basar::Int32 blockID) const = 0;

		virtual void saveBlockedArticle(const BlockedArticlesPtr& blockedArticles) const = 0;
	};

} //blockedarticles
} //libcsc

#endif // !GUARD_LIBCSC_BLOCKEDARTICLES_IBLOCKEDARTICLESREPOSITORY_H
