#include "tcawrap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>
#ifdef WIN32
#include <winsock2.h>
#include <io.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#ifdef WIN32
#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
#endif

//------------------------------------------------------------------------------
static int checkSocket (
    int                sock   ,
    const char * const ipaddr ,
    const char * const port   ,
    int                timeout,
    ErrorMsg           errmsg )
{
#ifndef WIN32
    // set non-blocking
    {
        int file = fcntl(sock, F_GETFL, NULL);

        if ( 0 > file )
        {
            sprintf(errmsg,
                    "error in fcntl(%d, F_GETFL) (%d, %s)\n",
                    sock,
                    errno,
                    strerror(errno));

            return 0;
        }

        file |= O_NONBLOCK;

        if( -1 == fcntl(sock, F_SETFL, file) )
        {
            sprintf(errmsg,
                    "error in fcntl(%d, F_SETFL) (%d, %s)\n",
                    sock,
                    errno,
                    strerror(errno));
            return 0;
        }
    }
#endif
    // try to connect with timeout
    {
        struct sockaddr_in addr;

        addr.sin_family      = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ipaddr);
        addr.sin_port        = htons    ((u_short)atoi(port));

        if ( -1 == connect(sock, (struct sockaddr *)&addr, sizeof(addr)) )
        {
            if (EINPROGRESS != errno)
            {
                sprintf(errmsg,
                        "error in connect(%d, (%s:%s)) (%d, %s)\n",
                        sock,
                        ipaddr,
                        port,
                        errno,
                        strerror(errno));
                return 0;
            }

            struct timeval tv;
            tv.tv_sec  = timeout;
            tv.tv_usec = 0;

            fd_set writefs;
            FD_ZERO(&writefs);
            FD_SET (sock, &writefs);

            int sel = select(sock + 1, NULL, &writefs, NULL, &tv);

            switch (sel)
            {
            case -1:
                sprintf(errmsg,
                        "error in select(%d, %d sec) (%d, %s)\n",
                        sock,
                        timeout,
                        errno,
                        strerror(errno));
                return 0;

            case 0:
                sprintf(errmsg,
                        "timeout in select(%d, %d sec)\n",
                        sock,
                        timeout);
                return 0;

            default:
                assert(FD_ISSET(sock, &writefs));
                break;
            }

            // socket selected for write
#ifdef WIN32
            int optlen = sizeof(int);
#else
            socklen_t optlen = sizeof(int);
#endif
            int       optval;

#ifdef WIN32
            if (-1 == getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&optval, &optlen) )
#else
            if (-1 == getsockopt(sock, SOL_SOCKET, SO_ERROR, &optval, &optlen) )
#endif
            {
                sprintf(errmsg,
                        "error in getsockopt(%d) (%d, %s)\n",
                        sock,
                        errno,
                        strerror(errno));
                return 0;
            }

            // check the returned value
            if (optval)
            {
                sprintf(errmsg,
                        "error in delayed, asynchronous connection (%d, %s)\n",
                        optval,
                        strerror(optval));
                return 0;
            }
        }
    }

    return 1;
}

//------------------------------------------------------------------------------
int isCicsAvail(const struct CicsConnParam * const pConnParam,
                int                                timeout   ,
                ErrorMsg                           errmsg    )
{
    strcpy(errmsg, "");

    int sock = (int)socket(AF_INET, SOCK_STREAM, 0);

    if ( -1 == sock )
    {
        sprintf(
            errmsg,
            "error creating socket(AF_INET, SOCKSTREAM, 0) (%d: %s)\n",
            errno,
            strerror(errno));

        return 0;
    }

    int ret = checkSocket(sock,
                          pConnParam->ipaddr,
                          pConnParam->port  ,
                          timeout           ,
                          errmsg            );

    // clean up
#ifdef WIN32
    if (-1 == _close(sock))
#else
    if (-1 == close(sock))
#endif
    {
        sprintf(errmsg,
                "error in close(%d) (%d, %s)\n",
                sock,
                errno,
                strerror(errno));
        return 0;
    }

    return ret;
}

