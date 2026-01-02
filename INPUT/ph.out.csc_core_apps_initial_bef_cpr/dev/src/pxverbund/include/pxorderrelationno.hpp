/*
 * pxorderrelationno.hpp
 *
 *  Created on: 04.08.2015   Author: steffen.heinlein
*/
#ifndef PXORDERRELATIONNO_HPP_
#define PXORDERRELATIONNO_HPP_

#include "pxbase/pxrecord.hpp"
#include "pxorderrelationnotype.hpp"

struct tORDERRELATIONNO;

// --------------------------------------------------------------------------------------------------- //
class pxOrderRelationNo : public pxDBRecord
{
	public:

														pxOrderRelationNo( pxOrderRelationNo& src );

														pxOrderRelationNo( pxSession *session );

														pxOrderRelationNo( pxSession *session, tORDERRELATIONNO& src );

		virtual											~pxOrderRelationNo();

		pxOrderRelationNo&								operator=( const pxOrderRelationNo& src );

		pxOrderRelationNo&								operator=( const tORDERRELATIONNO& src );

		friend pxOrderRelationNo&						Assign( pxOrderRelationNo& dest, const tORDERRELATIONNO& src );

		friend tORDERRELATIONNO&						Assign( tORDERRELATIONNO& dest, const pxOrderRelationNo& src);

		virtual int										CompareTo( const nCollectable *that, void *p,const long lparm ) const;

		virtual  int									Read( const void *record );

		virtual  int									Get( DBAccessMode mode = cDBGET_READONLY );

		long											CSCOrderNo() const;

		long											RelationNo() const;

        OrderRelationNoTypeEnum		                    RelationNoType() const;

		short											RelationNoTypeValue() const;

	protected:

		void											Init();

		long											CSCOrderNo_;

		long											RelationNo_;

		short											RelationNoType_;

	private:

		tORDERRELATIONNO&								Assign( tORDERRELATIONNO&  dest, const pxOrderRelationNo& src );

		pxOrderRelationNo&								Assign( pxOrderRelationNo& dest, const tORDERRELATIONNO& src );

		friend class pxOrderRelationNoList;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxOrderRelationNoList : public nDBRecordSet, public nDListCollect
{
	public:
										pxOrderRelationNoList( pxSession *session );

		virtual							~pxOrderRelationNoList();

		pxSession*						Session();

		bool							SetOrderRelationNo( long cscorderno, long relationno, OrderRelationNoTypeEnum relationnotype );

		bool							RemoveOrderRelationNo( long cscorderno, OrderRelationNoTypeEnum relationnotype );

		bool							SelectOrderRelationNoByOrderNo( long cscorderno );

		bool							SelectOrderRelationNoByOrderNoAndType( long cscorderno, OrderRelationNoTypeEnum relationnotype );

		void							Clear();

		virtual int						GetNext( const void* record, const int cursorid );

		virtual int						StartBrowse( const void *keys, const int cursorid );

		virtual int						EndBrowse( const int cursorid );

		nCollectable*					AddToList( const void  *record, const int  row );

	private:

		bool							InsertData( const tORDERRELATIONNO& data );

		friend class pxOrderRelationNoListIter;
};
// --------------------------------------------------------------------------------------------------- //

// --------------------------------------------------------------------------------------------------- //
class pxOrderRelationNoListIter : public nDListCollectIter
{
	public:

									pxOrderRelationNoListIter( pxOrderRelationNoList& list ) : nDListCollectIter(list) {;}

	   virtual						~pxOrderRelationNoListIter() {;}
};
// --------------------------------------------------------------------------------------------------- //

#endif /* PXORDERRELATIONNO_HPP_ */
