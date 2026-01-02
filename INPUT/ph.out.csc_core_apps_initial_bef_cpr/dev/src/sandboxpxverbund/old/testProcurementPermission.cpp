#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

using namespace std;

void executeTest(short sourceBranchNo, short targetBranchNo, int customerNo, int articleNo)
{
    SessionUtil session(sourceBranchNo);
    pxOrderTransmit* xmit = session.get();
    bool result = xmit->isExportPermitted(targetBranchNo, customerNo, articleNo);
    cout << "Export from branch " << sourceBranchNo << " to customer " << customerNo << " (" << targetBranchNo << ") of article " << articleNo << " is "
         << (result ? "allowed" : "forbidden") << endl;
    if (!xmit->IsGoodState())
    {
        cout << "Error: " << xmit->ErrorNumber() << " - " << xmit->ErrorMsg() << endl;
    }
}

void testProcurementPermission()
{
    short sourceBranchNo = 5;   // Fuerth/Germany
    short targetBranchNo = 57;  // Munich/Germany
    int customerNo = 9134162;   // Austria

    int articleNo = 123;        // Allowed article // TODO: correct article
    executeTest(sourceBranchNo, targetBranchNo, customerNo, articleNo);

    articleNo = 456;            // Forbidden article (no entry in table 'cimexpermission') // TODO: correct article
    executeTest(sourceBranchNo, targetBranchNo, customerNo, articleNo);
}
