#ifndef GUARD_LIBCSC_CSCORDERTYPE_MAPPER_BASE_H
#define GUARD_LIBCSC_CSCORDERTYPE_MAPPER_BASE_H

#include <cscordertype/cscordertypeptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace cscordertype
{
class CSCOrderTypeMapperBase
{
public:
	CSCOrderTypeMapperBase( CSCOrderTypePtr orderType );

	void map();

protected:
	virtual ~CSCOrderTypeMapperBase();
    
	virtual void doMap() = 0;
    
	void setBranchNo( const basar::Int16 branchNo );
	void setOrderType( const basar::VarString & orderType );
	void setDescription( const basar::VarString & description );
	void setGlobal(const bool global);
	void setNatra(const bool natra);
	void setNetto(const bool netto);
	void setBild(const bool bild);
	void setHand(const bool hand);
	void setDafue(const bool dafue);
	void setDiscount(const bool discount);
	void setStandard(const bool standard);
	void setMuss(const bool muss);
	void setFreePrice(const bool freeprice);
	void setAufCons(const bool aufcons);
	void setAufNachl(const bool aufnachl);
	void setNoQuota(const bool noquota);
	void setDeferOrder(const bool deferorder);
	void setNoPart(const bool nopart);
	void setNoDD(const bool nodd);
	void setOnlyEH(const bool onlyeh);
	void setIVC(const bool ivc);
	void setOrgInvoice(const bool orginvoice);
	void setNoPromo(const bool nopromo);
	void setDefaultKennung(const bool defaultkennung);

	void setStockreservation(const bool stockreservation);

private:
    CSCOrderTypePtr   m_CSCOrderType;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_MAPPER_BASE_H
