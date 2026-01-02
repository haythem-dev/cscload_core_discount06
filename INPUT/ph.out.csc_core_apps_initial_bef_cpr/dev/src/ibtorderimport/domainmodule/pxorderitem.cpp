#include "pxorderitem.h"
#include "loggerpool/ibtorderimport_loggerpool.h"
#include <misc/metaclassmacro_definitions.h> // libutil
#include <misc/log_macro_definitions.h>      // libutil
#include "pxvb_includes.h"

//-----------------------------------------------------------------------------------------

namespace ibtorderimport {
namespace domMod {

//-----------------------------------------------------------------------------------------

PxOrderItem::PxOrderItem(const log4cplus::Logger& logger, ::pxOrderItem* item) :
	m_Logger(logger), m_pxItem(item)
{
}

//-----------------------------------------------------------------------------------------

PxOrderItem::~PxOrderItem()
{
}

//-----------------------------------------------------------------------------------------

const log4cplus::Logger& PxOrderItem::getLogger()
{
	return m_Logger;
}

//-----------------------------------------------------------------------------------------

void PxOrderItem::setRemark(basar::VarString remark)
{
	nString bemerkung (remark.c_str());
	m_pxItem->Bemerkungen(bemerkung);
}


//-----------------------------------------------------------------------------------------

void PxOrderItem::setQtyBooked(basar::Int32 qty)
{
	m_pxItem->MengeAbgebucht(qty);
}

//-----------------------------------------------------------------------------------------

bool PxOrderItem::isCompleteOrderedQtyConfirmed()
{
	return m_pxItem->MengeBestellt() == m_pxItem->MengeGeliefert();
}

//-----------------------------------------------------------------------------------------

void PxOrderItem::markAsNonPharmosBatch()
{
	m_pxItem->ToPharmosBatch(false);
}

//-----------------------------------------------------------------------------------------

void PxOrderItem::setCustomerOrderReference(basar::VarString ref)
{
	nString reference (ref.c_str());
	m_pxItem->KdAuftragBestellNr(reference);
}

//-----------------------------------------------------------------------------------------

void PxOrderItem::setArticleCodeProperties(basar::Int16 codeType, basar::VarString artCode)
{
	m_pxItem->SetArticleCodeValues(codeType, artCode.c_str());
}

//-----------------------------------------------------------------------------------------

void PxOrderItem::setIbtType(basar::Int16 type)
{
	m_pxItem->SetIBTTypeID(type);
}

//-----------------------------------------------------------------------------------------

::pxOrderItem * PxOrderItem::getPxVbOrderItem()
{
	return m_pxItem;
}

//-----------------------------------------------------------------------------------------

void PxOrderItem::setTourIdIbt(nString id)
{
	m_pxItem->SetTourIdIBT(id);
}

//-----------------------------------------------------------------------------------------

void PxOrderItem::setIbtTourWeekDay(basar::Int16 day)
{
	m_pxItem->SetIBTTourWeekDay(day);
}

//-----------------------------------------------------------------------------------------

} // namespace domMod
} // namespace ibtorderimport

//-----------------------------------------------------------------------------------------
