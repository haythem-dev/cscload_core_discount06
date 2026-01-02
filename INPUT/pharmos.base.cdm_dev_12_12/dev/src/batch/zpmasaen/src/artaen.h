#ifndef ARTIKEL_H_INCLUDE
#define ARTIKEL_H_INCLUDE

// ArtikelDoc.h : header file
//

#include <zartikel.h>
#include <zartwg.h>
#include <zartprei.h>
#include <ean.h>
#include <zartfeb2.h>
#include <zifa.h>
#include <zartsekb.h>
#include <zapflege.h>
#include <zaneuhei.h>

#define NUMBER_OF_WGR   5
#define NUMBER_OF_PRICE 4

#define NUMBER_OF_SEKBEZ 20

struct PFL_ARTIKEL
{
    struct ZARTIKEL  zartikel;
    struct EAN       ean;
    struct ZARTFEB2  zartfeb2;
    struct ZARTPREIS artpreis[NUMBER_OF_PRICE];
    struct ZARTWG    zartwg[NUMBER_OF_WGR];

    CString cPharmosSekbez; 
};


#include "SVglIfa.h"


#include  "wdbups/wpp_dbas.h"


class CArtikelDoc
{

private:
// members
    char   *m_Anwender;
    char   m_PrimekeyCond[100];

// zartikel
    int    m_Fd_Zartikel;
    long   m_lStatus_Zartikel;

    //  Indikator
    char   m_CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];

// ean
    int    m_Fd_Ean;
    long   m_lStatus_Ean;

// zartfeb2
    int    m_Fd_Zartfeb2;
    long   m_lStatus_Zartfeb2;

// zartpreis
    char   m_PrimekeyCond_Artpreis[100];
    int    m_Fd_Artpreis;
    long   m_lStatus_Artpreis[NUMBER_OF_PRICE];

// zartwg
    char   m_PrimekeyCond_Zartwg[100];
    int    m_Fd_Zartwg;
    long   m_lStatus_Zartwg[NUMBER_OF_WGR];

//  gesamt
    struct PFL_ARTIKEL m_Buf;
    struct PFL_ARTIKEL m_BufOld;
    struct PFL_ARTIKEL m_BufSave;

//  sekbez
    char   m_PrimekeyCond_Sekbez[100];
    int    m_Fd_Sekbez;
    int    m_nNrOfSekbez;
    int    m_nNewNrOfSekbez;
    int    m_nMaxNrOfSekbez;
    struct ZARTSEKBEZ m_SekbezBuf[NUMBER_OF_SEKBEZ];
    struct ZARTSEKBEZ m_SekbezBufOld[NUMBER_OF_SEKBEZ];

//  zapflege
    int    m_Fd_Zapflege;
    long   m_lStatus_Zapflege;
    struct ZAPFLEGE m_ZapflegeBuf;

//  zaneuheit
    int    m_Fd_Zaneuheit;
    long   m_lStatus_Zaneuheit;
    struct ZANEUHEIT m_ZaneuheitBuf;

public:   
    CArtikelDoc();           // protected constructor used by dynamic creation

// Operations
public:

    struct PFL_ARTIKEL* GetBuffer();
    struct PFL_ARTIKEL* GetOldBuffer();

    // record read write delete
private:
    int  GetBufferDesc( CString &cErrmld );
public:
    void FreeBufferDesc( );
    long ReadRecord  ( CString& cErrmld );
    long DeleteRecord( CString& cErrmld );
    long StoreRecord ( CString& cErrmld );
    int  InitRecord  ( CString& cErrmld );

    void InitPflegeDesc( char* Anwender );
    void StoreBuffer();
    void RestoreBuffer();

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

    // zartfeb2
    int  GetBufferDesc_Zartfeb2 ( CString &cErrmld );
    int  InitRecord_Zartfeb2    ( CString &cErrmld );
    long ReadRecord_Zartfeb2    ( CString& cErrmld );
    long DeleteRecord_Zartfeb2  ( CString& cErrmld );
    long StoreRecord_Zartfeb2   ( CString& cErrmld );
    void RestoreBuffer_Zartfeb2 ( );
    bool IsToDelete_Zartfeb2( );

    // artpreis
public:
    long ShiftUp_ARTPREIS( CString &cErrmld );
    long ShiftDown_ARTPREIS( CString &cErrmld );
private:
    int  GetBufferDesc_Artpreis ( CString &cErrmld );
    int  InitRecord_Artpreis    ( int i, CString &cErrmld );
    long ReadRecord_Artpreis    ( CString& cErrmld );
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

    // Zapflege
    int  GetBufferDesc_Zapflege( CString &cErrmld );
    long StoreRecord_Zapflege( long datum, CString &cErrmld );

    // Zaneuheit
    int  GetBufferDesc_Zaneuheit( CString &cErrmld );
    long StoreRecord_Zaneuheit  ( char *programm, CString &cErrmld );
    long DeleteRecord_Zaneuheit ( char *programm, CString &cErrmld );

public:
    struct ZARTSEKBEZ* CArtikelDoc::GetSekbezBuffer();
    int    GetNrOfSekbez( );
    void   SetNewNrOfSekbez( int nNewNr );
    long ReadRecord_Sekbez ( CString& cErrmld );
private:
    void ReadPharmosSekbez(  );

private:
    // nicht immer
    void FillCmpIndikator( );
    int  IsRecordModified( CString &cErrmld );

    /////////////////////////////////
    // Ifa
private:
    struct PFL_ARTIKEL m_BufIfaTest;

    struct ZIFA m_IfaBuf;
    struct ZIFA m_IfaBufOld;
    int    m_Fd_Ifa;
    long   m_lStatus_Ifa;
    BOOL   m_bIfaPflege;    
    char   m_PrimekeyCondIfa[40];

    void   SetPrimekeyCondition_Ifa ( );
    int    GetBufferDesc_Ifa( CString &cErrmld );
    long   StoreRecord_Ifa  ( CString& cErrmld );

    struct ZARTIKEL m_PhzaltBuf;
    struct ZARTIKEL m_PhzaltBufOld;
    long   m_lStatus_Phzalt;
    char   m_PrimekeyCond_PhzAlt[30];

    void   SetPrimekeyCondition_PhzAlt ( );
    long   StoreRecord_Zartikel_PhzAlt( CString &cErrmld );

    void   IfaToArtikelIntern( struct PFL_ARTIKEL *Buf );
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


public:
    struct ZIFA* GetIfaBuffer();
    long   ReadRecord_Ifa( long IfaNr, long SatzNr, CString& cErrmld );
    long   ReadRecord_Zartikel_PhzAlt( long PhzAlt, CString &cErrmld );
    int    IfaToArtikel( CString &cErrmld );
//  void   IfaToTestArtikel( );
    BOOL   CompareArtikelWithIfa( );
    void   SetIfaPflege( BOOL bSet ); 
    void   UpdateArtikelWithIfa( );
    long   DatumIfaToPho( char *str );
    double PreisIfaToPreis( char *str );

    struct VGL_IFA* GetVglIfaBuffer();

// Implementation
public: 
    virtual ~CArtikelDoc();

};

/////////////////////////////////////////////////////////////////////////////
//

#endif // ARTIKELDOC_H_INCLUDE

