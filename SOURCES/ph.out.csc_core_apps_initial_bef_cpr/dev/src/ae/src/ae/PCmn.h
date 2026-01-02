/******************************************************************************/
/**                                                                           */
/**   Author : T. Hörath PRZ GmbH                                             */
/**   Date   : 21.06.2004                                                     */
/**                                                                           */
/******************************************************************************/

#pragma once

#include <assert.h>
/*----------------------------------------------------------------------------*/
// Common Library Includes
/*----------------------------------------------------------------------------*/
#include <libsccpattern.h>
/*----------------------------------------------------------------------------*/
// GUI Common Library Includes
/*----------------------------------------------------------------------------*/
#include <libscgmmultilang.h>

using scgui::CResString;
using scgui::CWinAppMultiLang;
using scgui::CFrameWndMultiLang;
using scgui::CFormViewMultiLang;
using scgui::CPropertyPageMultiLang;
using scgui::CPropertySheetMultiLang;
using scgui::CDialogMultiLang;
using scgui::MsgBox1;
using scgui::MsgBox2;

INT_PTR MsgBoxOK(const char* const spMsg, UINT uiType = MB_ICONEXCLAMATION, const char* const spCaption = NULL);
INT_PTR MsgBoxOK(UINT uiMsg, UINT uiType = MB_ICONEXCLAMATION, UINT uiCaption = AFX_IDS_APP_TITLE);
INT_PTR MsgBoxYesNo(const char* const spMsg, UINT uiType = MB_ICONQUESTION | MB_DEFBUTTON2, const char* const spCaption = NULL);
INT_PTR MsgBoxYesNo(UINT uiMsg, UINT uiType = MB_ICONQUESTION | MB_DEFBUTTON2, UINT uiCaption = AFX_IDS_APP_TITLE);
