//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       26.12.2011
 *  \version    00.00.00.01 first version
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_PROPERTIES_DEFINITIONS_H
#define GUARD_PROPERTIES_DEFINITIONS_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libbasarproperty_definitions.h>
#include <libbasarproperty_propertydescription.h>

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace properties
{
    basar::ConstString NAMESPACE_NAME( "properties" );

    CONST_PROPERTY_DESCRIPTION( ARTICLE_NO,                     "articleno",                 basar::INT32   )
    CONST_PROPERTY_DESCRIPTION( TARGET_TABLE_NAME,              "targettablename",           basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( SOURCE_TABLE_NAME,              "sourcetablename",           basar::STRING  )
    CONST_PROPERTY_DESCRIPTION( ARTICLE_ACTIVE_TAG,             "articleactivetag",          basar::INT16   )
    CONST_PROPERTY_DESCRIPTION( WITH_ARTICLE_RESERVATION_TYPE,  "WithAticleReservationType", basar::INT16   )
    CONST_PROPERTY_DESCRIPTION( DIFFERENCE_TYPE,                "DifferenceType",            basar::INT16   )
    CONST_PROPERTY_DESCRIPTION( PERSISTENCE_STRATEGY,           "PersistenceStrategy",       basar::INT16   )
}

#endif
