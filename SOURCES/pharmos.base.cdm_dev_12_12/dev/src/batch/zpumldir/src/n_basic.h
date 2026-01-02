/* ---------------------------------------------------------------------- *
 *                           P _ B A S I C . H                            *
 * ---------------------------------------------------------------------- */

long StartTransaction ( char *errmld );
long CommitTransaction( char *errmld );
void CancelTransaction( void );

long OnFirst( char *user, char *errmld  );
long OpenForUmlisten  ( char *errmld  );
long OpenForHerwechsel( char *errmld  );
void OnLast( void );

long Insert_Pflege( long besla_nr, long artikel_nr, char *errmld );

long DeleteRecord_Zaneuheit( char programm, long artikel_nr, char *errmld );

long Lese_Artnrbl   ( long besla_nr, long artikel_nr, char *artikel_nr_bliefer,
                      char *errmld );
long Insert_Artnrbl ( long besla_nr, long artikel_nr, char *artikel_nr_bliefer,
                      char *errmld );
long Delete_Artnrbl ( long besla_nr, long artikel_nr, char *artikel_nr_bliefer,
                      char *errmld );

long Lese_Bliesort  ( long besla_nr, long artikel_nr, char *ermld );
long Insert_Bliesort( long besla_nr, long artikel_nr, char *ermld );
long Delete_Bliesort( long besla_nr, long artikel_nr, char *ermld );


#define MIT_NEM

#ifdef MIT_NEM
long StoreRecord_Zartikel( long artikel_nr, long besla_nr, char *errmld );
#endif

