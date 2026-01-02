// GenIfaLieferung.cpp: Implementierung der Klasse CGenIfaLieferung.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "GenIfaLieferung.h"
#include <hdatum/phodate.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CGenIfaLieferung::CGenIfaLieferung()
{

}

CGenIfaLieferung::~CGenIfaLieferung()
{

}


/* --- Include-Dateien einbinden ---------------------------------------- */

#define TAB  0x09
#define CR   0x0d
#define LF   0x0a
#define DEND 0x1a

#define MAX_ZEILE 1000


long CGenIfaLieferung::GenLiefer_Ili ( long lieferdatum, char *verz, char *errmld )
{
	FILE *fd;
	char pfad[500];
	strcpy( pfad, verz );
	strcat( pfad, "/liefer.ili" );
	fd = fopen( pfad, "w" );
	if ( fd == NULL )
	{
		strcpy( errmld, "liefer.ili wurde nicht erzeugt" );
		return 1;
	}

	fprintf( fd, "LBIK;IFA-Infodienst;1000026804-000040-02-20000801;" \
		         "1000026804-000030-02;;TWZEPF;%ld;\n", lieferdatum );
	fprintf( fd, "LEIS;136;Pharma Rechenzentrum;Herr Karlheinz Peetz;Postfach 2154;" \
		         "90711 Fuerth;1000026804;20000529;136;Pharma Rechenzentrum;" \
				 "Herr Karlheinz Peetz;Postfach 2154;D-90711 Fuerth;K.Peetz@Phoenix-AG.de;;\n" );
	fprintf( fd, "LAIS;IFA GmbH;Hajo Schmitt;Schillerstr. 6;76872 Steinweiler;" \
	             "phoenix@hajosoft.de;06349/929112;06349/3641;\n" );
	fprintf( fd, "LPIS;020106;Festbetragsdatei analog PHAGRO vom %ld / " \
		         "powered by Schmitt;00006188;20000801;;20000715;;\n", lieferdatum );
	fprintf( fd, "LKIS;003001;Festbetragszuordnungen / alle gueltigen / " \
		         "nur geaenderte Inhalte;00006308;\n" );
	fprintf( fd, "LKSS;00006308;IC09;216;Festbetragszuordnungssatz;\n" );                            
	fprintf( fd, "LDIS;00006308;DTTENAT;;;;;liefd001.ild;14716;20000719143230;\n" );                 
	fprintf( fd, "LBIE;IFA-Infodienst;1000026804-000040-02-20000801;" \
		         "1000026804-000030-02;;TWZEPF;20000725;14;\n" );

	fclose( fd );
	return 0;
}

void CGenIfaLieferung::Gen_KMPK_Satz( char *buf, long tagesdatum )
{
	sprintf( buf, 
		     "KMPK;003001;00006308;Festbetragszuordnungen / alle gueltigen / nur geaenderte Inhalte;" \
			 "%ld;;;;",
			 tagesdatum
			);
}

void CGenIfaLieferung::Gen_IC01_Satz( char *buf, char *ssatz, long datum, long pzn, long betrag )
{
	char C00SSATZ;
	long C00PZNFB;
	long C00GDAT;
	long C00FB;

	C00SSATZ = *ssatz;
	C00GDAT  = datum;
	C00PZNFB = pzn;
	C00FB = betrag;

	sprintf( buf, 
		     "IC09;%c;%ld;%ld;;;%ld;;", 
			 C00SSATZ,
			 C00PZNFB,
			 C00GDAT,
			 C00FB );
}

void CGenIfaLieferung::Gen_ASAS_Satz( char *buf, long anz )
{
	sprintf( buf, "ASAS;IC09;%ld;Festbetragszuordnungssatz;", anz );
}


void CGenIfaLieferung::Gen_KMPE_Satz( char *buf, long anz, long tagesdatum )
{
	sprintf( buf, 
		     "KMPE;003001;00006308;Festbetragszuordnungen / alle gueltigen / nur geaenderte Inhalte;" \
			 "%ld;;;;%ld;",
			 tagesdatum,
			 anz + 3
			);

}


/*	PZN;Festbetrag_DM;Festbetrag_Euro */
/*	649;91,69;46,89 */
/*  oder */
/*  PZN|Festbetrag_Euro| */
/*  649|0.0| */

/* PZN */
int CGenIfaLieferung::ScanPzn( int nPos, char trenn, long *pzn, char *zeile )
{
	int i;
	char *str;
	char *p_feld;
	char feld[MAX_ZEILE+1];
	str = zeile;
	i = 1;
	while ( *str && i < nPos )
	{
		while ( *str && *str != trenn )
			str++;
		if ( *str == trenn )
		{
			str++;
			i++;
		}
	}
	if ( *str == '\0' )
		return -2;

	p_feld = feld;

	while ( *str && *str != trenn ) *p_feld++ = *str++;
	if ( *str != trenn )	return -1;
	*p_feld = '\0';

	*pzn = atol( feld );// PZN8 --> Umwandlung erst in zpifestb
	return 0;
}

