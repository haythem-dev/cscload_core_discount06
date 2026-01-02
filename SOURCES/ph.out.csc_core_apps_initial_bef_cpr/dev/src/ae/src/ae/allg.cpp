/* allg.cpp */

#include "stdafx.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include "texte.h"
#include "allg.h"

#define CHAR_FOR_SPACE  '#'
#define CHAR_FOR_ZERO   '$'
#define CHAR_SPACE      ' '
#define CHAR_ZERO       '0'

/* kopieren ohne Speicherverletzungen */
void  AllgStrCopy(char *ziel, const char *quelle, unsigned max)
{
    if (strlen(quelle) <= max)
    {
        strcpy(ziel, quelle);
    }
    else
    {
        strncpy(ziel, quelle,max);
        ziel[max] = '\0';
    }
}

/* AllgEntfSpaces - Leerzeichen am Ende der Zeichenkette entf. */
void AllgEntfSpaces(char* str)
{
    int len;
    for (len = strlen(str) - 1; str[len] == ' ' && len >= 0; len--)
        str[len] = '\0';
    return;
}

/* AllgEntfSpaces - Leerzeichen am Anfang der Zeichenkette entf. */
void AllgEntfFirstSpaces(char* str)
{
    char s[2048];
    int i;

    for (i = 0; str[i] == ' '; i++)
    {
        ;
    }
    strcpy(s, str + i);
    strcpy(str, s);
}

/* AllgEntfAllSpaces - Spaces in & an der Zeichkette entf.    */
void AllgEntfAllSpaces(char* str)
{
    int i;
    int j = 0;
    int k = strlen(str) + 1;
    int l;

    for (i = k - 1; i > -1; i--)  /* entfernt alle Leerzeichen im String, alle !!! */
    {
        if (str[i] == ' ')
        {
            for (l = i; l < k - j; l++)
                str[l] = str[l + 1];
            j++;
        }
    }
}

/*  READ_LONG  */
int AllgReadLong(char* str, long* erg, __int64 min, __int64 max,
    char* error_msg)
{
    /* pruefen einer numerischen eingabe */

    char* fehadr;

    errno = 0;
    AllgEntfAllSpaces(str);
    if (str[0] == '\0')
    {
        sprintf(error_msg, CResString::ex().getStrTblText(IDS_TXT_EING_WERT_ERF));
        return -1;
    }

    *erg = strtol(str, &fehadr, 10);
    if (errno == ERANGE)
    {
        if (*erg == LONG_MIN)
        {
            sprintf(error_msg, CResString::ex().getStrTblText(IDS_TXT_EING_UNTERLAUF));
            return -1;
        }
        if (*erg == LONG_MAX)
        {
            sprintf(error_msg, CResString::ex().getStrTblText(IDS_TXT_EING_UEBERLAUF));
            return -1;
        }
    }
    if (*erg < min)
    {
        sprintf(error_msg, "%s %I64d", CResString::ex().getStrTblText(IDS_TXT_EING_WERT_MIN).GetString(), min);
        return -1;
    }
    if (*erg > max)
    {
        sprintf(error_msg, "%s %I64d", CResString::ex().getStrTblText(IDS_TXT_EING_WERT_MAX).GetString(), max);
        return -1;
    }
    if (*fehadr != '\0')
    {
        sprintf(error_msg, CResString::ex().getStrTblText(IDS_TXT_NICHT_KONVB_ZEICH));
        return -1;
    }
    return 0;
}

/* AllgEntfSpaces - Leerzeichen am Ende der Zeichenkette entf. */
void AllgMakeToLike(char* str, long max)
{
    int len;
    AllgEntfSpaces(str);
    len = strlen(str);
    if (len < max)
    {
        str[len] = '%';
        str[len + 1] = '\0';
    }
}

/* AllgDoubleToDMText - Transferiert double zu String mit DM-Ende */
char* AllgDoubleToDMText(double wert, char* str, char* dm)
{
    sprintf(str, "%.2f %s", wert, dm);
    return str;
}

/***********************************************************************
* AllgBitleisteN - liefert das n-te Element einer Bitleiste            *
***********************************************************************/

int AllgBitleisteN(Bitleiste bitleiste, int n)
{
    if (n > 15)
    {
        n = 15;
    }
    else if (n < 0)
    {
        n = 0;
    }
    return (int)(bitleiste >> (15 - n)) % 2;
}

/***********************************************************************
* AllgBitleiste2Char - wandelt eine 4-Byte-Bitleiste                   *
* in eine um 0/1 -Kombination (char)                                   *
***********************************************************************/

char* AllgBitleiste2Char(Bitleiste bitleiste, char* Char)
{
    int i;
    char str[16 + 1];

    Char[0] = '\0';
    for (i = 0; i < 16; i++)
    {
        if (bitleiste % 2)
        {
            strcat(Char, "1");
        }
        else
        {
            strcat(Char, "0");
        }
        bitleiste = bitleiste >> 1;
    }
    Char[16] = '\0';
    strcpy(str, Char);
    for (i = 0; i < 16; i++)
    {
        Char[i] = str[15 - i];
    }
    Char[16] = '\0';
    return Char;
}

