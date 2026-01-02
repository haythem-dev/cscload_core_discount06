#ifndef PXORDERITEMTOUR_HPP
#define PXORDERITEMTOUR_HPP

#include "pxbase/pxrecord.hpp"
#include <pxrecord.h>
#include <date.hpp>

class TourInfo;
class pxCommType;

// --------------------------------------------------------------------------------------------------- //
class pxOrderItemTour : public pxDBRecord
{
	public:

												pxOrderItemTour( pxOrderItemTour& src );

												pxOrderItemTour( pxSession *session );

												pxOrderItemTour( pxSession *session, tKDAUFTRAGPOSTOUR& src );

		virtual									~pxOrderItemTour();

		pxOrderItemTour&						operator=( const pxOrderItemTour& src );

		pxOrderItemTour&						operator=( const tKDAUFTRAGPOSTOUR& src );

		friend pxOrderItemTour&					Assign( pxOrderItemTour& dest, const tKDAUFTRAGPOSTOUR& src );

		friend tKDAUFTRAGPOSTOUR&				Assign( tKDAUFTRAGPOSTOUR& dest, const pxOrderItemTour& src);

		virtual int								CompareTo( const nCollectable *that, void *p,const long lparm ) const;

		virtual  int							Read( const void *record );

		virtual  int							Get( DBAccessMode mode = cDBGET_READONLY );

		long									getOrderNo() const;

		long									getLineNo() const;

		short									getDeliveryBranchNo() const;

		long									getDeliveryDate() const;

		short									getDeliveryTime() const;

		nString									getTourId() const;

		long									getDepartureDate() const;

		short									getDepartureTime() const;

		nDate									getTourDepartureDateTime(const bool normalized = false) const;

		long									getDrivingDuration() const;

		short									getDeliveryTimeBuffer() const;

		nString									getIBTTourId() const;

		long									getIBTCustomerNo() const;

		short									getIBTType() const;

		short									getDayIBT() const;

		nDate									getTourClosingDateTime(short branchno, long customerno, const pxCommType* pickingtype);

		long									getIBTTourDate() const;

		long									getIBTDepartureDate() const;

		long									getIBTDepartureTime() const;

		nDate									getIBTTourDepartureDateTime() const;

	protected:

		void									Init();

		tKDAUFTRAGPOSTOUR						m_OrderItemTourData;

	private:

		tKDAUFTRAGPOSTOUR&						Assign( tKDAUFTRAGPOSTOUR&  dest, const pxOrderItemTour& src );

		pxOrderItemTour&						Assign( pxOrderItemTour& dest, const tKDAUFTRAGPOSTOUR& src );

		friend class pxOrderItemTourList;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxOrderItemTourList : public nDBRecordSet, public nDListCollect
{
	public:
										pxOrderItemTourList( pxSession *session );

		virtual							~pxOrderItemTourList();

		pxSession*						Session();

		bool							AddOrderItemTour( const long& cscorderno, const long& positionno, const TourInfo& tourinfo );

		bool							RemoveOrderItemTour( const long& cscorderno, const long& positionno );

		bool							RemoveOrderItemTourIBT( const long& cscorderno, const long& positionno );

		bool							SelectOrderItemTour( const long& cscorderno, const long& positionno );

		int								SelectForOrder(const long& cscorderno);

		void							Clear();

		virtual int					GetNext( const void* record, const int cursorid );

		virtual int					StartBrowse( const void *keys, const int cursorid );

		virtual int					EndBrowse( const int cursorid );

		nCollectable*					AddToList( const void  *record, const int  row );

	private:

		bool							InsertData( const tKDAUFTRAGPOSTOUR& data );

		friend class pxOrderItemTourListIter;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxOrderItemTourListIter : public nDListCollectIter
{
	public:

									pxOrderItemTourListIter( pxOrderItemTourList& list ) : nDListCollectIter(list) {;}

	   virtual						~pxOrderItemTourListIter() {;}
};
// --------------------------------------------------------------------------------------------------- //

#endif /* PXORDERITEMTOUR_HPP */
