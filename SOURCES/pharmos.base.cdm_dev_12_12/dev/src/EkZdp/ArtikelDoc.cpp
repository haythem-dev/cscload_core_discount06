//////////////////////////////////////////////////////////////////
// ArtikelDoc.cpp  implementation file

#include "stdafx.h"

// wenn mit Bssichg automatisch aendern
#include "ekzdp.h"   
#include "BssichG.h"
	
#include "ArtikelDoc.h"

//#include <wudu.h>     // spaeter weg
#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups//wpp_bufd.h>

#include <hdatum/phodate.h>

#include <phxlib/phxutil.h>
#include "FeldBreite.h"
#include "ServerDatum.h"
#include "zart_gen.h"

#include "StellerUpdate.h"
#include "ArticleCodesDoc.h"

CArtikelDoc::CArtikelDoc()
{
	// !!!!!!!!!!!!!!!!!!!!!Neu 10.10.1998
	m_Fd_Zartikel			= -1;
	m_Fd_Ean				= -1;
	m_Fd_Artve				= -1;
	m_Fd_Cibt				= -1;
	m_Fd_Cartforeigncurr	= -1;
	m_Fd_CSafetyDataSheet	= -1;
	m_Fd_Zartfeb2			= -1;
	m_Fd_Artpreis			= -1;
	m_Fd_HazardNote			= -1;
	m_Fd_Zartwg				= -1;
	m_Fd_Carticlecodes		= -1;
	m_Fd_Ifa				= -1;  
	m_Fd_IfaOart			= -1;
	m_Fd_Sekbez				= -1;
	m_Fd_Artnrbl			= -1;
	m_Fd_Zapflege			= -1;
	m_Fd_CTransferCsc		= -1;
	m_Fd_Zpznpflege			= -1;
	m_Fd_Zartaustria		= -1;
	m_Fd_Zartswitzerland	= -1;
	m_Fd_Carticlelang		= -1;
	m_Fd_Carticleext		= -1;
	m_Fd_Cartrefundfrance	= -1;
	m_Fd_Zartfrance			= -1;
	m_Fd_Zartcroatia		= -1;
	m_Fd_Zartbulgaria		= -1;
	m_Fd_Zartserbia			= -1;
	m_Fd_Clioart			= -1;
	m_Fd_Lppr2Article		= -1;
	m_Fd_Zaneuheit			= -1;
	m_Fd_CRegisters			= -1;
	m_Fd_CRegistersPrices	= -1;
	m_Fd_CNhifPrices		= -1;
	m_Fd_PrewholeArtCustomerGroups = -1;
	m_Fd_CArtMedActor		= -1;

	m_blnCHazardClassificationLoaded = false;
	for (int i = 0; i < NUMBER_OF_HAZARDCLASSIFICATIONS; i++)
	{
		m_pCHazardClassification[i] = NULL;
	}
	m_blnPrewholeCustomerGroupLoaded = false;
	for (int i = 0; i < NUMBER_OF_PREWHOLECUSTOMERGROUP; i++)
	{
		m_pPrewholeCustomerGroup[i] = NULL;
	}
	m_tagesdatum = 0;
}

CArtikelDoc::~CArtikelDoc()
{
	FreeBufferDesc( );	// !!! neu 11.10.1998
	CleanupMemory();
}

void CArtikelDoc::CleanupMemory()
{
	for (int i = 0; i < NUMBER_OF_HAZARDCLASSIFICATIONS; i++)
	{
		if (m_pCHazardClassification[i] != NULL)
		{
			delete m_pCHazardClassification[i];
			m_pCHazardClassification[i] = NULL;
		}
	}
	for (int i = 0; i < NUMBER_OF_PREWHOLECUSTOMERGROUP; i++)
	{
		if (m_pPrewholeCustomerGroup[i] != NULL)
		{
			delete m_pPrewholeCustomerGroup[i];
			m_pPrewholeCustomerGroup[i] = NULL;
		}
	}
}

void CArtikelDoc::FillCTransferCscFields(struct ZARTIKEL * bufArtikelNew, struct ZARTIKEL * bufArtikelOld)
{
	// add further fields which should be transferred to KSC here and increase NUM_OF_CSC_TRANSFERS
	m_CscTransfers[0].fieldType = WERT_CHAR;
	m_CscTransfers[0].fieldName = "NAHRUNGSERGAENZUNG";
	m_CscTransfers[0].fieldValueNew = &bufArtikelNew->NAHRUNGSERGAENZUNG;
	m_CscTransfers[0].fieldValueOld = &bufArtikelOld->NAHRUNGSERGAENZUNG;
}

struct PFL_ARTIKEL* CArtikelDoc::GetBuffer()
{
	return &m_Buf;
}

struct PFL_ARTIKEL* CArtikelDoc::GetOldBuffer()
{
	return &m_BufOld;
}

struct CDSOART* CArtikelDoc::GetDsOArt()
{
	return &cdsoart;
}

struct NUMMEREK* CArtikelDoc::GetNummerek()
{
	return &nummerek;
}

struct CLIOART* CArtikelDoc::GetClioart()
{
	return &clioart;
}

void CArtikelDoc::SetTagesdatum( long datum )
{
	m_tagesdatum = datum;
}

void CArtikelDoc::InitPflegeDesc( char* Anwender )
{
	m_Anwender = Anwender;
	m_Fd_Zartikel			= -1;
	m_Fd_Ean				= -1;
	m_Fd_Artve				= -1;
	m_Fd_Cibt				= -1;
	m_Fd_Cartforeigncurr	= -1;
	m_Fd_CSafetyDataSheet	= -1;
	m_Fd_Zartfeb2			= -1;
	m_Fd_Artpreis			= -1;
	m_Fd_HazardNote			= -1;
	m_Fd_Zartwg				= -1;
	m_Fd_CRegisters = -1;
	m_Fd_CRegistersPrices = -1;
	m_Fd_CNhifPrices = -1;

//  IFA
	m_Fd_Ifa = -1;   
	m_Fd_IfaOart = -1; 
	m_bIfaPflege = FALSE;	

//  Sekbez
	m_Fd_Sekbez = -1;

//  Zapflege
	m_Fd_Zapflege = -1;
	m_Fd_CTransferCsc = -1;

//  Zaneuheit
	m_Fd_Zaneuheit = -1;

	m_Fd_Artnrbl			= -1;
	m_Fd_Zartaustria		= -1;
	m_Fd_Zartswitzerland	= -1;
	m_Fd_Carticlelang		= -1;
	m_Fd_Zpznpflege			= -1;
	m_Fd_Carticlecodes		= -1;
	m_Fd_Zartfrance			= -1;
	m_Fd_Cdsoart			= -1;
	m_Fd_Zartcroatia		= -1;
	m_Fd_Carticleext		= -1;
	m_Fd_Cartrefundfrance	= -1;
	m_Fd_Zartbulgaria		= -1;
	m_Fd_Zartserbia			= -1;
	m_Fd_Clioart			= -1;
	m_Fd_Lppr2Article		= -1;

	m_Fd_Nummerek			= -1;
	m_Fd_PrewholeArtCustomerGroups = -1;
	m_Fd_CArtMedActor = -1;

	m_bNummerekUpdate = false;	

	FillCTransferCscFields(&m_Buf.zartikel, &m_BufOld.zartikel);
}

void CArtikelDoc::StoreBuffer()
{
    m_BufSave = m_Buf;
	for (short i = 0; i < 4; ++i)
	{
		m_CArtMedActorBufSave[i] = m_CArtMedActorBuf[i];
	}
}

void CArtikelDoc::FreeBufferDesc( )
{
	if ( m_Fd_Zartikel >= 0 )
		CloseOneBufferDesc( m_Fd_Zartikel );
	m_Fd_Zartikel = -1;

	if ( m_Fd_Ean >= 0 )
		CloseOneBufferDesc( m_Fd_Ean );
	m_Fd_Ean = -1;

	if ( m_Fd_Artve >= 0 )
		CloseOneBufferDesc( m_Fd_Artve );
	m_Fd_Artve = -1;

	if ( m_Fd_Cibt >= 0 )
		CloseOneBufferDesc( m_Fd_Cibt );
	m_Fd_Cibt = -1;

	if ( m_Fd_Cartforeigncurr >= 0 )
		CloseOneBufferDesc( m_Fd_Cartforeigncurr );
	m_Fd_Cartforeigncurr = -1;

	if ( m_Fd_CSafetyDataSheet >= 0 )
		CloseOneBufferDesc( m_Fd_CSafetyDataSheet );
	m_Fd_CSafetyDataSheet = -1;

	if ( m_Fd_Zartfeb2 >= 0 )
		CloseOneBufferDesc( m_Fd_Zartfeb2 );
	m_Fd_Zartfeb2 = -1;

	if ( m_Fd_Artpreis >= 0 )
		CloseOneBufferDesc( m_Fd_Artpreis );
	m_Fd_Artpreis = -1;

	if ( m_Fd_HazardNote >= 0 )
		CloseOneBufferDesc( m_Fd_HazardNote );
	m_Fd_HazardNote = -1;

	if ( m_Fd_Zartwg >= 0 )
		CloseOneBufferDesc( m_Fd_Zartwg );
	m_Fd_Zartwg = -1;

//  Ifa
	if ( m_Fd_Ifa >= 0 )
		CloseOneBufferDesc( m_Fd_Ifa );
	m_Fd_Ifa = -1;

	if ( m_Fd_IfaOart >= 0 )
		CloseOneBufferDesc( m_Fd_IfaOart );
	m_Fd_IfaOart = -1;

//  Sekbez
	if ( m_Fd_Sekbez >= 0 )
		CloseOneBufferDesc( m_Fd_Sekbez );
	m_Fd_Sekbez = -1;

//  Zapflege
	if ( m_Fd_Zapflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zapflege );
	m_Fd_Zapflege = -1;

	if ( m_Fd_CTransferCsc >= 0 )
		CloseOneBufferDesc( m_Fd_CTransferCsc );
	m_Fd_CTransferCsc = -1;	

	if ( m_Fd_Zpznpflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zpznpflege );
	m_Fd_Zpznpflege = -1;

//  Zaneuheit
	if ( m_Fd_Zaneuheit >= 0 )
		CloseOneBufferDesc( m_Fd_Zaneuheit );
	m_Fd_Zaneuheit = -1;

	if ( m_Fd_Artnrbl >= 0 )
		CloseOneBufferDesc( m_Fd_Artnrbl );
	m_Fd_Artnrbl = -1;

	if ( m_Fd_Zartaustria >= 0 )
		CloseOneBufferDesc( m_Fd_Zartaustria );
	m_Fd_Zartaustria = -1;

	if ( m_Fd_Zartswitzerland >= 0 )
		CloseOneBufferDesc( m_Fd_Zartswitzerland );
	m_Fd_Zartswitzerland = -1;

	if ( m_Fd_Carticlelang >= 0 )
		CloseOneBufferDesc( m_Fd_Carticlelang );
	m_Fd_Carticlelang = -1;

	if ( m_Fd_Carticlecodes >= 0 )
		CloseOneBufferDesc( m_Fd_Carticlecodes );
	m_Fd_Carticlecodes = -1;

	if ( m_Fd_Zartfrance >= 0 )
		CloseOneBufferDesc( m_Fd_Zartfrance );
	m_Fd_Zartfrance = -1;

	if ( m_Fd_Zartcroatia >= 0 )
		CloseOneBufferDesc( m_Fd_Zartcroatia );
	m_Fd_Zartcroatia = -1;

	if ( m_Fd_Carticleext >= 0 )
		CloseOneBufferDesc( m_Fd_Carticleext );
	m_Fd_Carticleext = -1;

	if ( m_Fd_Cartrefundfrance >= 0 )
		CloseOneBufferDesc( m_Fd_Cartrefundfrance );
	m_Fd_Cartrefundfrance = -1;

	if ( m_Fd_Zartbulgaria >= 0 )
		CloseOneBufferDesc( m_Fd_Zartbulgaria );
	m_Fd_Zartbulgaria = -1;

	if (m_Fd_CRegisters >= 0)
		CloseOneBufferDesc(m_Fd_CRegisters);
	m_Fd_CRegisters = -1;

	if (m_Fd_CRegistersPrices >= 0)
		CloseOneBufferDesc(m_Fd_CRegistersPrices);
	m_Fd_CRegistersPrices = -1;

	if (m_Fd_CNhifPrices >= 0)
		CloseOneBufferDesc(m_Fd_CNhifPrices);
	m_Fd_CNhifPrices = -1;

	if ( m_Fd_Zartserbia >= 0 )
		CloseOneBufferDesc( m_Fd_Zartserbia );
	m_Fd_Zartserbia = -1;

	if ( m_Fd_Clioart >= 0 )
		CloseOneBufferDesc( m_Fd_Clioart );
	m_Fd_Clioart = -1;

	if ( m_Fd_Lppr2Article >= 0 )
		CloseOneBufferDesc( m_Fd_Lppr2Article );
	m_Fd_Lppr2Article = -1;

	if (m_Fd_PrewholeArtCustomerGroups >= 0)
		CloseOneBufferDesc(m_Fd_PrewholeArtCustomerGroups);
	m_Fd_PrewholeArtCustomerGroups = -1;

	if (m_Fd_CArtMedActor >= 0)
		CloseOneBufferDesc(m_Fd_CArtMedActor);
	m_Fd_CArtMedActor = -1;
}


/////////////////////////////////////////////////////////////////////////
// ZARTIKEL

void CArtikelDoc::FillCmpIndikator_Zartikel ( )
{ 
	memset( m_CmpIndikator_Zartikel, '1', POSANZ_ZARTIKEL );
	m_CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
	m_CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_ANLAGE]    = '0';
//	m_CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER]    = '0';
	m_CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_IFAAENDER] = '0';
//	m_CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]      = '0';

}

int CArtikelDoc::InitRecord_Zartikel( CString &cErrmld )
{
	if (cErrmld.GetLength()){}
	long nr;
    nr = m_Buf.zartikel.ARTIKEL_NR;
    FdInitTabBuf( m_Fd_Zartikel, &m_Buf.zartikel );
    m_Buf.zartikel.ARTIKEL_NR = nr;

	// spezielle Initialisierung ( Peetz 2.6.98 )
    m_Buf.zartikel.BESTANDSBUCHUNG[0] = '1';
    m_Buf.zartikel.SKONTOFAEHIG[0]    = '1';

	memset( m_Buf.zartikel.ZUZAHLUNG_IFA, '0', L_ZARTIKEL_ZUZAHLUNG_IFA );

	// nur in Deutschland gültige Inits
	if (IsCountry("D"))
	{
		m_Buf.zartikel.TAXPFL[0]          = '1';
	    m_Buf.zartikel.ZUZAHLUNG_IFA[0]   = '2';
		m_Buf.zartikel.ARTIKEL_GESPERRT[0]  = '1';
	}

	// Hersteller-% in Kroatien auf 35
	if (IsCountry("HR"))
	{
		m_Buf.zartikel.HERST_PROZENT = 35.0;
	}

	// Init Verfall für die Schweiz und Prewhole 
	if ( IsCountry("CH") || IsPrewhole() )
	{
		m_Buf.zartikel.VERFALL[0] = '1';
	}

	memset( m_Buf.zartikel.RABATTFAEHIG, '0', L_ZARTIKEL_RABATTFAEHIG );

	m_Buf.zartikel.NAHRUNGSERGAENZUNG[0] = 'N';
	m_Buf.zartikel.ELEKTROSCHROTT[0]   = 'N';

	m_Buf.zartikel.PREISSENKUNG[0]     = '0';
	m_Buf.zartikel.BSSICHG[0]		   = '0';
    m_Buf.zartikel.ANBIETERABSCHLAG[0] = '0';
    m_Buf.zartikel.AUTIDEMARTIKEL[0]   = '0';
    m_Buf.zartikel.FESTBETRARTIKEL[0]  = '0';

	m_Buf.zartikel.REZEPTURARZNEI[0]   = '0';
	m_Buf.zartikel.MEDIZINPRODUKT[0]   = '0';
	m_Buf.zartikel.IMPFSTOFF[0]        = '0';
	m_Buf.zartikel.CE_KENNZEICHEN[0]   = '0';
	m_Buf.zartikel.ARZNEIMITTEL[0]     = '0';
	m_Buf.zartikel.KONTRAZEPTIVUM[0]   = '0';
	m_Buf.zartikel.BIOZID_VERORD[0]    = '0';

	m_Buf.zartikel.ZENTRALPPELIST[0]   = '0';
	m_Buf.zartikel.EKORIGINALHS[0]     = '0';
	m_Buf.zartikel.BESTELL_NUR_OZEK[0] = '0';
	m_Buf.zartikel.HILFSM_VERBRAUCH[0] = '0';
	m_Buf.zartikel.CHARGENARTIKEL[0]   = '0';

	m_Buf.zartikel.HOMOEOPATHIKUM[0]   = '0';
	m_Buf.zartikel.ANTHROPOSOPHIKUM[0] = '0';
	m_Buf.zartikel.PHYTOPHARMAKON[0]   = '0';
	m_Buf.zartikel.TREZEPTARZNEI[0]	   = '0';
	m_Buf.zartikel.AMG_47[0]		   = '0';

	m_Buf.zartikel.BATTERIEGESETZ[0]		= 'N';
	m_Buf.zartikel.NEM_PHAGROPRUEFUNG[0]	= '0';
	m_Buf.zartikel.NEM_ZERTIFIKAT[0]		= '0';

	m_Buf.zartikel.STELLER[0]		   = 'N';
	m_Buf.zartikel.PFLSCHUTZ_VERORD[0] = 'N';

	m_Buf.zartikel.BESTELL_NICHT_AUSL[0] = '0';
	m_Buf.zartikel.EAN_NICHTVORHANDEN[0] = '0';
	m_Buf.zartikel.FAELSCH_GEFAHR[0] = '0';

	m_Buf.zartikel.SIDABLATT[0]		= '0';
	m_Buf.zartikel.GS_HOCHENTZ[0]	= '0';
	m_Buf.zartikel.GS_LEICHTENTZ[0] = '0';
	m_Buf.zartikel.GS_EXPLOSION[0]	= '0';
	m_Buf.zartikel.GS_BRAND[0]		= '0';
	m_Buf.zartikel.GS_AETZEND[0]	= '0';
	m_Buf.zartikel.GS_SEHRGIFTIG[0] = '0';
	m_Buf.zartikel.GS_GIFTIG[0]		= '0';
	m_Buf.zartikel.GS_GESUNDHSCH[0] = '0';
	m_Buf.zartikel.GS_REIZEND[0]	= '0';
	m_Buf.zartikel.GS_UMWELT[0]		= '0';		
	m_Buf.zartikel.NACHLIEFERUNG[0]	= '0';

	m_Buf.zartikel.PSYCHOTROP[0]		= 'N';
	m_Buf.zartikel.PRIVATSORTIMENT[0]	= 'N';
	
/*
	m_Buf.zartikel.DATUM_ANLAGE = m_tagesdatum;
	m_Buf.zartikel.DATUM_AENDER = m_Buf.zartikel.DATUM_ANLAGE;
	strcpy( m_Buf.zartikel.BEARBEITER, m_Anwender );
*/

	return 0;
}

void CArtikelDoc::SetPrimekeyCondition ( )
{
	char format[30];
	sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
	sprintf( m_PrimekeyCond, format, m_Buf.zartikel.ARTIKEL_NR );

//	sprintf( m_PrimekeyCond, "ARTIKEL_NR=%ld", m_Buf.zartikel.ARTIKEL_NR );
}

void CArtikelDoc::RestoreBuffer_Zartikel()
{
    m_BufSave.zartikel.ARTIKEL_NR   = m_Buf.zartikel.ARTIKEL_NR;
	m_BufSave.zartikel.DATUM_ANLAGE = m_Buf.zartikel.DATUM_ANLAGE;
	m_BufSave.zartikel.DATUM_AENDER = m_Buf.zartikel.DATUM_AENDER;
	m_BufSave.zartikel.DATUM_IFAAENDER = m_Buf.zartikel.DATUM_IFAAENDER;
	strcpy( m_BufSave.zartikel.BEARBEITER, m_Buf.zartikel.BEARBEITER );
	strcpy( m_BufSave.zartikel.USER_ANLAGE, m_Buf.zartikel.USER_ANLAGE );
    m_Buf.zartikel = m_BufSave.zartikel;
    m_Buf.zartikel.ARTIKEL_NR	  = m_BufSave.zartikel.ARTIKEL_NR;
	m_Buf.zartikel.DATUM_ANLAGE   = m_BufSave.zartikel.DATUM_ANLAGE;
	m_Buf.zartikel.DATUM_AENDER   = m_BufSave.zartikel.DATUM_AENDER;
	m_Buf.zartikel.DATUM_IFAAENDER = m_BufSave.zartikel.DATUM_IFAAENDER;
	strcpy( m_Buf.zartikel.BEARBEITER, m_BufSave.zartikel.BEARBEITER );
	strcpy( m_Buf.zartikel.USER_ANLAGE, m_BufSave.zartikel.USER_ANLAGE );
}

int CArtikelDoc::GetBufferDesc_Zartikel( CString &cErrmld )
{
	char *tabelle = "zartikel";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartikel >= 0 ) return 0;

	FillCmpIndikator_Zartikel ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartikel, tabelle,
                                m_CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errmld );
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

long CArtikelDoc::ReadRecord_Zartikel( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
    lStatus = ::FdReadRecord( m_Fd_Zartikel, m_PrimekeyCond,
							  &m_Buf.zartikel, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartikel = m_Buf.zartikel;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartikel( cErrmld ) == 0 )
		{
//			m_BufOld.zartikel = m_Buf.zartikel;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;
	m_lStatus_Zartikel = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Zartikel( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	// Artikel-Mc generieren
	if (IsCountry("BG")) 
		strcpy( m_Buf.zartikel.ARTIKEL_MC, MakeArtikelMc( m_Buf.zartikel.ARTIKEL_LANGNAME ) );
	else
		strcpy( m_Buf.zartikel.ARTIKEL_MC, MakeArtikelMc( m_Buf.zartikel.ARTIKEL_NAME ) );

	SetPrimekeyCondition ( );
	if ( m_lStatus_Zartikel == 100 )
		lStatus = ::FdDelayInsertRecord( m_Fd_Zartikel, &m_Buf.zartikel,
									 	 m_PrimekeyCond, errmld);
	else if ( m_lStatus_Zartikel == 0 )
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartikel, &m_Buf.zartikel,
									     &m_BufOld.zartikel, 
										 m_PrimekeyCond, errmld );
	else
	{
		lStatus = m_lStatus_Zartikel;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	
	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else
	{
		// notwendige Updates auf Artikelstamm, falls Steller-Artikel
		if (m_Buf.zartikel.STELLER[0] == 'T' )
		{
			CStellerUpdate StellUpd;

			if (IsCountry("CH"))
				StellUpd.StellerArtikelAenderung (GetCountry(), &m_Buf.zartikel, &m_Buf.zartswitzerland);
			else // if (IsCountry("D")) <-- für alle Länder
				StellUpd.StellerArtikelAenderung (GetCountry(), &m_Buf.zartikel);
		}

		// wenn Artikelneuanlage mit PZN aus nummerek, die nächste freie PZN dort wieder reinstellen
		if ( m_lStatus_Zartikel == 100 && m_bNummerekUpdate && m_Buf.zartikel.ARTIKEL_NR == nummerek.NR)
		{
			int pz;

			nummerek.NR = 10 * (((int) nummerek.NR / 10) + 1);			
			pz = GetPruefZiffer7( nummerek.NR );
			nummerek.NR += pz;

			lStatus = StoreNummerek( cErrmld );

			m_bNummerekUpdate = false;
		}	
			
		// EAN-Änderungen in zpznpflege schreiben
		if (lStatus == 0)
		{
			if ( m_lStatus_Zartikel == 100 )
			{
				char leer[ L_EAN_EAN_NR + 1 ];
				memset( leer, ' ', L_EAN_EAN_NR );
				
				if ( memcmp( m_Buf.ean.EAN_NR, leer, L_EAN_EAN_NR ) != 0 )
					lStatus = StoreRecord_Zpznpflege( m_tagesdatum, "09", cErrmld );
			}
			else // m_lStatus_Zartikel == 0
			{
				if ( strcmp ( m_BufOld.ean.EAN_NR , m_Buf.ean.EAN_NR ) != 0 )
					lStatus = StoreRecord_Zpznpflege( m_tagesdatum, "09", cErrmld );
			}
		}
		
		// Änderungen des Langnamens in zpznpflege schreiben (seit 31.05.11 für alle Länder, vorher nur BG & HR)
		if (lStatus == 0)
		{
			if ( m_lStatus_Zartikel == 100 )
			{
				char leer[ L_ZARTIKEL_ARTIKEL_LANGNAME + 1 ];
				memset( leer, ' ', L_ZARTIKEL_ARTIKEL_LANGNAME );
				
				if ( memcmp( m_Buf.zartikel.ARTIKEL_LANGNAME, leer, L_ZARTIKEL_ARTIKEL_LANGNAME ) != 0 )
					lStatus = StoreRecord_Zpznpflege( m_tagesdatum, "33", cErrmld );
			}
			else // m_lStatus_Zartikel == 0
			{
				if ( strcmp ( m_BufOld.zartikel.ARTIKEL_LANGNAME , m_Buf.zartikel.ARTIKEL_LANGNAME ) != 0 )
					lStatus = StoreRecord_Zpznpflege( m_tagesdatum, "33", cErrmld );
			}
		}
		
		// Änderungen der Gefahrstoffsymbole in zpznpflege schreiben für Update DKGFG (nicht bei Neuanlage), nur in Deutschland
		if (IsCountry("D"))
		{
			if (lStatus == 0)
			{
				if ( m_lStatus_Zartikel == 0 )
				{
					if ( strcmp ( m_BufOld.zartikel.GS_AETZEND,		m_Buf.zartikel.GS_AETZEND )		!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_BRAND,		m_Buf.zartikel.GS_BRAND )		!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_EXPLOSION,	m_Buf.zartikel.GS_EXPLOSION )	!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_GESUNDHSCH,	m_Buf.zartikel.GS_GESUNDHSCH )	!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_GIFTIG,		m_Buf.zartikel.GS_GIFTIG )		!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_HOCHENTZ,		m_Buf.zartikel.GS_HOCHENTZ )	!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_LEICHTENTZ,	m_Buf.zartikel.GS_LEICHTENTZ )	!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_REIZEND,		m_Buf.zartikel.GS_REIZEND )		!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_SEHRGIFTIG,	m_Buf.zartikel.GS_SEHRGIFTIG )	!= 0 ||
						strcmp ( m_BufOld.zartikel.GS_UMWELT,		m_Buf.zartikel.GS_UMWELT )		!= 0 ||
						strcmp ( m_BufOld.zartikel.GG_KLASSE,		m_Buf.zartikel.GG_KLASSE )		!= 0 ||
						strcmp ( m_BufOld.zartikel.GG_ZIFFER,		m_Buf.zartikel.GG_ZIFFER )		!= 0 ||
						strcmp ( m_BufOld.zartikel.GG_BUCHSTABE,	m_Buf.zartikel.GG_BUCHSTABE )	!= 0 ||
						strcmp ( m_BufOld.zartikel.G_UN_NR,			m_Buf.zartikel.G_UN_NR )		!= 0 ||
						strcmp ( m_BufOld.zartikel.G_WASSER,		m_Buf.zartikel.G_WASSER )		!= 0 ||
						strcmp ( m_BufOld.zartikel.G_VBF,			m_Buf.zartikel.G_VBF )			!= 0 ||
						strcmp ( m_BufOld.zartikel.G_VCI,			m_Buf.zartikel.G_VCI )			!= 0 )
						lStatus = StoreRecord_Zpznpflege( m_tagesdatum, "10", cErrmld );
				}
			}
		}
		
		if (lStatus == 0)
		{
			// Update auf artnrbl, falls Artikelnr. des Herstellers geändert
			// if ( m_lStatus_Zartikel == 0 )
			{
				// Änderung von zartikel.HERSTELLER_NR oder zartikel.ARTIKEL_NR_HERST
				if ( strcmp ( m_BufOld.zartikel.ARTIKEL_NR_HERST, m_Buf.zartikel.ARTIKEL_NR_HERST ) != 0 ||
					 m_BufOld.zartikel.HERSTELLER_NR != m_Buf.zartikel.HERSTELLER_NR ||
					 m_BufOld.zartikel.AWL1			 != m_Buf.zartikel.AWL1)
					lStatus = StoreRecord_Artnrbl( cErrmld );
			}
		}

		if ( lStatus == 0 )
			cErrmld = _T("");
	}
	return lStatus;
}