/***********************************************************************
* AllgChar2Bitleiste - wandelt eine 0/1 -Kombination (char)            *
* in eine 4-Byte-Bitleiste um                                          *
***********************************************************************/

Bitleiste AllgChar2Bitleiste(char* Char, Bitleiste* Bitl)
{
    int len;
    int i;

    len = strlen(Char);
    if (len > 16)
    {
        len = 16;
    }
    *Bitl = 0;
    for (i = 0; i < len; i++)
    {
        if (Char[i] == '1')
        {
            *Bitl <<= 1;
            *Bitl |= 1;
        }
        else
        {
            *Bitl <<= 1;
            *Bitl |= 0;
        }
    }
    return *Bitl;
}

/****************************************************************************************
*****************************************************************************************
**                                                                                     **
**  DATUMS- UND ZEITFUNKTIONEN                                                         **
**                                                                                     **
*****************************************************************************************
****************************************************************************************/

/* AllgGetDate - Datum als long fuer DB-Speicherung */
long AllgGetDate()
{
    struct tm* t;
    time_t tt;
    tt = time(0L);
    t = localtime(&tt);                             /* Ortszeit */
    return (long)(t->tm_year + 1900) * 10000L +
        (long)(t->tm_mon + 1) * 100L +
        (long)(t->tm_mday);
}

/* AllgGetTime - Zeit als long fuer DB-Speicherung */
long AllgGetTime()
{
    struct tm* t;
    time_t tt;
    tt = time(0L);
    t = localtime(&tt);                             /* Ortszeit */
    return (long)(t->tm_hour) * 10000L +
        (long)(t->tm_min) * 100L +
        (long)t->tm_sec;
}


/* AllgGetTM - Datum/Zeit als Struktur */
void AllgGetTM(struct tm* t)
{
    struct tm* ttt;
    time_t tt;
    tt = time(0L);
    ttt = localtime(&tt);                             /* Ortszeit */
    t->tm_sec = ttt->tm_sec;
    t->tm_min = ttt->tm_min;
    t->tm_hour = ttt->tm_hour;
    t->tm_mday = ttt->tm_mday;
    t->tm_mon = ttt->tm_mon;
    t->tm_year = ttt->tm_year;
    t->tm_wday = ttt->tm_wday;
    t->tm_yday = ttt->tm_yday;
    t->tm_isdst = ttt->tm_isdst;
    return;
}

/***********************************************************************
* datum_long2char - datum im Long-Format in char umwandeln dd.mm.jjjj  *
***********************************************************************/

char* AllgDatumLong2CharTTMMJJJJ(long LDatum, char* Out)  /* out: dd.mm.jjjj  */
{
    sprintf(Out, "%.2ld.%.2ld.%.4ld",
        LDatum % 100L,
        (LDatum % 10000L) / 100L,
        (LDatum / 10000L));
    return Out;
}

/* Datum mit zweistelligem Jahr */
char* AllgDatumLong2CharTTMMJJ(long LDatum, char* Out)    /* out: dd.mm.jj    */
{
    sprintf(Out, "%.2ld.%.2ld.%.2ld",
        LDatum % 100L,
        (LDatum % 10000L) / 100L,
        (LDatum / 10000L) % 100L);
    return Out;
}

/* Datum mit zweistelligem Jahr */
char* AllgDatumLong2CharMMJJ(long LDatum, char* Out)      /* out: mm/jj    */
{
    sprintf(Out, "%.2ld/%.2ld",
        (LDatum % 10000L) / 100L,
        (LDatum / 10000L) % 100L);
    return Out;
}

/* Datum mit zweistelligem Jahr */
char* AllgDatumLong2CharTTMM(long LDatum, char* Out)      /* out: dd.mm.      */
{
    sprintf(Out, "%.2ld.%.2ld.",
        LDatum % 100L,
        (LDatum % 10000L) / 100L);
    return Out;
}

char* AllgZeitLong2CharHHMM(long LZeit, char* Out)        /* out: hh:mm       */
{
    sprintf(Out, "%.2ld:%.2ld",
        LZeit / 10000L,
        (LZeit / 100L) % 100L);
    return Out;
}

char* AllgTourTimeToCharHHMM(long LTime, char* Out)
{
    LTime = LTime % 2400;
    sprintf(Out, "%02d:%02d", LTime / 100, LTime % 100);
    return Out;
}

char* AllgZeit2CharHHMM(long LTime)                     /* out: hh:mm       */
{
    static char timeStr[6];                              /* speicher alloc   */

    if (LTime < 2401)
        sprintf(timeStr, "%02d:%02d", LTime / 100, LTime % 100);
    else if (LTime < 240001)
        sprintf(timeStr, "%02d:%02d", LTime / 10000, (LTime / 100) % 100);
    else if (LTime < 24000001)
        sprintf(timeStr, "%02d:%02d", LTime / 1000000, (LTime / 10000) % 100);
    else
        strcpy(timeStr, "00:00");
    return(timeStr);
}

