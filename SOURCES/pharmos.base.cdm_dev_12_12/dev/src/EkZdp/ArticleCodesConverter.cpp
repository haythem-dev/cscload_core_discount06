/******************************************************************************/
/**                                                                           */
/**   Author : J. Machata PRZ GmbH											  */
/**   Date   : 17.11.2010                                                     */
/**                                                                           */
/******************************************************************************/

#include "stdafx.h"
#include "EkZdp.h"
#include "articlecodesconverter.h"

/******************************************************************************/

//-------------------------------------------------------------------------------------------------//
CArticleCodesConverter::CArticleCodesConverter( ChDlgEdit& articleCodeEdit, ChDlgEdit& articleNoEdit, CZartikelSelCtrl& selBox )
:	m_CodeEdit	( &articleCodeEdit	),
	m_NoEdit	( &articleNoEdit	),
	m_SelBox	( &selBox			)
{}         

//-------------------------------------------------------------------------------------------------//
CArticleCodesConverter::~CArticleCodesConverter()
{}

//-------------------------------------------------------------------------------------------------//
// find article-no by given code
long CArticleCodesConverter::getArticleNoByCode( CString& code, CString& cErrmld )
{
	code.Trim();
	removeLeadingZeros(code);	

	/*if ( code.IsEmpty() ){
		return RET_CODE_ERROR;
	}*/

	long no = ((CEkZdpApp*) AfxGetApp())->m_LsArticleCodes.getArticleNoByCode( code, cErrmld );

	if ( 0 > no ){
		cErrmld = CResString::ex().getStrTblText(IDS_STRING1232);
	}

	return no;
}

//-------------------------------------------------------------------------------------------------//
// find article-no by code of internal code-control
long CArticleCodesConverter::getArticleNoByCode	( CString& cErrmld )
{
	CString code;
	CodeBufferType codeBuff;

	m_CodeEdit->GetInput(&codeBuff[0]);
	code.Format("%s", codeBuff);

	return getArticleNoByCode ( code, cErrmld );
}

//-------------------------------------------------------------------------------------------------//
// find article-code by given no
CString CArticleCodesConverter::getPreferredCodeByNo ( long no, CString& cErrmld )
{
	return ((CEkZdpApp*) AfxGetApp())->m_LsArticleCodes.getPreferredCodeByArticleNo( no, cErrmld );
}

//-------------------------------------------------------------------------------------------------//
// find article-no by current internal codeEdit-text and set to articleNoEdit
int CArticleCodesConverter::setArticleNoEditCtrl( CString& cErrmld )
{
	if ( m_CodeEdit == 0 ){
		return RET_CODE_ERROR;
	}

	CodeBufferType codeBuff;
	CString code;

	m_CodeEdit->GetInput(&codeBuff[0]);
	
	code.Format("%s", codeBuff);
	return setArticleNoEditCtrl( code, *m_NoEdit, cErrmld );
}

//-------------------------------------------------------------------------------------------------//
// find article-no by articleCode and set to articleNoEdit
int CArticleCodesConverter::setArticleNoEditCtrl( const CString& articleCode, ChDlgEdit& articleNoEdit, CString& cErrmld )
{
	int ret = RET_CODE_OK;

	CString code (articleCode);
	code.Trim();

	/*if ( code.IsEmpty() ){
		ret = RET_CODE_ERROR;
	}*/

	long no = getArticleNoByCode( code, cErrmld );

	if ( 0 > no ){
		ret = RET_CODE_ERROR;
	}

	CString strNo;
	strNo.Format("%ld", no);

	articleNoEdit.SetWindowText( strNo );

	return ret;
}

//-------------------------------------------------------------------------------------------------//
// set article-code from actual record in selBox to given buffer of article-code-control
int CArticleCodesConverter::setArticleCodeEditCtrl( CZartikelSelCtrl& selBox, char* articleCodeCtrlBuffer )
{
	CString code;
	selBox.CodeOfActualRecord(code);
	strcpy (articleCodeCtrlBuffer, code);

	return RET_CODE_OK;
}

//-------------------------------------------------------------------------------------------------//
// set article-code from actual record in selBox to buffer and windowtext of given control
int CArticleCodesConverter::setArticleCodeEditCtrl()
{
	if ( m_CodeEdit == 0 || m_SelBox == 0 ){
		return RET_CODE_ERROR;
	}

	CString code;
	CodeBufferType codeBuff;

	setArticleCodeEditCtrl( *m_SelBox, &codeBuff[0] );
	code.Format("%s", codeBuff);

	code.Trim();
	m_CodeEdit->SetWindowText( code );
	m_CodeEdit->SetInput( code.GetBuffer() );

	return RET_CODE_OK;
}

//-------------------------------------------------------------------------------------------------//
// set preferred article-code from actual text in given no-ctrl
int CArticleCodesConverter::setPreferredArticleCodeEditCtrl( ChDlgEdit& noCtrl, ChDlgEdit& codeCtrl )
{
	CString code;
	CString cErrmld;
	CString sNo;
	long no;
	int ret = RET_CODE_OK;

	noCtrl.p_SetInput();
	noCtrl.GetWindowText( sNo );
	no = atol( sNo );

	code = CArticleCodesConverter::getPreferredCodeByNo( no, cErrmld );

	codeCtrl.SetWindowText( code );
	codeCtrl.SetInput( code.GetBuffer() );
	codeCtrl.p_GetInput();

	if ( code == "-1" ){
		ret = RET_CODE_ERROR;
	}

	return ret;	
}

//-------------------------------------------------------------------------------------------------//
// set preferred article-code from actual text in internal no-ctrl
int CArticleCodesConverter::setPreferredArticleCodeEditCtrl()
{
	return setPreferredArticleCodeEditCtrl( *m_NoEdit, *m_CodeEdit );
}

//-------------------------------------------------------------------------------------------------//
// returns internal no-edit control which was overhanded in c'tor
ChDlgEdit& CArticleCodesConverter::getArticleNoEditCtrl()
{
	return *m_NoEdit;
}

//-------------------------------------------------------------------------------------------------//
// returns internal code-edit control which was overhanded in c'tor
ChDlgEdit& CArticleCodesConverter::getArticleCodeEditCtrl()
{
	return *m_CodeEdit;
}
//-------------------------------------------------------------------------------------------------//
// removing all zeros at the beginning of given string ( e.g. 0020209 -> 20209 )
void CArticleCodesConverter::removeLeadingZeros( CString& str )
{
	while( str[0] == '0' ){
		str.Delete(0);
	}	
}
