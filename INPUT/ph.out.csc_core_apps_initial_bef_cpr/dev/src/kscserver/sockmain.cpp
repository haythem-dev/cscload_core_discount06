#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#endif

#include <string.h>
#include <errno.h>
#include <signal.h>
#include <allg.h>
#include <libbasarcmnutil_cmdline.h>
#ifndef WIN32
#include "gitversioninfo.h"
#endif
#include <logger/loggerpool.h>

#define S_BUF_SIZE 4096
#define S_ANZ_LEN  4

#define KSCSERVER_PORT_NR	"ksc_server"		 /*6003 */

/* --- Prototyping ------------------------------------------------- */
int FktvertPuffer_anp(char *ReadBuf,char *WriteBuf,int a_lng);

int listenSocket = 0;					/* Socket-Handle */
int clientSocket = 0;					/* Socket-Handle */


#ifdef __cplusplus
extern "C" {
#endif
extern const char versioninfo[];
#ifdef __cplusplus
}
#endif

/* --- Aktionen bei Prozess-Ende ----------------------------------- */

void prozess_ende()
{
	/* Prozess beendet */
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Prozess-Ende");
	/* Sockets Schliessen */
#ifndef WIN32
	close(listenSocket);
	close(clientSocket);
#else
	closesocket(listenSocket);
	closesocket(clientSocket);
#endif
}

/* --- Abbruch durch Signal SIGQUIT (3) ---------------------------- */

static void intrpt(int /*sig*/)
{
	signal(SIGTERM,SIG_IGN);
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Abbruch durch Signal");
	prozess_ende();
	exit(1);
}

/* --- Signal-Behandlung ------------------------------------------- */

void signal_beh()
{
	signal(SIGINT,SIG_IGN);
	signal(SIGTERM,intrpt);
#ifndef WIN32
	signal(SIGHUP,SIG_IGN);
	signal(SIGCHLD,SIG_IGN); 
#endif
}

static void error_exit(const char* s)
{
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s);
	prozess_ende();
	exit(1);
}

void ReadFromSocket(int hS, char *AnfBuf,int a_lng)
{
	int anz_gel;            /* Anzahl gelesene Byte */
	int rc, i;
	char error_msg[128];

	/* Lesen bis alle Daten gelesen */
	for(i = 0,anz_gel = 0, rc = 1 ; rc != 0; i++)
	{
#ifdef WIN32
		rc = recv(hS, AnfBuf + anz_gel, a_lng - anz_gel, 0);
		if (rc == 0)
		{
			AnfBuf[0]='\0';
			return;
		}
#else
		rc = read(hS, AnfBuf + anz_gel, a_lng - anz_gel );
#endif
		if (rc == 0)
		{
			error_exit( "Client hat sich abgemeldet");
		}
		else if (rc == -1)
		{
			if (errno == EINTR)
			{
				rc = 1;
				continue;
			}
			error_exit( "sockmain.c recv (2) -1");
		}
		else if (rc != a_lng - anz_gel)
		{
			anz_gel += rc;
			rc = 1;
		}
		else
			rc = 0;
	}

	if (rc != 0)
	{
		sprintf(error_msg,"recv-3 erw. Zeichen: %d gelesen: %d", a_lng, anz_gel);
		error_exit(error_msg);
	}
	AnfBuf[a_lng] = '\0';
}

/* --- Hauptprogramm ----------------------------------------------- */

int main(int argc, char **argv)
{
	char AnfBuf[ S_BUF_SIZE ];               /* Anforderungs-Puffer */
	char RetBuf[ S_BUF_SIZE ];               /* Ergebnis-Puffer */

	struct sockaddr_in server;
	struct servent *sp;
	int r_lng;
	int a_lng;
	int sohn;
	int rc, i;
	char error_msg[128];
	char portname[20];
	char *env;

	basar::cmnutil::CmdLineTokenizer args;
	args.setCmdLine(argc, argv);

#ifndef WIN32
	if (args.isParam("-version"))
	{
		std::cout << versioninfo << std::endl;
		std::cout << GitVersionInfo::instance() << std::endl;
		exit( 0 );
	}		
#endif

	/* --- Signal-Behandlung */
	signal_beh();

	/* --- neuer Prozess gestartet */
	BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "Prozess-Start");

