#include "cmnut.h"
#include <unittest/testappl.h>
#include <iostream>

#ifdef WIN32
	#include <windows.h>
#endif

class libcscTestCollection : public libutil::unittest::TestCollection
{
public:
	libcscTestCollection()
	{
		// add( <default test yes/no>, <command line parameter>, <Testsuite name> )

		// datatypes single
		add( true, "decimal", "TestDecimal" );		
		add( true, "int32", "TestInt32" );
		add( true, "datetime", "TestDateTime" );
		add( true, "date", "TestDate" );
		add( true, "varstring", "TestVarString" );
		add( true, "propertystate", "TestPropertyState" );
		add( true, "property", "TestProperty" );
		add( true, "propertycollection", "TestPropertyCollection" );
		// datatypes all
		add( true, "datatypes", "TestDecimal" );
		add( true, "datatypes", "TestInt32" );
		add( true, "datatypes", "TestDateTime" );
		add( true, "datatypes", "TestDate" );
		add( true, "datatypes", "TestVarString" );
		add( true, "datatypes", "TestPropertyState" );
		add( true, "datatypes", "TestProperty" );
		add( true, "datatypes", "TestPropertyCollection" );

	    add( true, "discountcalculatorresult", "TestDiscountCalculatorResult" );

	    add( true, "discountcalculatorcommands", "TestDiscountCalculatorCommands" );
	
		add( true, "configfilereader", "TestConfigFileReader");


		// system tests, have to be run dedicated
	    add( false, "systemdiscount", "TestDiscountSystem" );
	    add( false, "systemdiscount_hr", "TestDiscountSystemHR" );
		add( false, "systemdiscount_hr_hierarchy", "TestDiscountSystemHRHierarchy" );
	}
} testCollection;
 
int main( int argc, char *argv[] )
{
	libutil::unittest::TestAppl appl( argc, argv, testCollection );
	int ret = appl.run();

#ifdef WIN32
	if( IsDebuggerPresent() )
	{
		if( 0 == ret )
		{
			Sleep( 2000 );
		}
		else
		{
			std::cout << "Hit <Enter> to quit..." << std::endl;
			char ch;
			std::cin.read( &ch, 1 );
		}
	}
#endif

	return ret;
}