int CGenIfaLieferung::ScanFestb( int nPos, char trenn, long *betrag, char *zeile )
{
	int i;
	char *str;
	char *p_feld;
	char feld[MAX_ZEILE+1];
	str = zeile;
	i = 1;
	while ( *str && i < nPos )
	{
		while ( *str && *str != trenn )
			str++;
		if ( *str == trenn )
		{
			str++;
			i++;
		}
	}
	if ( *str == '\0' )
		return -3;

	p_feld = feld;
	while ( *str && *str != trenn ) 
	{
		if (*str == ',' )
			*p_feld++ = '.';
		else
			*p_feld++ = *str;
		str++;
	}
	if ( *str != trenn )	return -1;
	*p_feld = '\0';
	*betrag = (long)( 100.0*atof( feld ) + 0.1 );
	return 0;
}

int CGenIfaLieferung::ScanZeile( int nPosPzn, int nPosFest, char trenn, 
								 char *zeile, long *pzn, long *betrag )
{
	int i;
	int s;

	i = (int)strlen( zeile ) - 1;
	while ( i >= 0 && zeile[i] == ' ' ) i--;
	if ( zeile[i] != trenn )
	{
		zeile[++i] = trenn;
		zeile[++i] = '\0';
	}

	if ( *zeile == trenn )
		return 1;

	s = ScanPzn  ( nPosPzn, trenn, pzn, zeile );
	if ( s == 0 )
		s = ScanFestb( nPosFest, trenn, betrag, zeile );
	return s;


}

long CGenIfaLieferung::getDatum( char *str )
{
	char *stra;
	stra = str;
	while ( *str && isdigit( *str ) ) str++;
	if ( *str != '\0' )
		return -1;
	return atol( stra );
}


long CGenIfaLieferung::GenLiefd001( int nPosPzn, int nPosFest, char *trenn, 
								    char *ssatz, long nGuelDat, long nLiefDat, 
								    char *datei, char *verz, char *errmld )
{
	FILE *fd;
	FILE *fd_out;
	int  j;
	int  ok;
	long s;
	long anz;
	int  endzeile;

	long pzn;
	long betrag;
	char ze;
	char *anfZeile;
	char zeile[MAX_ZEILE+2];
	char pfad[500];
	char buf[200];

	if ( !( *ssatz == '0' || *ssatz == '1' || *ssatz == '2' || *ssatz == '3' ) )
	{
		strcpy( errmld, "C00SSATZ = 0 | 1 | 2 | 3 \n" );
		return -11;
	}


	fd = fopen( datei, "r" );
	if ( fd == NULL )
	{
	   sprintf( errmld, "%s nicht vohanden", datei );
	   return -1;
	}

	strcpy( pfad, verz );
	strcat( pfad, "/liefd001.ild" );
	fd_out = fopen( pfad, "w" );
	if ( fd_out == NULL )
	{
		strcpy( errmld, "liefd001.ild wurde nicht erzeugt" );
		return 1;
	}


	anz = 0;

	s = 0;

	Gen_KMPK_Satz( buf, nLiefDat );
	fprintf( fd_out, "%s\n", buf );

	ok = 1;
	while ( ok )
	{
		j = 0;
		endzeile = 0;
		while ( ok && !endzeile )
		{
			ok = fread( &ze, 1, 1, fd ) == 1;
			if ( ok )
			{
				if ( ze == LF )
					endzeile = 1;
				else if ( ze != CR )
				{
					ok = j < MAX_ZEILE;
					if ( ok )
						zeile[j++] = ze;
				}
			}
		} 
		zeile[j] = '\0';

		anfZeile = zeile;
		if ( *anfZeile == *trenn )	/* Trennzeichen am Zeilenanfang ueberlesen */
			anfZeile++;

		if ( ok )
		{  
			int ret;

			ret = ScanZeile( nPosPzn, nPosFest, *trenn, anfZeile, &pzn, &betrag );
			if ( ret == 0 )
			{   
				Gen_IC01_Satz( buf, ssatz, nGuelDat, pzn, betrag );
				fprintf( fd_out, "%s\n", buf );
				anz++;
			}
			else  if ( ret == -1 )
			{
				ok = 0;
			    strcpy( errmld, "Zeile hat falsches Format" );
				s = -1;
			}
			else  if ( ret == -2 )
			{
				ok = 0;
			    strcpy( errmld, "PZN Position falsch" );
				s = -1;
			}
			else  if ( ret == -3 )
			{
				ok = 0;
			    strcpy( errmld, "Festbetrags Position falsch" );
				s = -1;
			}
		}
	}

	if ( s == 0 )
	{
		Gen_ASAS_Satz( buf, anz );
		fprintf( fd_out, "%s\n", buf );
		Gen_KMPE_Satz( buf, anz, nLiefDat );
		fprintf( fd_out, "%s\n", buf );
	}

	fclose( fd );
	fclose( fd_out );
	
	if ( s != 0 )
		return s;
	return GenLiefer_Ili ( nLiefDat, verz, errmld );
}


long CGenIfaLieferung::GenFeb_2( int  nPosPzn, int nPosFest, char *trenn, 
								 char *ssatz, long nGuelDat, long nLiefDat,
								 char *datei, char *verz, char *errmld )
{
	*errmld = '\0';

	if ( strlen( trenn ) != 1 )
	{
		strcpy( errmld, "trenn darf nur ein Zeichen lang sein\n" );
		return 1;
	}
	return GenLiefd001( nPosPzn, nPosFest, trenn, ssatz, nGuelDat, nLiefDat, datei, verz, errmld );
}


long CGenIfaLieferung::GenFeb_ili( char *errmld )
{
	return GenLiefer_Ili ( PhoToday(), ".", errmld );
}
