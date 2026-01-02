/*
 * messagetxtresource.h
 *
 *  Created on: 22.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_UTIL_MESSAGETXTRESOURCE_H
#define GUARD_LIBCSC_UTIL_MESSAGETXTRESOURCE_H

#include "istringresource.h"
#include <sstream>

namespace libcsc {
namespace util {

class MessageTxtResource : public util::IStringResource
{
public:
    MessageTxtResource();
    virtual ~MessageTxtResource();

    void injectMsgStream(std::ifstream* msgStream);
    void setLanguageCode(int languageCode);

    virtual basar::VarString getString(basar::VarString const& key);

private:
    std::ifstream* m_MsgStream;
    int m_LanguageCode;

    void removeTrailingNewLine(basar::VarString& message);
};

typedef boost::shared_ptr<MessageTxtResource> MessageTxtResourcePtr;

} // end namespace util
} // end namespace libcsc

#endif // GUARD_LIBCSC_UTIL_MESSAGETXTRESOURCE_H
