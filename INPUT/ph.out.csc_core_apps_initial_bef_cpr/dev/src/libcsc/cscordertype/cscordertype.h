#ifndef GUARD_LIBCSC_CSCORDERTYPE_H
#define GUARD_LIBCSC_CSCORDERTYPE_H

#include <cscordertype/icscordertype.h>
#include <datatypes/propertycollection.h>
#include <cscordertype/cscordertypebatchconfig/cscordertypebatchconfigptr.h>

namespace libcsc
{
namespace cscordertype
{
class CSCOrderType : public ICSCOrderType
{
    // because of OR mapping
    friend class CSCOrderTypeMapperBase;
	friend class CSCOrderTypeRepository;

public:
    CSCOrderType();
    virtual ~CSCOrderType();

    virtual const libcsc::Int16 & getBranchNo() const;
    virtual const libcsc::VarString & getOrderType() const;
    virtual const libcsc::VarString & getDescription() const;
	virtual const libcsc::Bool & getGlobal() const;
	virtual const libcsc::Bool & getNatra() const;
	virtual const libcsc::Bool & getNetto() const;
	virtual const libcsc::Bool & getBild() const;
	virtual const libcsc::Bool & getDafue() const;
	virtual const libcsc::Bool & getHand() const;
	virtual const libcsc::Bool & getDiscount() const;
	virtual const libcsc::Bool & getStandard() const;
	virtual const libcsc::Bool & getMuss() const;
	virtual const libcsc::Bool & getFreePrice() const;
	virtual const libcsc::Bool & getAufCons() const;
	virtual const libcsc::Bool & getAufNachl() const;
	virtual const libcsc::Bool & getNoQuota() const;
	virtual const libcsc::Bool & getDeferOrder() const;
	virtual const libcsc::Bool & getNoPart() const;
	virtual const libcsc::Bool & getNoDD() const;
	virtual const libcsc::Bool & getOnlyEH() const;
	virtual const libcsc::Bool & getIVC() const;
	virtual const libcsc::Bool & getOrgInvoice() const;
	virtual const libcsc::Bool & getNoPromo() const;
	virtual const libcsc::Bool & getDefaultKennung() const;
	virtual const libcsc::Bool & getStockreservation() const;
	virtual ICSCOrderTypeBatchConfigPtr getBatchConfig() const;
	virtual OrderTypeFlagTypeCollectionPtr getOrderTypeFlagTypeCollection() const;
	virtual       bool isFlagSet(const OrderTypeFlagTypeEnum flag) const;

	virtual void setBranchNo(const basar::Int16 branchno);
	virtual void setOrderType(const basar::VarString & orderType);
	virtual void setDescription(const basar::VarString & description);
	virtual void setGlobal(const bool global);
	virtual void setNatra(const bool natra);
	virtual void setNetto(const bool netto);
	virtual void setBild(const bool bild);
	virtual void setHand(const bool hand);
	virtual void setDafue(const bool dafue);
	virtual void setDiscount(const bool discount);
	virtual void setStandard(const bool standard);
	virtual void setMuss(const bool muss);
	virtual void setFreePrice(const bool freeprice);
	virtual void setAufCons(const bool aufcons);
	virtual void setAufNachl(const bool aufnachl);
	virtual void setNoQuota(const bool noquota);
	virtual void setDeferOrder(const bool deferorder);
	virtual void setNoPart(const bool nopart);
	virtual void setNoDD(const bool nodd);
	virtual void setOnlyEH(const bool onlyeh);
	virtual void setIVC(const bool ivc);
	virtual void setOrgInvoice(const bool orginvoice);
	virtual void setNoPromo(const bool nopromo);
	virtual void setDefaultKennung(const bool defaultkennung);
	virtual void setStockreservation(const bool stockreservation);


    virtual std::ostream & toStream( std::ostream & strm = std::cout ) const;

	bool						isInsertable() const;
	bool						isUpdatable() const;
	bool						isClean() const;

	void setClean();
	bool containsDirty() const;

private:
    libcsc::Int16		m_BranchNo;
    libcsc::VarString	m_OrderType;
    libcsc::VarString	m_Description;
	libcsc::Bool		m_bGlobal;
	libcsc::Bool		m_bNatra;
	libcsc::Bool		m_bNetto;
	libcsc::Bool		m_bBild;
	libcsc::Bool		m_bDafue;
	libcsc::Bool		m_bHand;
	libcsc::Bool		m_bDiscount;
	libcsc::Bool		m_bStandard;
	libcsc::Bool		m_bMuss;
	libcsc::Bool		m_bFreePrice;
	libcsc::Bool		m_bAufCons;
	libcsc::Bool		m_bAufNachl;
	libcsc::Bool		m_bNoQuota;
	libcsc::Bool		m_bDeferOrder;
	libcsc::Bool		m_bNoPart;
	libcsc::Bool		m_bNoDD;
	libcsc::Bool		m_bOnlyEH;
	libcsc::Bool		m_bIVC;
	libcsc::Bool		m_bOrgInvoice;
	libcsc::Bool		m_bNoPromo;
	libcsc::Bool		m_bDefaultKennung;
	libcsc::Bool		m_bStockreservation;

	CSCOrderTypeBatchConfigPtr		m_BatchConfig;
	OrderTypeFlagTypeCollectionPtr	m_OrderTypeFlagTypeCollection;
	libcsc::PropertyCollection		m_PropertyCollection;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_H
