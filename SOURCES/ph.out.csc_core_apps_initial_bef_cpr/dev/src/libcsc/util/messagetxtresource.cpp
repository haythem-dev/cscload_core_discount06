/*
 * messagetxtresource.cpp
 *
 *  Created on: 22.06.2016
 *  Author: sebastian.barth
 */

#include "messagetxtresource.h"
#include "exceptions/invaliddataexception.h"
#include <message.hpp>
#include <libbasarcmnutil_bstring.h>

extern int pxGlobalLanguageId;

namespace libcsc {
namespace util {

MessageTxtResource::MessageTxtResource()
{
}

MessageTxtResource::~MessageTxtResource()
{
}

void MessageTxtResource::injectMsgStream(std::ifstream* msgStream)
{
    m_MsgStream = msgStream;
}

void MessageTxtResource::setLanguageCode(int languageCode)
{
    m_LanguageCode = languageCode;
}

basar::VarString MessageTxtResource::getString(basar::VarString const& key)
{
    if (!key.isDigit())
    {
        throw exceptions::InvalidDataException(basar::ExceptInfo("MessageTxtResource::getString()", "", __FILE__, __LINE__ ) );
    }
    int msgId = key.stoi();
    if (msgId <= 0)
    {
        throw exceptions::InvalidDataException(basar::ExceptInfo("MessageTxtResource::getString()", "", __FILE__, __LINE__ ) );
    }
    pxGlobalLanguageId = m_LanguageCode;
    nMessage message(m_MsgStream, msgId);
    basar::VarString msg(message.String());
    removeTrailingNewLine(msg);
    return msg;
}

void MessageTxtResource::removeTrailingNewLine(basar::VarString& message)
{
    message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
    message.erase(std::remove(message.begin(), message.end(), '\r'), message.end());
}

} // end namespace util
} // end namespace libcsc
