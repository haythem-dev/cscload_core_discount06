#include "cscordertype.h"
#include <cscordertype/cscordertypebatchconfig/cscordertypebatchconfig.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtype.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtypecollection.h>

namespace libcsc
{
namespace cscordertype
{
CSCOrderType::CSCOrderType()
{
    m_PropertyCollection.add( m_BranchNo );
    m_PropertyCollection.add( m_OrderType );
    m_PropertyCollection.add( m_Description );
	m_PropertyCollection.add( m_bGlobal );
	m_PropertyCollection.add( m_bNatra );
	m_PropertyCollection.add( m_bNetto );
	m_PropertyCollection.add( m_bBild );
	m_PropertyCollection.add( m_bDafue );
	m_PropertyCollection.add( m_bHand );
	m_PropertyCollection.add( m_bDiscount );
	m_PropertyCollection.add( m_bStandard );
	m_PropertyCollection.add( m_bMuss );
	m_PropertyCollection.add( m_bFreePrice );
	m_PropertyCollection.add( m_bAufCons );
	m_PropertyCollection.add( m_bAufNachl );
	m_PropertyCollection.add( m_bNoQuota );
	m_PropertyCollection.add( m_bDeferOrder );
	m_PropertyCollection.add( m_bNoPart );
	m_PropertyCollection.add( m_bNoDD );
	m_PropertyCollection.add( m_bOnlyEH );
	m_PropertyCollection.add( m_bIVC );
	m_PropertyCollection.add( m_bOrgInvoice );
	m_PropertyCollection.add( m_bNoPromo );
	m_PropertyCollection.add( m_bDefaultKennung );
}

CSCOrderType::~CSCOrderType()
{
}

const libcsc::Int16 & CSCOrderType::getBranchNo() const
{
	return m_BranchNo;
}

const libcsc::VarString & CSCOrderType::getOrderType() const
{
	return m_OrderType;
}

const libcsc::VarString & CSCOrderType::getDescription() const
{
	return m_Description;
}

const libcsc::Bool & CSCOrderType::getGlobal() const
{
	return m_bGlobal;
}

const libcsc::Bool & CSCOrderType::getNatra() const
{
	return m_bNatra;
}

const libcsc::Bool & CSCOrderType::getNetto() const
{
	return m_bNetto;
}

const libcsc::Bool & CSCOrderType::getBild() const
{
	return m_bBild;
}

const libcsc::Bool & CSCOrderType::getDafue() const
{
	return m_bDafue;
}

const libcsc::Bool & CSCOrderType::getHand() const
{
	return m_bHand;
}

const libcsc::Bool & CSCOrderType::getDiscount() const
{
	return m_bDiscount;
}

const libcsc::Bool & CSCOrderType::getStandard() const
{
	return m_bStandard;
}

const libcsc::Bool & CSCOrderType::getMuss() const
{
	return m_bMuss;
}

const libcsc::Bool & CSCOrderType::getFreePrice() const
{
	return m_bFreePrice;
}

const libcsc::Bool & CSCOrderType::getAufCons() const
{
	return m_bAufCons;
}

const libcsc::Bool & CSCOrderType::getAufNachl() const
{
	return m_bAufNachl;
}

const libcsc::Bool & CSCOrderType::getNoQuota() const
{
	return m_bNoQuota;
}

const libcsc::Bool & CSCOrderType::getDefaultKennung() const
{
	return m_bDefaultKennung;
}

const libcsc::Bool& CSCOrderType::getStockreservation() const
{
	return m_bStockreservation;
}

const libcsc::Bool & CSCOrderType::getDeferOrder() const
{
	return m_bDeferOrder;
}

const libcsc::Bool & CSCOrderType::getNoPart() const
{
	return m_bNoPart;
}

const libcsc::Bool & CSCOrderType::getNoDD() const
{
	return m_bNoDD;
}

const libcsc::Bool & CSCOrderType::getOnlyEH() const
{
	return m_bOnlyEH;
}

const libcsc::Bool & CSCOrderType::getNoPromo() const
{
	return m_bNoPromo;
}

const libcsc::Bool & CSCOrderType::getIVC() const
{
	return m_bIVC;
}

const libcsc::Bool & CSCOrderType::getOrgInvoice() const
{
	return m_bOrgInvoice;
}

ICSCOrderTypeBatchConfigPtr CSCOrderType::getBatchConfig() const
{
	return m_BatchConfig;
}

OrderTypeFlagTypeCollectionPtr CSCOrderType::getOrderTypeFlagTypeCollection() const
{
	return m_OrderTypeFlagTypeCollection;
}

bool CSCOrderType::isFlagSet(const OrderTypeFlagTypeEnum flag) const
{
	OrderTypeFlagTypeCollection::const_iterator it = m_OrderTypeFlagTypeCollection->begin();
	while (it != m_OrderTypeFlagTypeCollection->end())
	{
		if ((*it)->getOrderTypeFlagType() == flag)
		{
			return ((*it)->getOrderTypeFlag() != 0);
		}
		++it;
	}
	return false;
}


void CSCOrderType::setBranchNo(const basar::Int16 branchno)
{
	m_BranchNo = branchno;
}

void CSCOrderType::setOrderType(const basar::VarString & orderType)
{
	m_OrderType = orderType;
}

void CSCOrderType::setDescription(const basar::VarString & description)
{
	m_Description = description;
}

