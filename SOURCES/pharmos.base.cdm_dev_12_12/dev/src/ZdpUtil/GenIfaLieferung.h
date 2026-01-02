// GenIfaLieferung.h: Schnittstelle für die Klasse CGenIfaLieferung.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENIFALIEFERUNG_H__85114428_7D28_4EED_A0B4_968A43A1D5F2__INCLUDED_)
#define AFX_GENIFALIEFERUNG_H__85114428_7D28_4EED_A0B4_968A43A1D5F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGenIfaLieferung  
{
public:
	CGenIfaLieferung();
	virtual ~CGenIfaLieferung();

private:
	long GenLiefer_Ili( long lieferdatum,  char *verz, char *errmld );
	void Gen_KMPK_Satz( char *buf, long tagesdatum );
	void Gen_IC01_Satz( char *buf, char *ssatz, long datum, long pzn, long betrag );
	void Gen_ASAS_Satz( char *buf, long anz );
	void Gen_KMPE_Satz( char *buf, long anz, long tagesdatum );
	int  ScanPzn  ( int nPos, char trenn, long *pzn, char *zeile );
	int  ScanFestb( int nPos, char trenn, long *betrag, char *zeile );
	int  ScanZeile    ( int nPosPzn, int nPosFest, char trenn, 
		                char *zeile, long *pzn, long *betrag );
	long getDatum( char *str );
	long GenLiefd001( int nPosPzn, int nPosFest, char *trenn, 
		              char *ssatz, long nGuelDat, long nLiefDat,
					  char *datei, char *verz, char *errmld );

public:
	long GenFeb_2( int nPosPzn, int nPosFest, char *trenn, 
		           char *ssatz, long nGuelDat, long nLiefDat,
		           char *datei, char *verz,  char *errmld );

	long GenFeb_ili( char *errmld );

};

#endif // !defined(AFX_GENIFALIEFERUNG_H__85114428_7D28_4EED_A0B4_968A43A1D5F2__INCLUDED_)
