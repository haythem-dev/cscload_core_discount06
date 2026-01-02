/*
 * pxrecord.hpp
 *
 *  Created on: 19.05.2015
 *  Author: sebastian.barth
 */

#ifndef PXRECORD_INC
#define PXRECORD_INC

#include <database.hpp>
class pxSession;

class pxDBRecord : public nDBRecord
{
public:
    pxDBRecord() {}
    pxDBRecord(nDataBase* db) : nDBRecord(db) {}
    virtual ~pxDBRecord() {}

    pxSession* Session() const;
	std::ifstream* CMsgStream() const;
};

#endif