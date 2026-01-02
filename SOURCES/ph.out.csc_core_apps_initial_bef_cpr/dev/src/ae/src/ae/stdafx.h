#ifndef __PP_STDAFX_H_
#define __PP_STDAFX_H_

// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define _WIN32_WINNT 0x0502

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxsock.h>        // MFC socket extensions
#include <afxdisp.h>        // MFC OLE automation classes
#include <afxdtctl.h>       // MFC DateTime
#include <afxcmn.h>
#include <afxpriv.h>
#include <afxcoll.h>
#include <afx.h>
#include <afxdialogex.h>

#define NEXT_PG     0       //weitere Seite ausgeben
#define PRIOR_PG    1       //vorherige Seite ausgeben

#include "allgfktn.h"
#include "ColumnsTypes.h"
#include "ListCtrlHelper.h"
#include "LetterMan.h"
#include "PageBrowser.h"

#include "PCmn.h"           //MULTI-LANGUAGE

#include "ae.h"
#include "tm.h"
#include "aetexte.h"
#include "ppdatatypes.h"
#include <aasrv.h>
#include <ausrvfkt.h>
#include <aasrvfkt.h>
#include <ppstring.h>

#include <boost/smart_ptr.hpp>

//#define PIPE_AE_SRV       100     //Nummer der Serverpipe
#define PIPE_AE_SRV         0       //Nummer der Serverpipe
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>

#define SRV_OK          0       // looks nicer to check server result against SRV_OK than '!'
#define SRV_SQLNOTFOUND 1

//Sie können eine Klasse von CComModule ableiten und dies verwenden, wenn Sie
//etwas überladen wollen. Ändern Sie aber nicht den Namen von _Module
class CAEModule : public CComModule
{
public:
    LONG Unlock();
    LONG Lock();
    LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
    DWORD dwThreadID;
};
extern CAEModule _Module;
#define _ATL_MAX_VARTYPES 20    // to avoid an assertion in ATLCOM.H, line 3914
#include <atlcom.h>
#include <afxdhtml.h>
#include <afxdlgs.h>

#include "resource.h"

class CAeApp;
extern CAeApp* AeGetApp();

class COrderType;
COrderType& GetOrderType();

class CAeUser;
CAeUser& GetAeUser();

#endif   // GUARD
