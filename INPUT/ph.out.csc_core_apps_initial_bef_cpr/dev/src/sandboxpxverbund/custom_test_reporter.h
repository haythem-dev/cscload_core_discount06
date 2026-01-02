#include <UnitTest++/TestReporter.h>
#include <iostream>
#include <iomanip>
#include <ctime>

class CustomTestReporter : public UnitTest::TestReporter
{
public:
    CustomTestReporter(const std::string& databaseServer)
        : m_DatabaseServer(databaseServer)
    {
        std::cout << "\n\033[1;36m[INIT]\033[0m  "
                  << "[" << currentTime() << "] "
                  << "Test initialized for DB server: " << m_DatabaseServer << std::endl << std::endl;
    }

    void ReportTestStart(const UnitTest::TestDetails& test)
    {
        std::cout << "\033[1;34m[START]\033[0m "
                  << "[" << currentTime() << "] "
                  << "Suite: " << test.suiteName
                  << " | Test: " << test.testName
                  << std::endl;
    }

    void ReportFailure(const UnitTest::TestDetails& test, const char* failure)
    {
        std::cout << "\033[1;31m[FAIL]\033[0m  "
                  << "[" << currentTime() << "] "
                  << "Suite: " << test.suiteName
                  << " | Test: " << test.testName
                  << "\n  Location: " << test.filename << ":" << test.lineNumber
                  << "\n  Reason:   " << failure
                  << "\n  Suggestion: Check the logic in the test or the function being tested."
                  << std::endl;
    }

    void ReportTestFinish(const UnitTest::TestDetails& test, float secondsElapsed)
    {
        std::cout << "\033[1;32m[END]\033[0m   "
                  << "[" << currentTime() << "] "
                  << "Suite: " << test.suiteName
                  << " | Test: " << test.testName
                  << " | Dauer: " << std::fixed << std::setprecision(3) << secondsElapsed << "s"
                  << std::endl;
    }

    void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed)
    {
        std::cout << "\n\033[1;36m[SUMMARY]\033[0m "
                  << "Tests: " << totalTestCount
                  << ", Failed: " << failedTestCount
                  << ", Failures: " << failureCount
                  << ", Time: " << std::fixed << std::setprecision(3) << secondsElapsed << "s"
                  << std::endl;
    }

private:
    std::string currentTime() const
    {
        std::time_t t = std::time(NULL);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&t));
        return buf;
    }

	std::string m_DatabaseServer;
};
