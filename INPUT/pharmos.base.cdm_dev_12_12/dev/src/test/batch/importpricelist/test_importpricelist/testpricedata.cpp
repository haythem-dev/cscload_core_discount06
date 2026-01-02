
#include <libbasarcmnutil.h> 
#include <libbasarproperty.h>
#include <libbasardbaspect.h>
#include "testpricedatafixture.h"
#include <UnitTest++.h>

namespace test
{
	SUITE(TestPriceData)
	{
		// Testvorbereitung alle aktuellen zukünftigen Preise löschen
		TEST_FIXTURE(TestPriceDataFixture, PrepareTest)
		{
			m_unitTestConnection.getCurrentConnection().beginTransaction();
			basar::db::aspect::ExecuteResultInfo deleteResult = priceDataDMPtr->deletePriceDataByPharmacyGroup(priceData.pharmacyGroupId,priceData.dateFrom);
			CHECK(deleteResult.getAffectedRows() >= 0);
			m_unitTestConnection.getCurrentConnection().commitTransaction();
		}

		TEST_FIXTURE(TestPriceDataFixture, InsertPriceData)
		{
			using namespace importpricelist::domMod::pricedata;

			m_unitTestConnection.getCurrentConnection().beginTransaction();
			basar::db::sql::ExecuteReturnInfo insertResult = priceDataDMPtr->insertPriceData(priceData);
			CHECK(insertResult.getAffectedRows() == 1);
			m_unitTestConnection.getCurrentConnection().commitTransaction();
		}

		TEST_FIXTURE(TestPriceDataFixture, SelectPriceDataByPharmacyGroup)
		{
			m_unitTestConnection.getCurrentConnection().beginTransaction();
			basar::db::aspect::ExecuteResultInfo selectResult = priceDataDMPtr->selectPriceDataByPharmacyGroup(priceData.pharmacyGroupId,priceData.dateFrom);
			CHECK(selectResult.hasError() == false);
			basar::db::aspect::AccessorPropertyTableRef selectedData = priceDataDMPtr->getPriceData();
			CHECK(selectedData.getNumberOfFetchedRows() == 1);
			basar::db::aspect::AccessorPropertyTable_YIterator priceDataIterator = selectedData.begin();
			while (!priceDataIterator.isEnd())
			{
				std::stringstream dbg;
				dbg << "Test: SelectPriceDataByPharmacyGroup:";
				dbg << "\n   priceData.pharmacygroupid: " << priceDataIterator.getString(PRICEDATA_PHARMACYGROUPID.getName());
				dbg << "\n   priceData.articleno: " << priceDataIterator.getInt32(PRICEDATA_ARTICLENO.getName());
				dbg << "\n   priceData.datefrom: " << priceDataIterator.getInt32(PRICEDATA_DATEFROM.getName());
				dbg << "\n   priceData.dateto: " << priceDataIterator.getInt32(PRICEDATA_DATETO.getName());
				dbg << "\n   priceData.quantity: " << priceDataIterator.getInt32(PRICEDATA_QUANTITY.getName());
				dbg << "\n   priceData.fixedprice: " << priceDataIterator.getDecimal(PRICEDATA_FIXEDPRICE.getName());
				dbg << "\n";

				printf(dbg.str().c_str());
				priceDataIterator++;
			}

			m_unitTestConnection.getCurrentConnection().commitTransaction();
		}
	}
}