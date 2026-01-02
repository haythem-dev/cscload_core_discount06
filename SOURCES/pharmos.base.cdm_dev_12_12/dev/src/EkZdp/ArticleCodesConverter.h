/******************************************************************************/
/**                                                                           */
/**   Author : J. Machata PRZ GmbH											  */
/**   Date   : 17.11.2010                                                     */
/**                                                                           */
/******************************************************************************/
#ifndef __ARTICLECODESCONVERTER_H__
#define __ARTICLECODESCONVERTER_H__

#include <voodoo_table_header/carticlecodes.h>
#include <phxlib/ZArtikelSelCtrl.h>

#include "stdafx.h"

/******************************************************************************/
class CArticleCodesConverter
{
public:	

	CArticleCodesConverter	( ChDlgEdit& articleCodeEdit, ChDlgEdit& articleNoEdit, CZartikelSelCtrl& selBox );      
	~CArticleCodesConverter	();

	///////////////////////////////////////////
	// FINDS 
	///////////////////////////////////////////

	// find article-no by given code
	static long getArticleNoByCode		( CString& code, CString& cErrmld );

	// find article-no by code of internal code-control
	long getArticleNoByCode				( CString& cErrmld );

	// find article-code by given no
	static CString getPreferredCodeByNo	( long no, CString& cErrmld );

	///////////////////////////////////////////
	// ARTICLENO SETTER
	///////////////////////////////////////////

	// find article-no by current internal codeEdit-text and set to articleNoEdit
	int setArticleNoEditCtrl		( CString& cErrmld );

	// find article-no by articleCode and set to articleNoEdit
	static int setArticleNoEditCtrl	( const CString& articleCode, ChDlgEdit& articleNoEdit, CString& cErrmld );

	///////////////////////////////////////////
	// ARTICLECODE SETTER
	///////////////////////////////////////////

	// set article-code from actual record in selBox to given buffer of article-code-control
	static int setArticleCodeEditCtrl	( CZartikelSelCtrl& selBox, char* articleCodeCtrlBuffer );

	// set article-code from actual record in internal selBox to windowtext of internal code-control
	int setArticleCodeEditCtrl			();

	// set preferred article-code from actual text in given no-ctrl
	static int setPreferredArticleCodeEditCtrl( ChDlgEdit& noCtrl, ChDlgEdit& codeCtrl );

	// set preferred article-code from actual text in internal no-ctrl
	int setPreferredArticleCodeEditCtrl();

	///////////////////////////////////////////
	// GETTER
	///////////////////////////////////////////

	// returns internal no-edit control which was overhanded in c'tor
	ChDlgEdit& getArticleNoEditCtrl();

	// returns internal code-edit control which was overhanded in c'tor
	ChDlgEdit& getArticleCodeEditCtrl();

private:

	typedef char CodeBufferType[L_CARTICLECODES_ARTICLE_CODE + 1];

	CArticleCodesConverter(const CArticleCodesConverter& rhs);
    CArticleCodesConverter& operator= (const CArticleCodesConverter& rhs);

	// removing all zeros at the beginning of given string ( e.g. 0020209 -> 20209 )
	static void removeLeadingZeros( CString& str );

	ChDlgEdit*			m_CodeEdit;
	ChDlgEdit*			m_NoEdit;
	CZartikelSelCtrl*	m_SelBox;

	static const int RET_CODE_ERROR = -1;
	static const int RET_CODE_OK	=  0;

};

#endif 
