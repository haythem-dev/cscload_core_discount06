#ifndef ARTNAMEDOC_H_INCLUDE
#define ARTNAMEDOC_H_INCLUDE

// ArtnameDoc.h : header file
//

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartsekb.h>
#include <voodoo_table_header/zapflege.h>
#include <voodoo_table_header/zpznpflege.h>
#include <voodoo_table_header/hneuheit.h>
#include <voodoo_table_header/carticlelang.h>
#include "ArticleCodesConverter.h"


#define ANZ_ARTIKEL_2 15    // Anzahl zu erfassende Artikel

struct PFL_ARTIKEL_2
{
	struct ZARTIKEL zartikel;
};


struct struArtName
{
	long ARTIKEL_NR;
	char ARTIKEL_MC[L_ZARTIKEL_ARTIKEL_MC + 1];
	char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
	char EINHEIT[L_ZARTIKEL_EINHEIT + 1];
	char DARREICHFORM[L_ZARTIKEL_DARREICHFORM + 1];
	char ARTIKEL_GESPERRT[L_ZARTIKEL_ARTIKEL_GESPERRT + 1];
	char HAT_SEKBEZ[2];
	char ARTICLEMC[L_CARTICLELANG_ARTICLEMC + 1];
	char ARTICLENAME[L_CARTICLELANG_ARTICLENAME + 1];
	char PACKAGINGUNIT[L_CARTICLELANG_PACKAGINGUNIT + 1];
	char PHARMAFORM[L_CARTICLELANG_PHARMAFORM + 1];
	
};

#include <eklibs/wdbups/wpp_dbas.h>


class CArtnameDoc
{

private:
	enum { NUMBER_OF_ARTIKEL = ANZ_ARTIKEL_2 };

// members
	char   *m_Anwender;
	char   m_PrimekeyCond[100];
	char   m_PrimekeyCondCarticlelang[100];
// zartikel
	int    m_Fd_Zartikel;
	long   m_lStatus_Zartikel;
	struct ZARTIKEL m_Buf;
	struct ZARTIKEL m_BufOld;

// zartsekbez
	enum { ANZ_SEKBEZ = 2 };
	int    m_Fd_Sekbez;
	long   m_lStatus_Sekbez[ANZ_SEKBEZ];
	struct ZARTSEKBEZ m_BufSekbez[ANZ_SEKBEZ];
	struct ZARTSEKBEZ m_BufOldSekbez[ANZ_SEKBEZ];

	//	Indikator
	char   m_CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];
	char   m_CmpIndikator_Carticlelang[POSANZ_CARTICLELANG + 1];

//	Puffer ueber Select
	struct struArtName m_BufArtname[NUMBER_OF_ARTIKEL];
	struct struArtName m_BufOldArtname[NUMBER_OF_ARTIKEL];

//	zapflege
	int    m_Fd_Zapflege;
	long   m_lStatus_Zapflege;
	struct ZAPFLEGE m_ZapflegeBuf;

//	zpznpflege
	int    m_Fd_Zpznpflege;
	long   m_lStatus_Zpznpflege;
	struct ZPZNPFLEGE m_ZpznpflegeBuf;

//	zaneuheit
	int    m_Fd_Zaneuheit;
	long   m_lStatus_Zaneuheit;
	struct ZANEUHEIT m_ZaneuheitBuf;

// carticlelang
	int    m_Fd_Carticlelang;
	long   m_lStatus_Carticlelang;
	CString m_csLangId;
	struct CARTICLELANG m_BufCarticlelang;
	struct CARTICLELANG m_BufOldCarticlelang;

public:	  
	CArtnameDoc();           // protected constructor used by dynamic creation

// Operations
public:
	struct struArtName* GetBuffer( int k );
	struct struArtName* GetOldBuffer( int k );

private:
	int  GetBufferDesc( CString &cErrmld );
public:
	void FreeBufferDesc( );
	long ReadRecord  ( CString& cErrmld );
	long StoreRecord ( int *ind,  CString& cErrmld );

	void InitPflegeDesc( char* Anwender );

private:
	void SetPrimekeyCondition( );
	// zartikel
	int  GetBufferDesc_Zartikel( CString& cErrmld );
	void CopyBuffer_Zartikel   ( int j );
	long ReadRecord_Zartikel   ( CString& cErrmld );
	long StoreRecord_Zartikel  ( CString& cErrmld );
	void FillCmpIndikator_Zartikel();

	void FillZartikelFromArtname( int k );
	long StoreSingleRecord( int k, CString &cErrmld );

	// Carticlelang
	void SetPrimekeyConditionCarticlelang( );
	int  GetBufferDesc_Carticlelang( CString& cErrmld );
	void CopyBuffer_Carticlelang   ( int j );
	long ReadRecord_Carticlelang   ( CString& cErrmld );
	long StoreRecord_Carticlelang  ( CString& cErrmld );
	long StoreSingleRecord_Carticlelang( int k, CString &cErrmld );
	void FillCmpIndikator_Carticlelang();

	void FillCarticlelangFromArtname( int k );

	// Sekbez
	int GetBufferDesc_Sekbez( CString &cErrmld );
	long RemovePharmosSekbez( int k, CString cErrmld );
	long StorePharmosSekbez( int k, CString cErrmld );

	// Zapflege
	int  GetBufferDesc_Zapflege( CString &cErrmld );
	long StoreRecord_Zapflege( CString &cErrmld );

	// Zpznpflege
	int  GetBufferDesc_Zpznpflege( CString &cErrmld );
	long StoreRecord_Zpznpflege( CString &cErrmld );

	// Zaneuheit
	int  GetBufferDesc_Zaneuheit( CString &cErrmld );
	long DeleteRecord_Zaneuheit ( char programm, CString &cErrmld );

	bool IsNumber( CString cStr );

private:
	// nicht immer
	void FillCmpIndikator( );
	int  IsRecordModified( int k );
	int  IsRecordModifiedCarticlelang( int k );

private:
	int  m_FdSel;
	bool m_bUseCarticlelang;
public:
	void InitArtnameBuffer( int anz );
	long LeseEinzelSatz( int k, CString &cErrmld );
	long StartSuche( CString SuchB1, int *anz,CString &cErrmld );
	long NextSuche( int *anz, CString &cErrmld );
	void CloseSuche();

// Implementation
public: 
	virtual ~CArtnameDoc();

};


/////////////////////////////////////////////////////////////////////////////
//

#endif // ARTNAMEDOC_H_INCLUDE