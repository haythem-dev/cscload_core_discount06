/******************************************************************************/
/*     Hauptmodul: tpulzpbulgaria                                             */
/*         Source: tpulzpbulgaria.h                                           */
/*          Autor: A. Schmidt-Rehschuh                                        */
/*       Erstellt: 01.04.1998                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: typedefs aud structuren                                    */
/*                                                                            */
/******************************************************************************/

/*** TYPES ********************************************************************/

 typedef enum { be_impaired = -1, no_error = 0, read_error, write_error,
	            db_error, log_error, call_error, open_error, send_error,
				is_activ, eof } rterror;

 typedef struct { 
	 long  lDate;
	 long  lDateTo;
	 long  lDay;
	 char  *spFile;
	 char  *spFile2;
	 char  *spDestinationHost;
	 char  *spDestinationDir;
	 char  *spDestinationFile;
	 char  *spUser;
	 char  *spPassword;
	 char  *spDatabase;
 } parameter;

 #ifdef ESQL_C
 exec sql begin declare section;
 #endif

 typedef struct ZARTIKEL		  dezapzartikelSTR;
 typedef struct ZARTPREIS		  dezapzartpreisSTR;
 typedef struct ZARTSEKBEZ		  dezapzartsekbezSTR;
 typedef struct ZARTWG			  dezapzartwgSTR;
 typedef struct ZARTBULGARIA	  dezapzartbulgariaSTR;
 typedef struct ARTVE			  dezapartveSTR;
 typedef struct EAN				  dezapeanSTR;
 typedef struct CARTICLELANG	  dezapcarticlelangSTR;
 typedef struct ZDKWIR			  dezapzdkwirSTR;
 typedef struct CREGISTERS 		  dezapcregistersSTR;

 #ifdef ESQL_C
 exec sql end declare section;
 #endif
