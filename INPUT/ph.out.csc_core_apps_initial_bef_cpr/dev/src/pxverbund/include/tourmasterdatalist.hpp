#ifndef TOURMASTERDATALIST_HPP
#define TOURMASTERDATALIST_HPP

#include "database.hpp"

class pxSession;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class TourMasterDataList : public nDBRecordSet, public nDListCollect
{

	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:
									TourMasterDataList( pxSession* session );

		virtual						~TourMasterDataList();

		bool						getTourMasterData( const short branchno, const nString& tourid );		
		
	/*############################################################################################################################*/
	/*                                       P R O T E C T E D                                                                    */
	/*############################################################################################################################*/
	protected:

		nCollectable*				AddToList( const void  *record, const int  row );

		void						Clear();

		virtual int				EndBrowse( const int cursorid );

		virtual int				GetNext( const void* record, const int cursorid );

		virtual int				StartBrowse( const void *keys, const int cursorid );
		
	/*############################################################################################################################*/
	/*                                       P R I V A T E                                                                        */
	/*############################################################################################################################*/				
	private:		
		
		pxSession*					getSession();			

		short						m_BranchNo;

		friend class TourMasterDataListIter;
};


/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class TourMasterDataListIter : public nDListCollectIter
{
	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:
				TourMasterDataListIter( TourMasterDataList& list ) : nDListCollectIter(list) {;}

	   virtual	~TourMasterDataListIter() {;}
};

#endif /* TOURMASTERDATALIST_HPP */
