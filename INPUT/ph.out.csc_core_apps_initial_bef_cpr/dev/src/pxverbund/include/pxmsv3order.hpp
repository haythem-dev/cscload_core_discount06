/*
 * pxmsv3order.hpp
 *
 *  Created on: 27.08.2013   Author: steffen.heinlein
*/
#ifndef PXMSV3ORDER_HPP_
#define PXMSV3ORDER_HPP_

#include "pxbase/pxrecord.hpp"

struct tKDAUFTRAG;

class pxMSV3Order : public pxDBRecord
{
	public:
								pxMSV3Order( pxMSV3Order& src );
								pxMSV3Order( pxSession *session );
								pxMSV3Order( pxSession *session, tKDAUFTRAG& src );
		virtual					~pxMSV3Order();
		pxMSV3Order&			operator=( const pxMSV3Order& src );
		pxMSV3Order&			operator=( const tKDAUFTRAG& src );
		friend pxMSV3Order&		Assign( pxMSV3Order& dest, const tKDAUFTRAG& src );
		friend tKDAUFTRAG&		Assign( tKDAUFTRAG& dest, const pxMSV3Order& src );

	public:
		virtual int				CompareTo( const nCollectable *that, void *p, const long lparm ) const;
		virtual int			Get( DBAccessMode mode = cDBGET_READONLY );
		nString&				OrderLabel();
		bool					isOrderLabelEqual( nString orderlabel ) const;

	protected:
		void					Init();
		nString					OrderLabel_;

	private:
		tKDAUFTRAG&				Assign( tKDAUFTRAG&  dest, const pxMSV3Order& src );
		pxMSV3Order&			Assign( pxMSV3Order& dest, const tKDAUFTRAG& src );
		friend class			pxMSV3OrderList;
};

class pxMSV3OrderList : public nDBRecordSet, public nDListCollect
{
	public:
								pxMSV3OrderList(pxSession *session);
		virtual					~pxMSV3OrderList();
		pxSession*				Session();
	
		size_t				SelectMSV3OrderLabel( const short FilialNr, const long IDFNr, const nString& AuftragsArt, const long OrderPeriodID );
		void					Clear();
		virtual int			GetNext( const void* record, const int cursorid );
		virtual int			StartBrowse( const void *keys, const int cursorid );
		virtual int			EndBrowse( const int cursorid );
		nCollectable*			AddToList( const void  *record, const int  row );

	private:
		friend class			pxMSV3OrderListIter;
};

class pxMSV3OrderListIter : public nDListCollectIter
{
	public:
								pxMSV3OrderListIter( pxMSV3OrderList& list );
		virtual					~pxMSV3OrderListIter() {;}
};

#endif /* PXMSV3ORDER_HPP_ */
