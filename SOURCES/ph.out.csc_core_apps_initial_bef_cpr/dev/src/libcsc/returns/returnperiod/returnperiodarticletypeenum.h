#ifndef GUARD_LIBCSC_RETURNS_RETURNPERIOD_ARTICLETYPEENUM_H
#define GUARD_LIBCSC_RETURNS_RETURNPERIOD_ARTICLETYPEENUM_H

namespace libcsc {
namespace returns {

enum ReturnPeriodArticleTypeEnum
{
	RETURN_ARTICLE_DEFAULT = 0,		// Default, gültig für alle Artikel
	RETURN_ARTICLE_COOLCHAIN = 1,	// Gültig für KK - Artikel
	RETURN_ARTICLE_COOL08 = 2,		// Gültig für K8 - Artikel
	RETURN_ARTICLE_COOL20 = 3,		// Gültig für K20 - Artikel
	RETURN_ARTICLE_NARCOTICS = 4,	// Gültig für BTM - Artikel
	RETURN_ARTICLE_GUG = 5			// Gültig für meldepflichtige Artikel
};

} //returns
} //libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNPERIOD_ARTICLETYPEENUM_H
