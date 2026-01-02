#ifndef GUARD_LIBCSC_I_CSCORDERTYPE_H
#define GUARD_LIBCSC_I_CSCORDERTYPE_H

#include <datatypes/int16.h>
#include <datatypes/varstring.h>
#include <datatypes/boolean.h>
#include <base/istreamable.h>
#include <cscordertype/cscordertypebatchconfig/icscordertypebatchconfigptr.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtypecollectionptr.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtypeenum.h>

namespace libcsc
{
namespace cscordertype
{
class ICSCOrderType : public base::IStreamable
{
public:
	virtual ~ICSCOrderType() {}

    virtual const libcsc::Int16 & getBranchNo() const = 0;
    virtual const libcsc::VarString & getOrderType() const = 0;
    virtual const libcsc::VarString & getDescription() const = 0;
	virtual const libcsc::Bool & getGlobal() const = 0;
	virtual const libcsc::Bool & getNatra() const = 0;
	virtual const libcsc::Bool & getNetto() const = 0;
	virtual const libcsc::Bool & getBild() const = 0;
	virtual const libcsc::Bool & getDafue() const = 0;
	virtual const libcsc::Bool & getHand() const = 0;
	virtual const libcsc::Bool & getDiscount() const = 0;
	virtual const libcsc::Bool & getStandard() const = 0;
	virtual const libcsc::Bool & getMuss() const = 0;
	virtual const libcsc::Bool & getFreePrice() const = 0;
	virtual const libcsc::Bool & getAufCons() const = 0;
	virtual const libcsc::Bool & getAufNachl() const = 0;
	virtual const libcsc::Bool & getNoQuota() const = 0;
	virtual const libcsc::Bool & getDeferOrder() const = 0;
	virtual const libcsc::Bool & getNoPart() const = 0;
	virtual const libcsc::Bool & getNoDD() const = 0;
	virtual const libcsc::Bool & getOnlyEH() const = 0;
	virtual const libcsc::Bool & getIVC() const = 0;
	virtual const libcsc::Bool & getOrgInvoice() const = 0;
	virtual const libcsc::Bool & getNoPromo() const = 0;
	virtual const libcsc::Bool & getDefaultKennung() const = 0;
	virtual const libcsc::Bool & getStockreservation() const = 0;

	virtual void setBranchNo(const basar::Int16 branchno) = 0;
	virtual void setOrderType(const basar::VarString & orderType) = 0;
	virtual void setDescription(const basar::VarString & description) = 0;
	virtual void setGlobal(const bool global) = 0;
	virtual void setNatra(const bool natra) = 0;
	virtual void setNetto(const bool netto) = 0;
	virtual void setBild(const bool bild) = 0;
	virtual void setHand(const bool hand) = 0;
	virtual void setDafue(const bool dafue) = 0;
	virtual void setDiscount(const bool discount) = 0;
	virtual void setStandard(const bool standard) = 0;
	virtual void setMuss(const bool muss) = 0;
	virtual void setFreePrice(const bool freeprice) = 0;
	virtual void setAufCons(const bool aufcons) = 0;
	virtual void setAufNachl(const bool aufnachl) = 0;
	virtual void setNoQuota(const bool noquota) = 0;
	virtual void setDeferOrder(const bool deferorder) = 0;
	virtual void setNoPart(const bool nopart) = 0;
	virtual void setNoDD(const bool nodd) = 0;
	virtual void setOnlyEH(const bool onlyeh) = 0;
	virtual void setIVC(const bool ivc) = 0;
	virtual void setOrgInvoice(const bool orginvoice) = 0;
	virtual void setNoPromo(const bool nopromo) = 0;
	virtual void setDefaultKennung(const bool defaultkennung) = 0;
	virtual void setStockreservation(const bool stockreservation) = 0;

	virtual bool						isInsertable() const = 0;
	virtual bool						isUpdatable() const = 0;
	virtual bool						isClean() const = 0;

	virtual ICSCOrderTypeBatchConfigPtr		getBatchConfig() const = 0;
	virtual OrderTypeFlagTypeCollectionPtr	getOrderTypeFlagTypeCollection() const = 0;

	virtual bool isFlagSet(const OrderTypeFlagTypeEnum flag) const = 0;

};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_I_CSCORDERTYPE_H
