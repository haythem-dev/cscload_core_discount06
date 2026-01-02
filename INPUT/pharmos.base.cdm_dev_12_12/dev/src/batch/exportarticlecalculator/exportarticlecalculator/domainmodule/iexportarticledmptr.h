#ifndef GUARD_DOMMOD_EXPORTARTICLE_IEXPORTARTICLEDMPTR_H
#define GUARD_DOMMOD_EXPORTARTICLE_IEXPORTARTICLEDMPTR_H

#include <boost/shared_ptr.hpp>

namespace exportarticlecalculator {
namespace domMod {
namespace exportarticle {

	class IExportArticleDM;
	typedef boost::shared_ptr< IExportArticleDM > IExportArticleDMPtr;

}
}
}

#endif // GUARD_DOMMOD_EXPORTARTICLE_IEXPORTARTICLEDMPTR_H
