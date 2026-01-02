#ifndef GUARD_CSC_SERVICE_CSCLIBTOTHRIFTHANDLERBASE_H
#define GUARD_CSC_SERVICE_CSCLIBTOTHRIFTHANDLERBASE_H

#include <pxordertransmitptr.h>

namespace csc {
namespace service {

class CscLibToThriftHandlerBase
{
public:
    CscLibToThriftHandlerBase();
    virtual ~CscLibToThriftHandlerBase();

    void injectSession(pxOrderTransmitPtr session);
    
    inline pxOrderTransmitPtr getSession() const { return m_Session; }

private:

    pxOrderTransmitPtr m_Session;

};

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_CSCLIBTOTHRIFTHANDLERBASE_H