long CArtikelDoc::DeleteRecord_Zartikel( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	SetPrimekeyCondition( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartikel, &m_BufOld.zartikel, 
									 m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


/////////////////////////////////////////////////////////////////////////
// EAN

int CArtikelDoc::InitRecord_Ean( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
    nr = m_Buf.ean.ARTIKEL_NR;
    FdInitTabBuf( m_Fd_Ean, &m_Buf.ean );
    m_Buf.ean.ARTIKEL_NR = nr;
	return 0;
}

void CArtikelDoc::RestoreBuffer_Ean()
{
    m_BufSave.ean.ARTIKEL_NR = m_Buf.ean.ARTIKEL_NR;
    m_Buf.ean = m_BufSave.ean;
    m_Buf.ean.ARTIKEL_NR = m_BufSave.ean.ARTIKEL_NR;
}

int CArtikelDoc::GetBufferDesc_Ean( CString &cErrmld )
{
	char *tabelle = "ean";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Ean >= 0 ) return 0;

//	FillCmpIndikator_Ean ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Ean, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Ean = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Ean( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.ean.ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition ( );
    lStatus = ::FdReadRecord( m_Fd_Ean, m_PrimekeyCond, 
				  			  &m_Buf.ean, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.ean = m_Buf.ean;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Ean( cErrmld ) == 0 )
		{
//			m_BufOld.ean = m_Buf.ean;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;
	m_lStatus_Ean = lStatus;
	return lStatus;
}

int CArtikelDoc::IsRecordModified_Ean( CString &cErrmld )
{
	char errmld[100];
	int s;
	s = 0;

	s = ::FdIsRecordModified( m_Fd_Ean, &m_Buf.ean, &m_BufOld.ean, errmld );

	if ( s == 0 ) return 0;
	cErrmld = errmld;
	return s;
}

bool CArtikelDoc::IsToDelete_Ean( )
{	
	char leer[L_EAN_EAN_NR + 1];
	memset( leer, ' ', L_EAN_EAN_NR );
	return  memcmp( m_Buf.ean.EAN_NR, leer, L_EAN_EAN_NR  ) == 0;
}

long CArtikelDoc::StoreRecord_Ean( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	if (!IsRecordModified_Ean(cErrmld))
	{
		return 0;
	}

	/* in StoreRecordWithoutTransact verschoben
	// wenn neue EAN eingegeben, prüfen, ob diese nicht schon für eine andere PZN vergeben ist
	if ( !IsToDelete_Ean() )
	{
		if (lStatus = DoesEanAlreadyExist(cErrmld) != 0)
		{
			return lStatus;
		}
	} */

	SetPrimekeyCondition ( );
	if ( m_lStatus_Ean == 100 )
	{
		if ( !IsToDelete_Ean() )
			lStatus = ::FdDelayInsertRecord( m_Fd_Ean, &m_Buf.ean, 
											 m_PrimekeyCond, errmld);
	}
	else if ( m_lStatus_Ean == 0 )
	{
		if ( IsToDelete_Ean() )
			lStatus = ::FdDelayDeleteRecord( m_Fd_Ean, &m_BufOld.ean, 
											 m_PrimekeyCond, errmld );
		else
			lStatus = ::FdDelayUpdateRecord( m_Fd_Ean, &m_Buf.ean,
								 			 &m_BufOld.ean,
											 m_PrimekeyCond, errmld );
	}
	else
	{
		lStatus = m_lStatus_Ean;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


long CArtikelDoc::DeleteRecord_Ean( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Ean == 100 ) return 0;
	SetPrimekeyCondition ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Ean, &m_BufOld.ean, 
									 m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

int CArtikelDoc::DoesEanAlreadyExist( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	int iPzn;
	char code [L_CARTICLECODES_ARTICLE_CODE + 1];
	CString sql;

	sql.Format("select artikel_nr, article_code from EAN, carticlecodes where artikel_nr = articleno and preferred_flag = 1 and code_type in "
				"(select code_type from ccodetypes where artnr_substitute = 1) and EAN_NR='%s'", m_Buf.ean.EAN_NR);

    lStatus = ::SqlRead( sql, &iPzn, code, NULL);
	if ( lStatus == 100 ) return 0;
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		return lStatus;
	}

	cErrmld.Format(CResString::ex().getStrTblText(IDS_EAN_EXIST), m_Buf.ean.EAN_NR, code);
	return 1;
}

/////////////////////////////////////////////////////////////////////////
// ARTVE

int CArtikelDoc::InitRecord_Artve( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
	nr = m_Buf.artve.ARTIKEL_NR;
	FdInitTabBuf( m_Fd_Artve, &m_Buf.artve );
    m_Buf.artve.ARTIKEL_NR = nr;
	return 0;
}

void CArtikelDoc::RestoreBuffer_Artve()
{
    m_BufSave.artve.ARTIKEL_NR = m_Buf.artve.ARTIKEL_NR;
    m_Buf.artve = m_BufSave.artve;
    m_Buf.artve.ARTIKEL_NR = m_BufSave.artve.ARTIKEL_NR;
}

int CArtikelDoc::GetBufferDesc_Artve( CString &cErrmld )
{
	char *tabelle = "artve";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Artve >= 0 ) 
		return 0;

//	FillCmpIndikator_Artve ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Artve, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Artve = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Artve( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.artve.ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition ( );
    lStatus = ::FdReadRecord( m_Fd_Artve, m_PrimekeyCond, 
				  			  &m_Buf.artve, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.ean = m_Buf.ean;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Artve( cErrmld ) == 0 )
		{
//			m_BufOld.ean = m_Buf.ean;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Artve = lStatus;
	return lStatus;
}

int CArtikelDoc::IsRecordModified_Artve( CString &cErrmld )
{
	char errmld[100];
	int s;
	s = 0;

	s = ::FdIsRecordModified( m_Fd_Artve, &m_Buf.artve, &m_BufOld.artve, errmld );

	if ( s == 0 ) return 0;
	cErrmld = errmld;
	return s;
}

long CArtikelDoc::StoreRecord_Artve( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	if (!IsRecordModified_Artve(cErrmld))
	{
		return 0;
	}

	SetPrimekeyCondition ( );
	if ( m_lStatus_Artve == 100 )
	{
//		if ( !IsToDelete_Artve() )
			lStatus = ::FdDelayInsertRecord( m_Fd_Artve, &m_Buf.artve, 
											 m_PrimekeyCond, errmld);
	}
	else if ( m_lStatus_Artve == 0 )
	{
		/* nur Neuanlagen (beim Kopieren eines Artikels)
		if ( IsToDelete_Artve() )
			lStatus = ::FdDelayDeleteRecord( m_Fd_Artve, &m_BufOld.artve, 
											 m_PrimekeyCond, errmld );
		else
			lStatus = ::FdDelayUpdateRecord( m_Fd_Artve, &m_Buf.artve,
								 			 &m_BufOld.artve,
											 m_PrimekeyCond, errmld ); */
	}
	else
	{
		lStatus = m_lStatus_Artve;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

/* long CArtikelDoc::DeleteRecord_Artve( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Artve == 100 ) return 0;
	SetPrimekeyCondition ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Artve, &m_BufOld.ean, 
									 m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
} */

/////////////////////////////////////////////////////////////////////////
// CIBT (only in Germany)

int CArtikelDoc::InitRecord_Cibt(CString &cErrmld)
{
	if (cErrmld.GetLength()) {}
	long nr;
	nr = m_Buf.zartikel.ARTIKEL_NR;
	FdInitTabBuf(m_Fd_Cibt, &m_Buf.cibt);
	m_Buf.cibt.ARTICLENO = nr;
	return 0;
}

void CArtikelDoc::RestoreBuffer_Cibt()
{
	m_BufSave.cibt.ARTICLENO = m_Buf.cibt.ARTICLENO;
	m_Buf.cibt = m_BufSave.cibt;
	m_Buf.cibt.ARTICLENO = m_BufSave.cibt.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Cibt(CString &cErrmld)
{
	char *tabelle = "cibt";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if (m_Fd_Cibt >= 0)
		return 0;

	//	FillCmpIndikator_Cibt ( );
	lStatus = ::OpenBufferDesc(&m_Fd_Cibt, tabelle,
		NULL, NULL, V_PROTOKOL, errmld);
	if (lStatus != 0)
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Cibt = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Cibt(CString &cErrmld)
{
	long lStatus;
	char errmld[200];

	m_Buf.cibt.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_Cibt();
	lStatus = ::FdReadRecord( m_Fd_Cibt, m_PrimekeyCond_Cibt,
		                      &m_Buf.cibt, errmld);
	if (lStatus == 0)
	{
		cErrmld = _T("");
	}
	else if (lStatus == 100)
	{
		if (InitRecord_Cibt(cErrmld) != 0)
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Cibt = lStatus;
	return lStatus;
}

int CArtikelDoc::IsRecordModified_Cibt(CString &cErrmld)
{
	char errmld[100];
	int s;
	s = 0;

	s = ::FdIsRecordModified(m_Fd_Cibt, &m_Buf.cibt, &m_BufOld.cibt, errmld);

	if (s == 0) return 0;
	cErrmld = errmld;
	return s;
}

long CArtikelDoc::StoreRecord_Cibt(CString &cErrmld)
{
	long lStatus = 0;
	char errmld[200];

	if (!IsRecordModified_Cibt(cErrmld))
	{
		return 0;
	}

	SetPrimekeyCondition_Cibt();
	if (m_lStatus_Cibt == 100)
	{
		//		if ( !IsToDelete_Cibt() )
		lStatus = ::FdDelayInsertRecord( m_Fd_Cibt, &m_Buf.cibt,
										 m_PrimekeyCond_Cibt, errmld );
	}
	else if (m_lStatus_Cibt == 0)
	{
		/* nur Neuanlagen (beim Kopieren eines Artikels)
		if ( IsToDelete_Cibt() )
		lStatus = ::FdDelayDeleteRecord( m_Fd_Cibt, &m_BufOld.cibt,
		m_PrimekeyCond_Cibt, errmld );
		else
		lStatus = ::FdDelayUpdateRecord( m_Fd_Cibt, &m_Buf.cibt,
		&m_BufOld.cibt,
		m_PrimekeyCond_Cibt, errmld ); */

		lStatus = ::FdDelayUpdateRecord( m_Fd_Cibt, &m_Buf.cibt, &m_BufOld.cibt,
										 m_PrimekeyCond_Cibt, errmld );
	}
	else
	{
		lStatus = m_lStatus_Cibt;
		strcpy(errmld, CResString::ex().getStrTblText(IDS_INTER_ERR));
	}

	if (lStatus != 0) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


void CArtikelDoc::SetPrimekeyCondition_Cibt()
{
	char format[50];
	sprintf(format, "ARTICLENO=%c%d.ld", '%', L_ARTIKEL_NR);
	sprintf(m_PrimekeyCond_Cibt, format,
		    m_Buf.cibt.ARTICLENO);
}

/////////////////////////////////////////////////////////////////////////
// CARTFOREIGNCURR

int CArtikelDoc::InitRecord_Cartforeigncurr( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
	nr = m_Buf.cartforeigncurr.ARTICLENO;
    FdInitTabBuf( m_Fd_Cartforeigncurr, &m_Buf.cartforeigncurr );
    m_Buf.cartforeigncurr.ARTICLENO = nr;
	return 0;
}

void CArtikelDoc::RestoreBuffer_Cartforeigncurr()
{
    m_BufSave.cartforeigncurr.ARTICLENO = m_Buf.cartforeigncurr.ARTICLENO;
    m_Buf.cartforeigncurr = m_BufSave.cartforeigncurr;
    m_Buf.cartforeigncurr.ARTICLENO = m_BufSave.cartforeigncurr.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Cartforeigncurr( CString &cErrmld )
{
	char *tabelle = "cartforeigncurr";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Cartforeigncurr >= 0 ) return 0;

//	FillCmpIndikator_Cartforeigncurr ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Cartforeigncurr, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Cartforeigncurr = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Cartforeigncurr( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.cartforeigncurr.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_Cartforeigncurr ( );
	lStatus = ::FdReadRecord( m_Fd_Cartforeigncurr, m_PrimekeyCond_Cartforeigncurr, 
				  			  &m_Buf.cartforeigncurr, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.cartforeigncurr = m_Buf.cartforeigncurr;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Cartforeigncurr( cErrmld ) == 0 )
		{
//			m_BufOld.cartforeigncurr = m_Buf.cartforeigncurr;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Cartforeigncurr = lStatus;
	return lStatus;
}

int CArtikelDoc::IsRecordModified_Cartforeigncurr( CString &cErrmld )
{
	char errmld[100];
	int s;
	s = 0;

	s = ::FdIsRecordModified( m_Fd_Cartforeigncurr, &m_Buf.cartforeigncurr, &m_BufOld.cartforeigncurr, errmld );

	if ( s == 0 ) 
		return 0;
	
	cErrmld = errmld;
	return s;
}

bool CArtikelDoc::IsToDelete_Cartforeigncurr( )
{	
	char leer[L_CARTFOREIGNCURR_CURRENCYCODE + 1];
	memset( leer, ' ', L_CARTFOREIGNCURR_CURRENCYCODE );
	return  memcmp( m_Buf.cartforeigncurr.CURRENCYCODE, leer, L_CARTFOREIGNCURR_CURRENCYCODE  ) == 0;
}

long CArtikelDoc::StoreRecord_Cartforeigncurr( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	if (!IsRecordModified_Cartforeigncurr(cErrmld))
	{
		return 0;
	}

	SetPrimekeyCondition_Cartforeigncurr ( );
	if ( m_lStatus_Cartforeigncurr == 100 )
	{
		if ( !IsToDelete_Cartforeigncurr() )
		{
			// bei Neuanlage Umrechnungsfaktor mit aktuellem Wert initialisieren
			m_Buf.cartforeigncurr.EXCHANGE_RATE = ReadUmrechnungsfaktor_Cexchangeratio();
			m_Buf.cartforeigncurr.DATE_EXCHANGE_CALC = Today();

			if (m_Buf.cartforeigncurr.EXCHANGE_RATE <= 0.0)
			{
				lStatus = -1;
				strcpy( errmld, CResString::ex().getStrTblText(IDS_STRING1134) );
			}
			else
                lStatus = ::FdDelayInsertRecord( m_Fd_Cartforeigncurr, &m_Buf.cartforeigncurr, 
												m_PrimekeyCond_Cartforeigncurr, errmld);
		}
	}
	else if ( m_lStatus_Cartforeigncurr == 0 )
	{
		if ( IsToDelete_Cartforeigncurr() )
			lStatus = ::FdDelayDeleteRecord( m_Fd_Cartforeigncurr, &m_BufOld.cartforeigncurr, 
											 m_PrimekeyCond_Cartforeigncurr, errmld );
		else
			lStatus = ::FdDelayUpdateRecord( m_Fd_Cartforeigncurr, &m_Buf.cartforeigncurr,
								 			 &m_BufOld.cartforeigncurr,
											 m_PrimekeyCond_Cartforeigncurr, errmld );
	}
	else
	{
		lStatus = m_lStatus_Cartforeigncurr;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}


long CArtikelDoc::DeleteRecord_Cartforeigncurr( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Cartforeigncurr == 100 ) 
		return 0;

	SetPrimekeyCondition_Cartforeigncurr ( );

	lStatus = ::FdDelayDeleteRecord( m_Fd_Cartforeigncurr, &m_BufOld.cartforeigncurr, 
									 m_PrimekeyCond_Cartforeigncurr, errmld );

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_Cartforeigncurr( )
{
	char format[50];
	sprintf( format, "ARTICLENO=%c%d.ld", 
		             '%', L_ARTIKEL_NR);
	sprintf( m_PrimekeyCond_Cartforeigncurr, format, 
			m_Buf.cartforeigncurr.ARTICLENO );
}

/////////////////////////////////////////////////////////////////////////
// CSAFETYDATASHEET

int CArtikelDoc::InitRecord_CSafetyDataSheet( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
	nr = m_Buf.csafetydatasheet.ARTICLENO;
    FdInitTabBuf( m_Fd_CSafetyDataSheet, &m_Buf.csafetydatasheet );
    m_Buf.csafetydatasheet.ARTICLENO = nr;
	return 0;
}

void CArtikelDoc::RestoreBuffer_CSafetyDataSheet()
{
    m_BufSave.csafetydatasheet.ARTICLENO = m_Buf.csafetydatasheet.ARTICLENO;
    m_Buf.csafetydatasheet = m_BufSave.csafetydatasheet;
    m_Buf.csafetydatasheet.ARTICLENO = m_BufSave.csafetydatasheet.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_CSafetyDataSheet( CString &cErrmld )
{
	char *tabelle = "csafetydatasheet";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_CSafetyDataSheet >= 0 ) 
		return 0;

//	FillCmpIndikator_Cartforeigncurr ( );
	lStatus = ::OpenBufferDesc( &m_Fd_CSafetyDataSheet, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_CSafetyDataSheet = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_CSafetyDataSheet( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.csafetydatasheet.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_CSafetyDataSheet ( );
	lStatus = ::FdReadRecord( m_Fd_CSafetyDataSheet, m_PrimekeyCond_CSafetyDataSheet, 
				  			  &m_Buf.csafetydatasheet, errmld );
	
	if ( lStatus == 0 )
	{
//		m_BufOld.csafetydatasheet = m_Buf.csafetydatasheet;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_CSafetyDataSheet( cErrmld ) == 0 )
		{
//			m_BufOld.csafetydatasheet = m_Buf.csafetydatasheet;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_CSafetyDataSheet = lStatus;
	return lStatus;
}

int CArtikelDoc::IsRecordModified_CSafetyDataSheet( CString &cErrmld )
{
	char errmld[100];
	int s;
	s = 0;

	s = ::FdIsRecordModified( m_Fd_CSafetyDataSheet, &m_Buf.csafetydatasheet, &m_BufOld.csafetydatasheet, errmld );

	if ( s == 0 ) 
		return 0;
	
	cErrmld = errmld;
	return s;
}

bool CArtikelDoc::AreGhsArticleDataModified( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}

	// add all relevant zartikel-fields from ArtikelPage4 here:
	return	strcmp(m_Buf.zartikel.G_UN_NR, m_BufOld.zartikel.G_UN_NR) != 0							||
			strcmp(m_Buf.zartikel.G_TECH_NAME, m_BufOld.zartikel.G_TECH_NAME) != 0					||
			strcmp(m_Buf.zartikel.SIDABLATT, m_BufOld.zartikel.SIDABLATT) != 0						||
			strcmp(m_Buf.zartikel.G_WASSER, m_BufOld.zartikel.G_WASSER) != 0						||
			strcmp(m_Buf.zartikel.G_VCI, m_BufOld.zartikel.G_VCI) != 0								||
			strcmp(m_Buf.zartikel.GG_KLASSE, m_BufOld.zartikel.GG_KLASSE) != 0						||
			strcmp(m_Buf.zartikel.GS_HOCHENTZ, m_BufOld.zartikel.GS_HOCHENTZ) != 0					||
			strcmp(m_Buf.zartikel.GS_LEICHTENTZ, m_BufOld.zartikel.GS_LEICHTENTZ) != 0				||
			strcmp(m_Buf.zartikel.GS_EXPLOSION, m_BufOld.zartikel.GS_EXPLOSION) != 0				||
			strcmp(m_Buf.zartikel.GS_BRAND, m_BufOld.zartikel.GS_BRAND) != 0						||
			strcmp(m_Buf.zartikel.GS_AETZEND, m_BufOld.zartikel.GS_AETZEND) != 0					||
			strcmp(m_Buf.zartikel.GS_SEHRGIFTIG, m_BufOld.zartikel.GS_SEHRGIFTIG) != 0				||
			strcmp(m_Buf.zartikel.GS_GIFTIG, m_BufOld.zartikel.GS_GIFTIG) != 0						||
			strcmp(m_Buf.zartikel.GS_GESUNDHSCH, m_BufOld.zartikel.GS_GESUNDHSCH) != 0				||
			strcmp(m_Buf.zartikel.GS_REIZEND, m_BufOld.zartikel.GS_REIZEND) != 0					||
			strcmp(m_Buf.zartikel.GS_UMWELT, m_BufOld.zartikel.GS_UMWELT) != 0						||
			strcmp(m_Buf.zartikel.VERPACKUNGSGRUPPE, m_BufOld.zartikel.VERPACKUNGSGRUPPE) != 0			;
}

long CArtikelDoc::StoreRecord_CSafetyDataSheet( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	if (!IsRecordModified_CSafetyDataSheet(cErrmld) && !AreGhsArticleDataModified(cErrmld))
	{
		// keine Änderung von csafetydatasheet + keine Änderung von GHS-relevanten zartikel- Feldern
		return 0;
	}

	SetPrimekeyCondition_CSafetyDataSheet ( );

	// --- Änderungsdatum nicht setzen, wenn nur Prüfdatum geändert wurde
	m_Buf.csafetydatasheet.DATE_CHECKED = m_BufOld.csafetydatasheet.DATE_CHECKED;

	if (IsRecordModified_CSafetyDataSheet(cErrmld) || AreGhsArticleDataModified(cErrmld))
		m_Buf.csafetydatasheet.DATE_CHANGED = Today();

	m_Buf.csafetydatasheet.DATE_CHECKED = Today(); // Prüfdatum immer setzen, wenn tatsächlich eine Änderung erfolgt ist

	if ( m_lStatus_CSafetyDataSheet == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_CSafetyDataSheet, &m_Buf.csafetydatasheet, 
												m_PrimekeyCond_CSafetyDataSheet, errmld);
	}
	else if ( m_lStatus_CSafetyDataSheet == 0 )
	{
		lStatus = ::FdDelayUpdateRecord( m_Fd_CSafetyDataSheet, &m_Buf.csafetydatasheet,
								 			 &m_BufOld.csafetydatasheet,
											 m_PrimekeyCond_CSafetyDataSheet, errmld );
	}
	else
	{
		lStatus = m_lStatus_CSafetyDataSheet;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}


long CArtikelDoc::DeleteRecord_CSafetyDataSheet( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_CSafetyDataSheet == 100 ) 
		return 0;

	SetPrimekeyCondition_CSafetyDataSheet ( );

	lStatus = ::FdDelayDeleteRecord( m_Fd_CSafetyDataSheet, &m_BufOld.csafetydatasheet, 
									 m_PrimekeyCond_CSafetyDataSheet, errmld );

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_CSafetyDataSheet( )
{
	char format[50];
	sprintf( format, "ARTICLENO=%c%d.ld", 
		             '%', L_ARTIKEL_NR);
	sprintf( m_PrimekeyCond_CSafetyDataSheet, format, 
			m_Buf.csafetydatasheet.ARTICLENO );
}

/////////////////////////////////////////////////////////////////////////
// ZARTFEB2

int CArtikelDoc::InitRecord_Zartfeb2( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}

	long nr;
    nr = m_Buf.zartfeb2.ARTIKEL_NR;
    FdInitTabBuf( m_Fd_Zartfeb2, &m_Buf.zartfeb2 );
    m_Buf.zartfeb2.ARTIKEL_NR = nr;
	return 0;
}

void CArtikelDoc::RestoreBuffer_Zartfeb2()
{
    m_BufSave.zartfeb2.ARTIKEL_NR = m_Buf.zartfeb2.ARTIKEL_NR;
    m_Buf.zartfeb2 = m_BufSave.zartfeb2;
    m_Buf.zartfeb2.ARTIKEL_NR = m_BufSave.zartfeb2.ARTIKEL_NR;
}

int CArtikelDoc::GetBufferDesc_Zartfeb2( CString &cErrmld )
{
	char *tabelle = "zartfeb2";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartfeb2 >= 0 ) return 0;

//	FillCmpIndikator_Zartfeb2 ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartfeb2, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartfeb2 = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Zartfeb2( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.zartfeb2.ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition ( );
    lStatus = ::FdReadRecord( m_Fd_Zartfeb2, m_PrimekeyCond, 
				  			  &m_Buf.zartfeb2, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartfeb2 = m_Buf.zartfeb2;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartfeb2( cErrmld ) == 0 )
		{
//			m_BufOld.zartfeb2 = m_Buf.zartfeb2;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;
	m_lStatus_Zartfeb2 = lStatus;
	return lStatus;
}

bool CArtikelDoc::IsToDelete_Zartfeb2( )
{	
	return m_Buf.zartfeb2.FESTBETRAG2 == 0;
}

long CArtikelDoc::StoreRecord_Zartfeb2( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition ( );
	if ( m_lStatus_Zartfeb2 == 100 )
	{
		if ( !IsToDelete_Zartfeb2() )
			lStatus = ::FdDelayInsertRecord( m_Fd_Zartfeb2, &m_Buf.zartfeb2, 
											 m_PrimekeyCond, errmld);
	}
	else if ( m_lStatus_Zartfeb2 == 0 )
	{
		if ( IsToDelete_Zartfeb2() )
			lStatus = ::FdDelayDeleteRecord( m_Fd_Zartfeb2, &m_BufOld.zartfeb2, 
											 m_PrimekeyCond, errmld );
		else
			lStatus = ::FdDelayUpdateRecord( m_Fd_Zartfeb2, &m_Buf.zartfeb2,
								 			 &m_BufOld.zartfeb2,
											 m_PrimekeyCond, errmld );
	}
	else
	{
		lStatus = m_lStatus_Zartfeb2;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


long CArtikelDoc::DeleteRecord_Zartfeb2( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Zartfeb2 == 100 ) return 0;
	SetPrimekeyCondition ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartfeb2, &m_BufOld.zartfeb2, 
									 m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// ZARTPREIS

int CArtikelDoc::InitRecord_Artpreis( int i, CString &cErrmld )
{
	if (cErrmld.GetLength()) {}

	FdInitTabBuf( m_Fd_Artpreis, &m_Buf.artpreis[i] );

	m_Buf.artpreis[i].ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;

	m_Buf.artpreis[i].PREIS_TYP = m_Buf.sPreistyp;

	// Spezielle Initialisierung ( Peetz 2.6.98 )
	m_Buf.artpreis[i].KE_MWST[0] = '0';   // volle MWST

	// Spezielle Initialisierung für Frankreich mit Mwst-KZ 1
	if (IsCountry("F"))
		m_Buf.artpreis[i].KE_MWST[0] = '1';  

	return 0;
}

void CArtikelDoc::SetPrimekeyCondition_Artpreis( int i )
{
	char format[80];

	sprintf( format, "ARTIKEL_NR=%c%d.ld and PREIS_TYP=%cd and DATUMGUELTIGAB=%cld", 
		             '%', L_ARTIKEL_NR, '%', '%' );

	sprintf( m_PrimekeyCond_Artpreis, 
			 format, 
			 m_Buf.artpreis[i].ARTIKEL_NR,
			 m_Buf.sPreistyp,
			 m_Buf.artpreis[i].DATUMGUELTIGAB );
}

void CArtikelDoc::SetPrimekeyCondition_OldArtpreis( int i )
{
	char format[80];

	sprintf( format, "ARTIKEL_NR=%c%d.ld and PREIS_TYP=%cd and DATUMGUELTIGAB=%cld", 
		             '%', L_ARTIKEL_NR, '%', '%' );

	sprintf( m_PrimekeyCond_Artpreis, 
			 format, 
			 m_BufOld.artpreis[i].ARTIKEL_NR,
			 m_BufOld.sPreistyp,
			 m_BufOld.artpreis[i].DATUMGUELTIGAB );
}

void CArtikelDoc::RestoreBuffer_Artpreis( int i)
{
    m_BufSave.artpreis[i].ARTIKEL_NR		= m_Buf.artpreis[i].ARTIKEL_NR;
	m_BufSave.sPreistyp						= m_Buf.sPreistyp;
    m_BufSave.artpreis[i].DATUMGUELTIGAB	= m_Buf.artpreis[i].DATUMGUELTIGAB;

	m_Buf.artpreis[i] = m_BufSave.artpreis[i];

	m_Buf.artpreis[i].ARTIKEL_NR			= m_BufSave.artpreis[i].ARTIKEL_NR;
	m_Buf.sPreistyp							= m_BufSave.sPreistyp;
	m_Buf.artpreis[i].DATUMGUELTIGAB		= m_BufSave.artpreis[i].DATUMGUELTIGAB;
}

int CArtikelDoc::GetBufferDesc_Artpreis( CString &cErrmld )
{
	char *tabelle = "zartpreis";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Artpreis >= 0 ) return 0;

//	FillCmpIndikator_Artpreis ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Artpreis, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );
				
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Artpreis = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Artpreis( CString &cErrmld )
{
	long lStatus;
//	char errmld[200];
	int fd;
	int i;
	CString sql;

	lStatus = 100;
	cErrmld = _T("");
	i = 0;

	// Preis-Saetze initialisieren
	while ( i < NUMBER_OF_PRICE && lStatus == 100 )
	{
		if ( InitRecord_Artpreis( i, cErrmld ) == 0 )
			m_BufOld.artpreis[i] = m_Buf.artpreis[i];	
		else
			lStatus = -1;

		m_lStatus_Artpreis[i] = lStatus;
		i++;
	}
	if ( lStatus == -1 ) return lStatus;

	// Preis 0 mit Herst_prozent fuellen 07.10.98
	m_Buf.artpreis[0].HERST_PROZENT = m_Buf.zartikel.HERST_PROZENT;

	// Preis-Saetze lesen
	sprintf( m_PrimekeyCond_Artpreis, 
			 "ARTIKEL_NR=%ld and PREIS_TYP=%d",
			 m_Buf.zartikel.ARTIKEL_NR,
			 m_Buf.sPreistyp);

	// RR 12/07/05: "Select *" ersetzt
	sql.Format("select %s from ZARTPREIS where %s order by ARTIKEL_NR, DATUMGUELTIGAB desc",
				PROJECTION_ZARTPREIS, m_PrimekeyCond_Artpreis);

	lStatus = ::SqlOpenCs( &fd, sql );
	if ( lStatus != 0 ) 
	{
		cErrmld = DynErrmld();
		return lStatus;
	}

	i = 1;    // ab 1 !!!!!!
	while ( i < NUMBER_OF_PRICE && lStatus == 0 )
	{
		lStatus = SqlFetch( fd, 1, &m_Buf.artpreis[i], NULL );
		if ( lStatus == 0 )
		{
			// Preis 0  mit Werten aus Preis 1 initialisieren
			if ( i == 1 )
			{
				strcpy ( m_Buf.artpreis[0].KE_MWST, m_Buf.artpreis[i].KE_MWST ); 
				m_Buf.artpreis[0].DISC_DEDUCED_YET = m_Buf.artpreis[i].DISC_DEDUCED_YET;
			}

			m_lStatus_Artpreis[i] = lStatus;
			m_BufOld.artpreis[i] = m_Buf.artpreis[i];
			i++;
		}
	}

	cErrmld = DynErrmld();
	SqlCloseCs( fd );

	return lStatus;
}

int CArtikelDoc::IsSingleRecordModified_Artpreis( int i, char *errmld )
{
	return ::FdIsRecordModified( m_Fd_Artpreis, &m_Buf.artpreis[i],
		   						 				&m_BufOld.artpreis[i], errmld );
}

int CArtikelDoc::IsRecordModified_Artpreis( CString &cErrmld )
{
	char errmld[100];
	int s;
	int i;
	s = 0;
	i = 0;
	while ( s == 0 && i < NUMBER_OF_PRICE )
	{
		s = ::FdIsRecordModified( m_Fd_Artpreis, &m_Buf.artpreis[i],
										 	     &m_BufOld.artpreis[i], errmld );
		if ( s == 1 ) return 1;
		i++;
	}

	if ( s == 0 ) return 0;
	cErrmld = errmld;
	return s;
}

// eigenes Loeschen organisieren
bool CArtikelDoc::IsToDelete_Artpreis( int i )
{
	return  m_Buf.artpreis[i].DATUMGUELTIGAB == 0;
}

long CArtikelDoc::StoreRecord_Artpreis( int i, CString &cErrmld, long *datum )
{
	long lStatus;
	char errmld[200];
	
	*datum = 0;

	lStatus = 0;

	if ( m_lStatus_Artpreis[i] == 100 )
	{
		SetPrimekeyCondition_Artpreis ( i );
		if ( !IsToDelete_Artpreis( i ) )
		{
			*datum = m_Buf.artpreis[i].DATUMGUELTIGAB;
			lStatus = ::FdDelayInsertRecord( m_Fd_Artpreis, &m_Buf.artpreis[i], 
											 m_PrimekeyCond_Artpreis, errmld);
		}
	}
	else if ( m_lStatus_Artpreis[i] == 0 )
	{
		if ( IsToDelete_Artpreis( i ) )
		{
			SetPrimekeyCondition_OldArtpreis ( i );
			lStatus = ::FdDelayDeleteRecord( m_Fd_Artpreis, &m_BufOld.artpreis[i], 
											 m_PrimekeyCond_Artpreis, errmld );
		}
		else
		{
			if ( m_Buf.artpreis[i].DATUMGUELTIGAB == m_BufOld.artpreis[i].DATUMGUELTIGAB )
			{
				bool bModified;
				SetPrimekeyCondition_Artpreis ( i );
				bModified = IsSingleRecordModified_Artpreis( i, errmld ) == 1;
				if ( bModified )
					*datum = m_Buf.artpreis[i].DATUMGUELTIGAB;
				lStatus = ::FdDelayUpdateRecord( m_Fd_Artpreis, &m_Buf.artpreis[i],
												 &m_BufOld.artpreis[i],
												 m_PrimekeyCond_Artpreis, errmld );
			}
			else
			{
				SetPrimekeyCondition_OldArtpreis ( i );
				lStatus = ::FdDelayDeleteRecord( m_Fd_Artpreis, &m_BufOld.artpreis[i], 
												 m_PrimekeyCond_Artpreis, errmld );

				SetPrimekeyCondition_Artpreis ( i );
				*datum = m_Buf.artpreis[i].DATUMGUELTIGAB;
				lStatus = ::FdDelayInsertRecord( m_Fd_Artpreis, &m_Buf.artpreis[i], 
												 m_PrimekeyCond_Artpreis, errmld);
			}
		}
	}
	else
	{
		lStatus = m_lStatus_Artpreis[i];
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_Artpreis( int i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Artpreis[i] == 100 ) 
		return 0;

	SetPrimekeyCondition_Artpreis ( i );

	lStatus = ::FdDelayDeleteRecord( m_Fd_Artpreis, &m_BufOld.artpreis[i], 
									 m_PrimekeyCond_Artpreis, errmld );

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// ZARTWG

int CArtikelDoc::InitRecord_Zartwg( int i, CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	strcpy( m_Buf.zartwg[i].WARENGRUPPE, "     " );
	return 0;
}

void CArtikelDoc::SetPrimekeyCondition_Zartwg( int i)
{
	char format[50];
	sprintf( format, "ARTIKEL_NR=%c%d.ld and ART='%cs'", 
		             '%', L_ARTIKEL_NR, '%' );
	sprintf( m_PrimekeyCond_Zartwg, format, 
			 m_Buf.zartwg[i].ARTIKEL_NR,
			 m_Buf.zartwg[i].ART );
}

void CArtikelDoc::RestoreBuffer_Zartwg( int i)
{
    m_BufSave.zartwg[i].ARTIKEL_NR = m_Buf.zartwg[i].ARTIKEL_NR;
    strcpy( m_BufSave.zartwg[i].ART, m_Buf.zartwg[i].ART );
    m_Buf.zartwg[i] = m_BufSave.zartwg[i];
    strcpy( m_Buf.zartwg[i].ART, m_BufSave.zartwg[i].ART );
	m_Buf.zartwg[i].ARTIKEL_NR = m_BufSave.zartwg[i].ARTIKEL_NR;
}

int CArtikelDoc::GetBufferDesc_Zartwg( CString &cErrmld )
{
	char *tabelle = "zartwg";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartwg >= 0 ) return 0;

//	FillCmpIndikator_Zartwg ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartwg, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartwg = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Zartwg( int i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.zartwg[i].ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;

	// Unterscheidung wg. alphanumerischen Arten
	if (i < 9)
		m_Buf.zartwg[i].ART[0] = static_cast<char>(i + '0' + 1);	// '0' = 48 (ASCII-Code)
	else
		m_Buf.zartwg[i].ART[0] = static_cast<char>(i + 56);		// i = 9 ---> ART = 'A' (ASCII-Code 65)

	m_Buf.zartwg[i].ART[1] = '\0';

	SetPrimekeyCondition_Zartwg ( i );
    lStatus = ::FdReadRecord( m_Fd_Zartwg, m_PrimekeyCond_Zartwg, 
							  &m_Buf.zartwg[i], errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld = m_Buf;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartwg( i, cErrmld ) == 0 )
		{
//			m_BufOld = m_Buf;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;
	m_lStatus_Zartwg[i] = lStatus;
	return lStatus;
}

bool CArtikelDoc::IsToDelete_Zartwg( int i )
{
	char *str;
	str = m_Buf.zartwg[i].WARENGRUPPE;
	while ( *str && (*str == ' ' || *str == '0') ) str++;
	return *str == '\0'; 
}

long CArtikelDoc::StoreRecord_Zartwg( int i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	lStatus = 0;
	SetPrimekeyCondition_Zartwg ( i );
	if ( m_lStatus_Zartwg[i] == 100 )
	{
		if ( !IsToDelete_Zartwg( i ) )
			lStatus = ::FdDelayInsertRecord( m_Fd_Zartwg, &m_Buf.zartwg[i], 
											 m_PrimekeyCond_Zartwg, errmld);
	}
	else if ( m_lStatus_Zartwg[i] == 0 )
	{
		if ( IsToDelete_Zartwg( i ) )
			lStatus = ::FdDelayDeleteRecord( m_Fd_Zartwg, &m_BufOld.zartwg[i], 
											 m_PrimekeyCond_Zartwg, errmld );
		else
			lStatus = ::FdDelayUpdateRecord( m_Fd_Zartwg, &m_Buf.zartwg[i],
											 &m_BufOld.zartwg[i],
											 m_PrimekeyCond_Zartwg, errmld );
	}
	else
	{
		lStatus = m_lStatus_Zartwg[i];
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


long CArtikelDoc::DeleteRecord_Zartwg( int i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Zartwg[i] == 100 ) return 0;
	SetPrimekeyCondition_Zartwg ( i );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartwg, &m_BufOld.zartwg[i], 
									 m_PrimekeyCond_Zartwg, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// chazardnote2article

int CArtikelDoc::InitRecord_chazardnote2article( int i, CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	strcpy( m_Buf.chazardnotes[i].HAZARDNOTEID, "     " );
	m_Buf.chazardnotes[i].ARTICLENO = 0;
	return 0;
}

void CArtikelDoc::SetPrimekeyCondition_chazardnote2article( )
{
	char format[100];
	sprintf( format, "ARTICLENO=%c%d.ld and HAZARDNOTEID='%cs'", 
		             '%', L_ARTIKEL_NR, '%');
	sprintf( m_PrimekeyCond_HazardNote, format, 
				m_Buf.zartikel.ARTIKEL_NR, m_Buf.chazardnotes[0].HAZARDNOTEID );
}

int CArtikelDoc::GetBufferDesc_chazardnote2article( CString &cErrmld )
{
	char *tabelle = "chazardnote2article";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_HazardNote >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_HazardNote, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_HazardNote = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_chazardnote2article( CString &cErrmld )
{
	long lStatus;
	int fd;
	int i;
	CString sql;

	lStatus = 100;
	cErrmld = _T("");
	i = 0;

	// Saetze initialisieren
	while ( i < NUMBER_OF_HAZARDNOTES && lStatus == 100 )
	{
		if ( InitRecord_chazardnote2article( i, cErrmld ) == 0 )
			m_BufOld.chazardnotes[i] = m_Buf.chazardnotes[i];	
		else
			lStatus = -1;

		m_lStatus_HazardNote[i] = lStatus;
		i++;
	}

	if ( lStatus == -1 ) 
		return lStatus;

	// Preis-Saetze lesen
	sprintf( m_PrimekeyCond_HazardNote, 
			 "ARTICLENO=%ld",
			 m_Buf.zartikel.ARTIKEL_NR);

	sql.Format("select %s from CHAZARDNOTE2ARTICLE where %s order by HAZARDNOTEID",
				PROJECTION_CHAZARDNOTE2ARTICLE, m_PrimekeyCond_HazardNote);

	lStatus = ::SqlOpenCs( &fd, sql );
	if ( lStatus != 0 ) 
	{
		cErrmld = DynErrmld();
		return lStatus;
	}

	i = 0;
	while ( i < NUMBER_OF_HAZARDNOTES && lStatus == 0 )
	{
		lStatus = SqlFetch( fd, 1, &m_Buf.chazardnotes[i], NULL );
		if ( lStatus == 0 )
		{
			m_lStatus_HazardNote[i] = lStatus;
			m_BufOld.chazardnotes[i] = m_Buf.chazardnotes[i];
			i++;
		}
	}

	cErrmld = DynErrmld();
	SqlCloseCs( fd );

	return lStatus;
}

void CArtikelDoc::SetHazardNoteIdToProcess	( char * hazardNoteId )
{
	m_Buf.chazardnotes[0].ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	strcpy(m_Buf.chazardnotes[0].HAZARDNOTEID, hazardNoteId);
}

long CArtikelDoc::StoreRecord_chazardnote2article( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	lStatus = 0;
	SetPrimekeyCondition_chazardnote2article ( );
	
	// no updates!
	lStatus = ::FdInsertRecord( m_Fd_HazardNote, &m_Buf.chazardnotes[0], 
											 m_PrimekeyCond_HazardNote, errmld);
	
	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_chazardnote2article( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	
	SetPrimekeyCondition_chazardnote2article ( );

	lStatus = ::FdDeleteRecord( m_Fd_HazardNote, &m_Buf.chazardnotes[0], 
									 m_PrimekeyCond_HazardNote, errmld );
	
	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else
		cErrmld = _T("");

	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// clppr2article

int CArtikelDoc::InitRecord_clppr2article( int i, CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	strcpy( m_Buf.clpprcodes[i].CODE_LPPR, "               " );
	m_Buf.clpprcodes[i].ARTICLENO = 0;
	m_Buf.clpprcodes[i].DATEFROM = 0;
	m_Buf.clpprcodes[i].REIMBCALCFLAG = 0;
	return 0;
}

void CArtikelDoc::SetPrimekeyCondition_clppr2article( int i )
{
	char format[100];
	sprintf( format, "ARTICLENO=%c%d.ld and CODE_LPPR='%cs'", 
		             '%', L_ARTIKEL_NR, '%');
	sprintf( m_PrimekeyCond_Lppr2Article, format, 
				m_Buf.zartikel.ARTIKEL_NR, m_Buf.clpprcodes[i].CODE_LPPR );
}

int CArtikelDoc::GetBufferDesc_clppr2article( CString &cErrmld )
{
	char *tabelle = "clppr2article";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Lppr2Article >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Lppr2Article, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Lppr2Article = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_clppr2article( CString &cErrmld )
{
	long lStatus;
	int fd;
	int i;
	CString sql;

	lStatus = 100;
	cErrmld = _T("");
	i = 0;

	// Saetze initialisieren
	while ( i < NUMBER_OF_LPPRS && lStatus == 100 )
	{
		if ( InitRecord_clppr2article( i, cErrmld ) == 0 )
			m_BufOld.clpprcodes[i] = m_Buf.clpprcodes[i];	
		else
			lStatus = -1;

		m_lStatus_Lppr2Article[i] = lStatus;
		i++;
	}

	if ( lStatus == -1 ) 
		return lStatus;

	// Preis-Saetze lesen
	sprintf( m_PrimekeyCond_Lppr2Article, 
			 "ARTICLENO=%ld",
			 m_Buf.zartikel.ARTIKEL_NR);

	sql.Format("select %s from CLPPR2ARTICLE where %s order by CODE_LPPR",
				PROJECTION_CLPPR2ARTICLE, m_PrimekeyCond_Lppr2Article);

	lStatus = ::SqlOpenCs( &fd, sql );
	if ( lStatus != 0 ) 
	{
		cErrmld = DynErrmld();
		return lStatus;
	}

	i = 0;
	while ( i < NUMBER_OF_LPPRS && lStatus == 0 )
	{
		lStatus = SqlFetch( fd, 1, &m_Buf.clpprcodes[i], NULL );
		if ( lStatus == 0 )
		{
			m_lStatus_Lppr2Article[i] = lStatus;
			m_BufOld.clpprcodes[i] = m_Buf.clpprcodes[i];
			i++;
		}
	}

	cErrmld = DynErrmld();
	SqlCloseCs( fd );

	return lStatus;
}

long CArtikelDoc::StoreRecord_clppr2article( int i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	lStatus = 0;
	SetPrimekeyCondition_clppr2article ( i );
	
	if ( m_lStatus_Lppr2Article[i] == 100 )
	{
		m_Buf.clpprcodes[i].ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;

		lStatus = ::FdInsertRecord( m_Fd_Lppr2Article, &m_Buf.clpprcodes[i], 
											 m_PrimekeyCond_Lppr2Article, errmld);
	}
	else if ( m_lStatus_Lppr2Article[i] == 0 )
	{
		lStatus = ::FdUpdateRecord( m_Fd_Lppr2Article, &m_Buf.clpprcodes[i],
							 			 &m_BufOld.clpprcodes[i],
										 m_PrimekeyCond_Lppr2Article, errmld );
	}
	else
	{
		lStatus = m_lStatus_Lppr2Article[i];
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	
	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_clppr2article( int i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	
	SetPrimekeyCondition_clppr2article ( i );

	lStatus = ::FdDeleteRecord( m_Fd_Lppr2Article, &m_Buf.clpprcodes[i], 
									 m_PrimekeyCond_Lppr2Article, errmld );
	
	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else
		cErrmld = _T("");

	return lStatus;
}

double CArtikelDoc::Read_LpprReimbValueSum	 ( long datefrom )
{
	long lStatus;
	double dReimbValue;
	CString sql;

	sql.Format( "select sum(reimbursement_val) from clppr2article a, outer clpprreimb r where articleno = %ld "
				" and a.code_lppr = r.code_lppr and reimbcalcflag = 1 "
				" and a.datefrom <= %ld "
				" and  r.datefrom  = (select max(datefrom) from clpprreimb where code_lppr = a.code_lppr and datefrom <= %ld)", m_Buf.zartikel.ARTIKEL_NR, datefrom, datefrom);
			
	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = SqlRead(sql, &dReimbValue, NULL);
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
 
	if ( lStatus != 0 )
	{	
		dReimbValue = -1;
	}	

	return dReimbValue;
}

/////////////////////////////////////////////////////////////////////////
// CARTICLECODES

int CArtikelDoc::InitRecord_Carticlecodes( int i, CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	strcpy( m_Buf.carticlecodes[i].ARTICLE_CODE, "                         " );
	m_Buf.carticlecodes[i].PREFERRED_FLAG = 0;
	m_Buf.carticlecodes[i].SERIAL_NUMBER = 0;

	return 0;
}

void CArtikelDoc::SetPrimekeyCondition_Carticlecodes( int i)
{
	char format[100];
	short serial = 0;

	if (m_Buf.carticlecodes[i].CODE_TYPE == 22 || m_Buf.carticlecodes[i].CODE_TYPE == 26)
		serial = 1;

	// serial_number vorerst immer 0, wird voraussichtlich später mal benötigt (z.B. Mehrfach-EAN)
	sprintf( format, "ARTICLENO=%c%d.ld and CODE_TYPE=%%d and SERIAL_NUMBER=%%d", 
		             '%', L_ARTIKEL_NR );
	sprintf( m_PrimekeyCond_Carticlecodes, format, 
			 m_Buf.carticlecodes[i].ARTICLENO,
			 m_Buf.carticlecodes[i].CODE_TYPE,
			 serial);
}

void CArtikelDoc::RestoreBuffer_Carticlecodes( int i)
{
    // es dürfen nur codes mit artnr_substitute!=1 kopiert werden!
	if (true == CheckCodetypeMayBeCopied(m_Buf.carticlecodes[i].CODE_TYPE))
	{
		m_BufSave.carticlecodes[i].ARTICLENO = m_Buf.carticlecodes[i].ARTICLENO;
		m_BufSave.carticlecodes[i].CODE_TYPE = m_Buf.carticlecodes[i].CODE_TYPE;
		m_Buf.carticlecodes[i] = m_BufSave.carticlecodes[i];
		m_Buf.carticlecodes[i].CODE_TYPE = m_BufSave.carticlecodes[i].CODE_TYPE;
		m_Buf.carticlecodes[i].ARTICLENO = m_BufSave.carticlecodes[i].ARTICLENO;
	}
}

int CArtikelDoc::GetBufferDesc_Carticlecodes( CString &cErrmld )
{
	char *tabelle = "carticlecodes";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Carticlecodes >= 0 ) 
		return 0;

//	FillCmpIndikator_Carticlecodese ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Carticlecodes, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );

	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Carticlecodes = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_Carticlecodes( short i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.carticlecodes[i].ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	m_Buf.carticlecodes[i].CODE_TYPE = i + 1;
	//m_Buf.carticlecodes[i].SERIAL_NUMBER = 0;

	SetPrimekeyCondition_Carticlecodes ( i );
    lStatus = ::FdReadRecord( m_Fd_Carticlecodes, m_PrimekeyCond_Carticlecodes, 
							  &m_Buf.carticlecodes[i], errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld = m_Buf;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Carticlecodes( i, cErrmld ) == 0 )
		{
//			m_BufOld = m_Buf;	// initialisierten Satz sichern
		}
		else
		{
			lStatus = -1;
	}
	}
	else
	{
		cErrmld = errmld;
	}

	m_lStatus_Carticlecodes[i] = lStatus;
	return lStatus;
}

bool CArtikelDoc::IsToDelete_Carticlecodes( int i )
{
//	return  strcmp( m_Buf.carticlecodes[i].WARENGRUPPE, "     " ) == 0;

	char *str;
	str = m_Buf.carticlecodes[i].ARTICLE_CODE;

	while ( *str && *str == ' ' ) 
		str++;

	return *str == '\0'; 
}

long CArtikelDoc::StoreRecord_Carticlecodes( int i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	int s;

	lStatus = 0;
	SetPrimekeyCondition_Carticlecodes ( i );

	if ( m_lStatus_Carticlecodes[i] == 100 )
	{
		if ( !IsToDelete_Carticlecodes( i ) )
		{
			m_Buf.carticlecodes[i].DATE_CHANGED = m_tagesdatum;

			if (m_Buf.carticlecodes[i].CODE_TYPE == 22 || m_Buf.carticlecodes[i].CODE_TYPE == 26)
			    m_Buf.carticlecodes[i].SERIAL_NUMBER = 1;

			lStatus = ::FdDelayInsertRecord( m_Fd_Carticlecodes, &m_Buf.carticlecodes[i], 
											 m_PrimekeyCond_Carticlecodes, errmld);
			m_bCarticlecodes_changed = TRUE;
		}
	}
	else if ( m_lStatus_Carticlecodes[i] == 0 )
	{
		if ( IsToDelete_Carticlecodes( i ) )
		{
			lStatus = ::FdDelayDeleteRecord( m_Fd_Carticlecodes, &m_BufOld.carticlecodes[i], 
											 m_PrimekeyCond_Carticlecodes, errmld );
			m_bCarticlecodes_changed = TRUE;
		}
		else
		{
			// Update nur, wenn tatsächlich Änderung (weil sonst auch immer zpznpflege-Ausgabe)
			s = ::FdIsRecordModified( m_Fd_Carticlecodes, &m_Buf.carticlecodes[i], 
				&m_BufOld.carticlecodes[i], errmld );

			if ( s == 1 ) 
			{
				m_Buf.carticlecodes[i].DATE_CHANGED = m_tagesdatum;

				lStatus = ::FdDelayUpdateRecord( m_Fd_Carticlecodes, &m_Buf.carticlecodes[i],
												 &m_BufOld.carticlecodes[i], m_PrimekeyCond_Carticlecodes, errmld );

				m_bCarticlecodes_changed = TRUE;
			}
		}
	}
	else
	{
		lStatus = m_lStatus_Carticlecodes[i];
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_Carticlecodes( int i, CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Carticlecodes[i] == 100 ) 
		return 0;

	SetPrimekeyCondition_Carticlecodes ( i );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Carticlecodes, &m_BufOld.carticlecodes[i], 
									 m_PrimekeyCond_Carticlecodes, errmld );

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
	{
		cErrmld = _T("");
	}

	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// ZAPFLEGE

int CArtikelDoc::GetBufferDesc_Zapflege( CString &cErrmld )
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

int CArtikelDoc::GetBufferDesc_CTransferCsc( CString &cErrmld )
{
	char *tabelle = "ctransfercsc";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_CTransferCsc >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_CTransferCsc, tabelle,
                                NULL, NULL, V_OHNE, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_CTransferCsc = -1;
		return -1;
	}
	return 0;
}


/*----------------------------------------------------------------------------*/
int CArtikelDoc::GetBufferDesc_Zpznpflege( CString &cErrmld )
{
	char *tabelle = "zpznpflege";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_Zpznpflege >= 0 ) 
		return 0;

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

long CArtikelDoc::StoreRecord_Zapflege( long datum, CString &cErrmld )
{
	long lStatus;

	char PrimekeyCond_Zapflege[100];
	char errmld[200];

	m_ZapflegeBuf.ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
	m_ZapflegeBuf.DATUM		 = datum;

	sprintf( PrimekeyCond_Zapflege, "ARTIKEL_NR=%ld and DATUM=%ld",
									m_ZapflegeBuf.ARTIKEL_NR, 
									m_ZapflegeBuf.DATUM       );

    lStatus = ::FdReadRecord( m_Fd_Zapflege, PrimekeyCond_Zapflege,
				  			  &m_ZapflegeBuf, errmld );

	if ( lStatus == 100 )
	{
		m_ZapflegeBuf.ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
		m_ZapflegeBuf.DATUM		 = datum;

/* zapflege immer sofort schreiben, weil es sonst zum Abbruch kommen kann, wenn die Funktion mehrmals mit dem gleichen Datum aufgerufen wird
		lStatus = ::FdDelayInsertRecord( m_Fd_Zapflege, &m_ZapflegeBuf,  */
		lStatus = ::FdInsertRecord( m_Fd_Zapflege, &m_ZapflegeBuf, 
									PrimekeyCond_Zapflege, errmld );
	}

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::StoreRecord_CTransferCsc( CString &cErrmld )
{
	long lStatus;

	char errmld[200];
	char PrimekeyCond_CTransferCsc[50];

	if ( GetBufferDesc_CTransferCsc		( cErrmld ) != 0 ) 
		return -1;

	strcpy(m_CTransferCscBuf.ENTRYDATETIME, "current");
	m_CTransferCscBuf.TRANSFERID = 0; // serial
	m_CTransferCscBuf.PROCESSEDFLAG = 0;
	
	sprintf( PrimekeyCond_CTransferCsc, "TRANSFERID=%ld",
									m_CTransferCscBuf.TRANSFERID);

    lStatus = ::FdDelayInsertRecord( m_Fd_CTransferCsc, &m_CTransferCscBuf, 
										PrimekeyCond_CTransferCsc, errmld );
	
	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::StoreRecord_Zpznpflege( long datum, CString dezap_sa, CString &cErrmld )
{
	long lStatus;

	char PrimekeyCond_Zpznpflege[100];
	char errmld[200];

	m_ZpznpflegeBuf.ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
	m_ZpznpflegeBuf.DATUM      = datum;
	strcpy (m_ZpznpflegeBuf.DEZAP_SA, dezap_sa);
	
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

int CArtikelDoc::GetBufferDesc_Zaneuheit( CString &cErrmld )
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

long CArtikelDoc::StoreRecord_Zaneuheit( char programm, CString &cErrmld )
{
	long lStatus;

	char prog[2]; 
	char PrimekeyCond_Zaneuheit[100];
	char errmld[200];
   
	prog[0] = programm;
	prog[1] = '\0';
	strcpy( m_ZaneuheitBuf.PFLEGEPROGRAMM, prog );
	m_ZaneuheitBuf.ARTIKEL_NR  = m_Buf.zartikel.ARTIKEL_NR;

	sprintf( PrimekeyCond_Zaneuheit, "PFLEGEPROGRAMM='%s' and ARTIKEL_NR=%ld",
	 							     m_ZaneuheitBuf.PFLEGEPROGRAMM, 
									 m_ZaneuheitBuf.ARTIKEL_NR       );

    lStatus = ::FdReadRecord( m_Fd_Zaneuheit, PrimekeyCond_Zaneuheit,
				  			  &m_ZaneuheitBuf, errmld );

	if ( lStatus == 100 )
	{
		strcpy( m_ZaneuheitBuf.PFLEGEPROGRAMM, prog );
		m_ZaneuheitBuf.ARTIKEL_NR  = m_Buf.zartikel.ARTIKEL_NR;
		strcpy( m_ZaneuheitBuf.ARTIKEL_MC, m_Buf.zartikel.ARTIKEL_MC );

		if ( *prog == NH_HERSTELLER_WECHSEL )
			m_ZaneuheitBuf.HERSTELLER_NR = m_BufOld.zartikel.HERSTELLER_NR;
		else
			m_ZaneuheitBuf.HERSTELLER_NR = m_Buf.zartikel.HERSTELLER_NR;

		m_ZaneuheitBuf.DATUM = m_tagesdatum;
		lStatus = ::FdDelayInsertRecord( m_Fd_Zaneuheit, &m_ZaneuheitBuf, 
										 PrimekeyCond_Zaneuheit, errmld );
	}

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

long CArtikelDoc::DeleteRecord_Zaneuheit( char programm, CString &cErrmld )
{
	long lStatus;
	char prog[2];
	char errmld[200];
	char PrimekeyCond_Zaneuheit[100];

	prog[0] = programm;
	prog[1] = '\0';

	strcpy( m_ZaneuheitBuf.PFLEGEPROGRAMM, prog );
	m_ZaneuheitBuf.ARTIKEL_NR  = m_Buf.zartikel.ARTIKEL_NR;

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

int CArtikelDoc::IsRecordModified( CString &cErrmld )
{
	char errmld[100];
	int s;

	// Artikel-Mc generieren  auch hier !!!!!!!! pruefen
	if (IsCountry("BG")) 
		strcpy( m_Buf.zartikel.ARTIKEL_MC, MakeArtikelMc( m_Buf.zartikel.ARTIKEL_LANGNAME ) );
	else
		strcpy( m_Buf.zartikel.ARTIKEL_MC, MakeArtikelMc( m_Buf.zartikel.ARTIKEL_NAME ) );

	s = ::FdIsRecordModified( m_Fd_Zartikel, &m_Buf.zartikel,
											 &m_BufOld.zartikel, errmld );
	if ( s == 1 ) return 1;

	if ( s == 0 )
	{
		s = ::FdIsRecordModified( m_Fd_Ean, &m_Buf.ean, 
										    &m_BufOld.ean, errmld );
		if ( s == 1 ) return 1;
	}

	if ( s == 0 )
	{
		s = ::FdIsRecordModified( m_Fd_Cartforeigncurr, &m_Buf.cartforeigncurr, 
								&m_BufOld.cartforeigncurr, errmld );
		if ( s == 1 ) return 1;
	}

	if ( s == 0 )
	{
		s = ::FdIsRecordModified( m_Fd_CSafetyDataSheet, &m_Buf.csafetydatasheet, 
								&m_BufOld.csafetydatasheet, errmld );
		if ( s == 1 ) return 1;
	}

	if ( s == 0 )
	{
		s = ::FdIsRecordModified( m_Fd_Zartfeb2, &m_Buf.zartfeb2, 
											     &m_BufOld.zartfeb2, errmld );
		if ( s == 1 ) return 1;
	}

// carticleext
	if ( s == 0 )
	{
		s = ::FdIsRecordModified( m_Fd_Carticleext, &m_Buf.carticleext, 
			&m_BufOld.carticleext, errmld );
		if ( s == 1 ) return 1;
	}

// cibt nur in Deutschland
	if (IsCountry("D"))
	{
		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Cibt, &m_Buf.cibt, 
				&m_BufOld.cibt, errmld );
			if ( s == 1 ) return 1;
		}
	}
	
// zartaustria nur in Österreich
	if (IsCountry("A"))
	{
		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Zartaustria, &m_Buf.zartaustria, 
				&m_BufOld.zartaustria, errmld );
			if ( s == 1 ) return 1;
		}
	}

// zartswitzerland nur in der Schweiz
	if (IsCountry("CH"))
	{
		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Zartswitzerland, &m_Buf.zartswitzerland, 
				&m_BufOld.zartswitzerland, errmld );
			if ( s == 1 ) return 1;
		}
	}

// zartfrance & cartrefundfrance nur in Frankreich
	if (IsCountry("F"))
	{
		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Zartfrance, &m_Buf.zartfrance, 
				&m_BufOld.zartfrance, errmld );
			if ( s == 1 ) 
				return 1;
		}

		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Cartrefundfrance, &m_Buf.cartrefundfrance, 
				&m_BufOld.cartrefundfrance, errmld );
			if ( s == 1 ) 
				return 1;
		}
	}

// zartcroatia nur in Kroatien
	if (IsCountry("HR"))
	{
		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Zartcroatia, &m_Buf.zartcroatia, 
				&m_BufOld.zartcroatia, errmld );
			if ( s == 1 ) return 1;
		}
	}

// zartbulgaria nur in Bulgarien
	if (IsCountry("BG"))
	{
		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Zartbulgaria, &m_Buf.zartbulgaria, 
				&m_BufOld.zartbulgaria, errmld );
			if ( s == 1 ) return 1;
		}

		if (s == 0)
		{
			s = ::FdIsRecordModified(m_Fd_CRegisters, &m_Buf.cregisters,
				&m_BufOld.cregisters, errmld);
			if (s == 1) return 1;
		}

		if (s == 0)
		{
			s = ::FdIsRecordModified(m_Fd_CRegistersPrices, &m_Buf.cregistersprices,
				&m_BufOld.cregistersprices, errmld);
			if (s == 1) return 1;
		}

		if (s == 0)
		{
			s = ::FdIsRecordModified(m_Fd_CNhifPrices, &m_Buf.cnhifprices,
				&m_BufOld.cnhifprices, errmld);
			if (s == 1) return 1;
		}
	}

// zartserbia nur in Serbien
	if (IsCountry("RS"))
	{
		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Zartserbia, &m_Buf.zartserbia, 
				&m_BufOld.zartserbia, errmld );
			if ( s == 1 ) return 1;
		}
	}

// carticlelang nur in der Schweiz und Bulgarien
	if (IsCountry("CH") || IsCountry("BG"))
	{
		if ( s == 0 )
		{
			s = ::FdIsRecordModified( m_Fd_Carticlelang, &m_Buf.carticlelang, 
				&m_BufOld.carticlelang, errmld );
			if ( s == 1 ) return 1;
		}
	}

	int i = 0;
	while ( s == 0 && i < NUMBER_OF_WGR )
	{
		s = ::FdIsRecordModified( m_Fd_Zartwg, &m_Buf.zartwg[i],
											   &m_BufOld.zartwg[i], errmld ); // "00000" <-> "     " ==> modified
		if ( s == 1 ) return 1;
		i++;
	}

	i = 0;
	while ( s == 0 && i < NUMBER_OF_CODES )
	{
		s = ::FdIsRecordModified( m_Fd_Carticlecodes, &m_Buf.carticlecodes[i],
					    		  &m_BufOld.carticlecodes[i], errmld );
		if ( s == 1 ) return 1;
		i++;
	}
	
	if ( s == 0 )
	{
		s = IsRecordModified_Sekbez( ); 
		if ( s == 1 ) return 1;
	}

	if ( s == 0 ) return 0;
	cErrmld = errmld;
	return s;
}

void CArtikelDoc::RestoreBuffer()
{
	if (m_BufSave.zartikel.ARTIKEL_NR <= 0)
		return; // don´t paste, if nothing was copied before - otherwise it could happen, that m_BufSave which was not initialized via InitRecord... is set to m_Buf !!!
	
	RestoreBuffer_Zartikel();
	RestoreBuffer_Ean();
	RestoreBuffer_Artve();
	RestoreBuffer_Cibt();
	RestoreBuffer_Cartforeigncurr();
	RestoreBuffer_CSafetyDataSheet();
	RestoreBuffer_Zartfeb2();
	RestoreBuffer_Zartaustria();
	RestoreBuffer_Zartswitzerland();
	RestoreBuffer_Carticlelang();
	RestoreBuffer_Zartcroatia();
	RestoreBuffer_Zartbulgaria();
	RestoreBuffer_Zartserbia();
	RestoreBuffer_CArtMedActor();

	int i;
	for ( i = 0; i < NUMBER_OF_WGR; i++ )
		RestoreBuffer_Zartwg( i );

	for ( i = 0; i < NUMBER_OF_CODES; i++ )
		RestoreBuffer_Carticlecodes( i );
}

int CArtikelDoc::GetBufferDesc( CString &cErrmld )
{
   if ( GetBufferDesc_Zartikel			( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_Ean				( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_Artve				( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_Cartforeigncurr	( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_CSafetyDataSheet	( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_Zartfeb2			( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_Zartwg			( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_Carticlecodes		( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_Artpreis			( cErrmld ) != 0 ) return -1;
   if ( GetBufferDesc_chazardnote2article(cErrmld ) != 0 ) return -1;
   
  // wegmachen :: nur bei Bedarf !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if ( GetBufferDesc_Sekbez( cErrmld ) != 0 ) return -1;
// kein FreeBufferDesc !!!!!!!!!!!!!!

	if ( GetBufferDesc_Zapflege			( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_CTransferCsc		( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_Zpznpflege		( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_Zaneuheit		( cErrmld ) != 0 ) return -1;
	if ( GetBufferDesc_Carticleext		( cErrmld ) != 0 ) return -1;

// cibt only in Germany
	if (IsCountry("D"))
	{
		if ( GetBufferDesc_Cibt ( cErrmld ) != 0 ) return -1;
	}

// zartaustria nur in Österreich
	if (IsCountry("A"))
	{
		if ( GetBufferDesc_Zartaustria ( cErrmld ) != 0 ) return -1;
	}

// zartswitzerland nur in der Schweiz
	if (IsCountry("CH"))
	{
		if ( GetBufferDesc_Zartswitzerland ( cErrmld ) != 0 ) return -1;
	}

// zartfrance & cartrefundfrance nur in Frankreich
	if (IsCountry("F"))
	{
		if ( GetBufferDesc_Zartfrance		( cErrmld ) != 0 ) return -1;
		if ( GetBufferDesc_Cartrefundfrance ( cErrmld ) != 0 ) return -1;
		if ( GetBufferDesc_clppr2article	(cErrmld  ) != 0 ) return -1;
	}

// zartcroatia nur in Kroatien
	if (IsCountry("HR"))
	{
		if ( GetBufferDesc_Zartcroatia ( cErrmld ) != 0 ) return -1;
	}

// zartbulgaria nur in Bulgarien
	if (IsCountry("BG"))
	{
		if ( GetBufferDesc_Zartbulgaria ( cErrmld ) != 0 ) return -1;
		if (GetBufferDesc_CRegisters(cErrmld) != 0) return -1;
		if (GetBufferDesc_CRegistersPrices(cErrmld) != 0) return -1;
		if (GetBufferDesc_CNhifPrices(cErrmld) != 0) return -1;
	}

// zartserbia nur in Serbien
	if (IsCountry("RS"))
	{
		if ( GetBufferDesc_Zartserbia ( cErrmld ) != 0 ) return -1;
	}

// carticlelang nur in der Schweiz und Bulgarien
	if (IsCountry("CH") || IsCountry("BG"))
	{
		if ( GetBufferDesc_Carticlelang ( cErrmld ) != 0 ) return -1;
	}

	if (GetBufferDesc_PrewholeArtCustomerGroups(cErrmld) != 0) return -1;

	if ((((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToOne) || 
		(((CEkZdpApp*)AfxGetApp())->GetMedActorParameter() == MedActor_Parameter::OneToN))
	{
		if (GetBufferDesc_CArtMedActor(cErrmld) != 0) return -1;
	}

   return 0;
}

int CArtikelDoc::InitRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

	InitRecord_Zartikel			( cErrmld );
	InitRecord_Ean				( cErrmld );
	InitRecord_Artve			( cErrmld );
	InitRecord_Cibt				( cErrmld );
	InitRecord_Cartforeigncurr	( cErrmld );
	InitRecord_CSafetyDataSheet	( cErrmld );
	InitRecord_Zartfeb2			( cErrmld );
	InitRecord_Zartaustria		( cErrmld );
	InitRecord_Zartswitzerland	( cErrmld );
	InitRecord_Carticlelang		( cErrmld );
	InitRecord_Zartfrance		( cErrmld );
	InitRecord_Zartcroatia		( cErrmld );
	InitRecord_Zartbulgaria		( cErrmld );
	InitRecord_Zartserbia		( cErrmld );
	InitRecord_CRegisters		( cErrmld );
	InitRecord_CArtMedActor		( cErrmld );
	int i;
	for ( i = 0; i < NUMBER_OF_WGR; i++ )
		InitRecord_Zartwg( i, cErrmld );

	for ( i = 0; i < NUMBER_OF_CODES; i++ )
		InitRecord_Carticlecodes( i, cErrmld );

	for ( i = 0; i < NUMBER_OF_PRICE; i++ )
		InitRecord_Artpreis( i, cErrmld );

	for ( i = 0; i < NUMBER_OF_HAZARDNOTES; i++ )
		InitRecord_chazardnote2article( i, cErrmld );

	for ( i = 0; i < NUMBER_OF_LPPRS; i++ )
		InitRecord_clppr2article( i, cErrmld );

	for ( i = 0; i < NUMBER_OF_PRICES_NHIF; i++ )
		InitRecord_CNhifPrices( i, cErrmld );

	for ( i = 0; i < NUMBER_OF_PRICES_REGISTERS; i++ )
		InitRecord_CRegistersPrices( i, cErrmld );

	return 0;
}

int CArtikelDoc::GetBufferDesc_Cdsoart( CString &cErrmld )
{
	char *tabelle = "cdsoart";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_Cdsoart >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Cdsoart, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );
									
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Cdsoart = -1;
		return -1;
	}
	return 0;
}

int CArtikelDoc::GetBufferDesc_Nummerek( CString &cErrmld )
{
	char *tabelle = "nummerek";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_Nummerek >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Nummerek, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );
									
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Nummerek = -1;
		return -1;
	}
	return 0;
}

int CArtikelDoc::GetBufferDesc_Clioart( CString &cErrmld )
{
	char *tabelle = "clioart";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_Clioart >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Clioart, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );
									
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Clioart = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadCDsOArt( CString &cErrmld )
{
	long lStatus;

	if ( GetBufferDesc_Cdsoart( cErrmld ) != 0 )
		return -1;

	char errmld[200];

	FdInitTabBuf( m_Fd_Cdsoart, &cdsoart );

	char PrimekeyCond[30];
	sprintf( PrimekeyCond, "ARTICLENO=%ld", m_Buf.zartikel.ARTIKEL_NR );
	
	lStatus = ::FdReadRecord( m_Fd_Cdsoart, PrimekeyCond,
							  &cdsoart, errmld );
	
	if ( lStatus == 0 || lStatus == 100 )
	{
		cErrmld = _T("");
	}
	else
		cErrmld = errmld;
	
	return lStatus;
}

long CArtikelDoc::ReadNummerek( CString &cErrmld )
{
	long lStatus;

	if ( GetBufferDesc_Nummerek( cErrmld ) != 0 )
		return -1;

	char errmld[200];

	FdInitTabBuf( m_Fd_Nummerek, &nummerek );

	char PrimekeyCond[50];
	sprintf( PrimekeyCond, "NR_ART='NEWPZN'" );
	
	lStatus = ::FdReadRecord( m_Fd_Nummerek, PrimekeyCond,
		&nummerek, errmld );
	
	if ( lStatus == 0 )
	{
		cErrmld = _T("");

		nummerek_old = nummerek;

		// prüfen, ob Artikel schon existiert, wenn ja ---> nummerek erhöhen
		CString sql;
		int		iPzn, pz;

		sql.Format( "select artikel_nr from zartikel where artikel_nr = %ld", nummerek.NR );
		lStatus = SqlRead(sql, &iPzn, NULL);

		if (lStatus == 0)
		{
			nummerek.NR = 10 * (((int) nummerek.NR / 10) + 1);			
			pz = GetPruefZiffer7( nummerek.NR );
			nummerek.NR += pz;
		}
		else if (lStatus == 100)
			lStatus = 0;
	}
	else if (lStatus == 100)
	{
		cErrmld = CResString::ex().getStrTblText(IDS_STRING10194);
	}
	else
	{
		cErrmld = errmld;
	}
	
	m_lStatus_Nummerek = lStatus;

	return lStatus;
}

long CArtikelDoc::ReadClioart  ( CString& cErrmld )
{
	long lStatus;

	if ( GetBufferDesc_Clioart( cErrmld ) != 0 )
		return -1;

	char errmld[200];

	FdInitTabBuf( m_Fd_Clioart, &clioart );

	char PrimekeyCond[30];
	sprintf( PrimekeyCond, "PHAR=%ld", m_Buf.zartikel.ARTIKEL_NR );
	
	lStatus = ::FdReadRecord( m_Fd_Clioart, PrimekeyCond,
							  &clioart, errmld );
	
	if ( lStatus == 0 || lStatus == 100 )
		cErrmld = _T("");
	else
		cErrmld = errmld;
	
	return lStatus;
}

long CArtikelDoc::ReadClioart( long articleNo, CString& cErrmld )
{
	long lStatus;
	char errmld[200];
	char PrimekeyCond[30];

	if ( GetBufferDesc_Clioart( cErrmld ) != 0 )
		return -1;

	sprintf(PrimekeyCond, "PHAR=%ld", articleNo);

	lStatus = ::FdReadRecord( m_Fd_Clioart, PrimekeyCond,
		                      &clioart, errmld );

	if (lStatus == 0)
		cErrmld = _T("");
	else
	{
		FdInitTabBuf( m_Fd_Clioart, &clioart );
		clioart.PHAR = articleNo;
		cErrmld = errmld;
	}

	return lStatus;
}

long CArtikelDoc::StoreNummerek( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( m_lStatus_Nummerek == 0 )
	{
		char PrimekeyCond[50];
		sprintf( PrimekeyCond, "NR_ART='NEWPZN'" );
	
		lStatus = ::FdDelayUpdateRecord( m_Fd_Nummerek, &nummerek, &nummerek_old, 
										 PrimekeyCond, errmld );
	}
	else if ( m_lStatus_Nummerek == 100 )
		lStatus = 0;
	else
	{
		lStatus = m_lStatus_Nummerek;
		sprintf( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR), lStatus );
	}	

	if ( lStatus != 0 )	cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

const bool CArtikelDoc::IsHealthInsuranceArticle( )
{
	long lStatus;
	double iCount;
	CString sql;

	sql.Format("select count(*) from chealthinsurancearticles where articleno=%ld", m_Buf.zartikel.ARTIKEL_NR);

    lStatus = ::SqlRead( sql, &iCount, NULL);

	if ( lStatus != 0 || iCount < 1.0)
		return false;
	else
		return true;
}

long CArtikelDoc::ReadRecord( CString &cErrmld )
{
	long lStatus;

	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

    lStatus = ReadRecord_Zartikel( cErrmld ); // Artikel immer zuerst lesen
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

	lStatus = ReadRecord_Ean( cErrmld );
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

	lStatus = ReadRecord_Artve( cErrmld );
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

	lStatus = ReadRecord_Cartforeigncurr( cErrmld );
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

	lStatus = ReadRecord_CSafetyDataSheet( cErrmld );
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

	lStatus = ReadRecord_Zartfeb2( cErrmld );
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

    lStatus = ReadRecord_Artpreis( cErrmld );	
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

	lStatus = ReadRecord_chazardnote2article( cErrmld );	
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

	lStatus = ReadRecord_Carticleext( cErrmld );	
	if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

// cibt only in Germany
	if (IsCountry("D"))
	{
		lStatus = ReadRecord_Cibt( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

// zartaustria nur in Österreich
	if (IsCountry("A"))
	{
		lStatus = ReadRecord_Zartaustria( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

// zartswitzerland nur in der Schweiz
	if (IsCountry("CH"))
	{
		lStatus = ReadRecord_Zartswitzerland( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

// zartfrance nur in Frankreich
	if (IsCountry("F"))
	{
		lStatus = ReadRecord_Zartfrance( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

		lStatus = ReadRecord_Cartrefundfrance( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

		lStatus = ReadRecord_clppr2article( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

// zartcroatia nur in Kroatien
	if (IsCountry("HR"))
	{
		lStatus = ReadRecord_Zartcroatia( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

// zartbulgaria nur in Bulgarien
	if (IsCountry("BG"))
	{
		lStatus = ReadRecord_Zartbulgaria( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

		lStatus = ReadRecord_Carticlecodes(22, cErrmld);
		if (!(lStatus == 0 || lStatus == 100)) return -1;

		lStatus = ReadRecord_Zartwg(16, cErrmld);
		if (!(lStatus == 0 || lStatus == 100)) return -1;

		lStatus = ReadRecord_CRegisters(cErrmld);
		if (!(lStatus == 0 || lStatus == 100)) return -1;


		lStatus = ReadRecord_CRegistersPrices(cErrmld);
		if (!(lStatus == 0 || lStatus == 100)) return -1;

		lStatus = ReadRecord_CNhifPrices(cErrmld);
		if (!(lStatus == 0 || lStatus == 100)) return -1;
	}

// zartserbia nur in Serbien
	if (IsCountry("RS"))
	{
		lStatus = ReadRecord_Zartserbia( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

// carticlelang nur in der Schweiz und Bulgarien
	if (IsCountry("CH") || IsCountry("BG"))
	{
		lStatus = ReadRecord_Carticlelang( cErrmld );	
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

	short i;
	for ( i = 0; i < NUMBER_OF_WGR; i++ )
	{
	    lStatus = ReadRecord_Zartwg( i, cErrmld );
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

	for ( i = 0; i < NUMBER_OF_CODES; i++ )
	{
		lStatus = ReadRecord_Carticlecodes( i, cErrmld );
		if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;
	}

	m_nNrOfSekbez = 0;		// Sekbez init
	m_nNewNrOfSekbez = 0;

	ReadPharmosSekbez(  );	// Sekbez zur Anzeige

	m_BufOld = m_Buf;  // gelesenen Satz sichern: erst hier

	return m_lStatus_Zartikel;   // !!!!!!!!!!!!!!!!!
}

// long CArtikelDoc::StoreRecord( CString &cErrmld )
long CArtikelDoc::StoreRecordWithoutTransact( CString &cErrmld, const CString code )
{
	if ( GetBufferDesc( cErrmld ) != 0 )  return -1;

	// hier BSsichG berechnen 18.12.2002
	// Bssichg wird nur bei Neuanlagen automatisch brechnet 23.01.2003
	// bssichg: 23.12.2003 entfaellt wieder, da neues Gesetz
/*
	if ( m_lStatus_Zartikel == 100 )
	{
		CBssichG *m_pBssichG;
		m_pBssichG = &((CEkZdpApp*) AfxGetApp())->m_BssichG;
		m_pBssichG->SetBSSichG( &m_Buf.zartikel, m_Buf.zartwg[0].WARENGRUPPE );
	}
*/
	// wenn Satz geaendert

	int iStatus_Artikel;
	int iStatus_Preis;

	if ( ( iStatus_Artikel = IsRecordModified( cErrmld ) ) == -1 ) return -1;
	if ( ( iStatus_Preis = IsRecordModified_Artpreis( cErrmld ) ) == -1 ) return -1;

	if ( iStatus_Artikel == 0 && iStatus_Preis == 0 ) return 0;	// neu: keine Aenderung

//	if ( iStatus_Artikel == 1 )   // ab 26.01.1999
	if ( iStatus_Artikel == 1 || iStatus_Preis == 1 ) 
	{
		strcpy( m_Buf.zartikel.BEARBEITER, m_Anwender );
		if ( m_lStatus_Zartikel == 0 )
			m_Buf.zartikel.DATUM_AENDER = m_tagesdatum;
		else
		{
			m_Buf.zartikel.DATUM_ANLAGE = m_tagesdatum;
			strcpy( m_Buf.zartikel.USER_ANLAGE, m_Anwender );
		}
	}

	// wenn neue EAN eingegeben, prüfen, ob diese nicht schon für eine andere PZN vergeben ist
	if (IsRecordModified_Ean(cErrmld))
	{
		if ( !IsToDelete_Ean() )
		{
			if (int lStatus = DoesEanAlreadyExist(cErrmld) != 0)
			{
				return -1;
			}
		}
	}

	m_Buf.zartserbia.CERTIFICATEFLAG = m_Buf.carticleext.CERTIFICATEFLAG; //TH remove as soon as GI also switched to carticleext !!!
	
    if ( StoreRecord_Zartikel( cErrmld ) != 0 ) return -1;
    if ( StoreRecord_Ean( cErrmld ) != 0 ) return -1;
    if ( StoreRecord_Artve( cErrmld ) != 0 ) return -1;
    if ( StoreRecord_Cartforeigncurr( cErrmld ) != 0 ) return -1;
	if ( StoreRecord_CSafetyDataSheet( cErrmld ) != 0 ) return -1;
	if ( StoreRecord_Zartfeb2( cErrmld ) != 0 ) return -1;
	if ( StoreRecord_Carticleext( cErrmld ) != 0 ) return -1;

// cibt only for Germany
	if (IsCountry("D"))
	{
		if ( StoreRecord_Cibt( cErrmld ) != 0 ) return -1;
	}

// zartaustria nur in Österreich
	if (IsCountry("A"))
	{
		if ( StoreRecord_Zartaustria( cErrmld ) != 0 ) return -1;
	}

// zartswitzerland nur in der Schweiz
	if (IsCountry("CH"))
	{
		if ( StoreRecord_Zartswitzerland( cErrmld ) != 0 ) return -1;
	}

// zartfrance & cartrefundfrance nur in Frankreich
	if (IsCountry("F"))
	{
		if ( StoreRecord_Zartfrance( cErrmld ) != 0 ) return -1;
		if ( StoreRecord_Cartrefundfrance( cErrmld ) != 0 ) return -1;
	}

// zartcroatia nur in Kroatien
	if (IsCountry("HR"))
	{
		if ( StoreRecord_Zartcroatia( cErrmld ) != 0 ) return -1;
	}

// zartbulgaria nur in Bulgarien
	if (IsCountry("BG"))
	{
		if ( StoreRecord_Zartbulgaria( cErrmld ) != 0 ) return -1;
	}

// zartserbia nur in Serbien
	if (IsCountry("RS"))
	{
		if ( StoreRecord_Zartserbia( cErrmld ) != 0 ) return -1;
	}

// carticlelang nur in der Schweiz und Bulgarien
	if (IsCountry("CH") || IsCountry("BG"))
	{
		if ( StoreRecord_Carticlelang( cErrmld ) != 0 ) return -1;
	}

	int i;

	for ( i = 0; i < NUMBER_OF_WGR; i++ )
	{
	    if ( StoreRecord_Zartwg( i, cErrmld ) != 0 ) return -1;
	}

	m_bCarticlecodes_changed = FALSE;

	for ( i = 0; i < NUMBER_OF_CODES; i++ )
	{
		if ( StoreRecord_Carticlecodes( i, cErrmld ) != 0 ) return -1;
	}

	// Ausgabe zpznpflege für Artikel-Codes, falls sich mindestens ein Code geändert hat
	if (m_bCarticlecodes_changed)
	{
		if ( StoreRecord_Zpznpflege( m_tagesdatum, "34", cErrmld ) != 0)
			return -1;
	}

	long PreisDatum[NUMBER_OF_PRICE];
	for ( i = 0; i < NUMBER_OF_PRICE; i++ )
	{
		PreisDatum[i] = 0;
	    if ( StoreRecord_Artpreis( i, cErrmld, &PreisDatum[i] ) != 0 ) return -1;
	}

/// neu Sekbez !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if ( StoreRecord_Sekbez( cErrmld ) != 0 ) return -1;

	// nur bei IFA-Pflege
	if ( m_bIfaPflege )
	{
	    if ( StoreRecord_Ifa( cErrmld ) != 0 )  return -1;
		if ( StoreRecord_Zartikel_PhzAlt( cErrmld ) != 0 ) return -1;
	}

//  neu Zapflege. jetzt neu mit Preisen
	bool b_Tagesdatum;
	b_Tagesdatum = false;
	if ( iStatus_Artikel ==  1 ) 
	{
	    if ( StoreRecord_Zapflege( m_tagesdatum, cErrmld ) != 0 ) return -1;
		b_Tagesdatum = true;
	}
	if ( iStatus_Preis == 1 )
	{
		for ( i = 0; i < NUMBER_OF_PRICE; i++ )
		{
			if ( PreisDatum[i] > 0 )
			{
				if ( PreisDatum[i] <= m_tagesdatum )
				{
					if ( !b_Tagesdatum )
					{
						if ( StoreRecord_Zapflege( m_tagesdatum, cErrmld ) != 0 ) 
							return -1;
						b_Tagesdatum = true;
					}
				}			
				else
				{
					if ( StoreRecord_Zapflege( PreisDatum[i], cErrmld ) != 0 ) 
						return -1;
				}
			}
		}
	}

	// Hinweis: zapflege-Ausgabe mit speziellem Datum sollte auch in Schnellerfassung (PflartDoc.cpp) nachgezogen werden

	// bei Änderung Datum wieder lieferbar ab zapflege mit diesem Datum schreiben, damit Satz 
	// zu diesem Zeitpunkt nochmal rausgeschickt wird
	if ( m_Buf.zartikel.DATUM_LIEFERBAR_AB != m_BufOld.zartikel.DATUM_LIEFERBAR_AB &&
		 m_Buf.zartikel.DATUM_LIEFERBAR_AB > 0 && 
		 m_Buf.zartikel.DATUM_LIEFERBAR_AB != m_tagesdatum &&
		 IsCountry("D") )
	{
		if ( StoreRecord_Zapflege( m_Buf.zartikel.DATUM_LIEFERBAR_AB, cErrmld ) != 0 ) 
			return -1;
	}

	// bei Änderung RR-Datum oder AH-Datum zapflege mit diesem Datum schreiben, damit Satz 
	// zu diesem Zeitpunkt nochmal rausgeschickt wird (wegen Anforderung aus der Schweiz, 
	// dass die Kennzeichen im Pharmos erst an diesem Tag auf J gesetzt werden)
	if ( m_Buf.zartikel.DATUM_AH != m_BufOld.zartikel.DATUM_AH &&
		 m_Buf.zartikel.DATUM_AH > m_tagesdatum ) 
	{
		if ( StoreRecord_Zapflege( m_Buf.zartikel.DATUM_AH, cErrmld ) != 0 ) 
			return -1;
	}

	if ( m_Buf.zartikel.DATUM_RR != m_BufOld.zartikel.DATUM_RR &&
		 m_Buf.zartikel.DATUM_RR > m_tagesdatum ) 
	{
		if ( StoreRecord_Zapflege( m_Buf.zartikel.DATUM_RR, cErrmld ) != 0 ) 
			return -1;
	}

	// bei Änderung Erstattungs-Gültigkeits-Datum (Frankreich) zapflege mit diesem Datum schreiben, damit Satz 
	// zu diesem Zeitpunkt vom zpcalcprice selektiert werden kann (für Übertragung zukünftige in aktuelle Werte)
	if ( m_Buf.cartrefundfrance.DATEFROM != m_BufOld.cartrefundfrance.DATEFROM &&
		 m_Buf.cartrefundfrance.DATEFROM > m_tagesdatum ) 
	{
		if ( StoreRecord_Zapflege( m_Buf.cartrefundfrance.DATEFROM, cErrmld ) != 0 ) 
			return -1;
	}

//  neu Zaneuheit
	if ( m_lStatus_Zartikel == 100 )	// wenn Neuanlage
	{
//		keine Neuheit fuer PHARMOS bei ArtikelNeuAnlage
	    if ( StoreRecord_Zaneuheit( NH_NEUHEIT_PHOSIX , cErrmld ) != 0 )
			return -1;
	}
	else 	// wenn Aenderung
	{
		// PHARMOS-Neuheit ( nur noch von IFA erzeugt ) loeschen
		if ( DeleteRecord_Zaneuheit( NH_NEUHEIT_PHARMOS, cErrmld ) != 0 ) return -1;
		// wenn neuer Hersteller, dann Herstelleraenderung fuer PHOSIX
		if ( m_Buf.zartikel.HERSTELLER_NR != m_BufOld.zartikel.HERSTELLER_NR )
		{
			if ( StoreRecord_Zaneuheit( NH_HERSTELLER_WECHSEL, cErrmld ) != 0 )
				return -1;
		}
	}

// Schreiben CArticleCodes bei Neuanlage
	if ( m_lStatus_Zartikel == 100 ) 
	{
		CArticleCodesDoc artCodesDoc;
		artCodesDoc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
		artCodesDoc.SetTagesdatum(m_tagesdatum);

		CARTICLECODES * pBufArtCode = artCodesDoc.GetBuffer();

		pBufArtCode->ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
		sprintf( pBufArtCode->ARTICLE_CODE, "%ld", m_Buf.zartikel.ARTIKEL_NR );
		pBufArtCode->CODE_TYPE = 11; // Codetype "PZN7"
		pBufArtCode->SERIAL_NUMBER = 1;

		double dCount;
		CString sql;
		sql.Format( "select count(*) from carticlecodes where articleno = %ld and preferred_flag = 1", m_Buf.zartikel.ARTIKEL_NR );
		SqlRead(sql, &dCount, NULL);

		if ( dCount == 0.0 ) // mit Codetyp "PZN7" in ALLEN Ländern keine 1:1 Ersetzungen mehr anlegen, die nicht preferred sind!
		{
			if (code.GetLength() < 8 || false == IsCountry("D")) // Codetyp "PZN7" nur im Ausland oder für 7-stellige PZN´s in D
			{
				if ( false == IsCountry("D") || m_tagesdatum < 20130101 )
				{
					pBufArtCode->PREFERRED_FLAG = 1; // bis 2013 auch in D preferred für Codetyp "PZN7"
				}
				else
					pBufArtCode->PREFERRED_FLAG = 0; // ab 2013 Codetyp "PZN7" nicht-preferred und nur noch übergangsweise !

				if ( artCodesDoc.StoreRecord(cErrmld) != 0 ) // 1:1 mit Codetype "PZN7"
					return -1;
			}
		}

		if ( dCount == 0.0 && IsCountry("D") && code.GetLength() <= 8) // in D auch 7-stellige PZN´s mit Codetyp "PZN8" hinterlegen
		{
			pBufArtCode->ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
			sprintf( pBufArtCode->ARTICLE_CODE, "%s", code.GetString());
			pBufArtCode->CODE_TYPE = 16; // Codetype "PZN8"
			
			if (code.GetLength() < 8 && m_tagesdatum < 20130101)
				pBufArtCode->PREFERRED_FLAG = 0; // in 2012 Codetyp "PZN8" für 7-stellige PZN´s noch als NICHT- preferred anlegen!
			else
				pBufArtCode->PREFERRED_FLAG = 1;

			if ( artCodesDoc.StoreRecord(cErrmld) != 0 )
				return -1;
		}
	}

/*
	char errmld[200];
	if ( FdTransact( errmld ) != 0 ) 
	{
		cErrmld = errmld;
		return -1;
	}
*/

	if ( m_lStatus_Zartikel != 100 )	// spezielle Änderungen (nicht bei Neuanlagen!) an KSC übermitteln
	{
		if ( TransferDataToCsc( m_Buf.zartikel.ARTIKEL_NR, cErrmld ) < 0 )
			return -1;
	}
	
	return 0;
}

long CArtikelDoc::TransferDataToCsc( long articleNo, CString &cErrmld )
{
	short transferCounter = 0;

	while (transferCounter < NUM_OF_CSC_TRANSFERS)
	{
		if (m_CscTransfers[transferCounter].fieldType == WERT_CHAR)
		{
			if ( strcmp( (char*)m_CscTransfers[transferCounter].fieldValueNew, (char*)m_CscTransfers[transferCounter].fieldValueOld) == 0 )
			{
				++transferCounter;
				continue;
			}
				
			strcpy(m_CTransferCscBuf.FIELDVALUE, (char*)m_CscTransfers[transferCounter].fieldValueNew);
		}
		else if (m_CscTransfers[transferCounter].fieldType == WERT_LONG)
		{
			if ( *((long *)m_CscTransfers[transferCounter].fieldValueNew) == *((long *)m_CscTransfers[transferCounter].fieldValueOld) )
			{
				++transferCounter;
				continue;
			}

			sprintf(m_CTransferCscBuf.FIELDVALUE, "%ld", *((long *)m_CscTransfers[transferCounter].fieldValueNew));
		}
		else // WERT_DOUBLE
		{
			if ( *((double *)m_CscTransfers[transferCounter].fieldValueNew) == *((double *)m_CscTransfers[transferCounter].fieldValueOld) )
			{
				++transferCounter;
				continue;
			}

			sprintf(m_CTransferCscBuf.FIELDVALUE, "%.2lf", *((double *)m_CscTransfers[transferCounter].fieldValueNew));
		}

		strcpy(m_CTransferCscBuf.FIELDNAME, m_CscTransfers[transferCounter].fieldName);
		m_CTransferCscBuf.ARTICLENO = articleNo;

		if ( StoreRecord_CTransferCsc(cErrmld) != 0 )
			return -1;

		++transferCounter;
	}

	return 0;
}

long CArtikelDoc::StoreRecord( CString &cErrmld, const CString code)
{
	long s;
	s = StoreRecordWithoutTransact( cErrmld, code );
	if ( s != 0 )
		return s;

	char errmld[200];
	if ( FdTransact( errmld ) != 0 ) 
	{
		cErrmld = errmld;
		return -1;
	}
	return 0;
}

long CArtikelDoc::DeleteRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;
    if ( DeleteRecord_Zartikel( cErrmld ) != 0 ) return -1;
    if ( DeleteRecord_Ean( cErrmld ) != 0 ) return -1;
    if ( DeleteRecord_Cartforeigncurr( cErrmld ) != 0 ) return -1;
    if ( DeleteRecord_CSafetyDataSheet( cErrmld ) != 0 ) return -1;
    if ( DeleteRecord_Zartfeb2( cErrmld ) != 0 ) return -1;

	// zartaustria hier nicht noetig, da Löschen nicht direkt aufgerufen werden kann

	int i;
	for ( i = 0; i < NUMBER_OF_WGR; i++ ) // hier alle Zartwg loeschen !!
	{
	    if ( DeleteRecord_Zartwg( i, cErrmld ) != 0 ) return -1;
	}

	for ( i = 0; i < NUMBER_OF_CODES; i++ ) // hier alle Carticlecodes loeschen !!
	{
		if ( DeleteRecord_Carticlecodes( i, cErrmld ) != 0 ) return -1;
	}

	for ( i = 0; i < NUMBER_OF_PRICE; i++ ) // hier alle Preise loeschen !!
	{
	    if ( DeleteRecord_Artpreis( i, cErrmld ) != 0 ) return -1;
	}

	if ( DeleteRecord_Sekbez( cErrmld ) != 0 ) return -1;


	char errmld[200];
	if ( FdTransact( errmld ) != 0 ) 
	{
		cErrmld = errmld;
		return -1;
	}
	return 0;
}


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// IFA
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

double CArtikelDoc::PreisIfaToPreis( char *str )
  {
    char buf[9];
    memcpy( buf, str, 5 );
    buf[5] = '.';
    memcpy( &buf[6], &str[5], 2 );
    buf[8] = '\0';
    return atof( buf );
   }

long CArtikelDoc::DatumIfaToPho( char *str )
  {
    long datum;
    ConvToPhoDate   ( str, &datum, "ttmmjj" );
    MakeLongPhoDate ( &datum );
    return datum;
   }

struct ZIFAART* CArtikelDoc::GetIfaBuffer()
{
	return &m_IfaBuf;
}

struct ZIFAOART* CArtikelDoc::GetIfaOartBuffer()
{
	return &m_IfaOartBuf;
}

void CArtikelDoc::SetIfaPflege( BOOL bSet )
{
	m_bIfaPflege = bSet;
}

void CArtikelDoc::SetNummerekUpdate( BOOL bSet )
{
	m_bNummerekUpdate = bSet;
}

BOOL CArtikelDoc::GetNummerekUpdate( )
{
	return m_bNummerekUpdate;
}

void CArtikelDoc::SetPrimekeyCondition_Ifa ( )
{
	sprintf( m_PrimekeyCondIfa, "IFANR=%ld and SATZNR=%ld",
			 m_IfaBuf.IFANR,
			 m_IfaBuf.SATZNR );
}

int CArtikelDoc::GetBufferDesc_Ifa( CString &cErrmld )
{
	char *tabelle = "zifaart";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Ifa >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Ifa, tabelle,
                                NULL, NULL, V_OHNE, errmld );
				// !!!!!!!!!!!!!!!!!!!!     V_PROTOKOL // zum Test
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Ifa = -1;
		return -1;
	}
	return 0;
}

void CArtikelDoc::SetPrimekeyCondition_IfaOart ( )
{
	sprintf( m_PrimekeyCondIfaOart, "A00PZN=%ld",
				m_IfaOartBuf.A00PZN);
}

int CArtikelDoc::GetBufferDesc_IfaOart( CString &cErrmld )
{
	char *tabelle = "zifaoart";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_IfaOart >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_IfaOart, tabelle,
                                NULL, NULL, V_OHNE, errmld );
				// !!!!!!!!!!!!!!!!!!!!     V_PROTOKOL // zum Test
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_IfaOart = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_IfaOart( long articleNo, CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( GetBufferDesc_IfaOart( cErrmld ) != 0 ) 
		return -1;

	m_IfaOartBuf.A00PZN  = articleNo;
	
	SetPrimekeyCondition_IfaOart ( );
    lStatus = ::FdReadRecord( m_Fd_IfaOart, m_PrimekeyCondIfaOart, 
				  			  &m_IfaOartBuf, errmld );
	if ( lStatus == 0 )
		cErrmld = _T("");
	else
	{
		FdInitTabBuf( m_Fd_IfaOart, &m_IfaOartBuf );
		m_IfaOartBuf.A00PZN  = articleNo;
		cErrmld = errmld;
	}
	
	return lStatus;
}

long CArtikelDoc::ReadRecord_Ifa( long IfaNr, long SatzNr, CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( GetBufferDesc_Ifa( cErrmld ) != 0 ) return -1;

	m_IfaBuf.IFANR  = IfaNr;
	m_IfaBuf.SATZNR = SatzNr;
	SetPrimekeyCondition_Ifa ( );
    lStatus = ::FdReadRecord( m_Fd_Ifa, m_PrimekeyCondIfa, 
				  			  &m_IfaBuf, errmld );
	if ( lStatus == 0 )
		cErrmld = _T("");
	else
		cErrmld = errmld;
	m_lStatus_Ifa = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Ifa( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	SetPrimekeyCondition_Ifa( );
	m_IfaBufOld = m_IfaBuf;          // gelesenen Satz sichern
	if ( m_lStatus_Ifa == 0 )
		lStatus = ::FdDelayUpdateRecord( m_Fd_Ifa, &m_IfaBuf,
									     &m_IfaBufOld, 
										 m_PrimekeyCondIfa, errmld );
	else
	{
		lStatus = m_lStatus_Ifa;
		sprintf( errmld, CResString::ex().getStrTblText(IDS_STORE_ERR_IFA), lStatus );
	}	
	if ( lStatus != 0 )	cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


/////////////////////////////////////////////
// alte PHZ-NR

void CArtikelDoc::SetPrimekeyCondition_PhzAlt ( )
{
	char format[30];
	sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
	sprintf( m_PrimekeyCond_PhzAlt, format, m_PhzaltBuf.ARTIKEL_NR );

//	sprintf( m_PrimekeyCond_PhzAlt, "ARTIKEL_NR=%ld", m_PhzaltBuf.ARTIKEL_NR );
}

long CArtikelDoc::ReadRecord_Zartikel_PhzAlt( long PhzAlt, CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_PhzaltBuf.ARTIKEL_NR = PhzAlt;
	if ( PhzAlt == 0 ) 
	{
		m_lStatus_Phzalt = 100;
		return m_lStatus_Phzalt;
	}

	SetPrimekeyCondition_PhzAlt( );

    lStatus = ::FdReadRecord( m_Fd_Zartikel, m_PrimekeyCond_PhzAlt,
							  &m_PhzaltBuf, errmld );
	if ( lStatus == 0 )
	{
		m_PhzaltBufOld = m_PhzaltBuf;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else
		cErrmld = errmld;
	m_lStatus_Phzalt = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Zartikel_PhzAlt( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( m_lStatus_Phzalt == 0 )
	{
		SetPrimekeyCondition_PhzAlt( );

		m_PhzaltBuf.ERSATZ_NR = m_IfaBuf.A00PZN;
//		m_PhzaltBuf.DATUM_IFAAENDER = DatumIfaToPho( m_IfaBuf.GUELDAT );
		m_PhzaltBuf.DATUM_IFAAENDER = m_IfaBuf.DATUMGUELTIGAB;
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartikel,
										 &m_PhzaltBuf, &m_PhzaltBufOld, 
										 m_PrimekeyCond_PhzAlt, errmld );
	}
	else if ( m_lStatus_Phzalt == 100 )
		lStatus = 0;
	else
	{
		lStatus = m_lStatus_Phzalt;
		sprintf( errmld, CResString::ex().getStrTblText(IDS_STORE_ERR_PHZALT), lStatus );
	}	
	if ( lStatus != 0 )	cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


///////////////////////////////////////////////
// Ifa nach Artikel

void CArtikelDoc::MakePreisAusHerstProz( double herst_proz, 
										 double *grosso, double *aep )
{
	double wert;
	if ( herst_proz >=  0.00999 )
	{
		if ( *aep < 0.005 )
		{
			wert = (*grosso)*herst_proz/100.0;
			::KaufmRunden( &wert, 2);
			*aep = (*grosso) + wert;
		}
	}
	else if ( herst_proz <= -0.00999 )
	{
		if ( (*grosso) < 0.005 )
		{
			wert = (*aep)*herst_proz/100.0;
			::KaufmRunden( &wert, 2);
			*grosso = (*aep) + wert;
		}
	}
}

void CArtikelDoc::IfaToArtikelIntern( struct PFL_ARTIKEL *PflBuf, 
									  bool bArtikelVorhanden )
{

	struct ZARTIKEL *Buf    = &PflBuf->zartikel;
	struct ZIFAART  *IfaBuf = &m_IfaBuf;
	int IsArtikelVorhanden;
	int ToStoreAbdaWg = 0;

	if ( bArtikelVorhanden )
		IsArtikelVorhanden = 1;
	else
		IsArtikelVorhanden = 0;
    
	::IfaSatzToArtikel( IfaBuf, Buf, IsArtikelVorhanden, &ToStoreAbdaWg );	 

	// hier BSsichG berechnen 18.12.2002
	// Bssichg wird nur bei Neuanlagen automatisch brechnet 23.01.2003
	// bssichg: 23.12.2003 entfaellt wieder, da neues Gesetz
/*
	if ( m_lStatus_Zartikel == 100 )
	{
		CBssichG *m_pBssichG;
		m_pBssichG = &((CEkZdpApp*) AfxGetApp())->m_BssichG;
		m_pBssichG->SetBSSichG( Buf, PflBuf->zartwg[0].WARENGRUPPE );
	}
*/
	
	if ( ::HasPreisAValue( IfaBuf ) )
 	   ::IfaSatzToPreis  ( IfaBuf, &PflBuf->artpreis[0], IsArtikelVorhanden );
  
//	PflBuf->artpreis[0].HERST_PROZENT = 0.0;

	if ( ::HasEanAValue( IfaBuf ) )
	   ::IfaSatzToEan   ( IfaBuf, &PflBuf->ean);

}

int CArtikelDoc::IfaToArtikel( CString &cErrmld )
{
	// Artikel-Nr
	m_Buf.zartikel.ARTIKEL_NR = m_IfaBuf.A00PZN;

	if ( InitRecord( cErrmld ) != 0 ) return -1;
	// !!!!!!!!!!!!!!! InitRecord untersuchen ( nr-Save ?????? )

	IfaToArtikelIntern( &m_Buf, 0 );
	return 0;
}

/*
void CArtikelDoc::IfaToTestArtikel( )
{
	IfaToArtikelIntern( &m_BufIfaTest );
}
*/

BOOL CArtikelDoc::CompareArtikelWithIfa( )
{
	int i;

	for ( i = 0; i <  L_VGL_IFA; i++ )
	{
		vgi[i].bEqual   = FALSE;
		vgi[i].bChecked = FALSE;
		vgi[i].nStatus  = 0;
		strcpy( vgi[i].TextArtikel, "" );
		strcpy( vgi[i].TextIfa, "" );
	}

							// Felder mit alten Werten initialisieren
	m_BufIfaTest = m_Buf;	// neu in dieser Version, da IFA nicht alle 
							// Felder ausfuellt 

	IfaToArtikelIntern( &m_BufIfaTest, 1 );

	struct ZARTIKEL* Buf1;
	struct ZARTIKEL* Buf2;
	struct ZARTIKEL* BufPhzalt;

	Buf1 = &m_Buf.zartikel;
	Buf2 = &m_BufIfaTest.zartikel;

	BufPhzalt = &m_PhzaltBuf;
	if ( m_lStatus_Phzalt != 0 )
			BufPhzalt->ERSATZ_NR = 0;

	i = 0;
	// Artikel-Nr
/*
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_ARTNR));
	vgi[i].bEqual = Buf1->ARTIKEL_NR == Buf2->ARTIKEL_NR;
	vgi[i].WertArtikel = &Buf1->ARTIKEL_NR;
	vgi[i].WertIfa     = &Buf2->ARTIKEL_NR;
	vgi[i++].WertArt   = WERT_LONG;
*/
	// Artikelname
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_ARTBEZ));
   	vgi[i].bEqual = strcmp( Buf1->ARTIKEL_NAME, Buf2->ARTIKEL_NAME ) == 0;
	vgi[i].WertArtikel = &Buf1->ARTIKEL_NAME;
	vgi[i].WertIfa     = &Buf2->ARTIKEL_NAME;
	vgi[i].bChecked    = TRUE;   // Artikelname, wird unten auf FALSE gesetzt
	vgi[i].nStatus     = 1;      // defaultmaessig kein Check 
	vgi[i++].WertArt   = WERT_CHAR;
	// EAN
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_EANNR));
	vgi[i].bEqual = strcmp( m_Buf.ean.EAN_NR, m_BufIfaTest.ean.EAN_NR ) == 0; 
	vgi[i].WertArtikel = &m_Buf.ean.EAN_NR;
	vgi[i].WertIfa     = &m_BufIfaTest.ean.EAN_NR;
	vgi[i++].WertArt   = WERT_CHAR;
	// Hersteller-Nr
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_HERSTNR));
	vgi[i].bEqual = Buf1->HERSTELLER_NR == Buf2->HERSTELLER_NR;
	vgi[i].WertArtikel = &Buf1->HERSTELLER_NR;
	vgi[i].WertIfa     = &Buf2->HERSTELLER_NR;
	vgi[i++].WertArt   = WERT_LONG;
	// Negativartikel
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_NEGART));
	vgi[i].bEqual = strcmp( Buf1->NEGATIVLISTE, Buf2->NEGATIVLISTE ) == 0;
	vgi[i].WertArtikel = &Buf1->NEGATIVLISTE;
	vgi[i].WertIfa     = &Buf2->NEGATIVLISTE;
	vgi[i++].WertArt   = WERT_COMBO; //WERT_YESNO;
	// Packung / Einheit
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_EINHEIT));
	vgi[i].bEqual = strcmp( Buf1->EINHEIT, Buf2->EINHEIT ) == 0;
	vgi[i].WertArtikel = &Buf1->EINHEIT;
	vgi[i].WertIfa     = &Buf2->EINHEIT;
	vgi[i++].WertArt   = WERT_CHAR;
	// DARREICHFORM        
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_DARFORM));
	vgi[i].bEqual = strcmp( Buf1->DARREICHFORM, Buf2->DARREICHFORM ) == 0;
	vgi[i].WertArtikel = &Buf1->DARREICHFORM;
	vgi[i].WertIfa     = &Buf2->DARREICHFORM;
	vgi[i++].WertArt   = WERT_CHAR;
/*
	// Datum Anlage
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_DATUM1));
	vgi[i].bEqual = Buf1->DATUM_ANLAGE == Buf2->DATUM_ANLAGE;
	vgi[i].WertArtikel = &Buf1->DATUM_ANLAGE;
	vgi[i].WertIfa     = &Buf2->DATUM_ANLAGE;
	vgi[i++].WertArt   = WERT_DATUM;
	// Datum IFA_Aender
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_DATUM2));
	vgi[i].bEqual = Buf1->DATUM_IFAAENDER == Buf2->DATUM_IFAAENDER;
	vgi[i].WertArtikel = &Buf1->DATUM_IFAAENDER;
	vgi[i].WertIfa     = &Buf2->DATUM_IFAAENDER;
	vgi[i++].WertArt   = WERT_DATUM;
*/
	// Preisempfehlung
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_PREISEMP));
	vgi[i].bEqual = strcmp( Buf1->PREISEMPFEHLUNG, Buf2->PREISEMPFEHLUNG ) == 0;
	vgi[i].WertArtikel = &Buf1->PREISEMPFEHLUNG;
	vgi[i].WertIfa     = &Buf2->PREISEMPFEHLUNG;
	vgi[i++].WertArt   = WERT_YESNO;
	// Verfallkennzeichen
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_VERFALL));
	vgi[i].bEqual = strcmp( Buf1->VERFALL, Buf2->VERFALL ) == 0;
	vgi[i].WertArtikel = &Buf1->VERFALL;
	vgi[i].WertIfa     = &Buf2->VERFALL;
	vgi[i++].WertArt   = WERT_COMBO;
	// Nichuebergh
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_NICHTUBER));
	vgi[i].bEqual = strcmp( Buf1->NICHTUEBERGH, Buf2->NICHTUEBERGH ) == 0;
	vgi[i].WertArtikel = &Buf1->NICHTUEBERGH;
	vgi[i].WertIfa     = &Buf2->NICHTUEBERGH;
	vgi[i++].WertArt   = WERT_YESNO;
	// nurkva
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_NURKVA));
	vgi[i].bEqual = strcmp( Buf1->NURKVA, Buf2->NURKVA ) == 0;
	vgi[i].WertArtikel = &Buf1->NURKVA;
	vgi[i].WertIfa     = &Buf2->NURKVA;
	vgi[i++].WertArt   = WERT_YESNO;
	// Nettoartikel
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_NETTOART));
	vgi[i].bEqual = strcmp( Buf1->NETTOARTIKEL, Buf2->NETTOARTIKEL ) == 0;
	vgi[i].WertArtikel = &Buf1->NETTOARTIKEL;
	vgi[i].WertIfa     = &Buf2->NETTOARTIKEL;
	vgi[i++].WertArt   = WERT_YESNO;
	// Abgabebestimmung
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_ABGABEBEST));
	vgi[i].bEqual = strcmp( Buf1->ABGABEBEST_IFA, Buf2->ABGABEBEST_IFA ) == 0;
	vgi[i].WertArtikel = &Buf1->ABGABEBEST_IFA;
	vgi[i].WertIfa     = &Buf2->ABGABEBEST_IFA;
	vgi[i++].WertArt   = WERT_COMBO;
	// Apotekenpfl
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_APOTHEKENPFL));
	vgi[i].bEqual = strcmp( Buf1->APOTHEKENPFL, Buf2->APOTHEKENPFL ) == 0;
	vgi[i].WertArtikel = &Buf1->APOTHEKENPFL;
	vgi[i].WertIfa     = &Buf2->APOTHEKENPFL;
	vgi[i++].WertArt   = WERT_YESNO;
	// Rezeptpfl
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_REZEPTPFL));
	vgi[i].bEqual = strcmp( Buf1->REZEPTPFL, Buf2->REZEPTPFL ) == 0;
	vgi[i].WertArtikel = &Buf1->REZEPTPFL;
	vgi[i].WertIfa     = &Buf2->REZEPTPFL;
	vgi[i++].WertArt   = WERT_YESNO;
	// Taxpfl
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_TAXPFL));
	vgi[i].bEqual = strcmp( Buf1->TAXPFL, Buf2->TAXPFL ) == 0;
	vgi[i].WertArtikel = &Buf1->TAXPFL;
	vgi[i].WertIfa     = &Buf2->TAXPFL;
//	vgi[i++].WertArt   = WERT_YESNO;
	vgi[i++].WertArt   = WERT_COMBO;	// OTCX_RX	
	// Nettoartikel
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_NETTOART));
	vgi[i].bEqual = strcmp( Buf1->NETTOARTIKEL, Buf2->NETTOARTIKEL ) == 0;
	vgi[i].WertArtikel = &Buf1->NETTOARTIKEL;
	vgi[i].WertIfa     = &Buf2->NETTOARTIKEL;
	vgi[i++].WertArt   = WERT_YESNO;
	// Betaeubungsmittel
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_BTM));
	vgi[i].bEqual = strcmp( Buf1->BTM, Buf2->BTM ) == 0;
	vgi[i].WertArtikel = &Buf1->BTM;
	vgi[i].WertIfa     = &Buf2->BTM;
	vgi[i++].WertArt   = WERT_YESNO;
	// Klinikpackung
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_KLINIKPACK));
	vgi[i].bEqual = strcmp( Buf1->KLINIKPACKUNG, Buf2->KLINIKPACKUNG ) == 0;
	vgi[i].WertArtikel = &Buf1->KLINIKPACKUNG;
	vgi[i].WertIfa     = &Buf2->KLINIKPACKUNG;
	vgi[i++].WertArt   = WERT_YESNO;
	// Vertriebsbindung	// ??????????????????????????????????????????????????
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_VERTRBIND));
	vgi[i].bEqual = strcmp( Buf1->VERTRBIND_IFA, Buf2->VERTRBIND_IFA ) == 0;
	vgi[i].WertArtikel = &Buf1->VERTRBIND_IFA;
	vgi[i].WertIfa     = &Buf2->VERTRBIND_IFA;
	vgi[i++].WertArt   = WERT_YESNO;
	// Laufzeit in Monaten
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_LAUFZEIT));
	vgi[i].bEqual = Buf1->LAUFZEITMONATE == Buf2->LAUFZEITMONATE;
	vgi[i].WertArtikel = &Buf1->LAUFZEITMONATE;
	vgi[i].WertIfa     = &Buf2->LAUFZEITMONATE;
	vgi[i++].WertArt   = WERT_LONG;
	// Kuehlartikel
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_COLDART));
	vgi[i].bEqual = strcmp( Buf1->KUEHLARTIKEL, Buf2->KUEHLARTIKEL ) == 0;
	vgi[i].WertArtikel = &Buf1->KUEHLARTIKEL;
	vgi[i].WertIfa     = &Buf2->KUEHLARTIKEL;
	vgi[i++].WertArt   = WERT_COMBO;

   /* Arzneimittel 14.03.2003 */
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_MEDIC));
	vgi[i].bEqual = strcmp( Buf1->ARZNEIMITTEL, Buf2->ARZNEIMITTEL ) == 0;
	vgi[i].WertArtikel = &Buf1->ARZNEIMITTEL;
	vgi[i].WertIfa     = &Buf2->ARZNEIMITTEL;
	vgi[i++].WertArt   = WERT_YESNO;

   /* Medizinprodukt 14.03.2003 */
 	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_MEDICART));
	vgi[i].bEqual = strcmp( Buf1->MEDIZINPRODUKT, Buf2->MEDIZINPRODUKT ) == 0;
	vgi[i].WertArtikel = &Buf1->MEDIZINPRODUKT;
	vgi[i].WertIfa     = &Buf2->MEDIZINPRODUKT;
	vgi[i++].WertArt   = WERT_YESNO;  

   /* CE-Kennzeichen 14.03.2003 */
 	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_CEKENNZ));
	vgi[i].bEqual = strcmp( Buf1->CE_KENNZEICHEN, Buf2->CE_KENNZEICHEN ) == 0;
	vgi[i].WertArtikel = &Buf1->CE_KENNZEICHEN;
	vgi[i].WertIfa     = &Buf2->CE_KENNZEICHEN;
	vgi[i++].WertArt   = WERT_YESNO;     


   /* Hilfsmittel Verbrauch */
 	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_HILFVERB));
	vgi[i].bEqual = strcmp( Buf1->HILFSM_VERBRAUCH, Buf2->HILFSM_VERBRAUCH ) == 0;
	vgi[i].WertArtikel = &Buf1->HILFSM_VERBRAUCH;
	vgi[i].WertIfa     = &Buf2->HILFSM_VERBRAUCH;
	vgi[i++].WertArt   = WERT_COMBO;    

