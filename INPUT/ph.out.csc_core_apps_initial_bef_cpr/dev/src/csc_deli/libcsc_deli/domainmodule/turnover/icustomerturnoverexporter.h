#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVEREXPORTER_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVEREXPORTER_H

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
    class ICustomerTurnoverExporter
    {
    public:
        virtual ~ICustomerTurnoverExporter() {}

        virtual void                                                loadCustomerTurnoverCollection() = 0;
        virtual void                                                exportToSAP()                    = 0;
    };

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVEREXPORTER_H
