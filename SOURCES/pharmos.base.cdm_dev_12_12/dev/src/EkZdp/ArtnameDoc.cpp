//////////////////////////////////////////////////////////////////
// ArtnameDoc.cpp  implementation file

#include "stdafx.h"
#include "ekzdp.h"
	
#include "ArtnameDoc.h"
#include "ArticleCodesConverter.h"

// #include <wudu.h>     // spaeter weg
#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>

#include <phxlib/phxutil.h>
#include "FeldBreite.h"
#include "ServerDatum.h"

CArtnameDoc::CArtnameDoc()
{
/*	m_csLangId = "FR";
	
	if (IsPrewhole())
		m_csLangId = "DE";
	else
		m_csLangId = "FR"; 

	if (IsCountry("CH"))
		m_bUseCarticlelang = true;
	else 
		m_bUseCarticlelang = false; */

	m_csLangId = GetCarticlelangCountryCode();

	if (m_csLangId != "")
		m_bUseCarticlelang = true;
	else 
		m_bUseCarticlelang = false;
}

CArtnameDoc::~CArtnameDoc()
{
}

struct struArtName* CArtnameDoc::GetBuffer( int k )
{
	return &m_BufArtname[k];
}

struct struArtName* CArtnameDoc::GetOldBuffer( int k )
{
	return &m_BufOldArtname[k];
}

void CArtnameDoc::InitPflegeDesc( char* Anwender )
{
	m_Anwender = Anwender;
	m_Fd_Zartikel = -1;

//  Zapflege
	m_Fd_Zapflege = -1;

//  Zpznpflege
	m_Fd_Zpznpflege = -1;

//  Zartsekbez
	m_Fd_Sekbez   = -1;

//  Zaneuheit
	m_Fd_Zaneuheit = -1;

// Carticlelang
	m_Fd_Carticlelang = -1;

//	Suche
	m_FdSel = -1;
}

void CArtnameDoc::FreeBufferDesc( )
{
//  Zartikel
	if ( m_Fd_Zartikel >= 0 )
		CloseOneBufferDesc( m_Fd_Zartikel );
	m_Fd_Zartikel = -1;

//  Sekbez
	if ( m_Fd_Sekbez >= 0 )
		CloseOneBufferDesc( m_Fd_Sekbez );
	m_Fd_Sekbez = -1;

//  Zapflege
	if ( m_Fd_Zapflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zapflege );
	m_Fd_Zapflege = -1;

//  Zpznpflege
	if ( m_Fd_Zpznpflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zpznpflege );
	m_Fd_Zpznpflege = -1;

//  Zneuheit
	if ( m_Fd_Zaneuheit >= 0 )
		CloseOneBufferDesc( m_Fd_Zaneuheit );
	m_Fd_Zaneuheit = -1;

//  Carticlelang
	if (m_bUseCarticlelang && ( m_Fd_Carticlelang >= 0 ))
		CloseOneBufferDesc( m_Fd_Carticlelang );
	m_Fd_Carticlelang = -1;
}

/////////////////////////////////////////////////////////////////////////
// ZARTIKEL

// erweitern ???????
void CArtnameDoc::FillCmpIndikator_Zartikel ( )
{ 
	memset( m_CmpIndikator_Zartikel, '0', POSANZ_ZARTIKEL );
	m_CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
/*
	m_CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_ANLAGE]    = '0';
	m_CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER]    = '0';
	m_CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_IFAAENDER] = '0';
	m_CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]      = '0';
*/
	m_CmpIndikator_Zartikel[P_ZARTIKEL_ARTIKEL_NR]      = '1';
	m_CmpIndikator_Zartikel[P_ZARTIKEL_ARTIKEL_NAME]    = '1';
	m_CmpIndikator_Zartikel[P_ZARTIKEL_EINHEIT]         = '1';
	m_CmpIndikator_Zartikel[P_ZARTIKEL_DARREICHFORM]    = '1';
}

void CArtnameDoc::SetPrimekeyCondition ( )
{
	char format[30];
	sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
	sprintf( m_PrimekeyCond, format, m_Buf.ARTIKEL_NR );
//	sprintf( m_PrimekeyCond, "ARTIKEL_NR=%ld", m_Buf.ARTIKEL_NR );
}