/*	SCHLACHTVIEH 13.07.99  
	// Schlachtvieh
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_TIERARZNEI));
	vgi[i].bEqual = strcmp( Buf1->TIERARZNEI, Buf2->TIERARZNEI ) == 0;
	vgi[i].WertArtikel = &Buf1->TIERARZNEI;
	vgi[i].WertIfa     = &Buf2->TIERARZNEI;
	vgi[i++].WertArt   = WERT_YESNO;
*/

//	Buf.zartikel.ERSATZ_NR = m_IfaBuf.PHZALT;
		// bei PHZALT : ERSATZ_NR = ARTIKEL_NR
	// Zuzahlung-IFA
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_PAYIFA));
	vgi[i].bEqual = strcmp( Buf1->ZUZAHLUNG_IFA, Buf2->ZUZAHLUNG_IFA ) == 0;
	vgi[i].WertArtikel = &Buf1->ZUZAHLUNG_IFA;
	vgi[i].WertIfa     = &Buf2->ZUZAHLUNG_IFA;
	vgi[i++].WertArt   = WERT_CHAR;
/*
	// ZZ
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_STRING976));
	vgi[i].bEqual = strcmp( Buf1->ZZ, Buf2->ZZ ) == 0;
	vgi[i].WertArtikel = &Buf1->ZZ;
	vgi[i].WertIfa     = &Buf2->ZZ;
	vgi[i++].WertArt   = WERT_CHAR;
*/
	///////////////////////////////////
	// Datum-AH
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_DATUMAH));
	vgi[i].bEqual = Buf1->DATUM_AH == Buf2->DATUM_AH;
	vgi[i].WertArtikel = &Buf1->DATUM_AH;
	vgi[i].WertIfa     = &Buf2->DATUM_AH;
	vgi[i++].WertArt   = WERT_DATUM;
	// Datum-RR
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_DATUMRR));
	vgi[i].bEqual = Buf1->DATUM_RR == Buf2->DATUM_RR;
	vgi[i].WertArtikel = &Buf1->DATUM_RR;
	vgi[i].WertIfa     = &Buf2->DATUM_RR;
	vgi[i++].WertArt   = WERT_DATUM;

	///////////////////////////////////
	// PznAlt

	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_ALTPZN));
	vgi[i].WertArtikel = &BufPhzalt->ERSATZ_NR;	
	vgi[i].WertIfa     = &Buf2->ARTIKEL_NR;

	long phzalt;
	phzalt = m_IfaBuf.A06PZNNF;	// !!!!!!!!!!!!!!!!!!!!!!!
	sprintf( vgi[i].TextIfa, "%ld", phzalt );
	if ( m_lStatus_Phzalt == 0 )
	{
		vgi[i].bEqual = BufPhzalt->ERSATZ_NR == Buf2->ARTIKEL_NR;
		if ( vgi[i].bEqual )
			sprintf( vgi[i].TextArtikel, "%ld", phzalt );
		else
			sprintf( vgi[i].TextArtikel, CResString::ex().getStrTblText(IDS_ALTPZN2),
					 phzalt, BufPhzalt->ERSATZ_NR, Buf2->ARTIKEL_NR );
	}
	else
	{
		vgi[i].bEqual = phzalt == 0;
		if ( vgi[i].bEqual )
			sprintf( vgi[i].TextArtikel, "%ld", phzalt );
		else
		{
			sprintf( vgi[i].TextArtikel, CResString::ex().getStrTblText(IDS_ALTPZN_NOTEXIST),
					 phzalt );
			vgi[i].bChecked = TRUE;   //  wird unten auf FALSE gesetzt
			vgi[i].nStatus  = 2;      // defaultmaessig niemals Check 
		}
	}
