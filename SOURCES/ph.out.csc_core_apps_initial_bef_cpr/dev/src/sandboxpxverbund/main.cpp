#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestReporterStdout.h>
#include <UnitTest++/TestRunner.h>
#include <cstring>
#include "custom_test_reporter.h"
#include "SessionUtil.h"
#include "CommandLineParser.h"

// ------------------------------------------------------------------------------------------- //

struct TestNamePredicate
{
    const char* suite;
    const char* test;
    TestNamePredicate(const char* suiteName, const char* testName)
        : suite(suiteName), test(testName) {
    }

    bool operator()(const UnitTest::Test* t) const
    {
        return (std::strcmp(t->m_details.suiteName, suite) == 0) &&
            (std::strcmp(t->m_details.testName, test) == 0);
    }
};

// ------------------------------------------------------------------------------------------- //

static int runAllTests()
{
    CustomTestReporter reporter(SessionUtil::getDatabaseServer());
    UnitTest::TestRunner runner(reporter);
    int failedTests = 0;

    // Alle Tests ausführen, aber mit CustomTestReporter
    failedTests += runner.RunTestsIf(UnitTest::Test::GetTestList(), 0, UnitTest::True(), 0);
    return failedTests;
}

// ------------------------------------------------------------------------------------------- //

static int runSpecificTestSuite(std::string testSuiteName)
{
    CustomTestReporter reporter(SessionUtil::getDatabaseServer());
    UnitTest::TestRunner runner(reporter);
    int failedTests = 0;

    // Nur die Suite "TourManager" ausführen
    // Der dritte Parameter ist ein Prädikat, das immer true liefert (alle Tests der Suite)
    failedTests += runner.RunTestsIf(UnitTest::Test::GetTestList(), testSuiteName.c_str(), UnitTest::True(), 0);
    return failedTests;
}

// ------------------------------------------------------------------------------------------- //

// Nur die Suite "TourManager" ausführen
/*
static int runSpecificTestSuite()
{
    return runSpecificTestSuite("TourManager");
}
*/
// ------------------------------------------------------------------------------------------- //

static int runSpecificTest(std::string testSuiteName, std::string testName)
{
    CustomTestReporter reporter(SessionUtil::getDatabaseServer());
    UnitTest::TestRunner runner(reporter);
    int failedTests = 0;

    failedTests += runner.RunTestsIf(
        UnitTest::Test::GetTestList(),
        testSuiteName.c_str(),
        TestNamePredicate(testSuiteName.c_str(), testName.c_str()),
        0
    );
    return failedTests;
}

// ------------------------------------------------------------------------------------------- //

// Nur den Test "TourManager_determineFollowingTour" aus der Suite "TourManager" ausführen
/*
static int runSpecificTest()
{
    return runSpecificTest("TourManager", "TourManager_determineFollowingTour");
}
*/
// ------------------------------------------------------------------------------------------- //

int main(int argc, char** argv)
{
    CommandLineParser cmdParser(argc, argv);

    if (!cmdParser.getPositional().empty())
    {
        SessionUtil::setDatabaseServer(cmdParser.getPositional()[0]);
    }

    int failedTests = 0;

    if (cmdParser.hasOption("testsuite"))
    {
        if (cmdParser.hasOption("test"))
        {
            failedTests += runSpecificTest(cmdParser.getOption("testsuite"), cmdParser.getOption("test"));
        }
        else
        {
            failedTests += runSpecificTestSuite(cmdParser.getOption("testsuite"));
        }
    }
    else
    {
        failedTests += runAllTests();
    }

    return failedTests;
}

// ------------------------------------------------------------------------------------------- //
