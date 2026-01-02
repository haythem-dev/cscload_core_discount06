#include "xmlconfigreader.h"
#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_functions.h>
//#include "loggerpool/csc_phadex_loggerpool.h"
#include <libbasarcmnutil.h>

//! don't use deprecated Boost functions
#define BOOST_SYSTEM_NO_DEPRECATED 
//! don't use deprecated Boost functions
#define BOOST_FILESYSTEM_NO_DEPRECATED

#ifdef __GNUG__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

#include <boost/property_tree/ptree.hpp>

#ifdef __GNUG__
#pragma GCC diagnostic pop
#endif

#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/filesystem.hpp>

namespace csc_phadex
{
namespace infrastructure
{
//// pimpl: hide property_tree because of compiler warnings, 
//// if included in header file
//class PropertyTree : public boost::property_tree::ptree
//{
//};

XMLConfigReader::XMLConfigReader()
{
}

XMLConfigReader::~XMLConfigReader()
{
}

//bool XMLConfigReader::getValue( const basar::VarString & key, basar::VarString & value ) const
//{
//	const boost::optional<basar::VarString> ret = m_PropertyColl->get_optional<basar::VarString>( key );
//	if( false == ret )
//	{
//		return false;
//	}
//
//	value = ret.get();
//	return true;
//}

//void XMLConfigReader::streamNodes( const PropertyTree & pt, std::ostream & stream, const basar::VarString & path )
void XMLConfigReader::streamNodes( const boost::property_tree::ptree & pt, std::ostream & stream, const basar::VarString & path )
{
	using boost::property_tree::ptree;
	ptree::const_iterator itEnd = pt.end();

	ptree::const_iterator it = pt.begin();
	for( ; it != itEnd; ++it )
	{
		basar::VarString extpath = path;
		if( false == path.empty() )
		{
			extpath += ".";
		}
		extpath += it->first;

		stream	<< "config key: <" << extpath << ">";
		if( false == it->second.data().empty() )
		{
			stream << ", config value: <" << it->second.data() << ">";
		}
		stream << std::endl;

		if( false == it->second.empty() )		// node with further children
		{
			//const PropertyTree * pPTree = static_cast<const PropertyTree *>( &( it->second ) );
			const boost::property_tree::ptree * pPTree = static_cast<const boost::property_tree::ptree *>( &( it->second ) );
			streamNodes( *pPTree, stream, extpath );
		}
	}
}

void XMLConfigReader::toStream( std::ostream & stream /* = std::cout */ ) const
{
	streamNodes( *m_PropertyColl, stream, "" );
}

bool XMLConfigReader::readConfig( const basar::VarString & xmlFilename )
{
	//m_PropertyColl = PropertyTreePtr( new PropertyTree() );
	m_PropertyColl = PropertyTreePtr( new boost::property_tree::ptree() );

	try
	{
		boost::property_tree::ptree * pPt = m_PropertyColl.get();
		boost::property_tree::read_xml( xmlFilename, *pPt, 
											boost::property_tree::xml_parser::trim_whitespace | 
											boost::property_tree::xml_parser::no_comments
												);
	}
	catch( const boost::property_tree::xml_parser::xml_parser_error & /*e*/ )
	{
		//std::stringstream ss;
		//ss << "Error parsing xml: file: " << e.filename() << ", line: " << e.line() << " - " << e.message();
		//BLOG_ERROR( csc_phadex::LoggerPool::getLoggerCsc_phadex(), ss.str().c_str() );
		return false;
	}

	return true;
}

boost::optional<const boost::property_tree::ptree &> XMLConfigReader::findAttr( const boost::property_tree::ptree & pt )
{
	using boost::property_tree::ptree;
    ptree::const_assoc_iterator p = pt.find( "<xmlattr>" );
    return ( p != pt.not_found() ? p->second : boost::optional<const ptree &>() );
}

const basar::VarString XMLConfigReader::getAttrValue( const boost::property_tree::ptree & pt, const basar::VarString & attrName )
{
	using boost::property_tree::ptree;
	if( boost::optional<const ptree &> attrs = findAttr( pt ) ) 
	{
		ptree::const_iterator iter = attrs.get().begin();
		for( ; iter != attrs.get().end(); ++iter )
		{
			if( iter->first == attrName )
			{
				return iter->second.data();
			}
		}
	}

	return "";
}

const basar::VarString XMLConfigReader::getValue( const boost::property_tree::ptree & pt, const basar::VarString & name )
{
    return pt.find( name )->second.data();
}

basar::Int16 XMLConfigReader::getInt16( const basar::VarString & value )
{
	return static_cast<basar::Int16>( value.stoi() );
}

basar::Int32 XMLConfigReader::getInt32( const basar::VarString & value )
{
	return value.stoi();
}

} // namespace infrastructure
} // namespace csc_phadex


/*
<?xml version="1.0"?>
<sked>
  <version>2</version>
  <flight>
    <carrier>BA</carrier>
    <number>4001</number>
    <date>2011-07-21</date>
  </flight>
  <flight cancelled="true">
    <carrier>BA</carrier>
    <number>4002</number>
    <date>2011-07-21</date>
  </flight>
</sked>


#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

Sked read( std::istream & is )
{
    // populate tree structure pt
    using boost::property_tree::ptree;
    ptree pt;
    read_xml(is, pt);

    // traverse pt
    Sked ans;
    BOOST_FOREACH( ptree::value_type const& v, pt.get_child("sked") ) {
        if( v.first == "flight" ) {
            Flight f;
            f.carrier = v.second.get<std::string>("carrier");
            f.number = v.second.get<unsigned>("number");
            f.date = v.second.get<Date>("date");
            f.cancelled = v.second.get("<xmlattr>.cancelled", false);
            ans.push_back(f);
        }
    }

    return ans;
}

*/