/*
	CString S;
	S = vgi[i].TextArtikel + (CString)_T("\n") + vgi[i].TextIfa;
	AfxMessageBox( S );
*/
	vgi[i++].WertArt = WERT_PZNALT;

	///////////////////////////////////
	// Preise
	struct ZARTPREIS* Preis1;
	struct ZARTPREIS* Preis2;

	// DatumGueltig ab
	int PreisStatus = 0;
	BOOL bPreisEqual;
	Preis2 = &m_BufIfaTest.artpreis[0];
	// richtigen Preis bestimmen !!!!!!!!!!!!!!!!!!!!
	if ( Preis2->DATUMGUELTIGAB > m_Buf.artpreis[1].DATUMGUELTIGAB )
	{
		Preis1 = &m_Buf.artpreis[0]; 
/*		Hier nicht, weiter unten
		MakePreisAusHerstProz( Preis1->HERST_PROZENT,
							   &Preis2->GROSSO, &Preis2->AEP );
*/
		bPreisEqual = FALSE;
	}
	else if ( Preis2->DATUMGUELTIGAB == m_Buf.artpreis[1].DATUMGUELTIGAB )
	{
		Preis1 = &m_Buf.artpreis[1]; 
		bPreisEqual = Preis1->GROSSO == Preis2->GROSSO &&
					  Preis1->AEP == Preis2->AEP &&
					  Preis1->AVP == Preis2->AVP &&
					  Preis1->EAVP == Preis2->EAVP &&
					  strcmp( Preis1->KE_MWST, Preis2->KE_MWST ) == 0;				  
	}
	else
	{
		PreisStatus = 2;
		Preis1 = &m_Buf.artpreis[1]; 
		bPreisEqual = FALSE;
	}

	// DatumGueltig ab
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_GULTIGAB));
	vgi[i].bEqual = bPreisEqual;
	vgi[i].WertArtikel = &Preis1->DATUMGUELTIGAB;
	vgi[i].WertIfa     = &Preis2->DATUMGUELTIGAB;
	ConvFromPhoDate( vgi[i].TextArtikel, Preis1->DATUMGUELTIGAB, "tt.mm.jjjj" );
	ConvFromPhoDate( vgi[i].TextIfa, Preis2->DATUMGUELTIGAB, "tt.mm.jjjj" );
	if ( PreisStatus == 2 )
	{
		strcat ( vgi[i].TextIfa, CResString::ex().getStrTblText(IDS_ZU_ALT) );
		vgi[i].bChecked = TRUE;   //  wird unten auf FALSE gesetzt
	}
	vgi[i].nStatus   = PreisStatus;  
	vgi[i++].WertArt = WERT_PREIS;
	// Grosso
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_GROSSO));
	vgi[i].bEqual = bPreisEqual;
	vgi[i].WertArtikel = &Preis1->GROSSO;
	vgi[i].WertIfa     = &Preis2->GROSSO;
	sprintf( vgi[i].TextArtikel, "%.2f", Preis1->GROSSO );
	sprintf( vgi[i].TextIfa, "%.2f", Preis2->GROSSO );
	vgi[i].bChecked = TRUE;   //  wird unten auf FALSE gesetzt
	vgi[i].nStatus  = 2;      // defaultmaessig niemals Check 
	vgi[i++].WertArt   = WERT_PREIS;
	// ApoEk
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_APOEK));
	vgi[i].bEqual = bPreisEqual;
	vgi[i].WertArtikel = &Preis1->AEP;
	vgi[i].WertIfa     = &Preis2->AEP;
	sprintf( vgi[i].TextArtikel, "%.2f", Preis1->AEP );
	sprintf( vgi[i].TextIfa, "%.2f", Preis2->AEP );
	vgi[i].bChecked = TRUE;   //  wird unten auf FALSE gesetzt
	vgi[i].nStatus  = 2;      // defaultmaessig niemals Check 
	vgi[i++].WertArt   = WERT_PREIS;
	// ApoVk
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_APOVK));
	vgi[i].bEqual = bPreisEqual;
	vgi[i].WertArtikel = &Preis1->AVP;
	vgi[i].WertIfa     = &Preis2->AVP;
	sprintf( vgi[i].TextArtikel, "%.2f", Preis1->AVP );
	sprintf( vgi[i].TextIfa, "%.2f", Preis2->AVP );
	vgi[i].bChecked = TRUE;   //  wird unten auf FALSE gesetzt
	vgi[i].nStatus  = 2;      // defaultmaessig niemals Check 
	vgi[i++].WertArt   = WERT_PREIS;
	// EApoVk
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_APOEVK));
	vgi[i].bEqual = bPreisEqual;
	vgi[i].WertArtikel = &Preis1->EAVP;
	vgi[i].WertIfa     = &Preis2->EAVP;
	sprintf( vgi[i].TextArtikel, "%.2f", Preis1->EAVP );
	sprintf( vgi[i].TextIfa, "%.2f", Preis2->EAVP );
	vgi[i].bChecked = TRUE;   //  wird unten auf FALSE gesetzt
	vgi[i].nStatus  = 2;      // defaultmaessig niemals Check 
	vgi[i++].WertArt   = WERT_PREIS;
	// MWST-KENN
	vgi[i].Name = _strdup(CResString::ex().getStrTblText(IDS_MWSTKZ));
	vgi[i].bEqual = bPreisEqual;
	vgi[i].WertArtikel = &Preis1->KE_MWST;
	vgi[i].WertIfa     = &Preis2->KE_MWST;
	strcpy( vgi[i].TextArtikel, Preis1->KE_MWST );
	strcpy( vgi[i].TextIfa, Preis2->KE_MWST );
	vgi[i].bChecked = TRUE;   //  wird unten auf FALSE gesetzt
	vgi[i].nStatus  = 2;      // defaultmaessig niemals Check 
	vgi[i++].WertArt   = WERT_PREIS;

	vgi[i].nStatus  = -1;

	i = 0;
	while ( vgi[i].nStatus != -1 )
	{
		if ( vgi[i].WertArt == WERT_YESNO )
		{
			char *wert;
			wert = (char *) vgi[i].WertArtikel;
			if ( *wert == '1' )
				strcpy( vgi[i].TextArtikel, CResString::ex().getStrTblText(IDS_YES) );
			else
				strcpy( vgi[i].TextArtikel, CResString::ex().getStrTblText(IDS_NO) );

			wert = (char *) vgi[i].WertIfa;
			if ( *wert == '1' )
				strcpy( vgi[i].TextIfa, CResString::ex().getStrTblText(IDS_YES) );
			else
				strcpy( vgi[i].TextIfa, CResString::ex().getStrTblText(IDS_NO) );
		}
		else if ( vgi[i].WertArt == WERT_CHAR )
		{
			strcpy( vgi[i].TextArtikel, (char *)(vgi[i].WertArtikel) );
			strcpy( vgi[i].TextIfa,		(char *)(vgi[i].WertIfa) );
		}
		else if ( vgi[i].WertArt == WERT_DATUM )
		{
			long datum;
			datum = *(( long *)(vgi[i].WertArtikel));
			ConvFromPhoDate( vgi[i].TextArtikel, datum, "tt.mm.jjjj" );
			datum = *(( long *)(vgi[i].WertIfa));
			ConvFromPhoDate( vgi[i].TextIfa,     datum, "tt.mm.jjjj" );
		}
		else if ( vgi[i].WertArt == WERT_LONG )
		{
			long wert;
			wert = *(( long *)(vgi[i].WertArtikel));
			sprintf( vgi[i].TextArtikel, "%ld", wert );
			wert = *(( long *)(vgi[i].WertIfa));
			sprintf( vgi[i].TextIfa, "%ld", wert );
		}
		else if ( vgi[i].WertArt == WERT_PZNALT )
		{
			// hier nichts machen
		}
		else if ( vgi[i].WertArt == WERT_DOUBLE )
		{
			double wert;
			wert = *(( double *)(vgi[i].WertArtikel));
			sprintf( vgi[i].TextArtikel, "%.2f", wert );
			wert = *(( double *)(vgi[i].WertIfa));
			sprintf( vgi[i].TextIfa, "%.2f", wert );
		}
		else if ( vgi[i].WertArt == WERT_COMBO )  // wegmachen !!!!!
		{
			strcpy( vgi[i].TextArtikel, (char *)(vgi[i].WertArtikel) );
			strcpy( vgi[i].TextIfa,		(char *)(vgi[i].WertIfa) );
		}
		vgi[i].bChecked = !vgi[i].bChecked; // rumdrehen
		i++;
	}

	// hier Hersteller-% verarbeiten 
	if ( Preis2->DATUMGUELTIGAB > m_Buf.artpreis[1].DATUMGUELTIGAB )
		MakePreisAusHerstProz( Preis1->HERST_PROZENT,
							   &Preis2->GROSSO, &Preis2->AEP );

	i = 0;
	while ( vgi[i].nStatus != -1  && vgi[i].bEqual ) i++;
	return vgi[i].nStatus == -1; 
}

