//Klasse zur Drucken eines Auftrags
#include "AeOutputs.h"

class CDruckAuftrag : public CAeOutputs
{
private:
    CStringList m_CListKopf;    // Liste der Kopfzeilen
    CStringList m_CListPos;     // Liste der Positionen
    CStringList m_CListFuss;    // Liste der Fusszeilen

public:
    void AddKopfZeile (const CString &Kopf);
    virtual void AddZeile(CString& s);

    void AddPosZeile(const CString& Position) { m_CListPos.AddTail(Position); }
    void AddFussZeile(const CString& Fuss);
    void DelKopfZeilen() { m_CListKopf.RemoveAll(); }   // loescht alle Kopfzeilen
    void DelPosZeilen() { m_CListPos.RemoveAll(); }     // loescht alle Positionszeilen
    void DelFussZeilen() { m_CListFuss.RemoveAll(); }   // loescht alle Fusszeilen
    void DelAllData();      // loescht alles
    void Druck(BOOL Querdruck = FALSE);     // druckt die Daten
    bool StartDruck(BOOL Querdruck = FALSE);
    void EndDruck();
    void PageDruck();

protected:
    int beginfuss;
    int anzfuss;
    int anzkopf;
    int anzpos;
    int anzposgesamt;
    int anzseiten;
    int nExtPage;
    int nCharHeight;
    int nCharWidth;
    char szError[50];
    CString Str;
    POSITION poskopf, poszeile, posfuss;
    CDC* dc;
    DOCINFO di;
    CFont* m_pFont;

    void doppproz(CString& str);
};
