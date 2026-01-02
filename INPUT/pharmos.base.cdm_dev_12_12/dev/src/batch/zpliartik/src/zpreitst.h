#ifndef ZPREITST_INCLUDED
#define ZPREITST_INCLUDED

int TestPreis_Neuaufnahme( struct CLIART *li );
int TestPreis_Aenderung( struct CLIART *li,
                         long ifa_gro, long ifa_avp, 
                         long art_gro, long art_aep, long art_avp);

#endif
