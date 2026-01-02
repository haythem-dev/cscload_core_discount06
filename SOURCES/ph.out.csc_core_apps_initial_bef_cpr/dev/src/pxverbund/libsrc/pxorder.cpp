#include "pxorder.hpp"
#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxoeparm.hpp"
#include "pxdelpos.hpp"
#include "pxitem.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"
#include "pxbranch.hpp"
#include "pxcstonr.hpp"
#include "pxseporderartgrp.hpp"
#include "pxcstprint.hpp"
#include "pxtendercustomer.hpp"
#include <pxcustomergrpflags.hpp>

bool pxOrder::IsDiscountable()
{
    return ( Customer()->CustomerGroupFlagsList()->IsKscDiscountEnabled() && OrderType().IsDiscountable() );
}

bool pxOrder::isNormal()
{
    return ( OrderType().IsNormal() );
}

bool pxOrder::isTenderInvoice()
{
    return ( OrderType().IsTenderInvoice() );
}

// ---------------------------------------------------------------------------------------
const pxCustOrderType& pxOrder::OrderType()
{
    if( NULL == OrderType_ )
    {
        OrderType( KdAuftragArt(), KoArt(), BuchArt() ); // instantiate OrderType_
    }
    return *OrderType_;
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void pxOrder::VSEPut()
{
    if( IsDirty() )
    {
        Put();
    }
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
bool pxOrder::hasDefaultOrderLabel()
{
    return OrderType().isDefaultOrderLabel( OrderLabel_ );
}
// ---------------------------------------------------------------------------------------
