/*! $Id: testselectionlist.h 15359 2009-11-24 10:50:35Z anke.klink $                                          
*                                                  
* @file                                            
* @brief ...                                       
* @author Anke Klink                      
* @date 2009                            
*/    


#ifndef  __LIBTESTUTILS_TESTSELECTION_H__ 
#define  __LIBTESTUTILS_TESTSELECTION_H__ 

#include <iostream>
#include <UnitTest++.h>
#include <TestReporterStdout.h>  
#include <vector>  
#include <libbasarcmnutil.h> 
#include <vector>
#include <map>
namespace test
{	 
	/*!
	* A Selection/Group of none, one ore more unitTest Suite Names, that are
	* grouped together under one name
	*/
	struct NamedTestSelection
	{
		bool m_runDefault;
		basar::VarString m_name;
		std::vector<basar::VarString > m_tests;


		NamedTestSelection::NamedTestSelection( );
		NamedTestSelection(bool runDefault, const basar::VarString & name);
		NamedTestSelection(const basar::VarString & name, const basar::VarString & testname);
		NamedTestSelection(bool runDefault, const basar::VarString & name, const basar::VarString & testname);
		NamedTestSelection(bool runDefault, const basar::VarString & name, const std::vector<basar::VarString> & testname);
	};

	/*!
	* A Selection of a list of grouped  unitTest Suite Names. The groups can be called seperately, 
	* with runOneTest(groupname, reporter) or as one group, with runDefaultTests(reporter), then all
	* groups that have the m_runDefault Parameter as true, are run sequential.
	* The Testgroups can be added by the various addTestToList methods. You can add a testsuite 
	* more than once, it is usefull then to set the runDefault only once.
	*/
	struct TestSelectionList
	{
		std::map<basar::VarString , NamedTestSelection> m_map;

		void addTestToList(bool runDefault, const basar::VarString & name, const basar::VarString & testname);
		void addTestToList(bool runDefault, const basar::VarString & name);
		void addTestToList(bool runDefault, const basar::VarString & name, const std::vector<basar::VarString> & testname);

		void addDefaultTestsToVec(std::vector<basar::VarString> & vec);
		void addTestsToVec(const basar::VarString & name, std::vector<basar::VarString> & );

		int runDefaultTests(UnitTest::TestReporterStdout & reporter); 
		int runOneTest( const basar::VarString & name,UnitTest::TestReporterStdout & reporter); 

	}; 
}
#endif 

// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
