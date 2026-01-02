#include "cscordertypemapperbase.h"
#include <cscordertype/cscordertype.h>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace cscordertype
{
CSCOrderTypeMapperBase::CSCOrderTypeMapperBase( CSCOrderTypePtr orderType )
: m_CSCOrderType( orderType )
{
}

CSCOrderTypeMapperBase::~CSCOrderTypeMapperBase()
{
}

void CSCOrderTypeMapperBase::map()
{
    doMap();

	// TODO
    std::stringstream ss;
    ss << "CSCOrderTypeMapperBase::map(), m_CSCOrderType:" << *m_CSCOrderType << std::endl;
    BLOG_TRACE( LoggerPool::getLoggerParameter(), ss.str().c_str() );
}

void CSCOrderTypeMapperBase::setBranchNo( const basar::Int16 branchNo )
{
	m_CSCOrderType->m_BranchNo = branchNo;
	m_CSCOrderType->m_BranchNo.setClean();
}

void CSCOrderTypeMapperBase::setOrderType( const basar::VarString & orderType )
{
	m_CSCOrderType->m_OrderType = orderType;
	m_CSCOrderType->m_OrderType.setClean();
}

void CSCOrderTypeMapperBase::setDescription( const basar::VarString & description )
{
	m_CSCOrderType->m_Description = description;
	m_CSCOrderType->m_Description.setClean();
}

void CSCOrderTypeMapperBase::setGlobal(const bool global)
{
	m_CSCOrderType->m_bGlobal = global;
	m_CSCOrderType->m_bGlobal.setClean();
}

void CSCOrderTypeMapperBase::setNatra(const bool natra)
{
	m_CSCOrderType->m_bNatra = natra;
	m_CSCOrderType->m_bNatra.setClean();
}

void CSCOrderTypeMapperBase::setNetto(const bool netto)
{
	m_CSCOrderType->m_bNetto = netto;
	m_CSCOrderType->m_bNetto.setClean();
}

void CSCOrderTypeMapperBase::setBild(const bool bild)
{
	m_CSCOrderType->m_bBild = bild;
	m_CSCOrderType->m_bBild.setClean();
}

void CSCOrderTypeMapperBase::setHand(const bool hand)
{
	m_CSCOrderType->m_bHand = hand;
	m_CSCOrderType->m_bHand.setClean();
}

void CSCOrderTypeMapperBase::setDafue(const bool dafue)
{
	m_CSCOrderType->m_bDafue = dafue;
	m_CSCOrderType->m_bDafue.setClean();
}

void CSCOrderTypeMapperBase::setDiscount(const bool discount)
{
	m_CSCOrderType->m_bDiscount = discount;
	m_CSCOrderType->m_bDiscount.setClean();
}

void CSCOrderTypeMapperBase::setStandard(const bool standard)
{
	m_CSCOrderType->m_bStandard = standard;
	m_CSCOrderType->m_bStandard.setClean();
}

void CSCOrderTypeMapperBase::setMuss(const bool muss)
{
	m_CSCOrderType->m_bMuss = muss;
	m_CSCOrderType->m_bMuss.setClean();
}

void CSCOrderTypeMapperBase::setFreePrice(const bool freeprice)
{
	m_CSCOrderType->m_bFreePrice = freeprice;
	m_CSCOrderType->m_bFreePrice.setClean();
}

void CSCOrderTypeMapperBase::setAufCons(const bool aufcons)
{
	m_CSCOrderType->m_bAufCons = aufcons;
	m_CSCOrderType->m_bAufCons.setClean();
}

void CSCOrderTypeMapperBase::setAufNachl(const bool aufnachl)
{
	m_CSCOrderType->m_bAufNachl = aufnachl;
	m_CSCOrderType->m_bAufNachl.setClean();
}

void CSCOrderTypeMapperBase::setNoQuota(const bool noquota)
{
	m_CSCOrderType->m_bNoQuota = noquota;
	m_CSCOrderType->m_bNoQuota.setClean();
}

void CSCOrderTypeMapperBase::setDeferOrder(const bool deferorder)
{
	m_CSCOrderType->m_bDeferOrder = deferorder;
	m_CSCOrderType->m_bDeferOrder.setClean();
}

void CSCOrderTypeMapperBase::setNoPart(const bool nopart)
{
	m_CSCOrderType->m_bNoPart = nopart;
	m_CSCOrderType->m_bNoPart.setClean();
}

void CSCOrderTypeMapperBase::setNoDD(const bool nodd)
{
	m_CSCOrderType->m_bNoDD = nodd;
	m_CSCOrderType->m_bNoDD.setClean();
}

void CSCOrderTypeMapperBase::setOnlyEH(const bool onlyeh)
{
	m_CSCOrderType->m_bOnlyEH = onlyeh;
	m_CSCOrderType->m_bOnlyEH.setClean();
}

void CSCOrderTypeMapperBase::setIVC(const bool ivc)
{
	m_CSCOrderType->m_bIVC = ivc;
	m_CSCOrderType->m_bIVC.setClean();
}

void CSCOrderTypeMapperBase::setOrgInvoice(const bool orginvoice)
{
	m_CSCOrderType->m_bOrgInvoice = orginvoice;
	m_CSCOrderType->m_bOrgInvoice.setClean();
}

void CSCOrderTypeMapperBase::setNoPromo(const bool nopromo)
{
	m_CSCOrderType->m_bNoPromo = nopromo;
	m_CSCOrderType->m_bNoPromo.setClean();
}

void CSCOrderTypeMapperBase::setDefaultKennung(const bool defaultkennung)
{
	m_CSCOrderType->m_bDefaultKennung = defaultkennung;
	m_CSCOrderType->m_bDefaultKennung.setClean();
}
void CSCOrderTypeMapperBase::setStockreservation(const bool stockreservation)
{
	m_CSCOrderType->m_bStockreservation = stockreservation;
	m_CSCOrderType->m_bStockreservation.setClean();
}
} // end namespace cscordertype
} // end namespace libcsc

