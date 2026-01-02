#ifndef ARTIKELDOC_H_INCLUDE
#define ARTIKELDOC_H_INCLUDE

// ArtikelDoc.h : header file
//

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/zartprei.h>
#include <voodoo_table_header/ean.h>
#include <voodoo_table_header/artve.h>
#include <voodoo_table_header/cartforeigncurr.h>
#include <voodoo_table_header/csafetydatasheet.h>
#include <voodoo_table_header/zartfeb2.h>
#include <voodoo_table_header/zifaart.h>
#include <voodoo_table_header/zifaoart.h>
#include <voodoo_table_header/zartsekb.h>
#include <voodoo_table_header/zapflege.h>
#include <voodoo_table_header/ctransfercsc.h>
#include <voodoo_table_header/zpznpflege.h>
#include <voodoo_table_header/hneuheit.h>
#include <voodoo_table_header/zartaustria.h>
#include <voodoo_table_header/zartswitzerland.h>
#include <voodoo_table_header/carticlelang.h>
#include <voodoo_table_header/cdsoart.h>
#include <voodoo_table_header/zpznpflege.h>
#include <voodoo_table_header/artnrbl.h>
#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/zartfrance.h>
#include <voodoo_table_header/zartcroatia.h>
#include <voodoo_table_header/carticleext.h>
#include <voodoo_table_header/cartrefundfrance.h>
#include <voodoo_table_header/zartbulgaria.h>
#include <voodoo_table_header/zartserbia.h>
#include <voodoo_table_header/nummerek.h>
#include <voodoo_table_header/clioart.h>
#include <voodoo_table_header/chazardnote2article.h>
#include <voodoo_table_header/clppr2article.h>
#include <voodoo_table_header/cibt.h>
#include <voodoo_table_header/cregisters.h>
#include <voodoo_table_header/cregistersprices.h>
#include <voodoo_table_header/cnhifprices.h>
#include <voodoo_table_header/chazardclassification.h>
#include <voodoo_table_header/prewhole_customergroup.h>
#include <voodoo_table_header/prewhole_artcustomergroups.h>
#include <voodoo_table_header/cartmedactor.h>
#include <voodoo_table_header/cmedicalactor.h>
#define NUMBER_OF_WGR   17	// aktuell höchster Wert der art: 'H' (3. Saisonwarengruppe)
							// muss auch im PflartDoc.h angepasst werden
#define NUMBER_OF_PRICE 20	// changed from 4 --> 20 with new subdialog for maintaining prices
#define NUMBER_OF_CODES 26
#define NUMBER_OF_SEKBEZ 20
#define NUMBER_OF_ARTNRBL 20
#define NUMBER_OF_HAZARDNOTES 20
#define NUMBER_OF_LPPRS 20
#define NUMBER_OF_PRICES_REGISTERS 4
#define NUMBER_OF_PRICES_NHIF 2
#define NUMBER_OF_HAZARDCLASSIFICATIONS 100
#define NUMBER_OF_PREWHOLECUSTOMERGROUP 100

struct PFL_ARTIKEL
{
	struct ZARTIKEL			zartikel;
	struct EAN				ean;
	struct ARTVE			artve;
	struct CARTFOREIGNCURR	cartforeigncurr;
	struct CSAFETYDATASHEET	csafetydatasheet;
	struct ZARTFEB2			zartfeb2;
 	struct ZARTPREIS		artpreis[NUMBER_OF_PRICE];
	struct ZARTWG			zartwg[NUMBER_OF_WGR];
	struct ZARTAUSTRIA		zartaustria;
	struct ZARTSWITZERLAND	zartswitzerland;
	struct CARTICLELANG		carticlelang;
	struct CARTICLECODES	carticlecodes[NUMBER_OF_CODES];
	struct ZARTFRANCE		zartfrance;
	struct ZARTCROATIA		zartcroatia;
	struct ZARTBULGARIA		zartbulgaria;
	struct ZARTSERBIA		zartserbia;
	struct CARTICLEEXT		carticleext;
	struct CARTREFUNDFRANCE cartrefundfrance;
	struct CHAZARDNOTE2ARTICLE	chazardnotes[NUMBER_OF_HAZARDNOTES];
	struct CLPPR2ARTICLE	clpprcodes[NUMBER_OF_LPPRS];
	struct CIBT				cibt;
	struct CREGISTERS       cregisters;
	struct CREGISTERSPRICES cregistersprices[NUMBER_OF_PRICES_REGISTERS];
	struct CNHIFPRICES		cnhifprices[NUMBER_OF_PRICES_NHIF];


	CString cPharmosSekbez;	
	long	iVolumen;
	short	sPreistyp;
	long	articleno_save;
};

