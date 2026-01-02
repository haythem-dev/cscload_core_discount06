//----------------------------------------------------------------------------
/*! \file	  customeracc.cpp
 *  \brief  string builder definitions for customer
 *  \author	Frank Naumann
 *  \date   25.03.2010
 */
//----------------------------------------------------------------------------

#include "commonheader.h"
#include "customeracc.h"
#include "zpldcust_definitions.h"
#include "loggerpool.h"

//----------------------------------------------------------------------------

namespace acc_customer {

//---------------------------------------------------------------------------

BUILDER_DEFINITION(SelectCustomer)

ENSURE_PROPERTIES_ARE_SET(SelectCustomer,
  lit::zpldcust::CUSTOMERNO.toPropertyString()
  )

void SelectCustomer::buildSQLString()
{
  resolve(
    "SELECT c.customerno, c.customer_name, c.postal_code, c.city, "
           "c.branchno, c.multiplecustflag "
    "FROM ccustomermaindata c "
    "WHERE c.customerno=#customerno#"
  );
  BLOG_TRACE(zpldcust::LoggerPool::zpldcust, getSQLString());
}

//---------------------------------------------------------------------------

BUILDER_DEFINITION(InsertCustomer)

ENSURE_PROPERTIES_ARE_SET_AND_ONE_IN_STATE(InsertCustomer,
  lit::zpldcust::CUSTOMERNO.toPropertyString() + 
  lit::zpldcust::CUSTOMER_NAME.toPropertyString() + 
  lit::zpldcust::POSTAL_CODE.toPropertyString() + 
  lit::zpldcust::CITY.toPropertyString() + 
  lit::zpldcust::BRANCHNO.toPropertyString() + 
  lit::zpldcust::MULTIPLECUSTFLAG.toPropertyString(),
  basar::SS_INSERT)

void InsertCustomer::buildSQLString()
{
  resolve(
    "INSERT INTO ccustomermaindata "
      "(customerno, customer_name, postal_code, city, branchno, multiplecustflag) VALUES "
      "(#customerno#, '#customer_name#', '#postal_code#', '#city#', #branchno#, #multiplecustflag#)"
  );
  BLOG_TRACE(zpldcust::LoggerPool::zpldcust, getSQLString());
}

//---------------------------------------------------------------------------

BUILDER_DEFINITION(UpdateCustomer)

ENSURE_PROPERTIES_ARE_SET_AND_ONE_IN_STATE(UpdateCustomer,
  lit::zpldcust::CUSTOMERNO.toPropertyString() + 
  lit::zpldcust::CUSTOMER_NAME.toPropertyString() + 
  lit::zpldcust::POSTAL_CODE.toPropertyString() + 
  lit::zpldcust::CITY.toPropertyString() + 
  lit::zpldcust::BRANCHNO.toPropertyString() + 
  lit::zpldcust::MULTIPLECUSTFLAG.toPropertyString(),
  basar::SS_UPDATE)

void UpdateCustomer::buildSQLString()
{
  resolve(
    "UPDATE ccustomermaindata SET "
      "customerno=#customerno#, customer_name='#customer_name#', postal_code='#postal_code#', "
      "city='#city#', branchno=#branchno#, multiplecustflag=#multiplecustflag# "
    "WHERE customerno=#customerno#"
  );
  BLOG_TRACE(zpldcust::LoggerPool::zpldcust, getSQLString());
}

//---------------------------------------------------------------------------

BEGIN_ACCESSOR_DEFINITION("AccDefinitionCustomer")

  BEGIN_PROPERTY_DESCRIPTION_LIST
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::CUSTOMERNO)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::CUSTOMER_NAME)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::POSTAL_CODE)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::CITY)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::BRANCHNO)
    PROPERTY_DESCRIPTION_LIST_ADD(lit::zpldcust::MULTIPLECUSTFLAG)
  END_PROPERTY_DESCRIPTION_LIST

//---------------------------------------------------------------------------
								
  ACCESS_METHOD("amSelectCustomer")
    SQL_BUILDER_CREATE(SelectCustomer)
    SQL_BUILDER_PUSH_BACK(SelectCustomer)

  ACCESS_METHOD("amSaveCustomer")
    SQL_BUILDER_CREATE(InsertCustomer)
    SQL_BUILDER_PUSH_BACK(InsertCustomer)
    SQL_BUILDER_CREATE(UpdateCustomer)
    SQL_BUILDER_PUSH_BACK(UpdateCustomer)

END_ACCESSOR_DEFINITION
				
//----------------------------------------------------------------------------

} // namespace acc_customer

//----------------------------------------------------------------------------
