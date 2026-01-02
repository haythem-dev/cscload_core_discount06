#include <iostream>
#include <UnitTest++.h>
#include <TestReporterStdout.h>  
#include <libbasarcmnutil.h>
#include "unittesthelper.h"
#include "testselectionlist.h"

#ifdef WIN32
#pragma warning (push) 
#pragma warning(disable: 4512)
#endif

#include <QtCore/QCoreApplication>

#ifdef WIN32
#pragma warning (pop)
#endif

// all the various tests, that can be selected seperately
struct ImportPriceListSelectionList : public test::TestSelectionList
{
	// all the various tests, that can be called seperately
	ImportPriceListSelectionList()
	{
		addTestToList(false, "TestPriceData", "TestPriceData");
	}
};

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	int result = -1;

	UnitTest::TestReporterStdout reporter;

	ImportPriceListSelectionList selection;
	bool selectedTestsOnly = true;
	if (argc > 1)
	{
		basar::VarString arg = argv[1];
		if ("all" == arg)
		{
			selectedTestsOnly = false;
			UnitTest::TestRunner runner(reporter);
			result = runner.RunTestsIf(UnitTest::Test::GetTestList(),
				NULL,
				UnitTest::True(),
				0);

		}
		else
		{
			result = selection.runOneTest(basar::VarString(arg), reporter);
		}
	}
	else
	{
		result = selection.runDefaultTests(reporter);
	}

	if (selectedTestsOnly)
	{
		if (result > 0)
		{
			std::cerr << "Result: FAILURE:" << result << "  failures)." << std::endl;
			std::cout << "Result: FAILURE:" << result << "  failures)." << std::endl;
		}
		else
		{
			std::cout << "Result: all tests successfull. " << std::endl;
		}
	}

	std::cout << "Hit <Enter> to quit..." << std::endl;
	char ch;
	std::cin.read(&ch, 1);

	return(result);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+