#define NUM_OF_CSC_TRANSFERS 1

struct CSC_TRANSFER_FIELDS
{
	short fieldType;
	void  *fieldValueNew;
	void  *fieldValueOld;
	char  *fieldName;
};


#include "SVglIfa.h"


#include <eklibs/wdbups/wpp_dbas.h>


class CArtikelDoc
{

	friend class CArtikelDatacare;
	friend class CDepositTypesDoc;

private:
// members
	char   *m_Anwender;
	char   m_PrimekeyCond[100];

// zartikel
	int    m_Fd_Zartikel;
	long   m_lStatus_Zartikel;

//	Indikator
	char   m_CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];

// ean
	int    m_Fd_Ean;
	long   m_lStatus_Ean;

// artve
	int    m_Fd_Artve;
	long   m_lStatus_Artve;

// cibt
	int    m_Fd_Cibt;
	long   m_lStatus_Cibt;
	char   m_PrimekeyCond_Cibt[100];

// cartforeigncurr
	int    m_Fd_Cartforeigncurr;
	long   m_lStatus_Cartforeigncurr;
	char   m_PrimekeyCond_Cartforeigncurr[100];

// csafetydatasheet
	int    m_Fd_CSafetyDataSheet;
	long   m_lStatus_CSafetyDataSheet;
	char   m_PrimekeyCond_CSafetyDataSheet[100];

// chazardclassificiation
	bool   m_blnCHazardClassificationLoaded;
	struct CHAZARDCLASSIFICATION* m_pCHazardClassification[NUMBER_OF_HAZARDCLASSIFICATIONS];

// prewhole_customergroup
	bool   m_blnPrewholeCustomerGroupLoaded;
	struct PREWHOLE_CUSTOMERGROUP* m_pPrewholeCustomerGroup[NUMBER_OF_PREWHOLECUSTOMERGROUP];

// prewhole_artcustomergroups
	int    m_Fd_PrewholeArtCustomerGroups;
	long   m_lStatus_PrewholeArtCustomerGroups;
	struct PREWHOLE_ARTCUSTOMERGROUPS m_PrewholeArtCustomerGroupsBuf;
	
// cartmedactor
	int    m_Fd_CArtMedActor;
	struct CARTMEDACTOR m_CArtMedActorBuf[4];
	struct CARTMEDACTOR m_CArtMedActorBufOld[4];
	struct CARTMEDACTOR m_CArtMedActorBufSave[4];

// zartfeb2
	int    m_Fd_Zartfeb2;
	long   m_lStatus_Zartfeb2;

// zartpreis
	char   m_PrimekeyCond_Artpreis[100];
	int    m_Fd_Artpreis;
	long   m_lStatus_Artpreis[NUMBER_OF_PRICE];

// chazardnote2article
	char   m_PrimekeyCond_HazardNote[100];
	int    m_Fd_HazardNote;
	long   m_lStatus_HazardNote[NUMBER_OF_HAZARDNOTES];

// clppr2article
	char   m_PrimekeyCond_Lppr2Article[100];
	int    m_Fd_Lppr2Article;
	long   m_lStatus_Lppr2Article[NUMBER_OF_LPPRS];

// zartwg
	char   m_PrimekeyCond_Zartwg[100];
	int    m_Fd_Zartwg;
	long   m_lStatus_Zartwg[NUMBER_OF_WGR];

//	gesamt
	struct PFL_ARTIKEL m_Buf;
	struct PFL_ARTIKEL m_BufOld;
	struct PFL_ARTIKEL m_BufSave;

//  sekbez
	char   m_PrimekeyCond_Sekbez[100];
	int    m_Fd_Sekbez;
	int	   m_nNrOfSekbez;
	int	   m_nNewNrOfSekbez;
	int	   m_nMaxNrOfSekbez;
	struct ZARTSEKBEZ m_SekbezBuf[NUMBER_OF_SEKBEZ];
	struct ZARTSEKBEZ m_SekbezBufOld[NUMBER_OF_SEKBEZ];

//  artnrbl
	char   m_PrimekeyCond_Artnrbl[100];
	int    m_Fd_Artnrbl;
	int	   m_nNrOfArtnrbl;
	int	   m_nMaxNrOfArtnrbl;
	struct ARTNRBL m_ArtnrblBuf[NUMBER_OF_ARTNRBL];
	struct ARTNRBL m_ArtnrblBufOld[NUMBER_OF_ARTNRBL];

//	zapflege
	int    m_Fd_Zapflege;
	long   m_lStatus_Zapflege;
	struct ZAPFLEGE m_ZapflegeBuf;

//	ctransfercsc
	int    m_Fd_CTransferCsc;
	struct CTRANSFERCSC m_CTransferCscBuf;

