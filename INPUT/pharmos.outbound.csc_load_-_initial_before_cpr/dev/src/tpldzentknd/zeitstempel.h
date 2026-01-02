/*****************************************************************************/
/*                                                                           */
/*   Hauptmodule: lorbas                                                     */
/*   Header     : zeitstempel.h                                              */
/*   Autor      : A. Schmidt-Rehschuh (644)                                  */
/*   erstellt   : 10.04.96                                                   */
/*   Sprache    : C                                                          */
/*   erzeugt    : manuell                                                    */
/*                                                                           */
/*   Aufgabe    : Test-Defines fuer Zeitstempel in Microsecunden bei esql    */
/*                                                                           */
/*****************************************************************************/

/*** DEFINE - FUNKTIONS-AUFRUFE **********************************************/

 #ifndef __CZEITSTEMPEL__1234
 #define __CZEITSTEMPEL__1234

 #if defined(__CPLUS__) || defined(PPC543C50)
 extern "C" {
 #endif					

 void SetStart( void );
 void SetEnd( char *, int, char * );
 
 #if defined(__CPLUS__) || defined(PPC543C50)
 }
 #endif					

 #ifdef _XCICS
 #define SETSTART()      SetStart()
 #define SETEND(a)       SetEnd( __FILE__, __LINE__, a )
 #else
 #define SETSTART()      /* SetStart() */
 #define SETEND(a)       /* a */
 #endif
#endif
/*** ENDE ********************************************************************/
