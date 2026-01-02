/*
 * pxorderremarks.hpp
 *
 *  Created on: 05.05.2014   Author: steffen.heinlein
*/
#ifndef PXORDERREMARKS_HPP_
#define PXORDERREMARKS_HPP_

#include "pxorderremarktypes.hpp"
//#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
struct tORDERREMARKS;

// --------------------------------------------------------------------------------------------------- //
class pxGenericOrderRemark : public pxDBRecord
{	
	public:

												pxGenericOrderRemark( pxGenericOrderRemark& src );

												pxGenericOrderRemark( pxSession *session );

												pxGenericOrderRemark( pxSession *session, tORDERREMARKS& src );

		virtual									~pxGenericOrderRemark();

		pxGenericOrderRemark&					operator=( const pxGenericOrderRemark& src );

		pxGenericOrderRemark&					operator=( const tORDERREMARKS& src );

		virtual int								CompareTo( const nCollectable *that, void *p,const long lparm ) const;

		virtual  int							Read( const void *record );

		virtual  int							Get( DBAccessMode mode = cDBGET_READONLY );
		virtual  int                            Delete();

		long									CSCOrderNo() const;

		long									PositionNo() const;

		OrderRemarkTypeEnum						RemarkType() const;

		short									TextNumber() const;

		const basar::VarString&					RemarkText() const;

	protected:

		void									Init();

		long									CSCOrderNo_;

		long									PositionNo_;

		OrderRemarkTypeEnum						RemarkType_;

		short									TextNumber_;

		basar::VarString						RemarkText_;

	private:		

		tORDERREMARKS&							Assign( tORDERREMARKS&  dest, const pxGenericOrderRemark& src );

		pxGenericOrderRemark&					Assign( pxGenericOrderRemark& dest, const tORDERREMARKS& src );

		friend class pxGenericOrderRemarkList;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxGenericOrderRemarkList : public nDBRecordSet, public nDListCollect
{
	public:
							pxGenericOrderRemarkList( pxSession *session );
		virtual				~pxGenericOrderRemarkList();
		pxSession*			Session();

		bool				AddOrderRemark( const long cscorderno, const long positionno, const OrderRemarkTypeEnum remarktype, const basar::VarString& remarktext, const short textnumber = 0 );
		bool				ChangeOrderRemark( const long cscorderno, const long positionno, const OrderRemarkTypeEnum remarktype, const basar::VarString& remarktext, const short textnumber = 0 );
		bool				RemoveOrderRemark( const long cscorderno, const long positionno, const OrderRemarkTypeEnum remarktype, const basar::VarString& remarktext, const short textnumber = 0 );

		bool				SelectOrderRemarksByOrderNo( const long cscorderno );
		bool				SelectOrderRemarksByOrderNoAndType( const long cscorderno, const OrderRemarkTypeEnum remarktype );
		bool				SelectOrderRemarksByOrderLine( const long cscorderno, const long positionno );
		bool				SelectOrderRemarksByOrderLineAndType( const long cscorderno, const long positionno, const OrderRemarkTypeEnum remarktype );

		void				Clear();

		virtual int			GetNext( const void* record, const int cursorid );
		virtual int			StartBrowse( const void *keys, const int cursorid );
		virtual int			EndBrowse( const int cursorid );
		nCollectable*		AddToList( const void  *record, const int  row );

	private:
		bool				InsertData( const tORDERREMARKS& data );

		friend class pxGenericOrderRemarkListIter;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxGenericOrderRemarkListIter : public nDListCollectIter
{
	public:

							pxGenericOrderRemarkListIter( pxGenericOrderRemarkList& list ) : nDListCollectIter(list) {;}
		virtual				~pxGenericOrderRemarkListIter() {;}
};
// --------------------------------------------------------------------------------------------------- //

#endif /* PXORDERREMARKS_HPP_ */
