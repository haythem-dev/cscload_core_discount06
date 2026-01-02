/******************************************************************************/
/**                                                                           */
/**   Author : T. Hörath PRZ GmbH                                             */
/**   Date   : 21.06.2004                                                     */
/**                                                                           */
/******************************************************************************/

#include "stdafx.h"

INT_PTR MsgBoxOK(const char* const spMsg, UINT uiType, const char* const spCaption)
{
    return MsgBox1(spMsg,
        CResString::ex().getStrTblText(IDS_MSG_OK),
        uiType,
        spCaption);
}

INT_PTR MsgBoxOK(UINT uiMsg, UINT uiType, UINT uiCaption)
{
    return MsgBox1(uiMsg,
        IDS_MSG_OK,
        uiType,
        uiCaption);
}

INT_PTR MsgBoxYesNo(const char* const spMsg, UINT uiType, const char* const spCaption)
{
    return MsgBox2(spMsg,
        CResString::ex().getStrTblText(IDS_MSG_YES),
        CResString::ex().getStrTblText(IDS_MSG_NO),
        uiType,
        spCaption);
}

INT_PTR MsgBoxYesNo(UINT uiMsg, UINT uiType, UINT uiCaption)
{
    return MsgBox2(uiMsg,
        IDS_MSG_YES,
        IDS_MSG_NO,
        uiType,
        uiCaption);
}