//	zpznpflege
	int    m_Fd_Zpznpflege;
	long   m_lStatus_Zpznpflege;
	struct ZPZNPFLEGE m_ZpznpflegeBuf;

//	zaneuheit
	int    m_Fd_Zaneuheit;
	long   m_lStatus_Zaneuheit;
	struct ZANEUHEIT m_ZaneuheitBuf;

// zartaustria
	int    m_Fd_Zartaustria;
	long   m_lStatus_Zartaustria;

// zartswitzerland
	int    m_Fd_Zartswitzerland;
	long   m_lStatus_Zartswitzerland;

// carticlelang
	char   m_PrimekeyCond_Carticlelang[100];
	int    m_Fd_Carticlelang;
	long   m_lStatus_Carticlelang;

// LogIndex
	int m_Fd_Clioart;
	struct CLIOART	clioart;

// DataSemp
	int m_Fd_Cdsoart;
	struct CDSOART cdsoart;
	
// Nummerek
	int m_Fd_Nummerek;
	struct NUMMEREK nummerek;
	struct NUMMEREK nummerek_old;
	
// carticlecodes
	char   m_PrimekeyCond_Carticlecodes[100];
	int    m_Fd_Carticlecodes;
	long   m_lStatus_Carticlecodes[NUMBER_OF_CODES];
	BOOL   m_bCarticlecodes_changed;

// zartfrance
	char   m_PrimekeyCond_Zartfrance[100];
	int    m_Fd_Zartfrance;
	long   m_lStatus_Zartfrance;

// zartcroatia
	char   m_PrimekeyCond_Zartcroatia[100];
	int    m_Fd_Zartcroatia;
	long   m_lStatus_Zartcroatia;

// carticleext
	char   m_PrimekeyCond_Carticleext[100];
	int    m_Fd_Carticleext;
	long   m_lStatus_Carticleext;

// cartrefundfrance
	char   m_PrimekeyCond_Cartrefundfrance[100];
	int    m_Fd_Cartrefundfrance;
	long   m_lStatus_Cartrefundfrance;

// zartbulgaria
	char   m_PrimekeyCond_Zartbulgaria[100];
	int    m_Fd_Zartbulgaria;
	long   m_lStatus_Zartbulgaria;

// cregisters
	char   m_PrimekeyCond_CRegisters[100];
	int    m_Fd_CRegisters;
	long   m_lStatus_CRegisters;

// cregistersprices
	char   m_PrimekeyCond_CRegistersPrices[100];
	int    m_Fd_CRegistersPrices;
	long   m_lStatus_CRegistersPrices;

// cnhif
	char   m_PrimekeyCond_CNhifPrices[100];
	int    m_Fd_CNhifPrices;
	long   m_lStatus_CNhifPrices;

// zartserbia
	char   m_PrimekeyCond_Zartserbia[100];
	int    m_Fd_Zartserbia;
	long   m_lStatus_Zartserbia;

// Status-Sicher-Felder
	long   m_lSaveStatus_Zartikel;
	long   m_lSaveStatus_Ean;
	long   m_lSaveStatus_Artve;
	long   m_lSaveStatus_Cibt;
	long   m_lSaveStatus_Cartforeigncurr;
	long   m_lSaveStatus_Zartfeb2;
	long   m_lSaveStatus_Artpreis[NUMBER_OF_PRICE];
	long   m_lSaveStatus_HazardNote[NUMBER_OF_HAZARDNOTES];
	long   m_lSaveStatus_Lppr2Article[NUMBER_OF_LPPRS];
	long   m_lSaveStatus_Zartwg[NUMBER_OF_WGR];
	long   m_lSaveStatus_Carticlecodes[NUMBER_OF_CODES];
	long   m_lSaveStatus_Zartaustria;
	long   m_lSaveStatus_Zartswitzerland;
	long   m_lSaveStatus_Carticlelang;
	long   m_lSaveStatus_Zartfrance;
	long   m_lSaveStatus_Zartcroatia;
	long   m_lSaveStatus_Zartbulgaria;
	long   m_lSaveStatus_Zartserbia;

//   Tagesdatum
	long 	m_tagesdatum;

public:	  
	CArtikelDoc();           // protected constructor used by dynamic creation

// Operations
public:

	struct PFL_ARTIKEL* GetBuffer();
	struct PFL_ARTIKEL* GetOldBuffer();

	struct CDSOART*		GetDsOArt();
	struct NUMMEREK*	GetNummerek();
	struct CLIOART*		GetClioart();
	std::vector<CMEDICALACTOR*> m_medicalActors;
	bool Buf_Restored = FALSE;

	// record read write delete
