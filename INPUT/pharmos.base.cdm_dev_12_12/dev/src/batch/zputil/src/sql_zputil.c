/* ---------------------------------------------------------------------- *
 * Aufgabe        : SQL - Funktionen für zputil  					      *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 08.07.2005                                            *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/wdbups/wpp_dbas.h>

#include <eklibs/wdbups/wpp_prot.h>
#include <voodoo_table_header/pflege.h>
#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>
#include <eklibs/sqltabs/tabsqld.h>

#include "util_form.h"

#include "sql_zputil.h"

/* ------------------------------------------------------------------- */
int TransferToCsc(long art_no, char * errmld)
{
	int i = 1;
	int status = 0;
	char sql[500];
	
	while ( i <= anz_columns )
	{
		if ( strstr(upd_columns[i], "NAHRUNGSERGAENZUNG" ) != NULL )
		{
			sprintf( sql, 
			"insert into ctransfercsc ( articleno, fieldname, fieldvalue ) "
			"values ( %ld, '%s', '%s' )",
			art_no, upd_columns[i], upd_values[i] );

			status = SqlExecuteImm( sql );
	
			break;
		}
	
		i++;
	}

	if ( status != 0 )
	{
		strcpy( errmld, "ctransfercsc (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int WriteZAPflege(long art_no, long date, char * errmld)
{
	int status = 0;
	char sql[500];
	long dummy;

	sprintf( sql, 
		"select datum from zapflege where artikel_nr = %ld "
		"and datum = %ld",
		art_no, date );
	
    status = SqlRead( sql, &dummy, NULL );

	if ( status == 100 ) 
	{
		sprintf( sql, 
			"insert into zapflege ( artikel_nr, datum ) "
			"values ( %ld, %ld )",
			art_no, date );

		status = SqlExecuteImm( sql );
	}
	
	if ( status != 0 )
	{
		strcpy( errmld, "zapflege (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int WriteGrpPflege(long comp_no, char * dezap_sa, long date, char * errmld)
{
	long status;
	long datum;
	char sql[500];
	char company[10];
	
	sprintf ( company, "%05ld", comp_no );

	sprintf( sql, 
		"select datum from zgrppflege where key_gruppe = '%s' "
		"and datum = %ld and dezap_sa = '%s'",
		company, date, dezap_sa );

    status = SqlRead( sql, &datum, NULL );
	
    if ( status == 100 ) 
	{
		sprintf( sql, 
			"insert into zgrppflege ( key_gruppe, datum, dezap_sa ) "
			"values ( '%s', %ld, '%s' )",
			company, date, dezap_sa );

		status = SqlExecuteImm( sql );
	}
	
	if ( status != 0 )
	{
		strcat( errmld, "\nzgrppflege (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}

/* ------------------------------------------------------------------- */
int WritePznPflege(long art_no, char * dezap_sa, long date, char * errmld)
{
	int status;
	long datum;
  char sql[120] = { 0 };
	
	sprintf( sql, 
		"select datum from zpznpflege where artikel_nr = %ld "
		"and datum = %ld and dezap_sa = '%s'",
		art_no, date, dezap_sa );
	
    status = SqlRead( sql, &datum, NULL );

    if ( status == 100 ) 
	{
		sprintf( sql, 
			"insert into zpznpflege ( artikel_nr, datum, dezap_sa ) "
			"values ( %ld, %ld, '%s' )",
			art_no, date, dezap_sa );

		status = SqlExecuteImm( sql );
	}
	
	if ( status != 0 )
	{
		strcat( errmld, "\nzpznpflege (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return status;
}


/* ------------------------------------------------------------------- */
int sel_zartikel (const int *Fd_ZArtikel, char* art_nr, char* errmld)
{
	long lStatus;
	char PK [100];
	static int temp_created = 0;

	if ( *Fd_ZArtikel < 0 ) 
		return -1;


	sprintf ( PK, "ARTIKEL_NR=%7s", art_nr );

	lStatus = FdReadRecord( *Fd_ZArtikel, PK, &m_BufOldZArt, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zartikel (Suche nach Artikel): " );
		strcat( errmld, DynErrmld() );
	}

	if ( lStatus == 0 )
	{
		char statm_temp [200];

		if ( temp_created == 0 )
		{
			sprintf( statm_temp, "create temp table zputil_temp ("        
								 "ARTIKEL_NR INTEGER NOT NULL ) with no log" );

			lStatus = SqlExecuteImm( statm_temp );

			if ( lStatus != 0 )
				strcpy( errmld, DynErrmld() );
			else
				temp_created = 1;
		}

		if ( temp_created == 1 )
		{
			sprintf ( statm_temp, "insert into zputil_temp ( artikel_nr ) values ( %s )", art_nr );

			lStatus = SqlExecuteImm ( statm_temp );

			if ( lStatus != 0 )
				strcpy( errmld, DynErrmld() );
		}
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_zartfrance(const int *Fd_ZArtFrance, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1000] = "";
	char PK [100];

	struct ZARTFRANCE	BufZArtFranceOld;
	struct ZARTFRANCE	BufZArtFranceAkt;

	if ( *Fd_ZArtFrance < 0 ) 
		return -1;

	if(fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s", upd_values[0]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZArtFrance, PK, &BufZArtFranceOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZARTFRANCE (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( sql, "update zartfrance %s "
					"where articleno = %s",
					upd_section, upd_values[0] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartfrance (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile(fd_prot);

		FdReadRecord(*Fd_ZArtFrance, PK, &BufZArtFrance, errmld);

		if (memcmp(&BufZArtFrance, &m_BufOldZArtFrance, sizeof(m_BufOldZArtFrance)) != 0)
		{
			lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtFrance, PK, &BufZArtFranceAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTFRANCE (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartfranceTab[] = "zartfrance";
			static void *zartfranceDesc  = NULL;

			lStatus = SqlGetTabDesc( zartfranceTab, &zartfranceDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTFRANCE (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZArtFranceOld, &BufZArtFranceAkt, sizeof(BufZArtFranceAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartfranceDesc,
											&BufZArtFranceOld, &BufZArtFranceAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

int ArticleEligibleForConsignment(char* articleNum, char* consigNo, int valType)
{
	char sql[2048];
	memset(sql, 0, 2048);
	double count = 0.0;
	long lStatus = 0;

	if ((valType == 0) || (valType == 2))
	{
		// the current EkZDP rule is that all manufacturer numbers are accepted as consigment partners, which are defined as manufacturers
		sprintf(sql,
			"SELECT count(hersteller_nr) FROM herstel WHERE hersteller_nr = %s", consigNo);
		count = 0.0;
		lStatus = SqlRead(sql, &count, NULL);
		if (lStatus != 0)
		{
			char* error = DynErrmld();
			printf("Sql error:%s\n", error);
			return -1;
		}
		// abort here, if validation failed
		if ((int)count == 0)
		{
			return 0;
		}
	}

	if ((valType == 1) || (valType == 2))
	{ 
		// validation rule for consignment labeling is dependent to article's manufacturer and that its not narcotic but a batch article
		sprintf(sql,
			"SELECT count(artikel_nr) "
			"FROM zartikel "
			"WHERE hersteller_nr IN ("
			"SELECT hersteller_nr FROM herstel WHERE konsig_partner_nr > 0) "
			"AND artikel_nr = %s "
			"AND chargenartikel > 0 "
			"AND btm = 0", articleNum);

		count = 0.0;
		lStatus = SqlRead(sql, &count, NULL);
		if (lStatus != 0)
		{
			char* error = DynErrmld();
			printf("Sql error:%s\n", error);
			return -1;
		}
		// abort here, if validation failed
		if ((int)count == 0)
		{
			return 0;
		}
	}
	return 1;
}

int fill_upd_section(char* upd_section)
{
	int result = 0;
	char temp_upd_section[250];
	int i = 1;
	
	if(anz_columns > 0)
	{
		memset(temp_upd_section, '\0', 150);
		strcat(upd_section, "set ");
	}
	
	while(i <= anz_columns)
	{
		// subsequentdelivery values columns start with column 3 - first 2 columns belong to PK
		if (m_eUpdTable != UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG || i > 1)
		{
			sprintf(temp_upd_section, "%s = '%s'", upd_columns[i], upd_values[i]);
			strcat(upd_section, temp_upd_section);

			if (i+1 <= anz_columns)
			{
				strcat(upd_section, ", ");
			}
		}
		i++;
	}

	// update lastchange and probably lastuser fields automatically
	if (m_eUpdTable == UPD_CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG)
	{
		sprintf(temp_upd_section, ", lastchangedate = CURRENT");
		strcat(upd_section, temp_upd_section);
	}
	else if (m_eUpdTable == UPD_ZARTIKEL)
	{   // Aenderungsdatum und Bearbeiter in zartikel setzen
		sprintf(temp_upd_section, ", datum_aender = %ld, bearbeiter = '%s'", GetPhoDate(), user);
		strcat(upd_section, temp_upd_section);
	}

	if(strlen(upd_section) == 0)
	{
		result = -1;
	}

	return result;
}

int fill_ins_section(char* ins_section_fields, char* ins_section_values)
{
	return fill_ins_section_uni(1, ins_section_fields, ins_section_values);
}

// if PK contains more then one field...
int fill_ins_section_uni(int pkCount, char* ins_section_fields, char* ins_section_values)
{
	int result = 0;
	char temp_ins_field[150];
	char temp_ins_value[150];
	int i = pkCount;

	while (i <= anz_columns)
	{
		sprintf(temp_ins_field, "%s", upd_columns[i]);
		strcat(ins_section_fields, temp_ins_field);

		sprintf(temp_ins_value, "'%s'", upd_values[i]);
		strcat(ins_section_values, temp_ins_value);

		i++;

		if (i <= anz_columns)
		{
			strcat(ins_section_fields, ", ");
			strcat(ins_section_values, ", ");
		}
	}

	if (strlen(ins_section_fields) == 0 || strlen(ins_section_values) == 0)
	{
		result = -1;
	}

	return result;
}

/* ------------------------------------------------------------------- */
int upd_zartswitzerland(const int *Fd_ZArtSwitzerland, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1000] = "";
	char PK [100];

	struct ZARTSWITZERLAND	BufZArtSwitzerlandOld;
	struct ZARTSWITZERLAND	BufZArtSwitzerlandAkt;

	if ( *Fd_ZArtSwitzerland < 0 ) 
		return -1;

	if(fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTIKEL_NR=%7s", upd_values[0]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZArtSwitzerland, PK, &BufZArtSwitzerlandOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZARTSWITZERLAND (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( sql, "update zartswitzerland %s "
					"where artikel_nr = %s",
					upd_section, upd_values[0] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartswitzerland (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile(fd_prot);

		FdReadRecord(*Fd_ZArtSwitzerland, PK, &BufZArtSwitzerland, errmld);

		if (memcmp(&BufZArtSwitzerland, &m_BufOldZArtSwitzerland, sizeof(m_BufOldZArtSwitzerland)) != 0)
		{
			lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtSwitzerland, PK, &BufZArtSwitzerlandAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTSWITZERLAND (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartswitzerlandTab[] = "zartswitzerland";
			static void *zartswitzerlandDesc  = NULL;

			lStatus = SqlGetTabDesc( zartswitzerlandTab, &zartswitzerlandDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTSWITZERLAND (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZArtSwitzerlandOld, &BufZArtSwitzerlandAkt, sizeof(BufZArtSwitzerlandAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartswitzerlandDesc,
											&BufZArtSwitzerlandOld, &BufZArtSwitzerlandAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_zartserbia(const int *Fd_ZArtSerbia, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1000] = "";
	char PK [100];

	struct ZARTSERBIA	BufZArtSerbiaOld;
	struct ZARTSERBIA	BufZArtSerbiaAkt;

	if ( *Fd_ZArtSerbia < 0 ) 
		return -1;

	if(fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s", upd_values[0]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZArtSerbia, PK, &BufZArtSerbiaOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZARTSERBIA (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( sql, "update zartserbia %s "
					"where articleno = %s",
					upd_section, upd_values[0] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartserbia (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile(fd_prot);

		FdReadRecord(*Fd_ZArtSerbia, PK, &BufZArtSerbia, errmld);

		if (memcmp(&BufZArtSerbia, &m_BufOldZArtSerbia, sizeof(m_BufOldZArtSerbia)) != 0)
		{
			lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtSerbia, PK, &BufZArtSerbiaAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTSERBIA (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartserbiaTab[] = "zartserbia";
			static void *zartserbiaDesc  = NULL;

			lStatus = SqlGetTabDesc( zartserbiaTab, &zartserbiaDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTSERBIA (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZArtSerbiaOld, &BufZArtSerbiaAkt, sizeof(BufZArtSerbiaAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartserbiaDesc,
											&BufZArtSerbiaOld, &BufZArtSerbiaAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_zartaustria(const int *Fd_ZArtAustria, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1000] = "";
	char PK [100];

	struct ZARTAUSTRIA	BufZArtAustriaOld;
	struct ZARTAUSTRIA	BufZArtAustriaAkt;

	if ( *Fd_ZArtAustria < 0 ) 
		return -1;

	if(fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTIKEL_NR=%7s", upd_values[0]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZArtAustria, PK, &BufZArtAustriaOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZARTAUSTRIA (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( sql, "update zartaustria %s "
					"where artikel_nr = %s",
					upd_section, upd_values[0] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartaustria (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile(fd_prot);

		FdReadRecord(*Fd_ZArtAustria, PK, &BufZArtAustria, errmld);

		if (memcmp(&BufZArtAustria, &m_BufOldZArtAustria, sizeof(m_BufOldZArtAustria)) != 0)
		{
			lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtAustria, PK, &BufZArtAustriaAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTAUSTRIA (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartaustriaTab[] = "zartaustria";
			static void *zartaustriaDesc  = NULL;

			lStatus = SqlGetTabDesc( zartaustriaTab, &zartaustriaDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTAUSTRIA (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZArtAustriaOld, &BufZArtAustriaAkt, sizeof(BufZArtAustriaAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartaustriaDesc,
											&BufZArtAustriaOld, &BufZArtAustriaAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ---------------------- */
int TrimANRH (char *s)
{
	int i;
	
	for (i = (int)strlen(s)-1; i >= 0; i--)
	{
		if (s[i] != ' ')
		{
			break;
		}
	}

	s[i+1] = '\0';

	return i;
}

/* ------------------------------------------------------------------- */
static char  PflegeTab[] = "pflege";
static void *PflDesc  = NULL;

/* ------------------------------------------------------------------- */
long InitPflegeTab( char *errmld )
{
    static int alloc_status = 0;
    static long s;
    static char smeld[80];
    if ( alloc_status == 0 )
    {
        alloc_status = 1;
        s = SqlGetTabDesc( PflegeTab, &PflDesc, DESC_DEFAULT, smeld );
    }
    if ( s != 0 )
    {
        PflDesc = NULL;
        strcpy( errmld, smeld );
    }
    return s;
}

/* ------------------------------------------------------------------- */
void ClosePflegeTab( )
{
    if ( PflDesc != NULL )
    {
        SqlFreeTabDesc ( PflDesc );
        PflDesc = NULL;
    }
}

/* ------------------------------------------------------------------- */
long InsertPflegePhysically( struct PFLEGE *Buf_Pflege )

{
	char sql[300];
	sprintf( sql, "insert into pflege " \
		          "(PFLEGE_NR, DATUM, UHRZEIT, ANWENDER, STATUS, FEHLERTEXT, FUNKTION, INFO) values " \
				  "(%ld, %ld, %ld, '%s', '%s', '%s', %d, '%s')",
				  Buf_Pflege->PFLEGE_NR,
				  Buf_Pflege->DATUM,
				  Buf_Pflege->UHRZEIT,
				  Buf_Pflege->ANWENDER,
				  Buf_Pflege->STATUS,
				  Buf_Pflege->FEHLERTEXT,
				  Buf_Pflege->FUNKTION,
				  Buf_Pflege->INFO );
	return SqlExecuteImm( sql );
}

/* ------------------------------------------------------------------- */
long Insert_Pflege( long besla_nr, long artikel_nr )
{
    long s;
    struct PFLEGE  Buf_Pflege;
	char key_select[15];
	char errmld[100];
	
    Buf_Pflege.PFLEGE_NR = 0;
    Buf_Pflege.DATUM     = GetPhoDate();
    Buf_Pflege.UHRZEIT   = GetPhoTime();
    strcpy( Buf_Pflege.ANWENDER, user);
    strcpy( Buf_Pflege.STATUS, "0" );
    strcpy( Buf_Pflege.FEHLERTEXT, " " );
    Buf_Pflege.FUNKTION = 1;
    sprintf( Buf_Pflege.INFO, "%ld %ld", artikel_nr, besla_nr );

    strcpy( key_select, "pflege_nr=0");

    s = Insert_Protokoll( P_INSERT, V_PROTO_VERTEIL, PflDesc,
                          &Buf_Pflege, &Buf_Pflege,
                          key_select, user, "", 0, errmld );

	if ( s == 0 )
		s = InsertPflegePhysically( &Buf_Pflege );

    return s;
}

/* ------------------------------------------------------------------- */
int upd_zartikel(const int *Fd_ZArtikel, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1000] = "";
	char PK [100];
	char tvalue[100] = "";
	char tmsg[1500] = "";

	struct ZARTIKEL	BufZArtikelOld;
	struct ZARTIKEL	BufZArtikelAkt;

// --- SR-081422
	int i = 1;
	int found = 0;
	char str[12];
	char name[100];
// --- 
	
	if ( *Fd_ZArtikel < 0 ) 
		return -1;

	if(fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf ( PK, "ARTIKEL_NR=%7s", upd_values[0] );

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZArtikel, PK, &BufZArtikelOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZARTIKEL (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

// --- SR-081422
	strcpy (name, " ");
	while ( i <= anz_columns )
	{
		if ( strstr(upd_columns[i], "DATUM_AH" ) != NULL )
		{
			found = 1;

			if ( atol( upd_values[i] ) != 0 )
			{
				ConvFromPhoDate( str, atol( upd_values[i] ), "mmjj" );

				WriteZAPflege( atol(upd_values[0]), atol( upd_values[i] ), errmld);
			}
			else 
				strcpy (str, "    ");

			if (strcmp(database, "zpps2at") == 0  || strcmp(database, "iat21") == 0    ||
				strcmp(database, "zpps2pat") == 0 || strcmp(database, "iat21pre") == 0  )
			{
				sprintf (name, ", artikel_name = substr(artikel_name, 1, 25) || ' %s'", str);
			}
			// in CH den Namen nur ändern, wenn AH- Datum kleiner "heute" = wenn AH in der Zukunft, wird der Name erst am entsprechenden Tag durch zpdailyclosing verändert.
			else if ( (strcmp(database, "ich21pre") != 0  && strcmp(database, "ich21") != 0) || atol( upd_values[i] ) <= GetPhoDate() )
			{
				sprintf (name, ", artikel_name = substr(artikel_name, 1, 26) || '%s'", str);
			}
			else
				found = 0;

			break;
		}
		i++;
	}

	// add plausi check for konsig partner no - consignment labelling
	i = 1;
	while (i <= anz_columns)
	{
		if (m_eUpdTable == UPD_ZARTIKEL && strcmp(upd_columns[i], "KONSIG_PARTNER_NR") == 0)
		{
			// check if article is eligible for consignment labelling
			if (ArticleEligibleForConsignment(upd_values[0], upd_values[i], 0) <= 0)
			{ // skip not eligible
				lStatus = 2;
				strcpy(tvalue, upd_values[i]);
			}
		}
		i++;
	}

// --- 

// SR-23021761: Plausiprüfung: wenn zartikel.cmi_flag = 1 dann darf nicht zartikel.apo_auto_faehig_knapp = 1 oder
//	zartikel.apo_auto_faehig_rowa = 1 gesetzt werden
	if (m_BufOldZArt.CMI_FLAG == 1)
	{
		i = 1;
		while (i <= anz_columns)
		{
			if (strcmp(upd_columns[i], "APO_AUTO_FAEHIG_KNAPP") == 0 || strcmp(upd_columns[i], "APO_AUTO_FAEHIG_ROWA") == 0)
			{
				if (upd_values[i] != 0)
				{
					lStatus = 1;
				}
				break;
			}
			i++;
		}
	}
	if (lStatus == 0)
	{
		sprintf ( sql, "update zartikel %s %s "
						"where artikel_nr = %s",
						upd_section, name, upd_values[0] );

		lStatus = SqlExecuteImm( sql );
	}
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartikel (Update einer Zeile): " );
		
		if (lStatus == 1)
		{
			strcat( errmld, "APO_AUTO_FAEHIG_KNAPP oder APO_AUTO_FAEHIG_ROWA kann nicht gesetzt werden, da Kennzeichen für Direktgeschäft gesetzt ist." );
		}
		else if (lStatus == 2)
		{
			sprintf(tmsg, "KONSIG_PARTNER_NR (%s) kann nicht im Artikel (%s) gesetzt werden, da die Nr nicht als Hersteller im System existiert.", tvalue, upd_values[0]);
			strcat(errmld, tmsg);
		}
		else
		{
		strcat( errmld, DynErrmld() );
		}
	}
	else
	{
		WriteProtZeile( fd_prot );

		FdReadRecord( *Fd_ZArtikel, PK, &BufZArtUpd, errmld );

		if ( memcmp( &BufZArtUpd, &m_BufOldZArt, sizeof(m_BufOldZArt) ) != 0 )
		{
			lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtikel, PK, &BufZArtikelAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTIKEL (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartikelTab[] = "zartikel";
			static void *zartikelDesc  = NULL;

			lStatus = SqlGetTabDesc( zartikelTab, &zartikelDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTIKEL (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZArtikelOld, &BufZArtikelAkt, sizeof(BufZArtikelAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartikelDesc,
											&BufZArtikelOld, &BufZArtikelAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */

		if (lStatus != 0) /* Im Fehlerfall Verarbeitung abbrechen */
		{
			return lStatus;
		}

		TransferToCsc(atol(upd_values[0]), errmld);

		// nur in der Schweiz !!!
		if (strcmp(database, "zpps1ch") == 0	|| strcmp(database, "ich21")	== 0 ||
			strcmp(database, "zpps1pch") == 0	|| strcmp(database, "ich21pre") == 0)
		{
	// --- SR-081422
			if (found == 1 )
			{
				sprintf ( sql, "update carticlelang set articlename = substr(articlename, 1, 26) || '%s' "
						"where articleno = %s and langid = 'FR'",
						str, upd_values[0] );

				SqlExecuteImm( sql );

				WritePznPflege(atoi(upd_values[0]), "11", tages_datum, errmld);
			}
	// --- 

			// Versorgung Tabelle artnrbl, wenn zartikel.hersteller_nr o. awl1 o. artikel_nr_herst geändert wurden
			if ((BufZArtUpd.HERSTELLER_NR != m_BufOldZArt.HERSTELLER_NR && BufZArtUpd.AWL1 == 0) ||
				 BufZArtUpd.AWL1		  != m_BufOldZArt.AWL1									 ||
				 strcmp(BufZArtUpd.ARTIKEL_NR_HERST, m_BufOldZArt.ARTIKEL_NR_HERST) != 0)
			{
				int beslanr;

				if (BufZArtUpd.AWL1 > 0)
					beslanr = BufZArtUpd.AWL1;
				else
					beslanr = BufZArtUpd.HERSTELLER_NR;

				// zunächst alte Einträge löschen, wenn zartikel.hersteller_nr o. awl1 geändert wurden 
				if (	BufZArtUpd.HERSTELLER_NR != m_BufOldZArt.HERSTELLER_NR  ||
						BufZArtUpd.AWL1			 != m_BufOldZArt.AWL1	)
				{
					int beslanr_old;

					if (m_BufOldZArt.AWL1 > 0)
						beslanr_old = m_BufOldZArt.AWL1;
					else
						beslanr_old = m_BufOldZArt.HERSTELLER_NR;

					sprintf ( sql, "delete from artnrbl where besla_nr = %ld and artikel_nr = %ld",
									beslanr_old, m_BufOldZArt.ARTIKEL_NR );

					SqlExecuteImm( sql );

					// Versorgung Tabelle bliesort, wenn zartikel.hersteller_nr o. awl1 geändert wurden 
					if ( sel_bliesort ( &Fd_Bliesort, m_BufOldZArt.ARTIKEL_NR, beslanr_old , &bliesort, errmld ) == 0 )
					{
						bliesort.BESLA_NR = beslanr;

						upd_bliesort	( &Fd_Bliesort,  &bliesort, beslanr_old, errmld);
					}
					else
					{
						bliesort.BESLA_NR = beslanr;
						bliesort.ARTIKEL_NR = m_BufOldZArt.ARTIKEL_NR;

						ins_bliesort	( &Fd_Bliesort,  &bliesort, errmld);
					}		

					Insert_Pflege( beslanr, m_BufOldZArt.ARTIKEL_NR );
				}
				
				// so wird nur der artnrbl-Satz geschrieben / geändert, wo PZN und HNR übereinstimmen
				if ( sel_artnrbl ( &Fd_ArtnrBl, m_BufOldZArt.ARTIKEL_NR, beslanr , &artbl, errmld ) == 0 )
				{
					TrimANRH(BufZArtUpd.ARTIKEL_NR_HERST);
					if ( strcmp(BufZArtUpd.ARTIKEL_NR_HERST,"") == 0 )
					{
						del_artnrbl ( &Fd_ArtnrBl, errmld);
					}
					else
					{
						strcpy ( artbl.ARTIKEL_NR_BLIEFER, BufZArtUpd.ARTIKEL_NR_HERST );
				
						upd_artnrbl	( &Fd_ArtnrBl,  &artbl, errmld);
					}
				}
				else
				{
					strcpy ( artbl.ARTIKEL_NR_BLIEFER, BufZArtUpd.ARTIKEL_NR_HERST );

					artbl.BESLA_NR = beslanr;
					artbl.ARTIKEL_NR = m_BufOldZArt.ARTIKEL_NR;

					ins_artnrbl	( &Fd_ArtnrBl,  &artbl, errmld);
				}			
			}
		}
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_artnrbl		( const int *Fd_ArtnrBl,  const long art_nr, const long her_nr, 
						struct ARTNRBL *artbl, char* errmld)
{
	long lStatus;
	char PK [100];

	if ( *Fd_ArtnrBl < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", her_nr, art_nr );

	lStatus = FdReadRecord( *Fd_ArtnrBl, PK, artbl, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldArtBl = *artbl;  
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nartnrbl (Suche nach Artikel): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_bliesort		( const int *Fd_Bliesort,  const long art_nr, const long her_nr, 
						struct BLIESORT *bliesort, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Bliesort < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", her_nr, art_nr );

	lStatus = FdReadRecord( *Fd_Bliesort, PK, bliesort, errmld );
	
	if ( lStatus == 0 )
	{
		m_BufOldBLieSort = *bliesort;  
	}
	else if ( lStatus != 100 )
	{
		strcat( errmld, "\nbliesort (Suche nach Artikel): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_bliesort_direkt(const int* Fd_Bliesort, char* art_nr, char* besla_nr, char* errmld)
{
	long lStatus;
	char PK[100];

	if (*Fd_Bliesort < 0)
		return -1;

	sprintf(PK, "BESLA_NR=%5s and ARTIKEL_NR=%7s", besla_nr, art_nr);

	lStatus = FdReadRecord(*Fd_Bliesort, PK, &m_BufOldBLieSort, errmld);

	if (lStatus != 0 && lStatus != 100)
	{
		strcpy(errmld, "bliesort (Suche nach bliesort): \n");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_artnrbl_loop		( const int *Fd_ArtnrBl,  const long art_nr, char* artnrherst, char* errmld)
{
	long lStatus;
	int fd;
	char PK [100];
	char sql[300];
	struct ARTNRBL anb;
	int i;
	
		
	if ( *Fd_ArtnrBl < 0 ) 
		return -1;

	//sprintf ( PK, "ARTIKEL_NR=%ld and ARTIKEL_NR_BLIEFER='%s'", art_nr, artnrherst );
	sprintf ( PK, "ARTIKEL_NR=%7ld", art_nr );
	sprintf ( sql,"SELECT %s FROM ARTNRBL WHERE %s", PROJECTION_ARTNRBL, PK );

	lStatus = SqlOpenCs( &fd, sql );
	if ( lStatus != 0 ) 
	{
		strcat( errmld, DynErrmld() );
		return lStatus;
	}
	
	i = 0;    
	m_nNrOfArtnrbl = 0;

	while ( lStatus == 0 && i < 20 )
	{
		lStatus = SqlFetch( fd, 1, &anb, NULL );
		if ( lStatus == 0 )
		{
			if (strncmp(anb.ARTIKEL_NR_BLIEFER, artnrherst, L_ARTNRBL_ARTIKEL_NR_BLIEFER - 1) == 0)
			{
				m_ArtnrblBuf[i] = anb;
				m_ArtnrblBufOld[i] = m_ArtnrblBuf[i];
				i++;
			}
			else
				m_nNrOfArtnrbl++;
		}
	}

	strcat( errmld, DynErrmld() );
	SqlCloseCs( fd );
	m_nNrOfArtnrblToUpdate = i;
	m_nNrOfArtnrbl = m_nNrOfArtnrbl + m_nNrOfArtnrblToUpdate;
	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_artnrbl		( const int *Fd_ArtnrBl,  struct ARTNRBL *artbl, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_ArtnrBl < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", artbl->BESLA_NR, artbl->ARTIKEL_NR );

	lStatus = FdUpdateRecord( *Fd_ArtnrBl, artbl, &m_BufOldArtBl, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nartnrbl (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_bliesort		( const int *Fd_Bliesort,  struct BLIESORT *bliesort, const long beslaOld, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Bliesort < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", beslaOld, bliesort->ARTIKEL_NR );

	lStatus = FdUpdateRecord( *Fd_Bliesort, bliesort, &m_BufOldBLieSort, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nbliesort (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

int upd_bliesort_direkt(const int* Fd_Bliesort, const int* Fd_ZANeuheit, char* errmld)
{
	long lStatus = 0;
	char PK[100];

	if (*Fd_Bliesort < 0)
		return -1;

	/* set bliesort values */
	bliesort.ARTIKEL_NR = m_BufOldBLieSort.ARTIKEL_NR;
	bliesort.BESLA_NR = m_BufOldBLieSort.BESLA_NR;

	sprintf(PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", m_BufOldBLieSort.BESLA_NR, bliesort.ARTIKEL_NR);

	lStatus = FdUpdateRecord(*Fd_Bliesort, &bliesort, &m_BufOldBLieSort, PK, errmld);

	if (lStatus != 0)
	{
		strcpy(errmld, "bliesort (Update einer Zeile): \n");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);
	}

	if (lStatus != 0)
	{
		return lStatus;
	}
	else
    {
		lStatus = del_zaneuheit( &Fd_ZANeuheit, bliesort.ARTIKEL_NR, errmld );

		if (lStatus != 0)
		{
			strcpy(errmld, "zaneuheit (Delete einer Zeile): \n");
			strcat(errmld, DynErrmld());
		}
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_artnrbl_loop	( const int *Fd_ArtnrBl,  
							char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_ArtnrBl < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", artbl.BESLA_NR, artbl.ARTIKEL_NR );

	lStatus = FdUpdateRecord( *Fd_ArtnrBl, &artbl, &m_BufOldArtBl, 
										 PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nartnrbl (Update einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_artnrbl		( const int *Fd_ArtnrBl,  struct ARTNRBL *artbl, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_ArtnrBl < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", artbl->BESLA_NR, artbl->ARTIKEL_NR );

	lStatus = FdInsertRecord( *Fd_ArtnrBl, artbl, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nartnrbl (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_bliesort		( const int *Fd_Bliesort,  struct BLIESORT *bliesort, char *errmld)
{
	long lStatus = 0;
	char PK [100];
	
	if ( *Fd_Bliesort < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", bliesort->BESLA_NR, bliesort->ARTIKEL_NR );

	lStatus = FdInsertRecord( *Fd_Bliesort, bliesort, PK, errmld);

	if ( lStatus != 0 )
	{
		strcat( errmld, "\nbliesort (Insert einer Zeile): \n" );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_bliesort_direkt(const int* Fd_Bliesort, const int* Fd_ZANeuheit, char* errmld)
{
	long lStatus = 0;
	char PK[100];

	if (*Fd_Bliesort < 0)
		return -1;

	/* set bliesort values from the input file */
	bliesort.ARTIKEL_NR = atol(upd_values[0]);
	bliesort.BESLA_NR = atol(upd_values[1]);

	sprintf( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", bliesort.BESLA_NR, bliesort.ARTIKEL_NR );

	lStatus = FdInsertRecord(*Fd_Bliesort, &bliesort, PK, errmld);

	if (lStatus != 0)
	{
		strcpy(errmld, "bliesort (Insert einer Zeile): \n");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);
	}

	if (lStatus != 0)
	{
		return lStatus;
	}
	else
	{
	    lStatus = del_zaneuheit( &Fd_ZANeuheit, bliesort.ARTIKEL_NR, errmld );

		if (lStatus != 0)
		{
			strcpy(errmld, "zaneuheit (Delete einer Zeile): \n");
			strcat(errmld, DynErrmld());
		}
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_zaneuheit( const int* Fd_ZANeuheit, long artikelnr, char* errmld )
{
	long lStatus = 0;
	char PK[100];

	struct ZANEUHEIT ZANeuheitBuf;

	ZANeuheitBuf.ARTIKEL_NR = artikelnr;

	sprintf( PK, "ARTIKEL_NR=%7ld and PFLEGEPROGRAMM='1'", ZANeuheitBuf.ARTIKEL_NR );

	lStatus = FdReadRecord( *Fd_ZANeuheit, PK, &ZANeuheitBuf, errmld );

	if ( lStatus == 0 )
	{
		lStatus = FdDeleteRecord( *Fd_ZANeuheit, &ZANeuheitBuf, PK, errmld );
	}
	else if ( lStatus == 100 )
	{
		lStatus = 0;
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartpreis (const int *Fd_ZArtPreis, char* art_nr, char* datgueltab, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ZArtPreis < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s and DATUMGUELTIGAB=%s", art_nr, datgueltab );

	lStatus = FdReadRecord( *Fd_ZArtPreis, PK, &m_BufOldZPreis, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zartpreis (Suche nach Preis): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ---------------------------------------- */
int sel_zartpreis_current( const int *Fd_ZArtPreis, char* art_nr, char* datgueltab, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ZArtPreis < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s and DATUMGUELTIGAB<%s ORDER BY DATUMGUELTIGAB desc", art_nr, datgueltab );

	lStatus = FdReadRecord( *Fd_ZArtPreis, PK, &m_BufOldZPreis, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zartpreis (Suche nach Preis für Wertuebernahme for Insert): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- 
int upd_zartpreis(const int *Fd_ZArtPreis, char* errmld)
{
	long lStatus = 0;
	char sql [1000];
	char upd_section[500];
	
	if ( *Fd_ZArtPreis < 0 ) 
		return -1;

	switch ( anz_columns )
	{
	case 2:
		sprintf ( upd_section, "set %s = '%s'",
					upd_columns[2], upd_values[2]);
		break;
	case 3:
		sprintf ( upd_section, "set %s = '%s', %s = '%s'",
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3]);
		break;
	case 4:
		sprintf ( upd_section, "set %s = '%s', %s = '%s', %s = '%s'",
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4]);
		break;
	case 5:
		sprintf ( upd_section, "set %s = '%s', %s = '%s', %s = '%s', %s = '%s'",
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5]);
		break;
	default:
		return -1;
		break;
	}

	sprintf ( sql, "update zartpreis %s "
					"where artikel_nr = %s and datumgueltigab = %s",
					upd_section, upd_values[0], upd_values[1] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartpreis (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		char PK [100];
	
		sprintf ( PK, "artikel_nr=%s and datumgueltigab=%s", upd_values[0], upd_values[1] );

		FdReadRecord( *Fd_ZArtPreis, PK, &BufZPreisUpd, errmld );

		if ( memcmp( &BufZPreisUpd, &m_BufOldZPreis, sizeof(m_BufOldZPreis) ) != 0 )
			WriteZAPflege( atol(upd_values[0]), atol ( upd_values[1] ), errmld);
	}

	return lStatus;
}*/

/* ------------------------------------------------------------------- */
int ins_zartpreis(const int *Fd_ZArtPreis, char* errmld)
{
	long lStatus = 0;

	char PK [100];
	sprintf ( PK, "ARTIKEL_NR=%7s and DATUMGUELTIGAB=%s", upd_values[0], upd_values[1] );

	BufZPreisIns.DATUMGUELTIGAB = atol( upd_values[1] );
	
	lStatus = FdInsertRecord( *Fd_ZArtPreis, &BufZPreisIns, PK, errmld);

	if ( lStatus == 0 )
		WriteZAPflege( atol(upd_values[0]), BufZPreisIns.DATUMGUELTIGAB, errmld);	
	else
	{
		strcpy( errmld, "zartpreis (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_ccpvalperiod(const int *Fd_CcpValPeriod, const int *Fd_ZArtikel, char* errmld)
{
	long lStatus = 0;

	char PK [100];
	sprintf ( PK, "ARTICLE_NO_PACK=%7ld", m_CArtComPack_CurrentPackNo );

	BufCcpValPeriod.ARTICLE_NO_PACK = m_CArtComPack_CurrentPackNo;
	BufCcpValPeriod.COMPACK_TYPE = 1;
	
	lStatus = FdInsertRecord( *Fd_CcpValPeriod, &BufCcpValPeriod, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "ccpvalperiod (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		// bei Kopf- PZN auch zartikel.steller auf S setzen --> zapflege ???
		char sql [200];

		struct ZARTIKEL	BufZArtikelOld;
		struct ZARTIKEL	BufZArtikelAkt;

		sprintf ( PK, "ARTIKEL_NR=%7ld", m_CArtComPack_CurrentPackNo );
		sprintf ( sql, "update zartikel set steller = 'S', datum_aender = %ld, bearbeiter = '%s' where %s ", GetPhoDate(), user, PK);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		lStatus = FdReadRecord( *Fd_ZArtikel, PK, &BufZArtikelOld, errmld );

		if (lStatus != 0)
		{
			strcpy(errmld, "ZARTIKEL (Lesen einer Zeile): ");
			strcat(errmld, DynErrmld());
			return lStatus;
		}
		/* ----------------------------------------------------------------------------- */

		lStatus = SqlExecuteImm( sql );

		if (lStatus != 0) /* Im Fehlerfall Verarbeitung abbrechen */
		{
			return lStatus;
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtikel, PK, &BufZArtikelAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTIKEL (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartikelTab[] = "zartikel";
			static void *zartikelDesc  = NULL;

			lStatus = SqlGetTabDesc( zartikelTab, &zartikelDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTIKEL (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZArtikelOld, &BufZArtikelAkt, sizeof(BufZArtikelAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartikelDesc,
											&BufZArtikelOld, &BufZArtikelAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cdiscgrp(const int *Fd_CDiscGrp, char* errmld)
{
	long lStatus = 0;

	char PK [100];
	sprintf ( PK, "DISCOUNTGRPNO=%d", m_CDiscGrpMem_CurrentGroupNo );

	BufCDiscGrp.DISCOUNTGRPNO = m_CDiscGrpMem_CurrentGroupNo;
	strcpy(BufCDiscGrp.DESCRIPTION, "created by ZdpUtil automatically");
	BufCDiscGrp.DISCOUNTGRPTYPE = 0;
	BufCDiscGrp.CUSTOMERNO = 0;
	
	lStatus = FdInsertRecord( *Fd_CDiscGrp, &BufCDiscGrp, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cdiscgrp (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cgibatchentry(const int *Fd_CGiBatchEntry, char* errmld)
{
	long lStatus = 0;
	char sql [500];
	char PK[100];

	struct CGIBATCHENTRY	BufCGiBatchEntry;

	if ( *Fd_CGiBatchEntry < 0 ) 
		return -1;

	sprintf(PK, "ARTICLENO=%7s", upd_values[0] );

	sprintf ( sql, "insert into cgibatchentry (articleno, company_code, datefrom, dateto, date_changed) "
					"values (%s, %s, %s, %s, %ld)",
					upd_values[0], upd_values[1], upd_values[2], upd_values[3], tages_datum );

	lStatus = SqlExecuteImm( sql );

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cgibatchentry (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_CGiBatchEntry, PK, &BufCGiBatchEntry, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CGIBATCHENTRY (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cgibatchentryTab[] = "cgibatchentry";
			static void *cgibatchentryDesc  = NULL;

			lStatus = SqlGetTabDesc( cgibatchentryTab, &cgibatchentryDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CGIBATCHENTRY (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, cgibatchentryDesc,
										NULL, &BufCGiBatchEntry, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cdiscount_flexible(const int *Fd_CDiscount, char* errmld)
{
	long lStatus = 0;
	char sql [2500];
	char PK[1000];
	char temp[200];

	struct CDISCOUNT	BufCDiscount;

	char ins_section_fields[1000] = "";
	char ins_section_values[1000] = "";

	char section_pharmacygrp_field[20];
	char section_pharmacygrp_value[5];
	
	char section_pharmgrpexcl_field[20];
	char section_pharmgrpexcl_value[5];

	char section_pharmgrpexcl2_field[20];
	char section_pharmgrpexcl2_value[5];
	
	char section_pharmgrpexcl3_field[20];
	char section_pharmgrpexcl3_value[5];
		
	char section_internaldisc_field[20];
	char section_internaldisc_value[5];

	char section_monthlydisc_field[20];
	char section_monthlydisc_value[5];
	
	if ( *Fd_CDiscount < 0 || anz_columns < 4) // less than 4 fields not possible !
		return -1;

	if(fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s", upd_values[0]);

	int i = 1;

	while (i <= anz_columns)
	{
		sprintf(temp, " and %s = '%s'", upd_columns[i], upd_values[i]);
		strcat(PK, temp);

		i++;
	}

	if ( strstr(ins_section_fields, "PHARMACYGROUPID" ) == NULL )
	{
		sprintf ( section_pharmacygrp_field, "%s", "PHARMACYGROUPID, ");
		sprintf ( section_pharmacygrp_value, "%s", "'000', ");				
	}
	else
	{
		sprintf ( section_pharmacygrp_field, "%s", " ");
		sprintf ( section_pharmacygrp_value, "%s", " ");				
	}

	if ( strstr(ins_section_fields, "PHARMGRPEXCLUDED" ) == NULL )
	{
		sprintf ( section_pharmgrpexcl_field, "%s", "PHARMGRPEXCLUDED, ");
		sprintf ( section_pharmgrpexcl_value, "%s", "'000', ");				
	}
	else
	{
		sprintf ( section_pharmgrpexcl_field, "%s", " ");
		sprintf ( section_pharmgrpexcl_value, "%s", " ");				
	}

	if ( strstr(ins_section_fields, "PHARMGRPEXCL_2" ) == NULL )
	{
		sprintf ( section_pharmgrpexcl2_field, "%s", "PHARMGRPEXCL_2, ");
		sprintf ( section_pharmgrpexcl2_value, "%s", "'000', ");				
	}
	else
	{
		sprintf ( section_pharmgrpexcl2_field, "%s", " ");
		sprintf ( section_pharmgrpexcl2_value, "%s", " ");				
	}

	if ( strstr(ins_section_fields, "PHARMGRPEXCL_3" ) == NULL )
	{
		sprintf ( section_pharmgrpexcl3_field, "%s", "PHARMGRPEXCL_3, ");
		sprintf ( section_pharmgrpexcl3_value, "%s", "'000', ");				
	}
	else
	{
		sprintf ( section_pharmgrpexcl3_field, "%s", " ");
		sprintf ( section_pharmgrpexcl3_value, "%s", " ");				
	}

	if ( strstr(ins_section_fields, "INTERNALDISCOUNT" ) == NULL )
	{
		sprintf ( section_internaldisc_field, "%s", "INTERNALDISCOUNT, ");
		sprintf ( section_internaldisc_value, "%s", "'0', ");				
	}
	else
	{
		sprintf ( section_internaldisc_field, "%s", " ");
		sprintf ( section_internaldisc_value, "%s", " ");				
	}

	if ( strstr(ins_section_fields, "MONTHLYDISCOUNT" ) == NULL )
	{
		sprintf ( section_monthlydisc_field, "%s", "MONTHLYDISCOUNT, ");
		sprintf ( section_monthlydisc_value, "%s", "'0', ");				
	}
	else
	{
		sprintf ( section_monthlydisc_field, "%s", " ");
		sprintf ( section_monthlydisc_value, "%s", " ");				
	}

	sprintf ( sql, "INSERT INTO cdiscount ( articleno, %s, %s %s %s %s %s %s "
					"addondiscountok, paymenttermtype, no_multiple_qty, turnovercalcimpact) "
					"VALUES ( %ld, %s, %s %s %s %s %s %s "
					"'0', '0', '0', '0') ",
					ins_section_fields, section_pharmacygrp_field, section_pharmgrpexcl_field, section_internaldisc_field, 
						section_pharmgrpexcl2_field, section_pharmgrpexcl3_field, section_monthlydisc_field,
					atol(upd_values[0]), ins_section_values, section_pharmacygrp_value, section_pharmgrpexcl_value, section_internaldisc_value,
						section_pharmgrpexcl2_value, section_pharmgrpexcl3_value, section_monthlydisc_value );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "cdiscount (flexibler Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_CDiscount, PK, &BufCDiscount, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CDISCOUNT (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cdiscountTab[] = "cdiscount";
			static void *cdiscountDesc  = NULL;

			lStatus = SqlGetTabDesc( cdiscountTab, &cdiscountDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CDISCOUNT (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, cdiscountDesc,
										NULL, &BufCDiscount, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */

		if (lStatus != 0) /* Im Fehlerfall Verarbeitung abbrechen */
		{
			return lStatus;
		}

		WriteProtZeile( fd_prot );
		
		if ( atol(upd_values[0]) == 0) // PZN = 0 --> zgrppflege
		{
			int i = 1;
			int bFound = 0;
			int key = 0;

			while ( i <= anz_columns )
			{
				if ( strstr(upd_columns[i], "DISCOUNTGRPNO" ) != NULL )
				{
					key = atoi( upd_values[i] ); 
					bFound = 1;
					break;
				}
				i++;
			}

			if (bFound == 1 && key > 0 )
				lStatus = WriteGrpPflege( key, "2A", tages_datum, errmld );
			else
			{
				i = 1;

				while ( i <= anz_columns )
				{
					if ( strstr(upd_columns[i], "MANUFACTURERNO" ) != NULL )
					{
						key = atoi( upd_values[i] ); 
						bFound = 1;
						break;
					}
					i++;
				}

				if (bFound == 1 && key > 0)
					lStatus = WriteGrpPflege( key, "2B", tages_datum, errmld );
				else
					lStatus = WriteGrpPflege( 0, "2D", tages_datum, errmld );
			}
		}
		else
			lStatus = WritePznPflege( atol(upd_values[0]), "28", tages_datum, errmld );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_cartcompack(const int *Fd_CArtComPack, const int *Fd_ZArtikel, char* errmld)
{
	long lStatus = 0;
	char sql [300];
	char PK1 [100];
	char PK2 [100];

	struct ZARTIKEL	BufZArtikelOld;
	struct ZARTIKEL	BufZArtikelAkt;

	struct CARTCOMPACK	BufCArtComPackOld;

	if ( *Fd_CArtComPack < 0 ) 
		return -1;

	sprintf(PK1, "ARTIKEL_NR=%7s", upd_values[1]);
	sprintf(PK2, "ARTICLE_NO_PACK=%7s", upd_values[1]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZArtikel, PK1, &BufZArtikelOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZARTIKEL (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}

	lStatus = FdReadRecord( *Fd_CArtComPack, PK2, &BufCArtComPackOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "CARTCOMPACK (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	// VOR delete: bei allen Element- PZN´s auch zartikel.steller auf N zurücksetzen, wenn Element nicht noch Teil eines anderen Stellers ist!
	sprintf ( sql, "update zartikel set steller = 'N', datum_aender = %ld, bearbeiter = '%s' where artikel_nr in (select article_no_element from cartcompack where article_no_pack = %ld) and "
					"artikel_nr not in (select article_no_element from cartcompack where article_no_pack != %ld)",
					GetPhoDate(), user, atol(upd_values[1]), atol(upd_values[1]) );

	lStatus = SqlExecuteImm( sql );

	sprintf ( sql, "DELETE FROM cartcompack "
					"WHERE article_no_pack = %ld",
					atol(upd_values[1]));

	lStatus = SqlExecuteImm( sql );

	if ( lStatus == 0 )
	{
		lStatus = WritePznPflege( atol(upd_values[1]), "13", tages_datum, errmld );

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtikel, PK1, &BufZArtikelAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTIKEL (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartikelTab[] = "zartikel";
			static void *zartikelDesc  = NULL;

			lStatus = SqlGetTabDesc( zartikelTab, &zartikelDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTIKEL (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartikelDesc,
										&BufZArtikelOld, &BufZArtikelAkt, PK1,
										user, "", 0, errmld );

			if (lStatus != 0)
			{
				return lStatus;
			}

			static char  cartcompackTab[] = "cartcompack";
			static void *cartcompackDesc  = NULL;

			lStatus = SqlGetTabDesc( cartcompackTab, &cartcompackDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTCOMPACK (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_DELETE, V_PROTO_VERTEIL, cartcompackDesc,
										&BufCArtComPackOld, NULL, PK2,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}
	else
	{
		strcpy( errmld, "cartcompack (Delete für PackNo): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cartrefundfrance(char* errmld)
{
	long lStatus = 0;
	char sql [250];
	
	sprintf ( sql, "insert into cartrefundfrance(articleno, datefrom, reimbursement_type) values (%ld, %ld, '9')",
					atoi(upd_values[0]), atoi(upd_values[1]) );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "cartrefundfrance (Insert): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_zartpreis_future(const int *Fd_ZArtPreis, char* errmld)
{
	long lStatus = 0;
	char sql [250];
	char PK[100];

	struct ZARTPREIS	BufZArtPreis;

	if ( *Fd_ZArtPreis < 0 )
		return -1;

	sprintf(PK, "ARTIKEL_NR=%7s", upd_values[0]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZArtPreis, PK, &BufZArtPreis, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZARTPREIS (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */
	
	sprintf ( sql, "delete from zartpreis where artikel_nr = %ld and datumgueltigab > %ld",
					atoi(upd_values[0]), atoi(upd_values[1]) );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartpreis (Delete future): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			static char  zartpreisTab[] = "zartpreis";
			static void *zartpreisDesc  = NULL;

			lStatus = SqlGetTabDesc( zartpreisTab, &zartpreisDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTPREIS (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_DELETE, V_PROTO_VERTEIL, zartpreisDesc,
										&BufZArtPreis, NULL, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_cdiscgrpmem(const int *Fd_CDiscGrpMem, char* errmld)
{
	long lStatus = 0;
	char sql [250];
	char PK[100];

	struct CDISCGRPMEM	BufCDiscGrpMem;
	
	if ( *Fd_CDiscGrpMem < 0 ) 
		return -1;

	sprintf(PK, "DISCOUNTGRPNO=%s", upd_values[1]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_CDiscGrpMem, PK, &BufCDiscGrpMem, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "CDISCGRPMEM (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( sql, "DELETE FROM cdiscgrpmem "
					"WHERE discountgrpno = %ld",
					atol(upd_values[1]));

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus == 0 )
	{
		lStatus = WriteGrpPflege( atol(upd_values[1]), "31", tages_datum, errmld );

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			static char  cdiscgrpmemTab[] = "cdiscgrpmem";
			static void *cdiscgrpmemDesc  = NULL;

			lStatus = SqlGetTabDesc( cdiscgrpmemTab, &cdiscgrpmemDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CDISCGRPMEM (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_DELETE, V_PROTO_VERTEIL, cdiscgrpmemDesc,
										&BufCDiscGrpMem, NULL, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}
	else
	{
		strcpy( errmld, "cdiscgrpmem (Delete für GrpNo): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cartcompack(const int *Fd_CArtComPack, const int *Fd_ZArtikel, char* errmld)
{
	long lStatus = 0;
	char sql [2500];
	char PK [100];

	char ins_section_fields[1000] = "";
	char ins_section_values[1000] = "";

	struct CARTCOMPACK	BufCArtComPack;

	if ( *Fd_CArtComPack < 0 ) 
		return -1;

	if(fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLE_NO_PACK=%7ld", atol(upd_values[1]));
	
	sprintf ( sql, "INSERT INTO cartcompack ( article_no_element, %s) "
					"VALUES ( %ld, %s) ",
					ins_section_fields, 
					atol(upd_values[0]), ins_section_values);

	lStatus = SqlExecuteImm( sql );

	if ( lStatus == 0 )
	{
		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_CArtComPack, PK, &BufCArtComPack, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTCOMPACK (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cartcompackTab[] = "cartcompack";
			static void *cartcompackDesc  = NULL;

			lStatus = SqlGetTabDesc( cartcompackTab, &cartcompackDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTCOMPACK (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, cartcompackDesc,
										NULL, &BufCArtComPack, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */

		if (lStatus != 0) /* Im Fehlerfall Verarbeitung abbrechen */
		{
			return lStatus;
		}

		struct ZARTIKEL	BufZArtikelOld;
		struct ZARTIKEL	BufZArtikelAkt;

		sprintf(PK, "ARTIKEL_NR=%7s", upd_values[0]);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		lStatus = FdReadRecord( *Fd_ZArtikel, PK, &BufZArtikelOld, errmld );

		if (lStatus != 0)
		{
			strcpy(errmld, "ZARTIKEL (Lesen einer Zeile): ");
			strcat(errmld, DynErrmld());
			return lStatus;
		}
		/* ----------------------------------------------------------------------------- */

		// bei allen Element- PZN´s auch zartikel.steller auf T setzen!
		sprintf ( sql, "update zartikel set steller = 'T', datum_aender = %ld, bearbeiter = '%s' where artikel_nr = %ld ", 
						GetPhoDate(), user, atol(upd_values[0]) );

		lStatus = SqlExecuteImm( sql );

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtikel, PK, &BufZArtikelAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTIKEL (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartikelTab[] = "zartikel";
			static void *zartikelDesc  = NULL;

			lStatus = SqlGetTabDesc( zartikelTab, &zartikelDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTIKEL (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZArtikelOld, &BufZArtikelAkt, sizeof(BufZArtikelAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartikelDesc,
											&BufZArtikelOld, &BufZArtikelAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */

		if (lStatus != 0) /* Im Fehlerfall Verarbeitung abbrechen */
		{
			return lStatus;
		}

		WriteProtZeile( fd_prot );

		lStatus = WritePznPflege( atol(upd_values[1]), "13", tages_datum, errmld );
	}
	else
	{
		strcpy( errmld, "cartcompack (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cdiscgrpmem(const int *Fd_CDiscGrpMem, char* errmld)
{
	long lStatus = 0;
	char sql [2500];
	char PK [100];

	char ins_section_fields[1000] = "";
	char ins_section_values[1000] = "";

	struct CDISCGRPMEM	BufCDiscGrpMem;

	if ( *Fd_CDiscGrpMem < 0 ) 
		return -1;

	if(fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s", upd_values[0]);

	sprintf ( sql, "INSERT INTO cdiscgrpmem ( articleno, %s) "
					"VALUES ( %ld, %s) ",
					ins_section_fields, 
					atol(upd_values[0]), ins_section_values);

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus == 0 )
	{
		WriteProtZeile( fd_prot );

		lStatus = WriteGrpPflege( atol(upd_values[1]), "31", tages_datum, errmld );

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_CDiscGrpMem, PK, &BufCDiscGrpMem, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CDISCGRPMEM (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cdiscgrpmemTab[] = "cdiscgrpmem";
			static void *cdiscgrpmemDesc  = NULL;

			lStatus = SqlGetTabDesc( cdiscgrpmemTab, &cdiscgrpmemDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CDISCGRPMEM (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, cdiscgrpmemDesc,
										NULL, &BufCDiscGrpMem, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}
	else
	{
		strcpy( errmld, "cdiscgrpmem (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cdiscount(const int *Fd_CDiscount, struct CDISCOUNT *cdisc, char* errmld)
{
	long lStatus = 0;
	char PK [1000];

	if ( *Fd_CDiscount < 0 ) 
		return -1;

	sprintf ( PK,	"ARTICLENO=%7ld and DISCOUNTGRPNO=%ld and PHARMACYGROUPID='%s' and CUSTOMERNO=%ld "
					"and BASEQTY=%ld and GRPDISCOUNTTYP=%d and DISCOUNTTYPE=%d and DISCOUNTSPEC=%d "
					"and BASE_VALUE=%f and BASE_MULT_STD_QTY=%ld and DATEFROM=%ld and DATETO=%ld "
					"and MANUFACTURERNO=%ld and ARTCATEGORYNO=%ld and PAYMENTTARGETNO=%d ",
					cdisc->ARTICLENO,
					cdisc->DISCOUNTGRPNO,
					cdisc->PHARMACYGROUPID,
					cdisc->CUSTOMERNO,
					cdisc->BASEQTY,
					cdisc->GRPDISCOUNTTYP,
					cdisc->DISCOUNTTYPE,
					cdisc->DISCOUNTSPEC,
					cdisc->BASE_VALUE,
					cdisc->BASE_MULT_STD_QTY,
					cdisc->DATEFROM,
					cdisc->DATETO,
					cdisc->MANUFACTURERNO,
					cdisc->ARTCATEGORYNO,
					cdisc->PAYMENTTARGETNO);

	lStatus = FdDelayInsertRecord( *Fd_CDiscount, cdisc, PK, errmld);

	if ( lStatus == 0 )
	{
		lStatus = FdTransactWithoutWork(errmld);

		if ( lStatus == 0 )
		{
			if ( cdisc->ARTICLENO != 0 )
				lStatus = WritePznPflege( cdisc->ARTICLENO, "28", tages_datum, errmld );
			else
				lStatus = WriteGrpPflege( cdisc->DISCOUNTGRPNO, "28", tages_datum, errmld );
		}
	}
	else
	{
		if ( strstr(errmld, "-239" ) != NULL )
		{
			strcpy ( errmld, "");
			lStatus = 239; // duplicate index
		}
		else
		{
			strcpy( errmld, "cdiscount (Insert einer Zeile): " );
			strcat( errmld, DynErrmld() );
		}
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_cdiscount(const int *Fd_CDiscount, char* errmld)
{
	long lStatus = 0;
	char PK [1000];

	if ( *Fd_CDiscount < 0 ) 
		return -1;

	sprintf ( PK,	"ARTICLENO=%7ld and DISCOUNTGRPNO=%ld and PHARMACYGROUPID='%s' and CUSTOMERNO=%ld "
					"and BASEQTY=%ld and GRPDISCOUNTTYP=%d and DISCOUNTTYPE=%d and DISCOUNTSPEC=%d "
					"and BASE_VALUE=%f and BASE_MULT_STD_QTY=%ld and DATEFROM=%ld and DATETO=%ld "
					"and MANUFACTURERNO=%ld and ARTCATEGORYNO=%ld and PAYMENTTARGETNO=%d",
					m_BufOldCDiscountUnchanged.ARTICLENO,
					m_BufOldCDiscountUnchanged.DISCOUNTGRPNO,
					m_BufOldCDiscountUnchanged.PHARMACYGROUPID,
					m_BufOldCDiscountUnchanged.CUSTOMERNO,
					m_BufOldCDiscountUnchanged.BASEQTY,
					m_BufOldCDiscountUnchanged.GRPDISCOUNTTYP,
					m_BufOldCDiscountUnchanged.DISCOUNTTYPE,
					m_BufOldCDiscountUnchanged.DISCOUNTSPEC,
					m_BufOldCDiscountUnchanged.BASE_VALUE,
					m_BufOldCDiscountUnchanged.BASE_MULT_STD_QTY,
					m_BufOldCDiscountUnchanged.DATEFROM,
					m_BufOldCDiscountUnchanged.DATETO,
					m_BufOldCDiscountUnchanged.MANUFACTURERNO,
					m_BufOldCDiscountUnchanged.ARTCATEGORYNO,
					m_BufOldCDiscountUnchanged.PAYMENTTARGETNO);

	lStatus = FdDelayUpdateRecord( *Fd_CDiscount, &m_BufOldCDiscount, &m_BufOldCDiscountUnchanged, PK, errmld);

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cdiscount (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		lStatus = FdTransact(errmld);
		if ( lStatus != 0 && strstr(errmld, "-346" ) != NULL ) // update would cause duplicate key !
		{
			strcpy ( errmld, "");
			lStatus = del_cdiscount(Fd_CDiscount, errmld);
		}
		else
		{
			if ( m_BufOldCDiscount.ARTICLENO != 0 )
				lStatus = WritePznPflege( m_BufOldCDiscount.ARTICLENO, "28", tages_datum, errmld );
			else
				lStatus = WriteGrpPflege( m_BufOldCDiscount.DISCOUNTGRPNO, "2A", tages_datum, errmld );
		}
	}
	return lStatus;

}

/* ------------------------------------------------------------------- */
int del_cdiscount(const int *Fd_CDiscount, char* errmld)
{
	long lStatus = 0;
	char PK [1000];

	if ( *Fd_CDiscount < 0 ) 
		return -1;

	sprintf ( PK,	"ARTICLENO=%7ld and DISCOUNTGRPNO=%ld and PHARMACYGROUPID='%s' and CUSTOMERNO=%ld "
					"and BASEQTY=%ld and GRPDISCOUNTTYP=%d and DISCOUNTTYPE=%d and DISCOUNTSPEC=%d "
					"and BASE_VALUE=%f and BASE_MULT_STD_QTY=%ld and DATEFROM=%ld and DATETO=%ld ",
					m_BufOldCDiscountUnchanged.ARTICLENO,
					m_BufOldCDiscountUnchanged.DISCOUNTGRPNO,
					m_BufOldCDiscountUnchanged.PHARMACYGROUPID,
					m_BufOldCDiscountUnchanged.CUSTOMERNO,
					m_BufOldCDiscountUnchanged.BASEQTY,
					m_BufOldCDiscountUnchanged.GRPDISCOUNTTYP,
					m_BufOldCDiscountUnchanged.DISCOUNTTYPE,
					m_BufOldCDiscountUnchanged.DISCOUNTSPEC,
					m_BufOldCDiscountUnchanged.BASE_VALUE,
					m_BufOldCDiscountUnchanged.BASE_MULT_STD_QTY,
					m_BufOldCDiscountUnchanged.DATEFROM,
					m_BufOldCDiscountUnchanged.DATETO);

	lStatus = FdDelayDeleteRecord( *Fd_CDiscount, &m_BufOldCDiscountUnchanged, PK, errmld );
	
	if ( lStatus != 0 )
	{
		strcpy( errmld, "cdiscount (Delete aus cdiscount): " );
		strcat( errmld, DynErrmld() );
	}
	else
		lStatus = FdTransact(errmld);
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_count_ccpvalperiod(long * count, char* errmld)
{
	long lStatus = 0;
	char sql [250];

	sprintf ( sql, " ccpvalidityperiod where article_no_pack = %d", m_CArtComPack_CurrentPackNo );
	
	lStatus = SqlCount( sql, count );			
	
	if ( lStatus != 0 )
	{
		strcpy( errmld, "ccpvalidityperiod (Count): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_count_cdiscgrp(long * count, char* errmld)
{
	long lStatus = 0;
	char sql [250];

	sprintf ( sql, " cdiscgrp where discountgrpno = %d", m_CDiscGrpMem_CurrentGroupNo );
	
	lStatus = SqlCount( sql, count );			
	
	if ( lStatus != 0 )
	{
		strcpy( errmld, "cdiscgrp (Count): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_count_cdiscount_to_stop(long * count, char* errmld)
{
	long lStatus = 0;
	char sql [2500];
	char where_section[1300];
	char upd_section[1200];
	char hnr_section[200];

	int i = 1;
	int j = 1;
	int bFound = 0;
	int bFoundHnr = 0;
	int Hnr = 0;

	int fd;
	struct CDISCOUNT disc;

	while ( i <= anz_columns )
	{
		if ( strstr(upd_columns[i], "DATETO" ) != NULL )
		{
			strcpy(upd_columns[i], upd_values[i]);
			tages_datum = atoi( upd_values[i] ); 
			bFound = 1;
			break;
		}
		i++;
	}

	while ( j <= anz_columns )
	{
		if ( strstr(upd_columns[j], "HERSTELLER_NR" ) != NULL )
		{
			strcpy(upd_columns[j], upd_values[j]);
			Hnr = atoi( upd_values[j] ); 
			bFoundHnr = 1;
			break;
		}
		j++;
	}
	
	switch ( anz_columns )
	{
	case 0:
		sprintf ( upd_section, "%s", " " );
		break;

	case 1:
		sprintf ( upd_section, "and %s = '%s'",
					upd_columns[1], upd_values[1]);
		break;
	case 2:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2]);
		break;
	case 3:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3]);
		break;
	case 4:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4]);
		break;
	case 5:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5]);
		break;
	case 6:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6]);
		break;
	case 7:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6],
					upd_columns[7], upd_values[7]);
		break;
	case 8:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6],
					upd_columns[7], upd_values[7],
					upd_columns[8], upd_values[8]);
		break;
	case 9:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6],
					upd_columns[7], upd_values[7],
					upd_columns[8], upd_values[8],
					upd_columns[9], upd_values[9]);
		break;
	case 10:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6],
					upd_columns[7], upd_values[7],
					upd_columns[8], upd_values[8],
					upd_columns[9], upd_values[9],
					upd_columns[10], upd_values[10]);
		break;

	default:
		return -1;
		break;
	}
	
	if ( strcmp(upd_values[0], "-9999") == 0 ) // beenden auch ohne PZN möglich!
	{
		sprintf ( where_section,	" where datefrom <= %ld and dateto > %ld %s ", tages_datum, tages_datum, upd_section );
	}
	else
	{
		sprintf ( where_section,	" where articleno = %s and datefrom <= %ld and dateto > %ld %s ",
					upd_values[0], tages_datum, tages_datum, upd_section );
	}

	if (bFoundHnr == 1)
	{
		sprintf ( hnr_section, " and articleno in (select artikel_nr from zartikel where hersteller_nr = %ld) ", Hnr);
		strcat( where_section, hnr_section );

		strcpy(upd_columns[j], "HERSTELLER_NR");
		Hnr = 0; 	
	}

	sprintf ( sql, " cdiscount " );
	strcat( sql, where_section );

	lStatus = SqlCount( sql, count );			
	
	if ( lStatus != 0 )
	{
		strcpy( errmld, "cdiscount (Count): " );
		strcat( errmld, DynErrmld() );
	}

	if (bFound == 1)
	{
		strcpy(upd_columns[i], "DATETO");
		tages_datum = GetPhoDate(); 	
	}

	
// wegen Schreiben zpznpflege / zgrppflege --------------------------------------------
	
	sprintf ( sql, "SELECT %s FROM CDISCOUNT %s", PROJECTION_CDISCOUNT, where_section );

	lStatus = SqlOpenCs( &fd, sql );
	if ( lStatus != 0 ) 
	{
		strcat( errmld, DynErrmld() );
		return lStatus;
	}
	
	while ( lStatus == 0 )
	{
		lStatus = SqlFetch( fd, 1, &disc, NULL );
		if ( lStatus == 0 )
		{
			if (disc.ARTICLENO == 0)
			{
				if (disc.DISCOUNTGRPNO > 0)
					WriteGrpPflege( disc.DISCOUNTGRPNO, "2A", tages_datum, errmld );
				else if (disc.MANUFACTURERNO > 0)
					WriteGrpPflege( disc.MANUFACTURERNO, "2B", tages_datum, errmld );
				else if (disc.ARTCATEGORYNO > 0)
					WriteGrpPflege( disc.ARTCATEGORYNO, "2C", tages_datum, errmld );
				else
					WriteGrpPflege( 0, "2D", tages_datum, errmld );
			}
			else
				lStatus = WritePznPflege( disc.ARTICLENO, "28", tages_datum, errmld );
		}
	}

	if (lStatus == 100 )
		lStatus = 0;

	SqlCloseCs( fd );
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int stop_cdiscount(const int *Fd_CDiscount, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1200];
	char hnr_section[200];

	int i = 1;
	int j = 1;
	int bFound = 0;
	int bFoundHnr = 0;
	int Hnr = 0;

	char PK [1500];

	struct CDISCOUNT	BufCDiscountOld;
	struct CDISCOUNT	BufCDiscountAkt;

	while ( i <= anz_columns )
	{
		if ( strstr(upd_columns[i], "DATETO" ) != NULL )
		{
			strcpy(upd_columns[i], upd_values[i]);
			tages_datum = atoi( upd_values[i] ); 
			bFound = 1;
			break;
		}
		i++;
	}

	while ( j <= anz_columns )
	{
		if ( strstr(upd_columns[j], "HERSTELLER_NR" ) != NULL )
		{
			strcpy(upd_columns[j], upd_values[j]);
			Hnr = atoi( upd_values[j] ); 
			bFoundHnr = 1;
			break;
		}
		j++;
	}
	
	if ( *Fd_CDiscount < 0 ) 
		return -1;

	switch ( anz_columns )
	{
	case 0:
		sprintf ( upd_section, "%s", " " );
		break;

	case 1:
		sprintf ( upd_section, "and %s = '%s'",
					upd_columns[1], upd_values[1]);
		break;
	case 2:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2]);
		break;
	case 3:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3]);
		break;
	case 4:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4]);
		break;
	case 5:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5]);
		break;
	case 6:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6]);
		break;
	case 7:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6],
					upd_columns[7], upd_values[7]);
		break;
	case 8:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6],
					upd_columns[7], upd_values[7],
					upd_columns[8], upd_values[8]);
		break;
	case 9:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6],
					upd_columns[7], upd_values[7],
					upd_columns[8], upd_values[8],
					upd_columns[9], upd_values[9]);
		break;
	case 10:
		sprintf ( upd_section, "and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s' and %s = '%s'",
					upd_columns[1], upd_values[1],
					upd_columns[2], upd_values[2],
					upd_columns[3], upd_values[3],
					upd_columns[4], upd_values[4],
					upd_columns[5], upd_values[5],
					upd_columns[6], upd_values[6],
					upd_columns[7], upd_values[7],
					upd_columns[8], upd_values[8],
					upd_columns[9], upd_values[9],
					upd_columns[10], upd_values[10]);
		break;

	default:
		return -1;
		break;
	}
	
	if ( strcmp(upd_values[0], "-9999") == 0 ) // beenden auch ohne PZN möglich!
	{
		sprintf ( sql, "update cdiscount set dateto = %ld "
					"where datefrom <= %ld and dateto > %ld %s ",
					tages_datum, tages_datum, tages_datum, upd_section );

		sprintf(PK, "DATEFROM<=%ld and DATETO>%ld %s ",
					tages_datum, tages_datum, upd_section);
	}
	else
	{
		sprintf ( sql, "update cdiscount set dateto = %ld "
					"where articleno = %s and datefrom <= %ld and dateto > %ld %s ",
					tages_datum, upd_values[0], tages_datum, tages_datum, upd_section );

		sprintf(PK, "ARTICLENO=%7s and DATEFROM<=%ld and DATETO>%ld %s ",
				upd_values[0], tages_datum, tages_datum, upd_section);
	}

	if (bFoundHnr == 1)
	{
		sprintf ( hnr_section, " and articleno in (select artikel_nr from zartikel where hersteller_nr = %ld) ", Hnr);
		strcat( sql, hnr_section );

		strcpy(upd_columns[j], "HERSTELLER_NR");
		Hnr = 0; 	
	}

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_CDiscount, PK, &BufCDiscountOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "CDISCOUNT (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	lStatus = SqlExecuteImm( sql );
	
	if ( lStatus != 0 )
	{
		strcpy( errmld, "cdiscount (Stop): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			if ( strcmp(upd_values[0], "-9999") == 0 )
			{
				sprintf(PK, "DATEFROM<=%ld and DATETO=%ld %s",
					tages_datum, tages_datum, upd_section);
			}
			else
			{
				sprintf(PK, "ARTICLENO=%7s and DATEFROM<=%ld and DATETO=%ld %s",
					upd_values[0], tages_datum, tages_datum, upd_section);
			}

			lStatus = FdReadRecord( *Fd_CDiscount, PK, &BufCDiscountAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CDISCOUNT (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cdiscountTab[] = "cdiscount";
			static void *cdiscountDesc  = NULL;

			lStatus = SqlGetTabDesc( cdiscountTab, &cdiscountDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CDISCOUNT (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufCDiscountOld, &BufCDiscountAkt, sizeof(BufCDiscountAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, cdiscountDesc,
											&BufCDiscountOld, &BufCDiscountAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */

		// zpznpflege / zgrppflege bereits vorab in sel_count_cdiscount_to_stop geschrieben !
	}

	if (bFound == 1)
	{
		strcpy(upd_columns[i], "DATETO");
		tages_datum = GetPhoDate();
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_carticleext(const int *Fd_CArticleExt, char* art_nr, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_CArticleExt < 0 ) 
		return -1;


	sprintf ( PK, "ARTICLENO=%7s", art_nr );

	lStatus = FdReadRecord( *Fd_CArticleExt, PK, &m_BufOldCArticleExt, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "carticleext (Suche nach carticleext): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_carticlecodes(const int *Fd_CArticleCodes, char* art_nr, char* code_type, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_CArticleCodes < 0 ) 
		return -1;


	sprintf ( PK, "ARTICLENO=%7s and CODE_TYPE=%s", art_nr, code_type );

	lStatus = FdReadRecord( *Fd_CArticleCodes, PK, &m_BufOldCArticleCodes, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "carticlecodes (Suche nach carticlecodes): " );
		strcat( errmld, DynErrmld() );
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zchargenrr(const int *Fd_ZChargenRR, char* art_nr, char* batch, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ZChargenRR < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s and CHARGE='%s'", art_nr, batch );

	lStatus = FdReadRecord( *Fd_ZChargenRR, PK, &m_BufOldZChargenRR, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zchargenrueckruf (Suche nach zchargenrueckruf): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartfrance(const int *Fd_ZArtFrance, char* art_nr, char* errmld)
{
	long lStatus;
	char PK [100];
	static int temp_created = 0;
		
	if ( *Fd_ZArtFrance < 0 ) 
		return -1;

	sprintf ( PK, "ARTICLENO=%7s", art_nr );

	lStatus = FdReadRecord( *Fd_ZArtFrance, PK, &m_BufOldZArtFrance, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zartfrance (Suche nach zartfrance): " );
		strcat( errmld, DynErrmld() );
	}

	if ( lStatus == 0 )
	{
		char statm_temp [200];

		if ( temp_created == 0 )
		{
			sprintf( statm_temp, "create temp table zputil_temp ("        
								 "ARTIKEL_NR INTEGER NOT NULL ) with no log" );

			lStatus = SqlExecuteImm( statm_temp );

			if ( lStatus != 0 )
				strcpy( errmld, DynErrmld() );
			else
				temp_created = 1;
		}

		if ( temp_created == 1 )
		{
			sprintf ( statm_temp, "insert into zputil_temp ( artikel_nr ) values ( %s )", art_nr );

			lStatus = SqlExecuteImm ( statm_temp );

			if ( lStatus != 0 )
				strcpy( errmld, DynErrmld() );
		}
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int exists_in_cmedicalactor(const char* medicalactor_id, const char* medicalactor_type, char* errmld)
{
	long lStatus;
	char PK[200] = "";

	sprintf(PK, "medicalactor_id='%s' and medicalactor_type=%s and active='1'",
			medicalactor_id, medicalactor_type);

	lStatus = FdReadRecord(Fd_Cmedicalactor, PK, &BufCMedicalactor, errmld);

	if (lStatus == 0)
	{
		// Found active record
		return 1;
	}
	else if (lStatus != 0) 
	{
		// Not found or inactive
		sprintf(errmld,
				"medicalactor_id='%s', medicalactor_type=%s not found or not active in CMEDICALACTOR",
				medicalactor_id, medicalactor_type);
		return 0;
	}
}

/* ------------------------------------------------------------------- */
int exists_in_cartmedactor(const char* medicalactor_id, char* errmld)
{
	long lStatus;
	char PK[200] = "";

	sprintf(PK, "medicalactor_id='%s'", medicalactor_id);

	lStatus = FdReadRecord(Fd_Cartmedactor, PK, &BufCArtmedactor, errmld);

	if (lStatus == 0) 
	{
		// Found record: update not possible for fields 'medicalactor_type' or 'active'
		sprintf(errmld,
				"medicalactor_id='%s' is used in CARTMEDACTOR, change of 'medicalactor_type' or 'active' not allowed",
				medicalactor_id);
		return 0;
	}
	else if (lStatus != 0) 
	{
		// Not found: update possible
		return 1;
	} 
}

/* ------------------------------------------------------------------- */
int sel_cartmedactor(const int* Fd_Cartmedactor, char* art_nr, char* medicalactor_type, char* errmld)
{
	long lStatus;
	char PK[200] = "";

	if (*Fd_Cartmedactor < 0)
	{
		return -1;
	}

	sprintf(PK, "article_no=%7s and medicalactor_type='%s'", art_nr, medicalactor_type);

	lStatus = FdReadRecord(*Fd_Cartmedactor, PK, &m_BufOldCArtmedactor, errmld);

	if (lStatus != 0 && lStatus != 100)
	{
		strcpy(errmld, "cartmedactor (Suche nach cartmedactor): ");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_cartmedactor(const int* Fd_Cartmedactor, char* errmld)
{
	long lStatus = 0;
	char sql[300];
	char upd_section[200];
	char PK[200] = "";

	struct CARTMEDACTOR	BufCArtmedactorOld;
	struct CARTMEDACTOR	BufCArtmedactorAkt;

	if (*Fd_Cartmedactor < 0) 
	{
		return -1;
	}

	if (!exists_in_cmedicalactor(upd_values[1], upd_values[2], errmld))
	{
		return -1;
	}

	sprintf(PK, "article_no=%7s and medicalactor_type='%s'", upd_values[0], upd_values[2]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord(*Fd_Cartmedactor, PK, &BufCArtmedactorOld, errmld);

	if (lStatus != 0)
	{
		strcpy(errmld, "CARTMEDACTOR (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf(upd_section, "set medicalactor_id = '%s'", upd_values[1]);

	sprintf(sql, "update cartmedactor %s "
			"where article_no = %s and medicalactor_type = %s",
			upd_section, upd_values[0], upd_values[2]);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "cartmedactor (Update einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);

		FdReadRecord(*Fd_Cartmedactor, PK, &BufCArtmedactor, errmld);

		if (memcmp(&BufCArtmedactor, &m_BufOldCArtmedactor, sizeof(m_BufOldCArtmedactor)) != 0)
		{
			lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord(*Fd_Cartmedactor, PK, &BufCArtmedactorAkt, errmld);

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTMEDACTOR (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cartmedactorTab[] = "cartmedactor";
			static void* cartmedactorDesc = NULL;

			lStatus = SqlGetTabDesc(cartmedactorTab, &cartmedactorDesc, DESC_DEFAULT, errmld);

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTMEDACTOR (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufCArtmedactorOld, &BufCArtmedactorAkt, sizeof(BufCArtmedactorAkt)) != 0)
			{
				lStatus = Insert_Protokoll(P_UPDATE, V_PROTO_VERTEIL, cartmedactorDesc,
										   &BufCArtmedactorOld, &BufCArtmedactorAkt, PK,
										   user, "", 0, errmld);
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cartmedactor(const int* Fd_Cartmedactor, char* errmld)
{
	long lStatus = 0;
	char sql[2048];
	char PK[200] = "";
	char ins_section_fields[1024] = "";
	char ins_section_values[1024] = "";

	struct CARTICLEEXT	BufCArticleExt;

	if (*Fd_Cartmedactor < 0)
	{
		return -1;
	}

	if (fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	if (!exists_in_cmedicalactor(upd_values[1], upd_values[2], errmld))
	{
		return -1;
	}

	sprintf(PK, "article_no=%s", upd_values[0]);

	sprintf(sql, "INSERT INTO CARTMEDACTOR ( article_no, %s) "
			"VALUES ( %ld, %s) ", ins_section_fields,
			atol(upd_values[0]), ins_section_values);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "CARTMEDACTOR (Insert einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);

		lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord(*Fd_Cartmedactor, PK, &BufCArticleExt, errmld);

			if (lStatus != 0)
			{
				strcpy(errmld, "CMEDICALACTOR (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cartmedactorTab[] = "cartmedactor";
			static void* cartmedactorDesc = NULL;

			lStatus = SqlGetTabDesc(cartmedactorTab, &cartmedactorDesc, DESC_DEFAULT, errmld);

			if (lStatus != 0)
			{
				strcpy(errmld, "CMEDICALACTOR (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(P_INSERT, V_PROTO_VERTEIL, cartmedactorDesc,
				NULL, &BufCArticleExt, PK,
				user, "", 0, errmld);
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_cmedicalactor(const int* Fd_Cmedicalactor, char* medicalactor_id, char* errmld)
{
	long lStatus;
	char PK[200] = "";

	if (*Fd_Cmedicalactor < 0)
	{
		return -1;
	}

	sprintf(PK, "medicalactor_id='%s'", medicalactor_id);

	lStatus = FdReadRecord(*Fd_Cmedicalactor, PK, &m_BufOldCMedicalactor, errmld);

	if (lStatus != 0 && lStatus != 100)
	{
		strcpy(errmld, "cmedicalactor (Suche nach cmedicalactor): ");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_cmedicalactor(const int* Fd_Cmedicalactor, char* errmld)
{
	long lStatus = 0;
	char sql[300];
	char upd_section[1000] = "";
	char PK[200] = "";

	struct CMEDICALACTOR	BufCMedicalactorOld;

	if (*Fd_Cmedicalactor < 0) 
	{
		return -1;
	}

	sprintf(PK, "medicalactor_id='%s'", upd_values[0]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord(*Fd_Cmedicalactor, PK, &BufCMedicalactorOld, errmld);
	
	if (!exists_in_cartmedactor(upd_values[0], errmld))
	{
		if ((BufCArtmedactor.MEDICALACTOR_TYPE != atoi(upd_values[1])) ||
			((strcmp(BufCMedicalactorOld.ACTIVE, "1") == 0) &&
				(strcmp(upd_values[2], "0") == 0)))
		{
			return -1; // update of 'medicalactor_type' or 'active' not allowed
		}
	}

	if (lStatus != 0)
	{
		strcpy(errmld, "CMEDICALACTOR (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf(upd_section, 
			"set medicalactor_type= %d, active= '%s', matchcode= '%s', name= '%s', "
			"street_nr= '%s', street_name= '%s', city_name= '%s', country_code= '%s', email= '%s'",
			atoi(upd_values[1]),	// medicalactor_type
			upd_values[2],			// active
			upd_values[3],			// matchcode
			upd_values[4], 			// name
			upd_values[5], 			// street_nr
			upd_values[6], 			// street_name
			upd_values[7],			// city_name
			upd_values[8], 			// country_code
			upd_values[9]); 		// email	
								
	sprintf(sql, "update cmedicalactor %s "
			"where medicalactor_id = '%s'", upd_section, upd_values[0]);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "cmedicalactor (Update einer Zeile): ");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cmedicalactor(const int* Fd_Cmedicalactor, char* errmld)
{
	long lStatus = 0;
	char sql[2048];
	char ins_section_cols[2048] = "";
	char ins_section_vals[2048] = "";

	if (*Fd_Cmedicalactor < 0)
	{
		return -1;
	}

	sprintf(ins_section_cols,
			"medicalactor_id, medicalactor_type, active, matchcode, "
			"name, street_nr, street_name, city_name, country_code, email");

	sprintf(ins_section_vals,
			"'%s', %d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s'",
			upd_values[0],			// medicalactor_id
			atoi(upd_values[1]),	// medicalactor_type
			upd_values[2],			// active
			upd_values[3],			// matchcode
			upd_values[4],			// name
			upd_values[5],			// street_nr
			upd_values[6],			// street_name
			upd_values[7],			// city_name
			upd_values[8],			// country_code
			upd_values[9]);			// email		

	sprintf(sql, "INSERT INTO CMEDICALACTOR ( %s ) VALUES ( %s )",
			ins_section_cols, ins_section_vals);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "CMEDICALACTOR (Insert einer Zeile): ");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartswitzerland(const int *Fd_ZArtSwitzerland, char* art_nr, char* errmld)
{
	long lStatus;
	char PK [100];
		
	if ( *Fd_ZArtSwitzerland < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s", art_nr );

	lStatus = FdReadRecord( *Fd_ZArtSwitzerland, PK, &m_BufOldZArtSwitzerland, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zartswitzerland (Suche nach zartswitzerland): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartserbia(const int *Fd_ZArtSerbia, char* art_nr, char* errmld)
{
	long lStatus;
	char PK [100];
		
	if ( *Fd_ZArtSerbia < 0 ) 
		return -1;

	sprintf ( PK, "ARTICLENO=%7s", art_nr );

	lStatus = FdReadRecord( *Fd_ZArtSerbia, PK, &m_BufOldZArtSerbia, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zartserbia (Suche nach zartserbia): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartaustria(const int *Fd_ZArtAustria, char* art_nr, char* errmld)
{
	long lStatus;
	char PK [100];
		
	if ( *Fd_ZArtAustria < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s", art_nr );

	lStatus = FdReadRecord( *Fd_ZArtAustria, PK, &m_BufOldZArtAustria, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zartaustria (Suche nach zartaustria): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartwg(const int *Fd_ZArtWg, char* art_nr, char* art, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ZArtWg < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s and ART='%s'", art_nr, art );

	lStatus = FdReadRecord( *Fd_ZArtWg, PK, &m_BufOldZArtWg, errmld );

	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "zartwg (Suche nach zartwg): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_zartwg_5ag(const int* Fd_ZArtWg_5ag, char* art_nr, char* art, char* errmld)
{
	long lStatus;
	char PK[100];

	if (*Fd_ZArtWg_5ag < 0)
		return -1;

	sprintf(PK, "ARTIKEL_NR=%7s and ART='%s'", art_nr, art);

	lStatus = FdReadRecord(*Fd_ZArtWg_5ag, PK, &m_BufOldZArtWg, errmld);

	if (lStatus != 0 && lStatus != 100)
	{
		strcpy(errmld, "zartwg (Suche nach zartwg): ");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_cimexblock(const int *Fd_Cimexblock, char* art_nr, char* country, char* imex_mode, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Cimexblock < 0 ) 
		return -1;

	sprintf ( PK, "ARTICLENO=%7s and COUNTRY_IFACODE='%s' and IMEX_MODE='%s'", art_nr, country, imex_mode );

	lStatus = FdReadRecord( *Fd_Cimexblock, PK, &m_BufOldCimexblock, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "cimexblock (Suche nach cimexblock): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_cdiscount(int *Fd_CDiscount, struct CDISCOUNT *cdisc, char* errmld)
{
	long lStatus;
	char PK [2000];
	
	if ( *Fd_CDiscount < 0 ) 
		return -1;

	sprintf ( PK, "SELECT %s FROM CDISCOUNT WHERE "
					"ARTICLENO=%7ld and DISCOUNTGRPNO=%ld and PHARMACYGROUPID='%s' and CUSTOMERNO=%ld "
					"and BASEQTY=%ld and GRPDISCOUNTTYP=%d and DISCOUNTTYPE=%d and DISCOUNTSPEC=%d "
					"and BASE_VALUE=%f and BASE_MULT_STD_QTY=%ld and DATETO >= %ld "
					"and MANUFACTURERNO=%ld and ARTCATEGORYNO=%ld and PAYMENTTARGETNO=%d",
					PROJECTION_CDISCOUNT,
					cdisc->ARTICLENO,
					cdisc->DISCOUNTGRPNO,
					cdisc->PHARMACYGROUPID,
					cdisc->CUSTOMERNO,
					cdisc->BASEQTY,
					cdisc->GRPDISCOUNTTYP,
					cdisc->DISCOUNTTYPE,
					cdisc->DISCOUNTSPEC,
					cdisc->BASE_VALUE,
					cdisc->BASE_MULT_STD_QTY,
					cdisc->DATEFROM,
					cdisc->MANUFACTURERNO,
					cdisc->ARTCATEGORYNO,
					cdisc->PAYMENTTARGETNO);

	lStatus = SqlOpenCsWh( Fd_CDiscount, PK );

	if ( lStatus != 0 )
	{
		strcpy( errmld, "cdiscount (Suche nach cdiscount): " );
		strcat( errmld, DynErrmld() );
		return lStatus;
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_cimexblock(const int *Fd_Cimexblock, char* art_nr, char* country, char* imex_mode, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_Cimexblock < 0 ) 
		return -1;

	sprintf ( PK, "ARTICLENO=%7s and COUNTRY_IFACODE='%s' and IMEX_MODE='%s'", art_nr, country, imex_mode );

	lStatus = FdDeleteRecord( *Fd_Cimexblock, &m_BufOldCimexblock, PK, errmld );
	
	if ( lStatus != 0 )
	{
		strcpy( errmld, "cimexblock (Delete aus cimexblock): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_zartwg(const int *Fd_ZArtWg, char* art_nr, char* art, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ZArtWg < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s and ART='%s'", art_nr, art );

	lStatus = FdDeleteRecord( *Fd_ZArtWg, &m_BufOldZArtWg, PK, errmld );
	
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartwg (Delete aus zartwg): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		lStatus = WriteZAPflege(atol(art_nr), tages_datum, errmld);
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_artnrbl(const int *Fd_ArtnrBl, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ArtnrBl < 0 ) 
		return -1;

	sprintf ( PK, "BESLA_NR=%5ld and ARTIKEL_NR=%7ld", m_BufOldArtBl.BESLA_NR, m_BufOldArtBl.ARTIKEL_NR );

	lStatus = FdDeleteRecord( *Fd_ArtnrBl, &m_BufOldArtBl, PK, errmld );
	
	if ( lStatus != 0 )
	{
		strcpy( errmld, "artnrbl (Delete aus artnrbl): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_carticlecodes(const int *Fd_CArticleCodes, char* errmld)
{
	long lStatus = 0;
	char sql [300];
	char upd_section[200];
	char PK [100];

	struct CARTICLECODES	BufCArticleCodesOld;
	struct CARTICLECODES	BufCArticleCodesAkt;

	if ( *Fd_CArticleCodes < 0 ) 
		return -1;

	sprintf ( PK, "ARTICLENO=%7s and CODE_TYPE=%s", upd_values[0], upd_values[1] );

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_CArticleCodes, PK, &BufCArticleCodesOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "CARTICLECODES (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( upd_section, "set article_code = '%s', date_changed = %ld", upd_values[2], tages_datum);	

	sprintf ( sql, "update carticlecodes %s "
					"where articleno = %s and code_type = %s ",
					upd_section, upd_values[0], upd_values[1] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "carticlecodes (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		FdReadRecord( *Fd_CArticleCodes, PK, &BufCArticleCodes, errmld );

		if ( memcmp( &BufCArticleCodes, &m_BufOldCArticleCodes, sizeof(m_BufOldCArticleCodes) ) != 0 )
		{
			lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_CArticleCodes, PK, &BufCArticleCodesAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTICLECODES (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  carticlecodesTab[] = "carticlecodes";
			static void *carticlecodesDesc  = NULL;

			lStatus = SqlGetTabDesc( carticlecodesTab, &carticlecodesDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTICLECODES (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufCArticleCodesOld, &BufCArticleCodesAkt, sizeof(BufCArticleCodesAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, carticlecodesDesc,
											&BufCArticleCodesOld, &BufCArticleCodesAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_zartwg(const int *Fd_ZArtWg, char* errmld)
{
	long lStatus = 0;
	char sql [300];
	char upd_section[200];
	char PK [100];

	struct ZARTWG	BufZArtWgOld;
	struct ZARTWG	BufZArtWgAkt;
	
	if ( *Fd_ZArtWg < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s and ART='%s'", upd_values[0], upd_columns[1] );

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZArtWg, PK, &BufZArtWgOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZARTWG (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( upd_section, "set warengruppe = '%s'", upd_values[1]);	

	sprintf ( sql, "update zartwg %s "
					"where artikel_nr = %s and art = '%s'",
					upd_section, upd_values[0], upd_columns[1] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "ZARTWG (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		FdReadRecord( *Fd_ZArtWg, PK, &BufZArtWgUpd, errmld );

		if ( memcmp( &BufZArtWgUpd, &m_BufOldZArtWg, sizeof(m_BufOldZArtWg) ) != 0 )
		{
			lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtWg, PK, &BufZArtWgAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTWG (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartwgTab[] = "zartwg";
			static void *zartwgDesc  = NULL;

			lStatus = SqlGetTabDesc( zartwgTab, &zartwgDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTWG (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZArtWgOld, &BufZArtWgAkt, sizeof(BufZArtWgAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zartwgDesc,
											&BufZArtWgOld, &BufZArtWgAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}


/* ------------------------------------------------------------------- */
int upd_zartwg_5ag(const int* Fd_ZArtWg_5ag, char* errmld)
{
	long lStatus = 0;
	char PK[100];

	if (*Fd_ZArtWg_5ag < 0)
		return -1;

	/* set zartwg values */
	BufZArtWgUpd.ARTIKEL_NR = m_BufOldZArtWg.ARTIKEL_NR;
	strcpy(BufZArtWgUpd.ART, m_BufOldZArtWg.ART);
	strcpy(BufZArtWgUpd.WARENGRUPPE, upd_values[2]);

	sprintf(PK, "ARTIKEL_NR=%7ld and ART='%s' ", m_BufOldZArtWg.ARTIKEL_NR, m_BufOldZArtWg.ART);

	lStatus = FdUpdateRecord(*Fd_ZArtWg_5ag, &BufZArtWgUpd, &m_BufOldZArtWg, PK, errmld);

	if (lStatus != 0)
	{
		strcpy(errmld, "zartwg (Update einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);

		if (memcmp(&BufZArtWgUpd, &m_BufOldZArtWg, sizeof(m_BufOldZArtWg)) != 0)
		{
			lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
		}
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_carticlecodes(const int *Fd_CArticleCodes, char* errmld)
{
	long lStatus = 0;
	char sql [500];
	char PK [100];

	struct CARTICLECODES	BufCArticleCodes;
	
	if ( *Fd_CArticleCodes < 0 ) 
		return -1;

	sprintf ( PK, "ARTICLENO=%7s and CODE_TYPE=%s", upd_values[0], upd_values[1] );

	sprintf ( sql, "insert into carticlecodes (articleno, code_type, article_code, serial_number, preferred_flag, date_changed) "
					"values (%s, %s, '%s', 0, 0, %ld)",
					upd_values[0], upd_values[1], upd_values[2], tages_datum );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "carticlecodes (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		FdReadRecord( *Fd_CArticleCodes, PK, &BufCArticleCodes, errmld );

		if ( memcmp( &BufCArticleCodes, &m_BufOldCArticleCodes, sizeof(m_BufOldCArticleCodes) ) != 0 )
		{
			lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_CArticleCodes, PK, &BufCArticleCodes, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTICLECODES (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  carticlecodesTab[] = "carticlecodes";
			static void *carticlecodesDesc  = NULL;

			lStatus = SqlGetTabDesc( carticlecodesTab, &carticlecodesDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTICLECODES (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, carticlecodesDesc,
										NULL, &BufCArticleCodes, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_zchargenrr(const int *Fd_ZChargenRR, char* errmld)
{
	long lStatus = 0;
	char sql [2500];
	char PK [100];

	char ins_section_fields[1000] = "";
	char ins_section_values[1000] = "";

	char section_einschr_field[20];
	char section_einschr_value[5];

	char section_rrkz_field[20];
	char section_rrkz_value[5];

	struct ZCHARGENRUECKRUF	BufZChargenRR;

	if ( *Fd_ZChargenRR < 0 ) 
		return -1;

	if(fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTIKEL_NR=%7s", upd_values[0]);

	if ( strstr(ins_section_fields, "EINSCHRAENKUNGEN" ) == NULL )
	{
		sprintf ( section_einschr_field, "%s", "EINSCHRAENKUNGEN, ");
		sprintf ( section_einschr_value, "%s", "'00', ");				
	}
	else
	{
		sprintf ( section_einschr_field, "%s", " ");
		sprintf ( section_einschr_value, "%s", " ");				
	}

	if ( strstr(ins_section_fields, "RUECKRUF_KZ" ) == NULL )
	{
		sprintf ( section_rrkz_field, "%s", "RUECKRUF_KZ, ");
		sprintf ( section_rrkz_value, "%s", "'C', ");				
	}
	else
	{
		sprintf ( section_rrkz_field, "%s", " ");
		sprintf ( section_rrkz_value, "%s", " ");				
	}

	sprintf ( sql, "INSERT INTO zchargenrueckruf ( artikel_nr, %s %s datum_anlage, %s ) "
					"VALUES ( %ld, %s %s %ld, %s) ",
					section_einschr_field, section_rrkz_field, ins_section_fields, 
					atol(upd_values[0]), section_einschr_value, section_rrkz_value, tages_datum, ins_section_values);

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zchargenrueckruf (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		lStatus = WritePznPflege( atol(upd_values[0]), "22", tages_datum, errmld);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZChargenRR, PK, &BufZChargenRR, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZCHARGENRUECKRUF (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zchargenrrTab[] = "zchargenrueckruf";
			static void *zchargenrrDesc  = NULL;

			lStatus = SqlGetTabDesc( zchargenrrTab, &zchargenrrDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZCHARGENRUECKRUF (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, zchargenrrDesc,
										NULL, &BufZChargenRR, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_zchargenrr(const int *Fd_ZChargenRR, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1000] = "";
	char PK [100];

	struct ZCHARGENRUECKRUF	BufZChargenRROld;
	struct ZCHARGENRUECKRUF	BufZChargenRRAkt;

	if ( *Fd_ZChargenRR < 0 ) 
		return -1;

	if(fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf ( PK, "ARTIKEL_NR=%7s and CHARGE='%s'", upd_values[0], upd_values[1] );

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ZChargenRR, PK, &BufZChargenRROld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ZCHARGENRUECKRUF (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( sql, "update zchargenrueckruf %s "
					"where artikel_nr = %s and charge = '%s'",
					upd_section, upd_values[0], upd_values[1] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zchargenrueckruf (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		FdReadRecord( *Fd_ZChargenRR, PK, &BufZChargenRR, errmld );

		if ( memcmp( &BufZChargenRR, &m_BufOldZChargenRR, sizeof(m_BufOldZChargenRR) ) != 0 )
		{
			lStatus = WritePznPflege( atol(upd_values[0]), "22", tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZChargenRR, PK, &BufZChargenRRAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZCHARGENRUECKRUF (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zchargenrrTab[] = "zchargenrueckruf";
			static void *zchargenrrDesc  = NULL;

			lStatus = SqlGetTabDesc( zchargenrrTab, &zchargenrrDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZCHARGENRUECKRUF (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufZChargenRROld, &BufZChargenRRAkt, sizeof(BufZChargenRRAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, zchargenrrDesc,
											&BufZChargenRROld, &BufZChargenRRAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cimexblock(const int *Fd_Cimexblock, char* errmld)
{
	long lStatus = 0;
	char sql [300];
	char PK[100];

	struct CIMEXBLOCK	BufCimexblock;

	if ( *Fd_Cimexblock < 0 ) 
		return -1;

	sprintf(PK, "ARTICLENO=%7s", upd_values[0]);

	sprintf ( sql, "insert into cimexblock (articleno, country_ifacode, imex_mode) "
					"values (%s, '%s', '%s')",
					upd_values[0], upd_values[1], upd_values[2] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "cimexblock (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile(fd_prot);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_Cimexblock, PK, &BufCimexblock, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CIMEXBLOCK (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cimexblockTab[] = "cimexblock";
			static void *cimexblockDesc  = NULL;

			lStatus = SqlGetTabDesc( cimexblockTab, &cimexblockDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CIMEXBLOCK (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, cimexblockDesc,
										NULL, &BufCimexblock, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_zartwg(const int *Fd_ZArtWg, char* errmld)
{
	long lStatus = 0;
	char sql [300];
	char PK [100];

	struct ZARTWG	BufZArtWg;

	if ( *Fd_ZArtWg < 0 ) 
		return -1;

	sprintf ( PK, "ARTIKEL_NR=%7s and ART='%s'", upd_values[0], upd_columns[1] );

	sprintf ( sql, "insert into zartwg (artikel_nr, art, warengruppe) "
					"values (%s, '%s', '%s')",
					upd_values[0], upd_columns[1], upd_values[1] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "zartwg (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );
	
		FdReadRecord( *Fd_ZArtWg, PK, &BufZArtWgUpd, errmld );

		if ( memcmp( &BufZArtWgUpd, &m_BufOldZArtWg, sizeof(m_BufOldZArtWg) ) != 0 )
		{
			lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ZArtWg, PK, &BufZArtWg, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTWG (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  zartwgTab[] = "zartwg";
			static void *zartwgDesc  = NULL;

			lStatus = SqlGetTabDesc( zartwgTab, &zartwgDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ZARTWG (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, zartwgDesc,
										NULL, &BufZArtWg, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_zartwg_5ag(const int* Fd_ZArtWg_5ag, char* errmld)
{
	long lStatus = 0;
	char PK[100];

	if (*Fd_ZArtWg_5ag < 0)
		return -1;

	/* set zwartwg values */
	BufZArtWgUpd.ARTIKEL_NR = atol(upd_values[0]);
	strcpy(BufZArtWgUpd.ART, upd_values[1]);
	strcpy(BufZArtWgUpd.WARENGRUPPE, upd_values[2]);

	sprintf(PK, "ARTIKEL_NR=%7ld and ART='%s' ", BufZArtWgUpd.ARTIKEL_NR, BufZArtWgUpd.ART);

	lStatus = FdInsertRecord(*Fd_ZArtWg_5ag, &BufZArtWgUpd, PK, errmld);

	if (lStatus != 0)
	{
		strcpy(errmld, "zartwg (Insert einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);

		lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_artve(const int *Fd_ArtVe, char* art_nr, char* errmld)
{
	long lStatus;
	char PK [100];
	
	if ( *Fd_ArtVe < 0 ) 
		return -1;


	sprintf ( PK, "ARTIKEL_NR=%7s", art_nr );

	lStatus = FdReadRecord( *Fd_ArtVe, PK, &m_BufOldArtVe, errmld );
	
	if ( lStatus != 0 && lStatus != 100 )
	{
		strcpy( errmld, "artve (Suche nach artve): " );
		strcat( errmld, DynErrmld() );
	}
	
	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_carticleext(const int *Fd_CArticleExt, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1000] = "";
	char PK [100];

	struct CARTICLEEXT	BufCArticleExtOld;
	struct CARTICLEEXT	BufCArticleExtAkt;

	if ( *Fd_CArticleExt < 0 ) 
		return -1;

	if(fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf ( PK, "ARTICLENO=%7s", upd_values[0] );

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_CArticleExt, PK, &BufCArticleExtOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "CARTICLEEXT (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( sql, "update carticleext %s "
					"where articleno = %s",
					upd_section, upd_values[0] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "carticleext (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		FdReadRecord( *Fd_CArticleExt, PK, &BufCArticleExt, errmld );

		if ( memcmp( &BufCArticleExt, &m_BufOldCArticleExt, sizeof(m_BufOldCArticleExt) ) != 0 )
		{
			lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_CArticleExt, PK, &BufCArticleExtAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTICLEEXT (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  carticleextTab[] = "carticleext";
			static void *carticleextDesc  = NULL;

			lStatus = SqlGetTabDesc( carticleextTab, &carticleextDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTICLEEXT (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufCArticleExtOld, &BufCArticleExtAkt, sizeof(BufCArticleExtAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, carticleextDesc,
											&BufCArticleExtOld, &BufCArticleExtAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_artve(const int *Fd_ArtVe, char* errmld)
{
	long lStatus = 0;
	char sql [1500];
	char upd_section[1000] = "";
	char PK [100];

	struct ARTVE	BufArtVeOld;
	struct ARTVE	BufArtVeAkt;

	if ( *Fd_ArtVe < 0 ) 
		return -1;

	if(fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf ( PK, "ARTIKEL_NR=%7s", upd_values[0] );

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_ArtVe, PK, &BufArtVeOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "ARTVE (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf ( sql, "update artve %s "
					"where artikel_nr = %s",
					upd_section, upd_values[0] );

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "artve (Update einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		FdReadRecord( *Fd_ArtVe, PK, &BufArtVe, errmld );

		if ( memcmp( &BufArtVe, &m_BufOldArtVe, sizeof(m_BufOldArtVe) ) != 0 )
		{
			lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);
		}

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ArtVe, PK, &BufArtVeAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ARTVE (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  artveTab[] = "artve";
			static void *artveDesc  = NULL;

			lStatus = SqlGetTabDesc( artveTab, &artveDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ARTVE (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufArtVeOld, &BufArtVeAkt, sizeof(BufArtVeAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, artveDesc,
											&BufArtVeOld, &BufArtVeAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_carticleext(const int *Fd_CArticleExt, char* errmld)
{
	long lStatus = 0;
	char sql [2500];
	char PK [100];

	char ins_section_fields[1000] = "";
	char ins_section_values[1000] = "";

	struct CARTICLEEXT	BufCArticleExt;

	if ( *Fd_CArticleExt < 0 ) 
		return -1;

	if(fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s", upd_values[0]);

	sprintf ( sql, "INSERT INTO carticleext ( articleno, %s) "
					"VALUES ( %ld, %s) ",
					ins_section_fields, 
					atol(upd_values[0]), ins_section_values);

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "carticleext (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_CArticleExt, PK, &BufCArticleExt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTICLEEXT (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  carticleextTab[] = "carticleext";
			static void *carticleextDesc  = NULL;

			lStatus = SqlGetTabDesc( carticleextTab, &carticleextDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CARTICLEEXT (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, carticleextDesc,
										NULL, &BufCArticleExt, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_artve(const int *Fd_ArtVe, char* errmld)
{
	long lStatus = 0;
	char sql [2500];
	char PK [100];

	char ins_section_fields[1000] = "";
	char ins_section_values[1000] = "";

	struct ARTVE	BufArtVe;

	if ( *Fd_ArtVe < 0 ) 
		return -1;

	if(fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf ( PK, "ARTIKEL_NR=%7s", upd_values[0] );

	sprintf ( sql, "INSERT INTO artve ( artikel_nr, %s) "
					"VALUES ( %ld, %s) ",
					ins_section_fields, 
					atol(upd_values[0]), ins_section_values);

	lStatus = SqlExecuteImm( sql );
			
	if ( lStatus != 0 )
	{
		strcpy( errmld, "artve (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
	else
	{
		WriteProtZeile( fd_prot );

		lStatus = WriteZAPflege( atol(upd_values[0]), tages_datum, errmld);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_ArtVe, PK, &BufArtVe, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ARTVE (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  artveTab[] = "artve";
			static void *artveDesc  = NULL;

			lStatus = SqlGetTabDesc( artveTab, &artveDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "ARTVE (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, artveDesc,
										NULL, &BufArtVe, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_cibt(const int *Fd_Cibt, char* art_nr, char* errmld)
{
	long lStatus;
	char PK[100];

	if (*Fd_Cibt < 0)
		return -1;

	sprintf(PK, "ARTICLENO=%7s", art_nr);

	lStatus = FdReadRecord(*Fd_Cibt, PK, &m_BufOldCibt, errmld);

	if (lStatus != 0 && lStatus != 100)
	{
		strcpy(errmld, "cibt (Suche nach cibt): ");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_cibt(const int *Fd_Cibt, char* errmld)
{
	long lStatus = 0;
	char sql[1500];
	char PK[100];
	char upd_section[1000] = "";

	struct CIBT	BufCibtOld;
	struct CIBT	BufCibtAkt;

	if (*Fd_Cibt < 0)
		return -1;

	if (fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s", upd_values[0]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_Cibt, PK, &BufCibtOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "CIBT (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf(sql, "update cibt %s "
		"where articleno = %s",
		upd_section, upd_values[0]);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "cibt (Update einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_Cibt, PK, &BufCibtAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CIBT (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cibtTab[] = "cibt";
			static void *cibtDesc  = NULL;

			lStatus = SqlGetTabDesc( cibtTab, &cibtDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CIBT (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufCibtOld, &BufCibtAkt, sizeof(BufCibtAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, cibtDesc,
											&BufCibtOld, &BufCibtAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */

		//FdReadRecord(*Fd_Cibt, PK, &BufCibt, errmld);

		//if (memcmp(&BufCibt, &m_BufOldCibt, sizeof(m_BufOldCibt)) != 0)
		//{
		//	WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
		//}
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_cibt(const int *Fd_Cibt, char* errmld)
{
	long lStatus = 0;
	char sql[2500];
	char PK[100];

	char ins_section_fields[1000] = "";
	char ins_section_values[1000] = "";

	struct CIBT	BufCibt;

	if (*Fd_Cibt < 0)
		return -1;

	if (fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s", upd_values[0]);

	sprintf(sql, "INSERT INTO cibt ( articleno, %s) "
		"VALUES ( %ld, %s) ",
		ins_section_fields,
		atol(upd_values[0]), ins_section_values);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "cibt (Insert einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_Cibt, PK, &BufCibt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CIBT (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  cibtTab[] = "cibt";
			static void *cibtDesc  = NULL;

			lStatus = SqlGetTabDesc( cibtTab, &cibtDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CIBT (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, cibtDesc,
										NULL, &BufCibt, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */

		//lStatus = WriteZAPflege(atol(upd_values[0]), tages_datum, errmld);
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int sel_ean(const int *Fd_Ean, char* art_nr, char* errmld)
{
	long lStatus;
	char PK[100];

	if (*Fd_Ean < 0)
		return -1;


	sprintf(PK, "ARTIKEL_NR=%7s", art_nr);

	lStatus = FdReadRecord(*Fd_Ean, PK, &m_BufOldEan, errmld);

	if (lStatus != 0 && lStatus != 100)
	{
		strcpy(errmld, "ean (Suche nach ean): ");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

int sel_csubsequentdeliverybrancharticleconfig(const int* Fd_Csubsequentdeliverybrancharticleconfig, char* art_nr, char* branch, char* errmld)
{
	long lStatus;
	char PK[100];

	if (*Fd_Csubsequentdeliverybrancharticleconfig < 0)
		return -1;

	sprintf(PK, "ARTICLENO=%7s AND BRANCHNO=%s", art_nr, branch);

	lStatus = FdReadRecord(*Fd_Csubsequentdeliverybrancharticleconfig, PK, &m_BufOldCsubsequentdeliverybrancharticleconfig, errmld);

	if (lStatus != 0 && lStatus != 100)
	{
		strcpy(errmld, "csubsequentdeliverybrancharticleconfig (Suche nach csubsequentdeliverybrancharticleconfig): ");
		strcat(errmld, DynErrmld());
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int del_ean(const int *Fd_Ean, char* art_nr, char* errmld)
{
	long lStatus;
	char PK[100];

	if (*Fd_Ean < 0)
		return -1;

	sprintf(PK, "ARTIKEL_NR=%7s", art_nr);

	lStatus = FdDeleteRecord(*Fd_Ean, &m_BufOldEan, PK, errmld);

	if (lStatus != 0)
	{
		strcpy(errmld, "ean (Delete aus ean): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		lStatus = WritePznPflege(atol(upd_values[0]), "09", tages_datum, errmld);
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int ins_ean(const int *Fd_Ean, char* errmld)
{
	long lStatus = 0;
	char sql[2500];
	char PK[100];

	char ins_section_fields[1000] = "";
	char ins_section_values[1000] = "";

	struct EAN	BufEan;

	if (*Fd_Ean < 0)
		return -1;

	if (fill_ins_section(ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTIKEL_NR=%7s", upd_values[0]);

	sprintf(sql, "INSERT INTO ean ( artikel_nr, %s) "
		"VALUES ( %ld, %s) ",
		ins_section_fields,
		atol(upd_values[0]), ins_section_values);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "ean (Insert einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		lStatus = WritePznPflege(atol(upd_values[0]), "09", tages_datum, errmld);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_Ean, PK, &BufEan, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "EAN (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  eanTab[] = "ean";
			static void *eanDesc  = NULL;

			lStatus = SqlGetTabDesc( eanTab, &eanDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "EAN (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, eanDesc,
										NULL, &BufEan, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

int ins_csubsequentdeliverybrancharticleconfig(const int* Fd_Csubsequentdeliverybrancharticleconfig, char* errmld)
{
	long lStatus = 0;
	char sql[2500];
	char PK[100];

	char ins_section_fields[500] = "";
	char ins_section_values[500] = "";

	struct CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG	BufCsubsequentdeliverybrancharticleconfig;

	if (*Fd_Csubsequentdeliverybrancharticleconfig < 0)
		return -1;

	if (fill_ins_section_uni(2, ins_section_fields, ins_section_values) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s AND BRANCHNO=%s", upd_values[0], upd_values[1]);

	sprintf(sql, "INSERT INTO csubsequentdeliverybrancharticleconfig ( articleno, branchno, lastchangedate, %s) "
		"VALUES ( %ld, %d, CURRENT, %s) ",
		ins_section_fields,
		atol(upd_values[0]), atoi(upd_values[1]), ins_section_values);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "csubsequentdeliverybrancharticleconfig (Insert einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		lStatus = WritePznPflege(atol(upd_values[0]), "09", tages_datum, errmld);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_Csubsequentdeliverybrancharticleconfig, PK, &BufCsubsequentdeliverybrancharticleconfig, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  csubsequentdeliverybrancharticleconfigTab[] = "csubsequentdeliverybrancharticleconfig";
			static void *csubsequentdeliverybrancharticleconfigDesc  = NULL;

			lStatus = SqlGetTabDesc( csubsequentdeliverybrancharticleconfigTab, &csubsequentdeliverybrancharticleconfigDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			lStatus = Insert_Protokoll(	P_INSERT, V_PROTO_VERTEIL, csubsequentdeliverybrancharticleconfigDesc,
										NULL, &BufCsubsequentdeliverybrancharticleconfig, PK,
										user, "", 0, errmld );
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

int upd_csubsequentdeliverybrancharticleconfig(const int* Fd_Csubsequentdeliverybrancharticleconfig, char* errmld)
{
	long lStatus = 0;
	char sql[1500];
	char PK[100];

	char upd_section[1000] = "";

	struct CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG	BufCsubsequentdeliverybrancharticleconfigOld;
	struct CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG	BufCsubsequentdeliverybrancharticleconfigAkt;

	if (*Fd_Csubsequentdeliverybrancharticleconfig < 0)
		return -1;

	if (fill_upd_section(upd_section) != 0)
	{
		return -1;
	}

	sprintf(PK, "ARTICLENO=%7s and BRANCHNO=%s", upd_values[0], upd_values[1]);

	/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
	lStatus = FdReadRecord( *Fd_Csubsequentdeliverybrancharticleconfig, PK, &BufCsubsequentdeliverybrancharticleconfigOld, errmld );

	if (lStatus != 0)
	{
		strcpy(errmld, "CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG (Lesen einer Zeile): ");
		strcat(errmld, DynErrmld());
		return lStatus;
	}
	/* ----------------------------------------------------------------------------- */

	sprintf(sql, "UPDATE csubsequentdeliverybrancharticleconfig %s "
		"WHERE articleno = %s AND branchno=%s",
		upd_section, upd_values[0], upd_values[1]);

	lStatus = SqlExecuteImm(sql);

	if (lStatus != 0)
	{
		strcpy(errmld, "csubsequentdeliverybrancharticleconfig (Update einer Zeile): ");
		strcat(errmld, DynErrmld());
	}
	else
	{
		WriteProtZeile(fd_prot);

		FdReadRecord(*Fd_Csubsequentdeliverybrancharticleconfig, PK, &BufCSubSeqDelUpd, errmld);

		/* ---------------------------- N E U   f u e r   P r o t o k o l -------------- */
		if (lStatus == 0)
		{
			lStatus = FdReadRecord( *Fd_Csubsequentdeliverybrancharticleconfig, PK, &BufCsubsequentdeliverybrancharticleconfigAkt, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG (Lesen einer Zeile): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			static char  csubsequentdeliverybrancharticleconfigTab[] = "csubsequentdeliverybrancharticleconfig";
			static void *csubsequentdeliverybrancharticleconfigDesc  = NULL;

			lStatus = SqlGetTabDesc( csubsequentdeliverybrancharticleconfigTab, &csubsequentdeliverybrancharticleconfigDesc, DESC_DEFAULT, errmld );

			if (lStatus != 0)
			{
				strcpy(errmld, "CSUBSEQUENTDELIVERYBRANCHARTICLECONFIG (Lesen der Description): ");
				strcat(errmld, DynErrmld());
				return lStatus;
			}

			if (memcmp(&BufCsubsequentdeliverybrancharticleconfigOld, &BufCsubsequentdeliverybrancharticleconfigAkt, sizeof(BufCsubsequentdeliverybrancharticleconfigAkt)) != 0)
			{
				lStatus = Insert_Protokoll(	P_UPDATE, V_PROTO_VERTEIL, csubsequentdeliverybrancharticleconfigDesc,
											&BufCsubsequentdeliverybrancharticleconfigOld, &BufCsubsequentdeliverybrancharticleconfigAkt, PK,
											user, "", 0, errmld );
			}
		}
		/* ----------------------------------------------------------------------------- */
	}

	return lStatus;
}

/* ------------------------------------------------------------------- */
int upd_negval_zartikel(const int *Fd_ZArtikel, char* errmld)
{
	return upd_negval("zartikel", "artikel_nr", Fd_ZArtikel, errmld);
}

/* ------------------------------------------------------------------- */
int upd_negval_zartfrance(const int *Fd_ZArtFrance, char* errmld)
{
	return upd_negval("zartfrance", "articleno", Fd_ZArtFrance, errmld);
}

/* ------------------------------------------------------------------- */
int upd_negval_zartserbia(const int *Fd_ZArtSerbia, char* errmld)
{
	return upd_negval("zartserbia", "articleno", Fd_ZArtSerbia, errmld);
}

/* ------------------------------------------------------------------- */
int upd_negval_zartaustria(const int *Fd_ZArtAustria, char* errmld)
{
	return upd_negval("zartaustria", "artikel_nr", Fd_ZArtAustria, errmld);
}

int upd_negval(const char* table_name, const char* col_name, const int* fd, char* errmld)
{
	long lStatus = 0;
	char sql [1000];			// update-stmt
	char set_statm [500];		// set-part of update-stmt
	char zapflege_statm [500];	// where-part for zapflege-stmt
	char statm_temp [1000];		// stmt for zapflege

	char temp[100];
	int updcol = 0;
	
	if (*fd < 0) 
		return -1;

	if ( strcmp ( neg_values[0], "" ) != 0 )
	{
		sprintf ( set_statm, "%s = '%s'", upd_columns[1], neg_values[0] );
		updcol = 1;

		sprintf ( zapflege_statm, "%s != '%s'", upd_columns[1], neg_values[0] );
	}

	if ( strcmp ( neg_values[1], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[2], neg_values[1] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[2], neg_values[1] );
			strcat ( zapflege_statm, temp );	
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[2], neg_values[1] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[2], neg_values[1] );
		}
	}

	if ( strcmp ( neg_values[2], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[3], neg_values[2] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[3], neg_values[2] );
			strcat ( zapflege_statm, temp );	
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[3], neg_values[2] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[3], neg_values[2] );
		}
	}

	if ( strcmp ( neg_values[3], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[4], neg_values[3] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[4], neg_values[3] );
			strcat ( zapflege_statm, temp );
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[4], neg_values[3] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[4], neg_values[3] );
		}
	}

	if ( strcmp ( neg_values[4], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[5], neg_values[4] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[5], neg_values[4] );
			strcat ( zapflege_statm, temp );
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[5], neg_values[4] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[5], neg_values[4] );
		}
	}

	if ( strcmp ( neg_values[5], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[6], neg_values[5] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[6], neg_values[5] );
			strcat ( zapflege_statm, temp );
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[6], neg_values[5] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[6], neg_values[5] );
		}
	}

	if ( strcmp ( neg_values[6], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[7], neg_values[6] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[7], neg_values[6] );
			strcat ( zapflege_statm, temp );
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[7], neg_values[6] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[7], neg_values[6] );
		}
	}

	if ( strcmp ( neg_values[7], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[8], neg_values[7] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[8], neg_values[7] );
			strcat ( zapflege_statm, temp );
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[8], neg_values[7] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[8], neg_values[7] );
		}
	}

	if ( strcmp ( neg_values[8], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[9], neg_values[8] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[9], neg_values[8] );
			strcat ( zapflege_statm, temp );
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[9], neg_values[8] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[9], neg_values[8] );
		}
	}

	if ( strcmp ( neg_values[9], "" ) != 0 )
	{
		if ( updcol != 0 )
		{
			strcat( set_statm, " , " );
			sprintf ( temp, "%s = '%s'", upd_columns[10], neg_values[9] );
			strcat ( set_statm, temp );

			sprintf ( temp, " or %s != '%s'", upd_columns[10], neg_values[9] );
			strcat ( zapflege_statm, temp );
		}
		else
		{
			sprintf ( set_statm, "%s = '%s'", upd_columns[10], neg_values[9] );
			updcol = 1;

			sprintf ( zapflege_statm, "%s != '%s'", upd_columns[10], neg_values[9] );
		}
	}

	if ( updcol == 1 )
	{
		if ( SqlBeginWork() == 0 )
		{
			//-----ZaPflege schreiben ------------ 
			sprintf ( statm_temp, "insert into zapflege ( artikel_nr, datum ) "
										" select %s, %ld from %s where %s not in "
												"(select artikel_nr from zputil_temp) and %s and "
												"%s not in (select artikel_nr from zapflege where "
												"datum = %ld)", 
						col_name, tages_datum, table_name, col_name, zapflege_statm, col_name, tages_datum);

			lStatus = SqlExecuteImm ( statm_temp );
			//-----------------
			
			if ( lStatus == 0 )
			{
				sprintf ( sql, "update %s set %s where %s not in "
							"( select artikel_nr from zputil_temp )", table_name, set_statm, col_name);

				lStatus = SqlExecuteImm ( sql );
			}

			if ( lStatus != 0 )
			{
				strcpy( errmld, DynErrmld() );
				SqlRollbackWork();
			}
			else
				SqlCommitWork();
		}
		else
			strcpy( errmld, DynErrmld() );
	}

	return lStatus;
}

