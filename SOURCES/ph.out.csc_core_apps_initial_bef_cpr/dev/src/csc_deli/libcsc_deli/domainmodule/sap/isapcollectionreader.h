#ifndef GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONREADER_H
#define GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONREADER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
            class AccessorPropertyTableRef;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// interface class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace sap
{
    class ISAPCollectionReader
    {
    public:
        virtual ~ISAPCollectionReader() {}

        // from interface
        virtual basar::db::aspect::AccessorPropertyTableRef                 get()     const  = 0;
        virtual bool                                                        isEmpty() const  = 0;

        virtual void                                                        readCollection() = 0;
        virtual void                                                        backup()  const  = 0;
    };

} // end namespace sap
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_SAP_ISAPCOLLECTIONREADER_H
