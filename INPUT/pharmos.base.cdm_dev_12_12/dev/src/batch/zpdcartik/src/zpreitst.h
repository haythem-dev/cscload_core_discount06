#ifndef ZPREITST_INCLUDED
#define ZPREITST_INCLUDED

int TestPreis_Neuaufnahme( struct ZDCART *dc );
int TestPreis_Aenderung( struct ZDCART *dc, long ProzentPM,
                         long ifa_gro, long ifa_aep, long ifa_avp, 
                         long art_gro, long art_aep, long art_avp, char taxkzwrgrp);



/* --- Taxartikel ----- */
#define TAXART_NONE '9'
#define TAXART_NETTO '0'
#define TAXART_1 '1'
#define TAXART_2 '2'
#define TAXART_3 '3'
#define TAXART_4 '4'

#define SONDERGRKZ "S"

#endif
