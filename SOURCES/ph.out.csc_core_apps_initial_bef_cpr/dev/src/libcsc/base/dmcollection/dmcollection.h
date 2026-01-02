/*
 * dmcollection.h
 *
 *  Created on: 08.06.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_BASE_DMCOLLECTION_H
#define GUARD_LIBCSC_BASE_DMCOLLECTION_H

#include <list>

namespace log4cplus {
    class Logger;
}

namespace libcsc {
namespace base {

template<typename T>
class DmCollection
{
public:
    typedef typename std::list<T>::iterator Iterator;

    DmCollection()
    {
    }

    virtual ~DmCollection()
    {
    }

    virtual Iterator end()
    {
        return m_Values.end();
    }

    virtual Iterator begin()
    {
        return m_Values.begin();
    }

    virtual bool isEmpty() const
    {
        return m_Values.empty();
    }

    virtual typename std::list<T>::size_type count()
    {
        return m_Values.size();
    }

    virtual void clear()
    {
        m_Values.clear();
    }

    virtual void add(T value)
    {
        m_Values.push_back(value);
    }

private:
    DmCollection(const DmCollection&);
    DmCollection& operator=(const DmCollection&);

    std::list<T> m_Values;
};

} // namespace base
} // namespace libcsc

#endif // GUARD_LIBCSC_BASE_DMCOLLECTION_H
