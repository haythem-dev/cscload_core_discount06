#ifndef GUARD_LIBCSC_RETURNS_RETURNPERIODMAPPERBASE_H
#define GUARD_LIBCSC_RETURNS_RETURNPERIODMAPPERBASE_H

#include "returnperiodptr.h"
#include <libbasar_definitions.h>

namespace libcsc {
	namespace returns {

		class ReturnPeriodMapperBase
		{
		public:
			ReturnPeriodMapperBase(ReturnPeriodPtr returnPeriod);

			void map();

		protected:
			virtual ~ReturnPeriodMapperBase();

			virtual void doMap() = 0;

			void setArticleTypeID(const basar::Int16& articleTypeID);
			void setReturnReasonCode(const basar::VarString& reasonCode);
			void setPeriodOfValidReturn(const basar::Int16& periodOfValidReturn);
			void setName(const basar::VarString& name);

		private:
			ReturnPeriodPtr m_ReturnPeriod;

		};

	} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNPERIODMAPPERBASE_H
