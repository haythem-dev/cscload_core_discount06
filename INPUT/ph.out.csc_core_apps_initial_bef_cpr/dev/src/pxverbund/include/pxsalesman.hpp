/*
 * pxsalesman.hpp
 *
 *  Created on: 17.09.2015
 *      Author: martin.zoephel
 */

#ifndef PXSALESMAN_HPP_
#define PXSALESMAN_HPP_

#include "pxbase/pxrecord.hpp"
#include "tsalesman.h"

struct tDISCOUNT;
struct tSALESMAN;

class pxSalesMan : public pxDBRecord
{

public:

// constructors:
	pxSalesMan(pxSalesMan& src);
	pxSalesMan(pxSession *session);
	pxSalesMan(pxSession *session, short branchNo, short salesmanNo);
	pxSalesMan(pxSession *session, tSALESMAN& src);

// destructor:
	virtual  ~pxSalesMan();

	pxSalesMan&   operator=(const pxSalesMan& src);
	pxSalesMan&   operator=(const tSALESMAN& src);

    friend pxSalesMan& Assign(pxSalesMan& dest, const tSALESMAN& src);
    friend tDISCOUNT& Assign(tSALESMAN& dest, const pxSalesMan& src);
    virtual int       CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

    short BranchNo() {return BranchNo_         ;}
    short SalesmanNo() {return SalesmanNo_         ;}
    nString& SalesmanName() {return SalesmanName_         ;}
    nString& SalesmanStreet() {return SalesmanStreet_         ;}
    nString& SalesmanCity() {return SalesmanCity_         ;}
    nString& PostCode() {return PostCode_         ;}
    short SActive() {return SActive_         ;}
    short SPreWhole() {return SPreWhole_         ;}
    nString&  EmailAdress() {return EmailAdress_         ;}

protected:
    void        Init();

    short BranchNo_;
    short SalesmanNo_;
    nString SalesmanName_;
	nString SalesmanStreet_;
	nString SalesmanCity_;
	nString PostCode_;
	short SActive_;
	short SPreWhole_;
    nString EmailAdress_;

private:
    tSALESMAN& Assign (tSALESMAN&  dest, const pxSalesMan& src);
    pxSalesMan& Assign( pxSalesMan& dest, const tSALESMAN& src );

    friend class pxSalesManList;
};

class pxSalesManList : public nDBRecordSet, public nDListCollect
{

public:

    pxSalesManList(pxSession *session);

    virtual ~pxSalesManList() {Clear();}

    pxSession* Session()       { return (pxSession*) DataBase();}

    tSALESMAN 			  SelectBySalesManNo ( const short salesManNo, const short branchno);
    tSALESMAN 			  SelectByPartnerNo ( const int partnerNo, const short branchno);

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);
    nCollectable*     AddToList( const void  *record, const int  row);

private:

    friend class pxSalesManListIter;
};

class pxSalesManListIter : public nDListCollectIter
{

public:
// constructors:
	pxSalesManListIter(pxSalesManList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxSalesManListIter() {;}
};



#endif /* INCLUDE_PXSALESMAN_HPP_ */