#ifdef WIN32
	WSADATA WSAData;                /* Struktur zur Windows Socket-Version */
	if (WSAStartup(MAKEWORD(1,1), &WSAData) != 0)   /* Windows-Sockets initialisieren */
	{
		sprintf(error_msg, "OpenServer error: WSAStartup");
		return -1;
	}
#endif

	/* --- Socket generieren  */
	listenSocket = socket (AF_INET, SOCK_STREAM, 0);
	if (listenSocket < 0)
		error_exit( "sockmain.c socket -1");

	/* --- Name dem Socked zuweisen  */
	env = getenv( "PORTNR" );
	if ( env == NULL )
		sprintf(portname, "%s", KSCSERVER_PORT_NR);
	else
		sprintf(portname, "%s", env);
	sp = getservbyname(portname, "tcp");
	if (sp == NULL)
		error_exit("sockmain.c getserverbyname tcp");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port = sp->s_port;
	rc = bind(listenSocket,(struct sockaddr *)&server, sizeof server);
	if (rc == -1)
		error_exit("sockmain.c bind -1");

	listen(listenSocket,5);
	for(;;)
	{
		for(i = 0, rc = 1; i < 5 && rc != 0; i++)
		{
			if((clientSocket = accept(listenSocket, (struct sockaddr *) 0, NULL)) == -1 )
			{
#ifdef WIN32
				Sleep(300);
#else
				sleep(1);
#endif
				rc = 1;
			}
			else
				rc = 0;
		}

		if (rc != 0)
			error_exit("sockmain.c accept -1");

		sohn = 0;
		/* --- Prozess kopieren (fuer weitere Clients)  */
#ifdef WIN32
		//nase
#else
		if ((sohn = fork()) == -1) error_exit( "sockmain.c fork -1");
#endif

		if (sohn != 0) // Vaterprozess
		{
#ifdef WIN32
			closesocket(clientSocket);
#else
			close(clientSocket);
#endif
			continue;
		}

		// ab hier child-process
#ifdef WIN32
		//closesocket(listenSocket);
#else
		close(listenSocket);
#endif

		/* --- solange Client aktiv  */
		do
		{
			/* Laenge der Nachricht ermitteln */
			ReadFromSocket(clientSocket, AnfBuf, S_ANZ_LEN);
#ifdef WIN32
			if (AnfBuf[0] == '\0')
			{
				// client disconnected, go back to accept() and wait for new client
				closesocket(clientSocket);
				break; 
			}
#endif
			a_lng = atoi(AnfBuf) - S_ANZ_LEN;

			/* Lesen der Daten */
			ReadFromSocket(clientSocket, AnfBuf, a_lng);

			BLOG_TRACE(libcsc::LoggerPool::getLoggerSession(), AnfBuf);

			/* Dekomprimierung der Daten */
			if ((a_lng = AllgBufDeCompr(AnfBuf, S_BUF_SIZE)) < 0 )
			{
				sprintf(error_msg,"sockmain.c AllgBufDeCompr: error");
				error_exit(error_msg);
			}

			do {   /* FETCH-Schleife */
				r_lng = FktvertPuffer_anp(RetBuf, AnfBuf , a_lng);
				RetBuf[r_lng] = '\0';

				/* --- Ergebnisdaten komprimieren  */
				if ((r_lng = AllgBufCompress(RetBuf, S_BUF_SIZE-S_ANZ_LEN)) < 0 ) /* Header nicht komrimieren */
				{
					sprintf(error_msg,"sockmain.c AllgBufCompress: error");
					error_exit(error_msg);
				}

				sprintf(AnfBuf,"%04d",r_lng + S_ANZ_LEN);                       /* Uebertragungslaenge schreiben */
				memcpy(AnfBuf + S_ANZ_LEN, RetBuf, r_lng);                      /* Daten anfuegen */
				r_lng += S_ANZ_LEN;                                                                     /* Laenge korrigieren */
				AnfBuf[r_lng] = '\0';

				BLOG_TRACE(libcsc::LoggerPool::getLoggerSession(), AnfBuf + S_ANZ_LEN);
#ifdef WIN32
				rc = send(clientSocket, AnfBuf, r_lng,0);
#else
				rc = write(clientSocket, AnfBuf, r_lng);
#endif
				if (rc == -1)
					error_exit("sockmain.c write -1");
				else if (rc != r_lng)
					error_exit("write");
			} while(RetBuf[0]=='3'); /*Ende der FETCH-Schleife*/
		} while (rc > 0 && a_lng != 0);
	}
}
