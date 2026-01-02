//////////////////////////////////////////////////////////////////
// DialogServer.cpp  implementation file

#include "stdafx.h"
#include <wudu.h>
#include "DlServer.h"

CDlServer::CDlServer()
{
	m_Fd = -1;
	m_ServerName = "";
}

CDlServer::~CDlServer()
{
}

void CDlServer::DefineServer( char *ServerName )
{
	m_ServerName = ServerName;
	m_Fd = -1;
}

void CDlServer::DefineServer( CString ServerName )
{
	m_ServerName = ServerName;
	m_Fd = -1;
}

long CDlServer::OpenConversation( CString& errmld )
{
	int  fd;
	long s;
	char w_buf[400];  

	if ( m_Fd == -1 )
	{
/*
		s =  UnxGetenv( "WWS", w_buf );       
		if ( s != 0 )                         
		{                                     
			errmld = DynErrmld();     
			return s;                           
		}                                     
		strcat( w_buf, "/lib/" );             
		strcat( w_buf, m_ServerName );  
*/
		/* das geht jetzt ueber LD_LIBRARY_PATH */
		strcpy( w_buf, m_ServerName );  

		if ( strcmp( &w_buf[strlen(w_buf) - 3], ".so" ) != 0 )   
			strcat ( w_buf, ".so" );                                                                                      
		s = UnxDlConvOpen( &fd, w_buf, 0 );                     
		if ( s != 0 )                                           
		{         
		  	errmld = DynErrmld();     
			return s;                                                       
		}                                    
		m_Fd = fd;
	}
	return 0;
}


long CDlServer::CloseConversation( CString& errmld )
{
	long s;

	s = 0;
	errmld = "";

	if ( m_Fd != -1 )
	{
		s = UnxDlConvClose ( m_Fd );  
		m_Fd = -1;
		if ( s != 0 )
			errmld = DynErrmld();     
	}
	return s;
}


long CDlServer::Conversation( char *fkt, 
							  char *w_buf, int w_lng, 
							  char *r_buf, int *r_lng,
							  CString& errmld )
{
	long s; 

	s =  UnxDlConv( m_Fd, fkt,  
                    w_buf, strlen(w_buf), r_buf, r_lng );  
	if ( s != 0 )                                                                                                       
		errmld = DynErrmld();
	return s;
}