void CArtikelDoc::UpdateArtikelWithIfa( ) 
{
	long datum;
	long lwert;
	double dwert;
	int i;

	i = 0;
	while ( vgi[i].nStatus != -1 )
	{
		if ( vgi[i].bChecked )
		{
			if ( vgi[i].WertArt == WERT_YESNO )
			{
				strcpy( (char *)(vgi[i].WertArtikel), (char *)(vgi[i].WertIfa) );
			}
			else if ( vgi[i].WertArt == WERT_CHAR )
			{
				strcpy( (char *)(vgi[i].WertArtikel), (char *)(vgi[i].WertIfa) );
			}
			else if ( vgi[i].WertArt == WERT_DATUM )
			{
				datum = *(( long *)(vgi[i].WertIfa));
				*(( long *)(vgi[i].WertArtikel)) = datum;
			}
			else if ( vgi[i].WertArt == WERT_LONG )
			{
				lwert = *(( long *)(vgi[i].WertIfa));
				*(( long *)(vgi[i].WertArtikel)) = lwert;
			}
			else if ( vgi[i].WertArt == WERT_PZNALT )
			{
				lwert = *(( long *)(vgi[i].WertIfa));
				*(( long *)(vgi[i].WertArtikel)) = lwert;
			}
			else if ( vgi[i].WertArt == WERT_DOUBLE )
			{
				dwert = *(( double *)(vgi[i].WertIfa));
				*(( double *)(vgi[i].WertArtikel)) = dwert;
			}
			else if ( vgi[i].WertArt == WERT_COMBO )  // wegmachen !!!!!
			{
				strcpy( (char *)(vgi[i].WertArtikel), (char *)(vgi[i].WertIfa) );
			}
			else if ( vgi[i].WertArt == WERT_PREIS )
			{	
				datum = *(( long *)(vgi[i].WertIfa));
				*(( long *)(vgi[i].WertArtikel)) = datum;

				dwert = *(( double *)(vgi[i+1].WertIfa));
				*(( double *)(vgi[i+1].WertArtikel)) = dwert;

				dwert = *(( double *)(vgi[i+2].WertIfa));
				*(( double *)(vgi[i+2].WertArtikel)) = dwert;

				dwert = *(( double *)(vgi[i+3].WertIfa));
				*(( double *)(vgi[i+3].WertArtikel)) = dwert;

				strcpy( (char *)(vgi[i+4].WertArtikel), 
						(char *)(vgi[i+4].WertIfa) );
			}
		}
		i++;
	}
}

struct VGL_IFA* CArtikelDoc::GetVglIfaBuffer()
{
	return vgi;
};


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// SEKBEZ
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

int CArtikelDoc::InitRecord_Sekbez( int i, CString &cErrmld )
{
	if (cErrmld.GetLength()) {}

    FdInitTabBuf( m_Fd_Sekbez, &m_SekbezBuf[i] );
     m_SekbezBuf[i].ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
	return 0;
}

void CArtikelDoc::SetPrimekeyCondition_Sekbez( int i )
{
	char format[50];
	sprintf( format, "ARTIKEL_NR=%c%d.ld and ARTIKEL_NAME='%cs'", 
		             '%', L_ARTIKEL_NR, '%' );
	sprintf( m_PrimekeyCond_Sekbez, format, 
			 m_SekbezBuf[i].ARTIKEL_NR,
			 m_SekbezBuf[i].ARTIKEL_NAME );
/*
	sprintf( m_PrimekeyCond_Sekbez, 
			 "ARTIKEL_NR=%ld and ARTIKEL_NAME='%s'",
			 m_SekbezBuf[i].ARTIKEL_NR,
			 m_SekbezBuf[i].ARTIKEL_NAME );
*/
}

