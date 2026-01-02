/*! $Id$
*
* @file
* @brief ...
* @author NTT DATA
* @date 2021
*/




#include "config.h"



#include "testpricedatafixture.h"
#include "domainmodule/pricedata/pricedatadm.h"
#include "infrastructure/accessor/pricedata/pricedataacc.h"
#include "loggerpool/importpricelist_loggerpool.h"


namespace test
{

	// ---------------------------------------------------------------------------------------
	using namespace importpricelist;


	TestPriceDataFixture::TestPriceDataFixture()
		:logger(LoggerPool::getLoggerAccessors())
	{
		initConnection();
		createComponents();
		initPriceDataForTest();
	}
	// ---------------------------------------------------------------------------------------
	TestPriceDataFixture::~TestPriceDataFixture()
	{
	}

	void TestPriceDataFixture::createComponents()
	{
		priceDataDMPtr = domMod::pricedata::PriceDataDMPtr(new domMod::pricedata::PriceDataDM(logger));
		priceDataAccPtr = libutil::infrastructure::accessor::AccessorProxyPtr(
			new libutil::infrastructure::accessor::AccessorProxy(infrastructure::accessor::pricedata::lit::PriceDataAcc, m_unitTestConnection.getCurrentConnection()));
		priceDataDMPtr->injectAccessor(priceDataAccPtr);
	}

	void TestPriceDataFixture::initPriceDataForTest()
	{
		basar::Int32 currentDate = basar::DateTime().getDate();

		priceData.pharmacyGroupId = 1;
		priceData.articleNo = 4711;
		priceData.dateFrom = currentDate;
		priceData.dateTo = currentDate + 10;
		priceData.quantity = 1;
		priceData.fixedPrice = (basar::Decimal) 12.99;
	}
	// ---------------------------------------------------------------------------------------

}
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
