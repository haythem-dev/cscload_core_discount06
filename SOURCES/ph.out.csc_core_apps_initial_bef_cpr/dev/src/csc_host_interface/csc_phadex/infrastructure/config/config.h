#ifndef GUARD_LIBCSC_PHADEX_CONFIG_H
#define GUARD_LIBCSC_PHADEX_CONFIG_H

#include "libbasar_definitions.h"
#include <iostream>
#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace infrastructure
{
class Config
{
public:
	Config( const basar::VarString xmlFilename );
	virtual ~Config();

	// TODO DK

	bool getValue( const basar::VarString & key, basar::VarString & value ) const;
	void toStream( std::ostream & stream = std::cout ) const;

private:
	Config( const Config & );
	Config & operator = ( const Config & );

	static void streamNodes( const PropertyTree & pt, std::ostream & stream, const basar::VarString & path );
	void readConfig( const basar::VarString & xmlFilename );
	
	typedef boost::shared_ptr<PropertyTree> PropertyTreePtr;
	PropertyTreePtr		m_PropertyColl;
};

} // namespace infrastructure
} // namespace csc_phadex

#endif	// GUARD_LIBCSC_PHADEX_CONFIG_H