	void CSCOrderType::setGlobal(const bool global)
{
	m_bGlobal = global;
}

void CSCOrderType::setNatra(const bool natra)
{
	m_bNatra = natra;
}

void CSCOrderType::setNetto(const bool netto)
{
	m_bNetto = netto;
}

void CSCOrderType::setBild(const bool bild)
{
	m_bBild = bild;
}

void CSCOrderType::setDafue(const bool dafue)
{
	m_bDafue = dafue;
}

void CSCOrderType::setHand(const bool hand)
{
	m_bHand = hand;
}

void CSCOrderType::setDiscount(const bool discount)
{
	m_bDiscount = discount;
}

void CSCOrderType::setStandard(const bool standard)
{
	m_bStandard = standard;
}

void CSCOrderType::setMuss(const bool muss)
{
	m_bMuss = muss;
}

void CSCOrderType::setFreePrice(const bool freeprice)
{
	m_bFreePrice = freeprice;
}

void CSCOrderType::setAufCons(const bool aufcons)
{
	m_bAufCons = aufcons;
}

void CSCOrderType::setAufNachl(const bool aufnachl)
{
	m_bAufNachl = aufnachl;
}

void CSCOrderType::setNoQuota(const bool noquota)
{
	m_bNoQuota = noquota;
}

void CSCOrderType::setDeferOrder(const bool deferorder)
{
	m_bDeferOrder = deferorder;
}

void CSCOrderType::setNoPart(const bool nopart)
{
	m_bNoPart = nopart;
}

void CSCOrderType::setNoDD(const bool nodd)
{
	m_bNoDD = nodd;
}

void CSCOrderType::setOnlyEH(const bool onlyeh)
{
	m_bOnlyEH = onlyeh;
}

void CSCOrderType::setIVC(const bool ivc)
{
	m_bIVC = ivc;
}

void CSCOrderType::setOrgInvoice(const bool orginvoice)
{
	m_bOrgInvoice = orginvoice;
}

void CSCOrderType::setNoPromo(const bool nopromo)
{
	m_bNoPromo = nopromo;
}

void CSCOrderType::setDefaultKennung(const bool defaultkennung)
{
	m_bDefaultKennung = defaultkennung;
}

void CSCOrderType::setStockreservation(const bool stockreservation)
{
		m_bStockreservation = stockreservation;
}

bool CSCOrderType::isInsertable() const
{
	return	m_BranchNo.isDirty() &&
		m_OrderType.isDirty();
}

bool CSCOrderType::isUpdatable() const
{
	return m_BranchNo.isClean() &&
		m_OrderType.isClean() &&
		(
			m_PropertyCollection.containsDirty()
	);
}

bool CSCOrderType::isClean() const
{
	return m_PropertyCollection.isClean();
}

void CSCOrderType::setClean()
{
	m_PropertyCollection.setClean();
}

bool CSCOrderType::containsDirty() const
{
	return m_PropertyCollection.containsDirty();
}

std::ostream & CSCOrderType::toStream( std::ostream & strm /*= std::cout*/ ) const
{
	// TODO
	strm << "TODO";
	return strm;
}

} // end namespace cscordertype
} // end namespace libcsc

