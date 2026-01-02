#ifndef CUSTOMERTOURLIST_HPP
#define CUSTOMERTOURLIST_HPP

class CSCCustomer;
class CustomerTour;
class pxArtBase;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class CustomerTourList : public nDBRecordSet, public nDListCollect
{

	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:
									CustomerTourList( pxSession* session, const short branchno, const long customerno );

		virtual						~CustomerTourList();

		bool						getTour( const nString& tourid );

		CustomerTour*				getTour( const nString& tourid, nDate tourdate );

		bool						getTours(const nString& ordertype = "" );

		bool						getCurrentTour( const nString& tourid );

		bool						getCurrentTours(const nString& ordertype = "" );		

		nString						getFirstTourId();

		nString						getLastTourId();

		bool						isArticleDeliverable( pxArtBase* article );

		bool						isTourAvailable( const nString& tourid ); 

		bool						isTourAvailableForWeekday( const nString& tourid, short weekday ); 
		
		bool						isTourPossibleForArticle( const nString& tourid, pxArtBase* article ); 

		void						removeExpiredTours( const pxCommType* commtype );

		void						removeUnassignableTours();

		void						setIBTShuttleTourDetermination( const bool b = true );

		void						setIBTOrderImport( const bool b = true );

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
		CustomerTourList&			operator = (const CustomerTourList&);
		
		CSCCustomer*				getCustomer();		

		pxSession*					getSession();	

		bool						getToursForToday();		

		bool						getToursForToday(const nString& tourid);		

		bool						getToursForWeek();				

		bool						getToursForWeek(const nString& tourid);				

		bool						hasToursWithOrderType( const nString& ordertype );

		void						removeToursWithDepartureOnPublicHoliday();

		void						removeToursWithoutOrderType( const nString& ordertype );		

		mutable CSCCustomer*		m_Customer;

		const short					m_BranchNo;
		const long					m_CustomerNo;

		friend class CustomerTourListIter;
};


/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class CustomerTourListIter : public nDListCollectIter
{
	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:
				CustomerTourListIter( CustomerTourList& list ) : nDListCollectIter(list) {;}

	   virtual	~CustomerTourListIter() {;}
};


#endif /* CUSTOMERTOURLIST_HPP */
