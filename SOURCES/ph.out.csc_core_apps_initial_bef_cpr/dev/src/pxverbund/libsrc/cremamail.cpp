#include "pxcremamail.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCremaMail :: pxCremaMail
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
pxCremaMail :: pxCremaMail
(
        pxCremaMail& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCREMAMAIL structure to construct this instance.                       */
/*----------------------------------------------------------------------------*/
pxCremaMail :: pxCremaMail
(
    pxSession   *session,
    tCREMAMAIL& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCremaMail :: ~pxCremaMail()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDISCOUNT structure.           */
/*----------------------------------------------------------------------------*/
tCREMAMAIL& pxCremaMail :: Assign
(
    tCREMAMAIL&           dest,
    const pxCremaMail&       src
)
{
    src.Server_.GetData(dest.SERVER)                  ;
    dest.PORT                  = src.Port_            ;
    dest.DLPERCENTAGE          = src.DlPercentage_    ;
    dest.KDAUFTRAGNR           = src.KdAuftragNr_     ;
    src.SentFromAddress_.GetData(dest.SENTFROMADDRESS);
    src.SentToAddress_.GetData(dest.SENTTOADDRESS)    ;
    src.Guid_.GetData(dest.GUID)                      ;
    dest.WASSEND               = src.WasSend_         ;
    dest.SENDDATE              = src.SendDate_        ;
    dest.SENDTIME              = src.SendTime_        ;
    dest.SMTPUSERGROUPID       = src.SmtpUserGroupID_ ;
    dest.SMTPID                = src.SmtpID_          ;
    src.URL_.GetData(dest.URL)                        ;
    dest.EMAILTYPE             = src.EmailType_       ;
    dest.LEVELTYPE             = src.LevelType_       ;
    dest.WERTAUFTRAG           = src.WertAuftrag_     ;
    dest.APPROVALPERSONSNEEDED  = src.ApprovalPersonsNeeded_;
    dest.SENDGVLMAIL            = src.SendGVLMail_    ;
    dest.THRESHOLDAMOUNT        = src.ThresholdAmount_;
    dest.CREMATYPEID            = src.CremaTypeID_    ;
    dest.PARTNERNO              = src.PartnerNo_      ;
    dest.SENDTIME               = src.SendTime_       ;
    dest.BRANCHNO               = src.BranchNo_       ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDISCOUNT structure to                     */
/*  a pxDiscount object.                                                      */
/*----------------------------------------------------------------------------*/
pxCremaMail& pxCremaMail :: Assign
(
    pxCremaMail&              dest,
    const tCREMAMAIL&    src
)
{
    dest.Server_                 = src.SERVER          ;
    dest.Port_                   = src.PORT            ;
    dest.DlPercentage_           = src.DLPERCENTAGE    ;
    dest.KdAuftragNr_            = src.KDAUFTRAGNR     ;
    dest.SentFromAddress_        = src.SENTFROMADDRESS ;
    dest.SentToAddress_          = src.SENTTOADDRESS   ;
    dest.Guid_                   = src.GUID            ;
    dest.WasSend_                = src.WASSEND         ;
    dest.SendDate_               = src.SENDDATE        ;
    dest.SendTime_               = src.SENDTIME        ;
    dest.SmtpUserGroupID_        = src.SMTPUSERGROUPID ;
    dest.SmtpID_                 = src.SMTPID          ;
    dest.URL_                    = src.URL             ;
    dest.EmailType_              = src.EMAILTYPE       ;
    dest.LevelType_              = src.LEVELTYPE       ;
    dest.WertAuftrag_            = src.WERTAUFTRAG     ;
    dest.ApprovalPersonsNeeded_  = src.APPROVALPERSONSNEEDED;
    dest.SendGVLMail_            = src.SENDGVLMAIL     ;
    dest.ThresholdAmount_        = src.THRESHOLDAMOUNT ;
    dest.CremaTypeID_            = src.CREMATYPEID     ;
    dest.PartnerNo_              = src.PARTNERNO       ;
    dest.BranchNo_               = src.BRANCHNO        ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void pxCremaMail :: Init()
{
    tCREMAMAIL    record;
    memset(&record, 0 , sizeof(tCREMAMAIL));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDISCOUNT struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCremaMail& pxCremaMail :: operator=( const pxCremaMail& src)
{
    tCREMAMAIL record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISCOUNT structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCremaMail& pxCremaMail :: operator=( const tCREMAMAIL& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int pxCremaMail :: Get
(
    DBAccessMode /*mode*/
)

{
    tCREMAMAIL record;
    memset(&record, 0, sizeof(tCREMAMAIL));
    int retval = nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tCREMAMAIL struct
    return retval;
}

bool pxCremaMail :: InsertData
(
    const tCREMAMAIL& data
)
{
    tCREMAMAIL fil;
    int     rc;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer
    fil = data;

    rc = pxCremaMailInsert(&fil);

    return (rc == 0);
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCremaMail :: Delete
(
)
{
    tCREMAMAIL record;
    memset(&record, 0, sizeof(tCREMAMAIL));
    Assign(record, *this);
    return nDBDelete(&record);
}


int
pxCremaMail :: Delete
(
    const void  *record
)
{
    return pxCremaMailDelete((tCREMAMAIL*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*----------------------------------------------------------------------------*/
int
pxCremaMail :: CompareTo
(
    const nCollectable*   That,
          void*           /*p*/,
    const long            /*lparm*/
)   const

{
    pxCremaMail *that = (pxCremaMail*)That;

    int retval = (Server_ == that->Server_) ? 0
                : (Server_ > that->Server_ ? 1 : -1);

    if ( retval == 0 )
       retval = (Port_ == that->Port_) ? 0
                : (Port_ > that->Port_ ? 1 : -1);

    if ( retval == 0 )
        retval = (DlPercentage_ == that->DlPercentage_) ? 0
                  : (DlPercentage_ > that->DlPercentage_ ? 1 : -1);

    if ( retval == 0 )

        retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                  : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);

    if ( retval == 0 )

        retval = (SentFromAddress_ == that->SentFromAddress_) ? 0
                  : (SentFromAddress_ > that->SentFromAddress_ ? 1 : -1);

    if ( retval == 0 )
       retval = (SentToAddress_ == that->SentToAddress_) ? 0
                : (SentToAddress_ > that->SentToAddress_ ? 1 : -1);

    if ( retval == 0 )
       retval = (Guid_ == that->Guid_) ? 0
                : (Guid_ > that->Guid_ ? 1 : -1);

    if ( retval == 0 )
       retval = (WasSend_ == that->WasSend_) ? 0
                : (WasSend_ > that->WasSend_ ? 1 : -1);

    if ( retval == 0 )
       retval = (SendDate_ == that->SendDate_) ? 0
                : (SendDate_ > that->SendDate_ ? 1 : -1);

    if ( retval == 0 )
       retval = (SendTime_ == that->SendTime_) ? 0
                : (SendTime_ > that->SendTime_ ? 1 : -1);

    if ( retval == 0 )
          retval = (DebtLevelID_ == that->DebtLevelID_) ? 0
                   : (DebtLevelID_ > that->DebtLevelID_ ? 1 : -1);

    if ( retval == 0 )
          retval = (SmtpID_ == that->SmtpID_) ? 0
                   : (SmtpID_ > that->SmtpID_ ? 1 : -1);

    if ( retval == 0 )
          retval = (SmtpUserGroupID_ == that->SmtpUserGroupID_) ? 0
                   : (SmtpUserGroupID_ > that->SmtpUserGroupID_ ? 1 : -1);


    if ( retval == 0 )
          retval = (URL_ == that->URL_) ? 0
                   : (URL_ > that->URL_ ? 1 : -1);

    if ( retval == 0 )
          retval = (EmailType_ == that->EmailType_) ? 0
                   : (EmailType_ > that->EmailType_ ? 1 : -1);

    if ( retval == 0 )
          retval = (LevelType_ == that->LevelType_) ? 0
                   : (LevelType_ > that->LevelType_ ? 1 : -1);

    if ( retval == 0 )
          retval = (WertAuftrag_ == that->WertAuftrag_) ? 0
                   : (WertAuftrag_ > that->WertAuftrag_ ? 1 : -1);


    if ( retval == 0 )
          retval = (ApprovalPersonsNeeded_ == that->ApprovalPersonsNeeded_) ? 0
                   : (ApprovalPersonsNeeded_ > that->ApprovalPersonsNeeded_ ? 1 : -1);

    if ( retval == 0 )
          retval = (SendGVLMail_ == that->SendGVLMail_) ? 0
                   : (SendGVLMail_ > that->SendGVLMail_ ? 1 : -1);

    if ( retval == 0 )
          retval = (ThresholdAmount_ == that->ThresholdAmount_) ? 0
                   : (ThresholdAmount_ > that->ThresholdAmount_ ? 1 : -1);

    if ( retval == 0 )
          retval = (CremaTypeID_ == that->CremaTypeID_) ? 0
                   : (CremaTypeID_ > that->CremaTypeID_ ? 1 : -1);

    if ( retval == 0 )
          retval = (PartnerNo_ == that->PartnerNo_) ? 0
                   : (PartnerNo_ > that->PartnerNo_ ? 1 : -1);

    if ( retval == 0 )
          retval = (SendTime_ == that->SendTime_) ? 0
                   : (SendTime_ > that->SendTime_ ? 1 : -1);

    if ( retval == 0 )
          retval = (BranchNo_ == that->BranchNo_) ? 0
                   : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    return retval;
}

pxCremaMailList :: pxCremaMailList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}


bool pxCremaMailList :: SelectWasSendOrder
(
    const long     orderNo,
    const short     branchno
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.KDAUFTRAGNR = orderNo;
    fil.BRANCHNO = branchno;

    int cursorid = cCRSDEBTMAIL_CHECKWASSEND_ORDER;
    nDBSelect(&fil, cursorid, count_, &fil);

    return (count_ > 0);
}

bool pxCremaMailList :: SelectWasSendAmountPartner
(
    const int partnerNo,
    const short branchno,
    const double amount
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.PARTNERNO = partnerNo;
    fil.BRANCHNO = branchno;
    fil.WERTAUFTRAG = amount;

    int cursorid = cCRSDEBTMAIL_CHECKWASSEND_AMOUNT_PARTNER;
    nDBSelect(&fil, cursorid, count_, &fil);

    return count_ > 0;
}

bool pxCremaMailList :: SelectWasSendWarningPartner
(
    const int partnerNo,
    const short branchno,
    const short levelType,
    const double dlPercentage
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.PARTNERNO = partnerNo;
    fil.BRANCHNO = branchno;
    fil.DLPERCENTAGE = dlPercentage;
    fil.LEVELTYPE = levelType;

    int cursorid = cCRSDEBTMAIL_CHECKWASSEND_WARNING_PARTNER;
    nDBSelect(&fil, cursorid, count_, &fil);

    return count_ > 0;
}

tCREMAMAIL pxCremaMailList :: SelectDataForLevel
(
    const short levelType,
    const short branchNo
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.LEVELTYPE = levelType;
    fil.BRANCHNO = branchNo;

    int cursorid = cCRSDEBTMAIL_GETDATAFORLEVEL;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList :: SelectDataForPercentage
(
    const double dlPercentage,
    const short branchNo
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.DLPERCENTAGE = dlPercentage;
    fil.BRANCHNO = branchNo;

    int cursorid = cCRSDEBTMAIL_GETDATAFORPERCENTAGE;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList :: SelectDataForAmount
(
    const double amount,
    const short branchNo
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.WERTAUFTRAG = amount;
    fil.BRANCHNO = branchNo;

    int cursorid = cCRSDEBTMAIL_GETDATAFORAMOUNT;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList :: SelectMailAdresses
(
    const int smtpUserGroupId,
    const short emailType
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.SMTPUSERGROUPID = smtpUserGroupId;
    fil.EMAILTYPE = emailType;

    int cursorid = cCRSDEBTMAIL_GETMAILADDRESSES;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList :: SelectMailAdressesForGUID
(
    const std::string& guid
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    strcpy(fil.GUID,guid.c_str());

    int cursorid = cCRSDEBTMAIL_GETMAILDATAFORUUID;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList :: SelectMailTypePercentage
(
    const double dlPercentage
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.DLPERCENTAGE = dlPercentage;

    int cursorid = cCRSDEBTMAIL_GETTYPEFORPERCENTAGE;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList::SelectMailTypeAmount
(
    const double usedCreditAmount
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.THRESHOLDAMOUNT = usedCreditAmount;

    int cursorid = cCRSDEBTMAIL_GETTYPEFORAMOUNT;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList :: SelectMaxApprovalNeeded
(
    const long orderNo,
    const short branchNo
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.KDAUFTRAGNR = orderNo;
    fil.BRANCHNO = branchNo;

    int cursorid = cCRSDEBTMAIL_GETAPPROVALSNEEDED;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList :: SelectGVLMailByType
(
    const int smtpUserGroupID,
    const short emailType
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.SMTPUSERGROUPID = smtpUserGroupID;
    fil.EMAILTYPE = emailType;

    int cursorid = cCRSDEBTMAIL_GETGVLMAIL;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

int pxCremaMailList :: SelectDeferredCremaOrders
(
    const short branchNo
)
{
    tCREMAMAIL fil;
    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.BRANCHNO = branchNo;

    nDBSelect(&fil, cCRSDEBTMAIL_GET_DEFERRED_ORDERS, cDEFAULT);
    return static_cast<int>(Entries());
}

tCREMAMAIL pxCremaMailList :: SelectPartnerVZS
(
    const int partnerNo
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.PARTNERNO = partnerNo;

    int cursorid = cCRSDEBTMAIL_GET_WARNING_PARTNER_VZS;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList :: SelectLanguageForPartner
(
    const int partnerNo
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.PARTNERNO = partnerNo;

    int cursorid = cCRSDEBTMAIL_GETLANGUAGEFORPARTNER;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList::SelectGuidForOrder
(
    const long orderNo
)
{
    tCREMAMAIL fil;
    int     count_ = -1;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer

    fil.KDAUFTRAGNR = orderNo;

    int cursorid = cCRSDEBTMAIL_GETGUIDFORORDERNO;
    nDBSelect(&fil, cursorid, count_, &fil);

    return fil;
}

tCREMAMAIL pxCremaMailList::SelectSmtpServer
(
)
{
    tCREMAMAIL fil;

    memset(&fil, 0, sizeof(tCREMAMAIL));  // zero out entire record buffer
    int cursorid = cCRSDEBTMAIL_GETSMTPSERVER;
    nDBSelect(&fil, cursorid, -1, &fil);
    return fil;
}

int pxCremaMailList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCremaMailEndBrowse(cursorid);
}

int pxCremaMailList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCremaMailGetNext((tCREMAMAIL*)record, cursorid);
}

int pxCremaMailList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCremaMailStartBrowse((tCREMAMAIL*)keys, cursorid);
}

nCollectable* pxCremaMailList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxDiscount' object:
    pxCremaMail *objectp = new pxCremaMail(Session(), *(tCREMAMAIL*) record);
    InsertAscending(objectp);
    return objectp;
}
