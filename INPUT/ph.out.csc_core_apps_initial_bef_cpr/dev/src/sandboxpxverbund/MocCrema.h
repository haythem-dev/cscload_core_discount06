#pragma once
#include <string>

class pxOrderTransmit;
class SessionUtil;

struct CremaDataSearchValues
{
    short branchno;
    int orderno;
};

// =======================================================================================================================================
// =======================================================================================================================================

class MocUserSuggestion
{
private:
    // ================================================================================================================
    // !!! Don't use a REAL branch number as in cleanup() EVERYTHING with this branch number is DELETED from zdev21 !!!
    // ================================================================================================================
    const static short branchno = 666;

    SessionUtil& _session;

public:
    MocUserSuggestion(SessionUtil& session);
    ~MocUserSuggestion();

    short getBranchNo() const;
    const char* getTestUser() const;

    void createOrder(const int customerno, const int orderno);

private:
    void cleanup();
};

// =======================================================================================================================================
// =======================================================================================================================================

class MocOpenCremaOrder
{
private:
    SessionUtil& _session;
    std::string _uuid;

public:
    MocOpenCremaOrder(SessionUtil& session);
    ~MocOpenCremaOrder();

    short createOpenCremaOrder();

private:
    void cleanup();

    CremaDataSearchValues findOrderWithoutLimitBreach();
    int findSmtpusergroupId(const short branchno, const short crematypeid);
    void createDebtmailsendEntry(const short branchno, const int orderno, const int smtpusergroupId, const short crematypeid);
    static std::string generateUUID();
};

// =======================================================================================================================================
// =======================================================================================================================================

class MocFinishedTodayCremaOrder
{
private:
    SessionUtil& _session;

public:
    MocFinishedTodayCremaOrder(SessionUtil& session);
    ~MocFinishedTodayCremaOrder();

    short createFinishedTodayCremaOrder();

private:
    void cleanup();

    CremaDataSearchValues findOrderWithoutDebtRel();
    void createDebtRelEntry(const int orderno);
};
