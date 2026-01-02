#ifndef CUSTOMERBUSINESSHOURS_HPP
#define CUSTOMERBUSINESSHOURS_HPP

#include "pxbase/pxrecord.hpp"
#include <pxrecord.h>

class nDate;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class CustomerBusinessHours : public pxDBRecord
{

	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:

									CustomerBusinessHours( pxSession* session, const short& branchno, const long& customerno );

		virtual						~CustomerBusinessHours();		

		bool						isInsideBusinessHours( const nDate& datetime ) const;

		short						getWeekday() const;
		short						getBranchNo() const;
		long						getCustomerNo() const;
		long						getBusinesshoursStart() const;
		long						getBusinesshoursEnd() const;		

	/*############################################################################################################################*/
	/*                                       P R O T E C T E D                                                                    */
	/*############################################################################################################################*/
	protected:
		
									CustomerBusinessHours( pxSession* session, tCUSTOMERBUSINESSHOURS& src );

		CustomerBusinessHours&		Assign( CustomerBusinessHours& dest, const tCUSTOMERBUSINESSHOURS& src );		
		tCUSTOMERBUSINESSHOURS&		Assign( tCUSTOMERBUSINESSHOURS&  dest, const CustomerBusinessHours& src );		

		void						Init();				

	/*############################################################################################################################*/
	/*                                       P R I V A T E                                                                        */
	/*############################################################################################################################*/
	private:									
									CustomerBusinessHours( CustomerBusinessHours& src );									

		CustomerBusinessHours&		operator=( const CustomerBusinessHours& src );
		CustomerBusinessHours&		operator=( const tCUSTOMERBUSINESSHOURS& src );

		virtual int					CompareTo( const nCollectable *that ) const;														

		tCUSTOMERBUSINESSHOURS		m_Values;		

		friend class CustomerBusinessHoursList;
};

#endif /* CUSTOMERBUSINESSHOURS_HPP */
