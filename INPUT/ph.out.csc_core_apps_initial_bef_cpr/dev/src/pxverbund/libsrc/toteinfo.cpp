/*
 * toteinfo.cpp
 *
 *  Created on: 27.10.2014
 *      Author: martin.zoephel
 */

#include "pxtoteinfo.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxToteInfo :: pxToteInfo
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxToteInfo :: pxToteInfo
(
		pxToteInfo& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTOTEINFO structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxToteInfo :: pxToteInfo
(
    pxSession   *session,
    tTOTEINFO& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

pxToteInfo :: pxToteInfo
(
    pxSession   *session,
	nString& DataInfotype,
	short BranchNoIbt,
	long ToteNo,
	long OrderNo,
	long PickingStartDateTime,
	short BranchNo,
	nString& TourID
)
    : pxDBRecord(session)
{
    Init();
    ID_						= 0;
    BranchNoIbt_    		= BranchNoIbt;
    ToteNo_ 	 			= ToteNo;
    DataInfoType_ 			= DataInfotype;
    OrdernoIbt_ 			= OrderNo;
    PickingStartDateTime_ 	= PickingStartDateTime;
    BranchNo_			 	= BranchNo;
    TourID_ 				= TourID;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxToteInfo :: ~pxToteInfo()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDISCOUNT structure.           */
/*----------------------------------------------------------------------------*/
tTOTEINFO& pxToteInfo :: Assign
(
	tTOTEINFO&           dest,
    const pxToteInfo&       src
)
{
    dest.ID           			= src.ID_     			  		  ;
    src.DataInfoType_.GetData(dest.DataInfoType)                  ;
    dest.ToteNo                 = src.ToteNo_            		  ;
    dest.OrdernoIbt        		= src.OrdernoIbt_    		  	  ;
    dest.BranchNoIbt           	= src.BranchNoIbt_     			  ;
    dest.PickingStartDateTime   = src.PickingStartDateTime_       ;
    dest.BranchNo           	= src.BranchNo_     			  ;
    src.TourID_.GetData(dest.TourID)                  		      ;

    return dest;
}

pxToteInfo& pxToteInfo :: Assign
(
	pxToteInfo&              dest,
    const tTOTEINFO&    src
)
{
    dest.ID_            			= src.ID     				;
    dest.DataInfoType_              = src.DataInfoType          ;
    dest.ToteNo_                    = src.ToteNo            	;
    dest.OrdernoIbt_           		= src.OrdernoIbt    		;
    dest.BranchNoIbt_            	= src.BranchNoIbt     		;
    dest.PickingStartDateTime_      = src.PickingStartDateTime 	;
    dest.TourID_              		= src.TourID           		;
    dest.BranchNo_              	= src.BranchNo          	;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void pxToteInfo :: Init()
{
	tTOTEINFO    record;
    memset(&record, 0 , sizeof(tTOTEINFO));
    Assign(*this, record);

}

pxToteInfo& pxToteInfo :: operator=( const pxToteInfo& src)
{
    tTOTEINFO record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISCOUNT structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxToteInfo& pxToteInfo :: operator=( const tTOTEINFO& src)
{
    return Assign(*this, src);
}

bool pxToteInfo :: InsertData
(
)
{
	tTOTEINFO fil;
	int     rc;

	memset(&fil, 0, sizeof(tTOTEINFO));  // zero out entire record buffer
	fil.OrdernoIbt = OrdernoIbt_;
	fil.ToteNo = ToteNo_;
	fil.BranchNoIbt = BranchNoIbt_;
	fil.PickingStartDateTime = PickingStartDateTime_;
	DataInfoType_.GetData(fil.DataInfoType);
	fil.BranchNo = BranchNo_;
	TourID_.GetData(fil.TourID);

	rc = pxToteInfoInsert(&fil);

	return (rc == 0);
}

bool pxToteInfo :: InsertData
(
	const tTOTEINFO& data
)
{
	tTOTEINFO fil;
	int     rc;

	memset(&fil, 0, sizeof(tTOTEINFO));  // zero out entire record buffer
	fil = data;

	rc = pxToteInfoInsert(&fil);

	return (rc == 0);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*----------------------------------------------------------------------------*/
int
pxToteInfo :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const

{
	pxToteInfo *that = (pxToteInfo*)That;

    int retval = (DataInfoType_ == that->DataInfoType_) ? 0
                : (DataInfoType_ > that->DataInfoType_ ? 1 : -1);

    if ( retval == 0 )
       retval = (ToteNo_ == that->ToteNo_) ? 0
                : (ToteNo_ > that->ToteNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (OrdernoIbt_ == that->OrdernoIbt_) ? 0
                  : (OrdernoIbt_ > that->OrdernoIbt_ ? 1 : -1);

    if ( retval == 0 )

        retval = (BranchNoIbt_ == that->BranchNoIbt_) ? 0
                  : (BranchNoIbt_ > that->BranchNoIbt_ ? 1 : -1);

    if ( retval == 0 )

        retval = (PickingStartDateTime_ == that->PickingStartDateTime_) ? 0
                  : (PickingStartDateTime_ > that->PickingStartDateTime_ ? 1 : -1);

    if ( retval == 0 )
    	retval = (TourID_ == that->TourID_) ? 0
                : (TourID_ > that->TourID_ ? 1 : -1);


    if ( retval == 0 )

        retval = (BranchNo_ == that->BranchNo_) ? 0
                  : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    return retval;
}