private:
	int  GetBufferDesc( CString &cErrmld );

public:
	void CleanupMemory();
	void FreeBufferDesc( );
	long ReadRecord  ( CString& cErrmld );
	long ReadCDsOArt ( CString& cErrmld );
	long ReadClioart  ( CString& cErrmld );
	long ReadClioart  ( long articleNo, CString& cErrmld );

	long ReadNummerek( CString& cErrmld );
	long StoreNummerek( CString& cErrmld );
	void SetNummerekUpdate( BOOL bSet ); 
	BOOL GetNummerekUpdate( ); 

	long DeleteRecord( CString& cErrmld );
	long StoreRecord ( CString& cErrmld, const CString code );
	int  InitRecord  ( CString& cErrmld );

	void SaveStati   ( CString& cErrmld );
	void RestoreStati( CString& cErrmld );
	void ChangePznInBuffer( int iPzn, CString& cErrmld );
	void InitArticleno_save();
	void InitPflegeDesc( char* Anwender );
	void StoreBuffer();
	void RestoreBuffer();
	void RestoreBuffer_CArtMedActor();

	long StoreRecordWithoutTransact( CString &cErrmld, const CString code = "" );

	void SetTagesdatum( long datum );
//	void UpdatePharmosSekbez( CString cs );

private:
	void SetPrimekeyCondition( );

	// zartikel
	int  GetBufferDesc_Zartikel( CString &cErrmld );
	int  InitRecord_Zartikel   ( CString &cErrmld ); 
	long ReadRecord_Zartikel   ( CString& cErrmld );
	long DeleteRecord_Zartikel ( CString& cErrmld );
	long StoreRecord_Zartikel  ( CString& cErrmld );
	void RestoreBuffer_Zartikel();
	void FillCmpIndikator_Zartikel();

	// ean
	int  GetBufferDesc_Ean ( CString &cErrmld );
	int  InitRecord_Ean    ( CString &cErrmld );
	long ReadRecord_Ean    ( CString& cErrmld );
	long DeleteRecord_Ean  ( CString& cErrmld );
	long StoreRecord_Ean   ( CString& cErrmld );
	void RestoreBuffer_Ean ( );
	bool IsToDelete_Ean( );
	int  IsRecordModified_Ean ( CString &cErrmld );
	int  DoesEanAlreadyExist ( CString &cErrmld );

	// artve
	int  GetBufferDesc_Artve	( CString &cErrmld );
	int  InitRecord_Artve		( CString &cErrmld );
	long ReadRecord_Artve		( CString& cErrmld );
	int  IsRecordModified_Artve ( CString &cErrmld );
/*	long DeleteRecord_Artve		( CString& cErrmld ); <-- wird momentan höchstens neu angelegt */
	long StoreRecord_Artve		( CString& cErrmld );
	void RestoreBuffer_Artve	( );

	// cibt
	int  GetBufferDesc_Cibt			( CString &cErrmld );
	int  InitRecord_Cibt			( CString &cErrmld );
	long ReadRecord_Cibt			( CString& cErrmld );
	int  IsRecordModified_Cibt		( CString &cErrmld );
	long StoreRecord_Cibt			( CString& cErrmld );
	void RestoreBuffer_Cibt			( );
	void SetPrimekeyCondition_Cibt	( );

	// cartforeigncurr
	int  GetBufferDesc_Cartforeigncurr ( CString &cErrmld );
	int  InitRecord_Cartforeigncurr    ( CString &cErrmld );
	long ReadRecord_Cartforeigncurr    ( CString& cErrmld );
	long DeleteRecord_Cartforeigncurr  ( CString& cErrmld );
	long StoreRecord_Cartforeigncurr   ( CString& cErrmld );
	void RestoreBuffer_Cartforeigncurr ( );
	void SetPrimekeyCondition_Cartforeigncurr	( );
	bool IsToDelete_Cartforeigncurr( );
	int  IsRecordModified_Cartforeigncurr ( CString &cErrmld );

	// csafetydatasheet
	int  GetBufferDesc_CSafetyDataSheet ( CString &cErrmld );
	int  InitRecord_CSafetyDataSheet    ( CString &cErrmld );
	long ReadRecord_CSafetyDataSheet    ( CString& cErrmld );
	long DeleteRecord_CSafetyDataSheet  ( CString& cErrmld );
	long StoreRecord_CSafetyDataSheet   ( CString& cErrmld );
	void RestoreBuffer_CSafetyDataSheet ( );
	void SetPrimekeyCondition_CSafetyDataSheet	( );
	int  IsRecordModified_CSafetyDataSheet ( CString &cErrmld );
	bool AreGhsArticleDataModified ( CString &cErrmld );

	// zartfeb2
	int  GetBufferDesc_Zartfeb2 ( CString &cErrmld );
	int  InitRecord_Zartfeb2    ( CString &cErrmld );
	long ReadRecord_Zartfeb2    ( CString& cErrmld );
	long DeleteRecord_Zartfeb2  ( CString& cErrmld );
	long StoreRecord_Zartfeb2   ( CString& cErrmld );
	void RestoreBuffer_Zartfeb2 ( );
	bool IsToDelete_Zartfeb2( );

	// artpreis
	int  GetBufferDesc_Artpreis ( CString &cErrmld );
	int  InitRecord_Artpreis    ( int i, CString &cErrmld );

	// public wg. erneutem Lesen der Preise nach Änderung Preistyp
