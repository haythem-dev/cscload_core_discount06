#ifndef GUARD_LIBCSC_PHADEX_XML_CONFIG_READER_H
#define GUARD_LIBCSC_PHADEX_XML_CONFIG_READER_H

#include "libbasar_definitions.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif
#include <boost/property_tree/xml_parser.hpp>
#ifdef __GNUC__
#pragma GCC diagnostic push
#endif

namespace csc_phadex
{
namespace infrastructure
{
// pimpl: hide property_tree because of compiler warnings, 
// if included in header file
//class PropertyTree : public boost::property_tree::ptree
//{
//};

class XMLConfigReader
{
public:
	XMLConfigReader();
	virtual ~XMLConfigReader();

	bool readConfig( const basar::VarString & xmlFilename );
	//bool getValue( const basar::VarString & key, basar::VarString & value ) const;
	void toStream( std::ostream & stream = std::cout ) const;

protected:
	//typedef boost::shared_ptr<PropertyTree> PropertyTreePtr;
	typedef boost::shared_ptr<boost::property_tree::ptree> PropertyTreePtr;
	PropertyTreePtr		m_PropertyColl;

	//static void streamNodes( const PropertyTree & pt, std::ostream & stream, const basar::VarString & path );
	static void streamNodes( const boost::property_tree::ptree & pt, std::ostream & stream, const basar::VarString & path );
	static boost::optional<const boost::property_tree::ptree &> findAttr( const boost::property_tree::ptree & pt );
	static const basar::VarString getAttrValue( const boost::property_tree::ptree & pt, const basar::VarString & attrName );
	static const basar::VarString getValue( const boost::property_tree::ptree & pt, const basar::VarString & name );

	static basar::Int16 getInt16( const basar::VarString & value );
	static basar::Int32 getInt32( const basar::VarString & value );

private:
	XMLConfigReader( const XMLConfigReader & );
	XMLConfigReader & operator = ( const XMLConfigReader & );
};

} // namespace infrastructure
} // namespace csc_phadex

inline std::ostream & operator<<( std::ostream & stream, const csc_phadex::infrastructure::XMLConfigReader & r )
{
	r.toStream( stream );
	return stream;
}

#endif	// GUARD_LIBCSC_PHADEX_XML_CONFIG_READER_H
