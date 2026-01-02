#ifndef IBTBRANCHES_HPP
#define IBTBRANCHES_HPP

#include "pxbase/pxrecord.hpp"
#include "pxrecord.h"

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class IBTBranches : public pxDBRecord
{

	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:

									IBTBranches( pxSession* session);

		virtual						~IBTBranches();		

		short						getBranchNo() const;
		short						getIBTBranchNo() const;
		short						getIBTType() const;
		short						getDayIBT() const;
		long						getIBTCustomerNo() const;
		short						getPriority() const;
		short						getActiveFlag() const;
		short						getNLevelIBTType() const;

		bool						isDayIBT() const;

	/*############################################################################################################################*/
	/*                                       P R O T E C T E D                                                                    */
	/*############################################################################################################################*/
	protected:
		
		IBTBranches&				Assign( IBTBranches& dest, const tIBTBRANCHES& src );
		
		tIBTBRANCHES&				Assign( tIBTBRANCHES&  dest, const IBTBranches& src );		

		void						Init();				

	/*############################################################################################################################*/
	/*                                       P R I V A T E                                                                        */
	/*############################################################################################################################*/
	private:

									IBTBranches( pxSession* session, tIBTBRANCHES& src );

									IBTBranches( IBTBranches& src );					

		IBTBranches&				operator=( const IBTBranches& src );

		IBTBranches&				operator=( const tIBTBRANCHES& src );

		virtual int					CompareTo( const nCollectable *that/*, void *p,const long lparm*/ ) const;												
		
		tIBTBRANCHES				m_Values;

		friend class IBTBranchesList;
};

#endif /* IBTBRANCHES_HPP */
