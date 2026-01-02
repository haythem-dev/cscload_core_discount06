#ifndef GUARD_LIBCSC_PHADEX_PHADEX_XML_CONFIG_READER_H
#define GUARD_LIBCSC_PHADEX_PHADEX_XML_CONFIG_READER_H

#include "xmlconfigreader.h"
#include "phadexconfigstruct.h"
#include <map>

namespace csc_phadex
{
namespace infrastructure
{
class PhadexXMLConfigReader : public XMLConfigReader
{
public:
	PhadexXMLConfigReader();
	virtual ~PhadexXMLConfigReader();

	const PhadexConfigStruct getBranchConfig( const basar::Int16 branchno ) const;

private:
	PhadexXMLConfigReader( const PhadexXMLConfigReader & );
	PhadexXMLConfigReader & operator = ( const PhadexXMLConfigReader & );

	void getGeneralConfig( PhadexConfigStruct & config ) const;
	void getBranchConfigFromSubTree( const boost::property_tree::ptree & subTree, PhadexConfigStruct & config ) const;

	typedef std::map<basar::Int16, csc_phadex::infrastructure::PhadexConfigStruct> PhadexBranchConfigCollection;
	mutable PhadexBranchConfigCollection	m_PhadexBranchConfigCollection;
};

} // namespace infrastructure
} // namespace csc_phadex

#endif	// GUARD_LIBCSC_PHADEX_XML_CONFIG_READER_H
