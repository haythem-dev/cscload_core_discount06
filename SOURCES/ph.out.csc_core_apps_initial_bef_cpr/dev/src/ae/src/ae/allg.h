#pragma once

typedef unsigned short Bitleiste;

#define ALLG_SONNTAG    0
#define ALLG_MONTAG     1
#define ALLG_DIENSTAG   2
#define ALLG_MITTWOCH   3
#define ALLG_DONNERSTAG 4
#define ALLG_FREITAG    5
#define ALLG_SONNABEND  6

#define ALLG_AKT_TAG    0
#define ALLG_FOLGE_TAG  1
#define ALLG_VOR_TAG    2

#define ALLG_ERR        -1
#define ALLG_ERR_MEM    -2
#define ALLG_ERR_LENGTH -3

void AllgStrCopy(char* ziel, const char* quelle, unsigned max);
int  AllgReadLong(char* str, long* erg, __int64 min, __int64 max, char* error_msg);
void AllgEntfAllSpaces(char* str);
void AllgEntfSpaces(char* str);
void AllgEntfFirstSpaces(char* str);
void AllgMakeToLike(char* str, long max);
char* AllgDoubleToDMText(double wert, char* str, char* dm);

/* Bitleisten-Funktionen */
Bitleiste AllgChar2Bitleiste(char* Char, Bitleiste* Bit1);
char* AllgBitleiste2Char(Bitleiste bitleiste, char* Char);
int  AllgBitleisteN(Bitleiste bitleiste, int n);

/* Datums- und Zeitfunktionen */
long AllgGetDate();                                         /* out: jjjjmmdd    */
long AllgGetTime();                                         /* out: hhmmss00    */
void AllgGetTM(struct tm* t);                               /* Datum/Zeit als Struktur */
long AllgAddDate(long Datum, int AnzTage, char* error_msg); /* out: Tag + AnzTage (jjjjmmdd) */
int  AllgAddTime(long Zeit, long Intervall, long* Ergebnis); /* out: hhmmss */
int  AllgAddTimeSpan(long Zeit, long seconds, long* Ergebnis); /* out: hhmmss */
long AllgGetWeekDay(long Datum, char* error_msg);           /* out: Wochentag, 0 - Sonntag */
char* AllgDatumLong2CharTTMMJJJJ(long LDatum, char* Out);   /* out: dd.mm.jjjj  */
char* AllgDatumLong2CharTTMMJJ(long LDatum, char* Out);     /* out: dd.mm.jj    */
char* AllgDatumLong2CharMMJJ(long LDatum, char* Out);       /* out: mm/jj       */
char* AllgDatumLong2CharTTMM(long LDatum, char* Out);       /* out: dd.mm.      */
char* AllgZeitLong2CharHHMM(long LZeit, char* Out);         /* out: hh:mm       */
char* AllgZeit2CharHHMM(long LZeit);                        /* Lzeit kann 4/6/8 stellig sein(hh:mm) */
char* AllgTourTimeToCharHHMM(long LTime, char* Out);
char* AllgZeit2CharHHMMSS(long LTime);                      /* Lzeit kann 6/8 stellig sein(hh:mm) */
char* AllgZeitLong2CharHHMMSS(long LZeit, char* Out);       /* out: hh:mm:ss    */

short CharToShort(char c);