#include "stdafx.h"
#include "aeconnection.h"
#include <sockclient.h>


int OpenAEConnection(const CString& server, int port, char* error_msg)
{
    CString myServer = server;
    
    if (-1 != myServer.Find('\\'))
    {
        myServer.Remove('\\');
    }

    return ::ppSOpenSServer(myServer, port, error_msg);
}