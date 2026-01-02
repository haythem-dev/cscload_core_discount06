#include "pxdefs.hpp"
#include <stdio.h>

/*---------------------------------------------------------------------------*/
/*  Messages.                                                                */
/*---------------------------------------------------------------------------*/
char  pxMsgDefault[18];
char* pxMsgTable[] =
{
(char*) "Unbekannter Fehler\n",
(char*) "Zuwenig Hauptspeicher\n",
(char*) "Fehler beim Eroeffnen der .ini Datei %s\n",
(char*) "Fehler beim Eroeffnen der Nachrichten-/Textdatei %s\n",
(char*) "Session-Parameter fehlt \n",
(char*) "Session-Inifile-Parameter fehlt \n",
(char*) " "                             /* last message, unused               */
};

char*  pxErrorMsg
(
    pxMsgNumber    msgnum               // message number
)
{
    char* msgp;
    if (msgnum >=  sizeof(pxMsgTable) / sizeof(char*) || ((msgp = pxMsgTable[msgnum]) == NULL))
    {                                   // Print the number if no message
       msgp = pxMsgDefault;
       sprintf(msgp,"%i\n", msgnum);
    }
    return msgp;
}
