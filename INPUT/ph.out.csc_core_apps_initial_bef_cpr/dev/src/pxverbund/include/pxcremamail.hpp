/*
 * pxcremamail.hpp
 *
 *  Created on: 02.04.2013
 *      Author: martin.zoephel
 */

#ifndef PXCREMAMAIL_HPP_
#define PXCREMAMAIL_HPP_

#include "pxbase/pxrecord.hpp"
#include <string.h>

struct tCREMAMAIL;
struct tDISCOUNT;

class pxCremaMail : public pxDBRecord
{

public:

// constructors:
	pxCremaMail(pxCremaMail& src);
	pxCremaMail(pxSession *session);
	pxCremaMail(pxSession *session, tCREMAMAIL& src);

// destructor:
	virtual  ~pxCremaMail();

	pxCremaMail&   operator=(const pxCremaMail& src);
	pxCremaMail&   operator=(const tCREMAMAIL& src);

    friend pxCremaMail& Assign(pxCremaMail& dest, const tCREMAMAIL& src);
    friend tDISCOUNT& Assign(tCREMAMAIL& dest, const pxCremaMail& src);
    virtual int       CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

    bool             InsertData ( const tCREMAMAIL& data );
    virtual  int     Delete();

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);

    virtual  int     Delete(const void *record);

    short BranchNo() const { return BranchNo_; }
    nString& Server() {return Server_         ;}
    long Port() {return Port_         ;}
    double DlPercentage() {return DlPercentage_         ;}
    long KdAuftragNr() {return KdAuftragNr_         ;}
    nString& SentFromAddress() {return SentFromAddress_         ;}
    nString& SentToAddress() {return SentToAddress_         ;}
    nString& Guid() {return Guid_         ;}
    char WasSend() {return WasSend_         ;}
    long SendDate() {return SendDate_         ;}
    long SendTime() {return SendTime_         ;}
    long SmtpUserGroupID() { return SmtpUserGroupID_; }
    long SmtpID() { return SmtpID_; }
    long DebtLevelID() { return DebtLevelID_; }
    nString& URL() { return URL_; }
    short EmailType() { return EmailType_; }
    short LevelType() { return LevelType_; }
    double WertAuftrag() {return WertAuftrag_;}
    short ApprovalPersonsNeeded() {return ApprovalPersonsNeeded_;}
    short SendGVLMail() {return SendGVLMail_;}
    double ThresholdAmount() {return ThresholdAmount_;}
    long CremaTypeID() {return CremaTypeID_;}
    long PartnerNo() {return PartnerNo_;}

protected:
    void        Init();

    short BranchNo_;
    double DlPercentage_;
    nString Server_;
	long SmtpUserGroupID_;
	long SmtpID_;
	long Port_;
	long DebtLevelID_;
    nString SentFromAddress_;
    long KdAuftragNr_;
    nString Guid_;
    nString SentToAddress_;
    char WasSend_;
    long SendDate_;
	long SendTime_;
    nString URL_;
    short EmailType_;
    short LevelType_;
    double WertAuftrag_;
    short ApprovalPersonsNeeded_;
    short SendGVLMail_;
    double ThresholdAmount_;
    long CremaTypeID_;
    long PartnerNo_;

private:
    tCREMAMAIL& Assign (tCREMAMAIL&  dest, const pxCremaMail& src);
    pxCremaMail& Assign( pxCremaMail& dest, const tCREMAMAIL& src );

    friend class pxCremaMailList;
};

class pxCremaMailList : public nDBRecordSet, public nDListCollect
{

public:

    pxCremaMailList(pxSession *session);

    virtual ~pxCremaMailList() {Clear();}

    pxSession* Session()       { return (pxSession*) DataBase();}

    bool 			  SelectWasSendOrder ( const long orderNo, const short branchno);
    bool 			  SelectWasSendAmountPartner(const int partnerNo, const short branchno, const double amount);
    tCREMAMAIL 		  SelectDataForPercentage ( const double dlPercentage, const short branchNo );
    tCREMAMAIL 		  SelectDataForLevel( const short levelType, const short branchNo);
    bool 			  SelectWasSendWarningPartner(const int partnerNo, const short branchno, const short levelType, const double dlPercentage);
    tCREMAMAIL 		  SelectMailAdresses ( const int smtpUserGroupId, const short emailType );
    tCREMAMAIL		  SelectMailTypePercentage ( const double dlPercentage );
    tCREMAMAIL		  SelectMailTypeAmount ( const double usedCreditAmount );
    tCREMAMAIL		  SelectDataForAmount( const double amount, const short branchNo);
    tCREMAMAIL 		  SelectMaxApprovalNeeded( const long orderNo, const short branchNo);
    tCREMAMAIL 		  SelectGVLMailByType ( const int smtpUserGroupId, const short emailType );
    int      		  SelectDeferredCremaOrders( const short branchNo );
    tCREMAMAIL  	  SelectPartnerVZS ( const int partnerNo);
	tCREMAMAIL	      SelectMailAdressesForGUID( const std::string& guid );
    tCREMAMAIL		  SelectLanguageForPartner(const int partnerNo);
	tCREMAMAIL		  SelectGuidForOrder( const long orderNo );
	tCREMAMAIL		  SelectSmtpServer();

// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}

    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);
    nCollectable*     AddToList( const void  *record, const int  row);

private:
    friend class pxCremaMailListIter;
};

class pxCremaMailListIter : public nDListCollectIter
{

public:
// constructors:
	pxCremaMailListIter(pxCremaMailList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxCremaMailListIter() {;}
};

#endif /* PXCREMAMAIL_HPP_ */
