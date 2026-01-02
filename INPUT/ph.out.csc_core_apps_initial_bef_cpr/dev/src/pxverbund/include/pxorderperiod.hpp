/*
 * pxorderperiod.hpp
 *
 *  Created on: 29.08.2013   Author: steffen.heinlein
*/
#ifndef PXORDERPERIOD_HPP_
#define PXORDERPERIOD_HPP_

#include "pxbase/pxrecord.hpp"
#include <torderperiod.h>
#include <libbasarcmnutil_date.h>

class pxOrderPeriod : public pxDBRecord
{
	public:
								pxOrderPeriod( pxOrderPeriod& src );
								pxOrderPeriod( pxSession *session );
								pxOrderPeriod( pxSession *session, long id );
								pxOrderPeriod( pxSession *session, tORDERPERIOD& src );
		virtual					~pxOrderPeriod();
		pxOrderPeriod&			operator=( const pxOrderPeriod& src );
		pxOrderPeriod&			operator=( const tORDERPERIOD& src );
		friend pxOrderPeriod&	Assign( pxOrderPeriod& dest, const tORDERPERIOD& src );
		friend pxOrderPeriod&	Assign( tORDERPERIOD& dest, const pxOrderPeriod& src );

	public:
		virtual int				CompareTo( const nCollectable *that, void *p, const long lparm ) const;
		virtual int 			Get( DBAccessMode mode = cDBGET_READONLY );
		virtual int 			Read(const void* record);
		
		long					CustomerNo() const;
		const nString&			TourID() const;
		long					ID() const;
		short					BranchNo() const;
		short					WeekDay() const;
		long					Order_Period_ID() const;
		long					FromTime() const;
		long					ToTime() const;
		long					MainTime() const;
		const basar::Date&		ChangeDate() const;

	protected:
		void					Init();
		
		long					CustomerNo_;
		nString					TourID_;
		long					ID_;
		short					BranchNo_;
		short					WeekDay_;
		long					Order_Period_ID_;
		long					FromTime_;
		long					ToTime_;		
		long					MainTime_;
		basar::Date				ChangeDate_;

	private:
		tORDERPERIOD&			Assign( tORDERPERIOD&  dest, const pxOrderPeriod& src );
		pxOrderPeriod&			Assign( pxOrderPeriod& dest, const tORDERPERIOD& src );
		friend class			pxOrderPeriodList;		
};

class pxOrderPeriodList : public nDBRecordSet, public nDListCollect
{
	public:
								pxOrderPeriodList(pxSession *session);
		virtual					~pxOrderPeriodList();
		pxSession*				Session();

		size_t					SelectByBranchNoCustomerNo(const short FilialNr, const long IDFNr);

		tORDERPERIOD			SelectCurrentOrderPeriod( const short FilialNr, const long IDFNr, const short WeekDay );
		tORDERPERIOD			SelectCurrentOrderPeriodID( const short FilialNr, const long IDFNr );		
		tORDERPERIOD			SelectFirstOrderPeriodIDOfWeek( const short FilialNr, const long IDFNr );
		tORDERPERIOD			SelectFirstOrderPeriodByWeekday( const short FilialNr, const long IDFNr, const short WeekDay );

		pxOrderPeriod			getFirstOrderPeriodByWeekday(const short filialnr, const long idfnr, const short weekday);
		pxOrderPeriod			getCurrentOrderPeriodID(const short filialnr, const long idfnr);
		pxOrderPeriod			getCurrentOrderPeriod(const short filialnr, const long idfnr, short weekday);
			
		void					Clear();
		virtual int			GetNext( const void* record, const int cursorid );
		virtual int			StartBrowse( const void *keys, const int cursorid );
		virtual int			EndBrowse( const int cursorid );
		nCollectable*			AddToList( const void  *record, const int  row );

	private:
		friend class			pxOrderPeriodListIter;
};

class pxOrderPeriodListIter : public nDListCollectIter
{
	public:
								pxOrderPeriodListIter( pxOrderPeriodList& list );
		virtual					~pxOrderPeriodListIter() {;}
};

#endif /* PXORDERPERIOD_HPP_ */
