//-------------------------------------------------------------------------------------------------//
/*! \file	pricelist2pharmacygroupdm.h
*   \brief	domain module for mapping price list to pharmacy group
*   \author NTT DATA
*   \date	13.09.2021
*/
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_PRICELIST2PHARMACYGROUPDM_H  
#define GUARD_PRICELIST2PHARMACYGROUPDM_H

#include <libutil/accessor.h>
#include <libutil/dbconnection.h>
#include <libbasardbsql.h>
#include <libbasardbaspect_accessor.h>

//-----------------------------------------------------------------------------------------

namespace log4cplus {
	class Logger;
}

//-----------------------------------------------------------------------------------------

namespace importpricelist
{
	namespace domMod
	{
		namespace pricelist2pharmacygroup
		{
			class PriceList2PharmacyGroup
			{
			public:
				basar::Int32 priceListId; 
				basar::VarString priceListName;
				basar::Int32 pharmacyGroupId;
				basar::Int16 discountType;
				basar::Int16 discountSpec;

			public:
				PriceList2PharmacyGroup();
				~PriceList2PharmacyGroup() {};
				PriceList2PharmacyGroup(const PriceList2PharmacyGroup& other);
				PriceList2PharmacyGroup& operator=(const PriceList2PharmacyGroup& other);
			};

			class PriceList2PharmacyGroupDM
			{
			public: 
				PriceList2PharmacyGroupDM(const log4cplus::Logger& logger);
				~PriceList2PharmacyGroupDM();

				virtual void injectAccessor(libutil::infrastructure::accessor::IAccessorPtr accessor) { m_Accessor = accessor; }
				virtual void injectDbConnection(libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr conn);

				bool selectPharmacyGroupByPriceListId(const basar::Int32 priceListId, PriceList2PharmacyGroup& priceList2PharmacyGroup);

			private:
				PriceList2PharmacyGroupDM(const PriceList2PharmacyGroupDM& other);
				PriceList2PharmacyGroupDM& operator=(const PriceList2PharmacyGroupDM& other);

				const log4cplus::Logger& m_Logger;
				const log4cplus::Logger& getLogger() { return m_Logger; }

				libutil::infrastructure::accessor::IAccessorPtr m_Accessor;
				libutil::infrastructure::accessor::IAccessorPtr getAccessor() { return m_Accessor; };

				basar::db::aspect::ConnectionRef m_DbConnection;
				basar::db::aspect::ConnectionRef& getDbConnection() { return m_DbConnection; };

				basar::db::aspect::AccessorPropertyTableRef getPriceList2PharmacyGroup();
			};

			typedef boost::shared_ptr< PriceList2PharmacyGroupDM > PriceList2PharmacyGroupDMPtr;

			//! List price list 2 pharmacy group properties
			CONST_PROPERTY_DESCRIPTION(PRL2PHGRP_PRICELISTID, "pricelistid", basar::DECIMAL)
			CONST_PROPERTY_DESCRIPTION(PRL2PHGRP_PRICELISTNAME, "pricelistname", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(PRL2PHGRP_PHARMACYGROUPID, "pharmacygroupid", basar::STRING)
			CONST_PROPERTY_DESCRIPTION(PRL2PHGRP_DISCOUNT_TYPE, "discounttype", basar::INT16)
			CONST_PROPERTY_DESCRIPTION(PRL2PHGRP_DISCOUNT_SPEC, "discountspec", basar::INT16)

		} // namespace pricedata
	} // namespace domMod
}// namespace importpricelist
#endif