void CArtikelDoc::SetPrimekeyCondition_OldSekbez( int i )
{
	char format[50];
	sprintf( format, "ARTIKEL_NR=%c%d.ld and ARTIKEL_NAME='%cs'", 
		             '%', L_ARTIKEL_NR, '%' );
	sprintf( m_PrimekeyCond_Sekbez, format, 
			 m_SekbezBufOld[i].ARTIKEL_NR,
			 m_SekbezBufOld[i].ARTIKEL_NAME );
/*
	sprintf( m_PrimekeyCond_Sekbez, 
			 "ARTIKEL_NR=%ld and ARTIKEL_NAME='%s'",
			 m_SekbezBufOld[i].ARTIKEL_NR,
			 m_SekbezBufOld[i].ARTIKEL_NAME );
*/
}

int CArtikelDoc::GetBufferDesc_Sekbez( CString &cErrmld )
{
	char *tabelle = "zartsekbez";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Sekbez >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Sekbez, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Sekbez = -1;
		return -1;
	}
	//////////////////////////////////////////////////////////////////
	m_nMaxNrOfSekbez = NUMBER_OF_SEKBEZ;
	return 0;
}

long CArtikelDoc::ReadRecord_Sekbez( CString &cErrmld )
{
	long lStatus;
//	char errmld[200];
	int fd;
	int i;
	CString sql;

	if ( GetBufferDesc_Sekbez( cErrmld ) != 0 ) return -1;

	lStatus = 100;
	cErrmld = _T("");

	// Sekbez-Saetze initialisieren
	m_nNrOfSekbez = 0;
	i = 0;
	while ( i < m_nMaxNrOfSekbez && lStatus == 100 )
	{
		if ( InitRecord_Sekbez( i, cErrmld ) == 0 )
			m_SekbezBufOld[i] = m_SekbezBuf[i];	
		else
			lStatus = -1;
		i++;
	}
	if ( lStatus == -1 ) return lStatus;

	// Sekbez-Saetze lesen
	struct ZARTSEKBEZ sek;
	sprintf( m_PrimekeyCond_Sekbez, 
			 "ARTIKEL_NR=%ld",
			 m_Buf.zartikel.ARTIKEL_NR );

	sql.Format("select %s from ZARTSEKBEZ where %s order by ARTIKEL_NAME",
				PROJECTION_ZARTSEKBEZ, m_PrimekeyCond_Sekbez);

	lStatus = ::SqlOpenCs( &fd, sql );
	if ( lStatus != 0 ) 
	{
		cErrmld = DynErrmld();
		return lStatus;
	}

	i = 0;    
	while ( lStatus == 0 && i < m_nMaxNrOfSekbez )
	{
		lStatus = SqlFetch( fd, 1, &sek, NULL );
		if ( lStatus == 0 )
		{
			m_SekbezBuf[i] = sek;
			m_SekbezBufOld[i] = m_SekbezBuf[i];
			i++;
		}
	}
	cErrmld = DynErrmld();
	SqlCloseCs( fd );
	m_nNrOfSekbez = i;
	m_nNewNrOfSekbez = i;
	return lStatus;
}

int CArtikelDoc::IsRecordModified_Sekbez( )
{
	if ( m_nNrOfSekbez != m_nNewNrOfSekbez )
		return 1;	// modified

	int i, j;

	j = 0;
	while ( j < m_nNewNrOfSekbez )
	{
		i = 0;
		while ( i < m_nNrOfSekbez &&
				( strcmp( m_SekbezBufOld[i].ARTIKEL_NAME,
				 	      m_SekbezBuf[j].ARTIKEL_NAME )   != 0 ||
				  strcmp( m_SekbezBufOld[i].PHARMOS_SEKBEZ, 
			              m_SekbezBuf[j].PHARMOS_SEKBEZ ) != 0 || 
				  strcmp( m_SekbezBufOld[i].BEMERKUNGEN, 
			              m_SekbezBuf[j].BEMERKUNGEN )    != 0    )
			  )
			i++;

		if ( i >= m_nNrOfSekbez )  
			return 1;	// Record j was modified 

		j++;
	}
	return 0;	// not modified
}

long CArtikelDoc::StoreRecord_Sekbez( CString &cErrmld )
{
	int  i;
	int  j;
	long lStatus;
	char errmld[200];

	lStatus = 0;

	// Records to be delete 
	i = 0;
	while ( lStatus == 0 && i < m_nNrOfSekbez )
	{
		j = 0;
		while ( j < m_nNewNrOfSekbez &&
				strcmp( m_SekbezBufOld[i].ARTIKEL_NAME,
					    m_SekbezBuf[j].ARTIKEL_NAME ) != 0 )
				j++;
		if ( j >= m_nNewNrOfSekbez )  // Record  i deleted 
		{
			SetPrimekeyCondition_OldSekbez ( i );
			lStatus = ::FdDelayDeleteRecord( m_Fd_Sekbez, &m_SekbezBufOld[i], 
											 m_PrimekeyCond_Sekbez, errmld );
		}
		i++;
	}
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		return lStatus;
	}

	// New Records and records to update
	j = 0;
	while ( lStatus == 0 && j < m_nNewNrOfSekbez )
	{
		i = 0;
		while ( i < m_nNrOfSekbez &&
				strcmp( m_SekbezBufOld[i].ARTIKEL_NAME,
					    m_SekbezBuf[j].ARTIKEL_NAME ) != 0 )
				i++;

		// Artikel-Mc generieren
		strcpy( m_SekbezBuf[j].ARTIKEL_MC,
			    MakeArtikelMc( m_SekbezBuf[j].ARTIKEL_NAME ) );


		if ( i >= m_nNrOfSekbez )  // Record  j is new 
		{
			SetPrimekeyCondition_Sekbez ( j );
			lStatus = ::FdDelayInsertRecord( m_Fd_Sekbez, &m_SekbezBuf[j], 
											 m_PrimekeyCond_Sekbez, errmld);
		}
		else
		{
			SetPrimekeyCondition_Sekbez ( j );
			lStatus = ::FdDelayUpdateRecord( m_Fd_Sekbez, &m_SekbezBuf[j],
											 &m_SekbezBufOld[i],
											 m_PrimekeyCond_Sekbez, errmld );
		}
		j++;
	}
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}


long CArtikelDoc::DeleteRecord_Sekbez( CString &cErrmld )
{
	int  i;
	long lStatus;
	char errmld[200];

	lStatus = 0;
	i = 0;
	while ( lStatus == 0 && i < m_nNrOfSekbez )
	{
		SetPrimekeyCondition_OldSekbez ( i );
		lStatus = ::FdDelayDeleteRecord( m_Fd_Sekbez, &m_SekbezBufOld[i], 
										 m_PrimekeyCond_Sekbez, errmld );
		i++;
	}
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

struct ZARTSEKBEZ* CArtikelDoc::GetSekbezBuffer()
{
	return m_SekbezBuf;
}

int CArtikelDoc::GetNrOfSekbez( )
{
	return m_nNrOfSekbez;
}

void CArtikelDoc::SetNewNrOfSekbez( int nNewNr )
{
	m_nNewNrOfSekbez = nNewNr;
}

///////////////////////////////////////////////////////////
//  Read PHARMOS-Sekbez

void CArtikelDoc::ReadPharmosSekbez( )
{	
	m_Buf.cPharmosSekbez = " ";

	if ( m_lStatus_Zartikel != 0 )
		return;

	char str[51];
	CString sql;
	sprintf( str, "%ld", m_Buf.zartikel.ARTIKEL_NR );
	sql = "select ARTIKEL_NAME from ZARTSEKBEZ where ARTIKEL_NR=";
	sql += str;
	sql += " and PHARMOS_SEKBEZ='1'";
	if ( SqlRead( sql, str, NULL ) == 0 )
		m_Buf.cPharmosSekbez = str;
}

////////////////////////////////////////////////////////////
// ARTNRBL
////////////////////////////////////////////////////////////

void CArtikelDoc::SetPrimekeyCondition_Artnrbl( int i )
{
	char format[50];
	sprintf( format, "ARTIKEL_NR=%c%d.ld and BESLA_NR=%c%d.1ld",'%', L_ARTIKEL_NR, '%', L_BESLA_NR );

	if (i < 0)
		sprintf( m_PrimekeyCond_Artnrbl, format, m_Buf.zartikel.ARTIKEL_NR, m_Buf.zartikel.HERSTELLER_NR );
	else
		sprintf( m_PrimekeyCond_Artnrbl, format, m_ArtnrblBuf[i].ARTIKEL_NR, m_ArtnrblBuf[i].BESLA_NR );
}

int CArtikelDoc::GetBufferDesc_Artnrbl( CString &cErrmld )
{
	char *tabelle = "artnrbl";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Artnrbl >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Artnrbl, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Artnrbl = -1;
		return -1;
	}
	//////////////////////////////////////////////////////////////////
	m_nMaxNrOfArtnrbl = NUMBER_OF_ARTNRBL;
	return 0;
}