int CArtnameDoc::GetBufferDesc_Zartikel( CString &cErrmld )
{
	char *tabelle = "zartikel";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartikel >= 0 ) return 0;

	FillCmpIndikator_Zartikel ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartikel, tabelle,
                                m_CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL,	errmld );
									// !!!!!!!bis 20.12.2000   V_PROTOKOL 
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartikel = -1;
		return -1;
	}
	return 0;
}

long CArtnameDoc::ReadRecord_Zartikel(  CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
    lStatus = ::FdReadRecord( m_Fd_Zartikel, m_PrimekeyCond,
							  &m_Buf, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartikel = m_Buf.zartikel;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus != 100 )
		cErrmld = errmld;
	m_lStatus_Zartikel = lStatus;
	return lStatus;
}

long CArtnameDoc::StoreRecord_Zartikel( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	// Artikel-Mc generieren
	if (IsCountry("BG")) 
		strcpy( m_Buf.ARTIKEL_MC, MakeArtikelMc( m_Buf.ARTIKEL_LANGNAME ) );
	else
		strcpy( m_Buf.ARTIKEL_MC, MakeArtikelMc( m_Buf.ARTIKEL_NAME ) );

	SetPrimekeyCondition ( );

	if ( m_lStatus_Zartikel == 100 )
		lStatus = ::FdDelayInsertRecord( m_Fd_Zartikel, &m_Buf,
									 	 m_PrimekeyCond, errmld);
	else if ( m_lStatus_Zartikel == 0 )
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartikel, &m_Buf,
									     &m_BufOld, 
										 m_PrimekeyCond, errmld );
	else
	{
		lStatus = m_lStatus_Zartikel;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// CARTICLELANG

void CArtnameDoc::FillCmpIndikator_Carticlelang ( )
{ 
	memset( m_CmpIndikator_Carticlelang, '0', POSANZ_CARTICLELANG );
	m_CmpIndikator_Carticlelang[POSANZ_CARTICLELANG] = '\0';
	m_CmpIndikator_Carticlelang[P_CARTICLELANG_LANGID]         = '1';
	m_CmpIndikator_Carticlelang[P_CARTICLELANG_ARTICLENO]      = '1';
	m_CmpIndikator_Carticlelang[P_CARTICLELANG_ARTICLENAME]    = '1';
	m_CmpIndikator_Carticlelang[P_CARTICLELANG_PACKAGINGUNIT]  = '1';
	m_CmpIndikator_Carticlelang[P_CARTICLELANG_PHARMAFORM]	   = '1';
}
                  
void CArtnameDoc::SetPrimekeyConditionCarticlelang ( )
{
	char format[60];
	sprintf( format, "ARTICLENO=%c%d.ld AND LANGID= '%cs'", '%', L_ARTIKEL_NR,'%' );
	sprintf( m_PrimekeyCondCarticlelang, format, m_BufCarticlelang.ARTICLENO, m_csLangId );
}

int CArtnameDoc::GetBufferDesc_Carticlelang( CString &cErrmld )
{
	char *tabelle = "carticlelang";
	long lStatus;
	char errmld[100];
	cErrmld = _T("");

	if (!m_bUseCarticlelang)	// Use Carticlelang ?
		return 0;

	if ( m_Fd_Carticlelang >= 0 ) return 0;

	FillCmpIndikator_Carticlelang ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Carticlelang, tabelle,
                                m_CmpIndikator_Carticlelang, NULL, V_PROTO_VERTEIL,	errmld );

	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Carticlelang = -1;
		return -1;
	}
	return 0;
}

long CArtnameDoc::ReadRecord_Carticlelang(  CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if (!m_bUseCarticlelang)	// Use Carticlelang ?
		return 0;


	SetPrimekeyConditionCarticlelang ( );
    lStatus = ::FdReadRecord( m_Fd_Carticlelang, m_PrimekeyCondCarticlelang,
							  &m_BufCarticlelang, errmld );
	if ( lStatus == 0 )
	{
		m_BufOldCarticlelang = m_BufCarticlelang;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus != 100 )
		cErrmld = errmld;
	m_lStatus_Carticlelang = lStatus;
	return lStatus;
}

