#include "pxtransmissionresponse.hpp"
#include "transmissionresponse.h"
#include "pxsess.hpp"
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/*  read one table entry to construct this instance                           */
/*----------------------------------------------------------------------------*/
pxTransmissionResponse :: pxTransmissionResponse
(
	pxSession *session,
	const basar::VarString& transmissionGuid
) : pxDBRecord(session)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: pxTransmissionResponse()");

	Init();
	Request_Id = transmissionGuid;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTransmissionResponse :: ~pxTransmissionResponse()
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: ~pxTransmissionResponse()");
}

/*----------------------------------------------------------------------------*/
/* Assign the values of the 'src' object to a tTRANSMISSIONRESPONSE structure.*/
/*----------------------------------------------------------------------------*/
tTRANSMISSIONRESPONSE&
Assign
(
	tTRANSMISSIONRESPONSE&			dest,
	const pxTransmissionResponse&	src
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Assign(tTRANSMISSIONRESPONSE&, const pxTransmissionResponse&)");

	dest.Id = src.Id;
	strncpy(dest.Request_Id, src.Request_Id.c_str(), 36);
	dest.Support_Id = src.Support_Id;
	dest.BranchNo = src.BranchNo;
	dest.CustomerNo = src.CustomerNo;
	dest.Is_Offer = src.Is_Offer;
	dest.ResponseAsXml = const_cast<char*>(src.ResponseAsXml.c_str());
	dest.Create_Date = src.Create_Date;

	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tBLIEFER structure to a                    */
/*  pxTransmissionResponse object.                                            */
/*----------------------------------------------------------------------------*/
pxTransmissionResponse&
Assign
(
	pxTransmissionResponse& dest,
	const tTRANSMISSIONRESPONSE& src
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Assign(pxTransmissionResponse&, const tTRANSMISSIONRESPONSE&)");

	dest.Id = src.Id;
	dest.Request_Id = src.Request_Id;
	dest.Support_Id = src.Support_Id;
	dest.BranchNo = src.BranchNo;
	dest.CustomerNo = src.CustomerNo;
	dest.Is_Offer = src.Is_Offer;
	if (NULL != src.ResponseAsXml)
		dest.ResponseAsXml = src.ResponseAsXml;
	dest.Create_Date = src.Create_Date;
	return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize the object.                                                    */
/*----------------------------------------------------------------------------*/
void
pxTransmissionResponse :: Init()
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Init()");

	tTRANSMISSIONRESPONSE record;
	memset(&record, 0 , sizeof(tTRANSMISSIONRESPONSE));
	Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tBLIEFER            */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxTransmissionResponse&
pxTransmissionResponse :: operator=(const pxTransmissionResponse& src)
{
    tTRANSMISSIONRESPONSE    record;             // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tBLIEFER struct. 'src' to this instance          */
/*----------------------------------------------------------------------------*/
pxTransmissionResponse&
pxTransmissionResponse :: operator=(const tTRANSMISSIONRESPONSE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxTransmissionResponse :: Get
(
    DBAccessMode mode
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Get()");

    tTRANSMISSIONRESPONSE record;
    memset(&record, 0, sizeof(tTRANSMISSIONRESPONSE));
    Assign(record, *this);
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;
    else if ( retval > cDBXR_NORMAL )
	{
	}
	return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxTransmissionResponse :: Put
(
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Put()");

	tTRANSMISSIONRESPONSE record;
	memset(&record, 0, sizeof(tTRANSMISSIONRESPONSE));
	Assign(record, *this);
	int retVal = nDBWrite(&record, sizeof(tTRANSMISSIONRESPONSE));

	// get serial from database
	this->Id = record.Id;

	return retVal;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTransmissionResponse :: Read
(
	const void  *record
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Read()");
	return pxTransmissionResponseRead((tTRANSMISSIONRESPONSE*)record);
}

int
pxTransmissionResponse :: ReadLock
(
	const void  *record
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: ReadLock()");
	return pxTransmissionResponseReadLock((tTRANSMISSIONRESPONSE*)record);
}

int
pxTransmissionResponse :: Insert
(
	const void  *record
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Insert()");
	return pxTransmissionResponseInsert((tTRANSMISSIONRESPONSE*)record);
}

int
pxTransmissionResponse :: Update
(
	const void  *record
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Update()");
	return pxTransmissionResponseUpdate((tTRANSMISSIONRESPONSE*)record);
}

int
pxTransmissionResponse :: Delete
(
	const void  *record
)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxTransmissionResponse :: Delete()");
	return pxTransmissionResponseDelete((tTRANSMISSIONRESPONSE*)record);
}
