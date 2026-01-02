#include "SessionUtil.h"
#include "crema/maildata/maildataptr.h"
#include "crema/maildata/maildata.h"
#include "crema/maildata/maildatamapperbase.h"
#include "crema/maildata/recipient.h"
#include "crema/componentmanager/cremacomponentmanager.h"
#include "crema/componentmanager/cremacomponentmanagerptr.h"
#include "crema/repository/repository.h"
#include "crema/repository/repositoryptr.h"

using namespace std;

class MailDataMapperTest : public libcsc::crema::MailDataMapperBase
{
public:
    MailDataMapperTest(libcsc::crema::MailDataPtr mailData) : MailDataMapperBase(mailData)
    {
    }
    virtual ~MailDataMapperTest()
    {
    }

protected:
    virtual void doMap()
    {
        setSender("");
        setRecipient(0, "you");
    }

private:
    MailDataMapperTest(const MailDataMapperTest&);
    MailDataMapperTest& operator=(const MailDataMapperTest&);
};

void testCremaMaildata()
{
    SessionUtil session(5);
    pxOrderTransmit* xmit = session.get();

    basar::VarString uuid = "";

    libcsc::crema::MailDataPtr md = boost::make_shared<libcsc::crema::MailData>();
    MailDataMapperTest mapper(md);
    mapper.map();

    basar::VarString sender1 = md->getSender();

    libcsc::crema::repo::IRepositoryPtr repo = xmit->getCremaComponentManager()->getRepository();
    libcsc::crema::MailDataPtr result = repo->findMailData(uuid);

    if (result == NULL)
    {
        cout << "result == NULL" << endl;
        return;
    }

    libcsc::crema::MailData* pResult = result.get();

    if (pResult == NULL)
    {
        cout << "result.get() == NULL" << endl;
        return;
    }

    try
    {
        basar::VarString sender = result->getSender();
        cout << "sender == " << sender << endl;
    }
    catch (...)
    {
        cout << "getSender has thrown exception" << endl;
    }
}
