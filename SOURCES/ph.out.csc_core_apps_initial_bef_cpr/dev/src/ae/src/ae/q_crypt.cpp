
/* ---------------------------------------------------------------------- *
 *                               Q _ C R Y P T . C                        *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Sortiments-Pflege                                            *
 * Modul:    Menue-Maske                                                  *
 * Aufgabe:  Veschluesselung des Passwortes                               *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  13.09.1992                                                   *
 * Update :  09.02.1994                                                   *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "q_crypt.h"

/* ---- wegen SQL-Error: nicht folgende Zeichen ----------------- */

#define NOCHAR_1  127
#define NOCHAR_2  '"'
#define NOCHAR_3  '\''

/* ---- die NOCHAR's werden nicht verschluesselt ----------- */
/* ---- ergibt die Verschluesselung ein NOCHAR, dann wird -- */
/* ---- das Originalzeichen als Verschluesselung genommen -- */
/* ---- wegen SQL duerfen also die NOCHAR's nicht als ------ */
/* ---- akzeptiert werden ---------------------------------- */

static int  perm[] = { 2, 7, 1, 5, 3, 0, 4, 6 };

#define PERM_ANZ ( sizeof( perm ) / sizeof( int ) )

static char offs[] =
  { 0X1C, 0X08, 0X1B, 0X05, 0X17, 0X0D, 0X13, 0X09 };
/*
  { 0X1C, 0X18, 0X1B, 0X15, 0X17, 0X1D, 0X13, 0X19 };
  { 0X0C, 0X08, 0X0B, 0X05, 0X07, 0X0D, 0X03, 0X09 };
*/

#define OFFS_ANZ ( sizeof( offs ) / sizeof( char ) )


void pwd_crypt(const char* orig, char* crypt, int clng)
{
    int i;
    int j;
    for (i = 0; i < clng; i++)
    {
        j = perm[i % PERM_ANZ];
        if (orig[j] == NOCHAR_1 ||
            orig[j] == NOCHAR_2 ||
            orig[j] == NOCHAR_3)
        {
            crypt[i] = orig[j];
        }
        else
        {
            crypt[i] = (orig[j] ^ offs[i % OFFS_ANZ]) & (char)0X7F;
            if (crypt[i] == NOCHAR_1 ||
                crypt[i] == NOCHAR_2 ||
                crypt[i] == NOCHAR_3)
                crypt[i] = orig[j];
        }
    }
    for (i = 0; i < clng; i++)
        if (isupper(crypt[i]) && crypt[i] & (char)0X01)
            crypt[i] = (char)tolower(crypt[i]);
        else if (islower(crypt[i]) && crypt[i] & (char)0X01)
            crypt[i] = (char)toupper(crypt[i]);
    crypt[clng] = '\0';
}

void pwd_decrypt(char* orig, char* crypt, int clng)
{
    int i;
    int j;
    for (i = 0; i < clng; i++)
        if (isupper(crypt[i]) && crypt[i] & (char)0X01)
            crypt[i] = (char)tolower(crypt[i]);
        else if (islower(crypt[i]) && crypt[i] & (char)0X01)
            crypt[i] = (char)toupper(crypt[i]);
    for (i = 0; i < clng; i++)
    {
        j = perm[i % PERM_ANZ];
        if (crypt[i] == NOCHAR_1 ||
            crypt[i] == NOCHAR_2 ||
            crypt[i] == NOCHAR_3)
        {
            orig[j] = crypt[i];
        }
        else
        {
            orig[j] = (crypt[i] ^ offs[i % OFFS_ANZ]) & (char)0X7F;
            if (orig[j] == NOCHAR_1 ||
                orig[j] == NOCHAR_2 ||
                orig[j] == NOCHAR_3)
                orig[j] = crypt[i];
        }
    }
    orig[clng] = '\0';
}
