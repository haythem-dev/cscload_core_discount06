/* ---------------------------------------------------------------------- *
 * Aufgabe        : Preistest			                                  *
 * ---------------------------------------------------------------------- *
 * Autor          : Hoerath                                               *
 * erstellt am    : 02.02.2005                                            *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "znb_gen_li.h"
#include "sql_zliart.h"
//#include "zpreitst.h"


/* ---------------------------------------------------------------------- */
int IsLIGrossoNull( double liGep )
{
    return liGep >= -0.01 && liGep <= 0.01;
}

/* ---------------------------------------------------------------------- */
int TestPreis_Aenderung( struct CLIART *li,
                         long dc_gro, long dc_avp, 
                         long art_gro, long art_aep, long art_avp )
{
  return 0;
}


/* ---------------------------------------------------------------------- */
int TestPreis_Neuaufnahme( struct CLIART *li )
{
  return 1;
}
