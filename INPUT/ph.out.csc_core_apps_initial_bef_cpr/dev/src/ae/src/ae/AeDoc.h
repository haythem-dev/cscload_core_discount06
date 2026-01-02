#pragma once

// aedoc.h : interface of the CAeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef AUFPOSBUCH_H
#include <auftrag.h>
#endif

class CAeDoc : public CDocument
{
protected: // create from serialization only
    CAeDoc();
    DECLARE_DYNCREATE(CAeDoc)

// Attributes
public:

//Verwaltung Auftragsliste
private:
    AUFPOSBUCH* pFirstPos;                          //Zeiger auf Beginn der Liste
    //NULL, wenn die Liste leer ist

public:
    void UpdListPosition(int pos, AUFPOSBUCH Pos);  //Ändern der Position
    void AddPosition(const AUFPOSBUCH& Pos);        //Einfügen Position in Liste
    void UpdPosition(long OrdPos, AUFPOSBUCH Pos);  //Ändern der Position
    AUFPOSBUCH* GetListPosition(int pos);           //Adresse einer Position liefern
    AUFPOSBUCH* GetPosition(long OrdPos);           //Adresse einer Position liefern
    void DelPosition(int pos);                      //Löschen der Position
    void DelPosListe();                             //Löschen der gesammten Liste
    AUFPOSBUCH* GetPosListe() { return pFirstPos; } //Zeiger auf Liste

public:
    //Auftragsparameter
    CPtrArray m_AufArtEn;       //mögliche Auftragsarten
    CPtrArray m_AufKomb;        //mögliche Auftragskombinationen
    CPtrArray m_TourEn;         //mögliche Touren
    CString m_AufArt;           //aktuelle Auftragsart
    CString m_Tour;             //aktuelle Tour
    int m_KomArt;               //aktuelle Kommiart
    int m_BuchArt;              //aktuelle Buchungsart
    int m_ValutaMax;            //maximale Valutamonate
    int m_Valuta;               //Anzahl Valutamonate
    CString m_AufText;          //Bemerkung zum Auftrag
    bool m_bAllItemsInList;     //All order items in the list

public:
    virtual BOOL OnNewDocument();
    virtual BOOL CanCloseFrame(CFrameWnd* pFrame);

protected:
    virtual BOOL SaveModified();

public:
    virtual ~CAeDoc();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    DECLARE_MESSAGE_MAP()
};
