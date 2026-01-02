#ifndef CUSTOMERBUSINESSHOURSLIST_HPP
#define CUSTOMERBUSINESSHOURSLIST_HPP

#include "database.hpp"

class pxSession;
class CustomerBusinessHours;
class nDate;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class CustomerBusinessHoursList : public nDBRecordSet, public nDListCollect
{

	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:
									CustomerBusinessHoursList( pxSession* session );

		virtual						~CustomerBusinessHoursList();			

		bool						getBusinessHours( const short branchno, const long& customerno );

		bool						isInsideBusinessHours( const nDate& datetime );

	/*############################################################################################################################*/
	/*                                       P R O T E C T E D                                                                    */
	/*############################################################################################################################*/
	protected:

		nCollectable*				AddToList( const void *record, const int row );

		void						Clear();

		virtual int 				EndBrowse( const int cursorid );

		virtual int 				GetNext( const void* record, const int cursorid );

		virtual int 				StartBrowse( const void *keys, const int cursorid );
		
	/*############################################################################################################################*/
	/*                                       P R I V A T E                                                                        */
	/*############################################################################################################################*/				
	private:		
		
		pxSession*					getSession();	

		friend class CustomerBusinessHoursListIter;
};


/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class CustomerBusinessHoursListIter : public nDListCollectIter
{
	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:
				CustomerBusinessHoursListIter( CustomerBusinessHoursList& list ) : nDListCollectIter(list) {;}

	   virtual	~CustomerBusinessHoursListIter() {;}
};


#endif /* CUSTOMERBUSINESSHOURSLIST_HPP */