public:
	long ReadRecord_Artpreis    ( CString& cErrmld );
	long Shift_Artpreis			( short step, CString& cErrmld);

private:
	long DeleteRecord_Artpreis  ( int i, CString& cErrmld );
	long StoreRecord_Artpreis   ( int i, CString &cErrmld, long *datum );
	void RestoreBuffer_Artpreis ( int i );
	void SetPrimekeyCondition_Artpreis( int i );
	void SetPrimekeyCondition_OldArtpreis( int i );
	bool IsToDelete_Artpreis( int i );
	int  IsRecordModified_Artpreis( CString &cErrmld );
	int  IsSingleRecordModified_Artpreis( int i, char *errmld );

	// zartwg
	int  GetBufferDesc_Zartwg ( CString &cErrmld );
	int  InitRecord_Zartwg    ( int i, CString &cErrmld );
	long ReadRecord_Zartwg    ( int i, CString& cErrmld );
	long DeleteRecord_Zartwg  ( int i, CString& cErrmld );
	long StoreRecord_Zartwg   ( int i, CString& cErrmld );
	void RestoreBuffer_Zartwg ( int i );
	void SetPrimekeyCondition_Zartwg( int i );
	bool IsToDelete_Zartwg( int i );

	// sekbez
	int  GetBufferDesc_Sekbez   ( CString &cErrmld );
	int  InitRecord_Sekbez      ( int i, CString &cErrmld );
	long DeleteRecord_Sekbez    ( CString& cErrmld );
	long StoreRecord_Sekbez     ( CString& cErrmld );
	int  IsRecordModified_Sekbez( );
	void SetPrimekeyCondition_Sekbez( int i );
	void SetPrimekeyCondition_OldSekbez( int i );

	// artnrbl
	int  GetBufferDesc_Artnrbl   ( CString &cErrmld );
	long ReadRecord_Artnrbl		 ( CString& cErrmld );
	long DeleteRecord_Artnrbl    ( CString& cErrmld );
	long StoreRecord_Artnrbl     ( CString& cErrmld );
	void SetPrimekeyCondition_Artnrbl( int i );

	// Zapflege
	int  GetBufferDesc_Zapflege( CString &cErrmld );
	long StoreRecord_Zapflege( long datum, CString &cErrmld );

	// CTransferCsc
	int  GetBufferDesc_CTransferCsc( CString &cErrmld );
	long StoreRecord_CTransferCsc( CString &cErrmld );

	struct CSC_TRANSFER_FIELDS m_CscTransfers[NUM_OF_CSC_TRANSFERS];

public: // public wegen Aufrufen aus PflartDoc
	void FillCTransferCscFields(struct ZARTIKEL * bufArtikelNew, struct ZARTIKEL * bufArtikelOld);
	long TransferDataToCsc( long articleNo, CString &cErrmld );

private:
	// Zpznpflege
	int GetBufferDesc_Zpznpflege( CString &cErrmld );
	long StoreRecord_Zpznpflege ( long datum, CString dezap_sa, CString &cErrmld );

	// Zaneuheit
	int  GetBufferDesc_Zaneuheit( CString &cErrmld );
	long StoreRecord_Zaneuheit  ( char programm, CString &cErrmld );
	long DeleteRecord_Zaneuheit ( char programm, CString &cErrmld );

	// zartaustria
	int  GetBufferDesc_Zartaustria ( CString &cErrmld );
	int  InitRecord_Zartaustria    ( CString &cErrmld );
	long ReadRecord_Zartaustria    ( CString& cErrmld );
	long DeleteRecord_Zartaustria  ( CString& cErrmld );
	long StoreRecord_Zartaustria   ( CString& cErrmld );
	void RestoreBuffer_Zartaustria ( );
