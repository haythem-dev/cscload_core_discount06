// aedoc.cpp : implementation of the CAeDoc class
//

#include "stdafx.h"
#include "AeFView.h"
#include "AeDoc.h"


/////////////////////////////////////////////////////////////////////////////
// CAeDoc

IMPLEMENT_DYNCREATE(CAeDoc, CDocument)

BEGIN_MESSAGE_MAP(CAeDoc, CDocument)
    ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
    ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAeDoc construction/destruction

CAeDoc::CAeDoc()
{
    pFirstPos = NULL;       //Positionsliste ist leer
    m_bAllItemsInList = false;
}

CAeDoc::~CAeDoc()
{
    DelPosListe(); //Freigabe des Listenspeichers
}

BOOL CAeDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAeDoc serialization

void CAeDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
    }
    else
    {
    }
}

/////////////////////////////////////////////////////////////////////////////
// CAeDoc diagnostics

#ifdef _DEBUG
void CAeDoc::AssertValid() const
{
    CDocument::AssertValid();
}

void CAeDoc::Dump(CDumpContext& dc) const
{
    CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAeDoc commands

BOOL CAeDoc::CanCloseFrame(CFrameWnd* /*pFrame*/)
{
    if (!IsModified())
        return TRUE;   //Dokument wurde nicht geändert

    if (((CAeFView*)AeGetApp()->m_pViewEing)->AuftragSave())
    {
        return FALSE;
    }
    return FALSE;
}

void CAeDoc::AddPosition(const AUFPOSBUCH& Pos)     //Einfügen Position in Liste
{

    AUFPOSBUCH *ptrPos      = pFirstPos;        //aktuelle Position
    AUFPOSBUCH *ptrVorg     = NULL;             //Vorgänger
    AUFPOSBUCH *ptrNewPos   = new AUFPOSBUCH;   //neue Position
    *ptrNewPos = Pos;

    if (pFirstPos == NULL)  //Liste war leer
    {
        pFirstPos = ptrNewPos;
        pFirstPos->FETCH_REL = NULL;
        return;
    }

    do
    {
        if (AeGetApp()->IsBG())
        {

            /* ******** deaktivierung sort  ******* */
            /* ******** fuer BG reaktiviert ******* */
            int erg = strcmp(ptrPos->ARTIKEL_LANGNAME, ptrNewPos->ARTIKEL_LANGNAME);
            if (erg > 0)
            {
                break;
            }
            else if (erg == 0)
            {
                erg = strcmp(ptrPos->EINHEIT, ptrNewPos->EINHEIT);
                if (erg > 0)
                {
                    break;
                }
            }
        /* ********* deaktivierung sort ******* */
        }

        ptrVorg = ptrPos;
        ptrPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL);
    } while (ptrPos != NULL);

    if (AeGetApp()->IsBG())
    {

        /* ******** deaktivierung sort  ******* */
        /* ******** fuer BG reaktiviert ******* */
        if (ptrVorg == NULL)   //an erster Stelle einfügen
        {
            pFirstPos = ptrNewPos;
        }
        else
        {
            ptrVorg->FETCH_REL = (long)ptrNewPos;
        }
        /* ******** deaktivierung sort ******* */
    }
    else
    {
        ptrVorg->FETCH_REL = (long)ptrNewPos;
    }
    ptrNewPos->FETCH_REL = (long)ptrPos;
}

void CAeDoc::UpdPosition(long OrdPos, AUFPOSBUCH Pos)   //Ändern der Position
{
    AUFPOSBUCH* ptrPos = pFirstPos;     //aktuelle Position
    for (int i = 0; ptrPos->POSNR != OrdPos && ptrPos != NULL; i++)
    {
        ptrPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL);
    }
    if (ptrPos == NULL)
    {
        return; //Ungueltige Position
    }
    Pos.FETCH_REL = ptrPos->FETCH_REL;
    *ptrPos = Pos;
}

AUFPOSBUCH *CAeDoc::GetPosition(long OrdPos)
{
    AUFPOSBUCH* Pos = pFirstPos;        //aktuelle Position
    for (int i = 0; Pos != NULL; i++)
    {
        if (Pos->POSNR == OrdPos)
            break;
        Pos = (AUFPOSBUCH*)(Pos->FETCH_REL);
    }
    return Pos;
}

void CAeDoc::UpdListPosition(int pos, AUFPOSBUCH Pos)   //Ändern der Position
{
    //Ändern der i-ten Position in der Liste
    AUFPOSBUCH* ptrPos = pFirstPos;     //aktuelle Position
    for (int i = 0; i < pos && ptrPos != NULL; i++)
    {
        ptrPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL);
    }
    if (ptrPos == NULL)
    {
        return; //Ungueltige Position
    }
    Pos.FETCH_REL = ptrPos->FETCH_REL;
    *ptrPos = Pos;
}

AUFPOSBUCH *CAeDoc::GetListPosition(int pos)
{
    AUFPOSBUCH* Pos = pFirstPos;        //aktuelle Position
    for (int i = 0; i < pos && Pos != NULL; i++)
    {
        Pos = (AUFPOSBUCH*)(Pos->FETCH_REL);
    }
    return Pos;
}

void CAeDoc::DelPosition(int pos)
{
    //Löschen der i-ten Position
    AUFPOSBUCH* ptrPos = pFirstPos;     //aktuelle Position
    AUFPOSBUCH* ptrVorg = pFirstPos;    //Vorgänger
    for (int i = 0; i < pos && ptrPos != NULL; i++)
    {
        ptrVorg = ptrPos;
        ptrPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL);
    }
    if (ptrPos == NULL)
    {
        return; //Ungueltige Position
    }
    if (ptrPos == pFirstPos)  //1. Position wird geloescht
    {
        pFirstPos = (AUFPOSBUCH*)(ptrPos->FETCH_REL);
        delete ptrPos;
    }
    else
    {
        ptrVorg->FETCH_REL = ptrPos->FETCH_REL;
        delete ptrPos;
    }
}

void CAeDoc::DelPosListe()
{
    //Löschen der gesammten Liste
    AUFPOSBUCH* ptr;
    while (pFirstPos != NULL)
    {
        ptr = (AUFPOSBUCH*)(pFirstPos->FETCH_REL);
        delete pFirstPos;
        pFirstPos = ptr;
    }
}

BOOL CAeDoc::SaveModified()
{
    return TRUE;
}
