/*! $Id: testselectionlist.cpp 15359 2009-11-24 10:50:35Z anke.klink $                                          
*                                                  
* @file                                            
* @brief ...                                       
* @author Anke Klink                      
* @date 2009                            
*/    

#include "testselectionlist.h"
#include "unittesthelper.h" 
namespace test
{  
	// -------------------------------------------------------------------------
	NamedTestSelection::NamedTestSelection( ):
	m_name(""),
	m_runDefault(false)

	{ 
	}
	// -------------------------------------------------------------------------
	NamedTestSelection::NamedTestSelection(bool runDefault, const basar::VarString & name):
	m_name(name),
	m_runDefault(runDefault)
	{
	}

	// -------------------------------------------------------------------------
	NamedTestSelection::NamedTestSelection(
										const basar::VarString & name, 
										const basar::VarString & testname):
	m_name(name),
	m_runDefault(true)

	{
		m_tests.push_back(testname);
	}

	// -------------------------------------------------------------------------
	NamedTestSelection::NamedTestSelection(
										bool runDefault, 
										const basar::VarString & name, 
										const basar::VarString & testname):
	m_name(name),
	m_runDefault(runDefault)
	{
		m_tests.push_back(testname);
	}

	// -------------------------------------------------------------------------
	NamedTestSelection::NamedTestSelection(
										bool runDefault, 
										const basar::VarString & name,
										const std::vector<basar::VarString> & testname):
	m_name(name),
	m_runDefault(runDefault),
	m_tests(testname)
	{
	}

	// ----------------------------------------------------------------------------
	// TestSelectionList
	// ----------------------------------------------------------------------------


	void TestSelectionList::addTestToList(
										bool runDefault, 
										const basar::VarString & name, 
										const basar::VarString & testname)
	{
		m_map[name] = NamedTestSelection(runDefault, name, testname);
	}
	// ----------------------------------------------------------------------------


	void TestSelectionList::addTestToList(
										bool runDefault, 
										const basar::VarString & name )
	{
		m_map[name] = NamedTestSelection(runDefault, name);
	}	
	// ----------------------------------------------------------------------------


	void TestSelectionList:: addTestToList(bool runDefault, const basar::VarString & name, const std::vector<basar::VarString> & testname)
	{
		m_map[name] = NamedTestSelection(runDefault, name, testname);

	}

	// ----------------------------------------------------------------------------

	void TestSelectionList::addDefaultTestsToVec(std::vector<basar::VarString> & vec )
	{
		std::map<basar::VarString , NamedTestSelection>::const_iterator iter ; 
		for (iter = m_map.begin(); iter != m_map.end(); ++iter)
		{
			if (iter->second.m_runDefault)
			{
				std::vector<basar::VarString>::const_iterator veciter; 
				for (veciter = iter->second.m_tests.begin(); veciter != iter->second.m_tests.end(); ++veciter)
				{
					vec.push_back(*veciter);
				}
			}
		}
	}
	// ----------------------------------------------------------------------------
	void TestSelectionList::addTestsToVec(const basar::VarString & name, std::vector<basar::VarString> & vec)
	{
		std::map<basar::VarString , NamedTestSelection>::const_iterator iter =
			m_map.find(name);
		if (iter != m_map.end())
		{
			std::vector<basar::VarString>::const_iterator veciter; 
			for (veciter = iter->second.m_tests.begin(); veciter != iter->second.m_tests.end(); ++veciter)
			{
				vec.push_back(*veciter);
			}
		}
		else
		{
			vec.push_back(name); 
		}
	}
	// ----------------------------------------------------------------------------

	int TestSelectionList::runDefaultTests(UnitTest::TestReporterStdout & reporter)
	{
		std::vector<basar::VarString> list;
		addDefaultTestsToVec(list);
		return test::runTestList(list, reporter);
	}
	// ----------------------------------------------------------------------------
	int TestSelectionList::runOneTest( const basar::VarString & name,UnitTest::TestReporterStdout & reporter)
	{
		std::vector<basar::VarString> list;
		addTestsToVec(name, list);
		return test::runTestList(list, reporter);
	}
	// ----------------------------------------------------------------------------
}
// ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
