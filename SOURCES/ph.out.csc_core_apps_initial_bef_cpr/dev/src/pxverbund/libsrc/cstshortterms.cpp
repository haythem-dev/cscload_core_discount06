#include "pxcstbas.hpp"
#include "pxsess.hpp"
#include "pxcustdisccondition.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxsubordertype.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  DiscountConditions: this methode                                          */
/*----------------------------------------------------------------------------*/
int
pxCustBase :: DiscountConditions
(
    const nString&  OrderType,
    const nString&  SubOrderType
)

{
    pxCustDiscConditionList* dcontlist = NULL;
    pxCustDiscCondition*     dcontp    = NULL;

    // check Customers DiscountConditions Table cstdiscountcont
    if (! CustDiscCondition_ )              // then entry is not constructed
    {

       if ( SubOrderType.IsEmpty() )
       {
          dcontlist = new  pxCustDiscConditionList(Session());
          dcontlist->Select( VertriebszentrumNr_, IDFNr_, OrderType );

          if ( dcontlist->Entries() == 0 )
          {
             ExternalError(CMsgStream(), CMSG_CST_NO_DISCCOUNTCOND, IDFNr_,
                           (char*)OrderType, (char*)SubOrderType);
             delete dcontlist;
             return ErrorState();
          }
          dcontp = (pxCustDiscCondition*)dcontlist->At(0);
       }

       if ( dcontp )
       {
          CustDiscCondition_ = new pxCustDiscCondition(Session(), VertriebszentrumNr_,
                                                       IDFNr_,
                                                       dcontp->OrderType(),
                                                       dcontp->SubOrderType());
       }
       else
       {
          CustDiscCondition_ = new pxCustDiscCondition(Session(), VertriebszentrumNr_,
                                                       IDFNr_,
                                                       OrderType,
                                                       SubOrderType);
       }

       if ( CustDiscCondition_->Get() )             // read entry from database
       {
          ExternalError(CMsgStream(), CMSG_CST_NO_DISCCOUNTCOND, IDFNr_,
                        (char*)OrderType, (char*)SubOrderType);
          delete CustDiscCondition_;
          CustDiscCondition_ = NULL;
          return ErrorState();
       }
    }
    // check SubOrderType entry Table discountlist
    if (! SubOrderType_ )                  // then entry is not constructed
    {
       SubOrderType_ = new pxSubOrderType(Session(), CustDiscCondition_->OrderType(),
                                          CustDiscCondition_->SubOrderType());
       if ( SubOrderType_->Get() )
       {
          ExternalError(CMsgStream(), CMSG_CST_NO_DISCCOUNTLIST,
                        (char*)OrderType, (char*)SubOrderType);
          delete CustDiscCondition_;
          CustDiscCondition_ = NULL;
          delete SubOrderType_;
          SubOrderType_ = NULL;
          if ( dcontlist )
          {
             delete dcontlist;
          }
          return ErrorState();
       }
    }
    // check PharmacyGroupId
    if ( PharmGroupList() )
    {
       if ( SubOrderType_->PharmacyGroupId() == "000" )
       {
          if ( dcontlist )
          {
             delete dcontlist;
          }
          return ErrorState();
       }
       if ( PharmGroupList_->Find(SubOrderType_->PharmacyGroupId() ) )
       {
          if ( dcontlist )
          {
             delete dcontlist;
          }
          return ErrorState();
       }
    }

    ExternalError(CMsgStream(), CMSG_CST_NO_PHARMACYGROUPID,
                                (char*)SubOrderType_->PharmacyGroupId(), IDFNr_,
                                (char*) SubOrderType);
    delete CustDiscCondition_;
    CustDiscCondition_ = NULL;
    delete SubOrderType_;
    SubOrderType_ = NULL;
    if ( dcontlist )
    {
       delete dcontlist;
    }
    return ErrorState();
}


