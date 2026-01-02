/*** INCLUDE ******************************************************************/

  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "dezap.h"

/*** DEFINE *******************************************************************/

  #include "define.h"
  #define PRINT(x,y,z) fprintf( dz, "%s:%-*.*s\n", x, z, z, y );

/*** DECLARATION **************************************************************/

  void DruckeDezap( struct O_DEZAP * );
  static FILE *Open( const char * );
  static void Close( FILE * );

/*** DRUCKE-DEZAP *************************************************************/

  void DruckeDezap( struct O_DEZAP *d )
  {
    FILE *dz;

    dz = Open( "a" );
    PRINT( "ZAPSA             ", d->ZAPSA             , L_DEZAP_ZAPSA              )
    PRINT( "ZAPKUBZ           ", d->ZAPKUBZ           , L_DEZAP_ZAPKUBZ            )
    PRINT( "ZAPPZN            ", d->ZAPPZN            , L_DEZAP_ZAPPZN             )
    PRINT( "ZAPSBEZ           ", d->ZAPSBEZ           , L_DEZAP_ZAPSBEZ            )
    PRINT( "ZAPATCCODE        ", d->ZAPATCCODE        , L_DEZAP_ZAPATCCODE         )
    PRINT( "ZAPHLNR           ", d->ZAPHLNR           , L_DEZAP_ZAPHLNR            )
    PRINT( "ZAPALNR1          ", d->ZAPALNR1          , L_DEZAP_ZAPALNR1           )
    PRINT( "ZAPKZAL1          ", d->ZAPKZAL1          , L_DEZAP_ZAPKZAL1           )
    PRINT( "ZAPALNR2          ", d->ZAPALNR2          , L_DEZAP_ZAPALNR2           )
    PRINT( "ZAPKZAL2          ", d->ZAPKZAL2          , L_DEZAP_ZAPKZAL2           )
    PRINT( "ZAPANRH           ", d->ZAPANRH           , L_DEZAP_ZAPANRH            )
    PRINT( "ZAPVE             ", d->ZAPVE             , L_DEZAP_ZAPVE              )
    PRINT( "ZAPSART           ", d->ZAPSART           , L_DEZAP_ZAPSART            )
/*    PRINT( "ZAPSVON           ", d->ZAPSVON           , L_DEZAP_ZAPSVON            )
    PRINT( "ZAPSBIS           ", d->ZAPSBIS           , L_DEZAP_ZAPSBIS            )
    PRINT( "ZAPSRYT           ", d->ZAPSRYT           , L_DEZAP_ZAPSRYT            ) */
    PRINT( "ZAPSEK            ", d->ZAPSEK            , L_DEZAP_ZAPSEK             )
    PRINT( "ZAPLOE            ", d->ZAPLOE            , L_DEZAP_ZAPLOE             )
    PRINT( "ZAPSPERR          ", d->ZAPSPERR          , L_DEZAP_ZAPSPERR           )
    PRINT( "ZAPABDA           ", d->ZAPABDA           , L_DEZAP_ZAPABDA            )
    PRINT( "ZAPAHDAT          ", d->ZAPAHDAT          , L_DEZAP_ZAPAHDAT           )
    PRINT( "ZAPPRZUAB         ", d->ZAPPRZUAB         , L_DEZAP_ZAPPRZUAB          )
    PRINT( "ZAPGESKL          ", d->ZAPGESKL          , L_DEZAP_ZAPGESKL           )
    PRINT( "ZAPFEUKL          ", d->ZAPFEUKL          , L_DEZAP_ZAPFEUKL           )
    PRINT( "ZAPWIRK           ", d->ZAPWIRK           , L_DEZAP_ZAPWIRK            )
    PRINT( "ZAPORPA           ", d->ZAPORPA           , L_DEZAP_ZAPORPA            )
    PRINT( "ZAPFEPR           ", d->ZAPFEPR           , L_DEZAP_ZAPFEPR            )
    PRINT( "ZAPIMSC           ", d->ZAPIMSC           , L_DEZAP_ZAPIMSC            )
    PRINT( "ZAPABDC           ", d->ZAPABDC           , L_DEZAP_ZAPABDC            )
    PRINT( "ZAPMEDK           ", d->ZAPMEDK           , L_DEZAP_ZAPMEDK            )
    PRINT( "ZAPSIW            ", d->ZAPSIW            , L_DEZAP_ZAPSIW             )
    PRINT( "ZAPINFO           ", d->ZAPINFO           , L_DEZAP_ZAPINFO            )
    PRINT( "ZAPKAT4           ", d->ZAPKAT4           , L_DEZAP_ZAPKAT4            )
    PRINT( "ZAPGREPG          ", d->ZAPGREPG          , L_DEZAP_ZAPGREPG           )
    PRINT( "ZAPINFGR          ", d->ZAPINFGR          , L_DEZAP_ZAPINFGR           )
    PRINT( "ZAPPAEND          ", d->ZAPPAEND          , L_DEZAP_ZAPPAEND           )
    PRINT( "ZAPKOLO           ", d->ZAPKOLO           , L_DEZAP_ZAPKOLO            )
    PRINT( "ZAPAANR           ", d->ZAPAANR           , L_DEZAP_ZAPAANR            )
    PRINT( "ZAPNRTI           ", d->ZAPNRTI           , L_DEZAP_ZAPNRTI            )
    PRINT( "ZAPAEP            ", d->ZAPAEP            , L_DEZAP_ZAPAEP             )
    PRINT( "ZAPAVP            ", d->ZAPAVP            , L_DEZAP_ZAPAVP             )
    PRINT( "ZAPGEP            ", d->ZAPGEP            , L_DEZAP_ZAPGEP             )
    PRINT( "ZAPGEPNA          ", d->ZAPGEPNA          , L_DEZAP_ZAPGEPNA           )
    PRINT( "ZAPEINH           ", d->ZAPEINH           , L_DEZAP_ZAPEINH            )
    PRINT( "ZAPABEZ           ", d->ZAPABEZ           , L_DEZAP_ZAPABEZ            )
    PRINT( "ZAPDRFO           ", d->ZAPDRFO           , L_DEZAP_ZAPDRFO            )
    PRINT( "ZAPAPCK           ", d->ZAPAPCK           , L_DEZAP_ZAPAPCK            )
    PRINT( "ZAPLGE            ", d->ZAPLGE            , L_DEZAP_ZAPLGE             )
    PRINT( "ZAPBRE            ", d->ZAPBRE            , L_DEZAP_ZAPBRE             )
    PRINT( "ZAPHOE            ", d->ZAPHOE            , L_DEZAP_ZAPHOE             )
    PRINT( "ZAPVOL            ", d->ZAPVOL            , L_DEZAP_ZAPVOL             )
    PRINT( "ZAPGEW            ", d->ZAPGEW            , L_DEZAP_ZAPGEW             )
    PRINT( "ZAPBUEN           ", d->ZAPBUEN           , L_DEZAP_ZAPBUEN            )
    PRINT( "ZAPZURA           ", d->ZAPZURA           , L_DEZAP_ZAPZURA            )
    PRINT( "ZAPKRABHV         ", d->ZAPKRABHV         , L_DEZAP_ZAPKRABHV          )
    PRINT( "ZAPTHER           ", d->ZAPTHER           , L_DEZAP_ZAPTHER            )
    PRINT( "ZAPWGR            ", d->ZAPWGR            , L_DEZAP_ZAPWGR             )
    PRINT( "ZAPLZEIT          ", d->ZAPLZEIT          , L_DEZAP_ZAPLZEIT           )
    PRINT( "ZAPGIFT1          ", d->ZAPGIFT1          , L_DEZAP_ZAPGIFT1           )
    PRINT( "ZAPGIFT2          ", d->ZAPGIFT2          , L_DEZAP_ZAPGIFT2           )
    PRINT( "ZAPGIFT3          ", d->ZAPGIFT3          , L_DEZAP_ZAPGIFT3           )
    PRINT( "ZAPREZ            ", d->ZAPREZ            , L_DEZAP_ZAPREZ             )
    PRINT( "ZAPAPO            ", d->ZAPAPO            , L_DEZAP_ZAPAPO             )
    PRINT( "ZAPTAX            ", d->ZAPTAX            , L_DEZAP_ZAPTAX             )
    PRINT( "ZAPOPI            ", d->ZAPOPI            , L_DEZAP_ZAPOPI             )
    PRINT( "ZAPTIER           ", d->ZAPTIER           , L_DEZAP_ZAPTIER            )
    PRINT( "ZAPVBED           ", d->ZAPVBED           , L_DEZAP_ZAPVBED            )
    PRINT( "ZAPVBA           ", d->ZAPVBA           , L_DEZAP_ZAPVBA            )
    PRINT( "ZAPVBB           ", d->ZAPVBB           , L_DEZAP_ZAPVBB            )
    PRINT( "ZAPVBC           ", d->ZAPVBC           , L_DEZAP_ZAPVBC            )
    PRINT( "ZAPVB1         ", d->ZAPVB1         , L_DEZAP_ZAPVB1          )
    PRINT( "ZAPVB2        ", d->ZAPVB2        , L_DEZAP_ZAPVB2         )
    PRINT( "ZAPVB3          ", d->ZAPVB3          , L_DEZAP_ZAPVB3           )
    PRINT( "ZAPVB4           ", d->ZAPVB4           , L_DEZAP_ZAPVB4            )
    PRINT( "ZAPSEKB           ", d->ZAPSEKB           , L_DEZAP_ZAPSEKB            )
    PRINT( "ZAPNF             ", d->ZAPNF             , L_DEZAP_ZAPNF              )
    PRINT( "ZAPPZNS           ", d->ZAPPZNS           , L_DEZAP_ZAPPZNS            )
    PRINT( "ZAPAHDL           ", d->ZAPAHDL           , L_DEZAP_ZAPAHDL            )
    PRINT( "ZAPAUSL           ", d->ZAPAUSL           , L_DEZAP_ZAPAUSL            )
    PRINT( "ZAPRAKT           ", d->ZAPRAKT           , L_DEZAP_ZAPRAKT            )
    PRINT( "ZAPNAK            ", d->ZAPNAK            , L_DEZAP_ZAPNAK             )
    PRINT( "ZAPNART           ", d->ZAPNART           , L_DEZAP_ZAPNART            )
    PRINT( "ZAPK08            ", d->ZAPK08            , L_DEZAP_ZAPK08             )
    PRINT( "ZAPK20            ", d->ZAPK20            , L_DEZAP_ZAPK20             )
    PRINT( "ZAPKK             ", d->ZAPKK             , L_DEZAP_ZAPKK              )
    PRINT( "ZAPNLH            ", d->ZAPNLH            , L_DEZAP_ZAPNLH             )
    PRINT( "ZAPNGH            ", d->ZAPNGH            , L_DEZAP_ZAPNGH             )
    PRINT( "ZAPNGR            ", d->ZAPNGR            , L_DEZAP_ZAPNGR             )
    PRINT( "ZAPKLIP           ", d->ZAPKLIP           , L_DEZAP_ZAPKLIP            )
    PRINT( "ZAPRESP           ", d->ZAPRESP           , L_DEZAP_ZAPRESP            )
    PRINT( "ZAPMELD           ", d->ZAPMELD           , L_DEZAP_ZAPMELD            )
    PRINT( "ZAPHERD           ", d->ZAPHERD           , L_DEZAP_ZAPHERD            )
    PRINT( "ZAPVERD           ", d->ZAPVERD           , L_DEZAP_ZAPVERD            )
    PRINT( "ZAPVEDM           ", d->ZAPVEDM           , L_DEZAP_ZAPVEDM            )
    PRINT( "ZAPMWST           ", d->ZAPMWST           , L_DEZAP_ZAPMWST            )
    PRINT( "ZAPBBU            ", d->ZAPBBU            , L_DEZAP_ZAPBBU             )
    PRINT( "ZAPBKCA           ", d->ZAPBKCA           , L_DEZAP_ZAPBKCA            )
    PRINT( "ZAPBKVK           ", d->ZAPBKVK           , L_DEZAP_ZAPBKVK            )
    PRINT( "ZAPFEUER          ", d->ZAPFEUER          , L_DEZAP_ZAPFEUER           )
    PRINT( "ZAPBKZO           ", d->ZAPBKZO           , L_DEZAP_ZAPBKZO            )
    PRINT( "ZAPAUTO           ", d->ZAPAUTO           , L_DEZAP_ZAPAUTO            )
    PRINT( "ZAPDYN            ", d->ZAPDYN            , L_DEZAP_ZAPDYN             )
    PRINT( "ZAPWAKO           ", d->ZAPWAKO           , L_DEZAP_ZAPWAKO            )
    PRINT( "ZAPHORE           ", d->ZAPHORE           , L_DEZAP_ZAPHORE            )
    PRINT( "ZAPNGF            ", d->ZAPNGF            , L_DEZAP_ZAPNGF             )
    PRINT( "ZAPMWE            ", d->ZAPMWE            , L_DEZAP_ZAPMWE             )
    PRINT( "ZAPAFEPR          ", d->ZAPAFEPR          , L_DEZAP_ZAPAFEPR           )
    PRINT( "ZAPNEGA           ", d->ZAPNEGA           , L_DEZAP_ZAPNEGA            )
    PRINT( "ZAPPOOL           ", d->ZAPPOOL           , L_DEZAP_ZAPPOOL            )
    PRINT( "ZAPHOME           ", d->ZAPHOME           , L_DEZAP_ZAPHOME            )
    PRINT( "ZAPGSG            ", d->ZAPGSG            , L_DEZAP_ZAPGSG             )
    PRINT( "ZAPLWA            ", d->ZAPLWA            , L_DEZAP_ZAPLWA             )
    PRINT( "ZAPKV             ", d->ZAPKV             , L_DEZAP_ZAPKV              )
    PRINT( "ZAPSKTOF          ", d->ZAPSKTOF          , L_DEZAP_ZAPSKTOF           )
    PRINT( "ZAPPRISMA         ", d->ZAPPRISMA         , L_DEZAP_ZAPPRISMA          )
    PRINT( "ZAPZUZA           ", d->ZAPZUZA           , L_DEZAP_ZAPZUZA            )
    PRINT( "ZAPPRISO          ", d->ZAPPRISO          , L_DEZAP_ZAPPRISO           )
    PRINT( "ZAPK25            ", d->ZAPK25            , L_DEZAP_ZAPK25             )
    PRINT( "ZAPKBEZU          ", d->ZAPKBEZU          , L_DEZAP_ZAPKBEZU           )
    PRINT( "ZAPIHNR           ", d->ZAPIHNR           , L_DEZAP_ZAPIHNR            )
    PRINT( "ZAPIZLA           ", d->ZAPIZLA           , L_DEZAP_ZAPIZLA            )
    PRINT( "ZAPMISK           ", d->ZAPMISK           , L_DEZAP_ZAPMISK            )
    PRINT( "ZAPS1             ", d->ZAPS1             , L_DEZAP_ZAPS1              )
    PRINT( "ZAPS2             ", d->ZAPS2             , L_DEZAP_ZAPS2              )
    PRINT( "ZAPS3             ", d->ZAPS3             , L_DEZAP_ZAPS3              )
    PRINT( "ZAPS4             ", d->ZAPS4             , L_DEZAP_ZAPS4              )
    PRINT( "ZAPS5             ", d->ZAPS5             , L_DEZAP_ZAPS5              )
    PRINT( "ZAPPERF           ", d->ZAPPERF           , L_DEZAP_ZAPPERF            )
    PRINT( "ZAPZYTO           ", d->ZAPZYTO           , L_DEZAP_ZAPZYTO            )
    PRINT( "ZAPZEKS           ", d->ZAPZEKS           , L_DEZAP_ZAPZEKS            )
    PRINT( "ZAPTFG            ", d->ZAPTFG            , L_DEZAP_ZAPTFG             )
    PRINT( "ZAPSKK            ", d->ZAPSKK            , L_DEZAP_ZAPSKK             )
    PRINT( "ZAPKZBUEN         ", d->ZAPKZBUEN         , L_DEZAP_ZAPKZBUEN          )
    PRINT( "ZAPPSS            ", d->ZAPPSS            , L_DEZAP_ZAPPSS             )
    PRINT( "ZAPCHARGE         ", d->ZAPCHARGE         , L_DEZAP_ZAPCHARGE          )
    PRINT( "ZAPNALI           ", d->ZAPNALI           , L_DEZAP_ZAPNALI            )
    PRINT( "ZAPWART           ", d->ZAPWART           , L_DEZAP_ZAPWART            )
    PRINT( "ZAPMIBO           ", d->ZAPMIBO           , L_DEZAP_ZAPMIBO            )
    PRINT( "ZAPGST            ", d->ZAPGST            , L_DEZAP_ZAPGST             )
    PRINT( "ZAPPRISMAE        ", d->ZAPPRISMAE        , L_DEZAP_ZAPPRISMAE         )
    PRINT( "ZAPEKRAB          ", d->ZAPEKRAB          , L_DEZAP_ZAPEKRAB           )
    PRINT( "ZAPBTMGRP         ", d->ZAPBTMGRP         , L_DEZAP_ZAPBTMGRP          )
    PRINT( "ZAPKEYTXT         ", d->ZAPKEYTXT         , L_DEZAP_ZAPKEYTXT          )
    PRINT( "ZAPWGRRGRP        ", d->ZAPWGRRGRP        , L_DEZAP_ZAPWGRRGRP         )
    PRINT( "ZAPNEKZ           ", d->ZAPNEKZ           , L_DEZAP_ZAPNEKZ            )
    PRINT( "ZAPNEINF          ", d->ZAPNEINF          , L_DEZAP_ZAPNEINF           )
    PRINT( "ZAPGEGU           ", d->ZAPGEGU           , L_DEZAP_ZAPGEGU            )
    PRINT( "ZAPMAMN           ", d->ZAPMAMN           , L_DEZAP_ZAPMAMN            )
    PRINT( "ZAPVRIS           ", d->ZAPVRIS           , L_DEZAP_ZAPVRIS            )
    PRINT( "ZAPMIDAS          ", d->ZAPMIDAS          , L_DEZAP_ZAPMIDAS           )
    PRINT( "ZAPARZMI          ", d->ZAPARZMI          , L_DEZAP_ZAPARZMI           )
    PRINT( "ZAPEKORG          ", d->ZAPEKORG          , L_DEZAP_ZAPEKORG           )
    PRINT( "ZAPMEDGAS         ", d->ZAPMEDGAS         , L_DEZAP_ZAPMEDGAS          )
    PRINT( "ZAPAMGAURE        ", d->ZAPAMGAURE        , L_DEZAP_ZAPAMGAURE         )
    PRINT( "ZAPKONTPPE        ", d->ZAPKONTPPE        , L_DEZAP_ZAPKONTPPE         )
    PRINT( "FILLER            ", d->FILLER            , L_DEZAP_FILLER             )
    PRINT( " ", " ", 2 )
    Close( dz );

    return;
  }

/*** OPEN *********************************************************************/

  static FILE *Open( const char *ch )
  {
    char* dat = 0;
    const char* log_file = "ldeb.dat";

	FILE* fp = NULL;

#ifdef UNSER_UEBERFLIEGER
    sprintf( dat, "%s/ldeb.dat", getenv( "LOG_PATH" ) );
#else
    const char* str = getenv( "LOG_PATH" );
    if ( str != NULL )
	{
        size_t path_length = strlen(str);
		path_length += strlen(log_file);
		/*adjust for a) path limiter (slash) b) 0-termination*/
		path_length += 2;

		dat = malloc(sizeof(char) * path_length);
		memset(dat, 0, path_length);

		sprintf( dat, "%s/%s", str, log_file );
	}
    else
	{
        size_t path_length = strlen(log_file);
		path_length += 1;
		dat = malloc(sizeof(char) * path_length);
		memset(dat, 0, path_length);
		sprintf( dat, log_file );
	}
#endif
	fp = fopen(dat, ch);
	
	/*cleanup*/
	free(dat);

    return fp;
  }

/*** CLOSE ********************************************************************/

  static void Close( FILE *dz )
  {
    fclose( dz );
    return;
  }
