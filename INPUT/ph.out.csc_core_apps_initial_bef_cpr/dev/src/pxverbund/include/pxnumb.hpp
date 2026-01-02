#ifndef NUMMER_DOTH
#define NUMMER_DOTH

#include <database.hpp>
#include <tnummer.h>

class pxSession;

// VORDEFINIERTE NUMMERNTYPEN:
enum NumberTypeEnum
{
	cNUM_Auftrag = 1,           // order number
	//#define cNUM_INVQUEUE_SEQNO 2           // invoice queue sequence number
	//#define cNUM_ArtikelKonto   4           // artikekonto laufender nummer
	cNUM_BatchOrderNo = 7,           // BatchOrderNo for Branch 48
	cNUM_BatchOrderNo2 = 8			// BatchOrderNo for Branch 43
};

class pxNumber : public nDBRecord
{
public:
    pxNumber(pxSession *session);

    long       GetNextNumber(const NumberTypeEnum NummerTyp);
    long       GetNextNumberFromSequence(const NumberTypeEnum NummerTyp);
//  Liefert die nächste Nummer aus dem Object

protected:
    virtual int Read(const void *record);
    virtual int ReadLock(const void *record);
    virtual int Insert(const void *record);
    virtual int Update(const void *record);
    void        Init();
    tNUMMER     nummer;
	tNUMMERSEQUENCE numSeq;
};

#endif
