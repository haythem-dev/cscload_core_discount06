/*! $Id: unittesthelper.h 15359 2009-11-24 10:50:35Z anke.klink $                                          
*                                                  
* @file                                            
* @brief ...                                       
* @author Anke Klink                      
* @date 2009                            
*/    

#ifndef  __LIBTESTUTILS_UNITTESTHELPER_H__ 
#define  __LIBTESTUTILS_UNITTESTHELPER_H__ 

#include <iostream>
#include <UnitTest++.h>
#include <TestReporterStdout.h>  
#include <vector>  
#include <libbasarcmnutil.h> 
#include <vector>

namespace test
{ 
	struct TestSelectionList;
	/*
	 * runs a predefined list of named tests seperately
	 */
	int runTestList(
		std::vector< basar::VarString > & testList, 
		UnitTest::TestReporterStdout & reporter); 


}
#endif 

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
