/*
 * pxorderrelationnotype.hpp
 *
 *  Created on: 04.08.2015   Author: steffen.heinlein
*/
#ifndef PXORDERRELATIONNOTYPE_HPP
#define PXORDERRELATIONNOTYPE_HPP

#include "pxbase/pxrecord.hpp"
#include "types/orderrelationnotypeenum.inc"

struct tORDERRELATIONNOTYPES;

// --------------------------------------------------------------------------------------------------- //
class pxOrderRelationNoType : public pxDBRecord
{
	public:

									pxOrderRelationNoType( pxOrderRelationNoType& src );

									pxOrderRelationNoType( pxSession *session );

									pxOrderRelationNoType( pxSession *session, tORDERRELATIONNOTYPES& src );

		virtual						~pxOrderRelationNoType();

		pxOrderRelationNoType&		operator=( const pxOrderRelationNoType& src );

		pxOrderRelationNoType&		operator=( const tORDERRELATIONNOTYPES& src );

		friend pxOrderRelationNoType&	Assign( pxOrderRelationNoType& dest, const tORDERRELATIONNOTYPES& src );

		friend tORDERRELATIONNOTYPES&	Assign( tORDERRELATIONNOTYPES& dest, const pxOrderRelationNoType& src);

		virtual int					CompareTo( const nCollectable *that, void *p,const long lparm ) const;

		virtual  int				Read( const void *record );

		virtual  int				Get( DBAccessMode mode = cDBGET_READONLY );

		short						getOrderRelationNoTypeValue() const;

        OrderRelationNoTypeEnum		getOrderRelationNoType() const;

		const nString&				getOrderRelationNoTypeName() const;

	protected:

		void						Init();

		short						OrderRelationNoType_;

		nString						OrderRelationNoName_;

	private:

		tORDERRELATIONNOTYPES&		Assign( tORDERRELATIONNOTYPES&  dest, const pxOrderRelationNoType& src );

		pxOrderRelationNoType&		Assign( pxOrderRelationNoType& dest, const tORDERRELATIONNOTYPES& src );

		friend class pxOrderRelationNoTypeList;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxOrderRelationNoTypeList : public nDBRecordSet, public nDListCollect
{
	public:
									pxOrderRelationNoTypeList( pxSession *session );

		virtual						~pxOrderRelationNoTypeList();

		pxSession*					Session();

		bool						SelectOrderRelationNoTypes();

		void						Clear();

		virtual int					GetNext( const void* record, const int cursorid );

		virtual int					StartBrowse( const void *keys, const int cursorid );

		virtual int					EndBrowse( const int cursorid );

		nCollectable*				AddToList( const void  *record, const int  row );

	private:

		friend class pxOrderRelationNoTypeListIter;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxOrderRelationNoTypeListIter : public nDListCollectIter
{
	public:

									pxOrderRelationNoTypeListIter( pxOrderRelationNoTypeList& list ) : nDListCollectIter(list) {;}

	   virtual						~pxOrderRelationNoTypeListIter() {;}
};
// --------------------------------------------------------------------------------------------------- //

#endif /* PXORDERRELATIONNOTYPE_HPP */
