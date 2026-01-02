#ifndef GUARD_LIBCSC_RETURNS_RETURNPERIODREPOSITORY_H
#define GUARD_LIBCSC_RETURNS_RETURNPERIODREPOSITORY_H

#include <returns/returnperiod/ireturnperiodrepository.h>
#include <returns/returnperiod/returnperiodptr.h>
#include <persistence/iaccessorptr.h>
#include <libbasar_definitions.h>

namespace basar {
	namespace db {
		namespace sql {
			class ResultsetRef;
		}
	}
}

namespace libcsc {
	namespace returns {

		class ReturnPeriodRepository : public IReturnPeriodRepository
		{

		public:
			ReturnPeriodRepository();
			virtual ~ReturnPeriodRepository();

			virtual void injectReturnPeriodAccessor(persistence::IAccessorPtr accessor);

			virtual ReturnPeriodPtr findReturnPeriod(const basar::VarString& returnReasonCode, const ReturnPeriodArticleTypeEnum articleTypeID) const;

		private:
			persistence::IAccessorPtr			m_SelectReturnPeriodAccessor;
			mutable ReturnPeriodCollectionPtr	m_ReturnPeriods;
		};

	} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNPERIODREPOSITORY_H
