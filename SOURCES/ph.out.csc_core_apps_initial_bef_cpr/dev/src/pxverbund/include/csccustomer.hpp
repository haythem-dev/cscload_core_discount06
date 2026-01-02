#ifndef CSCCUSTOMER_HPP
#define CSCCUSTOMER_HPP

#include "pxbase/pxrecord.hpp"
#include "tcsccustomer.h"
#include <libbasar_definitions.h>

class pxCustOrderTypeList;
class CustomerBusinessHoursList;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class CSCCustomer : public pxDBRecord
{

	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:

									CSCCustomer( pxSession* session, const short& branchno, const long& customerno );

		virtual						~CSCCustomer();

		int							Read();

		const short&				getBranchNo() const;
		const long&					getCustomerNo() const;
		const basar::VarString		getNameApo() const;
		const basar::VarString		getNameInhaber() const;
		const basar::VarString		getStrasse() const;
		const basar::VarString		getOrt() const;
		const basar::VarString		getPostLeitZahl() const;
		const basar::VarString		getTelnr() const;
		const basar::VarString		getTelnrDafue() const;
		const basar::VarString		getFaxnr() const;
		const basar::VarString		getAnredeKz() const;
		const long&					getImsBezirkNr() const;
		const basar::VarString		getKdGruppe() const;
		const long&					getPersonalNrVertr() const;
		const basar::VarString		getKzSprache() const;
		const basar::VarString		getDafueSystemSchluessel() const;

		const basar::VarString		isVersandApo() const;
        bool                        isFMDCustomer() const;

		nString						getDefaultOrderType() const;
		nString						getDefaultOrderTypeCombination() const;
		const long&					getTourBreakoverMinutes() const;
		bool						getUseSeparateOrder() const;

		pxCustOrderTypeList*		getCustomerOrderTypeList(); // NO CROSS DATABASE SUPPORT!!!
		CustomerBusinessHoursList*	getCustomerBusinessHoursList();


	/*############################################################################################################################*/
	/*                                       P R O T E C T E D                                                                    */
	/*############################################################################################################################*/
	protected:

		CSCCustomer&				Assign( CSCCustomer& dest, const tCSCCUSTOMER& src );
		tCSCCUSTOMER&				Assign( tCSCCUSTOMER&  dest, const CSCCustomer& src );

		void						Init();

	/*############################################################################################################################*/
	/*                                       P R I V A T E                                                                        */
	/*############################################################################################################################*/
	private:
									CSCCustomer( CSCCustomer& src );

		CSCCustomer&				operator=( const CSCCustomer& src );
		CSCCustomer&				operator=( const tCSCCUSTOMER& src );

		virtual int					CompareTo( const nCollectable *that ) const;

		tCSCCUSTOMER				m_Values;

		pxCustOrderTypeList*		m_CustomerOrderTypeList;
		CustomerBusinessHoursList*  m_CustomerBusinessHoursList;

};

#endif /* CSCCUSTOMER_HPP */
