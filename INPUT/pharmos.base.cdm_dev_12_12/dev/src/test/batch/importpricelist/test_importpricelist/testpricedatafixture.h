/*! $Id$
*
* @file
* @brief ...
* @author NTT DATA
* @date 2021
*/


#ifndef  __TEST_IMPORTPRICELISTFIXTURE_H__ 
#define  __TEST_IMPORTPRICELISTFIXTURE_H__ 

#include "basefixture.h"
#include "domainmodule/pricedata/pricedatadm.h"
#include "infrastructure/accessor/pricedata/pricedataacc.h"

namespace test
{
	using namespace importpricelist::domMod::pricedata;

	class TestPriceDataFixture : public BaseFixture
	{
		private:
		protected:
		public:
			TestPriceDataFixture();
			virtual ~TestPriceDataFixture();

			void createComponents();
			void initPriceDataForTest();
			PriceData& getPriceData() { return priceData; }

		protected:
			importpricelist::domMod::pricedata::PriceDataDMPtr priceDataDMPtr;
			libutil::infrastructure::accessor::IAccessorPtr priceDataAccPtr;
			PriceData priceData;
			const log4cplus::Logger& logger;
			
	};

}
#endif 

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