long CArtnameDoc::StoreRecord_Carticlelang( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	CString csName;
	int s;

	if (!m_bUseCarticlelang)	// Use Carticlelang ?
		return 0;

	// Artikel-Mc generieren
	if (IsCountry("BG")) 
		strcpy( m_BufCarticlelang.ARTICLEMC, MakeArtikelMc( m_BufCarticlelang.ARTICLENAMELONG ) );
	else
		strcpy( m_BufCarticlelang.ARTICLEMC, MakeArtikelMc( m_BufCarticlelang.ARTICLENAME ) );

	SetPrimekeyConditionCarticlelang ( );

	if ( m_lStatus_Carticlelang == 100 )
		lStatus = ::FdDelayInsertRecord( m_Fd_Carticlelang, &m_BufCarticlelang,
									 	 m_PrimekeyCondCarticlelang, errmld);
	else if ( m_lStatus_Carticlelang == 0 )
	{
		csName = m_BufCarticlelang.ARTICLENAME;
		if (csName.Trim().IsEmpty())
		{
			lStatus = ::FdDelayDeleteRecord( m_Fd_Carticlelang, &m_BufOldCarticlelang,
									     m_PrimekeyCondCarticlelang, errmld );
		}
		else
			lStatus = ::FdDelayUpdateRecord( m_Fd_Carticlelang, &m_BufCarticlelang,
									     &m_BufOldCarticlelang, 
										 m_PrimekeyCondCarticlelang, errmld );
	}
	else
	{
		lStatus = m_lStatus_Carticlelang;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
	{
		// Zpznpflege nur schreiben, wenn sich Carticlelang wirklich geändert hat
		s = ::FdIsRecordModified( m_Fd_Carticlelang, &m_BufCarticlelang, 
				&m_BufOldCarticlelang, errmld );
		if ( s == 1 ) 
		{
			lStatus = StoreRecord_Zpznpflege( cErrmld );

			if ( lStatus == 0 ) 
				cErrmld = _T("");
		}
	}

	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// ZARTSEKBEZ

int CArtnameDoc::GetBufferDesc_Sekbez( CString &cErrmld )
{
	char *tabelle = "zartsekbez";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Sekbez >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Sekbez, tabelle,
                                NULL, NULL, V_PROTOKOL, 
								errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Sekbez = -1;
		return -1;
	}
	return 0;
}

long CArtnameDoc::RemovePharmosSekbez( int k, CString cErrmld )
{
	long lStatus;
	char PrimekeyCond[100];
	char errmld[200];
	CString sql;

	// RR 12/07/05: "Select *" ersetzt
	sql.Format("select %s from ZARTSEKBEZ where ARTIKEL_NR=%ld and PHARMOS_SEKBEZ='1'",
				PROJECTION_ZARTSEKBEZ, m_BufArtname[k].ARTIKEL_NR);

/*	sql.Format( "select * from ZARTSEKBEZ " \
				"where ARTIKEL_NR=%ld and PHARMOS_SEKBEZ='1'",
				m_BufArtname[k].ARTIKEL_NR ); */

    lStatus = ::SqlRead( sql, &m_BufSekbez[0], NULL);
	if ( lStatus == 100 ) return 0;
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		return lStatus;
	}

	sprintf( PrimekeyCond,
			 "ARTIKEL_NR=%ld and ARTIKEL_NAME='%s'",
	 		 m_BufSekbez[0].ARTIKEL_NR,
			 m_BufSekbez[0].ARTIKEL_NAME );

	m_BufOldSekbez[0] = m_BufSekbez[0]; 
	*m_BufSekbez[0].PHARMOS_SEKBEZ = '0';

	lStatus = ::FdDelayUpdateRecord( m_Fd_Sekbez, &m_BufSekbez[0],
								     &m_BufOldSekbez[0], 
									 PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

long CArtnameDoc::StorePharmosSekbez( int k, CString cErrmld )
{
	long lStatus;
	char PrimekeyCond[100];
	char errmld[200];
	CString sql;

	// RR 12/07/05: "Select *" ersetzt
	sql.Format("select %s from ZARTSEKBEZ where ARTIKEL_NR=%ld and ARTIKEL_NAME='%s'",
				PROJECTION_ZARTSEKBEZ, m_BufOldArtname[k].ARTIKEL_NR, m_BufOldArtname[k].ARTIKEL_NAME);

/*	sql.Format( "select * from ZARTSEKBEZ " \
				"where ARTIKEL_NR=%ld and ARTIKEL_NAME='%s'",
				m_BufOldArtname[k].ARTIKEL_NR,			
				m_BufOldArtname[k].ARTIKEL_NAME ); */

    lStatus = ::SqlRead( sql, &m_BufSekbez[1], NULL );

	if ( !( lStatus == 0 || lStatus == 100 ) )
	{
		cErrmld = errmld;
		return lStatus;
	}

	sprintf( PrimekeyCond, 
			 "ARTIKEL_NR=%ld and ARTIKEL_NAME='%s'",
	 		 m_BufOldArtname[k].ARTIKEL_NR,
			 m_BufOldArtname[k].ARTIKEL_NAME );

	if ( lStatus == 0 )
	{
		m_BufOldSekbez[1] = m_BufSekbez[1]; 
		*m_BufSekbez[1].PHARMOS_SEKBEZ = '1';
		lStatus = ::FdDelayUpdateRecord( m_Fd_Sekbez, &m_BufSekbez[1],
									     &m_BufOldSekbez[1], 
										 PrimekeyCond, errmld );
	}
	else
	{
		m_BufSekbez[1].ARTIKEL_NR = m_BufArtname[k].ARTIKEL_NR;
		strcpy( m_BufSekbez[1].ARTIKEL_NAME, m_BufOldArtname[k].ARTIKEL_NAME );
		strcpy( m_BufSekbez[1].ARTIKEL_MC,
			    MakeArtikelMc( m_BufSekbez[1].ARTIKEL_NAME ) );

		memset( m_BufSekbez[1].BEMERKUNGEN, ' ', L_ZARTSEKBEZ_BEMERKUNGEN );
		m_BufSekbez[1].BEMERKUNGEN[L_ZARTSEKBEZ_BEMERKUNGEN] = '\0';

		m_BufSekbez[1].PHARMOS_SEKBEZ[0] = '1';
		m_BufSekbez[1].PHARMOS_SEKBEZ[L_ZARTSEKBEZ_PHARMOS_SEKBEZ] = '\0';

		lStatus = ::FdDelayInsertRecord( m_Fd_Sekbez, &m_BufSekbez[1],
									 	 m_PrimekeyCond, errmld);
	}
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


/////////////////////////////////////////////////////////////////////////
// ZAPFLEGE

int CArtnameDoc::GetBufferDesc_Zapflege( CString &cErrmld )
{
	char *tabelle = "zapflege";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zapflege >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Zapflege, tabelle,
                                NULL, NULL, V_OHNE, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zapflege = -1;
		return -1;
	}
	return 0;
}

long CArtnameDoc::StoreRecord_Zapflege( CString &cErrmld )
{
	long lStatus;
	long datum;
	char PrimekeyCond_Zapflege[100];
	char errmld[200];

	datum = ::Today();
	m_ZapflegeBuf.ARTIKEL_NR = m_Buf.ARTIKEL_NR;
	m_ZapflegeBuf.DATUM		 = datum;

	sprintf( PrimekeyCond_Zapflege, "ARTIKEL_NR=%ld and DATUM=%ld",
									m_ZapflegeBuf.ARTIKEL_NR, 
									m_ZapflegeBuf.DATUM       );

    lStatus = ::FdReadRecord( m_Fd_Zapflege, PrimekeyCond_Zapflege,
				  			  &m_ZapflegeBuf, errmld );

	if ( lStatus == 100 )
	{
		m_ZapflegeBuf.ARTIKEL_NR = m_Buf.ARTIKEL_NR;
		m_ZapflegeBuf.DATUM		 = datum;
		lStatus = ::FdDelayInsertRecord( m_Fd_Zapflege, &m_ZapflegeBuf, 
										 PrimekeyCond_Zapflege, errmld );
	}

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// ZPZNPFLEGE

int CArtnameDoc::GetBufferDesc_Zpznpflege( CString &cErrmld )
{
	char *tabelle = "zpznpflege";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zpznpflege >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Zpznpflege, tabelle,
                                NULL, NULL, V_OHNE, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zpznpflege = -1;
		return -1;
	}
	return 0;
}

long CArtnameDoc::StoreRecord_Zpznpflege( CString &cErrmld )
{
	long lStatus;
	long datum;
	char PrimekeyCond_Zpznpflege[100];
	char errmld[200];

	datum = ::Today();
	m_ZpznpflegeBuf.ARTIKEL_NR = m_BufCarticlelang.ARTICLENO;
	m_ZpznpflegeBuf.DATUM      = datum;
	strcpy (m_ZpznpflegeBuf.DEZAP_SA, "11");
	
	sprintf( PrimekeyCond_Zpznpflege, "ARTIKEL_NR=%ld and DATUM=%ld and DEZAP_SA = '%s'",
									m_ZpznpflegeBuf.ARTIKEL_NR, 
									m_ZpznpflegeBuf.DATUM,
									m_ZpznpflegeBuf.DEZAP_SA );

    lStatus = ::FdReadRecord( m_Fd_Zpznpflege, PrimekeyCond_Zpznpflege,
				  			  &m_ZpznpflegeBuf, errmld );

	if ( lStatus == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_Zpznpflege, &m_ZpznpflegeBuf, 
										 PrimekeyCond_Zpznpflege, errmld );
	}

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// ZANEUHEIT

int CArtnameDoc::GetBufferDesc_Zaneuheit( CString &cErrmld )
{
	char *tabelle = "zaneuheit";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zaneuheit >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Zaneuheit, tabelle,
                                NULL, NULL, V_OHNE, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zaneuheit = -1;
		return -1;
	}
	return 0;
}


long CArtnameDoc::DeleteRecord_Zaneuheit( char programm, CString &cErrmld )
{
	long lStatus;
	char prog[2];
	char errmld[200];
	char PrimekeyCond_Zaneuheit[100];

	prog[0] = programm;
	prog[1] = '\0';

	strcpy( m_ZaneuheitBuf.PFLEGEPROGRAMM, prog );
	m_ZaneuheitBuf.ARTIKEL_NR  = m_Buf.ARTIKEL_NR;

	sprintf( PrimekeyCond_Zaneuheit, "PFLEGEPROGRAMM='%s' and ARTIKEL_NR=%ld",
	 							     m_ZaneuheitBuf.PFLEGEPROGRAMM, 
									 m_ZaneuheitBuf.ARTIKEL_NR       );
	lStatus = ::FdReadRecord( m_Fd_Zaneuheit, PrimekeyCond_Zaneuheit,
				  			  &m_ZaneuheitBuf, errmld );

	if ( lStatus == 0 )
	{
		lStatus = ::FdDeleteRecord( m_Fd_Zaneuheit, &m_ZaneuheitBuf, 
									PrimekeyCond_Zaneuheit, errmld );
		if ( lStatus != 0 ) cErrmld = errmld;
	}
	else if ( lStatus == 100 )
		lStatus = 0;
	else
		cErrmld = errmld;

	return lStatus;
}


////////////////////////////////////////////////////////////////////
// Zusammen

int CArtnameDoc::GetBufferDesc( CString &cErrmld )
{
	if ( GetBufferDesc_Zartikel ( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_Sekbez	( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_Zapflege ( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_Zpznpflege ( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_Zaneuheit( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_Carticlelang( cErrmld ) != 0 ) return -1;
   return 0;
}


long CArtnameDoc::ReadRecord(  CString &cErrmld )
{
	long lStatus;

	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

    lStatus = ReadRecord_Zartikel( cErrmld ); // Artikel immer zuerst lesen
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

	m_BufOld = m_Buf;  // gelesenen Satz sichern: erst hier

	return m_lStatus_Zartikel;   // !!!!!!!!!!!!!!!!!
}

long CArtnameDoc::StoreSingleRecord( int k, CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 )  return -1;

	FillZartikelFromArtname( k );

	if ( ReadRecord( cErrmld ) != 0 ) return -1;

	FillZartikelFromArtname( k );
	strcpy( m_Buf.BEARBEITER, m_Anwender );
	long datum = ::Today();
	m_Buf.DATUM_AENDER = datum;
	
	// zartikel
    if ( StoreRecord_Zartikel( cErrmld ) != 0 ) return -1;

	// sekbez
	if ( *m_BufArtname[k].HAT_SEKBEZ == '*' && 
		 strcmp( m_BufArtname[k].ARTIKEL_NAME,
				 m_BufOldArtname[k].ARTIKEL_NAME ) != 0 )
	{
		if ( RemovePharmosSekbez( k, cErrmld ) != 0 ) return -1;
		if ( StorePharmosSekbez ( k, cErrmld ) != 0 ) return -1;
	}

//  neu Zapflege
    if ( StoreRecord_Zapflege( cErrmld ) != 0 ) return -1;

//  neu Zneuheit
	if ( DeleteRecord_Zaneuheit( NH_NEUHEIT_PHARMOS, cErrmld ) != 0 )
		return -1;

	char errmld[200];
	if ( FdTransact( errmld ) != 0 ) 
	{
		cErrmld = errmld;
		return -1;
	}

	return 0;
}


long CArtnameDoc::StoreSingleRecord_Carticlelang( int k, CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 )  return -1;

	FillCarticlelangFromArtname( k );

//	if ( ReadRecord_Carticlelang( cErrmld ) != 0 ) return -1;
	ReadRecord_Carticlelang( cErrmld );	// auch Neuanlagen möglich

	FillCarticlelangFromArtname( k );
	
	// Carticlelang
    if ( StoreRecord_Carticlelang( cErrmld ) != 0 ) return -1;

	char errmld[200];
	if ( FdTransact( errmld ) != 0 ) 
	{
		cErrmld = errmld;
		return -1;
	}

	return 0;
}


long CArtnameDoc::StoreRecord( int *ind,  CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 )  return -1;
	int  k;
	long s;
	k = 0;
	s = 0;

	while ( s == 0 && k < NUMBER_OF_ARTIKEL && m_BufArtname[k].ARTIKEL_NR != 0 )
	{
		if ( IsRecordModified( k ) ) {
			s = StoreSingleRecord( k, cErrmld );
		}
		if ( IsRecordModifiedCarticlelang( k ) ) {
			s = StoreSingleRecord_Carticlelang( k, cErrmld );
		}

		if ( s == 0 ) k++;
	}
	*ind = k;
	return s;
}

void CArtnameDoc::FillZartikelFromArtname( int k )
{
	m_Buf.ARTIKEL_NR = m_BufArtname[k].ARTIKEL_NR;
	strcpy( m_Buf.ARTIKEL_NAME, m_BufArtname[k].ARTIKEL_NAME );
//	strcpy( m_Buf.ARTIKEL_MC, m_BufArtname[k].ARTIKEL_MC );
//	strcpy( m_Buf.zartikel.ARTIKEL_MC,
//		    MakeArtikelMc( m_Buf.zartikel.ARTIKEL_NAME ) );

	strcpy( m_Buf.EINHEIT, m_BufArtname[k].EINHEIT );
	strcpy( m_Buf.DARREICHFORM, m_BufArtname[k].DARREICHFORM );
/*
	memset( m_BufArtname[i].ARTIKEL_GESPERRT, ' ',L_ZARTIKEL_ARTIKEL_GESPERRT );
	memset( m_BufArtname[i].HAT_SEKBEZ, ' ', 1 );
*/
}
void CArtnameDoc::FillCarticlelangFromArtname( int k )
{
	m_BufCarticlelang.ARTICLENO = m_BufArtname[k].ARTIKEL_NR;
	strcpy( m_BufCarticlelang.LANGID,m_csLangId);
	strcpy( m_BufCarticlelang.ARTICLENAME, m_BufArtname[k].ARTICLENAME );
	strcpy( m_BufCarticlelang.PACKAGINGUNIT, m_BufArtname[k].PACKAGINGUNIT );
	strcpy( m_BufCarticlelang.PHARMAFORM, m_BufArtname[k].PHARMAFORM );
}


int CArtnameDoc::IsRecordModified( int k )
{
	if ( strcmp( m_BufArtname[k].ARTIKEL_NAME, 
		         m_BufOldArtname[k].ARTIKEL_NAME ) != 0 ) return 1;
	if ( strcmp( m_BufArtname[k].EINHEIT, 
			     m_BufOldArtname[k].EINHEIT ) != 0 ) return 1;
	if ( strcmp( m_BufArtname[k].DARREICHFORM,
				 m_BufOldArtname[k].DARREICHFORM ) !=0 ) return 1;
/*
	memset( m_BufArtname[i].ARTIKEL_GESPERRT, ' ',L_ZARTIKEL_ARTIKEL_GESPERRT );
	memset( m_BufArtname[i].HAT_SEKBEZ, ' ', 1 );
*/
	return 0;
}

int CArtnameDoc::IsRecordModifiedCarticlelang( int k )
{
	if (!m_bUseCarticlelang)	// Use Carticlelang ?
		return 0;

	if ( strcmp( m_BufArtname[k].ARTICLENAME, 
		         m_BufOldArtname[k].ARTICLENAME ) != 0 ) return 1;
	if ( strcmp( m_BufArtname[k].PHARMAFORM, 
			     m_BufOldArtname[k].PHARMAFORM ) != 0 ) return 1;
	if ( strcmp( m_BufArtname[k].PACKAGINGUNIT,
				 m_BufOldArtname[k].PACKAGINGUNIT ) !=0 ) return 1;

	return 0;
}


///////////////////////////////////////////////////////////////////////
// Suche

void CArtnameDoc::InitArtnameBuffer( int anz )
{
	int i;
	for ( i = anz; i < NUMBER_OF_ARTIKEL; i++ )
	{
		memset( ( char*) &m_BufArtname[i], '\0', sizeof( struct struArtName ) );
		m_BufArtname[i].ARTIKEL_NR = 0;
		memset( m_BufArtname[i].ARTIKEL_MC, ' ',L_ZARTIKEL_ARTIKEL_MC );
		memset( m_BufArtname[i].ARTIKEL_NAME, ' ',L_ZARTIKEL_ARTIKEL_NAME );
		memset( m_BufArtname[i].EINHEIT, ' ',L_ZARTIKEL_EINHEIT );
		memset( m_BufArtname[i].DARREICHFORM, ' ',L_ZARTIKEL_DARREICHFORM );
		memset( m_BufArtname[i].ARTIKEL_GESPERRT, ' ',L_ZARTIKEL_ARTIKEL_GESPERRT );
		memset( m_BufArtname[i].HAT_SEKBEZ, ' ', 1 );

		memset( m_BufArtname[i].ARTICLEMC, ' ',L_CARTICLELANG_ARTICLEMC );
		memset( m_BufArtname[i].ARTICLENAME, ' ',L_CARTICLELANG_ARTICLENAME );
		memset( m_BufArtname[i].PACKAGINGUNIT, ' ',L_CARTICLELANG_PACKAGINGUNIT );
		memset( m_BufArtname[i].PHARMAFORM, ' ',L_CARTICLELANG_PHARMAFORM );


	}
}


long CArtnameDoc::LeseEinzelSatz( int k, CString &cErrmld )
{
	long s;
	s = SqlFetch( m_FdSel, 1, &m_BufArtname[k], NULL );
	if ( s == 0 )
	{
		if ( *m_BufArtname[k].ARTIKEL_GESPERRT == '1' )
			 *m_BufArtname[k].ARTIKEL_GESPERRT = 'J';
		 else
			 *m_BufArtname[k].ARTIKEL_GESPERRT = 'N';	

		CString sql;
		sql.Format( "select PHARMOS_SEKBEZ from ZARTSEKBEZ "\
		            "where ZARTSEKBEZ.ARTIKEL_NR=%ld and PHARMOS_SEKBEZ='1'",
					m_BufArtname[k].ARTIKEL_NR );
		s = SqlRead( sql, m_BufArtname[k].HAT_SEKBEZ, NULL );
		if ( s == 0 )
			 *m_BufArtname[k].HAT_SEKBEZ = 'J';
		else
			 *m_BufArtname[k].HAT_SEKBEZ = 'N';			 
		if ( s == 100 ) s = 0;

		if (m_bUseCarticlelang)
		{
			sql.Format( "select ARTICLEMC,ARTICLENAME,PACKAGINGUNIT,PHARMAFORM from CARTICLELANG "\
		            "where ARTICLENO=%ld and LANGID='%s'",
					m_BufArtname[k].ARTIKEL_NR,m_csLangId );
			s = SqlRead( sql, m_BufArtname[k].ARTICLEMC,m_BufArtname[k].ARTICLENAME,
			              m_BufArtname[k].PACKAGINGUNIT,m_BufArtname[k].PHARMAFORM, NULL );
			if ( s == 100 ) s = 0;
		}
		m_BufOldArtname[k] = m_BufArtname[k];
		if ( s != 0 )
		{	
			cErrmld  = CResString::ex().getStrTblText(IDS_STRING44);
			cErrmld += DynErrmld();
		}
	}
	else
	{	
		cErrmld  = CResString::ex().getStrTblText(IDS_STRING45);
		cErrmld += DynErrmld();
	}
	return s;
}


bool CArtnameDoc::IsNumber( CString cStr )
{
	CString str;
	str = cStr;
	str.TrimLeft();
	str.TrimRight();
	if ( str.IsEmpty() ) return false;

	int i;
	i = 0;
	while ( i < str.GetLength( ) )
	{
		if ( !isdigit( (unsigned char)str.GetAt( i ) ) )
			return false;
		i++;
	}
	return true;
}

long CArtnameDoc::StartSuche( CString SuchB1, int *anz, CString &cErrmld )
{
	CString sql;

	InitArtnameBuffer( 0 );

	SuchB1.TrimLeft();
	SuchB1.TrimRight();

	CString SuchB2;
	SuchB2 = SuchB1.Mid(1, SuchB1.GetLength() - 1);

	sql = "select ARTIKEL_NR,ARTIKEL_MC,ARTIKEL_NAME," \
			"EINHEIT,DARREICHFORM,ARTIKEL_GESPERRT " \
			"from ZARTIKEL, CARTICLECODES " \
			"where ZARTIKEL.ARTIKEL_NR = CARTICLECODES.ARTICLENO and PREFERRED_FLAG = 1 and ";
//	if ( SuchB1.GetLength( ) > 0 && SuchB1.GetAt( 0 ) == '#' )
	if ( IsNumber( SuchB1 ) )
	{
 		CString nr;
//		nr.Format("%ld", atol( SuchB1.Mid(1)));
//		nr.Format("%ld", atol( SuchB1 ) );	

		nr.Format("%ld", CArticleCodesConverter::getArticleNoByCode( SuchB1, cErrmld ) );

		sql += " ZARTIKEL.ARTIKEL_NR>=";
		sql += nr;
		sql += " order by ZARTIKEL.ARTIKEL_NR";
	}
	else
	{
		if ( SuchB1.GetLength() == 0 )
		{
			sql += "ZARTIKEL.ARTIKEL_MC>=' '";
			sql += " order by ZARTIKEL.ARTIKEL_MC";
		}
		else if (SuchB1.GetAt( 0 ) == '#' && IsNumber( SuchB2 ) )
		{
			sql += "ZARTIKEL.HERSTELLER_NR = ";
			sql += SuchB2;
			sql += " order by ZARTIKEL.ARTIKEL_MC";
		}
		else
		{
			sql += "ZARTIKEL.ARTIKEL_MC matches ";
			sql += AppendStar( MakeArtikelMc( SuchB1 ) );
			sql += " order by ZARTIKEL.ARTIKEL_MC";
		}
//		sql += " order by ARTIKEL_MC";
	}
	
	long s;
	CloseSuche();
	s = SqlOpenCsWh( &m_FdSel, sql );

	*anz = 0;

	if ( s != 0 )
	{
		cErrmld = DynErrmld();
		return s;
	}

	int k;
	k = 0;
	while ( s == 0 && k < NUMBER_OF_ARTIKEL )
	{
		s = LeseEinzelSatz( k, cErrmld );
		if ( s == 0 ) k++;
	}
	if ( k == 0 && s == 100 )
	{
		cErrmld = CResString::ex().getStrTblText(IDS_STRING46);
		return s;
	}

	if ( s == 100 ) s = 0;

	if ( s == 0 )
		*anz = k;
	return s;
}

long CArtnameDoc::NextSuche( int *anz, CString &cErrmld )
{
	long s;
	int  k;
	InitArtnameBuffer( 0 );
	s = 0;
	k = 0;
	while ( s == 0 && k < NUMBER_OF_ARTIKEL )
	{
		s = LeseEinzelSatz( k, cErrmld );
		if ( s == 0 ) k++;
	}
	if ( s == 100 ) s = 0;

	if ( s == 0 )
		*anz = k;
	return s;
}



void CArtnameDoc::CloseSuche()
{
	if ( m_FdSel != -1 )
		SqlCloseCs( m_FdSel );
	m_FdSel = -1;
}