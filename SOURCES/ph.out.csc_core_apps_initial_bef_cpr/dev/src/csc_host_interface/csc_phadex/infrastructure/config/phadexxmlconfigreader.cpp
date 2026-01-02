#include "phadexxmlconfigreader.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <loggerpool/csc_phadex_loggerpool.h>
#include <exceptions/invalidparameterexception.h>
#include <misc/log_macro_definitions.h>
#include <misc/metaclassmacro_definitions.h>

namespace csc_phadex
{
namespace infrastructure
{
PhadexXMLConfigReader::PhadexXMLConfigReader()
{
}

PhadexXMLConfigReader::~PhadexXMLConfigReader()
{
}

const PhadexConfigStruct PhadexXMLConfigReader::getBranchConfig( const basar::Int16 branchno ) const
{
    METHODNAME_DEF( PhadexXMLConfigReader, getBranchConfig );
    BLOG_TRACE_METHOD( LoggerPool::getLoggerCsc_phadex(), fun );

    PhadexBranchConfigCollection::const_iterator iter = m_PhadexBranchConfigCollection.find( branchno );
    if( iter != m_PhadexBranchConfigCollection.end() )
    {
        return iter->second;
    }

    try
    {
        using boost::property_tree::ptree;
        const ptree & node = m_PropertyColl.get()->get_child( "KSCRefreshSettings.Country.Branches" );
        ptree::const_iterator treeIter = node.begin();
        for( ; treeIter != node.end(); ++treeIter )
        {
            if(treeIter->first == "Branch" )
            {
                const ptree & subTree = treeIter->second;
                basar::Int16 tempBranchno = getInt16( getAttrValue( subTree, "BranchNo" ) );
                if( branchno != tempBranchno )
                {
                    continue;
                }
                PhadexConfigStruct & config = m_PhadexBranchConfigCollection[ tempBranchno ];
                config.branchno = tempBranchno;
                getGeneralConfig( config );
                getBranchConfigFromSubTree( subTree, config );
                return config;
            }
        }
    }
    catch( const boost::property_tree::ptree_error & /*e*/ )
    {
        throw libcsc::exceptions::InvalidParameterException( basar::ExceptInfo( fun, "Error reading branches from XML config file!", __FILE__, __LINE__ ) );
    }

    std::stringstream ss;
    ss << "No config found for branch <" << branchno << "> in XML config file!";
    throw libcsc::exceptions::InvalidParameterException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
}

void PhadexXMLConfigReader::getGeneralConfig( PhadexConfigStruct & config ) const
{
    METHODNAME_DEF( PhadexXMLConfigReader, getGeneralConfig );
    BLOG_TRACE_METHOD( LoggerPool::getLoggerCsc_phadex(), fun );

    using boost::property_tree::ptree;
    try
    {
        // TODO: DK noch mehr abstrahieren, Ziel im Client-Code:
        // mandatoryValue = getMandatoryValue( "KSCRefreshSettings.Country", "Country" );
        //  optionalValue = getOptionalValue(  "KSCRefreshSettings.Country.Settings.General", "LogLevel", <default_value> );
        // mandatoryValue = getMandatoryValue( "KSCRefreshSettings.Country", "Country" );
        //  optionalValue = getOptionalValue(  "KSCRefreshSettings.Country.Settings.General", "LogLevel", <default_value> );

        // assumption: only one country node in XML
        const ptree & countryNode = m_PropertyColl.get()->get_child( "KSCRefreshSettings.Country" );
        config.country = getAttrValue( countryNode, "Country" );

        const ptree & generalNode = countryNode.get_child( "Settings.General" );
        config.logLevel = getAttrValue( generalNode, "LogLevel" );
        config.pollInterval = getInt32( getAttrValue( generalNode, "PollInterval" ) );
        config.maxSelect = getInt32( getAttrValue( generalNode, "MaxSelect" ) );
        config.test = ( getAttrValue( generalNode, "Test" ) == "true" );
        config.noCICS = (getAttrValue(generalNode, "NoCICS") == "true");

        const ptree & smtpNode = countryNode.get_child( "Settings.SMTP" );
        config.smtpHost = getAttrValue( smtpNode, "Host" );
        config.smtpPort = getInt16( getAttrValue( smtpNode, "Port" ) );
        config.smtpFromEmail = getAttrValue( smtpNode, "SendMailFrom" );

        const ptree & smtpInfoNode = smtpNode.get_child( "Information" );
        config.smtpInfoEmail = getAttrValue( smtpInfoNode, "eMail" );

        const ptree & smtpWarnNode = smtpNode.get_child( "Warnings" );
        config.smtpWarningEmail = getAttrValue( smtpWarnNode, "eMail" );

        const ptree & smtpErrorNode = smtpNode.get_child( "Errors" );
        config.smtpErrorEmail = getAttrValue( smtpErrorNode, "eMail" );

        const ptree & tcaNode = countryNode.get_child( "Settings.TCAccess" );
        config.tcaTransaction = getAttrValue( tcaNode, "TCATransaction" );
        config.tcaHost = getAttrValue( tcaNode, "TCAHost" );
        config.tcaConnectionRetries = getInt32( getAttrValue( tcaNode, "ConnectionRetries" ) );
        config.tcaConnectionWaitBeforeRetry = getInt32( getAttrValue( tcaNode, "ConnectionWaitBeforeRetry" ) );
        config.tcaUsername = getAttrValue( tcaNode, "Username" );
        config.tcaPassword = getAttrValue( tcaNode, "Password" );

        const ptree & ifxNode = countryNode.get_child( "Settings.Informix" );
        config.ifxConnectionRetries = getInt32( getAttrValue( ifxNode, "ConnectionRetries" ) );
        config.ifxConnectionWaitBeforeRetry = getInt32( getAttrValue( ifxNode, "ConnectionWaitBeforeRetry" ) );
        config.ifxServiceName = getAttrValue( ifxNode, "IfxServiceName" );
        config.ifxHost = getAttrValue( ifxNode, "IfxHost" );
        config.ifxDatabase = getAttrValue( ifxNode, "IfxDataBase" );

        const ptree & pxVerbundNode = countryNode.get_child( "Settings.pxVerbund" );
        config.deviceType = getInt16( getAttrValue( pxVerbundNode, "DeviceType" ) );
        config.deviceName = getAttrValue( pxVerbundNode, "DeviceName" );
        config.messageFile = getAttrValue( pxVerbundNode, "MessageFile" );
    }
    catch( const boost::property_tree::ptree_error & /*e*/ )
    {
        throw libcsc::exceptions::InvalidParameterException( basar::ExceptInfo( fun, "Error reading general config from XML config file!", __FILE__, __LINE__ ) );
    }
}

void PhadexXMLConfigReader::getBranchConfigFromSubTree( const boost::property_tree::ptree & subTree, PhadexConfigStruct & config ) const
{
    METHODNAME_DEF( PhadexXMLConfigReader, getBranchConfigFromSubTree );
    BLOG_TRACE_METHOD( LoggerPool::getLoggerCsc_phadex(), fun );

    using boost::property_tree::ptree;
    try
    {
        ptree node = subTree.get_child("Settings.TCAccess");
        config.tcaIPAddress = getAttrValue(node, "IPAddress");
        config.tcaPort = getInt16(getAttrValue(node, "Port"));

        try
        {
            node = subTree.get_child("Settings.General");
            if (getAttrValue(node, "NoCICS") == "true")
                config.noCICS = true;
        }
        catch (const boost::property_tree::ptree_error & /*e*/)
        {
            // ignore exception!
        }
    }
    catch( const boost::property_tree::ptree_error & /*e*/ )
    {
        throw libcsc::exceptions::InvalidParameterException( basar::ExceptInfo( fun, "Error reading branch config from XML config file!", __FILE__, __LINE__ ) );
    }
}

} // namespace infrastructure
} // namespace csc_phadex

