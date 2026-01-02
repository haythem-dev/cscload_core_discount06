#include "infrastructure/accessor/sap/saplimitcollectionacc.h"
#include "infrastructure/accessor/sap/saplimitcollectionacc_definitions.h"
#include "infrastructure/accessor/sap/sap_definitions.h"
#include "infrastructure/accessor/backup_settings.h"

#include "infrastructure/parameter/iaccparameter.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"

#include "exception/filenotfoundexception.h"

#include <fstream>
#include <boost/filesystem.hpp>

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace sap
{
    SAPLimitCollectionACC::SAPLimitCollectionACC()
        : AccessorBase( lit::SAP_LIMIT_COLLECTION_ACC )
    {
    }

    SAPLimitCollectionACC::~SAPLimitCollectionACC()
    {
    }

    void SAPLimitCollectionACC::registerAccessorMethods( AccMethodCaller& accMethodCaller )
    {
        accMethodCaller.registerAccessMethod( lit::READ_SAP_LIMIT_COLLECTION, &SAPLimitCollectionACC::readSAPLimitsFromFile, this );
        accMethodCaller.registerAccessMethod( lit::BACKUP_SAP_LIMIT, &SAPLimitCollectionACC::backupSAPLimitFile, this );
    }

    void SAPLimitCollectionACC::setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef pdl ) const
    {
        pdl.push_back( properties::PARTNER_NO );
        pdl.push_back( properties::LIMIT      );
    }

    void SAPLimitCollectionACC::injectACCParameter( parameter::IACCParameterPtr accParam )
    {
        m_AccParameter = accParam;
    }

    parameter::IACCParameterPtr SAPLimitCollectionACC::getAccParameter() const
    {
        CHECK_INSTANCE_EXCEPTION( m_AccParameter.get() );
        return m_AccParameter;
    }

    bool SAPLimitCollectionACC::isFileExisting() const
    {
        static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();

        bool openable = false;
        basar::VarString filePath;
        try
        {
            filePath = getAccParameter()->getParameterValue( lit::SAP_LIMIT_FILE );
            std::ifstream file( filePath.c_str(), std::ifstream::in );
            openable = file.is_open();
            file.close();
        }
        catch( ... )
        {
        }

        if( ! openable )
        {
            std::ostringstream msg;
            msg <<  __FILE__ ": Could not import file '" << filePath << "'!" << std::endl
                << "Abort SAP import!" << std::endl;
            BLOG_WARN( logger, msg.str() );
        }

        return openable;
    }

    const basar::db::aspect::ExecuteResultInfo SAPLimitCollectionACC::readSAPLimitsFromFile( basar::db::aspect::AccessorPropertyTable_YIterator, 
                                                                                             bool /* flagExcept */ )
    {
        METHODNAME_DEF( SAPLimitCollectionACC, readSAPLimitsFromFile );
        static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
        BLOG_TRACE_METHOD( logger, fun );

        basar::db::aspect::ExecuteResultInfo resInfo;
        if( ! isFileExisting() )
        {
            return resInfo;
        }

        const basar::VarString accArea = getAccParameter()->getParameterValue( lit::SAP_ACCOUNTING_AREA );
        std::ifstream file( getAccParameter()->getParameterValue( lit::SAP_LIMIT_FILE ).c_str(), std::ifstream::in );
        for( basar::VarString line; file.good() && std::getline( file, line ); resInfo.m_affectedRows++ )
        {
            if( line.length() >= m_LineLength ) // ignore lines not matching length
            {
                try
                {
                    const basar::Int32 partnerNo          = line.substr(  0, 9 ).stoi();
                    const basar::VarString accountingArea = line.substr(  9, 4 );
                    const char recordType                 = line[13]; // has to be 'L' which means limit
                    basar::VarString limit                = line.substr( 22, 16 ); limit.trim( basar::VarString::ALL );

                    if( accountingArea == accArea && recordType == m_RecordType && partnerNo > 0 )
                    {
                        basar::db::aspect::AccessorPropertyTable_YIterator yit = getPropertyTable().insert( basar::FOR_CLEAN );
                    
                        yit.setInt32  ( properties::PARTNER_NO, partnerNo               );
                        yit.setDecimal( properties::LIMIT,      basar::Decimal( limit ) );
                    }
                }
                catch( std::exception& e )
                {
                    std::ostringstream msg;
                    msg << "Exception parsing string '" << line << "': " << e.what();
                    BLOG_ERROR( logger, msg.str() );
                }
            } // end if
        } // end for

        return resInfo;
    }

    const basar::db::aspect::ExecuteResultInfo SAPLimitCollectionACC::backupSAPLimitFile( basar::db::aspect::AccessorPropertyTable_YIterator, 
                                                                                          bool /* flagExcept */ )
    {
        METHODNAME_DEF( SAPLimitCollectionACC, backupSAPLimitFile );
        static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
        BLOG_TRACE_METHOD( logger, fun );

        try
        {
            boost::filesystem::path backupDir = getAccParameter()->getParameterValue( UADM_BACKUP_DIR ).c_str();
            if( ! boost::filesystem::is_directory( backupDir ) )
            {
                BLOG_WARN( logger, basar::VarString( backupDir.string().c_str() ) + basar::VarString( " doesn't exist!" ) );
                return basar::db::aspect::ExecuteResultInfo();
            }

            basar::DateTime dt = basar::DateTime::getCurrent();
            boost::filesystem::path filePath = getAccParameter()->getParameterValue( lit::SAP_LIMIT_FILE ).c_str();
            if( boost::filesystem::is_regular_file( filePath ) )
            {
                std::ostringstream dstFile;
                dstFile << filePath.stem().string() << "_" << dt.getDate() << dt.getHour() << filePath.extension().string();
                boost::filesystem::path dest = backupDir / boost::filesystem::path( dstFile.str() );

                BLOG_INFO( logger, basar::VarString( "Backup '" ) + filePath.string() + "' to '" + dest.string() + "'" );
                boost::filesystem::copy_file( filePath, dest, boost::filesystem::copy_option::overwrite_if_exists );
            }
        }
        catch( libutil::exceptions::BaseException& e )
        {
            BLOG_WARN( logger, "Backup of SAP limit file failed: " + e.reason() );
        }
        catch( std::exception& e )
        {
            BLOG_WARN( logger, basar::VarString( "Backup of SAP limit file failed: " ) + e.what() );
        }

        return basar::db::aspect::ExecuteResultInfo();
    }

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

