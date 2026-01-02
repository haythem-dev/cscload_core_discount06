/*
 * pxrecord.hpp
 *
 *  Created on: 19.05.2015
 *  Author: sebastian.barth
 */

#include "pxbase/pxrecord.hpp"
#include "pxsess.hpp"

pxSession* pxDBRecord::Session() const
{
    return (pxSession*)nDBRecord::Session();
}

std::ifstream* pxDBRecord::CMsgStream() const
{
    return Session()->CMsgStream();
}
