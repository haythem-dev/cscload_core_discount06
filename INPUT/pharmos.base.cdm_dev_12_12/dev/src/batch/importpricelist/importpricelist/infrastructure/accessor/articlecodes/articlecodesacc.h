//-------------------------------------------------------------------------------------------------//
/*! \file	articlecodesacc.h
*   \brief	Accessor for article code.
*   \author NTT DATA
*   \date	14.02.2022
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_ARTICLECODESACC_H
#define GUARD_ARTICLECODESACC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasardbaspect_macros.h>
#include <libbasardbaspect_definitions.h>
#include <libbasardbaspect_sqlstringbuilder.h>

//-------------------------------------------------------------------------------------------------//
// sqlstring builder declaration section
//-------------------------------------------------------------------------------------------------//
namespace importpricelist
{
	namespace infrastructure
	{
		namespace accessor
		{
			namespace articlecodes
			{
				namespace lit
				{
					const basar::VarString ArticleCodesAcc("ArticleCodesAcc");
					const basar::VarString SelectArticleNoByCodeAndType("SelectArticleNoByCodeAndType");
				}

				BEGIN_QUERY_BUILDER_DECLARATION(SelectArticleNoByCodeAndType)
				END_BUILDER_DECLARATION
			} // end namespace articlecodes
		} // end namespace accessor
	} // end namespace infrastructure
} // end namespace importpricelist

#endif // GUARD_ARTICLECODESACC_H