char* AllgZeit2CharHHMMSS(long d)                       /* out: hh:mm       */
{
    static char timeStr[9];                            /* speicher alloc   */

    if (d < 2401)
        return (char*)0;
    else if (d < 240001)
        sprintf(timeStr, "%02d:%02d:%02d", d / 10000, (d / 100) % 100, d % 100);
    else if (d < 24000001)
        sprintf(timeStr, "%02d:%02d:%02d", d / 1000000, (d / 10000) % 100,
            (d % 10000) / 100);
    else
        strcpy(timeStr, "00:00");

    return(timeStr);
}

char* AllgZeitLong2CharHHMMSS(long LZeit, char* Out)      /* out: hh:mm:ss    */
{
    sprintf(Out, "%.2ld:%.2ld:%.2ld",
        LZeit / 10000L,
        (LZeit / 100L) % 100L,
        LZeit % 100L);
    return Out;
}

long AllgAddDate(long Datum, int AnzTage, char* error_msg)
{
    time_t Dat;
    struct tm tt, * t;
    t = &tt;

    t->tm_year = (int)((Datum / 10000L) - 1900L);
    t->tm_mon = (int)(((Datum / 100L) % 100L) - 1L);
    t->tm_mday = (int)(Datum % 100L);
    t->tm_hour = 0;
    t->tm_min = 0;
    t->tm_sec = 0;
    t->tm_isdst = -1;
    if ((Dat = mktime(t)) == -1)
    {
        sprintf(error_msg, CResString::ex().getStrTblText(IDS_TXT_DATUM_KONV), Datum);
        return -2L;
    }
    Dat += (long)AnzTage * 24L * 60L * 60L; /* Anzahl Tage addieren (vorzeichenabhaengig) */
    t = localtime(&Dat);
    return (long)(t->tm_year + 1900) * 10000L +
        (long)(t->tm_mon + 1) * 100L +
        (long)t->tm_mday;
}

int AllgAddTime(long Zeit1, long Zeit2, long* Ergebnis)
{
    long sec1, sec2;
    long ganzertag;
    int ret;
    ganzertag = 24L * 3600L;
    sec1 = Zeit1 % 100 + ((Zeit1 / 100) % 100) * 60 + (Zeit1 / 10000) * 3600;
    sec2 = Zeit2 % 100 + ((Zeit2 / 100) % 100) * 60 + (Zeit2 / 10000) * 3600;
    sec1 = sec1 + sec2;
    if (sec1 > ganzertag)
    {
        sec1 = sec1 - ganzertag;
        ret = ALLG_FOLGE_TAG;
    }
    else if (sec1 < 0)
    {
        sec1 = ganzertag + sec1;
        ret = ALLG_VOR_TAG;
    }
    else ret = ALLG_AKT_TAG;
    *Ergebnis = (sec1 / 3600) * 10000 + ((sec1 / 60) % 60) * 100 + sec1 % 60;
    return ret;
}

int AllgAddTimeSpan(long Zeit1, long sec2, long* Ergebnis)
{
    long sec1;
    long ganzertag;
    int ret;
    ganzertag = 24L * 3600L;
    sec1 = Zeit1 % 100 + ((Zeit1 / 100) % 100) * 60 + (Zeit1 / 10000) * 3600;
    sec1 = sec1 + sec2;
    if (sec1 > ganzertag)
    {
        sec1 = sec1 - ganzertag;
        ret = ALLG_FOLGE_TAG;
    }
    else if (sec1 < 0)
    {
        sec1 = ganzertag + sec1;
        ret = ALLG_VOR_TAG;
    }
    else ret = ALLG_AKT_TAG;
    *Ergebnis = (sec1 / 3600) * 10000 + ((sec1 / 60) % 60) * 100 + sec1 % 60;
    return ret;
}

long AllgGetWeekDay(long Datum, char* error_msg)
{
    time_t Dat;
    struct tm tt, * t;
    t = &tt;

    t->tm_year = (int)((Datum / 10000L) - 1900L);
    t->tm_mon = (int)(((Datum / 100L) % 100L) - 1L);
    t->tm_mday = (int)(Datum % 100L);
    t->tm_hour = 0;
    t->tm_min = 0;
    t->tm_sec = 0;
    t->tm_isdst = -1;
    if ((Dat = mktime(t)) == -1)
    {
        sprintf(error_msg, CResString::ex().getStrTblText(IDS_TXT_DATUM_KONV), Datum);
        return -2L;
    }
    t = localtime(&Dat);
    return (long)(t->tm_wday);
}

short CharToShort(char c)
{
    char huelse[2];
    huelse[0] = c;
    huelse[1] = '\0';
    return static_cast<short>(atoi(huelse));
}
