#ifndef ARTIKELTAUSCH_H_INCLUDED
#define ARTIKELTAUSCH_H_INCLUDED

// ArtikelTausch.h : header file
//

class CArtikelTausch
{

public:	  
	CArtikelTausch();           // protected constructor used by dynamic creation
	long PznAlt2PznNeu( long PznAlt, long PznNeu, CString &cErrmld );

// Implementation
public: 
	virtual ~CArtikelTausch();
};

#endif // ARTIKELTAUSCH_H_INCLUDED