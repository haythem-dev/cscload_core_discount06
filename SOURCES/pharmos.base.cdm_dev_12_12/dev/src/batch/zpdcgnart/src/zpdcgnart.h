#ifndef  ZPDCGNART_INCLUDED
#define  ZPDCGNART_INCLUDED
long GenArtLoop ( char *db, char *param1, char *param2, char *param3, char *param4,
                  char *spBuf );
void GenArtUsage( char *spBuf, const char *prog );

long Zdcart_Protokol_Loop  ( char *db, char *c_ifadatum, char *verzeichnis, char *spBuf );
void Zdcart_Protokol_Usage ( char *spBuf, const char *prog );
#endif