//	bool IsToDelete_Zartaustria( );

	// zartswitzerland
	int  GetBufferDesc_Zartswitzerland ( CString &cErrmld );
	int  InitRecord_Zartswitzerland    ( CString &cErrmld );
	long ReadRecord_Zartswitzerland    ( CString& cErrmld );
	long DeleteRecord_Zartswitzerland  ( CString& cErrmld );
	long StoreRecord_Zartswitzerland   ( CString& cErrmld );
	void RestoreBuffer_Zartswitzerland ( );

	// carticlelang
	int  GetBufferDesc_Carticlelang			( CString &cErrmld );
	int  InitRecord_Carticlelang			( CString &cErrmld );
	long ReadRecord_Carticlelang			( CString& cErrmld );
	long DeleteRecord_Carticlelang			( CString& cErrmld );
	long StoreRecord_Carticlelang			( CString& cErrmld );
	void RestoreBuffer_Carticlelang			( );
	void SetPrimekeyCondition_Carticlelang	( );

	// carticletext
	int  GetBufferDesc_Carticletext			( CString &cErrmld );
	int  InitRecord_Carticletext			( CString &cErrmld );
	long ReadRecord_Carticletext			( CString& cErrmld );
	long DeleteRecord_Carticletext			( CString& cErrmld );
	long StoreRecord_Carticletext			( CString& cErrmld );
	void RestoreBuffer_Carticletext			( );
	void SetPrimekeyCondition_Carticletext	( );

	// Galdat + DataSemp + Nummerek
	int GetBufferDesc_Cdsoart				( CString &cErrmld );
	int GetBufferDesc_Nummerek				( CString &cErrmld );
	int GetBufferDesc_Clioart				( CString &cErrmld );

	// carticlecodes
	int  GetBufferDesc_Carticlecodes ( CString &cErrmld );
	int  InitRecord_Carticlecodes    ( int i, CString &cErrmld );
	long ReadRecord_Carticlecodes    ( short i, CString& cErrmld );
	long DeleteRecord_Carticlecodes  ( int i, CString& cErrmld );
	long StoreRecord_Carticlecodes   ( int i, CString& cErrmld );
	void RestoreBuffer_Carticlecodes ( int i );
	void SetPrimekeyCondition_Carticlecodes( int i );
	bool IsToDelete_Carticlecodes( int i );

	// chazardnote2article
public:
	long ReadRecord_chazardnote2article    ( CString& cErrmld );
	long DeleteRecord_chazardnote2article  ( CString& cErrmld );
	long StoreRecord_chazardnote2article   ( CString& cErrmld );
	void SetHazardNoteIdToProcess		   ( char * hazardNoteId );

private:
	int  GetBufferDesc_chazardnote2article ( CString &cErrmld );
	int  InitRecord_chazardnote2article    ( int i, CString &cErrmld );
	void SetPrimekeyCondition_chazardnote2article();

	// clppr2article
public:
	long ReadRecord_clppr2article    ( CString& cErrmld );
	long DeleteRecord_clppr2article  ( int i, CString& cErrmld );
	long StoreRecord_clppr2article   ( int i, CString& cErrmld );
	double Read_LpprReimbValueSum	 ( long datefrom );
	
private:
	int  GetBufferDesc_clppr2article ( CString &cErrmld );
	int  InitRecord_clppr2article    ( int i, CString &cErrmld );
	void SetPrimekeyCondition_clppr2article( int i);

	// zartfrance
	int  GetBufferDesc_Zartfrance ( CString &cErrmld );
	int  InitRecord_Zartfrance    ( CString &cErrmld );
	long ReadRecord_Zartfrance    ( CString& cErrmld );
	long DeleteRecord_Zartfrance  ( CString& cErrmld );
	long StoreRecord_Zartfrance   ( CString& cErrmld );
	void RestoreBuffer_Zartfrance ( );
	void SetPrimekeyCondition_Zartfrance	( );
