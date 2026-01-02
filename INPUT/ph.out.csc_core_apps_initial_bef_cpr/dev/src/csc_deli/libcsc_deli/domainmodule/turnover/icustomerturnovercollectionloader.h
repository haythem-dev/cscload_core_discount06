#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVERCOLLECTIONLOADER_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVERCOLLECTIONLOADER_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//

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
namespace turnover
{
    class ICustomerTurnoverCollectionLoader
    {
    public:
        virtual ~ICustomerTurnoverCollectionLoader() {}

        virtual basar::db::aspect::AccessorPropertyTableRef         get()     const = 0;
        virtual bool                                                isEmpty() const = 0;

        virtual void                                                load()          = 0;
    };

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVERCOLLECTIONLOADER_H
