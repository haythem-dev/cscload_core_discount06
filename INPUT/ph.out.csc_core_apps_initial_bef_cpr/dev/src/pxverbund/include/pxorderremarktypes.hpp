/*
 * pxorderremarktypes.hpp
 *
 *  Created on: 05.05.2014   Author: steffen.heinlein
*/
#ifndef PXORDERREMARKTYPES_HPP_
#define PXORDERREMARKTYPES_HPP_

#include "pxbase/pxrecord.hpp"
#include "types/orderremarktypeenum.inc"

struct tORDERREMARKTYPES;

// --------------------------------------------------------------------------------------------------- //
class pxOrderRemarkType : public pxDBRecord
{
	public:

		enum OrderRemarkLevel
		{
			eOrderRemarkTypeHeaderLevel = 0,
			eOrderRemarkTypeLineLevel = 1,
			eOrderRemarkTypeBoth = 2
		};

	public:

									pxOrderRemarkType( pxOrderRemarkType& src );

									pxOrderRemarkType( pxSession *session );

									pxOrderRemarkType( pxSession *session, tORDERREMARKTYPES& src );

		virtual						~pxOrderRemarkType();

		pxOrderRemarkType&			operator=( const pxOrderRemarkType& src );

		pxOrderRemarkType&			operator=( const tORDERREMARKTYPES& src );

		virtual int					CompareTo( const nCollectable *that, void *p,const long lparm ) const;

		bool						InsertData( const tORDERREMARKTYPES& data );

		virtual  int				Read( const void *record );

		virtual  int				Get( DBAccessMode mode = cDBGET_READONLY );

		OrderRemarkTypeEnum			RemarkType() const;

		OrderRemarkLevel			Level() const;

		const nString&				RemarkName() const;

		bool						IsValidForOrderHeader() const;

		bool						IsValidForOrderLine() const;

	protected:

		void						Init();

		OrderRemarkTypeEnum			RemarkType_;

		OrderRemarkLevel			Level_;

		nString						RemarkName_;

	private:

		tORDERREMARKTYPES&			Assign( tORDERREMARKTYPES&  dest, const pxOrderRemarkType& src );

		pxOrderRemarkType&			Assign( pxOrderRemarkType& dest, const tORDERREMARKTYPES& src );

		friend class pxOrderRemarkTypeList;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxOrderRemarkTypeList : public nDBRecordSet, public nDListCollect
{
	public:
									pxOrderRemarkTypeList( pxSession *session );

		virtual						~pxOrderRemarkTypeList();

		pxSession*					Session();

		bool						SelectOrderRemarkTypes( pxOrderRemarkType::OrderRemarkLevel level = pxOrderRemarkType::eOrderRemarkTypeBoth );

		void						Clear();

		virtual int					GetNext( const void* record, const int cursorid );

		virtual int					StartBrowse( const void *keys, const int cursorid );

		virtual int					EndBrowse( const int cursorid );

		nCollectable*				AddToList( const void  *record, const int  row );

	private:

		friend class pxOrderRemarkTypeListIter;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxOrderRemarkTypeListIter : public nDListCollectIter
{
	public:

									pxOrderRemarkTypeListIter( pxOrderRemarkTypeList& list ) : nDListCollectIter(list) {;}

	   virtual						~pxOrderRemarkTypeListIter() {;}
};
// --------------------------------------------------------------------------------------------------- //

#endif /* PXORDERREMARKTYPES_HPP_ */
