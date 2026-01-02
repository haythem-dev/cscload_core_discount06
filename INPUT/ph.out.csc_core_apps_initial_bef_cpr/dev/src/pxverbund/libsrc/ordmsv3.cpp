#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxholiday.hpp"
#include "pxorderremarks.hpp"
//#include "logger/loggerpool.h"

/*----------------------------------------------------------------------------*/
void pxOrder::SetDefaultOrderLabel()
{
    if( OrderType_ )
    {
        if( !OrderType_->isAllowedForMSV3() )
        {
            SetOrderLabel( "" );
            return;
        }
        SetOrderLabel( OrderType_->getDefaultOrderLabel() );
    }
    else
    {
        pxCustOrderType* customerOrderType = new pxCustOrderType(Session());
        if( 0 == customerOrderType->getCustomerOrderType( FilialNr_, IDFNr_, KdAuftragArt_ ) )
        {
            if( !customerOrderType->isAllowedForMSV3() )
            {
                SetOrderLabel( "" );
                return;
            }
            SetOrderLabel( customerOrderType->getDefaultOrderLabel() );
        }
    }
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::isMSV3Order() const
{
    nString thisorderlabel(OrderLabel_);
    thisorderlabel.Strip();
    return ( thisorderlabel.Length() > 0 );
}

bool pxOrder::IsMSV3InfoOrder() const
{
    return IsInfoOrder() && Session()->IsSubDeviceTypeOf(MSV3) && Session()->isGermany();
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::isSalesWebOrder()
{
    bool retval = false;
    if( this->ItemList()->Entries() > 0 )
    {
        pxOrderItemListIter it( *this->ItemList() );
        pxOrderItem *item = NULL;
        while( (item = (pxOrderItem*) ++it ) != NULL )
        {
            if( 2 == item->SubGeraetTyp() ) // 2 == SalesWeb XML
            {
                retval = true;
                break;
            }
        }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::isOrderLabelEqual( nString orderlabel ) const
{
    orderlabel.Strip();
    nString thisorderlabel(OrderLabel_);
    thisorderlabel.Strip();
    return ( 0 == thisorderlabel.Compare(orderlabel) );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::IsOCPOrder()
{
    bool ret = false;
    bool btmp = false;
    if (Session()->isFrancePrewhole() == true)
    {
        if (ItemList_ == NULL)
        {
            btmp = true;
        }
        pxOrderItemListIter it(*ItemList());
        pxOrderItem* item = NULL;

        while (((item = (pxOrderItem*) ++it) != NULL) && (ret == false))
        {
            if (item->hasOCPOrderInfo())
            {
                ret = true;
            }
        }
        if (btmp == true)
        {
            // locally created, so need to clear and delete also
            ItemList_->Clear();
            delete ItemList_;
            ItemList_ = NULL;
        }
    }
    //std::stringstream getOrderStr;
    //getOrderStr.str(std::string());
    //getOrderStr << "####IsOCPOrder#### order no[" << KdAuftragNr() << "] with OCP State=" << ret << " pfr=" << Session()->isFrancePrewhole() << " local=" << btmp;
    //BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), getOrderStr.str());
    return ret;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

bool pxOrder::getOCPOrderValue(double& value)
{
    value = 0.0f;
    bool ret = false;
    bool btmp = false;
    if (Session()->isFrancePrewhole() == true)
    {
        if (ItemList_ == NULL)
        {
            btmp = true;
        }
        pxOrderItemListIter it(*ItemList());
        pxOrderItem* item = NULL;
        while ((item = (pxOrderItem*) ++it) != NULL)
        {
            // set the special rules
            // If Delivered qty > 0 then value = Ordered Qty X Invoiced Price
            // If Delivered qty = 0 then value = Ordered Qty X AEP
            double itemValue = 0.0f;
            if (item->MengeGeliefert() > 0)
            {
                // we do not know the invoiced price for this item (will be only done in Sales), but we narrow it with the discount, if given
                itemValue = ((double)item->MengeBestellt() * (double)item->PreisEKApo()) * (100 - item->GetDiscountValuePct()) / 100;
            }
            else
            {
                itemValue = (double)item->MengeBestellt() * (double)item->PreisEKApo();
            }
            value += itemValue;
            //std::stringstream getOrderStr;
            //getOrderStr.str(std::string());
            //getOrderStr << "####getOCPOrderValue#### order no=" << KdAuftragNr() << ", pos=" << item->PosNr() << ", orderqty=" << item->MengeBestellt() << ", deliverqty=" << item->MengeGeliefert() << ", aep="<<(double)item->PreisEKApo() << ", discountpct="<< item->GetDiscountValuePct() << ", calcValue="<< itemValue;
            //BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), getOrderStr.str());
        }
        if (btmp == true)
        {
            // locally created, so need to clear and delete also
            ItemList_->Clear();
            delete ItemList_;
            ItemList_ = NULL;
        }
        ret = true;
    }
    return ret;
}

bool pxOrder::getOCPOrderInfo(basar::VarString& channelId, int& offerID, double& freightCost, double& carriageFree)
{
    basar::VarString itemChannelId = basar::VarString("");
    int itemOfferID = 0;
    double itemFreightCost = 0;
    double itemCarriageFree = 0;
    bool firstItem = true;
    bool btmp = false;

    if (Session()->isFrancePrewhole() == true)
    {
        if (ItemList_ == NULL)
        {
            btmp = true;
        }
        pxOrderItemListIter it(*ItemList());
        pxOrderItem* item = NULL;

        // pick best or lowest freightCost/carriageFree for the customer and last item channelID and offerID
        while ((item = (pxOrderItem*) ++it) != NULL)
        {
            if (item->getOCPOrderInfo(itemChannelId, itemOfferID, itemFreightCost, itemCarriageFree))
            {
                channelId = itemChannelId;
                offerID = itemOfferID;
                if (firstItem)
                {
                    freightCost = itemFreightCost;
                    carriageFree = itemCarriageFree;
                    firstItem = false;
                }
                else
                {
                    if (itemFreightCost < freightCost)
                        itemFreightCost = freightCost;
                    if (itemCarriageFree < carriageFree)
                        itemCarriageFree = carriageFree;
                }
            }
        }
        if (btmp == true)
        {
            // locally created, so need to clear and delete also
            ItemList_->Clear();
            delete ItemList_;
            ItemList_ = NULL;
        }
    }
    //std::stringstream getOrderStr;
    //getOrderStr.str(std::string());
    //getOrderStr << "####getOCPOrderInfo#### order no[" << KdAuftragNr() << "] pfr=" << Session()->isFrancePrewhole() << " local=" << btmp << " channel=" << channelId << " offerID=" << offerID << " freightCost="<< freightCost << " carriageFree=" << carriageFree;
    //BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), getOrderStr.str());

    // at least one item found with OCPOrderInfo or OCP OrderRemarks
    return !firstItem; 
}
/*----------------------------------------------------------------------------*/