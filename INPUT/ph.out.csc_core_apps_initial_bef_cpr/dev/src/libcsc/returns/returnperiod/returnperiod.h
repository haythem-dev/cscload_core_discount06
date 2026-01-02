#ifndef GUARD_LIBCSC_RETURNS_RETURNPERIOD_H
#define GUARD_LIBCSC_RETURNS_RETURNPERIOD_H

#include <datatypes/int16.h>
#include <datatypes/varstring.h>

namespace libcsc {
	namespace returns {

		class ReturnPeriod
		{
			// because of OR mapping
			friend class ReturnPeriodMapperBase;

		public:
			ReturnPeriod();
			virtual ~ReturnPeriod();

			virtual const basar::Int16&		getArticleTypeID() const;
			virtual const basar::VarString& getReturnReasonCode() const;
			virtual const basar::Int16&		getPeriodOfValidReturn() const;
			virtual const basar::VarString&	getName() const;


		private:
			libcsc::Int16		m_ArticleTypeID;
			libcsc::VarString	m_ReturnReasonCode;
			libcsc::Int16		m_PeriodOfValidReturn;
			libcsc::VarString	m_Name;

		};

	} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNPERIOD_H
