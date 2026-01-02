/* ---------------------------------------------------------------------- *
 *   Aufgabe        : Start of zpcalcprice				                  *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 29.11.2006                                          *
 *   Autor          : Hoerath                                              *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <libscsvoodoo.h>
#include "logfile.h"

#ifndef WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
static int sig_accepted = 0;
static void intrpt_term(int sig)
{
    signal(SIGTERM, SIG_IGN);
    sig_accepted = 1;
}

static void signal_beh(void)
{
    signal(SIGTERM, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
}
#endif

/* --------- Prototype ------------- */

long parseArguments(int argc, char* argv[], char* statustxt);
long executeConsignmentCalculator(int argc, char* argv[], char* buf);

/* --------- main function --------- */
void ProgUsage()
{
    printf("usage:\n");
    printf("- zpconsig -db <database> -date <processdate(yyyymmdd)> -sim <yes/no>\n");
}

int main ( int argc, char *argv[] )
{
    long s;
    HNMP handle;
    char statustxt[5000];
    char data[5000];

    memset(statustxt, 0, sizeof(statustxt));
    memset(data, 0, sizeof(data));

    write_logfile(S_INFO, "main", "------application start-------");
    s = parseArguments(argc, argv, statustxt);
    if (s != 0)
    {
        ProgUsage();
    }
    else
    {
#if defined(WIN32)
        if ((s = ViaEshuOpenEx(&handle, "zdev21", "uiserv", 55260)) == 0)
        {
#else
        signal_beh();
        if ((s = PipwRead(argc, argv, statustxt, 0)) == -1)
        {
            sig_accepted = 0;
            signal(SIGTERM, intrpt_term);
#endif
            s = executeConsignmentCalculator(argc, argv, statustxt);

#if defined(WIN32)
            NmpCloseHandle(handle);
#endif
        }
        else
        {
            strcpy(statustxt, "Error in opening Voodoo Pipe: ");
            strcat(statustxt, DynErrmld());
        }
    }

    if (s != 0)
    {
        sprintf(data, "Errorcode %ld: %s", s, statustxt);
        write_logfile(S_ERROR, "main", data);
        s= 1;
    }
    sprintf(data, "----application end (RC %d)----", s);
    write_logfile(S_INFO, "main", data);
    return s;
}