long CArtikelDoc::ReadRecord_Artnrbl( CString &cErrmld )
{
	long lStatus;
//	char errmld[200];
	int fd;
	int i;
	CString sql;

	if ( GetBufferDesc_Artnrbl( cErrmld ) != 0 ) return -1;

	lStatus = 100;
	cErrmld = _T("");

	// Artnrbl-Saetze lesen
	struct ARTNRBL anb;
	sprintf( m_PrimekeyCond_Artnrbl, 
			 "ARTIKEL_NR=%ld",
			 m_Buf.zartikel.ARTIKEL_NR );

	sql.Format("select %s from ARTNRBL where %s order by ARTIKEL_NR_BLIEFER",
				PROJECTION_ARTNRBL, m_PrimekeyCond_Artnrbl);

	lStatus = ::SqlOpenCs( &fd, sql );
	if ( lStatus != 0 ) 
	{
		cErrmld = DynErrmld();
		return lStatus;
	}

	i = 0;    
	while ( lStatus == 0 && i < m_nMaxNrOfArtnrbl )
	{
		lStatus = SqlFetch( fd, 1, &anb, NULL );
		if ( lStatus == 0 )
		{
			m_ArtnrblBuf[i] = anb;
			m_ArtnrblBufOld[i] = m_ArtnrblBuf[i];
			i++;
		}
	}

	cErrmld = DynErrmld();
	SqlCloseCs( fd );
	m_nNrOfArtnrbl = i;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Artnrbl( CString &cErrmld )
{
	int  i;
	long lStatus;
	char errmld[200];

	lStatus = 0;

	// erstmal alle Sätze zu diesem Artikel einlesen
	ReadRecord_Artnrbl( cErrmld );

	long beslanr	= m_Buf.zartikel.HERSTELLER_NR;
	long beslanrOld = m_BufOld.zartikel.HERSTELLER_NR;

	// wenn awl1 gesetzt, dann diese Nr statt der HNR verwenden (lt. Fr.Papadymitriya am 21.06.2011)
	if (IsCountry("CH") && m_Buf.zartikel.AWL1 > 0)
		beslanr = m_Buf.zartikel.AWL1;

	if (IsCountry("CH") && m_BufOld.zartikel.AWL1 > 0)
		beslanrOld = m_BufOld.zartikel.AWL1;

	// in Kroatien, Österreich + Schweiz neuen Satz schreiben, wenn bisher keiner da
	if ( (IsCountry("HR") || IsCountry("CH") || IsCountry("A")) && 
		m_nNrOfArtnrbl == 0 &&							// noch kein Eintrag in artnrbl für diese PZN
	   (m_lStatus_Zartikel == 100 ||					// Artikel- Neuanlage
		strncmp ( m_BufOld.zartikel.ARTIKEL_NR_HERST,	// bisher keine ANRH hinterlegt
				"               ", L_ZARTIKEL_ARTIKEL_NR_HERST ) == 0) &&
		strncmp ( m_Buf.zartikel.ARTIKEL_NR_HERST,		// Insert nur, wenn ANRH überhaupt gefüllt ist
				"               ", L_ZARTIKEL_ARTIKEL_NR_HERST ) != 0 )
	{
		SetPrimekeyCondition_Artnrbl( -1 );

	    FdInitTabBuf( m_Fd_Artnrbl, &m_ArtnrblBuf[0] );
		m_ArtnrblBuf[0].ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
		m_ArtnrblBuf[0].BESLA_NR = beslanr;

		strcpy (m_ArtnrblBuf[0].ARTIKEL_NR_BLIEFER, m_Buf.zartikel.ARTIKEL_NR_HERST);

		lStatus = ::FdDelayInsertRecord( m_Fd_Artnrbl, &m_ArtnrblBuf[0],
									 	 m_PrimekeyCond_Artnrbl, errmld);
	}
	else 
	{
		i = 0;
		double dCount = 0.0;
		
		// in der Schweiz prüfen, ob bereits ein Satz zur Kombination PZN / HNR (ggfs. geändert!) existiert
		if (IsCountry("CH")) 
		{
			CString sql;
			sql.Format( "select count(*) from artnrbl where artikel_nr = %ld and besla_nr = %ld",
							m_Buf.zartikel.ARTIKEL_NR, beslanr );
			SqlRead(sql, &dCount, NULL);
		}

		while ( lStatus == 0 && i < m_nNrOfArtnrbl )
		{
		// nur Sätze, bei denen die ANRH dem alten zartikel-Wert entspricht
			if ( (strncmp (m_ArtnrblBuf[i].ARTIKEL_NR_BLIEFER, 
							m_BufOld.zartikel.ARTIKEL_NR_HERST, L_ZARTIKEL_ARTIKEL_NR_HERST) == 0

				// und in der Schweiz der Satz zur bisherigen HNR gehörte 
				// --> auskommentieren, wenn alle Sätze upgedated werden sollen, nicht nur der zur HNR passende
				&& ( IsCountry("CH") == false || m_ArtnrblBuf[i].BESLA_NR == beslanrOld ) 
				 
		// oder in der Schweiz, wenn ein Satz für die neue HNR bereits existiert
				) || (	IsCountry("CH") == TRUE  &&	m_ArtnrblBuf[i].BESLA_NR == beslanr ))
			{
				SetPrimekeyCondition_Artnrbl( i );
						
				// wenn Änderung --> Update, sonst Löschen artnrbl
				if ( strncmp ( m_Buf.zartikel.ARTIKEL_NR_HERST, "               ", L_ZARTIKEL_ARTIKEL_NR_HERST ) != 0 &&
					// und in der Schweiz die neue HNR noch nicht vorhanden
					(IsCountry("CH") == false || dCount == 0.0 || 
					// oder die bisherige HNR ungleich artnrbl --> sonst wird der aktuelle Satz gelöscht
					  m_ArtnrblBuf[i].BESLA_NR != beslanrOld || 
					// oder die HNR + AWL1 unverändert
					 ( m_BufOld.zartikel.HERSTELLER_NR	== m_Buf.zartikel.HERSTELLER_NR && 
					   m_BufOld.zartikel.AWL1			== m_Buf.zartikel.AWL1 ) ) )
				{
					strcpy (m_ArtnrblBuf[i].ARTIKEL_NR_BLIEFER, m_Buf.zartikel.ARTIKEL_NR_HERST);
					
					if (IsCountry("CH") && m_ArtnrblBuf[i].BESLA_NR == beslanrOld)
						m_ArtnrblBuf[i].BESLA_NR = beslanr;
		
					lStatus = ::FdDelayUpdateRecord( m_Fd_Artnrbl, &m_ArtnrblBuf[i],
												&m_ArtnrblBufOld[i],
												m_PrimekeyCond_Artnrbl, errmld );
				}
				else
				{
					lStatus = ::FdDelayDeleteRecord( m_Fd_Artnrbl, &m_ArtnrblBufOld[i],
												m_PrimekeyCond_Artnrbl, errmld );
				}
			}

			i++;
		}
	}

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

/*
long CArtikelDoc::DeleteRecord_Artnrbl( CString &cErrmld )
{
	int  i;
	long lStatus;
	char errmld[200];

	lStatus = 0;
	i = 0;
	while ( lStatus == 0 && i < m_nNrOfArtnrbl )
	{
		SetPrimekeyCondition_OldArtnrbl ( i );
		lStatus = ::FdDelayDeleteRecord( m_Fd_Artnrbl, &m_ArtnrblBufOld[i], 
										 m_PrimekeyCond_Artnrbl, errmld );
		i++;
	}
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

*/

/////////////////////////////////////////////////////////////////////////
// zartaustria (nur Österreich)

int CArtikelDoc::InitRecord_Zartaustria( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
    nr = m_Buf.zartaustria.ARTIKEL_NR;
    FdInitTabBuf( m_Fd_Zartaustria, &m_Buf.zartaustria );
    m_Buf.zartaustria.ARTIKEL_NR = nr;

	m_Buf.zartaustria.WECHSELARTIKEL[0]   = '0';
	m_Buf.zartaustria.BUENDELPACKUNG[0]   = '0';
	m_Buf.zartaustria.NACHLIEFERUNG[0]    = '0';
	m_Buf.zartaustria.CHARGENARTIKEL[0]   = '0';

	return 0;
}

void CArtikelDoc::RestoreBuffer_Zartaustria()
{
    m_BufSave.zartaustria.ARTIKEL_NR = m_Buf.zartaustria.ARTIKEL_NR;
    m_Buf.zartaustria = m_BufSave.zartaustria;
    m_Buf.zartaustria.ARTIKEL_NR = m_BufSave.zartaustria.ARTIKEL_NR;
}

int CArtikelDoc::GetBufferDesc_Zartaustria( CString &cErrmld )
{
	char *tabelle = "zartaustria";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartaustria >= 0 ) return 0;

//	FillCmpIndikator_Zartaustria ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartaustria, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartaustria = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Zartaustria( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.zartaustria.ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition ( );
    lStatus = ::FdReadRecord( m_Fd_Zartaustria, m_PrimekeyCond, 
				  			  &m_Buf.zartaustria, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartaustria = m_Buf.zartaustria;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartaustria( cErrmld ) == 0 )
		{
//			m_BufOld.zartaustria = m_Buf.zartaustria;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;
	m_lStatus_Zartaustria = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Zartaustria( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition ( );
	if ( m_lStatus_Zartaustria == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_Zartaustria, &m_Buf.zartaustria, 
										 m_PrimekeyCond, errmld);
	}
	else if ( m_lStatus_Zartaustria == 0 )
	{
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartaustria, &m_Buf.zartaustria,
							 			 &m_BufOld.zartaustria,
										 m_PrimekeyCond, errmld );
	}
	else
	{
		lStatus = m_lStatus_Zartaustria;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

long CArtikelDoc::DeleteRecord_Zartaustria( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Zartaustria == 100 ) return 0;
	SetPrimekeyCondition ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartaustria, &m_BufOld.zartaustria, 
									 m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// zartswitzerland (nur Schweiz)

int CArtikelDoc::InitRecord_Zartswitzerland( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
    nr = m_Buf.zartswitzerland.ARTIKEL_NR;
    FdInitTabBuf( m_Fd_Zartswitzerland, &m_Buf.zartswitzerland );
    m_Buf.zartswitzerland.ARTIKEL_NR = nr;

	m_Buf.zartswitzerland.BUENDELPACKUNG[0]     = '0';
	m_Buf.zartswitzerland.VERTRBIND_NUR_APO[0]  = '0';
	m_Buf.zartswitzerland.VERTRBIND_NUR_SPIT[0] = '0';
	m_Buf.zartswitzerland.VERTRBIND_KUENZLE[0]  = '0';
	m_Buf.zartswitzerland.VERTRBIND_INLAND[0]   = '0';
	m_Buf.zartswitzerland.VERTRBIND_KANTONAL[0] = '0';
	m_Buf.zartswitzerland.VERTRBIND_PREWHOLE[0] = '0';
	m_Buf.zartswitzerland.VERTRBIND_LISTE_C[0]  = '0';
	m_Buf.zartswitzerland.VERTRBIND_LISTE_D[0]  = '0';

	return 0;
}

void CArtikelDoc::RestoreBuffer_Zartswitzerland()
{
    m_BufSave.zartswitzerland.ARTIKEL_NR = m_Buf.zartswitzerland.ARTIKEL_NR;
    m_Buf.zartswitzerland = m_BufSave.zartswitzerland;
    m_Buf.zartswitzerland.ARTIKEL_NR = m_BufSave.zartswitzerland.ARTIKEL_NR;
}

int CArtikelDoc::GetBufferDesc_Zartswitzerland( CString &cErrmld )
{
	char *tabelle = "zartswitzerland";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartswitzerland >= 0 ) return 0;

//	FillCmpIndikator_Zartswitzerland ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartswitzerland, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartswitzerland = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Zartswitzerland( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.zartswitzerland.ARTIKEL_NR = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition ( );
    lStatus = ::FdReadRecord( m_Fd_Zartswitzerland, m_PrimekeyCond, 
				  			  &m_Buf.zartswitzerland, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartswitzerland = m_Buf.zartswitzerland;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartswitzerland( cErrmld ) == 0 )
		{
//			m_BufOld.zartswitzerland = m_Buf.zartswitzerland;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;
	m_lStatus_Zartswitzerland = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Zartswitzerland( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition ( );
	if ( m_lStatus_Zartswitzerland == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_Zartswitzerland, &m_Buf.zartswitzerland, 
										 m_PrimekeyCond, errmld);
	}
	else if ( m_lStatus_Zartswitzerland == 0 )
	{
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartswitzerland, &m_Buf.zartswitzerland,
							 			 &m_BufOld.zartswitzerland,
										 m_PrimekeyCond, errmld );
	}
	else
	{
		lStatus = m_lStatus_Zartswitzerland;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

long CArtikelDoc::DeleteRecord_Zartswitzerland( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Zartswitzerland == 100 ) return 0;
	SetPrimekeyCondition ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartswitzerland, &m_BufOld.zartswitzerland, 
									 m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

/////////////////////////////////////////////////////////////////////////
// carticlelang (nur Schweiz und Bulgarien)

int CArtikelDoc::InitRecord_Carticlelang( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
    nr = m_Buf.carticlelang.ARTICLENO;
	FdInitTabBuf( m_Fd_Carticlelang, &m_Buf.carticlelang );
    m_Buf.carticlelang.ARTICLENO = nr;
	strcpy(m_Buf.carticlelang.LANGID, GetCarticlelangCountryCode());

	// für Prewhole sind die deutschen Namen die fremdsprachigen
/*	if (IsPrewhole())
		strcpy(m_Buf.carticlelang.LANGID, "DE");
	else
		strcpy(m_Buf.carticlelang.LANGID, "FR"); */

	return 0;
}

void CArtikelDoc::RestoreBuffer_Carticlelang()
{
    strcpy (m_BufSave.carticlelang.LANGID, m_Buf.carticlelang.LANGID);
    m_BufSave.carticlelang.ARTICLENO = m_Buf.carticlelang.ARTICLENO;
    m_Buf.carticlelang = m_BufSave.carticlelang;
    strcpy (m_Buf.carticlelang.LANGID, m_BufSave.carticlelang.LANGID);
    m_Buf.carticlelang.ARTICLENO = m_BufSave.carticlelang.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Carticlelang( CString &cErrmld )
{
	char *tabelle = "carticlelang";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Carticlelang >= 0 ) return 0;

//	FillCmpIndikator_carticlelang ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Carticlelang, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
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

long CArtikelDoc::ReadRecord_Carticlelang( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.carticlelang.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;

	SetPrimekeyCondition_Carticlelang ( );
	lStatus = ::FdReadRecord( m_Fd_Carticlelang, m_PrimekeyCond_Carticlelang, 
				  			  &m_Buf.carticlelang, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.carticlelang = m_Buf.carticlelang;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Carticlelang( cErrmld ) == 0 )
		{
//			m_BufOld.carticlelang = m_Buf.carticlelang;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Carticlelang = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Carticlelang( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];
	int s;

	// Artikel-Mc generieren
	if (IsCountry("BG")) 
		strcpy( m_Buf.carticlelang.ARTICLEMC, MakeArtikelMc( m_Buf.carticlelang.ARTICLENAMELONG ) );
	else
		strcpy( m_Buf.carticlelang.ARTICLEMC, MakeArtikelMc( m_Buf.carticlelang.ARTICLENAME ) );

	SetPrimekeyCondition_Carticlelang ( );
	if ( m_lStatus_Carticlelang == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_Carticlelang, &m_Buf.carticlelang, 
										 m_PrimekeyCond_Carticlelang, errmld);
	}
	else if ( m_lStatus_Carticlelang == 0 )
	{
		lStatus = ::FdDelayUpdateRecord( m_Fd_Carticlelang, &m_Buf.carticlelang,
							 			 &m_BufOld.carticlelang,
										 m_PrimekeyCond_Carticlelang, errmld );
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
		s = ::FdIsRecordModified( m_Fd_Carticlelang, &m_Buf.carticlelang, 
				&m_BufOld.carticlelang, errmld );
		if ( s == 1 ) 
		{
			lStatus = StoreRecord_Zpznpflege( m_tagesdatum, "11", cErrmld );

			if ( lStatus == 0 ) 
				cErrmld = _T("");
		}
	}

	return lStatus;
}

long CArtikelDoc::DeleteRecord_Carticlelang( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Carticlelang == 100 ) return 0;
	SetPrimekeyCondition_Carticlelang ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Carticlelang, &m_BufOld.carticlelang, 
									 m_PrimekeyCond_Carticlelang, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_Carticlelang( )
{
	char format[50];
/*	char langid[3];

	// für Prewhole sind die deutschen Namen die fremdsprachigen
	if (IsPrewhole())
		strcpy(langid, "DE");
	else
		strcpy(langid, "FR"); */

	sprintf( format, "ARTICLENO=%c%d.ld and LANGID='%cs'", 
		             '%', L_ARTIKEL_NR, '%' );

	sprintf( m_PrimekeyCond_Carticlelang, format, 
			 m_Buf.carticlelang.ARTICLENO, GetCarticlelangCountryCode());
}

/////////////////////////////////////////////////////////////////////////
// zartfrance (nur Frankreich)

int CArtikelDoc::InitRecord_Zartfrance( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
    nr = m_Buf.zartfrance.ARTICLENO;
    FdInitTabBuf( m_Fd_Zartfrance, &m_Buf.zartfrance );
    m_Buf.zartfrance.ARTICLENO = nr;

	m_Buf.zartfrance.REIMBURSEMENT_TYPE[0] = '0';

	// Init code bloquage mit '9' (neuer Artikel)
	m_Buf.zartfrance.CODE_BLOQUAGE[0] = '9';

	return 0;
}

void CArtikelDoc::RestoreBuffer_Zartfrance()
{
    m_BufSave.zartfrance.ARTICLENO = m_Buf.zartfrance.ARTICLENO;
    m_Buf.zartfrance = m_BufSave.zartfrance;
    m_Buf.zartfrance.ARTICLENO = m_BufSave.zartfrance.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Zartfrance( CString &cErrmld )
{
	char *tabelle = "zartfrance";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartfrance >= 0 ) return 0;

//	FillCmpIndikator_Zartfrance ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartfrance, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartfrance = -1;
		return -1;
	}
	return 0;
}

long CArtikelDoc::ReadRecord_Zartfrance( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.zartfrance.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_Zartfrance ( );
    lStatus = ::FdReadRecord( m_Fd_Zartfrance, m_PrimekeyCond_Zartfrance, 
				  			  &m_Buf.zartfrance, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartfrance = m_Buf.zartfrance;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartfrance( cErrmld ) == 0 )
		{
//			m_BufOld.zartfrance = m_Buf.zartfrance;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;
	m_lStatus_Zartfrance = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Zartfrance( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_Zartfrance ( );
	if ( m_lStatus_Zartfrance == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_Zartfrance, &m_Buf.zartfrance, 
					m_PrimekeyCond_Zartfrance, errmld);
	}
	else if ( m_lStatus_Zartfrance == 0 )
	{
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartfrance, &m_Buf.zartfrance,
							 			 &m_BufOld.zartfrance,
										 m_PrimekeyCond_Zartfrance, errmld );
	}
	else
	{
		lStatus = m_lStatus_Zartfrance;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

long CArtikelDoc::DeleteRecord_Zartfrance( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Zartfrance == 100 ) return 0;
	SetPrimekeyCondition_Zartfrance ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartfrance, &m_BufOld.zartfrance, 
				m_PrimekeyCond_Zartfrance, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_Zartfrance( )
{
	char format[50];
	sprintf( format, "ARTICLENO=%c%d.ld", 
		             '%', L_ARTIKEL_NR);
	sprintf( m_PrimekeyCond_Zartfrance, format, 
			 m_Buf.zartfrance.ARTICLENO );
}

/////////////////////////////////////////////////////////////////////////
// carticleext

int CArtikelDoc::InitRecord_Carticleext( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
	nr = m_Buf.carticleext.ARTICLENO;
	FdInitTabBuf( m_Fd_Carticleext, &m_Buf.carticleext );
	m_Buf.carticleext.ARTICLENO = nr;

	return 0;
}

void CArtikelDoc::RestoreBuffer_Carticleext()
{
	m_BufSave.carticleext.ARTICLENO = m_Buf.carticleext.ARTICLENO;
	m_Buf.carticleext = m_BufSave.carticleext;
	m_Buf.carticleext.ARTICLENO = m_BufSave.carticleext.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Carticleext( CString &cErrmld )
{
	char *tabelle = "carticleext";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Carticleext >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Carticleext, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Carticleext = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_Carticleext( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.carticleext.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_Carticleext ( );
	lStatus = ::FdReadRecord( m_Fd_Carticleext, m_PrimekeyCond_Carticleext, 
								&m_Buf.carticleext, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.carticleext = m_Buf.carticleext;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Carticleext( cErrmld ) == 0 )
		{
//			m_BufOld.carticleext = m_Buf.carticleext;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Carticleext = lStatus;

	return lStatus;
}

bool CArtikelDoc::IsCarticleextDefault()
{
	return( m_Buf.carticleext.VINTAGE == 0 && 
			m_Buf.carticleext.ALCOHOLIC_STRENGTH == 0.0 &&
			m_Buf.carticleext.CERTIFICATEFLAG == 0 &&
			m_Buf.carticleext.SHORTEXPIRYFLAG == 0 &&
			m_Buf.carticleext.ANIMALDRUG_PROOFOBLIGATION_FLAG == 0 && 
			m_Buf.carticleext.HIGH_THERAPEUTIC_VALUE == 0 );
}

long CArtikelDoc::StoreRecord_Carticleext( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_Carticleext ( );
	if ( m_lStatus_Carticleext == 100 )
	{
		if (IsCarticleextDefault())
			lStatus = 0; // kein Insert, wenn keine "echten" Werte != default gesetzt sind.
		else
			lStatus = ::FdDelayInsertRecord( m_Fd_Carticleext, &m_Buf.carticleext, 
											 m_PrimekeyCond_Carticleext, errmld);
	}
	else if ( m_lStatus_Carticleext == 0 )
	{
		if (IsCarticleextDefault())
			lStatus = DeleteRecord_Carticleext(cErrmld); // kein Update sondern Delete, wenn keine "echten" Werte != default gesetzt sind.
		else
			lStatus = ::FdDelayUpdateRecord( m_Fd_Carticleext, &m_Buf.carticleext,
										&m_BufOld.carticleext,
										 m_PrimekeyCond_Carticleext, errmld );
	}
	else
	{
		lStatus = m_lStatus_Carticleext;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

long CArtikelDoc::DeleteRecord_Carticleext( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Carticleext == 100 ) return 0;
	SetPrimekeyCondition_Carticleext ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Carticleext, &m_BufOld.carticleext, 
		m_PrimekeyCond_Carticleext, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_Carticleext( )
{
	char format[50];
	sprintf( format, "ARTICLENO=%c%d.ld", 
		             '%', L_ARTIKEL_NR);
	sprintf( m_PrimekeyCond_Carticleext, format, 
				m_Buf.carticleext.ARTICLENO );
}

/////////////////////////////////////////////////////////////////////////
// cartrefundfrance

int CArtikelDoc::InitRecord_Cartrefundfrance( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
	nr = m_Buf.cartrefundfrance.ARTICLENO;
	FdInitTabBuf( m_Fd_Cartrefundfrance, &m_Buf.cartrefundfrance );
	m_Buf.cartrefundfrance.ARTICLENO = nr;

	m_Buf.cartrefundfrance.REIMBURSEMENT_TYPE[0] = '0';

	return 0;
}

void CArtikelDoc::RestoreBuffer_Cartrefundfrance()
{
	m_BufSave.cartrefundfrance.ARTICLENO = m_Buf.cartrefundfrance.ARTICLENO;
	m_Buf.cartrefundfrance = m_BufSave.cartrefundfrance;
	m_Buf.cartrefundfrance.ARTICLENO = m_BufSave.cartrefundfrance.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Cartrefundfrance( CString &cErrmld )
{
	char *tabelle = "cartrefundfrance";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Cartrefundfrance >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Cartrefundfrance, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Cartrefundfrance = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_Cartrefundfrance( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.cartrefundfrance.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_Cartrefundfrance ( );
	lStatus = ::FdReadRecord( m_Fd_Cartrefundfrance, m_PrimekeyCond_Cartrefundfrance, 
								&m_Buf.cartrefundfrance, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.cartrefundfrance = m_Buf.cartrefundfrance;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Cartrefundfrance( cErrmld ) == 0 )
		{
//			m_BufOld.cartrefundfrance = m_Buf.cartrefundfrance;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Cartrefundfrance = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Cartrefundfrance( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_Cartrefundfrance ( );
	if ( m_lStatus_Cartrefundfrance == 100 )
	{
		if (IsCartrefundfranceFilled())
			lStatus = ::FdDelayInsertRecord( m_Fd_Cartrefundfrance, &m_Buf.cartrefundfrance, 
											 m_PrimekeyCond_Cartrefundfrance, errmld);
		else
			lStatus = 0; // kein Insert, wenn keine "echten" Werte != default gesetzt sind.
	}
	else if ( m_lStatus_Cartrefundfrance == 0 )
	{
		if (IsCartrefundfranceFilled())
			lStatus = ::FdDelayUpdateRecord( m_Fd_Cartrefundfrance, &m_Buf.cartrefundfrance,
											&m_BufOld.cartrefundfrance, m_PrimekeyCond_Cartrefundfrance, errmld );
		else
			lStatus = DeleteRecord_Cartrefundfrance(cErrmld); // kein Update sondern Delete, wenn keine "echten" Werte != default gesetzt sind.
	}
	else
	{
		lStatus = m_lStatus_Cartrefundfrance;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_Cartrefundfrance( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( m_lStatus_Cartrefundfrance == 100 ) 
		return 0;

	SetPrimekeyCondition_Cartrefundfrance ( );

	lStatus = ::FdDelayDeleteRecord( m_Fd_Cartrefundfrance, &m_BufOld.cartrefundfrance, 
		m_PrimekeyCond_Cartrefundfrance, errmld );

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_Cartrefundfrance( )
{
	char format[50];
	sprintf( format, "ARTICLENO=%c%d.ld", 
		             '%', L_ARTIKEL_NR);
	sprintf( m_PrimekeyCond_Cartrefundfrance, format, 
				m_Buf.cartrefundfrance.ARTICLENO );
}

bool CArtikelDoc::IsCartrefundfranceFilled()
{
	return( m_Buf.cartrefundfrance.DATEFROM > 0 );
}

/////////////////////////////////////////////////////////////////////////
// zartcroatia (nur Kroatien)

int CArtikelDoc::InitRecord_Zartcroatia( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
    nr = m_Buf.zartcroatia.ARTICLENO;
    FdInitTabBuf( m_Fd_Zartcroatia, &m_Buf.zartcroatia );
    m_Buf.zartcroatia.ARTICLENO = nr;

	m_Buf.zartcroatia.BATCHARTICLE[0]   = '0';

	return 0;
}

void CArtikelDoc::RestoreBuffer_Zartcroatia()
{
    m_BufSave.zartcroatia.ARTICLENO = m_Buf.zartcroatia.ARTICLENO;
    m_Buf.zartcroatia = m_BufSave.zartcroatia;
    m_Buf.zartcroatia.ARTICLENO = m_BufSave.zartcroatia.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Zartcroatia( CString &cErrmld )
{
	char *tabelle = "zartcroatia";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartcroatia >= 0 ) return 0;

//	FillCmpIndikator_Zartcroatia ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartcroatia, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartcroatia = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_Zartcroatia( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.zartcroatia.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_Zartcroatia ( );
	lStatus = ::FdReadRecord( m_Fd_Zartcroatia, m_PrimekeyCond_Zartcroatia, 
				  			  &m_Buf.zartcroatia, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartcroatia = m_Buf.zartcroatia;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartcroatia( cErrmld ) == 0 )
		{
//			m_BufOld.zartcroatia = m_Buf.zartcroatia;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Zartcroatia = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Zartcroatia( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_Zartcroatia ( );
	if ( m_lStatus_Zartcroatia == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_Zartcroatia, &m_Buf.zartcroatia, 
			m_PrimekeyCond_Zartcroatia, errmld);
	}
	else if ( m_lStatus_Zartcroatia == 0 )
	{
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartcroatia, &m_Buf.zartcroatia,
							 			 &m_BufOld.zartcroatia,
										 m_PrimekeyCond_Zartcroatia, errmld );
	}
	else
	{
		lStatus = m_lStatus_Zartcroatia;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

long CArtikelDoc::DeleteRecord_Zartcroatia( CString &cErrmld )
{
	long lStatus;
	char errmld[200];
	if ( m_lStatus_Zartcroatia == 100 ) return 0;
	SetPrimekeyCondition_Zartcroatia ( );
	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartcroatia, &m_BufOld.zartcroatia, 
		m_PrimekeyCond_Zartcroatia, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_Zartcroatia( )
{
	char format[50];
	sprintf( format, "ARTICLENO=%c%d.ld", 
		             '%', L_ARTIKEL_NR);
	sprintf( m_PrimekeyCond_Zartcroatia, format, 
			 m_Buf.zartcroatia.ARTICLENO );
}

/////////////////////////////////////////////////////////////////////////
// CRegisters (nur Bulgarien)

int CArtikelDoc::InitRecord_CRegisters(CString &cErrmld)
{
	if (cErrmld.GetLength()) {}
	char code[26];
	//sprintf(code, m_Buf.cregisters.MINISTRYPRODUCTCODE, 26);
	strcpy(code, m_Buf.cregisters.MINISTRYPRODUCTCODE);


	//code = m_Buf.cregisters.MINISTRYPRODUCTCODE;
	FdInitTabBuf(m_Fd_CRegisters, &m_Buf.cregisters);

	//m_Buf.cregisters.MINISTRYPRODUCTCODE = code;
	strcpy(m_Buf.cregisters.MINISTRYPRODUCTCODE, code);

	return 0;
}

void CArtikelDoc::RestoreBuffer_CRegisters()
{

	strcpy(m_BufSave.cregisters.MINISTRYPRODUCTCODE, m_Buf.cregisters.MINISTRYPRODUCTCODE);
	//m_BufSave.cregisters.ARTICLENO = m_Buf.cregisters.ARTICLENO;
	m_Buf.cregisters = m_BufSave.cregisters;

	strcpy(m_Buf.cregisters.MINISTRYPRODUCTCODE, m_BufSave.cregisters.MINISTRYPRODUCTCODE);
	//m_Buf.cregisters.ARTICLENO = m_BufSave.cregisters.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_CRegisters(CString &cErrmld)
{
	char *tabelle = "cregisters";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if (m_Fd_CRegisters >= 0) return 0;

	//	FillCmpIndikator_CRegisters ( );
	lStatus = ::OpenBufferDesc(&m_Fd_CRegisters, tabelle,
		NULL, NULL, V_PROTOKOL, errmld);
	if (lStatus != 0)
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_CRegisters = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_CRegisters(CString &cErrmld)
{
	long lStatus;
	char errmld[200];
	strcpy(m_Buf.cregisters.MINISTRYPRODUCTCODE, m_Buf.carticlecodes[22].ARTICLE_CODE);
	SetPrimekeyCondition_CRegisters();
	lStatus = ::FdReadRecord(m_Fd_CRegisters, m_PrimekeyCond_CRegisters,
		&m_Buf.cregisters, errmld);
	if (lStatus == 0)
	{
		cErrmld = _T("");
	}
	else if (lStatus == 100)
	{
		if (InitRecord_CRegisters(cErrmld) == 0){}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_CRegisters = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_CRegisters(CString &cErrmld)
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_CRegisters();
	if (m_lStatus_CRegisters == 100)
	{
		lStatus = ::FdDelayInsertRecord(m_Fd_CRegisters, &m_Buf.cregisters,
			m_PrimekeyCond_CRegisters, errmld);
	}
	else if (m_lStatus_CRegisters == 0)
	{
		lStatus = ::FdDelayUpdateRecord(m_Fd_CRegisters, &m_Buf.cregisters,
			&m_BufOld.cregisters,
			m_PrimekeyCond_CRegisters, errmld);
	}
	else
	{
		lStatus = m_lStatus_CRegisters;
		strcpy(errmld, CResString::ex().getStrTblText(IDS_INTER_ERR));
	}

	if (lStatus != 0)
		cErrmld = errmld;
	else
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_CRegisters(CString &cErrmld)
{
	long lStatus;
	char errmld[200];

	if (m_lStatus_CRegisters == 100)
		return 0;

	SetPrimekeyCondition_CRegisters();

	lStatus = ::FdDelayDeleteRecord(m_Fd_CRegisters, &m_BufOld.cregisters,
		m_PrimekeyCond_CRegisters, errmld);

	if (lStatus != 0)
		cErrmld = errmld;
	else
		cErrmld = _T("");

	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_CRegisters()
{
	char format[50];
	sprintf(format, "MINISTRYPRODUCTCODE='%cs'", '%');
	sprintf(m_PrimekeyCond_CRegisters, format,
		m_Buf.cregisters.MINISTRYPRODUCTCODE);
}

/////////////////////////////////////////////////////////////////////////
// CRegistersPrices (nur Bulgarien)

int CArtikelDoc::InitRecord_CRegistersPrices(int i, CString &cErrmld)
{
	if (cErrmld.GetLength()) {}
	char code[26];
	strcpy(code, m_Buf.cregistersprices[i].MINISTRYPRODUCTCODE);
	FdInitTabBuf(m_Fd_CRegistersPrices, &m_Buf.cregistersprices[i]);
	strcpy(m_Buf.cregistersprices[i].MINISTRYPRODUCTCODE, code);
	return 0;
}

void CArtikelDoc::RestoreBuffer_CRegistersPrices(int i)
{
	strcpy(m_BufSave.cregistersprices[i].MINISTRYPRODUCTCODE, m_Buf.cregistersprices[i].MINISTRYPRODUCTCODE);
	m_Buf.cregistersprices[i] = m_BufSave.cregistersprices[i];
	strcpy(m_Buf.cregistersprices[i].MINISTRYPRODUCTCODE, m_BufSave.cregistersprices[i].MINISTRYPRODUCTCODE);
}

int CArtikelDoc::GetBufferDesc_CRegistersPrices(CString &cErrmld)
{
	char *tabelle = "cregistersprices";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if (m_Fd_CRegistersPrices >= 0) return 0;

	lStatus = ::OpenBufferDesc(&m_Fd_CRegistersPrices, tabelle,
		NULL, NULL, V_PROTOKOL, errmld);
	if (lStatus != 0)
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_CRegistersPrices = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_CRegistersPrices(CString &cErrmld)
{
	long lStatus = 0L;
	int fd, i;
	CString sql;
	sql.Format("select first 4 ministryproductcode, datevalidfrom, producerprice, maxwholesaleprice, maxretailprice, referenceprice, datelastchange from cregistersprices where MINISTRYPRODUCTCODE='%s' order by MINISTRYPRODUCTCODE, DATEVALIDFROM desc", m_Buf.carticlecodes[22].ARTICLE_CODE);
	lStatus = ::SqlOpenCs(&fd, sql);
	if (lStatus == 100 || lStatus == 0)
	{
		for (i = 0; i < NUMBER_OF_PRICES_REGISTERS; i++)
		{
			m_Buf.cregistersprices[i].DATEVALIDFROM = 0;
			m_Buf.cregistersprices[i].MAXRETAILPRICE = 0.0;
			m_Buf.cregistersprices[i].MAXWHOLESALEPRICE = 0.0;
			m_Buf.cregistersprices[i].PRODUCERPRICE = 0.0;
			m_Buf.cregistersprices[i].REFERENCEPRICE = 0.0;
			m_Buf.cregistersprices[i].DATELASTCHANGE = 0;
		}
		for (i = 0; i < NUMBER_OF_PRICES_REGISTERS && SqlFetch(fd, 1, &m_Buf.cregistersprices[i], NULL) == 0; i++) {}
	}
	else
		cErrmld = "";

	SqlCloseCs(fd);
	m_lStatus_CRegistersPrices = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_CRegistersPrices(int i, CString &cErrmld)
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_CRegistersPrices(i);
	if (m_lStatus_CRegistersPrices == 100)
	{
		lStatus = ::FdDelayInsertRecord(m_Fd_CRegistersPrices, &m_Buf.cregistersprices[i],
			m_PrimekeyCond_CRegistersPrices, errmld);
	}
	else if (m_lStatus_CRegistersPrices == 0)
	{
		lStatus = ::FdDelayUpdateRecord(m_Fd_CRegistersPrices, &m_Buf.cregistersprices[i],
			&m_BufOld.cregistersprices[i],
			m_PrimekeyCond_CRegistersPrices, errmld);
	}
	else
	{
		lStatus = m_lStatus_CRegistersPrices;
		strcpy(errmld, CResString::ex().getStrTblText(IDS_INTER_ERR));
	}

	if (lStatus != 0)
		cErrmld = errmld;
	else
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_CRegistersPrices(int i, CString &cErrmld)
{
	long lStatus;
	char errmld[200];

	if (m_lStatus_CRegistersPrices == 100)
		return 0;

	SetPrimekeyCondition_CRegistersPrices(i);

	lStatus = ::FdDelayDeleteRecord(m_Fd_CRegistersPrices, &m_BufOld.cregistersprices[i],
		m_PrimekeyCond_CRegistersPrices, errmld);

	if (lStatus != 0)
		cErrmld = errmld;
	else
		cErrmld = _T("");

	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_CRegistersPrices(int i)
{
	// Todo rm
	char format[100];
	sprintf(format, "MINISTRYPRODUCTCODE='%cs' order by MINISTRYPRODUCTCODE, DATEVALIDFROM desc", '%');
	sprintf(m_PrimekeyCond_CRegistersPrices, format,
		m_Buf.cregistersprices[i].MINISTRYPRODUCTCODE);
}


/////////////////////////////////////////////////////////////////////////
// CNhifPrices (nur Bulgarien)

int CArtikelDoc::InitRecord_CNhifPrices(int i, CString &cErrmld)
{
	if (cErrmld.GetLength()) {}
	char code[5];
	strcpy(code, m_Buf.cnhifprices[i].NHIFCODE);
	FdInitTabBuf(m_Fd_CNhifPrices, &m_Buf.cnhifprices);
	strcpy(m_Buf.cnhifprices[i].NHIFCODE, code);
	return 0;
}

void CArtikelDoc::RestoreBuffer_CNhifPrices(int i)
{
	strcpy(m_BufSave.cnhifprices[i].NHIFCODE, m_Buf.cnhifprices[i].NHIFCODE);
	m_Buf.cnhifprices[i] = m_BufSave.cnhifprices[i];
	strcpy(m_Buf.cnhifprices[i].NHIFCODE, m_BufSave.cnhifprices[i].NHIFCODE);
}

int CArtikelDoc::GetBufferDesc_CNhifPrices(CString &cErrmld)
{
	char *tabelle = "cnhifprices";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if (m_Fd_CNhifPrices >= 0) return 0;

	lStatus = ::OpenBufferDesc(&m_Fd_CNhifPrices, tabelle,
		NULL, NULL, V_PROTOKOL, errmld);
	if (lStatus != 0)
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_CNhifPrices = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_CNhifPrices(CString &cErrmld)
{
	long lStatus = 0L;
	int fd;
	CString sql;
	sql.Format("SELECT first 2 nhifcode, datevalidfrom, nhifprice FROM cnhifprices where NHIFCODE='%s' order by NHIFCODE, DATEVALIDFROM desc", m_Buf.zartwg[16].WARENGRUPPE);
	lStatus = ::SqlOpenCs(&fd, sql);
	if (lStatus == 100 || lStatus == 0)
	{
		for (int i = 0; i < NUMBER_OF_PRICES_NHIF; i++)
		{
			m_Buf.cnhifprices[i].DATEVALIDFROM = 0;
			m_Buf.cnhifprices[i].NHIFPRICE = 0.0;
		}
		for (int i = 0; i < NUMBER_OF_PRICES_NHIF && SqlFetch(fd, 1, &m_Buf.cnhifprices[i], NULL) == 0; i++) {}
	}
	else
		cErrmld = "";

	SqlCloseCs(fd);
	m_lStatus_CNhifPrices = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_CNhifPrices(int i, CString &cErrmld)
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_CNhifPrices(i);
	if (m_lStatus_CNhifPrices == 100)
	{
		lStatus = ::FdDelayInsertRecord(m_Fd_CNhifPrices, &m_Buf.cnhifprices[i],
			m_PrimekeyCond_CNhifPrices, errmld);
	}
	else if (m_lStatus_CNhifPrices == 0)
	{
		lStatus = ::FdDelayUpdateRecord(m_Fd_CNhifPrices, &m_Buf.cnhifprices[i],
			&m_BufOld.cnhifprices[i],
			m_PrimekeyCond_CNhifPrices, errmld);
	}
	else
	{
		lStatus = m_lStatus_CNhifPrices;
		strcpy(errmld, CResString::ex().getStrTblText(IDS_INTER_ERR));
	}

	if (lStatus != 0)
		cErrmld = errmld;
	else
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_CNhifPrices(int i, CString &cErrmld)
{
	long lStatus;
	char errmld[200];

	if (m_lStatus_CNhifPrices == 100)
		return 0;

	SetPrimekeyCondition_CNhifPrices(i);

	lStatus = ::FdDelayDeleteRecord(m_Fd_CNhifPrices, &m_BufOld.cnhifprices[i],
		m_PrimekeyCond_CNhifPrices, errmld);

	if (lStatus != 0)
		cErrmld = errmld;
	else
		cErrmld = _T("");

	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_CNhifPrices(int i)
{
	char format[100];
	sprintf(format, "NHIFCODE='%cs' order by NHIFCODE, DATEVALIDFROM desc", '%');
	sprintf(m_PrimekeyCond_CNhifPrices, format,
		m_Buf.cnhifprices[i].NHIFCODE);
}

/////////////////////////////////////////////////////////////////////////
// zartbulgaria (nur Bulgarien)

int CArtikelDoc::InitRecord_Zartbulgaria( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
    nr = m_Buf.zartbulgaria.ARTICLENO;
    FdInitTabBuf( m_Fd_Zartbulgaria, &m_Buf.zartbulgaria );
    m_Buf.zartbulgaria.ARTICLENO = nr;

	return 0;
}

void CArtikelDoc::RestoreBuffer_Zartbulgaria()
{
    m_BufSave.zartbulgaria.ARTICLENO = m_Buf.zartbulgaria.ARTICLENO;
    m_Buf.zartbulgaria = m_BufSave.zartbulgaria;
    m_Buf.zartbulgaria.ARTICLENO = m_BufSave.zartbulgaria.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Zartbulgaria( CString &cErrmld )
{
	char *tabelle = "zartbulgaria";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartbulgaria >= 0 ) return 0;

//	FillCmpIndikator_Zartbulgaria ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartbulgaria, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartbulgaria = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_Zartbulgaria( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.zartbulgaria.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_Zartbulgaria ( );
	lStatus = ::FdReadRecord( m_Fd_Zartbulgaria, m_PrimekeyCond_Zartbulgaria, 
				  			  &m_Buf.zartbulgaria, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartbulgaria = m_Buf.zartbulgaria;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartbulgaria( cErrmld ) == 0 )
		{
//			m_BufOld.zartbulgaria = m_Buf.zartbulgaria;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Zartbulgaria = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Zartbulgaria( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_Zartbulgaria ( );
	if ( m_lStatus_Zartbulgaria == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_Zartbulgaria, &m_Buf.zartbulgaria, 
			m_PrimekeyCond_Zartbulgaria, errmld);
	}
	else if ( m_lStatus_Zartbulgaria == 0 )
	{
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartbulgaria, &m_Buf.zartbulgaria,
							 			 &m_BufOld.zartbulgaria,
										 m_PrimekeyCond_Zartbulgaria, errmld );
	}
	else
	{
		lStatus = m_lStatus_Zartbulgaria;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_Zartbulgaria( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( m_lStatus_Zartbulgaria == 100 ) 
		return 0;

	SetPrimekeyCondition_Zartbulgaria ( );

	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartbulgaria, &m_BufOld.zartbulgaria, 
		m_PrimekeyCond_Zartbulgaria, errmld );

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_Zartbulgaria( )
{
	char format[50];
	sprintf( format, "ARTICLENO=%c%d.ld", 
		             '%', L_ARTIKEL_NR);
	sprintf( m_PrimekeyCond_Zartbulgaria, format, 
			 m_Buf.zartbulgaria.ARTICLENO );
}

/////////////////////////////////////////////////////////////////////////
// zartserbia (nur Serbien)

int CArtikelDoc::InitRecord_Zartserbia( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	long nr;
    nr = m_Buf.zartserbia.ARTICLENO;
    FdInitTabBuf( m_Fd_Zartserbia, &m_Buf.zartserbia );
    m_Buf.zartserbia.ARTICLENO = nr;

	return 0;
}

void CArtikelDoc::RestoreBuffer_Zartserbia()
{
    m_BufSave.zartserbia.ARTICLENO = m_Buf.zartserbia.ARTICLENO;
    m_Buf.zartserbia = m_BufSave.zartserbia;
    m_Buf.zartserbia.ARTICLENO = m_BufSave.zartserbia.ARTICLENO;
}

int CArtikelDoc::GetBufferDesc_Zartserbia( CString &cErrmld )
{
	char *tabelle = "zartserbia";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zartserbia >= 0 ) return 0;

//	FillCmpIndikator_Zartserbia ( );
	lStatus = ::OpenBufferDesc( &m_Fd_Zartserbia, tabelle,
                                NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zartserbia = -1;
		return -1;
	}

	return 0;
}

long CArtikelDoc::ReadRecord_Zartserbia( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	m_Buf.zartserbia.ARTICLENO = m_Buf.zartikel.ARTIKEL_NR;
	SetPrimekeyCondition_Zartserbia ( );
	lStatus = ::FdReadRecord( m_Fd_Zartserbia, m_PrimekeyCond_Zartserbia, 
				  			  &m_Buf.zartserbia, errmld );
	if ( lStatus == 0 )
	{
//		m_BufOld.zartserbia = m_Buf.zartserbia;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord_Zartserbia( cErrmld ) == 0 )
		{
//			m_BufOld.zartserbia = m_Buf.zartserbia;	// initialisierten Satz sichern
		}
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus_Zartserbia = lStatus;
	return lStatus;
}

long CArtikelDoc::StoreRecord_Zartserbia( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition_Zartserbia ( );
	if ( m_lStatus_Zartserbia == 100 )
	{
		lStatus = ::FdDelayInsertRecord( m_Fd_Zartserbia, &m_Buf.zartserbia, 
			m_PrimekeyCond_Zartserbia, errmld);
	}
	else if ( m_lStatus_Zartserbia == 0 )
	{
		lStatus = ::FdDelayUpdateRecord( m_Fd_Zartserbia, &m_Buf.zartserbia,
							 			 &m_BufOld.zartserbia,
										 m_PrimekeyCond_Zartserbia, errmld );
	}
	else
	{
		lStatus = m_lStatus_Zartserbia;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::DeleteRecord_Zartserbia( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( m_lStatus_Zartserbia == 100 ) 
		return 0;

	SetPrimekeyCondition_Zartserbia ( );

	lStatus = ::FdDelayDeleteRecord( m_Fd_Zartserbia, &m_BufOld.zartserbia, 
		m_PrimekeyCond_Zartserbia, errmld );

	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

void CArtikelDoc::SetPrimekeyCondition_Zartserbia( )
{
	char format[50];
	sprintf( format, "ARTICLENO=%c%d.ld", 
		             '%', L_ARTIKEL_NR);
	sprintf( m_PrimekeyCond_Zartserbia, format, 
			 m_Buf.zartserbia.ARTICLENO );
}

int CArtikelDoc::GetUmlaut ( int Sign, char * Conv )
{
	if ( Sign == 196 )
		strcpy ( Conv, "AE" );
	else if ( Sign == 214 )
		strcpy ( Conv, "OE" );
	else if ( Sign == 220 )
		strcpy ( Conv, "UE" );
	else if ( Sign == 228 )
		strcpy ( Conv, "ae" );
	else if ( Sign == 246 )
		strcpy ( Conv, "oe" );
	else if ( Sign == 252 )
		strcpy ( Conv, "ue" );
	else if ( (Sign >= 192 && Sign <= 195) || (Sign >= 197 && Sign <= 198))
	{
		strcpy ( Conv, "A" );
		return 1;
	}
	else if ( Sign == 199 )
	{
		strcpy ( Conv, "C" );
		return 1;
	}
	else if ( Sign >= 200 && Sign <= 203 )
	{
		strcpy ( Conv, "E" );
		return 1;
	}
	else if ( Sign >= 204 && Sign <= 207 )
	{
		strcpy ( Conv, "I" );
		return 1;
	}
	else if ( Sign >= 210 && Sign <= 213 )
	{
		strcpy ( Conv, "O" );
		return 1;
	}
	else if ( Sign >= 217 && Sign <= 219 )
	{
		strcpy ( Conv, "U" );
		return 1;
	}
	else if ( (Sign >= 224 && Sign <= 227) || (Sign >= 229 && Sign <= 230))
	{
		strcpy ( Conv, "a" );
		return 1;
	}
	else if ( Sign == 231 )
	{
		strcpy ( Conv, "c" );
		return 1;
	}
	else if ( Sign >= 232 && Sign <= 235 )
	{
		strcpy ( Conv, "e" );
		return 1;
	}
	else if ( Sign >= 236 && Sign <= 239 )
	{
		strcpy ( Conv, "i" );
		return 1;
	}
	else if ( Sign >= 242 && Sign <= 245 )
	{
		strcpy ( Conv, "o" );
		return 1;
	}
	else if ( Sign >= 249 && Sign <= 251 )
	{
		strcpy ( Conv, "u" );
		return 1;
	}
	else if ( (Sign == 39) || (Sign == 92) )
	{
		strcpy ( Conv, " " );
		return 1;
	}
	else
		return 0;

	return 2;
}

void CArtikelDoc::ConvertUmlaute ( unsigned char *strOrig, char * strConv )
{
	char temp[3];
	int ret;

	int iOrig;
	int iConv = 0;
	
	for ( iOrig = 0; iOrig < (int) strlen ((char *) strOrig); iOrig++ )
	{
		memset ( temp, '\0', 3 );
		
		ret = GetUmlaut ( strOrig[iOrig], temp );

		if ( ret == 2 )
		{		
			strConv[iConv] = temp [0];
			iConv++;
			strConv[iConv] = temp [1];
		}
		else if ( ret == 1 )
		{
			strConv[iConv] = temp [0];
		}
		else
		{
			strConv[iConv] = strOrig[iOrig];
		}
		iConv++;
	}
	strConv[iConv] = '\0';
}

void CArtikelDoc::SaveStati ( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	int i;

	m_lSaveStatus_Zartikel			= m_lStatus_Zartikel;
	m_lSaveStatus_Ean				= m_lStatus_Ean;
	m_lSaveStatus_Artve				= m_lStatus_Artve;
	m_lSaveStatus_Cibt				= m_lStatus_Cibt;
	m_lSaveStatus_Cartforeigncurr	= m_lStatus_Cartforeigncurr;
	m_lSaveStatus_Zartfeb2			= m_lStatus_Zartfeb2;
	m_lSaveStatus_Zartaustria		= m_lStatus_Zartaustria;
	m_lSaveStatus_Zartswitzerland	= m_lStatus_Zartswitzerland;
	m_lSaveStatus_Carticlelang		= m_lStatus_Carticlelang;
	m_lSaveStatus_Zartfrance		= m_lStatus_Zartfrance;
	m_lSaveStatus_Zartcroatia		= m_lStatus_Zartcroatia;
	m_lSaveStatus_Zartbulgaria		= m_lStatus_Zartbulgaria;
	m_lSaveStatus_Zartserbia		= m_lStatus_Zartserbia;
		
	for (i = 0; i < NUMBER_OF_PRICE; i++)
	{
		m_lSaveStatus_Artpreis[i] = m_lStatus_Artpreis[i];
	}

	for (i = 0; i < NUMBER_OF_WGR; i++)
	{
		m_lSaveStatus_Zartwg[i] = m_lStatus_Zartwg[i];
	}

	for (i = 0; i < NUMBER_OF_CODES; i++)
	{
		m_lSaveStatus_Carticlecodes[i] = m_lStatus_Carticlecodes[i];
	}

	return; 
}

void CArtikelDoc::RestoreStati ( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}
	int i;

	m_lStatus_Zartikel			= m_lSaveStatus_Zartikel;
	m_lStatus_Ean				= m_lSaveStatus_Ean;
	m_lStatus_Artve				= m_lSaveStatus_Artve;
	m_lStatus_Cibt				= m_lSaveStatus_Cibt;
	m_lStatus_Cartforeigncurr	= m_lSaveStatus_Cartforeigncurr;
	m_lStatus_Zartfeb2			= m_lSaveStatus_Zartfeb2;
	m_lStatus_Zartaustria		= m_lSaveStatus_Zartaustria;
	m_lStatus_Zartswitzerland	= m_lSaveStatus_Zartswitzerland;
	m_lStatus_Carticlelang		= m_lSaveStatus_Carticlelang;
	m_lStatus_Zartfrance		= m_lSaveStatus_Zartfrance;
	m_lStatus_Zartcroatia		= m_lSaveStatus_Zartcroatia;
	m_lStatus_Zartbulgaria		= m_lSaveStatus_Zartbulgaria;
	m_lStatus_Zartserbia		= m_lSaveStatus_Zartserbia;

	for (i = 0; i < NUMBER_OF_PRICE; i++)
	{
		m_lStatus_Artpreis[i] = m_lSaveStatus_Artpreis[i];
	}

	for (i = 0; i < NUMBER_OF_WGR; i++)
	{
		m_lStatus_Zartwg[i] = m_lSaveStatus_Zartwg[i];
	}

	for (i = 0; i < NUMBER_OF_CODES; i++)
	{
		m_lStatus_Carticlecodes[i] = m_lSaveStatus_Carticlecodes[i];
	}

	return; 
}

void CArtikelDoc::ChangePznInBuffer ( int iPzn, CString &cErrmld )
{
	if (cErrmld.GetLength()) {}

	int i;

	m_Buf.articleno_save = m_Buf.zartikel.ARTIKEL_NR;

	m_Buf.zartikel.ARTIKEL_NR = iPzn;

	m_Buf.zartikel.DATUM_ANLAGE = m_tagesdatum;
	m_Buf.zartikel.DATUM_AENDER = 0;
	strcpy( m_Buf.zartikel.BEARBEITER, m_Anwender );
	strcpy( m_Buf.zartikel.USER_ANLAGE, m_Anwender );
	m_Buf.zartikel.STELLER[0] = 'N';

	// in der Schweiz keine Langnamen übernehmen
	if (IsCountry("CH"))
	{
		memset ( &m_Buf.zartikel.ARTIKEL_LANGNAME[0], ' ', 50);
		memset ( &m_Buf.carticlelang.ARTICLENAMELONG[0], ' ', 50);
	}

	m_Buf.ean.ARTIKEL_NR = iPzn;
	m_Buf.artve.ARTIKEL_NR = iPzn;
	m_Buf.cibt.ARTICLENO = iPzn;
	m_Buf.cartforeigncurr.ARTICLENO = iPzn;
	m_Buf.zartfeb2.ARTIKEL_NR = iPzn;
	m_Buf.zartaustria.ARTIKEL_NR = iPzn;
	m_Buf.zartswitzerland.ARTIKEL_NR = iPzn;
	m_Buf.carticlelang.ARTICLENO = iPzn;
	m_Buf.zartfrance.ARTICLENO = iPzn;
	m_Buf.zartcroatia.ARTICLENO = iPzn;
	m_Buf.carticleext.ARTICLENO = iPzn;
	m_Buf.zartbulgaria.ARTICLENO = iPzn;
	m_Buf.zartserbia.ARTICLENO = iPzn;

	for (i = 0; i < NUMBER_OF_WGR; i++)
	{
		m_Buf.zartwg[i].ARTIKEL_NR = iPzn;
	}

	for (i = 0; i < NUMBER_OF_CODES; i++)
	{
		m_Buf.carticlecodes[i].ARTICLENO = iPzn;
	}

	// nur den zuletzt gültigen Preis übernehmen und mit aktuellem Datum versehen
	m_Buf.artpreis[0] = m_Buf.artpreis[1];
	m_Buf.artpreis[0].ARTIKEL_NR = iPzn;
	m_Buf.artpreis[0].DATUMGUELTIGAB = ::Today();

	for (i = 1; i < NUMBER_OF_PRICE; i++)
	{
		FdInitTabBuf( m_Fd_Artpreis, &m_Buf.artpreis[i] );
	}

}
void CArtikelDoc::InitArticleno_save()
{
	m_Buf.articleno_save = 0;
}

/*
void CArtikelDoc::UpdatePharmosSekbez ( CString cs )
{
	CString sql;
	CString Matchcode;
	CString cErrmld;
	long s;

	// Artikel-Mc generieren
	Matchcode.Format("%s", MakeArtikelMc( cs ) );

	// Versuch, Pharmos-Sekundaerbezeichnung zu lesen 
	char str[51];

	sql.Format("select ARTIKEL_NAME from ZARTSEKBEZ where ARTIKEL_NR=%d and PHARMOS_SEKBEZ='1'", 
				m_Buf.zartikel.ARTIKEL_NR);
	s = SqlRead( sql, str, NULL );

	if (s == 0)
	{
		sql.Format("UPDATE zartsekbez SET artikel_mc = '%s', artikel_name = '%s' "
				   "WHERE ARTIKEL_NR = %d and PHARMOS_SEKBEZ='1'", 
					Matchcode, cs, m_Buf.zartikel.ARTIKEL_NR);

		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		s = SqlExecuteImm( sql );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	}
	else if (s == 100)
	{
		sql.Format("INSERT INTO zartsekbez values ('%s', %d, '%s', '', '1')",
					Matchcode, m_Buf.zartikel.ARTIKEL_NR, cs);

		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		s = SqlExecuteImm( sql );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	}

	if ( s != 0 )
	{
		cErrmld = DynErrmld();
		MsgBoxOK( cErrmld );
	}

	m_Buf.cPharmosSekbez = cs;
}
*/

long CArtikelDoc::GetlStatus ( )
{
	return m_lStatus_Zartikel;
}

bool CArtikelDoc::CheckAutIdemSperre()
{
	long lStatus;
	long datum;
	
	char sql[100];

	sprintf( sql, "select datumgueltigab from zautidemsperre where artikel_nr = %ld",
					m_Buf.zartikel.ARTIKEL_NR);

    lStatus = SqlRead( sql, &datum, NULL );

	if ( lStatus == 0 )
		return true;

	return false;
}

bool CArtikelDoc::CheckLieferNahrungsergänzung()
{
	long lStatus;
	double iCount;
	CString sql;

	sql.Format("SELECT count(*) FROM liefer l join herlief hl on l.lant_nr = hl.lant_nr join herstel h on h.hersteller_nr = hl.hersteller_nr join zartikel z on z.hersteller_nr = l.hersteller_nr where Trim(l.nahrungsergaenzung) in ('N', 'G', 'A') and z.artikel_nr = %ld",
		m_Buf.zartikel.ARTIKEL_NR);

	lStatus = SqlRead(sql, &iCount, NULL);

	if (lStatus != 0 || iCount < 1.0)
		return false;
	else
		return true;
}

bool CArtikelDoc::CheckLieferHatKeinBioZertifikat()
{
	long lStatus;
	double iCount;
	CString sql;

	sql.Format("SELECT count(*) FROM liefer l join herlief hl on l.lant_nr = hl.lant_nr join herstel h on h.hersteller_nr = hl.hersteller_nr join zartikel z on z.hersteller_nr = l.hersteller_nr where l.bio_zertifikat = 0 and Trim(l.nahrungsergaenzung) in ('V', 'B', 'A') and z.artikel_nr = %ld",
		m_Buf.zartikel.ARTIKEL_NR);

	lStatus = SqlRead(sql, &iCount, NULL);

	if (lStatus != 0 || iCount < 1.0)
		return false;
	else
		return true;
}

CString CArtikelDoc::ReadBtmEinheit( )
{	
	char str[10];
	CString sql, Einheit = " ";
	long s;

	sql.Format("select BTM_EINHEIT from ZDKBTM where BTM_GRUPPE='%s'", m_Buf.zartwg[5].WARENGRUPPE);

	s = SqlRead( sql, str, NULL );

	if ( s == 0 )
		Einheit = str;

	return Einheit;
}

double CArtikelDoc::ReadUmrechnungsfaktor( )
{	
	double dFaktor;
	CString sql;
	long s;

	sql.Format("select WAEHRFAKTOR from RFILIALE where FILIALNR = 79");

	s = SqlRead( sql, &dFaktor, NULL );

	if ( s != 0 )
	{
		return -1.0;
	}

	return dFaktor;
}

double CArtikelDoc::ReadUmrechnungsfaktor_Cexchangeratio( )
{	
	double dFaktor;
	CString sql;
	long s;

	sql.Format(
			//	-- Fremdwährung --> Hauswährung
			"select exchangeratevalue / fromfactor * tofactor from cexchangeratio c where "
			"fromcurrencyid = (select currencyid from ccurrency where currencycode = '%s') and "
			"tocurrencyid = (select currencyid from ccurrency where defaultcurrencyflag = 1) and "
			"ratiodate = (select max(ratiodate) from cexchangeratio r where ratiodate <= TODAY and "
			"r.fromcurrencyid = c.fromcurrencyid and r.tocurrencyid = c.tocurrencyid) "
			" UNION "
			//  -- Hauswährung --> Fremdwährung
			"select exchangeratereversevalue / fromfactorreverse * tofactorreverse from cexchangeratio c where "
			"fromcurrencyid = (select currencyid from ccurrency where defaultcurrencyflag = 1) and "
			"tocurrencyid = (select currencyid from ccurrency where currencycode = '%s') and "
			"ratiodate = (select max(ratiodate) from cexchangeratio r where ratiodate <= TODAY and "
			"r.fromcurrencyid = c.fromcurrencyid and r.tocurrencyid = c.tocurrencyid)",
			m_Buf.cartforeigncurr.CURRENCYCODE, m_Buf.cartforeigncurr.CURRENCYCODE);

	s = SqlRead( sql, &dFaktor, NULL );

	if ( s != 0 )
	{
		return -1.0;
	}

	return dFaktor;
}

long CArtikelDoc::CheckArtikelNrHerstExisting()
{
	long lStatus;
	long pzn;
	
	char sql[150];

	sprintf( sql, "select artikel_nr from zartikel where artikel_nr_herst = '%s' "
				  "and artikel_nr != %ld", 
				  m_Buf.zartikel.ARTIKEL_NR_HERST, m_Buf.zartikel.ARTIKEL_NR);

    lStatus = SqlRead( sql, &pzn, NULL );

	if ( lStatus != 0 )
		return 0;

	return pzn;
}

bool CArtikelDoc::CheckCodetypeMayBeCopied( short code_type )
{
	long	lStatus;
	short	artnr_substitute;
	
	char sql[150];

	sprintf( sql, "select artnr_substitute from ccodetypes where code_type = %d ", code_type);

    lStatus = SqlRead( sql, &artnr_substitute, NULL );

	if ( lStatus != 0 )
		return false;

	if (artnr_substitute != 0)
		return false;

	return true;
}

long CArtikelDoc::Shift_Artpreis ( short step, CString& cErrmld)
{
	short posTo		= NUMBER_OF_PRICE - 1;
	short posFrom	= posTo - step;

	while (posFrom >= 0)
	{
		m_Buf.artpreis[posTo]			= m_Buf.artpreis[posFrom];
		m_BufOld.artpreis[posTo]		= m_BufOld.artpreis[posFrom];
		m_lStatus_Artpreis[posTo]		= m_lStatus_Artpreis[posFrom];
		
		posFrom--;
		posTo--;
	}

	while (step > 0)
	{
		step--;
		InitRecord_Artpreis(step, cErrmld);
		m_BufOld.artpreis[step] = m_Buf.artpreis[step];
		m_lStatus_Artpreis[step] = 100;
	}

	return 0;
}

CString CArtikelDoc::GetCalcstorageclassid( )
{	
	char str1[5], str2[5];
	CString sql, Lagerklasse = "";
	short sPrio1, sPrio2, sPrioritaet = 999;
	long s;

	// Schritt 1: Ermittlung Lagerklasse mit der höchsten Priorität auf Basis aller eingetragenen H-Sätze
	sql.Format("select cs.storageclassid, cs.storageclasspriority from cstorageclass cs, chazardnote ch, chazardnote2article ca "
			   "where cs.storageclasspriority = (select min(storageclasspriority) from cstorageclass "
			   "where storageclasspriority > 0 and storageclassid in "
			   "(select storageclassid from chazardnote where hazardnoteid in "
			   "(select hazardnoteid from chazardnote2article where articleno = %ld))) and cs.storageclasspriority > 0 "
			   "and cs.storageclassid = ch.storageclassid and ch.hazardnoteid = ca.hazardnoteid and ca.articleno = %ld", 
			   m_Buf.zartikel.ARTIKEL_NR, m_Buf.zartikel.ARTIKEL_NR);

	s = SqlRead( sql, str1, &sPrio1, NULL );

	if ( s == 0 )
	{
		Lagerklasse = str1;
		sPrioritaet = sPrio1;
	}

	// Schritt 2: Ermittlung Lagerklasse mit der höchsten Priorirät auf Basis UN-Nummer / Gefahrenklasse / Verpackungsgruppe
	sql.Format("select cs.storageclassid, cs.storageclasspriority from cstorageclass cs "
			   "where cs.storageclasspriority = (select min(storageclasspriority) from cstorageclass "
			   "where storageclasspriority > 0 and storageclassid in "
			   "(select storageclassid from cadrstorageclass where "
			   "case when gg_klasse != '' THEN gg_klasse ELSE '%s' END = '%s' and "
			   "case when verpackungsgruppe != '' THEN verpackungsgruppe ELSE '%s' END = '%s' and "
			   "case when g_un_nr != '' THEN g_un_nr ELSE '%s' END = '%s')) ",
			   m_Buf.zartikel.GG_KLASSE, m_Buf.zartikel.GG_KLASSE, m_Buf.zartikel.VERPACKUNGSGRUPPE, m_Buf.zartikel.VERPACKUNGSGRUPPE, 
			   m_Buf.zartikel.G_UN_NR, m_Buf.zartikel.G_UN_NR);

	s = SqlRead( sql, str2, &sPrio2, NULL );
	
	// die Lagerklasse mit der höchsten Priorität (= niedrigere Prio-Nummer) ist die relevante
	if ( s == 0 )
	{
		if (sPrio2 < sPrioritaet)
			Lagerklasse = str2;
	}
	
	// LGK 6.1A/6.1B, 6.1C/6.1D und 8A/B unterscheiden sich nur bzgl. des Kriteriums brennbar J/N
	// da dieses nicht eindeutig geprüft werden kann, wird hier im Zweifelsfall immer die brennbare Klasse vergeben
	// wenn aber die LGK aus dem SDB die nicht brennbare ist, wird das angeglichen, um unnötige Differenzen zu vermeiden

	if ((Lagerklasse == "6.1A" && strncmp (m_Buf.zartikel.G_VCI, "6.1B", L_ZARTIKEL_G_VCI) == 0) ||
		(Lagerklasse == "6.1C" && strncmp (m_Buf.zartikel.G_VCI, "6.1D", L_ZARTIKEL_G_VCI) == 0) ||
		(Lagerklasse == "8A  " && strncmp (m_Buf.zartikel.G_VCI, "8B  ", L_ZARTIKEL_G_VCI) == 0))
		Lagerklasse.Format("%s", m_Buf.zartikel.G_VCI);

	return Lagerklasse;
}

CString CArtikelDoc::ReadAdr2011( )
{	
	char str[10];
	CString sql, Adr2011 = "";
	long s;

	sql.Format("select ADR2011 from CACCDANGERROUTE where G_UN_NR='%s' and VERPACKUNGSGRUPPE = '%s'", m_Buf.zartikel.G_UN_NR, m_Buf.zartikel.VERPACKUNGSGRUPPE);

	s = SqlRead( sql, str, NULL );

	if ( s == 0 )
		Adr2011 = str;

	return Adr2011;
}

struct CHAZARDCLASSIFICATION* CArtikelDoc::GetHazardClassification(long classID, CString classType)
{
	struct CHAZARDCLASSIFICATION* ret = NULL;
	if (m_blnCHazardClassificationLoaded == false)
	{
		m_blnCHazardClassificationLoaded = ReadHazardClassifications(classType);
	}
	int i = 0;
	bool fnd = false;
	while ((i < NUMBER_OF_HAZARDCLASSIFICATIONS) && (fnd == false))
	{
		struct CHAZARDCLASSIFICATION* check = m_pCHazardClassification[i];
		if (check != NULL)
		{
			CString classcode = CString(check->CLASSIFICATION_CODE);
			classcode.Trim();
			if ((classID == check->CLASSIFICATION_ID) && (classcode.CompareNoCase(classType) == 0))
			{
				fnd = true;
				ret = check;
			}
		}
		i++;
	}

	return ret;
}

struct CHAZARDCLASSIFICATION* CArtikelDoc::GetHazardClassification(short index)
{
	struct CHAZARDCLASSIFICATION* ret = NULL;
	if (m_blnCHazardClassificationLoaded == false)
	{
		return ret;
	}
	int i = 0;
	bool fnd = false;
	while ((i < NUMBER_OF_HAZARDCLASSIFICATIONS) && (fnd == false))
	{
		struct CHAZARDCLASSIFICATION* check = m_pCHazardClassification[i];
		if (check != NULL)
		{
			if (i == index)
			{
				fnd = true;
				ret = check;
			}
		}
		i++;
	}

	return ret;
}

bool CArtikelDoc::ReadHazardClassifications(CString classType)
{
	bool ret = true;
	CString sqlQuery = "";
	long sqlStatus = 0;
	int  sqlHandle;
	char sqlErr[1000];

	sqlQuery = "SELECT classification_id, classification_code, designation FROM chazardclassification WHERE classification_code='" + classType + "' ORDER BY classification_id";
	sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
	if (sqlStatus != SQL_SUCCESS)
	{
		strcpy(sqlErr, DynErrmld());
		ret = false;
	}
	else
	{
		int index = 0;
		// make a default
		m_pCHazardClassification[index] = new CHAZARDCLASSIFICATION();
		m_pCHazardClassification[index]->CLASSIFICATION_ID = 0;
		strcpy(m_pCHazardClassification[index]->CLASSIFICATION_CODE, classType);
		strcpy(m_pCHazardClassification[index]->DESIGNATION, "None");
		index++;
		do
		{
			long id = 0;
			char code[11] = { '\0' };
			char desc[201] = { '\0' };
			sqlStatus = SqlFetch(sqlHandle, 1, &id, 
											   &code, 
											   &desc, NULL);
			if (sqlStatus == SQL_SUCCESS)
			{
				m_pCHazardClassification[index] = new CHAZARDCLASSIFICATION();
				m_pCHazardClassification[index]->CLASSIFICATION_ID = id;
				strcpy(m_pCHazardClassification[index]->CLASSIFICATION_CODE, code);
				strcpy(m_pCHazardClassification[index]->DESIGNATION, desc);
				index++;
			}
		}
		while (sqlStatus == SQL_SUCCESS);

		if (sqlStatus < SQL_SUCCESS)
		{
			strcpy(sqlErr, DynErrmld());
			ret = false;
		}
		SqlCloseCs(sqlHandle);
	}
	return ret;
}

struct PREWHOLE_CUSTOMERGROUP* CArtikelDoc::GetMainCustomerGroup(long classID, CString classType)
{
	struct PREWHOLE_CUSTOMERGROUP* ret = NULL;
	if (m_blnPrewholeCustomerGroupLoaded == false)
	{
		m_blnPrewholeCustomerGroupLoaded = ReadMainCustomerGroup(classType);
	}
	int i = 0;
	bool fnd = false;
	while ((i < NUMBER_OF_PREWHOLECUSTOMERGROUP) && (fnd == false))
	{
		struct PREWHOLE_CUSTOMERGROUP* check = m_pPrewholeCustomerGroup[i];
		if (check != NULL)
		{
			CString classcode = CString(check->CUSTOMERGROUP_CODE);
			classcode.Trim();
			if ((classID == check->CUSTOMERGROUP_NO) && (classcode.CompareNoCase(classType) == 0))
			{
				fnd = true;
				ret = check;
			}
		}
		i++;
	}

	return ret;
}

struct PREWHOLE_CUSTOMERGROUP* CArtikelDoc::GetMainCustomerGroup(short index)
{
	struct PREWHOLE_CUSTOMERGROUP* ret = NULL;
	if (m_blnPrewholeCustomerGroupLoaded == false)
	{
		return ret;
	}
	int i = 0;
	bool fnd = false;
	while ((i < NUMBER_OF_PREWHOLECUSTOMERGROUP) && (fnd == false))
	{
		struct PREWHOLE_CUSTOMERGROUP* check = m_pPrewholeCustomerGroup[i];
		if (check != NULL)
		{
			if (i == index)
			{
				fnd = true;
				ret = check;
			}
		}
		i++;
	}

	return ret;
}

bool CArtikelDoc::ReadMainCustomerGroup(CString classType)
{
	bool ret = true;
	CString sqlQuery = "";
	long sqlStatus = 0;
	int  sqlHandle;
	char sqlErr[1000];

	sqlQuery = "SELECT CUSTOMERGROUP_NO, CUSTOMERGROUP_CODE, DESIGNATION FROM PREWHOLE_CUSTOMERGROUP WHERE CUSTOMERGROUP_CODE='" + classType + "' ORDER BY CUSTOMERGROUP_NO";
	sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);
	if (sqlStatus != SQL_SUCCESS)
	{
		strcpy(sqlErr, DynErrmld());
		ret = false;
	}
	else
	{
		int index = 0;
		// make a default
		m_pPrewholeCustomerGroup[index] = new PREWHOLE_CUSTOMERGROUP();
		m_pPrewholeCustomerGroup[index]->CUSTOMERGROUP_NO = 0;
		strcpy(m_pPrewholeCustomerGroup[index]->CUSTOMERGROUP_CODE, classType);
		strcpy(m_pPrewholeCustomerGroup[index]->DESIGNATION, "None");
		index++;
		do
		{
			long id = 0;
			char code[11] = { '\0' };
			char desc[101] = { '\0' };
			sqlStatus = SqlFetch(sqlHandle, 1, &id,
								 &code,
								 &desc, NULL);
			if (sqlStatus == SQL_SUCCESS)
			{
				m_pPrewholeCustomerGroup[index] = new PREWHOLE_CUSTOMERGROUP();
				m_pPrewholeCustomerGroup[index]->CUSTOMERGROUP_NO = id;
				strcpy(m_pPrewholeCustomerGroup[index]->CUSTOMERGROUP_CODE, code);
				strcpy(m_pPrewholeCustomerGroup[index]->DESIGNATION, desc);
				index++;
			}
		} while (sqlStatus == SQL_SUCCESS);

		if (sqlStatus < SQL_SUCCESS)
		{
			strcpy(sqlErr, DynErrmld());
			ret = false;
		}
		SqlCloseCs(sqlHandle);
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////
// prewhole_artcustomergroups

int CArtikelDoc::GetBufferDesc_PrewholeArtCustomerGroups(CString& cErrmld)
{
	char* tabelle = "prewhole_artcustomergroups";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if (m_Fd_PrewholeArtCustomerGroups >= 0)
		return 0;

	lStatus = ::OpenBufferDesc(&m_Fd_PrewholeArtCustomerGroups, tabelle,
							   NULL, NULL, V_PROTOKOL, errmld);
	if (lStatus != 0)
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_PrewholeArtCustomerGroups = -1;
		return -1;
	}
	return 0;
}

int CArtikelDoc::InitRecord_PrewholeArtCustomerGroups(CString& cErrmld)
{
	if (cErrmld.GetLength()) {}
	long nr;
	nr = m_Buf.zartikel.ARTIKEL_NR;
	FdInitTabBuf(m_Fd_PrewholeArtCustomerGroups, &m_PrewholeArtCustomerGroupsBuf);
	m_PrewholeArtCustomerGroupsBuf.ARTICLE_NO = nr;
	return 0;
}

long CArtikelDoc::ReadRecord_PrewholeArtCustomerGroups(CString cErrmld, long customergroup_no)
{
	long lStatus;
	char errmld[200];
	char KeyCond[200];

	if (GetBufferDesc_PrewholeArtCustomerGroups(cErrmld) != 0) return -1;
	
	sprintf(KeyCond, "article_no=%ld and customergroup_no=%ld",
			m_Buf.zartikel.ARTIKEL_NR, customergroup_no);

	lStatus = ::FdReadRecord(m_Fd_PrewholeArtCustomerGroups, KeyCond, &m_PrewholeArtCustomerGroupsBuf, errmld);
	
	if (InitRecord_PrewholeArtCustomerGroups(cErrmld) != 0)
		lStatus = -1;

	if (lStatus != 0) cErrmld = errmld; else cErrmld = _T("");

	m_lStatus_PrewholeArtCustomerGroups = lStatus;
	return lStatus;
}

long CArtikelDoc::DeleteRecord_PrewholeArtCustomerGroups(CString cErrmld, long customergroup_no)
{
	long lStatus;
	char errmld[200];
	char KeyCond[200];

	if (GetBufferDesc_PrewholeArtCustomerGroups(cErrmld) != 0) return -1;

	sprintf(KeyCond, "article_no=%ld and customergroup_no=%ld",
			m_Buf.zartikel.ARTIKEL_NR, customergroup_no);

	m_PrewholeArtCustomerGroupsBuf.CUSTOMERGROUP_NO = customergroup_no;

	lStatus = ::FdDelayDeleteRecord(m_Fd_PrewholeArtCustomerGroups, &m_PrewholeArtCustomerGroupsBuf,
									KeyCond, errmld);

	if (lStatus != 0) cErrmld = errmld; else cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::InsertRecord_PrewholeArtCustomerGroups(CString cErrmld, long customergroup_no)
{
	long lStatus;
	char errmld[200];
	char KeyCond[200];

	if (GetBufferDesc_PrewholeArtCustomerGroups(cErrmld) != 0) return -1;

	sprintf(KeyCond, "article_no=%ld and customergroup_no=%ld",
			m_Buf.zartikel.ARTIKEL_NR, customergroup_no);

	m_PrewholeArtCustomerGroupsBuf.CUSTOMERGROUP_NO = customergroup_no;

	lStatus = ::FdDelayInsertRecord(m_Fd_PrewholeArtCustomerGroups, &m_PrewholeArtCustomerGroupsBuf,
									KeyCond, errmld);

	if (lStatus == 0) cErrmld = _T(""); else cErrmld = errmld;

	return lStatus;
}

CMEDICALACTOR* CArtikelDoc::GetMedicalActor(short index)
{
	if (index >= 0 && index < m_medicalActors.size())
	{
		return m_medicalActors[index];
	}
	return nullptr;
}

void CArtikelDoc::ReadMedicalActor()
{
	CString sqlQuery = "";
	long sqlStatus = 0;
	int  sqlHandle;
	char sqlErr[1000];

	sqlQuery = "SELECT medicalactor_id, medicalactor_type, name FROM cmedicalactor WHERE active = 1 ORDER BY medicalactor_type, medicalactor_id ";

	sqlStatus = SqlOpenCs(&sqlHandle, sqlQuery);

	if (sqlStatus != SQL_SUCCESS)
	{
		strcpy(sqlErr, DynErrmld());
	}
	for (CMEDICALACTOR* actor : m_medicalActors)
	{
		delete actor;
	}
	m_medicalActors.clear();

	// make a default
	CMEDICALACTOR* defaultActor = new CMEDICALACTOR();
	strcpy(defaultActor->MEDICALACTOR_ID, "");
	strcpy(defaultActor->NAME, "");
	defaultActor->MEDICALACTOR_TYPE = 0;
	m_medicalActors.push_back(defaultActor);

	do
	{
		char medicalactor_id[21] = { '\0' };
		short medicalactor_type = 0;
		char name[31] = { '\0' };

		sqlStatus = SqlFetch(sqlHandle, 1, &medicalactor_id, &medicalactor_type, &name, NULL);
		if (sqlStatus == SQL_SUCCESS)
		{
			CMEDICALACTOR* actor = new CMEDICALACTOR();
			strcpy(actor->MEDICALACTOR_ID, medicalactor_id);
			actor->MEDICALACTOR_TYPE = medicalactor_type;
			strcpy(actor->NAME, name);
			m_medicalActors.push_back(actor);
		}
	} while (sqlStatus == SQL_SUCCESS);

	if (sqlStatus < SQL_SUCCESS)
	{
		strcpy(sqlErr, DynErrmld());
	}
	SqlCloseCs(sqlHandle);

}

int CArtikelDoc::GetBufferDesc_CArtMedActor(CString& cErrmld)
{
	char* tabelle = "cartmedactor";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if (m_Fd_CArtMedActor >= 0)
		return 0;

	lStatus = ::OpenBufferDesc(&m_Fd_CArtMedActor, tabelle,
							   NULL, NULL, V_PROTOKOL, errmld);
	if (lStatus != 0)
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_CArtMedActor = -1;
		return -1;
	}
	return 0;
}

int CArtikelDoc::InitRecord_CArtMedActor(CString& cErrmld)
{
	if (cErrmld.GetLength()) {}
	long nr;
	nr = m_Buf.zartikel.ARTIKEL_NR;
	for (short i = 0; i < 4; ++i)
	{
		FdInitTabBuf(m_Fd_CArtMedActor, &m_CArtMedActorBuf[i]);
		m_CArtMedActorBuf[i].ARTICLE_NO = nr;
	}
	return 0;
}

void CArtikelDoc::RestoreBuffer_CArtMedActor()
{
	for (short i = 0; i < 4; ++i)
	{
		m_CArtMedActorBufSave[i].ARTICLE_NO = m_CArtMedActorBuf[i].ARTICLE_NO;
		m_CArtMedActorBuf[i] = m_CArtMedActorBufSave[i];
		m_CArtMedActorBuf[i].ARTICLE_NO = m_CArtMedActorBufSave[i].ARTICLE_NO;
	}	
		Buf_Restored = TRUE;
}

long CArtikelDoc::ReadRecord_CArtMedActor_OneToOne(CString cErrmld, char* medicalactor_id, short medicalactor_type)
{
	long lStatus = 0;
	char errmld[200];
	char KeyCond[200];
	CEkZdpApp* theApp = (CEkZdpApp*)AfxGetApp();
	if (GetBufferDesc_CArtMedActor(cErrmld) != 0) return -1;

	if (m_Buf.articleno_save > 0 && theApp->m_bArtikelKopie)
		sprintf(KeyCond, "article_no=%ld and medicalactor_type=%d",
			m_Buf.articleno_save, medicalactor_type);
	else
		sprintf(KeyCond, "article_no=%ld and medicalactor_type=%d",
			m_Buf.zartikel.ARTIKEL_NR, medicalactor_type);

	if (!Buf_Restored)
	{
		lStatus = ::FdReadRecord(m_Fd_CArtMedActor, KeyCond, &m_CArtMedActorBuf[medicalactor_type], errmld);
	}

	if (lStatus == 0)
	{
		strcpy(medicalactor_id, m_CArtMedActorBuf[medicalactor_type].MEDICALACTOR_ID);
	}

	// Set error message
	if (lStatus != 0) cErrmld = errmld; else cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::ReadRecord_CArtMedActor_OneToN(CString cErrmld, char* medicalactor_id, short medicalactor_type)
{
	long lStatus = 0;
	char errmld[200];
	char KeyCond[200];

	if (GetBufferDesc_CArtMedActor(cErrmld) != 0) return -1;

	sprintf(KeyCond, "article_no=%ld and medicalactor_id='%s' and medicalactor_type=%d",
		m_Buf.zartikel.ARTIKEL_NR, medicalactor_id, medicalactor_type);

	lStatus = ::FdReadRecord(m_Fd_CArtMedActor, KeyCond, &m_CArtMedActorBuf[medicalactor_type], errmld);

	if (InitRecord_CArtMedActor(cErrmld) != 0)
		lStatus = -1;

	// Set error message
	if (lStatus != 0) cErrmld = errmld; else cErrmld = _T("");

	return lStatus;
}

long CArtikelDoc::StoreRecord_CArtMedActor(CString cErrmld, char* medicalactor_id, short medicalactor_type)
{
	long lStatus = 0;
	long lRStatus = 0;
	char errmld[200];
	char KeyCond[200];
	bool idEmpty = (medicalactor_id[0] == '\0' || strspn(medicalactor_id, " ") == strlen(medicalactor_id));

	if (GetBufferDesc_CArtMedActor(cErrmld) != 0) return -1;

	sprintf(KeyCond, "article_no=%ld and medicalactor_type=%d",
			m_Buf.zartikel.ARTIKEL_NR, medicalactor_type);

	sprintf(m_CArtMedActorBuf[medicalactor_type].MEDICALACTOR_ID, "%s ", medicalactor_id);
	m_CArtMedActorBuf[medicalactor_type].MEDICALACTOR_TYPE = medicalactor_type;
	m_CArtMedActorBuf[medicalactor_type].ARTICLE_NO = m_Buf.zartikel.ARTIKEL_NR;

	lRStatus = ::FdReadRecord(m_Fd_CArtMedActor, KeyCond, &m_CArtMedActorBufOld[medicalactor_type], errmld);

	if (idEmpty)
	{
		if (lRStatus == 0) // delete only if entry in table was found
		{
			lStatus = ::FdDelayDeleteRecord(m_Fd_CArtMedActor, &m_CArtMedActorBufOld[medicalactor_type],
											KeyCond, errmld);
		}
	}
	else
	{
		if (lRStatus == 0)
		{
			lStatus = ::FdDelayUpdateRecord(m_Fd_CArtMedActor, &m_CArtMedActorBuf[medicalactor_type],
											&m_CArtMedActorBufOld[medicalactor_type], KeyCond, errmld);
		}
		else if (lRStatus == 100)
		{
			lStatus = ::FdDelayInsertRecord(m_Fd_CArtMedActor, &m_CArtMedActorBuf[medicalactor_type],
											KeyCond, errmld);
		}
		else
		{
			strcpy(errmld, CResString::ex().getStrTblText(IDS_INTER_ERR));
		}
	}
	if (lStatus == 0) cErrmld = _T(""); else cErrmld = errmld;

	return lStatus;
}

long CArtikelDoc::InsertRecord_CArtMedActor(CString cErrmld, char* medicalactor_id, short medicalactor_type)
{
	long lStatus = 0;
	char errmld[200];
	char KeyCond[200];

	if (GetBufferDesc_CArtMedActor(cErrmld) != 0) return -1;

	sprintf(KeyCond, "article_no=%ld and medicalactor_id='%s' and medicalactor_type=%d",
			m_Buf.zartikel.ARTIKEL_NR, medicalactor_id, medicalactor_type);

	strcpy(m_CArtMedActorBuf[medicalactor_type].MEDICALACTOR_ID, medicalactor_id);
	m_CArtMedActorBuf[medicalactor_type].MEDICALACTOR_TYPE = medicalactor_type;

	lStatus = ::FdDelayInsertRecord(m_Fd_CArtMedActor, &m_CArtMedActorBuf[medicalactor_type],
									KeyCond, errmld);

	if (lStatus == 0) cErrmld = _T(""); else cErrmld = errmld;

	return lStatus;
}

long CArtikelDoc::DeleteRecord_CArtMedActor(CString cErrmld, char* medicalactor_id, short medicalactor_type)
{
	long lStatus = 0;
	char errmld[200];
	char KeyCond[200];

	if (GetBufferDesc_CArtMedActor(cErrmld) != 0) return -1;

	sprintf(KeyCond, "article_no=%ld and medicalactor_id='%s' and medicalactor_type=%d",
			m_Buf.zartikel.ARTIKEL_NR, medicalactor_id, medicalactor_type);

	strcpy(m_CArtMedActorBuf[medicalactor_type].MEDICALACTOR_ID, medicalactor_id);
	m_CArtMedActorBuf[medicalactor_type].MEDICALACTOR_TYPE = medicalactor_type;

	lStatus = ::FdDelayDeleteRecord(m_Fd_CArtMedActor, &m_CArtMedActorBuf[medicalactor_type],
									KeyCond, errmld);

	if (lStatus != 0) cErrmld = errmld; else cErrmld = _T("");

	return lStatus;
}