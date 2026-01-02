//-------------------------------------------------------------------------------------------------//
/*! \file	articleacc.h
*   \brief	Accessor for article data.
*   \author NTT DATA
*   \date	18.10.2022
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_ARTICLEACC_H
#define GUARD_ARTICLEACC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

//-------------------------------------------------------------------------------------------------//
// sqlstring builder declaration section
//-------------------------------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
	namespace infrastructure
	{
		namespace accessor
		{
			namespace article
			{
				namespace lit
				{
					const basar::VarString ArticleAcc("ArticleAcc");
					const basar::VarString SelectArticles("SelectArticles");
				}

				BEGIN_QUERY_BUILDER_DECLARATION(SelectArticles)
				END_BUILDER_DECLARATION
			} // end namespace article
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace subsequentdeliveryrelevantcalculator

#endif // GUARD_ARTICLEACC_H

