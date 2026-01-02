/*! $Id$
*
* @file
* @brief ...
* @author NTT DATA
* @date 2021
*/


#ifndef  __TEST_BASEFIXTURE_H__ 
#define  __TEST_BASEFIXTURE_H__ 

#include "utils/unittestconnection.h"
namespace test
{
	/**
	*
	*/
	class BaseFixture
	{
	private:
	protected:
	public:
		BaseFixture();
		virtual ~BaseFixture();
		void initConnection();

	protected:
		test::utils::UnitTestConnection		m_unitTestConnection;	//database connection
	};

}
#endif 

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
