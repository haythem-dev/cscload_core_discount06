/*
   kf_rund.c  : implementation file
   Kaufmaennisches Runden
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#ifdef UEBER_PRINTF

/*
laeuft unter UNIX Hajo falsch,
wenn letzte RundungsStelle+1 = 5 und alle rechts davon liegenden = 0
z.B 14.945 gerunden = 12.94
*/

void Runden_Printf( double *wert, int stellen )
{
   if ( stellen >= 0 )
   {
      char str[50];

      int i;
      double rund;

      rund = 1.0;
      for ( i = 0; i < stellen; i++ ) rund *= 10.0;

      sprintf( str, "%.0f", (*wert) * rund );
      *wert = atof( str ) / rund;
   }
}

#endif

#ifdef UEBER_FLOOR
/*
benoetigt unter UNIX die math-lib libm.a
laeuft unter UNIX Hajo falsch,
*/

void Runden_Floor( double *wert, int stellen )
{
   if ( stellen >= 0 )
   {

      int i;
      double rund;
      double result;

      rund = 1.0;
      for ( i = 0; i < stellen; i++ ) rund *= 10.0;

      i = 1;
      result = *wert;
      if ( result < 0.0 )
      {
         result = -result;
         i = -1;
      }
      result = floor( result*rund + 0.5 ) / rund;
      if ( i == 1 )
        *wert = result;
      else
        *wert = -result;
   }
}
#endif

void Runden_Modf( double *wert, int stellen )
{
   if ( stellen >= 0 )
   {

      int i;
      double rund;
      double result;
      double rest;

      rund = 1.0;
      for ( i = 0; i < stellen; i++ ) rund *= 10.0;

      i = 1;
      result = *wert;
      if ( result < 0.0 )
      {
         result = -result;
         i = -1;
      }

      rest = modf( result*rund + 0.5, &result );

		/* RR 17.12.08: die Anzahl der 9er hinter dem Komma war zu hoch. Beispiel: bei einem AEP von 
						10.300,- enthält das Feld rest in einer Zwischenberechnung nur noch 9 9er 
						hinter dem Komma und das result wird damit fälschlicherweise nicht um 1 
						erhöht 

		if ( rest >= 0.99999999999 ) */
		if ( rest >= 0.99999999 ) 
			result += 1.0;

      result /= rund;
      if ( i == 1 )
        *wert = result;
      else
        *wert = -result;
   }
}


void KaufmRunden( double *wert, int stellen )
{
   Runden_Modf( wert, stellen );
}

