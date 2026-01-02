/*! $Id$
*
* @file
* @brief ...
* @author NTT DATA
* @date 2021
*/




#include "config.h"
#include "basefixture.h"


namespace test
{

	// ---------------------------------------------------------------------------------------

	BaseFixture::BaseFixture()
	{

	}
	// ---------------------------------------------------------------------------------------
	BaseFixture::~BaseFixture()
	{
		//m_unitTestConnection.getSqlConnection().rollback();
		//m_unitTestConnection.disconnect();
	}

	void BaseFixture::initConnection()
	{
		m_unitTestConnection.connect("unittest");
	}

	// ---------------------------------------------------------------------------------------
}
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
