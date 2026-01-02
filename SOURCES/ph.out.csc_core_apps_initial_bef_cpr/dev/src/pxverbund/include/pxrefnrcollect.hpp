/*
27 March 2008 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXREFNRCOLLECT_DOTH
#define PXREFNRCOLLECT_DOTH

#include <dlistcol.hpp>
#include <string.hpp>

class pxRefnrCollect : public nCollectable
{

public:
	pxRefnrCollect(const nString& KdAuftragBestellNr);
	pxRefnrCollect(const pxRefnrCollect &src);

	virtual  ~pxRefnrCollect();

	pxRefnrCollect& operator=(const pxRefnrCollect& src);

    virtual int CompareTo(const nCollectable *that, void *p, const long lparm) const;

    const nString& KdAuftragBestellNr() const  { return KdAuftragBestellNr_;}
    long           RefNrCount() const          { return RefNrCount_ ;       }

    void           SetRefNrCount(const long c) { RefNrCount_ = c;}

protected:
    nString    KdAuftragBestellNr_;  // RefenceNr
    long       RefNrCount_        ;  // count of position with same refenr

private:
    friend class pxRefnrCollectList;
};

class pxRefnrCollectList : public nDListCollect
{

public:
	virtual  ~pxRefnrCollectList() {Clear();}
	void        Clear();
	bool        Find(const nString& KdAuftragBestellNr);
private:
    friend class pxRefnrCollectListIter;
};

class pxRefnrCollectListIter : public nDListCollectIter
{
public:
    pxRefnrCollectListIter(pxRefnrCollectList& list) : nDListCollectIter(list) {}
    virtual  ~pxRefnrCollectListIter() {}
};
#endif
