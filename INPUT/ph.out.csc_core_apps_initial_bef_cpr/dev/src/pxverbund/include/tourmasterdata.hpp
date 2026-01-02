#ifndef TOURMASTERDATA_HPP
#define TOURMASTERDATA_HPP

#include "pxbase/pxrecord.hpp"
#include "ttourmasterdata.h"

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class TourMasterData : public pxDBRecord 
{

	/*############################################################################################################################*/
	/*                                       P U B L I C                                                                          */
	/*############################################################################################################################*/
	public:

									TourMasterData( pxSession* session );

		virtual						~TourMasterData();

		long						getPickingDate() const;
		short						getBranchNo() const;
		long						getDecTour() const;
		const char*					getTourID() const;	

	/*############################################################################################################################*/
	/*                                       P R O T E C T E D                                                                    */
	/*############################################################################################################################*/
	protected:
		
		TourMasterData&				Assign( TourMasterData& dest, const tTOURMASTERDATA& src );

		tTOURMASTERDATA&			Assign( tTOURMASTERDATA&  dest, const TourMasterData& src );

		void						Init();

	/*############################################################################################################################*/
	/*                                       P R I V A T E                                                                        */
	/*############################################################################################################################*/
	private:

									TourMasterData( pxSession* session, tTOURMASTERDATA& src );

									TourMasterData( TourMasterData& src );

		TourMasterData&				operator=( const TourMasterData& src );

		TourMasterData&				operator=( const tTOURMASTERDATA& src );

		virtual int					CompareTo( const nCollectable *that ) const;

		tTOURMASTERDATA				m_Values;
		
		friend class TourMasterDataList;
};

#endif /* TOURMASTERDATA_HPP */