//	bool IsToDelete_Zartfrance( );

	// zartcroatia
	int  GetBufferDesc_Zartcroatia ( CString &cErrmld );
	int  InitRecord_Zartcroatia    ( CString &cErrmld );
	long ReadRecord_Zartcroatia    ( CString& cErrmld );
	long DeleteRecord_Zartcroatia  ( CString& cErrmld );
	long StoreRecord_Zartcroatia   ( CString& cErrmld );
	void RestoreBuffer_Zartcroatia ( );
	void SetPrimekeyCondition_Zartcroatia ( );

	// carticleext
	int  GetBufferDesc_Carticleext ( CString &cErrmld );
	int  InitRecord_Carticleext    ( CString &cErrmld );
	long ReadRecord_Carticleext    ( CString& cErrmld );
	long DeleteRecord_Carticleext  ( CString& cErrmld );
	long StoreRecord_Carticleext   ( CString& cErrmld );
	void RestoreBuffer_Carticleext ( );
	void SetPrimekeyCondition_Carticleext ( );
	bool IsCarticleextDefault	   ( );

	// cartrefundfrance
	int  GetBufferDesc_Cartrefundfrance			( CString &cErrmld );
	int  InitRecord_Cartrefundfrance			( CString &cErrmld );
	long ReadRecord_Cartrefundfrance			( CString& cErrmld );
	long DeleteRecord_Cartrefundfrance			( CString& cErrmld );
	long StoreRecord_Cartrefundfrance			( CString& cErrmld );
	void RestoreBuffer_Cartrefundfrance			( );
	void SetPrimekeyCondition_Cartrefundfrance	( );
	bool IsCartrefundfranceFilled				( );

	// zartbulgaria
	int  GetBufferDesc_Zartbulgaria ( CString &cErrmld );
	int  InitRecord_Zartbulgaria    ( CString &cErrmld );
	long ReadRecord_Zartbulgaria    ( CString& cErrmld );
	long DeleteRecord_Zartbulgaria  ( CString& cErrmld );
	long StoreRecord_Zartbulgaria   ( CString& cErrmld );
	void RestoreBuffer_Zartbulgaria ( );
	void SetPrimekeyCondition_Zartbulgaria ( );

	// CRegisters
	int  GetBufferDesc_CRegisters(CString &cErrmld);
	int  InitRecord_CRegisters(CString &cErrmld);
	long ReadRecord_CRegisters(CString& cErrmld);
	long DeleteRecord_CRegisters(CString& cErrmld);
	long StoreRecord_CRegisters(CString& cErrmld);
	void RestoreBuffer_CRegisters();
	void SetPrimekeyCondition_CRegisters();

	// CRegistersPrices
	int  GetBufferDesc_CRegistersPrices(CString &cErrmld);
	int  InitRecord_CRegistersPrices(int i, CString &cErrmld);
	long ReadRecord_CRegistersPrices(CString& cErrmld);
	long DeleteRecord_CRegistersPrices(int i, CString& cErrmld);
	long StoreRecord_CRegistersPrices(int i, CString& cErrmld);
	void RestoreBuffer_CRegistersPrices(int i);
	void SetPrimekeyCondition_CRegistersPrices(int i);

	// CNhif
	int  GetBufferDesc_CNhifPrices(CString &cErrmld);
	int  InitRecord_CNhifPrices(int i, CString &cErrmld);
	long ReadRecord_CNhifPrices(CString& cErrmld);
	long DeleteRecord_CNhifPrices(int i, CString& cErrmld);
	long StoreRecord_CNhifPrices(int i, CString& cErrmld);
	void RestoreBuffer_CNhifPrices(int i);
	void SetPrimekeyCondition_CNhifPrices(int i);

	// zartserbia
	int  GetBufferDesc_Zartserbia ( CString &cErrmld );
	int  InitRecord_Zartserbia    ( CString &cErrmld );
	long ReadRecord_Zartserbia    ( CString& cErrmld );
	long DeleteRecord_Zartserbia  ( CString& cErrmld );
	long StoreRecord_Zartserbia   ( CString& cErrmld );
	void RestoreBuffer_Zartserbia ( );
	void SetPrimekeyCondition_Zartserbia ( );

	// prewhole_artcustomergroups
	int  GetBufferDesc_PrewholeArtCustomerGroups(CString& cErrmld);
	// cartmedactor
	int  GetBufferDesc_CArtMedActor(CString& cErrmld);

public:
	struct ZARTSEKBEZ* CArtikelDoc::GetSekbezBuffer();
	int		GetNrOfSekbez( );
	void	SetNewNrOfSekbez( int nNewNr );
	long	ReadRecord_Sekbez ( CString& cErrmld );
	bool	CheckAutIdemSperre();
	bool	CheckLieferNahrungsergänzung();
	bool	CheckLieferHatKeinBioZertifikat();
	CString ReadBtmEinheit();
	double  ReadUmrechnungsfaktor();
	double  ReadUmrechnungsfaktor_Cexchangeratio();
	long	CheckArtikelNrHerstExisting();
	const bool IsHealthInsuranceArticle( );
	CString GetCalcstorageclassid();
	CString ReadAdr2011();
	struct CHAZARDCLASSIFICATION* GetHazardClassification(long classID, CString classType);
	struct CHAZARDCLASSIFICATION* GetHazardClassification(short index);
	struct PREWHOLE_CUSTOMERGROUP* GetMainCustomerGroup(long classID, CString classType);
	struct PREWHOLE_CUSTOMERGROUP* GetMainCustomerGroup(short index);
	void ReadMedicalActor();
	struct CMEDICALACTOR* GetMedicalActor(short index);
	
	// prewhole_artcustomergroups
	int  InitRecord_PrewholeArtCustomerGroups(CString& cErrmld);
	long ReadRecord_PrewholeArtCustomerGroups(CString cErrmld, long customergroup_no);
	long DeleteRecord_PrewholeArtCustomerGroups(CString cErrmld, long customergroup_no);
	long InsertRecord_PrewholeArtCustomerGroups(CString cErrmld, long customergroup_no);

	// cartmedactor
	long StoreRecord_CArtMedActor(CString cErrmld, char* medicalactor_id, short medicalactor_type);
	long ReadRecord_CArtMedActor_OneToOne(CString cErrmld, char* medicalactor_id, short medicalactor_type);
	long ReadRecord_CArtMedActor_OneToN(CString cErrmld, char* medicalactor_id, short medicalactor_type);
	int  InitRecord_CArtMedActor(CString& cErrmld);
	long InsertRecord_CArtMedActor(CString cErrmld, char* medicalactor_id, short medicalactor_type);
	long DeleteRecord_CArtMedActor(CString cErrmld, char* medicalactor_id, short medicalactor_type);

