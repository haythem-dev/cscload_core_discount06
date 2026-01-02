#include "pxnumb.hpp"
#include "pxsess.hpp"

pxNumber :: pxNumber
(
     pxSession *session
)
    :nDBRecord(session)
{
    Init();
}

long pxNumber::GetNextNumberFromSequence(const NumberTypeEnum NummerTyp)
{
	long newNumber = 0;
	switch (NummerTyp)
	{
	case cNUM_Auftrag:			numSeq.SequenceType = cSEQUENCE_ORDERNO; break;
	case cNUM_BatchOrderNo:		numSeq.SequenceType = cSEQUENCE_BATCHORDERNO; break;
	case cNUM_BatchOrderNo2:	numSeq.SequenceType = cSEQUENCE_BATCHORDERNO2; break;
	default: break;
	}
	if (pxNummerSequence(&numSeq) == cDBXR_NORMAL)
	{
		newNumber = numSeq.NextVal;
	}
	return newNumber;
}

long pxNumber :: GetNextNumber
(
     const NumberTypeEnum type
)
{
	nummer.NummerTyp = static_cast<short>(type);
	int x = nDBReadLock(&nummer);
	if (x)
		return 0;                       // database i/o failed
	if ((nummer.NummerWert + nummer.NummerInkrement) > nummer.NummerHoechst)
	{
		if (nummer.NummerModus == 0)
		{
			nummer.NummerWert = nummer.NummerMindest;
		}
		else
		{
			return 0;                     /* no wrap allowed           */
		}
		nummer.NummerWert = nummer.NummerMindest;
	}
	else
	{
		nummer.NummerWert += nummer.NummerInkrement;
	}
	if (nummer.NummerTyp)             // database object
	{
		SetDirty();                     // database must be updated
		x = nDBWrite(&nummer, sizeof(tNUMMER));
	}
	return nummer.NummerWert;
}

void
pxNumber :: Init()
{
    nummer.NummerWert = 0;
    nummer.NummerMindest =  1;
    nummer.NummerHoechst = 999999;
    nummer.NummerInkrement = 1;
    nummer.NummerModus = 0;           // default : wrap
    nummer.NummerTyp = 0;             // memory type ( no DB )
}

int pxNumber::Read(const void *record)
{
    return pxNummerRead((tNUMMER*)record);
}

int pxNumber::ReadLock(const void *record)
{
    return pxNummerReadLock((tNUMMER*)record);
}

int pxNumber::Insert(const void *record)
{
    return pxNummerInsert((tNUMMER*)record);
}

int pxNumber::Update(const void *record)
{
    return pxNummerUpdate((tNUMMER*)record);
}
