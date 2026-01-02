/*
 * pxtoteinfo.hpp
 *
 *  Created on: 27.10.2014
 *      Author: martin.zoephel
 */

#ifndef INCLUDE_PXTOTEINFO_HPP_
#define INCLUDE_PXTOTEINFO_HPP_

#include "pxbase/pxrecord.hpp"

struct tTOTEINFO;
struct tDISCOUNT;

class pxToteInfo : public pxDBRecord
{

public:

// constructors:
	pxToteInfo(pxToteInfo& src);
	pxToteInfo(pxSession *session);
	pxToteInfo(pxSession *session, 	nString& DataInfotype,
									short BranchNoIbt,
            						long ToteNo,
            						long OrderNo,
									long PickingStartDateTime,
									short BranchNo,
									nString& TourID);
	pxToteInfo(pxSession *session, tTOTEINFO& src);

// destructor:
	virtual  ~pxToteInfo();

	pxToteInfo&   operator=(const pxToteInfo& src);
	pxToteInfo&   operator=(const tTOTEINFO& src);

    friend tTOTEINFO& Assign(pxToteInfo& dest, const tTOTEINFO& src);
    friend tDISCOUNT& Assign(tTOTEINFO& dest, const pxToteInfo& src);
    virtual int       CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    bool              InsertData( const tTOTEINFO& data );
    bool              InsertData();

    long ID() {return ID_         ;}
    nString& DataInfoType() {return DataInfoType_         ;}
    long ToteNo() {return ToteNo_         ;}
    long OrdernoIbt() {return OrdernoIbt_         ;}
    short BranchNoIbt() {return BranchNoIbt_         ;}
    long PickingStartDateTime() {return PickingStartDateTime_         ;}
    short BranchNo() {return BranchNo_        ;}
    nString& TourID() {return TourID_         ;}

protected:
    void        Init();

    long ID_;
    nString DataInfoType_;
	long ToteNo_;
	long OrdernoIbt_;
	short BranchNoIbt_;
	long PickingStartDateTime_;
	short BranchNo_;
	nString TourID_;

private:
    tTOTEINFO& Assign (tTOTEINFO&  dest, const pxToteInfo& src);
    pxToteInfo& Assign( pxToteInfo& dest, const tTOTEINFO& src );
};

#endif /* INCLUDE_PXTOTEINFO_HPP_ */
