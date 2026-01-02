// ZdpUtilDoc.h : Schnittstelle der Klasse CZdpUtilDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZDPUTILDOC_H__EB066948_999E_454E_A5B4_86647DCAC1D7__INCLUDED_)
#define AFX_ZDPUTILDOC_H__EB066948_999E_454E_A5B4_86647DCAC1D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CZdpUtilDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CZdpUtilDoc();
	DECLARE_DYNCREATE(CZdpUtilDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZdpUtilDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CZdpUtilDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CZdpUtilDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZDPUTILDOC_H__EB066948_999E_454E_A5B4_86647DCAC1D7__INCLUDED_)
