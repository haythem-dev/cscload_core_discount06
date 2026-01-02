#ifndef DLSERVER_H_INCLUDE
#define DLSERVER_H_INCLUDE

// DlServer.h : header file
//

class CDlServer
{

private:
	// members
	int	    m_Fd;
	CString m_ServerName;

public:	  
	CDlServer();           // protected constructor used by dynamic creation

// Operations
public:
	void DefineServer ( char* ServerName );
	void DefineServer ( CString ServerName );

	long OpenConversation ( CString& errmld );
	long CloseConversation( CString& errmld );
	long Conversation( char *fkt, 
		               char* WriteBuffer,  int  WriteBufferLength, 
					   char* ReturnBuffer, int* ReturnBufferLength,
					   CString& errmld );

// Implementation
public:  
	virtual ~CDlServer();

};

/////////////////////////////////////////////////////////////////////////////
//

#endif // DLSERVER_H_INCLUDE