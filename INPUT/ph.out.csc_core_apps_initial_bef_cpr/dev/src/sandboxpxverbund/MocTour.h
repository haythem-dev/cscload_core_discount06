#pragma once
#include <string>

class SessionUtil;
class pxOrderTransmit;

class MocTour
{
private:
    // ================================================================================================================
    // !!! Don't use a REAL branch number as in cleanup() EVERYTHING with this branch number is DELETED from zdev21 !!!
    // ================================================================================================================
    const static short branchno = 666;

    SessionUtil& _session;

public:
    MocTour(SessionUtil& session);
    ~MocTour();

    short getBranchNo() const;

    void setup(long customerno);

private:
    std::string createInsertRechnerStmt() const;
    std::string createInsertKundeStmt(long customerno) const;
    std::string createInsertKundeschalterStmt(long customerno) const;
    std::string createInsertTourplantagStmt(long customerno, std::string tourid, std::string ordertype) const;
    std::string createInsertTourStmt(std::string tourid) const;
    std::string createInsertTourplantagwocheStmt(long customerno, std::string tourid) const;
    std::string createInsertTourplanwocheStmt(std::string tourid) const;

    void cleanup();
};