private:
	void ReadPharmosSekbez(  );
	bool CheckCodetypeMayBeCopied( short code_type );
	bool ReadHazardClassifications(CString classType);
	bool ReadMainCustomerGroup(CString classType);

private:
	// nicht immer
	void FillCmpIndikator( );
	int  IsRecordModified( CString &cErrmld );

	/////////////////////////////////
	// Ifa
private:
	struct PFL_ARTIKEL m_BufIfaTest;

	struct ZIFAART m_IfaBuf;
	struct ZIFAART m_IfaBufOld;
	int    m_Fd_Ifa;
	long   m_lStatus_Ifa;
	BOOL   m_bIfaPflege;	
	char   m_PrimekeyCondIfa[40];

	void   SetPrimekeyCondition_Ifa ( );
	int    GetBufferDesc_Ifa( CString &cErrmld );
	long   StoreRecord_Ifa  ( CString& cErrmld );

	BOOL   m_bNummerekUpdate;	
	long   m_lStatus_Nummerek;

	struct ZARTIKEL m_PhzaltBuf;
	struct ZARTIKEL m_PhzaltBufOld;
	long   m_lStatus_Phzalt;
	char   m_PrimekeyCond_PhzAlt[30];

	void   SetPrimekeyCondition_PhzAlt ( );
	long   StoreRecord_Zartikel_PhzAlt( CString &cErrmld );

	void   IfaToArtikelIntern( struct PFL_ARTIKEL *Buf, bool bArtikelVorhanden );
	void   MakePreisAusHerstProz( double herst_proz, 
								  double *grosso, double *aep );

	enum 
	{
		WERT_LONG,
		WERT_DOUBLE,
		WERT_CHAR,
		WERT_DATUM,
		WERT_YESNO,
		WERT_COMBO,
		WERT_PZNALT,
		WERT_PREIS
	};

	enum { L_VGL_IFA = 40 };
	struct VGL_IFA vgi[ L_VGL_IFA + 1 ]; 

	struct ZIFAOART m_IfaOartBuf;
	int    m_Fd_IfaOart;
	char   m_PrimekeyCondIfaOart[40];

	void   SetPrimekeyCondition_IfaOart ( );
	int    GetBufferDesc_IfaOart( CString &cErrmld );
	
public:
	struct ZIFAOART* GetIfaOartBuffer();
	long   ReadRecord_IfaOart( long articleNo, CString& cErrmld );
	
	struct ZIFAART* GetIfaBuffer();
	long   ReadRecord_Ifa( long IfaNr, long SatzNr, CString& cErrmld );
	long   ReadRecord_Zartikel_PhzAlt( long PhzAlt, CString &cErrmld );
	int	   IfaToArtikel( CString &cErrmld );
//	void   IfaToTestArtikel( );
	BOOL   CompareArtikelWithIfa( );
	void   SetIfaPflege( BOOL bSet ); 
	void   UpdateArtikelWithIfa( );
	long   DatumIfaToPho( char *str );
	double PreisIfaToPreis( char *str );

	struct VGL_IFA* GetVglIfaBuffer();
	long ReadGTIN(long artikelnummer);
	long ReadNTIN(long artikelnummer);

// Implementation
public: 
	virtual ~CArtikelDoc();

	void ConvertUmlaute( unsigned char *strOrig, char * strConv );
	int  GetUmlaut ( int Sign, char * Conv );
	long  GetlStatus ( );

};

/////////////////////////////////////////////////////////////////////////////
//

#endif // ARTIKELDOC_H_INCLUDE