//////////////////////////////////////////////////////////////////
// ArtikelTausch.cpp  implementation file

#include "stdafx.h"
#include "ekzdp.h"
	
#include "ArtikelTausch.h"
#include "ArtikelDoc.h"

#include <wudu.h>     // spaeter weg
#include <wpx_prot.h>
#include <wpx_bufd.h>

#include <phodate.h>
#include <phxutil.h>

CArtikelTausch::CArtikelTausch()
{
}

CArtikelTausch::~CArtikelTausch()
{
}


long CArtikelTausch::PznAlt2PznNeu( long PznAlt, long PznNeu, CString &cErrmld )
{
	int  i;
	long s;

	CArtikelDoc AltDoc;	
	CArtikelDoc NeuDoc;	
	struct PFL_ARTIKEL *AltBuf;
	struct PFL_ARTIKEL *NeuBuf;

	AltBuf = AltDoc.GetBuffer();  
	AltBuf->zartikel.ARTIKEL_NR = PznAlt;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = AltDoc.ReadRecord ( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( s == 100 )
		cErrmld = "PznAlt nicht vorhanden";
	if ( s != 0 )
		return s;

	NeuBuf = NeuDoc.GetBuffer();  
	NeuBuf->zartikel.ARTIKEL_NR = PznNeu;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = NeuDoc.ReadRecord ( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	if ( s == 0 )
		cErrmld = "PznNeu bereits vorhanden";
	if ( s != 0 )
		return s;

	// PznNeu
	*NeuBuf = *AltBuf;
	// ersetze Artikel_Nr
	NeuBuf->zartikel.ARTIKEL_NR = PznNeu;
	NeuBuf->ean.ARTIKEL_NR = PznNeu;
	NeuBuf->zartfeb2.ARTIKEL_NR = PznNeu;
	for ( i = 0; i < NUMBER_OF_PRICE; i++ )
 		NeuBuf->artpreis[i].ARTIKEL_NR;
	for ( i = 0; i < NUMBER_OF_WGR; i++ )
		NeuBuf->zartwg[i].ARTIKEL_NR;
	
	// PznAlt
	*AltBuf->zartikel.ARTIKEL_GELOESCHT = '1';
	

	s = AltDoc.StoreRecord( cErrmld );
	if ( s != 0 ) return s;

	s = NeuDoc.StoreRecord( cErrmld );
	
	return s;
}

