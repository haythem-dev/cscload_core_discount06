// ZdpDruckDoc.h : interface of the CZdpDruckDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZDPDRUCKDOC_H__6E2D8B6D_AEC3_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_ZDPDRUCKDOC_H__6E2D8B6D_AEC3_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CZdpDruckDoc : public CDocument
{
protected: // create from serialization only
	CZdpDruckDoc();
	DECLARE_DYNCREATE(CZdpDruckDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZdpDruckDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	// neu zum Drucken
	virtual void DeleteContents();			
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL


// Implementation
public:
	virtual ~CZdpDruckDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


private:
	CStringArray m_sAr;


protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CZdpDruckDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDPDRUCKDOC_H__6E2D8B6D_AEC3_11D2_92F8_0060973B18D8__INCLUDED_)
