#ifndef GUARD_PXTRANSMISSIONRESPONSE_HPP
#define GUARD_PXTRANSMISSIONRESPONSE_HPP

#include "pxbase/pxrecord.hpp"
#include <libbasarcmnutil_bstring.h>

struct tTRANSMISSIONRESPONSE;

class pxTransmissionResponse : public pxDBRecord
{

public:
	pxTransmissionResponse(pxSession *session, const basar::VarString& transmissionGuid);
	virtual ~pxTransmissionResponse();

    pxTransmissionResponse&   operator=(const pxTransmissionResponse& src);

    pxTransmissionResponse&   operator=(const tTRANSMISSIONRESPONSE& src);

    friend pxTransmissionResponse&  Assign(pxTransmissionResponse& dest, const tTRANSMISSIONRESPONSE& src);
    friend tTRANSMISSIONRESPONSE&        Assign(tTRANSMISSIONRESPONSE& dest, const pxTransmissionResponse& src);
    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

//  Queries:
	long					getId()								{ return Id; }
	const basar::VarString& getTransmissionGuid()				{ return Request_Id; }
	long					getTransmissionSupportId()			{ return Support_Id; }
	short					getBranchNo()						{ return BranchNo; }
	long					getCustomerNo()						{ return CustomerNo; }
	bool					getIsOffer()						{ return (Is_Offer != 0); }
	const basar::VarString& getResponseAsXml()					{ return ResponseAsXml; }
	long					getCreationDate()					{ return Create_Date; }

	void	setTransmissionGuid(const basar::VarString& val)	{ Request_Id = val; }
	void	setTransmissionSupportId(const long val)			{ Support_Id = val; }
	void	setBranchNo(const short val)						{ BranchNo = val; }
	void	setCustomerNo(const long val)						{ CustomerNo = val; }
	void	setIsOffer(const bool val)							{ Is_Offer = (val == true) ? 1 : 0; }
	void	setResponseAsXml(const basar::VarString& val)		{ ResponseAsXml = val; }
	void	setCreationDate(const long val)						{ Create_Date = val; }

protected:
    void        Init();

	long				Id;
	basar::VarString	Request_Id;
	long				Support_Id;
	short				BranchNo;
	long				CustomerNo;
	short				Is_Offer;
	basar::VarString	ResponseAsXml;
	long				Create_Date;

private:

};

#endif // GUARD_PXTRANSMISSIONRESPONSE_HPP
