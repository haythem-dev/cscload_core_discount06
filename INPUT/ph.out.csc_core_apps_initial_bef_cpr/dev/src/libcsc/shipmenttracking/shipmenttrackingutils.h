#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_UTILS_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_UTILS_H

#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_date.h>
#include <libbasar_definitions.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>
#include <sstream>


namespace libcsc {
namespace shipmenttracking {

//----------------------------------------------------------------------------------
// Usefull types:
//----------------------------------------------------------------------------------

typedef std::list<basar::Int32> Int32List;

typedef std::map<basar::Int32, bool> Int32HashSetMap;
typedef std::map<basar::Int32, basar::Int32> Int32ToInt32Map;

typedef boost::shared_ptr<Int32ToInt32Map> Int32ToInt32MapPtr;

//----------------------------------------------------------------------------------
// std::list Helpers:
//----------------------------------------------------------------------------------

//NOTE: Template functions, including member functions, must be written entirely in the header files. This means that if you have a template class, its implementation must be entirely in a header file.
//      This is because the compiler needs to have access to the entire template definition (not just the signature) in order to generate code for each instantiation of the template.
//      See: https://stackoverflow.com/questions/1353973/c-template-linking-error

//! \brief a helper: It works like C# string.Join()
template<class T>
std::string stringJoin(const std::list<T>& list, const char * separator)
{
    std::stringstream resultStrm;

    for (typename std::list<T>::const_iterator it = list.begin();
        it != list.end();
        it++
        )
    {
        if (separator != NULL && resultStrm.tellp() > 0)
        {
            resultStrm << separator;
        }

        resultStrm << *it;
    }

    return resultStrm.str();
}

template<class T>
std::string stringJoin(const std::list<T>& list, std::string separator)
{
    return stringJoin(list, separator.c_str());
}

//----------------------------------------------------------------------------------
// std::map Helpers:
//----------------------------------------------------------------------------------

//! \brief a helper: It works like C# string.Join()
template<class TKey, class TValue>
std::string stringJoinKeys(const std::map<TKey, TValue>& map, const char * separator)
{
    std::stringstream resultStrm;

    for (typename std::map<TKey, TValue>::const_iterator it = map.begin();
        it != map.end();
        it++
        )
    {
        if (separator != NULL && resultStrm.tellp() > 0)
        {
            resultStrm << separator;
        }

        resultStrm << it->first;
    }

    return resultStrm.str();
}

template<class TKey, class TValue>
std::string stringJoinKeys(const std::map<TKey, TValue>& map, std::string separator)
{
    return stringJoin(map, separator.c_str());
}


} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_UTILS_H
